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

#include "OSGVRMLCoordinate.h"
#include "OSGDataElementDesc.h"
#include "OSGVRMLToOSGAction.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGVRMLCOORDINATE_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_BEGIN_NAMESPACE

VRMLAction::ActionResult osgVRMLCoordinateToOpenSG(VRMLNode   &oNode,
                                                   VRMLAction *pAction);

OSG_END_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlCoordinateDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        MFVec3f::getClassType(),
        "point",
        OSG_RC_ELEM_IDM_DESC(VRMLCoordinate::PointField),
        false,
        (DataElemGetMethod) &VRMLCoordinate::getMFPoint,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}

VRMLObjectType VRMLCoordinate::_type(
    "Coordinate",
    "VRMLUnlimitedNode",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLCoordinate::createEmpty,
    VRMLCoordinate::init,
    vrmlCoordinateDescInserter,
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

void VRMLCoordinate::init(void)
{
    VRMLToOSGAction::registerDefaultTrav(
        VRMLCoordinate::getClassType(),
        osgTypedFunctionFunctor2Ref<VRMLAction::ActionResult,
                                    VRMLNode,
                                    VRMLAction *>(osgVRMLCoordinateToOpenSG));
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

VRMLCoordinate::VRMLCoordinate(void) :
     Inherited(),
    _mfPoint  ()
{
}

VRMLCoordinate::VRMLCoordinate(const VRMLCoordinate &source) :
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

OSG_VRMLOBJ_DEF(VRMLCoordinate, Ptr);

#ifdef WIN32
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLCoordinate::~VRMLCoordinate(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLCoordinate::setElement(Field  *pField, 
                                UInt32  uiElementId)
{
    if(uiElementId == PointFieldId)
    {
        MFVec3f              *pPoints = 
            dynamic_cast<MFVec3f              *>(pField);

        VRMLCoordinateBinder *pBinder = 
            dynamic_cast<VRMLCoordinateBinder *>(_pBinder);

        if(pPoints && pBinder != NULL)
        {
            pBinder->setPoints(*pPoints);
        }
    }
}

MFVec3f *VRMLCoordinate::getMFPoint(void)
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

VRMLCoordinateBinder::VRMLCoordinateBinder(void) :
	 Inherited(      ),
    _pCoords  (NullFC)
{
}

VRMLCoordinateBinder::~VRMLCoordinateBinder(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLCoordinateBinder::init(VRMLToOSGAction *pAction)
{
    if(pAction == NULL)
        return;

    if(_pNode == NULL)
        return;

    VRMLCoordinate *pNode = dynamic_cast<VRMLCoordinate *>(_pNode);

    if(pNode == NULL)
        return;

    UInt32 numPnts = pNode->getMFPoint()->size();

    if(numPnts == 0)
        return;

    _pCoords = GeoPositions3f::create();

    beginEditCP(_pCoords, GeoPositions3f::GeoPropDataFieldMask);
    {
        if(pAction->getDataTransferMode() == VRMLToOSGAction::CopyData)
        {
            _pCoords->getFieldPtr()->resize(numPnts);
            
            memcpy(&(_pCoords->getFieldPtr()->front()), 
                   &( pNode  ->getMFPoint ()->front()),
                   sizeof(Vec3f) * numPnts);
        }
        else
        {
            MFPnt3f *pPoints = 
                reinterpret_cast<MFPnt3f *>(pNode->getMFPoint());

            _pCoords->getFieldPtr()->getValues().swap(pPoints->getValues());
        }
    }
    endEditCP  (_pCoords, GeoPositions3f::GeoPropDataFieldMask);

    _pFieldContainer = _pCoords;
}

void VRMLCoordinateBinder::finish(VRMLToOSGAction *)
{
}

void VRMLCoordinateBinder::setPoints(MFVec3f &vPoints)
{
    UInt32 numPnts = vPoints.size();

   if(numPnts == 0)
        return;

    if(_pCoords == NullFC)
        return;
    
    beginEditCP(_pCoords, GeoPositions3f::GeoPropDataFieldMask);
    {
        _pCoords->getFieldPtr()->resize(numPnts);

        memcpy(&(_pCoords->getFieldPtr()->front()), 
               &( vPoints.                front()),
               sizeof(Vec3f) * numPnts);
    }
    endEditCP  (_pCoords, GeoPositions3f::GeoPropDataFieldMask);
}


VRMLAction::ActionResult OSG::osgVRMLCoordinateToOpenSG(
    VRMLNode   &oNode,
    VRMLAction *pAction)
{
    fprintf(stderr, "Visit Coordinate : %s\n", oNode.getName().str());

    VRMLToOSGAction *pConvAction = 
        dynamic_cast<VRMLToOSGAction *>(pAction);

    VRMLCoordinate  *pCoord      =
        dynamic_cast<VRMLCoordinate  *>(&oNode  );

    if(pConvAction != NULL && pCoord != NULL)
    {
        VRMLCoordinateBinder *pBinder = new VRMLCoordinateBinder();

        pBinder->setNode(pCoord);
        pBinder->init   (pConvAction);

        pBinder->finish(pConvAction);
        oNode.setBinder(pBinder);
    }

    return VRMLAction::Continue;
}
