/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
 *                                                                           *
 *                            www.opensg.org                                 *
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

#ifndef _OSGREFLEXIVECONTAINER_HPP_
#define _OSGREFLEXIVECONTAINER_HPP_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGReflexiveContainerType.h>
#include <OSGSupportTypes.h>

//#include <OSGTemplateDescCollector.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! ReflexiveContainer
//! \ingroup DataStoreLib

class OSG_SYSTEMLIB_DLLMAPPING ReflexiveContainer
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    static  const UInt32                       NextElemId   =    0;
    static  const BitVector                    NextElemMask = 0x00;

//    typedef       Val2Count<NextElemId>::Count NextElementCount;

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

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

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    //! prohibit default function (move to 'public' if needed) 
    void operator =(const ReflexiveContainer &source);

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

    static ReflexiveContainerType _type;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    ReflexiveContainer(void);
    ReflexiveContainer(const ReflexiveContainer &source);

    virtual ~ReflexiveContainer(void); 

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    /*------------------------- type information-----------------------------*/

    static ReflexiveContainerType &getClassType  (void);
    static UInt32                  getClassTypeId(void);

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*------------------------- type information-----------------------------*/
    
    virtual       ReflexiveContainerType &getReflexType(void);
    virtual const ReflexiveContainerType &getReflexType(void) const;

                  UInt32                  getTypeId    (void) const;
                  UInt16                  getGroupId   (void) const;

            const Char8                  *getTypeName  (void) const;

    /*------------------------------ size -----------------------------------*/

    virtual UInt32               getSize (void) const = 0;

    /*----------------------------- access ----------------------------------*/

            AnonObjectP          getElement(      UInt32 uiElementId);
            AnonObjectP          getElement(const Char8 *szElementName);

    /*------------------------------ edit -----------------------------------*/

    virtual void beginEdit(BitVector whichElement                 );
    virtual void endEdit  (BitVector whichElement                 );
    virtual void changed  (BitVector whichElement, ChangeMode from);
};

// Macros used to derive a new data store

#define OSG_RC_FIRST_ELEM_IDM_DECL(OSG_ELEMNAME)                              \
    static const UInt32     OSG_ELEMNAME##Id   = Inherited::NextElemId;       \
    static const BitVector  OSG_ELEMNAME##Mask = 1 << OSG_ELEMNAME##Id;       \
                                                                              \
    static const UInt32    FirstElemId   =        OSG_ELEMNAME##Id;           \
    static const BitVector FirstElemMask =        OSG_ELEMNAME##Mask;

#define OSG_RC_EMPTY_FIRST_IDM_DECL                                           \
    static  const UInt32 FirstElemId = Inherited::NextElemId;

#define OSG_RC_ELEM_IDM_DECL(OSG_ELEMNAME, OSG_PREV_ELEMNAME)                 \
    static const UInt32    OSG_ELEMNAME##Id   = OSG_PREV_ELEMNAME##Id + 1;    \
    static const BitVector OSG_ELEMNAME##Mask = 1 << OSG_ELEMNAME##Id;

#define OSG_RC_LAST_ELEM_IDM_DECL(OSG_PREV_ELEMNAME)                          \
    static const UInt32     NextElemId   = OSG_PREV_ELEMNAME##Id + 1;         \
    static const BitVector  NextElemMask = 1 << NextElemId;                   \
                                                                              \
    static  const    UInt32 LastElemId  = OSG_PREV_ELEMNAME##Id;

#define OSG_RC_EMPTY_LAST_ELEM_IDM_DECL(OSG_PREV_ELEMNAME)                    \
    static  const    UInt32 LastElemId  = OSG_PREV_ELEMNAME##Id;

#define OSG_RC_ELEM_IDM_DESC(OSG_ELEMNAME)                                    \
    OSG_ELEMNAME##Id, OSG_ELEMNAME##Mask

// Macros used to derive a new data store

