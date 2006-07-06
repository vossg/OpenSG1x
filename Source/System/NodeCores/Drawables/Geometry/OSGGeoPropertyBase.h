/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000-2002 by OpenSG Forum                   *
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

#include <OSGGL.h>

#include <OSGSystemDef.h>
#include <OSGMFVecTypes.h>
#include <OSGMFSysTypes.h>
#include <OSGMFBaseTypes.h>
#include <OSGAttachment.h>
#include <OSGGeoPropertyInterface.h>

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpSystemDrawablesGeometryProperties
    \brief AbstractGeoProperty is a specialized form of Attachment, used to
    define the properties of the geometry node. See \ref 
    PageSystemGeoProperties for a description.
    
    This is the abstract base class for all GeoProperties and is used to
    include the GeoPropertyArrayInterface into the class hierarchy. See
    \ref PageSystemGeoProperties for a description.
*/

template <class GeoPropertyDesc>
class AbstractGeoProperty :
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

    virtual UInt32  getFormat    (void) const = 0;
    virtual UInt32  getFormatSize(void) const = 0;
    virtual UInt32  getStride    (void) const = 0;
    virtual UInt32  getDimension (void) const = 0;
    virtual UInt32  getSize      (void) const = 0;
    virtual UInt32  size         (void) const = 0;
    virtual UInt8  *getData      (void) const = 0;

    virtual GenericType getValue (const UInt32       index )       = 0;

    virtual GenericType getValue (const UInt32       index ) const = 0;

    virtual void        getValue (      GenericType &val,
                                  const UInt32       index )       = 0;

    virtual void        getValue (      GenericType &val,
                                  const UInt32       index ) const = 0;


    virtual void        setValue (const GenericType &val,
                                  const UInt32       index )       = 0;

    virtual void        addValue (const GenericType &val   )       = 0;

    virtual bool        insertValue(const GenericType &val,
                                    const UInt32 index)            = 0;

    virtual void        clear    (      void               )       = 0;
    virtual void        resize   (      size_t      newsize)       = 0;
    virtual void        push_back(const GenericType &val   )       = 0;

    virtual void        shrink   (void                     )       = 0;

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

    // Cannot name type Inherited because of MS compiler probs

    typedef typename GeoPropertyDesc::Inherited            LocalInherited;
    typedef typename GeoPropertyDesc::InheritedDesc        LocalInheritedDesc;

#ifndef OSG_SUPPORT_NO_GEO_INTERFACE
    typedef          GeoPropertyInterface<GeoPropertyDesc> LocalInterface;
#endif

    static FieldContainerType _type;
};


