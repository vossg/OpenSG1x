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

#ifndef _OSGVRMLNODEATTACHMENT_HPP_
#define _OSGVRMLNODEATTACHMENT_HPP_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>

#include <OSGRefCountMixin.h>
#include <OSGAttachmentMixin.h>
#include <OSGVRMLNodeFields.h>
#include <OSGVRMLObject.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

struct VRMLNodeAttachmentDesc
{
    typedef VRMLObject                     Parent;

    typedef VRMLNode                      *ParentPtr;
    typedef MFVRMLNode                     MFParentPtr;
    
    static void descInserter(ReflexiveContainerType *pType)
    {
        typedef AttachmentMixin<VRMLNodeAttachmentDesc> AM;

        if(pType == NULL)
            return;

        DataElementDesc *pDesc = NULL;

        pDesc = new DataElementDesc(
            AM::MFParentPtr::getClassType(),
            "parents",
            OSG_RC_ELEM_IDM_DESC(AM::ParentsField),
            false,
            (DataElemGetMethod) &AM::getMFParents,
            NULL,
            NULL);

        pType->addInitialDesc(pDesc);
    }
};

#ifndef OSG_COMPILEVRMLNODEATTACHMENT

#ifdef __sgi

#pragma do_not_instantiate AttachmentMixin<VRMLNodeAttachmentDesc>

#else

extern template class OSG_VRML_DLLMAPPING
    AttachmentMixin<VRMLNodeAttachmentDesc>;

#endif

#endif

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! VRMLNodeAttachment
//! \ingroup VRMLRuntimeLib

class OSG_VRML_DLLMAPPING VRMLNodeAttachment : 
    public AttachmentMixin<VRMLNodeAttachmentDesc>
{
  private:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef AttachmentMixin<VRMLNodeAttachmentDesc> Inherited;

  public:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef       VRMLNodeAttachment *Ptr;
    typedef const VRMLNodeAttachment *ConstPtr;

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
    void operator =(const VRMLNodeAttachment &source);

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

    VRMLNodeAttachment(void);
    VRMLNodeAttachment(const VRMLNodeAttachment &source);

  public :

    OSG_ABSTR_VRMLOBJ_DECL(Ptr);

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    virtual ~VRMLNodeAttachment(void); 
};

OSG_END_NAMESPACE

#define OSGVRMLNODEATTACHMENT_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGVRMLNODEATTACHMENT_HPP_ */

