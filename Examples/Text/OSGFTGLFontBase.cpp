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

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 **     Do not change this file, changes should be done in the derived      **
 **     class FTGLFont!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define OSG_COMPILEFTGLFONTINST

#include <stdlib.h>
#include <stdio.h>

#include <OpenSG/OSGConfig.h>

#include "OSGFTGLFontBase.h"
#include "OSGFTGLFont.h"


OSG_USING_NAMESPACE

const OSG::BitVector  FTGLFontBase::NameFieldMask = 
    (TypeTraits<BitVector>::One << FTGLFontBase::NameFieldId);

const OSG::BitVector  FTGLFontBase::DrawTypeFieldMask = 
    (TypeTraits<BitVector>::One << FTGLFontBase::DrawTypeFieldId);

const OSG::BitVector  FTGLFontBase::SizeFieldMask = 
    (TypeTraits<BitVector>::One << FTGLFontBase::SizeFieldId);

const OSG::BitVector  FTGLFontBase::ResFieldMask = 
    (TypeTraits<BitVector>::One << FTGLFontBase::ResFieldId);

const OSG::BitVector  FTGLFontBase::DepthFieldMask = 
    (TypeTraits<BitVector>::One << FTGLFontBase::DepthFieldId);

const OSG::BitVector  FTGLFontBase::GLIdFieldMask = 
    (TypeTraits<BitVector>::One << FTGLFontBase::GLIdFieldId);

const OSG::BitVector FTGLFontBase::MTInfluenceMask = 
    (Inherited::MTInfluenceMask) | 
    (static_cast<BitVector>(0x0) << Inherited::NextFieldId); 


// Field descriptions

/*! \var std::string     FTGLFontBase::_sfName
    The font file name.
*/
/*! \var UInt32          FTGLFontBase::_sfDrawType
    Type of Font to use for drawing, see OSGFTGLFont.h for possible types.
*/
/*! \var UInt32          FTGLFontBase::_sfSize
    Size, in points.
*/
/*! \var UInt32          FTGLFontBase::_sfRes
    Resolution of the output device.
*/
/*! \var Real32          FTGLFontBase::_sfDepth
    Extrusion depth, in points.
*/
/*! \var UInt32          FTGLFontBase::_sfGLId
    Internal ID for registration with Window, needed for updates and         validation.
*/

//! FTGLFont description

FieldDescription *FTGLFontBase::_desc[] = 
{
    new FieldDescription(SFString::getClassType(), 
                     "name", 
                     NameFieldId, NameFieldMask,
                     false,
                     (FieldAccessMethod) &FTGLFontBase::getSFName),
    new FieldDescription(SFUInt32::getClassType(), 
                     "drawType", 
                     DrawTypeFieldId, DrawTypeFieldMask,
                     false,
                     (FieldAccessMethod) &FTGLFontBase::getSFDrawType),
    new FieldDescription(SFUInt32::getClassType(), 
                     "size", 
                     SizeFieldId, SizeFieldMask,
                     false,
                     (FieldAccessMethod) &FTGLFontBase::getSFSize),
    new FieldDescription(SFUInt32::getClassType(), 
                     "res", 
                     ResFieldId, ResFieldMask,
                     false,
                     (FieldAccessMethod) &FTGLFontBase::getSFRes),
    new FieldDescription(SFReal32::getClassType(), 
                     "depth", 
                     DepthFieldId, DepthFieldMask,
                     false,
                     (FieldAccessMethod) &FTGLFontBase::getSFDepth),
    new FieldDescription(SFUInt32::getClassType(), 
                     "GLId", 
                     GLIdFieldId, GLIdFieldMask,
                     true,
                     (FieldAccessMethod) &FTGLFontBase::getSFGLId)
};


FieldContainerType FTGLFontBase::_type(
    "FTGLFont",
    "FieldContainer",
    NULL,
    (PrototypeCreateF) &FTGLFontBase::createEmpty,
    FTGLFont::initMethod,
    _desc,
    sizeof(_desc));

//OSG_FIELD_CONTAINER_DEF(FTGLFontBase, FTGLFontPtr)

/*------------------------------ get -----------------------------------*/

FieldContainerType &FTGLFontBase::getType(void) 
{
    return _type; 
} 

const FieldContainerType &FTGLFontBase::getType(void) const 
{
    return _type;
} 


FieldContainerPtr FTGLFontBase::shallowCopy(void) const 
{ 
    FTGLFontPtr returnValue; 

    newPtr(returnValue, dynamic_cast<const FTGLFont *>(this)); 

    return returnValue; 
}

UInt32 FTGLFontBase::getContainerSize(void) const 
{ 
    return sizeof(FTGLFont); 
}


void FTGLFontBase::executeSync(      FieldContainer &other,
                                    const BitVector      &whichField)
{
    this->executeSyncImpl((FTGLFontBase *) &other, whichField);
}

/*------------------------- constructors ----------------------------------*/

#ifdef OSG_WIN32_ICL
#pragma warning (disable : 383)
#endif

