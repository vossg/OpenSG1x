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

#include "OSGSimpleAttachments.h"
#include "OSGVRMLTransform.h"
#include "OSGDataElementDesc.h"
#include "OSGVRMLToOSGAction.h"

OSG_USING_NAMESPACE

OSG_BEGIN_NAMESPACE

VRMLAction::ActionResult osgVRMLTransformToOpenSG(VRMLNode   &oNode,
                                                  VRMLAction *pAction);

OSG_END_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlTransformDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        SFVec3f::getClassType(),
        "center",
        OSG_RC_ELEM_IDM_DESC(VRMLTransform::CenterField),
        false,
        (DataElemGetMethod) &VRMLTransform::getSFCenter,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFRotation::getClassType(),
        "rotation",
        OSG_RC_ELEM_IDM_DESC(VRMLTransform::RotationField),
        false,
        (DataElemGetMethod) &VRMLTransform::getSFRotation,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFVec3f::getClassType(),
        "scale",
        OSG_RC_ELEM_IDM_DESC(VRMLTransform::ScaleField),
        false,
        (DataElemGetMethod) &VRMLTransform::getSFScale,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFRotation::getClassType(),
        "scaleOrientation",
        OSG_RC_ELEM_IDM_DESC(VRMLTransform::ScaleOrientationField),
        false,
        (DataElemGetMethod) &VRMLTransform::getSFScaleOrientation,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFVec3f::getClassType(),
        "translation",
        OSG_RC_ELEM_IDM_DESC(VRMLTransform::TranslationField),
        false,
        (DataElemGetMethod) &VRMLTransform::getSFTranslation,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}