#define OSG_RC_TMPL_FIRST_ELEM_IDM_DECL(OSG_ELEMNAME)                         \
    static const UInt32     OSG_ELEMNAME##Id   = Inherited::NextElemId;       \
    static const BitVector  OSG_ELEMNAME##Mask = 1 << OSG_ELEMNAME##Id;       \
                                                                              \
    static const UInt32    FirstElemId   =        OSG_ELEMNAME##Id;           \
    static const BitVector FirstElemMask =        OSG_ELEMNAME##Mask;

#define OSG_RC_TMPL_EMPTY_FIRST_IDM_DECL                                      \
    static  const UInt32 FirstElemId = Inherited::NextElemId;                 \

#define OSG_RC_TMPL_ELEM_IDM_DECL(OSG_ELEMNAME, OSG_PREV_ELEMNAME)            \
    static const UInt32    OSG_ELEMNAME##Id   = OSG_PREV_ELEMNAME##Id + 1;    \
    static const BitVector OSG_ELEMNAME##Mask = 1 << OSG_ELEMNAME##Id;

#define OSG_RC_TMPL_LAST_ELEM_IDM_DECL(OSG_PREV_ELEMNAME)                     \
    static const UInt32     NextElemId   = OSG_PREV_ELEMNAME##Id + 1;         \
    static const BitVector  NextElemMask = 1 << NextElemId;                   \
                                                                              \
    static  const    UInt32 LastElemId  = OSG_PREV_ELEMNAME##Id;

#define OSG_RC_TMPL_EMPTY_LAST_ELEM_IDM_DECL(OSG_PREV_ELEMNAME)               \
    static  const    UInt32 LastElemId  = OSG_PREV_ELEMNAME##Id;


/*---------------------------- get type -------------------------------------*/

#define OSG_RC_GET_TYPE_DECL                                                  \
    virtual       ReflexiveContainerType &getReflexType(void);                \
    virtual const ReflexiveContainerType &getReflexType(void) const;

#define OSG_RC_GET_TYPE_DEF(OSG_CLASS)                                        \
    ReflexiveContainerType &OSG_CLASS::getReflexType(void)                    \
    {                                                                         \
        return _type;                                                         \
    }                                                                         \
    const ReflexiveContainerType &OSG_CLASS::getReflexType(void) const        \
    {                                                                         \
        return _type;                                                         \
    }

#define OSG_RC_GET_TYPE_INL_TMPL_DEF(OSG_TMPL_PARAM, OSG_CLASS)               \
  template <class OSG_TMPL_PARAM> inline                                      \
  ReflexiveContainerType &OSG_CLASS<OSG_TMPL_PARAM>::getReflexType(void)      \
  {                                                                           \
      return _type;                                                           \
  }                                                                           \
  template <class OSG_TMPL_PARAM> inline                                      \
  const ReflexiveContainerType &                                              \
      OSG_CLASS<OSG_TMPL_PARAM>::getReflexType(void) const                    \
  {                                                                           \
      return _type;                                                           \
  }


#define OSG_RC_GET_TYPE_INL_TMPL_DEF2(OSG_TMPL_PARAM1_TYPE,                   \
                                      OSG_TMPL_PARAM1,                        \
                                      OSG_TMPL_PARAM2_TYPE,                   \
                                      OSG_TMPL_PARAM2,                        \
                                      OSG_CLASS)                              \
  template <OSG_TMPL_PARAM1_TYPE OSG_TMPL_PARAM1,                             \
            OSG_TMPL_PARAM2_TYPE OSG_TMPL_PARAM2> inline                      \
  ReflexiveContainerType &OSG_CLASS<OSG_TMPL_PARAM1,                          \
                                    OSG_TMPL_PARAM2>::getReflexType(void)     \
  {                                                                           \
      return _type;                                                           \
  }                                                                           \
  template <OSG_TMPL_PARAM1_TYPE OSG_TMPL_PARAM1,                             \
            OSG_TMPL_PARAM2_TYPE OSG_TMPL_PARAM2> inline                      \
  const ReflexiveContainerType &OSG_CLASS<                                    \
      OSG_TMPL_PARAM1,                                                        \
      OSG_TMPL_PARAM2>::getReflexType(void) const                             \
  {                                                                           \
      return _type;                                                           \
  }

/*---------------------------- get static type ------------------------------*/

