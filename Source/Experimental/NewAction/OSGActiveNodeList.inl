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
 - CLASS ActiveNodeList::ListEntry                                           -
\*****************************************************************************/

inline
ActiveNodeList::ListEntry::ListEntry(bool bActive, PriorityType priority)
    : _bActive (bActive ),
      _priority(priority)
{
}

inline bool
ActiveNodeList::ListEntry::getActive(void) const
{
    return _bActive;
}

inline void
ActiveNodeList::ListEntry::setActive(bool bActive)
{
    _bActive = bActive;
}

inline ActiveNodeList::PriorityType
ActiveNodeList::ListEntry::getPriority(void) const
{
    return _priority;
}

inline void
ActiveNodeList::ListEntry::setPriority(PriorityType priority)
{
    _priority = priority;
}

/*****************************************************************************\
 - CLASS ActiveNodeList                                                      -
\*****************************************************************************/

inline
ActiveNodeList::ActiveNodeList(void)
    : _pNode           (NullFC),
      _list            (      ),
      _uiNumActive     (0     )
{
}

inline
ActiveNodeList::ActiveNodeList(NodePtr pNode)
    : _pNode           (NullFC),
      _list            (      ),
      _uiNumActive     (0     )
{
    setParent(pNode);
}

inline
ActiveNodeList::~ActiveNodeList(void)
{
}

inline void
ActiveNodeList::setParent(NodePtr pNode)
{
    _pNode       = pNode;
    _uiNumActive = pNode->getNChildren();

    _list.assign(_uiNumActive, ListEntry());
};
    
inline NodePtr
ActiveNodeList::getParent(void) const
{
    return _pNode;
}

inline bool
ActiveNodeList::getActive(UInt32 uiIndex) const
{
    return _list[uiIndex].getActive();
}

inline void
ActiveNodeList::deactivate(UInt32 uiIndex)
{
    if(_list[uiIndex].getActive() == true)
        --_uiNumActive;

    _list[uiIndex].setActive(false);
}

inline ActiveNodeList::PriorityType
ActiveNodeList::getPriority(UInt32 uiIndex) const
{
    return _list[uiIndex].getPriority();
}

inline void
ActiveNodeList::setPriority(UInt32 uiIndex, PriorityType priority)
{
    _list[uiIndex].setPriority(priority);
}

inline void
ActiveNodeList::clear(void)
{
    _list.clear();
}

inline UInt32
ActiveNodeList::size(void) const
{
    return _list.size();
}

inline UInt32
ActiveNodeList::getNumActive(void) const
{
    return _uiNumActive;
}

inline void
ActiveNodeList::swap(ActiveNodeList &other)
{
    std::swap(_pNode,       other._pNode      );
    std::swap(_list,        other._list       );
    std::swap(_uiNumActive, other._uiNumActive);
}

/****************************************************************************\
 * NOTE:                                                                    *
 * must define the iterators here first - then continue with                *
 * ActiveNodeList itself. inline order... :(                                *
\****************************************************************************/

/***************************************************************************\
 * CLASS ActiveNodeListConstIt                                             *
\***************************************************************************/

inline
ActiveNodeListConstIt::ActiveNodeListConstIt(
    const ActiveNodeList &refList,
          UInt32          uiIndex )   
    
    : _pList  (&refList),
      _uiIndex(uiIndex )
{
}

inline
ActiveNodeListConstIt::ActiveNodeListConstIt(
    const ActiveNodeListConstIt &source)
    
    : _pList  (source._pList  ),
      _uiIndex(source._uiIndex)
{
}

inline ActiveNodeListConstIt &
ActiveNodeListConstIt::operator++(void)
{
    UInt32 uiSize = _pList->_list.size();

    ++_uiIndex;
    
    while((_uiIndex < uiSize) && (_pList->getActive(_uiIndex) == false))
    {
        ++_uiIndex;
    }

    return *this;
}

inline ActiveNodeListConstIt
ActiveNodeListConstIt::operator++(int)
{
    ActiveNodeListConstIt tmp = *this;

    ++*this;

    return tmp;
}

inline ActiveNodeListConstIt &
ActiveNodeListConstIt::operator--(void)
{
    --_uiIndex;

    while((_uiIndex > 0) && (_pList->getActive(_uiIndex) == false))
    {
        --_uiIndex;
    }

    return *this;
}

inline ActiveNodeListConstIt
ActiveNodeListConstIt::operator--(int)
{
    ActiveNodeListConstIt tmp = *this;

    --*this;

    return tmp;
}

inline const ActiveNodeList &
ActiveNodeListConstIt::getList(void) const
{
    return *_pList;
}

inline NodePtr
ActiveNodeListConstIt::getNode(void) const
{
    return _pList->getParent()->getChild(_uiIndex);
}

inline UInt32
ActiveNodeListConstIt::getIndex(void) const
{
    return _uiIndex;
}

