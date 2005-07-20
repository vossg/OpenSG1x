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

#ifndef _OSGFIELDCONTAINERIMPL_H_
#define _OSGFIELDCONTAINERIMPL_H_
#ifdef __sgi
#pragma once
#endif

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGFieldContainerImpl.h
    \ingroup GrpSystemFieldContainer
 */
#endif

#include <OSGSystemDef.h>
#include <OSGIDStringLink.h>

#include <OSGFieldContainerBase.h>

#if defined(OSG_GV_BETA) && defined(OSG_DBG_MEM)
#include <OSGTime.h>
#include <OSGThread.h>
#endif

OSG_BEGIN_NAMESPACE

class Field;
class BinaryDataHandler;

/*! \ingroup GrpSystemFieldContainer
 */

class FieldContainer 
{
    /*==========================  PUBLIC  =================================*/

  public:

    enum { NextFieldId = 1 };

    static const BitVector NextFieldMask   = 
                    (TypeTraits<BitVector>::One << NextFieldId);
    static const BitVector MTInfluenceMask = 0x00;

    /*---------------------------------------------------------------------*/
    /*! \name             Get Class Type Information                       */
    /*! \{                                                                 */
     
    static OSG_SYSTEMLIB_DLLMAPPING FieldContainerType &getClassType   (void); 
    static OSG_SYSTEMLIB_DLLMAPPING UInt32              getClassTypeId (void);
    static OSG_SYSTEMLIB_DLLMAPPING UInt16              getClassGroupId(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name             Get Instance Type Information                    */
    /*! \{                                                                 */
    
    OSG_SYSTEMLIB_DLLMAPPING 
    virtual       FieldContainerType &getType    (void);

    OSG_SYSTEMLIB_DLLMAPPING 
    virtual const FieldContainerType &getType    (void) const;

                  OSG_SYSTEMLIB_DLLMAPPING 
                  UInt32              getTypeId  (void) const;

                  OSG_SYSTEMLIB_DLLMAPPING 
                  UInt16              getGroupId (void) const;

            OSG_SYSTEMLIB_DLLMAPPING 
            const Char8              *getTypeName(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Container Size                            */
    /*! \{                                                                 */

    OSG_SYSTEMLIB_DLLMAPPING 
    virtual UInt32  getContainerSize(void) const = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                                                              */
    /*! \{                    Generic Field Access                         */

            OSG_SYSTEMLIB_DLLMAPPING 
            Field  *getField        (      UInt32 fieldId  );

            OSG_SYSTEMLIB_DLLMAPPING 
            Field  *getField        (const Char8 *fieldName);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                       Clone                                  */
    /*! \{                                                                 */

    virtual FieldContainerPtr shallowCopy(void) const = 0;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Access                              */
    /*! \{                                                                 */

    OSG_SYSTEMLIB_DLLMAPPING 
    virtual UInt32  getBinSize (const BitVector         &whichField);

    OSG_SYSTEMLIB_DLLMAPPING 
    virtual void    copyToBin  (      BinaryDataHandler &pMem, 
                                const BitVector         &whichField);

    OSG_SYSTEMLIB_DLLMAPPING 
    virtual void    copyFromBin(      BinaryDataHandler &pMem, 
                                const BitVector         &whichField);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Changed                               */
    /*! \{                                                                 */

    OSG_SYSTEMLIB_DLLMAPPING 
    virtual void changed        (BitVector whichField, UInt32 origin);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    OSG_SYSTEMLIB_DLLMAPPING 
    virtual void dump(      UInt32    uiIndent = 0, 
                      const BitVector bvFlags  = 0) const = 0;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                CoredNodePtr helper                           */
    /*! \{                                                                 */

    /*! \ingroup GrpSystemFieldContainer
        Dummy class for CoredNodePtr instantiations on classes that are not
        NodeCores
    */

    class attempt_to_create_CoredNodePtr_on_non_NodeCore_FC
    {
        attempt_to_create_CoredNodePtr_on_non_NodeCore_FC() {}
    };
    
    static const bool isNodeCore = false;
    
    /*! \}                                                                 */   
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    static FieldContainerType _type;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    UInt32 _shares;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    OSG_SYSTEMLIB_DLLMAPPING 
    FieldContainer(void);

    OSG_SYSTEMLIB_DLLMAPPING 
    FieldContainer(const FieldContainer &obj);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    OSG_SYSTEMLIB_DLLMAPPING 
    virtual ~FieldContainer (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Create Fieldcontainer                           */
    /*! \{                                                                 */

    template <class ObjectPtrT>
    static void newPtr(      
                       ObjectPtrT                   &result, 
        const typename ObjectPtrT::StoredObjectType *prototypeP);

    template <class ObjectPtrT>
    static void newPtr(ObjectPtrT &result);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    MT Edit                                   */
    /*! \{                                                                 */

    template<class FieldTypeT>
    void beginEditX(const BitVector &whichField, FieldTypeT &field);

    template<class FieldTypeT>
    void endEditX  (const BitVector &whichField, FieldTypeT &field);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                MT Construction                               */
    /*! \{                                                                 */

    OSG_SYSTEMLIB_DLLMAPPING 
    void onCreate      (const FieldContainer *source = NULL);

    OSG_SYSTEMLIB_DLLMAPPING 
    void onCreateAspect(const FieldContainer *aspect0,
                        const FieldContainer *source = NULL);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                MT Destruction                                */
    /*! \{                                                                 */

    OSG_SYSTEMLIB_DLLMAPPING 
    virtual void onDestroy      (void);

#if defined(OSG_FIXED_MFIELDSYNC)
    OSG_SYSTEMLIB_DLLMAPPING 
    virtual void onDestroyAspect(UInt32 uiId, UInt32 uiAspect);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Sync                                     */
    /*! \{                                                                 */

#if !defined(OSG_FIXED_MFIELDSYNC)
    OSG_SYSTEMLIB_DLLMAPPING 
    virtual void executeSync    (      FieldContainer &other,
                                 const BitVector      &whichField) = 0;

            OSG_SYSTEMLIB_DLLMAPPING 
            void executeSyncImpl(      FieldContainer *pOther,
                                 const BitVector      &whichField);
#else
    OSG_SYSTEMLIB_DLLMAPPING 
    virtual void executeSync       (      FieldContainer &other,
                                    const BitVector      &whichField,
                                    const SyncInfo       &iSinfo    ) = 0;

            OSG_SYSTEMLIB_DLLMAPPING 
            void executeSyncImpl   (      FieldContainer *pOther,
                                    const BitVector      &whichField,
                                    const SyncInfo       &sInfo     );

    OSG_SYSTEMLIB_DLLMAPPING 
    virtual void execBeginEdit     (const BitVector &whichField, 
                                          UInt32     uiAspect,
                                          UInt32     uiContainerSize) = 0;

    OSG_SYSTEMLIB_DLLMAPPING 
            void execBeginEditImpl (const BitVector &whichField, 
                                          UInt32     uiAspect,
                                          UInt32     uiContainerSize);
#endif

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainerPtrBase;
    friend class FieldContainerPtr;

    /*!\brief prohibit default functions (move to 'public' if needed) */
    FieldContainer &operator = (const FieldContainer &other);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

#define OSG_FC_TMPL_VAR_INL 

#if 0
#ifdef FMSCOMPILER

// Macros used to derive a new fieldcontainer

/*! \ingroup GrpSystemFieldContainerX
 *  \relates FieldContainer
 *  \brief declare the first field
 */

#define OSG_FC_FIRST_FIELD_IDM_DECL(OSG_FIELDNAME)                            \
    static const OSG::UInt32    OSG_FIELDNAME##Id;                            \
    static const OSG::BitVector OSG_FIELDNAME##Mask;

/*! \ingroup GrpSystemFieldContainerX
 *  \relates FieldContainer
 *  \brief define the first field
 */

#define OSG_FC_FIRST_FIELD_IDM_DEF(OSG_CLASS, OSG_FIELDNAME)                  \
const OSG::UInt32    OSG_CLASS::OSG_FIELDNAME##Id   =                         \
    Inherited::NextFieldId;                                                   \
const OSG::BitVector OSG_CLASS::OSG_FIELDNAME##Mask =                         \
    Inherited::NextFieldMask;

/*! \ingroup GrpSystemFieldContainerX
 *  \relates FieldContainer
 *  \brief define the first field in template
 */

#define OSG_FC_FIRST_FIELD_IDM_INL_TMPL_DEF(OSG_CLASS,                        \
                                            OSG_TMPL_PARAM,                   \
                                            OSG_FIELDNAME)                    \
template <class OSG_TMPL_PARAM> OSG_FC_TMPL_VAR_INL                           \
const OSG::UInt32    OSG_CLASS<OSG_TMPL_PARAM>::OSG_FIELDNAME##Id    =        \
    Inherited::NextFieldId;                                                   \
template <class OSG_TMPL_PARAM> OSG_FC_TMPL_VAR_INL                           \
const OSG::BitVector OSG_CLASS<OSG_TMPL_PARAM>::OSG_FIELDNAME##Mask  =        \
    Inherited::NextFieldMask;

/*! \ingroup GrpSystemFieldContainerX
 *  \relates FieldContainer
 *  \brief declare a field
 */

#define OSG_FC_FIELD_IDM_DECL(OSG_FIELDNAME)                                  \
    static const OSG::UInt32    OSG_FIELDNAME##Id;                            \
    static const OSG::BitVector OSG_FIELDNAME##Mask;

/*! \ingroup GrpSystemFieldContainerX
 *  \relates FieldContainer
 *  \brief define a field
 */

#define OSG_FC_FIELD_IDM_DEF(OSG_CLASS, OSG_FIELDNAME, OSG_PREV_FIELDNAME)    \
const OSG::UInt32    OSG_CLASS::OSG_FIELDNAME##Id    =                        \
    OSG_PREV_FIELDNAME##Id + 1;                                               \
const OSG::BitVector OSG_CLASS::OSG_FIELDNAME##Mask  =                        \
    OSG_PREV_FIELDNAME##Mask << 1;

/*! \ingroup GrpSystemFieldContainerX
 *  \relates FieldContainer
 *  \brief define a field in template
 */

#define OSG_FC_FIELD_IDM_INL_TMPL_DEF(OSG_CLASS,                              \
                                      OSG_TMPL_PARAM,                         \
                                      OSG_FIELDNAME,                          \
                                      OSG_PREV_FIELDNAME)                     \
template <class OSG_TMPL_PARAM> OSG_FC_TMPL_VAR_INL                           \
const OSG::UInt32    OSG_CLASS<OSG_TMPL_PARAM>::OSG_FIELDNAME##Id    =        \
    OSG_PREV_FIELDNAME##Id + 1;                                               \
template <class OSG_TMPL_PARAM> OSG_FC_TMPL_VAR_INL                           \
const OSG::BitVector OSG_CLASS<OSG_TMPL_PARAM>::OSG_FIELDNAME##Mask  =        \
    OSG_PREV_FIELDNAME##Mask << 1;

/*! \ingroup GrpSystemFieldContainerX
 *  \brief declare the end of fields
 */

#define OSG_FC_LAST_FIELD_IDM_DECL                                            \
    static const OSG::UInt32    NextFieldId;                                  \
    static const OSG::BitVector NextFieldMask;

/*! \ingroup GrpSystemFieldContainerX
 *  \brief define the end of fields
 */

#define OSG_FC_LAST_FIELD_IDM_DEF(OSG_CLASS, OSG_PREV_FIELDNAME)              \
const OSG::UInt32    OSG_CLASS::NextFieldId   =                               \
    OSG_PREV_FIELDNAME##Id + 1;                                               \
const OSG::BitVector OSG_CLASS::NextFieldMask =                               \
    OSG_PREV_FIELDNAME##Mask << 1;

/*! \ingroup GrpSystemFieldContainerX
 *  \brief define the end of fields in template
 */

#define OSG_FC_LAST_FIELD_IDM_INL_TMPL_DEF(OSG_CLASS,                         \
                                           OSG_TMPL_PARAM,                    \
                                           OSG_PREV_FIELDNAME)                \
template <class OSG_TMPL_PARAM> OSG_FC_TMPL_VAR_INL                           \
const OSG::UInt32    OSG_CLASS<OSG_TMPL_PARAM>::NextFieldId   =               \
    OSG_PREV_FIELDNAME##Id + 1;                                               \
template <class OSG_TMPL_PARAM> OSG_FC_TMPL_VAR_INL                           \
const OSG::BitVector OSG_CLASS<OSG_TMPL_PARAM>::NextFieldMask =               \
    OSG_PREV_FIELDNAME##Mask << 1;

/*! \ingroup GrpSystemFieldContainerX
 *  \brief put the field information in the fielddescription constructor
 */
#else
#define OSG_FC_FIRST_FIELD_IDM_DECL(OSG_ELEMNAME)                             \
  static const OSG::UInt32    OSG_ELEMNAME##Id   = Inherited::NextFieldId;    \
  static const OSG::BitVector OSG_ELEMNAME##Mask = Inherited::NextFieldMask;

#define OSG_FC_FIELD_IDM_DECL(OSG_ELEMNAME, OSG_PREV_ELEMNAME)                \
  static const OSG::UInt32    OSG_ELEMNAME##Id   = OSG_PREV_ELEMNAME##Id + 1; \
  static const OSG::BitVector OSG_ELEMNAME##Mask = OSG_PREV_ELEMNAME##Mask <<1;

#define OSG_FC_LAST_FIELD_IDM_DECL(OSG_PREV_ELEMNAME)                         \
  static const OSG::UInt32    NextFieldId   = OSG_PREV_ELEMNAME##Id + 1;      \
  static const OSG::BitVector NextFieldMask = OSG_PREV_ELEMNAME##Mask << 1;

 
#define OSG_FC_FIRST_FIELD_IDM_DEF(OSG_CLASS, OSG_ELEMNAME)                   \
  const OSG::UInt32    OSG_CLASS::OSG_ELEMNAME##Id;                           \
  const OSG::BitVector OSG_CLASS::OSG_ELEMNAME##Mask;

#define OSG_FC_FIRST_FIELD_IDM_INL_TMPL_DEF(OSG_CLASS,                        \
                                            OSG_TMPL_PARAM,                   \
                                            OSG_ELEMNAME)                     \
  template <class OSG_TMPL_PARAM> OSG_FC_TMPL_VAR_INL                         \
  const OSG::UInt32    OSG_CLASS<OSG_TMPL_PARAM>::OSG_ELEMNAME##Id;           \
  template <class OSG_TMPL_PARAM> OSG_FC_TMPL_VAR_INL                         \
  const OSG::BitVector OSG_CLASS<OSG_TMPL_PARAM>::OSG_ELEMNAME##Mask;


