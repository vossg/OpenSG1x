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

#include "OSGVRMLPointLight.h"

#include <OSGDataElementDesc.h>

#include "OSGVRMLToOSGAction.h"

#include <OSGGroup.h>
#include <OSGNode.h>

OSG_USING_NAMESPACE

OSG_BEGIN_NAMESPACE

VRMLAction::ActionResult osgVRMLPointLightToOpenSG(VRMLNode   &oNode,
                                                    VRMLAction *pAction);

OSG_END_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlPointLightDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        SFVec3f::getClassType(),
        "attenuation",
        OSG_RC_ELEM_IDM_DESC(VRMLPointLight::AttenuationField),
        false,
        (DataElemGetMethod) &VRMLPointLight::getSFAttenuation,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFVec3f::getClassType(),
        "location",
        OSG_RC_ELEM_IDM_DESC(VRMLPointLight::LocationField),
        false,
        (DataElemGetMethod) &VRMLPointLight::getSFLocation,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "radius",
        OSG_RC_ELEM_IDM_DESC(VRMLPointLight::RadiusField),
        false,
        (DataElemGetMethod) &VRMLPointLight::getSFRadius,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}


VRMLObjectType VRMLPointLight::_type(
    "PointLight",
    "VRMLLight",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLPointLight::createEmpty,
    VRMLPointLight::init, // Init
    vrmlPointLightDescInserter,
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

void VRMLPointLight::init(void)
{
    VRMLToOSGAction::registerDefaultTrav(
        VRMLPointLight::getClassType(),
        osgTypedFunctionFunctor2Ref<
            VRMLAction::ActionResult,
            VRMLNode,
            VRMLAction *>(osgVRMLPointLightToOpenSG));

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

VRMLPointLight::VRMLPointLight(void) :
 	 Inherited    (),

    _sfAttenuation(),
    _sfLocation   (),
    _sfRadius     (100.f)
{
    _sfAttenuation.getValue().setValues(1.f, 0.f, 0.f);
    _sfLocation   .getValue().setValues(0.f, 0.f, 0.f);
}


VRMLPointLight::VRMLPointLight(const VRMLPointLight &source) :
	 Inherited    (source               ),

    _sfAttenuation(source._sfAttenuation),
    _sfLocation   (source._sfLocation   ),
    _sfRadius     (source._sfRadius     )
{
}


/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLPointLight, Ptr);

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLPointLight::~VRMLPointLight(void)
{
}

/*------------------------------ access -----------------------------------*/

SFVec3f  *VRMLPointLight::getSFAttenuation(void)
{
    return &_sfAttenuation;
}

SFVec3f  *VRMLPointLight::getSFLocation(void)
{
    return &_sfLocation;
}

SFReal32 *VRMLPointLight::getSFRadius(void)
{
    return &_sfRadius;
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

VRMLPointLightBinder::VRMLPointLightBinder(void) :
     Inherited(      ),
    _pLight   (NullFC)
{
}

VRMLPointLightBinder::~VRMLPointLightBinder(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLPointLightBinder::init(VRMLToOSGAction *pAction)
{
}

void VRMLPointLightBinder::finish(VRMLToOSGAction *pAction)
{
    if(_pNode == NULL)
        return;

    VRMLPointLight *pNode = dynamic_cast<VRMLPointLight *>(_pNode);

    if(pNode == NULL)
        return;

    NodePtr  pBeaconNode = Node ::create();
    GroupPtr pBeaconCore = Group::create();

    beginEditCP(pBeaconNode, Node::CoreFieldMask);
    {
        pBeaconNode->setCore(pBeaconCore);
    }
    endEditCP  (pBeaconNode, Node::CoreFieldMask);

    _pFieldContainer = pBeaconNode;

    _pLight = PointLight::create();


    Color4f cCol;

    Real32     rAmbientIntens = pNode->getSFAmbientIntensity()->getValue();
    Real32     rIntensity     = pNode->getSFIntensity       ()->getValue();
    SFColor3f *pColor         = pNode->getSFColor           ();

    cCol.setValuesRGBA(pColor->getValue()[0] * rAmbientIntens,
                       pColor->getValue()[1] * rAmbientIntens,
                       pColor->getValue()[2] * rAmbientIntens,
                       1.f);

    beginEditCP(_pLight);
    {
        _pLight->setAmbient(cCol);

        _pLight->setAttenuation(pNode->getSFAttenuation()->getValue()[0],
                                pNode->getSFAttenuation()->getValue()[1],
                                pNode->getSFAttenuation()->getValue()[2]);

        _pLight->setBeacon(pBeaconNode);

        cCol.setValuesRGBA(pColor->getValue()[0] * rIntensity,
                           pColor->getValue()[1] * rIntensity,
                           pColor->getValue()[2] * rIntensity,
                           1.f);

        _pLight->setDiffuse (cCol);

        _pLight->setOn(pNode->getSFOn()->getValue());

        _pLight->setPosition(pNode->getSFLocation()->getValue()[0],
                             pNode->getSFLocation()->getValue()[1],
                             pNode->getSFLocation()->getValue()[2]);

        _pLight->setSpecular(cCol);
    }
    endEditCP  (_pLight);

    pAction->dropLight(_pLight);
}


VRMLAction::ActionResult OSG::osgVRMLPointLightToOpenSG(
    VRMLNode   &oNode,
    VRMLAction *pAction)
{
#ifdef OSG_DEBUG_VRMLTOOSG
    fprintf(stderr, 
            "Visit Point Light : %s\n", 
            oNode.getName().str());
#endif

    VRMLToOSGAction *pConvAction = 
        dynamic_cast<VRMLToOSGAction *>(pAction);

    VRMLPointLight  *pLight      = 
        dynamic_cast<VRMLPointLight  *>(&oNode );

    if(pConvAction != NULL && pLight != NULL)
    {
        VRMLPointLightBinder *pBinder     = 
            new VRMLPointLightBinder();

        pBinder->setNode(pLight);
        pBinder->init   (pConvAction);

        pBinder->finish(pConvAction);
        oNode.setBinder(pBinder);
    }

    return VRMLAction::Continue;
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
    static Char8 cvsid_hpp[] = OSGVRMLPOINTLIGHT_HEADER_CVSID;
}
