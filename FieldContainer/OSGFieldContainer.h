/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
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


#ifndef _OSGFIELDCONTAINER_H_
#define _OSGFIELDCONTAINER_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGFieldContainerBase.h>
#include <OSGFieldContainerType.h>
#include <OSGStringLink.h>
#include <OSGFieldContainerFactory.h>
#include <OSGThreadManager.h>
#include <OSGMField.h>
#include <OSGSField.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class Field;
class FieldContainerPtr;

namespace FieldBits
{
    const BitVector AllFields = 0xFFFFFFFF;

    const BitVector Field0    = 0x00000001;
    const BitVector Field1    = 0x00000002;
    const BitVector Field2    = 0x00000004;
    const BitVector Field3    = 0x00000008;

    const BitVector Field4    = 0x00000010;
    const BitVector Field5    = 0x00000020;
    const BitVector Field6    = 0x00000040;
    const BitVector Field7    = 0x00000080;

    const BitVector Field8    = 0x00000100;
    const BitVector Field9    = 0x00000200;
    const BitVector Field10   = 0x00000400;
    const BitVector Field11   = 0x00000800;

    const BitVector Field12   = 0x00001000;
    const BitVector Field13   = 0x00002000;
    const BitVector Field14   = 0x00004000;
    const BitVector Field15   = 0x00008000;

    const BitVector Field16   = 0x00010000;
    const BitVector Field17   = 0x00020000;
    const BitVector Field18   = 0x00040000;
    const BitVector Field19   = 0x00080000;

    const BitVector Field20   = 0x00100000;
    const BitVector Field21   = 0x00200000;
    const BitVector Field22   = 0x00400000;
    const BitVector Field23   = 0x00800000;

    const BitVector Field24   = 0x01000000;
    const BitVector Field25   = 0x02000000;
    const BitVector Field26   = 0x04000000;
    const BitVector Field27   = 0x08000000;

    const BitVector Field28   = 0x10000000;
    const BitVector Field29   = 0x20000000;
    const BitVector Field30   = 0x40000000;
    const BitVector Field31   = 0x80000000;
}

namespace FCDumpFlags
{
    const BitVector RefCount   = 0x00000001;

    const BitVector AllAspects = 0x00000002;

    const BitVector All        = 0xFFFFFFFF;
}

OSG_FIELDCONTAINER_DLLMAPPING
void addRefCP   (const FieldContainerPtrBase &objectP);

OSG_FIELDCONTAINER_DLLMAPPING
void subRefCP   (const FieldContainerPtrBase &objectP);

OSG_FIELDCONTAINER_DLLMAPPING
void setRefdCP  (const FieldContainerPtrBase &objectP,
                 const FieldContainerPtrBase &newObjectP);

OSG_FIELDCONTAINER_DLLMAPPING
void clearRefCP(FieldContainerPtrBase &objectP);

OSG_FIELDCONTAINER_DLLMAPPING
void beginEditCP(const FieldContainerPtr &objectP, 
                       BitVector          whichField = FieldBits::AllFields);

OSG_FIELDCONTAINER_DLLMAPPING
void endEditCP  (const FieldContainerPtr &objectP, 
                       BitVector          whichField = FieldBits::AllFields);

OSG_FIELDCONTAINER_DLLMAPPING
void changedCP  (const FieldContainerPtr &objectP, 
                       BitVector          whichField = FieldBits::AllFields);

OSG_FIELDCONTAINER_DLLMAPPING
void endEditNotChangedCP(const FieldContainerPtr &objectP, 
                         BitVector          whichField = FieldBits::AllFields);


//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/** \defgroup FieldContainerLib OpenSG Field Container Library
 *  \brief This lib contains all field container elements like NodeCore's,
 *  Attachments.
 */

/*! \ingroup FieldContainerLib
 *  \brief FieldContainer
 */

