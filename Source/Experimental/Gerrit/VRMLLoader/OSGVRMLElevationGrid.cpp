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

#include "OSGVRMLElevationGrid.h"
#include "OSGDataElementDesc.h"
#include "OSGVRMLNormal.h"
#include "OSGVRMLColor.h"
#include "OSGVRMLTextureCoordinate.h"
#include "OSGVRMLElevationGrid.h"
#include "OSGVRMLToOSGAction.h"

#include <OSGGeoFunctions.h>
#include <OSGGeoPropPtrs.h>

OSG_USING_NAMESPACE

OSG_BEGIN_NAMESPACE

VRMLAction::ActionResult osgVRMLElevationGridToOpenSG(VRMLNode   &oNode,
                                                      VRMLAction *pAction);

OSG_END_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlElevationGridDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        SFVRMLNode::getClassType(),
        "color",
        OSG_RC_ELEM_IDM_DESC(VRMLElevationGrid::ColorField),
        false,
        (DataElemGetMethod) &VRMLElevationGrid::getSFColor,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFVRMLNode::getClassType(),
        "normal",
        OSG_RC_ELEM_IDM_DESC(VRMLElevationGrid::NormalField),
        false,
        (DataElemGetMethod) &VRMLElevationGrid::getSFNormal,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFVRMLNode::getClassType(),
        "texCoord",
        OSG_RC_ELEM_IDM_DESC(VRMLElevationGrid::TexCoordField),
        false,
        (DataElemGetMethod) &VRMLElevationGrid::getSFTexCoord,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFReal32::getClassType(),
        "height",
        OSG_RC_ELEM_IDM_DESC(VRMLElevationGrid::HeightField),
        false,
        (DataElemGetMethod) &VRMLElevationGrid::getMFHeight,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFBool::getClassType(),
        "ccw",
        OSG_RC_ELEM_IDM_DESC(VRMLElevationGrid::CcwField),
        false,
        (DataElemGetMethod) &VRMLElevationGrid::getSFCcw,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFBool::getClassType(),
        "ColorPerVertex",
        OSG_RC_ELEM_IDM_DESC(VRMLElevationGrid::ColorPerVertexField),
        false,
        (DataElemGetMethod) &VRMLElevationGrid::getSFColorPerVertex,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "creaseAngle",
        OSG_RC_ELEM_IDM_DESC(VRMLElevationGrid::CreaseAngleField),
        false,
        (DataElemGetMethod) &VRMLElevationGrid::getSFCreaseAngle,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFBool::getClassType(),
        "normalPerVertex",
        OSG_RC_ELEM_IDM_DESC(VRMLElevationGrid::NormalPerVertexField),
        false,
        (DataElemGetMethod) &VRMLElevationGrid::getSFNormalPerVertex,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFBool::getClassType(),
        "solid",
        OSG_RC_ELEM_IDM_DESC(VRMLElevationGrid::SolidField),
        false,
        (DataElemGetMethod) &VRMLElevationGrid::getSFSolid,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFInt32::getClassType(),
        "xDimension",
        OSG_RC_ELEM_IDM_DESC(VRMLElevationGrid::XDimensionField),
        false,
        (DataElemGetMethod) &VRMLElevationGrid::getSFXDimension,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "xSpacing",
        OSG_RC_ELEM_IDM_DESC(VRMLElevationGrid::XSpacingField),
        false,
        (DataElemGetMethod) &VRMLElevationGrid::getSFXSpacing,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFInt32::getClassType(),
        "zDimension",
        OSG_RC_ELEM_IDM_DESC(VRMLElevationGrid::ZDimensionField),
        false,
        (DataElemGetMethod) &VRMLElevationGrid::getSFZDimension,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "zSpacing",
        OSG_RC_ELEM_IDM_DESC(VRMLElevationGrid::ZSpacingField),
        false,
        (DataElemGetMethod) &VRMLElevationGrid::getSFZSpacing,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}


