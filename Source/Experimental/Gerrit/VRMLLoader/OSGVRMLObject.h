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

#ifndef _OSGVRMLOBJECT_HPP_
#define _OSGVRMLOBJECT_HPP_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGVRMLBase.h>
#include <OSGReflexiveContainer.h>
#include <OSGRefCountMixin.h>
#include <OSGVRMLObjectType.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class Field;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

typedef RefCountMixin<ReflexiveContainer> RCReflexiveContainer;

#ifndef OSG_COMPILEVRMLOBJECTINST

#ifdef __sgi

#pragma do_not_instantiate RefCountMixin<ReflexiveContainer>

#else

#if !defined(__hpux) && !defined(OSG_LINUX_ICC)
extern template class OSG_VRML_DLLMAPPING RefCountMixin<ReflexiveContainer>;
#endif

#endif

#endif

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! VRMLObject
//! \ingroup VRMLBaseLib

class OSG_VRML_DLLMAPPING VRMLObject : public RCReflexiveContainer
{
  private:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef RCReflexiveContainer Inherited;

  public:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef       VRMLObject *Ptr;
    typedef const VRMLObject *ConstPtr;

    typedef       VRMLObject  ObjectType;

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   enums                                                               
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

    static VRMLObjectType _type;

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
    void operator =(const VRMLObject &source);

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

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    UInt32 _uiId;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    VRMLObject(void);
    VRMLObject(const VRMLObject &source);

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static VRMLObjectType &getClassType  (void);
    static UInt32          getClassTypeId(void);

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    virtual ~VRMLObject(void); 

    /*------------------------- type information-----------------------------*/
    
    virtual       ReflexiveContainerType &getReflexType(void);
    virtual const ReflexiveContainerType &getReflexType(void) const;

    virtual       VRMLObjectType         &getType      (void);
    virtual const VRMLObjectType         &getType      (void) const;

                  UInt32                  getId        (void) const;

    /*----------------------------- access ----------------------------------*/

            Field *getElement(      UInt32  uiElementId  );
            Field *getElement(const Char8  *szElementName);

    virtual void   setElement(      Field  *pField, 
                                    UInt32  uiElementId  );
    
    /*----------------------------- clone ----------------------------------*/

    virtual VRMLObject *shallowCopy(void) = 0;
};

#define OSG_VO_TMPL_VAR_INL 

/*---------------------------- get type -------------------------------------*/

#define OSG_VO_GET_TYPE_DECL                                                  \
    virtual       VRMLObjectType &getType(void);                              \
    virtual const VRMLObjectType &getType(void) const;

#define OSG_VO_GET_TYPE_DEF(OSG_CLASS)                                        \
    VRMLObjectType &OSG_CLASS::getType(void)                                  \
    {                                                                         \
        return _type;                                                         \
    }                                                                         \
    const VRMLObjectType &OSG_CLASS::getType(void) const                      \
    {                                                                         \
        return _type;                                                         \
    }

#define OSG_VO_GET_TYPE_INL_TMPL_DEF(OSG_TMPL_PARAM, OSG_CLASS)               \
  template <class OSG_TMPL_PARAM> inline                                      \
  VRMLObjectType &OSG_CLASS<OSG_TMPL_PARAM>::getType(void)                    \
  {                                                                           \
      return _type;                                                           \
  }                                                                           \
  template <class OSG_TMPL_PARAM> inline                                      \
  const VRMLObjectType &OSG_CLASS<OSG_TMPL_PARAM>::getType(void) const        \
  {                                                                           \
      return _type;                                                           \
  }


#define OSG_VO_GET_TYPE_INL_TMPL_DEF2(OSG_TMPL_PARAM1_TYPE,                   \
                                      OSG_TMPL_PARAM1,                        \
                                      OSG_TMPL_PARAM2_TYPE,                   \
                                      OSG_TMPL_PARAM2,                        \
                                      OSG_CLASS)                              \
  template <OSG_TMPL_PARAM1_TYPE OSG_TMPL_PARAM1,                             \
            OSG_TMPL_PARAM2_TYPE OSG_TMPL_PARAM2> inline                      \
        VRMLObjectType &OSG_CLASS<OSG_TMPL_PARAM1,                            \
                                  OSG_TMPL_PARAM2>::getType(void)             \
  {                                                                           \
      return _type;                                                           \
  }                                                                           \
  template <OSG_TMPL_PARAM1_TYPE OSG_TMPL_PARAM1,                             \
            OSG_TMPL_PARAM2_TYPE OSG_TMPL_PARAM2> inline                      \
  const VRMLObjectType &OSG_CLASS<OSG_TMPL_PARAM1,                            \
                                  OSG_TMPL_PARAM2>::getType(void) const       \
  {                                                                           \
      return _type;                                                           \
  }

