/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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
#include <OSGDrawTreeNode.h>

#include <OSGMaterial.h>

#include <OSGGeometry.h>
#include <OSGLog.h>

#include <OSGLightBase.h>

#include <OSGGL.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::RenderAction
    \ingroup ActionLib

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

vector<Action::Functor> *RenderAction::_vDefaultEnterFunctors = NULL;
vector<Action::Functor> *RenderAction::_vDefaultLeaveFunctors = NULL;


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
        _vDefaultEnterFunctors = new vector<Action::Functor>;
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
        _vDefaultLeaveFunctors = new vector<Action::Functor>;
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
    _pMaterial           (NULL),

    _uiMatrixId          (0),
    _currMatrix          (),
    _vMatrixStack        (),

    _mMatMap             (),

    _pRoot               (NULL),
    _pMatRoot            (NULL),
    _pTransMatRoot       (NULL),

    _uiActiveMatrix      (0),
    _pActiveState        (NULL),

    _uiNumMaterialChanges(0),
    _uiNumMatrixChanges  (0),
    _uiNumGeometries     (0),
    _uiNumTransGeometries(0),

    _bSortTrans          (true),

    _vLights()
{
    if(_vDefaultEnterFunctors != NULL)
        _enterFunctors = *_vDefaultEnterFunctors;

    if(_vDefaultLeaveFunctors != NULL)
        _leaveFunctors = *_vDefaultLeaveFunctors;
}


/** \brief Copy-Constructor
 */

