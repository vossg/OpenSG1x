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
#include <OSGGLEXT.h>

#include <OSGBaseFunctions.h>

#include <OSGDrawTreeNodeFactory.h>

#include <OSGMaterial.h>
#include <OSGMultiPassMaterial.h>

#include <OSGGeometry.h>
#include <OSGLog.h>

#include <OSGLight.h>
#include <OSGLightEnv.h>

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
StatElemDesc<StatIntOnceElem > RenderAction::statNTextures("NTextures",
"number of texture changes");
StatElemDesc<StatIntOnceElem > RenderAction::statNTexBytes("NTexBytes",
"sum of all used textures' sizes (approx., in bytes)");


UInt32 RenderAction::_arbOcclusionQuery;
UInt32 RenderAction::_funcGenQueriesARB         = Window::invalidFunctionID;
UInt32 RenderAction::_funcDeleteQueriesARB      = Window::invalidFunctionID;
UInt32 RenderAction::_funcBeginQueryARB         = Window::invalidFunctionID;
UInt32 RenderAction::_funcEndQueryARB           = Window::invalidFunctionID;
UInt32 RenderAction::_funcGetQueryObjectuivARB  = Window::invalidFunctionID;

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
    _pNodeFactory        (NULL),

    _uiMatrixId          (0),
    _currMatrix          (),
    _vMatrixStack        (),

    _mMatMap             (),

    _pMatRoots           (),
    _pTransMatRoots      (),
    _pNoStateSortRoot    (NULL),
    _pNoStateSortTransRoot(NULL),

    _ocRoot              (),
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
    _bOcclusionCulling       (false),

    _vLights(),
    _lightsMap(),
    _lightsState(0),
    _activeLightsState(0),
    _activeLightsCount(0),
    _activeLightsMask(0),

    _lightsTable(),
    _lightsPath(),
    _lightEnvsLightsState(),

    _stateSorting(true),
    _visibilityStack(),

    _occlusionQuery         (0),
    _glGenQueriesARB        (NULL),
    _glDeleteQueriesARB     (NULL),
    _glBeginQueryARB        (NULL),
    _glEndQueryARB          (NULL),
    _glGetQueryObjectuivARB (NULL)
{
    if(_vDefaultEnterFunctors != NULL)
        _enterFunctors = *_vDefaultEnterFunctors;

    if(_vDefaultLeaveFunctors != NULL)
        _leaveFunctors = *_vDefaultLeaveFunctors;

    _pNodeFactory = new DrawTreeNodeFactory;

    _arbOcclusionQuery          = Window::registerExtension("GL_ARB_occlusion_query");
    _funcGenQueriesARB          = Window::registerFunction (OSG_DLSYM_UNDERSCORE"glGenQueriesARB");
    _funcDeleteQueriesARB       = Window::registerFunction (OSG_DLSYM_UNDERSCORE"glDeleteQueriesARB");
    _funcBeginQueryARB          = Window::registerFunction (OSG_DLSYM_UNDERSCORE"glBeginQueryARB");
    _funcEndQueryARB            = Window::registerFunction (OSG_DLSYM_UNDERSCORE"glEndQueryARB");
    _funcGetQueryObjectuivARB   = Window::registerFunction (OSG_DLSYM_UNDERSCORE"glGetQueryObjectuivARB");
}


/** \brief Copy-Constructor
 */

