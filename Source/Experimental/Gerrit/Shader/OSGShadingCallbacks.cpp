/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                *
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

#include "OSGShadingCallbacks.h"

#include "OSGShadingAction.h"
#include "OSGMaterialDrawable.h"
#include "OSGSlices.h"
#include "OSGParticles.h"
#include "OSGGeometry.h"
#include "OSGGroup.h"
#include "OSGBillboard.h"
#include "OSGComponentTransform.h"
#include "OSGDistanceLOD.h"
#include "OSGMaterialGroup.h"
#include "OSGSwitch.h"
#include "OSGTransform.h"
#include "OSGDirectionalLight.h"
#include "OSGPointLight.h"
#include "OSGSpotLight.h"

OSG_USING_NAMESPACE

Action::ResultE ShadingCallbacks::billboardRenderEnter(CNodePtr &pNode, 
                                                       Action   *action)
{
    ShadingAction *pAct = dynamic_cast<ShadingAction *>(action         );
    Billboard     *pBB  = dynamic_cast<Billboard     *>(pNode.getCPtr());

    Matrix mMat;

//    cerr << "BB::render" << std::endl;

    pBB->calcMatrix(pAct, pAct->top_matrix(), mMat);

    pAct->push_matrix(mMat);

// !!! can't use visibles, as ToWorld gives garbage leading to wrong culling
//    pAct->selectVisibles();

    return Action::Continue;
}

Action::ResultE ShadingCallbacks::billboardRenderLeave(CNodePtr &, 
                                                       Action   *action)
{
    ShadingAction *pAct = dynamic_cast<ShadingAction *>(action);

    pAct->pop_matrix();

    return Action::Continue;
}


Action::ResultE ShadingCallbacks::compTransRenderEnter(CNodePtr &pNode, 
                                                       Action   *action)
{
    ShadingAction      *pAct = 
        dynamic_cast<ShadingAction      *>(action         );
    ComponentTransform *pTr  = 
        dynamic_cast<ComponentTransform *>(pNode.getCPtr());

    pAct->push_matrix(pTr->getMatrix());

    pAct->selectVisibles();

    return Action::Continue;
}

Action::ResultE ShadingCallbacks::compTransRenderLeave(CNodePtr &, 
                                                       Action   *action)
{
    ShadingAction *pAct = dynamic_cast<ShadingAction *>(action);

    pAct->pop_matrix();

    return Action::Continue;
}


Action::ResultE ShadingCallbacks::dirlightRenderEnter(CNodePtr &pNode, 
                                                      Action   *action)
{
    DirectionalLight *pDl = dynamic_cast<DirectionalLight *>(pNode.getCPtr());

    if(pDl->getOn() == false)
        return Action::Continue;

    DrawActionBase *da    = dynamic_cast<DrawActionBase *>(action);

    da->getStatistics()->getElem(
        DirectionalLight::statNDirectionalLights)->inc();
    
    return lightRenderEnter(pDl, action);
}

Action::ResultE ShadingCallbacks::dirlightRenderLeave(CNodePtr &pNode, 
                                                      Action   *action)
{
    DirectionalLight *pDl = dynamic_cast<DirectionalLight *>(pNode.getCPtr());

    if(pDl->getOn() == false)
        return Action::Continue;

    return lightRenderLeave(pDl, action);
}


Action::ResultE ShadingCallbacks::distanceLODRender(CNodePtr &pNode, 
                                                    Action   *action)
{
    DrawActionBase *da    = dynamic_cast<DrawActionBase *>(action);
    ShadingAction  *ra    = dynamic_cast<ShadingAction  *>(action);

    DistanceLOD    *pDLOD = dynamic_cast<DistanceLOD    *>(pNode.getCPtr());


    UInt32 numLevels = action->getNNodes ();
    UInt32 numRanges = pDLOD ->getMFRange()->size();

    UInt32 limit     = osgMin(numLevels, numRanges); 
    
    Int32  index     = -1;

    Pnt3f  eyepos(0.f, 0.f, 0.f);
    Pnt3f  objpos;

    da->getCameraToWorld().mult(eyepos);

    if(ra != NULL)
    {
        ra->top_matrix()              .mult(pDLOD->getCenter(), objpos);
    }
    else
    {
        da->getActNode()->getToWorld().mult(pDLOD->getCenter(), objpos);
    }
        
    Real32 dist = osgsqrt((eyepos[0] - objpos[0])*(eyepos[0] - objpos[0]) +
                          (eyepos[1] - objpos[1])*(eyepos[1] - objpos[1]) +
                          (eyepos[2] - objpos[2])*(eyepos[2] - objpos[2]));
    
    da->useNodeList();
    
    if(numRanges != 0 && numLevels!=0 )
    {
        if(dist < (*(pDLOD->getMFRange()))[0])
        {
            index = 0;
        } 
        else if(dist >= (*(pDLOD->getMFRange()))[numRanges-1])
        {
	    index = (numLevels > numRanges) ? numRanges : (limit-1); 
        }
        else
        {
            UInt32 i = 1;

            while( (i < numRanges) && 
                  !( ((*(pDLOD->getMFRange()))[i-1] <= dist) && 
                     (dist < (*(pDLOD->getMFRange()))[i]   )   ) )
            {
                i++;
            }
            
            index = osgMin(i, limit-1);
        } 
        
        if(da->isVisible(action->getNode(index).getCPtr()))
        {
            da->addNode(action->getNode(index));
        }
    }

    return Action::Continue;
}



