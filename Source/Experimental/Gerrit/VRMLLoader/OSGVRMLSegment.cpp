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

#include "OSGVRMLSegment.h"

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlSegmentDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        SFVec3f::getClassType(),
        "centerOfMass",
        OSG_RC_ELEM_IDM_DESC(VRMLSegment::CenterOfMassField),
        false,
        (DataElemGetMethod) &VRMLSegment::getSFCenterOfMass,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFVRMLNode::getClassType(),
        "coord",
        OSG_RC_ELEM_IDM_DESC(VRMLSegment::CoordField),
        false,
        (DataElemGetMethod) &VRMLSegment::getSFCoord,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFVRMLNode::getClassType(),
        "displacers",
        OSG_RC_ELEM_IDM_DESC(VRMLSegment::DisplacersField),
        false,
        (DataElemGetMethod) &VRMLSegment::getMFDisplacers,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "mass",
        OSG_RC_ELEM_IDM_DESC(VRMLSegment::MassField),
        false,
        (DataElemGetMethod) &VRMLSegment::getSFMass,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFReal32::getClassType(),
        "momentOfInertia",
        OSG_RC_ELEM_IDM_DESC(VRMLSegment::MomentsOfInertiaField),
        false,
        (DataElemGetMethod) &VRMLSegment::getMFMomentsOfInertia,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFString::getClassType(),
        "name",
        OSG_RC_ELEM_IDM_DESC(VRMLSegment::NameField),
        false,
        (DataElemGetMethod) &VRMLSegment::getSFName,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}


VRMLObjectType VRMLSegment::_type(
    "Segment",
    "Group",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLSegment::createEmpty,
    NULL,
    vrmlSegmentDescInserter,
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

VRMLSegment::VRMLSegment(void) :
	 Inherited         (    ),
    _sfCenterOfMass    (    ),
    _sfCoord           (NULL),
    _mfDisplacers      (    ),
    _sfMass            ( 0.f),
    _mfMomentsOfInertia(    ),
    _sfName            (    )
{
    // TODO Empty Moments

    _sfCenterOfMass.getValue().setValues(0.f, 0.f, 0.f);
}


VRMLSegment::VRMLSegment(const VRMLSegment &source) :
	 Inherited         (source                    ),
    _sfCenterOfMass    (source._sfCenterOfMass    ),
    _sfCoord           (source._sfCoord           ),
    _mfDisplacers      (source._mfDisplacers      ),
    _sfMass            (source._sfMass            ),
    _mfMomentsOfInertia(source._mfMomentsOfInertia),
    _sfName            (source._sfName            )
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLSegment, Ptr);

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLSegment::~VRMLSegment(void)
{
}

/*------------------------------ access -----------------------------------*/

SFVec3f *VRMLSegment::getSFCenterOfMass(void)
{
    return &_sfCenterOfMass;
}

SFVRMLNode *VRMLSegment::getSFCoord(void)
{
    return &_sfCoord;
}

MFVRMLNode *VRMLSegment::getMFDisplacers(void)
{
    return &_mfDisplacers;
}

SFReal32 *VRMLSegment::getSFMass(void)
{
    return &_sfMass;
}

MFReal32 *VRMLSegment::getMFMomentsOfInertia(void)
{
    return &_mfMomentsOfInertia;
}

SFString *VRMLSegment::getSFName(void)
{
    return &_sfName;
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
    static Char8 cvsid_hpp[] = OSGVRMLSEGMENT_HEADER_CVSID;
}
