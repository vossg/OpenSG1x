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

#include "OSGVRMLCone.h"
#include "OSGDataElementDesc.h"

#include <OSGGeometry.h>
#include <OSGSimpleGeometry.h>
#include <OSGVRMLToOSGAction.h>

OSG_USING_NAMESPACE

OSG_BEGIN_NAMESPACE

VRMLAction::ActionResult osgVRMLConeToOpenSG(VRMLNode   &oNode,
                                             VRMLAction *pAction);

OSG_END_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlConeDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "bottomRadius",
        OSG_RC_ELEM_IDM_DESC(VRMLCone::BottomRadiusField),
        false,
        (DataElemGetMethod) &VRMLCone::getSFBottomRadius,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "height",
        OSG_RC_ELEM_IDM_DESC(VRMLCone::HeightField),
        false,
        (DataElemGetMethod) &VRMLCone::getSFHeight,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFBool::getClassType(),
        "side",
        OSG_RC_ELEM_IDM_DESC(VRMLCone::SideField),
        false,
        (DataElemGetMethod) &VRMLCone::getSFSide,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFBool::getClassType(),
        "bottom",
        OSG_RC_ELEM_IDM_DESC(VRMLCone::BottomField),
        false,
        (DataElemGetMethod) &VRMLCone::getSFBottom,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}


VRMLObjectType VRMLCone::_type(
    "Cone",
    "VRMLGeometry",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLCone::createEmpty,
    &VRMLCone::init,
    vrmlConeDescInserter,
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

void VRMLCone::init(void)
{
    VRMLToOSGAction::registerDefaultTrav(
        VRMLCone::getClassType(),
        osgTypedFunctionFunctor2Ref<VRMLAction::ActionResult,
                                    VRMLNode,
                                    VRMLAction *>(osgVRMLConeToOpenSG));
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

VRMLCone::VRMLCone(void) :
 	 Inherited     (    ),
    _sfBottomRadius(1.f ),
    _sfHeight      (2.f ),
    _sfSide        (true),
    _sfBottom      (true)

{
}


VRMLCone::VRMLCone(const VRMLCone &source) :
 	 Inherited     (source                ),
    _sfBottomRadius(source._sfBottomRadius),
    _sfHeight      (source._sfHeight      ),
    _sfSide        (source._sfSide        ),
    _sfBottom      (source._sfBottom      )
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLCone, Ptr);

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLCone::~VRMLCone(void)
{
}

/*------------------------------ access -----------------------------------*/

SFReal32 *VRMLCone::getSFBottomRadius(void)
{
    return &_sfBottomRadius;
}

SFReal32 *VRMLCone::getSFHeight(void)
{
    return &_sfHeight;
}

SFBool   *VRMLCone::getSFSide(void)
{
    return &_sfSide;
}

SFBool   *VRMLCone::getSFBottom(void)
{
    return &_sfBottom;
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

VRMLConeBinder::VRMLConeBinder(void) :
	Inherited()
{
}

VRMLConeBinder::~VRMLConeBinder(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLConeBinder::init(VRMLToOSGAction *)
{
    if(_pNode == NULL)
        return;

    VRMLCone *pNode = dynamic_cast<VRMLCone *>(_pNode);

    if(pNode == NULL)
        return;

    _pFieldContainer = 
        makeConeGeo(pNode->getSFHeight()      ->getValue(),
                    pNode->getSFBottomRadius()->getValue(),
                    32,
                    pNode->getSFSide()        ->getValue(),
                    pNode->getSFBottom()      ->getValue());
}

void VRMLConeBinder::finish(VRMLToOSGAction *)
{
}


VRMLAction::ActionResult OSG::osgVRMLConeToOpenSG(
    VRMLNode   &oNode,
    VRMLAction *pAction)
{
    fprintf(stderr,
            "Visit Cone : %s\n", 
            oNode.getName().str());

    VRMLToOSGAction *pConvAction = 
        dynamic_cast<VRMLToOSGAction *>(pAction);

    VRMLCone        *pCone       = 
        dynamic_cast<VRMLCone        *>(&oNode );

    if(pConvAction != NULL && pCone != NULL)
    {
        VRMLConeBinder *pBinder = new VRMLConeBinder();

        pBinder->setNode(pCone);
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
    static Char8 cvsid_hpp[] = OSGVRMLCONE_HEADER_CVSID;
}
