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

#include "OSGDepthFirstStateAction.h"

OSG_USING_NAMESPACE

//==== PUBLIC ================================================================

#ifdef OSG_NEWACTION_STATISTICS

//----------------------------------------------------------------------------
//    Statistics
//----------------------------------------------------------------------------

StatElemDesc<StatIntElem>
DepthFirstStateAction::statStateClones  ("DepthFirstState::stateClones",
                                         "Number of state clones created"     );
StatElemDesc<StatIntElem>
DepthFirstStateAction::statStateRestores("DepthFirstState::statStateRestores",
                                         "Number of state restores"           );

#endif /* OSG_NEWACTION_STATISTICS */

//----------------------------------------------------------------------------
//    Destructor
//----------------------------------------------------------------------------

/*! Destructor.
 */

DepthFirstStateAction::~DepthFirstStateAction(void)
{
}

//----------------------------------------------------------------------------
//    Create
//----------------------------------------------------------------------------

/*! Create new instance.
 */

DepthFirstStateAction *
DepthFirstStateAction::create(void)
{
    return new DepthFirstStateAction();
}

//----------------------------------------------------------------------------
//    Apply
//----------------------------------------------------------------------------

DepthFirstStateAction::ResultE
DepthFirstStateAction::apply(NodePtr pRoot)
{
    ResultE result = NewActionTypes::Continue;

    startEvent();

    result = startActors();

    if(result & NewActionTypes::Quit)
        return result;

    _itInitialState = getState  ();
    _itActiveState  = cloneState();

    // gained refs: active, root
    incRefCount(_itActiveState, 2);

    _nodeStack.push_back(NodeStackEntry(pRoot, _itActiveState, 1));

    if((_extendLeaveActors.empty() == true) &&
       (_basicLeaveActors .empty() == true)    )
    {
        result = traverseEnter();
    }
    else
    {
        result = traverseEnterLeave();
    }

    setState(_itInitialState);

    // lost refs: active, current node
    decRefCount(_itActiveState, 2);

    _itActiveState   = _itInitialState;
    _stateClonedFlag = true;

    _nodeStack         .clear();
#ifndef OSG_NEWACTION_STATESLOTINTERFACE
    _stateStore        .clear();
#endif
    _stateRefCountStore.clear();

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

DepthFirstStateAction::DepthFirstStateAction(void)
    : Inherited          (     ),
      _nodeStack         (     ),
      _stateRefCountStore(     ),
#ifndef OSG_NEWACTION_STATESLOTINTERFACE
      _stateStore        (     ),
#endif
      _itInitialState    (     ),
      _itActiveState     (     ),
      _stateClonedFlag   (false),
      _extendEnterActors (     ),
      _extendLeaveActors (     ),
      _basicEnterActors  (     ),
      _basicLeaveActors  (     )
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
DepthFirstStateAction::addExtendEvent(ExtendActorBase *pActor, UInt32 actorIndex)
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
DepthFirstStateAction::subExtendEvent(ExtendActorBase *pActor, UInt32 actorIndex)
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
DepthFirstStateAction::addBasicEvent(BasicActorBase *pActor, UInt32 actorIndex)
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
DepthFirstStateAction::subBasicEvent(BasicActorBase *pActor, UInt32 actorIndex)
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

void
DepthFirstStateAction::startEvent(void)
{
    Inherited::startEvent();

#ifdef OSG_NEWACTION_STATISTICS
    getStatistics()->getElem(statStateClones  )->reset();
    getStatistics()->getElem(statStateRestores)->reset();
#endif /* OSG_NEWACTION_STATISTICS */
}

void
DepthFirstStateAction::stopEvent(void)
{
    Inherited::stopEvent();
}


/*! Creates a copy of the state of the attached actors and activates the copy.
 */

void
DepthFirstStateAction::beginEditStateEvent(ActorBase *pActor, UInt32 actorId)
{
    if(_stateClonedFlag == false)
    {
#ifdef OSG_NEWACTION_STATISTICS
        getStatistics()->getElem(statStateClones)->inc();
#endif /* OSG_NEWACTION_STATISTICS */

        _stateClonedFlag = true;

        StateRefCountStoreIt itClonedState = cloneState();

        // gained refs: active and current node
        incRefCount(itClonedState, 2);

        // lost refs: active and current node
        decRefCount(_itActiveState, 2);

        _nodeStack.back().setStateRefCount(itClonedState);

        _itActiveState = itClonedState;
    }
}

/*! Does nothing.
 */

void
DepthFirstStateAction::endEditStateEvent(ActorBase *pActor, UInt32 actorId)
{
}

//==== PRIVATE ===============================================================
//----------------------------------------------------------------------------
//    Helper Methods
//----------------------------------------------------------------------------

DepthFirstStateAction::ResultE
DepthFirstStateAction::traverseEnter(void)
{
    ResultE              result          = NewActionTypes::Continue;
    NodePtr              pNode;
    Int32                nodePass;        // pass over current node
    UInt32               multiPasses;     // requested passes over current node
    StateRefCountStoreIt itStateRefCount; // state for current node

    while((_nodeStack.empty() == false) && !(result & NewActionTypes::Quit))
    {
        pNode           = _nodeStack.back().getNode         ();
        nodePass        = _nodeStack.back().getPassCount    ();
        itStateRefCount = _nodeStack.back().getStateRefCount();

#ifdef OSG_NEWACTION_STATISTICS
        getStatistics()->getElem(statNodesEnter)->inc();
#endif /* OSG_NEWACTION_STATISTICS */

        if(itStateRefCount != _itActiveState)
        {
#ifdef OSG_NEWACTION_STATISTICS
            getStatistics()->getElem(statStateRestores)->inc();
#endif /* OSG_NEWACTION_STATISTICS */

            setState(itStateRefCount);

            // gained refs: active
            incRefCount(itStateRefCount);

            // lost refs: active
            decRefCount(_itActiveState);

            _itActiveState = itStateRefCount;
        }

        _stateClonedFlag = false;

        getChildrenList().setParentNode(pNode);

        result      = enterNode   (pNode, static_cast<UInt32>(nodePass - 1));
        multiPasses = getNumPasses(                                        );

        _nodeStack.pop_back();

        // only initial pass (nodePass == 1) can request multiPasses
        if((nodePass == 1) && (multiPasses > 1))
        {
            for(; multiPasses > 1; --multiPasses)
            {
                // gained refs: additional pass
                incRefCount(_itActiveState);
                
                _nodeStack.push_back(
                    NodeStackEntry(pNode, _itActiveState, multiPasses));
            }
        }
        
        pushChildren(pNode, result);

        // lost refs: current node
        decRefCount(_itActiveState);
    }

    return result;
}

DepthFirstStateAction::ResultE
DepthFirstStateAction::traverseEnterLeave(void)
{
    ResultE              result          = NewActionTypes::Continue;
    Int32                nodePass;        // pass over current node
    UInt32               multiPasses;     // requested passes over current node
    NodePtr              pNode;
    StateRefCountStoreIt itStateRefCount;

    while((_nodeStack.empty() == false) && !(result & NewActionTypes::Quit))
    {
        pNode           = _nodeStack.back().getNode         ();
        nodePass        = _nodeStack.back().getPassCount    ();
        itStateRefCount = _nodeStack.back().getStateRefCount();

        if(itStateRefCount != _itActiveState)
        {
#ifdef OSG_NEWACTION_STATISTICS
            getStatistics()->getElem(statStateRestores)->inc();
#endif /* OSG_NEWACTION_STATISTICS */

            setState(itStateRefCount);

            // gained refs: active
            incRefCount(itStateRefCount);

            // lost refs: active
            decRefCount(_itActiveState);

            _itActiveState = itStateRefCount;
        }

        getChildrenList().setParentNode(pNode);

        if(nodePass > 0)
        {
            // positive pass -> enter node
            
#ifdef OSG_NEWACTION_STATISTICS
            getStatistics()->getElem(statNodesEnter)->inc();
#endif /* OSG_NEWACTION_STATISTICS */
            
            _stateClonedFlag = false;

            result      = enterNode   (pNode, static_cast<UInt32>(nodePass - 1));
            multiPasses = getNumPasses(                                        );

            // only initial pass (nodePass == 1) can request multiPass.
            if((nodePass == 1) && (multiPasses > 1))
            {
                // remove current node from stack
                _nodeStack.pop_back();
                
                for(; multiPasses > 1; -- multiPasses)
                {
                    // gained refs: addtional passs
                    incRefCount(_itActiveState);
                    
                    _nodeStack.push_back(
                        NodeStackEntry(pNode, _itActiveState, multiPasses));
                }
                
                // readd current node - with negative pass -> leave
                _nodeStack.push_back(
                    NodeStackEntry(pNode, _itActiveState, -nodePass));
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
            
            _stateClonedFlag = true;

            result = leaveNode(pNode, static_cast<UInt32>(-nodePass - 1));

            _nodeStack.pop_back();

            // lost refs: current node
            decRefCount(_itActiveState);
        }
    }

    return result;
}

void
DepthFirstStateAction::pushChildren(const NodePtr &pNode, ResultE result)
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
                // gained refs: child
                incRefCount(_itActiveState);

                _nodeStack.push_back(
                    NodeStackEntry(cl.getChild(i), _itActiveState, 1));
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
                // gained refs: child
                incRefCount(_itActiveState);

                _nodeStack.push_back(
                    NodeStackEntry(*itChildren, _itActiveState, 1));
            }
        }
    }

    for(UInt32 i = 0, size = ecl.getSize(); i < size; ++i)
    {
        if(( ecl.getActive(i)                                 == true  ) &&
           ( ecl.getChild (i)                                 != NullFC) &&
           ((ecl.getChild (i)->getTravMask() & getTravMask()) != 0     )   )
        {
            // gained refs: extra child
            incRefCount(_itActiveState);

            _nodeStack.push_back(
                NodeStackEntry(ecl.getChild(i), _itActiveState, 1));
        }
    }

    setChildrenListEnabled(false);
    ecl.clear             (     );
    setNumPasses          (1    );
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGDepthFirstStateAction.cpp,v 1.2 2004/09/17 14:09:42 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGDEPTHFIRSTSTATEACTION_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGDEPTHFIRSTSTATEACTION_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