#define OSG_FC_FIELD_IDM_DEF(OSG_CLASS, OSG_ELEMNAME, OSG_PREV_ELEMNAME)      \
  const OSG::UInt32    OSG_CLASS::OSG_ELEMNAME##Id;                           \
  const OSG::BitVector OSG_CLASS::OSG_ELEMNAME##Mask;

#define OSG_FC_FIELD_IDM_INL_TMPL_DEF(OSG_CLASS,                              \
                                      OSG_TMPL_PARAM,                         \
                                      OSG_ELEMNAME,                           \
                                      OSG_PREV_ELEMNAME)                      \
  template <class OSG_TMPL_PARAM> OSG_FC_TMPL_VAR_INL                         \
  const OSG::UInt32    OSG_CLASS<OSG_TMPL_PARAM>::OSG_ELEMNAME##Id;           \
  template <class OSG_TMPL_PARAM> OSG_FC_TMPL_VAR_INL                         \
  const OSG::BitVector OSG_CLASS<OSG_TMPL_PARAM>::OSG_ELEMNAME##Mask;

#define OSG_FC_LAST_FIELD_IDM_DEF(OSG_CLASS, OSG_PREV_ELEMNAME)               \
  const OSG::UInt32    OSG_CLASS::NextFieldId;                                \
  const OSG::BitVector OSG_CLASS::NextFieldMask;

