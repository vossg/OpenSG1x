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
 **     class DVRVolume!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <OSGConfig.h>

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &DVRVolumeBase::getClassType(void)
{
    return _type; 
} 

//! access the numerical type of the class
inline
OSG::UInt32 DVRVolumeBase::getClassTypeId(void) 
{
    return _type.getId(); 
} 

//! create a new instance of the class
inline
DVRVolumePtr DVRVolumeBase::create(void) 
{
    DVRVolumePtr fc; 

    if(getClassType().getPrototype() != OSG::NullFC) 
    {
        fc = DVRVolumePtr::dcast(
            getClassType().getPrototype()-> shallowCopy()); 
    }
    
    return fc; 
}

//! create an empty new instance of the class, do not copy the prototype
inline
DVRVolumePtr DVRVolumeBase::createEmpty(void) 
{ 
    DVRVolumePtr returnValue; 
    
    newPtr(returnValue); 

    return returnValue; 
}


/*------------------------------ get -----------------------------------*/

//! Get the DVRVolume::_sfAppearance field.
inline
SFDVRAppearancePtr *DVRVolumeBase::getSFAppearance(void)
{
    return &_sfAppearance;
}

//! Get the DVRVolume::_sfGeometry field.
inline
SFDVRGeometryPtr *DVRVolumeBase::getSFGeometry(void)
{
    return &_sfGeometry;
}

//! Get the DVRVolume::_sfShader field.
inline
SFDVRShaderPtr *DVRVolumeBase::getSFShader(void)
{
    return &_sfShader;
}

//! Get the DVRVolume::_sfFileName field.
inline
SFString *DVRVolumeBase::getSFFileName(void)
{
    return &_sfFileName;
}

//! Get the DVRVolume::_sfSampling field.
inline
SFReal32 *DVRVolumeBase::getSFSampling(void)
{
    return &_sfSampling;
}

//! Get the DVRVolume::_sfSamplingInteractive field.
inline
SFReal32 *DVRVolumeBase::getSFSamplingInteractive(void)
{
    return &_sfSamplingInteractive;
}

//! Get the DVRVolume::_sfBaseAlpha field.
inline
SFReal32 *DVRVolumeBase::getSFBaseAlpha(void)
{
    return &_sfBaseAlpha;
}

//! Get the DVRVolume::_sfDoTextures field.
inline
SFBool *DVRVolumeBase::getSFDoTextures(void)
{
    return &_sfDoTextures;
}

//! Get the DVRVolume::_sfBrickOverlap field.
inline
SFUInt32 *DVRVolumeBase::getSFBrickOverlap(void)
{
    return &_sfBrickOverlap;
}

//! Get the DVRVolume::_sfTextures2D field.
inline
SFQBit *DVRVolumeBase::getSFTextures2D(void)
{
    return &_sfTextures2D;
}

//! Get the DVRVolume::_sfRenderMaterial field.
inline
SFMaterialPtr *DVRVolumeBase::getSFRenderMaterial(void)
{
    return &_sfRenderMaterial;
}

//! Get the DVRVolume::_sfBrickingMode field.
inline
SFUInt16 *DVRVolumeBase::getSFBrickingMode(void)
{
    return &_sfBrickingMode;
}

//! Get the DVRVolume::_sfBrickStaticMemoryMB field.
inline
SFUInt16 *DVRVolumeBase::getSFBrickStaticMemoryMB(void)
{
    return &_sfBrickStaticMemoryMB;
}

//! Get the DVRVolume::_sfBrickStaticSubdivision field.
inline
SFVec3f *DVRVolumeBase::getSFBrickStaticSubdivision(void)
{
    return &_sfBrickStaticSubdivision;
}

//! Get the DVRVolume::_sfBrickMaxSize field.
inline
SFVec3f *DVRVolumeBase::getSFBrickMaxSize(void)
{
    return &_sfBrickMaxSize;
}

//! Get the DVRVolume::_sfShowBricks field.
inline
SFBool *DVRVolumeBase::getSFShowBricks(void)
{
    return &_sfShowBricks;
}