inline bool
ActiveNodeListConstIt::getActive(void) const
{
    return _pList->getActive(_uiIndex);
}

inline ActiveNodeListConstIt::PriorityType
ActiveNodeListConstIt::getPriority(void) const
{
    return _pList->getPriority(_uiIndex);
}

/***************************************************************************\
 * CLASS ActiveNodeListIt                                                  *
\***************************************************************************/

inline
ActiveNodeListIt::ActiveNodeListIt(ActiveNodeList &refList,
                                   UInt32          uiIndex )
    : _pList  (&refList),
      _uiIndex(uiIndex )
{
}

inline
ActiveNodeListIt::ActiveNodeListIt(const ActiveNodeListIt &source)
    : _pList  (source._pList  ),
      _uiIndex(source._uiIndex)
{
}

inline
ActiveNodeListIt::operator ActiveNodeListConstIt(void) const
{
    return ActiveNodeListConstIt(*_pList, _uiIndex);
}

inline ActiveNodeListIt &
ActiveNodeListIt::operator++(void)
{
    UInt32 uiSize = _pList->_list.size();

    ++_uiIndex;

    while((_uiIndex < uiSize) && (_pList->getActive(_uiIndex) == false))
    {
        ++_uiIndex;
    }

    return *this;
}

inline ActiveNodeListIt
ActiveNodeListIt::operator++(int)
{
    ActiveNodeListIt tmp = *this;

    ++*this;

    return tmp;
}

inline ActiveNodeListIt &
ActiveNodeListIt::operator--(void)
{
    --_uiIndex;

    while((_uiIndex > 0) && (_pList->getActive(_uiIndex) == false))
    {
        --_uiIndex;
    }

    return *this;
}

inline ActiveNodeListIt
ActiveNodeListIt::operator--(int)
{
    ActiveNodeListIt tmp = *this;

    --*this;

    return tmp;
}

inline ActiveNodeList &
ActiveNodeListIt::getList(void) const
{
    return *_pList;
}

inline NodePtr
ActiveNodeListIt::getNode(void) const
{
    return _pList->getParent()->getChild(getIndex());
}

inline UInt32
ActiveNodeListIt::getIndex(void) const
{
    return _uiIndex;
}

inline bool
ActiveNodeListIt::getActive(void) const
{
    return _pList->getActive(_uiIndex);
}

inline ActiveNodeListIt::PriorityType
ActiveNodeListIt::getPriority(void) const
{
    return _pList->getPriority(_uiIndex);
}

inline void
ActiveNodeListIt::deactivate(void) const
{
    _pList->deactivate(_uiIndex);
}

inline void
ActiveNodeListIt::setPriority(PriorityType priority) const
{
    _pList->setPriority(_uiIndex, priority);
}

/*****************************************************************************\
 * GLOBAL FUNCTIONS                                                          *
\*****************************************************************************/

inline bool
operator==(const ActiveNodeListConstIt &lhs, 
           const ActiveNodeListConstIt &rhs)
{
    return (lhs.getIndex() == rhs.getIndex());
}

inline bool
operator!=(const ActiveNodeListConstIt &lhs,
           const ActiveNodeListConstIt &rhs)
{
    return !(lhs == rhs);
}

inline bool
operator==(const ActiveNodeListIt      &lhs,
           const ActiveNodeListIt      &rhs )
{
    return (lhs.getIndex() == rhs.getIndex());
}

inline bool
operator!=(const ActiveNodeListIt      &lhs,
           const ActiveNodeListIt      &rhs )
{
    return !(lhs == rhs);
}

/*****************************************************************************\
 * NOTE:                                                                     *
 * ActiveNodeList definition contiues here:                                  *
\*****************************************************************************/

inline ActiveNodeListIt
ActiveNodeList::begin(void)
{
    UInt32           uiSize (_list.size());
    ActiveNodeListIt retIter(*this, 0  );

    if((retIter.getIndex() < uiSize) && (retIter.getActive() == false))
        ++retIter;

    return retIter;
}

inline ActiveNodeListIt
ActiveNodeList::end(void)
{
    return ActiveNodeListIt(*this, _list.size());
}

inline ActiveNodeListConstIt
ActiveNodeList::begin(void) const
{
    UInt32                uiSize (_list.size());
    ActiveNodeListConstIt retIter(*this, 0    );

    if((retIter.getIndex() < uiSize) && (retIter.getActive() == false))
        ++retIter;

    return retIter;
}

inline ActiveNodeListConstIt
ActiveNodeList::end(void) const
{
    return ActiveNodeListConstIt(*this, _list.size());
}

OSG_END_NAMESPACE

namespace std
{
    template <>
    inline void
    swap(OSG::ActiveNodeList &list1, OSG::ActiveNodeList &list2)
    {
        list1.swap(list2);
    }
}

#define OSGACTIVENODELIST_INLINE_CVSID "@(#)$Id: OSGActiveNodeList.inl,v 1.1 2003/10/10 13:51:06 neumannc Exp $"
