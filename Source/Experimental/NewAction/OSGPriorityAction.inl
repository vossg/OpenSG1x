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

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*    PriorityAction::StateUseCounter                                      */

/*! Constructor.
 */

inline
PriorityAction::StateUseCounter::StateUseCounter(
    StateStoreIt itState, Int32 iUseCount)

    : _itState  (itState  ),
      _iUseCount(iUseCount)
{
}

/*! Copy constructor.
 *  \warning Using this will screw up the use counting and likely result in
 *  desaster.
 *  It only exists to initialize elements in an stl container.
 */

inline
PriorityAction::StateUseCounter::StateUseCounter(
    const StateUseCounter &source)

    : _itState  (source._itState  ),
      _iUseCount(source._iUseCount)
{
}

/*! Returns the iterator into the StateStore.
 */

inline PriorityAction::StateStoreIt
PriorityAction::StateUseCounter::getState(void) const
{
    return _itState;
}

/*! Sets the iterator into the StateStore.
 */

inline void
PriorityAction::StateUseCounter::setState(StateStoreIt itState)
{
    _itState = itState;
}

/*! Returns the number of users.
 */

inline Int32
PriorityAction::StateUseCounter::getUseCount(void) const
{
    return _iUseCount;
}

/*! Increase the use count by iUse.
 */

inline void
PriorityAction::StateUseCounter::addUse(Int32 iUse)
{
    _iUseCount += iUse;
}

/*! Decrease the use count by iUse.
 */

inline void
PriorityAction::StateUseCounter::subUse(Int32 iUse)
{
    _iUseCount -= iUse;
}

/*-------------------------------------------------------------------------*/
/*    PriorityAction::NodeQueueEntry                                       */

inline
PriorityAction::NodeQueueEntry::NodeQueueEntry(
    const NodePtr &pNode, PriorityType priority, StateUseStoreIt itState)
    : _pNode   (pNode   ),
      _priority(priority),
      _itState (itState )
{
}

inline
PriorityAction::NodeQueueEntry::NodeQueueEntry(
    const NodePtr &pNode, PriorityType priority)
    : _pNode   (pNode   ),
      _priority(priority),
      _itState (        )
{
}

inline NodePtr
PriorityAction::NodeQueueEntry::getNode(void) const
{
    return _pNode;
}

inline void
PriorityAction::NodeQueueEntry::setNode(const NodePtr &pNode)
{
    _pNode = pNode;
}

inline PriorityAction::PriorityType
PriorityAction::NodeQueueEntry::getPriority(void) const
{
    return _priority;
}

inline void
PriorityAction::NodeQueueEntry::setPriority(PriorityType priority)
{
    _priority = priority;
}

inline PriorityAction::StateUseStoreIt
PriorityAction::NodeQueueEntry::getState(void) const
{
    return _itState;
}

inline void
PriorityAction::NodeQueueEntry::setState(StateUseStoreIt itState)
{
    _itState = itState;
}

/*-------------------------------------------------------------------------*/
/*    PriorityAction::NodeQueueEntry::LessCompare                          */

/*! STL function object to compare two NodeQueueEntry.
 */

inline bool
PriorityAction::NodeQueueEntry::LessCompare::operator()(
    const NodeQueueEntry &lhs, const NodeQueueEntry &rhs)
{
    return (lhs.getPriority() < rhs.getPriority());
}

/*-------------------------------------------------------------------------*/
/*    PriorityAction                                                       */

/*! Call the applyEnter method of all actors.
 */

inline PriorityAction::ResultE
PriorityAction::callEnter(const NodePtr &pNode)
{
    ResultE           result      = NewActionTypes::Continue;
    ActorStoreIt      itActors    = beginActors();
    ActorStoreConstIt endItActors = endActors  ();

    for(; (itActors != endItActors) && !(result & NewActionTypes::Quit);
        ++itActors                                                      )
    {
        result = static_cast<ResultE>(result |
                                      itActors->getActor()->applyEnter(pNode));
    }

    return result;
}

/*! Delete the state and remove the StateStore entry.
 */

inline void
PriorityAction::deleteState(StateStore *pStore, StateUseStoreIt itState)
{
    for(UInt32 i = getNumActors(); i > 0; --i, itState)
    {
        delete      *(itState->getState());  // delete the ActorState

        pStore->erase(itState->getState());  // remove the Ptr
    }
}

/*! Add users to the state.
 */

