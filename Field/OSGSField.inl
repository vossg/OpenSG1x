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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"
#include <OSGLog.h>

OSG_BEGIN_NAMESPACE

/*! \class osg::SField
 */

/** \typedef SField::Inherited
 *  \brief Parent type
 */

/** \var FieldTypeT SField::_value
 *  \brief Value store
 */

/*-------------------------------------------------------------------------*/
/*                             FieldType                                   */

#if defined(OSG_MICROSOFT_COMPILER_ALERT)
template <class FieldTypeT, Int32 fieldNameSpace>
const FieldType SField<FieldTypeT, fieldNameSpace>::_fieldType = FieldType(
    SFieldTraits::getSName(), 
    SFieldTraits::getPName(),
    SFieldTraits::getType (),
    create,
    FieldType::SINGLE_FIELD);
#else
template <class FieldTypeT, Int32 fieldNameSpace>
const FieldType SField<FieldTypeT, fieldNameSpace>::_fieldType(
    SFieldTraits::getSName(), 
    SFieldTraits::getPName(),
    SFieldTraits::getType (),
    create,
    FieldType::SINGLE_FIELD);
#endif

/*-------------------------------------------------------------------------*/
/*                            Class Get                                    */

template <class FieldTypeT, Int32 fieldNameSpace> inline
const FieldType &SField<FieldTypeT, fieldNameSpace>::getClassType(void)
{
    return _fieldType;
}


/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class FieldTypeT, Int32 fieldNameSpace> inline
SField<FieldTypeT, fieldNameSpace>::SField(void) :
    Inherited(),
    _value   ()
{
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
SField<FieldTypeT, fieldNameSpace>::SField(const SField &obj) :
     Inherited(obj       ),
    _value    (obj._value)
{
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
SField<FieldTypeT, fieldNameSpace>::SField(const FieldTypeT &value) :
     Inherited(),
    _value    (value)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

template <class FieldTypeT, Int32 fieldNameSpace> inline
SField<FieldTypeT, fieldNameSpace>::~SField(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Get                                       */

//! Return a reference to the stored value

template <class FieldTypeT, Int32 fieldNameSpace> inline
FieldTypeT &SField<FieldTypeT, fieldNameSpace>::getValue(void)
{
    return _value;
}

//! Return a const reference to the stored value

template <class FieldTypeT, Int32 fieldNameSpace> inline
const FieldTypeT &SField<FieldTypeT, fieldNameSpace>::getValue(void) const
{
    return _value;
}

//! Returns the size of the field, allway 1

template <class FieldTypeT, Int32 fieldNameSpace> inline
UInt32 SField<FieldTypeT, fieldNameSpace>::getSize(void) const
{
    return 1;
}

//! Returns the type of the field

template <class FieldTypeT, Int32 fieldNameSpace> inline
const FieldType &SField<FieldTypeT, fieldNameSpace>::getType(void) const
{
    return _fieldType;
}


/*-------------------------------------------------------------------------*/
/*                                Set                                      */

//! Copies the values from a given field iff the two fieldtypes match 

template <class FieldTypeT, Int32 fieldNameSpace> inline
void SField<FieldTypeT, fieldNameSpace>::setAbstrValue(const Field &obj)
{
    if(getType() == obj.getType())
    {
        setValue(*((const SField<FieldTypeT, fieldNameSpace> *) &obj));
    }
}

//! Sets the stored value from a given one

template <class FieldTypeT, Int32 fieldNameSpace> inline
void SField<FieldTypeT, fieldNameSpace>::setValue(const FieldTypeT &value)
{
    _value = value;
}

//! \brief Sets the stored value from a given field

template <class FieldTypeT, Int32 fieldNameSpace> inline
void SField<FieldTypeT, 
            fieldNameSpace>::setValue(const Self &obj)
{
    _value = obj._value;
}

/*-------------------------------------------------------------------------*/
/*                           String IO                                     */

//! Sets the field value from a given string

template <class FieldTypeT, Int32 fieldNameSpace> inline
void SField<FieldTypeT, fieldNameSpace>::pushValueByStr(const Char8 *str)
{
    typedef typename osgIF< (SFieldTraits::StringConvertable &
                             Traits::FromStringConvertable), 
                            SFieldTraits, 
                            ErrorFromToString<FieldTypeT> >::_IRet Converter;
    
    Converter::getFromString(_value, str);
}

//! Dump the field to a given string

template <class FieldTypeT, Int32 fieldNameSpace> inline
string &SField<FieldTypeT, 
               fieldNameSpace>::getValueByStr(string &str) const
{
    typedef typename osgIF< (SFieldTraits::StringConvertable &
                             Traits::ToStringConvertable), 
                            SFieldTraits, 
                            ErrorFromToString<FieldTypeT> >::_IRet Converter;
    
    Converter::putToString(_value, str);
    
    return str;
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
string &SField<FieldTypeT, 
               fieldNameSpace>::getValueByStr(string                    &str,
                                              StringConversionStateBase &state)
                                                                          const
{
    typedef typename osgIF< (SFieldTraits::StringConvertable &
                             Traits::ToStringConvertable), 
                            SFieldTraits, 
                            ErrorFromToString<FieldTypeT> >::_IRet Converter;
    
    string valStr;

    state.beginField(this, str);

    Converter::putToString(_value, valStr);
    state.addValueStr(valStr, str);

    state.endField(this, str);

    return str;
}

/*-------------------------------------------------------------------------*/
/*                              MT Sync                                    */

template <class FieldTypeT, Int32 fieldNameSpace> inline
void SField<FieldTypeT, fieldNameSpace>::syncWith(Self &source)
{
    setValue(source);
}

/*-------------------------------------------------------------------------*/
/*                         Binary Interface                                */

template <class FieldTypeT, Int32 fieldNameSpace> inline
UInt32 SField<FieldTypeT, fieldNameSpace>::getBinSize(void)
{
    return SFieldTraits::getBinSize(_value);
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
void SField<FieldTypeT, fieldNameSpace>::copyToBin(BinaryDataHandler &pMem)
{
    SFieldTraits::copyToBin( pMem, 
                            _value);
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
void SField<FieldTypeT, fieldNameSpace>::copyFromBin(BinaryDataHandler &pMem)
{
    SFieldTraits::copyFromBin( pMem, 
                              _value);
}

/*-------------------------------------------------------------------------*/
/*                              MT Sync                                    */

//! Sets the stored value from a given one

template <class FieldTypeT, Int32 fieldNameSpace> inline
void SField<FieldTypeT, fieldNameSpace>::operator =(const SField &source)
{
    if(this != &source)
    {
        _value = source._value;
    }
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

/*! \brief Dump property contents to stderr, should be changed to use a
    log stream instead
*/

template <class FieldTypeT, Int32 fieldNameSpace> inline
void SField<FieldTypeT, fieldNameSpace>::dump(void) const
{
//    cerr << "Dump Field : " << _value << endl;
}

/*-------------------------------------------------------------------------*/
/*                             Create                                      */

//! Create method used by the factory to create an instance

template <class FieldTypeT, Int32 fieldNameSpace> inline
Field *SField<FieldTypeT, fieldNameSpace>::create(void) 
{
    return new SField<FieldTypeT, fieldNameSpace>(); 
}

OSG_END_NAMESPACE

#define OSGMFIELD_INLINE_CVSID "@(#)$Id: $"
