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

#ifndef _OSGNEWACTIONTYPES_H_
#define _OSGNEWACTIONTYPES_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGSystemDef.h>
#include "OSGFunctorArgumentType.h"

OSG_BEGIN_NAMESPACE

//#define OSG_NEWACTION_STATESLOTINTERFACE
#define OSG_NEWACTION_STATISTICS

class ActorBase;

namespace NewActionTypes
{
    enum ResultE
    {
        Continue = 0x00,  // ok
        Skip     = 0x01,  // skip all child nodes
        Break    = 0x02,  // skip all child nodes and remaining actors
        Quit     = 0x04   // end traversal
    };

    typedef Real32                                        PriorityType;
    typedef TypeTraits<PriorityType>                      PriorityTypeTraits;

    //typedef ArgsCollector2   <ActorBase *, NodePtr>     FunctorArguments;
    typedef ArgsCollector    <FunctorArgumentType &  >    FunctorArguments;
    typedef TypedFunctor2Base<ResultE,
                              CPtrCallArg<NodeCorePtr>,
                              FunctorArguments          > Functor;
}

OSG_END_NAMESPACE

#define OSGNEWACTIONTYPES_HEADER_CVSID "@(#)$Id: OSGNewActionTypes.h,v 1.3 2004/09/17 14:09:43 neumannc Exp $"

#endif /* _OSGNEWACTIONTYPES_H_ */
