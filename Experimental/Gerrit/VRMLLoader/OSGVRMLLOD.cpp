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

#include "OSGVRMLLOD.h"

#include <OSGDistanceLOD.h>
#include <OSGVRMLToOSGAction.h>

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGVRMLLOD_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_BEGIN_NAMESPACE

VRMLAction::ActionResult osgVRMLLODToOpenSG(VRMLNode   &oNode,
                                            VRMLAction *pAction);


OSG_END_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlLODDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        MFVRMLNode::getClassType(),
        "level",
        OSG_RC_ELEM_IDM_DESC(VRMLLOD::LevelField),
        false,
        (DataElemGetMethod) &VRMLLOD::getMFLevel,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFVec3f::getClassType(),
        "center",
        OSG_RC_ELEM_IDM_DESC(VRMLLOD::CenterField),
        false,
        (DataElemGetMethod) &VRMLLOD::getSFCenter,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFReal32::getClassType(),
        "range",
        OSG_RC_ELEM_IDM_DESC(VRMLLOD::RangeField),
        false,
        (DataElemGetMethod) &VRMLLOD::getMFRange,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}

VRMLObjectType VRMLLOD::_type(
    "LOD",
    "VRMLUnlimitedNode",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLLOD::createEmpty,
    VRMLLOD::init,
    vrmlLODDescInserter,
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

void VRMLLOD::init(void)
{
    VRMLToOSGAction::registerDefaultTrav(
        VRMLLOD::getClassType(),
        osgTypedFunctionFunctor2Ref<VRMLAction::ActionResult,
                                    VRMLNode,
                                    VRMLAction *>(osgVRMLLODToOpenSG));
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

VRMLLOD::VRMLLOD(void) :
	 Inherited(),
    _mfLevel  (),
    _sfCenter (),
    _mfRange  ()
{
    _sfCenter.getValue().setValues(0.f, 0.f, 0.f);
}


VRMLLOD::VRMLLOD(const VRMLLOD &source) :
	 Inherited(source          ),
    _mfLevel  (source._mfLevel ),
    _sfCenter (source._sfCenter),
    _mfRange  (source._mfRange )
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#ifdef WIN32
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLLOD, Ptr);

#ifdef WIN32
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLLOD::~VRMLLOD(void)
{
}

/*------------------------------ access -----------------------------------*/

MFVRMLNode *VRMLLOD::getMFLevel(void)
{
    return &_mfLevel;
}

SFVec3f *VRMLLOD::getSFCenter(void)
{
    return &_sfCenter;
}

MFReal32 *VRMLLOD::getMFRange(void)
{
    return &_mfRange;
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

VRMLLODBinder::VRMLLODBinder(void) :
	Inherited()
{
}

VRMLLODBinder::~VRMLLODBinder(void)
{
}

void VRMLLODBinder::init(VRMLToOSGAction *)
{
    if(_pNode == NULL)
        return;

    VRMLLOD *pNode = dynamic_cast<VRMLLOD *>(_pNode);

    if(pNode == NULL)
        return;

    NodePtr        pLODNode = Node       ::create();
    DistanceLODPtr pLOD     = DistanceLOD::create();

    beginEditCP(pLODNode, Node::CoreFieldMask);
    {
        pLODNode->setCore(pLOD);
    }
    endEditCP  (pLODNode, Node::CoreFieldMask);

    _pFieldContainer = pLODNode;
}

void VRMLLODBinder::addLevel(NodePtr pLevel)
{
    NodePtr pNode = NodePtr::dcast(_pFieldContainer);

    if(pNode != NullFC && pLevel != NullFC)
    {
        beginEditCP(pNode, Node::ChildrenFieldMask);
        {
            pNode->addChild(pLevel);
        }
        endEditCP  (pNode, Node::ChildrenFieldMask);
    }
}

void VRMLLODBinder::finish(VRMLToOSGAction *)
{
    if(_pNode == NULL)
        return;

    VRMLLOD *pNode = dynamic_cast<VRMLLOD *>(_pNode);

    if(pNode == NULL)
        return;
    
    NodePtr pLODNode    = NodePtr::dcast(_pFieldContainer);

    if(pLODNode == NullFC)
        return;

    DistanceLODPtr pLOD = 
        DistanceLODPtr::dcast(pLODNode->getCore());
    
    if(pLOD == NullFC)
        return;

    UInt32    uiNumRanges;

    beginEditCP(pLOD, DistanceLOD::RangeFieldMask);
    {
        if(pNode->getMFRange()->empty() == false)
        {
            uiNumRanges = pNode->getMFRange()->size();
            
            pLOD->getMFRange()->resize(uiNumRanges);
            
            memcpy(&(pLOD ->getMFRange()->front()),
                   &(pNode->getMFRange()->front()),
                   sizeof(Real32) * uiNumRanges);
        }
    }
    endEditCP  (pLOD, DistanceLOD::RangeFieldMask);

    Vec3f v;

    beginEditCP(pLOD, DistanceLOD::CenterFieldMask);
    {
        v.setValues(pNode->getSFCenter()->getValue()[0],
                    pNode->getSFCenter()->getValue()[1],
                    pNode->getSFCenter()->getValue()[2]);

        pLOD->setCenter(v);
    }
    beginEditCP(pLOD, DistanceLOD::CenterFieldMask);
}


VRMLAction::ActionResult OSG::osgVRMLLODToOpenSG(
    VRMLNode   &oNode,
    VRMLAction *pAction)
{
    VRMLAction::ActionResult returnValue = VRMLAction::Continue;

    fprintf(stderr, "Visit LOD : %s\n", oNode.getName().str());

    VRMLToOSGAction *pConvAction = 
        dynamic_cast<VRMLToOSGAction *>(pAction);

    VRMLLOD         *pLOD        = 
        dynamic_cast<VRMLLOD         *>(&oNode );

    if(pConvAction != NULL && pLOD != NULL)
    {
        MFVRMLNode::iterator nodeIt  = pLOD->getMFLevel()->begin();
        MFVRMLNode::iterator nodeEnd = pLOD->getMFLevel()->end  (); 

        VRMLLODBinder *pBinder = new VRMLLODBinder();

        pBinder->setNode(pLOD);
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
                    pBinder->addLevel(pNode);
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
