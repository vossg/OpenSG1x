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

#include "OSGNewActionBase.h"

OSG_BEGIN_NAMESPACE

//----------------------------------------------------------------------------
//    Types
//----------------------------------------------------------------------------

/*! Default constructor.
 */

inline
ActorBase::ActorBaseState::ActorBaseState(void)
{
}

/*! Copy constructor.
 */

inline
ActorBase::ActorBaseState::ActorBaseState(const ActorBaseState &source)
{
}

//----------------------------------------------------------------------------
//    Config
//----------------------------------------------------------------------------

/*! Return if operations upon "entering" a node are enabled.
 */

inline bool
ActorBase::getEnterNodeFlag(void) const
{
    return _enterNodeFlag;
}

/*! Return if operations upon "leaving" a node are enabled.
 */

inline bool
ActorBase::getLeaveNodeFlag(void) const
{
    return _leaveNodeFlag;
}

/*! Set if operations upon "entering a node are desired.
    \warning You must not call this while the actor is attached to an action,
    it will cause possibly fatal inconsistency.
*/

inline void
ActorBase::setEnterNodeFlag(bool enter)
{
    _enterNodeFlag = enter;
}

/*! Set if operations upon "leaving a node are desired.
    \warning You must not call this while the actor is attached to an action,
    it will cause possibly fatal inconsistency.
*/

inline void
ActorBase::setLeaveNodeFlag(bool leave)
{
    _leaveNodeFlag = leave;
}

//----------------------------------------------------------------------------
//    Action Access
//----------------------------------------------------------------------------

inline const NewActionBase *
ActorBase::getAction(void) const
{
    return _pAction;
}

inline NewActionBase *
ActorBase::getAction(void)
{
    return _pAction;
}

inline UInt32
ActorBase::getActorId(void) const
{
    return _actorId;
}

//----------------------------------------------------------------------------
//    Children Management
//----------------------------------------------------------------------------

/*! Return if the children list is enabled.
 */

inline bool
ActorBase::getChildrenListEnabled(void) const
{
    return _pAction->getChildrenListEnabled();
}

/*! Enable or disable the children list.
 */

inline void
ActorBase::setChildrenListEnabled(bool enabled)
{
    _pAction->setChildrenListEnabled(enabled);
}

/*! Return the traversed node.
 */

inline NodePtr
ActorBase::getNode(void) const
{
    return _pAction->getChildrenList().getParentNode();
}

/*! Return the number of children of the traversed node.
 */

inline UInt32
ActorBase::getNumChildren(void) const
{
    return _pAction->getChildrenList().getSize();
}

/*! Return the childIndex'th child of the traversed node.
    \warning childIndex is not range checked.
*/

inline NodePtr
ActorBase::getChild(UInt32 childIndex) const
{
    return _pAction->getChildrenList().getChild(childIndex);
}

/*! Return if the childIndex'th child is active, i.e. whether it will be
    traversed.
    \warning childIndex is not range checked.
    \warning The children list must have been enabled with
    setChildrenListEnabled(true);
*/

inline bool
ActorBase::getChildActive(UInt32 childIndex) const
{
    return _pAction->getChildrenList().getActive(childIndex);
}

/*! Set if the childIndex'th child will be included in the traversal.
    \warning childIndex is not range checked.
    \warning The children list must have been enabled with
    setChildrenListEnabled(true);
*/

inline void
ActorBase::setChildActive(UInt32 childIndex, bool active)
{
    _pAction->getChildrenList().setActive(childIndex, active);
}

/*! Return the priority assigned to the childIndex'th child.
    \warning childIndex is not range checked.
    \warning The children list must have been enabled with
    setChildrenListEnabled(true);
*/

inline ActorBase::PriorityType
ActorBase::getChildPriority(UInt32 childIndex) const
{
    return _pAction->getChildrenList().getPriority(childIndex);
}

/*! Set the priority of the childIndex'th child.
    \warning childIndex is not range checked.
    \warning The children list must have been enabled with
    setChildrenListEnabled(true);
*/

