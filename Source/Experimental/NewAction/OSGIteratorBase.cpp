
#include <OSGConfig.h>
#include "OSGIteratorBase.h"
#include "OSGActorBase.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::IteratorBase

Base class for all Iterators that has facilities to communicate with the
NewAction object it is assigned to.

*/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*------------------------------ destructor -------------------------------*/

IteratorBase::~IteratorBase(void)
{
}

/*-------------------------------- roots ----------------------------------*/

void
IteratorBase::addRoot(NodePtr pRoot)
{
    _roots.push_back(pRoot);
}

void
IteratorBase::addRoot(const RootList &roots)
{
    _roots.insert(_roots.end(), roots.begin(), roots.end());
}

void
IteratorBase::clearRoots(void)
{
    _roots.clear();
}

const IteratorBase::RootList &
IteratorBase::getRoots(void) const
{
    return _roots;
}

IteratorBase::RootList &
IteratorBase::getRoots(void)
{
    return _roots;
}

/*----------------------------- active nodes ------------------------------*/

void
IteratorBase::resetNodeList(void)
{
    _activeNodes.clear();

    _bUseNodeList = false;
}

void
IteratorBase::setUseNodeList(void)
{
    if(_bUseNodeList == false)
    {
        _bUseNodeList = true;

        _activeNodes.setParent(getCurrentNode());
    }
}

bool
IteratorBase::getUseNodeList(void) const
{
    return _bUseNodeList;
}

ActiveNodeListIt
IteratorBase::beginNodes(void)
{
    return _activeNodes.begin();
}

ActiveNodeListIt
IteratorBase::endNodes(void)
{
    return _activeNodes.end();
}

ActiveNodeListConstIt
IteratorBase::beginNodes(void) const
{
    return _activeNodes.begin();
}

ActiveNodeListConstIt
IteratorBase::endNodes(void) const
{
    return _activeNodes.end();
}

ActiveNodeList &
IteratorBase::getNodeList(void)
{
    return _activeNodes;
}

const ActiveNodeList &
IteratorBase::getNodeList(void) const
{
    return _activeNodes;
}

/*------------------------------- access ----------------------------------*/

NewAction *
IteratorBase::getAction(void)
{
    return _pAction;
}

NodePtr
IteratorBase::getCurrentNode(void)
{
    return _pCurrNode;
}

/*------------------------------- signals -----------------------------*/

void
IteratorBase::receiveActorAdd(ActorBase *pActor, UInt32 uiActorId)
{
    if(pActor->hasEnterMethod() == true)
    {
        ActorStoreIt itEnter  = beginEnterList();
        ActorStoreIt endEnter = endEnterList  ();
        
        for(; itEnter != endEnter; ++itEnter)
        {
            if((*itEnter)->getActorId() >= uiActorId)
                break;
        }
        
        _enterList.insert(itEnter, pActor);
    }

    if(pActor->hasLeaveMethod() == true)
    {
        ActorStoreIt itLeave  = beginLeaveList();
        ActorStoreIt endLeave = endLeaveList  ();

        for(; itLeave != endLeave; ++itLeave)
        {
            if((*itLeave)->getActorId() >= uiActorId)
                break;
        }
        
        _leaveList.insert(itLeave, pActor);

        ++_uiNumLeaveActors;
    }

    ++_uiNumActors;

    if(pActor->hasOrderedState() == true)
    {
        ++_uiNumOrderedStateActors;
    }
}

void
IteratorBase::receiveActorSub(ActorBase *pActor, UInt32 uiActorId)
{
    if(pActor->hasEnterMethod() == true)
    {
        ActorStoreIt itEnter  = beginEnterList();
        ActorStoreIt endEnter = endEnterList  ();

        for(; itEnter != endEnter; ++itEnter)
        {
            if((*itEnter)->getActorId() == uiActorId)
            {
                _enterList.erase(itEnter);

                break;
            }
        }
    }

    if(pActor->hasLeaveMethod() == true)
    {
        ActorStoreIt itLeave  = beginLeaveList();
        ActorStoreIt endLeave = endLeaveList  ();

        for(; itLeave != endLeave; ++itLeave)
        {
            if((*itLeave)->getActorId() == uiActorId)
            {
                _leaveList.erase(itLeave);

                break;
            }
        }

        --_uiNumLeaveActors;
    }

    --_uiNumActors;

    if(pActor->hasOrderedState() == true)
    {
        --_uiNumOrderedStateActors;
    }
}

void
IteratorBase::receiveActorsClear(void)
{
    _enterList.clear();
    _leaveList.clear();
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*--------------------------- constructor ---------------------------------*/

IteratorBase::IteratorBase(void)
    : _activeNodes            (      ),
      _bUseNodeList           (false ),
      _roots                  (      ),
      _pCurrNode              (NullFC),
      _enterList              (      ),
      _leaveList              (      ),
      _uiNumActors            (     0),
      _uiNumLeaveActors       (     0),
      _uiNumOrderedStateActors(     0)
{
}

/*------------------------- action interface ------------------------------*/


IteratorBase::ResultE
IteratorBase::callEnter(NodePtr pNode)
{
    ActorStoreIt iterActors = beginEnterList();
    ActorStoreIt endActors  = endEnterList  ();

    setCurrentNode(pNode);

    return _pAction->enterNode(pNode, iterActors, endActors);
}

IteratorBase::ResultE
IteratorBase::callLeave(NodePtr pNode)
{
    ActorStoreIt iterActors = beginLeaveList();
    ActorStoreIt endActors  = endLeaveList  ();

    setCurrentNode(pNode);

    return _pAction->leaveNode(pNode, iterActors, endActors);
}

IteratorBase::ResultE
IteratorBase::startActors(void)
{
    return _pAction->startActors();
}

IteratorBase::ResultE
IteratorBase::stopActors(void)
{
    return _pAction->stopActors();
}

void
IteratorBase::cloneState(ActorStateChunk *pChunk)
{
    _pAction->cloneState(pChunk);
}

void
IteratorBase::getState(ActorStateChunk *pChunk)
{
    _pAction->getState(pChunk);
}

void
IteratorBase::setState(ActorStateChunk *pChunk)
{
    _pAction->setState(pChunk);
}

IteratorBase::ActorStoreIt
IteratorBase::beginActors(void)
{
    return _pAction->beginActors();
}

IteratorBase::ActorStoreIt
IteratorBase::endActors(void)
{
    return _pAction->endActors();
}

IteratorBase::ActorStoreConstIt
IteratorBase::beginActors(void) const
{
    return _pAction->beginActors();
}

IteratorBase::ActorStoreConstIt
IteratorBase::endActors(void) const
{
    return _pAction->endActors();
}

/*----------------------- derived class access ----------------------------*/


void
IteratorBase::setCurrentNode(NodePtr pCurrNode)
{
    _pCurrNode = pCurrNode;
}

IteratorBase::ActorStoreIt
IteratorBase::beginEnterList(void)
{
    return _enterList.begin();
}

IteratorBase::ActorStoreIt
IteratorBase::endEnterList(void)
{
    return _enterList.end();
}

IteratorBase::ActorStoreIt
IteratorBase::beginLeaveList(void)
{
    return _leaveList.begin();
}

IteratorBase::ActorStoreIt
IteratorBase::endLeaveList(void)
{
    return _leaveList.end();
}    

UInt32
IteratorBase::getNumActors(void)
{
    return _uiNumActors;
}

UInt32
IteratorBase::getNumLeaveActors(void)
{
    return _uiNumLeaveActors;
}

UInt32
IteratorBase::getNumOrderedStateActors(void)
{
    return _uiNumOrderedStateActors;
}

bool
IteratorBase::hasLeaveActors(void)
{
    return (_uiNumLeaveActors > 0);
}

bool
IteratorBase::hasOrderedStateActors(void)
{
    return (_uiNumOrderedStateActors > 0);
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

void
IteratorBase::setAction(NewAction *pAction)
{
    _pAction = pAction;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGIteratorBase.cpp,v 1.1 2003/10/10 13:51:06 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGITERATORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGITERATORBASE_INLINE_CVSID;
}
