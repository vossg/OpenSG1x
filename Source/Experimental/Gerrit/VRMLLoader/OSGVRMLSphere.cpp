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

#include "OSGVRMLSphere.h"
#include "OSGDataElementDesc.h"

#include <OSGGeometry.h>
#include <OSGSimpleGeometry.h>
#include <OSGVRMLToOSGAction.h>

OSG_USING_NAMESPACE

OSG_BEGIN_NAMESPACE

VRMLAction::ActionResult osgVRMLSphereToOpenSG(VRMLNode   &oNode,
                                               VRMLAction *pAction);

OSG_END_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlSphereDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "radius",
        OSG_RC_ELEM_IDM_DESC(VRMLSphere::RadiusField),
        false,
        (DataElemGetMethod) &VRMLSphere::getSFRadius,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}


VRMLObjectType VRMLSphere::_type(
    "Sphere",
    "VRMLGeometry",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLSphere::createEmpty,
    &VRMLSphere::init,
    vrmlSphereDescInserter,
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

void VRMLSphere::init(void)
{
    VRMLToOSGAction::registerDefaultTrav(
        VRMLSphere::getClassType(),
        osgTypedFunctionFunctor2Ref<VRMLAction::ActionResult,
                                    VRMLNode,
                                    VRMLAction *>(osgVRMLSphereToOpenSG));
}

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

VRMLSphere::VRMLSphere(void) :
 	 Inherited(   ),
    _sfRadius (1.f)
{
}

VRMLSphere::VRMLSphere(const VRMLSphere &source) :
	 Inherited(source),
    _sfRadius (source._sfRadius)
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLSphere, Ptr);

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLSphere::~VRMLSphere(void)
{
}

/*------------------------------ access -----------------------------------*/

SFReal32 *VRMLSphere::getSFRadius(void)
{
    return &_sfRadius;
}


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

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

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

VRMLSphereBinder::VRMLSphereBinder(void) :
	Inherited()
{
}

VRMLSphereBinder::~VRMLSphereBinder(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLSphereBinder::init(VRMLToOSGAction *)
{
    if(_pNode == NULL)
        return;

    VRMLSphere *pNode = dynamic_cast<VRMLSphere *>(_pNode);

    if(pNode == NULL)
        return;

    _pFieldContainer = makeSphereGeo(3, 
                                     pNode->getSFRadius()->getValue());
}

void VRMLSphereBinder::finish(VRMLToOSGAction *)
{
}


VRMLAction::ActionResult OSG::osgVRMLSphereToOpenSG(
    VRMLNode   &oNode,
    VRMLAction *pAction)
{
    fprintf(stderr,
            "Visit Sphere : %s\n", 
            oNode.getName().str());

    VRMLToOSGAction *pConvAction = 
        dynamic_cast<VRMLToOSGAction *>(pAction);

    VRMLSphere      *pSphere     = 
        dynamic_cast<VRMLSphere      *>(&oNode );

    if(pConvAction != NULL && pSphere != NULL)
    {
        VRMLSphereBinder *pBinder = new VRMLSphereBinder();

        pBinder->setNode(pSphere    );
        pBinder->init   (pConvAction);

        pBinder->finish (pConvAction);
        oNode.setBinder (pBinder);
    }

    return VRMLAction::Continue;
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
    static Char8 cvsid_hpp[] = OSGVRMLSPHERE_HEADER_CVSID;
}
