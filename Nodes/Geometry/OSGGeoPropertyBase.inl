/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000,2001 by OpenSG Forum                   *
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
#include "OSGGeoPropInterfaceFields.h"

OSG_BEGIN_NAMESPACE

template <class GeoPropertyDesc>
char AbstractGeoProperty<GeoPropertyDesc>::cvsid[] = 
    "@(#)$Id: $";

template <class GeoPropertyDesc>
const  AbstractGeoProperty<GeoPropertyDesc>::PtrType
    AbstractGeoProperty<GeoPropertyDesc>::NullPtr;

#if defined(OSG_MICROSOFT_COMPILER_ALERT)
template <class GeoPropertyDesc>
FieldContainerType AbstractGeoProperty<GeoPropertyDesc>::_type = 
    FieldContainerType(
        GeoPropertyDesc::getTypeName(),
        InheritDesc::getTypeName(),
        GeoPropertyDesc::getGroupName(),
        NULL,
        GeoPropertyDesc::getInitMethod(),
        NULL,
        0);
#else
template <class GeoPropertyDesc>
FieldContainerType AbstractGeoProperty<GeoPropertyDesc>::_type(
        GeoPropertyDesc::getTypeName(),
        InheritDesc::getTypeName(),
        GeoPropertyDesc::getGroupName(),
        NULL,
        GeoPropertyDesc::getInitMethod(),
        NULL,
        0);
#endif


OSG_ABSTR_FIELD_CONTAINER_INL_TMPL_DEF(AbstractGeoProperty,
                                       GeoPropertyDesc,
                                       PtrType)


template <class GeoPropertyDesc> inline
AbstractGeoProperty<GeoPropertyDesc>::AbstractGeoProperty(void) :
    Inherited()
{
}


template <class GeoPropertyDesc> inline
AbstractGeoProperty<GeoPropertyDesc>::AbstractGeoProperty(
    const AbstractGeoProperty &source) :
        Inherited(source)
{
}


template <class GeoPropertyDesc> inline
AbstractGeoProperty<GeoPropertyDesc>::~AbstractGeoProperty(void)
{
}

template <class GeoPropertyDesc> inline
void AbstractGeoProperty<GeoPropertyDesc>::dump(      UInt32     uiIndent, 
                                                const BitVector &bvFlags) const
{
    Inherited::dump(uiIndent, bvFlags);
}

template <class GeoPropertyDesc>
char GeoProperty<GeoPropertyDesc>::cvsid[] = 
    "@(#)$Id: $";

template <class GeoPropertyDesc>
const BitVector GeoProperty<GeoPropertyDesc>::GeoPropDataFieldMask = 
    (1 << GeoProperty<GeoPropertyDesc>::GeoPropDataFieldId);

/** \brief NULL pointer
 */


template <class GeoPropertyDesc>
const  GeoProperty<GeoPropertyDesc>::PtrType 
    GeoProperty<GeoPropertyDesc>::NullPtr;


/** \brief Property field description
 */

template <class GeoPropertyDesc>
FieldDescription *GeoProperty<GeoPropertyDesc>::_desc[] = 
{
    new FieldDescription(
        StoredFieldType::getClassType(), 
        GeoPropertyDesc::getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(GeoPropDataField),
        false,
        (FieldAccessMethod) &GeoProperty::getFieldPtr)
};

/** \brief Attachment type
 */

#if defined(OSG_MICROSOFT_COMPILER_ALERT)
template <class GeoPropertyDesc>
FieldContainerType GeoProperty<GeoPropertyDesc>::_type = 
    FieldContainerType(
        GeoPropertyDesc::getTypeName(),
        InheritDesc::getTypeName(),
        GeoPropertyDesc::getGroupName(),
        (PrototypeCreateF) &GeoProperty<GeoPropertyDesc>::createEmpty,
        GeoPropertyDesc::getInitMethod(),
        _desc,
        sizeof(_desc));
#else
template <class GeoPropertyDesc>
FieldContainerType GeoProperty<GeoPropertyDesc>::_type(
        GeoPropertyDesc::getTypeName(),
        InheritDesc::getTypeName(),
        GeoPropertyDesc::getGroupName(),
        (PrototypeCreateF) &GeoProperty<GeoPropertyDesc>::createEmpty,
        GeoPropertyDesc::getInitMethod(),
        _desc,
        sizeof(FieldDescription *));
#endif


OSG_FIELD_CONTAINER_INL_TMPL_DEF(GeoProperty,
                                 GeoPropertyDesc,
                                 PtrType)

/** \brief Constructor
 */

template <class GeoPropertyDesc> 
inline GeoProperty<GeoPropertyDesc>::GeoProperty(void) :
    Inherited(),
    _field()
{
}


/** \brief Copy Constructor
 */

template <class GeoPropertyDesc> 
inline GeoProperty<GeoPropertyDesc>::GeoProperty(
    const GeoProperty &source ) :
         Inherited(source),
        _field(source._field)
{
}


/** \brief Destructor
 */

template <class GeoPropertyDesc> 
inline GeoProperty<GeoPropertyDesc>::~GeoProperty(void)
{
}

template <class GeoPropertyDesc> 
void GeoProperty<GeoPropertyDesc>::executeSync(
          FieldContainer &other,
    const BitVector      &whichField)
{
    this->executeSyncImpl((GeoProperty *) &other, whichField);
}

