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

#include "OSGVRMLIndexedFaceSet.h"
#include "OSGDataElementDesc.h"
#include "OSGVRMLToOSGAction.h"
#include "OSGGeoFunctions.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGVRMLINDEXEDFACESET_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_BEGIN_NAMESPACE

VRMLAction::ActionResult osgVRMLIndexedFaceSetToOpenSG(VRMLNode   &oNode,
                                                       VRMLAction *pAction);

OSG_END_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlIndexedFaceSetDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;


    pDesc = new DataElementDesc(
        SFVRMLNode::getClassType(),
        "color",
        OSG_RC_ELEM_IDM_DESC(VRMLIndexedFaceSet::ColorField),
        false,
        (DataElemGetMethod) &VRMLIndexedFaceSet::getSFColor,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFVRMLNode::getClassType(),
        "coord",
        OSG_RC_ELEM_IDM_DESC(VRMLIndexedFaceSet::CoordField),
        false,
        (DataElemGetMethod) &VRMLIndexedFaceSet::getSFCoord,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFVRMLNode::getClassType(),
        "normal",
        OSG_RC_ELEM_IDM_DESC(VRMLIndexedFaceSet::NormalField),
        false,
        (DataElemGetMethod) &VRMLIndexedFaceSet::getSFNormal,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFVRMLNode::getClassType(),
        "texCoord",
        OSG_RC_ELEM_IDM_DESC(VRMLIndexedFaceSet::TexCoordField),
        false,
        (DataElemGetMethod) &VRMLIndexedFaceSet::getSFTexCoord,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFBool::getClassType(),
        "ccw",
        OSG_RC_ELEM_IDM_DESC(VRMLIndexedFaceSet::CcwField),
        false,
        (DataElemGetMethod) &VRMLIndexedFaceSet::getSFCcw,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFInt32::getClassType(),
        "colorIndex",
        OSG_RC_ELEM_IDM_DESC(VRMLIndexedFaceSet::ColorIndexField),
        false,
        (DataElemGetMethod) &VRMLIndexedFaceSet::getMFColorIndex,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFBool::getClassType(),
        "colorPerVertex",
        OSG_RC_ELEM_IDM_DESC(VRMLIndexedFaceSet::ColorPerVertexField),
        false,
        (DataElemGetMethod) &VRMLIndexedFaceSet::getSFColorPerVertex,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFBool::getClassType(),
        "convex",
        OSG_RC_ELEM_IDM_DESC(VRMLIndexedFaceSet::ConvexField),
        false,
        (DataElemGetMethod) &VRMLIndexedFaceSet::getSFConvex,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFInt32::getClassType(),
        "coordIndex",
        OSG_RC_ELEM_IDM_DESC(VRMLIndexedFaceSet::CoordIndexField),
        false,
        (DataElemGetMethod) &VRMLIndexedFaceSet::getMFCoordIndex,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFReal32::getClassType(),
        "creaseAngle",
        OSG_RC_ELEM_IDM_DESC(VRMLIndexedFaceSet::CreaseAngleField),
        false,
        (DataElemGetMethod) &VRMLIndexedFaceSet::getSFCreaseAngle,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFInt32::getClassType(),
        "normalIndex",
        OSG_RC_ELEM_IDM_DESC(VRMLIndexedFaceSet::NormalIndexField),
        false,
        (DataElemGetMethod) &VRMLIndexedFaceSet::getMFNormalIndex,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFBool::getClassType(),
        "normalPerVertex",
        OSG_RC_ELEM_IDM_DESC(VRMLIndexedFaceSet::NormalPerVertexField),
        false,
        (DataElemGetMethod) &VRMLIndexedFaceSet::getSFNormalPerVertex,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFBool::getClassType(),
        "solid",
        OSG_RC_ELEM_IDM_DESC(VRMLIndexedFaceSet::SolidField),
        false,
        (DataElemGetMethod) &VRMLIndexedFaceSet::getSFSolid,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFInt32::getClassType(),
        "texCoordIndex",
        OSG_RC_ELEM_IDM_DESC(VRMLIndexedFaceSet::TexCoordIndexField),
        false,
        (DataElemGetMethod) &VRMLIndexedFaceSet::getMFTexCoordIndex,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFString::getClassType(),
        "updateNormalMode",
        OSG_RC_ELEM_IDM_DESC(VRMLIndexedFaceSet::UpdateNormalModeField),
        false,
        (DataElemGetMethod) &VRMLIndexedFaceSet::getSFUpdateNormalMode,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}

