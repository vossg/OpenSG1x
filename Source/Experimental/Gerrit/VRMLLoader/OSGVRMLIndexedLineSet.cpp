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

#include "OSGVRMLIndexedLineSet.h"
#include "OSGDataElementDesc.h"

#include "OSGVRMLToOSGAction.h"

#include <OSGGeoFunctions.h>

OSG_USING_NAMESPACE

OSG_BEGIN_NAMESPACE

VRMLAction::ActionResult osgVRMLIndexedLineSetToOpenSG(VRMLNode   &oNode,
                                                       VRMLAction *pAction);


OSG_END_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

#if !defined(OSG_NO_FULL_DOC)

static void vrmlIndexedLineSetDescInserter(ReflexiveContainerType *pType)
{
    if(pType == NULL)
        return;

    DataElementDesc *pDesc = NULL;

    pDesc = new DataElementDesc(
        SFVRMLNode::getClassType(),
        "color",
        OSG_RC_ELEM_IDM_DESC(VRMLIndexedLineSet::ColorField),
        false,
        (DataElemGetMethod) &VRMLIndexedLineSet::getSFColor,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFVRMLNode::getClassType(),
        "coord",
        OSG_RC_ELEM_IDM_DESC(VRMLIndexedLineSet::CoordField),
        false,
        (DataElemGetMethod) &VRMLIndexedLineSet::getSFCoord,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFInt32::getClassType(),
        "colorIndex",
        OSG_RC_ELEM_IDM_DESC(VRMLIndexedLineSet::ColorIndexField),
        false,
        (DataElemGetMethod) &VRMLIndexedLineSet::getMFColorIndex,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        SFBool::getClassType(),
        "colorPerVertex",
        OSG_RC_ELEM_IDM_DESC(VRMLIndexedLineSet::ColorPerVertexField),
        false,
        (DataElemGetMethod) &VRMLIndexedLineSet::getSFColorPerVertex,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);

    pDesc = new DataElementDesc(
        MFInt32::getClassType(),
        "coordIndex",
        OSG_RC_ELEM_IDM_DESC(VRMLIndexedLineSet::CoordIndexField),
        false,
        (DataElemGetMethod) &VRMLIndexedLineSet::getMFCoordIndex,
        NULL,
        NULL);

    pType->addInitialDesc(pDesc);
}


