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

OSG_BEGIN_NAMESPACE

/*****************************************************************************\
 * PriorityIterator                                                          *
\*****************************************************************************/

inline PriorityIterator::ResultE
PriorityIterator::getResult(void) const
{
    return _result;
}
 
inline void
PriorityIterator::setResult(ResultE res)
{
    _result = res;
}

/*****************************************************************************\
 * PriorityIterator::PIBase                                                  *
\*****************************************************************************/

inline
PriorityIterator::PIBase::PIBase(PriorityIterator *pPQIter)
    : _pPQIter(pPQIter)
{
}

inline PriorityIterator *
PriorityIterator::PIBase::getIter(void)
{
    return _pPQIter;
}

/*****************************************************************************\
 * PriorityIterator::PIBase::LeaveEntryBase                                  *
\*****************************************************************************/

inline
PriorityIterator::PIBase::LeaveEntryBase::LeaveEntryBase(void)
    : _uiPending(0)
{
}

inline
PriorityIterator::PIBase::LeaveEntryBase::LeaveEntryBase(UInt32 uiPending)
    : _uiPending(uiPending)
{
}

inline
PriorityIterator::PIBase::LeaveEntryBase::~LeaveEntryBase(void)
{
}

inline UInt32
PriorityIterator::PIBase::LeaveEntryBase::getPending(void) const
{
    return _uiPending;
}

inline UInt32
PriorityIterator::PIBase::LeaveEntryBase::decPending(void)
{
    return --(_uiPending);
}

/*****************************************************************************\
 * PriorityIterator::PIBase::PQEntryBase                                     *
\*****************************************************************************/

inline
PriorityIterator::PIBase::PQEntryBase::PQEntryBase(void)
    : _pNode   (NullFC),
      _priority(      )
{
}

inline
PriorityIterator::PIBase::PQEntryBase::PQEntryBase(NodePtr      pNode, 
                                                   PriorityType prio  )
    : _pNode   (pNode),
      _priority(prio )
{
}

inline
PriorityIterator::PIBase::PQEntryBase::~PQEntryBase(void)
{
}

inline NodePtr
PriorityIterator::PIBase::PQEntryBase::getNode(void) const
{
    return _pNode;
}

inline PriorityIterator::PriorityType
PriorityIterator::PIBase::PQEntryBase::getPrio(void) const
{
    return _priority;
}

/*****************************************************************************\
 * PriorityIterator::PIBase::PQEntryLessCompare                              *
\*****************************************************************************/

inline bool
PriorityIterator::PIBase::PQEntryLessCompare::operator()(
    const PQEntryBase &refLHS, const PQEntryBase &refRHS)
{
    return (refLHS.getPrio() < refRHS.getPrio());
}

/*****************************************************************************\
 * PriorityIterator::PIEnter                                                 *
\*****************************************************************************/

inline
PriorityIterator::PIEnter::PIEnter(PriorityIterator *pPQIter)
    : Inherited(pPQIter),
      _pqueue  (       )
{
}

/*****************************************************************************\
 * PriorityIterator::PILeave                                                 *
\*****************************************************************************/

inline
PriorityIterator::PILeave::PILeave(PriorityIterator *pPQIter)
    : Inherited (pPQIter),
      _pqueue   (       ),
      _leaveList(       )
{
}

/*****************************************************************************\
 * PriorityIterator::PILeave::LeaveEntry                                     *
\*****************************************************************************/

inline
PriorityIterator::PILeave::LeaveEntry::LeaveEntry(void)
    : Inherited(),
      _itParent()
{
}

inline
PriorityIterator::PILeave::LeaveEntry::LeaveEntry(UInt32      uiPending,
                                                  LeaveListIt itParent  )
    : Inherited(uiPending),
      _itParent(itParent )
{
}

inline
PriorityIterator::PILeave::LeaveEntry::~LeaveEntry(void)
{
}

inline PriorityIterator::PILeave::LeaveListIt
PriorityIterator::PILeave::LeaveEntry::getParent(void) const
{
    return _itParent;
}

/*****************************************************************************\
 * PriorityIterator::PILeave::PQEntry                                        *
\*****************************************************************************/

inline
PriorityIterator::PILeave::PQEntry::PQEntry(void)
    : Inherited          (),
      _itParentLeaveEntry()
{
}

inline
PriorityIterator::PILeave::PQEntry::PQEntry(NodePtr      pNode,
                                            PriorityType prio,
                                            LeaveListIt  itParentLeaveEntry)
    : Inherited          (pNode, prio       ), 
      _itParentLeaveEntry(itParentLeaveEntry)
{
}

