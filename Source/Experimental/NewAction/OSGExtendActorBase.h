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

#ifndef _OSGEXTENDACTORBASE_H_
#define _OSGEXTENDACTORBASE_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGSystemDef.h>

#include "OSGActorBase.h"

OSG_BEGIN_NAMESPACE

class OSG_SYSTEMLIB_DLLMAPPING ExtendActorBase : public ActorBase
{
  public:

    virtual ~ExtendActorBase(void);

    virtual ResultE start    (      void          ) = 0;
    virtual ResultE stop     (      void          ) = 0;

    virtual ResultE enterNode(const NodePtr &pNode) = 0;
    virtual ResultE leaveNode(const NodePtr &pNode) = 0;


    inline bool getChildrenListEnabled(void        ) const;
    inline void setChildrenListEnabled(bool enabled);

    inline NodePtr      getNode         (void                    ) const;

    inline UInt32       getNumChildren  (void                    ) const;
    inline NodePtr      getChild        (UInt32       childIndex ) const;

    inline bool         getChildActive  (UInt32       childIndex ) const;
    inline void         setChildActive  (UInt32       childIndex,
                                         bool         active     );

    inline PriorityType getChildPriority(UInt32       childIndex ) const;
    inline void         setChildPriority(UInt32       childIndex,
                                         PriorityType prio       );

    inline UInt32 addExtraChild(const NodePtr &pNode                   );
    inline UInt32 addExtraChild(const NodePtr &pNode, PriorityType prio);

    inline UInt32       getNumExtraChildren  (void                    ) const;
    inline NodePtr      getExtraChild        (UInt32       childIndex ) const;

    inline bool         getExtraChildActive  (UInt32       childIndex ) const;
    inline void         setExtraChildActive  (UInt32       childIndex,
                                              bool         active     );

    inline PriorityType getExtraChildPriority(UInt32       childIndex ) const;
    inline void         setExtraChildPriority(UInt32       childIndex,
                                              PriorityType prio       );

  protected:
    typedef ActorBase            Inherited;
    typedef Inherited::StateType StateType;

    ExtendActorBase(void);

    virtual UInt32 addHelper (      NewActionBase *pAction);
    virtual void   subHelper (      NewActionBase *pAction);
    virtual UInt32 findHelper(const NewActionBase *pAction);
};

OSG_END_NAMESPACE

#include "OSGExtendActorBase.inl"

#define OSGEXTENDACTORBASE_HEADER_CVSID "@(#)$Id: OSGExtendActorBase.h,v 1.1 2004/09/10 15:00:46 neumannc Exp $"

#endif /* _OSGEXTENDACTORBASE_H_ */
