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

#include "OSGExtendActorBase.h"
#include "OSGBasicActorBase.h"

OSG_BEGIN_NAMESPACE

//----------------------------------------------------------------------------
//    Helper Methods
//----------------------------------------------------------------------------

/*! Calls the enterNode method of the attached actors.
 */

inline DepthFirstStateAction::ResultE
DepthFirstStateAction::enterNode(const NodePtr &pNode, UInt32 pass)
{
    FunctorArgumentType funcArg(NULL, pNode, pass);
    ResultE             result    = NewActionTypes::Continue;

    ExtendActorStoreIt  itExtend  = _extendEnterActors.begin();
    ExtendActorStoreIt  endExtend = _extendEnterActors.end  ();

    for(;  (itExtend != endExtend                                    )  &&
          !(result   &  (NewActionTypes::Break | NewActionTypes::Quit));
        ++itExtend                                                         )
    {
        funcArg.setActor(*itExtend);

        result = static_cast<ResultE>(result | (*itExtend)->enterNode(funcArg));
    }

    BasicActorStoreIt   itBasic   = _basicEnterActors.begin();
    BasicActorStoreIt   endBasic  = _basicEnterActors.end  ();

    for(;  (itBasic != endBasic                                     )  &&
          !(result  &  (NewActionTypes::Break | NewActionTypes::Quit));
        ++itBasic                                                        )
    {
        funcArg.setActor(*itBasic);

        result = static_cast<ResultE>(result | (*itBasic)->enterNode(funcArg));
    }

    return result;
}

/*! Calls the leaveNode method of the attached actors.
 */

inline DepthFirstStateAction::ResultE
DepthFirstStateAction::leaveNode(const NodePtr &pNode, UInt32 pass)
{
    FunctorArgumentType funcArg(NULL, pNode, pass);
    ResultE             result    = NewActionTypes::Continue;

    ExtendActorStoreIt  itExtend  = _extendLeaveActors.begin();
    ExtendActorStoreIt  endExtend = _extendLeaveActors.end  ();

    for(;  (itExtend != endExtend                                    )  &&
          !(result   &  (NewActionTypes::Break | NewActionTypes::Quit));
        ++itExtend                                                         )
    {
        funcArg.setActor(*itExtend);

        result = static_cast<ResultE>(result | (*itExtend)->leaveNode(funcArg));
    }

    BasicActorStoreIt  itBasic   = _basicLeaveActors.begin();
    BasicActorStoreIt  endBasic  = _basicLeaveActors.end  ();

    for(;  (itBasic != endBasic                                     )  &&
          !(result  &  (NewActionTypes::Break | NewActionTypes::Quit));
        ++itBasic                                                         )
    {
        funcArg.setActor(*itBasic);

        result = static_cast<ResultE>(result | (*itBasic)->leaveNode(funcArg));
    }

    return result;
}

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
DepthFirstStateAction::StateRefCount::StateRefCount(const StateRefCount &source)
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
DepthFirstStateAction::StateRefCount::StateRefCount(UInt32 stateSlot)
    : _stateSlot(stateSlot),
      _refCount (0        )
{
}

/*! Constructor.
 */

inline
DepthFirstStateAction::StateRefCount::StateRefCount
    (UInt32 stateSlot, Int32 refCount)

    : _stateSlot(stateSlot),
      _refCount (refCount )
{
}

/*! Return the state slot.
 */

inline UInt32
DepthFirstStateAction::StateRefCount::getStateSlot(void) const
{
    return _stateSlot;
}

/* Set the state slot.
 */

inline void
DepthFirstStateAction::StateRefCount::setStateSlot(UInt32 stateSlot)
{
    _stateSlot = stateSlot;
}

/*! Return the ref count.
 */

inline Int32
DepthFirstStateAction::StateRefCount::getRefCount(void) const
{
    return _refCount;
}

/*! Increment the ref count by ref.
 */

inline void
DepthFirstStateAction::StateRefCount::incRefCount(Int32 inc)
{
    _refCount += inc;
}

/*! Decrement the ref count by ref.
 */

inline void
DepthFirstStateAction::StateRefCount::decRefCount(Int32 dec)
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
DepthFirstStateAction::StateRefCount::StateRefCount(const StateRefCount &source)
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
DepthFirstStateAction::StateRefCount::StateRefCount(const StateStoreIt &itState)
    : _itState (itState),
      _refCount(0      )
{
}

/*! Constructor.
 */

inline
DepthFirstStateAction::StateRefCount::StateRefCount(
    const StateStoreIt &itState, Int32 refCount)

    : _itState (itState ),
      _refCount(refCount)
{
}

