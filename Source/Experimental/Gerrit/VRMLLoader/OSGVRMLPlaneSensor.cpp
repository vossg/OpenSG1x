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

#include "OSGVRMLPlaneSensor.h"

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlPlaneSensorDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        SFBool::getClassType(),
        "autoOffset",
        OSG_RC_ELEM_IDM_DESC(VRMLPlaneSensor::AutoOffsetField),
        false,
        (DataElemGetMethod) &VRMLPlaneSensor::getSFAutoOffset,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFVec2f::getClassType(),
        "maxPosition",
        OSG_RC_ELEM_IDM_DESC(VRMLPlaneSensor::MaxPositionField),
        false,
        (DataElemGetMethod) &VRMLPlaneSensor::getSFMaxPosition,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFVec2f::getClassType(),
        "minPosition",
        OSG_RC_ELEM_IDM_DESC(VRMLPlaneSensor::MinPositionField),
        false,
        (DataElemGetMethod) &VRMLPlaneSensor::getSFMinPosition,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFVec3f::getClassType(),
        "offset",
        OSG_RC_ELEM_IDM_DESC(VRMLPlaneSensor::OffsetField),
        false,
        (DataElemGetMethod) &VRMLPlaneSensor::getSFOffset,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}


VRMLObjectType VRMLPlaneSensor::_type(
    "PlaneSensor",
    "VRMLSensor",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLPlaneSensor::createEmpty,
    NULL, // Init
    vrmlPlaneSensorDescInserter,
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

VRMLPlaneSensor::VRMLPlaneSensor(void) :
     Inherited(),

    _sfAutoOffset (true),
    _sfMaxPosition(    ),
    _sfMinPosition(    ),
    _sfOffset     (    )
{
    _sfMaxPosition.getValue().setValues(-1.f, -1.f     );
    _sfMinPosition.getValue().setValues( 0.f,  0.f     );
    _sfOffset     .getValue().setValues( 0.f,  0.f, 0.f);
}


VRMLPlaneSensor::VRMLPlaneSensor(
    const VRMLPlaneSensor &source) :

     Inherited(source),

    _sfAutoOffset (source._sfAutoOffset ),
    _sfMaxPosition(source._sfMaxPosition),
    _sfMinPosition(source._sfMinPosition),
    _sfOffset     (source._sfOffset     )
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLPlaneSensor, Ptr);

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLPlaneSensor::~VRMLPlaneSensor(void)
{
}

void VRMLPlaneSensor::evaluate(Time)
{
}

/*------------------------------ access -----------------------------------*/

SFBool *VRMLPlaneSensor::getSFAutoOffset(void)
{
    return &_sfAutoOffset;
}

SFVec2f *VRMLPlaneSensor::getSFMaxPosition(void)
{
    return &_sfMaxPosition;
}

SFVec2f *VRMLPlaneSensor::getSFMinPosition(void)
{
    return &_sfMinPosition;
}

SFVec3f *VRMLPlaneSensor::getSFOffset(void)
{
    return &_sfOffset;
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
    static Char8 cvsid_hpp[] = OSGVRMLPLANESENSOR_HEADER_CVSID;
}
