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


#ifndef _OSGFIELDCONTAINER_H_
#define _OSGFIELDCONTAINER_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

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

class OSGField;
class OSGFieldContainerPtr;

namespace OSGFieldBits
{
    const OSGBitVector OSGAllFields = 0xFFFFFFFF;

    const OSGBitVector OSGField0    = 0x00000001;
    const OSGBitVector OSGField1    = 0x00000002;
    const OSGBitVector OSGField2    = 0x00000004;
    const OSGBitVector OSGField3    = 0x00000008;

    const OSGBitVector OSGField4    = 0x00000010;
    const OSGBitVector OSGField5    = 0x00000020;
    const OSGBitVector OSGField6    = 0x00000040;
    const OSGBitVector OSGField7    = 0x00000080;

    const OSGBitVector OSGField8    = 0x00000100;
    const OSGBitVector OSGField9    = 0x00000200;
    const OSGBitVector OSGField10   = 0x00000400;
    const OSGBitVector OSGField11   = 0x00000800;

    const OSGBitVector OSGField12   = 0x00001000;
    const OSGBitVector OSGField13   = 0x00002000;
    const OSGBitVector OSGField14   = 0x00004000;
    const OSGBitVector OSGField15   = 0x00008000;

    const OSGBitVector OSGField16   = 0x00010000;
    const OSGBitVector OSGField17   = 0x00020000;
    const OSGBitVector OSGField18   = 0x00040000;
    const OSGBitVector OSGField19   = 0x00080000;

    const OSGBitVector OSGField20   = 0x00100000;
    const OSGBitVector OSGField21   = 0x00200000;
    const OSGBitVector OSGField22   = 0x00400000;
    const OSGBitVector OSGField23   = 0x00800000;

    const OSGBitVector OSGField24   = 0x01000000;
    const OSGBitVector OSGField25   = 0x02000000;
    const OSGBitVector OSGField26   = 0x04000000;
    const OSGBitVector OSGField27   = 0x08000000;

    const OSGBitVector OSGField28   = 0x10000000;
    const OSGBitVector OSGField29   = 0x20000000;
    const OSGBitVector OSGField30   = 0x40000000;
    const OSGBitVector OSGField31   = 0x80000000;
}

void osgAddRefCP   (OSGFieldContainerPtr &objectP);
void osgSubRefCP   (OSGFieldContainerPtr &objectP);
void osgBeginEditCP(OSGFieldContainerPtr &objectP, 
                    OSGBitVector          whichField = 
                                                   OSGFieldBits::OSGAllFields);

void osgEndEditCP  (OSGFieldContainerPtr &objectP, 
                    OSGBitVector          whichField = 
                                                   OSGFieldBits::OSGAllFields);
void osgChangedCP  (OSGFieldContainerPtr &objectP, 
                    OSGBitVector          whichField = 
                                                   OSGFieldBits::OSGAllFields);

void osgEndEditNoChangedCP  (OSGFieldContainerPtr &objectP, 
                             OSGBitVector          whichField = 
                                                   OSGFieldBits::OSGAllFields);

void osgSetRefdCP  (OSGFieldContainerPtr &objectP,
                    OSGFieldContainerPtr &newObjectP);

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup baselib
 *  \brief Brief
 *
 *  detailed
 */


/** \defgroup FieldContainerLib FieldContainerLib
 *  \brief This lib contains all field container elements like NodeCore's,
 *  Attachments.
 */


class OSGFieldContainer 
{
  public:

    static const OSGUInt32    OSGNextFieldId   =    1;
    static const OSGBitVector OSGNextFieldMask = 0x01;

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    enum OSGChangeMode
    {
        OSGExternal = 0x01,
        OSGSync     = 0x02,
        OSGChild    = 0x03
    };

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /** Destructor */
    virtual ~OSGFieldContainer (void);

    /**  */
    // unsigned getFieldCount (void);
        
    /*------------------------- type information-----------------------------*/
    
    virtual const OSGFieldContainerType & getType       (void) const 
    { 
        return _type; 
    }
    static const OSGFieldContainerType & getStaticType (void)
    { 
        return _type; 
    }
    static OSGUInt32 getStaticTypeID (void)
    { 
        return _type.getId();
    }

    OSGUInt32 getTypeID(void) const { return getType().getId(); }

    const char *getTypeName(void) const { return getType().getName(); }


    OSGUInt16 getGroupID(void) const { return getType().getGroupId(); }

    /*------------------------------ size -----------------------------------*/

    virtual OSGUInt32 getSize(void) const = 0;

