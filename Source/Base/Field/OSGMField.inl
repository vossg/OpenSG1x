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
     Inherited   ( ),
    _values      ( ),
    _uiSharedWith(0)
{
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
MField<FieldTypeT, fieldNameSpace>::MField(const MField &obj) :
     Inherited   (obj        ),
    _values      (obj._values),
    _uiSharedWith(          0)
{
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
MField<FieldTypeT, fieldNameSpace>::MField(const UInt32 size) :
     Inherited   ( ),
    _values      ( ),
    _uiSharedWith(0)
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
void MField<FieldTypeT, fieldNameSpace>::setValues(
    const StorageTypeParent &value)
{
    // Hack probably move it to MFieldVector (GV)

    *(static_cast<StorageTypeParent *>(&_values)) = value;
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
                fieldNameSpace>::reverse_iterator 
    MField<FieldTypeT, 
           fieldNameSpace>::rbegin(void)
{
    return _values.rbegin();
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename MField<FieldTypeT, 
                fieldNameSpace>::reverse_iterator 
    MField<FieldTypeT, 
           fieldNameSpace>::rend(void)
{
    return _values.rend();
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
                fieldNameSpace>::const_reverse_iterator 
    MField<FieldTypeT, 
           fieldNameSpace>::rbegin(void) const
{
    return _values.rbegin();
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
typename MField<FieldTypeT, 
                fieldNameSpace>::const_reverse_iterator 
    MField<FieldTypeT, 
           fieldNameSpace>::rend(void) const
{
    return _values.rend();
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
UInt32 MField<FieldTypeT, fieldNameSpace>::capacity(void) const
{
    return _values.capacity();
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
bool MField<FieldTypeT, fieldNameSpace>::empty(void) const
{
    return _values.empty();
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
void MField<FieldTypeT, fieldNameSpace>::swap(MField &right)
{
    _values.swap(right._values);
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
                             FieldTraits ::ToStringConvertable),
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
                             FieldTraits ::ToStringConvertable),
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

template <class FieldTypeT, Int32 fieldNameSpace> inline
std::string &MField<FieldTypeT,
                    fieldNameSpace>::getValueByStr(
                        std::string &str, 
                        UInt32       index) const
{
    if(index >= size())
    {
        return str;
    }

    std::string tmpString;

    typedef typename osgIF< (MFieldTraits::StringConvertable &
                             FieldTraits::ToStringConvertable),
                            MFieldTraits,
                            ErrorFromToString<FieldTypeT> >::_IRet Converter;

    Converter::putToString(_values[index], tmpString);

    str.append(tmpString);

    return str;
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

#ifndef OSG_DISABLE_DEPRECATED
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

template <class FieldTypeT, Int32 fieldNameSpace> inline
UInt32 MField<FieldTypeT, fieldNameSpace>::getSize(void) const
{
    return size();
}

/*-------------------------------------------------------------------------*/
/*                              MT Sync                                    */

#if !defined(OSG_FIXED_MFIELDSYNC)
template <class FieldTypeT, Int32 fieldNameSpace> inline
void MField<FieldTypeT, fieldNameSpace>::syncWith(Self &source)
{
    setValues(source);
}
#else
template <class ValueT, Int32 iNamespace> inline
void MField<ValueT, iNamespace>::syncWith(      Self      &source,
                                          const SyncInfo  &sInfo )

/*
                                          BitVector  syncMode,
                                          UInt32     uiSyncInfo,
                                          UInt32     uiCopyOffset)
 */
{
    if(sInfo.syncMode != 0x0000)
    {
        setValues  (source);
    }
    else
    {
        UInt32 uiFromAspect  = (sInfo.uiSyncInfo & 0xFF000000) >> 24;
        UInt32 uiToAspect    = (sInfo.uiSyncInfo & 0x00FF0000) >> 16;

        bool   bTargetDelete = true;

        if(_uiSharedWith != 0x0000)
        {
            bTargetDelete = false;

            resolveShare(uiToAspect, sInfo.uiCopyOffset);
        }

        Char8  *pOtherMem = reinterpret_cast<Char8 *>(this);
        Self   *pOther    = NULL;
        UInt32  uiShared  = source._uiSharedWith;
        UInt32  uiCheck   = 1;

        pOtherMem -= uiToAspect * sInfo.uiCopyOffset;

        for(UInt32 i = 0; i < 32; ++i)
        {
            if(0x0000 != (uiShared & uiCheck))
            {
                pOther = 
                    reinterpret_cast<Self *>(
                        pOtherMem + (i * sInfo.uiCopyOffset));

                pOther->_uiSharedWith |= (1 << uiToAspect);

                uiShared &= ~uiCheck;
            }

            if(0x0000 == uiShared)
            {
                break;
            }

            uiCheck <<= 1;
        }
        
        _uiSharedWith        |= source._uiSharedWith;
        _uiSharedWith        |= (1 << uiFromAspect);

        source._uiSharedWith |= (1 << uiToAspect  );

        _values.shareValues(source._values, bTargetDelete);
    }
}

template <class ValueT, Int32 iNamespace> inline
void MField<ValueT, iNamespace>::beginEdit(UInt32 uiAspect,
                                           UInt32 uiCopyOffset)
{
    if(_uiSharedWith != 0x0000)
    {
        Self   *pOther = resolveShare(uiAspect, uiCopyOffset);

        _values.resolveShare();

        setValues(*pOther);
    }
}

template <class ValueT, Int32 iNamespace> inline
typename MField<ValueT, 
                iNamespace>::Self *
    MField<ValueT, 
           iNamespace>::resolveShare(UInt32 uiAspect, 
                                     UInt32 uiCopyOffset)
{
    Char8  *pOtherMem = reinterpret_cast<Char8 *>(this);
    Self   *pOther    = NULL;
    UInt32  uiShared  = _uiSharedWith;
    UInt32  uiCheck   = 1;
    UInt32  uiOwn     = 1 << uiAspect;
    
    pOtherMem -= uiAspect * uiCopyOffset;
    
    for(UInt32 i = 0; i < 32; ++i)
    {
        if(0x0000 != (uiShared & uiCheck))
        {
            pOther = 
                reinterpret_cast<Self *>(
                    pOtherMem + (i * uiCopyOffset));
            
            pOther->_uiSharedWith &= ~uiOwn;
            _uiSharedWith         &= ~uiCheck;
            
            uiShared &= ~uiCheck;
        }
        
        if(0x0000 == uiShared)
        {
            break;
        }
        
        uiCheck <<= 1;
    }    

    return pOther;
}

template <class ValueT, Int32 iNamespace> inline
void MField<ValueT, iNamespace>::terminateShare(UInt32 uiAspect, 
                                                UInt32 uiCopyOffset)
{
    if(_uiSharedWith != 0x0000)
    {
        Char8  *pOtherMem = reinterpret_cast<Char8 *>(this);
        Self   *pOther    = NULL;
        UInt32  uiShared  = _uiSharedWith;
        UInt32  uiCheck   = 1 << (uiAspect + 1);
        UInt32  uiOwn     = 1 << uiAspect;

        for(UInt32 i = 1; i < 32; ++i)
        {
            if(0x0000 != (uiShared & uiCheck))
            {
                pOther = 
                    reinterpret_cast<Self *>(
                        pOtherMem + (i * uiCopyOffset));
                
                pOther->_uiSharedWith &= ~uiOwn;
                _uiSharedWith         &= ~uiCheck;

                pOther->_values.resolveShare();

                uiShared &= ~uiCheck;
            }
            
            if(0x0000 == uiShared)
            {
                break;
            }

            uiCheck <<= 1;
        }
    }
}
#endif

/*-------------------------------------------------------------------------*/
/*                         Binary Interface                                */

template <class FieldTypeT, Int32 fieldNameSpace> inline
UInt32 MField<FieldTypeT, fieldNameSpace>::getBinSize(void) const
{
    return sizeof(UInt32) + // num elements
        (_values.size() ? 
            MFieldTraits::getBinSize(&(_values[0]), _values.size()) : 0);
}

template <class FieldTypeT, Int32 fieldNameSpace> inline
void MField<FieldTypeT, 
            fieldNameSpace>::copyToBin(BinaryDataHandler &pMem) const
{
    UInt32 n = _values.size();

    pMem.putValue(n);
    if(n)
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

    if(n)
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


