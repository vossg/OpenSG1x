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

/*! \class osg::MField
 */

/*! \typedef MField::Inherited
    \brief Parent type
*/

/*! \var StorageType MField::_values
    \brief Value store
*/

/*! \typedef vector<FieldTypeT> MField::StorageType
    \brief Storage type
*/

/*! \typedef vector<FieldTypeT>::iterator MField::iterator
    \brief Storage iterator
*/

/*! \typedef vector<FieldTypeT>::const_iterator MField::const_iterator
    \brief Const Storage iterator
*/

/*! \typedef vector<FieldTypeT>::reference MField::reference
    \brief Value reference
*/

/*! \typedef vector<FieldTypeT>::const_reference MField::const_reference
    \brief Const value reference
*/

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
    _values(0)
{
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
MField<FieldTypeT, fieldNameSpace>::MField(const MField &obj) :
     Inherited(obj),
    _values   (obj._values)
{
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
MField<FieldTypeT, fieldNameSpace>::MField(const UInt32 size) :
    Inherited()
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

//! Return a reference to the stored value at index index

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename MField<FieldTypeT, fieldNameSpace>::reference 
    MField<FieldTypeT, fieldNameSpace>::getValue(const UInt32 index)
{
    return _values[index];
}

//! Return a const reference to the stored value at index index

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename MField<FieldTypeT, fieldNameSpace>::const_reference
    MField<FieldTypeT, fieldNameSpace>::getValue(const UInt32 index) const
{
    return _values[index];
}

//! Return a reference to the value store 

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename MField<FieldTypeT, fieldNameSpace>::StorageType &
    MField<FieldTypeT, fieldNameSpace>::getValues(void)
{
    return _values;
}

//! Return a const reference to the value store 

template <class FieldTypeT, Int32 fieldNameSpace> inline
const typename MField<FieldTypeT, fieldNameSpace>::StorageType &
    MField<FieldTypeT, fieldNameSpace>::getValues(void) const
{
    return _values;
}

//! Returns the size of the field

template <class FieldTypeT, Int32 fieldNameSpace> inline
bool MField<FieldTypeT, fieldNameSpace>::isEmpty(void) const
{
    return  empty();
}


//! Returns the type of the field

#ifndef WIN32
template <class FieldTypeT, Int32 fieldNameSpace> inline
const FieldType &MField<FieldTypeT, fieldNameSpace>::getType(void) const
{
    return _fieldType;
}
#endif

/*-------------------------------------------------------------------------*/
/*                                Set                                      */

/*! \brief Copies the values from a given field iff the two fieldtypes are 
    the same.
*/

template <class FieldTypeT, Int32 fieldNameSpace> inline
void MField<FieldTypeT, fieldNameSpace>::setAbstrValue(const Field &obj)
{
    if(getType() == obj.getType())
    {
        setValues(*((const MField<FieldTypeT, fieldNameSpace> *) &obj));
    }
}

//! Set the value at the given index to values

template <class FieldTypeT, Int32 fieldNameSpace> inline
void MField<FieldTypeT, fieldNameSpace>::setValue(const FieldTypeT &value,
                                                  const UInt32      index)
{
    _values[index] = value;
}

//! Copies the values from a given value store

template <class FieldTypeT, Int32 fieldNameSpace> inline
void MField<FieldTypeT, fieldNameSpace>::setValues(const StorageType &value)
{
    _values = value;
}

//! Copies the values from a given field

template <class FieldTypeT, Int32 fieldNameSpace> inline
void MField<FieldTypeT, fieldNameSpace>::setValues(const Self &obj)
{
    _values = obj._values;
}

/*-------------------------------------------------------------------------*/
/*                                  Add                                    */

//! Append the given value to the store

template <class FieldTypeT, Int32 fieldNameSpace> inline
void MField<FieldTypeT, fieldNameSpace>::addValue(const FieldTypeT &value)
{
    _values.push_back(value);
}

/*-------------------------------------------------------------------------*/
/*                             STL Interface                               */

//! Return an iterator to the first element

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename MField<FieldTypeT, 
                fieldNameSpace>::iterator MField<FieldTypeT, 
                                                 fieldNameSpace>::begin (void)
{
    return _values.begin();
}

//! Return an iterator to the end of the store

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename MField<FieldTypeT, 
                fieldNameSpace>::iterator MField<FieldTypeT, 
                                                 fieldNameSpace>::end(void)
{
    return _values.end();
}

//! Return a const iterator to the first element

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename MField<FieldTypeT, 
                fieldNameSpace>::const_iterator MField<FieldTypeT, 
                                                       fieldNameSpace>::begin(
                                                           void) const
{
    return _values.begin();
}

//! Return a const iterator to the end of the store

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename MField<FieldTypeT, 
                fieldNameSpace>::const_iterator MField<FieldTypeT,
                                                       fieldNameSpace>::end(
                                                           void) const
{
    return _values.end();
}

//! Returns an interator to the first element

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename MField<FieldTypeT, 
                fieldNameSpace>::reference MField<FieldTypeT, 
                                                  fieldNameSpace>::front(void)
{
    return _values.front();
}

//! Returns a const interator to the first element

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename MField<FieldTypeT, 
                fieldNameSpace>::const_reference MField<FieldTypeT, 
                                                        fieldNameSpace>::front(
                                                            void) const
{
    return _values.front();
}

//! Returns an interator to the last element

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename MField<FieldTypeT, 
                fieldNameSpace>::reference MField<FieldTypeT, 
                                                  fieldNameSpace>::back(void)
{
    return _values.back();
}

//! Returns a const interator to the last element

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename MField<FieldTypeT, 
                fieldNameSpace>::const_reference MField<FieldTypeT, 
                                                        fieldNameSpace>::back(
                                                            void) const
{
    return _values.back();
}

//! Clears the value store

template <class FieldTypeT, Int32 fieldNameSpace> inline
void MField<FieldTypeT, fieldNameSpace>::clear(void)
{
    _values.clear();
}

//! Inserts value at the given pos

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename MField<FieldTypeT, 
                fieldNameSpace>::iterator MField<FieldTypeT, 
                                                 fieldNameSpace>::insert(
    iterator pos, const FieldTypeT &value)
{
    return _values.insert(pos, value);
}

//! Removes values from the given pos

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename MField<FieldTypeT, 
                fieldNameSpace>::iterator MField<FieldTypeT, 
                                                 fieldNameSpace>::erase(
                                                     iterator pos)
{
    return _values.erase(pos);
}


//! Returns an iterator to the given value if found otherwise end()

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename MField<FieldTypeT, 
                fieldNameSpace>::iterator MField<FieldTypeT, 
                                                 fieldNameSpace>::find(
    const FieldTypeT &value)
{
    return STD::find(_values.begin(), _values.end(), value);
}

//! Returns a const iterator to the given value if found otherwise end()

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename MField<FieldTypeT, 
                fieldNameSpace>::const_iterator MField<FieldTypeT, 
                                                       fieldNameSpace>::find(
    const FieldTypeT &value) const
{
    return STD::find(_values.begin(), _values.end(), value);
}

//! push back value

template <class FieldTypeT, Int32 fieldNameSpace> inline
void MField<FieldTypeT, fieldNameSpace>::push_back(const FieldTypeT &value)
{
    _values.push_back(value);
}

/*! \brief resizes the container to given size. Depends on the underlying
    stll container implementation
*/

template <class FieldTypeT, Int32 fieldNameSpace> inline
void MField<FieldTypeT, fieldNameSpace>::resize(size_t newsize)
{
    _values.resize(newsize);
}

/*! \brief allocates memory for the given number of elements. 
    Depends on the underlying stl container implementation
*/

template <class FieldTypeT, Int32 fieldNameSpace> inline
void MField<FieldTypeT, fieldNameSpace>::reserve(size_t newsize)
{
    _values.reserve(newsize);
}

//! Returns the size of the field

template <class FieldTypeT, Int32 fieldNameSpace> inline
UInt32 MField<FieldTypeT, fieldNameSpace>::size(void) const
{
    return _values.size();
}

//! Returns the size of the field, depreciated

template <class FieldTypeT, Int32 fieldNameSpace> inline
UInt32 MField<FieldTypeT, fieldNameSpace>::getSize(void) const
{
    return _values.size();
}

//! Returns true if the field does not hold any value

template <class FieldTypeT, Int32 fieldNameSpace> inline
bool MField<FieldTypeT, fieldNameSpace>::empty(void) const
{
    return _values.empty();
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
void MField<FieldTypeT, fieldNameSpace>::operator =(const MField &source)
{
    if(this == &source)
       return;

    _values = source._values;
}

/*-------------------------------------------------------------------------*/
/*                           String IO                                     */


//! Sets the field value from a given string

template <class FieldTypeT, Int32 fieldNameSpace> inline
void MField<FieldTypeT, fieldNameSpace>::pushValueByStr(const Char8 *str)
{
    FieldTypeT  tmpVal;

    typedef typename osgIF< (MFieldTraits::StringConvertable &
                             Traits::FromStringConvertable), 
                            MFieldTraits, 
                            ErrorFromToString<FieldTypeT> >::_IRet Converter;
    
    Converter::getFromString(tmpVal, str);
    
    addValue(tmpVal);
}

//! Dump the field to a given string

template <class FieldTypeT, Int32 fieldNameSpace> inline
string &MField<FieldTypeT, 
               fieldNameSpace>::getValueByStr(string &str) const
{
    string tmpString;

    typedef typename osgIF< (MFieldTraits::StringConvertable &
                             Traits::FromStringConvertable),
                            MFieldTraits,
                            ErrorFromToString<FieldTypeT> >::_IRet Converter;

    for(UInt32 i = 0; i < getSize(); ++i)
    {
        Converter::putToString(_values[i], tmpString);

        str.append(tmpString);

        if(i < (getSize()-1))
        {
            str.append(", ");
        }
    }

    return str;
}


template <class FieldTypeT, Int32 fieldNameSpace> inline
string &MField<FieldTypeT, 
               fieldNameSpace>::getValueByStr(string                   &outStr,
                                              StringConversionStateBase &state)
                                                                          const
{
    string valStr;

    typedef typename osgIF< (MFieldTraits::StringConvertable &
                             Traits::FromStringConvertable),
                            MFieldTraits,
                            ErrorFromToString<FieldTypeT> >::_IRet Converter;

    state.beginField(this, outStr);

    for(UInt32 i = 0; i < getSize(); ++i)
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

//! Returns a reference to the value at the given index 

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename MField<FieldTypeT, fieldNameSpace>::reference
    MField<FieldTypeT, fieldNameSpace>::operator [](UInt32 index)
{
    return _values[index];
}

//! Returns a const reference to the value at the given index 

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename MField<FieldTypeT, fieldNameSpace>::const_reference
    MField<FieldTypeT, fieldNameSpace>::operator [](UInt32 index) const
{
    return _values[index];
}

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

    pMem.put(&n, sizeof(n));
    MFieldTraits::copyToBin(   pMem, 
                            &(_values[0]),
                              _values.size());
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
void MField<FieldTypeT, fieldNameSpace>::copyFromBin(BinaryDataHandler &pMem)
{
    UInt32 n;

     pMem  .get   (&n, sizeof(UInt32));
    _values.clear ( );
    _values.resize(n);

    MFieldTraits::copyFromBin(   pMem, 
                              &(_values[0]),
                                 n);
}

/*-------------------------------------------------------------------------*/
/*                               Dump                                      */

/*! \brief Dump property contents to stderr, should be changed to use a
    log stream instead
*/

template <class FieldTypeT, Int32 fieldNameSpace> inline
void MField<FieldTypeT, fieldNameSpace>::dump(void) const
{
    cout << "STMFST : " << endl;

    for(UInt32 i = 0; i < _values.size(); i++)
    {
//        cout << _values[i] << " , ";
    }

    cout << endl;
}

/*-------------------------------------------------------------------------*/
/*                             Create                                      */

//! Create method used by the factory to create an instance

template <class FieldTypeT, Int32 fieldNameSpace> inline
Field *MField<FieldTypeT, fieldNameSpace>::create(void) 
{
    return new MField<FieldTypeT, fieldNameSpace>(); 
}

OSG_END_NAMESPACE

#define OSGMFIELD_INLINE_CVSID "@(#)$Id: $"