#define OSG_FC_LAST_FIELD_IDM_INL_TMPL_DEF(OSG_CLASS,                         \
                                           OSG_TMPL_PARAM,                    \
                                           OSG_PREV_FIELDNAME)                \
  template <class OSG_TMPL_PARAM> OSG_FC_TMPL_VAR_INL                         \
  const OSG::UInt32    OSG_CLASS<OSG_TMPL_PARAM>::NextFieldId;                \
  template <class OSG_TMPL_PARAM> OSG_FC_TMPL_VAR_INL                         \
  const OSG::BitVector OSG_CLASS<OSG_TMPL_PARAM>::NextFieldMask;

#endif
#endif

#define OSG_FC_FIRST_FIELD_IDM_DECL(OSG_ELEMNAME)                             \
  enum { OSG_ELEMNAME##Id   = Inherited::NextFieldId };                       \
  static const OSG::BitVector OSG_ELEMNAME##Mask;

#define OSG_FC_FIELD_IDM_DECL(OSG_ELEMNAME, OSG_PREV_ELEMNAME)                \
  enum { OSG_ELEMNAME##Id   = OSG_PREV_ELEMNAME##Id + 1 };                    \
  static const OSG::BitVector OSG_ELEMNAME##Mask;

#define OSG_FC_LAST_FIELD_IDM_DECL(OSG_PREV_ELEMNAME)                         \
  enum { NextFieldId   = OSG_PREV_ELEMNAME##Id + 1 };                         \

 
#define OSG_FC_FIRST_FIELD_IDM_DEF(OSG_CLASS, OSG_ELEMNAME)                   \
  const OSG::BitVector OSG_CLASS::OSG_ELEMNAME##Mask =                        \
      (TypeTraits<BitVector>::One << OSG_CLASS::OSG_ELEMNAME##Id);

#define OSG_FC_FIRST_FIELD_IDM_INL_TMPL_DEF(OSG_CLASS,                        \
                                            OSG_TMPL_PARAM,                   \
                                            OSG_ELEMNAME)                     \
  template <class OSG_TMPL_PARAM> OSG_FC_TMPL_VAR_INL                         \
  const OSG::BitVector OSG_CLASS<OSG_TMPL_PARAM>::OSG_ELEMNAME##Mask =        \
    (TypeTraits<BitVector>::One <<                                \
        OSG_CLASS<OSG_TMPL_PARAM>::OSG_ELEMNAME##Id);


#define OSG_FC_FIELD_IDM_DEF(OSG_CLASS, OSG_ELEMNAME, OSG_PREV_ELEMNAME)      \
  const OSG::BitVector OSG_CLASS::OSG_ELEMNAME##Mask =                        \
    (TypeTraits<BitVector>::One << OSG_CLASS::OSG_ELEMNAME##Id);

#define OSG_FC_FIELD_IDM_INL_TMPL_DEF(OSG_CLASS,                              \
                                      OSG_TMPL_PARAM,                         \
                                      OSG_ELEMNAME,                           \
                                      OSG_PREV_ELEMNAME)                      \
  template <class OSG_TMPL_PARAM> OSG_FC_TMPL_VAR_INL                         \
  const OSG::BitVector OSG_CLASS<OSG_TMPL_PARAM>::OSG_ELEMNAME##Mask =        \
    (TypeTraits<BitVector>::One <<                                \
        OSG_CLASS<OSG_TMPL_PARAM>::OSG_ELEMNAME##);

#define OSG_FC_LAST_FIELD_IDM_DEF(OSG_CLASS, OSG_PREV_ELEMNAME)

#define OSG_FC_LAST_FIELD_IDM_INL_TMPL_DEF(OSG_CLASS,                         \
                                           OSG_TMPL_PARAM,                    \
                                           OSG_PREV_FIELDNAME)


#define OSG_FC_FIELD_IDM_DESC(OSG_FIELDNAME)                                  \
    OSG_FIELDNAME##Id, OSG_FIELDNAME##Mask

/*---------------------------- get type -------------------------------------*/

#define OSG_FC_GET_TYPE_DECL                                                  \
    virtual       OSG::FieldContainerType &getType(void);                     \
    virtual const OSG::FieldContainerType &getType(void) const;

#define OSG_FC_GET_TYPE_DEF(OSG_CLASS)                                        \
    OSG::FieldContainerType &OSG_CLASS::getType(void)                         \
    {                                                                         \
        return _type;                                                         \
    }                                                                         \
    const OSG::FieldContainerType &OSG_CLASS::getType(void) const             \
    {                                                                         \
        return _type;                                                         \
    }

#define OSG_FC_GET_TYPE_INL_TMPL_DEF(OSG_TMPL_PARAM, OSG_CLASS)               \
  template <class OSG_TMPL_PARAM> inline                                      \
  OSG::FieldContainerType &OSG_CLASS<OSG_TMPL_PARAM>::getType(void)           \
  {                                                                           \
      return _type;                                                           \
  }                                                                           \
  template <class OSG_TMPL_PARAM> inline                                      \
  const OSG::FieldContainerType &OSG_CLASS<OSG_TMPL_PARAM>::getType(          \
      void) const                                                             \
  {                                                                           \
      return _type;                                                           \
  }


#define OSG_FC_GET_STATIC_TYPE_DECL                                           \
    static OSG::FieldContainerType & getClassType(void);           

#define OSG_FC_GET_STATIC_TYPE_INL_DEF(OSG_CLASS)                             \
    inline                                                                    \
    OSG::FieldContainerType &OSG_CLASS::getClassType(void)                    \
    {                                                                         \
        return _type;                                                         \
    }

#define OSG_FC_GET_STATIC_TYPE_INL_TMPL_DEF(OSG_TMPL_PARAM,                   \
                                            OSG_CLASS)                        \
    template <class OSG_TMPL_PARAM> inline                                    \
    OSG::FieldContainerType &OSG_CLASS<OSG_TMPL_PARAM>::getClassType(void)    \
    {                                                                         \
        return _type;                                                         \
    }

#define OSG_FC_GET_STATIC_TYPE_ID_DECL                                        \
    static OSG::UInt32 getClassTypeId(void);             

#define OSG_FC_GET_STATIC_TYPE_ID_INL_DEF(OSG_CLASS)                          \
    inline                                                                    \
    OSG::UInt32 OSG_CLASS::getClassTypeId(void)                               \
    {                                                                         \
        return _type.getId();                                                 \
    }

#define OSG_FC_GET_STATIC_TYPE_ID_INL_TMPL_DEF(OSG_TMPL_PARAM,                \
                                               OSG_CLASS)                     \
    template <class OSG_TMPL_PARAM> inline                                    \
    OSG::UInt32 OSG_CLASS<OSG_TMPL_PARAM>::getClassTypeId(void)               \
    {                                                                         \
        return _type.getId();                                                 \
    }

#define OSG_FC_TYPE_FUNCTIONS_DECL                                            \
    OSG_FC_GET_TYPE_DECL                                                      \
    OSG_FC_GET_STATIC_TYPE_DECL                                               \
    OSG_FC_GET_STATIC_TYPE_ID_DECL                     

#define OSG_FC_TYPE_FUNCTIONS_DEF(OSG_CLASS)                                  \
    OSG_FC_GET_TYPE_DEF(OSG_CLASS)

#define OSG_FC_TYPE_FUNCTIONS_INL_DEF(OSG_CLASS)                              \
    OSG_FC_GET_STATIC_TYPE_INL_DEF   (OSG_CLASS)                              \
    OSG_FC_GET_STATIC_TYPE_ID_INL_DEF(OSG_CLASS)


#define OSG_FC_TYPE_FUNCTIONS_INL_TMPL_DEF(OSG_TMPL_PARAM, OSG_CLASS)         \
    OSG_FC_GET_TYPE_INL_TMPL_DEF          (OSG_TMPL_PARAM, OSG_CLASS)         \
    OSG_FC_GET_STATIC_TYPE_INL_TMPL_DEF   (OSG_TMPL_PARAM, OSG_CLASS)         \
    OSG_FC_GET_STATIC_TYPE_ID_INL_TMPL_DEF(OSG_TMPL_PARAM, OSG_CLASS)

#define OSG_FC_ST_TYPE_FUNCTIONS_INL_TMPL_DEF(OSG_TMPL_PARAM, OSG_CLASS)      \
    OSG_FC_GET_STATIC_TYPE_INL_TMPL_DEF   (OSG_TMPL_PARAM, OSG_CLASS)         \
    OSG_FC_GET_STATIC_TYPE_ID_INL_TMPL_DEF(OSG_TMPL_PARAM, OSG_CLASS)


/*---------------------------- create ---------------------------------------*/

#define OSG_FC_CREATE_DECL(OSG_CLASS_PTR)                                     \
    static OSG_CLASS_PTR create(void);

#define OSG_FC_CREATE_INL_DEF(OSG_CLASS, OSG_CLASS_PTR)                       \
    inline                                                                    \
    OSG_CLASS_PTR OSG_CLASS::create(void)                                     \
    {                                                                         \
        OSG_CLASS_PTR fc;                                                     \
                                                                              \
        if(getClassType().getPrototype() != OSG::NullFC)                      \
         fc = OSG_CLASS_PTR::dcast(getClassType().getPrototype()->            \
                 shallowCopy());                                              \
                                                                              \
        return fc;                                                            \
    }

#define OSG_FC_CREATE_INL_TMPL_DEF(OSG_TMPL_PARAM,                            \
                                   OSG_CLASS,                                 \
                                   OSG_CLASS_PTR)                             \
    template <class OSG_TMPL_PARAM> inline                                    \
    typename OSG_CLASS<OSG_TMPL_PARAM>::OSG_CLASS_PTR                         \
        OSG_CLASS<OSG_TMPL_PARAM>::create(void)                               \
    {                                                                         \
        OSG_CLASS_PTR fc;                                                     \
                                                                              \
        if(getClassType().getPrototype() != OSG::NullFC)                      \
         fc = OSG_CLASS_PTR::dcast(getClassType().getPrototype()->            \
                  shallowCopy());                                             \
                                                                              \
        return fc;                                                            \
    }

#define OSG_FC_CREATE_EMPTY_DECL(OSG_CLASS_PTR)                         \
    static OSG_CLASS_PTR createEmpty(void);

#define OSG_FC_CREATE_EMPTY_INL_DEF(OSG_CLASS, OSG_CLASS_PTR)           \
    inline                                                              \
    OSG_CLASS_PTR OSG_CLASS::createEmpty(void)                          \
    {                                                                   \
        OSG_CLASS_PTR returnValue;                                      \
                                                                        \
        newPtr(returnValue);                                            \
                                                                        \
        return returnValue;                                             \
    }

#define OSG_FC_CREATE_EMPTY_INL_TMPL_DEF(OSG_TMPL_PARAM,                \
                                         OSG_CLASS,                     \
                                         OSG_CLASS_PTR)                 \
    template <class OSG_TMPL_PARAM> inline                              \
    typename OSG_CLASS<OSG_TMPL_PARAM>::OSG_CLASS_PTR                   \
        OSG_CLASS<OSG_TMPL_PARAM>::createEmpty(void)                    \
    {                                                                   \
        OSG_CLASS_PTR returnValue;                                      \
                                                                        \
        Self::newPtr(returnValue);                                      \
                                                                        \
        return returnValue;                                             \
    }