Action::ResultE ShadingCallbacks::groupRenderEnter(CNodePtr &, 
                                                   Action   *action)
{
    DrawActionBase *da = dynamic_cast<DrawActionBase *>(action);

    if(da->selectVisibles() == 0)
        return Action::Skip;
    
    return Action::Continue;
}

Action::ResultE ShadingCallbacks::groupRenderLeave(CNodePtr &, Action *)
{
    return Action::Continue;
}


Action::ResultE ShadingCallbacks::lightRenderEnter(Light  *pLight, 
                                                   Action *action)
{
    ShadingAction *pAction = dynamic_cast<ShadingAction *>(action);

    pAction->dropLight(pLight);

    return Action::Continue;
}

Action::ResultE ShadingCallbacks::lightRenderLeave(Light  *, 
                                                   Action *)
{
    return Action::Continue;
}


Action::ResultE ShadingCallbacks::matDrawableRenderEnter(CNodePtr &pNode, 
                                                         Action   *action)
{
    ShadingAction    *a   = dynamic_cast<ShadingAction    *>(action         );
    MaterialDrawable *pMD = dynamic_cast<MaterialDrawable *>(pNode.getCPtr());

    Material::DrawFunctor func;

    func = osgTypedMethodFunctor1ObjPtr(pMD, 
                                        &MaterialDrawable::drawPrimitives);

    Material *m = a->getMaterial();

    if(m == NULL)
    {
        if(pMD->getMaterial() != NullFC)
        {
            m = pMD->getMaterial().getCPtr();
        }
        else
        {
            fprintf(stderr, "MaterialDrawable::render: no Material!?!\n");
            return Action::Continue;
        }
    }

    a->dropFunctor(func, m);

    return Action::Continue;
}

Action::ResultE ShadingCallbacks::matDrawableRenderLeave(CNodePtr &, 
                                                         Action   *)
{
    return Action::Continue;
}


Action::ResultE ShadingCallbacks::matGroupRenderEnter(CNodePtr &pNode, 
                                                      Action   *action)
{
    ShadingAction *da  = dynamic_cast<ShadingAction *>(action         );
    MaterialGroup *pMG = dynamic_cast<MaterialGroup *>(pNode.getCPtr());

    if(da != NULL && pMG->getSFMaterial()->getValue() != NullFC)
    {
        da->setMaterial(&(*(pMG->getSFMaterial()->getValue())));
    }

    return Action::Continue;
}

Action::ResultE ShadingCallbacks::matGroupRenderLeave(CNodePtr &, 
                                                      Action   *action)
{
    ShadingAction *da = dynamic_cast<ShadingAction *>(action);

    if(da != NULL)
    {
        da->setMaterial(NULL);
    }

    return Action::Continue;
}


Action::ResultE ShadingCallbacks::pointlightRenderEnter(CNodePtr &pNode, 
                                                        Action   *action)
{
    PointLight *pPl = dynamic_cast<PointLight *>(pNode.getCPtr());

    if(pPl->getOn() == false)
        return Action::Continue;

    DrawActionBase *da    = dynamic_cast<DrawActionBase *>(action);

    da->getStatistics()->getElem(PointLight::statNPointLights)->inc();

    return lightRenderEnter(pPl, action);
}

