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

OSG_USING_NAMESPACE

/*! \class osg::NewAction
    \ingroup GrpSystemNewAction

The abstract base class for the new action system.

Basically an action is a container for actors with the ability to
traverse the scenegraph.
Actors can be attached or detached at runtime, but not during a traversal.
To actually start a traversal use the apply methods.
*/

/*-------------------------------------------------------------------------*/
/*    Desctuctor                                                           */

NewAction::~NewAction(void)
{
}

/*-------------------------------------------------------------------------*/
/*    Actor Handling                                                       */

/*! Add an actor at the end of the action.
 *  Note that the action assumes exclusive ownership of the actor.
 *  Do NOT call this method while a traversal is in progress.
 */

UInt32
NewAction::attachActor(ActorBase *pActor)
{
    UInt32 uiActorId = _actors.size();

    pActor->attachEvent(          this,   uiActorId                         );
    _actors.push_back  (ActorData(pActor, uiActorId, pActor->getStateSize()));
    this  ->attachEvent(          pActor, uiActorId                         );

    return uiActorId;
}

/*! Insert an actor at the given position of the action.
 *  Note that the action assumes exclusive ownership of the actor.
 *  Do NOT call this method while a traversal is in progress.
 */

UInt32
NewAction::attachActor(ActorBase *pActor, UInt32 uiIndex)
{
    pActor->attachEvent(this,   uiIndex);
    _actors.insert(beginActors() + uiIndex,
                   ActorData(pActor, uiIndex, pActor->getStateSize()));
    this  ->attachEvent(pActor, uiIndex);

    return uiIndex;
}

/*! Remove the actor at the given index.
 *  Ownership of the actor is returned to the caller.
 *  Do NOT call this method while a traversal is in progress.
 */

ActorBase *
NewAction::detachActor(UInt32 uiIndex)
{
    ActorStoreIt  itActor   = beginActors      () + uiIndex;
    ActorBase    *pActor    = itActor->getActor();

    this  ->detachEvent(pActor, itActor->getActorId());
    pActor->detachEvent(this,   itActor->getActorId());

    _actors.erase(itActor);

    return pActor;
}

/*! Remove the given actor.
 *  Ownership of the actor is returned to the caller.
 *  Do NOT call this method while a traversal is in progress.
 */

ActorBase *
NewAction::detachActor(ActorBase *pActor)
{
    ActorStoreIt itActor = beginActors() + findActor(pActor);

    this->detachEvent  (pActor, itActor->getActorId());
    pActor->detachEvent(this,   itActor->getActorId());

    _actors.erase(itActor);

    return pActor;
}

/*-------------------------------------------------------------------------*/
/*    Apply                                                                */

/*! Traverse the scenegraph from the given node.
 *  Note that this is only a convenience function for cases where priorities
 *  are not required.
 */

NewAction::ResultE
NewAction::apply(const NodePtr &pRootNode)
{
    return apply(pRootNode, TypeTraits<PriorityType>::getZeroElement());
}

/*! Traverse the scenegraph from the given node.
 */

NewAction::ResultE
NewAction::apply(const NodePtr &pRootNode, PriorityType priority)
{
    typedef NewActionTypes::NodePriorityPair NodePriorityPair;

    _rootNodes.push_back(NodePriorityPair(pRootNode, priority));

    return NewActionTypes::Continue;
}

/*! Traverse the scenegraph(s) from the given nodes.
 */

NewAction::ResultE
NewAction::apply(NodeListConstIt begin, NodeListConstIt end)
{
    _rootNodes.insert(_rootNodes.end(), begin, end);

    return NewActionTypes::Continue;
}

/*-------------------------------------------------------------------------*/
/*    Constructors                                                         */

NewAction::NewAction(void)
    : _actors                (                           ),
      _uiTravMask            (TypeTraits<UInt32>::BitsSet),
      _bUseActiveChildrenList(false                      ),
      _activeChildrenList    (                           )
{
}

/*-------------------------------------------------------------------------*/
/*    Events                                                               */

void
NewAction::attachEvent(ActorBase *pActor, UInt32 uiActorId)
{
}

void
NewAction::detachEvent(ActorBase *pActor, UInt32 uiActorId)
{
}

void
NewAction::beginEditStateEvent(ActorBase *pActor, UInt32 uiActorId)
{
}

void
NewAction::endEditStateEvent(ActorBase *pActor, UInt32 uiActorId)
{
}

/*-------------------------------------------------------------------------*/
/*    Helper Methods                                                       */

/*! Call the start method of all attached actors.
 */

NewAction::ResultE
NewAction::startActors(void)
{
    ResultE           result      = NewActionTypes::Continue;
    ActorStoreIt      itActors    = beginActors();
    ActorStoreConstIt endItActors = endActors  ();

    for(; (itActors != endItActors) && (result == NewActionTypes::Continue);
        ++itActors                                                          )
    {
        result = itActors->getActor()->start();
    }

    return result;
}

/*! Call the stop method of all attached actors.
 */

NewAction::ResultE
NewAction::stopActors(void)
{
    ResultE           result      = NewActionTypes::Continue;
    ActorStoreIt      itActors    = beginActors();
    ActorStoreConstIt endItActors = endActors  ();

    for(; (itActors != endItActors) && (result == NewActionTypes::Continue);
        ++itActors)
    {
        result = itActors->getActor()->stop();
    }

    return result;
}

/*------------------------------------------------------------------------*/
/*    cvs id's                                                            */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGNewAction.cpp,v 1.4 2004/04/20 13:47:08 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGNEWACTION_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGNEWACTION_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