#define OSG_RC_GET_STATIC_TYPE_DECL                                           \
    static ReflexiveContainerType & getClassType(void);           

#define OSG_RC_GET_STATIC_TYPE_DEF(OSG_CLASS)                                 \
    ReflexiveContainerType &OSG_CLASS::getClassType(void)                     \
    {                                                                         \
        return _type;                                                         \
    }

#define OSG_RC_GET_STATIC_TYPE_INL_TMPL_DEF(OSG_TMPL_PARAM,                   \
                                            OSG_CLASS)                        \
    template <class OSG_TMPL_PARAM> inline                                    \
    ReflexiveContainerType &OSG_CLASS<OSG_TMPL_PARAM>::getClassType(void)     \
    {                                                                         \
        return _type;                                                         \
    }

#define OSG_RC_GET_STATIC_TYPE_INL_TMPL_DEF2(OSG_TMPL_PARAM1_TYPE,            \
                                             OSG_TMPL_PARAM1,                 \
                                             OSG_TMPL_PARAM2_TYPE,            \
                                             OSG_TMPL_PARAM2,                 \
                                             OSG_CLASS)                       \
    template <OSG_TMPL_PARAM1_TYPE OSG_TMPL_PARAM1,                           \
              OSG_TMPL_PARAM2_TYPE OSG_TMPL_PARAM2> inline                    \
    ReflexiveContainerType &OSG_CLASS<OSG_TMPL_PARAM1,                        \
                                      OSG_TMPL_PARAM2>::getClassType(void)    \
    {                                                                         \
        return _type;                                                         \
    }

/*---------------------------- get static type id ---------------------------*/

#define OSG_RC_GET_STATIC_TYPE_ID_DECL                                        \
    static UInt32 getClassTypeId(void);             

#define OSG_RC_GET_STATIC_TYPE_ID_DEF(OSG_CLASS)                              \
    UInt32 OSG_CLASS::getClassTypeId(void)                                    \
    {                                                                         \
        return _type.getId();                                                 \
    }

#define OSG_RC_GET_STATIC_TYPE_ID_INL_TMPL_DEF(OSG_TMPL_PARAM,                \
                                               OSG_CLASS)                     \
    template <class OSG_TMPL_PARAM> inline                                    \
    UInt32 OSG_CLASS<OSG_TMPL_PARAM>::getClassTypeId(void)                    \
    {                                                                         \
        return _type.getId();                                                 \
    }

#define OSG_RC_GET_STATIC_TYPE_ID_INL_TMPL_DEF2(OSG_TMPL_PARAM1_TYPE,         \
                                                OSG_TMPL_PARAM1,              \
                                                OSG_TMPL_PARAM2_TYPE,         \
                                                OSG_TMPL_PARAM2,              \
                                                OSG_CLASS)                    \
    template <OSG_TMPL_PARAM1_TYPE OSG_TMPL_PARAM1,                           \
              OSG_TMPL_PARAM2_TYPE OSG_TMPL_PARAM2> inline                    \
    UInt32 OSG_CLASS<OSG_TMPL_PARAM1,                                         \
                     OSG_TMPL_PARAM2>::getClassTypeId(void)                   \
    {                                                                         \
        return _type.getId();                                                 \
    }

/*---------------------------- get static type id ---------------------------*/

#define OSG_RC_GET_STATIC_GROUP_ID_DECL                                       \
    static UInt32 getClassGroupId(void);             

#define OSG_RC_GET_STATIC_GROUP_ID_DEF(OSG_CLASS)                             \
    UInt32 OSG_CLASS::getClassGroupId(void)                                   \
    {                                                                         \
        return _type.getGroupId();                                            \
    }

#define OSG_RC_GET_STATIC_GROUP_ID_INL_TMPL_DEF(OSG_TMPL_PARAM,               \
                                                OSG_CLASS)                    \
    template <class OSG_TMPL_PARAM> inline                                    \
    UInt32 OSG_CLASS<OSG_TMPL_PARAM>::getClassGroupId(void)                   \
    {                                                                         \
        return _type.getGroupId();                                            \
    }

