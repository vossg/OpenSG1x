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

#include "OSGVRMLViewpoint.h"

#include <OSGDataElementDesc.h>

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGVRMLVIEWPOINT_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlViewpointDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "fieldOfView",
        OSG_RC_ELEM_IDM_DESC(VRMLViewpoint::FieldOfViewField),
        false,
        (DataElemGetMethod) &VRMLViewpoint::getSFFieldOfView,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFBool::getClassType(),
        "jump",
        OSG_RC_ELEM_IDM_DESC(VRMLViewpoint::JumpField),
        false,
        (DataElemGetMethod) &VRMLViewpoint::getSFJump,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFRotation::getClassType(),
        "orientation",
        OSG_RC_ELEM_IDM_DESC(VRMLViewpoint::OrientationField),
        false,
        (DataElemGetMethod) &VRMLViewpoint::getSFOrientation,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFVec3f::getClassType(),
        "position",
        OSG_RC_ELEM_IDM_DESC(VRMLViewpoint::PositionField),
        false,
        (DataElemGetMethod) &VRMLViewpoint::getSFPosition,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFString::getClassType(),
        "description",
        OSG_RC_ELEM_IDM_DESC(VRMLViewpoint::DescriptionField),
        false,
        (DataElemGetMethod) &VRMLViewpoint::getSFDescription,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}


VRMLObjectType VRMLViewpoint::_type(
    "Viewpoint",
    "VRMLUnlimitedNode",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLViewpoint::createEmpty,
    NULL,
    vrmlViewpointDescInserter,
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

VRMLViewpoint::VRMLViewpoint(void) :
	 Inherited(),

    _sfFieldOfView(0.785398f),
    _sfJump       (true     ),
    _sfOrientation(         ),
    _sfPosition   (         ),
    _sfDescription(         )
{
    _sfOrientation.getValue().setValueAsQuat(0.f, 0.f, 0.f, 1.f);
    _sfPosition   .getValue().setValues     (0.f, 0.f, 0.f     );
}


VRMLViewpoint::VRMLViewpoint(const VRMLViewpoint &source) :
	 Inherited    (source),

    _sfFieldOfView(source._sfFieldOfView),
    _sfJump       (source._sfJump       ),
    _sfOrientation(source._sfOrientation),
    _sfPosition   (source._sfPosition   ),
    _sfDescription(source._sfDescription)
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#ifdef WIN32
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLViewpoint, Ptr);

#ifdef WIN32
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLViewpoint::~VRMLViewpoint(void)
{
}

/*------------------------------ access -----------------------------------*/

SFReal32 *VRMLViewpoint::getSFFieldOfView (void)
{
    return &_sfFieldOfView;
}

SFBool *VRMLViewpoint::getSFJump(void)
{
    return &_sfJump;
}

SFRotation *VRMLViewpoint::getSFOrientation(void)
{
    return &_sfOrientation;
}

SFVec3f *VRMLViewpoint::getSFPosition(void)
{
    return &_sfPosition;
}

SFString *VRMLViewpoint::getSFDescription(void)
{
    return &_sfDescription;
}


