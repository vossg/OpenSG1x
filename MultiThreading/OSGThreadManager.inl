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


#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <OSGTypeFactory.h>

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

template <class MPFieldT>
char MPFieldStore<MPFieldT>::cvsid[] = "@(#)$Id: $";

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

template <class MPFieldT>
UInt32 MPFieldStore<MPFieldT>::registerMPType(
    MPFieldType *pType)
{
    UInt32 returnValue = 0;

    if(pType == NULL)
        return 0;

    MPFieldType *pTmp = findMPFieldType(pType->getCName());

    if(pTmp != NULL)
    {
        SLOG << "Error could not add second mp type with name " 
                << pType->getCName() 
                << endl;
        
        return returnValue;
    }

    returnValue = TypeFactory::the()->registerType(pType);

    if(returnValue == 0)
    {
        SLOG << "Error in base type registration" << endl;
        return returnValue;
    }

    _mFieldTypeMap[StringLink(pType->getCName())] = pType;

    return returnValue;
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

template <class MPFieldT>
MPFieldStore<MPFieldT>::MPFieldStore(void)
{
}

/** \brief Destructor
 */

template <class MPFieldT>
MPFieldStore<MPFieldT>::~MPFieldStore(void)
{
}

/*------------------------------ access -----------------------------------*/

template <class MPFieldT>
MPFieldT *MPFieldStore<MPFieldT>::getMPField(
    const Char8 *szName,
    const Char8 *szTypeName)
{
    MPFieldT    *returnValue = NULL;
    MPFieldType *pElemType;

    returnValue = findMPField(szName);

    if(returnValue == NULL)
    {
        pElemType = findMPFieldType(szTypeName);

        if(pElemType != NULL)
        {
            returnValue = pElemType->create(szName);
            
            if(returnValue != NULL)
            {
                _mFieldMap[StringLink(returnValue->getCName())] = 
                    returnValue;
            }
        }
        else
        {
            returnValue = NULL;
        }
    }

    return returnValue;
}

template <class MPFieldT>
MPFieldT *MPFieldStore<MPFieldT>::findMPField(
    const Char8 *szName)
{
    MPFieldMapIt gIt;
    
    if(szName == NULL)
        return NULL;

    gIt = _mFieldMap.find(StringLink(szName));

    if(gIt != _mFieldMap.end())
        return (*gIt).second;
    else
        return NULL;
}

template <class MPFieldT>
void MPFieldStore<MPFieldT>::removeMPField(MPFieldT *pField)
{
    if(pField == NULL)
        return;

    MPFieldMapIt gIt = _mFieldMap.find(
        StringLink(pField->getCName()));
    
    if(gIt != _mFieldMap.end())
    {
        _mFieldMap.erase(gIt);
    }
}

template <class MPFieldT>
void MPFieldStore<MPFieldT>::clear(void)
{
    MPFieldMapIt gIt = _mFieldMap.begin();

    while(gIt != _mFieldMap.end())
    {
        delete (*gIt).second;
        gIt++;
    }

    _mFieldMap.clear();
}

/*---------------------------- properties ---------------------------------*/

template <class MPFieldT>
MPFieldStore<MPFieldT>::MPFieldType *
    MPFieldStore<MPFieldT>::findMPFieldType(
        const Char8 *szName) const
{
    MPFieldTypeMapCIt gIt;

    if(szName == NULL)
    {
        SWARNING << "typename == NULL" << endl;
        return NULL;
    }

    gIt = _mFieldTypeMap.find(StringLink(szName));

    if(gIt != _mFieldTypeMap.end())
    {
        return (*gIt).second;
    }
    else 
    {
        SWARNING << "could not find type named : " << szName << endl;
        return NULL;
    }
}

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

OSG_END_NAMESPACE
