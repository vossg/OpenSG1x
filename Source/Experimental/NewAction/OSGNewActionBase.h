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

#ifndef _OSGNEWACTIONBASE_H_
#define _OSGNEWACTIONBASE_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBaseTypes.h>
#include <OSGNodePtr.h>
#include <OSGTypedFunctors.h>

#include <vector>

OSG_BEGIN_NAMESPACE

class ActorBase;

class OSG_SYSTEMLIB_DLLMAPPING NewActionBase
{
public:
    enum ResultE
    {
        Continue = 0x00,
        Stop     = 0x01,
        Abort    = 0x02
    };

    typedef ArgsCollector    <ActorBase *               > FunctorArgs;

    typedef TypedFunctor2Base<ResultE,
                              CPtrRefCallArg<NodeCorePtr>,
                              FunctorArgs               > Functor;

    typedef Real32                                        PriorityType;

    typedef std::vector<NodePtr>       RootList;
    typedef RootList::iterator         RootListIt;
    typedef RootList::const_iterator   RootListConstIt;

    typedef std::vector<ActorBase *>   ActorStore;
    typedef ActorStore::iterator       ActorStoreIt;
    typedef ActorStore::const_iterator ActorStoreConstIt;
};

OSG_END_NAMESPACE

#define OSGNEWACTIONBASE_HEADER_CVSID "@(#)$Id: OSGNewActionBase.h,v 1.2 2003/10/10 14:27:44 neumannc Exp $"

#endif /* _OSGNEWACTIONBASE_H_ */
