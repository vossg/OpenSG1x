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

#ifndef _OSGPRIORITYITERATOR_H_
#define _OSGPRIORITYITERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGStateAwareIterator.h"
#include "OSGActiveNodeList.h"
#include "OSGActorStateChunk.h"

#include <queue>

OSG_BEGIN_NAMESPACE

#ifdef __sgi
#pragma set woff 1375
#endif

class OSG_SYSTEMLIB_DLLMAPPING PriorityIterator : public StateAwareIterator
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name                     Types                                    */
    /*! \{                                                                 */
    typedef NewActionBase::PriorityType PriorityType;
    typedef NewActionBase::ResultE      ResultE;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Create                                   */
    /*! \{                                                                 */

    static    PriorityIterator *create          (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Destructor                                */
    /*! \{                                                                 */

    virtual                    ~PriorityIterator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Traverse                                 */
    /*! \{                                                                 */

    virtual ResultE start           (void);
    virtual void    stop            (void);
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Receive Signals                           */
    /*! \{                                                                 */

    virtual void receiveActorAdd   (ActorBase *pActor,   UInt32 uiActorId);
    virtual void receiveActorSub   (ActorBase *pActor,   UInt32 uiActorId);
    virtual void receiveActorsClear(void                                 );

    virtual void receiveStateRead  (UInt32     uiActorId                 );
    virtual void receiveStateWrite (UInt32     uiActorId                 );

    /*! \}                                                                 */
    /*========================== PROTECTED ================================*/
protected:
    /*---------------------------------------------------------------------*/
    /*! \name                     Result                                   */
    /*! \{                                                                 */

    inline ResultE getResult(void       ) const;
    inline void    setResult(ResultE res);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
    typedef StateAwareIterator Inherited;

    class PIBase;
    friend class PIBase;

    class PILeave;
    friend class PILeave;

    class PIEnter;
    friend class PIEnter;

    class PIEnterOrd;
    friend class PIEnterOrd;

    class PILeaveOrd;
    friend class PILeaveOrd;

    /*====================================================================*\
     * PIBase                                                             *
    \*====================================================================*/

    class PIBase
    {
    public:
        typedef PriorityIterator::PriorityType PriorityType;

        inline   PIBase(PriorityIterator *pPQIter);
        virtual ~PIBase(void                     ) = 0;

        virtual void    preTraversal    (void             ) = 0;
        virtual void    postTraversal   (void             ) = 0;

        virtual ResultE traverse        (NodePtr pRoot    ) = 0;

        virtual void    receiveStateRead (UInt32  uiActorId) = 0;
        virtual void    receiveStateWrite(UInt32  uiActorId) = 0;

    protected:

        struct PQEntryLessCompare;
        friend struct PQEntryLessCompare;

        friend class PILeave;

        /*====================== LeaveEntryBase ==========================*/

        class LeaveEntryBase
        {
        public:
            inline  LeaveEntryBase(void            );
            inline  LeaveEntryBase(UInt32 uiPending);
            inline ~LeaveEntryBase(void            );

            inline UInt32 getPending(void) const;
            inline UInt32 decPending(void);

        private:
            UInt32      _uiPending;
        };

        /*======================= PQEntryBase ============================*/

        class PQEntryBase
        {
        public:
            typedef PIBase::PriorityType PriorityType;

            inline  PQEntryBase(void                            );
            inline  PQEntryBase(NodePtr pNode, PriorityType prio);
            inline ~PQEntryBase(void                            );

            inline NodePtr      getNode(void) const;
            inline PriorityType getPrio(void) const;

        private:
            NodePtr      _pNode;
            PriorityType _priority;
        };

        /*====================== PQEntryLessCompare ======================*/

        struct PQEntryLessCompare;
        friend struct PQEntryLessCompare;

        struct PQEntryLessCompare
        {
            inline bool operator()(const PQEntryBase &refLHS,
                                   const PQEntryBase &refRHS );
        };

        inline PriorityIterator *getIter(void);

    private:
        PriorityIterator *_pPQIter;
    };

    /*====================================================================*\
     * PIEnter                                                            *
    \*====================================================================*/
    
    class PIEnter : public PIBase
    {
    public:
        inline   PIEnter(PriorityIterator *pPQIter);
        virtual ~PIEnter(void                     );

        virtual void    preTraversal    (void             );
        virtual void    postTraversal   (void             );

        virtual ResultE traverse        (NodePtr pRoot    );

        virtual void    receiveStateRead (UInt32  uiActorId);
        virtual void    receiveStateWrite(UInt32  uiActorId);

    protected:
        typedef PIBase::PQEntryBase                        PQEntry;
        typedef PIBase::PQEntryLessCompare                 PQEntryLessCompare;
        typedef std::priority_queue<PQEntry, 
                                    std::vector<PQEntry>,
                                    PQEntryLessCompare   > PrioQueueType;

    private:
        typedef PIBase Inherited;

        void pushChildren(void);

        PrioQueueType _pqueue;
    };

    /*====================================================================*\
     * PILeave                                                            *
    \*====================================================================*/

    class PILeave : public PIBase
    {
    public:
        inline   PILeave(PriorityIterator *pPQIter);
        virtual ~PILeave(void                     );

        virtual void    preTraversal    (void             );
        virtual void    postTraversal   (void             );

        virtual ResultE traverse        (NodePtr pRoot    );

        virtual void    receiveStateRead (UInt32  uiActorId);
        virtual void    receiveStateWrite(UInt32  uiActorId);

    protected:
        class LeaveEntry;
        friend class LeaveEntry;

        class PQEntry;
        friend class PQEntry;

        friend class PriorityIterator;

        typedef std::list<LeaveEntry> LeaveList;
        typedef LeaveList::iterator   LeaveListIt;

        /*==================== LeaveEntry ================================*/

        class LeaveEntry : public PIBase::LeaveEntryBase
        {
        public:
            typedef PILeave::PriorityType PriorityType;

            inline  LeaveEntry(void                                  );
            inline  LeaveEntry(UInt32 uiPending, LeaveListIt itParent);
            inline ~LeaveEntry(void                                  );

            inline LeaveListIt getParent (void) const;

        private:
            typedef PIBase::LeaveEntryBase Inherited;

            LeaveListIt _itParent;
        };

        /*====================== PQEntry =================================*/

        class PQEntry : public PIBase::PQEntryBase
        {
        public:
            typedef PILeave::PriorityType PriorityType;

            inline  PQEntry(void                                             );
            inline  PQEntry(NodePtr     pNode,             PriorityType prio,
                            LeaveListIt itParentLeaveEntry                   );

            inline ~PQEntry(void                                             );

            inline LeaveListIt getParentLeaveEntry(void) const;

        private:
            typedef PIBase::PQEntryBase Inherited;

            LeaveListIt _itParentLeaveEntry;
        };

        typedef PIBase::PQEntryLessCompare                 PQEntryLessCompare;
        typedef std::priority_queue<PQEntry,
                                    std::vector<PQEntry>,
                                    PQEntryLessCompare   > PrioQueueType;

    private:
        typedef PIBase Inherited;

        void pushChildren(void);
        
        PrioQueueType _pqueue;
        LeaveList     _leaveList;
    };

    friend class PILeave::LeaveEntry;
    friend class PILeave::PQEntry;

    /*====================================================================*\
     * PIEnterOrd                                                         *
    \*====================================================================*/

    class PIEnterOrd : public PIEnter
    {
    public:
        inline   PIEnterOrd(PriorityIterator *pPQIter);
        virtual ~PIEnterOrd(void                     );

        virtual void    preTraversal    (void             );
        virtual void    postTraversal   (void             );

        virtual ResultE traverse        (NodePtr pRoot    );

        virtual void    receiveStateRead (UInt32  uiActorId);
        virtual void    receiveStateWrite(UInt32  uiActorId);

    protected:
        class PQEntry;
        friend class PQEntry;

        friend class PriorityIterator;

        typedef std::list<ActorStateChunk> StateList;
        typedef StateList::iterator        StateListIt;
        
        /*====================== PQEntry =================================*/

        class PQEntry : public PIEnter::PQEntry
        {
          public:
            typedef PIEnterOrd::PriorityType PriorityType;

            inline  PQEntry(void                                        );
            inline  PQEntry(NodePtr     pNode,        PriorityType prio, 
                            StateListIt itParentState                   );
            inline ~PQEntry(void                                        );

            inline StateListIt getParentState(void) const;

          private:
            typedef PIEnter::PQEntry Inherited;

            StateListIt _itParentState;
        };

        typedef PIEnter::PQEntryLessCompare                PQEntryLessCompare;
        typedef std::priority_queue<PQEntry,
                                    std::vector<PQEntry>,
                                    PQEntryLessCompare   > PrioQueueType;

    private:
        typedef PIEnter Inherited;

        void pushChildren (void);
        void freeStateList(void);
        
        bool          _bStateValid;
        bool          _bStateSaved;

        PrioQueueType _pqueue;
        StateList     _stateList;

        StateListIt   _currState;
    };

    friend class PIEnterOrd::PQEntry;

    /*====================================================================*\
     * PILeaveOrd                                                         *
    \*====================================================================*/

    class PILeaveOrd : public PILeave
    {
    public:
        inline   PILeaveOrd(PriorityIterator *pPQIter);
        virtual ~PILeaveOrd(void                     );
        
        virtual void    preTraversal    (void             );
        virtual void    postTraversal   (void             );

        virtual ResultE traverse        (NodePtr pRoot    );

        virtual void    receiveStateRead (UInt32  uiActorId);
        virtual void    receiveStateWrite(UInt32  uiActorId);

    protected:        
        class LeaveEntry;
        friend class LeaveEntry;

        class PQEntry;
        friend class PQEntry;

        friend class PriorityIterator;

        typedef std::list<LeaveEntry>      LeaveList;
        typedef LeaveList::iterator        LeaveListIt;

        typedef std::list<ActorStateChunk> StateList;
        typedef StateList::iterator        StateListIt;

        /*======================= LeaveEntry =============================*/

        class LeaveEntry : public PIBase::LeaveEntryBase
        {
        public:
            typedef PILeaveOrd::PriorityType PriorityType;
            
            inline  LeaveEntry(void                                        );
            inline  LeaveEntry(UInt32      uiPending, LeaveListIt itParent,
                               StateListIt itState                         );
            inline ~LeaveEntry(void                                        );

            inline LeaveListIt getParent(void) const;
            inline StateListIt getState (void) const;

        private:
            typedef PIBase::LeaveEntryBase Inherited;

            LeaveListIt _itParent;
            StateListIt _itState;
        };

        /*========================= PQEntry ==============================*/

        class PQEntry : public PIBase::PQEntryBase
        {
        public:
            typedef PILeaveOrd::PriorityType PriorityType;

            inline  PQEntry(void                            );
            inline  PQEntry(NodePtr      pNode,              
                            PriorityType prio,
                            LeaveListIt  itParentLeaveEntry,
                            StateListIt  itState            );

            inline ~PQEntry(void                            );
            
            inline LeaveListIt getParentLeaveEntry(void) const;
            inline StateListIt getParentState     (void) const;

        private:
            typedef PIBase::PQEntryBase Inherited;

            LeaveListIt _itParentLeaveEntry;
            StateListIt _itState;
        };

        typedef PILeave::PQEntryLessCompare                PQEntryLessCompare;
        typedef std::priority_queue<PQEntry,
                                    std::vector<PQEntry>,
                                    PQEntryLessCompare   > PrioQueueType;

    private:
        typedef PILeave Inherited;

        void pushChildren (void);
        void freeStateList(void);
        
        bool          _bStateValid;
        bool          _bStateSaved;

        PrioQueueType _pqueue;
        LeaveList     _leaveList;
        StateList     _stateList;

        StateListIt   _currState;
    };

    friend class PILeaveOrd::LeaveEntry;
    friend class PILeaveOrd::PQEntry;

    PriorityIterator(void);

    ResultE     _result;

    PIBase     *_pIter;
    PIEnter    *_pEnterIter;
    PIEnterOrd *_pEnterOrdIter;
    PILeave    *_pLeaveIter;
    PILeaveOrd *_pLeaveOrdIter;
};

#ifdef __sgi
#pragma reset woff 1375
#endif

OSG_END_NAMESPACE

#include "OSGPriorityIterator.inl"

#define OSGPRIORITYITERATOR_HEADER_CVSID "@(#)$Id: OSGPriorityIterator.h,v 1.4 2003/10/15 09:31:29 vossg Exp $"

#endif /* _OSGPRIORITYITERATOR_H_ */
