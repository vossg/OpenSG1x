/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000,2001 by OpenSG Forum                   *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"
#include "OSGFieldContainerPtr.h"
#include "OSGFieldContainerType.h"
#include "OSGAttachment.h"
#include "OSGAttachmentContainer.h"
#include "OSGBinaryDataHandler.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id: $";
    static char cvsid_hpp[] = OSGATTACHMENTCONTAINER_HEADER_CVSID;
    static char cvsid_inl[] = OSGATTACHMENTCONTAINER_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/* Could not put this in the class declaration, since MS interprets them there
 * as pure virtual functions :-( (GV)
 */

const BitVector AttachmentContainer::AttachmentsFieldMask =
    (1 << AttachmentContainer::AttachmentsFieldId);

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



/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/



/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/



/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*! \fn FieldContainerType &AttachmentContainer::getClassType(void)
 *  \brief returns AttachmentContainer type
 */

/*! \fn UInt32 AttachmentContainer::getClassTypeId(void)
 *  \brief returns AttachmentContainer type id
 */

OSG_ABSTR_FIELD_CONTAINER_DEF(AttachmentContainer, AttachmentContainerPtr)

/*------------------------------ access -----------------------------------*/

void AttachmentContainer::addAttachment(const AttachmentPtr &fieldContainerP,
                                              UInt16         binding)
{
    UInt32 key;

    if(fieldContainerP == NullFC)
        return;

    key = (UInt32 (fieldContainerP->getGroupId()) << 16) | binding;

    addRefCP(fieldContainerP);

    AttachmentMap::iterator fcI = _attachmentMap.getValue().find(key);

    beginEditCP(fieldContainerP, Attachment::ParentsFieldMask);
    {
        fieldContainerP->addParent(getPtr());
    }
    endEditCP  (fieldContainerP, Attachment::ParentsFieldMask);

    if(fcI != _attachmentMap.getValue().end())
    {
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

    return (fcI == _attachmentMap.getValue().end()) ? NullFC : (*fcI).second;
}

/*---------------------------- properties ---------------------------------*/

SFAttachmentMap *AttachmentContainer::getSFAttachments(void)
{
    return &_attachmentMap;
}

AttachmentContainerPtr AttachmentContainer::getPtr(void)
{
    return AttachmentContainerPtr(*this);
}

void AttachmentContainer::changed(BitVector  ,
                                  ChangeMode )
{
}

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

/*------------------------------- dump ----------------------------------*/

void AttachmentContainer::dump(      UInt32     uiIndent,
                               const BitVector &bvFlags) const
{
    AttachmentMap::const_iterator fcI;

    fcI = _attachmentMap.getValue().begin();

    while(fcI != _attachmentMap.getValue().end())
    {
        (*fcI).second->dump(uiIndent + 4, bvFlags);
        ++fcI;
    }
}

/*-------------------------- comparison -----------------------------------*/


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

AttachmentContainer::AttachmentContainer(void) :
    Inherited     (),
    _attachmentMap()
{
}

/** \brief CopyConstructor, used only by the protoype mechanism
 */

AttachmentContainer::AttachmentContainer(const AttachmentContainer &source) :
    Inherited     (source),
    _attachmentMap()
{
    AttachmentMap::const_iterator fcI =
        source._attachmentMap.getValue().begin();

    while(fcI != source._attachmentMap.getValue().end())
    {
        addAttachment((*fcI).second);

        fcI++;
    }
}

/** \brief Destructor
 */

AttachmentContainer::~AttachmentContainer(void)
{
    // TODO Unlink Tree
}

/*------------------------------ access -----------------------------------*/

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



/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

///---------------------------------------------------------------------------
///  FUNCTION:
///---------------------------------------------------------------------------
//:  Example for the head comment of a function
///---------------------------------------------------------------------------
///
//p: Paramaters:
//p:
///
//g: GlobalVars:
//g:
///
//r: Return:
//r:
///
//c: Caution:
//c:
///
//a: Assumptions:
//a:
///
//d: Description:
//d:
///
//s: SeeAlso:
//s:
///---------------------------------------------------------------------------

