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
\*---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#define PRINT_MAT

#include "OSGConfig.h"

#include <OSGShadingAction.h>

#include <OSGWindow.h>
#include <OSGViewport.h>
#include <OSGCamera.h>
#include <OSGBackground.h>

#if 0
#include <OSGLog.h>
#include <OSGFieldContainer.h>
#include <OSGFieldContainerPtr.h>
#include <OSGNode.h>
#include <OSGNodeCore.h>
#include <OSGAction.h>

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
#endif

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/



/*! \brief the prototype which is copied to create new actions
 */

ShadingAction *ShadingAction::_pPrototype = NULL;

/*! \brief Default functors for instantiation
 */

std::vector<Action::Functor> *ShadingAction::_vDefaultEnterFunctors = NULL;
std::vector<Action::Functor> *ShadingAction::_vDefaultLeaveFunctors = NULL;


StatElemDesc<StatTimeElem> ShadingAction::statDrawTime(
    "shDrawTime", 
    "time for draw tree traversal");
StatElemDesc<StatIntElem > ShadingAction::statNMaterials(
    "shNMaterials", 
    "number of material changes");
StatElemDesc<StatIntElem > ShadingAction::statNMatrices(
    "shNMatrices",  
    "number of matrix changes");
StatElemDesc<StatIntElem > ShadingAction::statNGeometries(
    "shNGeometries", 
    "number of Geometry nodes");
StatElemDesc<StatIntElem > ShadingAction::statNTransGeometries(
    "shNTransGeometries",
    "number of transformed Geometry nodes");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/


/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*! \brief Default registration. static, so it can be called during static init
 */