class OSG_FIELDCONTAINER_DLLMAPPING FieldContainer 
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    static const UInt32    NextFieldId   =    1;
    static const BitVector NextFieldMask = 0x01;

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    enum ChangeMode
    {
        External = 0x01,
        Sync     = 0x02,
        Child    = 0x03
    };

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    /*------------------------- type information-----------------------------*/

    static       FieldContainerType &getClassType  (void);
    static       UInt32              getClassTypeId(void);

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*------------------------- type information-----------------------------*/
    
    virtual       FieldContainerType &getType    (void);
    virtual const FieldContainerType &getType    (void) const;

                  UInt32              getTypeId  (void) const;
                  UInt16              getGroupId (void) const;

            const Char8              *getTypeName(void) const;

    /*------------------------------ size -----------------------------------*/

    virtual UInt32            getSize    (void) const = 0;

    /*----------------------------- access ----------------------------------*/

            Field            *getField   (      UInt32 fieldId  );
            Field            *getField   (const Char8 *fieldName);

    /*----------------------------- clone ----------------------------------*/

    virtual FieldContainerPtr shallowCopy(void) const = 0;

    /*----------------------------- dump ----------------------------------*/

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector &bvFlags  = 0) const = 0;
    
  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    static FieldContainerType _type;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    UInt32 _shares;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    FieldContainer(void);
    FieldContainer(const FieldContainer &obj);
    virtual ~FieldContainer (void);

    virtual void finalize(void);

    template <class ObjectPtrT>
    static void newPtr(      
                       ObjectPtrT                &result, 
        const typename ObjectPtrT::ObjectType *prototypeP)
    {
        typedef typename ObjectPtrT::ObjectType ObjectType;

        UInt8 *pTmp;

        result._containerSize = sizeof(ObjectType);

        pTmp        = 
            (UInt8 *) operator new(
                sizeof(Int32)      + // ReferenceCount
                sizeof(UInt32)     + // ContainerId
                sizeof(ObjectType) * ThreadManager::getNumAspects());

        *((Int32 *) pTmp) = 0;
        
        pTmp += sizeof(Int32);

        *((UInt32 *) pTmp) = 
            FieldContainerFactory::the()->registerFieldContainer(result);

        pTmp += sizeof(UInt32);

        result._storeP = pTmp;

        for(UInt32 i = 0; i < ThreadManager::getNumAspects(); i++)
        {
            pTmp = (UInt8 *) new (pTmp) ObjectType(*prototypeP);

            pTmp += sizeof(ObjectType);
        }

#ifdef OSG_DEBUG_TYPED_FCPTR
        result.updateTypedStore();
#endif
        
    }

    template <class ObjectPtrT>
    static void newPtr(ObjectPtrT &result)
    {
        typedef typename ObjectPtrT::ObjectType ObjectType;

        UInt8 *pTmp;

        result._containerSize = sizeof(ObjectType);

        pTmp        =             
            (UInt8 *) operator new(
                sizeof(Int32)      + // ReferenceCount
                sizeof(UInt32)     + // ContainerId
                sizeof(ObjectType) * ThreadManager::getNumAspects());

        *((Int32 *) pTmp) = 0;
        
        pTmp  += sizeof(Int32);

        *((UInt32 *) pTmp) = 
            FieldContainerFactory::the()->registerFieldContainer(result);

        pTmp += sizeof(UInt32);
        
        result._storeP = pTmp;

        for(UInt32 i = 0; i < ThreadManager::getNumAspects(); i++)
        {
            pTmp = (UInt8 *) new (pTmp) ObjectType();
            
            pTmp += sizeof(ObjectType);
        }

#ifdef OSG_DEBUG_TYPED_FCPTR
        result.updateTypedStore();
#endif
    }

    template <class T>
    T getPtr(const typename T::ObjectType &object)
    {
        T returnValue(object); 
        return returnValue; 
    }

    template <class T>
    T getPtr(const typename T::ObjectType &object) const
    {
        T returnValue(object); 
        return returnValue; 
    }

    template <class FieldTypeT>
    void beginEdit(const BitVector             &,
                         SField<FieldTypeT> &fieldR)
    {
        fieldR.beginEdit();
    }

    template <class FieldTypeT>
    void beginEdit(const BitVector             &,
                         MField<FieldTypeT> &fieldR)
    {
        fieldR.beginEdit();
    }

    template <class FieldTypeT>
    void endEdit(const BitVector             &whichField,
                       SField<FieldTypeT> &)
    {
        FieldContainerPtr tmpPtr(this);
        endEditCP(tmpPtr, whichField);
    }

    template <class FieldTypeT>
    void endEdit(const BitVector             &whichField,
                       MField<FieldTypeT> &)
    {
        FieldContainerPtr tmpPtr(this);
        endEditCP(tmpPtr, whichField);
    }


    virtual void changed(BitVector whichField, ChangeMode from);

  private:


    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class FieldContainerPtrBase;
    friend class FieldContainerPtr;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    static char cvsid[];

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// prohibit default functions (move to 'public' if you need one)

    FieldContainer &operator = (const FieldContainer &other);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