/*! \ingroup GrpSystemDrawablesGeometryProperties
    \hideinhierarchy
    \brief GeoProperty is a specialized form of Attachment, used to
    define the properties of the geometry node. See \ref 
    PageSystemGeoProperties for a description.
*/
template <class GeoPropertyDesc>
class GeoProperty :
    public GeoPropertyDesc::Inherited
{
    /*==========================  PRIVATE  ================================*/
  private:

    // Cannot name type Inherited because of MS compiler probs

    typedef typename GeoPropertyDesc::Inherited     LocalInherited;
    typedef typename GeoPropertyDesc::InheritedDesc LocalInheritedDesc;
    typedef typename GeoPropertyDesc::InheritedPtr  LocalInheritedPtr;

    /*==========================  PUBLIC  =================================*/
  public:

    enum
    {
        GeoPropDataFieldId = LocalInherited::NextFieldId,

        NextFieldId        = GeoPropDataFieldId + 1
    };

    static const BitVector GeoPropDataFieldMask = 
                                   1 << static_cast<Int32>(GeoPropDataFieldId);

    typedef GeoProperty<GeoPropertyDesc>         PropertyType;
    typedef GeoProperty<GeoPropertyDesc>         Self;

    typedef FCPtr<LocalInheritedPtr,
                  PropertyType                 > PtrType;


    typedef typename GeoPropertyDesc::StoredFieldType     StoredFieldType;
    typedef typename GeoPropertyDesc::GenericType         StoredGenericType;
    typedef typename StoredFieldType::StoredType          StoredType;

    OSG_FIELD_CONTAINER_TMPL_DECL(PtrType)

#ifdef OSG_MICROSOFT_COMPILER_HACKS
    static FieldAccessMethod getFPtrAccessMethod(void);
#endif

    /*---------------------------------------------------------------------*/
    /*! \name                      Access                                  */
    /*! \{                                                                 */

          StoredFieldType *getFieldPtr(void);

          StoredFieldType &getField(void);
    const StoredFieldType &getField(void) const;

    virtual LocalInheritedPtr clone(void);

    virtual UInt32  getFormat    (void) const;
    virtual UInt32  getFormatSize(void) const;
    virtual UInt32  getStride    (void) const;
    virtual UInt32  getDimension (void) const;
    virtual UInt32  getSize      (void) const;
    virtual UInt32  size         (void) const;
    virtual UInt8  *getData      (void) const;

            StoredFieldType &operator->() { return _field; }

    virtual StoredGenericType getValue(const UInt32 index);

    virtual StoredGenericType getValue(const UInt32 index) const;

    virtual void              getValue(      StoredGenericType &val,
                                       const UInt32             index);

    virtual void              getValue(      StoredGenericType &val,
                                       const UInt32             index) const;

    virtual void              setValue(const StoredGenericType &val,
                                       const UInt32             index);

    virtual void              addValue(const StoredGenericType &val);

    virtual bool              insertValue(const StoredGenericType &val,
                                          const UInt32 index);
    virtual void    clear();

    virtual void    resize(size_t newsize);

    virtual void    push_back(const StoredGenericType &val);

    virtual void    shrink(void);

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

    StoredFieldType _field;

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
    
#if !defined(OSG_FIXED_MFIELDSYNC)
    virtual void executeSync    (      FieldContainer &other,
                                 const BitVector      &whichField);

            void executeSyncImpl(      GeoProperty *pOther,
                                 const BitVector   &whichField);
#else
    virtual void executeSync       (      FieldContainer &other,
                                    const BitVector      &whichField,
                                    const SyncInfo       &sInfo     );

            void executeSyncImpl   (      GeoProperty *pOther,
                                    const BitVector   &whichField,
                                    const SyncInfo    &sInfo     );

    virtual void execBeginEdit     (const BitVector &whichField, 
                                          UInt32     uiAspect,
                                          UInt32     uiContainerSize);

            void execBeginEditImpl (const BitVector &whichField, 
                                          UInt32     uiAspect,
                                          UInt32     uiContainerSize);

    virtual void onDestroyAspect(UInt32 uiId, UInt32 uiAspect);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Changed                                 */
    /*! \{                                                                 */

    virtual void changed        (BitVector whichField, 
                                 UInt32    origin    );
            
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

#if defined(OSG_MICROSOFT_COMPILER_ALERT)
    static FieldDescription   *_desc[];
#endif
    static FieldContainerType  _type;
};

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef AbstractGeoProperty<GeoPositionsPropertyDesc> GeoPositions;
#endif

#ifndef OSG_COMPILEGEOPROPINST
OSG_ABSTR_FC_DLLEXPORT_DECL(AbstractGeoProperty,
                            GeoPositionsPropertyDesc,
                            OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef AbstractGeoProperty<GeoNormalsPropertyDesc> GeoNormals;
#endif

#ifndef OSG_COMPILEGEOPROPINST
OSG_ABSTR_FC_DLLEXPORT_DECL(AbstractGeoProperty,
                            GeoNormalsPropertyDesc,
                            OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef AbstractGeoProperty<GeoColorsPropertyDesc> GeoColors;
#endif

#ifndef OSG_COMPILEGEOPROPINST
OSG_ABSTR_FC_DLLEXPORT_DECL(AbstractGeoProperty,
                            GeoColorsPropertyDesc,
                            OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef AbstractGeoProperty<GeoTexCoordsPropertyDesc> GeoTexCoords;
#endif

#ifndef OSG_COMPILEGEOPROPINST
OSG_ABSTR_FC_DLLEXPORT_DECL(AbstractGeoProperty,
                            GeoTexCoordsPropertyDesc,
                            OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef AbstractGeoProperty<GeoIndicesPropertyDesc> GeoIndices;
#endif

#ifndef OSG_COMPILEGEOPROPINST
OSG_ABSTR_FC_DLLEXPORT_DECL(AbstractGeoProperty,
                            GeoIndicesPropertyDesc,
                            OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef AbstractGeoProperty<GeoPTypesPropertyDesc> GeoPTypes;
#endif

#ifndef OSG_COMPILEGEOPROPINST
OSG_ABSTR_FC_DLLEXPORT_DECL(AbstractGeoProperty,
                            GeoPTypesPropertyDesc,
                            OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif

#if !defined(OSG_DO_DOC)   // created as a dummy class, remove to prevent doubles
typedef AbstractGeoProperty<GeoPLengthsPropertyDesc> GeoPLengths;
#endif

#ifndef OSG_COMPILEGEOPROPINST
OSG_ABSTR_FC_DLLEXPORT_DECL(AbstractGeoProperty,
                            GeoPLengthsPropertyDesc,
                            OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif

OSG_END_NAMESPACE

#include <OSGGeoPropertyBase.inl>


#endif /* _OSGGEOPROPERTYBASE_H_ */