#define OSG_RC_GET_STATIC_GROUP_ID_INL_TMPL_DEF2(OSG_TMPL_PARAM1_TYPE,        \
                                                 OSG_TMPL_PARAM1,             \
                                                 OSG_TMPL_PARAM2_TYPE,        \
                                                 OSG_TMPL_PARAM2,             \
                                                 OSG_CLASS)                   \
    template <OSG_TMPL_PARAM1_TYPE OSG_TMPL_PARAM1,                           \
              OSG_TMPL_PARAM2_TYPE OSG_TMPL_PARAM2> inline                    \
    UInt32 OSG_CLASS<OSG_TMPL_PARAM1,                                         \
                     OSG_TMPL_PARAM2>::getClassGroupId(void)                  \
    {                                                                         \
        return _type.getGroupId();                                            \
    }

/*---------------------------- get type grouping ----------------------------*/

#define OSG_RC_TYPE_FUNCTIONS_DECL                                            \
    OSG_RC_GET_TYPE_DECL                                                      \
    OSG_RC_GET_STATIC_TYPE_DECL                                               \
    OSG_RC_GET_STATIC_TYPE_ID_DECL                                            \
    OSG_RC_GET_STATIC_GROUP_ID_DECL                     

#define OSG_RC_TYPE_FUNCTIONS_DEF(OSG_CLASS)                                  \
    OSG_RC_GET_TYPE_DEF           (OSG_CLASS)                                 \
    OSG_RC_GET_STATIC_TYPE_DEF    (OSG_CLASS)                                 \
    OSG_RC_GET_STATIC_TYPE_ID_DEF (OSG_CLASS)                                 \
    OSG_RC_GET_STATIC_GROUP_ID_DEF(OSG_CLASS)


#define OSG_RC_TYPE_FUNCTIONS_INL_TMPL_DEF(OSG_TMPL_PARAM, OSG_CLASS)         \
    OSG_RC_GET_TYPE_INL_TMPL_DEF           (OSG_TMPL_PARAM, OSG_CLASS)        \
    OSG_RC_GET_STATIC_TYPE_INL_TMPL_DEF    (OSG_TMPL_PARAM, OSG_CLASS)        \
    OSG_RC_GET_STATIC_TYPE_ID_INL_TMPL_DEF (OSG_TMPL_PARAM, OSG_CLASS)        \
    OSG_RC_GET_STATIC_GROUP_ID_INL_TMPL_DEF(OSG_TMPL_PARAM, OSG_CLASS)

#define OSG_RC_TYPE_FUNCTIONS_INL_TMPL_DEF2(OSG_TMPL_PARAM1_TYPE,             \
                                            OSG_TMPL_PARAM1,                  \
                                            OSG_TMPL_PARAM2_TYPE,             \
                                            OSG_TMPL_PARAM2,                  \
                                            OSG_CLASS)                        \
    OSG_RC_GET_TYPE_INL_TMPL_DEF2           (OSG_TMPL_PARAM1_TYPE,            \
                                             OSG_TMPL_PARAM1,                 \
                                             OSG_TMPL_PARAM2_TYPE,            \
                                             OSG_TMPL_PARAM2,                 \
                                             OSG_CLASS)                       \
    OSG_RC_GET_STATIC_TYPE_INL_TMPL_DEF2    (OSG_TMPL_PARAM1_TYPE,            \
                                             OSG_TMPL_PARAM1,                 \
                                             OSG_TMPL_PARAM2_TYPE,            \
                                             OSG_TMPL_PARAM2,                 \
                                             OSG_CLASS)                       \
    OSG_RC_GET_STATIC_TYPE_ID_INL_TMPL_DEF2 (OSG_TMPL_PARAM1_TYPE,            \
                                             OSG_TMPL_PARAM1,                 \
                                             OSG_TMPL_PARAM2_TYPE,            \
                                             OSG_TMPL_PARAM2,                 \
                                             OSG_CLASS)                       \
    OSG_RC_GET_STATIC_GROUP_ID_INL_TMPL_DEF2(OSG_TMPL_PARAM1_TYPE,            \
                                             OSG_TMPL_PARAM1,                 \
                                             OSG_TMPL_PARAM2_TYPE,            \
                                             OSG_TMPL_PARAM2,                 \
                                             OSG_CLASS)

