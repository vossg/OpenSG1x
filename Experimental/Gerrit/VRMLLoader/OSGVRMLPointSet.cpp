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

#include "OSGVRMLPointSet.h"
#include "OSGDataElementDesc.h"
#include "OSGVRMLCoordinate.h"
#include "OSGVRMLColor.h"
#include "OSGVRMLToOSGAction.h"

#include <OSGGeometry.h>
#include <OSGGeoFunctions.h>
#include <OSGGeoPropPositions.h>


OSG_USING_NAMESPACE

OSG_BEGIN_NAMESPACE

VRMLAction::ActionResult osgVRMLPointSetToOpenSG(VRMLNode   &oNode,
                                                 VRMLAction *pAction);

OSG_END_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlPointSetDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        SFVRMLNode::getClassType(),
        "color",
        OSG_RC_ELEM_IDM_DESC(VRMLPointSet::ColorField),
        false,
        (DataElemGetMethod) &VRMLPointSet::getSFColor,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFVRMLNode::getClassType(),
        "coord",
        OSG_RC_ELEM_IDM_DESC(VRMLPointSet::CoordField),
        false,
        (DataElemGetMethod) &VRMLPointSet::getSFCoord,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}


VRMLObjectType VRMLPointSet::_type(
    "PointSet",
    "VRMLUnlimitedNode",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLPointSet::createEmpty,
    &VRMLPointSet::init,
    vrmlPointSetDescInserter,
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

void VRMLPointSet::init(void)
{
    VRMLToOSGAction::registerDefaultTrav(
        VRMLPointSet::getClassType(),
        osgTypedFunctionFunctor2Ref<VRMLAction::ActionResult,
                                    VRMLNode,
                                    VRMLAction *>(osgVRMLPointSetToOpenSG));
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

VRMLPointSet::VRMLPointSet(void) :
     Inherited(    ),
    _sfColor  (NULL),
    _sfCoord  (NULL)
{   
}

VRMLPointSet::VRMLPointSet(const VRMLPointSet &source) :
     Inherited(source         ),
    _sfColor  (source._sfColor),
    _sfCoord  (source._sfCoord)
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLPointSet, Ptr);

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLPointSet::~VRMLPointSet(void)
{
}

SFVRMLNode *VRMLPointSet::getSFColor(void)
{
    return &_sfColor;
}

SFVRMLNode *VRMLPointSet::getSFCoord(void)
{
    return &_sfCoord;
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

VRMLPointSetBinder::VRMLPointSetBinder(void) :
	Inherited()
{
}

VRMLPointSetBinder::~VRMLPointSetBinder(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLPointSetBinder::init(VRMLToOSGAction *)
{
    _pFieldContainer = Geometry::create();
}

void VRMLPointSetBinder::setCoords(VRMLNodeBinder *pCoordBinder)
{
    if(pCoordBinder == NULL)
        return;

    GeometryPtr pGeo = GeometryPtr::dcast(_pFieldContainer);
    
    if(pGeo == NullFC)
        return;

    GeoPositionsPtr pCoords = 
        GeoPositionsPtr::dcast(pCoordBinder->getFCPtr());

    if(pCoords != NullFC)
    {
        beginEditCP(pGeo, Geometry::PositionsFieldMask);
        {
            pGeo->setPositions(pCoords);
        }
        endEditCP  (pGeo, Geometry::PositionsFieldMask);
    }
    else
    {
        fprintf(stderr, "IFS: no valid coords given\n");
    }
}

void VRMLPointSetBinder::setColors(VRMLNodeBinder *pColorBinder)
{
    if(pColorBinder == NULL)
        return;

    GeometryPtr pGeo = GeometryPtr::dcast(_pFieldContainer);
    
    if(pGeo == NullFC)
        return;

    GeoColorsPtr pColors = 
        GeoColorsPtr::dcast(pColorBinder->getFCPtr());

    if(pColors != NullFC)
    {
        beginEditCP(pGeo, Geometry::ColorsFieldMask);
        {
            pGeo->setColors(pColors);
        }
        endEditCP  (pGeo, Geometry::ColorsFieldMask);
    }
    else
    {
        fprintf(stderr, "IFS: no valid colors given\n");
    }
}

void VRMLPointSetBinder::finish(VRMLToOSGAction *pAction)
{
    GeometryPtr pGeo = GeometryPtr::dcast(_pFieldContainer);
    
    if(pGeo == NullFC)
        return;

    GeoPLengthsUI32Ptr pLengths = GeoPLengthsUI32::create();  
    GeoPTypesUI8Ptr    pTypes   = GeoPTypesUI8::create();     

    GeoPositionsPtr    pPos     = pGeo->getPositions();
    GeoPositions3fPtr  pCoords  = GeoPositions3fPtr::dcast(pPos);

    if(pCoords == NullFC)
        return;

    GeoPLengthsUI32::StoredFieldType *pLenField  = 
        pLengths->getFieldPtr();

    GeoPTypesUI8   ::StoredFieldType *pTypeField = 
        pTypes ->getFieldPtr();

    beginEditCP(pLengths);
    {
        pLenField->addValue(pCoords->getFieldPtr()->size());
    }
    endEditCP  (pLengths);

    beginEditCP(pTypes);
    {
        pTypes->addValue(GL_POINTS);
    }
    endEditCP  (pTypes);

    beginEditCP(pGeo, 
                Geometry::TypesFieldMask | 
                Geometry::LengthsFieldMask);
    {
        pGeo->setLengths(pLengths);
        pGeo->setTypes  (pTypes  );
    }
    endEditCP  (pGeo, 
                Geometry::TypesFieldMask | 
                Geometry::LengthsFieldMask);
}


VRMLAction::ActionResult OSG::osgVRMLPointSetToOpenSG(
    VRMLNode   &oNode,
    VRMLAction *pAction)
{
    VRMLAction::ActionResult returnValue = VRMLAction::Continue;

#ifdef OSG_DEBUG_VRMLTOOSG
    fprintf(stderr,
            "Visit PointSet : %s\n", 
            oNode.getName().str());
#endif

    VRMLToOSGAction *pConvAction      = 
        dynamic_cast<VRMLToOSGAction    *>(pAction);

    VRMLPointSet *pPointSet = 
        dynamic_cast<VRMLPointSet *>(&oNode);

    if(pConvAction != NULL && pPointSet != NULL)
    {
        VRMLPointSetBinder          *pBinder     = NULL; 

        VRMLBindings::NodeBinderPtr  pNodeBinder = NULL;

        pBinder = new VRMLPointSetBinder();
        
        pBinder->setNode(pPointSet);
        pBinder->init   (pConvAction   );
        
        returnValue = 
                pConvAction->apply(pPointSet->getSFCoord()->getValue());

        if(pPointSet->getSFCoord()->getValue() != NULL)
        {
            pNodeBinder = pPointSet->getSFCoord()->getValue()->getBinder();

            if(pNodeBinder != NULL)
            {
                pBinder->setCoords(pNodeBinder);
            }
        }

        if(returnValue == VRMLAction::Continue)
        {
            returnValue = 
                pConvAction->apply(pPointSet->getSFColor()->getValue());
        }

        if(pPointSet->getSFColor()->getValue() != NULL)
        {
            pNodeBinder = pPointSet->getSFColor()->getValue()->getBinder();

            if(pNodeBinder != NULL)
            {
                pBinder->setColors(pNodeBinder);
            }
        }

        pBinder->finish(pConvAction);
        oNode.setBinder(pBinder);
    }

    return returnValue;
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
    static Char8 cvsid_hpp[] = OSGVRMLPOINTSET_HEADER_CVSID;
}
