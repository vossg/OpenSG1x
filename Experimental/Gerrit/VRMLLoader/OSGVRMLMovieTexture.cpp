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

#include "OSGVRMLMovieTexture.h"

#include <OSGDataElementDesc.h>

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGVRMLMOVIETEXTURE_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlMovieTextureDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        SFBool::getClassType(),
        "loop",
        OSG_RC_ELEM_IDM_DESC(VRMLMovieTexture::LoopField),
        false,
        (DataElemGetMethod) &VRMLMovieTexture::getSFLoop,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "speed",
        OSG_RC_ELEM_IDM_DESC(VRMLMovieTexture::SpeedField),
        false,
        (DataElemGetMethod) &VRMLMovieTexture::getSFSpeed,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFTime::getClassType(),
        "startTime",
        OSG_RC_ELEM_IDM_DESC(VRMLMovieTexture::StartTimeField),
        false,
        (DataElemGetMethod) &VRMLMovieTexture::getSFStartTime,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFTime::getClassType(),
        "stopTime",
        OSG_RC_ELEM_IDM_DESC(VRMLMovieTexture::StopTimeField),
        false,
        (DataElemGetMethod) &VRMLMovieTexture::getSFStopTime,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFString::getClassType(),
        "url",
        OSG_RC_ELEM_IDM_DESC(VRMLMovieTexture::UrlField),
        false,
        (DataElemGetMethod) &VRMLMovieTexture::getMFUrl,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}


VRMLObjectType VRMLMovieTexture::_type(
    "MovieTexture",
    "VRMLTexture",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLMovieTexture::createEmpty,
    NULL, // Init
    vrmlMovieTextureDescInserter,
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

VRMLMovieTexture::VRMLMovieTexture(void) :
     Inherited  (     ),
    
    _sfLoop     (false),
    _sfSpeed    (1.0f ),
    _sfStartTime(0.0  ),
    _sfStopTime (0.0  ),
    _mfUrl      (     )
{
}


VRMLMovieTexture::VRMLMovieTexture(const VRMLMovieTexture &source) :
     Inherited  (source             ),

    _sfLoop     (source._sfLoop     ),
    _sfSpeed    (source._sfSpeed    ),
    _sfStartTime(source._sfStartTime),
    _sfStopTime (source._sfStopTime ),
    _mfUrl      (source._mfUrl      )
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#ifdef WIN32
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLMovieTexture, Ptr);

#ifdef WIN32
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLMovieTexture::~VRMLMovieTexture(void)
{
}

/*------------------------------ access -----------------------------------*/

SFBool *VRMLMovieTexture::getSFLoop(void)
{
    return &_sfLoop;
}

SFReal32 *VRMLMovieTexture::getSFSpeed(void)
{
    return &_sfSpeed;
}

SFTime *VRMLMovieTexture::getSFStartTime(void)
{
    return &_sfStartTime;
}

SFTime *VRMLMovieTexture::getSFStopTime(void)
{
    return &_sfStopTime;
}

MFString *VRMLMovieTexture::getMFUrl(void)
{
    return &_mfUrl;
}
