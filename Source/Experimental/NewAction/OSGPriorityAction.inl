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

//----------------------------------------------------------------------------
//    Includes
//----------------------------------------------------------------------------

#include "OSGExtendActorBase.h"
#include "OSGBasicActorBase.h"

OSG_BEGIN_NAMESPACE

//----------------------------------------------------------------------------
//    Types
//----------------------------------------------------------------------------

#ifdef OSG_NEWACTION_STATESLOTINTERFACE

/*! Copy constructor.

\dev
    \warning You must not copy StateRefCount objects, the constructor is only
    here to put instances into an STL container.
\enddev
 */

inline
PriorityAction::StateRefCount::StateRefCount(const StateRefCount &source)
    : _stateSlot(source._stateSlot),
      _refCount (source._refCount )
{
}

/*! Constructor.

\dev
    The ref count is initalized to 0.
\enddev
 */

inline
PriorityAction::StateRefCount::StateRefCount(UInt32 stateSlot)
    : _stateSlot(stateSlot),
      _refCount (0        )
{
}

/*! Constructor.
 */

inline
PriorityAction::StateRefCount::StateRefCount(UInt32 stateSlot, Int32 refCount)
    : _stateSlot(stateSlot),
      _refCount (refCount )
{
}

/*! Return the state slot.
 */

inline UInt32
PriorityAction::StateRefCount::getStateSlot(void) const
{
    return _stateSlot;
}

/* Set the state slot.
 */

inline void
PriorityAction::StateRefCount::setStateSlot(UInt32 stateSlot)
{
    _stateSlot = stateSlot;
}

/*! Return the ref count.
 */

inline Int32
PriorityAction::StateRefCount::getRefCount(void) const
{
    return _refCount;
}

/*! Increment the ref count by ref.
 */

inline void
PriorityAction::StateRefCount::incRefCount(Int32 inc)
{
    _refCount += inc;
}

/*! Decrement the ref count by ref.
 */

inline void
PriorityAction::StateRefCount::decRefCount(Int32 dec)
{
    _refCount -= inc;
}

#else /* OSG_NEWACTION_STATESLOTINTERFACE */

/*! Copy constructor.

\dev
    \warning You must not copy StateRefCount objects, the constructor is only
    here to put instances into an STL container.
\enddev
 */

inline
PriorityAction::StateRefCount::StateRefCount(const StateRefCount &source)
    : _itState (source._itState ),
      _refCount(source._refCount)
{
}

/*! Constructor.

\dev
    The ref count is initalized to 0.
\enddev
 */

inline
PriorityAction::StateRefCount::StateRefCount(const StateStoreIt &itState)
    : _itState (itState),
      _refCount(0      )
{
}

/*! Constructor.
 */

inline
PriorityAction::StateRefCount::StateRefCount(
    const StateStoreIt &itState, Int32 refCount)

    : _itState (itState ),
      _refCount(refCount)
{
}

/*! Return the state store iterator.
 */

inline PriorityAction::StateStoreIt
PriorityAction::StateRefCount::getState(void) const
{
    return _itState;
}

/*! Set the state store iterator.
 */

inline void
PriorityAction::StateRefCount::setState(const StateStoreIt &itState)
{
    _itState = itState;
}

/*! Return the ref count.
 */

inline Int32
PriorityAction::StateRefCount::getRefCount(void) const
{
    return _refCount;
}

/*! Increment the ref count.
 */

inline void
PriorityAction::StateRefCount::incRefCount(Int32 inc)
{
    _refCount += inc;
}

/*! Decrement the ref count.
 */

inline void
PriorityAction::StateRefCount::decRefCount(Int32 dec)
{
    _refCount -= dec;
}

#endif /* OSG_NEWACTION_STATESLOTINTERFACE */

/*! Copy constructor.

\dev
    \warning You must not copy NodeQueueEntry objects, the constructor is only
    here to put instances into an STL container.
\enddev
 */

inline
PriorityAction::NodeQueueEntry::NodeQueueEntry(const NodeQueueEntry &source)
    : _pNode          (source._pNode          ),
      _priority       (source._priority       ),
      _itStateRefCount(source._itStateRefCount)
{
}