    /*----------------------------- access ----------------------------------*/

    OSGField *getField(const char *fieldName);

    /*----------------------------- clone ----------------------------------*/

    virtual OSGFieldContainerPtr clone(void) = 0;

    /*----------------------------- dump ----------------------------------*/

    virtual void dump(void) const = 0;
    
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

    static OSGFieldContainerType _type;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /** Default Constructor */
    OSGFieldContainer (void);

    /** Copy Constructor */
    OSGFieldContainer (const OSGFieldContainer &obj);

    template <class OSGObjectPtrT>
    static void newPtr(      
                       OSGObjectPtrT                   &result, 
        const typename OSGObjectPtrT::OSGContainerType *prototypeP)
    {
        typedef typename OSGObjectPtrT::OSGContainerType OSGObjectType;

        OSGUInt8 *pTmp;

        result._containerSize = sizeof(OSGObjectType);

        pTmp        = 
            (OSGUInt8 *) operator new(
                sizeof(OSGInt32)      + // ReferenceCount
                sizeof(OSGUInt32)     + // ContainerId
                sizeof(OSGObjectType) * OSGThreadManager::getNumAspects());

        *((OSGInt32 *) pTmp) = 0;
        
        pTmp += sizeof(OSGInt32);

        *((OSGUInt32 *) pTmp) = 
            OSGFieldContainerFactory::registerFieldContainer(result);

        pTmp += sizeof(OSGUInt32);

        result._storeP = pTmp;

        for(OSGUInt32 i = 0; i < OSGThreadManager::getNumAspects(); i++)
        {
            pTmp = (OSGUInt8 *) new (pTmp) OSGObjectType(*prototypeP);

            pTmp += sizeof(OSGObjectType);
        }

#ifdef OSG_DEBUG_TYPED_FCPTR
        result.updateTypedStore();
#endif
        
    }

    template <class OSGObjectPtrT>
    static void newPtr(OSGObjectPtrT &result)
    {
        typedef typename OSGObjectPtrT::OSGContainerType OSGObjectType;

        OSGUInt8 *pTmp;

        result._containerSize = sizeof(OSGObjectType);

        pTmp        =             
            (OSGUInt8 *) operator new(
                sizeof(OSGInt32)      + // ReferenceCount
                sizeof(OSGUInt32)     + // ContainerId
                sizeof(OSGObjectType) * OSGThreadManager::getNumAspects());

        *((OSGInt32 *) pTmp) = 0;
        
        pTmp  += sizeof(OSGInt32);

        *((OSGUInt32 *) pTmp) = 
            OSGFieldContainerFactory::registerFieldContainer(result);

        pTmp += sizeof(OSGUInt32);
        
        result._storeP = pTmp;

        for(OSGUInt32 i = 0; i < OSGThreadManager::getNumAspects(); i++)
        {
            pTmp = (OSGUInt8 *) new (pTmp) OSGObjectType();
            
            pTmp += sizeof(OSGObjectType);
        }

#ifdef OSG_DEBUG_TYPED_FCPTR
        result.updateTypedStore();
#endif
    }

    template <class T>
    T getPtr(const typename T::OSGContainerType &object)
    {
        T returnValue(object); 
        return returnValue; 
    }

    template <class OSGFieldTypeT>
    void beginEdit(const OSGBitVector             &,
                         OSGSField<OSGFieldTypeT> &fieldR)
    {
        fieldR.beginEdit();
    }

    template <class OSGFieldTypeT>
    void beginEdit(const OSGBitVector             &,
                         OSGMField<OSGFieldTypeT> &fieldR)
    {
        fieldR.beginEdit();
    }

    template <class OSGFieldTypeT>
    void endEdit(const OSGBitVector             &whichField,
                       OSGSField<OSGFieldTypeT> &)
    {
        OSGFieldContainerPtr tmpPtr(*this);
        osgEndEditCP(tmpPtr, whichField);
    }

    template <class OSGFieldTypeT>
    void endEdit(const OSGBitVector             &whichField,
                       OSGMField<OSGFieldTypeT> &)
    {
        OSGFieldContainerPtr tmpPtr(*this);
        osgEndEditCP(tmpPtr, whichField);
    }


    virtual void changed(OSGBitVector whichField, OSGChangeMode from);

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

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    friend class OSGFieldContainerPtr;

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

};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

#define OSG_FC_TMPL_VAR_INL 

// Macros used to derive a new fieldcontainer

#define OSG_FC_FIRST_FIELD_IDM_DECL(OSG_FIELDNAME)                            \
    static const OSGUInt32    OSG_FIELDNAME##Id;                              \
    static const OSGBitVector OSG_FIELDNAME##Mask;

