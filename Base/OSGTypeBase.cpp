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

#include "OSGTypeBase.h"
#include <OSGTypeFactory.h>

OSG_USING_NAMESPACE

namespace 
{
    char cvsid_cpp[] = "@(#)$Id: $";
    char cvsid_hpp[] = OSGTYPEBASE_HEADER_CVSID;
}

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

TypeBase::TypeBase(const Char8 *szName,
                   const Char8 *szParentName,
                         Bool   bRegister) :
    _uiTypeId    (0),
    _uiTypeRootId(0),
    _pParent     (NULL),
    _szName      (szName),
    _szParentName(szParentName)
{
    if(bRegister == true)
        _uiTypeId = TypeFactory::the()->registerType(this);
}

/** \brief Destructor
 */

TypeBase::~TypeBase(void)
{
}


/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/** \brief Get method for attribute Id
 */

UInt32 TypeBase::getId(void) const 
{
    return _uiTypeId; 
}

/** \brief Get method for attribute name 
 */

const IDString &TypeBase::getName(void) const
{
    return _szName;
}

/** \brief Get method for name as c string
 */

const Char8 *TypeBase::getCName(void) const 
{
    return _szName.str(); 
}

/** \brief Get method for attribute parent name 
 */

const IDString &TypeBase::getParentName (void) const
{
    return _szParentName;
}

/** \brief Get method for name as c string
 */

const Char8  *TypeBase::getCParentName(void) const
{
    return _szParentName.str();
}

/*-------------------------- inheriteance ---------------------------------*/

Bool TypeBase::isDerivedFrom(const TypeBase &OSG_CHECK_ARG(other)) const
{
    return false;
}

/*-------------------------- comparison -----------------------------------*/

Bool TypeBase::operator ==(const TypeBase &other) const
{
    return _uiTypeId == other._uiTypeId;
}

Bool TypeBase::operator !=(const TypeBase &other) const
{
    return ! (*this == other);
}


///---------------------------------------------------------------------------
///  FUNCTION: 
///---------------------------------------------------------------------------
//:  Example for the head comment of a function
///---------------------------------------------------------------------------
///
//p: Paramaters: 
//p: 
///
//g: GlobalVars:
//g: 
///
//r: Return:
//r: 
///
//c: Caution:
//c: 
///
//a: Assumptions:
//a: 
///
//d: Description:
//d: 
///
//s: SeeAlso:
//s: 
///---------------------------------------------------------------------------

