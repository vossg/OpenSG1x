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
//    Extra Children Management
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

//----------------------------------------------------------------------------
//    Multi Pass Management
//----------------------------------------------------------------------------

inline void
ExtendActorBase::setNumPasses(UInt32 numPasses)
{
    getAction()->setNumPasses(numPasses);
}

OSG_END_NAMESPACE

#define OSGEXTENDACTORBASE_INLINE_CVSID "@(#)$Id: OSGExtendActorBase.inl,v 1.4 2004/09/17 14:09:43 neumannc Exp $"
