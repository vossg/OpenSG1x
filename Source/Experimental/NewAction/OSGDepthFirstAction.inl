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
DepthFirstAction::enterNode(const NodePtr &pNode, UInt32 pass)
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

inline DepthFirstAction::ResultE
DepthFirstAction::leaveNode(const NodePtr &pNode, UInt32 pass)
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

inline
DepthFirstAction::NodeStackEntry::NodeStackEntry(void)
    : _pNode    (NullFC),
      _passCount(1     )
{
}

inline
DepthFirstAction::NodeStackEntry::NodeStackEntry(const NodeStackEntry &source)
    : _pNode    (source._pNode    ),
      _passCount(source._passCount)
{
}

inline
DepthFirstAction::NodeStackEntry::NodeStackEntry(
    const NodePtr &pNode, Int32 passCount)

    : _pNode    (pNode    ),
      _passCount(passCount)
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

inline Int32
DepthFirstAction::NodeStackEntry::getPassCount(void) const
{
    return _passCount;
}

inline void
DepthFirstAction::NodeStackEntry::setPassCount(Int32 passCount)
{
    _passCount = passCount;
}

OSG_END_NAMESPACE

#define OSGDEPTHFIRSTACTION_INLINE_CVSID "@(#)$Id: OSGDepthFirstAction.inl,v 1.3 2004/09/17 14:09:42 neumannc Exp $"