void ShadingAction::registerEnterDefault(const FieldContainerType &type, 
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

void ShadingAction::registerLeaveDefault(const FieldContainerType &type, 
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

void ShadingAction::setPrototype(ShadingAction *pPrototype)
{
    _pPrototype = pPrototype;
}

ShadingAction *ShadingAction::getPrototype(void)
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

ShadingAction::ShadingAction(void) :
     Inherited           (     ),

    _uiMatrixId          (    0),

    _currMatrix          (     ),
    _camInverse          (     ),
    _accMatrix           (     ),

    _vMatrixStack        (     ),

    _uiActiveMatrix      (    0),

    _bSortTrans          (true ),
    _bZWriteTrans        (false),

    _uiNumMaterialChanges(    0),
    _uiNumMatrixChanges  (    0),
    _uiNumGeometries     (    0),
    _uiNumTransGeometries(    0)
{
    if(_vDefaultEnterFunctors != NULL)
        _enterFunctors = *_vDefaultEnterFunctors;

    if(_vDefaultLeaveFunctors != NULL)
        _leaveFunctors = *_vDefaultLeaveFunctors;
}


ShadingAction::ShadingAction(const ShadingAction &source) :
     Inherited           (source                      ),

    _uiMatrixId          (source._uiMatrixId          ),

    _currMatrix          (source._currMatrix          ),
    _camInverse          (source._camInverse          ),
    _accMatrix           (source._accMatrix           ),

    _vMatrixStack        (source._vMatrixStack        ),

    _uiActiveMatrix      (source._uiActiveMatrix      ),

    _bSortTrans          (source._bSortTrans          ),
    _bZWriteTrans        (source._bZWriteTrans        ),

    _uiNumMaterialChanges(source._uiNumMaterialChanges),
    _uiNumMatrixChanges  (source._uiNumMatrixChanges  ),
    _uiNumGeometries     (source._uiNumGeometries     ),
    _uiNumTransGeometries(source._uiNumTransGeometries)
{
}

ShadingAction *ShadingAction::create(void)
{
    ShadingAction *returnValue;
    
    if(_pPrototype)
    {
        returnValue = new ShadingAction(*_pPrototype);
    }
    else
    {
        returnValue = new ShadingAction();
    }

    return returnValue;
}


ShadingAction::~ShadingAction(void)
{
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

void ShadingAction::setMaterial(ShadingMaterial *pMaterial)
{
//    _pMaterial = pMaterial;
}

void ShadingAction::dropGeometry(ShadingGeometry *pGeo)
{
#if 0
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

        if(_pTransMatRoot->getFirstChild() == NULL)
        {
            _pTransMatRoot->addChild(pNewElem);
        }
        else
        {
            DrawTreeNode *pCurrent = _pTransMatRoot->getFirstChild();
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
                    _pTransMatRoot->insertFirstChild(       pNewElem);
                }
                else
                {
                    _pTransMatRoot->insertChildAfter(pLast, pNewElem);
                }
            }
            else
            {
                _pTransMatRoot->addChild(pNewElem);
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
            
            _mMatMap[pMat].push_back(pNewMatElem);
            
            pNewElem->setNode       (getActNode());
            
            pNewElem->setGeometry   (pGeo);
            pNewElem->setMatrixStore(_currMatrix);
            
            pNewMatElem->addChild(pNewElem);
            pNewMatElem->setState(pState);
            
            _pMatRoot->addChild(pNewMatElem);
        }
        else
        {
            std::vector<DrawTreeNode *>::iterator treesIt = it->second.begin();
            std::vector<DrawTreeNode *>::iterator treesEnd= it->second.end();
            
            pNewElem->setGeometry   (pGeo);
            pNewElem->setMatrixStore(_currMatrix);
            
            for(;treesIt != treesEnd; ++treesIt)
            {
                (*treesIt)->addChild(pNewElem);
            }
        }
    }
#endif

}

void ShadingAction::dropFunctor(Material::DrawFunctor &func, 
                                ShadingMaterial       *mat )
{
#if 0
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

        if(_pTransMatRoot->getFirstChild() == NULL)
        {
            _pTransMatRoot->addChild(pNewElem);
        }
        else
        {
            DrawTreeNode *pCurrent = _pTransMatRoot->getFirstChild();
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
                    _pTransMatRoot->insertFirstChild(       pNewElem);
                }
                else
                {
                    _pTransMatRoot->insertChildAfter(pLast, pNewElem);
                }
            }
            else
            {
                _pTransMatRoot->addChild(pNewElem);
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
            _mMatMap[pMat].push_back(pNewMatElem);
            
            pNewElem->setNode       (getActNode());
            
            pNewElem->setFunctor    (func);
            pNewElem->setMatrixStore(_currMatrix);
            
            pNewMatElem->addChild(pNewElem);
            pNewMatElem->setState(pState);
            
            _pMatRoot->addChild(pNewMatElem);
        }
        else
        {
            std::vector<DrawTreeNode *>::iterator treesIt = it->second.begin();
            std::vector<DrawTreeNode *>::iterator treesEnd= it->second.end();

            pNewElem->setFunctor    (func);
            pNewElem->setMatrixStore(_currMatrix);
            
            for(;treesIt != treesEnd; ++treesIt)
            {
                (*treesIt)->addChild(pNewElem);
            }
        }
    }
#endif
}

void ShadingAction::dropLight(Light *pLight)
{
#if 0
    if(pLight != NULL)
    {
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

        _vLights.push_back(oStore);
    }
#endif
}

bool ShadingAction::isVisible(Node *node)
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

/*-------------------------- your_category---------------------------------*/

#if 0
void ShadingAction::dump(DrawTreeNode *pRoot, UInt32 uiIndent)
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

//#define PRINT_MAT

void ShadingAction::draw(DrawTreeNode *pRoot)
{
    if(pRoot == NULL)
    {
        return;
    }

    UInt32 uiNextMatrix = pRoot->getMatrixStore().first;

    if(uiNextMatrix != 0 && uiNextMatrix != _uiActiveMatrix)
    {
        glLoadMatrixf(pRoot->getMatrixStore().second.getValues());

        _uiActiveMatrix = uiNextMatrix;

        _uiNumMatrixChanges++;

        _currMatrix.second = pRoot->getMatrixStore().second;

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
        pRoot->getGeometry()->drawPrimitives(this);

        _uiNumGeometries++;
    }
    else if(pRoot->hasFunctor())
    {
        pRoot->getFunctor().call(this);

        _uiNumGeometries++;
    }
    
    if(pRoot->getFirstChild() != NULL)
    {
        draw(pRoot->getFirstChild());
    }

    if(pRoot->getBrother() != NULL)
    {
        draw(pRoot->getBrother());
    }
}
#endif

