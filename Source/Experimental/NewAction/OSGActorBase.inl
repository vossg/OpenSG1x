/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     * 
 *                                                                           * 
 *                                                                           * 
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                * 
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

/*--------------------------- Action Interface ----------------------------*/

inline void
ActorBase::addRoot(NodePtr pRoot)
{
    _pAction->addRoot(pRoot);
}

inline void
ActorBase::addRoot(const RootList &roots)
{
    _pAction->addRoot(roots);
}

inline const ActorBase::RootList &
ActorBase::getRoots(void) const
{
    return _pAction->getRoots();
}

inline ActorBase::RootList &
ActorBase::getRoots(void)
{
    return _pAction->getRoots();
}

inline NodePtr
ActorBase::getCurrNode(void) const
{
    return _pAction->getCurrNode();
}

inline void
ActorBase::setUseNodeList(void)
{
    _pAction->setUseNodeList();
}

inline bool
ActorBase::getUseNodeList(void) const
{
    return _pAction->getUseNodeList();
}

inline ActiveNodeListIt 
ActorBase::beginNodes(void)
{
    return _pAction->beginNodes();
}

inline ActiveNodeListIt
ActorBase::endNodes(void)
{
    return _pAction->endNodes();
}

inline ActiveNodeListConstIt
ActorBase::beginNodes(void) const
{
    return _pAction->beginNodes();
}

inline ActiveNodeListConstIt
ActorBase::endNodes(void) const
{
    return _pAction->endNodes();
}

inline ActiveNodeList &
ActorBase::getNodeList(void)
{
    return _pAction->getNodeList();
}

inline const ActiveNodeList &
ActorBase::getNodeList(void) const
{
    return _pAction->getNodeList();
}

/*-------------------------- get identification ---------------------------*/

inline NewAction *
ActorBase::getAction(void)
{
    return _pAction;
}


inline const NewAction *
ActorBase::getAction(void) const
{
    return _pAction;
}

inline UInt32
ActorBase::getActorId(void) const
{
    return _uiActorId;
}

/*------------------------------ state ------------------------------------*/

inline const ActorBase::ActorStateBase *
ActorBase::getState(void) const
{
    return _pState;
}

inline ActorBase::ActorStateBase *
ActorBase::getState(void)
{
    return _pState;
}

inline void
ActorBase::setState(ActorStateBase *pState)
{
    _pState = pState;
}

/*-------------------------- emit signals ---------------------------------*/

inline void
ActorBase::emitStateRead(void) const
{
    _pAction->emitStateRead(_uiActorId);
}

inline void
ActorBase::emitStateWrite(void) const
{
    _pAction->emitStateWrite(_uiActorId);
}

/*-------------------------- set identification ---------------------------*/

inline void
ActorBase::setAction(NewAction *pAction)
{
    _pAction = pAction;
}

inline void
ActorBase::setActorId(UInt32 uiActorId)
{
    _uiActorId = uiActorId;
}

OSG_END_NAMESPACE

#define OSGACTORBASE_INLINE_CVSID "@(#)$Id: OSGActorBase.inl,v 1.1 2003/10/10 13:51:06 neumannc Exp $"
