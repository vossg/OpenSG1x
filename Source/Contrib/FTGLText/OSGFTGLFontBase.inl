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
 **     class FTGLFont!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <OSGConfig.h>

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &FTGLFontBase::getClassType(void)
{
    return _type; 
} 

//! access the numerical type of the class
inline
OSG::UInt32 FTGLFontBase::getClassTypeId(void) 
{
    return _type.getId(); 
} 

//! create a new instance of the class
inline
FTGLFontPtr FTGLFontBase::create(void) 
{
    FTGLFontPtr fc; 

    if(getClassType().getPrototype() != OSG::NullFC) 
    {
        fc = FTGLFontPtr::dcast(
            getClassType().getPrototype()-> shallowCopy()); 
    }
    
    return fc; 
}

//! create an empty new instance of the class, do not copy the prototype
inline
FTGLFontPtr FTGLFontBase::createEmpty(void) 
{ 
    FTGLFontPtr returnValue; 
    
    newPtr(returnValue); 

    return returnValue; 
}


/*------------------------------ get -----------------------------------*/

//! Get the FTGLFont::_sfName field.
inline
SFString *FTGLFontBase::getSFName(void)
{
    return &_sfName;
}

//! Get the FTGLFont::_sfDrawType field.
inline
SFUInt32 *FTGLFontBase::getSFDrawType(void)
{
    return &_sfDrawType;
}

//! Get the FTGLFont::_sfSize field.
inline
SFUInt32 *FTGLFontBase::getSFSize(void)
{
    return &_sfSize;
}

//! Get the FTGLFont::_sfRes field.
inline
SFUInt32 *FTGLFontBase::getSFRes(void)
{
    return &_sfRes;
}

//! Get the FTGLFont::_sfDepth field.
inline
SFReal32 *FTGLFontBase::getSFDepth(void)
{
    return &_sfDepth;
}

//! Get the FTGLFont::_sfGLId field.
inline
SFUInt32 *FTGLFontBase::getSFGLId(void)
{
    return &_sfGLId;
}


//! Get the value of the FTGLFont::_sfName field.
inline
std::string &FTGLFontBase::getName(void)
{
    return _sfName.getValue();
}

//! Get the value of the FTGLFont::_sfName field.
inline
const std::string &FTGLFontBase::getName(void) const
{
    return _sfName.getValue();
}

//! Set the value of the FTGLFont::_sfName field.
inline
void FTGLFontBase::setName(const std::string &value)
{
    _sfName.setValue(value);
}

//! Get the value of the FTGLFont::_sfDrawType field.
inline
UInt32 &FTGLFontBase::getDrawType(void)
{
    return _sfDrawType.getValue();
}

//! Get the value of the FTGLFont::_sfDrawType field.
inline
const UInt32 &FTGLFontBase::getDrawType(void) const
{
    return _sfDrawType.getValue();
}

//! Set the value of the FTGLFont::_sfDrawType field.
inline
void FTGLFontBase::setDrawType(const UInt32 &value)
{
    _sfDrawType.setValue(value);
}

//! Get the value of the FTGLFont::_sfSize field.
inline
UInt32 &FTGLFontBase::getSize(void)
{
    return _sfSize.getValue();
}

//! Get the value of the FTGLFont::_sfSize field.
inline
const UInt32 &FTGLFontBase::getSize(void) const
{
    return _sfSize.getValue();
}

//! Set the value of the FTGLFont::_sfSize field.
inline
void FTGLFontBase::setSize(const UInt32 &value)
{
    _sfSize.setValue(value);
}

//! Get the value of the FTGLFont::_sfRes field.
inline
UInt32 &FTGLFontBase::getRes(void)
{
    return _sfRes.getValue();
}

//! Get the value of the FTGLFont::_sfRes field.
inline
const UInt32 &FTGLFontBase::getRes(void) const
{
    return _sfRes.getValue();
}

//! Set the value of the FTGLFont::_sfRes field.
inline
void FTGLFontBase::setRes(const UInt32 &value)
{
    _sfRes.setValue(value);
}

//! Get the value of the FTGLFont::_sfDepth field.
inline
Real32 &FTGLFontBase::getDepth(void)
{
    return _sfDepth.getValue();
}

//! Get the value of the FTGLFont::_sfDepth field.
inline
const Real32 &FTGLFontBase::getDepth(void) const
{
    return _sfDepth.getValue();
}

//! Set the value of the FTGLFont::_sfDepth field.
inline
void FTGLFontBase::setDepth(const Real32 &value)
{
    _sfDepth.setValue(value);
}

//! Get the value of the FTGLFont::_sfGLId field.
inline
UInt32 &FTGLFontBase::getGLId(void)
{
    return _sfGLId.getValue();
}

//! Get the value of the FTGLFont::_sfGLId field.
inline
const UInt32 &FTGLFontBase::getGLId(void) const
{
    return _sfGLId.getValue();
}

//! Set the value of the FTGLFont::_sfGLId field.
inline
void FTGLFontBase::setGLId(const UInt32 &value)
{
    _sfGLId.setValue(value);
}


OSG_END_NAMESPACE

#define OSGFTGLFONTBASE_INLINE_CVSID "@(#)$Id: OSGFTGLFontBase.inl,v 1.1 2004/08/05 05:22:50 dirk Exp $"
