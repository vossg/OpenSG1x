/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 **     Do not change this file, changes should be done in the derived      **
 **     class FBOViewport!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <OSGConfig.h>

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &FBOViewportBase::getClassType(void)
{
    return _type; 
} 

//! access the numerical type of the class
inline
OSG::UInt32 FBOViewportBase::getClassTypeId(void) 
{
    return _type.getId(); 
} 

//! create a new instance of the class
inline
FBOViewportPtr FBOViewportBase::create(void) 
{
    FBOViewportPtr fc; 

    if(getClassType().getPrototype() != OSG::NullFC) 
    {
        fc = FBOViewportPtr::dcast(
            getClassType().getPrototype()-> shallowCopy()); 
    }
    
    return fc; 
}

//! create an empty new instance of the class, do not copy the prototype
inline
FBOViewportPtr FBOViewportBase::createEmpty(void) 
{ 
    FBOViewportPtr returnValue; 
    
    newPtr(returnValue); 

    return returnValue; 
}


/*------------------------------ get -----------------------------------*/

//! Get the FBOViewport::_sfEnabled field.
inline
SFBool *FBOViewportBase::getSFEnabled(void)
{
    return &_sfEnabled;
}

//! Get the FBOViewport::_mfExcludeNodes field.
inline
MFNodePtr *FBOViewportBase::getMFExcludeNodes(void)
{
    return &_mfExcludeNodes;
}

//! Get the FBOViewport::_mfRenderNodes field.
inline
MFNodePtr *FBOViewportBase::getMFRenderNodes(void)
{
    return &_mfRenderNodes;
}

//! Get the FBOViewport::_mfTextures field.
inline
MFTextureChunkPtr *FBOViewportBase::getMFTextures(void)
{
    return &_mfTextures;
}

//! Get the FBOViewport::_sfFboOn field.
inline
SFBool *FBOViewportBase::getSFFboOn(void)
{
    return &_sfFboOn;
}

//! Get the FBOViewport::_sfStorageWidth field.
inline
SFInt32 *FBOViewportBase::getSFStorageWidth(void)
{
    return &_sfStorageWidth;
}

//! Get the FBOViewport::_sfStorageHeight field.
inline
SFInt32 *FBOViewportBase::getSFStorageHeight(void)
{
    return &_sfStorageHeight;
}

//! Get the FBOViewport::_sfGenCubemaps field.
inline
SFBool *FBOViewportBase::getSFGenCubemaps(void)
{
    return &_sfGenCubemaps;
}

//! Get the FBOViewport::_sfGenDepthmaps field.
inline
SFBool *FBOViewportBase::getSFGenDepthmaps(void)
{
    return &_sfGenDepthmaps;
}

//! Get the FBOViewport::_sfFrameBufferIndex field.
inline
SFUInt32 *FBOViewportBase::getSFFrameBufferIndex(void)
{
    return &_sfFrameBufferIndex;
}

//! Get the FBOViewport::_sfDepthBufferIndex field.
inline
SFUInt32 *FBOViewportBase::getSFDepthBufferIndex(void)
{
    return &_sfDepthBufferIndex;
}

//! Get the FBOViewport::_sfStencilBufferIndex field.
inline
SFUInt32 *FBOViewportBase::getSFStencilBufferIndex(void)
{
    return &_sfStencilBufferIndex;
}

//! Get the FBOViewport::_sfDirty field.
inline
SFBool *FBOViewportBase::getSFDirty(void)
{
    return &_sfDirty;
}

//! Get the FBOViewport::_sfReadBuffer field.
inline
SFBool *FBOViewportBase::getSFReadBuffer(void)
{
    return &_sfReadBuffer;
}


//! Get the value of the FBOViewport::_sfEnabled field.
inline
bool &FBOViewportBase::getEnabled(void)
{
    return _sfEnabled.getValue();
}

//! Get the value of the FBOViewport::_sfEnabled field.
inline
const bool &FBOViewportBase::getEnabled(void) const
{
    return _sfEnabled.getValue();
}

