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

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*    NewAction::ActorData                                                 */

inline
NewAction::ActorData::ActorData(ActorBase *pActor,
                                UInt32     uiActorId,
                                UInt32     uiStateSize)
    : _pActor     (pActor     ),
      _uiActorId  (uiActorId  ),
      _uiStateSize(uiStateSize)
{
}

inline ActorBase *
NewAction::ActorData::getActor(void) const
{
    return _pActor;
}

inline void
NewAction::ActorData::setActor(ActorBase *pActor)
{
    _pActor = pActor;
}

inline UInt32
NewAction::ActorData::getActorId(void) const
{
    return _uiActorId;
}

inline void
NewAction::ActorData::setActorId(UInt32 uiActorId)
{
    _uiActorId = uiActorId;
}

inline UInt32
NewAction::ActorData::getStateSize(void) const
{
    return _uiStateSize;
}

inline void
NewAction::ActorData::setStateSize(UInt32 uiStateSize)
{
    _uiStateSize = uiStateSize;
}

/*-------------------------------------------------------------------------*/
/*    Actor Handling                                                       */

/*! Return the index of the given actor.
 *  If the actor is not attached to this action TypeTraits<UInt32>::getMax()
 *  is returned.
 */

inline UInt32
NewAction::findActor(ActorBase *pActor) const
{
    UInt32 uiIndex   = TypeTraits<UInt32>::getMax();
    UInt32 uiActorId = pActor->getActorId();

    if(pActor == _actors[uiActorId].getActor())
    {
        uiIndex = uiActorId;
    }
    else
    {
        ActorStoreConstIt itActors    = beginActors();
        ActorStoreConstIt endItActors = endActors  ();

        for(; itActors != endItActors; ++itActors)
        {
            if(pActor == itActors->getActor())
            {
                uiIndex = itActors->getActorId();
                break;
            }
        }
    }

    return uiIndex;
}

/*! Return the actor at the given index.
 *  Note that no range check is performed.
 */

inline ActorBase *
NewAction::getActor(UInt32 uiIndex) const
{
    return _actors[uiIndex].getActor();
}

/*! Return the number of actors attached to this action.
 */

inline UInt32
NewAction::getNumActors(void) const
{
    return _actors.size();
}

/*-------------------------------------------------------------------------*/
/*    Root Nodes                                                           */

/*! Return const begin iterator for the list of root nodes.
 *  Do NOT use this as input for apply.
 */

inline NewAction::NodeListConstIt
NewAction::beginRootNodes(void) const
{
    return _rootNodes.begin();
}

/*! Return begin iterator for the list of root nodes.
 *  Do NOT use this as input for apply.
 */

inline NewAction::NodeListIt
NewAction::beginRootNodes(void)
{
    return _rootNodes.begin();
}

/*! Return const end iterator for the list of root nodes.
 *  Do NOT use this as input for apply.
 */

inline NewAction::NodeListConstIt
NewAction::endRootNodes(void) const
{
    return _rootNodes.end();
}

/*! Return end iterator for the list of root nodes.
 *  Do NOT use this as input for apply.
 */

inline NewAction::NodeListIt
NewAction::endRootNodes(void)
{
    return _rootNodes.end();
}

/*! Return the list of root nodes.
 *  This method is intended to be used by Actors inside their start method.
 *  The list initially contains the input to the apply methods.
 */

inline const NewAction::NodeList &
NewAction::getRootNodes(void) const
{
    return _rootNodes;
}

/*! Return the list of root nodes.
 *  This method is intended to be used by Actors inside their start method.
 *  The list initially contains the input to the apply methods.
 */

inline NewAction::NodeList &
NewAction::getRootNodes(void)
{
    return _rootNodes;
}

/*-------------------------------------------------------------------------*/
/*    Traversal Mask                                                       */

/*! Return the traversal mask for this action.
 */

inline UInt32
NewAction::getTravMask(void) const
{
    return _uiTravMask;
}

/*! Set the traversal mask for this action.
 */

inline void
NewAction::setTravMask(UInt32 uiTravMask)
{
    _uiTravMask = uiTravMask;
}

/*-------------------------------------------------------------------------*/
/*    Active Children                                                      */

/*! Return the ActiveChildrenList.
 *  Note that this list is only meaningful, if getUseActiveChildrenList()
 *  returns true.
 */

inline const ActiveChildrenList *
NewAction::getActiveChildrenList(void) const
{
    return &_activeChildrenList;
}

/*! Return the ActiveChildrenList.
 *  Note that this list is only meaningful, if getUseActiveChildrenList()
 *  returns true.
 */

inline ActiveChildrenList *
NewAction::getActiveChildrenList(void)
{
    return &_activeChildrenList;
}

/*! Return if the ActiveChildrenList is in use.
 */

inline bool
NewAction::getUseActiveChildrenList(void) const
{
    return _bUseActiveChildrenList;
}

/*! Activate the ActiveChildrenList.
 */

inline void
NewAction::setUseActiveChildrenList(bool bUseActiveChildrenList)
{
    if((bUseActiveChildrenList == true) && (_bUseActiveChildrenList == false))
    {
        _activeChildrenList.buildList();
    }

    _bUseActiveChildrenList = bUseActiveChildrenList;
}

/*-------------------------------------------------------------------------*/
/*    Actor Storage Access                                                 */

/*! Return begin const iterator for the actor storage.
 */

inline NewAction::ActorStoreConstIt
NewAction::beginActors(void) const
{
    return _actors.begin();
}

/*! Return begin iterator for the actor storage.
 */

inline NewAction::ActorStoreIt
NewAction::beginActors(void)
{
    return _actors.begin();
}

/*! Return end const iterator for the actor storage.
 */

inline NewAction::ActorStoreConstIt
NewAction::endActors(void) const
{
    return _actors.end();
}

/*! Return end iterator for the actor storage.
 */

inline NewAction::ActorStoreIt
NewAction::endActors(void)
{
    return _actors.end();
}

OSG_END_NAMESPACE

#define OSGNEWACTION_INLINE_CVSID "@(#)$Id: OSGNewAction.inl,v 1.4 2004/04/20 13:47:08 neumannc Exp $"
