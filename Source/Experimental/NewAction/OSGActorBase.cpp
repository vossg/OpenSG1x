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

#include <OSGConfig.h>
#include "OSGActorBase.h"

#include <OSGLog.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ActorBase::ActorStateBase
           Often Actors are naturally designed for depth first traversal. To
           allow different traversals all state that depends on the depth first
           order must be saved and restored. The ActorStateBase class is the
           for deriving classes that hold exactly the "ordered" state. You may
           put other state in there to but that results in unneccessary
           copying, unless you always use the DepthFirstIterator.
 */

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*----------------------- constructors & destructor  ----------------------*/

ActorBase::ActorStateBase::ActorStateBase(void)
{
}

ActorBase::ActorStateBase::ActorStateBase(const ActorStateBase &)
{
}

ActorBase::ActorStateBase::~ActorStateBase(void)
{
}

/*---------------------------------- clone  -------------------------------*/

ActorBase::ActorStateBase *
ActorBase::ActorStateBase::clone(void)
{
    FDEBUG(("ActorBase::ActorStateBase::clone()\n"));

    return new ActorStateBase();
}

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ActorBase
           Actors are the active component in the NewAction concept. They do
           the actual work on the traversed nodes either directly in their
           applyEnter/applyLeave methods, or by calling a registered functor
           for the current node's type.
 */

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*------------------------------ destructor -------------------------------*/

ActorBase::~ActorBase(void)
{
    FDEBUG(("ActorBase::~ActorBase(void)\n"));

    delete _pState;
}

/*-------------------------------- apply ----------------------------------*/

ActorBase::ResultE
ActorBase::applyEnter(NodeCorePtr OSG_CHECK_ARG(pNodeCore))
{
    FDEBUG(("ActorBase::applyEnter\n"));

    return NewActionBase::Continue;
}

ActorBase::ResultE
ActorBase::applyLeave(NodeCorePtr OSG_CHECK_ARG(pNodeCore))
{
    FDEBUG(("ActorBase::applyLeave\n"));

    return NewActionBase::Continue;
}

/*----------------------------- start/stop --------------------------------*/

ActorBase::ResultE
ActorBase::start(void)
{
    FDEBUG(("ActorBase::start\n"));

    return NewActionBase::Continue;
}

ActorBase::ResultE
ActorBase::stop(void)
{
    FDEBUG(("ActorBase::stop\n"));

    return NewActionBase::Continue;
}

/*------------------------- requirement queries ---------------------------*/
bool
ActorBase::hasEnterMethod(void) const
{
    return bHasEnterMethod;
}

bool
ActorBase::hasLeaveMethod(void) const
{
    return bHasLeaveMethod;
}

bool
ActorBase::hasOrderedState(void) const
{
    return bHasOrderedState;
}

bool
ActorBase::acceptsIterator(IteratorBase *) const
{
    return true;
}

void
ActorBase::receiveIteratorSet(IteratorBase *)
{
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*----------------------------- constructors  -----------------------------*/

ActorBase::ActorBase(void)
    : _pAction  (NULL),
      _uiActorId(0   ),
      _pState   (NULL)
{
    FDEBUG(("ActorBase::ActorBase(void)\n"));
}

/*--------------------------------- state ---------------------------------*/

void
ActorBase::createState(void)
{
    FDEBUG(("ActorBase::createState(void)\n"));

    setState(new Self::StateType());
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: $";
    static Char8 cvsid_hpp       [] = OSGACTORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGACTORBASE_INLINE_CVSID;
}
