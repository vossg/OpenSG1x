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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------


#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

#include <OSGDataElementDesc.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if 0

#if !defined(OSG_NO_FULL_DOC)

template <class AttachmentDescT>
struct DescHolderT<
    AttachmentDescT,
    AttachmentContainerMixin<AttachmentDescT>,
    typename AttachmentContainerMixin<
                                 AttachmentDescT>::AttachmentsFieldCount,
    DataElementDesc> :

    public DescHolderBaseT<
        AttachmentDescT,
        AttachmentContainerMixin<AttachmentDescT>,
        typename AttachmentContainerMixin<
                                 AttachmentDescT>::AttachmentsFieldCount,
        DataElementDesc   >
{
    typedef AttachmentContainerMixin<AttachmentDescT> ACM;

    static DataElementDesc _desc;
};

template <class AttachmentDescT>
DataElementDesc DescHolderT<
    AttachmentDescT,
    AttachmentContainerMixin<AttachmentDescT>,
    typename AttachmentContainerMixin<
                                 AttachmentDescT>::AttachmentsFieldCount,
    DataElementDesc                                                >::_desc(
        ACM::SFAttachmentObjMap::getClassType(),
        "attachments",
        OSG_RC_ELEM_IDM_DESC(ACM::AttachmentsField),
        false,
        (DataElemGetMethod) &ACM::getSFAttachments,
        NULL,
        NULL,
        DataElementDesc::DefaultBeginEditFunctor,
        DataElementDesc::DefaultEndEditFunctor,
        DataElementDesc::DefaultSyncFunctor);

#endif

#endif

#ifndef OSG_WIN32_CL
template <class AttachmentDescT>
typename AttachmentContainerMixin<AttachmentDescT>::ObjectType
    AttachmentContainerMixin<AttachmentDescT>::_type(
        Desc::getTypeName      (),
        Desc::getTypeParentName(),
        Desc::getTypeGroupName (),
        NULL,
        NULL, // Init
        Desc::descInserter,
        true);
#else
template <class AttachmentDescT>
typename AttachmentContainerMixin<AttachmentDescT>::ObjectType
    AttachmentContainerMixin<AttachmentDescT>::_type = 
        AttachmentContainerMixin<AttachmentDescT>::ObjectType(
            Desc::getTypeName      (),
            Desc::getTypeParentName(),
            Desc::getTypeGroupName (),
            NULL,
            NULL, // Init
            Desc::descInserter,
            true);
#endif

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

template<class AttachmentDescT> inline
AttachmentContainerMixin<AttachmentDescT>::AttachmentContainerMixin(
    void) :

     Inherited    (),
    
    _sfAttachments()
{
}


template<class AttachmentDescT> inline
AttachmentContainerMixin<AttachmentDescT>::AttachmentContainerMixin(
    const AttachmentContainerMixin &source) :

     Inherited    (source),

    _sfAttachments(      )
{
    typename AttachmentObjMap::const_iterator amIt   =
        source._sfAttachments.getValue().begin();

    typename AttachmentObjMap::const_iterator amEnd =
        source._sfAttachments.getValue().end  ();

    while(amIt != amEnd)
    {
        addAttachment((*amIt).second);

        amIt++;
    }
}


/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

template<class AttachmentDescT> inline
AttachmentContainerMixin<AttachmentDescT>::~AttachmentContainerMixin(void)
{
}

/*------------------------------ access -----------------------------------*/

template<class AttachmentDescT> inline
void AttachmentContainerMixin<AttachmentDescT>::addAttachment(
    const AttachmentObjPtr pContainer, 
          UInt16           uiBinding )
{
    UInt32 uiKey;

    if(pContainer == Desc::getNullPtr())
        return;

    uiKey = (UInt32 (pContainer->getGroupId()) << 16) | uiBinding;

    OSG::addRef<AttachmentObj>(pContainer);

    typename AttachmentObjMap::iterator amIt = 
        _sfAttachments.getValue().find(uiKey);

    OSG::beginEdit<AttachmentObj>(pContainer, AttachmentObj::ParentsFieldMask);
    {
        pContainer->addParent(Desc::getDownCastPtr(this));
    }
    OSG::endEdit  <AttachmentObj>(pContainer, AttachmentObj::ParentsFieldMask);

    if(amIt != _sfAttachments.getValue().end())
    {
        OSG::beginEdit<AttachmentObj>(pContainer, 
                                      AttachmentObj::ParentsFieldMask);
        {
            (*amIt).second->subParent(Desc::getDownCastPtr(this));
        }
        OSG::endEdit  <AttachmentObj>(pContainer, 
                                      AttachmentObj::ParentsFieldMask);

        OSG::subRef<AttachmentObj>((*amIt).second);

        (*amIt).second = pContainer;
    }
    else
    {
        _sfAttachments.getValue()[uiKey] = pContainer;
    }
}

template<class AttachmentDescT> inline
void AttachmentContainerMixin<AttachmentDescT>::subAttachment(
    const AttachmentObjPtr pContainer,
          UInt16           uiBinding )
{
    UInt32 uiKey;

    typename AttachmentObjMap::iterator amIt;

    if(pContainer == Desc::getNullPtr())
        return;

    uiKey = (UInt32(pContainer->getGroupId()) << 16) | uiBinding;

    amIt = _sfAttachments.getValue().find(uiKey);

    if(amIt != _sfAttachments.getValue().end())
    {
        OSG::beginEdit<AttachmentObj>(pContainer, 
                                      AttachmentObj::ParentsFieldMask);
        {
            (*amIt).second->subParent(Desc::getDownCastPtr(this));
        }
        OSG::endEdit  <AttachmentObj>(pContainer, 
                                      AttachmentObj::ParentsFieldMask);

        OSG::subRef<AttachmentObj>((*amIt).second);

        _sfAttachments.getValue().erase(amIt);
    }
}

template<class AttachmentDescT> inline
typename AttachmentContainerMixin<AttachmentDescT>::AttachmentObjPtr
     AttachmentContainerMixin<AttachmentDescT>::findAttachment(
         UInt32 uiGroupId,
         UInt16 uiBinding)
{
    UInt32 uiKey = (UInt32(uiGroupId) << 16) | uiBinding;

    typename AttachmentObjMap::iterator amIt = 
        _sfAttachments.getValue().find(uiKey);

    return (amIt == _sfAttachments.getValue().end()) ? 
        Desc::getNullPtr() : (*amIt).second;
}

template<class AttachmentDescT> inline
typename AttachmentContainerMixin<AttachmentDescT>::SFAttachmentObjMap *
    AttachmentContainerMixin<AttachmentDescT>::getSFAttachments(void)
{
    return &_sfAttachments;
}

OSG_END_NAMESPACE

#define OSGATTACHMENTCONTAINERMIXIN_INLINE_CVSID "@(#)$Id: $"
