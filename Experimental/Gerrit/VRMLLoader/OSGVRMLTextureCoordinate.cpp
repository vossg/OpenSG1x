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

#include "OSGVRMLTextureCoordinate.h"
#include "OSGDataElementDesc.h"

#include <OSGGeoPropTexCoords.h>
#include <OSGGeoPropPtrs.h>

#include <OSGVRMLToOSGAction.h>

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGVRMLTEXTURECOORDINATE_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_BEGIN_NAMESPACE

VRMLAction::ActionResult osgVRMLTextureCoordinateToOpenSG(VRMLNode   &oNode,
                                                          VRMLAction *pAction);

OSG_END_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlTextureCoordinateDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        MFVec2f::getClassType(),
        "point",
        OSG_RC_ELEM_IDM_DESC(VRMLTextureCoordinate::PointField),
        false,
        (DataElemGetMethod) &VRMLTextureCoordinate::getMFPoint,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}


VRMLObjectType VRMLTextureCoordinate::_type(
    "TextureCoordinate",
    "VRMLUnlimitedNode",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLTextureCoordinate::createEmpty,
    VRMLTextureCoordinate::init,
    vrmlTextureCoordinateDescInserter,
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

void VRMLTextureCoordinate::init(void)
{
    VRMLToOSGAction::registerDefaultTrav(
        VRMLTextureCoordinate::getClassType(),
        osgTypedFunctionFunctor2Ref<VRMLAction::ActionResult,
                                    VRMLNode,
                                    VRMLAction *>(
                                        osgVRMLTextureCoordinateToOpenSG));
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

VRMLTextureCoordinate::VRMLTextureCoordinate(void) :
     Inherited(),
    _mfPoint  ()
{
}

VRMLTextureCoordinate::VRMLTextureCoordinate(
    const VRMLTextureCoordinate &source) :

 	 Inherited(source),
    _mfPoint  (source._mfPoint)
{
}


/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#ifdef WIN32
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLTextureCoordinate, Ptr);

#ifdef WIN32
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLTextureCoordinate::~VRMLTextureCoordinate(void)
{
}

/*------------------------------ access -----------------------------------*/

MFVec2f *VRMLTextureCoordinate::getMFPoint(void)
{
    return &_mfPoint;
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

VRMLTextureCoordinateBinder::VRMLTextureCoordinateBinder(void) :
	Inherited()
{
}

VRMLTextureCoordinateBinder::~VRMLTextureCoordinateBinder(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLTextureCoordinateBinder::init(VRMLToOSGAction *)
{
    if(_pNode == NULL)
        return;

    VRMLTextureCoordinate *pNode = 
        dynamic_cast<VRMLTextureCoordinate *>(_pNode);

    if(pNode == NULL)
        return;

    UInt32 numPnts = pNode->getMFPoint()->size();

    if(numPnts == 0)
        return;

    GeoTexCoords2fPtr pTexCoords = GeoTexCoords2f::create();

    beginEditCP(pTexCoords, GeoTexCoords2f::GeoPropDataFieldMask);
    {
        pTexCoords->getFieldPtr()->resize(numPnts);

        memcpy(&(pTexCoords->getFieldPtr()->front()), 
               &(pNode     ->getMFPoint ()->front()),
               sizeof(Vec2f) * numPnts);
    }
    endEditCP  (pTexCoords, GeoTexCoords3f::GeoPropDataFieldMask);

    _pFieldContainer = pTexCoords;
}

void VRMLTextureCoordinateBinder::finish(VRMLToOSGAction *)
{
}


VRMLAction::ActionResult OSG::osgVRMLTextureCoordinateToOpenSG(
    VRMLNode   &oNode,
    VRMLAction *pAction)
{
  fprintf(stderr, "Visit TexCoordinate : %s\n", oNode.getName().str());

    VRMLToOSGAction       *pConvAction = 
        dynamic_cast<VRMLToOSGAction       *>(pAction);

    VRMLTextureCoordinate *pTexCoord   =
        dynamic_cast<VRMLTextureCoordinate *>(&oNode  );

    if(pConvAction != NULL && pTexCoord != NULL)
    {
        VRMLTextureCoordinateBinder *pBinder = 
            new VRMLTextureCoordinateBinder();

        pBinder->setNode(pTexCoord);
        pBinder->init   (pConvAction);

        pBinder->finish(pConvAction);
        oNode.setBinder(pBinder);
    }

    return VRMLAction::Continue;
}
