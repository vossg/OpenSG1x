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

#include "OSGVRMLDirectionalLight.h"

#include <OSGDataElementDesc.h>

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGVRMLDIRECTIONALLIGHT_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlDirectionalLightDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        SFVec3f::getClassType(),
        "direction",
        OSG_RC_ELEM_IDM_DESC(VRMLDirectionalLight::DirectionField),
        false,
        (DataElemGetMethod) &VRMLDirectionalLight::getSFDirection,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}

VRMLObjectType VRMLDirectionalLight::_type(
    "DirectionalLight",
    "VRMLLight",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLDirectionalLight::createEmpty,
    NULL, // Init
    vrmlDirectionalLightDescInserter,
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

VRMLDirectionalLight::VRMLDirectionalLight(void) :
	 Inherited  (),

    _sfDirection()
{
    _sfDirection.getValue().setValues(0.f, 0.f, -1.f);
}


VRMLDirectionalLight::VRMLDirectionalLight(
    const VRMLDirectionalLight &source) :

	 Inherited  (source             ),

    _sfDirection(source._sfDirection)
{
}


/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#ifdef WIN32
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLDirectionalLight, Ptr);

#ifdef WIN32
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLDirectionalLight::~VRMLDirectionalLight(void)
{
}

/*------------------------------ access -----------------------------------*/

SFVec3f *VRMLDirectionalLight::getSFDirection(void)
{
    return &_sfDirection;
}
