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

#ifndef _OSGPRIORITYACTION_H_
#define _OSGPRIORITYACTION_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGSystemDef.h>
#include "OSGNewAction.h"

#include <list>
#include <vector>
#include <queue>

OSG_BEGIN_NAMESPACE

class OSG_SYSTEMLIB_DLLMAPPING PriorityAction : public NewAction
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name    Create                                                    */
    /*! \{                                                                 */

    static  PriorityAction *create(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Destructor                                                */
    /*! \{                                                                 */

    virtual ~PriorityAction  (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Apply                                                     */
    /*! \{                                                                 */

    virtual ResultE apply(const NodePtr         &pRootNode,
                                PriorityType     priority  );
    virtual ResultE apply(      NodeListConstIt  begin,
                                NodeListConstIt  end       );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name    Constructors                                              */
    /*! \{                                                                 */

    PriorityAction(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Events (Incoming)                                         */
    /*! \{                                                                 */

    virtual void attachEvent        (ActorBase *pActor, UInt32 uiActorId);
    virtual void detachEvent        (ActorBase *pActor, UInt32 uiActorId);

    virtual void beginEditStateEvent(ActorBase *pActor, UInt32 uiActorId);
    virtual void endEditStateEvent  (ActorBase *pActor, UInt32 uiActorId);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    /*---------------------------------------------------------------------*/
    /*! \name    Types                                                     */
    /*! \{                                                                 */

    class StateUseCounter;

    friend class StateUseCounter;

    typedef NewAction                    Inherited;
    typedef ActorBase::ActorBaseState    ActorBaseState;

    class StateUseCounter
    {
      public:
        typedef std::list<ActorBaseState *>::iterator StateStoreIt;

        inline StateUseCounter(      StateStoreIt     itState,
                                     Int32            iUseCount);
        inline StateUseCounter(const StateUseCounter &source   );

        inline StateStoreIt getState   (void                 ) const;
        inline void         setState   (StateStoreIt itState );

        inline Int32        getUseCount(void                 ) const;
        inline void         addUse     (Int32        iUse = 1);
        inline void         subUse     (Int32        iUse = 1);

      private:
        StateStoreIt _itState;
        Int32        _iUseCount;
    };

    class NodeQueueEntry;
    friend class NodeQueueEntry;

    typedef std::list<ActorBaseState *>   StateStore;
    typedef StateStore::iterator          StateStoreIt;
    typedef StateStore::const_iterator    StateStoreConstIt;

    typedef std::list<StateUseCounter>    StateUseStore;
    typedef StateUseStore::iterator       StateUseStoreIt;
    typedef StateUseStore::const_iterator StateUseStoreConstIt;

    class NodeQueueEntry
    {
      public:
        inline NodeQueueEntry(const NodePtr         &pNode,
                                    PriorityType     priority,
                                    StateUseStoreIt  itState  );

        inline NodeQueueEntry(const NodePtr         &pNode,
                                    PriorityType     priority );

        inline NodePtr         getNode    (void                     ) const;
        inline void            setNode    (const NodePtr   &pNode   );

        inline PriorityType    getPriority(void                     ) const;
        inline void            setPriority(PriorityType     priority);

        inline StateUseStoreIt getState   (void                     ) const;
        inline void            setState   (StateUseStoreIt  itState );

        struct LessCompare
        {
            inline bool operator()(const NodeQueueEntry &lhs,
                                   const NodeQueueEntry &rhs );
        };

      private:
        NodePtr         _pNode;
        PriorityType    _priority;
        StateUseStoreIt _itState;
    };

    typedef std::priority_queue<NodeQueueEntry,
                                std::vector<NodeQueueEntry>,
                                NodeQueueEntry::LessCompare > PriorityNodeQueue;

    /*!\brief prohibit default function (move to 'public' of needed) */
    PriorityAction (const PriorityAction &source);
    /*!\brief prohibit default function (move to 'public' of needed) */
    void operator =(const PriorityAction &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name    Helper Methods                                            */
    /*! \{                                                                 */

           ResultE applyEnter          (void                            );
    inline ResultE callEnter           (const NodePtr         &pNode    );

    inline void         deleteState    (      StateStore      *pStore,
                                              StateUseStoreIt  itState  );
    inline void         addStateUse    (      StateUseStoreIt  itState,
                                              Int32            iUse = 1 );
    inline void         subStateUse    (      StateUseStoreIt  itState,
                                              Int32            iUse = 1 );

    inline StateStoreIt cloneState     (      StateStore      *pStore,
                                              StateStoreIt     itPos    );
    inline StateStoreIt getState       (      StateStore      *pStore,
                                              StateStoreIt     itPos    );
    inline void         setState       (      StateStoreIt     itPos    );

    inline void         enqueueChildren(const NodePtr         &pNode,
                                              ResultE          result   );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/

    PriorityNodeQueue  _nodePrioQueue;

    bool               _bStateCloned;

    StateUseStore      _stateUseStore;
    StateStore         _stateStore;

    StateUseStoreIt    _itCurrentState;
    StateStoreIt       _itInitialState;
};

OSG_END_NAMESPACE

#include "OSGPriorityAction.inl"

#define OSGPRIORITYACTION_HEADER_CVSID "@(#)$Id: OSGPriorityAction.h,v 1.4 2004/05/08 08:25:40 vossg Exp $"

#endif /* _OSGPRIORITYACTION_H_ */
