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

#include "OSGDepthFirstAction.h"

OSG_USING_NAMESPACE

//==== PUBLIC ================================================================
//----------------------------------------------------------------------------
//    Destructor
//----------------------------------------------------------------------------

/*! Destructor.
 */

DepthFirstAction::~DepthFirstAction(void)
{
}

//----------------------------------------------------------------------------
//    Create
//----------------------------------------------------------------------------

/*! Create new instance.
 */

DepthFirstAction *
DepthFirstAction::create(void)
{
    return new DepthFirstAction();
}

//----------------------------------------------------------------------------
//    Apply
//----------------------------------------------------------------------------

/*! Apply the action to the node pRoot, i.e. traverse the graph below it.
 */

DepthFirstAction::ResultE
DepthFirstAction::apply(NodePtr pRoot)
{
    ResultE result = NewActionTypes::Continue;

    startEvent();

    result = startActors();

    if(result & NewActionTypes::Quit)
        return result;

    _nodeStack.push_back(NodeStackEntry(pRoot, 1));

    if((_extendLeaveActors.empty() == true) &&
       (_basicLeaveActors .empty() == true)    )
    {
        result = traverseEnter();
    }
    else
    {
        result = traverseEnterLeave();
    }

    if(result & NewActionTypes::Quit)
        return result;

    result = stopActors();

    stopEvent();

    return result;
}

//==== PROTECTED =============================================================
//----------------------------------------------------------------------------
//    Constructors
//----------------------------------------------------------------------------

/*! Default constructor.
 */

DepthFirstAction::DepthFirstAction(void)
    : Inherited         (),
      _nodeStack        (),
      _extendEnterActors(),
      _extendLeaveActors(),
      _basicEnterActors (),
      _basicLeaveActors ()
{
}

//----------------------------------------------------------------------------
//    Events
//----------------------------------------------------------------------------

/*! Inserts the extend actor into an internal data structure, depending on
    whether the enter node flag and leave node flag are set.
    This avoids making the destinction everytime the actors are called.
 */

void
DepthFirstAction::addExtendEvent(ExtendActorBase *pActor, UInt32 actorIndex)
{
    ExtendActorStoreIt itActors  = beginExtend();
    ExtendActorStoreIt endActors = beginExtend() + actorIndex;

    ExtendActorStoreIt itEnter   = _extendEnterActors.begin();
    ExtendActorStoreIt itLeave   = _extendLeaveActors.begin();

    for(; itActors != endActors; ++itActors)
    {
        if((*itActors)->getEnterNodeFlag() == true)
            ++itEnter;

        if((*itActors)->getLeaveNodeFlag() == true)
            ++itLeave;
    }

    if(pActor->getEnterNodeFlag() == true)
        _extendEnterActors.insert(itEnter, pActor);

    if(pActor->getLeaveNodeFlag() == true)
        _extendLeaveActors.insert(itLeave, pActor);
}

/*! Removes the extend actor from the internal data structures.
 */

void
DepthFirstAction::subExtendEvent(ExtendActorBase *pActor, UInt32 actorIndex)
{
    ExtendActorStoreIt itEnter  = _extendEnterActors.begin();
    ExtendActorStoreIt endEnter = _extendEnterActors.end  ();

    ExtendActorStoreIt itLeave  = _extendLeaveActors.begin();
    ExtendActorStoreIt endLeave = _extendLeaveActors.end  ();

    for(; itEnter != endEnter; ++itEnter)
    {
        if(*itEnter == pActor)
        {
            _extendEnterActors.erase(itEnter);

            break;
        }
    }

    for(; itLeave != endLeave; ++itLeave)
    {
        if(*itLeave == pActor)
        {
            _extendLeaveActors.erase(itLeave);

            break;
        }
    }
}

/*! Inserts the basic actor into an internal data structure, depending on
    whether the enter node flag and leave node flag are set.
    This avoids making the destinction everytime the actors are called.
 */

