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

#include "OSGVRMLExtrusion.h"

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlExtrusionDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        SFBool::getClassType(),
        "beginCap",
        OSG_RC_ELEM_IDM_DESC(VRMLExtrusion::BeginCapField),
        false,
        (DataElemGetMethod) &VRMLExtrusion::getSFBeginCap,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFBool::getClassType(),
        "ccw",
        OSG_RC_ELEM_IDM_DESC(VRMLExtrusion::CcwField),
        false,
        (DataElemGetMethod) &VRMLExtrusion::getSFCcw,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFBool::getClassType(),
        "convex",
        OSG_RC_ELEM_IDM_DESC(VRMLExtrusion::ConvexField),
        false,
        (DataElemGetMethod) &VRMLExtrusion::getSFConvex,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "creaseAngle",
        OSG_RC_ELEM_IDM_DESC(VRMLExtrusion::CreaseAngleField),
        false,
        (DataElemGetMethod) &VRMLExtrusion::getSFCreaseAngle,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFVec2f::getClassType(),
        "crossSection",
        OSG_RC_ELEM_IDM_DESC(VRMLExtrusion::CrossSectionField),
        false,
        (DataElemGetMethod) &VRMLExtrusion::getMFCrossSection,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFBool::getClassType(),
        "endCap",
        OSG_RC_ELEM_IDM_DESC(VRMLExtrusion::EndCapField),
        false,
        (DataElemGetMethod) &VRMLExtrusion::getSFEndCap,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFRotation::getClassType(),
        "orientation",
        OSG_RC_ELEM_IDM_DESC(VRMLExtrusion::OrientationField),
        false,
        (DataElemGetMethod) &VRMLExtrusion::getMFOrientation,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFVec2f::getClassType(),
        "scale",
        OSG_RC_ELEM_IDM_DESC(VRMLExtrusion::ScaleField),
        false,
        (DataElemGetMethod) &VRMLExtrusion::getMFScale,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFBool::getClassType(),
        "solid",
        OSG_RC_ELEM_IDM_DESC(VRMLExtrusion::SolidField),
        false,
        (DataElemGetMethod) &VRMLExtrusion::getSFSolid,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFVec3f::getClassType(),
        "spine",
        OSG_RC_ELEM_IDM_DESC(VRMLExtrusion::SpineField),
        false,
        (DataElemGetMethod) &VRMLExtrusion::getMFSpine,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}


VRMLObjectType VRMLExtrusion::_type(
    "Extrusion",
    "VRMLGeometry",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLExtrusion::createEmpty,
    NULL, // Init
    vrmlExtrusionDescInserter,
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

VRMLExtrusion::VRMLExtrusion(void) :
     Inherited     (),

    _sfBeginCap    (true),
    _sfCcw         (true),
    _sfConvex      (true),
    _sfCreaseAngle ( 0.f),
    _mfCrossSection(    ),
    _sfEndCap      (true),
    _mfOrientation (    ),
    _mfScale       (    ),
    _sfSolid       (true),
    _mfSpine       (    )
{
}


VRMLExtrusion::VRMLExtrusion(const VRMLExtrusion &source) :
     Inherited     (source                ),

    _sfBeginCap    (source._sfBeginCap    ),
    _sfCcw         (source._sfCcw         ),
    _sfConvex      (source._sfConvex      ),
    _sfCreaseAngle (source._sfCreaseAngle ),
    _mfCrossSection(source._mfCrossSection),
    _sfEndCap      (source._sfEndCap      ),
    _mfOrientation (source._mfOrientation ),
    _mfScale       (source._mfScale       ),
    _sfSolid       (source._sfSolid       ),
    _mfSpine       (source._mfSpine       )
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLExtrusion, Ptr);

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLExtrusion::~VRMLExtrusion(void)
{
}

/*------------------------------ access -----------------------------------*/

SFBool *VRMLExtrusion::getSFBeginCap(void)
{
    return &_sfBeginCap;
}

SFBool *VRMLExtrusion::getSFCcw(void)
{
    return &_sfCcw;
}

SFBool *VRMLExtrusion::getSFConvex(void)
{
    return &_sfConvex;
}

SFReal32 *VRMLExtrusion::getSFCreaseAngle(void)
{
    return &_sfCreaseAngle;
}

MFVec2f *VRMLExtrusion::getMFCrossSection(void)
{
    return &_mfCrossSection;
}

SFBool *VRMLExtrusion::getSFEndCap(void)
{
    return &_sfEndCap;
}

MFRotation *VRMLExtrusion::getMFOrientation(void)
{
    return &_mfOrientation;
}

MFVec2f *VRMLExtrusion::getMFScale(void)
{
    return &_mfScale;
}

SFBool *VRMLExtrusion::getSFSolid(void)
{
    return &_sfSolid;
}

MFVec3f *VRMLExtrusion::getMFSpine(void)
{
    return &_mfSpine;
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
    static Char8 cvsid_hpp[] = OSGVRMLEXTRUSION_HEADER_CVSID;
}
