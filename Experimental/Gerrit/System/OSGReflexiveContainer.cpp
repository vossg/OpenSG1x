/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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

#define OSG_COMPILEDATASTORE

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

#include "OSGReflexiveContainer.h"
#include "OSGDataElementDesc.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGREFLEXIVECONTAINER_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

ReflexiveContainerType ReflexiveContainer::_type(
    "ReflexiveContainer",
    NULL,
    NULL,
    NULL,
    false);

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

ReflexiveContainerType &ReflexiveContainer::getClassType(void)
{ 
    return _type; 
}

UInt32 ReflexiveContainer::getClassTypeId(void)
{ 
    return _type.getId();
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

ReflexiveContainer::ReflexiveContainer(void)
{
}

ReflexiveContainer::ReflexiveContainer(const ReflexiveContainer &)
{
}

ReflexiveContainer::~ReflexiveContainer(void)
{
}

void ReflexiveContainer::beginEdit(BitVector)
{
}

void ReflexiveContainer::endEdit(BitVector)
{
}

void ReflexiveContainer::changed(BitVector, 
                                 ChangeMode)
{
    // fprintf(stderr, "FC Changed %d %d\n", whichField, fromSync);
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------------------------ access -----------------------------------*/

ReflexiveContainerType &ReflexiveContainer::getReflexType(void)
{ 
    return _type; 
}

const ReflexiveContainerType &ReflexiveContainer::getReflexType(
    void) const
{ 
    return _type; 
}

UInt32 ReflexiveContainer::getTypeId(void) const 
{
    return getReflexType().getId(); 
}

UInt16 ReflexiveContainer::getGroupId(void) const
{
    return getReflexType().getGroupId(); 
}

const Char8 *ReflexiveContainer::getTypeName(void) const 
{
    return getReflexType().getCName(); 
}

AnonObjectP ReflexiveContainer::getElement(UInt32 uiElementId)
{
	const DataElementDesc *pDesc = 
        getReflexType().getElementDesc(uiElementId);

    return pDesc ? pDesc->getElement(*this) : NULL;
}

AnonObjectP ReflexiveContainer::getElement(const Char8 *szElementName)
{
	const DataElementDesc *pDesc = 
        getReflexType().findElementDesc(szElementName);

	return pDesc ? pDesc->getElement(*this) : NULL;
}

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/
