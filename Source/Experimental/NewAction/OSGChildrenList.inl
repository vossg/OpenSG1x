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
/* NOTE                                                                    */
/*                                                                         */
/* ChildrenList::ChildrenListEntry must be defined first, because          */
/* the rest depends on the definition for inlining.                        */
/*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*/
/*    PRIVATE Types                                                        */

inline
ChildrenList::ChildrenListEntry::ChildrenListEntry(void)
    : _active  (true                                ),
      _priority(PriorityTypeTraits::getZeroElement())
{
}

inline
ChildrenList::ChildrenListEntry::ChildrenListEntry(bool         active,
                                                   PriorityType prio   )
    : _active  (active),
      _priority(prio  )
{
}

inline bool
ChildrenList::ChildrenListEntry::getActive(void) const
{
    return _active;
}

inline void
ChildrenList::ChildrenListEntry::setActive(bool active)
{
    _active = active;
}

inline ChildrenList::PriorityType
ChildrenList::ChildrenListEntry::getPriority(void) const
{
    return _priority;
}

inline void
ChildrenList::ChildrenListEntry::setPriority(PriorityType prio)
{
    _priority = prio;
}

/*-------------------------------------------------------------------------*/
/*    Constructors                                                         */

inline
ChildrenList::ChildrenList(void)
    : _pParentNode(NullFC),
      _childrenList(      )
{
}

/*-------------------------------------------------------------------------*/
/*    Destructor                                                           */

inline
ChildrenList::~ChildrenList(void)
{
}

/*-------------------------------------------------------------------------*/
/*    Parent                                                               */

inline void
ChildrenList::reset(void)
{
    _childrenList.assign(_pParentNode->getNChildren(), ChildrenListEntry());
}

inline NodePtr
ChildrenList::getParentNode(void) const
{
    return _pParentNode;
}

inline void
ChildrenList::setParentNode(const NodePtr &pParentNode)
{
    _pParentNode = pParentNode;
}

/*-------------------------------------------------------------------------*/
/*    Child                                                                */

inline NodePtr
ChildrenList::getChild(UInt32 childIndex) const
{
    return _pParentNode->getChild(childIndex);
}

/*-------------------------------------------------------------------------*/
/*    Active                                                               */

inline bool
ChildrenList::getActive(UInt32 childIndex) const
{
    return _childrenList[childIndex].getActive();
}

inline void
ChildrenList::setActive(UInt32 childIndex, bool active)
{
    _childrenList[childIndex].setActive(active);
}

/*-------------------------------------------------------------------------*/
/*    Priority                                                             */

inline ChildrenList::PriorityType
ChildrenList::getPriority(UInt32 childIndex) const
{
    return _childrenList[childIndex].getPriority();
}

inline void
ChildrenList::setPriority(UInt32 childIndex, PriorityType prio)
{
    _childrenList[childIndex].setPriority(prio);
}

/*-------------------------------------------------------------------------*/
/*    Misc                                                                 */

inline UInt32
ChildrenList::getSize(void) const
{
    //return _childrenList.size();
    return _pParentNode->getNChildren();
}

OSG_END_NAMESPACE

#define OSGCHILDRENLIST_INLINE_CVSID "@(#)$Id: OSGChildrenList.inl,v 1.2 2004/09/17 14:09:42 neumannc Exp $"
