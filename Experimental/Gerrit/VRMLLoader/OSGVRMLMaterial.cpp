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

#include "OSGVRMLMaterial.h"
#include "OSGDataElementDesc.h"

#include "OSGMaterialChunk.h"
#include "OSGVRMLToOSGAction.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGVRMLMATERIAL_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_BEGIN_NAMESPACE

VRMLAction::ActionResult osgVRMLMaterialToOpenSG(VRMLNode   &oNode,
                                                 VRMLAction *pAction);

OSG_END_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlMaterialDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "ambientIntensity",
        OSG_RC_ELEM_IDM_DESC(VRMLMaterial::AmbientIntensityField),
        false,
        (DataElemGetMethod) &VRMLMaterial::getSFAmbientIntensity,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFColor3f::getClassType(),
        "diffuseColor",
        OSG_RC_ELEM_IDM_DESC(VRMLMaterial::DiffuseColorField),
        false,
        (DataElemGetMethod) &VRMLMaterial::getSFDiffuseColor,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFColor3f::getClassType(),
        "emissiveColor",
        OSG_RC_ELEM_IDM_DESC(VRMLMaterial::EmissiveColorField),
        false,
        (DataElemGetMethod) &VRMLMaterial::getSFEmissiveColor,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "shininess",
        OSG_RC_ELEM_IDM_DESC(VRMLMaterial::ShininessField),
        false,
        (DataElemGetMethod) &VRMLMaterial::getSFShininess,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFColor3f::getClassType(),
        "specularColor",
        OSG_RC_ELEM_IDM_DESC(VRMLMaterial::SpecularColorField),
        false,
        (DataElemGetMethod) &VRMLMaterial::getSFSpecularColor,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "transparency",
        OSG_RC_ELEM_IDM_DESC(VRMLMaterial::TransparencyField),
        false,
        (DataElemGetMethod) &VRMLMaterial::getSFTransparency,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}

