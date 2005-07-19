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

//----------------------------------------------------------------------------
//    Includes
//----------------------------------------------------------------------------

#include <OSGConfig.h>
#include <OSGSystemDef.h>

#include "OSGNewActionBase.h"
#include "OSGActorBase.h"

#include <list>
#include <vector>
#include <queue>

OSG_BEGIN_NAMESPACE

class ExtendActorBase;
class BasicActorBase;

class OSG_SYSTEMLIB_DLLMAPPING PriorityAction : public NewActionBase
{
    /*==== PUBLIC ===========================================================*/
  public:
#ifdef OSG_NEWACTION_STATISTICS
    /*-----------------------------------------------------------------------*/
    /*! \name    Statistics                                                  */
    /*! \{                                                                   */

    static StatElemDesc<StatIntElem> statStateClones;
    static StatElemDesc<StatIntElem> statStateRestores;

    /*! \}                                                                   */
#endif /* OSG_NEWACTION_STATISTICS */
    /*-----------------------------------------------------------------------*/
    /*! \name    Destructor                                                  */
    /*! \{                                                                   */

    virtual ~PriorityAction(void);

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Create                                                      */
    /*! \{                                                                   */

    static PriorityAction *create(void);

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Apply                                                       */
    /*! \{                                                                   */

    virtual ResultE apply(NodePtr pRoot);

    /*! \}                                                                   */
    /*==== PROTECTED ========================================================*/
  protected:
    /*-----------------------------------------------------------------------*/
    /*! \name    Constructors                                                */
    /*! \{                                                                   */

    PriorityAction(void);

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Events                                                      */
    /*! \{                                                                   */

    virtual void addExtendEvent(ExtendActorBase *pActor, UInt32 actorIndex);
    virtual void subExtendEvent(ExtendActorBase *pActor, UInt32 actorIndex);

    virtual void addBasicEvent (BasicActorBase  *pActor, UInt32 actorIndex);
    virtual void subBasicEvent (BasicActorBase  *pActor, UInt32 actorIndex);

    virtual void startEvent    (void                                      );
    virtual void stopEvent     (void                                      );

    virtual void beginEditStateEvent(ActorBase *pActor, UInt32 actorId);
    virtual void endEditStateEvent  (ActorBase *pActor, UInt32 actorId);

    /*! \}                                                                   */
    /*==== PRIVATE ==========================================================*/
  private:
    /*-----------------------------------------------------------------------*/
    /*! \name    Types                                                       */
    /*! \{                                                                   */

    typedef NewActionBase             Inherited;
    typedef ActorBase::ActorBaseState ActorBaseState;

#ifdef OSG_NEWACTION_STATESLOTINTERFACE

    class StateRefCount
    {
      public:
        inline          StateRefCount(const StateRefCount &source    );

        inline explicit StateRefCount(      UInt32         stateSlot );
        inline explicit StateRefCount(      UInt32         stateSlot,
                                            Int32          refCount  );

        inline UInt32 getStateSlot(void            ) const;
        inline void   setStateSlot(UInt32 stateSlot);

        inline Int32  getRefCount (void            ) const;
        inline void   incRefCount (Int32  inc      );
        inline void   decRefCount (Int32  dec      );

      private:
        UInt32 _stateSlot;
        Int32  _refCount;
    };

#else /* OSG_NEWACTION_STATESLOTINTERFACE */

    typedef std::list<ActorBaseState *> StateStore;
    typedef StateStore::iterator        StateStoreIt;
    typedef StateStore::const_iterator  StateStoreConstIt;

    class StateRefCount;
    class NodeQueueEntry;
    friend class StateRefCount;
    friend class NodeQueueEntry;

    class StateRefCount
    {
      public:
        inline          StateRefCount(const StateRefCount &source  );

        inline explicit StateRefCount(const StateStoreIt  &itState );
        inline explicit StateRefCount(const StateStoreIt  &itState,
                                            Int32          refCount);

        inline StateStoreIt getState(      void                 ) const;
        inline void         setState(const StateStoreIt &itState);

        inline Int32        getRefCount(void         ) const;
        inline void         incRefCount(Int32 inc = 1);
        inline void         decRefCount(Int32 dec = 1);

      private:
        StateStoreIt _itState;
        Int32        _refCount;
    };

#endif /* OSG_NEWACTION_STATESLOTINTERFACE */

    typedef std::list<StateRefCount>           StateRefCountStore;
    typedef StateRefCountStore::iterator       StateRefCountStoreIt;
    typedef StateRefCountStore::const_iterator StateRefCountStoreConstIt;

    class NodeQueueEntry
    {
      public:
        inline NodeQueueEntry(const NodeQueueEntry       &source         );

        inline NodeQueueEntry(const NodePtr              &pNode,
                                    PriorityType          priority,
                                    UInt32                passCount,
                              const StateRefCountStoreIt &itStateRefCount);

        inline NodePtr              getNode         (void) const;
        inline PriorityType         getPriority     (void) const;
        inline UInt32               getPassCount    (void) const;
        inline StateRefCountStoreIt getStateRefCount(void) const;

        struct LessCompare
        {
            inline bool operator()(const NodeQueueEntry &leftArg,
                                   const NodeQueueEntry &rightArg);
        };

      private:
        NodePtr              _pNode;
        PriorityType         _priority;
        UInt32               _passCount;
        StateRefCountStoreIt _itStateRefCount;
    };

    // std::priority_queue<...> does not have clear(), for some reason...
    // so we use a vector and the pqFOO helper methods below  -cneumann
    typedef std::vector<NodeQueueEntry> NodePriorityQueue;
    typedef NodeQueueEntry::LessCompare NodePriorityQueueComp;

           ResultE traverseEnter  (      void                          );
           void    enqueueChildren(const NodePtr &pNode, ResultE result);

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Helper Methods                                              */
    /*! \{                                                                   */

    inline ResultE enterNode(const NodePtr &pNode, UInt32 pass);

    inline StateRefCountStoreIt cloneState(void                                );
    inline StateRefCountStoreIt getState  (void                                );
    inline void                 setState  (StateRefCountStoreIt itStateRefCount);

    inline void incRefCount(StateRefCountStoreIt itStateRefCount, Int32 inc = 1);
    inline void decRefCount(StateRefCountStoreIt itStateRefCount, Int32 dec = 1);

    inline const NodeQueueEntry &pqTop  (      void                 ) const;

    inline       void            pqPush (const NodeQueueEntry &entry);
    inline       void            pqPop  (      void                 );

    inline       bool            pqEmpty(      void                 ) const;
    inline       void            pqClear(      void                 );

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/

    ExtendActorStore      _extendEnterActors;
    BasicActorStore       _basicEnterActors;

    NodePriorityQueue     _nodePrioQueue;
    NodePriorityQueueComp _nodePrioQueueComp;

    bool                  _stateClonedFlag;

#ifndef OSG_NEWACTION_STATESLOTINTERFACE
    StateStore           _stateStore;
#endif

    StateRefCountStore   _stateRefCountStore;
    StateRefCountStoreIt _itInitialState;
    StateRefCountStoreIt _itActiveState;
};

OSG_END_NAMESPACE

#include "OSGPriorityAction.inl"

#define OSGPRIORITYACTION_HEADER_CVSID "@(#)$Id: OSGPriorityAction.h,v 1.7 2005/07/19 23:11:33 dirk Exp $"

#endif /* _OSGPRIORITYACTION_H_ */
