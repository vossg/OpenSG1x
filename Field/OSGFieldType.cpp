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

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include "OSGFieldType.h"
#include "OSGBaseFunctions.h"
#include "OSGFieldFactory.h"
#include "OSGThreadManager.h"
#include "OSGLog.h"

OSG_USING_NAMESPACE

/** \fn const char *FieldType::getClassname(void)
 *  \brief Classname
 */

/** \typedef Field * (*FieldType::CreateFieldMethod)(void)
 *  Field create method
 */

/** \var FieldDataType FieldType::_typeId
 *  \brief Field data type
 */

/** \var char *FieldType::_szName
 *  \brief Field type name
 */

/** \var FieldType::_createMethod
 *  \brief Field create method
 */

/** \fn FieldType::FieldType(const FieldType &source)
 *  \brief Not implemented.
 */

/** \fn void FieldType::operator =(const FieldType &source)
 *  \brief Not implemented.
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char FieldType::cvsid[] = "@(#)$Id: $";

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

/** \brief Constructor
 */

FieldType::FieldType(const char           *szName,
                           CreateFieldMethod  createMethod) :
    _typeId(0), 
    _szName(NULL), 
    _createMethod(createMethod)
{	
	if((szName       != NULL        ) && 
       (*szName      != '\0'        ) && 
       (createMethod != NULL))
    {
		if(FieldFactory::_fieldTypeV == NULL) 
        {
			FieldFactory::_fieldTypeV = new vector<FieldType *>;
		}
        
		FieldFactory::_fieldTypeV->push_back(this);
		_typeId = FieldFactory::_fieldTypeV->size();

        osgstringDup(szName, _szName);		
	}
	else
		cerr << "ERROR: Invalid Field::Field() parameter" << endl;

    SLOG << "Initialized FieldType : " << _szName << endl;
}


/** \brief Destructor
 */

FieldType::~FieldType(void)
{
	(*FieldFactory::_fieldTypeV)[_typeId] = 0;

	delete [] _szName;
}

/*--------------------------------- access ----------------------------------*/

/** \brief Get field data type. \sa FieldDataType
 */

UInt32 FieldType::getTypeId(void) const
{
    return _typeId;
}

/** \brief Get type name
 */

const char *FieldType::getName(void) const
{
    return _szName;
}

/*-------------------------------- comparision ------------------------------*/

Bool FieldType::operator ==(const FieldType &source) const
{
    return _typeId == source._typeId;
}

Bool FieldType::operator !=(const FieldType &source) const
{
    return ! (*this == source);
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/



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




