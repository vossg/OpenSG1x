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

#define OSG_COMPILEVRMLTOOSGACTIONINST

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>


#include "OSGVRMLToOSGAction.h"
#include "OSGVRMLNode.h"

#if 0
#include "VRMLGroup.hpp"
#include "VRMLSwitch.hpp"
#include "VRMLShape.hpp"
#include "VSCVRMLCoordinate.hpp"
#include "VSCVRMLNormal.hpp"
#include "VSCVRMLTextureCoordinate.hpp"
#include "VSCVRMLColor.hpp"
#include "VSCVRMLIndexedFaceSet.hpp"
#include "VSCVRMLIndexedLineSet.hpp"
#include "VSCVRMLMaterial.hpp"
#include "VSCVRMLAppearance.hpp"
#include "VSCVRMLTransform.hpp"
#include "VSCVRMLScalarInterpolator.hpp"
#include "VSCVRMLPositionInterpolator.hpp"
#include "VSCVRMLOrientationInterpolator.hpp"
#include "VSCVRMLTimeSensor.hpp"
#include "VSCVRMLUse.hpp"
#include "VSCVRMLBox.hpp"
#include "VSCVRMLCone.hpp"
#include "VSCVRMLCylinder.hpp"
#include "VSCVRMLSphere.hpp"
#include "VSCVRMLBillboard.hpp"
#include "VSCVRMLImageTexture.hpp"
#include "VSCVRMLLOD.hpp"
#include "VSCVRMLInline.hpp"

#include "VSCVRMLHumanoid.hpp"
#include "VSCVRMLSegment.hpp"
#include "VSCVRMLJoint.hpp"

#include "VSCVRMLGroupBinder.hpp"
#include "VSCVRMLSwitchBinder.hpp"
#include "VSCVRMLShapeBinder.hpp"
#include "VSCVRMLIndexedFaceSetBinder.hpp"
#include "VSCVRMLIndexedLineSetBinder.hpp"
#include "VSCVRMLCoordinateBinder.hpp"
#include "VSCVRMLNormalBinder.hpp"
#include "VSCVRMLTextureCoordinateBinder.hpp"
#include "VSCVRMLColorBinder.hpp"
#include "VSCVRMLAppearanceBinder.hpp"
#include "VSCVRMLMaterialBinder.hpp"
#include "VSCVRMLTransformBinder.hpp"
#include "VSCVRMLUseBinder.hpp"
#include "VSCVRMLBoxBinder.hpp"
#include "VSCVRMLConeBinder.hpp"
#include "VSCVRMLCylinderBinder.hpp"
#include "VSCVRMLSphereBinder.hpp"
#include "VSCVRMLBillboardBinder.hpp"
#include "VSCVRMLImageTextureBinder.hpp"
#include "VSCVRMLLODBinder.hpp"
#include "VSCVRMLInlineBinder.hpp"

#include "VSCVRMLHumanoidBinder.hpp"
#endif

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGVRMLTOOSGACTION_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

template class OSG_VRML_DLLMAPPING 
     VRMLStaticActionMixin<ToOpenSGActionDesc>;

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

VRMLToOSGAction::VRMLToOSGAction(void) :
 	 Inherited   (             ),
    _uiOptions   (CreateNormals),
    _pNameNodeMap(NULL         )
{
}


/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

VRMLToOSGAction::~VRMLToOSGAction(void)
{
}

/*------------------------------ access -----------------------------------*/

void VRMLToOSGAction::setOptions(UInt32 uiOptions)
{
    _uiOptions = uiOptions;
}

UInt32 VRMLToOSGAction::getOptions(void)
{
    return _uiOptions;
}

void VRMLToOSGAction::setNameNodeMap(NameNodeMap *pMap)
{
    _pNameNodeMap = pMap;
}

VRMLToOSGAction::NameNodeMap *VRMLToOSGAction::getNameNodeMap(void)
{
    return _pNameNodeMap;
}


#if 0
//---------------------------------------------------------------------------
//  Callbacks
//---------------------------------------------------------------------------


