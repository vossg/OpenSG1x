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

#include "OSGVRMLSound.h"

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlSoundDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        SFVec3f::getClassType(),
        "direction",
        OSG_RC_ELEM_IDM_DESC(VRMLSound::DirectionField),
        false,
        (DataElemGetMethod) &VRMLSound::getSFDirection,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "intensity",
        OSG_RC_ELEM_IDM_DESC(VRMLSound::IntensityField),
        false,
        (DataElemGetMethod) &VRMLSound::getSFIntensity,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFVec3f::getClassType(),
        "location",
        OSG_RC_ELEM_IDM_DESC(VRMLSound::LocationField),
        false,
        (DataElemGetMethod) &VRMLSound::getSFLocation,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "maxBack",
        OSG_RC_ELEM_IDM_DESC(VRMLSound::MaxBackField),
        false,
        (DataElemGetMethod) &VRMLSound::getSFMaxBack,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "maxFront",
        OSG_RC_ELEM_IDM_DESC(VRMLSound::MaxFrontField),
        false,
        (DataElemGetMethod) &VRMLSound::getSFMaxFront,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "minBack",
        OSG_RC_ELEM_IDM_DESC(VRMLSound::MinBackField),
        false,
        (DataElemGetMethod) &VRMLSound::getSFMinBack,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "minFront",
        OSG_RC_ELEM_IDM_DESC(VRMLSound::MinFrontField),
        false,
        (DataElemGetMethod) &VRMLSound::getSFMinFront,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "priority",
        OSG_RC_ELEM_IDM_DESC(VRMLSound::PriorityField),
        false,
        (DataElemGetMethod) &VRMLSound::getSFPriority,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFVRMLNode::getClassType(),
        "source",
        OSG_RC_ELEM_IDM_DESC(VRMLSound::SourceField),
        false,
        (DataElemGetMethod) &VRMLSound::getSFSource,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFBool::getClassType(),
        "spatialize",
        OSG_RC_ELEM_IDM_DESC(VRMLSound::SpatializeField),
        false,
        (DataElemGetMethod) &VRMLSound::getSFSpatialize,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}

VRMLObjectType VRMLSound::_type(
    "Sound",
    "VRMLUnlimitedNode",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLSound::createEmpty,
    NULL, // Init
    vrmlSoundDescInserter,
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

VRMLSound::VRMLSound(void) :
     Inherited(),

    _sfDirection (    ),
    _sfIntensity ( 1.f),
    _sfLocation  (    ),
    _sfMaxBack   (10.f),
    _sfMaxFront  (10.f),
    _sfMinBack   ( 0.f),
    _sfMinFront  ( 0.f),
    _sfPriority  ( 1.f),
    _sfSource    (NULL),
    _sfSpatialize(true)
{
    _sfDirection.getValue().setValues(0.f, 0.f, 1.f);
    _sfLocation .getValue().setValues(0.f, 0.f, 0.f);
}


VRMLSound::VRMLSound(const VRMLSound &source) :
     Inherited   (source              ),

    _sfDirection (source._sfDirection ),
    _sfIntensity (source._sfIntensity ),
    _sfLocation  (source._sfLocation  ),
    _sfMaxBack   (source._sfMaxBack   ),
    _sfMaxFront  (source._sfMaxFront  ),
    _sfMinBack   (source._sfMinBack   ),
    _sfMinFront  (source._sfMinFront  ),
    _sfPriority  (source._sfPriority  ),
    _sfSource    (source._sfSource    ),
    _sfSpatialize(source._sfSpatialize)
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLSound, Ptr);

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLSound::~VRMLSound(void)
{
}

/*------------------------------ access -----------------------------------*/

SFVec3f *VRMLSound::getSFDirection(void)
{
    return &_sfDirection;
}

SFReal32 *VRMLSound::getSFIntensity(void)
{
    return &_sfIntensity;
}

SFVec3f *VRMLSound::getSFLocation(void)
{
    return &_sfLocation;
}

SFReal32 *VRMLSound::getSFMaxBack(void)
{
    return &_sfMaxBack;
}

SFReal32 *VRMLSound::getSFMaxFront(void)
{
    return &_sfMaxFront;
}

SFReal32 *VRMLSound::getSFMinBack(void)
{
    return &_sfMinBack;
}

SFReal32 *VRMLSound::getSFMinFront(void)
{
    return &_sfMinFront;
}

SFReal32 *VRMLSound::getSFPriority(void)
{
    return &_sfPriority;
}

SFVRMLNode *VRMLSound::getSFSource(void)
{
    return &_sfSource;
}

SFBool *VRMLSound::getSFSpatialize(void)
{
    return &_sfSpatialize;
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
    static Char8 cvsid_hpp[] = OSGVRMLSOUND_HEADER_CVSID;
}