/*---------------------------- create ---------------------------------------*/

#define OSG_RC_CREATE_DECL(OSG_CLASS_PTR)                                     \
    static OSG_CLASS_PTR create(void);

#define OSG_RC_CREATE_DEF(OSG_CLASS, OSG_CLASS_PTR)                           \
    OSG_CLASS::OSG_CLASS_PTR OSG_CLASS::create(void)                          \
    {                                                                         \
        OSG_CLASS_PTR fc;                                                     \
                                                                              \
        if(_type.getPrototype() != NULL)                                      \
            fc = dynamic_cast<OSG_CLASS_PTR>(                                 \
                     _type.getPrototype()->shallowCopy());                    \
                                                                              \
        return fc;                                                            \
    }

#define OSG_RC_CREATE_INL_TMPL_DEF(OSG_TMPL_PARAM,                          \
                                   OSG_CLASS,                               \
                                   OSG_CLASS_PTR)                           \
    template <class OSG_TMPL_PARAM> inline                                  \
    OSG_CLASS<OSG_TMPL_PARAM>::OSG_CLASS_PTR                                \
        OSG_CLASS<OSG_TMPL_PARAM>::create(void)                             \
    {                                                                       \
        OSG_CLASS_PTR fc;                                                   \
                                                                            \
        if(_type.getPrototype() != NULL)                                    \
            fc = dynamic_cast<OSG_CLASS_PTR>(                               \
                     _type.getPrototype()->shallowCopy());                  \
                                                                            \
        return fc;                                                          \
    }

#define OSG_RC_CREATE_INL_TMPL_DEF2(OSG_TMPL_PARAM1_TYPE,                     \
                                    OSG_TMPL_PARAM1,                          \
                                    OSG_TMPL_PARAM2_TYPE,                     \
                                    OSG_TMPL_PARAM2,                          \
                                    OSG_CLASS,                                \
                                    OSG_CLASS_PTR)                            \
    template <OSG_TMPL_PARAM1_TYPE OSG_TMPL_PARAM1,                           \
              OSG_TMPL_PARAM2_TYPE OSG_TMPL_PARAM2> inline                    \
    OSG_CLASS<OSG_TMPL_PARAM1, OSG_TMPL_PARAM2>::OSG_CLASS_PTR                \
        OSG_CLASS<OSG_TMPL_PARAM1, OSG_TMPL_PARAM2>::create(void)             \
    {                                                                         \
        OSG_CLASS_PTR fc;                                                     \
                                                                              \
        if(_type.getPrototype() != NULL)                                      \
            fc = dynamic_cast<OSG_CLASS_PTR>(                                 \
                     _type.getPrototype()->shallowCopy());                    \
                                                                              \
        return fc;                                                            \
    }

#define OSG_RC_CREATE_EMPTY_DECL(OSG_CLASS_PTR)                         \
    static OSG_CLASS_PTR createEmpty(void);

#define OSG_RC_CREATE_EMPTY_DEF(OSG_CLASS, OSG_CLASS_PTR)               \
    OSG_CLASS::OSG_CLASS_PTR OSG_CLASS::createEmpty(void)               \
    {                                                                   \
        return new OSG_CLASS;                                           \
    }

#define OSG_RC_CREATE_EMPTY_INL_TMPL_DEF(OSG_TMPL_PARAM,                \
                                         OSG_CLASS,                     \
                                         OSG_CLASS_PTR)                 \
    template <class OSG_TMPL_PARAM> inline                              \
    OSG_CLASS<OSG_TMPL_PARAM>::OSG_CLASS_PTR                            \
        OSG_CLASS<OSG_TMPL_PARAM>::createEmpty(void)                    \
    {                                                                   \
        return new OSG_CLASS;                                           \
    }

