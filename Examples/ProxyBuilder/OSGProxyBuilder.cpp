/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include <OpenSG/OSGGraphOpSeq.h>
#include <OpenSG/OSGStripeGraphOp.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGTriangleIterator.h>
#include <OpenSG/OSGProxyGroup.h>

#include "OSGProxyBuilder.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ProxyBuilder

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ProxyBuilder::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ProxyBuilder::ProxyBuilder(void) :
    Inherited()
{
}

ProxyBuilder::ProxyBuilder(const ProxyBuilder &source) :
    Inherited(source)
{
}

ProxyBuilder::~ProxyBuilder(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ProxyBuilder::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ProxyBuilder::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ProxyBuilder NI" << std::endl;
}

void ProxyBuilder::createProxyGroup(GeometryPtr proxyBuilder)
{
    MFNodePtr parents;
    MFNodePtr::iterator pI;
    NodePtr node;
    char proxyPath[2048];
    UInt32 indices  =0;
    UInt32 triangles=0;
    UInt32 positions=0;

    if(proxyBuilder->getParents().size() == 0)
        return;

    // path name
    sprintf(proxyPath,"%s_%d.osb",_filePrefix.c_str(),_proxyNum++);

    // create geo core and copy from proxy builder
    GeometryPtr geo = Geometry::create();
    beginEditCP(geo);

    geo->setIndices(proxyBuilder->getIndices());
    (*geo->getMFIndexMapping()) = *(proxyBuilder->getMFIndexMapping());
    geo->setPositions(proxyBuilder->getPositions());
    geo->setLengths(proxyBuilder->getLengths());
    geo->setTypes(proxyBuilder->getTypes());
    geo->setNormals(proxyBuilder->getNormals());
    geo->setColors(proxyBuilder->getColors());
    geo->setSecondaryColors(proxyBuilder->getSecondaryColors());
    geo->setTexCoords(proxyBuilder->getTexCoords());
    geo->setTexCoords1(proxyBuilder->getTexCoords1());
    geo->setTexCoords2(proxyBuilder->getTexCoords2());
    geo->setTexCoords3(proxyBuilder->getTexCoords3());
    geo->setDlistCache(proxyBuilder->getDlistCache());
    endEditCP(geo);

    node = Node::create();
    addRefCP(node);
    beginEditCP(node);
    node->setCore(geo);
    endEditCP(node);

    // stripe
    osg::GraphOpSeq op;
    op.addGraphOp(new StripeGraphOp);
    op.run(node);

    // statistics
    GeoIndicesPtr indicesPtr=geo->getIndices();
    if(indicesPtr != NullFC)
        indices += indicesPtr->getSize();
    GeoPositionsPtr positionsPtr=geo->getPositions();
    if(positionsPtr != NullFC)
        positions += positionsPtr->getSize();
    for(TriangleIterator f=geo->beginTriangles() ; f!=geo->endTriangles() ; ++f)
        triangles++;

    // ignore small geos
    if(positions < _positionsThreshold) 
    {
        geo->setMaterial(proxyBuilder->getMaterial());
        parents = *proxyBuilder->getMFParents();
        // replace proxy builder
        for(pI  = parents.begin() ; pI != parents.end() ; ++pI) 
            (*pI)->setCore(geo);
    }
    else 
    {
        // write proxy file
        OSG::SceneFileHandler::the().write(node,proxyPath,_zip);

        // create proxy group
        node->updateVolume();
        OSG::ProxyGroupPtr proxy;
        proxy = ProxyGroup::create();
        beginEditCP(proxy);
        proxy->setVolume(node->getVolume());
        proxy->setConcurrentLoad(_concurrentLoad);
        proxy->setUrl(proxyPath);
        proxy->setIndices(indices);
        proxy->setTriangles(triangles);
        proxy->setPositions(positions);
        proxy->setGeometries(1);
        endEditCP(proxy);

        // create material group
        MaterialGroupPtr matGroupPtr = MaterialGroup::create();
        beginEditCP(matGroupPtr);
        matGroupPtr->setMaterial(proxyBuilder->getMaterial());
        endEditCP(matGroupPtr);

        addRefCP(proxyBuilder);
        parents = *proxyBuilder->getMFParents();
        // replace proxy builder
        for(pI  = parents.begin() ;
            pI != parents.end() ;
            ++pI) 
        {
            // create proxy child node
            NodePtr node = Node::create();
            beginEditCP(node);
            node->setCore(proxy);
            endEditCP(node);
            (*pI)->setCore(matGroupPtr);
            (*pI)->addChild(node);
        }

        // free space
        proxyBuilder->setIndices(osg::NullFC);
        proxyBuilder->getIndexMapping().clear();
        proxyBuilder->setPositions(osg::NullFC);
        proxyBuilder->setLengths(osg::NullFC);
        proxyBuilder->setTypes(osg::NullFC);
        proxyBuilder->setNormals(osg::NullFC);
        proxyBuilder->setColors(osg::NullFC);
        proxyBuilder->setSecondaryColors(osg::NullFC);
        proxyBuilder->setTexCoords(osg::NullFC);
        proxyBuilder->setTexCoords1(osg::NullFC);
        proxyBuilder->setTexCoords2(osg::NullFC);
        proxyBuilder->setTexCoords3(osg::NullFC);

        subRefCP(proxyBuilder);
    }

    // free temp node
    subRefCP(node);
}

