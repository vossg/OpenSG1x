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
 **     class RotateManipulator!
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#define OSG_COMPILEROTATEMANIPULATORINST

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>

#include "OSGRotateManipulatorBase.h"
#include "OSGRotateManipulator.h"


OSG_USING_NAMESPACE

const OSG::BitVector RotateManipulatorBase::MTInfluenceMask = 
    (Inherited::MTInfluenceMask) | 
    (static_cast<BitVector>(0x0) << Inherited::NextFieldId); 



FieldContainerType RotateManipulatorBase::_type(
    "RotateManipulator",
    "Manipulator",
    NULL,
    (PrototypeCreateF) &RotateManipulatorBase::createEmpty,
    RotateManipulator::initMethod,
    NULL,
    0);

//OSG_FIELD_CONTAINER_DEF(RotateManipulatorBase, RotateManipulatorPtr)

/*------------------------------ get -----------------------------------*/

FieldContainerType &RotateManipulatorBase::getType(void) 
{
    return _type; 
} 

const FieldContainerType &RotateManipulatorBase::getType(void) const 
{
    return _type;
} 


FieldContainerPtr RotateManipulatorBase::shallowCopy(void) const 
{ 
    RotateManipulatorPtr returnValue; 

    newPtr(returnValue, dynamic_cast<const RotateManipulator *>(this)); 

    return returnValue; 
}

UInt32 RotateManipulatorBase::getContainerSize(void) const 
{ 
    return sizeof(RotateManipulator); 
}


void RotateManipulatorBase::executeSync(      FieldContainer &other,
                                    const BitVector      &whichField)
{
    this->executeSyncImpl((RotateManipulatorBase *) &other, whichField);
}

/*------------------------- constructors ----------------------------------*/

#ifdef OSG_WIN32_ICL
#pragma warning (disable : 383)
#endif

RotateManipulatorBase::RotateManipulatorBase(void) :
    Inherited() 
{
}

#ifdef OSG_WIN32_ICL
#pragma warning (default : 383)
#endif

RotateManipulatorBase::RotateManipulatorBase(const RotateManipulatorBase &source) :
    Inherited                 (source)
{
}

/*-------------------------- destructors ----------------------------------*/

RotateManipulatorBase::~RotateManipulatorBase(void)
{
}

/*------------------------------ access -----------------------------------*/

UInt32 RotateManipulatorBase::getBinSize(const BitVector &whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);


    return returnValue;
}

void RotateManipulatorBase::copyToBin(      BinaryDataHandler &pMem,
                                  const BitVector         &whichField)
{
    Inherited::copyToBin(pMem, whichField);


}

void RotateManipulatorBase::copyFromBin(      BinaryDataHandler &pMem,
                                    const BitVector    &whichField)
{
    Inherited::copyFromBin(pMem, whichField);


}

void RotateManipulatorBase::executeSyncImpl(      RotateManipulatorBase *pOther,
                                        const BitVector         &whichField)
{

    Inherited::executeSyncImpl(pOther, whichField);


}



OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
DataType FieldDataTraits<RotateManipulatorPtr>::_type("RotateManipulatorPtr", "ManipulatorPtr");
#endif


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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGRotateManipulatorBase.cpp,v 1.2 2005/06/26 21:13:56 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGROTATEMANIPULATORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGROTATEMANIPULATORBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGROTATEMANIPULATORFIELDS_HEADER_CVSID;
}
