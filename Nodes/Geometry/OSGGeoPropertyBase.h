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


#ifndef _OSGGEOPROPERTYBASE_H_
#define _OSGGEOPROPERTYBASE_H_
#ifdef __sgi
#pragma once
#endif

#include <GL/gl.h>

#include <OSGSystemDef.h>
#include <OSGMFVecTypes.h>
#include <OSGMFSysTypes.h>
#include <OSGMFBaseTypes.h>
#include <OSGAttachment.h>
#include <OSGGeoPropertyInterface.h>

OSG_BEGIN_NAMESPACE

/*! \ingroup GeometryLib
 *  \brief GeoProperty is a specialized form of Attachment, used to
 *  define the properties of the geometry node. This is the abstract base
 *  class for all
 *  properties.
 */

template <class GeoPropertyDesc>
class OSG_SYSTEMLIB_DLLTMPLMAPPING AbstractGeoProperty :
    public GeoPropertyDesc::Inherited
#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    , public GeoPropertyDesc::Interface
#endif
{
    /*==========================  PUBLIC  =================================*/
  public:

    typedef AbstractGeoProperty<GeoPropertyDesc>          PropertyType;

    typedef FCPtr<typename GeoPropertyDesc::InheritedPtr,
                           PropertyType                 > PtrType;

    OSG_ABSTR_FIELD_CONTAINER_TMPL_DECL(PtrType)

    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    virtual PtrType clone(void) = 0;

    /*! \}                                                                 */
#ifdef OSG_SUPPORT_NO_GEO_INTERFACE
    /*---------------------------------------------------------------------*/
    /*! \name              Temp Interface Stuff                            */
    /*! \{                                                                 */

    typedef typename GeoPropertyDesc::GenericType          GenericType;

    virtual UInt32  getFormat    (void) = 0;
    virtual UInt32  getFormatSize(void) = 0;
    virtual UInt32  getStride    (void) = 0;
    virtual UInt32  getDimension (void) = 0;
    virtual UInt32  getSize      (void) = 0;
    virtual UInt8  *getData      (void) = 0;

    virtual GenericType getValue (const UInt32       index )       = 0;

    virtual GenericType getValue (const UInt32       index ) const = 0;

    virtual void        getValue (      GenericType &val,
                                  const UInt32       index )       = 0;

    virtual void        getValue (      GenericType &val,
                                  const UInt32       index ) const = 0;


    virtual void        setValue (const GenericType &val,
                                  const UInt32       index )       = 0;

    virtual void        addValue (const GenericType &val   )       = 0;


    virtual void        clear    (      void               )       = 0;
    virtual void        resize   (      size_t      newsize)       = 0;
    virtual void        push_back(const GenericType &val   )       = 0;

    /*! \}                                                                 */
#endif
    /*---------------------------------------------------------------------*/
    /*! \name                         Dump                                 */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    friend class OSG_SYSTEMLIB_DLLMAPPING FieldContainer;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    AbstractGeoProperty(void);
    AbstractGeoProperty(const AbstractGeoProperty &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AbstractGeoProperty(void);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:       

#ifdef OSG_MICROSOFT_COMPILER_HACKS
    typedef typename GeoPropertyDesc::Inherited            LocalInherited;
    typedef typename GeoPropertyDesc::InheritedDesc        LocalInheritedDesc;

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef          GeoPropertyInterface<GeoPropertyDesc> LocalInterface;
#endif
#else
    typedef typename GeoPropertyDesc::Inherited            Inherited;
    typedef typename GeoPropertyDesc::InheritedDesc        InheritedDesc;

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef          GeoPropertyInterface<GeoPropertyDesc> Interface;
#endif
#endif

    static FieldContainerType _type;
};

template <class GeoPropertyDesc>
class OSG_SYSTEMLIB_DLLMAPPING GeoProperty :
    public GeoPropertyDesc::Inherited
{
    /*==========================  PRIVATE  ================================*/
  private:

#ifdef OSG_MICROSOFT_COMPILER_HACKS
    typedef typename GeoPropertyDesc::Inherited     LocalInherited;
    typedef typename GeoPropertyDesc::InheritedDesc LocalInheritedDesc;
    typedef typename GeoPropertyDesc::InheritedPtr  LocalInheritedPtr;
#else
    typedef typename GeoPropertyDesc::Inherited     Inherited;
    typedef typename GeoPropertyDesc::InheritedDesc InheritedDesc;
    typedef typename GeoPropertyDesc::InheritedPtr  InheritedPtr;
#endif

    /*==========================  PUBLIC  =================================*/
  public:

    enum
    {
#ifdef OSG_MICROSOFT_COMPILER_HACKS
        GeoPropDataFieldId = LocalInherited::NextFieldId,
#else
        GeoPropDataFieldId = Inherited::NextFieldId,
#endif
        NextFieldId        = GeoPropDataFieldId + 1
    };

    static const BitVector GeoPropDataFieldMask;

    typedef GeoProperty<GeoPropertyDesc>                  PropertyType;

#ifdef OSG_MICROSOFT_COMPILER_HACKS
    typedef FCPtr<typename LocalInheritedPtr,
                           PropertyType                 > PtrType;
#else
    typedef FCPtr<typename InheritedPtr,
                           PropertyType                 > PtrType;
#endif

    typedef typename GeoPropertyDesc::StoredFieldType     StoredFieldType;
    typedef typename GeoPropertyDesc::GenericType         StoredGenericType;

    OSG_FIELD_CONTAINER_TMPL_DECL(PtrType)

    /*---------------------------------------------------------------------*/
    /*! \name                      Access                                  */
    /*! \{                                                                 */

          StoredFieldType *getFieldPtr(void);

          StoredFieldType &getField(void);
    const StoredFieldType &getField(void) const;


#ifdef OSG_MICROSOFT_COMPILER_HACKS
    virtual LocalInheritedPtr clone(void);
#else
    virtual InheritedPtr clone(void);
#endif

    virtual UInt32  getFormat    (void);
    virtual UInt32  getFormatSize(void);
    virtual UInt32  getStride    (void);
    virtual UInt32  getDimension (void);
    virtual UInt32  getSize      (void);
    virtual UInt8  *getData      (void);

    typename StoredFieldType &operator->() { return _field; }

    virtual StoredGenericType getValue(const UInt32 index);

    virtual StoredGenericType getValue(const UInt32 index) const;

    virtual void              getValue(      StoredGenericType &val,
                                       const UInt32             index);

    virtual void              getValue(      StoredGenericType &val,
                                       const UInt32             index) const;

    virtual void              setValue(const StoredGenericType &val,
                                       const UInt32             index);

    virtual void              addValue(const StoredGenericType &val);

    virtual void    clear();

    virtual void    resize(size_t newsize);

    virtual void    push_back(const StoredGenericType &val);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Assigment                               */
    /*! \{                                                                 */

    GeoProperty &operator =(const GeoProperty &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Output                                  */
    /*! \{                                                                 */

    virtual void dump(      UInt32    uiIndent = 0,
                      const BitVector bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/    
  protected:

    friend class OSG_SYSTEMLIB_DLLMAPPING FieldContainer;

    typename StoredFieldType _field;

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    GeoProperty(void);
    GeoProperty(const GeoProperty &source);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */
    
    virtual ~GeoProperty(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */
    
    virtual void executeSync    (      FieldContainer &other,
                                 const BitVector      &whichField);

            void executeSyncImpl(      GeoProperty *pOther,
                                 const BitVector   &whichField);
            
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Binary Operations                       */
    /*! \{                                                                 */

    virtual UInt32       getBinSize (const BitVector    &whichField);
    virtual void copyToBin  (      BinaryDataHandler &pMem,
                             const BitVector         &whichField);
    virtual void copyFromBin(      BinaryDataHandler &pMem,
                             const BitVector         &whichField);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    static const PtrType NullPtr;

    static FieldContainerType  _type;
};

typedef AbstractGeoProperty<GeoPositionsPropertyDesc> GeoPositions;

#ifndef OSG_COMPILEGEOPROPINST
#if defined(__sgi)

#pragma do_not_instantiate AbstractGeoProperty<GeoPositionsPropertyDesc>::_type

#else

OSG_ABSTR_FC_DLLEXPORT_DECL(AbstractGeoProperty,
                            GeoPositionsPropertyDesc,
                            OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

typedef AbstractGeoProperty<GeoNormalsPropertyDesc> GeoNormals;

#ifndef OSG_COMPILEGEOPROPINST
#if defined(__sgi)

#pragma do_not_instantiate AbstractGeoProperty<GeoNormalsPropertyDesc>::_type

#else

OSG_ABSTR_FC_DLLEXPORT_DECL(AbstractGeoProperty,
                            GeoNormalsPropertyDesc,
                            OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

typedef AbstractGeoProperty<GeoColorsPropertyDesc> GeoColors;

#ifndef OSG_COMPILEGEOPROPINST
#if defined(__sgi)

#pragma do_not_instantiate AbstractGeoProperty<GeoColorsPropertyDesc>::_type

#else

OSG_ABSTR_FC_DLLEXPORT_DECL(AbstractGeoProperty,
                            GeoColorsPropertyDesc,
                            OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

typedef AbstractGeoProperty<GeoTexCoordsPropertyDesc> GeoTexCoords;

#ifndef OSG_COMPILEGEOPROPINST
#if defined(__sgi)

#pragma do_not_instantiate AbstractGeoProperty<GeoTexCoordsPropertyDesc>::_type

#else

OSG_ABSTR_FC_DLLEXPORT_DECL(AbstractGeoProperty,
                            GeoTexCoordsPropertyDesc,
                            OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

typedef AbstractGeoProperty<GeoIndicesPropertyDesc> GeoIndices;

#ifndef OSG_COMPILEGEOPROPINST
#if defined(__sgi)

#pragma do_not_instantiate AbstractGeoProperty<GeoIndicesPropertyDesc>::_type

#else

OSG_ABSTR_FC_DLLEXPORT_DECL(AbstractGeoProperty,
                            GeoIndicesPropertyDesc,
                            OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

typedef AbstractGeoProperty<GeoPTypesPropertyDesc> GeoPTypes;

#ifndef OSG_COMPILEGEOPROPINST
#if defined(__sgi)

#pragma do_not_instantiate AbstractGeoProperty<GeoPTypesPropertyDesc>::_type

#else

OSG_ABSTR_FC_DLLEXPORT_DECL(AbstractGeoProperty,
                            GeoPTypesPropertyDesc,
                            OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

typedef AbstractGeoProperty<GeoPLengthsPropertyDesc> GeoPLengths;

#ifndef OSG_COMPILEGEOPROPINST
#if defined(__sgi)

#pragma do_not_instantiate AbstractGeoProperty<GeoPLengthsPropertyDesc>::_type

#else

OSG_ABSTR_FC_DLLEXPORT_DECL(AbstractGeoProperty,
                            GeoPLengthsPropertyDesc,
                            OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif

OSG_END_NAMESPACE

#include <OSGGeoPropertyBase.inl>


#endif /* _OSGGEOPROPERTYBASE_H_ */

