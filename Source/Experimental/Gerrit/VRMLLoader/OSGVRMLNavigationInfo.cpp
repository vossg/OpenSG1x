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

#include "OSGVRMLNavigationInfo.h"

#include <OSGDataElementDesc.h>

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlNavInfoDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        MFReal32::getClassType(),
        "avatarSize",
        OSG_RC_ELEM_IDM_DESC(VRMLNavigationInfo::AvatarSizeField),
        false,
        (DataElemGetMethod) &VRMLNavigationInfo::getMFAvatarSize,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFBool::getClassType(),
        "headlight",
        OSG_RC_ELEM_IDM_DESC(VRMLNavigationInfo::HeadlightField),
        false,
        (DataElemGetMethod) &VRMLNavigationInfo::getSFHeadlight,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "speed",
        OSG_RC_ELEM_IDM_DESC(VRMLNavigationInfo::SpeedField),
        false,
        (DataElemGetMethod) &VRMLNavigationInfo::getSFSpeed,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFString::getClassType(),
        "type",
        OSG_RC_ELEM_IDM_DESC(VRMLNavigationInfo::TypeField),
        false,
        (DataElemGetMethod) &VRMLNavigationInfo::getMFType,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "visibilityLimit",
        OSG_RC_ELEM_IDM_DESC(VRMLNavigationInfo::VisibilityLimitField),
        false,
        (DataElemGetMethod) &VRMLNavigationInfo::getSFVisibilityLimit,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}

VRMLObjectType VRMLNavigationInfo::_type(
    "NavigationInfo",
    "VRMLUnlimitedNode",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLNavigationInfo::createEmpty,
    NULL, // Init
    vrmlNavInfoDescInserter,
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

VRMLNavigationInfo::VRMLNavigationInfo(void) :
 	 Inherited        (),
    _mfAvatarSize     (),
    _sfHeadlight      (true),
    _sfSpeed          (1.0f),
    _mfType           (),
    _sfVisibilityLimit(0.0f)
{
    _mfAvatarSize.push_back(0.25f);
    _mfAvatarSize.push_back(1.60f);
    _mfAvatarSize.push_back(0.75f);

    string szType("WALK");

    _mfType.push_back(szType);
}


VRMLNavigationInfo::VRMLNavigationInfo(
    const VRMLNavigationInfo &source) :

 	 Inherited        (source                   ),

    _mfAvatarSize     (source._mfAvatarSize     ),
    _sfHeadlight      (source._sfHeadlight      ),
    _sfSpeed          (source._sfSpeed          ),
    _mfType           (source._mfType           ),
    _sfVisibilityLimit(source._sfVisibilityLimit)
{
}


/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLNavigationInfo, Ptr);

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLNavigationInfo::~VRMLNavigationInfo(void)
{
}

/*------------------------------ access -----------------------------------*/

MFReal32 *VRMLNavigationInfo::getMFAvatarSize(void)
{
    return &_mfAvatarSize;
}

SFBool *VRMLNavigationInfo::getSFHeadlight(void)
{
    return &_sfHeadlight;
}

SFReal32 *VRMLNavigationInfo::getSFSpeed(void)
{
    return &_sfSpeed;
}

MFString *VRMLNavigationInfo::getMFType(void)
{
    return &_mfType;
}

SFReal32 *VRMLNavigationInfo::getSFVisibilityLimit(void)
{
    return &_sfVisibilityLimit;
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
    static Char8 cvsid_hpp[] = OSGVRMLNAVIGATIONINFO_HEADER_CVSID;
}
