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

#include "OSGVRMLSwitch.h"
#include "OSGDataElementDesc.h"

#include <OSGSwitch.h>
#include <OSGVRMLToOSGAction.h>

OSG_USING_NAMESPACE

OSG_BEGIN_NAMESPACE

VRMLAction::ActionResult osgVRMLSwitchToOpenSG(VRMLNode   &oNode,
                                               VRMLAction *pAction);


OSG_END_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlSwitchDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        MFVRMLNode::getClassType(),
        "choice",
        OSG_RC_ELEM_IDM_DESC(VRMLSwitch::ChoiceField),
        false,
        (DataElemGetMethod) &VRMLSwitch::getMFChoice,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFInt32::getClassType(),
        "whichChoice",
        OSG_RC_ELEM_IDM_DESC(VRMLSwitch::WhichChoiceField),
        false,
        (DataElemGetMethod) &VRMLSwitch::getSFWhichChoice,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}

VRMLObjectType VRMLSwitch::_type(
    "Switch",
    "VRMLUnlimitedNode",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLSwitch::createEmpty,
    &VRMLSwitch::init,
    vrmlSwitchDescInserter,
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

void VRMLSwitch::init(void)
{
    VRMLToOSGAction::registerDefaultTrav(
        VRMLSwitch::getClassType(),
        osgTypedFunctionFunctor2Ref<VRMLAction::ActionResult,
                                    VRMLNode,
                                    VRMLAction *>(osgVRMLSwitchToOpenSG));
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

VRMLSwitch::VRMLSwitch(void) :
     Inherited (),
    
    _mfChoice     (  ),
    _sfWhichChoice(-1)
{
}

VRMLSwitch::VRMLSwitch(const VRMLSwitch &source) : 
     Inherited(source),

    _mfChoice     (source._mfChoice     ),
    _sfWhichChoice(source._sfWhichChoice)
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLSwitch, Ptr);

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLSwitch::~VRMLSwitch(void)
{
}

void VRMLSwitch::setWhichChoice(Int32 iChoice)
{
    _sfWhichChoice.setValue(iChoice);
}

void VRMLSwitch::addChoice(VRMLNode *pChoice)
{
    _mfChoice.push_back(pChoice);
}

MFVRMLNode *VRMLSwitch::getMFChoice(void)
{
    return &_mfChoice;
}

SFInt32 *VRMLSwitch::getSFWhichChoice(void)
{
    return &_sfWhichChoice;
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

VRMLSwitchBinder::VRMLSwitchBinder(void) :
	Inherited()
{
}

VRMLSwitchBinder::~VRMLSwitchBinder(void)
{
}

void VRMLSwitchBinder::init(VRMLToOSGAction *)
{
    if(_pNode == NULL)
        return;

    VRMLSwitch *pNode = dynamic_cast<VRMLSwitch *>(_pNode);

    if(pNode == NULL)
        return;

    NodePtr   pSwNode = Node  ::create();
    SwitchPtr pSwitch = Switch::create();

    beginEditCP(pSwitch, Switch::ChoiceFieldMask);
    {
        pSwitch->setChoice(pNode->getSFWhichChoice()->getValue());
    }
    endEditCP  (pSwitch, Switch::ChoiceFieldMask);

    beginEditCP(pSwNode, Node::CoreFieldMask);
    {
        pSwNode->setCore(pSwitch);
    }
    endEditCP  (pSwNode, Node::CoreFieldMask);

    _pFieldContainer = pSwNode;
}

void VRMLSwitchBinder::addChoice(NodePtr pChoice)
{
    NodePtr pNode = NodePtr::dcast(_pFieldContainer);

    if(pNode != NullFC && pChoice != NullFC)
    {
        beginEditCP(pNode, Node::ChildrenFieldMask);
        {
            pNode->addChild(pChoice);
        }
        endEditCP  (pNode, Node::ChildrenFieldMask);
    }
}

void VRMLSwitchBinder::finish(VRMLToOSGAction *)
{
}


VRMLAction::ActionResult OSG::osgVRMLSwitchToOpenSG(
    VRMLNode   &oNode,
    VRMLAction *pAction)
{
    VRMLAction::ActionResult returnValue = VRMLAction::Continue;

    fprintf(stderr, "Visit Switch : %s\n", oNode.getName().str());

    VRMLToOSGAction *pConvAction = 
        dynamic_cast<VRMLToOSGAction *>(pAction);

    VRMLSwitch      *pSwitch     = 
        dynamic_cast<VRMLSwitch      *>(&oNode );

    if(pConvAction != NULL && pSwitch != NULL)
    {
        MFVRMLNode::iterator nodeIt  = pSwitch->getMFChoice()->begin();
        MFVRMLNode::iterator nodeEnd = pSwitch->getMFChoice()->end  (); 

        VRMLSwitchBinder *pBinder = new VRMLSwitchBinder();

        pBinder->setNode(pSwitch);
        pBinder->init   (pConvAction);

        NodePtr                     pNode       = NullFC;
        VRMLBindings::NodeBinderPtr pNodeBinder = NULL;

        while(nodeIt != nodeEnd)
        {
            returnValue = pConvAction->apply(*nodeIt);

            pNodeBinder = (*nodeIt)->getBinder();

            if(pNodeBinder != NULL)
            {
                pNode = NodePtr::dcast(pNodeBinder->getFCPtr());

                if(pNode != NullFC)
                {
                    pBinder->addChoice(pNode);
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
    static Char8 cvsid_hpp[] = OSGVRMLSWITCH_HEADER_CVSID;
}