inline void
ActorBase::setChildPriority(UInt32 childIndex, PriorityType prio)
{
    _pAction->getChildrenList().setPriority(childIndex, prio);
}

//----------------------------------------------------------------------------
//    Extra Children Management
//----------------------------------------------------------------------------

/*! Return the number of extra children already added.
 */

inline UInt32
ActorBase::getNumExtraChildren(void) const
{
    return _pAction->getExtraChildrenList().getSize();
}

/*! Return the childIndex'th extra child.
    \warning childIndex is not range checked.
 */

inline NodePtr
ActorBase::getExtraChild(UInt32 childIndex) const
{
    return _pAction->getExtraChildrenList().getChild(childIndex);
}

/*! Return if the childIndex'th extra child is active, i.e. whether it will be
    traversed.
    \warning childIndex is not range checked.
*/

inline bool
ActorBase::getExtraChildActive(UInt32 childIndex) const
{
    return _pAction->getExtraChildrenList().getActive(childIndex);
}

/*! Set if the childIndex'th extra child will be included in the traversal.
    \warning childIndex is not range checked.
*/

inline void
ActorBase::setExtraChildActive(UInt32 childIndex, bool active)
{
    _pAction->getExtraChildrenList().setActive(childIndex, active);
}

/*! Return the priority assigned to the childIndex'th extra child.
    \warning childIndex is not range checked.
*/

inline ActorBase::PriorityType
ActorBase::getExtraChildPriority(UInt32 childIndex) const
{
    return _pAction->getExtraChildrenList().getPriority(childIndex);
}

/*! Set the priority of the childIndex'th extra child.
    \warning childIndex is not range checked.
*/

inline void
ActorBase::setExtraChildPriority(UInt32 childIndex, PriorityType prio)
{
    _pAction->getExtraChildrenList().setPriority(childIndex, prio);
}

//----------------------------------------------------------------------------
//    Multi Pass Management
//----------------------------------------------------------------------------

/*! Return the number of passes requested for the current node. The default
    number of passes is 1.
 */

inline UInt32
ActorBase::getNumPasses(void) const
{
    return _pAction->getNumPasses();
}

//----------------------------------------------------------------------------
//    State Management
//----------------------------------------------------------------------------

/*! Notify the action, that state is about to be edited.

\ext
    Call this method inside a functor or the enterNode method of an actor
    before accessing any state variables.
    If you are worried about top performance you may omit the call as long
    as you only read state values, but as this is error prone it is not
    recommended.
\endext
*/

inline void
ActorBase::beginEditState(void)
{
    _pAction->beginEditStateEvent(this, _actorId);
}

/*! Notify the action, that state access is complete.

\ext
    Call this method after you are done with modifying state.
    None of the implemented actions perform anything upon this call, hence it
    is not as critical as the beginEditState call.
\endext
 */

inline void
ActorBase::endEditState(void)
{
    _pAction->endEditStateEvent(this, _actorId);
}

/*! Get a const pointer to the currently used state.
 */

inline const ActorBase::ActorBaseState *
ActorBase::getState(void) const
{
    return _pState;
}

/*! Get a pointer to the currently used state.
 */

inline ActorBase::ActorBaseState *
ActorBase::getState(void)
{
    return _pState;
}

/*! Set the currently used state.
 */

inline void
ActorBase::setState(ActorBaseState *pState)
{
    _pState = pState;
}

#ifdef OSG_NEWACTION_STATESLOTINTERFACE

/*! Get a const reference to the SlotMap.
 */

inline const ActorBase::StateSlotMap &
ActorBase::getSlotMap(void) const
{
    return _stateSlotMap;
}

/*! Get a reference to the SlotMap.
 */

inline ActorBase::StateSlotMap &
ActorBase::getSlotMap(void)
{
    return _stateSlotMap;
}

#endif

OSG_END_NAMESPACE

#define OSGACTORBASE_INLINE_CVSID "@(#)$Id: OSGActorBase.inl,v 1.6 2004/09/17 14:09:42 neumannc Exp $"
