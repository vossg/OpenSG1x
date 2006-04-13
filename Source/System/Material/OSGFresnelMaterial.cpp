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

#include <OSGBaseFunctions.h>

#include "OSGFresnelMaterial.h"

OSG_USING_NAMESPACE

/*! \class osg::FresnelMaterial

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FresnelMaterial::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

FresnelMaterial::FresnelMaterial(void) :
    Inherited(),
    _materialChunk(NullFC),
    _textureChunk(NullFC),
    _texGenChunk(NullFC),
    _blendChunk(NullFC),
    _img(NullFC)
{
}

FresnelMaterial::FresnelMaterial(const FresnelMaterial &source) :
    Inherited(source),
    _materialChunk(source._materialChunk),
    _textureChunk(source._textureChunk),
    _texGenChunk(source._texGenChunk),
    _blendChunk(source._blendChunk),
    _img(source._img)
{
}

FresnelMaterial::~FresnelMaterial(void)
{
    if(_sfImage.getValue() != NullFC)
        subRefCP(_sfImage.getValue());

    if(_materialChunk != NullFC)
        subRefCP(_materialChunk);

    if(_textureChunk != NullFC)
        subRefCP(_textureChunk);

    if(_texGenChunk != NullFC)
        subRefCP(_texGenChunk);

    if(_blendChunk != NullFC)
        subRefCP(_blendChunk);

    if(_img != NullFC)
        subRefCP(_img);
}

void FresnelMaterial::prepareLocalChunks(void)
{
    if(_textureChunk != NullFC)
        return;

    _img = Image::create();
    addRefCP(_img);
    
    UInt8 imgdata[] = { 255,0,0,128,  0,255,0,128,  0,0,255,255,  255,255,255,255 };
   
    beginEditCP(_img);
        _img->set( Image::OSG_RGBA_PF, 2, 2, 1, 1, 1, 0, imgdata);
    endEditCP(_img);
    
    _materialChunk = MaterialChunk::create();
    addRefCP(_materialChunk);
    
    _textureChunk = TextureChunk::create();
    addRefCP(_textureChunk);
    beginEditCP(_textureChunk);
        _textureChunk->setEnvMode(GL_DECAL);
        _textureChunk->setMinFilter(GL_LINEAR_MIPMAP_LINEAR);
        _textureChunk->setMagFilter(GL_LINEAR);
        _textureChunk->setWrapS(GL_CLAMP);
        _textureChunk->setWrapT(GL_CLAMP);
    endEditCP  (_textureChunk);

    _texGenChunk  = TexGenChunk::create();
    addRefCP(_texGenChunk);
    beginEditCP(_texGenChunk);
        _texGenChunk->setGenFuncS(GL_SPHERE_MAP);
        _texGenChunk->setGenFuncT(GL_SPHERE_MAP);
    endEditCP  (_texGenChunk);
    
    _blendChunk = BlendChunk::create();
    addRefCP(_blendChunk);
    beginEditCP(_blendChunk);
        _blendChunk->setSrcFactor (GL_SRC_ALPHA);
        _blendChunk->setDestFactor(GL_ONE_MINUS_SRC_ALPHA);
    endEditCP  (_blendChunk);
}

void FresnelMaterial::updateFresnel(void)
{
    if(getImage() == NullFC)
        return;

    if(getImage()->getPixelFormat() != Image::OSG_RGB_PF &&
       getImage()->getPixelFormat() != Image::OSG_RGBA_PF)
    {
        FWARNING(("FresnelMaterial::updateFresnel : pixelformat(%u) not supported\n", getImage()->getPixelFormat()));
        return;
    }

    if(_img->getPixelFormat() != getImage()->getPixelFormat() ||
       _img->getWidth() != getImage()->getWidth() ||
       _img->getHeight() != getImage()->getHeight())
    {
        beginEditCP(_img);
            _img->set(Image::OSG_RGBA_PF, getImage()->getWidth(), getImage()->getHeight());
        endEditCP(_img);
    }

    if(_textureChunk->getImage() != _img)
    {
        beginEditCP(_textureChunk, TextureChunk::ImageFieldMask);
            _textureChunk->setImage(_img);
        endEditCP(_textureChunk, TextureChunk::ImageFieldMask);
    }

    // copy the image and calculate the alpha values.
    UInt8 *src = getImage()->getData();
    UInt8 *dst = _img->getData();
    
    beginEditCP(_img);
    
        Real32 bias = getBias();
        Real32 offset = getIndex();
        Real32 expo = getScale();
        Int32 width = _img->getWidth();
        Int32 height = _img->getHeight();
        Int32 bpp = getImage()->getBpp();
        Int32 ws = width / 2;
        Int32 hs = height / 2;

        for(Int32 y = -hs; y < hs; ++y)
        {
            for(Int32 x = -ws; x < ws; ++x)
            {
                Real32 xs = (Real32) x / (Real32) width;
                Real32 ys = (Real32) y / (Real32) height;
                
                Real32 a = osgpow(osgsqrt(xs * xs + ys * ys), expo) * bias + offset;
                UInt32 ac = ((UInt32) (a * 255.0f)) & 0xff;
                //ac = 255 - ac;
                
                UInt32 i = (x + ws) + ((y + hs) * width);
                
                UInt32 si = i * bpp;
                UInt32 di = i * 4;
                
                dst[di++] = src[si++]; // r
                dst[di++] = src[si++]; // g
                dst[di++] = src[si];   // b
                dst[di]   = ac;        // a
            }
        }

    endEditCP(_img);

    beginEditCP(_textureChunk, TextureChunk::ImageFieldMask);
            _textureChunk->imageContentChanged();
    endEditCP(_textureChunk, TextureChunk::ImageFieldMask);
}

/*----------------------------- class specific ----------------------------*/

