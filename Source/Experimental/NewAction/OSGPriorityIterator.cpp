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
#include "OSGPriorityIterator.h"

OSG_USING_NAMESPACE

PriorityIterator *
PriorityIterator::create(void)
{
    return new PriorityIterator();
}

PriorityIterator::~PriorityIterator(void)
{
    delete _pEnterIter;
    delete _pEnterOrdIter;
    delete _pLeaveIter;
    delete _pLeaveOrdIter;
}

PriorityIterator::ResultE
PriorityIterator::start(void)
{
    RootListIt itRoots  = getRoots().begin();
    RootListIt endRoots = getRoots().end  ();

    setResult(NewActionBase::Continue);

    for(; (itRoots != endRoots) && (getResult() == NewActionBase::Continue);
        ++itRoots)
    {
        _pIter->preTraversal();
        startActors         ();

        setResult(ResultE(getResult() | _pIter->traverse(*itRoots)));

        if((getResult() & NewActionBase::Abort) == 0)
        {
            stopActors();
        }
        
        _pIter->postTraversal();
    }

    return getResult();
}

void
PriorityIterator::stop(void)
{
    setResult(NewActionBase::Stop);
}

void
PriorityIterator::receiveActorAdd(ActorBase *pActor, UInt32 uiActorId)
{
    Inherited::receiveActorAdd(pActor, uiActorId);

    if(getNumLeaveActors() > 0)
    {
        if(getNumOrderedStateActors() > 0)
        {
            _pIter = _pLeaveOrdIter;
        }
        else
        {
            _pIter = _pLeaveIter;
        }
    }
    else
    {
        if(getNumOrderedStateActors() > 0)
        {
            _pIter = _pLeaveOrdIter;
        }
        else
        {
            _pIter = _pLeaveIter;
        }
    }
}

void
PriorityIterator::receiveActorSub(ActorBase *pActor, UInt32 uiActorId)
{
    Inherited::receiveActorSub(pActor, uiActorId);

    if(getNumLeaveActors() > 0)
    {
        if(getNumOrderedStateActors() > 0)
        {
            _pIter = _pLeaveOrdIter;
        }
        else
        {
            _pIter = _pLeaveIter;
        }
    }
    else
    {
        if(getNumOrderedStateActors() > 0)
        {
            _pIter = _pLeaveOrdIter;
        }
        else
        {
            _pIter = _pLeaveIter;
        }
    }
}

void
PriorityIterator::receiveActorsClear(void)
{
    Inherited::receiveActorsClear();
}

void
PriorityIterator::receiveStateRead(UInt32 uiActorId)
{
    _pIter->receiveStateRead(uiActorId);
}

void
PriorityIterator::receiveStateWrite(UInt32 uiActorId)
{
    _pIter->receiveStateWrite(uiActorId);
}

PriorityIterator::PriorityIterator(void)
    : _result       (NewActionBase::Continue),
      _pIter        (NULL                   ),
      _pEnterIter   (NULL                   ),
      _pEnterOrdIter(NULL                   ),
      _pLeaveIter   (NULL                   ),
      _pLeaveOrdIter(NULL                   )
{
    _pEnterIter    = new PIEnter   (this);
    _pEnterOrdIter = new PIEnterOrd(this);
    _pLeaveIter    = new PILeave   (this);
    _pLeaveOrdIter = new PILeaveOrd(this);
}

/*****************************************************************************\
 * PriorityIterator::PIBase                                                  *
\*****************************************************************************/

PriorityIterator::PIBase::~PIBase(void)
{
}

/*****************************************************************************\
 * PriorityIterator::PIEnter                                                 *
\*****************************************************************************/

PriorityIterator::PIEnter::~PIEnter(void)
{
}

void
PriorityIterator::PIEnter::preTraversal(void)
{
    FDEBUG(("PriorityIterator::PIEnter::preTraversal \n"));

    while(_pqueue.empty() == false)
        _pqueue.pop();
}

void
PriorityIterator::PIEnter::postTraversal(void)
{
    FDEBUG(("PriorityIterator::PIEnter::postTraversal \n"));
}

PriorityIterator::ResultE
PriorityIterator::PIEnter::traverse(NodePtr pRoot)
{
    FDEBUG(("PriorityIterator::PIEnter::traverse. \n"));

    _pqueue.push(PQEntry(pRoot, TypeTraits<PriorityType>::getMax()));

    while(_pqueue.empty() == false)
    {
        getIter()->resetNodeList();

        getIter()->setResult(
            ResultE(getIter()->getResult(                       ) | 
                    getIter()->callEnter(_pqueue.top().getNode())  ));

        pushChildren();
    }

    return getIter()->getResult();
}