/*! Constructor.
 */

inline
PriorityAction::NodeQueueEntry::NodeQueueEntry(
    const NodePtr              &pNode,
          PriorityType          priority,
          UInt32                passCount,
    const StateRefCountStoreIt &itStateRefCount)

    : _pNode          (pNode          ),
      _priority       (priority       ),
      _passCount      (passCount      ),
      _itStateRefCount(itStateRefCount)
{
}

/*! Return the node.
 */

inline NodePtr
PriorityAction::NodeQueueEntry::getNode(void) const
{
    return _pNode;
}

/*! Return the priority.
 */

inline PriorityAction::PriorityType
PriorityAction::NodeQueueEntry::getPriority(void) const
{
    return _priority;
}

/*! Return the pass count.
 */

inline UInt32
PriorityAction::NodeQueueEntry::getPassCount(void) const
{
    return _passCount;
}

/*! Return the iterator to the state ref count.
 */

inline PriorityAction::StateRefCountStoreIt
PriorityAction::NodeQueueEntry::getStateRefCount(void) const
{
    return _itStateRefCount;
}

/*! STL compare function object.
 */

inline bool
PriorityAction::NodeQueueEntry::LessCompare::operator()(
    const NodeQueueEntry &leftArg, const NodeQueueEntry &rightArg)
{
    return (leftArg.getPriority() < rightArg.getPriority());
}

//----------------------------------------------------------------------------
//    Helper Methods
//----------------------------------------------------------------------------

/*! Calls the enterNode method of the attached actors.
 */

inline PriorityAction::ResultE
PriorityAction::enterNode(const NodePtr &pNode, UInt32 pass)
{
    FunctorArgumentType funcArg(NULL, pNode, pass);
    ResultE             result     = NewActionTypes::Continue;
    
    ExtendActorStoreIt itExtend    = _extendEnterActors.begin();
    ExtendActorStoreIt endItExtend = _extendEnterActors.end  ();

    for(;  (itExtend != endItExtend                                 )  &&
          !(result   & (NewActionTypes::Break | NewActionTypes::Quit));
        ++itExtend                                                       )
    {
        funcArg.setActor(*itExtend);
        
        result = static_cast<ResultE>(result | (*itExtend)->enterNode(funcArg));
    }

    BasicActorStoreIt  itBasic     = beginBasic ();
    BasicActorStoreIt  endItBasic  = endBasic   ();

    for(;  (itBasic != endItBasic                                  )  &&
          !(result  & (NewActionTypes::Break | NewActionTypes::Quit));
        ++itBasic                                                        )
    {
        funcArg.setActor(*itBasic);
        
        result = static_cast<ResultE>(result | (*itBasic)->enterNode(funcArg));
    }

    return result;
}

/*! Creates a copy of the state currently used by the attached actors.
 */

inline PriorityAction::StateRefCountStoreIt
PriorityAction::cloneState(void)
{
#ifdef OSG_NEWACTION_STATESLOTINTERFACE

    UInt32               stateSlot;
    StateRefCountStoreIt itStateRefCount = --(_stateRefCountStore.end());

    ExtendActorStoreIt   itExtend        =    _extendEnterActors.begin();
    ExtendActorStoreIt   endExtend       =    _extendEnterActors.end  ();

    for(; itExtend != endExtend; ++itExtend)
    {
        stateSlot = (*itExtend)->createStateClone();
    }

    BasicActorStoreIt itBasic  = _basicEnterActors.begin();
    BasicActorStoreIt endBasic = _basicEnterActors.end  ();

    for(; itBasic != endBasic; ++itBasic)
    {
        stateSlot = (*itBasic)->createStateClone();
    }

    _stateRefCountStore.push_back(StateRefCount(stateSlot));

    return ++itStateRefCount;

#else  /* OSG_NEWACTION_STATESLOTINTERFACE */

    StateStoreIt         itState         = --(_stateStore        .end  ());
    StateRefCountStoreIt itStateRefCount = --(_stateRefCountStore.end  ());

    ExtendActorStoreIt   itExtend        =    _extendEnterActors .begin();
    ExtendActorStoreIt   endItExtend     =    _extendEnterActors .end  ();

    for(; itExtend != endItExtend; ++itExtend)
    {
        _stateStore.push_back((*itExtend)->createStateClone());
    }

    BasicActorStoreIt itBasic    = _basicEnterActors.begin();
    BasicActorStoreIt endItBasic = _basicEnterActors.end  ();

    for(; itBasic != endItBasic; ++itBasic)
    {
        _stateStore.push_back((*itBasic)->createStateClone());
    }

    _stateRefCountStore.push_back(StateRefCount(++itState));

    return ++itStateRefCount;

#endif /* OSG_NEWACTION_STATESLOTINTERFACE */
}