#define OSG_RC_CREATE_EMPTY_INL_TMPL_DEF2(OSG_TMPL_PARAM1_TYPE,         \
                                          OSG_TMPL_PARAM1,              \
                                          OSG_TMPL_PARAM2_TYPE,         \
                                          OSG_TMPL_PARAM2,              \
                                          OSG_CLASS,                    \
                                          OSG_CLASS_PTR)                \
    template <OSG_TMPL_PARAM1_TYPE OSG_TMPL_PARAM1,                     \
              OSG_TMPL_PARAM2_TYPE OSG_TMPL_PARAM2> inline              \
    OSG_CLASS<OSG_TMPL_PARAM1, OSG_TMPL_PARAM2>::OSG_CLASS_PTR          \
        OSG_CLASS<OSG_TMPL_PARAM1, OSG_TMPL_PARAM2>::createEmpty(void)  \
    {                                                                   \
        return new OSG_CLASS;                                           \
    }

/*---------------------------- create grouping ------------------------------*/

#define OSG_RC_CREATE_FUNCTIONS_DECL(OSG_CLASS_PTR)                     \
    OSG_RC_CREATE_DECL      (OSG_CLASS_PTR)                             \
    OSG_RC_CREATE_EMPTY_DECL(OSG_CLASS_PTR)

#define OSG_RC_CREATE_FUNCTIONS_DEF(OSG_CLASS, OSG_CLASS_PTR)           \
    OSG_RC_CREATE_DEF          (OSG_CLASS, OSG_CLASS_PTR)               \
    OSG_RC_CREATE_EMPTY_DEF    (OSG_CLASS, OSG_CLASS_PTR)

#define OSG_RC_CREATE_FUNCTIONS_INL_TMPL_DEF(OSG_TMPL_PARAM,            \
                                             OSG_CLASS,                 \
                                             OSG_CLASS_PTR)             \
    OSG_RC_CREATE_INL_TMPL_DEF      (OSG_TMPL_PARAM,                    \
                                     OSG_CLASS,                         \
                                     OSG_CLASS_PTR)                     \
    OSG_RC_CREATE_EMPTY_INL_TMPL_DEF(OSG_TMPL_PARAM,                    \
                                     OSG_CLASS,                         \
                                     OSG_CLASS_PTR)

#define OSG_RC_CREATE_FUNCTIONS_INL_TMPL_DEF2(OSG_TMPL_PARAM1_TYPE,     \
                                              OSG_TMPL_PARAM1,          \
                                              OSG_TMPL_PARAM2_TYPE,     \
                                              OSG_TMPL_PARAM2,          \
                                              OSG_CLASS,                \
                                              OSG_CLASS_PTR)            \
    OSG_RC_CREATE_INL_TMPL_DEF2      (OSG_TMPL_PARAM1_TYPE,             \
                                      OSG_TMPL_PARAM1,                  \
                                      OSG_TMPL_PARAM2_TYPE,             \
                                      OSG_TMPL_PARAM2,                  \
                                      OSG_CLASS,                        \
                                      OSG_CLASS_PTR)                    \
    OSG_RC_CREATE_EMPTY_INL_TMPL_DEF2(OSG_TMPL_PARAM1_TYPE,             \
                                      OSG_TMPL_PARAM1,                  \
                                      OSG_TMPL_PARAM2_TYPE,             \
                                      OSG_TMPL_PARAM2,                  \
                                      OSG_CLASS,                        \
                                      OSG_CLASS_PTR)

/*-------------------------- get size ---------------------------------------*/


#define OSG_RC_GET_SIZE_DECL                                           \
    virtual UInt32 getSize(void) const

#define OSG_RC_GET_SIZE_DEF(OSG_CLASS)                                 \
    UInt32 OSG_CLASS::getSize(void) const                              \
    {                                                                  \
        return sizeof(OSG_CLASS);                                      \
    }

#define OSG_RC_GET_SIZE_INL_TMPL_DEF(OSG_TMPL_PARAM, OSG_CLASS)        \
    template <class OSG_TMPL_PARAM> inline                             \
    UInt32 OSG_CLASS<OSG_TMPL_PARAM>::getSize(void) const              \
    {                                                                  \
        return sizeof(OSG_CLASS);                                      \
    }

