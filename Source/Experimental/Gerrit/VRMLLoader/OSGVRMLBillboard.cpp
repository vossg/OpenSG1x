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

#include "OSGVRMLBillboard.h"
#include "OSGDataElementDesc.h"

#include <OSGBillboard.h>
#include <OSGVRMLToOSGAction.h>

OSG_USING_NAMESPACE

OSG_BEGIN_NAMESPACE

VRMLAction::ActionResult osgVRMLBillboardToOpenSG(VRMLNode   &oNode,
                                                  VRMLAction *pAction);

OSG_END_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlBillboardDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        SFVec3f::getClassType(),
        "axisOfRotation",
        OSG_RC_ELEM_IDM_DESC(VRMLBillboard::AxisOfRotationField),
        false,
        (DataElemGetMethod) &VRMLBillboard::getSFAxisOfRotation,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}


VRMLObjectType VRMLBillboard::_type(
    "Billboard",
    "Group",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLBillboard::createEmpty,
    &VRMLBillboard::init,
    vrmlBillboardDescInserter,
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

void VRMLBillboard::init(void)
{
    VRMLToOSGAction::registerDefaultTrav(
        VRMLBillboard::getClassType(),
        osgTypedFunctionFunctor2Ref<VRMLAction::ActionResult,
                                    VRMLNode,
                                    VRMLAction *>(osgVRMLBillboardToOpenSG));
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

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLBillboard, Ptr);

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLBillboard::VRMLBillboard(void) :
	 Inherited       (),
    _sfAxisOfRotation()
{
    _sfAxisOfRotation.getValue().setValues(0.f, 1.f, 0.f);
}


VRMLBillboard::VRMLBillboard(const VRMLBillboard &source) :
     Inherited       (source                  ),
    _sfAxisOfRotation(source._sfAxisOfRotation)
{
}

VRMLBillboard::~VRMLBillboard(void)
{
}

/*------------------------------ access -----------------------------------*/

SFVec3f *VRMLBillboard::getSFAxisOfRotation(void)
{
    return &_sfAxisOfRotation;
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

VRMLBillboardBinder::VRMLBillboardBinder(void) :
	Inherited()
{
}

VRMLBillboardBinder::~VRMLBillboardBinder(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLBillboardBinder::init(VRMLToOSGAction *)
{
    if(_pNode == NULL)
        return;

    VRMLBillboard *pNode = dynamic_cast<VRMLBillboard *>(_pNode);

    if(pNode == NULL)
        return;

    NodePtr      pBNode     = Node     ::create();
    BillboardPtr pBillboard = Billboard::create();

    beginEditCP(pBNode, Node::CoreFieldMask);
    {
        pBNode->setCore(pBillboard);
    }
    endEditCP  (pBNode, Node::CoreFieldMask);

    Vec3f v;

    v.setValues(pNode->getSFAxisOfRotation()->getValue()[0],
                pNode->getSFAxisOfRotation()->getValue()[1],
                pNode->getSFAxisOfRotation()->getValue()[2]);

    beginEditCP(pBillboard, Billboard::AxisOfRotationFieldMask);
    {
        pBillboard->setAxisOfRotation(v);
    }
    endEditCP  (pBillboard, Billboard::AxisOfRotationFieldMask);

    _pFieldContainer = pBNode;
}

void VRMLBillboardBinder::addChild(NodePtr pChild)
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

void VRMLBillboardBinder::finish(VRMLToOSGAction *)
{
}


VRMLAction::ActionResult OSG::osgVRMLBillboardToOpenSG(
    VRMLNode   &oNode,
    VRMLAction *pAction)
{
    VRMLAction::ActionResult returnValue = VRMLAction::Continue;

    fprintf(stderr, "Visit Billboard : %s\n", oNode.getName().str());

    VRMLToOSGAction *pConvAction = 
        dynamic_cast<VRMLToOSGAction *>(pAction);

    VRMLBillboard   *pBillboard  = 
        dynamic_cast<VRMLBillboard   *>(&oNode );

    if(pConvAction != NULL && pBillboard != NULL)
    {
        MFVRMLNode::iterator nodeIt  = pBillboard->getMFChildren()->begin();
        MFVRMLNode::iterator nodeEnd = pBillboard->getMFChildren()->end  ();

        VRMLBillboardBinder *pBinder = new VRMLBillboardBinder();

        pBinder->setNode(pBillboard);
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
    static Char8 cvsid_hpp[] = OSGVRMLBILLBOARD_HEADER_CVSID;
}