/*---------------------------- get static type ------------------------------*/

#define OSG_VO_GET_STATIC_TYPE_DECL                                           \
    static VRMLObjectType & getClassType(void);           

#define OSG_VO_GET_STATIC_TYPE_DEF(OSG_CLASS)                                 \
    VRMLObjectType &OSG_CLASS::getClassType(void)                             \
    {                                                                         \
        return _type;                                                         \
    }

#define OSG_VO_GET_STATIC_TYPE_INL_TMPL_DEF(OSG_TMPL_PARAM,                   \
                                            OSG_CLASS)                        \
    template <class OSG_TMPL_PARAM> inline                                    \
    VRMLObjectType &OSG_CLASS<OSG_TMPL_PARAM>::getClassType(void)             \
    {                                                                         \
        return _type;                                                         \
    }

#define OSG_VO_GET_STATIC_TYPE_INL_TMPL_DEF2(OSG_TMPL_PARAM1_TYPE,            \
                                             OSG_TMPL_PARAM1,                 \
                                             OSG_TMPL_PARAM2_TYPE,            \
                                             OSG_TMPL_PARAM2,                 \
                                             OSG_CLASS)                       \
    template <OSG_TMPL_PARAM1_TYPE OSG_TMPL_PARAM1,                           \
              OSG_TMPL_PARAM2_TYPE OSG_TMPL_PARAM2> inline                    \
    VRMLObjectType &OSG_CLASS<OSG_TMPL_PARAM1,                                \
                              OSG_TMPL_PARAM2>::getClassType(void)            \
    {                                                                         \
        return _type;                                                         \
    }

/*---------------------------- get type grouping ----------------------------*/

#define OSG_VO_TYPE_FUNCTIONS_DECL                                            \
    OSG_RC_GET_TYPE_DECL                                                      \
    OSG_VO_GET_TYPE_DECL                                                      \
    OSG_VO_GET_STATIC_TYPE_DECL                                               \
    OSG_RC_GET_STATIC_TYPE_ID_DECL                                            \
    OSG_RC_GET_STATIC_GROUP_ID_DECL

#define OSG_VO_TYPE_FUNCTIONS_DEF(OSG_CLASS)                                  \
    OSG_RC_GET_TYPE_DEF           (OSG_CLASS)                                 \
    OSG_VO_GET_TYPE_DEF           (OSG_CLASS)                                 \
    OSG_VO_GET_STATIC_TYPE_DEF    (OSG_CLASS)                                 \
    OSG_RC_GET_STATIC_TYPE_ID_DEF (OSG_CLASS)                                 \
    OSG_RC_GET_STATIC_GROUP_ID_DEF(OSG_CLASS)


#define OSG_VO_TYPE_FUNCTIONS_INL_TMPL_DEF(OSG_TMPL_PARAM, OSG_CLASS)         \
    OSG_RC_GET_TYPE_INL_TMPL_DEF          (OSG_TMPL_PARAM, OSG_CLASS)         \
    OSG_VO_GET_TYPE_INL_TMPL_DEF          (OSG_TMPL_PARAM, OSG_CLASS)         \
    OSG_VO_GET_STATIC_TYPE_INL_TMPL_DEF   (OSG_TMPL_PARAM, OSG_CLASS)         \
    OSG_RC_GET_STATIC_TYPE_ID_INL_TMPL_DEF(OSG_TMPL_PARAM, OSG_CLASS)