#define OSG_RC_GET_SIZE_INL_TMPL_DEF2(OSG_TMPL_PARAM1_TYPE,            \
                                      OSG_TMPL_PARAM1,                 \
                                      OSG_TMPL_PARAM2_TYPE,            \
                                      OSG_TMPL_PARAM2,                 \
                                      OSG_CLASS)                       \
    template <OSG_TMPL_PARAM1_TYPE OSG_TMPL_PARAM1,                    \
              OSG_TMPL_PARAM2_TYPE OSG_TMPL_PARAM2> inline             \
    UInt32 OSG_CLASS<OSG_TMPL_PARAM1,                                  \
                     OSG_TMPL_PARAM2>::getSize(void) const             \
    {                                                                  \
        return sizeof(OSG_CLASS);                                      \
    }

#define OSG_RC_SIZE_FUNCTIONS_DECL                                     \
    OSG_RC_GET_SIZE_DECL

#define OSG_RC_SIZE_FUNCTIONS_DEF(OSG_CLASS)                           \
    OSG_RC_GET_SIZE_DEF(OSG_CLASS)

#define OSG_RC_SIZE_FUNCTIONS_INL_TMPL_DEF(OSG_TMPL_PARAM, OSG_CLASS)  \
    OSG_RC_GET_SIZE_INL_TMPL_DEF(OSG_TMPL_PARAM, OSG_CLASS)

#define OSG_RC_SIZE_FUNCTIONS_INL_TMPL_DEF2(OSG_TMPL_PARAM1_TYPE,      \
                                            OSG_TMPL_PARAM1,           \
                                            OSG_TMPL_PARAM2_TYPE,      \
                                            OSG_TMPL_PARAM2,           \
                                            OSG_CLASS)                 \
    OSG_RC_GET_SIZE_INL_TMPL_DEF2(OSG_TMPL_PARAM1_TYPE,                \
                                  OSG_TMPL_PARAM1,                     \
                                  OSG_TMPL_PARAM2_TYPE,                \
                                  OSG_TMPL_PARAM2,                     \
                                  OSG_CLASS)


/*------------------------ decl and def macros ------------------------------*/

#define OSG_REFLEXCONTAINER_DECL(OSG_CLASS_PTR)               \
    OSG_RC_TYPE_FUNCTIONS_DECL                                \
    OSG_RC_CREATE_FUNCTIONS_DECL(OSG_CLASS_PTR)               \
    OSG_RC_SIZE_FUNCTIONS_DECL

#define OSG_REFLEXCONTAINER_DEF(OSG_CLASS, OSG_CLASS_PTR)     \
    OSG_RC_TYPE_FUNCTIONS_DEF  (OSG_CLASS)                    \
    OSG_RC_CREATE_FUNCTIONS_DEF(OSG_CLASS, OSG_CLASS_PTR)     \
    OSG_RC_SIZE_FUNCTIONS_DEF  (OSG_CLASS)

/*--------------------- abstr decl and def macros --------------------------*/

#define OSG_ABSTR_REFLEXCONTAINER_DECL(OSG_CLASS_PTR)               \
    OSG_RC_TYPE_FUNCTIONS_DECL                                      \
    OSG_RC_SIZE_FUNCTIONS_DECL

#define OSG_ABSTR_REFLEXCONTAINER_DEF(OSG_CLASS, OSG_CLASS_PTR)     \
    OSG_RC_TYPE_FUNCTIONS_DEF  (OSG_CLASS)                          \
    OSG_RC_SIZE_FUNCTIONS_DEF  (OSG_CLASS)

/*------------------ template decl and def macros --------------------------*/

#define OSG_REFLEXCONTAINER_TMPL_DECL(OSG_CLASS_PTR)                 \
    OSG_RC_TYPE_FUNCTIONS_DECL                                       \
    OSG_RC_CREATE_FUNCTIONS_DECL(OSG_CLASS_PTR)                      \
    OSG_RC_SIZE_FUNCTIONS_DECL

