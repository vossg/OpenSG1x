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

#include "OSGActorBase.h"

OSG_USING_NAMESPACE

/*! Destructor.
 */

ActorBase::ActorBaseState::~ActorBaseState(void)
{
}

/*! Return a new copy of the state. This method is must be reimplemented in
 *  a derived class.
 */

ActorBase::ActorBaseState *
ActorBase::ActorBaseState::clone(MemoryHandle pMemHandle) const
{
    SWARNING << "AcotrBase::ActorBaseState::clone called." << endLog;

    return NULL;
}

/*! Return if there are any state elements in this class. This method is must
 *  be reimplemented in a derived class.
 */

bool
ActorBase::ActorBaseState::empty(void) const
{
    return true;
}

/*! Return the size of the state class. This method must be reimplemented in
 *  a derived class.
 */

UInt32
ActorBase::ActorBaseState::size(void) const
{
    return sizeof(ActorBaseState);
}

/*-------------------------------------------------------------------------*/
/*    Destructor                                                           */

/*! Destructor.
 */

ActorBase::~ActorBase(void)
{
    delete _pStatePtr;
}

/*-------------------------------------------------------------------------*/
/*    Start/Stop                                                           */

/*! The start method is called before a traversal begins, but it only returns
 *  NewActionTypes::Continue. This can be overridden in derived classes.
 */

ActorBase::ResultE
ActorBase::start(void)
{
    return NewActionTypes::Continue;
}

/*! The stop method is called after a traversal ends, but it only returns
 *  NewActionTypes::Continue. This can be overridden in derived classes.
 */

ActorBase::ResultE
ActorBase::stop(void)
{
    return NewActionTypes::Continue;
}

/*-------------------------------------------------------------------------*/
/*    Apply                                                                */

/*! Called upon entering a node; it does nothing and returns
 *  NewActionTypes::Continue.
 */

ActorBase::ResultE
ActorBase::applyEnter(const NodePtr &pNode)
{
    return NewActionTypes::Continue;
}

/*! Called upon leaving a node; it does nothing and returns
 *  NewActionTypes::Continue.
 */

ActorBase::ResultE
ActorBase::applyLeave(const NodePtr &pNode)
{
    return NewActionTypes::Continue;
}

/*-------------------------------------------------------------------------*/
/*    Events                                                               */

/*! Called by NewAction upon attaching an actor. This method can be overridden
 *  by a derived class, but you must call the base class's variant first.
 */

void
ActorBase::attachEvent(NewAction *pAction, UInt32 uiActorId)
{
    if(getAction() != NULL)
        SWARNING << "ActorBase::attachEvent: already attached."
                 << endLog;

    if(getActorId() != TypeTraits<UInt32>::getMax())
        SWARNING << "ActorBase::attachEvent: already attached."
                 << endLog;

    this->createState();

    _pAction   = pAction;
    _uiActorId = uiActorId;
}

/*! Called by NewAction upon detaching an actor. This method can be overridden
 *  by a derived class, but you must call the base class's variant at the end.
 */

void
ActorBase::detachEvent(NewAction *pAction, UInt32 uiActorId)
{
    if(pAction != getAction())
        SWARNING << "ActorBase::detachEvent: action inconsistency."
                 << endLog;

    if(uiActorId != getActorId())
        SWARNING << "ActorBase::detachEvent: actor id inconsistency."
                 << endLog;

    this->deleteState();

    _pAction   = NULL;
    _uiActorId = TypeTraits<UInt32>::getMax();
}

/*-------------------------------------------------------------------------*/
/*    Constructors                                                         */

/*! Constructor.
 */

ActorBase::ActorBase(void)
    : _pAction    (NULL                        ),
      _uiActorId  (TypeTraits<UInt32>::getMax()),
      _bApplyEnter(false                       ),
      _bApplyLeave(false                       ),
      _pStatePtr  (NULL                        )
{
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: $";
    static Char8 cvsid_hpp       [] = OSGACTORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGACTORBASE_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
