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

#ifndef _OSGINTERSECTACTOR_H_
#define _OSGINTERSECTACTOR_H_
#ifdef __sgi
#pragma once
#endif

OSG_BEGIN_NAMESPACE

class OSG_SYSTEMLIB_DLLMAPPING IntersectActor : public IntersectActorBase
{
public:
    static   IntersectActor *create(void);

    virtual ~IntersectActor        (void);

    virtual ResultE start(void);

    static  ResultE defaultFunctor(NodeCorePtr &refCore, ActorBase *pActor);
    
    void priorizeChildren(ActiveNodeListIt  itNodes,
                          ActiveNodeListIt  endNodes);
    
protected:
    IntersectActor(void);

private:
    typedef IntersectActorBase Inherited;
};

OSG_END_NAMESPACE

#include "OSGIntersectActor.inl"

#define OSGINTERSECTACTOR_HEADER_CVSID "@(#)$Id: OSGIntersectActor.h,v 1.1 2003/10/10 13:51:07 neumannc Exp $"

#endif /* _OSGINTERSECTACTOR_H_ */
