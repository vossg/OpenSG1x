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

#include "OSGVRMLAudioClip.h"

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlAudioClipDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        SFString::getClassType(),
        "description",
        OSG_RC_ELEM_IDM_DESC(VRMLAudioClip::DescriptionField),
        false,
        (DataElemGetMethod) &VRMLAudioClip::getSFDescription,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFBool::getClassType(),
        "loop",
        OSG_RC_ELEM_IDM_DESC(VRMLAudioClip::LoopField),
        false,
        (DataElemGetMethod) &VRMLAudioClip::getSFLoop,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "pitch",
        OSG_RC_ELEM_IDM_DESC(VRMLAudioClip::PitchField),
        false,
        (DataElemGetMethod) &VRMLAudioClip::getSFPitch,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFTime::getClassType(),
        "startTime",
        OSG_RC_ELEM_IDM_DESC(VRMLAudioClip::StartTimeField),
        false,
        (DataElemGetMethod) &VRMLAudioClip::getSFStartTime,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFTime::getClassType(),
        "stopTime",
        OSG_RC_ELEM_IDM_DESC(VRMLAudioClip::StopTimeField),
        false,
        (DataElemGetMethod) &VRMLAudioClip::getSFStopTime,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFString::getClassType(),
        "url",
        OSG_RC_ELEM_IDM_DESC(VRMLAudioClip::UrlField),
        false,
        (DataElemGetMethod) &VRMLAudioClip::getMFUrl,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}


VRMLObjectType VRMLAudioClip::_type(
    "AudioClip",
    "VRMLUnlimitedNode",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLAudioClip::createEmpty,
    NULL, // Init
    vrmlAudioClipDescInserter,
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

VRMLAudioClip::VRMLAudioClip(void) :
     Inherited    (),

    _sfDescription(),
    _sfLoop       (false),
    _sfPitch      (1.0f ),
    _sfStartTime  (0.0  ),
    _sfStopTime   (0.0  ),
    _mfUrl        (     )
{
}


VRMLAudioClip::VRMLAudioClip(const VRMLAudioClip &source) :
     Inherited    (source),

    _sfDescription(source._sfDescription),
    _sfLoop       (source._sfLoop       ),
    _sfPitch      (source._sfPitch      ),
    _sfStartTime  (source._sfStartTime  ),
    _sfStopTime   (source._sfStopTime   ),
    _mfUrl        (source._mfUrl        )
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLAudioClip, Ptr);

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLAudioClip::~VRMLAudioClip(void)
{
}

/*------------------------------ access -----------------------------------*/

SFString *VRMLAudioClip::getSFDescription(void)
{
    return &_sfDescription;
}

SFBool *VRMLAudioClip::getSFLoop(void)
{
    return &_sfLoop;
}

SFReal32 *VRMLAudioClip::getSFPitch(void)
{
    return &_sfPitch;
}

SFTime *VRMLAudioClip::getSFStartTime(void)
{
    return &_sfStartTime;
}

SFTime *VRMLAudioClip::getSFStopTime(void)
{
    return &_sfStopTime;
}

MFString *VRMLAudioClip::getMFUrl(void)
{
    return &_mfUrl;
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
    static Char8 cvsid_hpp[] = OSGVRMLAUDIOCLIP_HEADER_CVSID;
}