RenderAction::RenderAction(const RenderAction &source) :
     Inherited           (source),
    _pNodeFactory        (NULL),

    _uiMatrixId          (source._uiMatrixId),
    _currMatrix          (source._currMatrix),
    _vMatrixStack        (source._vMatrixStack),

    _mMatMap             (source._mMatMap),

    _pMatRoots           (source._pMatRoots),
    _pTransMatRoots      (source._pTransMatRoots),
    _pNoStateSortRoot    (source._pNoStateSortRoot),
    _pNoStateSortTransRoot(source._pNoStateSortTransRoot),

    _ocRoot              (source._ocRoot),

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
    _bOcclusionCulling       (source._bOcclusionCulling),

    _vLights             (source._vLights),
    _lightsMap           (source._lightsMap),
    _lightsState         (source._lightsState),
    _activeLightsState   (source._activeLightsState),
    _activeLightsCount   (source._activeLightsCount),
    _activeLightsMask    (source._activeLightsMask),

    _lightsTable         (source._lightsTable),
    _lightsPath          (source._lightsPath),
    _lightEnvsLightsState(source._lightEnvsLightsState),

    _stateSorting        (source._stateSorting),
    _visibilityStack     (source._visibilityStack),
    
    _occlusionQuery         (source._occlusionQuery),
    _glGenQueriesARB        (source._glGenQueriesARB),
    _glDeleteQueriesARB     (source._glDeleteQueriesARB),
    _glBeginQueryARB        (source._glBeginQueryARB),
    _glEndQueryARB          (source._glEndQueryARB),
    _glGetQueryObjectuivARB (source._glGetQueryObjectuivARB)
{
    _pNodeFactory = new DrawTreeNodeFactory;
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
    delete _pNodeFactory;

    if(_occlusionQuery != 0)
        _glDeleteQueriesARB(1, &_occlusionQuery);
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

// rendering state handling

void RenderAction::dropGeometry(Geometry *pGeo)
{
    Material *pMat;
    State    *pState;

    if(pGeo == NULL)
    {
        return;
    }

    if(getMaterial() != NULL)
    {
        pMat = getMaterial();
    }
    else if(pGeo->getMaterial() != NullFC)
    {
        pMat = pGeo->getMaterial().getCPtr();
    }
    else
    {
        return;
    }

    UInt32 mpMatPasses = 1;
    MultiPassMaterial *pMPMat = dynamic_cast<MultiPassMaterial *>(pMat);
    if(pMPMat != NULL)
        mpMatPasses = pMPMat->getNPasses();

    Int32 sortKey = pMat->getSortKey();

    if(!_stateSorting ||
       (sortKey == Material::NoStateSorting && 
        (!_bSortTrans || !pMat->isTransparent())))
    {
        for(UInt32 mpi=0;mpi<mpMatPasses;++mpi)
        {
            if(pMPMat != NULL)
                pState = pMPMat->getState(mpi).getCPtr();
            else
                pState = pMat->getState().getCPtr();

            DrawTreeNode *pNewElem = _pNodeFactory->create();
    
            pNewElem->setNode       (getActNode());
            pNewElem->setGeometry   (pGeo);
            pNewElem->setMatrixStore(_currMatrix);
            pNewElem->setLightsState(_lightsState);
            pNewElem->setState(pMat->getState().getCPtr());
            if(sortKey == Material::NoStateSorting)
                pNewElem->setNoStateSorting();
        
            if(pMPMat != NULL)
            {
                if(mpi == mpMatPasses-1)
                    pNewElem->setLastMultiPass();
                else
                    pNewElem->setMultiPass();
            }

            if(!pMat->isTransparent())
            {
                if(_pNoStateSortRoot == NULL)
                    _pNoStateSortRoot = pNewElem;
                else
                    _pNoStateSortRoot->addChild(pNewElem);
            }
            else
            {
                if(_pNoStateSortTransRoot == NULL)
                    _pNoStateSortTransRoot = pNewElem;
                else
                    _pNoStateSortTransRoot->addChild(pNewElem);
            }
        }
        return;
    }

    MaterialMap::iterator it        = _mMatMap.find(pMat);

#if 0
    pMat->rebuildState();
#endif

    if(sortKey == Material::NoStateSorting)
        sortKey = 0;

    DrawTreeNode *pLastMultiPass = NULL;

    for(UInt32 mpi=0;mpi<mpMatPasses;++mpi)
    {
        if(pMPMat != NULL)
            pState = pMPMat->getState(mpi).getCPtr();
        else
            pState = pMat->getState().getCPtr();

        if(_bSortTrans && pMat->isTransparent())
        {
            DrawTreeNode *pNewElem = _pNodeFactory->create();
            Pnt3f         objPos;
            getActNode()->getVolume().getCenter(objPos);

            _currMatrix.second.mult(objPos);

            pNewElem->setNode       (getActNode());
                
            pNewElem->setGeometry   (pGeo);
            pNewElem->setMatrixStore(_currMatrix);
                
            pNewElem->setState      (pState);
            pNewElem->setScalar     (objPos[2]);
            pNewElem->setLightsState(_lightsState);

            if(pMPMat != NULL)
            {
                if(mpi == mpMatPasses-1)
                    pNewElem->setLastMultiPass();
                else
                    pNewElem->setMultiPass();
            }

            if(_pTransMatRoots.find(sortKey) == _pTransMatRoots.end())
            {
                TransSortMap ts;
                _pTransMatRoots.insert(std::make_pair(sortKey, ts));
            }

            TransSortMap &ts = _pTransMatRoots[sortKey];
            TransSortMap::iterator it = ts.find(pNewElem->getScalar());
            if(it == ts.end())
                ts.insert(std::make_pair(pNewElem->getScalar(), pNewElem));
            else
                (*it).second->addChild(pNewElem);

            _uiNumTransGeometries++;
        }
        else
        {
            DrawTreeNode *pNewElem = _pNodeFactory->create();
     
            if(it == _mMatMap.end())
            {
                DrawTreeNode *pNewMatElem = _pNodeFactory->create();
    
                //_mMatMap[pMat].push_back(pNewMatElem);
                _mMatMap[pMat] = pNewMatElem;
                
                pNewElem->setNode       (getActNode());           
                pNewElem->setGeometry   (pGeo);
                pNewElem->setMatrixStore(_currMatrix);
                pNewElem->setLightsState(_lightsState);
    
                if(pMPMat != NULL)
                {
                    // for multipass we have a different state in all draw node
                    // children.
                    pNewElem->setState(pState);

                    if(mpi == mpMatPasses-1)
                        pNewElem->setLastMultiPass();
                    else
                        pNewElem->setMultiPass();
                }
                else
                {
                    // for non multipass materials there is only one state
                    // for all draw node children.
                    pNewMatElem->setState(pState);
                }

                pNewMatElem->addChild(pNewElem);
                pNewMatElem->setNode(getActNode());
                pNewMatElem->setLightsState(_lightsState);

                if(_pMatRoots.find(sortKey) == _pMatRoots.end())
                    _pMatRoots.insert(std::make_pair(sortKey, _pNodeFactory->create()));

                _pMatRoots[sortKey]->addChild(pNewMatElem);
            }
            else
            {
                pNewElem->setNode       (getActNode());
                pNewElem->setGeometry   (pGeo);
                pNewElem->setMatrixStore(_currMatrix);
                pNewElem->setLightsState(_lightsState);
    
                if(pMPMat != NULL)
                {
                    pNewElem->setState(pState);

                    if(mpi == mpMatPasses-1)
                        pNewElem->setLastMultiPass();
                    else
                        pNewElem->setMultiPass();
                }

                it->second->addChild(pNewElem);
            }
        }
    } // multipass
}

void RenderAction::dropFunctor(Material::DrawFunctor &func, Material *mat)
{
    Material *pMat;
    State    *pState;

    if(getMaterial() != NULL)
    {
        pMat = getMaterial();
    }
    else if(mat != NULL)
    {
        pMat = mat;
    }
    else
    {
        return;
    }

    UInt32 mpMatPasses = 1;
    MultiPassMaterial *pMPMat = dynamic_cast<MultiPassMaterial *>(pMat);
    if(pMPMat != NULL)
        mpMatPasses = pMPMat->getNPasses();

    Int32 sortKey = pMat->getSortKey();

    if(_bOcclusionCulling && _stateSorting)
    {
        DrawTreeNode *pLastMultiPass = NULL;
        for(UInt32 mpi=0;mpi<mpMatPasses;++mpi)
        {
            if(pMPMat != NULL)
                pState = pMPMat->getState(mpi).getCPtr();
            else
                pState = pMat->getState().getCPtr();

            DrawTreeNode *pNewElem = _pNodeFactory->create();

            pNewElem->setNode       (getActNode());
            pNewElem->setFunctor    (func);
            pNewElem->setMatrixStore(_currMatrix);
            pNewElem->setLightsState(_lightsState);
            pNewElem->setState      (pState);
            if(sortKey == Material::NoStateSorting)
                pNewElem->setNoStateSorting();

            if(pMPMat != NULL)
            {
                if(mpi == mpMatPasses-1)
                    pNewElem->setLastMultiPass();
                else
                    pNewElem->setMultiPass();
            }

            if(!pMat->isTransparent())
            {
                if(sortKey == 0)
                {
                    Pnt3f objPos;
                    //const Volume &vol = getActNode()->getVolume();
                    //vol.getCenter(objPos);
                    //_currMatrix.second.mult(objPos);

                    // we don't want the center we use the front most
                    // z value for the sorting.
                    DynamicVolume vol = getActNode()->getVolume();
                    vol.transform(_currMatrix.second);
                    objPos = vol.getMax();

                    pNewElem->setScalar(objPos[2]);

                    OCMap::iterator it = _ocRoot.find(pNewElem->getScalar());
                    if(it == _ocRoot.end())
                        _ocRoot.insert(std::make_pair(pNewElem->getScalar(), pNewElem));
                    else
                        (*it).second->addChild(pNewElem);
                }
                else
                {
                    if(_pMatRoots.find(sortKey) == _pMatRoots.end())
                        _pMatRoots.insert(std::make_pair(sortKey, _pNodeFactory->create()));

                    _pMatRoots[sortKey]->addChild(pNewElem);
                }
            }
            else
            {
                if(_bSortTrans)
                {
                    Pnt3f objPos;
                    getActNode()->getVolume().getCenter(objPos);
                    _currMatrix.second.mult(objPos);
                    pNewElem->setScalar(objPos[2]);

                    if(pMPMat != NULL)
                    {
                        if(mpi == mpMatPasses-1)
                            pNewElem->setLastMultiPass();
                        else
                            pNewElem->setMultiPass();
                    }
        
                    if(_pTransMatRoots.find(sortKey) == _pTransMatRoots.end())
                    {
                        TransSortMap ts;
                        _pTransMatRoots.insert(std::make_pair(sortKey, ts));
                    }
        
                    TransSortMap &ts = _pTransMatRoots[sortKey];
                    TransSortMap::iterator it = ts.find(pNewElem->getScalar());
                    if(it == ts.end())
                        ts.insert(std::make_pair(pNewElem->getScalar(), pNewElem));
                    else
                        (*it).second->addChild(pNewElem);

                    _uiNumTransGeometries++;
                }
                else
                {
                    if(_pNoStateSortTransRoot == NULL)
                        _pNoStateSortTransRoot = pNewElem;
                    else
                        _pNoStateSortTransRoot->addChild(pNewElem);
                }
            }
        }
        return;
    }

    if(!_stateSorting ||
       (sortKey == Material::NoStateSorting && 
        (!_bSortTrans || !pMat->isTransparent())))
    {
        for(UInt32 mpi=0;mpi<mpMatPasses;++mpi)
        {
            if(pMPMat != NULL)
                pState = pMPMat->getState(mpi).getCPtr();
            else
                pState = pMat->getState().getCPtr();

            DrawTreeNode *pNewElem = _pNodeFactory->create();

            pNewElem->setNode       (getActNode());
            pNewElem->setFunctor    (func);
            pNewElem->setMatrixStore(_currMatrix);
            pNewElem->setLightsState(_lightsState);
            pNewElem->setState(pState);
            if(sortKey == Material::NoStateSorting)
                pNewElem->setNoStateSorting();

            if(pMPMat != NULL)
            {
                if(mpi == mpMatPasses-1)
                    pNewElem->setLastMultiPass();
                else
                    pNewElem->setMultiPass();
            }

            if(!pMat->isTransparent())
            {
                if(_pNoStateSortRoot == NULL)
                    _pNoStateSortRoot = pNewElem;
                else
                    _pNoStateSortRoot->addChild(pNewElem);
            }
            else
            {
                if(_pNoStateSortTransRoot == NULL)
                    _pNoStateSortTransRoot = pNewElem;
                else
                    _pNoStateSortTransRoot->addChild(pNewElem);
            }
        }

        return;
    }

    MaterialMap::iterator it        = _mMatMap.find(pMat);

#if 0
    pMat->rebuildState();
#endif

    if(sortKey == Material::NoStateSorting)
        sortKey = 0;

    DrawTreeNode *pLastMultiPass = NULL;

    for(UInt32 mpi=0;mpi<mpMatPasses;++mpi)
    {
        if(pMPMat != NULL)
            pState = pMPMat->getState(mpi).getCPtr();
        else
            pState = pMat->getState().getCPtr();

        if(_bSortTrans && pMat->isTransparent())
        {
            DrawTreeNode *pNewElem = _pNodeFactory->create();
            Pnt3f         objPos;
            getActNode()->getVolume().getCenter(objPos);

            _currMatrix.second.mult(objPos);

            pNewElem->setNode       (getActNode());
                
            pNewElem->setFunctor    (func);
            pNewElem->setMatrixStore(_currMatrix);
                
            pNewElem->setState      (pState);
            pNewElem->setScalar     (objPos[2]);
            pNewElem->setLightsState(_lightsState);

            if(pMPMat != NULL)
            {
                if(mpi == mpMatPasses-1)
                    pNewElem->setLastMultiPass();
                else
                    pNewElem->setMultiPass();
            }

            if(_pTransMatRoots.find(sortKey) == _pTransMatRoots.end())
            {
                TransSortMap ts;
                _pTransMatRoots.insert(std::make_pair(sortKey, ts));
            }

            TransSortMap &ts = _pTransMatRoots[sortKey];
            TransSortMap::iterator it = ts.find(pNewElem->getScalar());
            if(it == ts.end())
                ts.insert(std::make_pair(pNewElem->getScalar(), pNewElem));
            else
                (*it).second->addChild(pNewElem);

            _uiNumTransGeometries++;
        }
        else
        {
            DrawTreeNode *pNewElem = _pNodeFactory->create();

            if(it == _mMatMap.end())
            {
                DrawTreeNode *pNewMatElem = _pNodeFactory->create();
                //_mMatMap[pMat].push_back(pNewMatElem);
                _mMatMap[pMat] = pNewMatElem;

                pNewElem->setNode       (getActNode());
                pNewElem->setFunctor    (func);
                pNewElem->setMatrixStore(_currMatrix);
                pNewElem->setLightsState(_lightsState);
                
                if(pMPMat != NULL)
                {
                    // for multipass we have a different state in all draw node
                    // children.
                    pNewElem->setState(pState);

                    if(mpi == mpMatPasses-1)
                        pNewElem->setLastMultiPass();
                    else
                        pNewElem->setMultiPass();
                }
                else
                {
                    // for non multipass materials there is only one state
                    // for all draw node children.
                    pNewMatElem->setState(pState);
                }

                pNewMatElem->addChild(pNewElem);
                pNewMatElem->setNode(getActNode());
                pNewMatElem->setLightsState(_lightsState);

                //_pMatRoot->addChild(pNewMatElem);

                if(_pMatRoots.find(sortKey) == _pMatRoots.end())
                    _pMatRoots.insert(std::make_pair(sortKey, _pNodeFactory->create()));

                _pMatRoots[sortKey]->addChild(pNewMatElem);
            }
            else
            {
                pNewElem->setNode       (getActNode());
                pNewElem->setFunctor    (func);
                pNewElem->setMatrixStore(_currMatrix);
                pNewElem->setLightsState(_lightsState);
                
                // FIXME call pNewElem->setState(pState); if the _lightsState
                // is different to the one from the last added child! Without it
                // activate or changeFrom is never called and the OSGActiveLightsMask in
                // the SHLChunk never updated.

                if(pMPMat != NULL)
                {
                    // for multipass we have a different state in all draw node
                    // children.
                    pNewElem->setState(pState);

                    if(mpi == mpMatPasses-1)
                        pNewElem->setLastMultiPass();
                    else
                        pNewElem->setMultiPass();
                }
                
                it->second->addChild(pNewElem);
            }
        }
    } // multipass
}

void RenderAction::dropLight(Light *pLight)
{
    if(pLight == NULL)
        return;

    LightStore oStore;

    pLight->makeChunk();

    oStore.first  =  pLight->getChunk().getCPtr();
//    oStore.second = _currMatrix.second;

    Matrix fromworld,tobeacon;
    
//        getActNode()->getToWorld(fromworld);

//    fromworld = top_matrix();

    NodePtr beacon = pLight->getBeacon();

    if(beacon == NullFC)
    {
        SINFO << "draw: no beacon set!" << std::endl;

        oStore.second = _currMatrix.second;
    }
    else
    {
        fromworld = _camInverse;
        fromworld.invert();

        beacon->getToWorld(tobeacon);

//        tobeacon.mult(fromworld);
        
        fromworld.mult(tobeacon);

        oStore.second = fromworld;
    }

    if(!_bLocalLights && _vLights.size() >= 8)
    {
        SWARNING << "RenderAction::dropLight: maximum light source limit is " <<  8
                 << " skipping light sources!" << std::endl;
    }

    _vLights.push_back(oStore);
    _lightsMap.push_back(pLight);

    if(_bLocalLights)
    {
        // light id's are in the range from 1 - N
        UInt32 lightState = _vLights.size();
        _lightsPath.push_back(lightState);
        // add current lights path to the lights table.
        _lightsTable.push_back(_lightsPath);
        _lightsState = lightState;
    }
}

void RenderAction::undropLight(Light *pLight)
{
    if(pLight == NULL)
        return;

    if(!_bLocalLights)
        return;

    if(_lightEnvsLightsState.empty())
        _lightsPath.pop_back();
}

void RenderAction::dropLightEnv(LightEnv *pLightEnv)
{
    if(pLightEnv == NULL)
        return;

    if(!_bLocalLights)
        return;

    _lightEnvsLightsState.push_back(_lightsState);
}

void RenderAction::undropLightEnv(LightEnv *pLightEnv)
{
    if(pLightEnv == NULL)
        return;

    if(!_bLocalLights)
        return;

    _lightsState = _lightEnvsLightsState.back();
    if(_lightsState > 0)
        _lightsPath = _lightsTable[_lightsState - 1];
    else
        _lightsPath.clear();
    _lightEnvsLightsState.pop_back();
}

std::vector<Light *> RenderAction::getActiveLights(void)
{
    std::vector<Light *> lights;
    if(_bLocalLights)
    {
        if(_activeLightsState > 0)
        {
            const std::vector<UInt32> &light_ids = _lightsTable[_activeLightsState - 1];
        
            for(UInt32 i=0;i<light_ids.size();++i)
            {
                UInt32 light_id = light_ids[i];
                if(light_id > 0 && light_id <= _lightsMap.size())
                    lights.push_back(_lightsMap[light_id - 1]);
            }
        }
    }
    else
    {
        return _lightsMap;
    }
    return lights;
}

bool RenderAction::isVisible( Node* node )
{
    if ( getFrustumCulling() == false )
        return true;

    // HACK but light sources beneath a LightEnv node can also
    // light it's brothers or parents.
    // It is not as bad as it looks like, the isVisible() method is only
    // used for Switch, DistanceLOD and ProxyGroup ...
    if(!_lightEnvsLightsState.empty())
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
    //printf("lightsState: %u %u\n", _activeLightsState, pRoot->getLightsState());
    if(_activeLightsState == pRoot->getLightsState())
        return;

    UInt32 light_id = 0;
    if(pRoot->getLightsState() > 0)
    {
        _activeLightsMask = 0;
        const std::vector<UInt32> &lights = _lightsTable[pRoot->getLightsState() - 1];

        //printf("activate lights: %u : ", pRoot->getLightsState() - 1);
        for(UInt32 i=0;i<lights.size();++i)
        {
            UInt32 light_index = lights[i] - 1;
            glPushMatrix();
            glLoadMatrixf(_vLights[light_index].second.getValues());
            _activeLightsMask |= (1 << light_id);
            //printf("%u,", light_id);
            _vLights[light_index].first->activate(this, light_id++);
            glPopMatrix();
        }
        //printf("\n");
    }

    if(light_id >= 8)
    {
        SWARNING << "RenderAction::activateLocalLights: maximum light source limit is " <<  8
                 << std::endl;
    }

    //printf("deactivate lights: ");
    for(UInt32 i = light_id;i < _activeLightsCount;++i)
    {
        //printf("%u,", i);
        _activeLightsMask &= ~(1 << i);
        glDisable(GL_LIGHT0 + i);
    }
    //printf("\n");

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

        setActNode(pRoot->getNode());

        if(_bLocalLights && _activeLightsState != pRoot->getLightsState())
            activateLocalLights(pRoot);

        State *pNewState = pRoot->getState();

        if(pNewState != NULL)
        {
            if(_pActiveState != NULL)
            {
                // ok for cgfx I have to call it also for equal states
                // to update the world matrix.
                if(pRoot->isMultiPass() || pRoot->isNoStateSorting() ||
                   pNewState != _pActiveState)
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

        if(pRoot->getGeometry() != NULL)
        {
            pRoot->getGeometry()->drawPrimitives(this);

            _uiNumGeometries++;
        }
        else if(pRoot->hasFunctor())
        {
            // skip occlusion test for small sized geometries
            UInt32 pos_size = 0;
            if(_bOcclusionCulling && pRoot->getNode()->getCore() != NullFC)
            {
                GeometryPtr geo = GeometryPtr::dcast(pRoot->getNode()->getCore());
                if(geo != NullFC)
                {
                    if(geo->getPositions() != NullFC)
                        pos_size = geo->getPositions()->getSize();
                }
            }

            if(_bOcclusionCulling && _glGenQueriesARB != NULL &&
               pos_size > 64)
            {
                //getStatistics()->getElem(statCullTestedNodes)->inc();
                glDepthMask(GL_FALSE);
                glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
                
                if(_occlusionQuery == 0)
                    _glGenQueriesARB(1, &_occlusionQuery);

                _glBeginQueryARB(GL_SAMPLES_PASSED_ARB, _occlusionQuery);

                const DynamicVolume& vol = pRoot->getNode()->getVolume();
                Pnt3f min,max;
                vol.getBounds(min, max);
                glBegin( GL_TRIANGLE_STRIP);
                glVertex3f( min[0], min[1], max[2]);
                glVertex3f( max[0], min[1], max[2]);
                glVertex3f( min[0], max[1], max[2]);
                glVertex3f( max[0], max[1], max[2]);
                glVertex3f( min[0], max[1], min[2]);
                glVertex3f( max[0], max[1], min[2]);
                glVertex3f( min[0], min[1], min[2]);
                glVertex3f( max[0], min[1], min[2]);
                glEnd();
        
                glBegin( GL_TRIANGLE_STRIP);
                glVertex3f( max[0], max[1], min[2]);
                glVertex3f( max[0], max[1], max[2]);
                glVertex3f( max[0], min[1], min[2]);
                glVertex3f( max[0], min[1], max[2]);
                glVertex3f( min[0], min[1], min[2]);
                glVertex3f( min[0], min[1], max[2]);
                glVertex3f( min[0], max[1], min[2]);
                glVertex3f( min[0], max[1], max[2]);
                glEnd();

                _glEndQueryARB(GL_SAMPLES_PASSED_ARB);

                glDepthMask(GL_TRUE);
                glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);

                GLuint pixels = 0;
                _glGetQueryObjectuivARB(_occlusionQuery, GL_QUERY_RESULT_ARB, &pixels);

                if(pixels > 0)
                {
                    pRoot->getFunctor().call(this);
                    _uiNumGeometries++;
                }
                else
                {
                    getStatistics()->getElem(statCulledNodes)->inc();
                }
            }
            else
            {
                pRoot->getFunctor().call(this);
                _uiNumGeometries++;
            }
        }

        if(pNewState != NULL && pRoot->isLastMultiPass()) // last pass
        {
            // without this the deactivate would be called in the next
            // changeFrom call, but before the deactivate the activate from
            // the new state is called this conflicts with the cgfx chunk!
            _pActiveState = NULL; // force a activate

            pNewState->deactivate(this);

            _uiNumMaterialChanges++;
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

void RenderAction::setOcclusionCulling(bool bVal)
{
    _bOcclusionCulling = bVal;
}

bool RenderAction::getOcclusionCulling(void)
{
    return _bOcclusionCulling;
}

// initialisation

Action::ResultE RenderAction::start(void)
{
    glErr("RenderAction: precheck");
    
    Inherited::start();

    if(_window != NULL)
    {
        _window->resizeGL();
    }

    if(_window->hasExtension(_arbOcclusionQuery))
    {
        _glGenQueriesARB          = (void (OSG_APIENTRY*)(GLsizei, GLuint *)) _window->getFunction(_funcGenQueriesARB);
        _glDeleteQueriesARB       = (void (OSG_APIENTRY*)(GLsizei, GLuint *)) _window->getFunction(_funcDeleteQueriesARB);
        _glBeginQueryARB          = (void (OSG_APIENTRY*)(GLenum, GLuint)) _window->getFunction(_funcBeginQueryARB);
        _glEndQueryARB            = (void (OSG_APIENTRY*)(GLenum)) _window->getFunction(_funcEndQueryARB);
        _glGetQueryObjectuivARB   = (void (OSG_APIENTRY*)(GLuint, GLenum, GLuint*)) _window->getFunction(_funcGetQueryObjectuivARB);
    }

    _uiMatrixId = 1;

    _currMatrix.first = 1;
    _currMatrix.second.setIdentity();

    _visibilityStack.clear();
    _visibilityStack.push_back(FrustumVolume::P_NONE);
    
    bool full = false;
    
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

    _pNodeFactory->freeAll();

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
    _pNoStateSortRoot = NULL;
    _pNoStateSortTransRoot = NULL;

    _ocRoot.clear();

    _pActiveState   = NULL;

    _uiActiveMatrix = 0;

    _uiNumMaterialChanges = 0;
    _uiNumMatrixChanges   = 0;
    _uiNumGeometries      = 0;
    _uiNumTransGeometries = 0;

    getStatistics()->reset();

    _vLights.clear();
    _lightsMap.clear();
    _lightsState       = 0;
    _activeLightsState = 0;
    _activeLightsCount = 0;
    _activeLightsMask  = 0;

    // for debugging
#if 0
    for(UInt32 i=0;i<_lightsTable.size();++i)
    {
        printf("Lights table: %u : ", i);
        for(UInt32 j=0;j<_lightsTable[i].size();++j)
        {
            printf("%u,", _lightsTable[i][j]);
        }
        printf("\n");
    }
#endif
    // -------------

    _lightsTable.clear();
    _lightsPath.clear();
    _lightEnvsLightsState.clear();

    _stateSorting = true;

    if(_viewport != NULL && full == false)
    {
        glDisable(GL_SCISSOR_TEST);
    }

    return Action::Continue;
}

Action::ResultE RenderAction::stop(ResultE res)
{
    getStatistics()->getElem(statDrawTime)->start();
    
    UInt32 i;

//    dump(_pMatRoot, 0);
//    dump(_pTransMatRoot, 0);

    //    _pNodeFactory->printStat();    

    if(!_bLocalLights)
    {
        _activeLightsMask = 0;
        for(i = 0; i < _vLights.size(); i++)
        {
            _activeLightsMask |= (1 << i);
            glLoadMatrixf(_vLights[i].second.getValues());
            _vLights[i].first->activate(this, i);
        }
    }

    if(_pNoStateSortRoot != NULL)
    {
        draw(_pNoStateSortRoot);
    }

    if(_bOcclusionCulling)
    {
        for(OCMap::reverse_iterator it = _ocRoot.rbegin();it != _ocRoot.rend();++it)
            draw((*it).second);
    }

    if(_pNoStateSortTransRoot != NULL)
    {
        draw(_pNoStateSortTransRoot);
    }

    SortKeyMap::iterator matRootsIt = _pMatRoots.begin();
    TransSortKeyMap::iterator transMatRootsIt = _pTransMatRoots.begin();

    while(matRootsIt != _pMatRoots.end() ||
          transMatRootsIt != _pTransMatRoots.end())
    {
        //printf("activeLightsState1: %d\n", _activeLightsState);

        if(matRootsIt != _pMatRoots.end())
        {
            //printf("_pMatRoots: sortKey %d\n", (*matRootsIt).first);
            draw((*matRootsIt).second->getFirstChild());
            ++matRootsIt;
        }
        //printf("activeLightsState2: %d\n", _activeLightsState);

        if(transMatRootsIt != _pTransMatRoots.end())
        {
            if(!_bZWriteTrans)
                glDepthMask(false);
        
            //printf("_pTransMatRoots: sortKey %d\n", (*transMatRootsIt).first);
            TransSortMap &ts = (*transMatRootsIt).second;
            for(TransSortMap::iterator it = ts.begin();it != ts.end();++it)
                draw((*it).second);

            if(!_bZWriteTrans)
                glDepthMask(true);
            ++transMatRootsIt;
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
        for(i = 0;i < _activeLightsCount;++i)
            glDisable(GL_LIGHT0 + i);
    }

    glFinish();

    StatTimeElem* elemDraw = getStatistics()->getElem(statDrawTime);
    elemDraw->stop();

    _viewport->setDrawTime((Real32)elemDraw->getTime());
    if(!_ownStat) 
    {
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

    _currMatrix  = _vMatrixStack.back();

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

