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

/** \fn const char *OSGSField::getClassname(void)
 *  \brief Classname
 */

/** \typedef OSGSField::Inherited
 *  \brief Parent type
 */

/** \var OSGFieldTypeT OSGSField::_value
 *  \brief Value store
 */


/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

template <class OSGFieldTypeT>
char OSGSField<OSGFieldTypeT>::cvsid[] = "@(#)$Id: $";

/** \brief Field type
 */

#if defined(OSG_MICROSOFT_COMPILER_ALERT)
template <class OSGFieldTypeT>
const OSGFieldType OSGSField<OSGFieldTypeT>::_fieldType = OSGFieldType(
	OSGFieldDataTraits<OSGFieldTypeT>::getSName(), 
	create);
#else
template <class OSGFieldTypeT>
const OSGFieldType OSGSField<OSGFieldTypeT>::_fieldType(
	OSGFieldDataTraits<OSGFieldTypeT>::getSName(), 
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
const OSGFieldType &OSGSField<OSGFieldTypeT>::getClassType(void)
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
OSGField *OSGSField<OSGFieldTypeT>::create(void) 
{
    return new OSGSField<OSGFieldTypeT>(); 
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
OSGSField<OSGFieldTypeT>::OSGSField(void) :
    Inherited(),
    _value()
{
}


/** \brief Constructor from a give value
 */

template <class OSGFieldTypeT> inline
OSGSField<OSGFieldTypeT>::OSGSField(const OSGFieldTypeT &value) :
    Inherited(),
    _value(value)
{
}

/** \brief Constructor from a given field
 */

template <class OSGFieldTypeT> inline
OSGSField<OSGFieldTypeT>::OSGSField(const OSGSField &obj) :
    Inherited(obj),
    _value(obj._value)
{
}

/** \brief Destructor
 */

template <class OSGFieldTypeT> inline
OSGSField<OSGFieldTypeT>::~OSGSField(void)
{
}

/*--------------------------------- access ----------------------------------*/

/** \brief Return a reference to the stored value
 */

template <class OSGFieldTypeT> inline
OSGFieldTypeT &OSGSField<OSGFieldTypeT>::getValue(void)
{
    return _value;
}

/** \brief Return a const reference to the stored value
 */

template <class OSGFieldTypeT> inline
const OSGFieldTypeT &OSGSField<OSGFieldTypeT>::getValue(void) const
{
    return _value;
}

/** \brief Copies the values from a given field iff the two fieldtypes match 
 */

template <class OSGFieldTypeT> inline
void OSGSField<OSGFieldTypeT>::setAbstrValue(const OSGField &obj)
{
    if(getType() == obj.getType())
    {
        setValue(*((OSGSField<OSGFieldTypeT> *) &obj));
    }
}

/** \brief Sets the stored value from a given one
 */

template <class OSGFieldTypeT> inline
void OSGSField<OSGFieldTypeT>::setValue(const OSGFieldTypeT &value)
{
    _value = value;
}

/** \brief Sets the stored value from a given field
 */

template <class OSGFieldTypeT> inline
void OSGSField<OSGFieldTypeT>::setValue(const OSGSField<OSGFieldTypeT> &obj)
{
    _value = obj._value;
}

/*------------------------- field information -------------------------------*/

/** \brief Returns the field cardinality, allways OSGField::SINGLE_FIELD
 */

template <class OSGFieldTypeT> inline
OSGField::Cardinality OSGSField<OSGFieldTypeT>::getCardinality (void) const
{
    return OSGField::SINGLE_FIELD;
}

/** \brief Returns the size of the field, allway 1
 */

template <class OSGFieldTypeT> inline
OSGUInt32 OSGSField<OSGFieldTypeT>::size(void) const
{
    return 1;
}

/*---------------------------- field type -----------------------------------*/

/** \brief Returns the type of the field
 */

template <class OSGFieldTypeT> inline
const OSGFieldType &OSGSField<OSGFieldTypeT>::getType(void) const
{
    return _fieldType;
}

/*----------------------------- string io -----------------------------------*/

/** \brief Sets the field value from a given string
 */

template <class OSGFieldTypeT> inline
void OSGSField<OSGFieldTypeT>::setValueByStr(const char *str)
{
    const char *szTmp = str;

    OSGFieldDataTraits<OSGFieldTypeT>::getFromString(_value, szTmp);
}

/** \brief Dump the field to a given string
 */

template <class OSGFieldTypeT> inline
OSGString &OSGSField<OSGFieldTypeT>::getStrValue(OSGString &string) const
{
    OSGFieldDataTraits<OSGFieldTypeT>::putToString(_value, string);
    
	return string;
}

/*--------------------------------- dump ------------------------------------*/

/** \brief Dump property contents to stderr, should be changed to use a
 *  log stream instead
 */

template <class OSGFieldTypeT> inline
void OSGSField<OSGFieldTypeT>::dump(void) const
{
    cerr << "Dump Field : " << _value << endl;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

template <class OSGFieldTypeT> inline
void OSGSField<OSGFieldTypeT>::doSync(OSGField *source)
{
    setValue(*((OSGSField<OSGFieldTypeT> *) source));
}

template <class OSGFieldTypeT> inline
void OSGSField<OSGFieldTypeT>::beginEdit(void)
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

