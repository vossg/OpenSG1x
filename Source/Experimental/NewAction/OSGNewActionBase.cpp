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

#include "OSGNewActionBase.h"

#include "OSGActorBase.h"
#include "OSGExtendActorBase.h"
#include "OSGBasicActorBase.h"

OSG_USING_NAMESPACE

//----------------------------------------------------------------------------
//    Description
//----------------------------------------------------------------------------

// Abstract function doc

/*! \fn void osg::NewActionBase::addExtendEvent(ExtendActorBase *pActor,
    UInt32 actorIndex)

    This method is called whenever an extend actor is added to the action. It
    can be used by derived classes to organize the actors more efficiently.
 */

/*! \fn void osg::NewActionBase::subExtendEvent(ExtendActorBase *pActor,
    UInt32 actorIndex)

    This method is called whenever an extend actor is removed from the action.
    It can be used by derived classes to organize the actors more efficiently.
 */

/*! \fn void osg::NewActionBase::addBasicEvent(BasicActorBase *pActor,
    UInt32 actorIndex)

    This method is called whenever an basic actor is added to the action. It
    can be used by derived classes to organize the actors more efficiently.
 */

/*! \fn void osg::NewActionBase::subBasicEvent(BasicActorBase *pActor,
    UInt32 actorIndex)

    This method is called whenever an basic actor is removed from the action.
    It can be used by derived classes to organize the actors more efficiently.
 */

/*! \fn void osg::NewActionBase::beginEditStateEvent(ActorBase *pActor,
    UInt32 actorId)

    This method is called whenever ActorBase::beginEditState(void) is called,
    i.e. before an actor is about to modify its state.
 */

/*! \fn void osg::NewActionBase::endEditStateEvent(ActorBase *pActor,
    UInt32 actorId)

    This method is called whenever ActorBase::endEditState(void) is called,
    i.e. after an actor is done modifying its state.
 */

#ifdef OSG_NEWACTION_STATISTICS

//----------------------------------------------------------------------------
//    Statistics
//----------------------------------------------------------------------------

StatElemDesc<StatIntElem>
NewActionBase::statNodesEnter("NewActionBase::nodesEnter",
                              "Number of nodes entered"   );
StatElemDesc<StatIntElem>
NewActionBase::statNodesLeave("NewActionBase::nodesLeave",
                              "Number of nodes left"      );


#endif /* OSG_NEWACTION_STATISTICS */

//----------------------------------------------------------------------------
//    Destructor
//----------------------------------------------------------------------------

/*! Destructor.
 */

NewActionBase::~NewActionBase(void)
{
}

//----------------------------------------------------------------------------
//    Generic Actor Management
//----------------------------------------------------------------------------

/*! Add an actor to this action, it will be appended to the list of
    extend or basic actors. Returns the index at which the actor was added.
    \warning Actions assume exclusive ownership of an actor, you can not add
    an actor to two actions at the same time.

\dev
    The ActorBase class has three "visitor pattern" style methods, that will
    call the appropriate method of the action, e.g. assume pActor is actually
    derived from ExtendActorBase, then its addHelper method will call the
    addExtendActor method of the action passed as parameter.
\enddev
 */

UInt32
NewActionBase::addActor(ActorBase *pActor)
{
    return pActor->addHelper(this);
}

/*! Remove an actor from this action. The actor may now be attached to
    another action.

\dev
    See NewActionBase::addActor(ActorBase *pActor) for an explanation of
    the mechanism used to discover the type of pActor.
\enddev
 */

void
NewActionBase::subActor(ActorBase *pActor)
{
    pActor->subHelper(this);
}

/*! Return the index of an actor or TypeTraits<UInt32>::getMax() if the actor
    can not be found. Note that two actors may have the same index, if one is
    derived from ExtendActorBase and the other from BasicActorBase.

\dev
    See NewActionBase::addActor(ActorBase *pActor) for an explanation of
    the mechanism used to discover the type of pActor.

    I'm not sure if this is a useful thing to have ??  -carsten
\enddev
 */

UInt32
NewActionBase::findActor(ActorBase *pActor) const
{
    return pActor->findHelper(this);
}

