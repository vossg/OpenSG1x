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

inline DepthFirstAction::ResultE
DepthFirstAction::enterNode(const NodePtr &pNode)
{
    ResultE            result    = NewActionTypes::Continue;

    ExtendActorStoreIt itExtend  = _extendEnterActors.begin();
    ExtendActorStoreIt endExtend = _extendEnterActors.end  ();

    BasicActorStoreIt  itBasic   = _basicEnterActors.begin();
    BasicActorStoreIt  endBasic  = _basicEnterActors.end  ();

    for(;  (itExtend != endExtend                                    )  &&
          !(result   &  (NewActionTypes::Break | NewActionTypes::Quit));
        ++itExtend                                                         )
    {
        result = static_cast<ResultE>(result | (*itExtend)->enterNode(pNode));
    }

    for(;  (itBasic != endBasic                                     )  &&
          !(result  &  (NewActionTypes::Break | NewActionTypes::Quit));
        ++itBasic                                                        )
    {
        result = static_cast<ResultE>(result | (*itBasic)->enterNode(pNode));
    }

    return result;
}

/*! Calls the leaveNode method of the attached actors.
 */

inline DepthFirstAction::ResultE
DepthFirstAction::leaveNode(const NodePtr &pNode)
{
    ResultE            result    = NewActionTypes::Continue;

    ExtendActorStoreIt itExtend  = _extendLeaveActors.begin();
    ExtendActorStoreIt endExtend = _extendLeaveActors.end  ();

    BasicActorStoreIt  itBasic   = _basicLeaveActors.begin();
    BasicActorStoreIt  endBasic  = _basicLeaveActors.end  ();

    for(;  (itExtend != endExtend                                    )  &&
          !(result   &  (NewActionTypes::Break | NewActionTypes::Quit));
        ++itExtend                                                         )
    {
        result = static_cast<ResultE>(result | (*itExtend)->leaveNode(pNode));
    }

    for(;  (itBasic != endBasic                                     )  &&
          !(result  &  (NewActionTypes::Break | NewActionTypes::Quit));
        ++itBasic                                                         )
    {
        result = static_cast<ResultE>(result | (*itBasic)->leaveNode(pNode));
    }

    return result;
}

//----------------------------------------------------------------------------
//    Types
//----------------------------------------------------------------------------

inline
DepthFirstAction::NodeStackEntry::NodeStackEntry(const NodePtr &pNode)
    : _pNode    (pNode),
      _enterFlag(true )
{
}

inline
DepthFirstAction::NodeStackEntry::NodeStackEntry(
    const NodePtr &pNode, bool enterFlag)

    : _pNode    (pNode    ),
      _enterFlag(enterFlag)
{
}

inline NodePtr
DepthFirstAction::NodeStackEntry::getNode(void) const
{
    return _pNode;
}

inline void
DepthFirstAction::NodeStackEntry::setNode(const NodePtr &pNode)
{
    _pNode = pNode;
}

inline bool
DepthFirstAction::NodeStackEntry::getEnterFlag(void) const
{
    return _enterFlag;
}

inline void
DepthFirstAction::NodeStackEntry::setEnterFlag(bool enterFlag)
{
    _enterFlag = enterFlag;
}

OSG_END_NAMESPACE

#define OSGDEPTHFIRSTACTION_INLINE_CVSID "@(#)$Id: OSGDepthFirstAction.inl,v 1.2 2004/09/10 15:00:46 neumannc Exp $"
