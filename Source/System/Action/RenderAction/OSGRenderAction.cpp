/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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
 *                                                                           *
\*---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

// enabled as default.
#ifndef OSG_OPT_DRAWTREE
#define OSG_OPT_DRAWTREE
#endif

#include <OSGLog.h>
#include <OSGFieldContainer.h>
#include <OSGFieldContainerPtr.h>
#include <OSGNode.h>
#include <OSGNodeCore.h>
#include <OSGAction.h>
#include <OSGRenderAction.h>
#include <OSGWindow.h>
#include <OSGCamera.h>
#include <OSGViewport.h>
#include <OSGBackground.h>

#include <OSGBaseFunctions.h>

#if defined(OSG_OPT_DRAWTREE)
# include <OSGDrawTreeNodeFactory.h>
#else
# include <OSGDrawTreeNode.h>
#endif

#include <OSGMaterial.h>

#include <OSGGeometry.h>
#include <OSGLog.h>

#include <OSGLight.h>

#include <OSGGL.h>
#include <OSGVolumeDraw.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::RenderAction
    \ingroup GrpSystemAction

    The render action class.

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char RenderAction::cvsid[] = "@(#)$Id: $";


/*! \brief the prototype which is copied to create new actions
 */

RenderAction *RenderAction::_pPrototype = NULL;

/*! \brief Default functors for instantiation
 */

std::vector<Action::Functor> *RenderAction::_vDefaultEnterFunctors = NULL;
std::vector<Action::Functor> *RenderAction::_vDefaultLeaveFunctors = NULL;


StatElemDesc<StatTimeElem> RenderAction::statDrawTime("drawTime", 
"time for draw tree traversal");
StatElemDesc<StatIntElem > RenderAction::statNMaterials("NMaterials", 
"number of material changes");
StatElemDesc<StatIntElem > RenderAction::statNMatrices("NMatrices",  
"number of matrix changes");
StatElemDesc<StatIntElem > RenderAction::statNGeometries("NGeometries", 
"number of Geometry nodes");
StatElemDesc<StatIntElem > RenderAction::statNTransGeometries("NTransGeometries",
"number of transformed Geometry nodes");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/



/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*! \brief Default registration. static, so it can be called during static init
 */

void RenderAction::registerEnterDefault(const FieldContainerType &type, 
                                        const Action::Functor    &func)
{
    if(_vDefaultEnterFunctors == NULL)
    {
        _vDefaultEnterFunctors = new std::vector<Action::Functor>;
    }

    while(type.getId() >= _vDefaultEnterFunctors->size())
    {
        _vDefaultEnterFunctors->push_back( 
            osgTypedFunctionFunctor2CPtrRef<
                ResultE, 
                CNodePtr,
                Action *                   >(&Action::_defaultEnterFunction));
    }
    
    (*_vDefaultEnterFunctors)[type.getId()] = func;
}

void RenderAction::registerLeaveDefault(const FieldContainerType &type, 
                                        const Action::Functor    &func)
{
    if(_vDefaultLeaveFunctors == NULL)
    {
        _vDefaultLeaveFunctors = new std::vector<Action::Functor>;
    }

    while(type.getId() >= _vDefaultLeaveFunctors->size())
    {
        _vDefaultLeaveFunctors->push_back( 
            osgTypedFunctionFunctor2CPtrRef<
                ResultE, 
                CNodePtr,
                Action *                   >(&Action::_defaultLeaveFunction));
    }
    
    (*_vDefaultLeaveFunctors)[type.getId()] = func;
}


/*! \brief  prototype access
 *  after setting the prototype all new DrawActions are clones of it
 */

void RenderAction::setPrototype(RenderAction *pPrototype)
{
    _pPrototype = pPrototype;
}