void FresnelMaterial::changed(BitVector whichField, UInt32 origin)
{
    prepareLocalChunks();

    if(whichField & ImageFieldMask)
    {
        if(origin & ChangedOrigin::Abstract)
        {
            if(origin & ChangedOrigin::AbstrIncRefCount)
            {
                addRefCP(_sfImage.getValue());
            }
            else
            {
                ImagePtr pImage = _sfImage.getValue();

                _sfImage.setValue(NullFC);

                setImage(pImage);
            }
        }
        
        if(getImage() != NullFC)
        {
            beginEditCP(_img);
                _img->set(Image::OSG_RGBA_PF, getImage()->getWidth(), getImage()->getHeight());
            endEditCP(_img);
            
            beginEditCP(_textureChunk, TextureChunk::ImageFieldMask);
                _textureChunk->setImage(_img);
            endEditCP(_textureChunk, TextureChunk::ImageFieldMask);
        }
    }
    
    if((whichField & ImageFieldMask) ||
       (whichField & IndexFieldMask) ||
       (whichField & ScaleFieldMask) ||
       (whichField & BiasFieldMask))
    {
        updateFresnel();
    }
    
    Inherited::changed(whichField, origin);
}

void FresnelMaterial::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump FresnelMaterial NI" << std::endl;
}

StatePtr FresnelMaterial::makeState(void)
{
    StatePtr state = State::create();
    
    Color3f v3;
    Color4f v4;
    float alpha = 1.f - getTransparency();
    
    prepareLocalChunks();
    
    beginEditCP(_materialChunk);
         v3 = getAmbient(); 
         v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);
        _materialChunk->setAmbient(v4);

         v3 = getDiffuse(); 
         v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);
        _materialChunk->setDiffuse(v4);

         v3 = getSpecular(); 
         v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);
        _materialChunk->setSpecular(v4);

        _materialChunk->setShininess(getShininess());

         v3 = getEmission(); 
         v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);
        _materialChunk->setEmission(v4);
        
        _materialChunk->setLit(getLit());
        _materialChunk->setColorMaterial(getColorMaterial());
    endEditCP  (_materialChunk);
    
    state->addChunk(_materialChunk);
    state->addChunk(_textureChunk);
    state->addChunk(_texGenChunk);

    if(isTransparent())
        state->addChunk(_blendChunk);
    
    for(MFStateChunkPtr::iterator i  = _mfChunks.begin();
                                  i != _mfChunks.end(); 
                                ++i)
    {
        state->addChunk(*i);
    }

    return state;
}

void FresnelMaterial::rebuildState(void)
{
    Color3f v3;
    Color4f v4;
    Real32  alpha = 1.f - getTransparency();

    if(_pState != NullFC)
    {
        _pState->clearChunks();
    }
    else
    {
        _pState = State::create();

        addRefCP(_pState);
    }

    prepareLocalChunks();

    beginEditCP(_materialChunk);
        v3 = getAmbient();
        v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);

        _materialChunk->setAmbient(v4);

        v3 = getDiffuse();
        v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);
        
        _materialChunk->setDiffuse(v4);
        
        v3 = getSpecular();
        v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);
        
        _materialChunk->setSpecular(v4);
        
        _materialChunk->setShininess(getShininess());
        
        v3 = getEmission();
        v4.setValuesRGBA(v3[0], v3[1], v3[2], alpha);
        
        _materialChunk->setEmission(v4);
        
        _materialChunk->setLit(getLit());
        _materialChunk->setColorMaterial(getColorMaterial());
    endEditCP  (_materialChunk);
    
    _pState->addChunk(_materialChunk);
    _pState->addChunk(_textureChunk);
    _pState->addChunk(_texGenChunk);
    
    if(isTransparent())
        _pState->addChunk(_blendChunk);
    
    for(MFStateChunkPtr::iterator i  = _mfChunks.begin();
                                  i != _mfChunks.end(); 
                                ++i)
    {
        _pState->addChunk(*i);
    }
}

bool FresnelMaterial::isTransparent(void) const
{
    return ((getTransparency() > Eps) || (Inherited::isTransparent()));
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGFresnelMaterial.cpp,v 1.5 2006/04/13 16:24:29 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGFRESNELMATERIAL_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGFRESNELMATERIAL_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGFRESNELMATERIALFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif
