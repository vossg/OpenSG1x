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

#include "OSGPriorityAction.h"

OSG_USING_NAMESPACE

//==== PUBLIC ================================================================

#ifdef OSG_NEWACTION_STATISTICS

//----------------------------------------------------------------------------
//    Statistics
//----------------------------------------------------------------------------

StatElemDesc<StatIntElem>
PriorityAction::statStateClones  ("PriorityAction::stateClones",
                                  "Number of state clones created");
StatElemDesc<StatIntElem>
PriorityAction::statStateRestores("PriorityAction::statStateRestores",
                                  "Number of state restores"          );

#endif /* OSG_NEWACTION_STATISTICS */

//----------------------------------------------------------------------------
//    Destructor
//----------------------------------------------------------------------------

PriorityAction::~PriorityAction(void)
{
}

//----------------------------------------------------------------------------
//    Create
//----------------------------------------------------------------------------

/*! Create new instance.
 */

PriorityAction *
PriorityAction::create(void)
{
    return new PriorityAction();
}

//----------------------------------------------------------------------------
//    Apply
//----------------------------------------------------------------------------

/*! Apply the action to the node pRoot, i.e. traverse the graph below it.
 */

PriorityAction::ResultE
PriorityAction::apply(NodePtr pRoot)
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

    pqPush(NodeQueueEntry(pRoot, PriorityTypeTraits::getZeroElement(),
                          1,     _itActiveState                       ));

    result = traverseEnter();

    setState(_itInitialState);

    // lost refs: active, current node
    decRefCount(_itActiveState, 2);

    _itActiveState   = _itInitialState;
    _stateClonedFlag = true;

    pqClear();
#ifndef OSG_NEWACTION_STATESLOTINTERFACE
    _stateStore        .clear();
#endif
    _stateRefCountStore.clear();

    if(result & NewActionTypes::Quit)
    {
        stopActors();
        stopEvent ();
    }
    else
    {
        result = stopActors();
        stopEvent();
    }
    
    return result;
}

//==== PROTECTED =============================================================
//----------------------------------------------------------------------------
//    Constructors
//----------------------------------------------------------------------------

PriorityAction::PriorityAction(void)
    : Inherited          (     ),
      _extendEnterActors (     ),
      _basicEnterActors  (     ),
      _nodePrioQueue     (     ),
      _nodePrioQueueComp (     ),
      _stateClonedFlag   (false),
#ifndef OSG_NEWACTION_STATESLOTINTERFACE
      _stateStore        (     ),
#endif
      _stateRefCountStore(     ),
      _itInitialState    (     ),
      _itActiveState     (     )
{
}

//----------------------------------------------------------------------------
//    Events
//----------------------------------------------------------------------------

/*! Inserts the extend actor into an internal data structure, depending on
    whether the enter node flag is set.
    This avoids making the destinction everytime the actors are called.
 */

void
PriorityAction::addExtendEvent(ExtendActorBase *pActor, UInt32 actorIndex)
{
    ExtendActorStoreIt itActors  = beginExtend();
    ExtendActorStoreIt endActors = beginExtend() + actorIndex;

    ExtendActorStoreIt itEnter   = _extendEnterActors.begin();

    if(pActor->getEnterNodeFlag() == true)
    {
        for(; itActors != endActors; ++itActors)
        {
            if((*itActors)->getEnterNodeFlag() == true)
                ++itEnter;
        }

        _extendEnterActors.insert(itEnter, pActor);
    }
}

/*! Removes the extend actor from the internal data structures.
 */

void
PriorityAction::subExtendEvent(ExtendActorBase *pActor, UInt32 actorIndex)
{
    ExtendActorStoreIt itEnter  = _extendEnterActors.begin();
    ExtendActorStoreIt endEnter = _extendEnterActors.end  ();

    for(; itEnter != endEnter; ++itEnter)
    {
        if(*itEnter == pActor)
        {
            _extendEnterActors.erase(itEnter);

            break;
        }
    }
}

/*! Inserts the basic actor into an internal data structure, depending on
    whether the enter node flag is set.
    This avoids making the destinction everytime the actors are called.
 */

void
PriorityAction::addBasicEvent(BasicActorBase *pActor, UInt32 actorIndex)
{
    BasicActorStoreIt itActors  = beginBasic();
    BasicActorStoreIt endActors = beginBasic() + actorIndex;

    BasicActorStoreIt itEnter   = _basicEnterActors.begin();

    if(pActor->getEnterNodeFlag() == true)
    {
        for(; itActors != endActors; ++itActors)
        {
            if((*itActors)->getEnterNodeFlag() == true)
                ++itEnter;
        }

        _basicEnterActors.insert(itEnter, pActor);
    }
}

/*! Removes the extend actor from the internal data structures.
 */

void
PriorityAction::subBasicEvent(BasicActorBase *pActor, UInt32 actorIndex)
{
    BasicActorStoreIt itEnter  = _basicEnterActors.begin();
    BasicActorStoreIt endEnter = _basicEnterActors.end  ();

    for(; itEnter != endEnter; ++itEnter)
    {
        if(*itEnter == pActor)
        {
            _basicEnterActors.erase(itEnter);

            break;
        }
    }
}

void
PriorityAction::startEvent(void)
{
    Inherited::startEvent();

#ifdef OSG_NEWACTION_STATISTICS
    getStatistics()->getElem(statStateClones  )->reset();
    getStatistics()->getElem(statStateRestores)->reset();
#endif /* OSG_NEWACTION_STATISTICS */
}

void
PriorityAction::stopEvent(void)
{
    Inherited::stopEvent();
}

/*! Creates a copy of the state of the attached actors and activates the copy.
 */

void
PriorityAction::beginEditStateEvent(ActorBase *pActor, UInt32 actorId)
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

        _itActiveState = itClonedState;
    }
}

/*! Does nothing.
 */

void
PriorityAction::endEditStateEvent(ActorBase *pActor, UInt32 actorId)
{
}

//==== PRIVATE ===============================================================
//----------------------------------------------------------------------------
//    Helper Methods.
//----------------------------------------------------------------------------

/*! Drives the traversal of the graph by activating the proper state for the
    nodes and calling the enterNode method of the actors.
 */

PriorityAction::ResultE
PriorityAction::traverseEnter(void)
{
    ResultE              result          = NewActionTypes::Continue;
    NodePtr              pNode;
    PriorityType         nodePrio;
    UInt32               nodePass;
    UInt32               multiPasses;
    StateRefCountStoreIt itStateRefCount;

    while((pqEmpty() == false) && !(result & NewActionTypes::Quit))
    {
        pNode           = pqTop().getNode         ();
        nodePrio        = pqTop().getPriority     ();
        nodePass        = pqTop().getPassCount    ();
        itStateRefCount = pqTop().getStateRefCount();

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

#ifdef OSG_NEWACTION_STATISTICS
        getStatistics()->getElem(statNodesEnter)->inc();
#endif /* OSG_NEWACTION_STATISTICS */

        result      = enterNode   (pNode, nodePass - 1);
        multiPasses = getNumPasses(                   );
        
        pqPop();
        
        // only initial pass (nodePass == 1) can request multiPasses
        if((nodePass == 1) && (multiPasses > 1))
        {
            for(; multiPasses > 1; --multiPasses)
            {
                // gained refs: additional pass
                incRefCount(_itActiveState);
                
                pqPush(NodeQueueEntry(pNode,       nodePrio, 
                                      multiPasses, _itActiveState));
            }
        }

        enqueueChildren(pNode, result);
    }

    return result;
}

/*! Inserts the active children and extra children into the internal
    priority queue.
 */

void
PriorityAction::enqueueChildren(const NodePtr &pNode, ResultE result)
{
    if(result & (NewActionTypes::Skip  |
                 NewActionTypes::Break |
                 NewActionTypes::Quit   ))
    {
        setChildrenListEnabled(false);
        setNumPasses          (1    );
        
        getExtraChildrenList().clear();

        // lost refs: current node
        decRefCount(_itActiveState);

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

                pqPush(NodeQueueEntry(cl.getChild(i), cl.getPriority(i),
                                      1,              _itActiveState    ));
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

                pqPush(
                    NodeQueueEntry(*itChildren,
                                   PriorityTypeTraits::getZeroElement(),
                                   1, _itActiveState                    ));
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

            pqPush(NodeQueueEntry(ecl.getChild(i), ecl.getPriority(i),
                                  1,               _itActiveState     ));
        }
    }

    setChildrenListEnabled(false);
    ecl.clear             (     );
    setNumPasses          (1    );

    // lost refs: current node
    decRefCount(_itActiveState);
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGPriorityAction.cpp,v 1.3 2004/09/17 14:09:43 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGPRIORITYACTION_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPRIORITYACTION_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