inline void
PriorityAction::addStateUse(StateUseStoreIt itState, Int32 iUse)
{
    itState->addUse(iUse);
}

/*! Subtract users from the state, if no users are left delete the state
 *  and erase the StateUseStore entry.
 */

inline void
PriorityAction::subStateUse(StateUseStoreIt itState, Int32 iUse)
{
    itState->subUse(iUse);

    if(itState->getUseCount() <= 0)
    {
        deleteState(&_stateStore, itState);

        _stateUseStore.erase(itState);
    }
}

/*! Clone the state of all actors and use the clone. Pointer to the cloned
 *  state are store in pStore before itPos. Returns an iterator to the
 *  first actor's state.
 */

inline PriorityAction::StateStoreIt
PriorityAction::cloneState(StateStore *pStore, StateStoreIt itPos)
{
    ActorStoreIt itActors    = beginActors();
    ActorStoreIt endItActors = endActors  ();

    StateStoreIt itState     = itPos;

    for(; itActors != endItActors; ++itActors)
    {
        pStore->insert(itPos,
                       itActors->getActor()->getStatePtr()->clone(NULL));

        --itPos;

        itActors->getActor()->setStatePtr(*itPos);
    }

    return --itState;
}

/*! Get the state pointer of all actors and store them before itPos in
    pStore. Returns an iterator to the first actor's state.
 */

inline PriorityAction::StateStoreIt
PriorityAction::getState(StateStore *pStore, StateStoreIt itPos)
{
    ActorStoreIt itActors    = beginActors();
    ActorStoreIt endItActors = endActors  ();

    StateStoreIt itState     = itPos;

    for(; itActors != endItActors; ++itActors, --itPos)
    {
        pStore->insert(itPos, itActors->getActor()->getStatePtr());
    }

    return --itState;
}

/*! Set the state pointer of all actors to the values stored at/before itPos.
 */

inline void
PriorityAction::setState(StateStoreIt itPos)
{
    ActorStoreIt itActors    = beginActors();
    ActorStoreIt endItActors = endActors  ();

    for(; itActors != endItActors; ++itActors, --itPos)
    {
        itActors->getActor()->setStatePtr(*itPos);
    }
}

/*! Insert the children of the current node into the priority queue.
 *  If the active children list was enabled only active children will
 *  be inserted.
 */

inline void
PriorityAction::enqueueChildren(const NodePtr &pNode, ResultE result)
{
    // Do we add any children ?
    if(result & (NewActionTypes::Skip | NewActionTypes::Quit))
    {
        // traversed node does not use state anymore
        subStateUse(_itCurrentState);

        return;
    }

    // Do we use the active list ?
    if(getUseActiveChildrenList() == true)
    {
        ActiveChildrenList *pACL = getActiveChildrenList();

        ActiveChildrenList::MFNodePtrConstIt itChildren    =
            pACL->beginChildren();
        ActiveChildrenList::MFNodePtrConstIt endItChildren =
            pACL->endChildren  ();

        // children use state
        addStateUse(_itCurrentState, pACL->getNumActive());

        for(UInt32 uiChildIndex = 0; itChildren != endItChildren;
            ++itChildren, ++uiChildIndex                         )
        {
            if(pACL->getActive(uiChildIndex) == true)
            {
                _nodePrioQueue.push(
                        NodeQueueEntry(*itChildren,
                                       pACL->getPriority(uiChildIndex),
                                       _itCurrentState                  ));
            }
        }

        // traversed node does not use state anymore
        subStateUse(_itCurrentState);
    }
    else
    {
        MFNodePtr::const_iterator itChildren    =
            pNode->getMFChildren()->begin();
        MFNodePtr::const_iterator endItChildren =
            pNode->getMFChildren()->end  ();

        // children use state
        addStateUse(_itCurrentState, pNode->getNChildren());

        for(; itChildren != endItChildren; ++itChildren)
        {
            _nodePrioQueue.push(
                    NodeQueueEntry(*itChildren,
                                   TypeTraits<PriorityType>::getZeroElement(),
                                   _itCurrentState                           ));
        }

        // traversed node does not use state anymore
        subStateUse(_itCurrentState);
    }
}

OSG_END_NAMESPACE

#define OSGPRIORITYACTION_INLINE_CVSID "@(#)$Id: OSGPriorityAction.inl,v 1.2 2004/04/21 12:15:20 neumannc Exp $"