#define OSG_FC_FIRST_FIELD_IDM_DEF(OSG_CLASS, OSG_FIELDNAME)                  \
const OSGUInt32    OSG_CLASS::OSG_FIELDNAME##Id   =                           \
    Inherited::OSGNextFieldId;                                                \
const OSGBitVector OSG_CLASS::OSG_FIELDNAME##Mask =                           \
    Inherited::OSGNextFieldMask;

#define OSG_FC_FIRST_FIELD_IDM_INL_TMPL_DEF(OSG_CLASS,                        \
                                            OSG_TMPL_PARAM,                   \
                                            OSG_FIELDNAME)                    \
template <class OSG_TMPL_PARAM> OSG_FC_TMPL_VAR_INL                           \
const OSGUInt32    OSG_CLASS<OSG_TMPL_PARAM>::OSG_FIELDNAME##Id    =          \
    Inherited::OSGNextFieldId;                                                \
template <class OSG_TMPL_PARAM> OSG_FC_TMPL_VAR_INL                           \
const OSGBitVector OSG_CLASS<OSG_TMPL_PARAM>::OSG_FIELDNAME##Mask  =          \
    Inherited::OSGNextFieldMask;


#define OSG_FC_FIELD_IDM_DECL(OSG_FIELDNAME)                                  \
    static const OSGUInt32    OSG_FIELDNAME##Id;                              \
    static const OSGBitVector OSG_FIELDNAME##Mask;

#define OSG_FC_FIELD_IDM_DEF(OSG_CLASS, OSG_FIELDNAME, OSG_PREV_FIELDNAME)    \
const OSGUInt32    OSG_CLASS::OSG_FIELDNAME##Id    =                          \
    OSG_PREV_FIELDNAME##Id + 1;                                               \
const OSGBitVector OSG_CLASS::OSG_FIELDNAME##Mask  =                          \
    OSG_PREV_FIELDNAME##Mask << 1;

#define OSG_FC_FIELD_IDM_INL_TMPL_DEF(OSG_CLASS,                              \
                                      OSG_TMPL_PARAM,                         \
                                      OSG_FIELDNAME,                          \
                                      OSG_PREV_FIELDNAME)                     \
template <class OSG_TMPL_PARAM> OSG_FC_TMPL_VAR_INL                           \
const OSGUInt32    OSG_CLASS<OSG_TMPL_PARAM>::OSG_FIELDNAME##Id    =          \
    OSG_PREV_FIELDNAME##Id + 1;                                               \
template <class OSG_TMPL_PARAM> OSG_FC_TMPL_VAR_INL                           \
const OSGBitVector OSG_CLASS<OSG_TMPL_PARAM>::OSG_FIELDNAME##Mask  =          \
    OSG_PREV_FIELDNAME##Mask << 1;


#define OSG_FC_LAST_FIELD_IDM_DECL                                            \
    static const OSGUInt32    OSGNextFieldId;                                 \
    static const OSGBitVector OSGNextFieldMask;

#define OSG_FC_LAST_FIELD_IDM_DEF(OSG_CLASS, OSG_PREV_FIELDNAME)              \
const OSGUInt32    OSG_CLASS::OSGNextFieldId   =                              \
    OSG_PREV_FIELDNAME##Id + 1;                                               \
const OSGBitVector OSG_CLASS::OSGNextFieldMask =                              \
    OSG_PREV_FIELDNAME##Mask << 1;

#define OSG_FC_LAST_FIELD_IDM_INL_TMPL_DEF(OSG_CLASS,                         \
                                           OSG_TMPL_PARAM,                    \
                                           OSG_PREV_FIELDNAME)                \
template <class OSG_TMPL_PARAM> OSG_FC_TMPL_VAR_INL                           \
const OSGUInt32    OSG_CLASS<OSG_TMPL_PARAM>::OSGNextFieldId   =              \
    OSG_PREV_FIELDNAME##Id + 1;                                               \
template <class OSG_TMPL_PARAM> OSG_FC_TMPL_VAR_INL                           \
const OSGBitVector OSG_CLASS<OSG_TMPL_PARAM>::OSGNextFieldMask =              \
    OSG_PREV_FIELDNAME##Mask << 1;

#define OSG_FC_FIELD_IDM_DESC(OSG_FIELDNAME)                                  \
    OSG_FIELDNAME##Id, OSG_FIELDNAME##Mask

/*---------------------------- get type -------------------------------------*/

