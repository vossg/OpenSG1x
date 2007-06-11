/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                *
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

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGSimpleAttachments.cpp
    \ingroup GrpSystemFieldContainer
 */
#endif

#define OSG_COMPILESIMPLEATTACHMENTSINST

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGAttachmentContainer.h"
#include "OSGSimpleAttachments.h"

OSG_USING_NAMESPACE


#ifdef WIN32
OSG_FC_TYPE_FUNCTIONS_INL_TMPL_DEF(AttachmentDescT,
                                   SimpleAttachment);
#endif

/*-------------------------------------------------------------------------*/
/*                            Name Attachment                              */

FieldDescription *NameAttachmentDesc::_desc[] =
{
    new FieldDescription(
        FieldTypeT::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(
            SimpleAttachment<NameAttachmentDesc>::SimpleField),
        false,
        (FieldAccessMethod) &SimpleAttachment<
                                  NameAttachmentDesc>::getFieldPtr)
};

OSG_BEGIN_NAMESPACE

OSG_FC_DLLEXPORT_DEF(SimpleAttachment,
                     NameAttachmentDesc,
                     OSG_SYSTEMLIB_DLLTMPLMAPPING);

OSG_END_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                            VoidP Attachment                             */

FieldDescription *VoidPAttachmentDesc::_desc[] =
{
    new FieldDescription(
        FieldTypeT::getClassType(), 
        getFieldName(), 
        OSG_FC_FIELD_IDM_DESC(
            SimpleAttachment<VoidPAttachmentDesc>::SimpleField),
        false,
        (FieldAccessMethod) &SimpleAttachment<
                                  VoidPAttachmentDesc>::getFieldPtr)
};

OSG_BEGIN_NAMESPACE

OSG_FC_DLLEXPORT_DEF(SimpleAttachment,
                     VoidPAttachmentDesc,
                     OSG_SYSTEMLIB_DLLTMPLMAPPING);


/*-------------------------------------------------------------------------*/
/*                   Name Attachment Utility Functions                     */

/*! 
  Return the name attached to the container, NULL if none attached or
  container is NULL.
 */

const Char8 *getName(AttachmentContainerPtr container)
{
    if(container == NullFC)
        return NULL;
   
    // Get attachment pointer
    AttachmentPtr att = 
        container->findAttachment(Name::getClassType().getGroupId());

    if(att == NullFC)
        return NULL;
   
    // Cast to name pointer                           

    NamePtr name = NamePtr::dcast(att);

    if(name == NullFC)
        return NULL;
   
    return name->getFieldPtr()->getValue().c_str();
}

/*! Set the name attached to the container. If the container doesn't have a
    name attachement yet one is created. 
 */

void setName(      AttachmentContainerPtr  container, 
             const std::string            &namestring)
{
    if(container == NullFC)
    {
        FFATAL(("setName: no container?!?\n"));
        return;
    }
   
    // Get attachment pointer

    NamePtr       name = NullFC;
    AttachmentPtr att  = 
        container->findAttachment(Name::getClassType().getGroupId());
    
    if(att == NullFC)
    {
        name = Name::create();
        beginEditCP(container, AttachmentContainer::AttachmentsFieldMask);
        {
            container->addAttachment(name);
        }
        endEditCP(container, AttachmentContainer::AttachmentsFieldMask);
    }
    else
    {   
        name = NamePtr::dcast(att);

        if(name == NullFC)
        {
            FFATAL(("setName: Name Attachment is not castable to Name?!?\n"));
            return;
        }
    }
    
  
    beginEditCP(name);
    {
        name->getFieldPtr()->getValue().assign(namestring);   
    }
    endEditCP(name);
}

/*! 
  Set the name attached to the container. If the container doesn't have 
  name attachement yet one is created. If the name is NULL, an attached
  name is removed.
 */

void setName(AttachmentContainerPtr container, const Char8 *name)
{
    if(name == NULL)
    {
        AttachmentPtr att = 
            container->findAttachment(Name::getClassType().getGroupId());
 
        if(att != NullFC)
        {
            container->subAttachment(att);
        }       
    }
    else
    {
        setName(container, std::string(name));
    }
}


/*-------------------------------------------------------------------------*/
/*                   VoidP Attachment Utility Functions                    */

/*! 
  Return the void * attached to the container, NULL if none attached or
  container is NULL.
 */

void *getVoidP(AttachmentContainerPtr container)
{
    if(container == NullFC)
        return NULL;
   
    // Get attachment pointer
    AttachmentPtr att = 
       container->findAttachment(VoidPAttachment::getClassType().getGroupId());

    if(att == NullFC)
        return NULL;
   
    // Cast to name pointer                           

    VoidPAttachmentPtr pVoid = VoidPAttachmentPtr::dcast(att);

    if(pVoid == NullFC)
        return NULL;
   
    return pVoid->getFieldPtr()->getValue();
}

/*! 
  Set the void * attached to the container. If the container doesn't have a
  VoidP attachement yet one is created. 
 */

void setVoidP(AttachmentContainerPtr  container, 
              void                   *pData,
              bool                   internal )
{
    if(container == NullFC)
    {
        FFATAL(("setVoidP: no container?!?\n"));
        return;
    }
   
    // Get attachment pointer

    VoidPAttachmentPtr  pVoid = NullFC;
    AttachmentPtr       att   = 
       container->findAttachment(VoidPAttachment::getClassType().getGroupId());
    
    if(att == NullFC)
    {
        pVoid = VoidPAttachment::create();
        container->addAttachment(pVoid);
    }
    else
    {   
        pVoid = VoidPAttachmentPtr::dcast(att);

        if(pVoid == NullFC)
        {
            FFATAL(("setVoidP: VoidP Attachment is not castable "
                    "to VoidPAttachment?!?\n"));
            return;
        }
    }
  
    pVoid->setInternal(internal);
    pVoid->getFieldPtr()->setValue(pData);
}

OSG_END_NAMESPACE


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGSIMPLEATTACHMENTS_HEADER_CVSID;
}

