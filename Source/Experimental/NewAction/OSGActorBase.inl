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

#include "OSGNewAction.h"

OSG_BEGIN_NAMESPACE

inline
ActorBase::ActorBaseState::ActorBaseState(void)
{
}

inline
ActorBase::ActorBaseState::ActorBaseState(const ActorBaseState &source)
{
}

inline const NewAction *
ActorBase::getAction(void) const
{
    return _pAction;
}

inline NewAction *
ActorBase::getAction(void)
{
    return _pAction;
}

inline UInt32
ActorBase::getActorId(void) const
{
    return _uiActorId;
}

inline bool
ActorBase::getApplyEnter(void) const
{
    return _bApplyEnter;
}

inline bool
ActorBase::getApplyLeave(void) const
{
    return _bApplyLeave;
}

/*! Set whether the applyEnter method should be called.
 *  Note that changing this value only has an effect if the actor is NOT
 *  attached to an action.
 */

inline void
ActorBase::setApplyEnter(bool bApplyEnter)
{
    _bApplyEnter = bApplyEnter;
}

/*! Set whether the applyLeave method should be called.
 *  Note that changing this value only has an effect if the actor is NOT
 *  attached to an action.
 */

inline void
ActorBase::setApplyLeave(bool bApplyLeave)
{
    _bApplyLeave = bApplyLeave;
}

inline NodePtr
ActorBase::getCurrNode(void) const
{
    return getAction()->getActiveChildrenList()->getParentNode();
}

inline NodePtr
ActorBase::getCurrNode(void)
{
    return getAction()->getActiveChildrenList()->getParentNode();
}

/*! Call this before accessing the state of an actor to ensure that the
 *  state is valid.
 */

inline void
ActorBase::beginEditState(void)
{
    _pAction->beginEditStateEvent(this, getActorId());
}

/*! Call this when done accessing the state of an actor.
 */

inline void
ActorBase::endEditState(void)
{
}

inline const ActorBase::ActorBaseState *
ActorBase::getStatePtr(void) const
{
    return _pStatePtr;
}

inline ActorBase::ActorBaseState *
ActorBase::getStatePtr(void)
{
    return _pStatePtr;
}

inline void
ActorBase::setStatePtr(ActorBaseState *pStatePtr)
{
    _pStatePtr = pStatePtr;
}

inline UInt32
ActorBase::getStateSize(void) const
{
    return getStatePtr()->size();
}

OSG_END_NAMESPACE

#define OSGACTORBASE_INLINE_CVSID "@(#)$Id: OSGActorBase.inl,v 1.3 2004/04/20 13:47:08 neumannc Exp $"
