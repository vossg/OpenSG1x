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

/** \fn const char *OSGSimpleAttachment::getClassname(void)
 *  \brief Classname
 */

/** \typedef OSGSimpleAttachment::Inherited
 *  \brief Parent type
 */

/** \typedef OSGSimpleAttachment::_field
 *  \brief Data store
 */

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

template <class GeoPropertyDesc>
char OSGAbstractGeoProperty<GeoPropertyDesc>::cvsid[] = 
    "@(#)$Id: $";

#ifndef __linux
template <class GeoPropertyDesc>
const  OSGAbstractGeoProperty<GeoPropertyDesc>::OSGPtrType
    OSGAbstractGeoProperty<GeoPropertyDesc>::OSGNullPtr;
#endif

#if defined(OSG_MICROSOFT_COMPILER_ALERT)
template <class GeoPropertyDesc>
OSGFieldContainerType OSGAbstractGeoProperty<GeoPropertyDesc>::_type = 
    OSGFieldContainerType(
        GeoPropertyDesc::getTypeName(),
        InheritDesc::getTypeName(),
        GeoPropertyDesc::getGroupName(),
        NULL,
        GeoPropertyDesc::getInitMethod(),
        NULL,
        0);
#else

template <class GeoPropertyDesc>
OSGFieldContainerType OSGAbstractGeoProperty<GeoPropertyDesc>::_type(
        GeoPropertyDesc::getTypeName(),
        InheritDesc::getTypeName(),
        GeoPropertyDesc::getGroupName(),
        NULL,
        GeoPropertyDesc::getInitMethod(),
        NULL,
        0);
#endif

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

OSG_ABSTR_FIELD_CONTAINER_INL_TMPL_DEF(OSGAbstractGeoProperty,
                                       GeoPropertyDesc,
                                       OSGPtrType)


/*------------- constructors & destructors --------------------------------*/

template <class GeoPropertyDesc> inline
OSGAbstractGeoProperty<GeoPropertyDesc>::OSGAbstractGeoProperty(void) :
    Inherited()
{
}


template <class GeoPropertyDesc> inline
OSGAbstractGeoProperty<GeoPropertyDesc>::OSGAbstractGeoProperty(
    const OSGAbstractGeoProperty &source) :
        Inherited(source)
{
}


template <class GeoPropertyDesc> inline
OSGAbstractGeoProperty<GeoPropertyDesc>::~OSGAbstractGeoProperty(void)
{
}


/*--------------------------- type information-----------------------------*/

/*------------------------------ access -----------------------------------*/

/*------------------------------ access -----------------------------------*/

/*------------------------------- size ----------------------------------*/

/*------------------------------- dump ----------------------------------*/

