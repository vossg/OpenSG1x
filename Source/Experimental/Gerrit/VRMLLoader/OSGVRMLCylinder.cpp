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

#include "OSGVRMLCylinder.h"
#include "OSGDataElementDesc.h"

#include <OSGGeometry.h>
#include <OSGSimpleGeometry.h>
#include <OSGVRMLToOSGAction.h>

OSG_USING_NAMESPACE

OSG_BEGIN_NAMESPACE

VRMLAction::ActionResult osgVRMLCylinderToOpenSG(VRMLNode   &oNode,
                                                 VRMLAction *pAction);

OSG_END_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlCylinderDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        SFBool::getClassType(),
        "bottom",
        OSG_RC_ELEM_IDM_DESC(VRMLCylinder::BottomField),
        false,
        (DataElemGetMethod) &VRMLCylinder::getSFBottom,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "height",
        OSG_RC_ELEM_IDM_DESC(VRMLCylinder::HeightField),
        false,
        (DataElemGetMethod) &VRMLCylinder::getSFHeight,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "radius",
        OSG_RC_ELEM_IDM_DESC(VRMLCylinder::RadiusField),
        false,
        (DataElemGetMethod) &VRMLCylinder::getSFRadius,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFBool::getClassType(),
        "side",
        OSG_RC_ELEM_IDM_DESC(VRMLCylinder::SideField),
        false,
        (DataElemGetMethod) &VRMLCylinder::getSFSide,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFBool::getClassType(),
        "top",
        OSG_RC_ELEM_IDM_DESC(VRMLCylinder::TopField),
        false,
        (DataElemGetMethod) &VRMLCylinder::getSFTop,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}


VRMLObjectType VRMLCylinder::_type(
    "Cylinder",
    "VRMLGeometry",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLCylinder::createEmpty,
    &VRMLCylinder::init,
    vrmlCylinderDescInserter,
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

void VRMLCylinder::init(void)
{
    VRMLToOSGAction::registerDefaultTrav(
        VRMLCylinder::getClassType(),
        osgTypedFunctionFunctor2Ref<VRMLAction::ActionResult,
                                    VRMLNode,
                                    VRMLAction *>(osgVRMLCylinderToOpenSG));
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

VRMLCylinder::VRMLCylinder(void) :
	 Inherited(    ),
    _sfBottom (true),
    _sfHeight (2.f ),
    _sfRadius (1.f ),
    _sfSide   (true),
    _sfTop    (true)
{
}


VRMLCylinder::VRMLCylinder(const VRMLCylinder &source) :
	 Inherited(source          ),
    _sfBottom (source._sfBottom),
    _sfHeight (source._sfHeight),
    _sfRadius (source._sfRadius),
    _sfSide   (source._sfSide  ),
    _sfTop    (source._sfTop   )
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLCylinder, Ptr);

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLCylinder::~VRMLCylinder(void)
{
}

/*------------------------------ access -----------------------------------*/

SFBool *VRMLCylinder::getSFBottom(void)
{
    return &_sfBottom;
}

SFReal32 *VRMLCylinder::getSFHeight(void)
{
    return &_sfHeight;
}

SFReal32 *VRMLCylinder::getSFRadius(void)
{
    return &_sfRadius;
}

SFBool *VRMLCylinder::getSFSide(void)
{
    return &_sfSide;
}

SFBool *VRMLCylinder::getSFTop(void)
{
    return &_sfTop;
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

VRMLCylinderBinder::VRMLCylinderBinder(void) :
	Inherited()
{
}

VRMLCylinderBinder::~VRMLCylinderBinder(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLCylinderBinder::init(VRMLToOSGAction *)
{
    if(_pNode == NULL)
        return;

    VRMLCylinder *pNode = dynamic_cast<VRMLCylinder *>(_pNode);

    if(pNode == NULL)
        return;

    _pFieldContainer = makeCylinderGeo(pNode->getSFHeight()->getValue(),
                                       pNode->getSFRadius()->getValue(),
                                       32,
                                       pNode->getSFSide  ()->getValue(),
                                       pNode->getSFTop   ()->getValue(),
                                       pNode->getSFBottom()->getValue());
}

void VRMLCylinderBinder::finish(VRMLToOSGAction *)
{
}


VRMLAction::ActionResult OSG::osgVRMLCylinderToOpenSG(
    VRMLNode   &oNode,
    VRMLAction *pAction)
{
    fprintf(stderr,
            "Visit Cylinder : %s\n", 
            oNode.getName().str());

    VRMLToOSGAction *pConvAction = 
        dynamic_cast<VRMLToOSGAction *>(pAction);

    VRMLCylinder    *pCylinder   = 
        dynamic_cast<VRMLCylinder    *>(&oNode );

    if(pConvAction != NULL && pCylinder != NULL)
    {
        VRMLCylinderBinder *pBinder = new VRMLCylinderBinder();

        pBinder->setNode(pCylinder  );
        pBinder->init   (pConvAction);

        pBinder->finish (pConvAction);
        oNode.setBinder (pBinder);
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
    static Char8 cvsid_hpp[] = OSGVRMLCYLINDER_HEADER_CVSID;
}
