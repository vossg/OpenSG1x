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

#include "OSGVRMLDirectionalLight.h"
#include <OSGDataElementDesc.h>
#include <OSGVRMLToOSGAction.h>
#include <OSGGroup.h>

OSG_USING_NAMESPACE

OSG_BEGIN_NAMESPACE

VRMLAction::ActionResult osgVRMLDirectionalLightToOpenSG(VRMLNode   &oNode,
                                                         VRMLAction *pAction);

OSG_END_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlDirectionalLightDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        SFVec3f::getClassType(),
        "direction",
        OSG_RC_ELEM_IDM_DESC(VRMLDirectionalLight::DirectionField),
        false,
        (DataElemGetMethod) &VRMLDirectionalLight::getSFDirection,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}

VRMLObjectType VRMLDirectionalLight::_type(
    "DirectionalLight",
    "VRMLLight",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLDirectionalLight::createEmpty,
    VRMLDirectionalLight::init,
    vrmlDirectionalLightDescInserter,
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

void VRMLDirectionalLight::init(void)
{
    VRMLToOSGAction::registerDefaultTrav(
        VRMLDirectionalLight::getClassType(),
        osgTypedFunctionFunctor2Ref<
            VRMLAction::ActionResult,
            VRMLNode,
            VRMLAction *>(osgVRMLDirectionalLightToOpenSG));

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

VRMLDirectionalLight::VRMLDirectionalLight(void) :
	 Inherited  (),

    _sfDirection()
{
    _sfDirection.getValue().setValues(0.f, 0.f, -1.f);
}


VRMLDirectionalLight::VRMLDirectionalLight(
    const VRMLDirectionalLight &source) :

	 Inherited  (source             ),

    _sfDirection(source._sfDirection)
{
}


/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLDirectionalLight, Ptr);

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLDirectionalLight::~VRMLDirectionalLight(void)
{
}

/*------------------------------ access -----------------------------------*/

SFVec3f *VRMLDirectionalLight::getSFDirection(void)
{
    return &_sfDirection;
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

VRMLDirectionalLightBinder::VRMLDirectionalLightBinder(void) :
     Inherited(           ),
    _pLight   (OSG::NullFC)
{
}

VRMLDirectionalLightBinder::~VRMLDirectionalLightBinder(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLDirectionalLightBinder::init(VRMLToOSGAction *)
{
}

void VRMLDirectionalLightBinder::finish(VRMLToOSGAction *pAction)
{
    if(_pNode == NULL)
        return;

    VRMLDirectionalLight *pNode = 
        dynamic_cast<VRMLDirectionalLight *>(_pNode);

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

    _pLight = DirectionalLight::create();


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

        _pLight->setBeacon(pBeaconNode);

        cCol.setValuesRGBA(pColor->getValue()[0] * rIntensity,
                           pColor->getValue()[1] * rIntensity,
                           pColor->getValue()[2] * rIntensity,
                           1.f);

        _pLight->setDiffuse (cCol);

        _pLight->setDirection(-pNode->getSFDirection()->getValue()[0],
                              -pNode->getSFDirection()->getValue()[1],
                              -pNode->getSFDirection()->getValue()[2]);

        _pLight->setOn(pNode->getSFOn()->getValue());

        _pLight->setSpecular(cCol);
    }
    endEditCP  (_pLight);

    pAction->dropLight(_pLight);
}


VRMLAction::ActionResult OSG::osgVRMLDirectionalLightToOpenSG(
    VRMLNode   &oNode,
    VRMLAction *pAction)
{
#ifdef OSG_DEBUG_VRMLTOOSG
    fprintf(stderr, 
            "Visit Directional Light : %s\n", 
            oNode.getName().str());
#endif

    VRMLToOSGAction      *pConvAction = 
        dynamic_cast<VRMLToOSGAction      *>(pAction);

    VRMLDirectionalLight *pLight      = 
        dynamic_cast<VRMLDirectionalLight *>(&oNode );

    if(pConvAction != NULL && pLight != NULL)
    {
        VRMLDirectionalLightBinder *pBinder = 
            new VRMLDirectionalLightBinder();

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
    static Char8 cvsid_hpp[] = OSGVRMLDIRECTIONALLIGHT_HEADER_CVSID;
}