Action::ResultE ShadingCallbacks::pointlightRenderLeave(CNodePtr &pNode, 
                                                        Action   *action)
{
    PointLight *pPl = dynamic_cast<PointLight *>(pNode.getCPtr());

    if(pPl->getOn() == false)
        return Action::Continue;

    return lightRenderLeave(pPl, action);
}


Action::ResultE ShadingCallbacks::spotlightRenderEnter(CNodePtr &pNode, 
                                                       Action   *action)
{
    SpotLight *pSp = dynamic_cast<SpotLight *>(pNode.getCPtr());

    if(pSp->getOn() == false)
        return Action::Continue;

    DrawActionBase *da    = dynamic_cast<DrawActionBase *>(action);

    da->getStatistics()->getElem(SpotLight::statNSpotLights)->inc();

    return pointlightRenderEnter(pNode, action);
}

Action::ResultE ShadingCallbacks::spotlightRenderLeave(CNodePtr &pNode, 
                                                       Action   *action)
{
    SpotLight *pSp = dynamic_cast<SpotLight *>(pNode.getCPtr());

    if(pSp->getOn() == false)
        return Action::Continue;

    return lightRenderLeave(pSp, action);
}


Action::ResultE ShadingCallbacks::switchRender(CNodePtr &pNode, 
                                               Action   *action)
{
    Action::ResultE  returnValue = Action::Continue;

    DrawActionBase  *da  = dynamic_cast<DrawActionBase *>(action         );
    Switch          *pSw = dynamic_cast<Switch         *>(pNode.getCPtr());

    if((pSw->getChoice() >= 0                  ) && 
       (pSw->getChoice() <  action->getNNodes())  )
    {
        da->useNodeList();

        if(da->isVisible(action->getNode(pSw->getChoice()).getCPtr()))
        {
            da->addNode(action->getNode(pSw->getChoice()));
        }
    }
    else if(pSw->getChoice() == Switch::ALL)
    {
        if(da->selectVisibles() == 0)
            returnValue = Action::Skip;
    }
    else
    {
        returnValue = Action::Skip;
    }

    return returnValue;
}


Action::ResultE ShadingCallbacks::transformRenderEnter(CNodePtr &pNode, 
                                                       Action   *action)
{
    ShadingAction *pAct = dynamic_cast<ShadingAction *>(action         );
    Transform     *pTr  = dynamic_cast<Transform     *>(pNode.getCPtr());

    pAct->push_matrix(pTr->getMatrix());

    pAct->selectVisibles();

    return Action::Continue;
}

Action::ResultE ShadingCallbacks::transformRenderLeave(CNodePtr &, 
                                                       Action   *action)
{
    ShadingAction *pAct = dynamic_cast<ShadingAction *>(action);

    pAct->pop_matrix();

    return Action::Continue;
}


/*-------------------------------------------------------------------------*/
/*                                   init                                  */

