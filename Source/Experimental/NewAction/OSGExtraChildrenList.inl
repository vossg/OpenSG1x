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

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/* NOTE NOTE                                                               */
/* ExtraChildrenList::ChildrenListEntry must be defined first, because     */
/* the rest depends on the definition for inlining.                        */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/*    PRIVATE Types                                                        */

inline
ExtraChildrenList::ChildrenListEntry::ChildrenListEntry(void)
    : _pNode   (NullFC                              ),
      _priority(PriorityTypeTraits::getZeroElement()),
      _active  (false                               )
{
}

inline
ExtraChildrenList::ChildrenListEntry::ChildrenListEntry(const NodePtr &pNode)
    : _pNode   (pNode                               ),
      _priority(PriorityTypeTraits::getZeroElement()),
      _active  (true                                )
{
}

inline
ExtraChildrenList::ChildrenListEntry::ChildrenListEntry(
    const NodePtr &pNode, PriorityType prio)

    : _pNode   (pNode),
      _priority(prio ),
      _active  (true )
{
}

inline NodePtr
ExtraChildrenList::ChildrenListEntry::getNode(void) const
{
    return _pNode;
}

inline void
ExtraChildrenList::ChildrenListEntry::setNode(const NodePtr &pNode)
{
    _pNode = pNode;
}

inline ExtraChildrenList::PriorityType
ExtraChildrenList::ChildrenListEntry::getPriority(void) const
{
    return _priority;
}

inline void
ExtraChildrenList::ChildrenListEntry::setPriority(PriorityType prio)
{
    _priority = prio;
}

inline bool
ExtraChildrenList::ChildrenListEntry::getActive(void) const
{
    return _active;
}

inline void
ExtraChildrenList::ChildrenListEntry::setActive(bool active)
{
    _active = active;
}

/*-------------------------------------------------------------------------*/
/*    Constructors                                                         */

inline
ExtraChildrenList::ExtraChildrenList(void)
    : _childrenList()
{
}

/*-------------------------------------------------------------------------*/
/*    Destructor                                                           */

inline
ExtraChildrenList::~ExtraChildrenList(void)
{
}

/*-------------------------------------------------------------------------*/
/*    Add                                                                  */

inline UInt32
ExtraChildrenList::addChild(const NodePtr &pNode)
{
    UInt32 childIndex = _childrenList.size();

    _childrenList.push_back(ChildrenListEntry(pNode));

    return childIndex;
}

inline UInt32
ExtraChildrenList::addChild(const NodePtr &pNode, PriorityType prio)
{
    UInt32 childIndex = _childrenList.size();

    _childrenList.push_back(ChildrenListEntry(pNode, prio));

    return childIndex;
}

/*-------------------------------------------------------------------------*/
/*    Access                                                               */

inline NodePtr
ExtraChildrenList::getChild(UInt32 childIndex) const
{
    return _childrenList[childIndex].getNode();
}

inline ExtraChildrenList::PriorityType
ExtraChildrenList::getPriority(UInt32 childIndex) const
{
    return _childrenList[childIndex].getPriority();
}

inline void
ExtraChildrenList::setPriority(UInt32 childIndex, PriorityType prio)
{
    _childrenList[childIndex].setPriority(prio);
}

inline bool
ExtraChildrenList::getActive(UInt32 childIndex) const
{
    return _childrenList[childIndex].getActive();
}

inline void
ExtraChildrenList::setActive(UInt32 childIndex, bool bActive)
{
    _childrenList[childIndex].setActive(bActive);
}

/*-------------------------------------------------------------------------*/
/*    Misc                                                                 */

inline UInt32
ExtraChildrenList::getSize(void) const
{
    return _childrenList.size();
}

inline void
ExtraChildrenList::clear(void)
{
    _childrenList.clear();
}

OSG_END_NAMESPACE

#define OSGEXTRACHILDRENLIST_INLINE_CVSID "@(#)$Id: OSGExtraChildrenList.inl,v 1.2 2004/09/17 14:09:43 neumannc Exp $"
