
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

#include <OSGConfig.h>
#include "OSGNewAction.h"
#include "OSGActorBase.h"
#include "OSGIteratorBase.h"
#include "OSGActorStateChunk.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::NewAction
    
The NewAction holds actors and one iterator. When the action is applied to a
node, it passes the information to the iterator, which then controls the order
of the traversal.

*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

NewAction *
NewAction::create(void)
{
    return new NewAction();
}

NewAction *
NewAction::create(IteratorBase *pIterator)
{
    return new NewAction(pIterator);
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*------------------------------ destructor -------------------------------*/

NewAction::~NewAction(void)
{
    // TODO: delete actors, iterator
}

/*---------------------------- actor access ------------------------------*/

/*! Add an actor at the end of the list and return its assigned index.
 */
Int32
NewAction::addActor(ActorBase *pActor)
{
    if(_bInTraversal)
    {
        FWARNING(("NewAction::addActor not possible during traversal.\n"));

        return -1;
    }

    if((_pIterator != NULL) && (pActor->acceptsIterator(_pIterator) == false))
    {
        FWARNING (("NewAction::addActor: actor %p does not ",  pActor   ));
        FPWARNING(("work with iterator %p. Ignoring.",        _pIterator));
        
        return -1;
    }

    UInt32 uiIndex = _actors.size();

    _actors.push_back(pActor);

    configureAdd(pActor, uiIndex);

    return uiIndex;
}

/*! Insert an actor at the given index and return its assigned index.
 */
Int32
NewAction::insertActor(ActorBase *pActor, UInt32 uiIndex)
{
    if(_bInTraversal)
    {
        FINFO(("NewAction::insertActor not possible during traversal.\n"));

        return -1;
    }

    if(uiIndex >= _actors.size())
    {
        return addActor(pActor);
    }

    if((_pIterator != NULL) && (pActor->acceptsIterator(_pIterator) == false))
    {
        FWARNING (("NewAction::insertActor: actor %p does not ",  pActor   ));
        FPWARNING(("work with iterator %p. Ignoring.",           _pIterator));
        
        return -1;
    }

    ActorStoreIt insIter    = _actors.begin() + uiIndex;
    ActorStoreIt end        = _actors.end();
    UInt32       uiNewIndex = uiIndex;
    

    _actors.insert(insIter, pActor);
    
    for(; insIter != end; ++insIter)
    {
        (*insIter)->setActorId(uiNewIndex);
        ++uiNewIndex;
    }
    
    configureAdd(pActor, uiIndex);
    
    return uiIndex;
}

/*! Remove actor at given index without deleting it. You may use the returned
    pointer to re-add it.
*/
ActorBase *
NewAction::subActor(UInt32 uiIndex)
{
    if(_bInTraversal)
    {
        FINFO(("NewAction::subActor not possible during traversal.\n"));

        return NULL;
    }

    FFASSERT((uiIndex < _actors.size()), 1,
             ("NewAction::subActor: index out of range.\n"););

    ActorStoreIt  iter      = _actors.begin() + uiIndex;
    ActorBase    *pOldActor = *iter;

    configureSub(pOldActor);

    _actors.erase(iter);

    return pOldActor;
}

/*! Remove given actor without deleting it. You may use the returned
    pointer ro re-add it.
*/
ActorBase *
NewAction::subActor(ActorBase *pActor)
{
    // need not test _bInTraversal

    Int32 iIndex = findActor(pActor);

    if(iIndex >= 0)
    {
        return subActor(iIndex);
    }
    else
    {
        return NULL;
    }

    // need not call _pIterator->signalConfigure
}

/*! Remove actor at given index. This actualy deletes the actor, don't use any
    stale pointers to re-add it. 
*/
void
NewAction::eraseActor(UInt32 uiIndex)
{
    if(_bInTraversal)
    {
        FINFO(("NewAction::removeActor not possible during traversal.\n"));

        return;
    }

    FFASSERT((uiIndex < _actors.size()), 1,
             ("NewAction::removeActor: index out of range.\n");)

    ActorStoreIt iter       = _actors.begin() + uiIndex;
    ActorBase    *pOldActor = *iter;

    configureSub(pOldActor);

    _actors.erase(iter);

    delete pOldActor;
}

/*! Remove given actor, if found. This actualy deletes the actor, don't use any
    stale pointers to re-add it. 
*/
void
NewAction::eraseActor(ActorBase *pActor)
{
    FDEBUG(("NewAction::removeActor(%p)\n", pActor));

    // need not test _bInTraversal

    Int32 iIndex = findActor(pActor);

    if(iIndex >= 0)
        eraseActor(iIndex);

    // need not call _pIterator->signalConfigure
}

ActorBase *
NewAction::getActor(UInt32 uiIndex) const
{
    FFASSERT((uiIndex < _actors.size()), 1,
             ("NewAction::getActor: index out of range.\n");)

    return _actors[uiIndex];
}

/*! Returns index of the actor or -1 if it's not found.
 */
Int32
NewAction::findActor(ActorBase *pActor) const
{
    if(_actors[pActor->getActorId()] == pActor)
    {
        return pActor->getActorId();
    }
    else
    {
        return -1;
    }
}

UInt32
NewAction::getNumActors(void) const
{
    return _actors.size();
}

bool
NewAction::setIterator(IteratorBase *pIterator)
{
    if(_pIterator == pIterator)
        return true;

    bool         bAccept   = true;
    ActorStoreIt itActors  = beginActors();
    ActorStoreIt end       = endActors  ();
    
    for(; itActors != end; ++itActors)
    {
        bAccept &= (*itActors)->acceptsIterator(pIterator);
    }

    if(bAccept == false)
    {
        FWARNING (("NewAction::setIterator: iterator %p is not ", pIterator));
        FPWARNING(("accepted by at least one actor. Ignoring.\n"           ));
    
        return false;
    }

    if(_pIterator != NULL)
    {
        _pIterator->setAction         (NULL);
        _pIterator->receiveActorsClear(    );
    }
    
    _pIterator = pIterator;

    if(_pIterator != NULL)
    {
        _pIterator->setAction(this);
        
        itActors  = beginActors();
        end       = endActors  ();

        for(; itActors != end; ++itActors)
        {
            (*itActors)->receiveIteratorSet(_pIterator               );
            _pIterator ->receiveActorAdd   (*itActors, 
                                            (*itActors)->getActorId());
        }
    }

    return true;
}

IteratorBase *
NewAction::getIterator(void) const
{
    return _pIterator;
}

/* Traverse the subtree with the given root node.
 */
NewActionBase::ResultE
NewAction::apply(NodePtr pRoot)
{
    _pIterator->clearRoots(     );
    _pIterator->addRoot   (pRoot);

    return _pIterator->start();
}

/* Traverse the subtrees with the given root nodes. Nodes in multiple subtrees
   are traversed multiple times.
*/
NewActionBase::ResultE
NewAction::apply(const RootList &roots)
{
    _pIterator->clearRoots(     );
    _pIterator->addRoot   (roots);

    return _pIterator->start();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*--------------------------- constructors --------------------------------*/

NewAction::NewAction(void)
    : _actors      (     ),
      _pIterator   (NULL ),
      _bInTraversal(false)
{
}

NewAction::NewAction(IteratorBase *pIterator)
    : _actors      (         ),
      _pIterator   (pIterator),
      _bInTraversal(false    )
{
}

/*------------------------- iterator interface ---------------------------*/

NewActionBase::ResultE
NewAction::startActors(void)
{
    ActorStoreIt iter = _actors.begin();
    ActorStoreIt end  = _actors.end  ();

    ResultE      res  = NewActionBase::Continue;

    for(; (iter != end) && (res == Continue); ++iter)
    {
        res = ResultE(res | (*iter)->start());
    }

    return res;
}

NewActionBase::ResultE
NewAction::stopActors(void)
{
    ActorStoreIt iter = _actors.begin();
    ActorStoreIt end  = _actors.end  ();

    ResultE      res  = NewActionBase::Continue;

    for(; (iter != end) && (res == Continue); ++iter)
    {
        res = ResultE(res | (*iter)->stop());
    }

    return res;
}

void
NewAction::cloneState(ActorStateChunk *pChunk)
{
    UInt32 uiNumActors = getNumActors();

    for(UInt32 i = 0; i < uiNumActors; ++i)
    {
        pChunk->setEntry(i, _actors[i]->getState()->clone());
                            
        _actors[i]->setState(pChunk->getEntry(i));
    }
}

void
NewAction::getState(ActorStateChunk *pChunk)
{
    UInt32 uiNumActors = getNumActors();

    for(UInt32 i = 0; i < uiNumActors; ++i)
    {
        pChunk->setEntry(i, _actors[i]->getState());
    }
}

void
NewAction::setState(ActorStateChunk *pChunk)
{
    UInt32 uiNumActors = getNumActors();
        
    for(UInt32 i = 0; i < uiNumActors; ++i)
    {
        _actors[i]->setState(pChunk->getEntry(i));
    }
}

NewActionBase::ResultE
NewAction::enterNode(NodePtr pNode, ActorStoreIt iter, ActorStoreIt end)
{
    ResultE res = NewActionBase::Continue;

    for(; iter != end; ++iter)
    {
        res = ResultE(res | (*iter)->applyEnter(pNode->getCore()));
    }

    return res;
}

NewActionBase::ResultE
NewAction::leaveNode(NodePtr pNode, ActorStoreIt iter, ActorStoreIt end)
{
    ResultE res = NewActionBase::Continue;

    for(; iter != end; ++iter)
    {
        res = ResultE(res | (*iter)->applyLeave(pNode->getCore()));
    }

    return res;
}

NewAction::ActorStoreIt
NewAction::beginActors(void)
{
    return _actors.begin();
}

NewAction::ActorStoreIt
NewAction::endActors(void)
{
    return _actors.end();
}

NewAction::ActorStoreConstIt
NewAction::beginActors(void) const
{
    return _actors.begin();
}

NewAction::ActorStoreConstIt
NewAction::endActors(void) const
{
    return _actors.end();
}

/*----------------------------- actor interface --------------------------*/

void
NewAction::addRoot(NodePtr pRoot)
{
    _pIterator->addRoot(pRoot);
}

void
NewAction::addRoot(const RootList &roots)
{
    _pIterator->addRoot(roots);
}

const NewAction::RootList &
NewAction::getRoots(void) const
{
    return _pIterator->getRoots();
}

NewAction::RootList &
NewAction::getRoots(void)
{
    return _pIterator->getRoots();
}

NodePtr
NewAction::getCurrNode(void) const
{
    return _pIterator->getCurrentNode();
}

void
NewAction::setUseNodeList(void)
{
    _pIterator->setUseNodeList();
}

bool
NewAction::getUseNodeList(void) const
{
    return _pIterator->getUseNodeList();
}

ActiveNodeListIt
NewAction::beginNodes(void)
{
    return _pIterator->beginNodes();
}

ActiveNodeListIt
NewAction::endNodes(void)
{
    return _pIterator->endNodes();
}

ActiveNodeListConstIt
NewAction::beginNodes(void) const
{
    return _pIterator->beginNodes();
}

ActiveNodeListConstIt
NewAction::endNodes(void) const
{
    return _pIterator->endNodes();
}

ActiveNodeList &
NewAction::getNodeList(void)
{
    return _pIterator->getNodeList();
}

const ActiveNodeList &
NewAction::getNodeList(void) const
{
    return _pIterator->getNodeList();
}

void
NewAction::emitStateRead(UInt32 uiActorId) const
{
    _pIterator->receiveStateRead(uiActorId);
}

void
NewAction::emitStateWrite(UInt32 uiActorId) const
{
    _pIterator->receiveStateWrite(uiActorId);
}

/*----------------------------- helpers ----------------------------------*/

void
NewAction::configureAdd(ActorBase *pActor, UInt32 uiActorId)
{
    pActor->setAction (this     );
    pActor->setActorId(uiActorId);

    if(_pIterator != NULL)
    {
        pActor    ->receiveIteratorSet(_pIterator          );
        _pIterator->receiveActorAdd   (pActor,    uiActorId);
    }
}

void
NewAction::configureSub(ActorBase *pActor)
{
    if(_pIterator != NULL)
        _pIterator->receiveActorSub(pActor, pActor->getActorId());

    pActor->setAction (NULL);
    pActor->setActorId(0   );
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif

namespace
{
    static Char8 cvsid_cpp     [] = "@(#)$Id: OSGNewAction.cpp,v 1.1 2003/10/10 13:51:06 neumannc Exp $";
    static Char8 cvsid_hpp     [] = OSGNEWACTION_HEADER_CVSID;
    static Char8 cvsid_inl     [] = OSGNEWACTION_INLINE_CVSID;
}