VRMLObjectType VRMLElevationGrid::_type(
    "ElevationGrid",
    "VRMLGeometry",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLElevationGrid::createEmpty,
    &VRMLElevationGrid::init,
    vrmlElevationGridDescInserter,
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

void VRMLElevationGrid::init(void)
{
    VRMLToOSGAction::registerDefaultTrav(
        VRMLElevationGrid::getClassType(),
        osgTypedFunctionFunctor2Ref<VRMLAction::ActionResult,
                                    VRMLNode,
                                    VRMLAction *>(
                                        osgVRMLElevationGridToOpenSG));
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

VRMLElevationGrid::VRMLElevationGrid(void) :
  	 Inherited        (    ),
    _sfColor          (NULL),
    _sfNormal         (NULL),
    _sfTexCoord       (NULL),
    
    _mfHeight         (    ),
    _sfCcw            (true),
    _sfColorPerVertex (true),
    _sfCreaseAngle    (0.0f),
    _sfNormalPerVertex(true),
    _sfSolid          (true),
    _sfXDimension     (   0),
    _sfXSpacing       (1.0f),
    _sfZDimension     (   0),
    _sfZSpacing       (1.0f)
{
}


VRMLElevationGrid::VRMLElevationGrid(const VRMLElevationGrid &source):
     Inherited(source),
    _sfColor          (source._sfColor          ),
    _sfNormal         (source._sfNormal         ),
    _sfTexCoord       (source._sfTexCoord       ),
    
    _mfHeight         (source._mfHeight         ),
    _sfCcw            (source._sfCcw            ),
    _sfColorPerVertex (source._sfColorPerVertex ),
    _sfCreaseAngle    (source._sfCreaseAngle    ),
    _sfNormalPerVertex(source._sfNormalPerVertex),
    _sfSolid          (source._sfSolid          ),
    _sfXDimension     (source._sfXDimension     ),
    _sfXSpacing       (source._sfXSpacing       ),
    _sfZDimension     (source._sfZDimension     ),
    _sfZSpacing       (source._sfZSpacing       )
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLElevationGrid, Ptr);

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLElevationGrid::~VRMLElevationGrid(void)
{
}

/*------------------------------ access -----------------------------------*/

SFVRMLNode *VRMLElevationGrid::getSFColor(void)
{
    return &_sfColor;
}

SFVRMLNode *VRMLElevationGrid::getSFNormal(void)
{
    return &_sfNormal;
}

SFVRMLNode *VRMLElevationGrid::getSFTexCoord(void)
{
    return &_sfTexCoord;
}

MFReal32 *VRMLElevationGrid::getMFHeight(void)
{
    return &_mfHeight;
}

SFBool *VRMLElevationGrid::getSFCcw(void)
{
    return &_sfCcw;
}

SFBool *VRMLElevationGrid::getSFColorPerVertex(void)
{
    return &_sfColorPerVertex;
}

SFReal32 *VRMLElevationGrid::getSFCreaseAngle(void)
{
    return &_sfCreaseAngle;
}

SFBool *VRMLElevationGrid::getSFNormalPerVertex(void)
{
    return &_sfNormalPerVertex;
}

SFBool *VRMLElevationGrid::getSFSolid(void)
{
    return &_sfSolid;
}

SFInt32 *VRMLElevationGrid::getSFXDimension(void)
{
    return &_sfXDimension;
}

SFReal32 *VRMLElevationGrid::getSFXSpacing(void)
{
    return &_sfXSpacing;
}

SFInt32 *VRMLElevationGrid::getSFZDimension(void)
{
    return &_sfZDimension;
}

SFReal32 *VRMLElevationGrid::getSFZSpacing(void)
{
    return &_sfZSpacing;
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

VRMLElevationGridBinder::VRMLElevationGridBinder(void) :
	Inherited()
{
}

VRMLElevationGridBinder::~VRMLElevationGridBinder(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLElevationGridBinder::init(VRMLToOSGAction *)
{
    _pFieldContainer = Geometry::create();
}

void VRMLElevationGridBinder::setNormals(VRMLNodeBinder *pNormalBinder)
{
    if(pNormalBinder == NULL)
        return;

    GeometryPtr pGeo = GeometryPtr::dcast(_pFieldContainer);
    
    if(pGeo == NullFC)
        return;

    GeoNormalsPtr pNormals = 
        GeoNormalsPtr::dcast(pNormalBinder->getFCPtr());

    if(pNormals != NullFC)
    {
        beginEditCP(pGeo, Geometry::NormalsFieldMask);
        {
            pGeo->setNormals(pNormals);
        }
        endEditCP  (pGeo, Geometry::NormalsFieldMask);
    }
    else
    {
        fprintf(stderr, "IFS: no valid normals given\n");
    }
}

void VRMLElevationGridBinder::setColors(VRMLNodeBinder *pColorBinder)
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

void VRMLElevationGridBinder::setTexCoords(
    VRMLNodeBinder *pTexCoordBinder)
{
    if(pTexCoordBinder == NULL)
        return;

    GeometryPtr pGeo = GeometryPtr::dcast(_pFieldContainer);
    
    if(pGeo == NullFC)
        return;

    GeoTexCoordsPtr pTexCoords = 
        GeoTexCoordsPtr::dcast(pTexCoordBinder->getFCPtr());

    if(pTexCoords != NullFC)
    {
        beginEditCP(pGeo, Geometry::TexCoordsFieldMask);
        {
            pGeo->setTexCoords(pTexCoords);
        }
        endEditCP  (pGeo, Geometry::TexCoordsFieldMask);
    }
    else
    {
        fprintf(stderr, "IFS: no valid tex coords given\n");
    }
}

void VRMLElevationGridBinder::finish(VRMLToOSGAction *pAction)
{
    if(_pNode == NULL)
        return;

    VRMLElevationGrid *pNode = 
        dynamic_cast<VRMLElevationGrid *>(_pNode);

    if(pNode == NULL)
        return;

    GeometryPtr pGeo = GeometryPtr::dcast(_pFieldContainer);
    
    if(pGeo == NullFC)
        return;

    UInt32 i         = 0;
    UInt32 j         = 0;

    Int32  iXDim      = pNode->getSFXDimension()->getValue();
    Int32  iZDim      = pNode->getSFZDimension()->getValue();
    Real32 rXSpacing  = pNode->getSFXSpacing  ()->getValue();
    Real32 rZSpacing  = pNode->getSFZSpacing  ()->getValue();

    MFReal32 *pHeight = pNode->getMFHeight();

    MFInt32 vCoordIndex;
    MFInt32 vDummyIndex;

    GeoPositions3fPtr pCoords = GeoPositions3f::create();

    beginEditCP(pCoords);
    {
        pCoords->getFieldPtr()->resize(iXDim * iZDim);

        for(i = 0; i < iXDim; ++i)
        {
            for(j = 0; j < iZDim; ++j)
            {
                (*(pCoords->getFieldPtr()))[i + j * iXDim][0] = 
                    rXSpacing * Real32(i);
                
                (*(pCoords->getFieldPtr()))[i + j * iXDim][1] = 
                    (*pHeight)[i + j * iXDim];
                
                (*(pCoords->getFieldPtr()))[i + j * iXDim][2] = 
                    rZSpacing * Real32(j);
            }
        }
    }
    endEditCP  (pCoords);

    vCoordIndex.reserve(iXDim * iZDim);
        
    for(i = 0; i < iXDim - 1; ++i)
    {
        for(j = 0; j < iZDim - 1; ++j)
        {
            vCoordIndex.push_back( i      + (j    ) * (iXDim));
            vCoordIndex.push_back((i + 1) + (j + 1) * (iXDim)); 
            vCoordIndex.push_back( i + 1  + (j    ) * (iXDim));
            vCoordIndex.push_back(-1);

            vCoordIndex.push_back( i      + (j    ) * (iXDim));
            vCoordIndex.push_back((i    ) + (j + 1) * (iXDim)); 
            vCoordIndex.push_back((i + 1) + (j + 1) * (iXDim)); 
            vCoordIndex.push_back(-1);
        }
    }

    beginEditCP(pGeo, Geometry::PositionsFieldMask);
    {
        pGeo->setPositions(pCoords);
    }
    endEditCP  (pGeo, Geometry::PositionsFieldMask);

    setIndexFromVRMLData(pGeo,
                         vCoordIndex.getValues(),
                         vDummyIndex.getValues(),
                         vDummyIndex.getValues(),
                         vDummyIndex.getValues(),
                         false,
                         pNode->getSFCcw            ()->getValue(),
                         pNode->getSFNormalPerVertex()->getValue(),
                         pNode->getSFColorPerVertex ()->getValue(),
                         false,
                         true);


    if((0 != (pAction->getOptions() & VRMLToOSGAction::CreateNormals)) &&
       (pGeo->getNormals() == NullFC))
    {
        calcVertexNormals(pGeo, pNode->getSFCreaseAngle()->getValue());
    }
    
    if(0 != (pAction->getOptions() & VRMLToOSGAction::StripeGeometry)) 
    {
//        createOptimizedPrimitives(pGeo, 1, true, true, 8, false);
    }
}


VRMLAction::ActionResult OSG::osgVRMLElevationGridToOpenSG(
    VRMLNode   &oNode,
    VRMLAction *pAction)
{
    VRMLAction::ActionResult returnValue = VRMLAction::Continue;

#ifdef OSG_DEBUG_VRMLTOOSG
    fprintf(stderr,
            "Visit ElevationGrid : %s\n", 
            oNode.getName().str());
#endif

    VRMLToOSGAction *pConvAction      = 
        dynamic_cast<VRMLToOSGAction    *>(pAction);

    VRMLElevationGrid *pElevationGrid = 
        dynamic_cast<VRMLElevationGrid *>(&oNode);

    if(pConvAction != NULL && pElevationGrid != NULL)
    {
        VRMLElevationGridBinder        *pBinder     = NULL; 

        VRMLBindings::NodeBinderPtr  pNodeBinder = NULL;

        pBinder = new VRMLElevationGridBinder();
        
        pBinder->setNode(pElevationGrid);
        pBinder->init   (pConvAction   );
        
        returnValue = 
                pConvAction->apply(pElevationGrid->getSFNormal()->getValue());

        if(pElevationGrid->getSFNormal()->getValue() != NULL)
        {
            pNodeBinder = 
                pElevationGrid->getSFNormal()->getValue()->getBinder();

            if(pNodeBinder != NULL)
            {
                pBinder->setNormals(pNodeBinder);
            }
        }

        if(returnValue == VRMLAction::Continue)
        {
            returnValue = 
                pConvAction->apply(pElevationGrid->getSFColor()->getValue());
        }

        if(pElevationGrid->getSFColor()->getValue() != NULL)
        {
            pNodeBinder = 
                pElevationGrid->getSFColor()->getValue()->getBinder();

            if(pNodeBinder != NULL)
            {
                pBinder->setColors(pNodeBinder);
            }
        }

        if(returnValue == VRMLAction::Continue)
        {
            returnValue = 
                pConvAction->apply(
                    pElevationGrid->getSFTexCoord()->getValue());
        }

        if(pElevationGrid->getSFTexCoord()->getValue() != NULL)
        {
            pNodeBinder = 
                pElevationGrid->getSFTexCoord()->getValue()->getBinder();

            if(pNodeBinder != NULL)
            {
                pBinder->setTexCoords(pNodeBinder);
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
    static Char8 cvsid_hpp[] = OSGVRMLELEVATIONGRID_HEADER_CVSID;
}