/*! Stores the state currently used by the attached actors.
 */

inline PriorityAction::StateRefCountStoreIt
PriorityAction::getState(void)
{
#ifdef OSG_NEWACTION_STATESLOTINTERFACE

    UInt32               stateSlot;
    StateRefCountStoreIt itStateRefCount = --(_stateRefCountStore.end  ());

    ExtendActorStoreIt   itExtend        =    _extendEnterActors .begin();
    ExtendActorStoreIt   endItExtend     =    _extendEnterActors .end  ();

    for(; itExtend != endItExtend; ++itExtend)
    {
        stateSlot = (*itExtend)->getSlotMap().size();

        (*itExtend)->getSlotMap().push_back((*itExtend)->getState());
    }

    BasicActorStoreIt itBasic    = _basicEnterActors.begin();
    BasicActorStoreIt endItBasic = _basicEnterActors.end  ();

    for(; itBasic != endItBasic; ++itBasic)
    {
        stateSlot = (*itExtend)->getSlotMap().size();

        (*itExtend)->getSlotMap().push_back((*itExtend)->getState());
    }

    _stateRefCountStore.push_back(StateRefCount(stateSlot));

    return ++itStateRefCount;

#else  /* OSG_NEWACTION_STATESLOTINTERFACE */

    StateStoreIt         itState         = --(_stateStore        .end  ());
    StateRefCountStoreIt itStateRefCount = --(_stateRefCountStore.end  ());

    ExtendActorStoreIt   itExtend        =    _extendEnterActors .begin();
    ExtendActorStoreIt   endItExtend     =    _extendEnterActors .end  ();

    for(; itExtend != endItExtend; ++itExtend)
    {
        _stateStore.push_back((*itExtend)->getState());
    }

    BasicActorStoreIt itBasic    = _basicEnterActors.begin();
    BasicActorStoreIt endItBasic = _basicEnterActors.end  ();

    for(; itBasic != endItBasic; ++itBasic)
    {
        _stateStore.push_back((*itBasic)->getState());
    }

    _stateRefCountStore.push_back(StateRefCount(++itState));

    return ++itStateRefCount;

#endif /* OSG_NEWACTION_STATESLOTINTERFACE */
}

/*! Sets the state to use for the attached actors.
 */

inline void
PriorityAction::setState(StateRefCountStoreIt itStateRefCount)
{
#ifdef OSG_NEWACTION_STATESLOTINTERFACE

    UInt32             stateSlot   = itStateRefCount->getStateSlot();

    ExtendActorStoreIt itExtend    = _extendEnterActors.begin();
    ExtendActorStoreIt endItExtend = _extendEnterActors.end  ();

    for(; itExtend != endExtend; ++itExtend, ++itState)
    {
        (*itExtend)->setState((*itExtend)->getSlotMap()[stateSlot]);
    }

    BasicActorStoreIt itBasic    = _basicEnterActors.begin();
    BasicActorStoreIt endItBasic = _basicEnterActors.end  ();

    for(; itBasic != endItBasic; ++itBasic, ++itState)
    {
        (*itBasic)->setState((*itBasic)->getSlotMap()[stateSlot]);
    }

#else  /* OSG_NEWACTION_STATESLOTINTERFACE */

    StateStoreIt       itState     = itStateRefCount->getState();

    ExtendActorStoreIt itExtend    = _extendEnterActors.begin();
    ExtendActorStoreIt endItExtend = _extendEnterActors.end  ();

    for(; itExtend != endItExtend; ++itExtend, ++itState)
    {
        (*itExtend)->setState(*itState);
    }

    BasicActorStoreIt itBasic    = _basicEnterActors.begin();
    BasicActorStoreIt endItBasic = _basicEnterActors.end  ();

    for(; itBasic != endItBasic; ++itBasic, ++itState)
    {
        (*itBasic)->setState(*itState);
    }

#endif /* OSG_NEWACTION_STATESLOTINTERFACE */
}

