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

#include "OSGVRMLBox.h"
#include "OSGDataElementDesc.h"

#include <OSGGeometry.h>
#include <OSGSimpleGeometry.h>
#include <OSGVRMLToOSGAction.h>

OSG_USING_NAMESPACE

OSG_BEGIN_NAMESPACE

VRMLAction::ActionResult osgVRMLBoxToOpenSG(VRMLNode   &oNode,
                                            VRMLAction *pAction);

OSG_END_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlBoxDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        SFVec3f::getClassType(),
        "size",
        OSG_RC_ELEM_IDM_DESC(VRMLBox::SizeField),
        false,
        (DataElemGetMethod) &VRMLBox::getSFSize,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}


VRMLObjectType VRMLBox::_type(
    "Box",
    "VRMLGeometry",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLBox::createEmpty,
    &VRMLBox::init,
    vrmlBoxDescInserter,
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

void VRMLBox::init(void)
{
    VRMLToOSGAction::registerDefaultTrav(
        VRMLBox::getClassType(),
        osgTypedFunctionFunctor2Ref<VRMLAction::ActionResult,
                                    VRMLNode,
                                    VRMLAction *>(osgVRMLBoxToOpenSG));
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

VRMLBox::VRMLBox(void) :
 	 Inherited(),
    _sfSize   ()
{
    _sfSize.getValue().setValues(2.f, 2.f, 2.f);
}


VRMLBox::VRMLBox(const VRMLBox &source) :
	 Inherited(source        ),
    _sfSize   (source._sfSize)
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLBox, Ptr);

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLBox::~VRMLBox(void)
{
}

/*------------------------------ access -----------------------------------*/

SFVec3f *VRMLBox::getSFSize(void)
{
    return &_sfSize;
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

VRMLBoxBinder::VRMLBoxBinder(void) :
	Inherited()
{
}

VRMLBoxBinder::~VRMLBoxBinder(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLBoxBinder::init(VRMLToOSGAction *)
{
    if(_pNode == NULL)
        return;

    VRMLBox *pNode = dynamic_cast<VRMLBox *>(_pNode);

    if(pNode == NULL)
        return;

    _pFieldContainer = makeBoxGeo(pNode->getSFSize()->getValue()[0],
                                  pNode->getSFSize()->getValue()[1],
                                  pNode->getSFSize()->getValue()[2],
                                  2,
                                  2,
                                  2);
}

void VRMLBoxBinder::finish(VRMLToOSGAction *)
{
}


VRMLAction::ActionResult OSG::osgVRMLBoxToOpenSG(VRMLNode   &oNode,
                                                 VRMLAction *pAction)
{
    fprintf(stderr,
            "Visit Box : %s\n", 
            oNode.getName().str());

    VRMLToOSGAction *pConvAction = 
        dynamic_cast<VRMLToOSGAction *>(pAction);

    VRMLBox         *pBox        = 
        dynamic_cast<VRMLBox         *>(&oNode );

    if(pConvAction != NULL && pBox != NULL)
    {
        VRMLBoxBinder *pBinder = new VRMLBoxBinder();

        pBinder->setNode(pBox);
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
    static Char8 cvsid_hpp[] = OSGVRMLBOX_HEADER_CVSID;
}
