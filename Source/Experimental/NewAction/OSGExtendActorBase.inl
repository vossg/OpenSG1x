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

//----------------------------------------------------------------------------
//    Children Managment
//----------------------------------------------------------------------------

/*! Return if the children list is enabled.
 */

inline bool
ExtendActorBase::getChildrenListEnabled(void) const
{
    return getAction()->getChildrenListEnabled();
}

/*! Enable or disable the children list.
 */

inline void
ExtendActorBase::setChildrenListEnabled(bool enabled)
{
    getAction()->setChildrenListEnabled(enabled);
}

/*! Return the traversed node.
 */

inline NodePtr
ExtendActorBase::getNode(void) const
{
    return getAction()->getChildrenList().getParentNode();
}

/*! Return the number of children of the traversed node.
 */

inline UInt32
ExtendActorBase::getNumChildren(void) const
{
    return getAction()->getChildrenList().getSize();
}

/*! Return the childIndex'th child of the traversed node.
    \warning childIndex is not range checked.
*/

inline NodePtr
ExtendActorBase::getChild(UInt32 childIndex) const
{
    return getAction()->getChildrenList().getChild(childIndex);
}

/*! Return if the childIndex'th child is active, i.e. whether it will be
    traversed.
    \warning childIndex is not range checked.
    \warning The children list must have been enabled with
    setChildrenListEnabled(true);
*/

inline bool
ExtendActorBase::getChildActive(UInt32 childIndex) const
{
    return getAction()->getChildrenList().getActive(childIndex);
}

/*! Set if the childIndex'th child will be included in the traversal.
    \warning childIndex is not range checked.
    \warning The children list must have been enabled with
    setChildrenListEnabled(true);
*/

inline void
ExtendActorBase::setChildActive(UInt32 childIndex, bool active)
{
    getAction()->getChildrenList().setActive(childIndex, active);
}

/*! Return the priority assigned to the childIndex'th child.
    \warning childIndex is not range checked.
    \warning The children list must have been enabled with
    setChildrenListEnabled(true);
*/

inline ExtendActorBase::PriorityType
ExtendActorBase::getChildPriority(UInt32 childIndex) const
{
    return getAction()->getChildrenList().getPriority(childIndex);
}

/*! Set the priority of the childIndex'th child.
    \warning childIndex is not range checked.
    \warning The children list must have been enabled with
    setChildrenListEnabled(true);
*/

inline void
ExtendActorBase::setChildPriority(UInt32 childIndex, PriorityType prio)
{
    getAction()->getChildrenList().setPriority(childIndex, prio);
}

//----------------------------------------------------------------------------
//    Extra Children Managment
//----------------------------------------------------------------------------

/*! Add a node as extra child, i.e. this node will be traversed as if it
    was a child of the currently traversed node.
 */

inline UInt32
ExtendActorBase::addExtraChild(const NodePtr &pNode)
{
    return getAction()->getExtraChildrenList().addChild(pNode);
}

/*! Add a node as extra child with priority, this node will be traversed as if
    it was a child of the currently traversed node.
 */

inline UInt32
ExtendActorBase::addExtraChild(const NodePtr &pNode, PriorityType prio)
{
    return getAction()->getExtraChildrenList().addChild(pNode, prio);
}

/*! Return the number of extra children already added.
 */

inline UInt32
ExtendActorBase::getNumExtraChildren(void) const
{
    return getAction()->getExtraChildrenList().getSize();
}

/*! Return the childIndex'th extra child.
    \warning childIndex is not range checked.
 */

inline NodePtr
ExtendActorBase::getExtraChild(UInt32 childIndex) const
{
    return getAction()->getExtraChildrenList().getChild(childIndex);
}

/*! Return if the childIndex'th extra child is active, i.e. whether it will be
    traversed.
    \warning childIndex is not range checked.
*/

inline bool
ExtendActorBase::getExtraChildActive(UInt32 childIndex) const
{
    return getAction()->getExtraChildrenList().getActive(childIndex);
}

/*! Set if the childIndex'th extra child will be included in the traversal.
    \warning childIndex is not range checked.
*/

inline void
ExtendActorBase::setExtraChildActive(UInt32 childIndex, bool active)
{
    getAction()->getExtraChildrenList().setActive(childIndex, active);
}

/*! Return the priority assigned to the childIndex'th extra child.
    \warning childIndex is not range checked.
*/

inline ExtendActorBase::PriorityType
ExtendActorBase::getExtraChildPriority(UInt32 childIndex) const
{
    return getAction()->getExtraChildrenList().getPriority(childIndex);
}

/*! Set the priority of the childIndex'th extra child.
    \warning childIndex is not range checked.
*/

inline void
ExtendActorBase::setExtraChildPriority(UInt32 childIndex, PriorityType prio)
{
    getAction()->getExtraChildrenList().setPriority(childIndex, prio);
}

OSG_END_NAMESPACE

#define OSGEXTENDACTORBASE_INLINE_CVSID "@(#)$Id: OSGExtendActorBase.inl,v 1.2 2004/09/11 11:10:03 neumannc Exp $"
