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

#include "OSGVRMLOrientationInterpolator.h"
#include "OSGDataElementDesc.h"

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlOrientationInterpolatorDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        MFReal32::getClassType(),
        "key",
        OSG_RC_ELEM_IDM_DESC(VRMLOrientationInterpolator::KeyField),
        false,
        (DataElemGetMethod) &VRMLOrientationInterpolator::getMFKey,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFQuaternion::getClassType(),
        "keyValue",
        OSG_RC_ELEM_IDM_DESC(VRMLOrientationInterpolator::KeyValueField),
        false,
        (DataElemGetMethod) &VRMLOrientationInterpolator::getMFKeyValue,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}


VRMLObjectType VRMLOrientationInterpolator::_type(
    "OrientationInterpolator",
    "VRMLUnlimitedNode",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLOrientationInterpolator::createEmpty,
    NULL, // Init
    vrmlOrientationInterpolatorDescInserter,
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


VRMLOrientationInterpolator::VRMLOrientationInterpolator(void) :
	 Inherited        (     ),
    _mfKey            (     ),
    _mfKeyValue       (     )
{
}


VRMLOrientationInterpolator::VRMLOrientationInterpolator(const VRMLOrientationInterpolator &source) :
	 Inherited          (source                ),
    _mfKey              (source._mfKey         ),
    _mfKeyValue         (source._mfKeyValue    )
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLOrientationInterpolator, Ptr);

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLOrientationInterpolator::~VRMLOrientationInterpolator(void)
{
}

/*-------------------------------- eval -----------------------------------*/

void VRMLOrientationInterpolator::evaluate(Time)
{
}

/*------------------------------ access -----------------------------------*/

MFReal32 *VRMLOrientationInterpolator::getMFKey(void)
{
    return &_mfKey;
}

MFQuaternion *VRMLOrientationInterpolator::getMFKeyValue(void)
{
    return &_mfKeyValue;
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
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGVRMLOrientationInterpolator.cpp,v 1.2 2004/03/07 17:43:09 a-m-z Exp $";
    static Char8 cvsid_hpp[] = OSGVRMLORIENTATIONINTERPOLATOR_HEADER_CVSID;
}