VSCVRMLAction::VSCActionResult VSC::vscVRMLSwitchToOpenSG(
    VSCVRMLNode   &oNode,
    VSCVRMLAction *pAction)
{
    VSCVRMLAction::VSCActionResult returnValue = VSCVRMLAction::VSCContinue;

//    fprintf(stderr, "Visit Switch : %s\n", oNode.getName().getString());

    VSCVRMLToOSGAction *pConvAction = 
        dynamic_cast<VSCVRMLToOSGAction *>(pAction);

    VSCVRMLSwitch      *pSwitch     = 
        dynamic_cast<VSCVRMLSwitch      *>(&oNode );

    if(pConvAction != NULL && pSwitch != NULL)
    {
        VSCMFVRMLNode::iterator nodeIt  = pSwitch->getMFChoice()->begin();
        VSCMFVRMLNode::iterator nodeEnd = pSwitch->getMFChoice()->end  (); 

        VSCVRMLSwitchBinder *pBinder = new VSCVRMLSwitchBinder();

        pBinder->setNode(pSwitch);
        pBinder->init   (pConvAction);

        OSG::NodePtr                           pNode       = OSG::NullFC;
        VSC::VSCVRMLBindings::VSCNodeBinderPtr pNodeBinder = NULL;

        while(nodeIt != nodeEnd)
        {
            returnValue = pConvAction->apply(*nodeIt);

            pNodeBinder = (*nodeIt)->getBinder();

            if(pNodeBinder != NULL)
            {
                pNode = OSG::NodePtr::dcast(pNodeBinder->getFCPtr());

                if(pNode != OSG::NullFC)
                {
                    pBinder->addChoice(pNode);
                }
            }
            if(returnValue != VSCVRMLAction::VSCContinue)
            {
                break;
            }

            ++nodeIt;
        }

        pBinder->finish(pConvAction);
        oNode.setBinder(pBinder);
    }

    return returnValue;
}

VSCVRMLAction::VSCActionResult VSC::vscVRMLInlineToOpenSG(
    VSCVRMLNode   &oNode,
    VSCVRMLAction *pAction)
{
    fprintf(stderr, "Visit Inline : %s\n", oNode.getName().getString());

    VSCVRMLToOSGAction *pConvAction = 
        dynamic_cast<VSCVRMLToOSGAction *>(pAction);

    VSCVRMLInline      *pInline     = 
        dynamic_cast<VSCVRMLInline      *>(&oNode );

    if(pConvAction != NULL && pInline != NULL)
    {
        VSCVRMLInlineBinder *pBinder = new VSCVRMLInlineBinder();

        pBinder->setNode(pInline    );
        pBinder->init   (pConvAction);

        pBinder->finish (pConvAction);
        oNode.setBinder (pBinder);
    }

    return VSCVRMLAction::VSCContinue;
}

VSCVRMLAction::VSCActionResult VSC::vscVRMLLODToOpenSG(
    VSCVRMLNode   &oNode,
    VSCVRMLAction *pAction)
{
    VSCVRMLAction::VSCActionResult returnValue = VSCVRMLAction::VSCContinue;

    fprintf(stderr, "Visit LOD : %s\n", oNode.getName().getString());

    VSCVRMLToOSGAction *pConvAction = 
        dynamic_cast<VSCVRMLToOSGAction *>(pAction);

    VSCVRMLLOD         *pLOD        = 
        dynamic_cast<VSCVRMLLOD         *>(&oNode );

    if(pConvAction != NULL && pLOD != NULL)
    {
        VSCMFVRMLNode::iterator nodeIt  = pLOD->getMFLevel()->begin();
        VSCMFVRMLNode::iterator nodeEnd = pLOD->getMFLevel()->end  (); 

        VSCVRMLLODBinder *pBinder = new VSCVRMLLODBinder();

        pBinder->setNode(pLOD);
        pBinder->init   (pConvAction);

        OSG::NodePtr                           pNode       = OSG::NullFC;
        VSC::VSCVRMLBindings::VSCNodeBinderPtr pNodeBinder = NULL;

        while(nodeIt != nodeEnd)
        {
            returnValue = pConvAction->apply(*nodeIt);

            pNodeBinder = (*nodeIt)->getBinder();

            if(pNodeBinder != NULL)
            {
                pNode = OSG::NodePtr::dcast(pNodeBinder->getFCPtr());

                if(pNode != OSG::NullFC)
                {
                    pBinder->addLevel(pNode);
                }
            }
            if(returnValue != VSCVRMLAction::VSCContinue)
            {
                break;
            }

            ++nodeIt;
        }

        pBinder->finish(pConvAction);
        oNode.setBinder(pBinder);
    }

    return returnValue;
}







