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

#include "OSGIntersectActorBase.h"
#include <OSGNodeCore.h>
#include <OSGStateAwareIterator.h>
#include <OSGStateUnawareIterator.h>

OSG_USING_NAMESPACE

/*--------------------------- static member init ----------------------------*/

IntersectActorBase::EnterStoreType *IntersectActorBase::_pClassEnterStore = NULL;
IntersectActorBase::LeaveStoreType *IntersectActorBase::_pClassLeaveStore = NULL;

/*=============================== PUBLIC ====================================*/

/*------------------------------ destructor ---------------------------------*/

IntersectActorBase::~IntersectActorBase(void)
{
}

/*--------------------------- enter registration ---------------------------*/


void
IntersectActorBase::regClassEnter(const Functor            &refFunc, 
                                 const FieldContainerType &refType )
{
    if(_pClassEnterStore == NULL)
        _pClassEnterStore = new EnterStoreType;

    _pClassEnterStore->regFunctor(refFunc, refType);
}

void
IntersectActorBase::regEnter(const Functor            &refFunc,
                            const FieldContainerType &refType )
{
    EnterStoreType::regFunctor(refFunc, refType);
}

void
IntersectActorBase::regDefaultClassEnter(const Functor &refFunc)
{
    if(_pClassEnterStore == NULL)
        _pClassEnterStore = new EnterStoreType;

    _pClassEnterStore->regDefaultFunctor(refFunc);
}

void
IntersectActorBase::regDefaultEnter(const Functor &refFunc)
{
    EnterStoreType::regDefaultFunctor(refFunc);
}

void
IntersectActorBase::unregClassEnter(const FieldContainerType &refType)
{
    if(_pClassEnterStore == NULL)
        _pClassEnterStore = new EnterStoreType;

    _pClassEnterStore->unregFunctor(refType);
}

void
IntersectActorBase::unregEnter(const FieldContainerType &refType)
{
    EnterStoreType::unregFunctor(refType);
}

void
IntersectActorBase::unregDefaultClassEnter(void)
{
    if(_pClassEnterStore == NULL)
        _pClassEnterStore = new EnterStoreType;

    _pClassEnterStore->unregDefaultFunctor();
}

void
IntersectActorBase::unregDefaultEnter(void)
{
    EnterStoreType::unregDefaultFunctor();
}

/*--------------------------- leave registration ---------------------------*/



/*---------------------------------- apply enter ----------------------------*/

IntersectActorBase::ResultE
IntersectActorBase::applyEnter(NodeCorePtr pNodeCore)
{
    Functor *pFunc = NULL;

    if((pFunc = EnterStoreType::getFunctor(pNodeCore->getType())) != NULL)
    {
        return pFunc->call(pNodeCore, this);
    }
       
    if((pFunc = _pClassEnterStore->getFunctor(pNodeCore->getType())) != NULL)
    {
        return pFunc->call(pNodeCore, this);
    }

    return Inherited::applyEnter(pNodeCore);
}

/*---------------------------------- apply leave ----------------------------*/


/*---------------------------- property queries  ---------------------------*/

bool
IntersectActorBase::hasEnterMethod(void) const
{
    return bHasEnterMethod;
}

bool
IntersectActorBase::hasLeaveMethod(void) const
{
    return bHasLeaveMethod;
}

bool
IntersectActorBase::hasOrderedState(void) const
{
    return bHasOrderedState;
}

bool
IntersectActorBase::acceptsIterator(IteratorBase *pIterator) const
{
    bool retVal = false;

    if(pIterator == NULL)
    {
        retVal = true;
    }
    else if(dynamic_cast<StateAwareIterator *>(pIterator) != NULL)
    {
        retVal = true;
    }
    else if(dynamic_cast<StateUnawareIterator *>(pIterator) != NULL)
    {
        retVal = false;
    }

    return retVal;
}

/*============================== PROTECTED ==================================*/

/*--------------------------- BEGIN STATE CLASS -----------------------------*/

/*----------------------------- constructors --------------------------------*/

IntersectActorBase::IntersectActorStateBase::IntersectActorStateBase(void) :
    _asLine(),
    _asScaleFactor(),
    Inherited::StateType()
{
}

IntersectActorBase::IntersectActorStateBase::IntersectActorStateBase(
    const IntersectActorStateBase &source) :
    _asLine(source._asLine),
    _asScaleFactor(source._asScaleFactor),
    Inherited::StateType(source)
{
}

/*------------------------------- destructor --------------------------------*/

IntersectActorBase::IntersectActorStateBase::~IntersectActorStateBase(void)
{
}

/*--------------------------------- clone -----------------------------------*/

ActorBase::ActorStateBase *
IntersectActorBase::IntersectActorStateBase::clone(void)
{
    return new IntersectActorStateBase(*this);
}

/*----------------------------- END STATE CLASS -----------------------------*/

/*------------------------------- constructors ------------------------------*/

IntersectActorBase::IntersectActorBase(void) :
    _asMaxDist(),
    _asHitDist(),
    _asHitObject(),
    _asHitTriangle(),
    _asHit(),
    Inherited()
{
}

/*------------------------------- create state ------------------------------*/

void
IntersectActorBase::createState(void)
{
    setState(new IntersectActorStateBase());
}


/*--------------------------------- cvs is's --------------------------------*/

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp   [] = "@(#)$Id:";
    static Char8 cvsid_hpp   [] = OSGINTERSECTACTORBASE_HEADER_CVSID;
    static Char8 cvsid_inl   [] = OSGINTERSECTACTORBASE_INLINE_CVSID;
}