inline
PriorityIterator::PILeave::PQEntry::~PQEntry(void)
{
}

inline PriorityIterator::PILeave::LeaveListIt
PriorityIterator::PILeave::PQEntry::getParentLeaveEntry(void) const
{
    return _itParentLeaveEntry;
}

/*****************************************************************************\
 * PriorityIterator::PIEnterOrd                                              *
\*****************************************************************************/

inline
PriorityIterator::PIEnterOrd::PIEnterOrd(PriorityIterator *pPQIter)
    : Inherited   (pPQIter         ),
      _bStateValid(true            ),
      _bStateSaved(false           ),
      _pqueue     (                ),
      _stateList  (                ),
      _currState  (_stateList.end())
{
}

/*****************************************************************************\
 * PriorityIterator::PIEnterOrd::PQEntry                                     *
\*****************************************************************************/

inline
PriorityIterator::PIEnterOrd::PQEntry::PQEntry(void)
    : Inherited     (),
      _itParentState()
{
}

inline
PriorityIterator::PIEnterOrd::PQEntry::PQEntry(NodePtr      pNode,
                                               PriorityType prio,
                                               StateListIt  itParentState)
    : Inherited     (pNode, prio  ),
      _itParentState(itParentState)
{
}

inline
PriorityIterator::PIEnterOrd::PQEntry::~PQEntry(void)
{
}

inline PriorityIterator::PIEnterOrd::StateListIt
PriorityIterator::PIEnterOrd::PQEntry::getParentState(void) const
{
    return _itParentState;
}

/*****************************************************************************\
 * PriorityIterator::PILeaveOrd                                              *
\*****************************************************************************/

inline
PriorityIterator::PILeaveOrd::PILeaveOrd(PriorityIterator *pPQIter)
    : Inherited   (pPQIter         ),
      _bStateValid(true            ),
      _bStateSaved(false           ),
      _pqueue     (                ),
      _leaveList  (                ),
      _stateList  (                ),
      _currState  (_stateList.end())
{
}

/*****************************************************************************\
 * PriorityIterator::PILeaveOrd::LeaveEntry                                  *
\*****************************************************************************/

inline
PriorityIterator::PILeaveOrd::LeaveEntry::LeaveEntry(void)
    : Inherited(),
      _itParent(),
      _itState ()
{
}

inline
PriorityIterator::PILeaveOrd::LeaveEntry::LeaveEntry(UInt32      uiPending,
                                                     LeaveListIt itParent,
                                                     StateListIt itState   )
    : Inherited(uiPending),
      _itParent(itParent ),
      _itState (itState  )
{
}

inline
PriorityIterator::PILeaveOrd::LeaveEntry::~LeaveEntry(void)
{
}

inline PriorityIterator::PILeaveOrd::LeaveListIt
PriorityIterator::PILeaveOrd::LeaveEntry::getParent(void) const
{
    return _itParent;
}

inline PriorityIterator::PILeaveOrd::StateListIt
PriorityIterator::PILeaveOrd::LeaveEntry::getState(void) const
{
    return _itState;
}

/*****************************************************************************\
 * PriorityIterator::PILeaveOrd::PQEntry                                     *
\*****************************************************************************/

inline
PriorityIterator::PILeaveOrd::PQEntry::PQEntry(void)
    : Inherited          (),
      _itParentLeaveEntry(),
      _itState           ()
{
}

inline
PriorityIterator::PILeaveOrd::PQEntry::PQEntry(NodePtr pNode,
                                               PriorityType prio,
                                               LeaveListIt itParentLeaveEntry,
                                               StateListIt itState            )
    : Inherited          (pNode, prio       ),
      _itParentLeaveEntry(itParentLeaveEntry),
      _itState           (itState           )
{
}

inline
PriorityIterator::PILeaveOrd::PQEntry::~PQEntry(void)
{
}

inline PriorityIterator::PILeaveOrd::LeaveListIt
PriorityIterator::PILeaveOrd::PQEntry::getParentLeaveEntry(void) const
{
    return _itParentLeaveEntry;
}

inline PriorityIterator::PILeaveOrd::StateListIt
PriorityIterator::PILeaveOrd::PQEntry::getParentState(void) const
{
    return _itState;
}

OSG_END_NAMESPACE

#define OSGPRIORITYITERATOR_INLINE_CVSID "@(#)$Id: OSGPriorityIterator.inl,v 1.2 2003/10/10 14:27:44 neumannc Exp $"
