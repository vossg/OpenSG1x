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

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*    PRIVATE Types                                                        */

inline
DepthFirstAction::NodeStackEntry::NodeStackEntry(const NodePtr &pNode)
    : _pNode     (pNode),
      _bEnterNode(true )
{
}

inline
DepthFirstAction::NodeStackEntry::NodeStackEntry(const NodePtr &pNode,
                                                       bool     bEnterNode)
    : _pNode     (pNode     ),
      _bEnterNode(bEnterNode)
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
DepthFirstAction::NodeStackEntry::getEnterNode(void) const
{
    return _bEnterNode;
}

inline void
DepthFirstAction::NodeStackEntry::setEnterNode(bool bEnterNode)
{
    _bEnterNode = bEnterNode;
}

/*-------------------------------------------------------------------------*/
/*    Helper Methods                                                       */

inline DepthFirstAction::ResultE
DepthFirstAction::callEnter(const NodePtr &pNode)
{
    ResultE                result    = NewActionTypes::Continue;
    ActorApplyStoreIt      itActors  = _actorsEnter.begin();
    ActorApplyStoreConstIt endActors = _actorsEnter.end  ();

    for(; (itActors != endActors) && !(result & NewActionTypes::Quit);
        ++itActors)
    {
        result = static_cast<ResultE>(result | (*itActors)->applyEnter(pNode));
    }

    return result;
}

inline DepthFirstAction::ResultE
DepthFirstAction::callLeave(const NodePtr &pNode)
{
    ResultE                result    = NewActionTypes::Continue;
    ActorApplyStoreIt      itActors  = _actorsLeave.begin();
    ActorApplyStoreConstIt endActors = _actorsLeave.end  ();

    for(; (itActors != endActors) && !(result & NewActionTypes::Quit);
        ++itActors)
    {
        result = static_cast<ResultE>(result | (*itActors)->applyLeave(pNode));
    }

    return result;
}

inline void
DepthFirstAction::pushChildren(const NodePtr &pNode, ResultE result)
{
    if(result & NewActionTypes::Quit)
        return;

    if(result & NewActionTypes::Skip)
        return;

    if(getUseActiveChildrenList() == true)
    {
        ActiveChildrenList *pActiveChildrenList = getActiveChildrenList();
        
        ActiveChildrenList::MFNodePtrConstIt itChildren    =
            pActiveChildrenList->beginChildren();
        ActiveChildrenList::MFNodePtrConstIt endItChildren =
            pActiveChildrenList->endChildren  ();

        for(; itChildren != endItChildren; ++itChildren)
        {
            if(pActiveChildrenList->getActive(itChildren) == true)
            {
                _nodeStack.push_back(NodeStackEntry(*itChildren));
            }
        }
    }
    else
    {
        MFNodePtr::const_iterator itChildren    =
            pNode->getMFChildren()->begin();
        MFNodePtr::const_iterator endItChildren =
            pNode->getMFChildren()->end  ();

        for(; itChildren != endItChildren; ++itChildren)
        {
            _nodeStack.push_back(NodeStackEntry(*itChildren));
        }
    }
}

OSG_END_NAMESPACE

#define OSGDEPTHFIRSTACTION_INLINE_CVSID "@(#)$Id: OSGDepthFirstAction.inl,v 1.1 2004/04/20 13:47:08 neumannc Exp $"