/*! Return the total number of actors attached to this action.
 */

UInt32
NewActionBase::getNumActors(void) const
{
    return _extendActors.size() + _basicActors.size();
}

//----------------------------------------------------------------------------
//    Extend Actor Management
//----------------------------------------------------------------------------

/*! Add an extend actor to this action. Returns the index at which the actor
    was added.
    \warning Actions assume exclusive ownership of an actor, you can not add
    an actor to two actions at the same time.
 */

UInt32
NewActionBase::addExtendActor(ExtendActorBase *pActor)
{
    return addExtendActor(pActor, _extendActors.size());
}

/*! Add an extend actor to this action before the index pos. Returns the index
    at which the actor was added, i.e. this should be pos.
    \warning Actions assume exclusive ownership of an actor, you can not add
    an actor to two actions at the same time.
 */

UInt32
NewActionBase::addExtendActor(ExtendActorBase *pActor, UInt32 pos)
{
    UInt32 actorId = getNumActors();

    pActor       ->addEvent      (this,                        actorId);
    _extendActors. insert        (_extendActors.begin() + pos, pActor );
    this         ->addExtendEvent(pActor,                      pos    );

    return pos;
}

/*! Remove the extend actor at index pos. The actor may now be attached to
    another action.
 */

void
NewActionBase::subExtendActor(UInt32 pos)
{
    ExtendActorStoreIt  itActor = _extendActors.begin() + pos;
    ExtendActorBase    *pActor  = *itActor;

    this  ->subExtendEvent(pActor, pos                 );
    pActor->subEvent      (this,   pActor->getActorId());

    _extendActors.erase(itActor);
}

/*! Return the index of the extend actor or TypeTraits<UInt32>::getMax() if
    the actor is not found. The return value may be used as the pos argument
    to the addExtendActor and subExtendActor methods.
 */

UInt32
NewActionBase::findExtendActor(ExtendActorBase *pActor) const
{
    ExtendActorStoreConstIt itActors  = _extendActors.begin();
    ExtendActorStoreConstIt endActors = _extendActors.end  ();

    UInt32             pos       = 0;
    bool               found     = false;

    for(; (itActors != endActors) && !found; ++itActors, ++pos)
    {
        if(*itActors == pActor)
        {
            found = true;
            break;
        }
    }

    return (found ? pos : TypeTraits<UInt32>::getMax());
}

/*! Return the number of extend actors attached to the action.
 */

UInt32
NewActionBase::getNumExtendActors(void) const
{
    return _extendActors.size();
}

//----------------------------------------------------------------------------
//    Basic Actor Management
//----------------------------------------------------------------------------

/*! Add an basic actor to this action. Returns the index at which the actor
    was added.
    \warning Actions assume exclusive ownership of an actor, you can not add
    an actor to two actions at the same time.
 */

UInt32
NewActionBase::addBasicActor(BasicActorBase *pActor)
{
    return addBasicActor(pActor, _basicActors.size());
}

/*! Add an basic actor to this action before the index pos. Returns the index
    at which the actor was added, i.e. this should be pos.
    \warning Actions assume exclusive ownership of an actor, you can not add
    an actor to two actions at the same time.
 */

UInt32
NewActionBase::addBasicActor(BasicActorBase *pActor, UInt32 pos)
{
    UInt32 actorId = getNumActors();

    pActor      ->addEvent     (this,                       actorId);
    _basicActors. insert       (_basicActors.begin() + pos, pActor );
    this        ->addBasicEvent(pActor,                     pos    );

    return pos;
}

/*! Remove the basic actor at index pos. The actor may now be attached to
    another action.
 */

void
NewActionBase::subBasicActor(UInt32 pos)
{
    BasicActorStoreIt  itActor = _basicActors.begin() + pos;
    BasicActorBase    *pActor  = *itActor;

    this  ->subBasicEvent(pActor, pos                 );
    pActor->subEvent     (this,   pActor->getActorId());

    _basicActors.erase(itActor);
}

/*! Return the index of the basic actor or TypeTraits<UInt32>::getMax() if
    the actor is not found. The return value may be used as the pos argument
    to the addBasicActor and subBasicActor methods.
 */