#define OSG_FC_SHALLOWCOPY_DECL                                         \
    virtual OSG::FieldContainerPtr shallowCopy(void) const;

#define OSG_FC_SHALLOWCOPY_DEF(OSG_CLASS, OSG_CLASS_PTR)                \
    OSG::FieldContainerPtr OSG_CLASS::shallowCopy(void) const           \
    {                                                                   \
        OSG_CLASS_PTR returnValue;                                      \
                                                                        \
        newPtr(returnValue, this);                                      \
                                                                        \
        return returnValue;                                             \
    } 

#define OSG_FC_SHALLOWCOPY_INL_TMPL_DEF(OSG_TMPL_PARAM,                       \
                                        OSG_CLASS,                            \
                                        OSG_CLASS_PTR)                        \
    template <class OSG_TMPL_PARAM> inline                                    \
    OSG::FieldContainerPtr OSG_CLASS<OSG_TMPL_PARAM>::shallowCopy(void) const \
    {                                                                         \
        OSG_CLASS_PTR returnValue;                                            \
                                                                              \
        Self::newPtr(returnValue, this);                                      \
                                                                              \
        return returnValue;                                                   \
    } 


#define OSG_FC_CREATE_FUNCTIONS_DECL(OSG_CLASS_PTR)                     \
    OSG_FC_CREATE_DECL      (OSG_CLASS_PTR)                             \
    OSG_FC_CREATE_EMPTY_DECL(OSG_CLASS_PTR)                             \
    OSG_FC_SHALLOWCOPY_DECL

