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

#include <OSGLog.h>

OSG_BEGIN_NAMESPACE

/** \fn const char *SField::getClassname(void)
 *  \brief Classname
 */

/** \typedef SField::Inherited
 *  \brief Parent type
 */

/** \var FieldTypeT SField::_value
 *  \brief Value store
 */


/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

template <class FieldTypeT, Int32 fieldNameSpace>
char SField<FieldTypeT, fieldNameSpace>::cvsid[] = "@(#)$Id: $";

/** \brief Field type
 */

#if defined(OSG_MICROSOFT_COMPILER_ALERT)
template <class FieldTypeT, Int32 fieldNameSpace>
const FieldType SField<FieldTypeT, fieldNameSpace>::_fieldType = FieldType(
	SFieldTraits::getSName(), 
	create);
#else
template <class FieldTypeT, Int32 fieldNameSpace>
const FieldType SField<FieldTypeT, fieldNameSpace>::_fieldType(
	SFieldTraits::getSName(), 
	create);
#endif

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/** \brief Get class type
 */

template <class FieldTypeT, Int32 fieldNameSpace> inline
const FieldType &SField<FieldTypeT, fieldNameSpace>::getClassType(void)
{
    return _fieldType;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/** \brief Create method used by the factory to create an instance
 */

template <class FieldTypeT, Int32 fieldNameSpace> inline
Field *SField<FieldTypeT, fieldNameSpace>::create(void) 
{
    return new SField<FieldTypeT>(); 
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

template <class FieldTypeT, Int32 fieldNameSpace> inline
SField<FieldTypeT, fieldNameSpace>::SField(void) :
    Inherited(),
    _value()
{
}


/** \brief Constructor from a give value
 */

template <class FieldTypeT, Int32 fieldNameSpace> inline
SField<FieldTypeT, fieldNameSpace>::SField(const FieldTypeT &value) :
    Inherited(),
    _value(value)
{
}

/** \brief Constructor from a given field
 */

template <class FieldTypeT, Int32 fieldNameSpace> inline
SField<FieldTypeT, fieldNameSpace>::SField(const SField &obj) :
    Inherited(obj),
    _value(obj._value)
{
}

/** \brief Destructor
 */

template <class FieldTypeT, Int32 fieldNameSpace> inline
SField<FieldTypeT, fieldNameSpace>::~SField(void)
{
}

/*--------------------------------- access ----------------------------------*/

/** \brief Return a reference to the stored value
 */

template <class FieldTypeT, Int32 fieldNameSpace> inline
FieldTypeT &SField<FieldTypeT, fieldNameSpace>::getValue(void)
{
    return _value;
}

/** \brief Return a const reference to the stored value
 */

template <class FieldTypeT, Int32 fieldNameSpace> inline
const FieldTypeT &SField<FieldTypeT, fieldNameSpace>::getValue(void) const
{
    return _value;
}

/** \brief Copies the values from a given field iff the two fieldtypes match 
 */

template <class FieldTypeT, Int32 fieldNameSpace> inline
void SField<FieldTypeT, fieldNameSpace>::setAbstrValue(const Field &obj)
{
    if(getType() == obj.getType())
    {
        setValue(*((SField<FieldTypeT> *) &obj));
    }
}

/** \brief Sets the stored value from a given one
 */

template <class FieldTypeT, Int32 fieldNameSpace> inline
void SField<FieldTypeT, fieldNameSpace>::setValue(const FieldTypeT &value)
{
    _value = value;
}

/** \brief Sets the stored value from a given field
 */

template <class FieldTypeT, Int32 fieldNameSpace> inline
void SField<FieldTypeT, 
            fieldNameSpace>::setValue(const SField<FieldTypeT> &obj)
{
    _value = obj._value;
}

/*------------------------- field information -------------------------------*/

/** \brief Returns the field cardinality, allways Field::SINGLE_FIELD
 */

template <class FieldTypeT, Int32 fieldNameSpace> inline
Field::Cardinality SField<FieldTypeT, 
                          fieldNameSpace>::getCardinality (void) const
{
    return SINGLE_FIELD;
}

/** \brief Returns the size of the field, allway 1
 */

template <class FieldTypeT, Int32 fieldNameSpace> inline
UInt32 SField<FieldTypeT, fieldNameSpace>::size(void) const
{
    return 1;
}

/*---------------------------- field type -----------------------------------*/

/** \brief Returns the type of the field
 */

template <class FieldTypeT, Int32 fieldNameSpace> inline
const FieldType &SField<FieldTypeT, fieldNameSpace>::getType(void) const
{
    return _fieldType;
}

/*----------------------------- string io -----------------------------------*/

/** \brief Sets the field value from a given string
 */

template <class FieldTypeT, Int32 fieldNameSpace> inline
void SField<FieldTypeT, fieldNameSpace>::pushValueByStr(const Char8 *str)
{
    typedef osgIF< (FieldDataTraits<FieldTypeT>::StringConvertable &
                    Traits::FromStringConvertable), 
                  FieldDataTraits<FieldTypeT>, 
                  ErrorFromToString<FieldTypeT> >::_IRet Converter;
    
    Converter::getFromString(_value, str);
}

/** \brief Dump the field to a given string
 */

template <class FieldTypeT, Int32 fieldNameSpace> inline
String &SField<FieldTypeT, fieldNameSpace>::getValueByStr(String &string) const
{
    typedef osgIF< (FieldDataTraits<FieldTypeT>::StringConvertable &
                    Traits::ToStringConvertable), 
                  FieldDataTraits<FieldTypeT>, 
                  ErrorFromToString<FieldTypeT> >::_IRet Converter;
    
    Converter::putToString(_value, string);
    
	return string;
}

/*--------------------------------- dump ------------------------------------*/

/** \brief Dump property contents to stderr, should be changed to use a
 *  log stream instead
 */

template <class FieldTypeT, Int32 fieldNameSpace> inline
void SField<FieldTypeT, fieldNameSpace>::dump(void) const
{
    cerr << "Dump Field : " << _value << endl;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

template <class FieldTypeT, Int32 fieldNameSpace> inline
void SField<FieldTypeT, fieldNameSpace>::doSync(Field *source)
{
    setValue(*((SField<FieldTypeT> *) source));
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
void SField<FieldTypeT, fieldNameSpace>::beginEdit(void)
{
    
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

OSG_END_NAMESPACE

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