UInt32
NewActionBase::findBasicActor(BasicActorBase *pActor) const
{
    BasicActorStoreConstIt itActors  = _basicActors.begin();
    BasicActorStoreConstIt endActors = _basicActors.end  ();

    UInt32            pos       = 0;
    bool              found     = false;

    for(; (itActors != endActors) && !found; ++itActors, ++pos)
    {
        if(*itActors == pActor)
        {
            found = true;
            break;
        }
    }

    return (found ? pos : TypeTraits<UInt32>::getMax());
}

/*! Return the number of basic actors attached to the action.
 */

UInt32
NewActionBase::getNumBasicActors(void) const
{
    return _basicActors.size();
}

//----------------------------------------------------------------------------
//    Constructor
//----------------------------------------------------------------------------

NewActionBase::NewActionBase(void)
    : _extendActors       (                           ),
      _basicActors        (                           ),
#ifdef OSG_NEWACTION_STATISTICS
      _pStatistics        (NULL                       ),
      _ownStatistics      (false                      ),
#endif /* OSG_NEWACTION_STATISTICS */
      _travMask           (TypeTraits<UInt32>::BitsSet),
      _numPasses          (1                          ),
      _childrenListEnabled(false                      ),
      _childrenList       (                           ),
      _extraChildrenList  (                           )
{
}

//----------------------------------------------------------------------------
//    Events
//----------------------------------------------------------------------------

/*! Called before the actors are started.
    When overriding this method the inherited version must be called.
 */

void
NewActionBase::startEvent(void)
{
#ifdef OSG_NEWACTION_STATISTICS
    if(_pStatistics == NULL)
    {
        _pStatistics   = StatCollector::create();
        _ownStatistics = true;
    }
    else
    {
        _ownStatistics = false;
    }

    getStatistics()->getElem(statNodesEnter)->reset();
    getStatistics()->getElem(statNodesLeave)->reset();
#endif /* OSG_NEWACTION_STATISTICS */
}

/*! Called after the actors are stopped.
    When overriding this method the inherited version must be called.
 */

void
NewActionBase::stopEvent(void)
{
#ifdef OSG_NEWACTION_STATISTICS
    if(_ownStatistics == true)
    {
        delete _pStatistics;
        _pStatistics = NULL;
    }
#endif /* OSG_NEWACTION_STATISTICS */
}

//----------------------------------------------------------------------------
//    Actor Access
//----------------------------------------------------------------------------

NewActionBase::ResultE
NewActionBase::startActors(void)
{
    ResultE            result      = NewActionTypes::Continue;

    ExtendActorStoreIt itExtend    = beginExtend();
    ExtendActorStoreIt endItExtend = endExtend  ();

    for(; (itExtend != endItExtend         ) &&
         !(result   &  NewActionTypes::Quit);    ++itExtend)
    {
        result = (*itExtend)->start();
    }

    BasicActorStoreIt itBasic    = beginBasic();
    BasicActorStoreIt endItBasic = endBasic  ();

    for(;  (itBasic != endItBasic          ) &&
          !(result  &  NewActionTypes::Quit);    ++itBasic)
    {
        result = (*itBasic)->start();
    }

    return result;
}

NewActionBase::ResultE
NewActionBase::stopActors(void)
{
    ResultE            result      = NewActionTypes::Continue;

    ExtendActorStoreIt itExtend    = beginExtend();
    ExtendActorStoreIt endItExtend = endExtend  ();

    for(; (itExtend != endItExtend         ) &&
         !(result   &  NewActionTypes::Quit);    ++itExtend)
    {
        result = (*itExtend)->stop();
    }

    BasicActorStoreIt itBasic    = beginBasic();
    BasicActorStoreIt endItBasic = endBasic  ();

    for(;  (itBasic != endItBasic          ) &&
          !(result  &  NewActionTypes::Quit);    ++itBasic)
    {
        result = (*itBasic)->stop();
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGNewActionBase.cpp,v 1.4 2005/08/30 13:18:01 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGNEWACTIONBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGNEWACTIONBASE_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