/*! \ingroup FieldContainerLib
 *  \relates FieldContainer
 *  \brief var needs inline
 */

#define OSG_FC_TMPL_VAR_INL 

#ifdef FMSCOMPILER

// Macros used to derive a new fieldcontainer

/*! \ingroup FieldContainerLib
 *  \relates FieldContainer
 *  \brief declare the first field
 */

#define OSG_FC_FIRST_FIELD_IDM_DECL(OSG_FIELDNAME)                            \
    static const OSG::UInt32    OSG_FIELDNAME##Id;                            \
    static const OSG::BitVector OSG_FIELDNAME##Mask;

/*! \ingroup FieldContainerLib
 *  \relates FieldContainer
 *  \brief define the first field
 */

#define OSG_FC_FIRST_FIELD_IDM_DEF(OSG_CLASS, OSG_FIELDNAME)                  \
const OSG::UInt32    OSG_CLASS::OSG_FIELDNAME##Id   =                         \
    Inherited::NextFieldId;                                                   \
const OSG::BitVector OSG_CLASS::OSG_FIELDNAME##Mask =                         \
    Inherited::NextFieldMask;

/*! \ingroup FieldContainerLib
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

/*! \ingroup FieldContainerLib
 *  \relates FieldContainer
 *  \brief declare a field
 */

#define OSG_FC_FIELD_IDM_DECL(OSG_FIELDNAME)                                  \
    static const OSG::UInt32    OSG_FIELDNAME##Id;                            \
    static const OSG::BitVector OSG_FIELDNAME##Mask;

/*! \ingroup FieldContainerLib
 *  \relates FieldContainer
 *  \brief define a field
 */

#define OSG_FC_FIELD_IDM_DEF(OSG_CLASS, OSG_FIELDNAME, OSG_PREV_FIELDNAME)    \
const OSG::UInt32    OSG_CLASS::OSG_FIELDNAME##Id    =                        \
    OSG_PREV_FIELDNAME##Id + 1;                                               \
const OSG::BitVector OSG_CLASS::OSG_FIELDNAME##Mask  =                        \
    OSG_PREV_FIELDNAME##Mask << 1;

/*! \ingroup FieldContainerLib
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

/*! \ingroup FieldContainerLib
 *  \brief declare the end of fields
 */

#define OSG_FC_LAST_FIELD_IDM_DECL                                            \
    static const OSG::UInt32    NextFieldId;                                  \
    static const OSG::BitVector NextFieldMask;

/*! \ingroup FieldContainerLib
 *  \brief define the end of fields
 */

#define OSG_FC_LAST_FIELD_IDM_DEF(OSG_CLASS, OSG_PREV_FIELDNAME)              \
const OSG::UInt32    OSG_CLASS::NextFieldId   =                               \
    OSG_PREV_FIELDNAME##Id + 1;                                               \
const OSG::BitVector OSG_CLASS::NextFieldMask =                               \
    OSG_PREV_FIELDNAME##Mask << 1;

