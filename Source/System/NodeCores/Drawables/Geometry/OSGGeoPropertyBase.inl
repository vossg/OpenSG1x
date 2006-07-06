/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000-2002 by OpenSG Forum                   *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*------------StoredFieldType---------------------------------------------------------------*\
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

OSG_BEGIN_NAMESPACE

#ifndef WIN32
OSG_ABSTR_FIELD_CONTAINER_INL_TMPL_DEF(AbstractGeoProperty,
                                       GeoPropertyDesc,
                                       PtrType)
#else
OSG_ABSTR_GEO_PROP_INL_TMPL_DEF(AbstractGeoProperty,
                                GeoPropertyDesc,
                                PtrType)
#endif

template <class GeoPropertyDesc> inline
AbstractGeoProperty<GeoPropertyDesc>::AbstractGeoProperty(void) :
      LocalInherited()
#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    , LocalInterface()
#endif
{
}


template <class GeoPropertyDesc> inline
AbstractGeoProperty<GeoPropertyDesc>::AbstractGeoProperty(
    const AbstractGeoProperty &source) :

      LocalInherited(source)
#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    , LocalInterface(source)
#endif
{
}


template <class GeoPropertyDesc> inline
AbstractGeoProperty<GeoPropertyDesc>::~AbstractGeoProperty(void)
{
}

template <class GeoPropertyDesc> inline
void AbstractGeoProperty<GeoPropertyDesc>::dump(      UInt32    uiIndent, 
                                                const BitVector bvFlags) const
{
    LocalInherited::dump(uiIndent, bvFlags);
}

/** \brief Property field description
 */

/** \brief Attachment type
 */

#ifndef WIN32
OSG_FIELD_CONTAINER_INL_TMPL_DEF(GeoProperty,
                                 GeoPropertyDesc,
                                 PtrType)
#else
OSG_GEO_PROP_INL_TMPL_DEF(GeoProperty,
                          GeoPropertyDesc,
                          PtrType)
#endif

#ifdef OSG_MICROSOFT_COMPILER_HACKS
template <class GeoPropertyDesc> inline 
FieldAccessMethod GeoProperty<GeoPropertyDesc>::getFPtrAccessMethod(void)
{
    typedef GeoProperty<GeoPropertyDesc> Self;
    typedef StoredFieldType *(Self::*GetFieldPtr)(void);

    GetFieldPtr       tmp       = &osg::GeoProperty<GeoPropertyDesc>::getFieldPtr;

    FieldAccessMethod tmpMethod = (*((FieldAccessMethod *) &tmp));

    return tmpMethod;
}
#endif

#if defined(__hpux)
template <class GeoPropertyDesc> 
const BitVector GeoProperty<GeoPropertyDesc>::GeoPropDataFieldMask;
#endif

template <class GeoPropertyDesc> inline 
GeoProperty<GeoPropertyDesc>::GeoProperty(void) :
     LocalInherited(),
    _field         ()
{
}

template <class GeoPropertyDesc> inline 
GeoProperty<GeoPropertyDesc>::GeoProperty(
    const GeoProperty &source ) :

     LocalInherited(source),
    _field         (source._field)
{
}

template <class GeoPropertyDesc> inline 
GeoProperty<GeoPropertyDesc>::~GeoProperty(void)
{
}

#if !defined(OSG_FIXED_MFIELDSYNC)
template <class GeoPropertyDesc> inline
void GeoProperty<GeoPropertyDesc>::executeSync(
          FieldContainer &other,
    const BitVector      &whichField)
{
    this->executeSyncImpl((GeoProperty *) &other, whichField);
}

template <class GeoPropertyDesc> inline
void GeoProperty<GeoPropertyDesc>::executeSyncImpl(
          GeoProperty *pOther,
    const BitVector   &whichField)
{
    LocalInherited::executeSyncImpl(pOther, whichField);

    if(FieldBits::NoField != (GeoPropDataFieldMask & whichField))
    {
        _field.syncWith(pOther->_field);
    }
}
#else
template <class GeoPropertyDesc> inline
void GeoProperty<GeoPropertyDesc>::executeSync(
          FieldContainer &other,
    const BitVector      &whichField,
    const SyncInfo       &sInfo     )
{
    this->executeSyncImpl((GeoProperty *) &other, whichField, sInfo);
}