/*! Increment the ref count by inc.
 */

inline void
PriorityAction::incRefCount(StateRefCountStoreIt itStateRefCount, Int32 inc)
{
    itStateRefCount->incRefCount(inc);
}

/*! Decrement the ref count by dec. If it reaches 0 the state is delete.
 */

inline void
PriorityAction::decRefCount(StateRefCountStoreIt itStateRefCount, Int32 dec)
{
#ifdef OSG_NEWACTION_STATESLOTINTERFACE

    itStateRefCount->decRefCount(dec);

    if(itStateRefCount->getRefCount() <= 0)
    {
        UInt32             stateSlot = itStateRefCount->getStateSlot();

        ExtendActorStoreIt itExtend  = _extendEnterActors.begin();
        ExtendActorStoreIt endExtend = _extendEnterActors.end  ();

        for(; itExtend != endExtend; ++itExtend)
        {
            delete (*itExtend)->getSlotMap()[stateSlot];

            //(*itExtend)->destroyStateClone(stateSlot);
        }

        BasicActorStoreIt itBasic  = _basicEnterActors.begin();
        BasicActorStoreIt endBasic = _basicEnterActors.end  ();

        for(; itBasic != endBasic; ++itBasic)
        {
            delete (*itBasic)->getSlotMap()[stateSlot];

            //(*itBasic)->destroyStateClone(stateSlot);
        }

        _stateRefCountStore.erase(itStateRefCount);
    }

#else /* OSG_NEWACTION_STATESLOTINTERFACE */

    itStateRefCount->decRefCount(dec);

    if(itStateRefCount->getRefCount() <= 0)
    {
        StateStoreIt       itState   = itStateRefCount->getState();

        ExtendActorStoreIt itExtend  = _extendEnterActors.begin();
        ExtendActorStoreIt endExtend = _extendEnterActors.end  ();

        for(; itExtend != endExtend; ++itExtend)
        {
            delete *itState;

            //(*itExtend)->destroyStateClone(*itState);

            itState = _stateStore.erase(itState);
        }

        BasicActorStoreIt itBasic  = _basicEnterActors.begin();
        BasicActorStoreIt endBasic = _basicEnterActors.end  ();

        for(; itBasic != endBasic; ++itBasic)
        {
            delete *itState;

            //(*itBasic)->destroyStateClone(*itState);

            itState = _stateStore.erase(itState);
        }

        _stateRefCountStore.erase(itStateRefCount);
    }

#endif /* OSG_NEWACTION_STATESLOTINTERFACE */
}

inline const PriorityAction::NodeQueueEntry &
PriorityAction::pqTop(void) const
{
    return _nodePrioQueue.front();
}

inline void
PriorityAction::pqPush(const NodeQueueEntry &entry)
{
    _nodePrioQueue.push_back(entry);

    std::push_heap(_nodePrioQueue.begin(), _nodePrioQueue.end(),
                   _nodePrioQueueComp                           );
}

inline void
PriorityAction::pqPop(void)
{
    std::pop_heap(_nodePrioQueue.begin(), _nodePrioQueue.end(),
                  _nodePrioQueueComp                           );

    _nodePrioQueue.pop_back();
}

inline bool
PriorityAction::pqEmpty(void) const
{
    return _nodePrioQueue.empty();
}

inline void
PriorityAction::pqClear(void)
{
    _nodePrioQueue.clear();
}

OSG_END_NAMESPACE

#define OSGPRIORITYACTION_INLINE_CVSID "@(#)$Id: OSGPriorityAction.inl,v 1.4 2004/09/17 14:09:43 neumannc Exp $"