VSCVRMLAction::VSCActionResult VSC::vscVRMLIndexedLineSetToOpenSG(
    VSCVRMLNode   &oNode,
    VSCVRMLAction *pAction)
{
    VSCVRMLAction::VSCActionResult returnValue = VSCVRMLAction::VSCContinue;

//    fprintf(stderr,
//            "Visit IndexedLineeSet : %s\n", 
//            oNode.getName().getString());

    VSCVRMLToOSGAction    *pConvAction     = 
        dynamic_cast<VSCVRMLToOSGAction    *>(pAction);

    VSCVRMLIndexedLineSet *pIndexedLineSet = 
        dynamic_cast<VSCVRMLIndexedLineSet *>(&oNode);

    if(pConvAction != NULL && pIndexedLineSet != NULL)
    {
        VSCVRMLIndexedLineSetBinder            *pBinder     = NULL; 

        VSC::VSCVRMLBindings::VSCNodeBinderPtr  pNodeBinder = NULL;

        pBinder = new VSCVRMLIndexedLineSetBinder();
        
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

        if(returnValue == VSCVRMLAction::VSCContinue)
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




VSCVRMLAction::VSCActionResult VSC::vscVRMLScalarInterpolatorToOpenSG(
    VSCVRMLNode   &oNode,
    VSCVRMLAction *pAction)
{
//    fprintf(stderr,
//            "Visit ScalarInterpolator : %s\n", 
//            oNode.getName().getString());

    VSCVRMLToOSGAction        *pConvAction = 
        dynamic_cast<VSCVRMLToOSGAction        *>(pAction);

    VSCVRMLScalarInterpolator *pInterpol   = 
        dynamic_cast<VSCVRMLScalarInterpolator *>(&oNode );

    if(pConvAction != NULL && pInterpol != NULL)
    {
    }

    return VSCVRMLAction::VSCContinue;
}

VSCVRMLAction::VSCActionResult VSC::vscVRMLPositionInterpolatorToOpenSG(
    VSCVRMLNode   &oNode,
    VSCVRMLAction *pAction)
{
//    fprintf(stderr,
//            "Visit PositionInterpolator : %s\n", 
//            oNode.getName().getString());

    VSCVRMLToOSGAction          *pConvAction = 
        dynamic_cast<VSCVRMLToOSGAction          *>(pAction);

    VSCVRMLPositionInterpolator *pInterpol   = 
        dynamic_cast<VSCVRMLPositionInterpolator *>(&oNode );

    if(pConvAction != NULL && pInterpol != NULL)
    {
    }

    return VSCVRMLAction::VSCContinue;
}

VSCVRMLAction::VSCActionResult VSC::vscVRMLOrientationInterpolatorToOpenSG(
    VSCVRMLNode   &oNode,
    VSCVRMLAction *pAction)
{
//    fprintf(stderr,
//            "Visit OrientationInterpolator : %s\n", 
//            oNode.getName().getString());

    VSCVRMLToOSGAction             *pConvAction = 
        dynamic_cast<VSCVRMLToOSGAction             *>(pAction);

    VSCVRMLOrientationInterpolator *pInterpol   = 
        dynamic_cast<VSCVRMLOrientationInterpolator *>(&oNode );

    if(pConvAction != NULL && pInterpol != NULL)
    {
    }

    return VSCVRMLAction::VSCContinue;
}

VSCVRMLAction::VSCActionResult VSC::vscVRMLTimeSensorToOpenSG(
    VSCVRMLNode   &oNode,
    VSCVRMLAction *pAction)
{
//    fprintf(stderr,
//            "Visit TimeSensor : %s\n", 
//            oNode.getName().getString());

    VSCVRMLToOSGAction *pConvAction = 
        dynamic_cast<VSCVRMLToOSGAction *>(pAction);

    VSCVRMLTimeSensor  *pSensor     = 
        dynamic_cast<VSCVRMLTimeSensor  *>(&oNode );

    if(pConvAction != NULL && pSensor != NULL)
    {
/*
        VSCVRMLMaterialBinder *pBinder     = new VSCVRMLMaterialBinder();
        VSCVRMLNodeBinder     *pNodeBinder = NULL;

        pBinder->setNode(pMat);
        pBinder->init   (pConvAction);

        pBinder->finish(pConvAction);
        oNode.setBinder(pBinder);
*/
    }

    return VSCVRMLAction::VSCContinue;
}



VSCVRMLAction::VSCActionResult VSC::vscVRMLBoxToOpenSG(VSCVRMLNode   &oNode,
                                                       VSCVRMLAction *pAction)
{
//    fprintf(stderr,
//            "Visit Box : %s\n", 
//            oNode.getName().getString());

    VSCVRMLToOSGAction *pConvAction = 
        dynamic_cast<VSCVRMLToOSGAction *>(pAction);

    VSCVRMLBox         *pBox        = 
        dynamic_cast<VSCVRMLBox         *>(&oNode );

    if(pConvAction != NULL && pBox != NULL)
    {
        VSCVRMLBoxBinder *pBinder = new VSCVRMLBoxBinder();

        pBinder->setNode(pBox);
        pBinder->init   (pConvAction);

        pBinder->finish (pConvAction);
        oNode.setBinder (pBinder);
    }

    return VSCVRMLAction::VSCContinue;
}

VSCVRMLAction::VSCActionResult VSC::vscVRMLConeToOpenSG(
    VSCVRMLNode   &oNode,
    VSCVRMLAction *pAction)
{
//    fprintf(stderr,
//            "Visit Cone : %s\n", 
//            oNode.getName().getString());

    VSCVRMLToOSGAction *pConvAction = 
        dynamic_cast<VSCVRMLToOSGAction *>(pAction);

    VSCVRMLCone        *pCone       = 
        dynamic_cast<VSCVRMLCone        *>(&oNode );

    if(pConvAction != NULL && pCone != NULL)
    {
        VSCVRMLConeBinder *pBinder = new VSCVRMLConeBinder();

        pBinder->setNode(pCone);
        pBinder->init   (pConvAction);

        pBinder->finish (pConvAction);
        oNode.setBinder (pBinder);
    }

    return VSCVRMLAction::VSCContinue;
}

VSCVRMLAction::VSCActionResult VSC::vscVRMLCylinderToOpenSG(
    VSCVRMLNode   &oNode,
    VSCVRMLAction *pAction)
{
//    fprintf(stderr,
//            "Visit Cylinder : %s\n", 
//            oNode.getName().getString());

    VSCVRMLToOSGAction *pConvAction = 
        dynamic_cast<VSCVRMLToOSGAction *>(pAction);

    VSCVRMLCylinder    *pCylinder   = 
        dynamic_cast<VSCVRMLCylinder    *>(&oNode );

    if(pConvAction != NULL && pCylinder != NULL)
    {
        VSCVRMLCylinderBinder *pBinder = new VSCVRMLCylinderBinder();

        pBinder->setNode(pCylinder  );
        pBinder->init   (pConvAction);

        pBinder->finish (pConvAction);
        oNode.setBinder (pBinder);
    }

    return VSCVRMLAction::VSCContinue;
}

VSCVRMLAction::VSCActionResult VSC::vscVRMLSphereToOpenSG(
    VSCVRMLNode   &oNode,
    VSCVRMLAction *pAction)
{
//    fprintf(stderr,
//            "Visit Sphere : %s\n", 
//            oNode.getName().getString());

    VSCVRMLToOSGAction *pConvAction = 
        dynamic_cast<VSCVRMLToOSGAction *>(pAction);

    VSCVRMLSphere      *pSphere     = 
        dynamic_cast<VSCVRMLSphere      *>(&oNode );

    if(pConvAction != NULL && pSphere != NULL)
    {
        VSCVRMLSphereBinder *pBinder = new VSCVRMLSphereBinder();

        pBinder->setNode(pSphere    );
        pBinder->init   (pConvAction);

        pBinder->finish (pConvAction);
        oNode.setBinder (pBinder);
    }

    return VSCVRMLAction::VSCContinue;
}

VSCVRMLAction::VSCActionResult VSC::vscVRMLBillboardToOpenSG(
    VSCVRMLNode   &oNode,
    VSCVRMLAction *pAction)
{
    VSCVRMLAction::VSCActionResult returnValue = VSCVRMLAction::VSCContinue;

//    fprintf(stderr, "Visit Billboard : %s\n", oNode.getName().getString());

    VSCVRMLToOSGAction *pConvAction = 
        dynamic_cast<VSCVRMLToOSGAction *>(pAction);

    VSCVRMLBillboard   *pBillboard  = 
        dynamic_cast<VSCVRMLBillboard   *>(&oNode );

    if(pConvAction != NULL && pBillboard != NULL)
    {
        VSCMFVRMLNode::iterator nodeIt  = pBillboard->getMFChildren()->begin();
        VSCMFVRMLNode::iterator nodeEnd = pBillboard->getMFChildren()->end  ();

        VSCVRMLBillboardBinder *pBinder = new VSCVRMLBillboardBinder();

        pBinder->setNode(pBillboard);
        pBinder->init   (pConvAction);

        OSG::NodePtr                           pNode       = OSG::NullFC;
        VSC::VSCVRMLBindings::VSCNodeBinderPtr pNodeBinder = NULL;

        while(nodeIt != nodeEnd)
        {
            returnValue = pConvAction->apply(*nodeIt);

            pNodeBinder = (*nodeIt)->getBinder();

            if(pNodeBinder != NULL)
            {
                pNode = OSG::NodePtr::dcast(pNodeBinder->getFCPtr());

                if(pNode != OSG::NullFC)
                {
                    pBinder->addChild(pNode);
                }
            }
            if(returnValue != VSCVRMLAction::VSCContinue)
            {
                break;
            }

            ++nodeIt;
        }

        pBinder->finish(pConvAction);
        oNode.setBinder(pBinder);
    }

    return returnValue;
}



VSCVRMLAction::VSCActionResult VSC::vscVRMLHumanoidToOpenSG(
    VSCVRMLNode   &oNode,
    VSCVRMLAction *pAction)
{
    VSCVRMLAction::VSCActionResult returnValue = VSCVRMLAction::VSCContinue;

    fprintf(stderr, "Visit Humanoid : %s\n", oNode.getName().getString());

    VSCVRMLToOSGAction *pConvAction = 
        dynamic_cast<VSCVRMLToOSGAction *>(pAction);

    VSCVRMLHumanoid    *pHuman      = 
        dynamic_cast<VSCVRMLHumanoid    *>(&oNode );

    if(pConvAction != NULL && pHuman != NULL)
    {
        VSCVRMLHumanoidBinder *pBinder = new VSCVRMLHumanoidBinder();
        
        pBinder->setNode(pHuman);
        pBinder->init   (pConvAction);
            
        VSCMFVRMLNode::iterator nodeIt  = pHuman->getMFSkinCoord()->begin();
        VSCMFVRMLNode::iterator nodeEnd = pHuman->getMFSkinCoord()->end  ();

        while(nodeIt != nodeEnd)
        {
            returnValue = pConvAction->apply(*nodeIt);
                
            if(returnValue != VSCVRMLAction::VSCContinue)
            {
                break;
            }
            
            ++nodeIt;
        }

        if(returnValue == VSCVRMLAction::VSCContinue)
        {
            nodeIt  = pHuman->getMFSkinNormal()->begin();
            nodeEnd = pHuman->getMFSkinNormal()->end  ();

            while(nodeIt != nodeEnd)
            {
                returnValue = pConvAction->apply(*nodeIt);
                
                if(returnValue != VSCVRMLAction::VSCContinue)
                {
                    break;
                }
                
                ++nodeIt;
            }
        }

        if(returnValue == VSCVRMLAction::VSCContinue)
        {
//            nodeIt  = pHuman->getMFSkeleton()->begin();
//            nodeEnd = pHuman->getMFSkeleton()->end  ();

            nodeIt  = pHuman->getMFSkin()->begin();
            nodeEnd = pHuman->getMFSkin()->end  ();

            OSG::NodePtr                           pNode       = OSG::NullFC;
            VSC::VSCVRMLBindings::VSCNodeBinderPtr pNodeBinder = NULL;
            
            while(nodeIt != nodeEnd)
            {
                returnValue = pConvAction->apply(*nodeIt);
                
                pNodeBinder = (*nodeIt)->getBinder();
                
                if(pNodeBinder != NULL)
                {
                    pNode = OSG::NodePtr::dcast(pNodeBinder->getFCPtr());
                    
                    if(pNode != OSG::NullFC)
                    {
                        pBinder->addChild(pNode);
                    }
                }
                
                if(returnValue != VSCVRMLAction::VSCContinue)
                {
                    break;
                }
                
                ++nodeIt;
            }

            nodeIt  = pHuman->getMFSkeleton()->begin();
            nodeEnd = pHuman->getMFSkeleton()->end  ();

            pNode       = OSG::NullFC;
            pNodeBinder = NULL;
            
            while(nodeIt != nodeEnd)
            {
                returnValue = pConvAction->apply(*nodeIt);
                
                pNodeBinder = (*nodeIt)->getBinder();
                
                if(pNodeBinder != NULL)
                {
                    pNode = OSG::NodePtr::dcast(pNodeBinder->getFCPtr());
                    
                    if(pNode != OSG::NullFC)
                    {
                        pBinder->addChild(pNode);
                    }
                }
                
                if(returnValue != VSCVRMLAction::VSCContinue)
                {
                    break;
                }
                
                ++nodeIt;
            }
        }

        pBinder->finish(pConvAction);
        oNode.setBinder(pBinder);
    }

    return returnValue;
}

void VSC::vscInitToOpenSGAction(void)
{

    VSCVRMLToOSGAction::registerDefaultTrav(
        VSCVRMLSwitch::getClassType(),
        vscTypedFunctionFunctor2(vscVRMLSwitchToOpenSG));

    VSCVRMLToOSGAction::registerDefaultTrav(
        VSCVRMLLOD::getClassType(),
        vscTypedFunctionFunctor2(vscVRMLLODToOpenSG));

    VSCVRMLToOSGAction::registerDefaultTrav(
        VSCVRMLInline::getClassType(),
        vscTypedFunctionFunctor2(vscVRMLInlineToOpenSG));

    VSCVRMLToOSGAction::registerDefaultTrav(
        VSCVRMLShape::getClassType(),
        vscTypedFunctionFunctor2(vscVRMLShapeToOpenSG));

    VSCVRMLToOSGAction::registerDefaultTrav(
        VSCVRMLCoordinate::getClassType(),
        vscTypedFunctionFunctor2(vscVRMLCoordinateToOpenSG));

    VSCVRMLToOSGAction::registerDefaultTrav(
        VSCVRMLNormal::getClassType(),
        vscTypedFunctionFunctor2(vscVRMLNormalToOpenSG));

    VSCVRMLToOSGAction::registerDefaultTrav(
        VSCVRMLTextureCoordinate::getClassType(),
        vscTypedFunctionFunctor2(vscVRMLTextureCoordinateToOpenSG));

    VSCVRMLToOSGAction::registerDefaultTrav(
        VSCVRMLColor::getClassType(),
        vscTypedFunctionFunctor2(vscVRMLColorToOpenSG));

    VSCVRMLToOSGAction::registerDefaultTrav(
        VSCVRMLIndexedFaceSet::getClassType(),
        vscTypedFunctionFunctor2(vscVRMLIndexedFaceSetToOpenSG));

    VSCVRMLToOSGAction::registerDefaultTrav(
        VSCVRMLIndexedLineSet::getClassType(),
        vscTypedFunctionFunctor2(vscVRMLIndexedLineSetToOpenSG));

    VSCVRMLToOSGAction::registerDefaultTrav(
        VSCVRMLMaterial::getClassType(),
        vscTypedFunctionFunctor2(vscVRMLMaterialToOpenSG));

    VSCVRMLToOSGAction::registerDefaultTrav(
        VSCVRMLAppearance::getClassType(),
        vscTypedFunctionFunctor2(vscVRMLAppearanceToOpenSG));

    VSCVRMLToOSGAction::registerDefaultTrav(
        VSCVRMLTransform::getClassType(),
        vscTypedFunctionFunctor2(vscVRMLTransformToOpenSG));

    VSCVRMLToOSGAction::registerDefaultTrav(
        VSCVRMLScalarInterpolator::getClassType(),
        vscTypedFunctionFunctor2(vscVRMLScalarInterpolatorToOpenSG));

    VSCVRMLToOSGAction::registerDefaultTrav(
        VSCVRMLPositionInterpolator::getClassType(),
        vscTypedFunctionFunctor2(vscVRMLPositionInterpolatorToOpenSG));

    VSCVRMLToOSGAction::registerDefaultTrav(
        VSCVRMLOrientationInterpolator::getClassType(),
        vscTypedFunctionFunctor2(vscVRMLOrientationInterpolatorToOpenSG));

    VSCVRMLToOSGAction::registerDefaultTrav(
        VSCVRMLTimeSensor::getClassType(),
        vscTypedFunctionFunctor2(vscVRMLTimeSensorToOpenSG));

    VSCVRMLToOSGAction::registerDefaultTrav(
        VSCVRMLUse::getClassType(),
        vscTypedFunctionFunctor2(vscVRMLUseToOpenSG));

    VSCVRMLToOSGAction::registerDefaultTrav(
        VSCVRMLBox::getClassType(),
        vscTypedFunctionFunctor2(vscVRMLBoxToOpenSG));

    VSCVRMLToOSGAction::registerDefaultTrav(
        VSCVRMLCone::getClassType(),
        vscTypedFunctionFunctor2(vscVRMLConeToOpenSG));

    VSCVRMLToOSGAction::registerDefaultTrav(
        VSCVRMLCylinder::getClassType(),
        vscTypedFunctionFunctor2(vscVRMLCylinderToOpenSG));

    VSCVRMLToOSGAction::registerDefaultTrav(
        VSCVRMLSphere::getClassType(),
        vscTypedFunctionFunctor2(vscVRMLSphereToOpenSG));

    VSCVRMLToOSGAction::registerDefaultTrav(
        VSCVRMLBillboard::getClassType(),
        vscTypedFunctionFunctor2(vscVRMLBillboardToOpenSG));

    VSCVRMLToOSGAction::registerDefaultTrav(
        VSCVRMLImageTexture::getClassType(),
        vscTypedFunctionFunctor2(vscVRMLImageTextureToOpenSG));

    // Humanoid

    VSCVRMLToOSGAction::registerDefaultTrav(
        VSCVRMLHumanoid::getClassType(),
        vscTypedFunctionFunctor2(vscVRMLHumanoidToOpenSG));

    VSCVRMLToOSGAction::registerDefaultTrav(
        VSCVRMLSegment::getClassType(),
        vscTypedFunctionFunctor2(vscVRMLGroupToOpenSG));

    VSCVRMLToOSGAction::registerDefaultTrav(
        VSCVRMLJoint::getClassType(),
        vscTypedFunctionFunctor2(vscVRMLTransformToOpenSG));
}
#endif