template <class GeoPropertyDesc> inline
void OSGAbstractGeoProperty<GeoPropertyDesc>::dump(void) const
{
    SDEBUG << "Dump OSGAbstractGeoProperty<GeoPropertyDesc> NI" << endl;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/




/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

OSG_FC_FIRST_FIELD_IDM_INL_TMPL_DEF(OSGGeoProperty,
                                    GeoPropertyDesc,
                                    OSGGeoPropDataField)

OSG_FC_LAST_FIELD_IDM_INL_TMPL_DEF(OSGGeoProperty,
                                   GeoPropertyDesc,
                                   OSGGeoPropDataField)

template <class GeoPropertyDesc>
char OSGGeoProperty<GeoPropertyDesc>::cvsid[] = 
    "@(#)$Id: $";


/** \brief NULL pointer
 */


template <class GeoPropertyDesc>
const  OSGGeoProperty<GeoPropertyDesc>::OSGPtrType 
    OSGGeoProperty<GeoPropertyDesc>::OSGNullPtr;


/** \brief Property field description
 */

template <class GeoPropertyDesc>
OSGFieldDescription OSGGeoProperty<GeoPropertyDesc>::_desc[] = 
{
    OSGFieldDescription(
        FieldType::getClassType(), 
        GeoPropertyDesc::getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(OSGGeoPropDataField),
        false,
        (OSGFieldAccessMethod) &OSGGeoProperty::getFieldPtr)
};

/** \brief Attachment type
 */

#if defined(OSG_MICROSOFT_COMPILER_ALERT)
template <class GeoPropertyDesc>
OSGFieldContainerType OSGGeoProperty<GeoPropertyDesc>::_type = 
    OSGFieldContainerType(
        GeoPropertyDesc::getTypeName(),
        InheritDesc::getTypeName(),
        GeoPropertyDesc::getGroupName(),
        (OSGPrototypeCreateF) &OSGGeoProperty<GeoPropertyDesc>::createEmpty,
        GeoPropertyDesc::getInitMethod(),
        _desc,
        sizeof(_desc));
#else
template <class GeoPropertyDesc>
OSGFieldContainerType OSGGeoProperty<GeoPropertyDesc>::_type(
        GeoPropertyDesc::getTypeName(),
        InheritDesc::getTypeName(),
        GeoPropertyDesc::getGroupName(),
        (OSGPrototypeCreateF) &OSGGeoProperty<GeoPropertyDesc>::createEmpty,
        GeoPropertyDesc::getInitMethod(),
        _desc,
        sizeof(OSGFieldDescription));
#endif




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

OSG_FIELD_CONTAINER_INL_TMPL_DEF(OSGGeoProperty,
                                 GeoPropertyDesc,
                                 OSGPtrType)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

template <class GeoPropertyDesc> 
inline OSGGeoProperty<GeoPropertyDesc>::OSGGeoProperty(void) :
    Inherited(),
    _field()
{
}


/** \brief Copy Constructor
 */

template <class GeoPropertyDesc> 
inline OSGGeoProperty<GeoPropertyDesc>::OSGGeoProperty(
    const OSGGeoProperty &source ) :
         Inherited(source),
        _field(source._field)
{
}


/** \brief Destructor
 */

template <class GeoPropertyDesc> 
inline OSGGeoProperty<GeoPropertyDesc>::~OSGGeoProperty(void)
{
}

/*------------------------------ access -----------------------------------*/

/** \brief Returns pointer to stored field
 */

template <class GeoPropertyDesc> 
inline typename GeoPropertyDesc::FieldType * 
    OSGGeoProperty<GeoPropertyDesc>::getFieldPtr(void)
{
    return &_field;
}

/** \brief Returns reference to the stored field
 */

template <class GeoPropertyDesc> 
inline typename GeoPropertyDesc::FieldType & 
    OSGGeoProperty<GeoPropertyDesc>::getField(void)
{
    return _field;
}

/** \brief Returns const reference to the stored field
 */

template <class GeoPropertyDesc> 
inline const typename GeoPropertyDesc::FieldType & 
    OSGGeoProperty<GeoPropertyDesc>::getField(void) const
{
    return _field;
}


/** \brief Returns dimensionality of property
 */

template <class GeoPropertyDesc> 
inline OSGUInt32 OSGGeoProperty<GeoPropertyDesc>::getFormat(void)
{
    return GeoPropertyDesc::getFormat();
}


template <class GeoPropertyDesc> 
inline OSGUInt32 OSGGeoProperty<GeoPropertyDesc>::getFormatSize(void)
{
    return GeoPropertyDesc::getFormatSize();
}


template <class GeoPropertyDesc> 
inline OSGUInt32 OSGGeoProperty<GeoPropertyDesc>::getStride(void)
{
    return GeoPropertyDesc::getStride();
}


template <class GeoPropertyDesc> 
inline OSGUInt32 OSGGeoProperty<GeoPropertyDesc>::getDimension(void)
{
    return GeoPropertyDesc::getDimension();
}

template <class GeoPropertyDesc> 
inline OSGUInt32 OSGGeoProperty<GeoPropertyDesc>::getSize(void)
{
    return _field.size();
}


template <class GeoPropertyDesc> 
inline OSGUInt8 *OSGGeoProperty<GeoPropertyDesc>::getData(void)
{
    return (OSGUInt8 *)_field.begin();
}


/*------------------------------- dump ----------------------------------*/

template <class GeoPropertyDesc> inline
void OSGGeoProperty<GeoPropertyDesc>::dump(void) const
{
    SDEBUG << "Dump OSGGeoProperty<GeoPropertyDesc> NI" << endl;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


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