/*! Return the state store iterator.
 */

inline DepthFirstStateAction::StateStoreIt
DepthFirstStateAction::StateRefCount::getState(void) const
{
    return _itState;
}

/*! Set the state store iterator.
 */

inline void
DepthFirstStateAction::StateRefCount::setState(const StateStoreIt &itState)
{
    _itState = itState;
}

/*! Return the ref count.
 */

inline Int32
DepthFirstStateAction::StateRefCount::getRefCount(void) const
{
    return _refCount;
}

/*! Increment the ref count.
 */

inline void
DepthFirstStateAction::StateRefCount::incRefCount(Int32 inc)
{
    _refCount += inc;
}

/*! Decrement the ref count.
 */

inline void
DepthFirstStateAction::StateRefCount::decRefCount(Int32 dec)
{
    _refCount -= dec;
}

#endif /* OSG_NEWACTION_STATESLOTINTERFACE */

inline
DepthFirstStateAction::NodeStackEntry::NodeStackEntry(void)

    : _pNode          (NullFC),
      _itStateRefCount(      ),
      _passCount      (0     )
{
}

inline
DepthFirstStateAction::NodeStackEntry::NodeStackEntry(
    const NodeStackEntry &source)

    : _pNode          (source._pNode          ),
      _itStateRefCount(source._itStateRefCount),
      _passCount      (source._passCount      )
{
}

inline
DepthFirstStateAction::NodeStackEntry::NodeStackEntry(
    const NodePtr &pNode,     const StateRefCountStoreIt &itStateRefCount,
          Int32    passCount                                              )

    : _pNode          (pNode          ),
      _itStateRefCount(itStateRefCount),
      _passCount      (passCount      )
{
}

inline NodePtr
DepthFirstStateAction::NodeStackEntry::getNode(void) const
{
    return _pNode;
}

inline Int32
DepthFirstStateAction::NodeStackEntry::getPassCount(void) const
{
    return _passCount;
}

inline void
DepthFirstStateAction::NodeStackEntry::setPassCount(Int32 passCount)
{
    _passCount = passCount;
}

inline DepthFirstStateAction::StateRefCountStoreIt
DepthFirstStateAction::NodeStackEntry::getStateRefCount(void) const
{
    return _itStateRefCount;
}

inline void
DepthFirstStateAction::NodeStackEntry::setStateRefCount(
    const StateRefCountStoreIt &itStateRefCount)
{
    _itStateRefCount = itStateRefCount;
}

/*! Creates a copy of the state currently used by the attached actors.
 */

