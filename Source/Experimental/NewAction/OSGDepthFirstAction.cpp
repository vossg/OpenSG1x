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

#include "OSGDepthFirstAction.h"

OSG_USING_NAMESPACE

/*-------------------------------------------------------------------------*/
/*    Create                                                               */

/*! Return a new instance of DepthFirstAction.
 */

DepthFirstAction *
DepthFirstAction::create(void)
{
    return new DepthFirstAction();
}

/*-------------------------------------------------------------------------*/
/*    Destructor                                                           */

DepthFirstAction::~DepthFirstAction(void)
{
}

/*-------------------------------------------------------------------------*/
/*    Apply                                                                */

/*! Traverse the scenegraph from the given node.
 *  The priority only ever matters if any of the attached actors add additional
 *  root nodes.
 */

DepthFirstAction::ResultE
DepthFirstAction::apply(const NodePtr &pRootNode, PriorityType priority)
{
    ResultE result = NewActionTypes::Continue;

    Inherited::apply(pRootNode, priority);

    result = startActors();

    if(result == NewActionTypes::Continue)
    {
        std::stable_sort(beginRootNodes(), endRootNodes(),
                         NodeList::value_type::LessCompare());

        NodeList::const_reverse_iterator itRootNodes  = getRootNodes().rbegin();
        NodeList::const_reverse_iterator endRootNodes = getRootNodes().rend  ();

        for(; itRootNodes != endRootNodes; ++itRootNodes)
            _nodeStack.push_back(NodeStackEntry(itRootNodes->getNode()));

        getRootNodes().clear();

        if(_actorsLeave.empty() == true)
        {
            result = applyEnter();
        }
        else
        {
            result = applyEnterLeave();
        }
    }

    if(result == NewActionTypes::Continue)
    {
        result = stopActors();
    }

    return result;
}

/*! Traverse the scenegraph(s) from the given nodes.
 *  The nodes are first sorted by their priority, if it is equal they retain
 *  the order in the NodeList.
 */

DepthFirstAction::ResultE
DepthFirstAction::apply(NodeListConstIt begin, NodeListConstIt end)
{
    ResultE result = NewActionTypes::Continue;

    Inherited::apply(begin, end);

    result = startActors();

    if(result == NewActionTypes::Continue)
    {
        std::stable_sort(beginRootNodes(), endRootNodes(),
                         NodeList::value_type::LessCompare());

        NodeList::const_reverse_iterator itRootNodes  = getRootNodes().rbegin();
        NodeList::const_reverse_iterator endRootNodes = getRootNodes().rend  ();

        for(; itRootNodes != endRootNodes; ++itRootNodes)
            _nodeStack.push_back(NodeStackEntry(itRootNodes->getNode()));

        getRootNodes().clear();

        if(_actorsLeave.empty() == true)
        {
            result = applyEnter();
        }
        else
        {
            result = applyEnterLeave();
        }
    }

    if(result == NewActionTypes::Continue)
    {
        result = stopActors();
    }

    return result;
}

/*-------------------------------------------------------------------------*/
/*    Constructors                                                         */

DepthFirstAction::DepthFirstAction(void)
    : _nodeStack  (),
      _actorsEnter(),
      _actorsLeave()
{
}

/*-------------------------------------------------------------------------*/
/*    Events                                                               */

/*! Inserts the newly attached actor into two internal datastructures to
 *  speed up enter/leave calling.
 */

void
DepthFirstAction::attachEvent(ActorBase *pActor, UInt32 uiActorId)
{
    ActorApplyStoreIt      itEnter  = _actorsEnter.begin();
    ActorApplyStoreConstIt endEnter = _actorsEnter.end  ();

    ActorApplyStoreIt      itLeave  = _actorsLeave.begin();
    ActorApplyStoreConstIt endLeave = _actorsLeave.end  ();

    Inherited::attachEvent(pActor, uiActorId);

    if(pActor->getApplyEnter() == true)
    {
        for(; itEnter != endEnter; ++itEnter)
        {
            if((*itEnter)->getActorId() > uiActorId)
                break;
        }

        _actorsEnter.insert(itEnter, pActor);
    }

    if(pActor->getApplyLeave() == true)
    {
        for(; itLeave != endLeave; ++itLeave)
        {
            if((*itLeave)->getActorId() > uiActorId)
                break;
        }

        _actorsLeave.insert(itLeave, pActor);
    }
}

/*! Removes the actor from internal datastructurs.
 */

void
DepthFirstAction::detachEvent(ActorBase *pActor, UInt32 uiActorId)
{
    ActorApplyStoreIt      itEnter  = _actorsEnter.begin();
    ActorApplyStoreConstIt endEnter = _actorsEnter.end  ();

    ActorApplyStoreIt      itLeave  = _actorsLeave.begin();
    ActorApplyStoreConstIt endLeave = _actorsLeave.end  ();

    if(pActor->getApplyEnter() == true)
    {
        for(; itEnter != endEnter; ++itEnter)
        {
            if(*itEnter == pActor)
            {
                _actorsEnter.erase(itEnter);
                break;
            }
        }
    }

    if(pActor->getApplyLeave() == true)
    {
        for(; itLeave != endLeave; ++itLeave)
        {
            if(*itLeave == pActor)
            {
                _actorsLeave.erase(itLeave);
                break;
            }
        }
    }

    Inherited::detachEvent(pActor, uiActorId);
}

/*! The actual traversal functunality, if no leave calls are required.
 */

DepthFirstAction::ResultE
DepthFirstAction::applyEnter(void)
{
    ResultE result   = NewActionTypes::Continue;
    NodePtr currNode;

    while((_nodeStack.empty() == false) && !(result & NewActionTypes::Quit))
    {
        currNode = _nodeStack.back().getNode();

        setUseActiveChildrenList(false);
        getActiveChildrenList   (     )->setParentNode(currNode);

        if( (currNode                                 == NullFC) ||
           ((currNode->getTravMask() & getTravMask()) == 0     )   )
        {
            _nodeStack.pop_back();
        }
        else
        {
            result = static_cast<ResultE>(NewActionTypes::Continue |
                                          callEnter(currNode)       );

            _nodeStack.pop_back();

            pushChildren(currNode, result);
        }
    }

    return result;
}

/*! The actual traveral functunality, if enter and leave calls are required.
 */

DepthFirstAction::ResultE
DepthFirstAction::applyEnterLeave(void)
{
    ResultE result   = NewActionTypes::Continue;
    NodePtr currNode;

    while((_nodeStack.empty() == false) && !(result & NewActionTypes::Quit))
    {
        NodeStackEntry &topEntry = _nodeStack.back ();
        currNode                 = topEntry.getNode();

        if( (currNode                                 == NullFC) ||
           ((currNode->getTravMask() & getTravMask()) == 0     )   )
        {
            _nodeStack.pop_back();
        }
        else
        {
            setUseActiveChildrenList(false);
            getActiveChildrenList   (     )->setParentNode(currNode);

            if(topEntry.getEnterNode() == true)
            {
                result = static_cast<ResultE>(NewActionTypes::Continue |
                                              callEnter(currNode)       );

                topEntry.setEnterNode(false);

                pushChildren(currNode, result);
            }
            else
            {
                result = static_cast<ResultE>(NewActionTypes::Continue |
                                              callLeave(currNode)       );

                _nodeStack.pop_back();
            }
        }
    }

    return result;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGDepthFirstAction.cpp,v 1.1 2004/04/20 13:47:08 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGDEPTHFIRSTACTION_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDEPTHFIRSTACTION_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
