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

#include "OSGBasicActorBase.h"

OSG_USING_NAMESPACE

//----------------------------------------------------------------------------
//    Destructor
//----------------------------------------------------------------------------

BasicActorBase::~BasicActorBase(void)
{
}

//----------------------------------------------------------------------------
//    Start/Stop
//----------------------------------------------------------------------------

BasicActorBase::ResultE
BasicActorBase::start(void)
{
    return Inherited::start();
}

BasicActorBase::ResultE
BasicActorBase::stop(void)
{
    return Inherited::stop();
}

//----------------------------------------------------------------------------
//    Enter/Leave
//----------------------------------------------------------------------------

BasicActorBase::ResultE
BasicActorBase::enterNode(FunctorArgumentType &funcArg)
{
    return NewActionTypes::Continue;
}

BasicActorBase::ResultE
BasicActorBase::leaveNode(FunctorArgumentType &funcArg)
{
    return NewActionTypes::Continue;
}

//----------------------------------------------------------------------------
//    Constructors
//----------------------------------------------------------------------------

/*! Default constructor
 */

BasicActorBase::BasicActorBase(void)
    : Inherited()
{
}

//----------------------------------------------------------------------------
//    Add, Sub and Find helper
//----------------------------------------------------------------------------

UInt32
BasicActorBase::addHelper(NewActionBase *pAction)
{
    return pAction->addBasicActor(this);
}

void
BasicActorBase::subHelper(NewActionBase *pAction)
{
    UInt32 actorIndex = pAction->findBasicActor(this);

    if(actorIndex == TypeTraits<UInt32>::getMax())
    {
        SWARNING << "BasicActorBase::subHelper: Illegal actor index."
                 << endLog;

        return;
    }

    pAction->subBasicActor(actorIndex);
}

UInt32
BasicActorBase::findHelper(const NewActionBase *pAction)
{
    return pAction->findBasicActor(this);
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGBasicActorBase.cpp,v 1.2 2004/09/17 14:09:42 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGBASICACTORBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGBASICACTORBASE_INLINE_CVSID;
}

#ifdef OSG_LINUX_ICC
#pragma warning(enable : 177)
#endif

#ifdef OSG_SGI_CC
#pragma reset woff 1174
#endif