inline DepthFirstStateAction::StateRefCountStoreIt
DepthFirstStateAction::cloneState(void)
{
#ifdef OSG_NEWACTION_STATESLOTINTERFACE

    UInt32               stateSlot;
    StateRefCountStoreIt itStateRefCount = --(_stateRefCountStore.end());

    ExtendActorStoreIt   itExtend        =    beginExtend();
    ExtendActorStoreIt   endItExtend     =    endExtend  ();

    for(; itExtend != endItExtend; ++itExtend)
    {
        stateSlot = (*itExtend)->createStateClone();
    }

    BasicActorStoreIt itBasic    = beginBasic();
    BasicActorStoreIt endItBasic = endBasic  ();

    for(; itBasic != endItBasic; ++itBasic)
    {
        stateSlot = (*itBasic)->createStateClone();
    }

    _stateRefCountStore.push_back(StateRefCount(stateSlot));

    return ++itStateRefCount;

#else  /* OSG_NEWACTION_STATESLOTINTERFACE */

    StateStoreIt         itState         = --(_stateStore        .end  ());
    StateRefCountStoreIt itStateRefCount = --(_stateRefCountStore.end  ());

    ExtendActorStoreIt   itExtend        =    beginExtend();
    ExtendActorStoreIt   endItExtend     =    endExtend  ();

    for(; itExtend != endItExtend; ++itExtend)
    {
        _stateStore.push_back((*itExtend)->createStateClone());
    }

    BasicActorStoreIt itBasic    = beginBasic();
    BasicActorStoreIt endItBasic = endBasic  ();

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

inline DepthFirstStateAction::StateRefCountStoreIt
DepthFirstStateAction::getState(void)
{
#ifdef OSG_NEWACTION_STATESLOTINTERFACE

    UInt32               stateSlot;
    StateRefCountStoreIt itStateRefCount = --(_stateRefCountStore.end  ());

    ExtendActorStoreIt   itExtend        =    beginExtend();
    ExtendActorStoreIt   endItExtend     =    endExtend  ();

    for(; itExtend != endItExtend; ++itExtend)
    {
        stateSlot = (*itExtend)->getSlotMap().size();

        (*itExtend)->getSlotMap().push_back((*itExtend)->getState());
    }

    BasicActorStoreIt itBasic    = beginBasic();
    BasicActorStoreIt endItBasic = endBasic  ();

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

    ExtendActorStoreIt   itExtend        =    beginExtend();
    ExtendActorStoreIt   endItExtend     =    endExtend  ();

    for(; itExtend != endItExtend; ++itExtend)
    {
        _stateStore.push_back((*itExtend)->getState());
    }

    BasicActorStoreIt itBasic    = beginBasic();
    BasicActorStoreIt endItBasic = endBasic  ();

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
DepthFirstStateAction::setState(StateRefCountStoreIt itStateRefCount)
{
#ifdef OSG_NEWACTION_STATESLOTINTERFACE

    UInt32             stateSlot   = itStateRefCount->getStateSlot();

    ExtendActorStoreIt   itExtend        =    beginExtend();
    ExtendActorStoreIt   endItExtend     =    endExtend  ();

    for(; itExtend != endItExtend; ++itExtend, ++itState)
    {
        (*itExtend)->setState((*itExtend)->getSlotMap()[stateSlot]);
    }

    BasicActorStoreIt itBasic    = beginBasic();
    BasicActorStoreIt endItBasic = endBasic  ();

    for(; itBasic != endItBasic; ++itBasic, ++itState)
    {
        (*itBasic)->setState((*itBasic)->getSlotMap()[stateSlot]);
    }

#else  /* OSG_NEWACTION_STATESLOTINTERFACE */

    StateStoreIt       itState     = itStateRefCount->getState();

    ExtendActorStoreIt itExtend    = beginExtend();
    ExtendActorStoreIt endItExtend = endExtend  ();

    for(; itExtend != endItExtend; ++itExtend, ++itState)
    {
        (*itExtend)->setState(*itState);
    }

    BasicActorStoreIt itBasic    = beginBasic();
    BasicActorStoreIt endItBasic = endBasic  ();

    for(; itBasic != endItBasic; ++itBasic, ++itState)
    {
        (*itBasic)->setState(*itState);
    }

#endif /* OSG_NEWACTION_STATESLOTINTERFACE */
}

/*! Increment the ref count by inc.
 */

inline void
DepthFirstStateAction::incRefCount(StateRefCountStoreIt itStateRefCount, Int32 inc)
{
    itStateRefCount->incRefCount(inc);
}

/*! Decrement the ref count by dec. If it reaches 0 the state is delete.
 */

inline void
DepthFirstStateAction::decRefCount(StateRefCountStoreIt itStateRefCount, Int32 dec)
{
#ifdef OSG_NEWACTION_STATESLOTINTERFACE

    itStateRefCount->decRefCount(dec);

    if(itStateRefCount->getRefCount() <= 0)
    {
        UInt32             stateSlot   = itStateRefCount->getStateSlot();

        ExtendActorStoreIt itExtend    = beginExtend();
        ExtendActorStoreIt endItExtend = endExtend  ();

        for(; itExtend != endExtend; ++itExtend)
        {
            delete (*itExtend)->getSlotMap()[stateSlot];

            //(*itExtend)->destroyStateClone(stateSlot);
        }

        BasicActorStoreIt itBasic    = beginBasic();
        BasicActorStoreIt endItBasic = endBasic  ();

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
        StateStoreIt       itState     = itStateRefCount->getState();

        ExtendActorStoreIt itExtend    = beginExtend();
        ExtendActorStoreIt endItExtend = endExtend  ();

        for(; itExtend != endItExtend; ++itExtend)
        {
            delete *itState;

            //(*itExtend)->destroyStateClone(*itState);

            itState = _stateStore.erase(itState);
        }

        BasicActorStoreIt itBasic    = beginBasic();
        BasicActorStoreIt endItBasic = endBasic  ();

        for(; itBasic != endItBasic; ++itBasic)
        {
            delete *itState;

            //(*itBasic)->destroyStateClone(*itState);

            itState = _stateStore.erase(itState);
        }

        _stateRefCountStore.erase(itStateRefCount);
    }

#endif /* OSG_NEWACTION_STATESLOTINTERFACE */
}

OSG_END_NAMESPACE

#define OSGDEPTHFIRSTSTATEACTION_INLINE_CVSID "@(#)$Id: OSGDepthFirstStateAction.inl,v 1.2 2004/09/17 14:09:43 neumannc Exp $"