void ProxyBuilder::createPendingProxyGroups(bool force)
{
    std::vector<GeometryPtr>::iterator gI;

    if(!force) 
    {
        // if first geo is valid, process all
        if(_geos.size() == 0 ||
           _geos[0]->getPositions() == osg::NullFC ||
           _geos[0]->getParents().size() == 0)
            return;
    }

    // reset geo proto
    Geometry::getClassType().setPrototype(_geometryProto);

    for(gI = _geos.begin() ; gI != _geos.end() ; ++gI)
    {
        createProxyGroup(*gI);
    }
    _geos.clear();

    // reset geo proto to proxy builder
    Geometry::getClassType().setPrototype(_proxyBuilderProto);
}

void ProxyBuilder::onCreate(const ProxyBuilder *source)
{
    createPendingProxyGroups();
    _geos.push_back(GeometryPtr(this));
    Inherited::onCreate(source);
}

void ProxyBuilder::start(const std::string &filePrefix,
                         UInt32 positionsThreshold,
                         bool concurrent,
                         bool zip)
{
    _filePrefix = filePrefix;
    _positionsThreshold = positionsThreshold;
    _concurrentLoad = concurrent;
    _zip = zip;
    _proxyBuilderProto = ProxyBuilder::create();
    addRefCP(_proxyBuilderProto);
    _geometryProto = Geometry::getClassType().getPrototype();
    addRefCP(_geometryProto);
    Geometry::getClassType().setPrototype(_proxyBuilderProto);
    _proxyNum = 0;
    _geos.clear();
}

void ProxyBuilder::stop()
{
    createPendingProxyGroups(true);
    Geometry::getClassType().setPrototype(_geometryProto);
}

/*------------------------------------------------------------------------*/
/*                              static fields                             */


FieldContainerPtr         ProxyBuilder::_geometryProto;
FieldContainerPtr         ProxyBuilder::_proxyBuilderProto;
UInt32                    ProxyBuilder::_proxyNum;
std::vector<GeometryPtr>  ProxyBuilder::_geos;
UInt32                    ProxyBuilder::_positionsThreshold=1000;
bool                      ProxyBuilder::_concurrentLoad=false;
bool                      ProxyBuilder::_zip=false;
std::string               ProxyBuilder::_filePrefix;

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: $";
    static Char8 cvsid_hpp       [] = OSGPROXYBUILDERBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPROXYBUILDERBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPROXYBUILDERFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