void
PriorityIterator::PIEnter::receiveStateRead(UInt32 OSG_CHECK_ARG(uiActorId))
{
}

void
PriorityIterator::PIEnter::receiveStateWrite(UInt32 OSG_CHECK_ARG(uiActorId))
{
}

void
PriorityIterator::PIEnter::pushChildren(void)
{
    if(getIter()->getUseNodeList() == true)
    {
        ActiveNodeListIt itNodes = getIter()->beginNodes();
        ActiveNodeListIt end     = getIter()->endNodes  ();

        _pqueue.pop();

        for(; itNodes != end; ++itNodes)
        {
            _pqueue.push(PQEntry(itNodes.getNode(), itNodes.getPriority()));
        }
    }
    else
    {
        MFNodePtr::iterator itNodes = 
            getIter()->getCurrentNode()->getMFChildren()->begin();
        MFNodePtr::iterator end     =
            getIter()->getCurrentNode()->getMFChildren()->end  ();

        _pqueue.pop();

        for(; itNodes != end; ++itNodes)
        {
            _pqueue.push(PQEntry(*itNodes, PriorityType()));
        }
    }
}

/*****************************************************************************\
 * PriorityIterator::PILeave                                                 *
\*****************************************************************************/

PriorityIterator::PILeave::~PILeave(void)
{
}

void
PriorityIterator::PILeave::preTraversal(void)
{
    FDEBUG(("PriorityIterator::PILeave::preTraversal \n"));

    while(_pqueue.empty() == false)
        _pqueue.pop();

    _leaveList.clear();
}

void
PriorityIterator::PILeave::postTraversal(void)
{
    FDEBUG(("PriorityIterator::PILeave::postTraversal \n"));
}

PriorityIterator::ResultE
PriorityIterator::PILeave::traverse(NodePtr pRoot)
{
    FDEBUG(("PriorityIterator::PILeave::traverse. \n"));
    
    _pqueue.push(PQEntry(pRoot,          TypeTraits<PriorityType>::getMax(),
                         _leaveList.end()                                   ));

    while(_pqueue.empty() == false)
    {
        getIter()->resetNodeList();

        getIter()->setResult(
            ResultE(getIter()->getResult(                       ) | 
                    getIter()->callEnter(_pqueue.top().getNode())  ));

        if((getIter()->getUseNodeList()              == true && 
            getIter()->getNodeList().getNumActive()  == 0      ) ||
           (_pqueue.top().getNode()->getNChildren()  == 0      )   )
        {
            NodePtr     pNode = _pqueue   .top().getNode            ();
            LeaveListIt it    = _pqueue   .top().getParentLeaveEntry();
            LeaveListIt end   = _leaveList.end();

            getIter()->setResult(ResultE(getIter()->getResult(     ) |
                                         getIter()->callLeave(pNode)  ));

            _pqueue.pop();

            while((it != end) && (it->decPending() == 0))
            {
                pNode   = pNode->getParent();
                it      = it   ->getParent();
                
                getIter()->setResult(ResultE(getIter()->getResult(     ) | 
                                             getIter()->callLeave(pNode)  ));
            }
        }
        else
        {
            pushChildren();
        }
    }

    return getIter()->getResult();
}

void
PriorityIterator::PILeave::receiveStateRead(UInt32)
{
}

void
PriorityIterator::PILeave::receiveStateWrite(UInt32)
{
}

void
PriorityIterator::PILeave::pushChildren(void)
{
    if(getIter()->getUseNodeList() == true)
    {
        _leaveList.push_back(
            LeaveEntry(getIter()->getNodeList().getNumActive(),
                       _pqueue.top().getParentLeaveEntry    () ));

        LeaveListIt      itLeave = --(_leaveList.end());
        ActiveNodeListIt itNodes = getIter()->beginNodes();
        ActiveNodeListIt end     = getIter()->endNodes  ();

        _pqueue.pop();

        for(; itNodes != end; ++itNodes)
        {
            _pqueue.push(PQEntry(itNodes.getNode(), itNodes.getPriority(),
                                 itLeave                                  ));
        }
    }
    else
    {
        _leaveList.push_back(
            LeaveEntry(getIter()->getCurrentNode()->getNChildren       (),
                       _pqueue.top              (). getParentLeaveEntry()));

        LeaveListIt         itLeave = --(_leaveList.end());
        MFNodePtr::iterator itNodes = 
            getIter()->getCurrentNode()->getMFChildren()->begin();
        MFNodePtr::iterator end     =
            getIter()->getCurrentNode()->getMFChildren()->end  ();

        _pqueue.pop();
        
        for(; itNodes != end; ++itNodes)
        {
            _pqueue.push(PQEntry(*itNodes, PriorityType(), itLeave));
        }
    }
}

