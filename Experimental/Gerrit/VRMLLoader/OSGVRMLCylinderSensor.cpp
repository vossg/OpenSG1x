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

#include "OSGVRMLCylinderSensor.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGVRMLCYLINDERSENSOR_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlCylinderSensorDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        SFBool::getClassType(),
        "autoOffset",
        OSG_RC_ELEM_IDM_DESC(VRMLCylinderSensor::AutoOffsetField),
        false,
        (DataElemGetMethod) &VRMLCylinderSensor::getSFAutoOffset,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "diskAngle",
        OSG_RC_ELEM_IDM_DESC(VRMLCylinderSensor::DiskAngleField),
        false,
        (DataElemGetMethod) &VRMLCylinderSensor::getSFDiskAngle,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "maxAngle",
        OSG_RC_ELEM_IDM_DESC(VRMLCylinderSensor::MaxAngleField),
        false,
        (DataElemGetMethod) &VRMLCylinderSensor::getSFMaxAngle,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "minAngle",
        OSG_RC_ELEM_IDM_DESC(VRMLCylinderSensor::MinAngleField),
        false,
        (DataElemGetMethod) &VRMLCylinderSensor::getSFMinAngle,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "offset",
        OSG_RC_ELEM_IDM_DESC(VRMLCylinderSensor::OffsetField),
        false,
        (DataElemGetMethod) &VRMLCylinderSensor::getSFOffset,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}


VRMLObjectType VRMLCylinderSensor::_type(
    "CylinderSensor",
    "VRMLSensor",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLCylinderSensor::createEmpty,
    NULL, // Init
    vrmlCylinderSensorDescInserter,
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

VRMLCylinderSensor::VRMLCylinderSensor(void) :
     Inherited(),

    _sfAutoOffset(true  ),
    _sfDiskAngle (0.262f),
    _sfMaxAngle  (-1.0f ),
    _sfMinAngle  ( 0.0f ),
    _sfOffset    ( 0.0f )
{
}


VRMLCylinderSensor::VRMLCylinderSensor(
    const VRMLCylinderSensor &source) :

     Inherited(source),

    _sfAutoOffset(source._sfAutoOffset),
    _sfDiskAngle (source._sfDiskAngle ),
    _sfMaxAngle  (source._sfMaxAngle  ),
    _sfMinAngle  (source._sfMinAngle  ),
    _sfOffset    (source._sfOffset    )
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#ifdef WIN32
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLCylinderSensor, Ptr);

#ifdef WIN32
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLCylinderSensor::~VRMLCylinderSensor(void)
{
}

void VRMLCylinderSensor::evaluate(Time)
{
}

/*------------------------------ access -----------------------------------*/

SFBool *VRMLCylinderSensor::getSFAutoOffset(void)
{
    return &_sfAutoOffset;
}

SFReal32 *VRMLCylinderSensor::getSFDiskAngle(void)
{
    return &_sfDiskAngle;
}

SFReal32 *VRMLCylinderSensor::getSFMaxAngle(void)
{
    return &_sfMaxAngle;
}

SFReal32 *VRMLCylinderSensor::getSFMinAngle(void)
{
    return &_sfMinAngle;
}

SFReal32 *VRMLCylinderSensor::getSFOffset(void)
{
    return &_sfOffset;
}