//! Get the DVRVolume::_sfDrawStyle field.
inline
SFUInt32 *DVRVolumeBase::getSFDrawStyle(void)
{
    return &_sfDrawStyle;
}

//! Get the DVRVolume::_mfDrawStyleNames field.
inline
MFString *DVRVolumeBase::getMFDrawStyleNames(void)
{
    return &_mfDrawStyleNames;
}

//! Get the DVRVolume::_sfTextureStorage field.
inline
SFChunkMaterialPtr *DVRVolumeBase::getSFTextureStorage(void)
{
    return &_sfTextureStorage;
}


//! Get the value of the DVRVolume::_sfAppearance field.
inline
DVRAppearancePtr &DVRVolumeBase::getAppearance(void)
{
    return _sfAppearance.getValue();
}

//! Get the value of the DVRVolume::_sfAppearance field.
inline
const DVRAppearancePtr &DVRVolumeBase::getAppearance(void) const
{
    return _sfAppearance.getValue();
}

//! Set the value of the DVRVolume::_sfAppearance field.
inline
void DVRVolumeBase::setAppearance(const DVRAppearancePtr &value)
{
    _sfAppearance.setValue(value);
}

//! Get the value of the DVRVolume::_sfGeometry field.
inline
DVRGeometryPtr &DVRVolumeBase::getGeometry(void)
{
    return _sfGeometry.getValue();
}

//! Get the value of the DVRVolume::_sfGeometry field.
inline
const DVRGeometryPtr &DVRVolumeBase::getGeometry(void) const
{
    return _sfGeometry.getValue();
}

//! Set the value of the DVRVolume::_sfGeometry field.
inline
void DVRVolumeBase::setGeometry(const DVRGeometryPtr &value)
{
    _sfGeometry.setValue(value);
}

//! Get the value of the DVRVolume::_sfShader field.
inline
DVRShaderPtr &DVRVolumeBase::getShader(void)
{
    return _sfShader.getValue();
}

//! Get the value of the DVRVolume::_sfShader field.
inline
const DVRShaderPtr &DVRVolumeBase::getShader(void) const
{
    return _sfShader.getValue();
}

//! Set the value of the DVRVolume::_sfShader field.
inline
void DVRVolumeBase::setShader(const DVRShaderPtr &value)
{
    _sfShader.setValue(value);
}

//! Get the value of the DVRVolume::_sfFileName field.
inline
std::string &DVRVolumeBase::getFileName(void)
{
    return _sfFileName.getValue();
}

//! Get the value of the DVRVolume::_sfFileName field.
inline
const std::string &DVRVolumeBase::getFileName(void) const
{
    return _sfFileName.getValue();
}

//! Set the value of the DVRVolume::_sfFileName field.
inline
void DVRVolumeBase::setFileName(const std::string &value)
{
    _sfFileName.setValue(value);
}

//! Get the value of the DVRVolume::_sfSampling field.
inline
Real32 &DVRVolumeBase::getSampling(void)
{
    return _sfSampling.getValue();
}

//! Get the value of the DVRVolume::_sfSampling field.
inline
const Real32 &DVRVolumeBase::getSampling(void) const
{
    return _sfSampling.getValue();
}

//! Set the value of the DVRVolume::_sfSampling field.
inline
void DVRVolumeBase::setSampling(const Real32 &value)
{
    _sfSampling.setValue(value);
}

//! Get the value of the DVRVolume::_sfSamplingInteractive field.
inline
Real32 &DVRVolumeBase::getSamplingInteractive(void)
{
    return _sfSamplingInteractive.getValue();
}

//! Get the value of the DVRVolume::_sfSamplingInteractive field.
inline
const Real32 &DVRVolumeBase::getSamplingInteractive(void) const
{
    return _sfSamplingInteractive.getValue();
}

//! Set the value of the DVRVolume::_sfSamplingInteractive field.
inline
void DVRVolumeBase::setSamplingInteractive(const Real32 &value)
{
    _sfSamplingInteractive.setValue(value);
}

