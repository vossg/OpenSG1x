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
 	 Inherited    (             ),
    _uiOptions    (CreateNormals),
    _pNameNodeMap (NULL         ),
    _eTransferMode(CopyData     )
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

void VRMLToOSGAction::setDataTransferMode(DataTransferMode eTransferMode)
{
    _eTransferMode = eTransferMode;
}

VRMLToOSGAction::DataTransferMode VRMLToOSGAction::getDataTransferMode(void)
{
    return _eTransferMode;
}


#if 0
//---------------------------------------------------------------------------
//  Callbacks
//---------------------------------------------------------------------------

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