#define OSG_VO_TYPE_FUNCTIONS_INL_TMPL_DEF2(OSG_TMPL_PARAM1_TYPE,             \
                                            OSG_TMPL_PARAM1,                  \
                                            OSG_TMPL_PARAM2_TYPE,             \
                                            OSG_TMPL_PARAM2,                  \
                                            OSG_CLASS)                        \
    OSG_RC_GET_TYPE_INL_TMPL_DEF2           (OSG_TMPL_PARAM1_TYPE,            \
                                             OSG_TMPL_PARAM1,                 \
                                             OSG_TMPL_PARAM2_TYPE,            \
                                             OSG_TMPL_PARAM2,                 \
                                             OSG_CLASS)                       \
    OSG_VO_GET_TYPE_INL_TMPL_DEF2           (OSG_TMPL_PARAM1_TYPE,            \
                                             OSG_TMPL_PARAM1,                 \
                                             OSG_TMPL_PARAM2_TYPE,            \
                                             OSG_TMPL_PARAM2,                 \
                                             OSG_CLASS)                       \
    OSG_VO_GET_STATIC_TYPE_INL_TMPL_DEF2    (OSG_TMPL_PARAM1_TYPE,            \
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

#if 0
#define OSG_DS_CREATE_DECL(OSG_CLASS_PTR)                                     \
    static OSG_CLASS_PTR create(void);

#define OSG_DS_CREATE_DEF(OSG_CLASS, OSG_CLASS_PTR)                           \
    OSG_CLASS::OSG_CLASS_PTR OSG_CLASS::create(void)                          \
    {                                                                         \
        OSG_CLASS_PTR fc;                                                     \
                                                                              \
        if(_type.getPrototype() != OSGDataStorePtr::OSGNullPtr)               \
            fc = dcast<OSG_CLASS_PTR>(_type.getPrototype()->shallowCopy());   \
                                                                              \
        return fc;                                                            \
    }

#define OSG_DS_CREATE_INL_TMPL_DEF(OSG_TMPL_PARAM,                          \
                                   OSG_CLASS,                               \
                                   OSG_CLASS_PTR)                           \
    template <class OSG_TMPL_PARAM> inline                                  \
    OSG_CLASS<OSG_TMPL_PARAM>::OSG_CLASS_PTR                                \
        OSG_CLASS<OSG_TMPL_PARAM>::create(void)                             \
    {                                                                       \
        OSG_CLASS_PTR fc;                                                   \
                                                                            \
        if(_type.getPrototype() != OSGDataStorePtr::OSGNullPtr)             \
            fc = dcast<OSG_CLASS_PTR>(_type.getPrototype()->shallowCopy()); \
                                                                            \
        return fc;                                                          \
    }

#define OSG_DS_CREATE_INL_TMPL_DEF2(OSG_TMPL_PARAM1_TYPE,                     \
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
        if(_type.getPrototype() != OSGDataStorePtr::OSGNullPtr)               \
            fc = dcast<OSG_CLASS_PTR>(_type.getPrototype()->shallowCopy());   \
                                                                              \
        return fc;                                                            \
    }

#define OSG_DS_CREATE_EMPTY_DECL(OSG_CLASS_PTR)                         \
    static OSG_CLASS_PTR createEmpty(void);

#define OSG_DS_CREATE_EMPTY_DEF(OSG_CLASS, OSG_CLASS_PTR)               \
    OSG_CLASS::OSG_CLASS_PTR OSG_CLASS::createEmpty(void)               \
    {                                                                   \
        OSG_CLASS_PTR returnValue;                                      \
                                                                        \
        newPtr(returnValue);                                            \
                                                                        \
        return returnValue;                                             \
    }

#define OSG_DS_CREATE_EMPTY_INL_TMPL_DEF(OSG_TMPL_PARAM,                \
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

#define OSG_DS_CREATE_EMPTY_INL_TMPL_DEF2(OSG_TMPL_PARAM1_TYPE,         \
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
        OSG_CLASS_PTR returnValue;                                      \
                                                                        \
        newPtr(returnValue);                                            \
                                                                        \
        return returnValue;                                             \
    }
#endif

#define OSG_VO_CLONE_DECL                                               \
    virtual VRMLObject *shallowCopy(void);

#define OSG_VO_CLONE_DEF(OSG_CLASS, OSG_CLASS_PTR)                      \
   VRMLObject *OSG_CLASS::shallowCopy(void)                             \
    {                                                                   \
        return new OSG_CLASS(*this);                                    \
    } 

#define OSG_VO_CLONE_INL_TMPL_DEF(OSG_TMPL_PARAM,                       \
                                  OSG_CLASS,                            \
                                  OSG_CLASS_PTR)                        \
    template <class OSG_TMPL_PARAM>                                     \
    VRMLObject *OSG_CLASS<OSG_TMPL_PARAM>::shallowCopy(void)            \
    {                                                                   \
        return new OSG_CLASS(*this);                                    \
    } 

