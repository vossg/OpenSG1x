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

#define OSG_COMPILEFIELDCONTAINER

#include <OSGString.h>

#include "OSGFieldContainer.h"
#include "OSGFieldDescription.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char FieldDescription::cvsid[] = "@(#)$Id: $";

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

/*! \brief Default Constructor 
 */

FieldDescription::FieldDescription(
    const FieldType         &fieldType, 
    const Char8             *name, 
    const UInt32             fieldId,
    const BitVector          fieldMask,
    const Bool               internal,
          FieldAccessMethod  accessMethod,
    const Char8             *defaultValue) :
    _fieldType(fieldType), 
    _name(name),
    _fieldId(fieldId),
    _fieldMask(fieldMask),
    _internal(internal),
    _accessMethod(accessMethod),
    _indexAccessMethod(NULL),
    _defaultValue(defaultValue) 
{
}

/*! \brief Default Constructor 
 */

FieldDescription::FieldDescription(
    const FieldType              &fieldType, 
    const Char8                  *name, 
    const UInt32                  fieldId,
    const BitVector               fieldMask,
    const Bool                    internal,
          FieldIndexAccessMethod  indexAccessMethod,
    const Char8                  *defaultValue) :
    _fieldType(fieldType), 
    _name(name),
    _fieldId(fieldId),
    _fieldMask(fieldMask),
    _internal(internal),
    _accessMethod(NULL),
    _indexAccessMethod(indexAccessMethod),
    _defaultValue(defaultValue) 
{
}

FieldDescription::FieldDescription(const FieldDescription &source) :
    _fieldType        (source._fieldType),
    _name             (source._name),
    _fieldId          (source._fieldId),
    _fieldMask        (source._fieldMask),
    _internal         (source._internal),
    _accessMethod     (source._accessMethod),
    _indexAccessMethod(source._indexAccessMethod),
    _defaultValue     (source._defaultValue) 
{
}


/*! \brief Destructor 
 */

FieldDescription::~FieldDescription(void) 
{
}



/*------------------------------ access -----------------------------------*/

/*! \brief get method for attribute name 
 */

const Char8 *FieldDescription::getName(void) const
{
    return _name.str(); 
}

/*! \brief get method for attribute defaultValue 
*/

const Char8 *FieldDescription::getDefaultValue(void) const
{
    return _defaultValue.str(); 
}

/*! \brief get method for attribute dataType 
 */

UInt32 FieldDescription::getTypeId(void) const
{
    return _fieldType.getTypeId(); 
}

BitVector FieldDescription::getFieldMask(void) const
{
    return _fieldMask;
}

void FieldDescription::setFieldMask(BitVector fieldMask)
{
    _fieldMask = fieldMask;
}

UInt32 FieldDescription::getFieldId(void) const
{
    return _fieldId;
}

void FieldDescription::setFieldId(UInt32 fieldId)
{
    _fieldId = fieldId;
}

Bool FieldDescription::isValid(void)  const
{
    return (_name.length()) ? true : false; 
} 

void FieldDescription::setAccessMethod(
    FieldAccessMethod accessMethod)
{
    _accessMethod = accessMethod;
}

void FieldDescription::setIndexAccessMethod(
    FieldIndexAccessMethod indexAccessMethod)
{
    _indexAccessMethod = indexAccessMethod;
}

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

void FieldDescription::print(void) const
{
	cerr << "FieldDescription: type: " << _fieldType.getName() << "("
		 << _fieldType.getTypeId() << "), name: " 
         << _name << ", " << _accessMethod
         << ", defaultValue: " 
         << (_defaultValue.str() ? _defaultValue.str() : "NONE") 
         << ", Id : " << _fieldId
         << ", Mask : " << _fieldMask
         << endl;
}

/*-------------------------- comparison -----------------------------------*/


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

Field *FieldDescription::getField(FieldContainer &fc) const
{
	Field *field = NULL;

	if(_accessMethod != NULL)
    {
		field = ( (&fc)->*_accessMethod) ();
    }
    else if(_indexAccessMethod != NULL)
    {
        field = ( (&fc)->*_indexAccessMethod)(_fieldId);
    }
	else 
    {
		SWARNING << "No accessMethod for " << _name << endl;
	}

	return field;
}

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