/*****************************************************************************\
 * PriorityIterator::PIEnterOrd                                              *
\*****************************************************************************/

PriorityIterator::PIEnterOrd::~PIEnterOrd(void)
{
    freeStateList();
}

void
PriorityIterator::PIEnterOrd::preTraversal(void)
{
    FDEBUG(("PriorityIterator::PIEnterOrd::preTraversal \n"));

    while(_pqueue.empty() == false)
        _pqueue.pop();

    _stateList.clear();

    _bStateValid = true;
    _bStateSaved = true;
}

void
PriorityIterator::PIEnterOrd::postTraversal(void)
{
    FDEBUG(("PriorityIterator::PIEnterOrd::postTraversal \n"));
    
    freeStateList();

    _bStateValid = false;
    _bStateSaved = true;
}

PriorityIterator::ResultE
PriorityIterator::PIEnterOrd::traverse(NodePtr pRoot)
{
    FDEBUG(("PriorityIterator::PIEnterOrd::traverse. \n"));

    _stateList.push_front(ActorStateChunk(getIter()->getNumActors()));

    _currState = _stateList.begin();

    getIter()->getState(&(*_currState));

    _pqueue.push(PQEntry(pRoot,      TypeTraits<PriorityType>::getMax(),
                         _currState                                     ));

    while(_pqueue.empty() == false)
    {
        getIter()->resetNodeList();

        if(_pqueue.top().getNode()->getParent() != getIter()->getCurrentNode())
        {
            _bStateValid = false;
            _currState   = _pqueue.top().getParentState();
        }

        _bStateSaved = false;

        getIter()->setResult(
            ResultE(getIter()->getResult(                       ) | 
                    getIter()->callEnter(_pqueue.top().getNode())  ));

        pushChildren();
    }

    return getIter()->getResult();
}

void
PriorityIterator::PIEnterOrd::receiveStateRead(UInt32)
{
    if(_bStateValid == false)
    {
        FDEBUG(("PI::PIEnterOrd: RESTORING STATE.\n"));

        _bStateValid = true;

        getIter()->setState(&(*_currState));
    }
}

void
PriorityIterator::PIEnterOrd::receiveStateWrite(UInt32 uiActorId)
{
    receiveStateRead(uiActorId);

    if(_bStateSaved == false)
    {
        FDEBUG(("PI::PIEnterOrd: SAVING STATE.\n"));

        _bStateSaved = true;

        _stateList.push_back(ActorStateChunk(getIter()->getNumActors()));

        _currState = --(_stateList.end());

        getIter()->cloneState(&(*_currState));
    }
}

void
PriorityIterator::PIEnterOrd::pushChildren(void)
{
    if(getIter()->getUseNodeList() == true)
    {
        ActiveNodeListIt itNodes = getIter()->beginNodes();
        ActiveNodeListIt end     = getIter()->endNodes  ();

        _pqueue.pop();

        for(; itNodes != end; ++itNodes)
        {
            _pqueue.push(PQEntry(itNodes.getNode(), itNodes.getPriority(),
                                 _currState                               ));
        }
    }
    else
    {
        MFNodePtr::iterator itNodes =
            getIter()->getCurrentNode()->getMFChildren()->begin();
        MFNodePtr::iterator end     =
            getIter()->getCurrentNode()->getMFChildren()->end  ();

        _pqueue.pop();
        
        for(; itNodes != end; ++itNodes)
        {
            _pqueue.push(PQEntry(*itNodes, PriorityType(), _currState));
        }
    }
}

void
PriorityIterator::PIEnterOrd::freeStateList(void)
{
    StateListIt itState  = _stateList.begin();
    StateListIt endState = _stateList.end  ();

    for(; itState != endState; ++itState)
    {
        if(itState != _currState)
        {
            itState->freeAll();
        }
    }
}

/*****************************************************************************\
 * PriorityIterator::PILeaveOrd                                              *
\*****************************************************************************/

PriorityIterator::PILeaveOrd::~PILeaveOrd(void)
{
    freeStateList();
}

void
PriorityIterator::PILeaveOrd::preTraversal(void)
{
    FDEBUG(("PriorityIterator::PILeaveOrd::preTraversal \n"));

    while(_pqueue.empty() == false)
        _pqueue.pop();

    _leaveList.clear();
    _stateList.clear();

    _bStateValid = true;
    _bStateSaved = true;
}

void
PriorityIterator::PILeaveOrd::postTraversal(void)
{
    FDEBUG(("PriorityIterator::PILeaveOrd::postTraversal \n"));

    freeStateList();

    _bStateValid = false;
    _bStateSaved = true; 
}

