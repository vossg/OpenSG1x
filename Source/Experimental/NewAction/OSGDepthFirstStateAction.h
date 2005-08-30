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

#ifndef _OSGDEPTHFIRSTSTATEACTION_H_
#define _OSGDEPTHFIRSTSTATEACTION_H_
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

#include <deque>
#include <list>

OSG_BEGIN_NAMESPACE

class ExtendActorBase;
class BasicActorBase;

class OSG_SYSTEMLIB_DLLMAPPING DepthFirstStateAction : public NewActionBase
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

    virtual ~DepthFirstStateAction(void);

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Create                                                      */
    /*! \{                                                                   */

    static DepthFirstStateAction *create(void);

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

    DepthFirstStateAction(void);

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Events                                                      */
    /*! \{                                                                   */

    virtual void addExtendEvent     (ExtendActorBase *pActor,
                                     UInt32           actorIndex);
    virtual void subExtendEvent     (ExtendActorBase *pActor,
                                     UInt32           actorIndex);

    virtual void addBasicEvent      (BasicActorBase  *pActor,
                                     UInt32           actorIndex);
    virtual void subBasicEvent      (BasicActorBase  *pActor,
                                     UInt32           actorIndex);

    virtual void startEvent         (void                       );
    virtual void stopEvent          (void                       );

    virtual void beginEditStateEvent(ActorBase       *pActor,
                                     UInt32           actorId   );
    virtual void endEditStateEvent  (ActorBase       *pActor,
                                     UInt32           actorId   );

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
    class NodeStackEntry;
    friend class StateRefCount;
    friend class NodeStackEntry;
    
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

    class NodeStackEntry
    {
      public:
        inline NodeStackEntry(      void                                  );
        inline NodeStackEntry(const NodeStackEntry       &source          );
        inline NodeStackEntry(const NodePtr              &pNode,
                              const StateRefCountStoreIt &itStateRefCount,
                                    Int32                 passCount       );

        inline NodePtr getNode     (void           ) const;

        inline Int32   getPassCount(void           ) const;
        inline void    setPassCount(Int32 passCount);

        inline StateRefCountStoreIt getStateRefCount(void          ) const;
        inline void setStateRefCount(const StateRefCountStoreIt &itStateRefCount);

      private:
        NodePtr              _pNode;
        StateRefCountStoreIt _itStateRefCount;
        Int32                _passCount;
    };

    typedef std::deque<NodeStackEntry> NodeStack;

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/
    /*! \name    Helper Methods                                              */
    /*! \{                                                                   */

           ResultE traverseEnter     (      void                          );
           ResultE traverseEnterLeave(      void                          );

           void    pushChildren      (const NodePtr &pNode, ResultE result);

    inline ResultE enterNode         (const NodePtr &pNode, UInt32  pass  );
    inline ResultE leaveNode         (const NodePtr &pNode, UInt32  pass  );

    inline StateRefCountStoreIt cloneState(void                                );
    inline StateRefCountStoreIt getState  (void                                );
    inline void                 setState  (StateRefCountStoreIt itStateRefCount);

    inline void incRefCount(StateRefCountStoreIt itStateRefCount, Int32 inc = 1);
    inline void decRefCount(StateRefCountStoreIt itStateRefCount, Int32 dec = 1);

    /*! \}                                                                   */
    /*-----------------------------------------------------------------------*/

    NodeStack            _nodeStack;
    StateRefCountStore   _stateRefCountStore;

#ifndef OSG_NEWACTION_STATESLOTINTERFACE
    StateStore           _stateStore;
#endif

    StateRefCountStoreIt _itInitialState;
    StateRefCountStoreIt _itActiveState;

    bool                 _stateClonedFlag;

    ExtendActorStore     _extendEnterActors;
    ExtendActorStore     _extendLeaveActors;

    BasicActorStore      _basicEnterActors;
    BasicActorStore      _basicLeaveActors;
};

OSG_END_NAMESPACE

#include "OSGDepthFirstStateAction.inl"

#define OSGDEPTHFIRSTSTATEACTION_HEADER_CVSID "@(#)$Id: OSGDepthFirstStateAction.h,v 1.3 2005/08/30 18:21:56 dirk Exp $"

#endif /* _OSGDEPTHFIRSTSTATEACTION_H_ */
