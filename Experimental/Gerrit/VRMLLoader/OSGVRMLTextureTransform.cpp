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

#include "OSGVRMLTextureTransform.h"
#include "OSGDataElementDesc.h"
#include "OSGVRMLToOSGAction.h"

#include <OSGTextureTransformChunk.h>

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGVRMLTEXTURETRANSFORM_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_BEGIN_NAMESPACE

VRMLAction::ActionResult osgVRMLTextureTransformToOpenSG(VRMLNode   &oNode,
                                                         VRMLAction *pAction);

OSG_END_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlTextureTransformDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        SFVec2f::getClassType(),
        "center",
        OSG_RC_ELEM_IDM_DESC(VRMLTextureTransform::CenterField),
        false,
        (DataElemGetMethod) &VRMLTextureTransform::getSFCenter,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "rotation",
        OSG_RC_ELEM_IDM_DESC(VRMLTextureTransform::RotationField),
        false,
        (DataElemGetMethod) &VRMLTextureTransform::getSFRotation,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFVec2f::getClassType(),
        "scale",
        OSG_RC_ELEM_IDM_DESC(VRMLTextureTransform::ScaleField),
        false,
        (DataElemGetMethod) &VRMLTextureTransform::getSFScale,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFVec2f::getClassType(),
        "translation",
        OSG_RC_ELEM_IDM_DESC(VRMLTextureTransform::TranslationField),
        false,
        (DataElemGetMethod) &VRMLTextureTransform::getSFTranslation,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}