RenderAction *RenderAction::getPrototype(void)
{
    return _pPrototype;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/



/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

RenderAction::RenderAction(void) :
     Inherited           (),
#if defined(OSG_OPT_DRAWTREE)
    _pNodeFactory        (NULL),
#endif
    _pMaterial           (NULL),

    _uiMatrixId          (0),
    _currMatrix          (),
    _vMatrixStack        (),

    _mMatMap             (),

    _pMatRoots           (),
    _pTransMatRoots      (),

    _uiActiveMatrix      (0),
    _pActiveState        (NULL),

    _uiNumMaterialChanges(0),
    _uiNumMatrixChanges  (0),
    _uiNumGeometries     (0),
    _uiNumTransGeometries(0),

    _bSortTrans              (true),
    _bZWriteTrans            (false),
    _bLocalLights            (false),
    _bCorrectTwoSidedLighting(false),

    _vLights(),
    _lightsMap(),
    _lightsState(0),
    _activeLightsState(0),
    _activeLightsCount(0),
    _visibilityStack()
{
    if(_vDefaultEnterFunctors != NULL)
        _enterFunctors = *_vDefaultEnterFunctors;

    if(_vDefaultLeaveFunctors != NULL)
        _leaveFunctors = *_vDefaultLeaveFunctors;

#if defined(OSG_OPT_DRAWTREE)
    _pNodeFactory = new DrawTreeNodeFactory;
#endif
}


/** \brief Copy-Constructor
 */

RenderAction::RenderAction(const RenderAction &source) :
     Inherited           (source),
#if defined(OSG_OPT_DRAWTREE)
    _pNodeFactory        (NULL),
#endif
    _pMaterial           (source._pMaterial),

    _uiMatrixId          (source._uiMatrixId),
    _currMatrix          (source._currMatrix),
    _vMatrixStack        (source._vMatrixStack),

    _mMatMap             (source._mMatMap),

    _pMatRoots           (source._pMatRoots),
    _pTransMatRoots      (source._pTransMatRoots),

    _uiActiveMatrix      (source._uiActiveMatrix),
    _pActiveState        (source._pActiveState),

    _uiNumMaterialChanges(source._uiNumMaterialChanges),
    _uiNumMatrixChanges  (source._uiNumMatrixChanges),
    _uiNumGeometries     (source._uiNumGeometries),
    _uiNumTransGeometries(source._uiNumTransGeometries),

    _bSortTrans              (source._bSortTrans),
    _bZWriteTrans            (source._bZWriteTrans),
    _bLocalLights            (source._bLocalLights),
    _bCorrectTwoSidedLighting(source._bCorrectTwoSidedLighting),

    _vLights             (source._vLights),
    _lightsMap           (source._lightsMap),
    _lightsState         (source._lightsState),
    _activeLightsState   (source._activeLightsState),
    _activeLightsCount   (source._activeLightsCount),
    _visibilityStack     (source._visibilityStack)
{
#if defined(OSG_OPT_DRAWTREE)
    _pNodeFactory = new DrawTreeNodeFactory;
#endif
}

/** \brief create a new DrawAction by cloning the prototype
 */

RenderAction * RenderAction::create(void)
{
    RenderAction *returnValue;
    
    if(_pPrototype)
    {
        returnValue = new RenderAction(*_pPrototype);
    }
    else
    {
        returnValue = new RenderAction();
    }

    return returnValue;
}


/** \brief Destructor
 */

RenderAction::~RenderAction(void)
{
#if defined(OSG_OPT_DRAWTREE)
    delete _pNodeFactory;
#endif    
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

// rendering state handling

void RenderAction::setMaterial(Material *pMaterial)
{
    _pMaterial = pMaterial;
}

void RenderAction::dropGeometry(Geometry *pGeo)
{
    Material *pMat;
    State    *pState;

    if(pGeo == NULL)
    {
        return;
    }

    if(_pMaterial != NULL)
    {
        pMat = _pMaterial;
    }
    else if(pGeo->getMaterial() != NullFC)
    {
        pMat = pGeo->getMaterial().getCPtr();
    }
    else
    {
        return;
    }

    MaterialMap::iterator it        = _mMatMap.find(pMat);

#if 0
    pMat->rebuildState();
#endif

    UInt32 sortKey = pMat->getSortKey();

    pState = pMat->getState().getCPtr();

    if(_bSortTrans == true && pMat->isTransparent() == true)
    {
#if defined(OSG_OPT_DRAWTREE)
        DrawTreeNode *pNewElem = _pNodeFactory->create();
#else
        DrawTreeNode *pNewElem = new DrawTreeNode;
#endif

        Pnt3f         objPos;
            
        getActNode()->getVolume().getCenter(objPos);
        
        _currMatrix.second.mult(objPos);
            
        pNewElem->setNode       (getActNode());
            
        pNewElem->setGeometry   (pGeo);
        pNewElem->setMatrixStore(_currMatrix);
            
        pNewElem->setState      (pState);
        pNewElem->setScalar     (objPos[2]);
        pNewElem->setLightsState(_lightsState);

        UInt32 rsize = _pTransMatRoots.size();
        if(sortKey >= rsize)
        {
            _pTransMatRoots.resize(sortKey + 1);
            for(UInt32 i=rsize;i<sortKey;++i)
                _pTransMatRoots[i] = NULL;

#if defined(OSG_OPT_DRAWTREE)
            _pTransMatRoots[sortKey] = _pNodeFactory->create();
#else
            _pTransMatRoots[sortKey] =  new DrawTreeNode;
            addRefP(_pTransMatRoots[sortKey]);
#endif
        }

        if(_pTransMatRoots[sortKey]->getFirstChild() == NULL)
        {
            _pTransMatRoots[sortKey]->addChild(pNewElem);
        }
        else
        {
            DrawTreeNode *pCurrent = _pTransMatRoots[sortKey]->getFirstChild();
            DrawTreeNode *pLast    = NULL;
            bool          bFound   = false;

            do
            {

                if(pNewElem->getScalar() > pCurrent->getScalar())
                {
                    pLast    = pCurrent;
                    pCurrent = pCurrent->getBrother();
                }
                else
                {
                    bFound = true;
                }

            } while(bFound   == false && 
                    pCurrent != NULL    );
            
            
            if(bFound == true)
            {
                if(pLast == NULL)
                {
                    _pTransMatRoots[sortKey]->insertFirstChild(       pNewElem);
                }
                else
                {
                    _pTransMatRoots[sortKey]->insertChildAfter(pLast, pNewElem);
                }
            }
            else
            {
                _pTransMatRoots[sortKey]->addChild(pNewElem);
            }
        }


        _uiNumTransGeometries++;
    }
    else
    {
#if defined(OSG_OPT_DRAWTREE)
        DrawTreeNode *pNewElem = _pNodeFactory->create();
#else
        DrawTreeNode *pNewElem = new DrawTreeNode;
#endif
 
        if(it == _mMatMap.end())
        {
#if defined(OSG_OPT_DRAWTREE)
            DrawTreeNode *pNewMatElem = _pNodeFactory->create();
#else
            DrawTreeNode *pNewMatElem = new DrawTreeNode;
#endif
            
            //_mMatMap[pMat].push_back(pNewMatElem);
            _mMatMap[pMat] = pNewMatElem;
            
            pNewElem->setNode       (getActNode());           
            pNewElem->setGeometry   (pGeo);
            pNewElem->setMatrixStore(_currMatrix);
            pNewElem->setLightsState(_lightsState);

            pNewMatElem->addChild(pNewElem);
            pNewMatElem->setState(pState);
            
            //_pMatRoot->addChild(pNewMatElem);
            UInt32 rsize = _pMatRoots.size();
            if(sortKey >= rsize)
            {
                _pMatRoots.resize(sortKey + 1);
                for(UInt32 i=rsize;i<sortKey;++i)
                    _pMatRoots[i] = NULL;
                
#if defined(OSG_OPT_DRAWTREE)
                _pMatRoots[sortKey] = _pNodeFactory->create();
#else
                _pMatRoots[sortKey] =  new DrawTreeNode;
                addRefP(_pMatRoots[sortKey]);
#endif
            }
            _pMatRoots[sortKey]->addChild(pNewMatElem);
        }
        else
        {
            pNewElem->setNode       (getActNode());
            pNewElem->setGeometry   (pGeo);
            pNewElem->setMatrixStore(_currMatrix);
            pNewElem->setLightsState(_lightsState);

            it->second->addChild(pNewElem);
        }
    }
}

void RenderAction::dropFunctor(Material::DrawFunctor &func, Material *mat)
{
    Material *pMat;
    State    *pState;

    if(_pMaterial != NULL)
    {
        pMat = _pMaterial;
    }
    else if(mat != NULL)
    {
        pMat = mat;
    }
    else
    {
        return;
    }

    MaterialMap::iterator it        = _mMatMap.find(pMat);

#if 0
    pMat->rebuildState();
#endif

    UInt32 sortKey = pMat->getSortKey();

    pState = pMat->getState().getCPtr();

    if(_bSortTrans == true && pMat->isTransparent() == true)
    {
#if defined(OSG_OPT_DRAWTREE)
        DrawTreeNode *pNewElem = _pNodeFactory->create();
#else
        DrawTreeNode *pNewElem = new DrawTreeNode;
#endif

        Pnt3f         objPos;
            
        getActNode()->getVolume().getCenter(objPos);
        
        _currMatrix.second.mult(objPos);
            
        pNewElem->setNode       (getActNode());
            
        pNewElem->setFunctor    (func);
        pNewElem->setMatrixStore(_currMatrix);
            
        pNewElem->setState      (pState);
        pNewElem->setScalar     (objPos[2]);
        pNewElem->setLightsState(_lightsState);

        UInt32 rsize = _pTransMatRoots.size();
        if(sortKey >= rsize)
        {
            _pTransMatRoots.resize(sortKey + 1);
            for(UInt32 i=rsize;i<=sortKey;++i)
                _pTransMatRoots[i] = NULL;
        }
        
        if(_pTransMatRoots[sortKey] == NULL)
        {
#if defined(OSG_OPT_DRAWTREE)
            _pTransMatRoots[sortKey] = _pNodeFactory->create();
#else
            _pTransMatRoots[sortKey] =  new DrawTreeNode;
            addRefP(_pTransMatRoots[sortKey]);
#endif
        }

        if(_pTransMatRoots[sortKey]->getFirstChild() == NULL)
        {
            _pTransMatRoots[sortKey]->addChild(pNewElem);
        }
        else
        {
            DrawTreeNode *pCurrent = _pTransMatRoots[sortKey]->getFirstChild();
            DrawTreeNode *pLast    = NULL;
            bool          bFound   = false;

            do
            {

                if(pNewElem->getScalar() > pCurrent->getScalar())
                {
                    pLast    = pCurrent;
                    pCurrent = pCurrent->getBrother();
                }
                else
                {
                    bFound = true;
                }

            } while(bFound   == false && 
                    pCurrent != NULL    );
            
            
            if(bFound == true)
            {
                if(pLast == NULL)
                {
                    _pTransMatRoots[sortKey]->insertFirstChild(       pNewElem);
                }
                else
                {
                    _pTransMatRoots[sortKey]->insertChildAfter(pLast, pNewElem);
                }
            }
            else
            {
                _pTransMatRoots[sortKey]->addChild(pNewElem);
            }
        }


        _uiNumTransGeometries++;
    }
    else
    {
#if defined(OSG_OPT_DRAWTREE)
        DrawTreeNode *pNewElem = _pNodeFactory->create();
#else
        DrawTreeNode *pNewElem = new DrawTreeNode;
#endif 
       
        if(it == _mMatMap.end())
        {
#if defined(OSG_OPT_DRAWTREE)
            DrawTreeNode *pNewMatElem = _pNodeFactory->create();
#else
            DrawTreeNode *pNewMatElem = new DrawTreeNode;
#endif            
            //_mMatMap[pMat].push_back(pNewMatElem);
            _mMatMap[pMat] = pNewMatElem;

            pNewElem->setNode       (getActNode());            
            pNewElem->setFunctor    (func);
            pNewElem->setMatrixStore(_currMatrix);
            pNewElem->setLightsState(_lightsState);
            
            pNewMatElem->addChild(pNewElem);
            pNewMatElem->setState(pState);

            //_pMatRoot->addChild(pNewMatElem);
            UInt32 rsize = _pMatRoots.size();
            if(sortKey >= rsize)
            {
                _pMatRoots.resize(sortKey + 1);
                for(UInt32 i=rsize;i<=sortKey;++i)
                    _pMatRoots[i] = NULL;
            }

            if(_pMatRoots[sortKey] == NULL)
            {
#if defined(OSG_OPT_DRAWTREE)
                _pMatRoots[sortKey] = _pNodeFactory->create();
#else
                _pMatRoots[sortKey] =  new DrawTreeNode;
                addRefP(_pMatRoots[sortKey]);
#endif
            }
            _pMatRoots[sortKey]->addChild(pNewMatElem);
        }
        else
        {
            pNewElem->setNode       (getActNode());
            pNewElem->setFunctor    (func);
            pNewElem->setMatrixStore(_currMatrix);
            pNewElem->setLightsState(_lightsState);
            
            it->second->addChild(pNewElem);
        }
    }
}

void RenderAction::dropLight(Light *pLight)
{
    if(pLight == NULL)
        return;

    LightStore oStore;

    pLight->makeChunk();

    oStore.first  =  pLight->getChunk().getCPtr();
    oStore.second = _currMatrix.second;

    Matrix fromworld,tobeacon;
    
//        getActNode()->getToWorld(fromworld);

    fromworld = top_matrix();
    fromworld.invert();

    NodePtr beacon = pLight->getBeacon();

    if(beacon == NullFC)
    {
        SINFO << "draw: no beacon set!" << std::endl;
    }
    else
    {
        beacon->getToWorld(tobeacon);

        tobeacon.mult(fromworld);
        
        oStore.second.mult(tobeacon);
    }

    bool light_limit_reached = (_vLights.size() >= (sizeof(_lightsState) * 8));

    if(!light_limit_reached)
    {
        _vLights.push_back(oStore);
    }
    else
    {
        SWARNING << "RenderAction::dropLight: maximum light source limit is " << (sizeof(_lightsState) * 8)
                 << " skipping light sources!" << std::endl;
    }

    if(_bLocalLights)
    {
        UInt32 lightState = _vLights.size() - 1;
        if(!light_limit_reached)
        {
            _lightsMap[pLight] = lightState;
            _lightsState += (1 << lightState);
        }
    }
}

void RenderAction::undropLight(Light *pLight)
{
    if(pLight == NULL)
        return;

    if(!_bLocalLights)
        return;

    RenderAction::LightsMap::iterator it = _lightsMap.find(pLight);
    if(it == _lightsMap.end())
        return;
    
    _lightsState -= (1 << (*it).second);
}

bool RenderAction::isVisible( Node* node )
{
    if ( getFrustumCulling() == false )
        return true;
        
    getStatistics()->getElem(statCullTestedNodes)->inc();
    
    DynamicVolume vol;

//    node->getWorldVolume( vol );

    node->updateVolume();
    vol = node->getVolume();

    vol.transform(top_matrix());

    if ( _frustum.intersect( vol ) )
    {
// fprintf(stderr,"%p: node 0x%p vis\n", Thread::getCurrent(), node);
        return true;
    }
    
    getStatistics()->getElem(statCulledNodes)->inc();

// fprintf(stderr,"%p: node 0x%p invis\n", Thread::getCurrent(), node);
// _frustum.dump();
    return false;
}

//! enter a new level for visibility Return false if node is not visible, true
//  if it is.

bool RenderAction::pushVisibility(void)
{
    if(getFrustumCulling() == false)
        return true;
    
    FrustumVolume::PlaneSet inplanes = _visibilityStack.back();

    if(inplanes == FrustumVolume::P_ALL)
    {
        _visibilityStack.push_back(inplanes);
        return true;
    }

    Color3f col;
    bool result = true;
    
    NodePtr node = getActNode();
    
    DynamicVolume vol = node->getVolume(true);
    FrustumVolume frustum = _frustum;

#if 1
    vol.transform(top_matrix());
#else   
    // not quite working 
    Matrix m = top_matrix();
    m.invert();
    
    frustum.transform(m);
#endif

    getStatistics()->getElem(statCullTestedNodes)->inc();
    
    if ( !intersect( frustum, vol, inplanes ) )
    {
        result = false;
        col.setValuesRGB(1,0,0);
        getStatistics()->getElem(statCulledNodes)->inc();
        useNodeList(); // ignore all children
    }
    else
    {
        if(inplanes == FrustumVolume::P_ALL)
        {
            col.setValuesRGB(0,1,0);            
        }
        else
        {
            col.setValuesRGB(0,0,1);            
        }
    }

    if(getVolumeDrawing())
    {
        dropVolume(this, node, col);
    }

    _visibilityStack.push_back(inplanes);
    return result;
}

void RenderAction::popVisibility(void)
{
    if(getFrustumCulling() == false)
        return;

    _visibilityStack.pop_back();
}


/*-------------------------- your_category---------------------------------*/

void RenderAction::dump(DrawTreeNode *pRoot, UInt32 uiIndent)
{
    if(pRoot == NULL)
    {
        return;
    }

    indentLog(uiIndent, PWARNING);

    PWARNING << "Node : "   << pRoot                         << " | " 
             << "Geo : "    << pRoot->getGeometry()          << " | "
             << "State : "  << pRoot->getState()             << " | "
             << "Node : "   << pRoot->getNode()              << " | "
             << "Matrix : " << pRoot->getMatrixStore().first << std::endl;

    indentLog(uiIndent, PWARNING);
    PWARNING << "{" << std::endl;

    if(pRoot->getFirstChild() != NULL)
    {
        dump(pRoot->getFirstChild(), uiIndent + 4);
    }

    indentLog(uiIndent, PWARNING);
    PWARNING << "}" << std::endl;

    if(pRoot->getBrother() != NULL)
    {
        dump(pRoot->getBrother(), uiIndent);
    }
}

void RenderAction::activateLocalLights(DrawTreeNode *pRoot)
{
    //printf("lightsState: %d\n", pRoot->getLightsState());
    if(_activeLightsState == pRoot->getLightsState())
        return;

    // ok this is not optimal yet but it works.
    UInt32 light_id = 0;
    for(UInt32 i = 0;i < _vLights.size();++i)
    {
        if((_activeLightsState & (1 << i)) ==
           (pRoot->getLightsState() & (1 << i)))
        {
            if(_activeLightsState & (1 << i))
                ++light_id;
            continue;
        }
        
        if(pRoot->getLightsState() & (1 << i))
        {
            //printf("activate light: %u\n", light_id);
            glPushMatrix();
            glLoadMatrixf(_vLights[i].second.getValues());
            _vLights[i].first->activate(this, light_id++);
            glPopMatrix();
        }
    }
    
    for(UInt32 i = light_id;i < _activeLightsCount;++i)
    {
        //printf("deactivate light: %u\n", i);
        glDisable(GL_LIGHT0 + i);
    }

    _activeLightsState = pRoot->getLightsState();
    _activeLightsCount = light_id;
}

//#define PRINT_MAT

void RenderAction::draw(DrawTreeNode *pRoot)
{
    while(pRoot != NULL)
    {
        UInt32 uiNextMatrix = pRoot->getMatrixStore().first;

        if(uiNextMatrix != 0 && uiNextMatrix != _uiActiveMatrix)
        {
            glLoadMatrixf(pRoot->getMatrixStore().second.getValues());

            _uiActiveMatrix = uiNextMatrix;

            _uiNumMatrixChanges++;

            _currMatrix.second = pRoot->getMatrixStore().second;
            updateTopMatrix();

            // Negative scaled matrices in conjunction with double sided lighting
            // gives wrong render results cause the lighting itselfs gets inverted.
            // This corrects this behavior.
            if(_bCorrectTwoSidedLighting)
            {
                const Matrix &m = _currMatrix.second;
                // test for a "flipped" matrix
                // glFrontFace can give conflicts with the polygon chunk ...
                if(m[0].cross(m[1]).dot(m[2]) < 0.0)
                    glFrontFace(GL_CW);
                else
                    glFrontFace(GL_CCW);
            }
            
    #ifdef PRINT_MAT
            fprintf(stderr, "pushed to gl %d\n", _uiActiveMatrix);

            for(int i = 0; i < 4; i++)
            {
                fprintf(stderr, "% 5.2f % 5.2f % 5.2f % 5.2f\n",
                        pRoot->getMatrixStore().second[i][0],
                        pRoot->getMatrixStore().second[i][1],
                        pRoot->getMatrixStore().second[i][2],
                        pRoot->getMatrixStore().second[i][3]);
            }
    #endif
        }

        State *pNewState = pRoot->getState();

        if(pNewState != NULL)
        {
            if(_pActiveState != NULL)
            {
                if(pNewState != _pActiveState)
                {
                    pNewState->changeFrom(this, _pActiveState);

                    _pActiveState = pNewState;

                    _uiNumMaterialChanges++;
                }
            }
            else
            {
                _pActiveState = pRoot->getState();

                _pActiveState->activate(this);

                _uiNumMaterialChanges++;
            }
        }

        setActNode(pRoot->getNode());

        if(pRoot->getGeometry() != NULL)
        {
            if(_bLocalLights && _activeLightsState != pRoot->getLightsState())
                activateLocalLights(pRoot);
            pRoot->getGeometry()->drawPrimitives(this);

            _uiNumGeometries++;
        }
        else if(pRoot->hasFunctor())
        {
            if(_bLocalLights && _activeLightsState != pRoot->getLightsState())
                activateLocalLights(pRoot);
            pRoot->getFunctor().call(this);

            _uiNumGeometries++;
        }

        if(pRoot->getFirstChild() != NULL)
        {
            draw(pRoot->getFirstChild());
        }

        pRoot = pRoot->getBrother();
    }
}

void RenderAction::setSortTrans(bool bVal)
{
    _bSortTrans = bVal;
}

bool RenderAction::getSortTrans(void)
{
    return _bSortTrans;
}

void RenderAction::setZWriteTrans(bool bVal)
{
    _bZWriteTrans = bVal;
}

bool RenderAction::getZWriteTrans(void)
{
    return _bZWriteTrans;
}

void RenderAction::setLocalLights(bool bVal)
{
    _bLocalLights = bVal;
}

bool RenderAction::getLocalLights(void)
{
    return _bLocalLights;
}

void RenderAction::setCorrectTwoSidedLighting(bool bVal)
{
    _bCorrectTwoSidedLighting = bVal;
}

bool RenderAction::getCorrectTwoSidedLighting(void)
{
    return _bCorrectTwoSidedLighting;
}

// initialisation

Action::ResultE RenderAction::start(void)
{
    Inherited::start();

    if(_window != NULL)
    {
        _window->resizeGL();
    }

    _uiMatrixId = 1;

    _currMatrix.first = 1;
    _currMatrix.second.setIdentity();

    _visibilityStack.clear();
    _visibilityStack.push_back(FrustumVolume::P_NONE);
    
    bool full;
    
    if(_viewport != NULL)
    {
        GLint pl  = _viewport->getPixelLeft();
        GLint pr  = _viewport->getPixelRight();
        GLint pb  = _viewport->getPixelBottom();
        GLint pt  = _viewport->getPixelTop();
        GLint pw  = pr - pl + 1;
        GLint ph  = pt - pb + 1;
        
        full = _viewport->isFullWindow();

        glViewport(pl, pb, pw, ph);

        if (full == false)
        {
            glScissor (pl, pb, pw, ph);
            glEnable(GL_SCISSOR_TEST);
        }

        if(_camera != NULL)
        {
            _camera->setupProjection(this, *_viewport);

            // set the viewing
            
            _camera->getViewing(_currMatrix.second, 
                                _viewport->getPixelWidth (),
                                _viewport->getPixelHeight());

            _camInverse.invertFrom(_currMatrix.second);
            
            glMatrixMode(GL_MODELVIEW);
        }

        if(_background != NULL)
        {
            _background->clear(this, _viewport);
        }
    }
    
    updateTopMatrix();

    _mMatMap.clear();

#if defined(OSG_OPT_DRAWTREE)
    _pNodeFactory->freeAll();
#else
    for(UInt32 i=0;i<_pMatRoots.size();++i)
        subRefP(_pMatRoots[i]);
    for(UInt32 i=0;i<_pTransMatRoots.size();++i)
        subRefP(_pTransMatRoots[i]);
#endif

    /*
    if(_pRoot != NULL)
    {
        fprintf(stderr, "CDN %d DDN %d ODN %d ",
                DrawTreeNode::_iCreateCount,
                DrawTreeNode::_iDeleteCount,
                DrawTreeNode::_iCreateCount - DrawTreeNode::_iDeleteCount);
    }
    */

    DrawTreeNode::_iCreateCount = 0;
    DrawTreeNode::_iDeleteCount = 0;

    _pMatRoots.clear();
    _pTransMatRoots.clear();

    _pActiveState   = NULL;

    _uiActiveMatrix = 0;

    _uiNumMaterialChanges = 0;
    _uiNumMatrixChanges   = 0;
    _uiNumGeometries      = 0;
    _uiNumTransGeometries = 0;

    _vLights.clear();
    _lightsMap.clear();
    _lightsState       = 0;
    _activeLightsState = 0;
    _activeLightsCount = 0;

    if(_viewport != NULL && full == false)
    {
        glDisable(GL_SCISSOR_TEST);
    }

    return Action::Continue;
}

Action::ResultE RenderAction::stop(ResultE res)
{
   // CF changed
#if 0
    if(!_ownStat)
       getStatistics()->getElem(statDrawTime)->start();
#else
    getStatistics()->getElem(statDrawTime)->start();
#endif
    
    UInt32 i;

//    dump(_pMatRoot, 0);
//    dump(_pTransMatRoot, 0);

#if defined(OSG_OPT_DRAWTREE)
    //    _pNodeFactory->printStat();    
#endif

    if(!_bLocalLights)
    {
        for(i = 0; i < _vLights.size(); i++)
        {
            glLoadMatrixf(_vLights[i].second.getValues());
            _vLights[i].first->activate(this, i);
        }
    }

    UInt32 passes = osgMax(_pMatRoots.size(), _pTransMatRoots.size());
    
    for(UInt32 i=0;i<passes;++i)
    {
        //printf("activeLightsState1: %d\n", _activeLightsState);
        if(i < _pMatRoots.size() && _pMatRoots[i] != NULL)
            draw(_pMatRoots[i]->getFirstChild());
        //printf("activeLightsState2: %d\n", _activeLightsState);

        if(i < _pTransMatRoots.size() && _pTransMatRoots[i] != NULL)
        {
            if(!_bZWriteTrans)
                glDepthMask(false);
        
            draw(_pTransMatRoots[i]->getFirstChild());
        
            if(!_bZWriteTrans)
                glDepthMask(true);
        }
    }

    if(_pActiveState != NULL)
    {
        _pActiveState->deactivate(this);
    }

    if(!_bLocalLights)
    {
        for(i = 0; i < _vLights.size(); ++i)
        {
            _vLights[i].first->deactivate(this, i);
        }
    }
    else
    {
        for(UInt32 i = 0;i < _activeLightsCount;++i)
            glDisable(GL_LIGHT0 + i);
    }

    // CF changed
#if 0
    if(!_ownStat)
    {
        glFinish();
        getStatistics()->getElem(statDrawTime)->stop();

        getStatistics()->getElem(statNMaterials      )->set(
            _uiNumMaterialChanges);
        getStatistics()->getElem(statNMatrices       )->set(
            _uiNumMatrixChanges);
        getStatistics()->getElem(statNGeometries     )->set(
            _uiNumGeometries);
        getStatistics()->getElem(statNTransGeometries)->set(
            _uiNumTransGeometries);
    }
#else

    glFinish();

    StatTimeElem* elemDraw = getStatistics()->getElem(statDrawTime);
    elemDraw->stop();

    _viewport->setDrawTime((Real32)elemDraw->getTime());
    if(!_ownStat) {
        getStatistics()->getElem(statNMaterials      )->set(
            _uiNumMaterialChanges);
        getStatistics()->getElem(statNMatrices       )->set(
            _uiNumMatrixChanges);
        getStatistics()->getElem(statNGeometries     )->set(
            _uiNumGeometries);
        getStatistics()->getElem(statNTransGeometries)->set(
            _uiNumTransGeometries);
    }
#endif


//    FINFO (("Material %d Matrix %d Geometry %d Transparent %d\r",
//            _uiNumMaterialChanges, 
//            _uiNumMatrixChanges, 
//            _uiNumGeometries,
//            _uiNumTransGeometries));

    Inherited::stop(res);
    return res;
}

void RenderAction::push_matrix(const Matrix &matrix)
{
    _vMatrixStack.push_back(_currMatrix);
    
#ifdef PRINT_MAT
    fprintf(stderr, "pushed %d\n", _currMatrix.first);

    for(int i = 0; i < 4; i++)
    {
        fprintf(stderr, "% 5.2f % 5.2f % 5.2f % 5.2f\n",
                _currMatrix.second[i][0],
                _currMatrix.second[i][1],
                _currMatrix.second[i][2],
                _currMatrix.second[i][3]);
    }
#endif

    _currMatrix.first = ++_uiMatrixId;
    _currMatrix.second.mult(matrix);
    updateTopMatrix();
    
#ifdef PRINT_MAT
    fprintf(stderr, "current %d\n", _currMatrix.first);

    for(int i = 0; i < 4; i++)
    {
        fprintf(stderr, "% 5.2f % 5.2f % 5.2f % 5.2f\n",
                _currMatrix.second[i][0],
                _currMatrix.second[i][1],
                _currMatrix.second[i][2],
                _currMatrix.second[i][3]);
    }
#endif
}

void RenderAction::pop_matrix(void)
{
#ifdef PRINT_MAT
    fprintf(stderr, "pop %d\n", _currMatrix.first);

    for(int i = 0; i < 4; i++)
    {
        fprintf(stderr, "% 5.2f % 5.2f % 5.2f % 5.2f\n",
                _currMatrix.second[i][0],
                _currMatrix.second[i][1],
                _currMatrix.second[i][2],
                _currMatrix.second[i][3]);
    }
#endif

    _currMatrix.first  = _vMatrixStack.back().first;
    _currMatrix.second = _vMatrixStack.back().second;
    updateTopMatrix();

    _vMatrixStack.pop_back();

#ifdef PRINT_MAT
    fprintf(stderr, "current %d\n", _currMatrix.first);

    for(int i = 0; i < 4; i++)
    {
        fprintf(stderr, "% 5.2f % 5.2f % 5.2f % 5.2f\n",
                _currMatrix.second[i][0],
                _currMatrix.second[i][1],
                _currMatrix.second[i][2],
                _currMatrix.second[i][3]);
    }
#endif
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

/*-------------------------- comparison -----------------------------------*/


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


std::vector<RenderAction::Functor> *RenderAction::getDefaultEnterFunctors(void)
{
    return _vDefaultEnterFunctors;
}

std::vector<RenderAction::Functor> *RenderAction::getDefaultLeaveFunctors(void)
{
    return _vDefaultLeaveFunctors;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/



///---------------------------------------------------------------------------
///  FUNCTION: 
///---------------------------------------------------------------------------
//:  Example for the head comment of a function
///---------------------------------------------------------------------------
///
//p: Paramaters: 
//p: 
///
//g: GlobalVars:
//g: 
///
//r: Return:
//r: 
///
//c: Caution:
//c: 
///
//a: Assumptions:
//a: 
///
//d: Description:
//d: 
///
//s: SeeAlso:
//s: 
///---------------------------------------------------------------------------

