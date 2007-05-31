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

#include <OSGConfig.h>

#include <OSGTextureGrabBackground.h>
#include <OSGPassiveBackground.h>
#include <OSGSolidBackground.h>
#include <OSGSimpleGeometry.h>
#include <OSGMaterialChunk.h>
#include <OSGImage.h>
#include <OSGMatrixCamera.h>
#include <OSGRenderActionBase.h>
#include <OSGDrawAction.h>
#include <OSGMatrixUtility.h>

#include "OSGDisplayFilterForeground.h"
#include "OSGDisplayFilter.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DisplayFilterForeground

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void DisplayFilterForeground::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

DisplayFilterForeground::DisplayFilterForeground(void) :
    Inherited()
{
}

DisplayFilterForeground::DisplayFilterForeground(const DisplayFilterForeground &source) :
    Inherited(source)
{
}

DisplayFilterForeground::~DisplayFilterForeground(void)
{
}

/*----------------------------- class specific ----------------------------*/

void DisplayFilterForeground::changed(BitVector whichField, UInt32 origin)
{
    if(whichField & FilterFieldMask) {
        clearGroups();
    }
    Inherited::changed(whichField, origin);
}

void DisplayFilterForeground::dump(      UInt32    , 
                                   const BitVector ) const
{
    SLOG << "Dump DisplayFilterForeground NI" << std::endl;
}

/*! do display correction
*/   
void DisplayFilterForeground::draw(DrawActionBase *action, Viewport *port)
{
    if (!getActive())
        return;
    
    UInt32 p,f;
    WindowPtr window = port->getParent();
    MFDisplayFilterPtr::iterator fI;

    RenderActionBase *ract = dynamic_cast<RenderActionBase*>(action);
    DrawAction       *dact = dynamic_cast<DrawAction*>(action);

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // rebuild filter, if enabled state changed
    if(_changedState.size() != getFilter().size())
    {
        clearGroups();
    }
    else
    {
        for(f = 0 ; f < getFilter().size() ; ++f)
        {
            if(_changedState[f] != getFilter()[f]->getChanged())
            {
                clearGroups();
                break;
            }
        }
    }

    // create filter
    if(_group.empty())
    {
        //int extension = Window::registerExtension("GL_ARB_texture_non_power_of_two" );
        //if(window->hasExtension(extension))
        //    _hasNonPowTwoTex = true;
        //else
        //    _hasNonPowTwoTex = false;
        _changedState.resize(getFilter().size());
        for(f = 0 ; f < getFilter().size() ; ++f)
        {
            _changedState[f] =  getFilter()[f]->getChanged();
            if(getFilter()[f]->getEnabled())
                getFilter()[f]->createFilter(this,port);
        }
    }
    // update viewport size
    for(p = 0 ; p < _port.size() ; ++p) 
    {
        _port[p]->setLeft(port->getLeft());
        _port[p]->setBottom(port->getBottom());
        _port[p]->setRight(port->getRight());
        _port[p]->setTop(port->getTop());
    }
    
    _hasNonPowTwoTex = true;    // due to changes in TexChunk
    
    // update texture transform
    if(!_hasNonPowTwoTex)
    {
        std::map<std::string,DisplayFilterGroup*>::iterator cI;
        for(cI = _group.begin() ;
            cI != _group.end() ;
            ++cI)
        {
            Matrix m;
            UInt32 tw = osgnextpower2(port->getPixelWidth());
            UInt32 th = osgnextpower2(port->getPixelHeight());
            Real32 sx = (Real32)port->getPixelWidth() / tw;
            Real32 sy = (Real32)port->getPixelHeight() / th;
            m.setScale(sx,sy,1);
            if(m != cI->second->getTextureTransform()->getMatrix())
            {
                beginEditCP(cI->second->getTextureTransform(),TextureTransformChunk::MatrixFieldMask);
                cI->second->getTextureTransform()->setMatrix(m);
                endEditCP(cI->second->getTextureTransform(),TextureTransformChunk::MatrixFieldMask);
            }
        }
    }

    // individual filter update
    for(fI = getFilter().begin() ;
        fI != getFilter().end() ;
        ++fI) {
        if((*fI)->getEnabled())
            (*fI)->updateFilter(port);
    }
    // do rendering
    for(p = 0 ; p < _port.size() ; ++p) 
    {
        // addPort() calls begin/endEditCP and that leads to crash in my (amz)
        // cluster environment, setting the viewport parent is actually what we want
        // and this works fine.
        //window->addPort(_port[p]);
        _port[p]->setParent(window);
        if(ract)
        {
            _port[p]->render(ract);
        }
        else
            if(dact)
                _port[p]->draw(dact);
        //window->subPort(_port[p]);
        _port[p]->setParent(NullFC);
    }

    glPopAttrib();
}