VRMLObjectType VRMLTextureTransform::_type(
    "TextureTransform",
    "Group",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLTextureTransform::createEmpty,
    &VRMLTextureTransform::init,
    vrmlTextureTransformDescInserter,
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

void VRMLTextureTransform::init(void)
{
    VRMLToOSGAction::registerDefaultTrav(
        VRMLTextureTransform::getClassType(),
        osgTypedFunctionFunctor2Ref<VRMLAction::ActionResult,
                                    VRMLNode,
                                    VRMLAction *>(
                                        osgVRMLTextureTransformToOpenSG));
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

VRMLTextureTransform::VRMLTextureTransform(void) :
	 Inherited         (   ),
    _sfCenter          (   ),
    _sfRotation        (0.f),
    _sfScale           (   ),
    _sfTranslation     (   )
{
    _sfCenter          .getValue().setValues        (0.f, 0.f);   
    _sfScale           .getValue().setValues        (1.f, 1.f);
    _sfTranslation     .getValue().setValues        (0.f, 0.f);
}


VRMLTextureTransform::VRMLTextureTransform(
    const VRMLTextureTransform &source) :

	 Inherited         (source                    ),
    _sfCenter          (source._sfCenter          ),
    _sfRotation        (source._sfRotation        ),
    _sfScale           (source._sfScale           ),
    _sfTranslation     (source._sfTranslation     )
{
}


/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#ifdef WIN32
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLTextureTransform, Ptr);

#ifdef WIN32
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLTextureTransform::~VRMLTextureTransform(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLTextureTransform::setElement(Field  *pField, 
                                      UInt32  uiElementId)
{
/*
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
        SFQuaternionf       *pRot    = 
            dynamic_cast<SFQuaternionf       *>(pField);
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
        SFQuaternionf       *pScaleOri = 
            dynamic_cast<SFQuaternionf       *>(pField);
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
*/
}


SFVec2f *VRMLTextureTransform::getSFCenter(void)
{
    return &_sfCenter;
}

SFReal32 *VRMLTextureTransform::getSFRotation(void)
{
    return &_sfRotation;
}

SFVec2f *VRMLTextureTransform::getSFScale(void)
{
    return &_sfScale;
}

SFVec2f *VRMLTextureTransform::getSFTranslation(void)
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

void VRMLTextureTransformBinder::pushValues(void)
{
    TextureTransformChunkPtr pTexTrans = 
        TextureTransformChunkPtr::dcast(_pFieldContainer);

    if(pTexTrans == NullFC)
        return;

    Matrix     m;

    m.setTransform(_vTrans,
                   _qRotation, 
                   _vScale, 
                   Quaternion::identity(), 
                   _vCenter);

    beginEditCP(pTexTrans);
    {
        pTexTrans->setMatrix(m);
    }
    endEditCP  (pTexTrans);
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

VRMLTextureTransformBinder::VRMLTextureTransformBinder(void) :
     Inherited(),
    _vCenter  (),
    _qRotation(),
    _vScale   (),
    _vTrans   ()
{
    _vCenter  .setValues     (0.f, 0.f, 0.f     );   
    _qRotation.setValueAsQuat(0.f, 0.f, 0.f, 1.f);
    _vScale   .setValues     (1.f, 1.f, 1.f     );
    _vTrans   .setValues     (0.f, 0.f, 0.f     );
}

VRMLTextureTransformBinder::~VRMLTextureTransformBinder(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLTextureTransformBinder::init(VRMLToOSGAction *)
{
    if(_pNode == NULL)
        return;

    VRMLTextureTransform *pNode = 
        dynamic_cast<VRMLTextureTransform *>(_pNode);

    if(pNode == NULL)
        return;

    _vCenter.setValues(pNode->getSFCenter()->getValue()[0],
                       pNode->getSFCenter()->getValue()[1],
                       0.f);
    
    _qRotation.setValueAsAxisRad(0.f, 0.f, 1.f,
                                 pNode->getSFRotation()->getValue());
    
    _vScale.setValues(pNode->getSFScale()->getValue()[0],
                      pNode->getSFScale()->getValue()[1],
                      1.f);
    
    _vTrans.setValues(pNode->getSFTranslation()->getValue()[0],
                      pNode->getSFTranslation()->getValue()[1],
                      0.f);
    
    _pFieldContainer = TextureTransformChunk::create();

    pushValues();
}

void VRMLTextureTransformBinder::finish(VRMLToOSGAction *)
{
}

void VRMLTextureTransformBinder::setCenter(Vec2f &vCenter)
{
    _vCenter.setValues(vCenter[0],
                       vCenter[1],
                       0.f);

    pushValues();
}

void VRMLTextureTransformBinder::setRotation(Real32 &rRotation)
{
    _qRotation.setValueAsAxisRad(0.f, 0.f, 1.f,
                                 rRotation);
    
    pushValues();
}

void VRMLTextureTransformBinder::setScale(Vec2f &vScale)
{
    _vScale.setValues(vScale[0],
                      vScale[1],
                      1.f);
    
    pushValues();
}

void VRMLTextureTransformBinder::setTranslation(Vec2f &vTrans)
{
    _vTrans.setValues(vTrans[0],
                      vTrans[1],
                      0.f);
    pushValues();
}



VRMLAction::ActionResult OSG::osgVRMLTextureTransformToOpenSG(
    VRMLNode   &oNode,
    VRMLAction *pAction)
{
#ifdef OSG_DEBUG_VRMLTOOSG
  fprintf(stderr, 
          "Visit TextureTransform : %s\n", 
          oNode.getName().str());
#endif

    VRMLToOSGAction  *pConvAction   = 
        dynamic_cast<VRMLToOSGAction      *>(pAction);

    VRMLTextureTransform *pTexTrans = 
        dynamic_cast<VRMLTextureTransform *>(&oNode );

    if(pConvAction != NULL && pTexTrans != NULL)
    {
        VRMLTextureTransformBinder *pBinder     = 
            new VRMLTextureTransformBinder();

        VRMLNodeBinder             *pNodeBinder = NULL;

        pBinder->setNode(pTexTrans);
        pBinder->init   (pConvAction);

        pBinder->finish(pConvAction);
        oNode.setBinder(pBinder);
    }

    return VRMLAction::Continue;
}