//! Get the value of the DVRVolume::_sfBaseAlpha field.
inline
Real32 &DVRVolumeBase::getBaseAlpha(void)
{
    return _sfBaseAlpha.getValue();
}

//! Get the value of the DVRVolume::_sfBaseAlpha field.
inline
const Real32 &DVRVolumeBase::getBaseAlpha(void) const
{
    return _sfBaseAlpha.getValue();
}

//! Set the value of the DVRVolume::_sfBaseAlpha field.
inline
void DVRVolumeBase::setBaseAlpha(const Real32 &value)
{
    _sfBaseAlpha.setValue(value);
}

//! Get the value of the DVRVolume::_sfDoTextures field.
inline
bool &DVRVolumeBase::getDoTextures(void)
{
    return _sfDoTextures.getValue();
}

//! Get the value of the DVRVolume::_sfDoTextures field.
inline
const bool &DVRVolumeBase::getDoTextures(void) const
{
    return _sfDoTextures.getValue();
}

//! Set the value of the DVRVolume::_sfDoTextures field.
inline
void DVRVolumeBase::setDoTextures(const bool &value)
{
    _sfDoTextures.setValue(value);
}

//! Get the value of the DVRVolume::_sfBrickOverlap field.
inline
UInt32 &DVRVolumeBase::getBrickOverlap(void)
{
    return _sfBrickOverlap.getValue();
}

//! Get the value of the DVRVolume::_sfBrickOverlap field.
inline
const UInt32 &DVRVolumeBase::getBrickOverlap(void) const
{
    return _sfBrickOverlap.getValue();
}

//! Set the value of the DVRVolume::_sfBrickOverlap field.
inline
void DVRVolumeBase::setBrickOverlap(const UInt32 &value)
{
    _sfBrickOverlap.setValue(value);
}

//! Get the value of the DVRVolume::_sfTextures2D field.
inline
QBit &DVRVolumeBase::getTextures2D(void)
{
    return _sfTextures2D.getValue();
}

//! Get the value of the DVRVolume::_sfTextures2D field.
inline
const QBit &DVRVolumeBase::getTextures2D(void) const
{
    return _sfTextures2D.getValue();
}

//! Set the value of the DVRVolume::_sfTextures2D field.
inline
void DVRVolumeBase::setTextures2D(const QBit &value)
{
    _sfTextures2D.setValue(value);
}

//! Get the value of the DVRVolume::_sfRenderMaterial field.
inline
MaterialPtr &DVRVolumeBase::getRenderMaterial(void)
{
    return _sfRenderMaterial.getValue();
}

//! Get the value of the DVRVolume::_sfRenderMaterial field.
inline
const MaterialPtr &DVRVolumeBase::getRenderMaterial(void) const
{
    return _sfRenderMaterial.getValue();
}

//! Set the value of the DVRVolume::_sfRenderMaterial field.
inline
void DVRVolumeBase::setRenderMaterial(const MaterialPtr &value)
{
    _sfRenderMaterial.setValue(value);
}

//! Get the value of the DVRVolume::_sfBrickingMode field.
inline
UInt16 &DVRVolumeBase::getBrickingMode(void)
{
    return _sfBrickingMode.getValue();
}

//! Get the value of the DVRVolume::_sfBrickingMode field.
inline
const UInt16 &DVRVolumeBase::getBrickingMode(void) const
{
    return _sfBrickingMode.getValue();
}

//! Set the value of the DVRVolume::_sfBrickingMode field.
inline
void DVRVolumeBase::setBrickingMode(const UInt16 &value)
{
    _sfBrickingMode.setValue(value);
}

//! Get the value of the DVRVolume::_sfBrickStaticMemoryMB field.
inline
UInt16 &DVRVolumeBase::getBrickStaticMemoryMB(void)
{
    return _sfBrickStaticMemoryMB.getValue();
}

//! Get the value of the DVRVolume::_sfBrickStaticMemoryMB field.
inline
const UInt16 &DVRVolumeBase::getBrickStaticMemoryMB(void) const
{
    return _sfBrickStaticMemoryMB.getValue();
}