#define OSG_FC_GET_TYPE_DECL                                                  \
    virtual const OSGFieldContainerType &getType(void) const;

#define OSG_FC_GET_TYPE_DEF(OSG_CLASS)                                        \
    const OSGFieldContainerType &OSG_CLASS::getType(void) const               \
    {                                                                         \
        return _type;                                                         \
    }

#define OSG_FC_GET_TYPE_INL_TMPL_DEF(OSG_TMPL_PARAM, OSG_CLASS)               \
  template <class OSG_TMPL_PARAM> inline                                      \
  const OSGFieldContainerType &OSG_CLASS<OSG_TMPL_PARAM>::getType(void) const \
  {                                                                           \
      return _type;                                                           \
  }


#define OSG_FC_GET_STATIC_TYPE_DECL                                           \
    static OSGFieldContainerType & getStaticType(void);           

#define OSG_FC_GET_STATIC_TYPE_INL_DEF(OSG_CLASS)                             \
    inline                                                                    \
    OSGFieldContainerType &OSG_CLASS::getStaticType(void)                     \
    {                                                                         \
        return _type;                                                         \
    }

#define OSG_FC_GET_STATIC_TYPE_INL_TMPL_DEF(OSG_TMPL_PARAM,                   \
                                            OSG_CLASS)                        \
    template <class OSG_TMPL_PARAM> inline                                    \
    OSGFieldContainerType &OSG_CLASS<OSG_TMPL_PARAM>::getStaticType(void)     \
    {                                                                         \
        return _type;                                                         \
    }

#define OSG_FC_GET_STATIC_TYPE_ID_DECL                                        \
    static OSGUInt32 getStaticTypeID(void);             

#define OSG_FC_GET_STATIC_TYPE_ID_INL_DEF(OSG_CLASS)                          \
    inline                                                                    \
    OSGUInt32 OSG_CLASS::getStaticTypeID(void)                                \
    {                                                                         \
        return _type.getId();                                                 \
    }

#define OSG_FC_GET_STATIC_TYPE_ID_INL_TMPL_DEF(OSG_TMPL_PARAM,                \
                                               OSG_CLASS)                     \
    template <class OSG_TMPL_PARAM> inline                                    \
    OSGUInt32 OSG_CLASS<OSG_TMPL_PARAM>::getStaticTypeID(void)                \
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


/*---------------------------- create ---------------------------------------*/

#define OSG_FC_CREATE_DECL(OSG_CLASS_PTR)                               \
    static OSG_CLASS_PTR create(void);

#ifdef OSG_HAS_MEMBER_TEMPLATE_RETURNVALUES
#define OSG_FC_CREATE_INL_DEF(OSG_CLASS, OSG_CLASS_PTR)                 \
    inline                                                              \
    OSG_CLASS_PTR OSG_CLASS::create(void)                               \
    {                                                                   \
        OSG_CLASS_PTR fc;                                               \
                                                                        \
        if(_type.getPrototype() != OSGNullFC)                           \
            fc = _type.getPrototype()->clone().dcast<OSG_CLASS_PTR>();  \
                                                                        \
        return fc;                                                      \
    }

#define OSG_FC_CREATE_INL_TMPL_DEF(OSG_TMPL_PARAM,                      \
                                   OSG_CLASS,                           \
                                   OSG_CLASS_PTR)                       \
    template <class OSG_TMPL_PARAM> inline                              \
    OSG_CLASS<OSG_TMPL_PARAM>::OSG_CLASS_PTR                            \
        OSG_CLASS<OSG_TMPL_PARAM>::create(void)                         \
    {                                                                   \
        OSG_CLASS_PTR fc;                                               \
                                                                        \
        if(_type.getPrototype() != OSGNullFC)                           \
            fc = _type.getPrototype()->clone().dcast<OSG_CLASS_PTR>();  \
                                                                        \
        return fc;                                                      \
    }
#else
#define OSG_FC_CREATE_INL_DEF(OSG_CLASS, OSG_CLASS_PTR)                 \
    inline                                                              \
    OSG_CLASS_PTR OSG_CLASS::create(void)                               \
    {                                                                   \
        OSG_CLASS_PTR fc;                                               \
                                                                        \
        if(_type.getPrototype() != NULL)                                \
            _type.getPrototype()->clone().dcast(fc);                    \
                                                                        \
        return fc;                                                      \
}

