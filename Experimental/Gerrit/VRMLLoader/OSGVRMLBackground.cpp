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

#include "OSGVRMLBackground.h"
#include <OSGDataElementDesc.h>

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGVRMLBACKGROUND_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlBackgroundDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        MFReal32::getClassType(),
        "groundAngle",
        OSG_RC_ELEM_IDM_DESC(VRMLBackground::GroundAngleField),
        false,
        (DataElemGetMethod) &VRMLBackground::getMFGroundAngle,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFColor3f::getClassType(),
        "groundColor",
        OSG_RC_ELEM_IDM_DESC(VRMLBackground::GroundColorField),
        false,
        (DataElemGetMethod) &VRMLBackground::getMFGroundColor,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFString::getClassType(),
        "backUrl",
        OSG_RC_ELEM_IDM_DESC(VRMLBackground::BackUrlField),
        false,
        (DataElemGetMethod) &VRMLBackground::getMFBackUrl,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFString::getClassType(),
        "bottomUrl",
        OSG_RC_ELEM_IDM_DESC(VRMLBackground::BackUrlField),
        false,
        (DataElemGetMethod) &VRMLBackground::getMFBackUrl,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFString::getClassType(),
        "frontUrl",
        OSG_RC_ELEM_IDM_DESC(VRMLBackground::FrontUrlField),
        false,
        (DataElemGetMethod) &VRMLBackground::getMFFrontUrl,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFString::getClassType(),
        "leftUrl",
        OSG_RC_ELEM_IDM_DESC(VRMLBackground::LeftUrlField),
        false,
        (DataElemGetMethod) &VRMLBackground::getMFLeftUrl,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFString::getClassType(),
        "rightUrl",
        OSG_RC_ELEM_IDM_DESC(VRMLBackground::RightUrlField),
        false,
        (DataElemGetMethod) &VRMLBackground::getMFRightUrl,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFString::getClassType(),
        "topUrl",
        OSG_RC_ELEM_IDM_DESC(VRMLBackground::TopUrlField),
        false,
        (DataElemGetMethod) &VRMLBackground::getMFTopUrl,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFReal32::getClassType(),
        "skyAngle",
        OSG_RC_ELEM_IDM_DESC(VRMLBackground::SkyAngleField),
        false,
        (DataElemGetMethod) &VRMLBackground::getMFSkyAngle,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFColor3f::getClassType(),
        "skyColor",
        OSG_RC_ELEM_IDM_DESC(VRMLBackground::SkyColorField),
        false,
        (DataElemGetMethod) &VRMLBackground::getMFSkyColor,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}


VRMLObjectType VRMLBackground::_type(
    "Background",
    "VRMLUnlimitedNode",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLBackground::createEmpty,
    NULL, // Init
    vrmlBackgroundDescInserter,
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

VRMLBackground::VRMLBackground(void) :
	Inherited(),

    _mfGroundAngle(),
    _mfGroundColor(),
    _mfBackUrl    (),
    _mfBottomUrl  (),
    _mfFrontUrl   (),
    _mfLeftUrl    (),
    _mfRightUrl   (),
    _mfTopUrl     (),
    _mfSkyAngle   (),
    _mfSkyColor   ()
{
    Color3f oBlack(0.f, 0.f, 0.f);

    _mfSkyColor.addValue(oBlack);
}


VRMLBackground::VRMLBackground(const VRMLBackground &source) :
	 Inherited    (source               ),

    _mfGroundAngle(source._mfGroundAngle),
    _mfGroundColor(source._mfGroundColor),
    _mfBackUrl    (source._mfBackUrl    ),
    _mfBottomUrl  (source._mfBottomUrl  ),
    _mfFrontUrl   (source._mfFrontUrl   ),
    _mfLeftUrl    (source._mfLeftUrl    ),
    _mfRightUrl   (source._mfRightUrl   ),
    _mfTopUrl     (source._mfTopUrl     ),
    _mfSkyAngle   (source._mfSkyAngle   ),
    _mfSkyColor   (source._mfSkyColor   )
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#ifdef WIN32
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLBackground, Ptr);

#ifdef WIN32
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLBackground::~VRMLBackground(void)
{
}

/*------------------------------ access -----------------------------------*/

MFReal32 *VRMLBackground::getMFGroundAngle(void)
{
    return &_mfGroundAngle;
}

MFColor3f *VRMLBackground::getMFGroundColor(void)
{
    return &_mfGroundColor;
}

MFString *VRMLBackground::getMFBackUrl(void)
{
    return &_mfBackUrl;
}

MFString *VRMLBackground::getMFBottomUrl(void)
{
    return &_mfBottomUrl;
}

MFString *VRMLBackground::getMFFrontUrl(void)
{
    return &_mfFrontUrl;
}

MFString *VRMLBackground::getMFLeftUrl(void)
{
    return &_mfLeftUrl;
}

MFString *VRMLBackground::getMFRightUrl(void)
{
    return &_mfRightUrl;
}

MFString *VRMLBackground::getMFTopUrl(void)
{
    return &_mfTopUrl;
}

MFReal32 *VRMLBackground::getMFSkyAngle(void)
{
    return &_mfSkyAngle;
}

MFColor3f *VRMLBackground::getMFSkyColor(void)
{
    return &_mfSkyColor;
}

