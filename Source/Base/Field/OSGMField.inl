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

#include <algorithm>

OSG_BEGIN_NAMESPACE

#ifndef STD
#define STD std
#endif

/*-------------------------------------------------------------------------*/
/*                            Class Get                                    */

#ifndef WIN32
template <class FieldTypeT, Int32 fieldNameSpace> inline
const FieldType &MField<FieldTypeT, fieldNameSpace>::getClassType(void)
{
    return _fieldType;
}
#endif

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class FieldTypeT, Int32 fieldNameSpace> inline
MField<FieldTypeT, fieldNameSpace>::MField(void) :
     Inherited(),
    _values   ()
{
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
MField<FieldTypeT, fieldNameSpace>::MField(const MField &obj) :
     Inherited(obj        ),
    _values   (obj._values)
{
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
MField<FieldTypeT, fieldNameSpace>::MField(const UInt32 size) :
     Inherited(),
    _values   ()
{
    _values.resize(size);
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

template <class FieldTypeT, Int32 fieldNameSpace> inline
MField<FieldTypeT, fieldNameSpace>::~MField(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Get                                       */

/*! Return a reference to the value store 
 */

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename MField<FieldTypeT, fieldNameSpace>::StorageType &
    MField<FieldTypeT, fieldNameSpace>::getValues(void)
{
    return _values;
}

/*! Return a const reference to the value store 
 */

template <class FieldTypeT, Int32 fieldNameSpace> inline
const typename MField<FieldTypeT, fieldNameSpace>::StorageType &
    MField<FieldTypeT, fieldNameSpace>::getValues(void) const
{
    return _values;
}

#ifndef WIN32
template <class FieldTypeT, Int32 fieldNameSpace> inline
const FieldType &MField<FieldTypeT, fieldNameSpace>::getType(void) const
{
    return _fieldType;
}
#endif

template <class FieldTypeT, Int32 fieldNameSpace> inline
bool MField<FieldTypeT, fieldNameSpace>::isEmpty(void) const
{
    return empty();
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
void MField<FieldTypeT, fieldNameSpace>::operator =(const MField &source)
{
    if(this == &source)
       return;

    _values = source._values;
}

/*-------------------------------------------------------------------------*/
/*                                Set                                      */

/*! \brief Copies the values from a given field iff the two fieldtypes are 
    equal.
*/

template <class FieldTypeT, Int32 fieldNameSpace> inline
void MField<FieldTypeT, fieldNameSpace>::setAbstrValue(const Field &obj)
{
    if(getType() == obj.getType())
    {
        setValues(*((const MField<FieldTypeT, fieldNameSpace> *) &obj));
    }
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
void MField<FieldTypeT, fieldNameSpace>::setValues(const StorageType &value)
{
    _values = value;
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
void MField<FieldTypeT, fieldNameSpace>::setValues(const Self &obj)
{
    _values = obj._values;
}

/*-------------------------------------------------------------------------*/
/*                             STL Interface                               */

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename MField<FieldTypeT, 
                fieldNameSpace>::iterator MField<FieldTypeT, 
                                                 fieldNameSpace>::begin (void)
{
    return _values.begin();
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename MField<FieldTypeT, 
                fieldNameSpace>::iterator MField<FieldTypeT, 
                                                 fieldNameSpace>::end(void)
{
    return _values.end();
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename MField<FieldTypeT, 
                fieldNameSpace>::const_iterator MField<FieldTypeT, 
                                                       fieldNameSpace>::begin(
                                                           void) const
{
    return _values.begin();
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename MField<FieldTypeT, 
                fieldNameSpace>::const_iterator MField<FieldTypeT,
                                                       fieldNameSpace>::end(
                                                           void) const
{
    return _values.end();
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename MField<FieldTypeT, 
                fieldNameSpace>::reference MField<FieldTypeT, 
                                                  fieldNameSpace>::front(void)
{
    return _values.front();
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename MField<FieldTypeT, 
                fieldNameSpace>::const_reference MField<FieldTypeT, 
                                                        fieldNameSpace>::front(
                                                            void) const
{
    return _values.front();
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename MField<FieldTypeT, 
                fieldNameSpace>::reference MField<FieldTypeT, 
                                                  fieldNameSpace>::back(void)
{
    return _values.back();
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename MField<FieldTypeT, 
                fieldNameSpace>::const_reference MField<FieldTypeT, 
                                                        fieldNameSpace>::back(
                                                            void) const
{
    return _values.back();
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
void MField<FieldTypeT, fieldNameSpace>::clear(void)
{
    _values.clear();
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename MField<FieldTypeT, 
                fieldNameSpace>::iterator MField<FieldTypeT, 
                                                 fieldNameSpace>::insert(
    iterator pos, ArgumentType value)
{
    return _values.insert(pos, value);
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename MField<FieldTypeT, 
                fieldNameSpace>::iterator MField<FieldTypeT, 
                                                 fieldNameSpace>::erase(
                                                     iterator pos)
{
    return _values.erase(pos);
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename MField<FieldTypeT, 
                fieldNameSpace>::iterator MField<FieldTypeT, 
                                                 fieldNameSpace>::find(
    ArgumentType value)
{
    return STD::find(_values.begin(), _values.end(), value);
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename MField<FieldTypeT, 
                fieldNameSpace>::const_iterator MField<FieldTypeT, 
                                                       fieldNameSpace>::find(
    ArgumentType value) const
{
    return STD::find(_values.begin(), _values.end(), value);
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
void MField<FieldTypeT, fieldNameSpace>::push_back(ArgumentType value)
{
    _values.push_back(value);
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
void MField<FieldTypeT, fieldNameSpace>::resize(size_t newsize, FieldTypeT t)
{
    _values.resize(newsize, t);
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
void MField<FieldTypeT, fieldNameSpace>::reserve(size_t newsize)
{
    _values.reserve(newsize);
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
UInt32 MField<FieldTypeT, fieldNameSpace>::size(void) const
{
    return _values.size();
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
bool MField<FieldTypeT, fieldNameSpace>::empty(void) const
{
    return _values.empty();
}

/*-------------------------------------------------------------------------*/
/*                           String IO                                     */

template <class FieldTypeT, Int32 fieldNameSpace> inline
void MField<FieldTypeT, fieldNameSpace>::pushValueByStr(const Char8 *str)
{
    FieldTypeT  tmpVal;

    typedef typename osgIF< (MFieldTraits::StringConvertable &
                             FieldTraits ::FromStringConvertable), 
                            MFieldTraits, 
                            ErrorFromToString<FieldTypeT> >::_IRet Converter;
    
    Converter::getFromString(tmpVal, str);
    
    push_back(tmpVal);
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
std::string &MField<FieldTypeT, 
                    fieldNameSpace>::getValueByStr(std::string &str) const
{
    std::string tmpString;

    typedef typename osgIF< (MFieldTraits::StringConvertable &
                             FieldTraits ::FromStringConvertable),
                            MFieldTraits,
                            ErrorFromToString<FieldTypeT> >::_IRet Converter;

    for(UInt32 i = 0; i < size(); ++i)
    {
        Converter::putToString(_values[i], tmpString);

        str.append(tmpString);

        if(i < (size()-1))
        {
            str.append(", ");
        }
    }

    return str;
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
std::string &MField<FieldTypeT, 
                    fieldNameSpace>::getValueByStr(
                        std::string               &outStr,
                        StringConversionStateBase &state) const
{
    std::string valStr;

    typedef typename osgIF< (MFieldTraits::StringConvertable &
                             FieldTraits ::FromStringConvertable),
                            MFieldTraits,
                            ErrorFromToString<FieldTypeT> >::_IRet Converter;

    state.beginField(this, outStr);

    for(UInt32 i = 0; i < size(); ++i)
    {
        valStr.erase();
        Converter::putToString(_values[i], valStr);

        state.addValueStr(valStr, outStr);
    }

    state.endField(this, outStr);
    
    return outStr;
}

/*-------------------------------------------------------------------------*/
/*                           Index Operator                                */

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename MField<FieldTypeT, fieldNameSpace>::reference
    MField<FieldTypeT, fieldNameSpace>::operator [](UInt32 index)
{
    return _values[index];
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename MField<FieldTypeT, fieldNameSpace>::const_reference
    MField<FieldTypeT, fieldNameSpace>::operator [](UInt32 index) const
{
    return _values[index];
}

#ifndef OSG_DISABLE_DEPRECIATED
template <class FieldTypeT, Int32 fieldNameSpace> inline
typename MField<FieldTypeT, fieldNameSpace>::reference 
    MField<FieldTypeT, fieldNameSpace>::getValue (const UInt32 index)
{
    return operator[](index);
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename MField<FieldTypeT, fieldNameSpace>::const_reference
    MField<FieldTypeT, fieldNameSpace>::getValue (const UInt32 index) const
{
    return operator[](index);
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
UInt32 MField<FieldTypeT, fieldNameSpace>::getSize(void) const
{
    return size();
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
void MField<FieldTypeT, fieldNameSpace>::setValue(       ArgumentType value,
                                                  const UInt32       index)
{
    operator[](index) = value;
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
void MField<FieldTypeT, fieldNameSpace>::addValue(ArgumentType value)
{
    push_back(value);
}
#endif

/*-------------------------------------------------------------------------*/
/*                              MT Sync                                    */

template <class FieldTypeT, Int32 fieldNameSpace> inline
void MField<FieldTypeT, fieldNameSpace>::syncWith(Self &source)
{
    setValues(source);
}

/*-------------------------------------------------------------------------*/
/*                         Binary Interface                                */

template <class FieldTypeT, Int32 fieldNameSpace> inline
UInt32 MField<FieldTypeT, fieldNameSpace>::getBinSize(void)
{
    return sizeof(UInt32) + // num elements
           MFieldTraits::getBinSize(&(_values[0]), _values.size());
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
void MField<FieldTypeT, fieldNameSpace>::copyToBin(BinaryDataHandler &pMem)
{
    UInt32 n = _values.size();

    pMem.putValue(n);
    MFieldTraits::copyToBin(   pMem, 
                            &(_values[0]),
                              _values.size());
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
void MField<FieldTypeT, fieldNameSpace>::copyFromBin(BinaryDataHandler &pMem)
{
    UInt32 n;

     pMem  .getValue(n);
    _values.clear ( );

#ifdef __hpux
    FieldTypeT tmpVal;

    _values.resize(n, tmpVal);
#else
    _values.resize(n);
#endif

    MFieldTraits::copyFromBin(pMem, 
                              &(_values[0]),
                              n);
}


/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

template <class FieldTypeT, Int32 fieldNameSpace> inline
void MField<FieldTypeT, fieldNameSpace>::dump(void) const
{
    std::cout << "STMFST : " << std::endl;

    for(UInt32 i = 0; i < _values.size(); i++)
    {
//        cout << _values[i] << " , ";
    }

    std::cout << std::endl;
}

/*-------------------------------------------------------------------------*/
/*                             Create                                      */

template <class FieldTypeT, Int32 fieldNameSpace> inline
Field *MField<FieldTypeT, fieldNameSpace>::create(void) 
{
    return new MField<FieldTypeT, fieldNameSpace>(); 
}

OSG_END_NAMESPACE

#define OSGMFIELD_INLINE_CVSID "@(#)$Id: $"