#define OSG_FC_CREATE_INL_TMPL_DEF(OSG_TMPL_PARAM,                      \
                                   OSG_CLASS,                           \
                                   OSG_CLASS_PTR)                       \
    template <class OSG_TMPL_PARAM> inline                              \
    OSG_CLASS<OSG_TMPL_PARAM>::OSG_CLASS_PTR                            \
        OSG_CLASS<OSG_TMPL_PARAM>::create(void)                         \
    {                                                                   \
        OSG_CLASS_PTR fc;                                               \
                                                                        \
        if(_type.getPrototype() != NULL)                                \
            _type.getPrototype()->clone().dcast(fc);                    \
                                                                        \
        return fc;                                                      \
}
#endif


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


#define OSG_FC_CLONE_DECL                                               \
    virtual OSGFieldContainerPtr clone(void);

#define OSG_FC_CLONE_DEF(OSG_CLASS, OSG_CLASS_PTR)                      \
    OSGFieldContainerPtr OSG_CLASS::clone(void)                         \
    {                                                                   \
        OSG_CLASS_PTR returnValue;                                      \
                                                                        \
        newPtr(returnValue, this);                                      \
                                                                        \
        return returnValue;                                             \
    } 

#define OSG_FC_CLONE_INL_TMPL_DEF(OSG_TMPL_PARAM,                       \
                                  OSG_CLASS,                            \
                                  OSG_CLASS_PTR)                        \
    template <class OSG_TMPL_PARAM>                                     \
    OSGFieldContainerPtr OSG_CLASS<OSG_TMPL_PARAM>::clone(void)         \
    {                                                                   \
        OSG_CLASS_PTR returnValue;                                      \
                                                                        \
        newPtr(returnValue, this);                                      \
                                                                        \
        return returnValue;                                             \
    } 


#define OSG_FC_CREATE_FUNCTIONS_DECL(OSG_CLASS_PTR)                     \
    OSG_FC_CREATE_DECL      (OSG_CLASS_PTR)                             \
    OSG_FC_CREATE_EMPTY_DECL(OSG_CLASS_PTR)                             \
    OSG_FC_CLONE_DECL

#define OSG_FC_CREATE_FUNCTIONS_DEF(OSG_CLASS, OSG_CLASS_PTR)           \
    OSG_FC_CLONE_DEF(OSG_CLASS, OSG_CLASS_PTR)

#define OSG_FC_CREATE_FUNCTIONS_INL_DEF(OSG_CLASS, OSG_CLASS_PTR)       \
    OSG_FC_CREATE_INL_DEF      (OSG_CLASS, OSG_CLASS_PTR)               \
    OSG_FC_CREATE_EMPTY_INL_DEF(OSG_CLASS, OSG_CLASS_PTR)

#define OSG_FC_CREATE_FUNCTIONS_INL_TMPL_DEF(OSG_TMPL_PARAM,            \
                                             OSG_CLASS,                 \
                                             OSG_CLASS_PTR)             \
    OSG_FC_CLONE_INL_TMPL_DEF       (OSG_TMPL_PARAM,                    \
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
    virtual OSGUInt32 getSize(void) const;

#define OSG_FC_GET_SIZE_DEF(OSG_CLASS)                                 \
    OSGUInt32 OSG_CLASS::getSize(void) const                           \
    {                                                                  \
        return sizeof(OSG_CLASS);                                      \
    }

#define OSG_FC_GET_SIZE_INL_TMPL_DEF(OSG_TMPL_PARAM, OSG_CLASS)        \
    template <class OSG_TMPL_PARAM> inline                             \
    OSGUInt32 OSG_CLASS<OSG_TMPL_PARAM>::getSize(void) const           \
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

/*---------------abstr template decl and def macros ------------------------*/

#define OSG_ABSTR_FIELD_CONTAINER_TMPL_DECL(OSG_CLASS_PTR)           \
    OSG_FC_TYPE_FUNCTIONS_DECL                                       \
    OSG_FC_SIZE_FUNCTIONS_DECL

#define OSG_ABSTR_FIELD_CONTAINER_INL_TMPL_DEF(OSG_CLASS,            \
                                               OSG_TMPL_PARAM,       \
                                               OSG_CLASS_PTR)        \
    OSG_FC_TYPE_FUNCTIONS_INL_TMPL_DEF  (OSG_TMPL_PARAM, OSG_CLASS)  \
    OSG_FC_SIZE_FUNCTIONS_INL_TMPL_DEF  (OSG_TMPL_PARAM, OSG_CLASS)


// class pointer

typedef OSGFieldContainer *OSGFieldContainerP;

OSG_END_NAMESPACE

#include <OSGFieldContainer.inl>

#endif // _OSGFIELDCONTAINER_H_
