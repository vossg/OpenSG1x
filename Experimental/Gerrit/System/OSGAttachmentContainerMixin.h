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

#ifndef _OSGATTACHMENTCONTAINERMIXIN_HPP_
#define _OSGATTACHMENTCONTAINERMIXIN_HPP_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class Attachment;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! Brief AttachmentContainerMixin
//! \ingroup DataStoreLib

template <class AttachmentDescT>
class AttachmentContainerMixin : public AttachmentDescT::Parent
{
  private:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef AttachmentDescT::Parent Inherited;

  public:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef       AttachmentContainerMixin      *Ptr;
    typedef const AttachmentContainerMixin      *ConstPtr;

    typedef       AttachmentDescT                Desc;

    typedef       Desc::AttachmentObjPtr         AttachmentObjPtr;
    typedef       Desc::AttachmentObj            AttachmentObj;
    typedef       Desc::SFAttachmentObjMap       SFAttachmentObjMap;

    typedef       Desc::ObjectType               ObjectType;

    typedef       SFAttachmentObjMap::StoredType AttachmentObjMap;

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    static const UInt32 StoreHasDescs = 1;

    OSG_RC_FIRST_ELEM_IDM_DECL(AttachmentsField);

    OSG_RC_LAST_ELEM_IDM_DECL (AttachmentsField);

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

    void operator =(const AttachmentContainerMixin &source);

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

    static ObjectType _type;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    SFAttachmentObjMap _sfAttachments;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    AttachmentContainerMixin(void);
    AttachmentContainerMixin(const AttachmentContainerMixin &source);

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    virtual ~AttachmentContainerMixin(void); 

    /*------------------------ handle attachments ---------------------------*/

    void             addAttachment (const AttachmentObjPtr pContainer, 
                                          UInt16           uiBinding = 0);

    void             subAttachment (const AttachmentObjPtr pContainer,
                                          UInt16           uiBinding = 0);

    AttachmentObjPtr findAttachment(      UInt32           uiGroupId,
                                          UInt16           uiBinding = 0);

/*
    AttachmentPtr findAttachment(const VSCFieldContainerType &type,
                                       VSCUInt16              binding   = 0);
*/

    /*-------------------------- field access -------------------------------*/

    SFAttachmentObjMap *getSFAttachments(void);
};

OSG_END_NAMESPACE

#define OSGATTACHMENTCONTAINERMIXIN_HEADER_CVSID "@(#)$Id: $"

#include <OSGAttachmentContainerMixin.inl>

#endif /* _OSGATTACHMENTCONTAINERMIXIN_HPP_ */