PriorityIterator::ResultE
PriorityIterator::PILeaveOrd::traverse(NodePtr pRoot)
{
    FDEBUG(("PriorityIterator::PILeaveOrd::traverse. \n"));

    _stateList.push_front(ActorStateChunk(getIter()->getNumActors()));

    _currState = _stateList.begin();
    
    getIter()->getState(&(*_currState));

    _pqueue.push(
        PQEntry(pRoot,            TypeTraits<PriorityType>::getMax(),
                _leaveList.end(), _currState                         ));

    while(_pqueue.empty() == false)
    {
        getIter()->resetNodeList();

        if(_pqueue.top().getNode()->getParent() != getIter()->getCurrentNode())
        {
            _bStateValid = false;
            _currState   = _pqueue.top().getParentState();
        }

        _bStateSaved = false;

        getIter()->setResult(
            ResultE(getIter()->getResult(                       ) | 
                    getIter()->callEnter(_pqueue.top().getNode())  ));

        if((getIter()->getUseNodeList()              == true && 
            getIter()->getNodeList().getNumActive()  == 0       ) ||
           (_pqueue.top().getNode()->getNChildren()  == 0       )    )
        {
            NodePtr     pNode = _pqueue   .top().getNode            ();
            LeaveListIt it    = _pqueue   .top().getParentLeaveEntry();
            LeaveListIt end   = _leaveList.end();

            getIter()->setResult(ResultE(getIter()->getResult(     ) | 
                                         getIter()->callLeave(pNode)  ));

            _pqueue.pop();

            while((it != end) && (it->decPending() == 0))
            {
                _currState   = it   ->getState ();
                pNode        = pNode->getParent();
                it           = it   ->getParent();
                _bStateValid = false;

                getIter()->setResult(ResultE(getIter()->getResult(     ) | 
                                             getIter()->callLeave(pNode)  ));
            }
        }
        else
        {
            pushChildren();
        }
    }

    return getIter()->getResult();
}

void
PriorityIterator::PILeaveOrd::receiveStateRead(UInt32)
{
    if(_bStateValid == false)
    {
        FDEBUG(("PILeaveOrd::sigRead: RESTORING State.\n"));

        _bStateValid = true;
        
        getIter()->setState(&(*_currState));
    }
}

void
PriorityIterator::PILeaveOrd::receiveStateWrite(UInt32 uiActorId)
{
    receiveStateRead(uiActorId);

    if(_bStateSaved == false)
    {
        FDEBUG(("PILeaveOrd::sigWrite: SAVING State.\n"));

        _bStateSaved = true;

        _stateList.push_back(ActorStateChunk(getIter()->getNumActors()));

        _currState = --(_stateList.end());

        getIter()->cloneState(&(*_currState));
    }
}

void
PriorityIterator::PILeaveOrd::pushChildren(void)
{
    if(getIter()->getUseNodeList() == true)
    {
        _leaveList.push_back(
            LeaveEntry(getIter()->getNodeList().getNumActive(),
                       _pqueue.top().getParentLeaveEntry   (),
                       _currState                             ));
        
        LeaveListIt      itLeave = --(_leaveList.end());
        ActiveNodeListIt itNodes = getIter()->beginNodes();
        ActiveNodeListIt end     = getIter()->endNodes  ();

        _pqueue.pop();

        for(; itNodes != end; ++itNodes)
        {
            _pqueue.push(PQEntry(itNodes.getNode(), itNodes.getPriority(),
                                 itLeave,           _currState            ));
        }   
    }
    else
    {
        _leaveList.push_back(
            LeaveEntry(getIter()->getCurrentNode()->getNChildren       (),
                       _pqueue.top()             .  getParentLeaveEntry(),
                       _currState                                         ));

        LeaveListIt         itLeave = --(_leaveList.end());
        MFNodePtr::iterator itNodes = 
            getIter()->getCurrentNode()->getMFChildren()->begin();
        MFNodePtr::iterator end     =
            getIter()->getCurrentNode()->getMFChildren()->end  ();

        _pqueue.pop();

        for(; itNodes != end; ++itNodes)
        {
            _pqueue.push(
                PQEntry(*itNodes, PriorityType(), itLeave, _currState));
        }
    }
}

void
PriorityIterator::PILeaveOrd::freeStateList(void)
{
    StateListIt itState  = _stateList.begin();
    StateListIt endState = _stateList.end  ();

    for(; itState != endState; ++itState)
    {
        if(itState != _currState)
        {
            itState->freeAll();
        }
    }
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGPriorityIterator.cpp,v 1.3 2003/10/15 09:31:29 vossg Exp $";
    static Char8 cvsid_hpp       [] = OSGPRIORITYITERATOR_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPRIORITYITERATOR_INLINE_CVSID;
}