#define OSG_DS_CLONE_INL_TMPL_DEF2(OSG_TMPL_PARAM1_TYPE,                \
                                   OSG_TMPL_PARAM1,                     \
                                   OSG_TMPL_PARAM2_TYPE,                \
                                   OSG_TMPL_PARAM2,                     \
                                   OSG_CLASS,                           \
                                   OSG_CLASS_PTR)                       \
    template <OSG_TMPL_PARAM1_TYPE OSG_TMPL_PARAM1,                     \
              OSG_TMPL_PARAM2_TYPE OSG_TMPL_PARAM2>                     \
    VRMLObject *OSG_CLASS<OSG_TMPL_PARAM1,                              \
                          OSG_TMPL_PARAM2>::shallowCopy(void)           \
    {                                                                   \
        return new OSG_CLASS(*this);                                    \
    } 

/*---------------------------- create grouping ------------------------------*/

#define OSG_VO_CREATE_FUNCTIONS_DECL(OSG_CLASS_PTR)                     \
    OSG_RC_CREATE_DECL      (OSG_CLASS_PTR)                             \
    OSG_RC_CREATE_EMPTY_DECL(OSG_CLASS_PTR)                             \
    OSG_VO_CLONE_DECL

#define OSG_VO_CREATE_FUNCTIONS_DEF(OSG_CLASS, OSG_CLASS_PTR)           \
    OSG_VO_CLONE_DEF           (OSG_CLASS, OSG_CLASS_PTR)               \
    OSG_RC_CREATE_DEF          (OSG_CLASS, OSG_CLASS_PTR)               \
    OSG_RC_CREATE_EMPTY_DEF    (OSG_CLASS, OSG_CLASS_PTR)

#define OSG_VO_CREATE_FUNCTIONS_INL_TMPL_DEF(OSG_TMPL_PARAM,            \
                                             OSG_CLASS,                 \
                                             OSG_CLASS_PTR)             \
    OSG_VO_CLONE_INL_TMPL_DEF       (OSG_TMPL_PARAM,                    \
                                     OSG_CLASS,                         \
                                     OSG_CLASS_PTR)                     \
    OSG_RC_CREATE_INL_TMPL_DEF      (OSG_TMPL_PARAM,                    \
                                     OSG_CLASS,                         \
                                     OSG_CLASS_PTR)                     \
    OSG_RC_CREATE_EMPTY_INL_TMPL_DEF(OSG_TMPL_PARAM,                    \
                                     OSG_CLASS,                         \
                                     OSG_CLASS_PTR)

#define OSG_VO_CREATE_FUNCTIONS_INL_TMPL_DEF2(OSG_TMPL_PARAM1_TYPE,     \
                                              OSG_TMPL_PARAM1,          \
                                              OSG_TMPL_PARAM2_TYPE,     \
                                              OSG_TMPL_PARAM2,          \
                                              OSG_CLASS,                \
                                              OSG_CLASS_PTR)            \
    OSG_VO_CLONE_INL_TMPL_DEF2       (OSG_TMPL_PARAM1_TYPE,             \
                                      OSG_TMPL_PARAM1,                  \
                                      OSG_TMPL_PARAM2_TYPE,             \
                                      OSG_TMPL_PARAM2,                  \
                                      OSG_CLASS,                        \
                                      OSG_CLASS_PTR)                    \
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


/*------------------------ decl and def macros ------------------------------*/

#define OSG_VRMLOBJ_DECL(OSG_CLASS_PTR)                       \
    OSG_VO_TYPE_FUNCTIONS_DECL                                \
    OSG_VO_CREATE_FUNCTIONS_DECL(OSG_CLASS_PTR)               \
    OSG_RC_SIZE_FUNCTIONS_DECL

#define OSG_VRMLOBJ_DEF(OSG_CLASS, OSG_CLASS_PTR)             \
    OSG_VO_TYPE_FUNCTIONS_DEF  (OSG_CLASS)                    \
    OSG_VO_CREATE_FUNCTIONS_DEF(OSG_CLASS, OSG_CLASS_PTR)     \
    OSG_RC_SIZE_FUNCTIONS_DEF  (OSG_CLASS)

/*--------------------- abstr decl and def macros --------------------------*/

#define OSG_ABSTR_VRMLOBJ_DECL(OSG_CLASS_PTR)                       \
    OSG_VO_TYPE_FUNCTIONS_DECL                                      \
    OSG_RC_SIZE_FUNCTIONS_DECL