template <class GeoPropertyDesc> inline
void GeoProperty<GeoPropertyDesc>::executeSyncImpl(
          GeoProperty *pOther,
    const BitVector   &whichField,
    const SyncInfo    &sInfo     )
{
    LocalInherited::executeSyncImpl(pOther, whichField, sInfo);

    if(FieldBits::NoField != (GeoPropDataFieldMask & whichField))
    {
        _field.syncWith(pOther->_field, sInfo);
    }
}

template <class GeoPropertyDesc> inline
void GeoProperty<GeoPropertyDesc>::execBeginEditImpl(
    const BitVector &whichField, 
          UInt32     uiAspect,
          UInt32     uiContainerSize)
{
    LocalInherited::execBeginEditImpl(whichField, uiAspect, uiContainerSize);

    if (FieldBits::NoField != (GeoPropDataFieldMask & whichField))
    {
        _field.beginEdit(uiAspect, uiContainerSize);
    }
}

template <class GeoPropertyDesc> inline
void GeoProperty<GeoPropertyDesc>::execBeginEdit(
    const BitVector &whichField, 
          UInt32     uiAspect,
          UInt32     uiContainerSize)
{
    this->execBeginEditImpl(whichField, uiAspect, uiContainerSize);
}

template <class GeoPropertyDesc> inline
void GeoProperty<GeoPropertyDesc>::onDestroyAspect(UInt32 uiId, 
                                                   UInt32 uiAspect)
{
    _field.terminateShare(uiAspect, this->getContainerSize());
}
#endif

template <class GeoPropertyDesc> inline 
void GeoProperty<GeoPropertyDesc>::changed(BitVector whichField, 
                                           UInt32    origin    )
{
    MFFieldContainerPtr::iterator parentsIt  = Self::_parents.begin();
    MFFieldContainerPtr::iterator parentsEnd = Self::_parents.end();

    while(parentsIt != parentsEnd)
    {
        (*parentsIt)->changed(
                TypeTraits<BitVector>::One << parentsIt->getParentFieldPos(),
                ChangedOrigin::Child);
        ++parentsIt;
    }

    LocalInherited::changed(whichField, origin);
}

template <class GeoPropertyDesc> inline 
UInt32 GeoProperty<GeoPropertyDesc>::getBinSize(const BitVector &whichField)
{
    UInt32 returnValue = LocalInherited::getBinSize(whichField);

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
    LocalInherited::copyToBin(pMem, whichField);

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
    LocalInherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (GeoPropDataFieldMask & whichField))
    {
        _field.copyFromBin(pMem);
    }
}

/*! Returns a pointer to the Stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the AbstractGeoProperty provides, but it
    necessitates compile-time knowledge about the involved concrete types.
*/
template <class GeoPropertyDesc> inline 
typename GeoProperty<GeoPropertyDesc>::StoredFieldType * 
    GeoProperty<GeoPropertyDesc>::getFieldPtr(void)
{
    return &_field;
}

/*! Returns a reference to the Stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the AbstractGeoProperty provides, but it
    necessitates compile-time knowledge about the involved concrete types. 
*/
template <class GeoPropertyDesc> inline 
typename GeoProperty<GeoPropertyDesc>::StoredFieldType & 
    GeoProperty<GeoPropertyDesc>::getField(void)
{
    return _field;
}

/*! Returns a const reference to the Stored field. 

    This allows direct access to the data, which is faster than the access via 
    the generic Interface that the AbstractGeoProperty provides, but it
    necessitates compile-time knowledge about the involved concrete types. 
*/
template <class GeoPropertyDesc> inline 
const typename GeoProperty<GeoPropertyDesc>::StoredFieldType & 
    GeoProperty<GeoPropertyDesc>::getField(void) const
{
    return _field;
}

template <class GeoPropertyDesc> inline
typename GeoProperty<GeoPropertyDesc>::LocalInheritedPtr
GeoProperty<GeoPropertyDesc>::clone(void)
{
    PtrType obj = GeoProperty<GeoPropertyDesc>::create();
    
    obj->_field.setValues( _field );
    return obj;
}


