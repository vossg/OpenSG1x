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

#include "OSGVRMLLight.h"

#include <OSGDataElementDesc.h>

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlLightDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "ambientIntensity",
        OSG_RC_ELEM_IDM_DESC(VRMLLight::AmbientIntensityField),
        false,
        (DataElemGetMethod) &VRMLLight::getSFAmbientIntensity,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFColor3f::getClassType(),
        "color",
        OSG_RC_ELEM_IDM_DESC(VRMLLight::ColorField),
        false,
        (DataElemGetMethod) &VRMLLight::getSFColor,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "intensity",
        OSG_RC_ELEM_IDM_DESC(VRMLLight::IntensityField),
        false,
        (DataElemGetMethod) &VRMLLight::getSFIntensity,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFBool::getClassType(),
        "on",
        OSG_RC_ELEM_IDM_DESC(VRMLLight::OnField),
        false,
        (DataElemGetMethod) &VRMLLight::getSFOn,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}

VRMLObjectType VRMLLight::_type(
    "VRMLLight",
    "VRMLUnlimitedNode",
    "VRMLNodes",
    NULL,
    NULL, // Init
    vrmlLightDescInserter,
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

VRMLLight::VRMLLight(void) :
	 Inherited         (    ),

    _sfAmbientIntensity(0.f ),
    _sfColor           (    ),
    _sfIntensity       (1.f ),
    _sfOn              (true)
{
    _sfColor.getValue().setValuesRGB(1.f, 1.f, 1.f);
}


VRMLLight::VRMLLight(const VRMLLight &source) :
	 Inherited         (source                    ),

    _sfAmbientIntensity(source._sfAmbientIntensity),
    _sfColor           (source._sfColor           ),
    _sfIntensity       (source._sfIntensity       ),
    _sfOn              (source._sfOn              )
{
}


/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (disable : 424)
#endif

OSG_ABSTR_VRMLOBJ_DEF(VRMLLight, Ptr);

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLLight::~VRMLLight(void)
{
}

/*------------------------------ access -----------------------------------*/

SFReal32 *VRMLLight::getSFAmbientIntensity(void)
{
    return &_sfAmbientIntensity;
}

SFColor3f  *VRMLLight::getSFColor(void)
{
    return &_sfColor;
}

SFReal32 *VRMLLight::getSFIntensity(void)
{
    return &_sfIntensity;
}

SFBool *VRMLLight::getSFOn(void)
{
    return &_sfOn;
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
    static Char8 cvsid_hpp[] = OSGVRMLLIGHT_HEADER_CVSID;
}
