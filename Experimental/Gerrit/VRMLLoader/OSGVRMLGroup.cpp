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

#include "OSGVRMLGroup.h"
#include "OSGDataElementDesc.h"
#include "OSGVRMLToOSGAction.h"

#include "OSGGroup.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGVRMLGROUP_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_BEGIN_NAMESPACE

VRMLAction::ActionResult osgVRMLGroupToOpenSG(VRMLNode   &oNode,
                                              VRMLAction *pAction);

OSG_END_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

#if 0

template<>
struct VSCDescHolderC<VSCVRMLGroup, 
                      VSCVRMLGroup::VSCChildrenFieldCount, 
                      VSCDataElementDesc> : 
    public VSCDescHolderBaseC<VSCVRMLGroup, 
                              VSCVRMLGroup::VSCChildrenFieldCount, 
                              VSCDataElementDesc>
{
    static VSCDataElementDesc _desc;
};

VSCDataElementDesc VSCDescHolderC<
    VSCVRMLGroup, 
    VSCVRMLGroup::VSCChildrenFieldCount, 
    VSCDataElementDesc                 >::_desc(
        VSCMFVRMLNode::getClassType(),
        "children",
        VSC_RC_ELEM_IDM_DESC(VSCVRMLGroup::VSCChildrenField),
        false,
        (VSCDataElemGetMethod) &VSCVRMLGroup::getMFChildren,
        NULL,
        NULL,
        VSCDataElementDesc::VSCDefaultBeginEditFunctor,
        VSCDataElementDesc::VSCDefaultEndEditFunctor,
        VSCDataElementDesc::VSCDefaultSyncFunctor);
#endif

static void vrmlGroupDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        MFVRMLNode::getClassType(),
        "children",
        OSG_RC_ELEM_IDM_DESC(VRMLGroup::ChildrenField),
        false,
        (DataElemGetMethod) &VRMLGroup::getMFChildren,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}

VRMLObjectType VRMLGroup::_type(
    "Group",
    "VRMLLimitedNode",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLGroup::createEmpty,
    &VRMLGroup::init, 
/*
    VSCDescHolderC<VSCVRMLGroup, 
                   VSCVRMLGroup::VSCLastElemCount,
                   VSCDataElementDesc            >::
        VSCGetHolder<VSCVRMLGroup::VSCFirstElemId>::getDescVec(),
*/
    vrmlGroupDescInserter,
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

void VRMLGroup::init(void)
{
    VRMLToOSGAction::registerDefaultTrav(
        VRMLGroup::getClassType(),
        osgTypedFunctionFunctor2Ref<VRMLAction::ActionResult,
                                    VRMLNode,
                                    VRMLAction *>(osgVRMLGroupToOpenSG));
}

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

VRMLGroup::VRMLGroup(void) :
 	 Inherited (),
    
    _mfChildren()
{
}

VRMLGroup::VRMLGroup(const VRMLGroup &source) : 
     Inherited(source),

    _mfChildren(source._mfChildren)
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#ifdef WIN32
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLGroup, Ptr);

#ifdef WIN32
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLGroup::~VRMLGroup(void)
{
}

void VRMLGroup::addChild(VRMLNode *pNode)
{
    if(pNode != NULL)
    {
        _mfChildren.push_back(pNode);
    }
}

MFVRMLNode *VRMLGroup::getMFChildren(void)
{
    return &_mfChildren;
}



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

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

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

VRMLGroupBinder::VRMLGroupBinder(void) :
	Inherited()
{
}

VRMLGroupBinder::~VRMLGroupBinder(void)
{
}

void VRMLGroupBinder::init(VRMLToOSGAction *)
{
    NodePtr   pNode = Node ::create();
    GroupPtr pGroup = Group::create();

    beginEditCP(pNode, Node::CoreFieldMask);
    {
        pNode->setCore(pGroup);
    }
    endEditCP  (pNode, Node::CoreFieldMask);

    _pFieldContainer = pNode;
}

void VRMLGroupBinder::addChild(NodePtr pChild)
{
    NodePtr pNode = NodePtr::dcast(_pFieldContainer);

    if(pNode != NullFC && pChild != NullFC)
    {
        beginEditCP(pNode, Node::ChildrenFieldMask);
        {
            pNode->addChild(pChild);
        }
        endEditCP  (pNode, Node::ChildrenFieldMask);
    }
}

void VRMLGroupBinder::finish(VRMLToOSGAction *)
{
}


VRMLAction::ActionResult OSG::osgVRMLGroupToOpenSG(
    VRMLNode   &oNode,
    VRMLAction *pAction)
{
    VRMLAction::ActionResult returnValue = VRMLAction::Continue;

    fprintf(stderr, "Visit Group : %s\n", oNode.getName().str());

    VRMLToOSGAction *pConvAction = 
        dynamic_cast<VRMLToOSGAction *>(pAction);

    VRMLGroup       *pGroup      = 
        dynamic_cast<VRMLGroup       *>(&oNode );

    if(pConvAction != NULL && pGroup != NULL)
    {
        MFVRMLNode::iterator nodeIt  = pGroup->getMFChildren()->begin();
        MFVRMLNode::iterator nodeEnd = pGroup->getMFChildren()->end  (); 
        
        VRMLGroupBinder *pBinder = new VRMLGroupBinder();
        
        pBinder->setNode(pGroup);
        pBinder->init   (pConvAction);
        
        NodePtr                     pNode       = NullFC;
        VRMLBindings::NodeBinderPtr pNodeBinder = NULL;

        while(nodeIt != nodeEnd)
        {
            returnValue = pConvAction->apply(*nodeIt);

            pNodeBinder = (*nodeIt)->getBinder();

            if(pNodeBinder != NULL)
            {
                pNode = OSG::NodePtr::dcast(pNodeBinder->getFCPtr());

                if(pNode != OSG::NullFC)
                {
                    pBinder->addChild(pNode);
                }
            }

            if(returnValue != VRMLAction::Continue)
            {
                break;
            }

            ++nodeIt;
        }

        pBinder->finish(pConvAction);
        oNode.setBinder(pBinder);
    }

    return returnValue;
}
