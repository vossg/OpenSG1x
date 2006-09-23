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
#include <OSGSwitchMaterial.h>

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

const Int32 RenderAction::OcclusionStopAndWait = 1;
const Int32 RenderAction::OcclusionMultiFrame  = 2;

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
    _occlusionCullingMode    (OcclusionStopAndWait),
    _occlusionCullingPixels  (0),

    _bSmallFeatureCulling   (false),
    _smallFeaturesPixels    (10.0f),
    _smallFeaturesThreshold (32),
    _worldToScreenMatrix    (),

    _useGLFinish            (true),

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
    _occlusionQueries       (),
    _glGenQueriesARB        (NULL),
    _glDeleteQueriesARB     (NULL),
    _glBeginQueryARB        (NULL),
    _glEndQueryARB          (NULL),
    _glGetQueryObjectuivARB (NULL),

    _cgChunkId(-1),
    _cgfxChunkId(-1),
    _shlChunkId(-1)
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

    // we can't include OSGCGChunk here because it is in Contrib ...
    StateChunkPtr cgChunk = StateChunkPtr::dcast(FieldContainerFactory::the()->createFieldContainer("CGChunk"));
    if(cgChunk != NullFC)
    {
        _cgChunkId = cgChunk->getClass()->getId();
        subRefCP(cgChunk);
    }

    // we can't include OSGCGFXChunk here because it is in Contrib ...
    StateChunkPtr cgfxChunk = StateChunkPtr::dcast(FieldContainerFactory::the()->createFieldContainer("CGFXChunk"));
    if(cgfxChunk != NullFC)
    {
        _cgfxChunkId = cgfxChunk->getClass()->getId();
        subRefCP(cgfxChunk);
    }

    StateChunkPtr shlChunk = StateChunkPtr::dcast(FieldContainerFactory::the()->createFieldContainer("SHLChunk"));
    if(shlChunk != NullFC)
    {
        _shlChunkId = shlChunk->getClass()->getId();
        subRefCP(shlChunk);
    }
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

    _bSmallFeatureCulling   (source._bSmallFeatureCulling),
    _smallFeaturesPixels    (source._smallFeaturesPixels),
    _smallFeaturesThreshold (source._smallFeaturesThreshold),
    _worldToScreenMatrix    (source._worldToScreenMatrix),

    _useGLFinish            (source._useGLFinish),

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
    _glGetQueryObjectuivARB (source._glGetQueryObjectuivARB),

    _cgfxChunkId(source._cgfxChunkId),
    _cgChunkId(source._cgChunkId),
    _shlChunkId(source._shlChunkId)
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
    clearOcclusionQueries();
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

