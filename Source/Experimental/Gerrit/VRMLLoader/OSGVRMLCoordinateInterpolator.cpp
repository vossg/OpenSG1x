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

#include "OSGVRMLCoordinateInterpolator.h"
#include "OSGDataElementDesc.h"

OSG_USING_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlCoordinateInterpolatorDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        MFReal32::getClassType(),
        "key",
        OSG_RC_ELEM_IDM_DESC(VRMLCoordinateInterpolator::KeyField),
        false,
        (DataElemGetMethod) &VRMLCoordinateInterpolator::getMFKey,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFVec3f::getClassType(),
        "keyValue",
        OSG_RC_ELEM_IDM_DESC(VRMLCoordinateInterpolator::KeyValueField),
        false,
        (DataElemGetMethod) &VRMLCoordinateInterpolator::getMFKeyValue,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

}


VRMLObjectType VRMLCoordinateInterpolator::_type(
    "CoordinateInterpolator",
    "VRMLUnlimitedNode",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLCoordinateInterpolator::createEmpty,
    NULL, // Init
    vrmlCoordinateInterpolatorDescInserter,
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


VRMLCoordinateInterpolator::VRMLCoordinateInterpolator(void) :
	 Inherited        (     ),
    _mfKey            (     ),
    _mfKeyValue       (     )
{
}


VRMLCoordinateInterpolator::VRMLCoordinateInterpolator(const VRMLCoordinateInterpolator &source) :
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

OSG_VRMLOBJ_DEF(VRMLCoordinateInterpolator, Ptr);

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLCoordinateInterpolator::~VRMLCoordinateInterpolator(void)
{
}

/*-------------------------------- eval -----------------------------------*/

void VRMLCoordinateInterpolator::evaluate(Time)
{
}

/*------------------------------ access -----------------------------------*/

MFReal32 *VRMLCoordinateInterpolator::getMFKey(void)
{
    return &_mfKey;
}

MFVec3f *VRMLCoordinateInterpolator::getMFKeyValue(void)
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
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGVRMLCoordinateInterpolator.cpp,v 1.1 2004/03/07 17:43:09 a-m-z Exp $";
    static Char8 cvsid_hpp[] = OSGVRMLCOORDINATEINTERPOLATOR_HEADER_CVSID;
}
