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

#include "OSGVRMLTimeSensor.h"
#include "OSGDataElementDesc.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGVRMLTIMESENSOR_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlTimeSensorDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        SFTime::getClassType(),
        "cycleInterval",
        OSG_RC_ELEM_IDM_DESC(VRMLTimeSensor::CycleIntervalField),
        false,
        (DataElemGetMethod) &VRMLTimeSensor::getSFCycleInterval,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFBool::getClassType(),
        "loop",
        OSG_RC_ELEM_IDM_DESC(VRMLTimeSensor::LoopField),
        false,
        (DataElemGetMethod) &VRMLTimeSensor::getSFLoop,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFTime::getClassType(),
        "startTime",
        OSG_RC_ELEM_IDM_DESC(VRMLTimeSensor::StartTimeField),
        false,
        (DataElemGetMethod) &VRMLTimeSensor::getSFStartTime,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFTime::getClassType(),
        "stopTime",
        OSG_RC_ELEM_IDM_DESC(VRMLTimeSensor::StopTimeField),
        false,
        (DataElemGetMethod) &VRMLTimeSensor::getSFStopTime,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFTime::getClassType(),
        "cycleTime",
        OSG_RC_ELEM_IDM_DESC(VRMLTimeSensor::CycleTimeField),
        false,
        (DataElemGetMethod) &VRMLTimeSensor::getSFCycleTime,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "fraction_changed",
        OSG_RC_ELEM_IDM_DESC(VRMLTimeSensor::FractionChangedField),
        false,
        (DataElemGetMethod) &VRMLTimeSensor::getSFFractionChanged,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFBool::getClassType(),
        "isActive",
        OSG_RC_ELEM_IDM_DESC(VRMLTimeSensor::IsActiveField),
        false,
        (DataElemGetMethod) &VRMLTimeSensor::getSFIsActive,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFTime::getClassType(),
        "time",
        OSG_RC_ELEM_IDM_DESC(VRMLTimeSensor::TimeField),
        false,
        (DataElemGetMethod) &VRMLTimeSensor::getSFTime,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}


VRMLObjectType VRMLTimeSensor::_type(
    "TimeSensor",
    "VRMLSensor",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLTimeSensor::createEmpty,
    NULL, // Init
    vrmlTimeSensorDescInserter,
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


VRMLTimeSensor::VRMLTimeSensor(void) :
	 Inherited        (     ),
    _sfCycleInterval  (1.0  ),
    _sfLoop           (false),
    _sfStartTime      (0.0  ),
    _sfStopTime       (0.0  ),
    
    _sfCycleTime      (0.0  ),
    _sfFractionChanged(false),
    _sfIsActive       (false),
    _sfTime           (0.0  )
{
}


VRMLTimeSensor::VRMLTimeSensor(const VRMLTimeSensor &source) :
	 Inherited        (source                   ),
    _sfCycleInterval  (source._sfCycleInterval  ),
    _sfLoop           (source._sfLoop           ),
    _sfStartTime      (source._sfStartTime      ),
    _sfStopTime       (source._sfStopTime       ),

    _sfCycleTime      (source._sfCycleTime      ),
    _sfFractionChanged(source._sfFractionChanged),
    _sfIsActive       (source._sfIsActive       ),
    _sfTime           (source._sfTime           )
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#ifdef WIN32
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLTimeSensor, Ptr);

#ifdef WIN32
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLTimeSensor::~VRMLTimeSensor(void)
{
}

/*-------------------------------- eval -----------------------------------*/

void VRMLTimeSensor::evaluate(Time)
{
}

/*------------------------------ access -----------------------------------*/

SFTime *VRMLTimeSensor::getSFCycleInterval(void)
{
    return &_sfCycleInterval;
}

SFBool *VRMLTimeSensor::getSFLoop(void)
{
    return &_sfLoop;
}

SFTime *VRMLTimeSensor::getSFStartTime(void)
{
    return &_sfStartTime;
}

SFTime *VRMLTimeSensor::getSFStopTime(void)
{
    return &_sfStopTime;
}

SFTime *VRMLTimeSensor::getSFCycleTime(void)
{
    return &_sfCycleTime;
}

SFReal32 *VRMLTimeSensor::getSFFractionChanged(void)
{
    return &_sfFractionChanged;
}

SFBool *VRMLTimeSensor::getSFIsActive(void)
{
    return &_sfIsActive;
}

SFTime *VRMLTimeSensor::getSFTime(void)
{
    return &_sfTime;
}
