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

    class PIBase
    {
    public:
        inline   PIBase(PriorityIterator &refPI);
        virtual ~PIBase(void                   ) = 0;

        virtual void    preTraversal    (void             ) = 0;
        virtual void    postTraversal   (void             ) = 0;

        virtual ResultE traverse        (NodePtr pRoot    ) = 0;

        virtual void    receiveStateRead (UInt32  uiActorId) = 0;
        virtual void    receiveStateWrite(UInt32  uiActorId) = 0;

    protected:
        class LeaveEntryBase
        {
        public:
            inline  LeaveEntryBase(UInt32 uiPending);
            inline ~LeaveEntryBase(void            );

            inline UInt32 getPending(void) const;
            inline UInt32 decPending(void);

        private:
            UInt32      _uiPending;
        };

        class PQEntryBase
        {
        public:
            inline  PQEntryBase(NodePtr pNode, PriorityType prio);
            inline ~PQEntryBase(void                            );

            inline NodePtr      getNode(void) const;
            inline PriorityType getPrio(void) const;

        private:
            NodePtr      _pNode;
            PriorityType _priority;
        };

        struct PQEntryLessCompare
        {
            inline bool operator()(const PQEntryBase &refLHS,
                                   const PQEntryBase &refRHS );
        };

        inline PriorityIterator &getIter(void);

//         inline ResultE                getResult     (void       ) const;
//         inline void                   setResult     (ResultE res);

//         inline void                   resetNodeList (void       );
//         inline void                   setUseNodeList(void       );
//         inline bool                   getUseNodeList(void       ) const;

//         inline ActiveNodeListIt       beginNodes    (void       );
//         inline ActiveNodeListIt       endNodes      (void       );
        
//         inline ActiveNodeListConstIt  beginNodes    (void       ) const;
//         inline ActiveNodeListConstIt  endNodes      (void       ) const;
        
//         inline       ActiveNodeList  &getNodeList   (void       );
//         inline const ActiveNodeList  &getNodeList   (void       ) const;


//         inline void    setCurrentNode    (NodePtr pCurrNode);
//         inline NodePtr getCurrentNode    (void             );
        

//         inline ResultE callEnter         (NodePtr pNode    );
//         inline ResultE callLeave         (NodePtr pNode    );

//         inline ResultE startActors       (void             );
//         inline ResultE stopActors        (void             );

    private:
        PriorityIterator &_refPI;
    };

    class PIEnter : public PIBase
    {
    public:
        inline   PIEnter(PriorityIterator &refPI);
        virtual ~PIEnter(void                   );

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

    class PILeave : public PIBase
    {
    public:
        inline   PILeave(PriorityIterator &refPI);
        virtual ~PILeave(void                   );

        virtual void    preTraversal    (void             );
        virtual void    postTraversal   (void             );

        virtual ResultE traverse        (NodePtr pRoot    );

        virtual void    receiveStateRead (UInt32  uiActorId);
        virtual void    receiveStateWrite(UInt32  uiActorId);

    protected:
        class LeaveEntry;
        
        typedef std::list<LeaveEntry> LeaveList;
        typedef LeaveList::iterator   LeaveListIt;

        class LeaveEntry : public PIBase::LeaveEntryBase
        {
        public:
            inline  LeaveEntry(UInt32 uiPending, LeaveListIt itParent);
            inline ~LeaveEntry(void                                  );

            inline LeaveListIt getParent (void) const;

        private:
            typedef PIBase::LeaveEntryBase Inherited;

            LeaveListIt _itParent;
        };

        class PQEntry : public PIBase::PQEntryBase
        {
        public:
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

    class PIEnterOrd : public PIEnter
    {
    public:
        inline   PIEnterOrd(PriorityIterator &refPI);
        virtual ~PIEnterOrd(void                   );

        virtual void    preTraversal    (void             );
        virtual void    postTraversal   (void             );

        virtual ResultE traverse        (NodePtr pRoot    );

        virtual void    receiveStateRead (UInt32  uiActorId);
        virtual void    receiveStateWrite(UInt32  uiActorId);

    protected:
        typedef std::list<ActorStateChunk> StateList;
        typedef StateList::iterator        StateListIt;

        class PQEntry : public PIEnter::PQEntry
        {
          public:
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

    class PILeaveOrd : public PILeave
    {
    public:
        inline   PILeaveOrd(PriorityIterator &refPI);
        virtual ~PILeaveOrd(void                   );
        
        virtual void    preTraversal    (void             );
        virtual void    postTraversal   (void             );

        virtual ResultE traverse        (NodePtr pRoot    );

        virtual void    receiveStateRead (UInt32  uiActorId);
        virtual void    receiveStateWrite(UInt32  uiActorId);

    protected:        
        class LeaveEntry;

        typedef std::list<LeaveEntry>      LeaveList;
        typedef LeaveList::iterator        LeaveListIt;

        typedef std::list<ActorStateChunk> StateList;
        typedef StateList::iterator        StateListIt;

        class LeaveEntry : public PIBase::LeaveEntryBase
        {
        public:
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

        class PQEntry : public PIBase::PQEntryBase
        {
        public:
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

    PriorityIterator(void);

    ResultE     _result;

    PIBase     *_pIter;
    PIEnter    *_pEnterIter;
    PIEnterOrd *_pEnterOrdIter;
    PILeave    *_pLeaveIter;
    PILeaveOrd *_pLeaveOrdIter;
};

OSG_END_NAMESPACE

#include "OSGPriorityIterator.inl"

#define OSGPRIORITYITERATOR_HEADER_CVSID "@(#)$Id: OSGPriorityIterator.h,v 1.1 2003/10/10 13:51:06 neumannc Exp $"

#endif /* _OSGPRIORITYITERATOR_H_ */
