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

#include "OSGVRMLPointLight.h"

#include <OSGDataElementDesc.h>

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGVRMLPOINTLIGHT_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlPointLightDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        SFVec3f::getClassType(),
        "attenuation",
        OSG_RC_ELEM_IDM_DESC(VRMLPointLight::AttenuationField),
        false,
        (DataElemGetMethod) &VRMLPointLight::getSFAttenuation,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFVec3f::getClassType(),
        "location",
        OSG_RC_ELEM_IDM_DESC(VRMLPointLight::LocationField),
        false,
        (DataElemGetMethod) &VRMLPointLight::getSFLocation,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "radius",
        OSG_RC_ELEM_IDM_DESC(VRMLPointLight::RadiusField),
        false,
        (DataElemGetMethod) &VRMLPointLight::getSFRadius,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}


VRMLObjectType VRMLPointLight::_type(
    "PointLight",
    "VRMLLight",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLPointLight::createEmpty,
    NULL, // Init
    vrmlPointLightDescInserter,
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

VRMLPointLight::VRMLPointLight(void) :
 	 Inherited    (),

    _sfAttenuation(),
    _sfLocation   (),
    _sfRadius     (100.f)
{
    _sfAttenuation.getValue().setValues(1.f, 0.f, 0.f);
    _sfLocation   .getValue().setValues(0.f, 0.f, 0.f);
}


VRMLPointLight::VRMLPointLight(const VRMLPointLight &source) :
	 Inherited    (source               ),

    _sfAttenuation(source._sfAttenuation),
    _sfLocation   (source._sfLocation   ),
    _sfRadius     (source._sfRadius     )
{
}


/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#ifdef WIN32
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLPointLight, Ptr);

#ifdef WIN32
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLPointLight::~VRMLPointLight(void)
{
}

/*------------------------------ access -----------------------------------*/

SFVec3f  *VRMLPointLight::getSFAttenuation(void)
{
    return &_sfAttenuation;
}

SFVec3f  *VRMLPointLight::getSFLocation(void)
{
    return &_sfLocation;
}

SFReal32 *VRMLPointLight::getSFRadius(void)
{
    return &_sfRadius;
}