VRMLObjectType VRMLTransform::_type(
    "Transform",
    "Group",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLTransform::createEmpty,
    VRMLTransform::init,
    vrmlTransformDescInserter,
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

void VRMLTransform::init(void)
{
    VRMLToOSGAction::registerDefaultTrav(
        VRMLTransform::getClassType(),
        osgTypedFunctionFunctor2Ref<VRMLAction::ActionResult,
                                    VRMLNode,
                                    VRMLAction *>(osgVRMLTransformToOpenSG));
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

VRMLTransform::VRMLTransform(void) :
	 Inherited         (),
    _sfCenter          (),
    _sfRotation        (),
    _sfScale           (),
    _sfScaleOrientation(),
    _sfTranslation     ()
{
    _sfCenter          .getValue().setValues     (0.f, 0.f, 0.f     );   
    _sfRotation        .getValue().setValueAsQuat(0.f, 0.f, 0.f, 1.f);
    _sfScale           .getValue().setValues     (1.f, 1.f, 1.f     );
    _sfScaleOrientation.getValue().setValueAsQuat(0.f, 0.f, 0.f, 1.f);
    _sfTranslation     .getValue().setValues     (0.f, 0.f, 0.f     );
}


VRMLTransform::VRMLTransform(const VRMLTransform &source) :
	 Inherited         (source                    ),
    _sfCenter          (source._sfCenter          ),
    _sfRotation        (source._sfRotation        ),
    _sfScale           (source._sfScale           ),
    _sfScaleOrientation(source._sfScaleOrientation),
    _sfTranslation     (source._sfTranslation     )
{
}


/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLTransform, Ptr);

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLTransform::~VRMLTransform(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLTransform::setElement(Field  *pField, 
                               UInt32  uiElementId)
{
    if(uiElementId == CenterFieldId)
    {
        SFVec3f             *pCenter = 
            dynamic_cast<SFVec3f             *>(pField);
        VRMLTransformBinder *pBinder = 
            dynamic_cast<VRMLTransformBinder *>(_pBinder);

        if(pCenter != NULL && pBinder != NULL)
        {
            pBinder->setCenter(pCenter->getValue());
        }
    }
    else if(uiElementId == RotationFieldId)
    {
        SFQuaternion        *pRot    = 
            dynamic_cast<SFQuaternion        *>(pField);
        VRMLTransformBinder *pBinder = 
            dynamic_cast<VRMLTransformBinder *>(_pBinder);

        if(pRot != NULL && pBinder != NULL)
        {
            pBinder->setRotation(pRot->getValue());
        }
    }
    else if(uiElementId == ScaleFieldId)
    {
        SFVec3f             *pScale  = 
            dynamic_cast<SFVec3f             *>(pField);
        VRMLTransformBinder *pBinder = 
            dynamic_cast<VRMLTransformBinder *>(_pBinder);

        if(pScale != NULL && pBinder != NULL)
        {
            pBinder->setScale(pScale->getValue());
        }
    }
    else if(uiElementId == ScaleOrientationFieldId)
    {
        SFQuaternion        *pScaleOri = 
            dynamic_cast<SFQuaternion        *>(pField);
        VRMLTransformBinder *pBinder   = 
            dynamic_cast<VRMLTransformBinder *>(_pBinder);

        if(pScaleOri != NULL && pBinder != NULL)
        {
            pBinder->setScaleOrientation(pScaleOri->getValue());
        }
    }
    else if(uiElementId == TranslationFieldId)
    {
        SFVec3f             *pTranslation = 
            dynamic_cast<SFVec3f *>(pField);
        VRMLTransformBinder *pBinder      = 
            dynamic_cast<VRMLTransformBinder *>(_pBinder);

        if(pTranslation != NULL && pBinder != NULL)
        {
            pBinder->setTranslation(pTranslation->getValue());
        }
    }
}


SFVec3f *VRMLTransform::getSFCenter(void)
{
    return &_sfCenter;
}

SFRotation *VRMLTransform::getSFRotation(void)
{
    return &_sfRotation;
}

SFVec3f *VRMLTransform::getSFScale(void)
{
    return &_sfScale;
}

SFRotation *VRMLTransform::getSFScaleOrientation(void)
{
    return &_sfScaleOrientation;
}

SFVec3f *VRMLTransform::getSFTranslation(void)
{
    return &_sfTranslation;
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

VRMLTransformBinder::VRMLTransformBinder(void) :
	 Inherited (           ),
    _pTransform(OSG::NullFC)
{
}

VRMLTransformBinder::~VRMLTransformBinder(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLTransformBinder::init(VRMLToOSGAction *)
{
    if(_pNode == NULL)
        return;

    VRMLTransform *pNode = dynamic_cast<VRMLTransform *>(_pNode);

    if(pNode == NULL)
        return;

    OSG::NodePtr pTrNode = OSG::Node              ::create();

    _pTransform          = OSG::ComponentTransform::create();

    OSG::Vec3f       v;
    OSG::Quaternion  q;

    OSG::beginEditCP(_pTransform);
    {
        v.setValues(pNode->getSFCenter()->getValue()[0],
                    pNode->getSFCenter()->getValue()[1],
                    pNode->getSFCenter()->getValue()[2]);

        _pTransform->setCenter(v);

        q.setValueAsQuat(pNode->getSFRotation()->getValue()[0],
                         pNode->getSFRotation()->getValue()[1],
                         pNode->getSFRotation()->getValue()[2],
                         pNode->getSFRotation()->getValue()[3]);
        
        _pTransform->setRotation(q);

        v.setValues(pNode->getSFScale()->getValue()[0],
                    pNode->getSFScale()->getValue()[1],
                    pNode->getSFScale()->getValue()[2]);

        _pTransform->setScale(v);

        q.setValueAsQuat(pNode->getSFScaleOrientation()->getValue()[0],
                         pNode->getSFScaleOrientation()->getValue()[1],
                         pNode->getSFScaleOrientation()->getValue()[2],
                         pNode->getSFScaleOrientation()->getValue()[3]);
        
        _pTransform->setScaleOrientation(q);

        v.setValues(pNode->getSFTranslation()->getValue()[0],
                    pNode->getSFTranslation()->getValue()[1],
                    pNode->getSFTranslation()->getValue()[2]);

        _pTransform->setTranslation(v);
    }
    OSG::endEditCP  (_pTransform);

    if(pNode->getName().str() != NULL)
    {
        NamePtr node_name = Name::create();
        beginEditCP(node_name);
            node_name->getFieldPtr()->setValue(pNode->getName().str());
        endEditCP(node_name);
        beginEditCP(pTrNode,  Node::AttachmentsFieldMask);
            pTrNode->addAttachment(node_name);
        endEditCP  (pTrNode, Node::AttachmentsFieldMask);
    }

    OSG::beginEditCP(pTrNode, OSG::Node::CoreFieldMask);
    {
        pTrNode->setCore(_pTransform);
    }
    OSG::endEditCP  (pTrNode, OSG::Node::CoreFieldMask);
    
    _pFieldContainer = pTrNode;
}

void VRMLTransformBinder::addChild(OSG::NodePtr pChild)
{
    OSG::NodePtr pNode = OSG::NodePtr::dcast(_pFieldContainer);

    if(pNode != OSG::NullFC && pChild != OSG::NullFC)
    {
        OSG::beginEditCP(pNode, OSG::Node::ChildrenFieldMask);
        {
            pNode->addChild(pChild);
        }
        OSG::endEditCP  (pNode, OSG::Node::ChildrenFieldMask);
    }
}

void VRMLTransformBinder::finish(VRMLToOSGAction *)
{
}

void VRMLTransformBinder::setCenter(Vec3f &vCenter)
{
    if(_pTransform == OSG::NullFC)
        return;

    OSG::Vec3f v;

    v.setValues(vCenter[0],
                vCenter[1],
                vCenter[2]);

    OSG::beginEditCP(_pTransform, OSG::ComponentTransform::CenterFieldMask);
    {
        _pTransform->setCenter(v);
    }
    OSG::endEditCP  (_pTransform, OSG::ComponentTransform::CenterFieldMask);
}

void VRMLTransformBinder::setRotation(Quaternion &qRotation)
{
    if(_pTransform == OSG::NullFC)
        return;

    OSG::Quaternion q;

    q.setValueAsQuat(qRotation[0],
                     qRotation[1],
                     qRotation[2],
                     qRotation[3]);

    OSG::beginEditCP(_pTransform, OSG::ComponentTransform::RotationFieldMask);
    {
        _pTransform->setRotation(q);
    }
    OSG::endEditCP  (_pTransform, OSG::ComponentTransform::RotationFieldMask);
}

void VRMLTransformBinder::setScale(Vec3f &vScale)
{
    if(_pTransform == OSG::NullFC)
        return;

    OSG::Vec3f v;

    v.setValues(vScale[0],
                vScale[1],
                vScale[2]);

    OSG::beginEditCP(_pTransform, OSG::ComponentTransform::ScaleFieldMask);
    {
        _pTransform->setScale(v);
    }
    OSG::endEditCP  (_pTransform, OSG::ComponentTransform::ScaleFieldMask);
}

void VRMLTransformBinder::setScaleOrientation(Quaternion &qScaleOri)
{
    if(_pTransform == OSG::NullFC)
        return;

    OSG::Quaternion q;

    q.setValueAsQuat(qScaleOri[0],
                     qScaleOri[1],
                     qScaleOri[2],
                     qScaleOri[3]);

    OSG::beginEditCP(_pTransform, 
                     OSG::ComponentTransform::ScaleOrientationFieldMask);
    {
        _pTransform->setScaleOrientation(q);
    }
    OSG::endEditCP  (_pTransform, 
                     OSG::ComponentTransform::ScaleOrientationFieldMask);
}

void VRMLTransformBinder::setTranslation(Vec3f &vTrans)
{
    if(_pTransform == OSG::NullFC)
        return;

    OSG::Vec3f v;

    v.setValues(vTrans[0],
                vTrans[1],
                vTrans[2]);

    OSG::beginEditCP(_pTransform, 
                     OSG::ComponentTransform::TranslationFieldMask);
    {
        _pTransform->setTranslation(v);
    }
    OSG::endEditCP  (_pTransform, 
                     OSG::ComponentTransform::TranslationFieldMask);
}

VRMLAction::ActionResult OSG::osgVRMLTransformToOpenSG(
    VRMLNode   &oNode,
    VRMLAction *pAction)
{
    VRMLAction::ActionResult returnValue = VRMLAction::Continue;

    fprintf(stderr, "Visit Transform : %s\n", oNode.getName().str());

    VRMLToOSGAction *pConvAction = 
        dynamic_cast<VRMLToOSGAction *>(pAction);

    VRMLTransform   *pTrans      = 
        dynamic_cast<VRMLTransform  *>(&oNode );

    if(pConvAction != NULL && pTrans != NULL)
    {
        MFVRMLNode::iterator nodeIt  = pTrans->getMFChildren()->begin();
        MFVRMLNode::iterator nodeEnd = pTrans->getMFChildren()->end  (); 

        VRMLTransformBinder *pBinder = new VRMLTransformBinder();

        pBinder->setNode(pTrans);
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
    static Char8 cvsid_hpp[] = OSGVRMLTRANSFORM_HEADER_CVSID;
}
