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

#include "OSGVRMLJoint.h"
#include "OSGDataElementDesc.h"

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlJointDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        MFReal32::getClassType(),
        "llimit",
        OSG_RC_ELEM_IDM_DESC(VRMLJoint::LLimitField),
        false,
        (DataElemGetMethod) &VRMLJoint::getMFLLimit,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFRotation::getClassType(),
        "limitOrientation",
        OSG_RC_ELEM_IDM_DESC(VRMLJoint::LimitOrientationField),
        false,
        (DataElemGetMethod) &VRMLJoint::getSFLimitOrientation,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFString::getClassType(),
        "name",
        OSG_RC_ELEM_IDM_DESC(VRMLJoint::NameField),
        false,
        (DataElemGetMethod) &VRMLJoint::getSFName,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
    
    pDesc = new DataElementDesc(
        MFInt32::getClassType(),
        "skinCoordIndex",
        OSG_RC_ELEM_IDM_DESC(VRMLJoint::SkinCoordIndexField),
        false,
        (DataElemGetMethod) &VRMLJoint::getMFSkinCoordIndex,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFReal32::getClassType(),
        "skinCoordWeight",
        OSG_RC_ELEM_IDM_DESC(VRMLJoint::SkinCoordWeightField),
        false,
        (DataElemGetMethod) &VRMLJoint::getMFSkinCoordWeight,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFReal32::getClassType(),
        "stiffness",
        OSG_RC_ELEM_IDM_DESC(VRMLJoint::StiffnessField),
        false,
        (DataElemGetMethod) &VRMLJoint::getMFStiffness,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFReal32::getClassType(),
        "ulimit",
        OSG_RC_ELEM_IDM_DESC(VRMLJoint::ULimitField),
        false,
        (DataElemGetMethod) &VRMLJoint::getMFULimit,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}


VRMLObjectType VRMLJoint::_type(
    "Joint",
    "Transform",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLJoint::createEmpty,
    NULL,
    vrmlJointDescInserter,
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

VRMLJoint::VRMLJoint(void) :
	 Inherited         (     ),
    _mfLLimit          (     ),
    _sfLimitOrientation(     ),
    _sfName            (     ),

    _mfSkinCoordIndex  (     ),
    _mfSkinCoordWeight (     ),

    _mfStiffness       (     ),
    _mfULimit          (     )
{
    _sfLimitOrientation.getValue().setValueAsQuat(0.f, 0.f, 0.f, 1.f);
}


VRMLJoint::VRMLJoint(const VRMLJoint &source) :
	 Inherited         (source                    ),
    _mfLLimit          (source._mfLLimit          ),
    _sfLimitOrientation(source._sfLimitOrientation),
    _sfName            (source._sfName            ),

    _mfSkinCoordIndex  (source._mfSkinCoordIndex  ),
    _mfSkinCoordWeight (source._mfSkinCoordWeight ),

    _mfStiffness       (source._mfStiffness       ),
    _mfULimit          (source._mfULimit          )
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLJoint, Ptr);

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLJoint::~VRMLJoint(void)
{
}

/*------------------------------ access -----------------------------------*/

/*------------------------------ access -----------------------------------*/

MFReal32 *VRMLJoint::getMFLLimit(void)
{
    return &_mfLLimit;
}

SFRotation *VRMLJoint::getSFLimitOrientation(void)
{
    return &_sfLimitOrientation;
}

SFString *VRMLJoint::getSFName(void)
{
    return &_sfName;
}

MFInt32 *VRMLJoint::getMFSkinCoordIndex(void)
{
    return &_mfSkinCoordIndex;
}

MFReal32 *VRMLJoint::getMFSkinCoordWeight(void)
{
    return &_mfSkinCoordWeight;
}

MFReal32 *VRMLJoint::getMFStiffness(void)
{
    return &_mfStiffness;
}

MFReal32 *VRMLJoint::getMFULimit(void)
{
    return &_mfULimit;
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
    static Char8 cvsid_hpp[] = OSGVRMLJOINT_HEADER_CVSID;
}