void RenderAction::getMaterialStates(Material *mat, std::vector<State *> &states)
{
    if(!mat->isMultiPass())
    {
        states.push_back(mat->getState().getCPtr());
    }
    else
    {
        // HACK need to find a nicer solution.
        MultiPassMaterial *mmat = dynamic_cast<MultiPassMaterial *>(mat);
        if(mmat != NULL)
        {
            // first check for a real multipass material.
            UInt32 passes = mmat->getMaterials().getSize();
            if(passes > 0)
            {
                for(UInt32 i=0;i<passes;++i)
                {
                    getMaterialStates(mmat->getMaterials(i).getCPtr(), states);
                }
            }
            else
            {
                // could be a derived multipass material like CGFXMaterial which overrides
                // only some virtual methods.
                passes = mmat->getNPasses();
                for(UInt32 i=0;i<passes;++i)
                    states.push_back(mmat->getState(i).getCPtr());
            }
        }
        else
        {
            SwitchMaterial *swmat = dynamic_cast<SwitchMaterial *>(mat);
            if(swmat != NULL)
            {
                getMaterialStates(swmat->getCurrentMaterial().getCPtr(), states);
            }
            else
            {
                UInt32 passes = mat->getNPasses();
                for(UInt32 i=0;i<passes;++i)
                    states.push_back(mat->getState(i).getCPtr());
            }
        }
    }
}


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

    std::vector<State *> states;
    getMaterialStates(pMat, states);

    UInt32 mpMatPasses = states.size();
    bool isMultiPass = (mpMatPasses > 1) || pMat->isMultiPass();

    Int32 sortKey = pMat->getRealSortKey();

    if(!_stateSorting ||
       (sortKey == Material::NoStateSorting && 
        (!_bSortTrans || !pMat->isTransparent())))
    {
        for(UInt32 mpi=0;mpi<mpMatPasses;++mpi)
        {
            pState = states[mpi];

            DrawTreeNode *pNewElem = _pNodeFactory->create();
    
            pNewElem->setNode       (getActNode());
            pNewElem->setGeometry   (pGeo);
            pNewElem->setMatrixStore(_currMatrix);
            pNewElem->setLightsState(_lightsState);
            pNewElem->setState(pState);
            if(sortKey == Material::NoStateSorting)
                pNewElem->setNoStateSorting();
        
            if(isMultiPass)
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
        pState = states[mpi];

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

            if(isMultiPass)
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
    
                if(isMultiPass)
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
    
                if(isMultiPass)
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

    std::vector<State *> states;
    getMaterialStates(pMat, states);

    UInt32 mpMatPasses = states.size();
    bool isMultiPass = (mpMatPasses > 1) || pMat->isMultiPass();

    Int32 sortKey = pMat->getRealSortKey();

    if(_bOcclusionCulling && _occlusionCullingMode == OcclusionStopAndWait && _stateSorting)
    {
        DrawTreeNode *pLastMultiPass = NULL;
        for(UInt32 mpi=0;mpi<mpMatPasses;++mpi)
        {
            pState = states[mpi];

            DrawTreeNode *pNewElem = _pNodeFactory->create();

            pNewElem->setNode       (getActNode());
            pNewElem->setFunctor    (func);
            pNewElem->setMatrixStore(_currMatrix);
            pNewElem->setLightsState(_lightsState);
            pNewElem->setState      (pState);
            if(sortKey == Material::NoStateSorting)
                pNewElem->setNoStateSorting();

            if(isMultiPass)
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

                    if(isMultiPass)
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
            pState = states[mpi];

            DrawTreeNode *pNewElem = _pNodeFactory->create();

            pNewElem->setNode       (getActNode());
            pNewElem->setFunctor    (func);
            pNewElem->setMatrixStore(_currMatrix);
            pNewElem->setLightsState(_lightsState);
            pNewElem->setState(pState);
            if(sortKey == Material::NoStateSorting)
                pNewElem->setNoStateSorting();

            if(isMultiPass)
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
        pState = states[mpi];

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

            if(isMultiPass)
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
                
                if(isMultiPass)
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

                if(isMultiPass)
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
    {
        _lightsPath.pop_back();
        if(!_lightsPath.empty())
            _lightsState = _lightsPath.back();
        else
            _lightsState = 0;
    }
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

    // HACK but light sources beneath a LightEnv node can also
    // light it's brothers or parents.
    if(!_lightEnvsLightsState.empty())
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

    if(!_lightEnvsLightsState.empty())
        return;

    if(!_visibilityStack.empty())
        _visibilityStack.pop_back();
    else
        SWARNING << "RenderAction::popVisibility: visibility stack is empty looks"
                    "like a pushVisibility and popVisibility mismatch!" << std::endl;
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

    if(light_id > 8)
    {
        SWARNING << "RenderAction::activateLocalLights: maximum light source limit is " <<  8
                 << std::endl;
    }

    //printf("deactivate lights: ");
    const Color4f black(0.0f, 0.0f, 0.0f, 1.0f);
    for(UInt32 i = light_id;i < _activeLightsCount;++i)
    {
        //printf("%u,", i);
        _activeLightsMask &= ~(1 << i);
        // reset diffuse color to black that's quite usefull for shaders.
        glLightfv(GL_LIGHT0 + i, GL_DIFFUSE,
                  black.getValuesRGBA());
        glDisable(GL_LIGHT0 + i);
    }
    //printf("\n");

    _activeLightsState = pRoot->getLightsState();
    _activeLightsCount = light_id;
}

bool RenderAction::isSmallFeature(const NodePtr &node)
{
    if(node == NullFC)
        return true;

    if(!_bSmallFeatureCulling)
        return false;

    //node->updateVolume();
    DynamicVolume vol = node->getVolume();
    vol.transform(top_matrix());

    Pnt3f p[8];
    vol.getBounds(p[0], p[4]);
    
    p[1].setValues(p[0][0], p[4][1], p[0][2]);
    p[2].setValues(p[4][0], p[4][1], p[0][2]);
    p[3].setValues(p[4][0], p[0][1], p[0][2]);
    
    p[5].setValues(p[4][0], p[0][1], p[4][2]);
    p[6].setValues(p[0][0], p[0][1], p[4][2]);
    p[7].setValues(p[0][0], p[4][1], p[4][2]);

    for(int i=0;i<8;++i)
        _worldToScreenMatrix.multFullMatrixPnt(p[i]);

    Pnt2f min(OSG::Inf, OSG::Inf);
    Pnt2f max(OSG::NegInf, OSG::NegInf);

    for(int i=0;i<8;++i)
    {
        if(p[i][0] < min[0])
            min[0] = p[i][0];
    
        if(p[i][1] < min[1])
            min[1] = p[i][1];
    
        if(p[i][0] > max[0])
            max[0] = p[i][0];
    
        if(p[i][1] > max[1])
            max[1] = p[i][1];
    }

    //for(int i=0;i<8;++i)
    //    printf("p%d: %f %f\n", i, p[i][0], p[i][1]);

    Real32 w = ((max[0] - min[0]) / 2.0f) * Real32(_viewport->getPixelWidth());
    Real32 h = ((max[1] - min[1]) / 2.0f) * Real32(_viewport->getPixelHeight());
    Real32 f = w * h;

    //printf("%f %f pixels: %f x %f = %f\n", max[0] - min[0], max[1] - min[1], w, h, f);

    if(f <= _smallFeaturesPixels)
        return true;

    return false;
}

bool RenderAction::isOccluded(DrawTreeNode *pRoot)
{
    // Skip draw tree nodes without a functor!
    if(!pRoot->hasFunctor())
        return false;

    // skip occlusion test for small sized geometries
    UInt32 pos_size = 0;
    UInt32 nodeid = 0;
    if((_bOcclusionCulling || _bSmallFeatureCulling) &&
        pRoot->getNode()->getCore() != NullFC)
    {
        GeometryPtr geo = GeometryPtr::dcast(pRoot->getNode()->getCore());
        if(geo != NullFC)
        {
            nodeid = pRoot->getNode().getFieldContainerId();
            if(geo->getPositions() != NullFC)
                pos_size = geo->getPositions()->getSize();
        }
    }

    bool foundSmallFeature = false;
    if(_bSmallFeatureCulling && pos_size > _smallFeaturesThreshold)
    {    
        foundSmallFeature = isSmallFeature(pRoot->getNode());
        if(foundSmallFeature)
        {
            getStatistics()->getElem(statCulledNodes)->inc();
            return true;
        }
    }

    if(!foundSmallFeature)
    {
        if(_bOcclusionCulling && _glGenQueriesARB != NULL &&
           pos_size > 64)
        {
            if(_occlusionCullingMode == OcclusionMultiFrame)
            {
                // ok we use a "multi frame" algorithm, which renders
                // the whole scene first and keeps the depth buffer. For each object
                // a bounding box is drawn with an occlusion query.
                // The results are fetched in the next frame, if the box was visible
                // the corresponding object is drawn.
                std::map<UInt32, GLuint>::iterator occIt = _occlusionQueries.find(nodeid);
                if(occIt == _occlusionQueries.end())
                {
                    return false;
                }

                GLuint pixels = 0;
                GLuint occlusionQuery = (*occIt).second;
                _glGetQueryObjectuivARB(occlusionQuery, GL_QUERY_RESULT_ARB, &pixels);

                if(pixels > _occlusionCullingPixels)
                {
                    return false;
                }
                else
                {
                    getStatistics()->getElem(statCulledNodes)->inc();
                    return true;
                }
            }
            else if(_occlusionCullingMode == OcclusionStopAndWait)
            {
                // ok we use a simple "stop an wait" algorithm, which renders
                // the scene in front to back order. For each object (except for the
                // front most object) a bounding box is drawn with an occlusion query.
                // The result is fetched immediately afterwards and if the box was visible
                // the corresponding object is drawn.

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
    
                if(pixels > _occlusionCullingPixels)
                {
                    return false;
                }
                else
                {
                    getStatistics()->getElem(statCulledNodes)->inc();
                    return true;
                }
            }
        }
    }

    return false;
}

void RenderAction::clearOcclusionQueries(void)
{
    for(std::map<UInt32, GLuint>::iterator occIt = _occlusionQueries.begin();
        occIt != _occlusionQueries.end();++occIt)
    {
        GLuint occlusionQuery = (*occIt).second;
        _glDeleteQueriesARB(1, &occlusionQuery);
    }
    _occlusionQueries.clear();
}

void RenderAction::drawMultiFrameOcclusionBB(DrawTreeNode *pRoot)
{
    while(pRoot != NULL)
    {
        if(pRoot->hasFunctor())
        {
            UInt32 pos_size = 0;
            GeometryPtr geo = GeometryPtr::dcast(pRoot->getNode()->getCore());
            if(geo != NullFC)
            {
                if(geo->getPositions() != NullFC)
                    pos_size = geo->getPositions()->getSize();
            }
        
            if(_glGenQueriesARB != NULL && pos_size > 64)
            {
                UInt32 uiNextMatrix = pRoot->getMatrixStore().first;
                if(uiNextMatrix != 0 && uiNextMatrix != _uiActiveMatrix)
                {
                    glLoadMatrixf(pRoot->getMatrixStore().second.getValues());
        
                    _uiActiveMatrix = uiNextMatrix;
        
                    _uiNumMatrixChanges++;
        
                    _currMatrix.second = pRoot->getMatrixStore().second;
                    updateTopMatrix();
                }

                GLuint occlusionQuery;
                _glGenQueriesARB(1, &occlusionQuery);
        
                _glBeginQueryARB(GL_SAMPLES_PASSED_ARB, occlusionQuery);
        
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
    
                // we use the node because the geometry core could be shared!
                _occlusionQueries.insert(std::make_pair(pRoot->getNode().getFieldContainerId(), occlusionQuery));
            }
        }

        if(pRoot->getFirstChild() != NULL)
        {
            drawMultiFrameOcclusionBB(pRoot->getFirstChild());
        }

        pRoot = pRoot->getBrother();
    }
}

//#define PRINT_MAT

void RenderAction::updateShader(State *state)
{
    if(state == NULL)
        return;

    if(_cgChunkId != -1)
    {
        StateChunkPtr cgChunk = state->getChunk(_cgChunkId);
        if(cgChunk != NULL)
            cgChunk->update(this);
    }

    if(_cgfxChunkId != -1)
    {
        StateChunkPtr cgfxChunk = state->getChunk(_cgfxChunkId);
        if(cgfxChunk != NULL)
            cgfxChunk->update(this);
    }

    StateChunkPtr shlChunk = state->getChunk(_shlChunkId);
    if(shlChunk != NULL)
        shlChunk->update(this);
}

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

        if(!isOccluded(pRoot))
        {
            if(_bLocalLights && _activeLightsState != pRoot->getLightsState())
                activateLocalLights(pRoot);

            State *pNewState = pRoot->getState();
    
            if(pNewState != NULL)
            {
                if(_pActiveState != NULL)
                {
                    // we need this cgfx test because for multipass cgfx materials
                    // the state doesn't change.
                    if(pNewState != _pActiveState ||
                       (_cgfxChunkId != -1 && pNewState->getChunk(_cgfxChunkId) != NULL) ||
                       pRoot->isNoStateSorting())
                    {
                        State *previous_state = _pActiveState;
                        _pActiveState = pNewState;
                        pNewState->changeFrom(this, previous_state);
                        _uiNumMaterialChanges++;
                    }
                    else
                    {
                        // even if the state didn't change we need to update
                        // the shaders to provide the right world matrix.
                        updateShader(pNewState);
                    }
                }
                else
                {
                    _pActiveState = pRoot->getState();
                    _pActiveState->activate(this);
                    _uiNumMaterialChanges++;
                }
            }
            else
            {
                updateShader(_pActiveState);
            }
    
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
    
            if(pNewState != NULL && pRoot->isLastMultiPass()) // last pass
            {
                // without this the deactivate would be called in the next
                // changeFrom call, but before the deactivate the activate from
                // the new state is called this conflicts with the cgfx chunk!
                _pActiveState = NULL; // force a activate
    
                pNewState->deactivate(this);
                _uiNumMaterialChanges++;
            }
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
    clearOcclusionQueries();
    _bOcclusionCulling = bVal;
}

bool RenderAction::getOcclusionCulling(void)
{
    return _bOcclusionCulling;
}

void RenderAction::setOcclusionCullingMode(Int32 mode)
{
    clearOcclusionQueries();
    _occlusionCullingMode = mode;
}

Int32 RenderAction::getOcclusionCullingMode(void)
{
    return _occlusionCullingMode;
}

void RenderAction::setOcclusionCullingPixels(UInt32 pixels)
{
    _occlusionCullingPixels = pixels;
}

UInt32 RenderAction::getOcclusionCullingPixels(void)
{
    return _occlusionCullingPixels;
}

void RenderAction::setSmallFeatureCulling(bool bVal)
{
    _bSmallFeatureCulling = bVal;
}

bool RenderAction::getSmallFeatureCulling(void)
{
    return _bSmallFeatureCulling;
}

void RenderAction::setSmallFeaturePixels(Real32 pixels)
{
    _smallFeaturesPixels = pixels;
}

Real32 RenderAction::getSmallFeaturePixels(void)
{
    return _smallFeaturesPixels;
}

void RenderAction::setSmallFeatureThreshold(UInt32 threshold)
{
    _smallFeaturesThreshold = threshold;
}

UInt32 RenderAction::getSmallFeatureThreshold(void)
{
    return _smallFeaturesThreshold;
}

void RenderAction::setUseGLFinish(bool s)
{
    _useGLFinish = s;
}

bool RenderAction::getUseGLFinish(void)
{
    return _useGLFinish;
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
            if(_bSmallFeatureCulling)
                _camera->getWorldToScreen(_worldToScreenMatrix, *_viewport);

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
    else
    {
        // reset all lights.
        const Color4f black(0.0f, 0.0f, 0.0f, 1.0f);
        for(i = 0;i < 8;++i)
        {
            glLightfv(GL_LIGHT0 + i, GL_DIFFUSE,
                      black.getValuesRGBA());
            glDisable(GL_LIGHT0 + i);
        }
    }

    glDepthMask(GL_TRUE);

    if(_pNoStateSortRoot != NULL)
    {
        draw(_pNoStateSortRoot);
    }

    if(_bOcclusionCulling && _occlusionCullingMode == OcclusionStopAndWait && !_ocRoot.empty())
    {
        OCMap::reverse_iterator it = _ocRoot.rbegin();
        // draw the front most object without occlusion query.
        _bOcclusionCulling = false;
            draw((*it++).second);
        _bOcclusionCulling = true;

        while(it != _ocRoot.rend())
            draw((*it++).second);
    }

    if(_pNoStateSortTransRoot != NULL)
    {
        draw(_pNoStateSortTransRoot);
    }

    // for multi frame occlusion culling we disable zwrite transparency.
    bool bZWriteTrans = _bZWriteTrans;
    if(_bOcclusionCulling && _occlusionCullingMode == OcclusionMultiFrame)
        _bZWriteTrans = false;

    SortKeyMap::iterator matRootsIt = _pMatRoots.begin();
    TransSortKeyMap::iterator transMatRootsIt = _pTransMatRoots.begin();

    while(matRootsIt != _pMatRoots.end() ||
          transMatRootsIt != _pTransMatRoots.end())
    {
        bool matRootsValid = (matRootsIt != _pMatRoots.end());
        bool transMatRootsValid = (transMatRootsIt != _pTransMatRoots.end());

        Int32 matSortKey = matRootsValid ? (*matRootsIt).first : 0;
        Int32 transSortKey = transMatRootsValid ? (*transMatRootsIt).first : 0;

        if(matRootsValid)
        {
            if(transMatRootsValid)
            {
                if(matSortKey <= transSortKey)
                {
                    //printf("draw opaque %d\n", matSortKey);
                    draw((*matRootsIt).second->getFirstChild());
                    ++matRootsIt;
                }
            }
            else
            {
                //printf("draw opaque %d\n", matSortKey);
                draw((*matRootsIt).second->getFirstChild());
                ++matRootsIt;
            }
        }

        if(transMatRootsValid)
        {
            if(matRootsValid)
            {
                if(transSortKey <= matSortKey)
                {
                    if(!_bZWriteTrans)
                        glDepthMask(GL_FALSE);
        
                    TransSortMap &ts = (*transMatRootsIt).second;
                    for(TransSortMap::iterator it = ts.begin();it != ts.end();++it)
                        draw((*it).second);
                    //printf("draw transparent %d\n", transSortKey);
        
                    if(!_bZWriteTrans)
                        glDepthMask(GL_TRUE);
                    ++transMatRootsIt;
                }
            }
            else
            {
                if(!_bZWriteTrans)
                    glDepthMask(GL_FALSE);
    
                TransSortMap &ts = (*transMatRootsIt).second;
                for(TransSortMap::iterator it = ts.begin();it != ts.end();++it)
                    draw((*it).second);
                //printf("draw transparent %d\n", transSortKey);
    
                if(!_bZWriteTrans)
                    glDepthMask(GL_TRUE);
                ++transMatRootsIt;
            }
        }
    }

    if(_pActiveState != NULL)
    {
        State *state = _pActiveState;
        // without this the deactivate would be called in
        // the next changeFrom call.
        _pActiveState = NULL;

        state->deactivate(this);
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
        const Color4f black(0.0f, 0.0f, 0.0f, 1.0f);
        for(i = 0;i < _activeLightsCount;++i)
        {
            glLightfv(GL_LIGHT0 + i, GL_DIFFUSE,
                      black.getValuesRGBA());
            glDisable(GL_LIGHT0 + i);
        }
    }

    if(_bOcclusionCulling && _occlusionCullingMode == OcclusionMultiFrame)
    {
        // restore old value.
        _bZWriteTrans = bZWriteTrans;

        _uiActiveMatrix = 0;

        // draw occlusion bounding boxes.
        // we check the occlusion results in the next frame!
        // -------
        glDepthMask(GL_FALSE);
        glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);

        // destroy old occlusion queries.
        clearOcclusionQueries();

        // now draw the bounding boxes of all opaque objects.
        matRootsIt = _pMatRoots.begin();
        while(matRootsIt != _pMatRoots.end())
            drawMultiFrameOcclusionBB((*matRootsIt++).second->getFirstChild());

        glDepthMask(GL_TRUE);
        glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
    }

    glDepthMask(GL_TRUE);

    if(_useGLFinish)
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

