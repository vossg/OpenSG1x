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

#include "OSGExtendActorBase.h"

OSG_USING_NAMESPACE

//----------------------------------------------------------------------------
//    Destructor
//----------------------------------------------------------------------------

ExtendActorBase::~ExtendActorBase(void)
{
}

//----------------------------------------------------------------------------
//    Start/Stop
//----------------------------------------------------------------------------

ExtendActorBase::ResultE
ExtendActorBase::start(void)
{
    return Inherited::start();
}

ExtendActorBase::ResultE
ExtendActorBase::stop(void)
{
    return Inherited::stop();
}

//----------------------------------------------------------------------------
//    Enter/Leave
//----------------------------------------------------------------------------

ExtendActorBase::ResultE
ExtendActorBase::enterNode(FunctorArgumentType &funcArg)
{
    return NewActionTypes::Continue;
}

ExtendActorBase::ResultE
ExtendActorBase::leaveNode(FunctorArgumentType &funcArg)
{
    return NewActionTypes::Continue;
}

//----------------------------------------------------------------------------
//    Constructors
//----------------------------------------------------------------------------

/*! Default constructor
 */

ExtendActorBase::ExtendActorBase(void)
    : Inherited()
{
}

//----------------------------------------------------------------------------
//    Add, Sub and Find helper
//----------------------------------------------------------------------------

UInt32
ExtendActorBase::addHelper(NewActionBase *pAction)
{
    return pAction->addExtendActor(this);
}

void
ExtendActorBase::subHelper(NewActionBase *pAction)
{
    UInt32 actorIndex = pAction->findExtendActor(this);

    if(actorIndex == TypeTraits<UInt32>::getMax())
    {
        SWARNING << "ExtendActorBase::subHelper: Illegal actor index."
                 << endLog;

        return;
    }

    pAction->subExtendActor(actorIndex);
}

UInt32
ExtendActorBase::findHelper(const NewActionBase *pAction)
{
    return pAction->findExtendActor(this);
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGExtendActorBase.cpp,v 1.3 2004/09/17 14:09:43 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGEXTENDACTORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGEXTENDACTORBASE_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
