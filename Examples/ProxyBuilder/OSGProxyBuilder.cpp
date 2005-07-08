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

    bool repaire;
    verifyIndexMap(geo,repaire);
/*
    // create index mapping, if missing
    if(geo->getIndexMapping().size() == 0) {
        UInt16 mask;
        if(geo->getPositions() != osg::NullFC) {
            printf("%d\n",geo->getPositions()->getSize());
            mask|=Geometry::MapPosition;
        }
        if(geo->getColors() != osg::NullFC) {
            printf("%d\n",geo->getColors()->getSize());
            mask|=Geometry::MapColor;
        }
        if(geo->getNormals() != osg::NullFC) {
            printf("%d\n",geo->getNormals()->getSize());
            mask|=Geometry::MapNormal;
        }
        geo->getIndexMapping().push_back(mask);
    }
*/
    // stripe
    if(_stripe)
    {
        osg::GraphOpSeq op;
        op.addGraphOp(new StripeGraphOp);
        op.run(node);
    }
#if 0
    int i;
    GeoNormals3sPtr n3s = GeoNormals3s::create();
    n3s->resize(proxyBuilder->getNormals()->getSize());
    for(i=0 ; i<proxyBuilder->getNormals()->getSize() ; ++i)
    {
        n3s->setValue(proxyBuilder->getNormals()->getValue(i),i);
    }
    geo->setNormals(n3s);

    if(proxyBuilder->getPositions()->getSize() < 65536)
    {
        GeoIndicesUI16Ptr i16 = GeoIndicesUI16::create();
        i16->resize(proxyBuilder->getIndices()->getSize());
        for(i=0 ; i<proxyBuilder->getIndices()->getSize() ; ++i)
        {
            i16->setValue(proxyBuilder->getIndices()->getValue(i),i);
        }
        geo->setIndices(i16);
    }
#endif
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
        printf("Vertices: %d\n",positions);

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
        // inline proxy
        if(_doInline) {
            FILE *in = fopen(proxyPath,"r");
            UInt8 c;
            while((fread(&c,1,1,in))) 
                proxy->getInline().push_back(UInt8(c));
            fclose(in);
#ifndef WIN32            
            unlink(proxyPath);
#endif
        }
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

void ProxyBuilder::createPendingProxyGroups()
{
    std::list<GeometryPtr>::iterator dI,gI;

    // reset geo proto
    Geometry::getClassType().setPrototype(_geometryProto);

    for(gI = _geos.begin() ; gI != _geos.end() ;)
    {
        if((*gI)->getPositions() != osg::NullFC &&
           (*gI)->getParents().size() != 0) 
        {
            createProxyGroup(*gI);
            dI=gI;
            ++gI;
            _geos.erase(dI);
        }
        else
        {
            ++gI;
        }
    }

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
                         bool zip,
                         bool doInline,
                         bool stripe)
{
    _filePrefix = filePrefix;
    _positionsThreshold = positionsThreshold;
    _concurrentLoad = concurrent;
    _zip = zip;
    _doInline = doInline;
    _stripe = stripe;
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
    createPendingProxyGroups();
    Geometry::getClassType().setPrototype(_geometryProto);
}


bool ProxyBuilder::verifyIndexMap(GeometryPtr &geo, bool &repair)
{
    repair = false;

    if(geo == NullFC)
        return true;

    if(geo->getIndices() == NullFC)
        return true;

    if(!geo->getIndexMapping().empty())
        return true;

    if(geo->getPositions() == NullFC)
        return true;

    UInt32 positions_size = geo->getPositions()->getSize();

    Int32 normals_size = 0;
    if(geo->getNormals() != NullFC)
        normals_size = geo->getNormals()->getSize();

    Int32 colors_size = 0;
    if(geo->getColors() != NullFC)
        colors_size = geo->getColors()->getSize();

    Int32 secondary_colors_size = 0;
    if(geo->getSecondaryColors() != NullFC)
        secondary_colors_size = geo->getSecondaryColors()->getSize();

    Int32 texccords_size = 0;
    if(geo->getTexCoords() != NullFC)
        texccords_size = geo->getTexCoords()->getSize();

    Int32 texccords1_size = 0;
    if(geo->getTexCoords1() != NullFC)
        texccords1_size = geo->getTexCoords1()->getSize();

    Int32 texccords2_size = 0;
    if(geo->getTexCoords2() != NullFC)
        texccords2_size = geo->getTexCoords2()->getSize();

    Int32 texccords3_size = 0;
    if(geo->getTexCoords3() != NullFC)
        texccords3_size = geo->getTexCoords3()->getSize();

    /*
    printf("sizes: %u %u %u %u %u %u %u %u\n", positions_size, normals_size,
                                   colors_size, secondary_colors_size,
                                   texccords_size, texccords1_size,
                                   texccords2_size, texccords3_size);
    */
    if((positions_size == normals_size || normals_size == 0) &&
       (positions_size == colors_size || colors_size == 0) &&
       (positions_size == secondary_colors_size || secondary_colors_size == 0) &&
       (positions_size == texccords_size || texccords_size == 0) &&
       (positions_size == texccords1_size || texccords1_size == 0) &&
       (positions_size == texccords2_size || texccords2_size == 0) &&
       (positions_size == texccords3_size || texccords3_size == 0))
    {
        UInt16 indexmap = 0;
        if(positions_size > 0)
            indexmap |= Geometry::MapPosition;
        if(normals_size > 0)
            indexmap |= Geometry::MapNormal;
        if(colors_size > 0)
            indexmap |= Geometry::MapColor;
        if(secondary_colors_size > 0)
            indexmap |= Geometry::MapSecondaryColor;
        if(texccords_size > 0)
            indexmap |= Geometry::MapTexCoords;
        if(texccords1_size > 0)
            indexmap |= Geometry::MapTexCoords1;
        if(texccords2_size > 0)
            indexmap |= Geometry::MapTexCoords2;
        if(texccords3_size > 0)
            indexmap |= Geometry::MapTexCoords3;

        beginEditCP(geo, Geometry::IndexMappingFieldMask);
            geo->getIndexMapping().push_back(indexmap);
        endEditCP(geo, Geometry::IndexMappingFieldMask);
        repair = true;
        return false;
    }
    else
    {
        return false;
    }

    return true;
}

/*------------------------------------------------------------------------*/
/*                              static fields                             */


FieldContainerPtr         ProxyBuilder::_geometryProto;
FieldContainerPtr         ProxyBuilder::_proxyBuilderProto;
UInt32                    ProxyBuilder::_proxyNum;
std::list<GeometryPtr>    ProxyBuilder::_geos;
UInt32                    ProxyBuilder::_positionsThreshold=1000;
bool                      ProxyBuilder::_concurrentLoad=false;
bool                      ProxyBuilder::_zip=false;
bool                      ProxyBuilder::_doInline=false;
bool                      ProxyBuilder::_stripe=false;
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