void
DepthFirstAction::addBasicEvent(BasicActorBase *pActor, UInt32 actorIndex)
{
    BasicActorStoreIt itActors  = beginBasic();
    BasicActorStoreIt endActors = beginBasic() + actorIndex;

    BasicActorStoreIt itEnter   = _basicEnterActors.begin();
    BasicActorStoreIt itLeave   = _basicLeaveActors.begin();

    for(; itActors != endActors; ++itActors)
    {
        if((*itActors)->getEnterNodeFlag() == true)
            ++itEnter;

        if((*itActors)->getLeaveNodeFlag() == true)
            ++itLeave;
    }

    if(pActor->getEnterNodeFlag() == true)
        _basicEnterActors.insert(itEnter, pActor);

    if(pActor->getLeaveNodeFlag() == true)
        _basicLeaveActors.insert(itLeave, pActor);
}

/*! Removes the extend actor from the internal data structures.
 */

void
DepthFirstAction::subBasicEvent(BasicActorBase *pActor, UInt32 actorIndex)
{
    BasicActorStoreIt itEnter  = _basicEnterActors.begin();
    BasicActorStoreIt endEnter = _basicEnterActors.end  ();

    BasicActorStoreIt itLeave  = _basicLeaveActors.begin();
    BasicActorStoreIt endLeave = _basicLeaveActors.end  ();

    for(; itEnter != endEnter; ++itEnter)
    {
        if(*itEnter == pActor)
        {
            _basicEnterActors.erase(itEnter);

            break;
        }
    }

    for(; itLeave != endLeave; ++itLeave)
    {
        if(*itLeave == pActor)
        {
            _basicLeaveActors.erase(itLeave);

            break;
        }
    }
}

/*! Does nothing, DepthFirstAction never copies state.
 */

void
DepthFirstAction::beginEditStateEvent(ActorBase *pActor, UInt32 actorId)
{
}

/*! Does nothing, DepthFirstAction never copies state.
 */

void
DepthFirstAction::endEditStateEvent(ActorBase *pActor, UInt32 actorId)
{
}

//==== PRIVATE ===============================================================
//----------------------------------------------------------------------------
//    Helper Methods
//----------------------------------------------------------------------------

/*! Drives the traversal of the graph. It only calls the actors upon "entering"
    a node.
 */

DepthFirstAction::ResultE
DepthFirstAction::traverseEnter(void)
{
    ResultE result = NewActionTypes::Continue;
    NodePtr pNode;
    Int32   nodePass;     // pass over the current node
    UInt32  multiPasses;  // requested passes over the current node

    while((_nodeStack.empty() == false) && !(result & NewActionTypes::Quit))
    {
        pNode    = _nodeStack.back().getNode     ();
        nodePass = _nodeStack.back().getPassCount();

        getChildrenList().setParentNode(pNode);

#ifdef OSG_NEWACTION_STATISTICS
        getStatistics()->getElem(statNodesEnter)->inc();
#endif /* OSG_NEWACTION_STATISTICS */

        result      = enterNode   (pNode, static_cast<UInt32>(nodePass - 1));
        multiPasses = getNumPasses(                                        );

        _nodeStack.pop_back();

        // only initial pass (nodePass == 1) can request multiPasses
        if((nodePass == 1) && (multiPasses > 1))
        {
            for(; multiPasses > 1; --multiPasses)
            {
                _nodeStack.push_back(NodeStackEntry(pNode, multiPasses));
            }
        }

        pushChildren(pNode, result);
    }

    return result;
}

/*! Drives the traversal of the graph. It calls the actors upon "entering" and
    "leaving" a node.
 */

