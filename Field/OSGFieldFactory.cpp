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
#include "OSGFieldFactory.h"
#include "OSGFieldType.h"
#include "OSGBaseFunctions.h"
#include "OSGLog.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGFIELDFACTORY_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/** \fn const char *FieldFactory::getClassname(void)
 *  \brief Classname
 */

/** \fn FieldFactory::FieldFactory(const FieldFactory &source)
 *  \brief Not implemented.
 */

/** \fn void FieldFactory::operator =(const FieldFactory &source)
 *  \brief Not implemented.
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/** \brief Factory instance
 */

FieldFactory FieldFactory::_the;

/** \brief Field type storage
 */

map<UInt32, FieldType *> *FieldFactory::_fieldTypeM  = NULL;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Destructor
 */

FieldFactory::~FieldFactory(void )
{
	SINFO << "INFO: Destroy Singleton FieldFactory" << endl;
}

/*------------------------------ create ------------------------------------*/

/** \brief Create a field of the given type
 */

Field * FieldFactory::createField(UInt32 typeId)
{
    FieldType *pType = getFieldType(typeId);


	if((pType                != NULL) &&
       (pType->_createMethod != NULL))
    {
		return pType->_createMethod();
    }
	else
    {
		return NULL;
    }
}

/** \brief Create a field of the type given by the type name
 */

Field * FieldFactory::createField(const Char8 *szName)
{
	FieldType *pType          = getFieldType(szName);

	if((pType                != NULL) &&
       (pType->_createMethod != NULL))
    {
		return pType->_createMethod();
    }
	else
    {
		return NULL;
    }
}

/*---------------------------------- type -----------------------------------*/

/** \Brief Get numer of field types
 */

UInt32 FieldFactory::getNFieldTypes( void )
{
	if(_fieldTypeM != NULL) 
 		return _fieldTypeM->size();

	return 0;
}
	

/** \Brief Get type by name
 */

FieldType * FieldFactory::getFieldType (const Char8 *szName)
{
    map<UInt32, FieldType *>::iterator  mIt;
	FieldType                          *returnValue = NULL;
	
	if(_fieldTypeM != NULL) 
    {
        mIt = _fieldTypeM->begin();

        while(mIt != _fieldTypeM->end())
        {
            if(strcmp(szName, (*mIt).second->getCName()) == 0)
            {
				returnValue = (*mIt).second;
				break;
			}
            
            mIt++;
        }
	}

	return returnValue;
}

/** \brief Get type by data type
 */

FieldType *FieldFactory::getFieldType(UInt32 typeId)
{
    map<UInt32, FieldType *>::iterator  mIt;

    if(_fieldTypeM == NULL)
        return NULL;
   
    mIt = _fieldTypeM->find(typeId);

    if(mIt != _fieldTypeM->end())
    {
        return (*mIt).second;
    }
    else
    {
        return NULL;
    }
}


/*---------------------------------- name -----------------------------------*/

/** \brief Get the name of the given data type
 */

const Char8 *FieldFactory::getFieldTypeName(UInt32 typeId)
{
	FieldType *pFieldType = getFieldType(typeId);

	return pFieldType ? pFieldType->getCName() : NULL;
}

/*---------------------------------- instance -------------------------------*/

/** \brief Returns a reference to the global factory
 */

FieldFactory &FieldFactory::the(void)
{
    return _the;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/** \brief Constructor
 */

FieldFactory::FieldFactory(void)
{
}


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

void FieldFactory::addType(FieldType *pType)
{
    if(pType == NULL)
        return;

    if(getFieldType(pType->getId()) != NULL)
        return;

    if(_fieldTypeM == NULL)
        _fieldTypeM = new map<UInt32, FieldType *>();

    (*_fieldTypeM)[pType->getId()] = pType;
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