void ShadingAction::setSortTrans(bool bVal)
{
    _bSortTrans = bVal;
}

void ShadingAction::setZWriteTrans(bool bVal)
{
    _bZWriteTrans = bVal;
}

// initialisation

Action::ResultE ShadingAction::start(void)
{
    Inherited::start();

    if(_window != NULL)
    {
        _window->resizeGL();
    }

    _uiMatrixId = 1;

    _currMatrix.first = 1;
    _currMatrix.second.setIdentity();

    bool full = true;
    
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

        if(full == false)
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

#if 0
    _mMatMap.clear();

#if defined(OSG_OPT_DRAWTREE)
    _pNodeFactory->freeAll();
#else
    subRefP(_pRoot);
    subRefP(_pMatRoot);
    subRefP(_pTransMatRoot);
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

#if defined(OSG_OPT_DRAWTREE)
    _pRoot = _pNodeFactory->create();
#else
    _pRoot         = new DrawTreeNode;
    addRefP(_pRoot);
#endif

#if defined(OSG_OPT_DRAWTREE)
    _pMatRoot = _pNodeFactory->create();
#else
    _pMatRoot      = new DrawTreeNode;

//    _pRoot->addChild(_pMatRoot);
    addRefP(_pMatRoot);
#endif

#if defined(OSG_OPT_DRAWTREE)
    _pTransMatRoot = _pNodeFactory->create();
#else
    _pTransMatRoot = new DrawTreeNode;

//    _pRoot->addChild(_pTransMatRoot);
    addRefP(_pTransMatRoot);
#endif

    _pActiveState   = NULL;

    _uiActiveMatrix = 0;

    _uiNumMaterialChanges = 0;
    _uiNumMatrixChanges   = 0;
    _uiNumGeometries      = 0;
    _uiNumTransGeometries = 0;

    _vLights.clear();
#endif

    if(_viewport != NULL && full == false)
    {
        glDisable(GL_SCISSOR_TEST);
    }

    return Action::Continue;
}

Action::ResultE ShadingAction::stop(ResultE res)
{
    if(!_ownStat)
       getStatistics()->getElem(statDrawTime)->start();

#if 0    
    UInt32 i;

//    dump(_pRoot, 0);
//    dump(_pMatRoot, 0);
//    dump(_pTransMatRoot, 0);

#if defined(OSG_OPT_DRAWTREE)
    //    _pNodeFactory->printStat();    
#endif

    for(i = 0; i < _vLights.size(); i++)
    {
        glLoadMatrixf(_vLights[i].second.getValues());
        _vLights[i].first->activate(this, i);
    }

    draw(_pMatRoot->getFirstChild());

    if(!_bZWriteTrans)
        glDepthMask(false);

    draw(_pTransMatRoot->getFirstChild());

    if(!_bZWriteTrans)
        glDepthMask(true);

    if(_pActiveState != NULL)
    {
        _pActiveState->deactivate(this);
    }

    for(i = 0; i < _vLights.size(); i++)
    {
        _vLights[i].first->deactivate(this, i);
    }

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
    

//    FINFO (("Material %d Matrix %d Geometry %d Transparent %d\r",
//            _uiNumMaterialChanges, 
//            _uiNumMatrixChanges, 
//            _uiNumGeometries,
//            _uiNumTransGeometries));
#endif

    Inherited::stop(res);
    return res;
}

void ShadingAction::push_matrix(const Matrix &matrix)
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

void ShadingAction::pop_matrix(void)
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

const Matrix &ShadingAction::top_matrix(void)
{
    _accMatrix = _camInverse;
    _accMatrix.mult(_currMatrix.second);

    return _accMatrix;
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

/*-------------------------- comparison -----------------------------------*/


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


std::vector<ShadingAction::Functor> *
    ShadingAction::getDefaultEnterFunctors(void)
{
    return _vDefaultEnterFunctors;
}

std::vector<ShadingAction::Functor> *
    ShadingAction::getDefaultLeaveFunctors(void)
{
    return _vDefaultLeaveFunctors;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

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
    static Char8 cvsid_hpp[] = OSGSHADINGACTION_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGSHADINGACTION_INLINE_CVSID;
}