RenderAction::RenderAction(const RenderAction &source) :
     Inherited           (source),
    _pMaterial           (source._pMaterial),

    _uiMatrixId          (source._uiMatrixId),
    _currMatrix          (source._currMatrix),
    _vMatrixStack        (source._vMatrixStack),

    _mMatMap             (source._mMatMap),

    _pRoot               (source._pRoot),
    _pMatRoot            (source._pMatRoot),
    _pTransMatRoot       (source._pTransMatRoot),

    _uiActiveMatrix      (source._uiActiveMatrix),
    _pActiveState        (source._pActiveState),

    _uiNumMaterialChanges(source._uiNumMaterialChanges),
    _uiNumMatrixChanges  (source._uiNumMatrixChanges),
    _uiNumGeometries     (source._uiNumGeometries),
    _uiNumTransGeometries(source._uiNumTransGeometries),

    _bSortTrans          (source._bSortTrans),
    _vLights             (source._vLights)
{
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

    pState = pMat->getState().getCPtr();

    if(_bSortTrans == true && pMat->isTransparent() == true)
    {
        DrawTreeNode *pNewElem = new DrawTreeNode;
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
        DrawTreeNode *pNewElem = new DrawTreeNode;
 
        if(it == _mMatMap.end())
        {
            DrawTreeNode *pNewMatElem = new DrawTreeNode;
            
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
            vector<DrawTreeNode *>::iterator treesIt  = it->second.begin();
            vector<DrawTreeNode *>::iterator treesEnd = it->second.end();
            
            pNewElem->setGeometry   (pGeo);
            pNewElem->setMatrixStore(_currMatrix);
            
            for(;treesIt != treesEnd; ++treesIt)
            {
                (*treesIt)->addChild(pNewElem);
            }
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

    pState = pMat->getState().getCPtr();

    if(_bSortTrans == true && pMat->isTransparent() == true)
    {
        DrawTreeNode *pNewElem = new DrawTreeNode;
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
        DrawTreeNode *pNewElem = new DrawTreeNode;
        
        if(it == _mMatMap.end())
        {
            DrawTreeNode *pNewMatElem = new DrawTreeNode;
            
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
            vector<DrawTreeNode *>::iterator treesIt  = it->second.begin();
            vector<DrawTreeNode *>::iterator treesEnd = it->second.end();
            
            pNewElem->setFunctor    (func);
            pNewElem->setMatrixStore(_currMatrix);
            
            for(;treesIt != treesEnd; ++treesIt)
            {
                (*treesIt)->addChild(pNewElem);
            }
        }
    }
}

void RenderAction::dropLight(LightBase *pLight)
{
    if(pLight != NULL)
    {
        LightStore oStore;

        pLight->makeChunk();

        oStore.first  =  pLight->getChunk().getCPtr();
        oStore.second = _currMatrix.second;

        Matrix fromworld,tobeacon;
        
//        getActNode()->getToWorld(fromworld);

        fromworld = _currMatrix.second;
        fromworld.invert();

        NodePtr beacon = pLight->getBeacon();

        if(beacon == NullFC)
        {
            SINFO << "draw: no beacon set!" << endl;
        }
        else
        {
            beacon->getToWorld(tobeacon);
    
            tobeacon.mult(fromworld);
            
            oStore.second.mult(tobeacon);
        }

        _vLights.push_back(oStore);
    }
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
             << "Matrix : " << pRoot->getMatrixStore().first << endl;

    indentLog(uiIndent, PWARNING);
    PWARNING << "{" << endl;

    if(pRoot->getFirstChild() != NULL)
    {
        dump(pRoot->getFirstChild(), uiIndent + 4);
    }

    indentLog(uiIndent, PWARNING);
    PWARNING << "}" << endl;

    if(pRoot->getBrother() != NULL)
    {
        dump(pRoot->getBrother(), uiIndent);
    }
}

//#define PRINT_MAT

void RenderAction::draw(DrawTreeNode *pRoot)
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
        pRoot->getGeometry()->draw(this);

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

void RenderAction::setSortTrans(bool bVal)
{
    _bSortTrans = bVal;
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

    if(_viewport != NULL)
    {
        GLint pl  = _viewport->getPixelLeft();
        GLint pr  = _viewport->getPixelRight();
        GLint pb  = _viewport->getPixelBottom();
        GLint pt  = _viewport->getPixelTop();
        GLint pw  = pr - pl + 1;
        GLint ph  = pt - pb + 1;
        bool full = _viewport->isFullWindow();

        glViewport(pl, pb, pw, ph);
        glScissor (pl, pb, pw, ph);

        if (full == false)
        {
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

    _mMatMap.clear();

    subRefP(_pRoot);
    subRefP(_pMatRoot);
    subRefP(_pTransMatRoot);

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

    _pRoot         = new DrawTreeNode;
    addRefP(_pRoot);

    _pMatRoot      = new DrawTreeNode;
//    _pRoot->addChild(_pMatRoot);
    addRefP(_pMatRoot);

    _pTransMatRoot = new DrawTreeNode;
//    _pRoot->addChild(_pTransMatRoot);
    addRefP(_pTransMatRoot);

    _pActiveState   = NULL;

    _uiActiveMatrix = 0;

    _uiNumMaterialChanges = 0;
    _uiNumMatrixChanges   = 0;
    _uiNumGeometries      = 0;
    _uiNumTransGeometries = 0;

    _vLights.clear();

    return Action::Continue;
}

Action::ResultE RenderAction::stop(ResultE res)
{
    if(!_ownStat)
       getStatistics()->getElem(statDrawTime)->start();
    
    UInt32 i;

//    dump(_pRoot, 0);
//    dump(_pMatRoot, 0);
//    dump(_pTransMatRoot, 0);

    for(i = 0; i < _vLights.size(); i++)
    {
        glLoadMatrixf(_vLights[i].second.getValues());
        _vLights[i].first->activate(this, i);
    }

    draw(_pMatRoot->getFirstChild());

// GL stuff handled by chunks now
//    glEnable   (GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glDepthMask(false);

    draw(_pTransMatRoot->getFirstChild());

//    glDisable  (GL_BLEND);
//    glDepthMask(true);

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

const Matrix &RenderAction::top_matrix(void)
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


vector<RenderAction::Functor> *RenderAction::getDefaultEnterFunctors(void)
{
    return _vDefaultEnterFunctors;
}

vector<RenderAction::Functor> *RenderAction::getDefaultLeaveFunctors(void)
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