//! Set the value of the FBOViewport::_sfEnabled field.
inline
void FBOViewportBase::setEnabled(const bool &value)
{
    _sfEnabled.setValue(value);
}

//! Get the value of the FBOViewport::_sfFboOn field.
inline
bool &FBOViewportBase::getFboOn(void)
{
    return _sfFboOn.getValue();
}

//! Get the value of the FBOViewport::_sfFboOn field.
inline
const bool &FBOViewportBase::getFboOn(void) const
{
    return _sfFboOn.getValue();
}

//! Set the value of the FBOViewport::_sfFboOn field.
inline
void FBOViewportBase::setFboOn(const bool &value)
{
    _sfFboOn.setValue(value);
}

//! Get the value of the FBOViewport::_sfStorageWidth field.
inline
Int32 &FBOViewportBase::getStorageWidth(void)
{
    return _sfStorageWidth.getValue();
}

//! Get the value of the FBOViewport::_sfStorageWidth field.
inline
const Int32 &FBOViewportBase::getStorageWidth(void) const
{
    return _sfStorageWidth.getValue();
}

//! Set the value of the FBOViewport::_sfStorageWidth field.
inline
void FBOViewportBase::setStorageWidth(const Int32 &value)
{
    _sfStorageWidth.setValue(value);
}

//! Get the value of the FBOViewport::_sfStorageHeight field.
inline
Int32 &FBOViewportBase::getStorageHeight(void)
{
    return _sfStorageHeight.getValue();
}

//! Get the value of the FBOViewport::_sfStorageHeight field.
inline
const Int32 &FBOViewportBase::getStorageHeight(void) const
{
    return _sfStorageHeight.getValue();
}

//! Set the value of the FBOViewport::_sfStorageHeight field.
inline
void FBOViewportBase::setStorageHeight(const Int32 &value)
{
    _sfStorageHeight.setValue(value);
}

//! Get the value of the FBOViewport::_sfGenCubemaps field.
inline
bool &FBOViewportBase::getGenCubemaps(void)
{
    return _sfGenCubemaps.getValue();
}

//! Get the value of the FBOViewport::_sfGenCubemaps field.
inline
const bool &FBOViewportBase::getGenCubemaps(void) const
{
    return _sfGenCubemaps.getValue();
}

//! Set the value of the FBOViewport::_sfGenCubemaps field.
inline
void FBOViewportBase::setGenCubemaps(const bool &value)
{
    _sfGenCubemaps.setValue(value);
}

//! Get the value of the FBOViewport::_sfGenDepthmaps field.
inline
bool &FBOViewportBase::getGenDepthmaps(void)
{
    return _sfGenDepthmaps.getValue();
}

//! Get the value of the FBOViewport::_sfGenDepthmaps field.
inline
const bool &FBOViewportBase::getGenDepthmaps(void) const
{
    return _sfGenDepthmaps.getValue();
}

//! Set the value of the FBOViewport::_sfGenDepthmaps field.
inline
void FBOViewportBase::setGenDepthmaps(const bool &value)
{
    _sfGenDepthmaps.setValue(value);
}

//! Get the value of the FBOViewport::_sfFrameBufferIndex field.
inline
UInt32 &FBOViewportBase::getFrameBufferIndex(void)
{
    return _sfFrameBufferIndex.getValue();
}

//! Get the value of the FBOViewport::_sfFrameBufferIndex field.
inline
const UInt32 &FBOViewportBase::getFrameBufferIndex(void) const
{
    return _sfFrameBufferIndex.getValue();
}

//! Set the value of the FBOViewport::_sfFrameBufferIndex field.
inline
void FBOViewportBase::setFrameBufferIndex(const UInt32 &value)
{
    _sfFrameBufferIndex.setValue(value);
}

//! Get the value of the FBOViewport::_sfDepthBufferIndex field.
inline
UInt32 &FBOViewportBase::getDepthBufferIndex(void)
{
    return _sfDepthBufferIndex.getValue();
}

//! Get the value of the FBOViewport::_sfDepthBufferIndex field.
inline
const UInt32 &FBOViewportBase::getDepthBufferIndex(void) const
{
    return _sfDepthBufferIndex.getValue();
}