//! Set the value of the DVRVolume::_sfBrickStaticMemoryMB field.
inline
void DVRVolumeBase::setBrickStaticMemoryMB(const UInt16 &value)
{
    _sfBrickStaticMemoryMB.setValue(value);
}

//! Get the value of the DVRVolume::_sfBrickStaticSubdivision field.
inline
Vec3f &DVRVolumeBase::getBrickStaticSubdivision(void)
{
    return _sfBrickStaticSubdivision.getValue();
}

//! Get the value of the DVRVolume::_sfBrickStaticSubdivision field.
inline
const Vec3f &DVRVolumeBase::getBrickStaticSubdivision(void) const
{
    return _sfBrickStaticSubdivision.getValue();
}

//! Set the value of the DVRVolume::_sfBrickStaticSubdivision field.
inline
void DVRVolumeBase::setBrickStaticSubdivision(const Vec3f &value)
{
    _sfBrickStaticSubdivision.setValue(value);
}

//! Get the value of the DVRVolume::_sfBrickMaxSize field.
inline
Vec3f &DVRVolumeBase::getBrickMaxSize(void)
{
    return _sfBrickMaxSize.getValue();
}

//! Get the value of the DVRVolume::_sfBrickMaxSize field.
inline
const Vec3f &DVRVolumeBase::getBrickMaxSize(void) const
{
    return _sfBrickMaxSize.getValue();
}

//! Set the value of the DVRVolume::_sfBrickMaxSize field.
inline
void DVRVolumeBase::setBrickMaxSize(const Vec3f &value)
{
    _sfBrickMaxSize.setValue(value);
}

//! Get the value of the DVRVolume::_sfShowBricks field.
inline
bool &DVRVolumeBase::getShowBricks(void)
{
    return _sfShowBricks.getValue();
}

//! Get the value of the DVRVolume::_sfShowBricks field.
inline
const bool &DVRVolumeBase::getShowBricks(void) const
{
    return _sfShowBricks.getValue();
}

//! Set the value of the DVRVolume::_sfShowBricks field.
inline
void DVRVolumeBase::setShowBricks(const bool &value)
{
    _sfShowBricks.setValue(value);
}

//! Get the value of the DVRVolume::_sfDrawStyle field.
inline
UInt32 &DVRVolumeBase::getDrawStyle(void)
{
    return _sfDrawStyle.getValue();
}

//! Get the value of the DVRVolume::_sfDrawStyle field.
inline
const UInt32 &DVRVolumeBase::getDrawStyle(void) const
{
    return _sfDrawStyle.getValue();
}

//! Set the value of the DVRVolume::_sfDrawStyle field.
inline
void DVRVolumeBase::setDrawStyle(const UInt32 &value)
{
    _sfDrawStyle.setValue(value);
}

//! Get the value of the DVRVolume::_sfTextureStorage field.
inline
ChunkMaterialPtr &DVRVolumeBase::getTextureStorage(void)
{
    return _sfTextureStorage.getValue();
}

//! Get the value of the DVRVolume::_sfTextureStorage field.
inline
const ChunkMaterialPtr &DVRVolumeBase::getTextureStorage(void) const
{
    return _sfTextureStorage.getValue();
}

//! Set the value of the DVRVolume::_sfTextureStorage field.
inline
void DVRVolumeBase::setTextureStorage(const ChunkMaterialPtr &value)
{
    _sfTextureStorage.setValue(value);
}


//! Get the value of the \a index element the DVRVolume::_mfDrawStyleNames field.
inline
std::string &DVRVolumeBase::getDrawStyleNames(const UInt32 index)
{
    return _mfDrawStyleNames[index];
}

//! Get the DVRVolume::_mfDrawStyleNames field.
inline
MFString &DVRVolumeBase::getDrawStyleNames(void)
{
    return _mfDrawStyleNames;
}

//! Get the DVRVolume::_mfDrawStyleNames field.
inline
const MFString &DVRVolumeBase::getDrawStyleNames(void) const
{
    return _mfDrawStyleNames;
}

OSG_END_NAMESPACE

#define OSGDVRVOLUMEBASE_INLINE_CVSID "@(#)$Id: $"
