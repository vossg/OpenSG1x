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

#include "OSGPriorityAction.h"

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*/
/*    Create                                                               */

/*! Return a new instance of PriorityAction.
 */

PriorityAction *
PriorityAction::create(void)
{
    return new PriorityAction();
}

/*-------------------------------------------------------------------------*/
/*    Destructor                                                           */

PriorityAction::~PriorityAction(void)
{
}

/*-------------------------------------------------------------------------*/
/*    Apply                                                                */

PriorityAction::ResultE
PriorityAction::apply(const NodePtr &pRootNode, PriorityType priority)
{
    ResultE         result            = NewActionTypes::Continue;
    StateUseStoreIt itStateUseStore;
    StateUseStoreIt endStateUseStore;

    Inherited::apply(pRootNode, priority);

    // start up the actors
    result = startActors();

    if(result == NewActionTypes::Continue)
    {
        NodeListConstIt itRootNodes    = beginRootNodes();
        NodeListConstIt endItRootNodes = endRootNodes  ();

        // Store the initial state ptr
        getState(&_stateStore, _stateStore.end());

        _itInitialState =   --(_stateStore.end());

        // Clone the inital state
        _stateUseStore.push_back(
            StateUseCounter(cloneState(&_stateStore, _stateStore.end()), 1));

        _itCurrentState = --(_stateUseStore.end());

        // Move the root nodes into the pqueue
        for(; itRootNodes != endItRootNodes; ++itRootNodes)
        {
            // each root node uses the cloned inital state
            addStateUse(_itCurrentState);

            _nodePrioQueue.push(NodeQueueEntry(itRootNodes->getNode    (),
                                               itRootNodes->getPriority(),
                                               _itCurrentState            ));
        }

        getRootNodes().clear();

        // run the traversal
        result = applyEnter();
    }

    if(result == NewActionTypes::Continue)
    {
        result = stopActors();
    }

    setState(_itInitialState);

    // Initial state is now current
    subStateUse(_itCurrentState);

    // Clean up any remaining state - be careful not to delete the initial
    // state.
    itStateUseStore  = _stateUseStore.begin();
    endStateUseStore = _stateUseStore.end  ();

    for(; itStateUseStore != endStateUseStore; ++itStateUseStore)
    {
        deleteState(&_stateStore, itStateUseStore);
    }

    _stateStore.clear();

    // std::priority_queue<> does not have clear :(
    while(_nodePrioQueue.empty() == false)
    {
        _nodePrioQueue.pop();
    }

    return result;
}

PriorityAction::ResultE
PriorityAction::apply(NodeListConstIt begin, NodeListConstIt end)
{
    ResultE         result           = NewActionTypes::Continue;
    StateUseStoreIt itStateUseStore;
    StateUseStoreIt endStateUseStore;

    Inherited::apply(begin, end);

    // start up the actors
    result = startActors();

    if(result == NewActionTypes::Continue)
    {
        NodeListConstIt itRootNodes    = beginRootNodes();
        NodeListConstIt endItRootNodes = endRootNodes  ();

        // Store the initial state ptr
        getState(&_stateStore, _stateStore.end());

        _itInitialState =   --(_stateStore.end());

        // Clone the inital state
        _stateUseStore.push_back(
            StateUseCounter(cloneState(&_stateStore, _stateStore.end()), 1));

        _itCurrentState = --(_stateUseStore.end());

        // Move the root nodes into the pqueue
        for(; itRootNodes != endItRootNodes; ++itRootNodes)
        {
            // each root node uses the cloned inital state
            addStateUse(_itCurrentState);

            _nodePrioQueue.push(NodeQueueEntry(itRootNodes->getNode    (),
                                               itRootNodes->getPriority(),
                                               _itCurrentState            ));
        }

        getRootNodes().clear();

        // run the traversal
        result = applyEnter();
    }

    if(result == NewActionTypes::Continue)
    {
        result = stopActors();
    }

    setState(_itInitialState);

    // Initial state is now current
    subStateUse(_itCurrentState);

    // Clean up any remaining state - be careful not to delete the initial
    // state.
    itStateUseStore  = _stateUseStore.begin();
    endStateUseStore = _stateUseStore.end  ();

    for(; itStateUseStore != endStateUseStore; ++itStateUseStore)
    {
        deleteState(&_stateStore, itStateUseStore);
    }

    _stateStore.clear();

    // std::priority_queue<> does not have clear :(
    while(_nodePrioQueue.empty() == false)
    {
        _nodePrioQueue.pop();
    }

    return result;
}

/*-------------------------------------------------------------------------*/
/*    Constructors                                                         */

PriorityAction::PriorityAction(void)
    : _nodePrioQueue (                    ),
      _bStateCloned  (false               ),
      _stateUseStore (                    ),
      _stateStore    (                    ),
      _itCurrentState(_stateUseStore.end()),
      _itInitialState(_stateStore   .end())
{
}

/*-------------------------------------------------------------------------*/
/*    Events                                                               */

void
PriorityAction::attachEvent(ActorBase *pActor, UInt32 uiActorId)
{
    Inherited::attachEvent(pActor, uiActorId);
}

void
PriorityAction::detachEvent(ActorBase *pActor, UInt32 uiActorId)
{
    Inherited::detachEvent(pActor, uiActorId);
}

void
PriorityAction::beginEditStateEvent(ActorBase *pActor, UInt32 uiActorId)
{
    if(_bStateCloned == false)
    {
        _bStateCloned = true;

        _stateUseStore.push_back(
            StateUseCounter(cloneState(&_stateStore, _stateStore.end()), 2));

        subStateUse(_itCurrentState); // the clone is current now
        subStateUse(_itCurrentState); // the traversed node uses the clone now

        _itCurrentState = --(_stateUseStore.end());
    }
}

void
PriorityAction::endEditStateEvent(ActorBase *pActor, UInt32 uiActorId)
{
}

/*-------------------------------------------------------------------------*/
/*    Helper Methods                                                       */

PriorityAction::ResultE
PriorityAction::applyEnter(void)
{
    ResultE result   = NewActionTypes::Continue;
    NodePtr currNode = NullFC;

    while( (_nodePrioQueue.empty() == false) &&
          !(result & NewActionTypes::Quit  )    )
    {
        const NodeQueueEntry &topEntry = _nodePrioQueue.top();
        currNode                       = topEntry.getNode();

        if( (currNode                                 == NullFC) ||
           ((currNode->getTravMask() & getTravMask()) == 0     )   )
        {
            // traversed node does not use state anymore
            subStateUse(topEntry.getState());

            _nodePrioQueue.pop();
        }
        else
        {
            // set state if necessary
            if(topEntry.getState() != _itCurrentState)
            {
                setState(topEntry.getState()->getState());

                subStateUse(_itCurrentState);
                _itCurrentState = topEntry.getState();
                addStateUse(_itCurrentState);
            }

            _bStateCloned = false;
            setUseActiveChildrenList(false);
            getActiveChildrenList   (     )->setParentNode(currNode);

            result = static_cast<ResultE>(NewActionTypes::Continue |
                                          callEnter(currNode)       );

            _nodePrioQueue.pop();

            enqueueChildren(currNode, result);
        }
    }

    return result;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGPriorityAction.cpp,v 1.1 2004/04/20 13:47:08 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGPRIORITYACTION_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPRIORITYACTION_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