void ShadingCallbacks::initialize(void)
{
    ShadingAction::registerEnterDefault( 
        Slices::getClassType(),
        osgTypedFunctionFunctor2CPtrRef<
            Action::ResultE      ,
            CNodePtr             ,
            Action               *>(
                &ShadingCallbacks::matDrawableRenderEnter));


    ShadingAction::registerEnterDefault(
        Geometry::getClassType(), 
        osgTypedFunctionFunctor2CPtrRef<
            Action::ResultE      , 
            CNodePtr             , 
            Action               *>(
                &ShadingCallbacks::matDrawableRenderEnter));


    ShadingAction::registerEnterDefault( 
        Particles::getClassType(),
        osgTypedFunctionFunctor2CPtrRef<
            Action::ResultE      ,
            CNodePtr             ,
            Action               *>(
                &ShadingCallbacks::matDrawableRenderEnter));


    ShadingAction::registerEnterDefault( 
        Group::getClassType(), 
        osgTypedFunctionFunctor2CPtrRef<
            Action::ResultE      ,
            CNodePtr             ,  
            Action               *>(&ShadingCallbacks::groupRenderEnter));

    ShadingAction::registerLeaveDefault( 
        Group::getClassType(), 
        osgTypedFunctionFunctor2CPtrRef<
            Action::ResultE      ,
            CNodePtr             ,  
            Action               *>(&ShadingCallbacks::groupRenderLeave));


    ShadingAction::registerEnterDefault(
        Billboard::getClassType(), 
        osgTypedFunctionFunctor2CPtrRef<
            Action::ResultE      ,
            CNodePtr             ,  
            Action               *>(&ShadingCallbacks::billboardRenderEnter));

    ShadingAction::registerLeaveDefault(
        Billboard::getClassType(), 
        osgTypedFunctionFunctor2CPtrRef<
            Action::ResultE,
            CNodePtr             ,  
            Action               *>(&ShadingCallbacks::billboardRenderLeave));


    ShadingAction::registerEnterDefault(
        ComponentTransform::getClassType(), 
        osgTypedFunctionFunctor2CPtrRef<
            Action::ResultE,
            CNodePtr             ,  
            Action               *>(&ShadingCallbacks::compTransRenderEnter));

    ShadingAction::registerLeaveDefault(
        ComponentTransform::getClassType(), 
        osgTypedFunctionFunctor2CPtrRef<
            Action::ResultE,
            CNodePtr             ,  
            Action               *>(&ShadingCallbacks::compTransRenderLeave));


    ShadingAction::registerEnterDefault(
        DistanceLOD::getClassType(),
        osgTypedFunctionFunctor2CPtrRef<
            Action::ResultE      ,
            CNodePtr             ,
            Action               *>(&ShadingCallbacks::distanceLODRender));


    ShadingAction::registerEnterDefault(
        MaterialGroup::getClassType(), 
        osgTypedFunctionFunctor2CPtrRef<
            Action::ResultE      ,
            CNodePtr             ,  
            Action               *>(&ShadingCallbacks::matGroupRenderEnter));

    ShadingAction::registerLeaveDefault(
        MaterialGroup::getClassType(), 
        osgTypedFunctionFunctor2CPtrRef<
            Action::ResultE      ,
            CNodePtr             ,  
            Action               *>(&ShadingCallbacks::matGroupRenderLeave));


    ShadingAction::registerEnterDefault(
        Switch::getClassType(),
        osgTypedFunctionFunctor2CPtrRef<
            Action::ResultE      ,
            CNodePtr             ,
            Action               *>(&ShadingCallbacks::switchRender));


    ShadingAction::registerEnterDefault(
        Transform::getClassType(), 
        osgTypedFunctionFunctor2CPtrRef<
            Action::ResultE      ,
            CNodePtr             ,  
            Action               *>(&ShadingCallbacks::transformRenderEnter));

    ShadingAction::registerLeaveDefault(
        Transform::getClassType(), 
        osgTypedFunctionFunctor2CPtrRef<
            Action::ResultE      ,
            CNodePtr             ,  
            Action               *>(&ShadingCallbacks::transformRenderLeave));


    ShadingAction::registerEnterDefault( 
        DirectionalLight::getClassType(), 
        osgTypedFunctionFunctor2CPtrRef<
            Action::ResultE      ,
            CNodePtr             ,  
            Action               *>(&ShadingCallbacks::dirlightRenderEnter));

    ShadingAction::registerLeaveDefault(
        DirectionalLight::getClassType(), 
        osgTypedFunctionFunctor2CPtrRef<
            OSG::Action::ResultE ,
            CNodePtr             ,  
            Action               *>(&ShadingCallbacks::dirlightRenderLeave));


    ShadingAction::registerEnterDefault( 
        PointLight::getClassType(), 
        osgTypedFunctionFunctor2CPtrRef<
            Action::ResultE      ,
            CNodePtr             ,  
            Action               *>(&ShadingCallbacks::pointlightRenderEnter));

    ShadingAction::registerLeaveDefault( 
        PointLight::getClassType(), 
        osgTypedFunctionFunctor2CPtrRef<
            Action::ResultE      ,
            CNodePtr             ,  
            Action               *>(&ShadingCallbacks::pointlightRenderLeave));


    ShadingAction::registerEnterDefault(
        SpotLight::getClassType(), 
        osgTypedFunctionFunctor2CPtrRef<
            Action::ResultE      ,
            CNodePtr             ,  
            Action               *>(&ShadingCallbacks::spotlightRenderEnter));

    ShadingAction::registerLeaveDefault( 
        SpotLight::getClassType(), 
        osgTypedFunctionFunctor2CPtrRef<
            Action::ResultE      ,
            CNodePtr             ,  
            Action               *>(&ShadingCallbacks::spotlightRenderLeave));
}


/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

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
    static Char8 cvsid_hpp[] = OSGSHADINGCALLBACKS_HEADER_CVSID;
//    static Char8 cvsid_inl[] = OSG_INLINE_CVSID;
}

