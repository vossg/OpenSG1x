/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

/*-------------------------------------------------------------------------*/
/*                            Class Get                                    */

#ifndef WIN32
template <class FieldTypeT, Int32 fieldNameSpace> inline
const FieldType &SField<FieldTypeT, fieldNameSpace>::getClassType(void)
{
    return _fieldType;
}
#endif

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class FieldTypeT, Int32 fieldNameSpace> inline
SField<FieldTypeT, fieldNameSpace>::SField(void) :
     Inherited(),
    _value    ()
{
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
SField<FieldTypeT, fieldNameSpace>::SField(const SField &obj) :
     Inherited(obj       ),
    _value    (obj._value)
{
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
SField<FieldTypeT, fieldNameSpace>::SField(ArgumentType value) :
     Inherited(     ),
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

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename SField<FieldTypeT, fieldNameSpace>::reference 
    SField<FieldTypeT, fieldNameSpace>::getValue(void)

{
    return _value;
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename SField<FieldTypeT, fieldNameSpace>::const_reference
    SField<FieldTypeT, fieldNameSpace>::getValue(void) const
{
    return _value;
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
bool SField<FieldTypeT, fieldNameSpace>::isEmpty(void) const
{
    return false;
}

#ifndef WIN32
template <class FieldTypeT, Int32 fieldNameSpace> inline
const FieldType &SField<FieldTypeT, fieldNameSpace>::getType(void) const
{
    return _fieldType;
}
#endif

template <class FieldTypeT, Int32 fieldNameSpace> inline
UInt32 SField<FieldTypeT, fieldNameSpace>::getSize(void) const
{
    return 1;
}

/*-------------------------------------------------------------------------*/
/*                                Set                                      */

template <class FieldTypeT, Int32 fieldNameSpace> inline
void SField<FieldTypeT, fieldNameSpace>::setValue(ArgumentType value)
{
    _value = value;
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
void SField<FieldTypeT, 
            fieldNameSpace>::setValue(const Self &obj)
{
    _value = obj._value;
}

/*! Copies the values from a given field iff the two fieldtypes are equal
 */

template <class FieldTypeT, Int32 fieldNameSpace> inline
void SField<FieldTypeT, fieldNameSpace>::setAbstrValue(const Field &obj)
{
    if(getType() == obj.getType())
    {
        setValue(*((const SField<FieldTypeT, fieldNameSpace> *) &obj));
    }
}

/*-------------------------------------------------------------------------*/
/*                           String IO                                     */

template <class FieldTypeT, Int32 fieldNameSpace> inline
void SField<FieldTypeT, fieldNameSpace>::pushValueByStr(const Char8 *str)
{
    typedef typename osgIF< (SFieldTraits::StringConvertable &
                             FieldTraits ::FromStringConvertable), 
                            SFieldTraits, 
                            ErrorFromToString<FieldTypeT> >::_IRet Converter;
    
    Converter::getFromString(_value, str);
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
std::string &SField<FieldTypeT, 
                    fieldNameSpace>::getValueByStr(std::string &str) const
{
    typedef typename osgIF< (SFieldTraits::StringConvertable &
                             FieldTraits ::ToStringConvertable), 
                            SFieldTraits, 
                            ErrorFromToString<FieldTypeT> >::_IRet Converter;
    
    Converter::putToString(_value, str);
    
    return str;
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
std::string &SField<FieldTypeT, 
                    fieldNameSpace>::getValueByStr(
                        std::string               &str,
                        StringConversionStateBase &state) const
{
    typedef typename osgIF< (SFieldTraits::StringConvertable &
                             FieldTraits ::ToStringConvertable), 
                            SFieldTraits, 
                            ErrorFromToString<FieldTypeT> >::_IRet Converter;
    
    std::string valStr;

    state.beginField(this, str);

    Converter::putToString(_value, valStr);
    state.addValueStr(valStr, str);

    state.endField(this, str);

    return str;
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
std::string &SField<FieldTypeT,
                    fieldNameSpace>::getValueByStr(std::string &str,
                                                   UInt32       index) const
{
    typedef typename osgIF< (SFieldTraits::StringConvertable &
                             FieldTraits ::ToStringConvertable), 
                            SFieldTraits, 
                            ErrorFromToString<FieldTypeT> >::_IRet Converter;

    if(index > 0)
    {
        return str;
    }

    Converter::putToString(_value, str);
    
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

template <class FieldTypeT, Int32 fieldNameSpace> inline
void SField<FieldTypeT, fieldNameSpace>::dump(void) const
{
//    std::cerr << "Dump Field : " << _value << std::endl;
}

/*-------------------------------------------------------------------------*/
/*                             Create                                      */

template <class FieldTypeT, Int32 fieldNameSpace> inline
Field *SField<FieldTypeT, fieldNameSpace>::create(void) 
{
    return new SField<FieldTypeT, fieldNameSpace>(); 
}

OSG_END_NAMESPACE

#define OSGSFIELD_INLINE_CVSID "@(#)$Id: $"