#define OSG_FC_CREATE_FUNCTIONS_DEF(OSG_CLASS, OSG_CLASS_PTR)           \
    OSG_FC_SHALLOWCOPY_DEF(OSG_CLASS, OSG_CLASS_PTR)

#define OSG_FC_CREATE_FUNCTIONS_INL_DEF(OSG_CLASS, OSG_CLASS_PTR)       \
    OSG_FC_CREATE_INL_DEF      (OSG_CLASS, OSG_CLASS_PTR)               \
    OSG_FC_CREATE_EMPTY_INL_DEF(OSG_CLASS, OSG_CLASS_PTR)

#define OSG_FC_CREATE_FUNCTIONS_INL_TMPL_DEF(OSG_TMPL_PARAM,            \
                                             OSG_CLASS,                 \
                                             OSG_CLASS_PTR)             \
    OSG_FC_SHALLOWCOPY_INL_TMPL_DEF       (OSG_TMPL_PARAM,              \
                                     OSG_CLASS,                         \
                                     OSG_CLASS_PTR)                     \
    OSG_FC_CREATE_INL_TMPL_DEF      (OSG_TMPL_PARAM,                    \
                                     OSG_CLASS,                         \
                                     OSG_CLASS_PTR)                     \
    OSG_FC_CREATE_EMPTY_INL_TMPL_DEF(OSG_TMPL_PARAM,                    \
                                     OSG_CLASS,                         \
                                     OSG_CLASS_PTR)