#define OSG_REFLEXCONTAINER_INL_TMPL_DEF(OSG_CLASS,                  \
                                         OSG_TMPL_PARAM,             \
                                         OSG_CLASS_PTR)              \
    OSG_RC_TYPE_FUNCTIONS_INL_TMPL_DEF  (OSG_TMPL_PARAM, OSG_CLASS)  \
    OSG_RC_SIZE_FUNCTIONS_INL_TMPL_DEF  (OSG_TMPL_PARAM, OSG_CLASS)  \
    OSG_RC_CREATE_FUNCTIONS_INL_TMPL_DEF(OSG_TMPL_PARAM,             \
                                         OSG_CLASS,                  \
                                         OSG_CLASS_PTR)

#define OSG_REFLEXCONTAINER_INL_TMPL_DEF2(OSG_CLASS,                  \
                                          OSG_TMPL_PARAM1_TYPE,       \
                                          OSG_TMPL_PARAM1,            \
                                          OSG_TMPL_PARAM2_TYPE,       \
                                          OSG_TMPL_PARAM2,            \
                                          OSG_CLASS_PTR)              \
    OSG_RC_TYPE_FUNCTIONS_INL_TMPL_DEF2  (OSG_TMPL_PARAM1_TYPE,       \
                                          OSG_TMPL_PARAM1,            \
                                          OSG_TMPL_PARAM2_TYPE,       \
                                          OSG_TMPL_PARAM2,            \
                                          OSG_CLASS)                  \
    OSG_RC_SIZE_FUNCTIONS_INL_TMPL_DEF2  (OSG_TMPL_PARAM1_TYPE,       \
                                          OSG_TMPL_PARAM1,            \
                                          OSG_TMPL_PARAM2_TYPE,       \
                                          OSG_TMPL_PARAM2,            \
                                          OSG_CLASS)                  \
    OSG_RC_CREATE_FUNCTIONS_INL_TMPL_DEF2(OSG_TMPL_PARAM1_TYPE,       \
                                          OSG_TMPL_PARAM1,            \
                                          OSG_TMPL_PARAM2_TYPE,       \
                                          OSG_TMPL_PARAM2,            \
                                          OSG_CLASS,                  \
                                          OSG_CLASS_PTR)

/*---------------abstr template decl and def macros ------------------------*/

#define OSG_ABSTR_REFLEXCONTAINER_TMPL_DECL(OSG_CLASS_PTR)           \
    OSG_RC_TYPE_FUNCTIONS_DECL                                       \
    OSG_RC_SIZE_FUNCTIONS_DECL

#define OSG_ABSTR_REFLEXCONTAINER_INL_TMPL_DEF(OSG_CLASS,            \
                                               OSG_TMPL_PARAM,       \
                                               OSG_CLASS_PTR)        \
    OSG_RC_TYPE_FUNCTIONS_INL_TMPL_DEF  (OSG_TMPL_PARAM, OSG_CLASS)  \
    OSG_RC_SIZE_FUNCTIONS_INL_TMPL_DEF  (OSG_TMPL_PARAM, OSG_CLASS)

#define OSG_ABSTR_REFLEXCONTAINER_INL_TMPL_DEF2(OSG_CLASS,            \
                                                OSG_TMPL_PARAM1_TYPE, \
                                                OSG_TMPL_PARAM1,      \
                                                OSG_TMPL_PARAM2_TYPE, \
                                                OSG_TMPL_PARAM2,      \
                                                OSG_CLASS_PTR)        \
    OSG_RC_TYPE_FUNCTIONS_INL_TMPL_DEF2  (OSG_TMPL_PARAM1_TYPE,       \
                                          OSG_TMPL_PARAM1,            \
                                          OSG_TMPL_PARAM2_TYPE,       \
                                          OSG_TMPL_PARAM2,            \
                                          OSG_CLASS)                  \
    OSG_RC_SIZE_FUNCTIONS_INL_TMPL_DEF2  (OSG_TMPL_PARAM1_TYPE,       \
                                          OSG_TMPL_PARAM1,            \
                                          OSG_TMPL_PARAM2_TYPE,       \
                                          OSG_TMPL_PARAM2,            \
                                          OSG_CLASS)

OSG_END_NAMESPACE

#define OSGREFLEXIVECONTAINER_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGREFLEXIVECONTAINER_HPP_ */