/*! Returns the format of this property. 

    
*/

template <class GeoPropertyDesc> inline 
UInt32 GeoProperty<GeoPropertyDesc>::getFormat(void) const
{
    return GeoPropertyDesc::getFormat();
}


template <class GeoPropertyDesc> inline 
UInt32 GeoProperty<GeoPropertyDesc>::getFormatSize(void) const
{
    return GeoPropertyDesc::getFormatSize();
}


template <class GeoPropertyDesc> inline
UInt32 GeoProperty<GeoPropertyDesc>::getStride(void) const
{
    return GeoPropertyDesc::getStride();
}


template <class GeoPropertyDesc> inline
UInt32 GeoProperty<GeoPropertyDesc>::getDimension(void) const
{
    return GeoPropertyDesc::getDimension();
}


template <class GeoPropertyDesc> inline
UInt32 GeoProperty<GeoPropertyDesc>::getSize(void) const
{
    return _field.size();
}


template <class GeoPropertyDesc> inline
UInt32 GeoProperty<GeoPropertyDesc>::size(void) const
{
    return _field.size();
}


template <class GeoPropertyDesc> inline
UInt8 *GeoProperty<GeoPropertyDesc>::getData(void) const
{
    return _field.empty() ? NULL : (UInt8 *) &(_field[0]);
}


template <class GeoPropertyDesc> inline 
typename GeoProperty<GeoPropertyDesc>::StoredGenericType
    GeoProperty<GeoPropertyDesc>::getValue(const UInt32 index)
{
//CHECKCHECK do conversion constructor iff necessary
    return StoredGenericType(_field[index]);
}

template <class GeoPropertyDesc> inline
typename GeoProperty<GeoPropertyDesc>::StoredGenericType
    GeoProperty<GeoPropertyDesc>::getValue(const UInt32 index) const
{
//CHECKCHECK do conversion constructor iff necessary
    return StoredGenericType(_field[index]);
}

template <class GeoPropertyDesc> inline 
void GeoProperty<GeoPropertyDesc>::getValue(      StoredGenericType &val,
                                            const UInt32             index)
{
    new (&val) StoredGenericType(_field[index]);
}


template <class GeoPropertyDesc> inline 
void GeoProperty<GeoPropertyDesc>::getValue(
          StoredGenericType &val,
    const UInt32             index) const
{
    new (&val) StoredGenericType(_field[index]);
}

template <class GeoPropertyDesc> inline 
void GeoProperty<GeoPropertyDesc>::setValue(const StoredGenericType &value,
                                            const UInt32             index)
{
//CHECKCHECK do conversion constructor iff necessary
    _field[index] = StoredType(value);
}

template <class GeoPropertyDesc> inline 
void GeoProperty<GeoPropertyDesc>::addValue(const StoredGenericType & value)
{
//CHECKCHECK do conversion constructor iff necessary
    _field.push_back( StoredType(value) );
}

template <class GeoPropertyDesc> inline
bool GeoProperty<GeoPropertyDesc>::insertValue(const StoredGenericType &val,
                                               const UInt32 index)
{
    if(_field.size() < index)
    {
        return false;
    }
    else if(_field.size() == index)
    {
        addValue(val);
        return true;
    }
    else
    {
        _field.insert(_field.begin() + index, StoredType(val));
        return true;
    }
}

template <class GeoPropertyDesc> inline
void GeoProperty<GeoPropertyDesc>::clear( void )
{
    _field.clear();
}

template <class GeoPropertyDesc> inline
void GeoProperty<GeoPropertyDesc>::push_back(
    const StoredGenericType &value)
{
    addValue(value);
}

template <class GeoPropertyDesc> inline
void GeoProperty<GeoPropertyDesc>::resize( size_t newsize )
{
    _field.resize(newsize);
}

template <class GeoPropertyDesc> inline
void GeoProperty<GeoPropertyDesc>::shrink( void )
{
    StoredFieldType(_field).swap(_field);
}

template <class GeoPropertyDesc> inline
void GeoProperty<GeoPropertyDesc>::dump(      UInt32    uiIndent, 
                                        const BitVector bvFlags) const
{
    LocalInherited::dump(uiIndent, bvFlags);
}

OSG_END_NAMESPACE