/*-------------------------- get size ---------------------------------------*/


#define OSG_FC_GET_SIZE_DECL                                           \
    virtual OSG::UInt32 getContainerSize(void) const;

#define OSG_FC_GET_SIZE_DEF(OSG_CLASS)                                 \
    OSG::UInt32 OSG_CLASS::getContainerSize(void) const                \
    {                                                                  \
        return sizeof(OSG_CLASS);                                      \
    }

#define OSG_FC_GET_SIZE_INL_TMPL_DEF(OSG_TMPL_PARAM, OSG_CLASS)         \
    template <class OSG_TMPL_PARAM> inline                              \
    OSG::UInt32 OSG_CLASS<OSG_TMPL_PARAM>::getContainerSize(void) const \
    {                                                                   \
        return sizeof(OSG_CLASS);                                       \
    }

#define OSG_FC_SIZE_FUNCTIONS_DECL                                     \
    OSG_FC_GET_SIZE_DECL

#define OSG_FC_SIZE_FUNCTIONS_DEF(OSG_CLASS)                           \
    OSG_FC_GET_SIZE_DEF(OSG_CLASS)

#define OSG_FC_SIZE_FUNCTIONS_INL_TMPL_DEF(OSG_TMPL_PARAM, OSG_CLASS)  \
    OSG_FC_GET_SIZE_INL_TMPL_DEF(OSG_TMPL_PARAM, OSG_CLASS)


