/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
 *                                                                           *
 *          contact: {reiners|vossg}@igd.fhg.de, jbehr@zgdv.de               *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

#include <OSGThread.h>
#include <OSGChangeList.h>

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
char OSGMFieldVector<_Tp, _Alloc>::cvsid[] = "@(#)$Id: $";

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
OSGMFieldVector<_Tp, _Alloc>::OSGMFieldVector(
    const typename Inherited::allocator_type &__a) :

    Inherited(__a)
{
}

/** \brief Creates a vector with n copies of value.
 */

template<class _Tp, class _Alloc> inline
OSGMFieldVector<_Tp, _Alloc>::OSGMFieldVector(
    typename Inherited::size_type  __n, 
    _Tp                            __value,
    const typename Inherited::allocator_type &__a) :

    Inherited(__n, __value, __a)
{
}

/** \brief Creates a vector with n elements.
 */

template<class _Tp, class _Alloc> inline
OSGMFieldVector<_Tp, _Alloc>::OSGMFieldVector(
    typename Inherited::size_type __n) :

    Inherited(__n)
{
}

/** \brief Copy constructor. 
 */

template<class _Tp, class _Alloc> inline
OSGMFieldVector<_Tp, _Alloc>::OSGMFieldVector(const OSGMFieldVector &__x) :
    Inherited(__x)
{
}
    
#ifndef __STL_MEMBER_TEMPLATES

/** \brief Creates a vector with a copy of a range. 
 */