FTGLFontBase::FTGLFontBase(void) :
    _sfName                   (), 
    _sfDrawType               (), 
    _sfSize                   (), 
    _sfRes                    (), 
    _sfDepth                  (), 
    _sfGLId                   (), 
    Inherited() 
{
}

#ifdef OSG_WIN32_ICL
#pragma warning (default : 383)
#endif

FTGLFontBase::FTGLFontBase(const FTGLFontBase &source) :
    _sfName                   (source._sfName                   ), 
    _sfDrawType               (source._sfDrawType               ), 
    _sfSize                   (source._sfSize                   ), 
    _sfRes                    (source._sfRes                    ), 
    _sfDepth                  (source._sfDepth                  ), 
    _sfGLId                   (source._sfGLId                   ), 
    Inherited                 (source)
{
}

/*-------------------------- destructors ----------------------------------*/

FTGLFontBase::~FTGLFontBase(void)
{
}

/*------------------------------ access -----------------------------------*/

UInt32 FTGLFontBase::getBinSize(const BitVector &whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (NameFieldMask & whichField))
    {
        returnValue += _sfName.getBinSize();
    }

    if(FieldBits::NoField != (DrawTypeFieldMask & whichField))
    {
        returnValue += _sfDrawType.getBinSize();
    }

    if(FieldBits::NoField != (SizeFieldMask & whichField))
    {
        returnValue += _sfSize.getBinSize();
    }

    if(FieldBits::NoField != (ResFieldMask & whichField))
    {
        returnValue += _sfRes.getBinSize();
    }

    if(FieldBits::NoField != (DepthFieldMask & whichField))
    {
        returnValue += _sfDepth.getBinSize();
    }

    if(FieldBits::NoField != (GLIdFieldMask & whichField))
    {
        returnValue += _sfGLId.getBinSize();
    }


    return returnValue;
}

void FTGLFontBase::copyToBin(      BinaryDataHandler &pMem,
                                  const BitVector         &whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (NameFieldMask & whichField))
    {
        _sfName.copyToBin(pMem);
    }

    if(FieldBits::NoField != (DrawTypeFieldMask & whichField))
    {
        _sfDrawType.copyToBin(pMem);
    }

    if(FieldBits::NoField != (SizeFieldMask & whichField))
    {
        _sfSize.copyToBin(pMem);
    }

    if(FieldBits::NoField != (ResFieldMask & whichField))
    {
        _sfRes.copyToBin(pMem);
    }

    if(FieldBits::NoField != (DepthFieldMask & whichField))
    {
        _sfDepth.copyToBin(pMem);
    }

    if(FieldBits::NoField != (GLIdFieldMask & whichField))
    {
        _sfGLId.copyToBin(pMem);
    }


}

void FTGLFontBase::copyFromBin(      BinaryDataHandler &pMem,
                                    const BitVector    &whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (NameFieldMask & whichField))
    {
        _sfName.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (DrawTypeFieldMask & whichField))
    {
        _sfDrawType.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (SizeFieldMask & whichField))
    {
        _sfSize.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (ResFieldMask & whichField))
    {
        _sfRes.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (DepthFieldMask & whichField))
    {
        _sfDepth.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (GLIdFieldMask & whichField))
    {
        _sfGLId.copyFromBin(pMem);
    }


}

void FTGLFontBase::executeSyncImpl(      FTGLFontBase *pOther,
                                        const BitVector         &whichField)
{

    Inherited::executeSyncImpl(pOther, whichField);

    if(FieldBits::NoField != (NameFieldMask & whichField))
        _sfName.syncWith(pOther->_sfName);

    if(FieldBits::NoField != (DrawTypeFieldMask & whichField))
        _sfDrawType.syncWith(pOther->_sfDrawType);

    if(FieldBits::NoField != (SizeFieldMask & whichField))
        _sfSize.syncWith(pOther->_sfSize);

    if(FieldBits::NoField != (ResFieldMask & whichField))
        _sfRes.syncWith(pOther->_sfRes);

    if(FieldBits::NoField != (DepthFieldMask & whichField))
        _sfDepth.syncWith(pOther->_sfDepth);

    if(FieldBits::NoField != (GLIdFieldMask & whichField))
        _sfGLId.syncWith(pOther->_sfGLId);


}



#include <OpenSG/OSGSFieldTypeDef.inl>
#include <OpenSG/OSGMFieldTypeDef.inl>

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldDataTraits<FTGLFontPtr>::_type("FTGLFontPtr", "FieldContainerPtr");
#endif

OSG_DLLEXPORT_SFIELD_DEF1(FTGLFontPtr, OSG_LIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(FTGLFontPtr, OSG_LIB_DLLTMPLMAPPING);

OSG_END_NAMESPACE


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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGFTGLFontBase.cpp,v 1.1 2004/08/24 23:05:51 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGFTGLFONTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGFTGLFONTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGFTGLFONTFIELDS_HEADER_CVSID;
}
