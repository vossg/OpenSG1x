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
 **     class ParallelComposer!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/

#include <OSGConfig.h>

OSG_BEGIN_NAMESPACE


//! access the type of the class
inline
OSG::FieldContainerType &ParallelComposerBase::getClassType(void)
{
    return _type; 
} 

//! access the numerical type of the class
inline
OSG::UInt32 ParallelComposerBase::getClassTypeId(void) 
{
    return _type.getId(); 
} 

//! create a new instance of the class
inline
ParallelComposerPtr ParallelComposerBase::create(void) 
{
    ParallelComposerPtr fc; 

    if(getClassType().getPrototype() != OSG::NullFC) 
    {
        fc = ParallelComposerPtr::dcast(
            getClassType().getPrototype()-> shallowCopy()); 
    }
    
    return fc; 
}

//! create an empty new instance of the class, do not copy the prototype
inline
ParallelComposerPtr ParallelComposerBase::createEmpty(void) 
{ 
    ParallelComposerPtr returnValue; 
    
    newPtr(returnValue); 

    return returnValue; 
}


/*------------------------------ get -----------------------------------*/

//! Get the ParallelComposer::_sfShort field.
inline
SFBool *ParallelComposerBase::getSFShort(void)
{
    return &_sfShort;
}

//! Get the ParallelComposer::_sfAlpha field.
inline
SFBool *ParallelComposerBase::getSFAlpha(void)
{
    return &_sfAlpha;
}

//! Get the ParallelComposer::_sfPcLibPath field.
inline
SFString *ParallelComposerBase::getSFPcLibPath(void)
{
    return &_sfPcLibPath;
}


//! Get the value of the ParallelComposer::_sfShort field.
inline
bool &ParallelComposerBase::getShort(void)
{
    return _sfShort.getValue();
}

//! Get the value of the ParallelComposer::_sfShort field.
inline
const bool &ParallelComposerBase::getShort(void) const
{
    return _sfShort.getValue();
}

//! Set the value of the ParallelComposer::_sfShort field.
inline
void ParallelComposerBase::setShort(const bool &value)
{
    _sfShort.setValue(value);
}

//! Get the value of the ParallelComposer::_sfAlpha field.
inline
bool &ParallelComposerBase::getAlpha(void)
{
    return _sfAlpha.getValue();
}

//! Get the value of the ParallelComposer::_sfAlpha field.
inline
const bool &ParallelComposerBase::getAlpha(void) const
{
    return _sfAlpha.getValue();
}

//! Set the value of the ParallelComposer::_sfAlpha field.
inline
void ParallelComposerBase::setAlpha(const bool &value)
{
    _sfAlpha.setValue(value);
}

//! Get the value of the ParallelComposer::_sfPcLibPath field.
inline
std::string &ParallelComposerBase::getPcLibPath(void)
{
    return _sfPcLibPath.getValue();
}

//! Get the value of the ParallelComposer::_sfPcLibPath field.
inline
const std::string &ParallelComposerBase::getPcLibPath(void) const
{
    return _sfPcLibPath.getValue();
}

//! Set the value of the ParallelComposer::_sfPcLibPath field.
inline
void ParallelComposerBase::setPcLibPath(const std::string &value)
{
    _sfPcLibPath.setValue(value);
}


OSG_END_NAMESPACE

#define OSGPARALLELCOMPOSERBASE_INLINE_CVSID "@(#)$Id: OSGParallelComposerBase.inl,v 1.1 2006/05/08 04:00:01 eysquared Exp $"
