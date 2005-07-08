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

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGAttachmentContainer.cpp
    \ingroup GrpSystemFieldContainer
 */
#endif

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"
#include "OSGAttachmentContainer.h"
#include "OSGFieldContainerPtr.h"
#include "OSGFieldContainerType.h"
#include "OSGAttachment.h"
#include "OSGBinaryDataHandler.h"

OSG_USING_NAMESPACE

const BitVector AttachmentContainer::AttachmentsFieldMask =
    (TypeTraits<BitVector>::One << 
        AttachmentContainer::AttachmentsFieldId);

FieldDescription *AttachmentContainer::_desc[] =
{
    new FieldDescription(SFAttachmentMap::getClassType(),
                         "attachments",
                         OSG_FC_FIELD_IDM_DESC(AttachmentsField),
                         false,
                         (FieldAccessMethod)
                             &AttachmentContainer::getSFAttachments)
};

FieldContainerType AttachmentContainer::_type(
    "AttachmentContainer",
    "FieldContainer",
    0,
    NULL,
    0,
    _desc,
    sizeof(_desc));


OSG_ABSTR_FIELD_CONTAINER_DEF(AttachmentContainer, AttachmentContainerPtr)

/*-------------------------------------------------------------------------*/
/*                          Handle Attachments                             */

void AttachmentContainer::addAttachment(const AttachmentPtr &fieldContainerP,
                                              UInt16         binding)
{
    UInt32 key;

    if(fieldContainerP == NullFC)
        return;

    key = (UInt32 (fieldContainerP->getGroupId()) << 16) | binding;

    addRefCP(fieldContainerP);

    beginEditCP(fieldContainerP, Attachment::ParentsFieldMask);
    {
        fieldContainerP->addParent(getPtr());
    }
    endEditCP  (fieldContainerP, Attachment::ParentsFieldMask);

    AttachmentMap::iterator fcI = _attachmentMap.getValue().find(key);

    if(fcI != _attachmentMap.getValue().end())
    {
        beginEditCP((*fcI).second, Attachment::ParentsFieldMask);
        {
            (*fcI).second->subParent(getPtr());
        }
        endEditCP  ((*fcI).second, Attachment::ParentsFieldMask);

        subRefCP((*fcI).second);

        (*fcI).second = fieldContainerP;
    }
    else
    {
        _attachmentMap.getValue()[key] = fieldContainerP;
    }
}

void AttachmentContainer::subAttachment(const AttachmentPtr &fieldContainerP,
                                              UInt16         binding)
{
    UInt32 key;

    AttachmentMap::iterator fcI;

    if(fieldContainerP == NullFC)
        return;

    key = (UInt32(fieldContainerP->getGroupId()) << 16) | binding;

    fcI = _attachmentMap.getValue().find(key);

    if(fcI != _attachmentMap.getValue().end())
    {
        beginEditCP(fieldContainerP, Attachment::ParentsFieldMask);
        {
            (*fcI).second->subParent(getPtr());
        }
        endEditCP  (fieldContainerP, Attachment::ParentsFieldMask);

        subRefCP((*fcI).second);

        _attachmentMap.getValue().erase(fcI);
    }
}

AttachmentPtr AttachmentContainer::findAttachment(UInt32 groupId,
                                                  UInt16 binding)
{
    UInt32 key = (UInt32(groupId) << 16) | binding;

    AttachmentMap::iterator fcI = _attachmentMap.getValue().find(key);

    if(fcI == _attachmentMap.getValue().end())
    {
        return NullFC;
    }
    else
    {
        return (*fcI).second;
    }
}

/*-------------------------------------------------------------------------*/
/*                            Field Access                                 */

SFAttachmentMap *AttachmentContainer::getSFAttachments(void)
{
    return &_attachmentMap;
}

/*-------------------------------------------------------------------------*/
/*                             Changed                                     */

void AttachmentContainer::changed(BitVector whichField,
                                  UInt32    origin    )
{
    if(whichField & AttachmentsFieldMask)
    {
        if(origin & ChangedOrigin::Abstract)
        {
            if(origin & ChangedOrigin::AbstrIncRefCount)
            {
                AttachmentMap::iterator attIt  = 
                    _attachmentMap.getValue().begin();
                AttachmentMap::iterator attEnd = 
                    _attachmentMap.getValue().end();

                while(attIt != attEnd)
                {
                    addRefCP((*attIt).second);
                    
                    ++attIt;
                }
            }
        }
    }
}