DisplayFilterForeground::DisplayFilterGroup *DisplayFilterForeground::findReadbackGroup(const std::string &name)
{
    DisplayFilterGroup *group;
    std::map<std::string,DisplayFilterGroup*>::iterator cI;

    std::string id = name + "_overlay";  
    cI = _group.find(name);
    if(cI !=  _group.end())
        return cI->second;
    // create group
    group = new DisplayFilterGroup(true,_port);
    _group[name] = group;
    return group;
}

DisplayFilterForeground::DisplayFilterGroup *DisplayFilterForeground::findOverlayGroup(const std::string &name)
{
    DisplayFilterGroup *group;
    std::map<std::string,DisplayFilterGroup*>::iterator cI;

    std::string id = name + "_readback";  
    cI = _group.find(id);
    if(cI !=  _group.end())
        return cI->second;
    // create group
    group = new DisplayFilterGroup(false,_port);
    _group[id] = group;
    return group;
}

void DisplayFilterForeground::clearGroups()
{
    std::map<std::string,DisplayFilterGroup*>::iterator cI;
    for(cI = _group.begin() ;
        cI != _group.end() ;
        ++cI)
        delete cI->second;
    _group.clear();
    _port.clear();
}


/*------------------------------------------------------------------------*/
/*                              DisplayFilterGroup                           */

/** A DisplayFilter group contains a background, that can be a texture
    readback backgound, a transformation node and a geometry
    with a ChunkMaterial attached to it. The idea is that 
    several filters can share the same group to avoid a texture
    readback for each filter. For example Color correction and
    distortion correction can share the same group as the first
    manipulates only the texture and the second modifies the
    geometry.
*/
DisplayFilterForeground::DisplayFilterGroup::DisplayFilterGroup(
    bool readback,
    std::vector<ViewportPtr> &ports)
{
    // create one or two viewports
    _vp = Viewport::create();
    _geometry = Geometry::create();
    _transform = ComponentTransform::create();
    _material = ChunkMaterial::create();
    _root = Node::create();
    NodePtr node = Node::create();
    MatrixCameraPtr cam = MatrixCamera::create();
    beginEditCP(node);
    beginEditCP(_vp);
    beginEditCP(_root);
    beginEditCP(_geometry);
    beginEditCP(_material);
    beginEditCP(_transform);

    createGrid(2,2);

    addRefCP(_vp);
    addRefCP(_root);

    ports.push_back(_vp);

    // camera
    cam->setNear(-1);
    cam->setFar ( 1);
    cam->setModelviewMatrix(Matrix::identity());
    cam->setProjectionMatrix(Matrix::identity());   

    Matrix proj;
    proj.setIdentity();
    MatrixOrthogonal(proj,0,1,0,1,-1,1);
    cam->setProjectionMatrix(proj);   

    // creat tree
    node->setCore(_geometry);
    _root->setCore(_transform);
    _root->addChild(node);
    _geometry->setMaterial(_material);

    _vp->setRoot(_root);
    _vp->setCamera(cam);

    if(!readback)
    {
        // no readback, create black solid backgrounds
        PassiveBackgroundPtr back = PassiveBackground::create();
        _vp->setBackground(back);
    }
    else
    {
        // image
        ImagePtr img = Image::create();
        beginEditCP(img);
        img->set(GL_RGB,1,1);
        endEditCP(img);
        // texture chunk
        _texture = TextureChunk::create();    
        beginEditCP(_texture);
        _texture->setImage(img);
        _texture->setWrapS(GL_CLAMP_TO_EDGE);
        _texture->setWrapT(GL_CLAMP_TO_EDGE);
        _texture->setMinFilter(GL_LINEAR);
        _texture->setMagFilter(GL_LINEAR);
        _texture->setScale(false);
        _texture->setEnvMode(GL_REPLACE);
        _texture->setNPOTMatrixScale(true);
        _texture->setScale(false);
        endEditCP(_texture);
        // texture grep background
        TextureGrabBackgroundPtr back = TextureGrabBackground::create();
        beginEditCP(back);
        back->setTexture(_texture);
        back->setColor(Color3f(0,0,0));
        endEditCP(back);
        _vp->setBackground(back);

        _material->addChunk(_texture);
    }

    // add texture transform chunk
    _textureTransform = TextureTransformChunk::create();
    _material->addChunk(_textureTransform);

    endEditCP(_vp);
    endEditCP(node);
    endEditCP(_root);
    endEditCP(_geometry);
    endEditCP(_material);
    endEditCP(_transform);
}

