/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

#include "OSGConfig.h"

#include <iostream>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

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

/***************************************************************************\
 *                           Instance methods                              *
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

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

template <class BaseT> inline
ScanParseFieldTypeMapper<BaseT>::ScanParseFieldTypeMapper(void) :
	Inherited(),
    _mIntExt(),
    _mExtInt()

{
    Inherited::setMapTypeIds(true);
}

/** \brief Destructor
 */

template <class BaseT> inline
ScanParseFieldTypeMapper<BaseT>::~ScanParseFieldTypeMapper(void)
{
}

/*------------------------------ access -----------------------------------*/

template <class BaseT> inline
void ScanParseFieldTypeMapper<BaseT>::setIntExtMapping(
    UInt32            uiMappedType,
    BuildInFieldTypes eBuildInType)
{
    _mExtInt[uiMappedType] = eBuildInType;
}

template <class BaseT> inline
void ScanParseFieldTypeMapper<BaseT>::setExtIntMapping(
    BuildInFieldTypes eBuildInType,
    UInt32            uiMappedType)
{
    _mIntExt[eBuildInType] = uiMappedType;
}

/*---------------------------- properties ---------------------------------*/

template <class BaseT> inline
Int32 ScanParseFieldTypeMapper<BaseT>::mapExtIntFieldType(
    const Char8 *,
    const Int32  iFieldTypeId)
{
    ExtIntMap::iterator gMIt = _mExtInt.find(iFieldTypeId);

    if(gMIt != _mExtInt.end())
    {
        return gMIt->second;
    }
    else
    {
        return -iFieldTypeId;
    }
}

template <class BaseT> inline
Int32 ScanParseFieldTypeMapper<BaseT>::mapIntExtFieldType(
    const Char8 *,
    const Int32  iFieldTypeId)
{
    IntExtMap::iterator gMIt = _mIntExt.find(
        (BuildInFieldTypes) iFieldTypeId);

    if(gMIt != _mIntExt.end())
    {
        return gMIt->second;
    }
    else
    {
        return -iFieldTypeId;
    }
}

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

OSG_END_NAMESPACE

#define OSGSCANPARSEFIELDTYPEMAPPER_INLINE_CVSID "@(#)$Id: $"
