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

#define OSG_COMPILEBASE

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

#include "OSGTypeFactory.h"

#include <OSGLog.h>
#include <OSGTypeBase.h>

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char TypeFactory::cvsid[] = "@(#)$Id: $";

TypeFactory *TypeFactory::_the = NULL;

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


TypeFactory *TypeFactory::the(void)
{
    if(_the == NULL)
        _the = new TypeFactory;

    return _the;
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

TypeFactory::TypeFactory(void) :
    _mTypeNameMap()
{
}


/** \brief Destructor
 */

TypeFactory::~TypeFactory(void)
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

UInt32 TypeFactory::findTypeStatic(const Char8 *szName)
{
	TypeNameMapCnstIt  typeIt;
	UInt32             uiTypeId = 0;

    typeIt   = _mTypeNameMap.find(StringLink(szName));
    uiTypeId = (typeIt == _mTypeNameMap.end()) ? 0 : (*typeIt).second;

	return uiTypeId;
}

UInt32 TypeFactory::registerType(TypeBase *pType)
{
    UInt32 returnValue = 0;

    if(pType == NULL)
    {
		SWARNING << "no data store given" << endl;

		return returnValue;        
    }

	if(pType->getName().empty() == true) 
    {
		SWARNING << "OSGDataElementType without name" << endl;

		return returnValue;
	}

    if(findTypeStatic(pType->getCName()) != 0)
    {
        SWARNING << "ERROR: Can't add a second "
                    << "type with the name" << pType->getCName() << endl;

        return returnValue;
    }

    returnValue = _mTypeNameMap.size() + 1;
    
    _mTypeNameMap[StringLink(pType->getCName())] = returnValue;

    PDEBUG << "Registered type " << pType->getCName() 
           << " | "              << returnValue 
           << endl;

    return returnValue;
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/




//---------------------------------------------------------------------------
//  FUNCTION: 
//---------------------------------------------------------------------------
//:  Example for the head comment of a function
//---------------------------------------------------------------------------
//
//p: Paramaters: 
//p: 
//
//g: GlobalVars:
//g: 
//
//r: Return:
//r: 
//
//c: Caution:
//c: 
//
//a: Assumptions:
//a: 
//
//d: Description:
//d: 
//
//s: SeeAlso:
//s: 
//---------------------------------------------------------------------------