DisplayFilterForeground::DisplayFilterGroup::~DisplayFilterGroup()
{
    subRefCP(_vp);
    subRefCP(_root);
}

TextureChunkPtr DisplayFilterForeground::DisplayFilterGroup::getTexture(void)
{
    return _texture;
}

GeometryPtr DisplayFilterForeground::DisplayFilterGroup::getGeometry(void)
{
    return _geometry;
}

ChunkMaterialPtr DisplayFilterForeground::DisplayFilterGroup::getMaterial(void)
{
    return _material;
}

ComponentTransformPtr DisplayFilterForeground::DisplayFilterGroup::getTransform(void)
{
    return _transform;
}

TextureTransformChunkPtr DisplayFilterForeground::DisplayFilterGroup::getTextureTransform(void)
{
    return _textureTransform;
}

void DisplayFilterForeground::DisplayFilterGroup::createGrid(UInt32 width,UInt32 height)
{
    GeoPTypesUI8Ptr   types = GeoPTypesUI8::create();
    GeoPLengthsPtr    lens = GeoPLengthsUI32::create();    
    GeoIndicesUI32Ptr index = GeoIndicesUI32::create();   
    GeoPositions3fPtr pos = GeoPositions3f::create();
    GeoTexCoords2fPtr texcoords = GeoTexCoords2f::create();

    if(width<2)
        width = 2;
    if(height<2)
        height = 2;

    beginEditCP(pos);
    beginEditCP(texcoords);
    beginEditCP(lens);
    beginEditCP(index);

    UInt16 x,y;
    Real32 xstep,ystep;
    xstep=1.0 / (width-1);
    ystep=1.0 / (height-1);

    for(y = 0; y < height; y++)
    {
        for(x = 0; x < width; x++)
        {
            pos->push_back(Pnt3f(x*xstep,y*ystep,0));
            texcoords->push_back(Vec2f(x*xstep, y*ystep));
        }
    }

    for(y = 0; y < (height-1); y++)
    {
        types->push_back(GL_TRIANGLE_STRIP);
        lens->push_back(2 * width);
        
        for(x = 0; x < width; x++)
        {
            index->push_back((y + 1) * width + x);
            index->push_back( y      * width + x);
        }
    }

    beginEditCP(_geometry);
    _geometry->setPositions(pos);
    _geometry->setTypes(types);
    _geometry->setTexCoords(texcoords);
    _geometry->setLengths(lens);
    _geometry->setIndices(index);
    endEditCP(_geometry);

    endEditCP(pos);
    endEditCP(texcoords);
    endEditCP(lens);
    endEditCP(index);
}

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
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.19 2003/05/05 10:05:28 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGDISPLAYFILTERFOREGROUNDBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDISPLAYFILTERFOREGROUNDBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGDISPLAYFILTERFOREGROUNDFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

