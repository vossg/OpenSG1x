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

#include "OSGVRMLColorInterpolator.h"
#include "OSGDataElementDesc.h"

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlColorInterpolatorDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        MFReal32::getClassType(),
        "key",
        OSG_RC_ELEM_IDM_DESC(VRMLColorInterpolator::KeyField),
        false,
        (DataElemGetMethod) &VRMLColorInterpolator::getMFKey,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFColor3f::getClassType(),
        "keyValue",
        OSG_RC_ELEM_IDM_DESC(VRMLColorInterpolator::KeyValueField),
        false,
        (DataElemGetMethod) &VRMLColorInterpolator::getMFKeyValue,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "set_fraction",
        OSG_RC_ELEM_IDM_DESC(VRMLColorInterpolator::SetFractionField),
        false,
        (DataElemGetMethod) &VRMLColorInterpolator::getSFSetFraction,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFColor3f::getClassType(),
        "value_changed",
        OSG_RC_ELEM_IDM_DESC(VRMLColorInterpolator::ValueChangedField),
        false,
        (DataElemGetMethod) &VRMLColorInterpolator::getSFValueChanged,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}


VRMLObjectType VRMLColorInterpolator::_type(
    "ColorInterpolator",
    "VRMLUnlimitedNode",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLColorInterpolator::createEmpty,
    NULL, // Init
    vrmlColorInterpolatorDescInserter,
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


VRMLColorInterpolator::VRMLColorInterpolator(void) :
	 Inherited        (     ),
    _mfKey            (     ),
    _mfKeyValue       (     ),
    _sfSetFraction    (0.0  ),
    _sfValueChanged   (     )
{
}


VRMLColorInterpolator::VRMLColorInterpolator(const VRMLColorInterpolator &source) :
	 Inherited          (source                ),
    _mfKey              (source._mfKey         ),
    _mfKeyValue         (source._mfKeyValue    ),
    _sfSetFraction      (source._sfSetFraction ),
    _sfValueChanged     (source._sfValueChanged)
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLColorInterpolator, Ptr);

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLColorInterpolator::~VRMLColorInterpolator(void)
{
}

/*-------------------------------- eval -----------------------------------*/

void VRMLColorInterpolator::evaluate(Time)
{
}

/*------------------------------ access -----------------------------------*/

MFReal32 *VRMLColorInterpolator::getMFKey(void)
{
    return &_mfKey;
}

MFColor3f *VRMLColorInterpolator::getMFKeyValue(void)
{
    return &_mfKeyValue;
}

SFReal32 *VRMLColorInterpolator::getSFSetFraction(void)
{
    return &_sfSetFraction;
}

SFColor3f *VRMLColorInterpolator::getSFValueChanged(void)
{
    return &_sfValueChanged;
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
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGVRMLColorInterpolator.cpp,v 1.1 2004/03/05 17:36:07 a-m-z Exp $";
    static Char8 cvsid_hpp[] = OSGVRMLPOSITIONINTERPOLATOR_HEADER_CVSID;
}