VRMLObjectType VRMLIndexedLineSet::_type(
    "IndexedLineSet",
    "VRMLGeometry",
    "VRMLNodes",
    (VRMLProtoCreateF) &VRMLIndexedLineSet::createEmpty,
    &VRMLIndexedLineSet::init,
    vrmlIndexedLineSetDescInserter,
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

void VRMLIndexedLineSet::init(void)
{
    VRMLToOSGAction::registerDefaultTrav(
        VRMLIndexedLineSet::getClassType(),
        osgTypedFunctionFunctor2Ref<VRMLAction::ActionResult,
                                    VRMLNode,
                                    VRMLAction *>(
                                        osgVRMLIndexedLineSetToOpenSG));
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

VRMLIndexedLineSet::VRMLIndexedLineSet(void) :
 	 Inherited        (    ),
    _sfColor          (NULL),
    _sfCoord          (NULL),

    _mfColorIndex     (    ),
    _sfColorPerVertex (true),
    _mfCoordIndex     (    )
{
}


VRMLIndexedLineSet::VRMLIndexedLineSet(
    const VRMLIndexedLineSet &source) :
	
     Inherited        (source                   ),
    _sfColor          (source._sfColor          ),
    _sfCoord          (source._sfCoord          ),

    _mfColorIndex     (source._mfColorIndex     ),
    _sfColorPerVertex (source._sfColorPerVertex ),
    _mfCoordIndex     (source._mfCoordIndex     )
{
}

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (disable : 424)
#endif

OSG_VRMLOBJ_DEF(VRMLIndexedLineSet, Ptr);

#if defined(WIN32) || defined(OSG_LINUX_ICC)
#pragma warning (default : 424)
#endif

/*------------- constructors & destructors --------------------------------*/

VRMLIndexedLineSet::~VRMLIndexedLineSet(void)
{
}

/*------------------------------ access -----------------------------------*/

SFVRMLNode *VRMLIndexedLineSet::getSFColor(void)
{
    return &_sfColor;
}

SFVRMLNode *VRMLIndexedLineSet::getSFCoord(void)
{
    return &_sfCoord;
}

MFInt32 *VRMLIndexedLineSet::getMFColorIndex(void)
{
    return &_mfColorIndex;
}

SFBool *VRMLIndexedLineSet::getSFColorPerVertex(void)
{
    return &_sfColorPerVertex;
}

MFInt32 *VRMLIndexedLineSet::getMFCoordIndex(void)
{
    return &_mfCoordIndex;
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

VRMLIndexedLineSetBinder::VRMLIndexedLineSetBinder(void) :
	Inherited()
{
}

VRMLIndexedLineSetBinder::~VRMLIndexedLineSetBinder(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLIndexedLineSetBinder::init(VRMLToOSGAction *)
{
    _pFieldContainer = Geometry::create();
}

void VRMLIndexedLineSetBinder::setCoords(VRMLNodeBinder *pCoordBinder)
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

void VRMLIndexedLineSetBinder::setColors(VRMLNodeBinder *pColorBinder)
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

void VRMLIndexedLineSetBinder::finish(VRMLToOSGAction *pAction)
{
    if(_pNode == NULL)
        return;

    VRMLIndexedLineSet *pNode = 
        dynamic_cast<VRMLIndexedLineSet *>(_pNode);

    if(pNode == NULL)
        return;

    GeometryPtr pGeo = GeometryPtr::dcast(_pFieldContainer);
    
    if(pGeo == NullFC)
        return;

    MFInt32 *pCoordIndex    = NULL;
    MFInt32 *pColorIndex    = NULL;

    UInt32   uiNumIndices;
    
    pCoordIndex = new MFInt32;

    if(pNode->getMFCoordIndex()->empty() == false)
    {
        uiNumIndices = pNode->getMFCoordIndex()->size();

        pCoordIndex->resize(uiNumIndices);

        memcpy(&(pCoordIndex                   ->front()),
               &(pNode      ->getMFCoordIndex()->front()),
               sizeof(Int32) * uiNumIndices);
    }

    pColorIndex = new MFInt32;

    if(pNode->getMFColorIndex()->empty() == false)
    {
        uiNumIndices = pNode->getMFColorIndex()->size();

        pColorIndex->resize(uiNumIndices);

        memcpy(&(pColorIndex                   ->front()),
               &(pNode      ->getMFColorIndex()->front()),
               sizeof(Int32) * uiNumIndices);
    }


    vector<Int32> dummyVec;
    bool          dummyBool = false;

    setIndexFromVRMLData(pGeo,
                         pCoordIndex   ->getValues(),
                         dummyVec,
                         pColorIndex   ->getValues(),
                         dummyVec,
                         dummyBool,
                         dummyBool,
                         dummyBool,
                         pNode->getSFColorPerVertex ()->getValue(),
                         false,
                         false);

    delete pCoordIndex;
    delete pColorIndex;
}


VRMLAction::ActionResult OSG::osgVRMLIndexedLineSetToOpenSG(
    VRMLNode   &oNode,
    VRMLAction *pAction)
{
    VRMLAction::ActionResult returnValue = VRMLAction::Continue;

    fprintf(stderr,
            "Visit IndexedLineeSet : %s\n", 
            oNode.getName().str());

    VRMLToOSGAction    *pConvAction     = 
        dynamic_cast<VRMLToOSGAction    *>(pAction);

    VRMLIndexedLineSet *pIndexedLineSet = 
        dynamic_cast<VRMLIndexedLineSet *>(&oNode);

    if(pConvAction != NULL && pIndexedLineSet != NULL)
    {
        VRMLIndexedLineSetBinder    *pBinder     = NULL; 

        VRMLBindings::NodeBinderPtr  pNodeBinder = NULL;

        pBinder = new VRMLIndexedLineSetBinder();
        
        pBinder->setNode(pIndexedLineSet);
        pBinder->init   (pConvAction    );
        
        returnValue = 
            pConvAction->apply(pIndexedLineSet->getSFCoord()->getValue());


        if(pIndexedLineSet->getSFCoord()->getValue() != NULL)
        {
            pNodeBinder = 
                pIndexedLineSet->getSFCoord()->getValue()->getBinder();

            if(pNodeBinder != NULL)
            {
                pBinder->setCoords(pNodeBinder);
            }
        }

        if(returnValue == VRMLAction::Continue)
        {
            returnValue = 
                pConvAction->apply(pIndexedLineSet->getSFColor()->getValue());
        }

        if(pIndexedLineSet->getSFColor()->getValue() != NULL)
        {
            pNodeBinder = 
                pIndexedLineSet->getSFColor()->getValue()->getBinder();

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
    static Char8 cvsid_hpp[] = OSGVRMLINDEXEDLINESET_HEADER_CVSID;
}