/*------------------------ decl and def macros ------------------------------*/

#define OSG_FIELD_CONTAINER_DECL(OSG_CLASS_PTR)               \
    OSG_FC_TYPE_FUNCTIONS_DECL                                \
    OSG_FC_CREATE_FUNCTIONS_DECL(OSG_CLASS_PTR)               \
    OSG_FC_SIZE_FUNCTIONS_DECL

#define OSG_FIELD_CONTAINER_DEF(OSG_CLASS, OSG_CLASS_PTR)     \
    OSG_FC_TYPE_FUNCTIONS_DEF  (OSG_CLASS)                    \
    OSG_FC_CREATE_FUNCTIONS_DEF(OSG_CLASS, OSG_CLASS_PTR)     \
    OSG_FC_SIZE_FUNCTIONS_DEF  (OSG_CLASS)

#define OSG_FIELD_CONTAINER_INL_DEF(OSG_CLASS, OSG_CLASS_PTR) \
    OSG_FC_TYPE_FUNCTIONS_INL_DEF  (OSG_CLASS)                \
    OSG_FC_CREATE_FUNCTIONS_INL_DEF(OSG_CLASS, OSG_CLASS_PTR)

/*--------------------- abstr decl and def macros --------------------------*/

#define OSG_ABSTR_FIELD_CONTAINER_DECL(OSG_CLASS_PTR)               \
    OSG_FC_TYPE_FUNCTIONS_DECL                                      \
    OSG_FC_SIZE_FUNCTIONS_DECL

#define OSG_ABSTR_FIELD_CONTAINER_DEF(OSG_CLASS, OSG_CLASS_PTR)     \
    OSG_FC_TYPE_FUNCTIONS_DEF  (OSG_CLASS)                          \
    OSG_FC_SIZE_FUNCTIONS_DEF  (OSG_CLASS)

#define OSG_ABSTR_FIELD_CONTAINER_INL_DEF(OSG_CLASS, OSG_CLASS_PTR) \
    OSG_FC_TYPE_FUNCTIONS_INL_DEF  (OSG_CLASS)

/*------------------ template decl and def macros --------------------------*/

#define OSG_FIELD_CONTAINER_TMPL_DECL(OSG_CLASS_PTR)                 \
    OSG_FC_TYPE_FUNCTIONS_DECL                                       \
    OSG_FC_CREATE_FUNCTIONS_DECL(OSG_CLASS_PTR)                      \
    OSG_FC_SIZE_FUNCTIONS_DECL

