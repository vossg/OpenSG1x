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

#if !defined(__sun) && !defined(WIN32)  && !defined(__linux)

/** \fn const char *OSGMFieldVector::getClassname(void)
 *  \brief Classname
 */

/** \typedef OSGMFieldVector::Inherited
 *  \brief Parent type
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

template<class _Tp, class _Alloc>
char MFieldVector<_Tp, _Alloc>::cvsid[] = "@(#)$Id: $";

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

template<class _Tp, class _Alloc> inline
MFieldVector<_Tp, _Alloc>::MFieldVector(
    const typename Inherited::allocator_type &__a) :

    Inherited(__a)
{
}

/** \brief Creates a vector with n copies of value.
 */

template<class _Tp, class _Alloc> inline
MFieldVector<_Tp, _Alloc>::MFieldVector(
    typename Inherited::size_type  __n, 
    _Tp                            __value,
    const typename Inherited::allocator_type &__a) :

    Inherited(__n, __value, __a)
{
}

/** \brief Creates a vector with n elements.
 */

template<class _Tp, class _Alloc> inline
MFieldVector<_Tp, _Alloc>::MFieldVector(
    typename Inherited::size_type __n) :

    Inherited(__n)
{
}

/** \brief Copy constructor. 
 */

template<class _Tp, class _Alloc> inline
MFieldVector<_Tp, _Alloc>::MFieldVector(const MFieldVector &__x) :
    Inherited(__x)
{
}
    
#ifndef __STL_MEMBER_TEMPLATES

/** \brief Creates a vector with a copy of a range. 
 */

template<class _Tp, class _Alloc> inline
MFieldVector<_Tp, _Alloc>::MFieldVector(
    const _Tp                                *__first,
    const _Tp                                *__last,
    const typename Inherited::allocator_type &__a) :
    
    Inherited(__first, __last, __a)
{
}

#endif /* __STL_MEMBER_TEMPLATES */


/** \brief Destructor
 */

template<class _Tp, class _Alloc> inline
MFieldVector<_Tp, _Alloc>::~MFieldVector()
{
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/** \brief Assignment
 */

template<class _Tp, class _Alloc> inline
MFieldVector<_Tp, _Alloc> &MFieldVector<_Tp, _Alloc>::operator =(
    const MFieldVector<_Tp, _Alloc> &__x)
{
	if (this == &__x)
		return *this;

	// copy parts inherited from parent
	*(static_cast<Inherited *>(this)) = __x;

    return *this;
}
#endif


/** \fn const char *MField::getClassname(void)
 *  \brief Classname
 */

/** \typedef MField::Inherited
 *  \brief Parent type
 */

/** \var FieldTypeT MField::_values
 *  \brief Value store
 */

/** \typedef vector<FieldTypeT> MField::StorageType
 *  \brief Storage type
 */

/** \typedef vector<FieldTypeT>::iterator MField::iterator
 *  \brief Storage iterator
 */

/** \typedef vector<FieldTypeT>::const_iterator MField::const_iterator
 *  \brief Const Storage iterator
 */

/** \typedef vector<FieldTypeT>::reference MField::reference
 *  \brief Value reference
 */

/** \typedef vector<FieldTypeT>::const_reference MField::const_reference
 *  \brief Const value reference
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

template <class FieldTypeT>
char MField<FieldTypeT>::cvsid[] = "@(#)$Id: $";

/** \brief Field type
 */

#if defined(OSG_MICROSOFT_COMPILER_ALERT)
template <class FieldTypeT>
const FieldType MField<FieldTypeT>::_fieldType = FieldType(
	FieldDataTraits<FieldTypeT>::getMName(), 
	create);
#else
template <class FieldTypeT>
const FieldType MField<FieldTypeT>::_fieldType(
	FieldDataTraits<FieldTypeT>::getMName(), 
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

template <class FieldTypeT> inline
const FieldType &MField<FieldTypeT>::getClassType(void)
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

template <class FieldTypeT> inline
Field *MField<FieldTypeT>::create(void) 
{
    return new MField<FieldTypeT>(); 
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

template <class FieldTypeT> inline
MField<FieldTypeT>::MField(void) :
    Inherited(),
    _values()
{
}

/** \brief Constructor, reserves size elements
 */

template <class FieldTypeT> inline
MField<FieldTypeT>::MField(const UInt32 size)
{
    _values.resize(size);
}

/** \brief Constructor from a given field
 */

template <class FieldTypeT> inline
MField<FieldTypeT>::MField(const MField &obj) :
    Inherited(obj),
    _values(obj._values)
{
}

/** \brief Destructor
 */

template <class FieldTypeT> inline
MField<FieldTypeT>::~MField(void)
{
}

/*--------------------------------- access ----------------------------------*/

/** \brief Return a reference to the stored value at index index
 */

template <class FieldTypeT> inline
FieldTypeT &MField<FieldTypeT>::getValue(const UInt32 index)
{
    return _values[index];
}

/** \brief Return a const reference to the stored value at index index
 */

template <class FieldTypeT> inline
const FieldTypeT &MField<FieldTypeT>::getValue(
    const UInt32 index) const
{
    return _values[index];
}

/** \brief Return a reference to the value store 
 */

template <class FieldTypeT> inline
MField<FieldTypeT>::StorageType &MField<FieldTypeT>::getValues(
    void)
{
    return _values;
}

/** \brief Return a const reference to the value store 
 */

template <class FieldTypeT> inline
const MField<FieldTypeT>::StorageType &
    MField<FieldTypeT>::getValues(void) const
{
    return _values;
}

/** \brief Copies the values from a given field iff the two fieldtypes are 
 *  the same.
 */

template <class FieldTypeT> inline
void MField<FieldTypeT>::setAbstrValue(const Field &obj)
{
    if(getType() == obj.getType())
    {
        setValues(*((MField<FieldTypeT> *) &obj));
    }
}

/** \brief Set the value at the given index to values
 */

template <class FieldTypeT> inline
void MField<FieldTypeT>::setValue(const FieldTypeT &value,
                                        const UInt32      index)
{
    _values[index] = value;
}

/** \brief Copies the values from a given value store
 */

template <class FieldTypeT> inline
void MField<FieldTypeT>::setValues(const StorageType &value)
{
    _values = value;
}

/** \brief Copies the values from a given field
 */

template <class FieldTypeT> inline
void MField<FieldTypeT>::setValues(const MField<FieldTypeT> &obj)
{
    _values = obj._values;
}

/*---------------------------- container interface --------------------------*/

/** \brief Append the given value to the store
 */

template <class FieldTypeT> inline
void MField<FieldTypeT>::addValue(const FieldTypeT &value)
{
    _values.push_back(value);
}

/** \brief Return an iterator to the first element
 */

template <class FieldTypeT> inline
MField<FieldTypeT>::iterator MField<FieldTypeT>::begin (void)
{
    return _values.begin();
}

/** \brief Return an iterator to the end of the store
 */

template <class FieldTypeT> inline
MField<FieldTypeT>::iterator MField<FieldTypeT>::end(void)
{
    return _values.end();
}

    
/** \brief Return a const iterator to the first element
 */

template <class FieldTypeT> inline
MField<FieldTypeT>::const_iterator MField<FieldTypeT>::begin(
    void) const
{
    return _values.begin();
}

/** \brief Return a const iterator to the end of the store
 */

template <class FieldTypeT> inline
MField<FieldTypeT>::const_iterator MField<FieldTypeT>::end(
    void) const
{
    return _values.end();
}

/** \brief Returns an interator to the first element
 */

template <class FieldTypeT> inline
MField<FieldTypeT>::reference MField<FieldTypeT>::front(void)
{
    return _values.front();
}

/** \brief Returns a const interator to the first element
 */

template <class FieldTypeT> inline
MField<FieldTypeT>::const_reference MField<FieldTypeT>::front(
    void) const
{
    return _values.front();
}

/** \brief Returns an interator to the last element
 */

template <class FieldTypeT> inline
MField<FieldTypeT>::reference MField<FieldTypeT>::back(void)
{
    return _values.back();
}

/** \brief Returns a const interator to the last element
 */

template <class FieldTypeT> inline
MField<FieldTypeT>::const_reference MField<FieldTypeT>::back(
    void) const
{
    return _values.back();
}

/** \brief Inserts value at the given pos
 */

template <class FieldTypeT> inline
MField<FieldTypeT>::iterator MField<FieldTypeT>::insert(
    iterator pos, const FieldTypeT &value)
{
    return _values.insert(pos, value);
}

/** \brief Removes values from the given pos
 */

template <class FieldTypeT> inline
MField<FieldTypeT>::iterator MField<FieldTypeT>::erase(
    iterator pos)
{
    return _values.erase(pos);
}

/** \brief Clears the value store
 */

template <class FieldTypeT> inline
void MField<FieldTypeT>::clear(void)
{
    _values.clear();
}

/** \brief Returns an iterator to the given value if found otherwise end()
 */

template <class FieldTypeT> inline
MField<FieldTypeT>::iterator MField<FieldTypeT>::find(
    const FieldTypeT &value)
{
    return std::find(_values.begin(), _values.end(), value);
}

/** \brief Returns a const iterator to the given value if found otherwise end()
 */

template <class FieldTypeT> inline
MField<FieldTypeT>::const_iterator MField<FieldTypeT>::find(
    const FieldTypeT &value) const
{
    return std::find(_values.begin(), _values.end(), value);
}

/** \brief resizes the container to given size. Depends on the underlying
 *  stll container implementation
 */

template <class FieldTypeT> inline
void MField<FieldTypeT>::resize(size_t newsize)
{
    _values.resize(newsize);
}

template <class FieldTypeT> inline
void MField<FieldTypeT>::push_back(const FieldTypeT &value)
{
    _values.push_back(value);
}

/** \brief Returns a reference to the value at the given index 
 */

template <class FieldTypeT> inline
FieldTypeT &MField<FieldTypeT>::operator [](UInt32 index)
{
    return _values[index];
}

/** \brief Returns a const reference to the value at the given index 
 */

template <class FieldTypeT> inline
const FieldTypeT &MField<FieldTypeT>::operator [](
    UInt32 index) const
{
    return _values[index];
}

/*-------------------------- field information ------------------------------*/

/** \brief Return the cardinality of the field, allways MULTI_FIELD
 */

template <class FieldTypeT> inline
Field::Cardinality MField<FieldTypeT>::getCardinality (void) const
{
    return MULTI_FIELD;
}

/** \brief Returns the size of the field
 */

template <class FieldTypeT> inline
UInt32 MField<FieldTypeT>::size(void) const
{
    return _values.size();
}

/** \brief Returns the size of the field
 */

template <class FieldTypeT> inline
UInt32 MField<FieldTypeT>::getSize(void) const
{
	return size();
}

/** \brief Returns the type of the field
 */

template <class FieldTypeT> inline
const FieldType &MField<FieldTypeT>::getType(void) const
{
    return _fieldType;
}

/*---------------------------- string io ------------------------------------*/

/** \brief Sets the field value from a given string
 */

template <class FieldTypeT> inline
void MField<FieldTypeT>::pushValueByStr(const Char8 *str)
{
    FieldTypeT  tmpVal;

    typedef osgIF< (FieldDataTraits<FieldTypeT>::StringConvertable &
                    Traits::FromStringConvertable), 
                  FieldDataTraits<FieldTypeT>, 
                  ErrorFromToString<FieldTypeT> >::_IRet Converter;
    
    Converter::getFromString(tmpVal, str);
    
    addValue(tmpVal);
}

/** \brief Dump the field to a given string
 */


template <class FieldTypeT> inline
String &MField<FieldTypeT>::getValueByStr(String &string) const
{
	SWARNING << "getStrValue: not implemented yet!" << endl;

	return string;
}

/*--------------------------------- dump ------------------------------------*/

/** \brief Dump property contents to stderr, should be changed to use a
 *  log stream instead
 */

template <class FieldTypeT> inline
void MField<FieldTypeT>::dump(void) const
{
    cout << "STMFST : " << endl;

    for(UInt32 i = 0; i < _values.size(); i++)
    {
        cout << _values[i] << " , ";
    }

    cout << endl;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

template <class FieldTypeT> inline
void MField<FieldTypeT>::doSync(Field *source)
{
    setValues(*((MField<FieldTypeT> *) source));
}

template <class FieldTypeT> inline
void MField<FieldTypeT>::beginEdit(void)
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

