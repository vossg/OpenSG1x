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
 **     class SHLChunk!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <OSGConfig.h>

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &SHLChunkBase::getClassType(void)
{
    return _type; 
} 

//! access the numerical type of the class
inline
OSG::UInt32 SHLChunkBase::getClassTypeId(void) 
{
    return _type.getId(); 
} 

//! create a new instance of the class
inline
SHLChunkPtr SHLChunkBase::create(void) 
{
    SHLChunkPtr fc; 

    if(getClassType().getPrototype() != OSG::NullFC) 
    {
        fc = SHLChunkPtr::dcast(
            getClassType().getPrototype()-> shallowCopy()); 
    }
    
    return fc; 
}

//! create an empty new instance of the class, do not copy the prototype
inline
SHLChunkPtr SHLChunkBase::createEmpty(void) 
{ 
    SHLChunkPtr returnValue; 
    
    newPtr(returnValue); 

    return returnValue; 
}


/*------------------------------ get -----------------------------------*/

//! Get the SHLChunk::_sfVertexProgram field.
inline
SFString *SHLChunkBase::getSFVertexProgram(void)
{
    return &_sfVertexProgram;
}

//! Get the SHLChunk::_sfFragmentProgram field.
inline
SFString *SHLChunkBase::getSFFragmentProgram(void)
{
    return &_sfFragmentProgram;
}

//! Get the SHLChunk::_mfParamNames field.
inline
MFString *SHLChunkBase::getMFParamNames(void)
{
    return &_mfParamNames;
}

//! Get the SHLChunk::_mfParamValues field.
inline
MFVec4f *SHLChunkBase::getMFParamValues(void)
{
    return &_mfParamValues;
}

//! Get the SHLChunk::_sfGLId field.
inline
SFUInt32 *SHLChunkBase::getSFGLId(void)
{
    return &_sfGLId;
}


//! Get the value of the SHLChunk::_sfVertexProgram field.
inline
std::string &SHLChunkBase::getVertexProgram(void)
{
    return _sfVertexProgram.getValue();
}

//! Get the value of the SHLChunk::_sfVertexProgram field.
inline
const std::string &SHLChunkBase::getVertexProgram(void) const
{
    return _sfVertexProgram.getValue();
}

//! Set the value of the SHLChunk::_sfVertexProgram field.
inline
void SHLChunkBase::setVertexProgram(const std::string &value)
{
    _sfVertexProgram.setValue(value);
}

//! Get the value of the SHLChunk::_sfFragmentProgram field.
inline
std::string &SHLChunkBase::getFragmentProgram(void)
{
    return _sfFragmentProgram.getValue();
}

//! Get the value of the SHLChunk::_sfFragmentProgram field.
inline
const std::string &SHLChunkBase::getFragmentProgram(void) const
{
    return _sfFragmentProgram.getValue();
}

//! Set the value of the SHLChunk::_sfFragmentProgram field.
inline
void SHLChunkBase::setFragmentProgram(const std::string &value)
{
    _sfFragmentProgram.setValue(value);
}

//! Get the value of the SHLChunk::_sfGLId field.
inline
UInt32 &SHLChunkBase::getGLId(void)
{
    return _sfGLId.getValue();
}

//! Get the value of the SHLChunk::_sfGLId field.
inline
const UInt32 &SHLChunkBase::getGLId(void) const
{
    return _sfGLId.getValue();
}

//! Set the value of the SHLChunk::_sfGLId field.
inline
void SHLChunkBase::setGLId(const UInt32 &value)
{
    _sfGLId.setValue(value);
}


//! Get the value of the \a index element the SHLChunk::_mfParamNames field.
inline
std::string &SHLChunkBase::getParamNames(const UInt32 index)
{
    return _mfParamNames[index];
}

//! Get the SHLChunk::_mfParamNames field.
inline
MFString &SHLChunkBase::getParamNames(void)
{
    return _mfParamNames;
}

//! Get the SHLChunk::_mfParamNames field.
inline
const MFString &SHLChunkBase::getParamNames(void) const
{
    return _mfParamNames;
}

//! Get the value of the \a index element the SHLChunk::_mfParamValues field.
inline
Vec4f &SHLChunkBase::getParamValues(const UInt32 index)
{
    return _mfParamValues[index];
}

//! Get the SHLChunk::_mfParamValues field.
inline
MFVec4f &SHLChunkBase::getParamValues(void)
{
    return _mfParamValues;
}

//! Get the SHLChunk::_mfParamValues field.
inline
const MFVec4f &SHLChunkBase::getParamValues(void) const
{
    return _mfParamValues;
}

OSG_END_NAMESPACE

#define OSGSHLCHUNKBASE_INLINE_CVSID "@(#)$Id: OSGSHLChunkBase.inl,v 1.1 2004/05/07 16:04:31 a-m-z Exp $"
