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

#include "OSGActorBase.h"

OSG_USING_NAMESPACE

//----------------------------------------------------------------------------
//    Description
//----------------------------------------------------------------------------

/*! \class osg::ActorBase
    \ingroup GrpExperimentalNewAction

ActorBase is the base class for all Actors. See \ref
PageExperimentalNewActionActorBase for a description.

\ext

To create a new actor you should use the actorEdit utility that can be found
in /OpenSG/Tools/actorEdit. It will generate a base class for your own actor
that takes care of the management of functors and state.

\endext

*/

// Abstract function doc

/*! \fn osg::ActorBase::ResultE osg::ActorBase::enterNode(const NodePtr &pNode)

    This method will be called by an action, when "entering" a node.
*/

/*! \fn osg::ActorBase::ResultE osg::ActorBase::leaveNode(const NodePtr &pNode)

    This method will be called by an action, when "leaving" a node.
*/


//----------------------------------------------------------------------------
//    Types
//----------------------------------------------------------------------------

ActorBase::ActorBaseState::~ActorBaseState(void)
{
}

//----------------------------------------------------------------------------
//    Destructor
//----------------------------------------------------------------------------

/*! Destructor
 */

ActorBase::~ActorBase(void)
{
}


//----------------------------------------------------------------------------
//    Start/Stop
//----------------------------------------------------------------------------

/*! Called by an action before a traversal.
    \warning When overriding this method, you must call the inherited version.
 */

ActorBase::ResultE
ActorBase::start(void)
{
#ifdef OSG_NEWACTION_STATESLOTINTERFACE
    _stateSlotMap.clear();
#endif

    return NewActionTypes::Continue;
}

/*! Called by an action after a traversal.
    \warning When overriding this method, you must call the inherited version.
 */

ActorBase::ResultE
ActorBase::stop(void)
{
#ifdef OSG_NEWACTION_STATESLOTINTERFACE
    _stateSlotMap.clear();
#endif

    return NewActionTypes::Continue;
}

//----------------------------------------------------------------------------
//    Constructor
//----------------------------------------------------------------------------

/*! Constructor
 */

ActorBase::ActorBase(void)
    : _pAction      (NULL                        ),
      _actorId      (TypeTraits<UInt32>::getMax()),
      _enterNodeFlag(false                       ),
      _leaveNodeFlag(false                       ),
#ifdef OSG_NEWACTION_STATESLOTINTERFACE
      _stateSlotMap (                            ),
#endif
      _pState       (NULL                        )
{
}

//----------------------------------------------------------------------------
//    Event Notification
//----------------------------------------------------------------------------

/*! Notifies the actor, that it was added to an action.
    \warning When overriding this method, you must call the inherited version.
 */

void
ActorBase::addEvent(NewActionBase *pAction, UInt32 actorId)
{
    if((_pAction != NULL) || (_actorId != TypeTraits<UInt32>::getMax()))
    {
        SWARNING << "ActorBase::attachEvent: Actor already attached."
                 << endLog;
    }

    createInitialState();

    _pAction = pAction;
    _actorId = actorId;
}

/*! Notifies the actor, that it was removed from an action.
    \warning When overriding this method, you must call the inherited version.
 */

void
ActorBase::subEvent(NewActionBase *pAction, UInt32 actorId)
{
    if((_pAction != pAction) || (_actorId != actorId))
    {
        SWARNING << "ActorBase::detachEvent: Inconsistency detected."
                 << endLog;
    }

    deleteInitialState();

    _pAction = NULL;
    _actorId = TypeTraits<UInt32>::getMax();
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