//! Set the value of the FBOViewport::_sfDepthBufferIndex field.
inline
void FBOViewportBase::setDepthBufferIndex(const UInt32 &value)
{
    _sfDepthBufferIndex.setValue(value);
}

//! Get the value of the FBOViewport::_sfStencilBufferIndex field.
inline
UInt32 &FBOViewportBase::getStencilBufferIndex(void)
{
    return _sfStencilBufferIndex.getValue();
}

//! Get the value of the FBOViewport::_sfStencilBufferIndex field.
inline
const UInt32 &FBOViewportBase::getStencilBufferIndex(void) const
{
    return _sfStencilBufferIndex.getValue();
}

//! Set the value of the FBOViewport::_sfStencilBufferIndex field.
inline
void FBOViewportBase::setStencilBufferIndex(const UInt32 &value)
{
    _sfStencilBufferIndex.setValue(value);
}

//! Get the value of the FBOViewport::_sfDirty field.
inline
bool &FBOViewportBase::getDirty(void)
{
    return _sfDirty.getValue();
}

//! Get the value of the FBOViewport::_sfDirty field.
inline
const bool &FBOViewportBase::getDirty(void) const
{
    return _sfDirty.getValue();
}

//! Set the value of the FBOViewport::_sfDirty field.
inline
void FBOViewportBase::setDirty(const bool &value)
{
    _sfDirty.setValue(value);
}

//! Get the value of the FBOViewport::_sfReadBuffer field.
inline
bool &FBOViewportBase::getReadBuffer(void)
{
    return _sfReadBuffer.getValue();
}

//! Get the value of the FBOViewport::_sfReadBuffer field.
inline
const bool &FBOViewportBase::getReadBuffer(void) const
{
    return _sfReadBuffer.getValue();
}

//! Set the value of the FBOViewport::_sfReadBuffer field.
inline
void FBOViewportBase::setReadBuffer(const bool &value)
{
    _sfReadBuffer.setValue(value);
}


//! Get the value of the \a index element the FBOViewport::_mfExcludeNodes field.
inline
NodePtr &FBOViewportBase::getExcludeNodes(const UInt32 index)
{
    return _mfExcludeNodes[index];
}

//! Get the FBOViewport::_mfExcludeNodes field.
inline
MFNodePtr &FBOViewportBase::getExcludeNodes(void)
{
    return _mfExcludeNodes;
}

//! Get the FBOViewport::_mfExcludeNodes field.
inline
const MFNodePtr &FBOViewportBase::getExcludeNodes(void) const
{
    return _mfExcludeNodes;
}

//! Get the value of the \a index element the FBOViewport::_mfRenderNodes field.
inline
NodePtr &FBOViewportBase::getRenderNodes(const UInt32 index)
{
    return _mfRenderNodes[index];
}

//! Get the FBOViewport::_mfRenderNodes field.
inline
MFNodePtr &FBOViewportBase::getRenderNodes(void)
{
    return _mfRenderNodes;
}

//! Get the FBOViewport::_mfRenderNodes field.
inline
const MFNodePtr &FBOViewportBase::getRenderNodes(void) const
{
    return _mfRenderNodes;
}

//! Get the value of the \a index element the FBOViewport::_mfTextures field.
inline
TextureChunkPtr &FBOViewportBase::getTextures(const UInt32 index)
{
    return _mfTextures[index];
}

//! Get the FBOViewport::_mfTextures field.
inline
MFTextureChunkPtr &FBOViewportBase::getTextures(void)
{
    return _mfTextures;
}

//! Get the FBOViewport::_mfTextures field.
inline
const MFTextureChunkPtr &FBOViewportBase::getTextures(void) const
{
    return _mfTextures;
}

OSG_END_NAMESPACE

#define OSGFBOVIEWPORTBASE_INLINE_CVSID "@(#)$Id: OSGFBOViewportBase.inl,v 1.1 2007/03/12 15:03:02 a-m-z Exp $"
