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

template <class VSCAttachmentDescT>
struct VSCDescHolderT<
    VSCAttachmentDescT,
    VSCAttachmentMixin<VSCAttachmentDescT>,
    typename VSCAttachmentMixin<VSCAttachmentDescT>::VSCParentsFieldCount,
    VSCDataElementDesc> :

    public VSCDescHolderBaseT<
        VSCAttachmentDescT,
        VSCAttachmentMixin<VSCAttachmentDescT>,
        typename VSCAttachmentMixin<VSCAttachmentDescT>::VSCParentsFieldCount,
        VSCDataElementDesc   >
{
    typedef VSCAttachmentMixin<VSCAttachmentDescT> VSCAM;

    static VSCDataElementDesc _desc;
};

template <class VSCAttachmentDescT>
VSCDataElementDesc VSCDescHolderT<
    VSCAttachmentDescT,
    VSCAttachmentMixin<VSCAttachmentDescT>,
    typename VSCAttachmentMixin<VSCAttachmentDescT>::VSCParentsFieldCount,
    VSCDataElementDesc                                                >::_desc(
        VSCAM::VSCMFParentPtr::getClassType(),
        "parents",
        VSC_RC_ELEM_IDM_DESC(VSCACM::VSCParentsField),
        false,
        (VSCDataElemGetMethod) &VSCAM::getMFParents,
        NULL,
        NULL,
        VSCDataElementDesc::VSCDefaultBeginEditFunctor,
        VSCDataElementDesc::VSCDefaultEndEditFunctor,
        VSCDataElementDesc::VSCDefaultSyncFunctor);

#endif

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


template <class AttachmentDescT> inline
AttachmentMixin<AttachmentDescT>::AttachmentMixin(void) :
     Inherited(),
    
    _mfParents()
{
}


template <class AttachmentDescT> inline
AttachmentMixin<AttachmentDescT>::AttachmentMixin(
    const AttachmentMixin &source) :

	 Inherited(source           ),

    _mfParents(source._mfParents)
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

template <class AttachmentDescT> inline
AttachmentMixin<AttachmentDescT>::~AttachmentMixin(void)
{
}

/*------------------------------ access -----------------------------------*/

template <class AttachmentDescT> inline
void AttachmentMixin<AttachmentDescT>::addParent(ParentPtr pParent)
{
    addRef(pParent);

    _mfParents.push_back(pParent);
}

template <class AttachmentDescT> inline
void AttachmentMixin<AttachmentDescT>::subParent(ParentPtr pParent)
{
    MFParentPtr::iterator parentIt = _mfParents.find(pParent);

    if(parentIt != _mfParents.end())
    {
         subRef(pParent);

        _mfParents.erase(parentIt);
    }
}

template <class AttachmentDescT> inline
AttachmentMixin<AttachmentDescT>::MFParentPtr *
    AttachmentMixin<AttachmentDescT>::getMFParents(void)
{
    return &_mfParents;
}


OSG_END_NAMESPACE