template <class GeoPropertyDesc> 
void GeoProperty<GeoPropertyDesc>::executeSyncImpl(
          GeoProperty *pOther,
    const BitVector   &whichField)
{
    Inherited::executeSyncImpl(pOther, whichField);

    if(FieldBits::NoField != (GeoPropDataFieldMask & whichField))
    {
        _field.syncWith(pOther->_field);
    }
}

template <class GeoPropertyDesc> inline 
UInt32 GeoProperty<GeoPropertyDesc>::getBinSize(const BitVector &whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (GeoPropDataFieldMask & whichField))
    {
        returnValue += _field.getBinSize();
    }

    return returnValue;
}

template <class GeoPropertyDesc> inline 
void GeoProperty<GeoPropertyDesc>::copyToBin(
          BinaryDataHandler &pMem,
    const BitVector         &whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (GeoPropDataFieldMask & whichField))
    {
        _field.copyToBin(pMem);
    }
}

template <class GeoPropertyDesc> inline 
void GeoProperty<GeoPropertyDesc>::copyFromBin(
          BinaryDataHandler &pMem,
    const BitVector         &whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (GeoPropDataFieldMask & whichField))
    {
        _field.copyFromBin(pMem);
    }
}

/** \brief Returns pointer to stored field
 */

template <class GeoPropertyDesc> inline 
GeoProperty<GeoPropertyDesc>::StoredFieldType * 
    GeoProperty<GeoPropertyDesc>::getFieldPtr(void)
{
    return &_field;
}

/** \brief Returns reference to the stored field
 */

template <class GeoPropertyDesc> inline 
GeoProperty<GeoPropertyDesc>::StoredFieldType & 
    GeoProperty<GeoPropertyDesc>::getField(void)
{
    return _field;
}

/** \brief Returns const reference to the stored field
 */

template <class GeoPropertyDesc> inline 
const GeoProperty<GeoPropertyDesc>::StoredFieldType & 
    GeoProperty<GeoPropertyDesc>::getField(void) const
{
    return _field;
}


/** \brief Clone this Property
 */

template <class GeoPropertyDesc> 
typename GeoPropertyDesc::InheritPtr
GeoProperty<GeoPropertyDesc>::clone(void)
{
    PtrType obj = GeoProperty<GeoPropertyDesc>::create();
    
    obj->_field.setValues( _field );
    return obj;
}


/** \brief Returns dimensionality of property
 */

template <class GeoPropertyDesc> inline 
UInt32 GeoProperty<GeoPropertyDesc>::getFormat(void)
{
    return GeoPropertyDesc::getFormat();
}


template <class GeoPropertyDesc> inline 
UInt32 GeoProperty<GeoPropertyDesc>::getFormatSize(void)
{
    return GeoPropertyDesc::getFormatSize();
}


template <class GeoPropertyDesc> 
inline UInt32 GeoProperty<GeoPropertyDesc>::getStride(void)
{
    return GeoPropertyDesc::getStride();
}


template <class GeoPropertyDesc> 
inline UInt32 GeoProperty<GeoPropertyDesc>::getDimension(void)
{
    return GeoPropertyDesc::getDimension();
}

template <class GeoPropertyDesc> 
inline UInt32 GeoProperty<GeoPropertyDesc>::getSize(void)
{
    return _field.size();
}


template <class GeoPropertyDesc> 
inline UInt8 *GeoProperty<GeoPropertyDesc>::getData(void)
{
    return (UInt8 *) &(_field[0]);
}

template <class propertyDesc> inline 
GeoProperty<propertyDesc>::StoredGenericType
    GeoProperty<propertyDesc>::getValue(const UInt32 index)
{
	return _field.getValue( index );
}

template <class propertyDesc> inline 
GeoProperty<propertyDesc>::StoredGenericType
    GeoProperty<propertyDesc>::getValue(const UInt32 index) const
{
	return _field.getValue( index );
}

template <class propertyDesc> inline 
void GeoProperty<propertyDesc>::getValue(      StoredGenericType &val,
                                         const UInt32             index)
{
	val = _field.getValue( index );
}


template <class propertyDesc> inline 
void GeoProperty<propertyDesc>::getValue(      StoredGenericType &val,
                                         const UInt32             index) const
{
	val = _field.getValue( index );
}

template <class propertyDesc> inline 
void GeoProperty<propertyDesc>::setValue(const StoredGenericType &value,
                                         const UInt32             index)
{
	_field.setValue( value, index );
}

template <class propertyDesc> inline 
void GeoProperty<propertyDesc>::addValue(const StoredGenericType & value)
{
	_field.addValue( value );
}

template <class propertyDesc> 
inline void GeoProperty<propertyDesc>::clear( void )
{
	_field.clear();
}

template <class propertyDesc> 
inline void GeoProperty<propertyDesc>::push_back(const StoredGenericType &value)
{
	addValue( value );
}

template <class propertyDesc> 
inline void GeoProperty<propertyDesc>::resize( size_t newsize )
{
	_field.resize( newsize );
}

template <class GeoPropertyDesc> inline
void GeoProperty<GeoPropertyDesc>::dump(      UInt32     uiIndent, 
                                        const BitVector &bvFlags) const
{
    Inherited::dump(uiIndent, bvFlags);
}

OSG_END_NAMESPACE
