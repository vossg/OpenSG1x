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

#include "OSGVRMLNormal.h"
#include "OSGDataElementDesc.h"

#include <OSGGeoPropNormals.h>
#include <OSGGeoPropPtrs.h>

#include <OSGVRMLToOSGAction.h>

OSG_USING_NAMESPACE

OSG_BEGIN_NAMESPACE

VRMLAction::ActionResult osgVRMLNormalToOpenSG(VRMLNode   &oNode,
                                               VRMLAction *pAction);

OSG_END_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlNormalDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        MFVec3f::getClassType(),
        "vector",
        OSG_RC_ELEM_IDM_DESC(VRMLNormal::VectorField),
        false,
        (DataElemGetMethod) &VRMLNormal::getMFVector,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}


VRMLObjectType VRMLNormal::_type(
    "Normal",
    "VRMLUnlimitedNode",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLNormal::createEmpty,
    VRMLNormal::init,
    vrmlNormalDescInserter,
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

void VRMLNormal::init(void)
{
    VRMLToOSGAction::registerDefaultTrav(
        VRMLNormal::getClassType(),
        osgTypedFunctionFunctor2Ref<VRMLAction::ActionResult,
                                    VRMLNode,
                                    VRMLAction *>(osgVRMLNormalToOpenSG));
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

VRMLNormal::VRMLNormal(void) :
     Inherited(),
    _mfVector ()
{
}

VRMLNormal::VRMLNormal(const VRMLNormal &source) :
 	 Inherited(source),
    _mfVector (source._mfVector)
{
}


/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLNormal, Ptr);

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLNormal::~VRMLNormal(void)
{
}

/*------------------------------ access -----------------------------------*/

MFVec3f *VRMLNormal::getMFVector(void)
{
    return &_mfVector;
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

VRMLNormalBinder::VRMLNormalBinder(void) :
	Inherited()
{
}

VRMLNormalBinder::~VRMLNormalBinder(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLNormalBinder::init(VRMLToOSGAction *)
{
    if(_pNode == NULL)
        return;

    VRMLNormal *pNode = dynamic_cast<VRMLNormal *>(_pNode);

    if(pNode == NULL)
        return;

    UInt32 numPnts = pNode->getMFVector()->size();

    if(numPnts == 0)
        return;

    GeoNormals3fPtr pNormals = GeoNormals3f::create();

    beginEditCP(pNormals, GeoNormals3f::GeoPropDataFieldMask);
    {
        pNormals->getFieldPtr()->resize(numPnts);

        memcpy(&(pNormals->getFieldPtr()->front()), 
               &(pNode   ->getMFVector()->front()),
               sizeof(Vec3f) * numPnts);
    }
    endEditCP  (pNormals, GeoNormals3f::GeoPropDataFieldMask);

    _pFieldContainer = pNormals;
}

void VRMLNormalBinder::finish(VRMLToOSGAction *)
{
}


VRMLAction::ActionResult OSG::osgVRMLNormalToOpenSG(
    VRMLNode   &oNode,
    VRMLAction *pAction)
{
    fprintf(stderr, "Visit Normal : %s\n", oNode.getName().str());

    VRMLToOSGAction *pConvAction = 
        dynamic_cast<VRMLToOSGAction *>(pAction);

    VRMLNormal      *pNormal     =
        dynamic_cast<VRMLNormal      *>(&oNode  );

    if(pConvAction != NULL && pNormal != NULL)
    {
        VRMLNormalBinder *pBinder = new VRMLNormalBinder();

        pBinder->setNode(pNormal);
        pBinder->init   (pConvAction);

        pBinder->finish(pConvAction);
        oNode.setBinder(pBinder);
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
    static Char8 cvsid_hpp[] = OSGVRMLNORMAL_HEADER_CVSID;
}
