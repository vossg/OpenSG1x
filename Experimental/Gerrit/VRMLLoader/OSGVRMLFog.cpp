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

#include "OSGVRMLFog.h"

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlFogDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        SFColor3f::getClassType(),
        "color",
        OSG_RC_ELEM_IDM_DESC(VRMLFog::ColorField),
        false,
        (DataElemGetMethod) &VRMLFog::getSFColor,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFString::getClassType(),
        "fogType",
        OSG_RC_ELEM_IDM_DESC(VRMLFog::FogTypeField),
        false,
        (DataElemGetMethod) &VRMLFog::getSFFogType,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "visibilityRange",
        OSG_RC_ELEM_IDM_DESC(VRMLFog::VisibilityRangeField),
        false,
        (DataElemGetMethod) &VRMLFog::getSFVisibilityRange,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}


VRMLObjectType VRMLFog::_type(
    "Fog",
    "VRMLUnlimitedNode",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLFog::createEmpty,
    NULL, // Init
    vrmlFogDescInserter,
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

VRMLFog::VRMLFog(void) :
     Inherited(),

    _sfColor          (   ),
    _sfFogType        (   ),
    _sfVisibilityRange(0.f)
{
    _sfColor  .getValue().setValuesRGB(1.0f, 1.0f, 1.0f);
    _sfFogType.getValue().assign      ("LINEAR"        );
}


VRMLFog::VRMLFog(const VRMLFog &source) :
     Inherited        (source                   ),

    _sfColor          (source._sfColor          ),
    _sfFogType        (source._sfFogType        ),
    _sfVisibilityRange(source._sfVisibilityRange)
{
}


/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLFog, Ptr);

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLFog::~VRMLFog(void)
{
}

/*------------------------------ access -----------------------------------*/

SFColor3f *VRMLFog::getSFColor(void)
{
    return &_sfColor;
}

SFString *VRMLFog::getSFFogType(void)
{
    return &_sfFogType;
}

SFReal32 *VRMLFog::getSFVisibilityRange(void)
{
    return &_sfVisibilityRange;
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
    static Char8 cvsid_hpp[] = OSGVRMLFOG_HEADER_CVSID;
}