#ifdef WIN32
#define OSG_FIELD_CONTAINER_INL_TMPL_DEF(OSG_CLASS,                  \
                                         OSG_TMPL_PARAM,             \
                                         OSG_CLASS_PTR)              \
    OSG_FC_SIZE_FUNCTIONS_INL_TMPL_DEF  (OSG_TMPL_PARAM, OSG_CLASS)  \
    OSG_FC_CREATE_FUNCTIONS_INL_TMPL_DEF(OSG_TMPL_PARAM,             \
                                         OSG_CLASS,                  \
                                         OSG_CLASS_PTR)
#else
#define OSG_FIELD_CONTAINER_INL_TMPL_DEF(OSG_CLASS,                  \
                                         OSG_TMPL_PARAM,             \
                                         OSG_CLASS_PTR)              \
    OSG_FC_TYPE_FUNCTIONS_INL_TMPL_DEF  (OSG_TMPL_PARAM, OSG_CLASS)  \
    OSG_FC_SIZE_FUNCTIONS_INL_TMPL_DEF  (OSG_TMPL_PARAM, OSG_CLASS)  \
    OSG_FC_CREATE_FUNCTIONS_INL_TMPL_DEF(OSG_TMPL_PARAM,             \
                                         OSG_CLASS,                  \
                                         OSG_CLASS_PTR)
#endif


#ifdef WIN32
#define OSG_FIELD_CONTAINER_ST_INL_TMPL_DEF(OSG_CLASS,                  \
                                            OSG_TMPL_PARAM,             \
                                            OSG_CLASS_PTR)              \
    OSG_FC_SIZE_FUNCTIONS_INL_TMPL_DEF     (OSG_TMPL_PARAM, OSG_CLASS)  \
    OSG_FC_CREATE_FUNCTIONS_INL_TMPL_DEF   (OSG_TMPL_PARAM,             \
                                            OSG_CLASS,                  \
                                            OSG_CLASS_PTR)
#else
#define OSG_FIELD_CONTAINER_ST_INL_TMPL_DEF(OSG_CLASS,                  \
                                            OSG_TMPL_PARAM,             \
                                            OSG_CLASS_PTR)              \
    OSG_FC_ST_TYPE_FUNCTIONS_INL_TMPL_DEF  (OSG_TMPL_PARAM, OSG_CLASS)  \
    OSG_FC_SIZE_FUNCTIONS_INL_TMPL_DEF     (OSG_TMPL_PARAM, OSG_CLASS)  \
    OSG_FC_CREATE_FUNCTIONS_INL_TMPL_DEF   (OSG_TMPL_PARAM,             \
                                            OSG_CLASS,                  \
                                            OSG_CLASS_PTR)
#endif

/*---------------abstr template decl and def macros ------------------------*/

#define OSG_ABSTR_FIELD_CONTAINER_TMPL_DECL(OSG_CLASS_PTR)           \
    OSG_FC_TYPE_FUNCTIONS_DECL                                       \
    OSG_FC_SIZE_FUNCTIONS_DECL

#define OSG_ABSTR_FIELD_CONTAINER_INL_TMPL_DEF(OSG_CLASS,            \
                                               OSG_TMPL_PARAM,       \
                                               OSG_CLASS_PTR)        \
    OSG_FC_TYPE_FUNCTIONS_INL_TMPL_DEF  (OSG_TMPL_PARAM, OSG_CLASS)  \
    OSG_FC_SIZE_FUNCTIONS_INL_TMPL_DEF  (OSG_TMPL_PARAM, OSG_CLASS)


/*--------------experimental--------------*/
/* macros for standard field access functions */

#define OSG_SFIELD_ACCESS_FUNCTIONS_DECL( OSG_FIELDTYPE, OSG_TYPE,      \
        OSG_NAME )                                                      \
    inline OSG_FIELDTYPE * getSF##OSG_NAME( void );                         \
    inline OSG_TYPE get##OSG_NAME( void );                                  \
    inline OSG_TYPE get##OSG_NAME( void ) const;                        \
    inline void set##OSG_NAME( const OSG_TYPE value );


#define OSG_SFIELD_ACCESS_FUNCTIONS_INL( OSG_CLASS, OSG_FIELDTYPE,      \
        OSG_TYPE, OSG_NAME )                                            \
    inline OSG_FIELDTYPE * OSG_CLASS::getSF##OSG_NAME( void )           \
    {                                                                   \
        return &_##OSG_NAME;                                            \
    }                                                                   \
    inline OSG_TYPE OSG_CLASS::get##OSG_NAME(void)                      \
    {                                                                   \
        return _##OSG_NAME.getValue();                                  \
    }                                                                   \
    inline OSG_TYPE OSG_CLASS::get##OSG_NAME(void) const                \
    {                                                                   \
        return _##OSG_NAME.getValue();                                  \
    }                                                                   \
    inline void OSG_CLASS::set##OSG_NAME( const OSG_TYPE val)           \
    {                                                                   \
        _##OSG_NAME.setValue( val );                                    \
    }                                                                   

OSG_END_NAMESPACE

#define OSGFIELDCONTAINER_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGFIELDCONTAINERIMPL_H_ */
