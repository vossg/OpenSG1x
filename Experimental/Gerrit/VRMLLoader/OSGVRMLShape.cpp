/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

#include "OSGVRMLShape.h"
#include "OSGDataElementDesc.h"
#include "OSGVRMLToOSGAction.h"
#include "OSGGroup.h"
#include "OSGMaterialGroup.h"

OSG_USING_NAMESPACE

OSG_BEGIN_NAMESPACE

VRMLAction::ActionResult osgVRMLShapeToOpenSG(VRMLNode   &oNode,
                                              VRMLAction *pAction);

OSG_END_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlShapeDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        SFVRMLNode::getClassType(),
        "appearance",
        OSG_RC_ELEM_IDM_DESC(VRMLShape::AppearanceField),
        false,
        (DataElemGetMethod) &VRMLShape::getSFAppearance,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFVRMLNode::getClassType(),
        "geometry",
        OSG_RC_ELEM_IDM_DESC(VRMLShape::GeometryField),
        false,
        (DataElemGetMethod) &VRMLShape::getSFGeometry,
        NULL,
        NULL);
    
    pType->addInitialDesc(pDesc);
}

VRMLObjectType VRMLShape::_type(
    "Shape",
    "VRMLUnlimitedNode",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLShape::createEmpty,
    VRMLShape::init, // Init
    vrmlShapeDescInserter,
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

void VRMLShape::init(void)
{
    VRMLToOSGAction::registerDefaultTrav(
        VRMLShape::getClassType(),
        osgTypedFunctionFunctor2Ref<VRMLAction::ActionResult,
                                    VRMLNode,
                                    VRMLAction *>(osgVRMLShapeToOpenSG));
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

VRMLShape::VRMLShape(void) :
     Inherited   (    ),
    _sfAppearance(NULL),
    _sfGeometry  (NULL)
{   
}

VRMLShape::VRMLShape(const VRMLShape &source) :
     Inherited   (source              ),
    _sfAppearance(source._sfAppearance),
    _sfGeometry  (source._sfGeometry  )
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLShape, Ptr);

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLShape::~VRMLShape(void)
{
}

SFVRMLNode *VRMLShape::getSFAppearance(void)
{
    return &_sfAppearance;
}

SFVRMLNode *VRMLShape::getSFGeometry(void)
{
    return &_sfGeometry;
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

VRMLShapeBinder::VRMLShapeBinder(void) :
	Inherited()
{
}

VRMLShapeBinder::~VRMLShapeBinder(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLShapeBinder::init(VRMLToOSGAction *)
{
    NodePtr          pMatNode  = Node         ::create();
    MaterialGroupPtr pMatGroup = MaterialGroup::create();
    
    beginEditCP(pMatNode, Node::CoreFieldMask);
    {
        pMatNode->setCore(pMatGroup);
    }
    endEditCP  (pMatNode, Node::CoreFieldMask);

    _pFieldContainer = pMatNode;

    NodePtr          pGeoNode  = Node::create();
    
    beginEditCP(pMatNode, Node::ChildrenFieldMask);
    {
        pMatNode->addChild(pGeoNode);
    }
    endEditCP  (pMatNode, Node::ChildrenFieldMask);
}

void VRMLShapeBinder::setAppearance(MaterialPtr pMat)
{
    if(pMat == NullFC)
        return;

    NodePtr pMatNode = NodePtr::dcast(_pFieldContainer);

    if(pMatNode != NullFC)
    {
        MaterialGroupPtr pMatGroup = 
            MaterialGroupPtr::dcast(pMatNode->getCore());

        if(pMatGroup != NullFC)
        {
            beginEditCP(pMatGroup, MaterialGroup::MaterialFieldMask);
            {
                pMatGroup->setMaterial(pMat);
            }
            endEditCP  (pMatGroup, MaterialGroup::MaterialFieldMask);
        }
    }
}

void VRMLShapeBinder::setGeometry(GeometryPtr pGeo)
{
    if(pGeo == NullFC)
        return;

    NodePtr pMatNode = NodePtr::dcast(_pFieldContainer);

    if(pMatNode != NullFC)
    {
        NodePtr pGeoNode = pMatNode->getChild(0);

        if(pGeoNode != NullFC)
        {
            beginEditCP(pGeoNode, Node::CoreFieldMask);
            {
                pGeoNode->setCore(pGeo);
            }
            endEditCP  (pGeoNode, Node::CoreFieldMask);
        }
    }
}

void VRMLShapeBinder::finish(VRMLToOSGAction *)
{
    NodePtr pMatNode = NodePtr::dcast(_pFieldContainer);

    if(pMatNode != NullFC)
    {
        NodePtr pGeoNode = pMatNode->getChild(0);

        if(pGeoNode            != NullFC &&
           pGeoNode->getCore() == NullFC)
        {
            GroupPtr pGroup = Group::create();

            beginEditCP(pGeoNode, Node::CoreFieldMask);
            {
                pGeoNode->setCore(pGroup);
            }
            endEditCP  (pGeoNode, Node::CoreFieldMask);
        }
    }
}



VRMLAction::ActionResult OSG::osgVRMLShapeToOpenSG(VRMLNode   &oNode,
                                                   VRMLAction *pAction)
{
    VRMLAction::ActionResult returnValue = VRMLAction::Continue;

//    fprintf(stderr, "Visit Shape : %s\n", oNode.getName().getString());

    VRMLToOSGAction *pConvAction = 
        dynamic_cast<VRMLToOSGAction *>(pAction);

    VRMLShape       *pShape      =
        dynamic_cast<VRMLShape       *>(&oNode );

    if(pConvAction != NULL && pShape != NULL)
    {
        VRMLShapeBinder *pBinder = new VRMLShapeBinder();

        GeometryPtr                 pGeo        = NullFC;
        MaterialPtr                 pMat        = NullFC;
        VRMLBindings::NodeBinderPtr pNodeBinder = NULL;

        pBinder->setNode(pShape);
        pBinder->init   (pConvAction);

        returnValue = 
            pConvAction->apply(pShape->getSFGeometry()->getValue());

        if(pShape->getSFGeometry()->getValue() != NULL)
        {
            pNodeBinder = pShape->getSFGeometry()->getValue()->getBinder();

            if(pNodeBinder != NULL)
            {
                pGeo = GeometryPtr::dcast(pNodeBinder->getFCPtr());

                if(pGeo != NullFC)
                {
                    pBinder->setGeometry(pGeo);
                }
                else
                {
                    fprintf(stderr, "S2OSG : Error no geo\n");
                }
            } 
            else
            {
                fprintf(stderr, "S2OSG : error no geo binder\n");
            }
        }

        if(returnValue == VRMLAction::Continue)
        {
            returnValue = 
                pConvAction->apply(pShape->getSFAppearance()->getValue());
        }

        if(pShape->getSFAppearance()->getValue() != NULL)
        {
            pNodeBinder = pShape->getSFAppearance()->getValue()->getBinder();
            
            if(pNodeBinder != NULL)
            {
                pMat = MaterialPtr::dcast(pNodeBinder->getFCPtr());
                
                if(pMat != NullFC)
                {
                    pBinder->setAppearance(pMat);
                }
                else
                {
                    fprintf(stderr, "S2OSG : Error no mat\n");
                }
            } 
            else
            {
                fprintf(stderr, "S2OSG : error no mat binder\n");
            }
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
    static Char8 cvsid_hpp[] = OSGVRMLSHAPE_HEADER_CVSID;
}
