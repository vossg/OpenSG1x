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

#include "OSGPrintNameActorBase.h"
#include <OSGNodeCore.h>
#include <OSGStateAwareIterator.h>
#include <OSGStateUnawareIterator.h>

OSG_USING_NAMESPACE

/*--------------------------- static member init ----------------------------*/

PrintNameActorBase::EnterStoreType *PrintNameActorBase::_pClassEnterStore = NULL;
PrintNameActorBase::LeaveStoreType *PrintNameActorBase::_pClassLeaveStore = NULL;

/*=============================== PUBLIC ====================================*/

/*------------------------------ destructor ---------------------------------*/

PrintNameActorBase::~PrintNameActorBase(void)
{
}

/*--------------------------- enter registration ---------------------------*/


/*--------------------------- leave registration ---------------------------*/



/*---------------------------------- apply enter ----------------------------*/


/*---------------------------------- apply leave ----------------------------*/


/*---------------------------- property queries  ---------------------------*/

bool
PrintNameActorBase::hasEnterMethod(void) const
{
    return bHasEnterMethod;
}

bool
PrintNameActorBase::hasLeaveMethod(void) const
{
    return bHasLeaveMethod;
}

bool
PrintNameActorBase::hasOrderedState(void) const
{
    return bHasOrderedState;
}

bool
PrintNameActorBase::acceptsIterator(IteratorBase *pIterator) const
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
        retVal = true;
    }

    return retVal;
}

/*============================== PROTECTED ==================================*/

/*--------------------------- BEGIN STATE CLASS -----------------------------*/

/*----------------------------- constructors --------------------------------*/

PrintNameActorBase::PrintNameActorStateBase::PrintNameActorStateBase(void) :
    Inherited::StateType()
{
}

PrintNameActorBase::PrintNameActorStateBase::PrintNameActorStateBase(
    const PrintNameActorStateBase &source) :
    Inherited::StateType(source)
{
}

/*------------------------------- destructor --------------------------------*/

PrintNameActorBase::PrintNameActorStateBase::~PrintNameActorStateBase(void)
{
}

/*--------------------------------- clone -----------------------------------*/

ActorBase::ActorStateBase *
PrintNameActorBase::PrintNameActorStateBase::clone(void)
{
    return new PrintNameActorStateBase(*this);
}

/*----------------------------- END STATE CLASS -----------------------------*/

/*------------------------------- constructors ------------------------------*/

PrintNameActorBase::PrintNameActorBase(void) :
    _asPrintOnEnter(true),
    _asPrintOnLeave(true),
    Inherited()
{
}

/*------------------------------- create state ------------------------------*/

void
PrintNameActorBase::createState(void)
{
    setState(new PrintNameActorStateBase());
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
    static Char8 cvsid_hpp   [] = OSGPRINTNAMEACTORBASE_HEADER_CVSID;
    static Char8 cvsid_inl   [] = OSGPRINTNAMEACTORBASE_INLINE_CVSID;
}
