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
#include <OSGBaseTypes.h>
#include <OSGTypedFunctors.h>
#include <OSGNodePtr.h>

OSG_BEGIN_NAMESPACE

class ActorBase;

namespace NewActionTypes
{
    typedef Real32 PriorityType;

    enum ResultE
    {
        Continue = 0x00,
        Skip     = 0x01,
        Quit     = 0x02
    };

    //typedef ArgsCollector2   <ActorBase *, NodePtr>         FunctorArguments;
    typedef ArgsCollector    <ActorBase *>                    FunctorArguments;
    typedef TypedFunctor2Base<ResultE,
                              CPtrCallArg<NodeCorePtr>,
                              FunctorArguments            > Functor;

    class OSG_SYSTEMLIB_DLLMAPPING NodePriorityPair
    {
      public:
        inline NodePriorityPair(const NodePtr &pNode                       );
        inline NodePriorityPair(const NodePtr &pNode, PriorityType priority);

        inline NodePtr      getNode    (void                 ) const;
        inline void         setNode    (const NodePtr &pNode );

        inline PriorityType getPriority(void                 ) const;
        inline void         setPriority(PriorityType priority);

        struct LessCompare
        {
            inline bool operator()(const NodePriorityPair &lhs,
                                   const NodePriorityPair &rhs );
        };

      private:
        NodePtr      _pNode;
        PriorityType _priority;
    };

    typedef std::vector<NodePriorityPair> NodeList;
    typedef NodeList::iterator            NodeListIt;
    typedef NodeList::const_iterator      NodeListConstIt;
}

OSG_END_NAMESPACE

#include "OSGNewActionTypes.inl"

#define OSGNEWACTIONTYPES_HEADER_CVSID "@(#)$Id: OSGNewActionTypes.h,v 1.1 2004/04/20 13:47:08 neumannc Exp $"

#endif /* _OSGNEWACTIONTYPES_H_ */