VRMLObjectType VRMLMaterial::_type(
    "Material",
    "VRMLUnlimitedNode",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLMaterial::createEmpty,
    VRMLMaterial::init,
    vrmlMaterialDescInserter,
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

void VRMLMaterial::init(void)
{
    VRMLToOSGAction::registerDefaultTrav(
        VRMLMaterial::getClassType(),
        osgTypedFunctionFunctor2Ref<VRMLAction::ActionResult,
                                    VRMLNode,
                                    VRMLAction *>(osgVRMLMaterialToOpenSG));
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

VRMLMaterial::VRMLMaterial(void) :
 	 Inherited         (    ),
    _sfAmbientIntensity(0.2f),
    _sfDiffuseColor    (    ),
    _sfEmissiveColor   (    ),
    _sfShininess       (0.2f),
    _sfSpecularColor   (    ),
    _sfTransparency    (0.0f)
{
    _sfDiffuseColor .getValue().setValuesRGB(0.8f, 0.8f, 0.8f);
    _sfEmissiveColor.getValue().setValuesRGB(0.0f, 0.0f, 0.0f);
    _sfSpecularColor.getValue().setValuesRGB(0.0f, 0.0f, 0.0f);
}


VRMLMaterial::VRMLMaterial(const VRMLMaterial &source) :
 	 Inherited         (source                    ),
    _sfAmbientIntensity(source._sfAmbientIntensity),
    _sfDiffuseColor    (source._sfDiffuseColor    ),
    _sfEmissiveColor   (source._sfEmissiveColor   ),
    _sfShininess       (source._sfShininess       ),
    _sfSpecularColor   (source._sfSpecularColor   ),
    _sfTransparency    (source._sfTransparency    )
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#ifdef WIN32
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLMaterial, Ptr);

#ifdef WIN32
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLMaterial::~VRMLMaterial(void)
{
}

/*------------------------------ access -----------------------------------*/

SFReal32 *VRMLMaterial::getSFAmbientIntensity(void)
{
    return &_sfAmbientIntensity;
}

SFColor3f *VRMLMaterial::getSFDiffuseColor(void)
{
    return &_sfDiffuseColor;
}

SFColor3f *VRMLMaterial::getSFEmissiveColor(void)
{
    return &_sfEmissiveColor;
}

SFReal32 *VRMLMaterial::getSFShininess(void)
{
    return &_sfShininess;
}

SFColor3f *VRMLMaterial::getSFSpecularColor(void)
{
    return &_sfSpecularColor;
}

SFReal32 *VRMLMaterial::getSFTransparency(void)
{
    return &_sfTransparency;
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

VRMLMaterialBinder::VRMLMaterialBinder(void) :
	Inherited()
{
}

VRMLMaterialBinder::~VRMLMaterialBinder(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLMaterialBinder::init(VRMLToOSGAction *)
{
    if(_pNode == NULL)
        return;

    VRMLMaterial *pNode = dynamic_cast<VRMLMaterial *>(_pNode);

    if(pNode == NULL)
        return;

    MaterialChunkPtr pMat = MaterialChunk::create();


    Color4f cCol;

    Real32 rAmbientIntens     = pNode->getSFAmbientIntensity()->getValue();
    Real32 rTransparency      = pNode->getSFTransparency    ()->getValue();
    Real32 rShininess         = pNode->getSFShininess       ()->getValue(); 

    SFColor3f *pDiffuseColor  = pNode->getSFDiffuseColor    ();
    SFColor3f *pEmissiveColor = pNode->getSFEmissiveColor   ();
    SFColor3f *pSpecularColor = pNode->getSFSpecularColor   ();

    cCol.setValuesRGBA(pDiffuseColor->getValue()[0] * rAmbientIntens,
                       pDiffuseColor->getValue()[1] * rAmbientIntens,
                       pDiffuseColor->getValue()[2] * rAmbientIntens,
                       1.f - rTransparency);

    beginEditCP(pMat);
    {
        pMat->setAmbient(cCol);
        
        cCol.setValuesRGBA(pDiffuseColor->getValue()[0],
                           pDiffuseColor->getValue()[1],
                           pDiffuseColor->getValue()[2],
                           1.f - rTransparency);
        
        pMat->setDiffuse(cCol);
        
        cCol.setValuesRGBA(pSpecularColor->getValue()[0],
                           pSpecularColor->getValue()[1],
                           pSpecularColor->getValue()[2],
                           1.f - rTransparency );
        
        pMat->setSpecular(cCol);
        
        pMat->setShininess(rShininess * 128.f );
        
        cCol.setValuesRGBA(pEmissiveColor->getValue()[0],
                           pEmissiveColor->getValue()[1],
                           pEmissiveColor->getValue()[2],
                           1.f - rTransparency);

        pMat->setEmission (cCol);
    }
    endEditCP  (pMat);
        
    _pFieldContainer = pMat;
}

void VRMLMaterialBinder::finish(VRMLToOSGAction *)
{
}


VRMLAction::ActionResult OSG::osgVRMLMaterialToOpenSG(
    VRMLNode   &oNode,
    VRMLAction *pAction)
{
    fprintf(stderr, "Visit Material : %s\n", oNode.getName().str());

    VRMLToOSGAction *pConvAction = 
        dynamic_cast<VRMLToOSGAction *>(pAction);

    VRMLMaterial    *pMat        = 
        dynamic_cast<VRMLMaterial    *>(&oNode );

    if(pConvAction != NULL && pMat != NULL)
    {
        VRMLMaterialBinder *pBinder     = new VRMLMaterialBinder();
        VRMLNodeBinder     *pNodeBinder = NULL;

        pBinder->setNode(pMat);
        pBinder->init   (pConvAction);

        pBinder->finish(pConvAction);
        oNode.setBinder(pBinder);
    }

    return VRMLAction::Continue;
}
