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

#ifndef _OSGVRMLNODE_HPP_
#define _OSGVRMLNODE_HPP_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGVRMLBase.h>
#include <OSGFieldType.h>
#include <OSGMField.h>
#include <OSGSField.h>
#include <OSGVRMLObjectType.h>
#include <OSGIDString.h>

#include <OSGVRMLObject.h>
#include <OSGAttachmentContainerMixin.h>
#include <OSGVRMLNodeAttachmentMap.h>

#include <OSGFieldContainerPtr.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class VRMLNode;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------


struct VRMLNodeAttachmentContainerDesc
{
    typedef VRMLObject                   Parent;

    typedef VRMLNodeAttachment          *AttachmentObjPtr;
    typedef VRMLNodeAttachment           AttachmentObj;
    typedef SFVRMLNodeAttachmentMap      SFAttachmentObjMap;

    typedef VRMLObjectType               ObjectType;

    typedef AttachmentContainerMixin<
                VRMLNodeAttachmentContainerDesc> AttachmentContainer;

    static AttachmentObjPtr getNullPtr(void)
    {
        return NULL;
    }

    static AttachmentContainer *getPtr(AttachmentContainer *pContainer)
    {
        return pContainer;
    }

    static VRMLNode *getDownCastPtr(AttachmentContainer *pContainer)
    {
        return reinterpret_cast<VRMLNode *>(pContainer);
    }

    static Char8 *getTypeName(void)
    {
        return "VRMLNodeAttachmentContainer";
    }

    static Char8 *getTypeParentName(void)
    {
        return "VRMLObject";
    }

    static Char8 *getTypeGroupName(void)
    {
        return "VRMLNodes";
    }

    static void descInserter(ReflexiveContainerType *pType);
};

typedef AttachmentContainerMixin<VRMLNodeAttachmentContainerDesc>
    VRMLNodeParent;

#ifndef OSG_COMPILEVRMLNODEINST

#ifdef __sgi

#pragma do_not_instantiate RefCountMixin<VRMLObject>

#pragma do_not_instantiate AttachmentContainerMixin<VRMLNodeAttachmentContainerDesc>

#else

// CHECKCHECK
#ifndef __linux
extern template class OSG_VRML_DLLMAPPING 
    AttachmentContainerMixin<VRMLNodeAttachmentContainerDesc>;
#endif

#endif

#endif

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

class VRMLNodeBinder;

struct VRMLBindings
{
    typedef VRMLNodeBinder  NodeBinder;
    typedef VRMLNodeBinder *NodeBinderPtr;

    static NodeBinderPtr getNullNodeBinder(void)
    {
        return NULL;
    }
};

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! VRMLNode
//! \ingroup VRMLNodeLib

class OSG_VRML_DLLMAPPING VRMLNode : 
    public VRMLNodeParent
{
  private:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef VRMLNodeParent Inherited;

  public:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef       VRMLNode *Ptr;
    typedef const VRMLNode *ConstPtr;

    typedef       VRMLNode  ObjectType;

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
    void operator =(const VRMLNode &source);

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef VRMLBindings::NodeBinderPtr NodeBinderPtr;

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

    IDString      _szName;

    NodeBinderPtr _pBinder;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    VRMLNode(void);
    VRMLNode(const VRMLNode &source);

  public :

    OSG_ABSTR_VRMLOBJ_DECL(Ptr);

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    virtual ~VRMLNode(void); 

    /*------------------------------ name ----------------------------------*/

          void      setName (const Char8 *szName  );
    
    const IDString &getName (void                  ) const;
    const Char8    *getCName(void                  ) const;

    /*----------------------------- binder ---------------------------------*/

    NodeBinderPtr getBinder(void                 );
    void          setBinder(NodeBinderPtr pBinder);

    /*------------------------------ name ----------------------------------*/

    void beginEdit(BitVector bWhichField);
    void endEdit  (BitVector bWhichField);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! VRMLNodeBinder
//! \ingroup VRMLOSGBindingLib

class OSG_VRML_DLLMAPPING VRMLNodeBinder 
{
  private:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

  public:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

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
    VRMLNodeBinder(const VRMLNodeBinder &source);
    //! prohibit default function (move to 'public' if needed) 
    void operator =(const VRMLNodeBinder &source);

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

    FieldContainerPtr  _pFieldContainer;

    VRMLNode          *_pNode;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    VRMLNodeBinder(void);

    virtual ~VRMLNodeBinder(void); 

    /*--------------------------- getFCPtr ---------------------------------*/

    FieldContainerPtr getFCPtr(void           );

    void              setNode (VRMLNode *pNode);
};

OSG_END_NAMESPACE

#define OSGVRMLNODE_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGVRMLNODE_HPP_ */