/*! \ingroup FieldContainerLib
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

/*! \ingroup FieldContainerLib
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
         fc = dcast<OSG_CLASS_PTR>(getClassType().getPrototype()->            \
                 shallowCopy());                                              \
                                                                              \
        return fc;                                                            \
    }

#define OSG_FC_CREATE_INL_TMPL_DEF(OSG_TMPL_PARAM,                            \
                                   OSG_CLASS,                                 \
                                   OSG_CLASS_PTR)                             \
    template <class OSG_TMPL_PARAM> inline                                    \
    OSG_CLASS<OSG_TMPL_PARAM>::OSG_CLASS_PTR                                  \
        OSG_CLASS<OSG_TMPL_PARAM>::create(void)                               \
    {                                                                         \
        OSG_CLASS_PTR fc;                                                     \
                                                                              \
        if(getClassType().getPrototype() != OSG::NullFC)                      \
         fc = dcast<OSG_CLASS_PTR>(getClassType().getPrototype()->            \
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
    OSG_CLASS<OSG_TMPL_PARAM>::OSG_CLASS_PTR                            \
        OSG_CLASS<OSG_TMPL_PARAM>::createEmpty(void)                    \
    {                                                                   \
        OSG_CLASS_PTR returnValue;                                      \
                                                                        \
        newPtr(returnValue);                                            \
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
    template <class OSG_TMPL_PARAM>                                           \
    OSG::FieldContainerPtr OSG_CLASS<OSG_TMPL_PARAM>::shallowCopy(void) const \
    {                                                                         \
        OSG_CLASS_PTR returnValue;                                            \
                                                                              \
        newPtr(returnValue, this);                                            \
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
    virtual OSG::UInt32 getSize(void) const;

#define OSG_FC_GET_SIZE_DEF(OSG_CLASS)                                 \
    OSG::UInt32 OSG_CLASS::getSize(void) const                         \
    {                                                                  \
        return sizeof(OSG_CLASS);                                      \
    }

#define OSG_FC_GET_SIZE_INL_TMPL_DEF(OSG_TMPL_PARAM, OSG_CLASS)        \
    template <class OSG_TMPL_PARAM> inline                             \
    OSG::UInt32 OSG_CLASS<OSG_TMPL_PARAM>::getSize(void) const         \
    {                                                                  \
        return sizeof(OSG_CLASS);                                      \
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

#define OSG_FIELD_CONTAINER_INL_TMPL_DEF(OSG_CLASS,                  \
                                         OSG_TMPL_PARAM,             \
                                         OSG_CLASS_PTR)              \
    OSG_FC_TYPE_FUNCTIONS_INL_TMPL_DEF  (OSG_TMPL_PARAM, OSG_CLASS)  \
    OSG_FC_SIZE_FUNCTIONS_INL_TMPL_DEF  (OSG_TMPL_PARAM, OSG_CLASS)  \
    OSG_FC_CREATE_FUNCTIONS_INL_TMPL_DEF(OSG_TMPL_PARAM,             \
                                         OSG_CLASS,                  \
                                         OSG_CLASS_PTR)

#define OSG_FIELD_CONTAINER_ST_INL_TMPL_DEF(OSG_CLASS,                  \
                                            OSG_TMPL_PARAM,             \
                                            OSG_CLASS_PTR)              \
    OSG_FC_ST_TYPE_FUNCTIONS_INL_TMPL_DEF  (OSG_TMPL_PARAM, OSG_CLASS)  \
    OSG_FC_SIZE_FUNCTIONS_INL_TMPL_DEF     (OSG_TMPL_PARAM, OSG_CLASS)  \
    OSG_FC_CREATE_FUNCTIONS_INL_TMPL_DEF   (OSG_TMPL_PARAM,             \
                                            OSG_CLASS,                  \
                                            OSG_CLASS_PTR)

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

#define OSG_SFIELD_ACCESS_FUNCTIONS_DECL( OSG_FIELDTYPE, OSG_TYPE,	 	\
		OSG_NAME )														\
	inline OSG_FIELDTYPE * getSF##OSG_NAME( void );						\
	inline OSG_TYPE get##OSG_NAME( void ); 								\
	inline OSG_TYPE get##OSG_NAME( void ) const; 						\
	inline void set##OSG_NAME( const OSG_TYPE value );


#define OSG_SFIELD_ACCESS_FUNCTIONS_INL( OSG_CLASS, OSG_FIELDTYPE,  	\
		OSG_TYPE, OSG_NAME )											\
	inline OSG_FIELDTYPE * OSG_CLASS::getSF##OSG_NAME( void )			\
	{																	\
		return &_##OSG_NAME;											\
	}																	\
	inline OSG_TYPE OSG_CLASS::get##OSG_NAME(void)						\
	{																	\
		return _##OSG_NAME.getValue();									\
	}																	\
	inline OSG_TYPE OSG_CLASS::get##OSG_NAME(void) const				\
	{																	\
		return _##OSG_NAME.getValue();									\
	}																	\
	inline void OSG_CLASS::set##OSG_NAME( const OSG_TYPE val)			\
	{																	\
		_##OSG_NAME.setValue( val );									\
	}																	



// class pointer

typedef FieldContainer *FieldContainerP;

OSG_END_NAMESPACE

#include <OSGFieldContainer.inl>

#endif /* _OSGFIELDCONTAINER_H_ */