template<class _Tp, class _Alloc> inline
OSGMFieldVector<_Tp, _Alloc>::OSGMFieldVector(
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
OSGMFieldVector<_Tp, _Alloc>::~OSGMFieldVector()
{
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/** \brief Assignment
 */

template<class _Tp, class _Alloc> inline
OSGMFieldVector<_Tp, _Alloc> &OSGMFieldVector<_Tp, _Alloc>::operator =(
    const OSGMFieldVector<_Tp, _Alloc> &__x)
{
	if (this == &__x)
		return *this;

	// copy parts inherited from parent
	*(static_cast<Inherited *>(this)) = __x;

    return *this;
}
#endif


/** \fn const char *OSGMField::getClassname(void)
 *  \brief Classname
 */

/** \typedef OSGMField::Inherited
 *  \brief Parent type
 */

/** \var OSGFieldTypeT OSGMField::_values
 *  \brief Value store
 */

/** \typedef vector<OSGFieldTypeT> OSGMField::OSGStorageType
 *  \brief Storage type
 */

/** \typedef vector<OSGFieldTypeT>::iterator OSGMField::iterator
 *  \brief Storage iterator
 */

/** \typedef vector<OSGFieldTypeT>::const_iterator OSGMField::const_iterator
 *  \brief Const Storage iterator
 */

/** \typedef vector<OSGFieldTypeT>::reference OSGMField::reference
 *  \brief Value reference
 */

/** \typedef vector<OSGFieldTypeT>::const_reference OSGMField::const_reference
 *  \brief Const value reference
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

template <class OSGFieldTypeT>
char OSGMField<OSGFieldTypeT>::cvsid[] = "@(#)$Id: $";

/** \brief Field type
 */

#if defined(OSG_MICROSOFT_COMPILER_ALERT)
template <class OSGFieldTypeT>
const OSGFieldType OSGMField<OSGFieldTypeT>::_fieldType = OSGFieldType(
	OSGFieldDataTraits<OSGFieldTypeT>::getMName(), 
	create);
#else
template <class OSGFieldTypeT>
const OSGFieldType OSGMField<OSGFieldTypeT>::_fieldType(
	OSGFieldDataTraits<OSGFieldTypeT>::getMName(), 
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

template <class OSGFieldTypeT> inline
const OSGFieldType &OSGMField<OSGFieldTypeT>::getClassType(void)
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

template <class OSGFieldTypeT> inline
OSGField *OSGMField<OSGFieldTypeT>::create(void) 
{
    return new OSGMField<OSGFieldTypeT>(); 
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

template <class OSGFieldTypeT> inline
OSGMField<OSGFieldTypeT>::OSGMField(void) :
    Inherited(),
    _values()
{
}

/** \brief Constructor, reserves size elements
 */

template <class OSGFieldTypeT> inline
OSGMField<OSGFieldTypeT>::OSGMField(const OSGUInt32 size)
{
    _values.resize(size);
}

/** \brief Constructor from a given field
 */

template <class OSGFieldTypeT> inline
OSGMField<OSGFieldTypeT>::OSGMField(const OSGMField &obj) :
    Inherited(obj),
    _values(obj._values)
{
}

/** \brief Destructor
 */

template <class OSGFieldTypeT> inline
OSGMField<OSGFieldTypeT>::~OSGMField(void)
{
}

/*--------------------------------- access ----------------------------------*/

/** \brief Return a reference to the stored value at index index
 */

template <class OSGFieldTypeT> inline
OSGFieldTypeT &OSGMField<OSGFieldTypeT>::getValue(const OSGUInt32 index)
{
    return _values[index];
}

/** \brief Return a const reference to the stored value at index index
 */

template <class OSGFieldTypeT> inline
const OSGFieldTypeT &OSGMField<OSGFieldTypeT>::getValue(
    const OSGUInt32 index) const
{
    return _values[index];
}

/** \brief Return a reference to the value store 
 */

template <class OSGFieldTypeT> inline
OSGMField<OSGFieldTypeT>::OSGStorageType &OSGMField<OSGFieldTypeT>::getValues(
    void)
{
    return _values;
}

/** \brief Return a const reference to the value store 
 */

template <class OSGFieldTypeT> inline
const OSGMField<OSGFieldTypeT>::OSGStorageType &
    OSGMField<OSGFieldTypeT>::getValues(void) const
{
    return _values;
}

/** \brief Copies the values from a given field iff the two fieldtypes are 
 *  the same.
 */

template <class OSGFieldTypeT> inline
void OSGMField<OSGFieldTypeT>::setAbstrValue(const OSGField &obj)
{
    if(getType() == obj.getType())
    {
        setValues(*((OSGMField<OSGFieldTypeT> *) &obj));
    }
}

/** \brief Set the value at the given index to values
 */

template <class OSGFieldTypeT> inline
void OSGMField<OSGFieldTypeT>::setValue(const OSGFieldTypeT &value,
                                        const OSGUInt32      index)
{
    _values[index] = value;
}

/** \brief Copies the values from a given value store
 */

template <class OSGFieldTypeT> inline
void OSGMField<OSGFieldTypeT>::setValues(const OSGStorageType &value)
{
    _values = value;
}

/** \brief Copies the values from a given field
 */

template <class OSGFieldTypeT> inline
void OSGMField<OSGFieldTypeT>::setValues(const OSGMField<OSGFieldTypeT> &obj)
{
    _values = obj._values;
}

/*---------------------------- container interface --------------------------*/

/** \brief Append the given value to the store
 */

template <class OSGFieldTypeT> inline
void OSGMField<OSGFieldTypeT>::addValue(const OSGFieldTypeT &value)
{
    _values.push_back(value);
}

/** \brief Return an iterator to the first element
 */

template <class OSGFieldTypeT> inline
OSGMField<OSGFieldTypeT>::iterator OSGMField<OSGFieldTypeT>::begin (void)
{
    return _values.begin();
}

/** \brief Return an iterator to the end of the store
 */

template <class OSGFieldTypeT> inline
OSGMField<OSGFieldTypeT>::iterator OSGMField<OSGFieldTypeT>::end(void)
{
    return _values.end();
}

    
/** \brief Return a const iterator to the first element
 */

template <class OSGFieldTypeT> inline
OSGMField<OSGFieldTypeT>::const_iterator OSGMField<OSGFieldTypeT>::begin(
    void) const
{
    return _values.begin();
}

/** \brief Return a const iterator to the end of the store
 */

template <class OSGFieldTypeT> inline
OSGMField<OSGFieldTypeT>::const_iterator OSGMField<OSGFieldTypeT>::end(
    void) const
{
    return _values.end();
}

/** \brief Returns an interator to the first element
 */

template <class OSGFieldTypeT> inline
OSGMField<OSGFieldTypeT>::reference OSGMField<OSGFieldTypeT>::front(void)
{
    return _values.front();
}

/** \brief Returns a const interator to the first element
 */

template <class OSGFieldTypeT> inline
OSGMField<OSGFieldTypeT>::const_reference OSGMField<OSGFieldTypeT>::front(
    void) const
{
    return _values.front();
}

/** \brief Returns an interator to the last element
 */

template <class OSGFieldTypeT> inline
OSGMField<OSGFieldTypeT>::reference OSGMField<OSGFieldTypeT>::back(void)
{
    return _values.back();
}

/** \brief Returns a const interator to the last element
 */

template <class OSGFieldTypeT> inline
OSGMField<OSGFieldTypeT>::const_reference OSGMField<OSGFieldTypeT>::back(
    void) const
{
    return _values.back();
}

/** \brief Inserts value at the given pos
 */

template <class OSGFieldTypeT> inline
OSGMField<OSGFieldTypeT>::iterator OSGMField<OSGFieldTypeT>::insert(
    iterator pos, const OSGFieldTypeT &value)
{
    return _values.insert(pos, value);
}

/** \brief Removes values from the given pos
 */

template <class OSGFieldTypeT> inline
OSGMField<OSGFieldTypeT>::iterator OSGMField<OSGFieldTypeT>::erase(
    iterator pos)
{
    return _values.erase(pos);
}

/** \brief Clears the value store
 */

template <class OSGFieldTypeT> inline
void OSGMField<OSGFieldTypeT>::clear(void)
{
    _values.clear();
}

/** \brief Returns an iterator to the given value if found otherwise end()
 */

template <class OSGFieldTypeT> inline
OSGMField<OSGFieldTypeT>::iterator OSGMField<OSGFieldTypeT>::find(
    const OSGFieldTypeT &value)
{
    return std::find(_values.begin(), _values.end(), value);
}

/** \brief Returns a const iterator to the given value if found otherwise end()
 */

template <class OSGFieldTypeT> inline
OSGMField<OSGFieldTypeT>::const_iterator OSGMField<OSGFieldTypeT>::find(
    const OSGFieldTypeT &value) const
{
    return std::find(_values.begin(), _values.end(), value);
}

/** \brief resizes the container to given size. Depends on the underlying
 *  stll container implementation
 */

template <class OSGFieldTypeT> inline
void OSGMField<OSGFieldTypeT>::resize(size_t newsize)
{
    _values.resize(newsize);
}

template <class OSGFieldTypeT> inline
void OSGMField<OSGFieldTypeT>::push_back(const OSGFieldTypeT &value)
{
    _values.push_back(value);
}

/** \brief Returns a reference to the value at the given index 
 */

template <class OSGFieldTypeT> inline
OSGFieldTypeT &OSGMField<OSGFieldTypeT>::operator [](OSGUInt32 index)
{
    return _values[index];
}

/** \brief Returns a const reference to the value at the given index 
 */

template <class OSGFieldTypeT> inline
const OSGFieldTypeT &OSGMField<OSGFieldTypeT>::operator [](
    OSGUInt32 index) const
{
    return _values[index];
}

/*-------------------------- field information ------------------------------*/

/** \brief Return the cardinality of the field, allways OSGField::MULTI_FIELD
 */

template <class OSGFieldTypeT> inline
OSGField::Cardinality OSGMField<OSGFieldTypeT>::getCardinality (void) const
{
    return OSGField::MULTI_FIELD;
}

/** \brief Returns the size of the field
 */

template <class OSGFieldTypeT> inline
OSGUInt32 OSGMField<OSGFieldTypeT>::size(void) const
{
    return _values.size();
}

/** \brief Returns the size of the field
 */

template <class OSGFieldTypeT> inline
OSGUInt32 OSGMField<OSGFieldTypeT>::getSize(void) const
{
	return size();
}

/** \brief Returns the type of the field
 */

template <class OSGFieldTypeT> inline
const OSGFieldType &OSGMField<OSGFieldTypeT>::getType(void) const
{
    return _fieldType;
}

/*---------------------------- string io ------------------------------------*/

/** \brief Sets the field value from a given string
 */

template <class OSGFieldTypeT> inline
void OSGMField<OSGFieldTypeT>::setValueByStr(const char *str)
{
    const char    *szTmp = str;
    OSGFieldTypeT  tmpVal;

    OSGBool bGotValid;

    bGotValid = OSGFieldDataTraits<OSGFieldTypeT>::getFromString(tmpVal, 
                                                                 szTmp);

    while(bGotValid == true)
    {
        
        bGotValid = OSGFieldDataTraits<OSGFieldTypeT>::getFromString(tmpVal, 
                                                                     szTmp);

        addValue(tmpVal);
    }
}

/** \brief Dump the field to a given string
 */


template <class OSGFieldTypeT> inline
OSGString &OSGMField<OSGFieldTypeT>::getStrValue(OSGString &string) const
{
	SWARNING << "getStrValue: not implemented yet!" << endl;

	return string;
}

/*--------------------------------- dump ------------------------------------*/

/** \brief Dump property contents to stderr, should be changed to use a
 *  log stream instead
 */

template <class OSGFieldTypeT> inline
void OSGMField<OSGFieldTypeT>::dump(void) const
{
    cout << "STMFST : " << endl;

    for(OSGUInt32 i = 0; i < _values.size(); i++)
    {
        cout << _values[i] << " , ";
    }

    cout << endl;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

template <class OSGFieldTypeT> inline
void OSGMField<OSGFieldTypeT>::doSync(OSGField *source)
{
    setValues(*((OSGMField<OSGFieldTypeT> *) source));
}

template <class OSGFieldTypeT> inline
void OSGMField<OSGFieldTypeT>::beginEdit(void)
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