DepthFirstAction::ResultE
DepthFirstAction::traverseEnterLeave(void)
{
    ResultE result = NewActionTypes::Continue;
    NodePtr pNode;
    Int32   nodePass;     // pass over the current node
    UInt32  multiPasses;  // requested passes over the current node

    while((_nodeStack.empty() == false) && !(result & NewActionTypes::Quit))
    {
        pNode    = _nodeStack.back().getNode     ();
        nodePass = _nodeStack.back().getPassCount();

        getChildrenList().setParentNode(pNode);

        if(nodePass > 0)
        {
            // positive pass -> enter node

#ifdef OSG_NEWACTION_STATISTICS
            getStatistics()->getElem(statNodesEnter)->inc();
#endif /* OSG_NEWACTION_STATISTICS */

            result      = enterNode   (pNode, static_cast<UInt32>(nodePass - 1));
            multiPasses = getNumPasses(               );

            // only initial pass (nodePass == 1) can request multiPasses
            if((nodePass == 1) && (multiPasses > 1))
            {
                // remove current node from stack
                _nodeStack.pop_back();

                for(; multiPasses > 1; --multiPasses)
                {
                    _nodeStack.push_back(NodeStackEntry(pNode, multiPasses));
                }

                // readd current node - with negative pass -> leave
                _nodeStack.push_back(NodeStackEntry(pNode, -nodePass));
            }
            else
            {
                // change current node passCount to negative -> leave
                _nodeStack.back().setPassCount(-nodePass);
            }

            pushChildren(pNode, result);
        }
        else
        {
            // negative pass -> leave node

#ifdef OSG_NEWACTION_STATISTICS
            getStatistics()->getElem(statNodesLeave)->inc();
#endif /* OSG_NEWACTION_STATISTICS */

            result = leaveNode(pNode, static_cast<UInt32>(-nodePass - 1));

            _nodeStack.pop_back();
        }
    }

    return result;
}

/*! Pushes the active children and extra children of the traversed node onto
    the internal stack.
 */

void
DepthFirstAction::pushChildren(const NodePtr &pNode, ResultE result)
{
    if(result & (NewActionTypes::Skip  |
                 NewActionTypes::Break |
                 NewActionTypes::Quit   ))
    {
        setChildrenListEnabled(false);
        setNumPasses          (1    );

        getExtraChildrenList().clear();

        return;
    }

    ChildrenList      &cl  = getChildrenList     ();
    ExtraChildrenList &ecl = getExtraChildrenList();

    if(getChildrenListEnabled() == true)
    {
        for(UInt32 i = 0, size = cl.getSize(); i < size; ++i)
        {
            if(( cl.getActive(i)                                 == true  ) &&
               ( cl.getChild (i)                                 != NullFC) &&
               ((cl.getChild (i)->getTravMask() & getTravMask()) != 0     )   )
            {
                _nodeStack.push_back(NodeStackEntry(cl.getChild(i), 1));
            }
        }
    }
    else
    {
        MFNodePtr::const_iterator itChildren  = pNode->getMFChildren()->begin();
        MFNodePtr::const_iterator endChildren = pNode->getMFChildren()->end  ();

        for(; itChildren != endChildren; ++itChildren)
        {
            if((  *itChildren                                  != NullFC) &&
               (((*itChildren)->getTravMask() & getTravMask()) != 0     )   )
            {
                _nodeStack.push_back(NodeStackEntry(*itChildren, 1));
            }
        }
    }

    for(UInt32 i = 0, size = ecl.getSize(); i < size; ++i)
    {
        if(( ecl.getActive(i)                                 == true  ) &&
           ( ecl.getChild (i)                                 != NullFC) &&
           ((ecl.getChild (i)->getTravMask() & getTravMask()) != 0     )   )
        {
            _nodeStack.push_back(NodeStackEntry(ecl.getChild(i), 1));
        }
    }

    setChildrenListEnabled(false);
    setNumPasses          (1    );
    ecl.clear             (     );
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGDepthFirstAction.cpp,v 1.4 2004/09/17 14:09:42 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGDEPTHFIRSTACTION_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDEPTHFIRSTACTION_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
