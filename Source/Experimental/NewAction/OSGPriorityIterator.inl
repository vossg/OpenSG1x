
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
PriorityIterator::PIBase::PIBase(PriorityIterator &refPI)
    : _refPI(refPI)
{
}

inline PriorityIterator &
PriorityIterator::PIBase::getIter(void)
{
    return _refPI;
}

// inline PriorityIterator::ResultE
// PriorityIterator::PIBase::getResult(void) const
// {
//     return _refPI.getResult();
// }

// inline void
// PriorityIterator::PIBase::setResult(ResultE res)
// {
//     _refPI.setResult(res);
// }

// inline void
// PriorityIterator::PIBase::resetNodeList(void)
// {
//     _refPI.resetNodeList();
// }

// inline void
// PriorityIterator::PIBase::setUseNodeList(void)
// {
//     _refPI.setUseNodeList();
// }

// inline bool
// PriorityIterator::PIBase::getUseNodeList(void) const
// {
//     return _refPI.getUseNodeList();
// }

// inline ActiveNodeListIt
// PriorityIterator::PIBase::beginNodes(void)
// {
//     return _refPI.beginNodes();
// }

// inline ActiveNodeListIt
// PriorityIterator::PIBase::endNodes(void)
// {
//     return _refPI.endNodes();
// }

// inline ActiveNodeListConstIt
// PriorityIterator::PIBase::beginNodes(void) const
// {
//     return _refPI.beginNodes();
// }

// inline ActiveNodeListConstIt
// PriorityIterator::PIBase::endNodes(void) const
// {
//     return _refPI.endNodes();
// }

// inline ActiveNodeList &
// PriorityIterator::PIBase::getNodeList(void)
// {
//     return _refPI.getNodeList();
// }

// inline const ActiveNodeList &
// PriorityIterator::PIBase::getNodeList(void) const
// {
//     return _refPI.getNodeList();
// }

// inline void
// PriorityIterator::PIBase::setCurrentNode(NodePtr pCurrNode)
// {
//     _refPI.setCurrentNode(pCurrNode);
// }

// inline NodePtr
// PriorityIterator::PIBase::getCurrentNode(void)
// {
//     return _refPI.getCurrentNode();
// }

// inline NewActionIterInterface &
// PriorityIterator::PIBase::getActionInterface(void)
// {
//     return _refPI.getActionInterface();
// }

// inline PriorityIterator::ResultE
// PriorityIterator::PIBase::callEnter(NodePtr pNode)
// {
//     return _refPI.callEnter(pNode);
// }

// inline PriorityIterator::ResultE
// PriorityIterator::PIBase::callLeave(NodePtr pNode)
// {
//     return _refPI.callLeave(pNode);
// }

// inline PriorityIterator::ResultE
// PriorityIterator::PIBase::startActors(void)
// {
//     return _refPI.startActors();
// }

// inline PriorityIterator::ResultE
// PriorityIterator::PIBase::stopActors(void)
// {
//     return _refPI.stopActors();
// }

/*****************************************************************************\
 * PriorityIterator::PIBase::LeaveEntryBase                                  *
\*****************************************************************************/

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
PriorityIterator::PIEnter::PIEnter(PriorityIterator &refPI)
    : Inherited(refPI),
      _pqueue  (     )
{
}

/*****************************************************************************\
 * PriorityIterator::PILeave                                                 *
\*****************************************************************************/

inline
PriorityIterator::PILeave::PILeave(PriorityIterator &refPI)
    : Inherited (refPI),
      _pqueue   (     ),
      _leaveList(     )
{
}

/*****************************************************************************\
 * PriorityIterator::PILeave::LeaveEntry                                     *
\*****************************************************************************/

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
PriorityIterator::PIEnterOrd::PIEnterOrd(PriorityIterator &refPI)
    : Inherited   (refPI           ),
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
PriorityIterator::PILeaveOrd::PILeaveOrd(PriorityIterator &refPI)
    : Inherited   (refPI           ),
      _bStateValid(true            ),
      _bStateSaved(true            ),
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

#define OSGPRIORITYITERATOR_INLINE_CVSID "@(#)$Id: $"