#define OSG_ABSTR_VRMLOBJ_DEF(OSG_CLASS, OSG_CLASS_PTR)             \
    OSG_VO_TYPE_FUNCTIONS_DEF  (OSG_CLASS)                          \
    OSG_RC_SIZE_FUNCTIONS_DEF  (OSG_CLASS)

/*------------------ template decl and def macros --------------------------*/

#define OSG_VRMLOBJ_TMPL_DECL(OSG_CLASS_PTR)                         \
    OSG_VO_TYPE_FUNCTIONS_DECL                                       \
    OSG_VO_CREATE_FUNCTIONS_DECL(OSG_CLASS_PTR)                      \
    OSG_RC_SIZE_FUNCTIONS_DECL

#define OSG_VRMLOBJ_INL_TMPL_DEF(OSG_CLASS,                          \
                                   OSG_TMPL_PARAM,                   \
                                   OSG_CLASS_PTR)                    \
    OSG_VO_TYPE_FUNCTIONS_INL_TMPL_DEF  (OSG_TMPL_PARAM, OSG_CLASS)  \
    OSG_RC_SIZE_FUNCTIONS_INL_TMPL_DEF  (OSG_TMPL_PARAM, OSG_CLASS)  \
    OSG_VO_CREATE_FUNCTIONS_INL_TMPL_DEF(OSG_TMPL_PARAM,             \
                                         OSG_CLASS,                  \
                                         OSG_CLASS_PTR)

#define OSG_VRMLOBJ_INL_TMPL_DEF2(OSG_CLASS,                          \
                                    OSG_TMPL_PARAM1_TYPE,             \
                                    OSG_TMPL_PARAM1,                  \
                                    OSG_TMPL_PARAM2_TYPE,             \
                                    OSG_TMPL_PARAM2,                  \
                                    OSG_CLASS_PTR)                    \
    OSG_VO_TYPE_FUNCTIONS_INL_TMPL_DEF2  (OSG_TMPL_PARAM1_TYPE,       \
                                          OSG_TMPL_PARAM1,            \
                                          OSG_TMPL_PARAM2_TYPE,       \
                                          OSG_TMPL_PARAM2,            \
                                          OSG_CLASS)                  \
    OSG_RC_SIZE_FUNCTIONS_INL_TMPL_DEF2  (OSG_TMPL_PARAM1_TYPE,       \
                                          OSG_TMPL_PARAM1,            \
                                          OSG_TMPL_PARAM2_TYPE,       \
                                          OSG_TMPL_PARAM2,            \
                                          OSG_CLASS)                  \
    OSG_VO_CREATE_FUNCTIONS_INL_TMPL_DEF2(OSG_TMPL_PARAM1_TYPE,       \
                                          OSG_TMPL_PARAM1,            \
                                          OSG_TMPL_PARAM2_TYPE,       \
                                          OSG_TMPL_PARAM2,            \
                                          OSG_CLASS,                  \
                                          OSG_CLASS_PTR)

/*---------------abstr template decl and def macros ------------------------*/

#define OSG_ABSTR_VRMLOBJ_TMPL_DECL(OSG_CLASS_PTR)                   \
    OSG_VO_TYPE_FUNCTIONS_DECL                                       \
    OSG_RC_SIZE_FUNCTIONS_DECL

#define OSG_ABSTR_VRMLOBJ_INL_TMPL_DEF(OSG_CLASS,                    \
                                         OSG_TMPL_PARAM,             \
                                         OSG_CLASS_PTR)              \
    OSG_VO_TYPE_FUNCTIONS_INL_TMPL_DEF  (OSG_TMPL_PARAM, OSG_CLASS)  \
    OSG_RC_SIZE_FUNCTIONS_INL_TMPL_DEF  (OSG_TMPL_PARAM, OSG_CLASS)

#define OSG_ABSTR_VRMLOBJ_INL_TMPL_DEF2(OSG_CLASS,                    \
                                          OSG_TMPL_PARAM1_TYPE,       \
                                          OSG_TMPL_PARAM1,            \
                                          OSG_TMPL_PARAM2_TYPE,       \
                                          OSG_TMPL_PARAM2,            \
                                          OSG_CLASS_PTR)              \
    OSG_VO_TYPE_FUNCTIONS_INL_TMPL_DEF2  (OSG_TMPL_PARAM1_TYPE,       \
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

#define OSGVRMLOBJECT_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGVRMLOBJECT_HPP_ */