/*-------------------------------------------------------------------------*/
/*                           Binary Access                                 */

UInt32 AttachmentContainer::getBinSize(const BitVector &whichField)
{
    UInt32 returnValue = 0;

    if(FieldBits::NoField != (AttachmentsFieldMask & whichField))
    {
        returnValue += _attachmentMap.getBinSize();
    }

    return returnValue;
}

void AttachmentContainer::copyToBin  (      BinaryDataHandler &pMem,
                                      const BitVector    &whichField)
{
    if(FieldBits::NoField != (AttachmentsFieldMask & whichField))
    {
        _attachmentMap.copyToBin(pMem);
    }
}

void AttachmentContainer::copyFromBin(      BinaryDataHandler &pMem,
                                      const BitVector    &whichField)
{
    if(FieldBits::NoField != (AttachmentsFieldMask & whichField))
    {
        _attachmentMap.copyFromBin(pMem);
    }
}

/*-------------------------------------------------------------------------*/
/*                                Dump                                     */

void AttachmentContainer::dump(      UInt32    uiIndent,
                               const BitVector bvFlags) const
{
    AttachmentMap::const_iterator fcI;

    fcI = _attachmentMap.getValue().begin();

    while(fcI != _attachmentMap.getValue().end())
    {
        (*fcI).second->dump(uiIndent + 4, bvFlags);
        ++fcI;
    }
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

AttachmentContainer::AttachmentContainer(void) :
     Inherited    (),
    _attachmentMap()
{
}

AttachmentContainer::AttachmentContainer(const AttachmentContainer &source) :
     Inherited    (source),
    _attachmentMap()
{
    AttachmentMap::const_iterator fcI =
        source._attachmentMap.getValue().begin();

    AttachmentMap::const_iterator fcEnd =
        source._attachmentMap.getValue().end  ();

    while(fcI != fcEnd)
    {
        addAttachment((*fcI).second);

        fcI++;
    }
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

AttachmentContainer::~AttachmentContainer(void)
{
    AttachmentMap::iterator attIt  = _attachmentMap.getValue().begin();
    AttachmentMap::iterator attEnd = _attachmentMap.getValue().end();

    AttachmentContainerPtr thisP = getPtr();

    while(attIt != attEnd)
    {
        beginEditCP((*attIt).second, Attachment::ParentsFieldMask);
        {
            (*attIt).second->subParent(thisP);
        }
        endEditCP  ((*attIt).second, Attachment::ParentsFieldMask);

        subRefCP   ((*attIt).second);

        ++attIt;
    }

    _attachmentMap.getValue().clear();
}

/*-------------------------------------------------------------------------*/
/*                                Sync                                     */

#if !defined(OSG_FIXED_MFIELDSYNC)
void AttachmentContainer::executeSync(      FieldContainer &other,
                                      const BitVector      &whichField)
{
    this->executeSyncImpl((AttachmentContainer *) &other, whichField);
}

void AttachmentContainer::executeSyncImpl(
          AttachmentContainer *pOther,
    const BitVector           &whichField)
{
    Inherited::executeSyncImpl(pOther, whichField);

    if (FieldBits::NoField != (AttachmentsFieldMask & whichField))
    {
        _attachmentMap.syncWith(pOther->_attachmentMap);
    }
}
#else
void AttachmentContainer::executeSync(      FieldContainer &other,
                                      const BitVector      &whichField,
                                      const SyncInfo       &sInfo     )
{
    this->executeSyncImpl((AttachmentContainer *) &other, whichField, sInfo);
}

void AttachmentContainer::executeSyncImpl(
          AttachmentContainer *pOther,
    const BitVector           &whichField,
    const SyncInfo            &sInfo     )
{
    Inherited::executeSyncImpl(pOther, whichField, sInfo);

    if (FieldBits::NoField != (AttachmentsFieldMask & whichField))
    {
        _attachmentMap.syncWith(pOther->_attachmentMap);
    }
}
#endif

/*-------------------------------------------------------------------------*/
/*                                Pointer                                  */

AttachmentContainerPtr AttachmentContainer::getPtr(void)
{
    return AttachmentContainerPtr(*this);
}


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
    static Char8 cvsid_hpp[] = OSGATTACHMENTCONTAINER_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGATTACHMENTCONTAINER_INLINE_CVSID;
}

