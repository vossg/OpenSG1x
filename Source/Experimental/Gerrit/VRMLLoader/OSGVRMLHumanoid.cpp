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

#include "OSGVRMLHumanoid.h"

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlHumanoidDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;


    pDesc = new DataElementDesc(
        MFString::getClassType(),
        "info",
        OSG_RC_ELEM_IDM_DESC(VRMLHumanoid::InfoField),
        false,
        (DataElemGetMethod) &VRMLHumanoid::getMFInfo,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFVRMLNode::getClassType(),
        "joints",
        OSG_RC_ELEM_IDM_DESC(VRMLHumanoid::JointsField),
        false,
        (DataElemGetMethod) &VRMLHumanoid::getMFJoints,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFString::getClassType(),
        "name",
        OSG_RC_ELEM_IDM_DESC(VRMLHumanoid::NameField),
        false,
        (DataElemGetMethod) &VRMLHumanoid::getSFName,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFVRMLNode::getClassType(),
        "segments",
        OSG_RC_ELEM_IDM_DESC(VRMLHumanoid::SegmentsField),
        false,
        (DataElemGetMethod) &VRMLHumanoid::getMFSegments,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFVRMLNode::getClassType(),
        "sites",
        OSG_RC_ELEM_IDM_DESC(VRMLHumanoid::SitesField),
        false,
        (DataElemGetMethod) &VRMLHumanoid::getMFSites,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFVRMLNode::getClassType(),
        "skeleton",
        OSG_RC_ELEM_IDM_DESC(VRMLHumanoid::SkeletonField),
        false,
        (DataElemGetMethod) &VRMLHumanoid::getMFSkeleton,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFVRMLNode::getClassType(),
        "skin",
        OSG_RC_ELEM_IDM_DESC(VRMLHumanoid::SkinField),
        false,
        (DataElemGetMethod) &VRMLHumanoid::getMFSkin,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
    
    pDesc = new DataElementDesc(
        SFVRMLNode::getClassType(),
        "skinCoord",
        OSG_RC_ELEM_IDM_DESC(VRMLHumanoid::SkinCoordField),
        false,
        (DataElemGetMethod) &VRMLHumanoid::getSFSkinCoord,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFVRMLNode::getClassType(),
        "skinNormal",
        OSG_RC_ELEM_IDM_DESC(VRMLHumanoid::SkinNormalField),
        false,
        (DataElemGetMethod) &VRMLHumanoid::getSFSkinNormal,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFString::getClassType(),
        "version",
        OSG_RC_ELEM_IDM_DESC(VRMLHumanoid::VersionField),
        false,
        (DataElemGetMethod) &VRMLHumanoid::getSFVersion,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFVRMLNode::getClassType(),
        "viewpoints",
        OSG_RC_ELEM_IDM_DESC(VRMLHumanoid::ViewpointsField),
        false,
        (DataElemGetMethod) &VRMLHumanoid::getMFViewpoints,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}

VRMLObjectType VRMLHumanoid::_type(
    "Humanoid",
    "Transform",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLHumanoid::createEmpty,
    NULL,
    vrmlHumanoidDescInserter,
    false);

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

VRMLHumanoid::VRMLHumanoid(void) :
	 Inherited           (    ),
    _mfInfo              (    ),
    _mfJoints            (    ),
    _sfName              (    ),
    _mfSegments          (    ),
    _mfSites             (    ),

    _mfSkeleton          (    ),
    _mfSkin              (    ),
    _sfSkinCoord         (    ),
    _sfSkinNormal        (    ),

    _sfVersion           (    ),
    _mfViewpoints        (    )
{
    _sfVersion.getValue().assign("2.0");
}


VRMLHumanoid::VRMLHumanoid(const VRMLHumanoid &source) :
	 Inherited           (source                      ),
    _mfInfo              (source._mfInfo              ),
    _mfJoints            (source._mfJoints            ),
    _sfName              (source._sfName              ),
    _mfSegments          (source._mfSegments          ),
    _mfSites             (source._mfSites             ),

    _mfSkeleton          (source._mfSkeleton          ),
    _mfSkin              (source._mfSkin              ),
    _sfSkinCoord         (source._sfSkinCoord         ),
    _sfSkinNormal        (source._sfSkinNormal        ),

    _sfVersion           (source._sfVersion           ),
    _mfViewpoints        (source._mfViewpoints        )
{
}


/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLHumanoid, Ptr);

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLHumanoid::~VRMLHumanoid(void)
{
}

/*------------------------------ access -----------------------------------*/

/*------------------------------ access -----------------------------------*/

MFString *VRMLHumanoid::getMFInfo(void)
{
    return &_mfInfo;
}

MFVRMLNode *VRMLHumanoid::getMFJoints(void)
{
    return &_mfJoints;
}

SFString *VRMLHumanoid::getSFName(void)
{
    return &_sfName;
}

MFVRMLNode *VRMLHumanoid::getMFSegments(void)
{
    return &_mfSegments;
}

MFVRMLNode *VRMLHumanoid::getMFSites(void)
{
    return &_mfSites;
}

MFVRMLNode *VRMLHumanoid::getMFSkeleton(void)
{
    return &_mfSkeleton;
}

MFVRMLNode *VRMLHumanoid::getMFSkin(void)
{
    return &_mfSkin;
}

SFVRMLNode *VRMLHumanoid::getSFSkinCoord(void)
{
    return &_sfSkinCoord;
}

SFVRMLNode *VRMLHumanoid::getSFSkinNormal(void)
{
    return &_sfSkinNormal;
}

SFString *VRMLHumanoid::getSFVersion(void)
{
    return &_sfVersion;
}

MFVRMLNode *VRMLHumanoid::getMFViewpoints(void)
{
    return &_mfViewpoints;
}



/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGVRMLHUMANOID_HEADER_CVSID;
}