VRMLObjectType VRMLIndexedFaceSet::_type(
    "IndexedFaceSet",
    "VRMLGeometry",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLIndexedFaceSet::createEmpty,
    VRMLIndexedFaceSet::init,
    vrmlIndexedFaceSetDescInserter,
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

void VRMLIndexedFaceSet::init(void)
{
    VRMLToOSGAction::registerDefaultTrav(
        VRMLIndexedFaceSet::getClassType(),
        osgTypedFunctionFunctor2Ref<
            VRMLAction::ActionResult,
            VRMLNode,
            VRMLAction *>(osgVRMLIndexedFaceSetToOpenSG));
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

VRMLIndexedFaceSet::VRMLIndexedFaceSet(void) :
 	 Inherited         (    ),
    _sfColor           (NULL),
    _sfCoord           (NULL),
    _sfNormal          (NULL),
    _sfTexCoord        (NULL),

    _sfCcw             (true),
    _mfColorIndex      (    ),
    _sfColorPerVertex  (true),
    _sfConvex          (true),
    _mfCoordIndex      (    ),
    _sfCreaseAngle     (0.f ),
    _mfNormalIndex     (    ),
    _sfNormalPerVertex (true),
    _sfSolid           (true),
    _mfTexCoordIndex   (    ),

    _sfUpdateNormalMode(    )
{
    _sfUpdateNormalMode.getValue().assign("nice");
}


VRMLIndexedFaceSet::VRMLIndexedFaceSet(
    const VRMLIndexedFaceSet &source) :
	
     Inherited         (source                    ),
    _sfColor           (source._sfColor           ),
    _sfCoord           (source._sfCoord           ),
    _sfNormal          (source._sfNormal          ),
    _sfTexCoord        (source._sfTexCoord        ),

    _sfCcw             (source._sfCcw             ),
    _mfColorIndex      (source._mfColorIndex      ),
    _sfColorPerVertex  (source._sfColorPerVertex  ),
    _sfConvex          (source._sfConvex          ),
    _mfCoordIndex      (source._mfCoordIndex      ),
    _sfCreaseAngle     (source._sfCreaseAngle     ),
    _mfNormalIndex     (source._mfNormalIndex     ),
    _sfNormalPerVertex (source._sfNormalPerVertex ),
    _sfSolid           (source._sfSolid           ),
    _mfTexCoordIndex   (source._mfTexCoordIndex   ),

    _sfUpdateNormalMode(source._sfUpdateNormalMode)
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#ifdef WIN32
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLIndexedFaceSet, Ptr);

#ifdef WIN32
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLIndexedFaceSet::~VRMLIndexedFaceSet(void)
{
}

/*------------------------------ access -----------------------------------*/

SFVRMLNode *VRMLIndexedFaceSet::getSFColor(void)
{
    return &_sfColor;
}

SFVRMLNode *VRMLIndexedFaceSet::getSFCoord(void)
{
    return &_sfCoord;
}

SFVRMLNode *VRMLIndexedFaceSet::getSFNormal(void)
{
    return &_sfNormal;
}

SFVRMLNode *VRMLIndexedFaceSet::getSFTexCoord(void)
{
    return &_sfTexCoord;
}

SFBool *VRMLIndexedFaceSet::getSFCcw(void)
{
    return &_sfCcw;
}

MFInt32 *VRMLIndexedFaceSet::getMFColorIndex(void)
{
    return &_mfColorIndex;
}

SFBool *VRMLIndexedFaceSet::getSFColorPerVertex(void)
{
    return &_sfColorPerVertex;
}

SFBool *VRMLIndexedFaceSet::getSFConvex(void)
{
    return &_sfConvex;
}

MFInt32 *VRMLIndexedFaceSet::getMFCoordIndex(void)
{
    return &_mfCoordIndex;
}

SFReal32 *VRMLIndexedFaceSet::getSFCreaseAngle(void)
{
    return &_sfCreaseAngle;
}

MFInt32 *VRMLIndexedFaceSet::getMFNormalIndex(void)
{
    return &_mfNormalIndex;
}

SFBool *VRMLIndexedFaceSet::getSFNormalPerVertex(void)
{
    return &_sfNormalPerVertex;
}

SFBool *VRMLIndexedFaceSet::getSFSolid(void)
{
    return &_sfSolid;
}

MFInt32 *VRMLIndexedFaceSet::getMFTexCoordIndex(void)
{
    return &_mfTexCoordIndex;
}

SFString *VRMLIndexedFaceSet::getSFUpdateNormalMode(void)
{
    return &_sfUpdateNormalMode;
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

VRMLIndexedFaceSetBinder::VRMLIndexedFaceSetBinder(void) :
	Inherited()
{
}

VRMLIndexedFaceSetBinder::~VRMLIndexedFaceSetBinder(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLIndexedFaceSetBinder::init(VRMLToOSGAction *)
{
    _pFieldContainer = Geometry::create();
}

void VRMLIndexedFaceSetBinder::setCoords(VRMLNodeBinder *pCoordBinder)
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

void VRMLIndexedFaceSetBinder::setNormals(VRMLNodeBinder *pNormalBinder)
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

void VRMLIndexedFaceSetBinder::setColors(VRMLNodeBinder *pColorBinder)
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

void VRMLIndexedFaceSetBinder::setTexCoords(
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

void VRMLIndexedFaceSetBinder::finish(VRMLToOSGAction *pAction)
{
    if(_pNode == NULL)
        return;

    VRMLIndexedFaceSet *pNode = 
        dynamic_cast<VRMLIndexedFaceSet *>(_pNode);

    if(pNode == NULL)
        return;

    GeometryPtr pGeo = GeometryPtr::dcast(_pFieldContainer);
    
    if(pGeo == NullFC)
        return;

    MFInt32 *pCoordIndex    = pNode->getMFCoordIndex();
    MFInt32 *pNormalIndex   = pNode->getMFNormalIndex();
    MFInt32 *pColorIndex    = pNode->getMFColorIndex();
    MFInt32 *pTexCoordIndex = pNode->getMFTexCoordIndex();

    setIndexFromVRMLData(pGeo,
                         pCoordIndex   ->getValues(),
                         pNormalIndex  ->getValues(),
                         pColorIndex   ->getValues(),
                         pTexCoordIndex->getValues(),
                         pNode->getSFConvex         ()->getValue(),
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
        createOptimizedPrimitives(pGeo, 1, true, true, 8, false);
    }
}



VRMLAction::ActionResult OSG::osgVRMLIndexedFaceSetToOpenSG(
    VRMLNode   &oNode,
    VRMLAction *pAction)
{
    VRMLAction::ActionResult returnValue = VRMLAction::Continue;

    fprintf(stderr,
            "Visit IndexedFaceSet : %s\n", 
            oNode.getName().str());

    VRMLToOSGAction *pConvAction        = 
        dynamic_cast<VRMLToOSGAction    *>(pAction);

    VRMLIndexedFaceSet *pIndexedFaceSet = 
        dynamic_cast<VRMLIndexedFaceSet *>(&oNode);

    if(pConvAction != NULL && pIndexedFaceSet != NULL)
    {
        VRMLIndexedFaceSetBinder    *pBinder     = NULL; 

        VRMLBindings::NodeBinderPtr  pNodeBinder = NULL;

        pBinder = new VRMLIndexedFaceSetBinder();
        
        pBinder->setNode(pIndexedFaceSet);
        pBinder->init   (pConvAction);
        
        returnValue = 
            pConvAction->apply(pIndexedFaceSet->getSFCoord()->getValue());

        if(pIndexedFaceSet->getSFCoord()->getValue() != NULL)
        {
            pNodeBinder = 
                pIndexedFaceSet->getSFCoord()->getValue()->getBinder();

            if(pNodeBinder != NULL)
            {
                pBinder->setCoords(pNodeBinder);
            }
        }

        if(returnValue == VRMLAction::Continue)
        {
            returnValue = 
                pConvAction->apply(pIndexedFaceSet->getSFNormal()->getValue());
        }

        if(pIndexedFaceSet->getSFNormal()->getValue() != NULL)
        {
            pNodeBinder = 
                pIndexedFaceSet->getSFNormal()->getValue()->getBinder();

            if(pNodeBinder != NULL)
            {
                pBinder->setNormals(pNodeBinder);
            }
        }

        if(returnValue == VRMLAction::Continue)
        {
            returnValue = 
                pConvAction->apply(pIndexedFaceSet->getSFColor()->getValue());
        }

        if(pIndexedFaceSet->getSFColor()->getValue() != NULL)
        {
            pNodeBinder = 
                pIndexedFaceSet->getSFColor()->getValue()->getBinder();

            if(pNodeBinder != NULL)
            {
                pBinder->setColors(pNodeBinder);
            }
        }

        if(returnValue == VRMLAction::Continue)
        {
            returnValue = 
                pConvAction->apply(
                    pIndexedFaceSet->getSFTexCoord()->getValue());
        }

        if(pIndexedFaceSet->getSFTexCoord()->getValue() != NULL)
        {
            pNodeBinder = 
                pIndexedFaceSet->getSFTexCoord()->getValue()->getBinder();

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
