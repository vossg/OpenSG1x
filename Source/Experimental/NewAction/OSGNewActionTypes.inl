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

namespace NewActionTypes
{

inline
NodePriorityPair::NodePriorityPair(const NodePtr &pNode)
    : _pNode   (pNode                                     ),
      _priority(TypeTraits<PriorityType>::getZeroElement())
{
}

inline
NodePriorityPair::NodePriorityPair(const NodePtr &pNode, PriorityType priority)
    : _pNode   (pNode   ),
      _priority(priority)
{
}

inline NodePtr
NodePriorityPair::getNode(void) const
{
    return _pNode;
}

inline void
NodePriorityPair::setNode(const NodePtr &pNode)
{
    _pNode = pNode;
}

inline PriorityType
NodePriorityPair::getPriority(void) const
{
    return _priority;
}

inline void
NodePriorityPair::setPriority(PriorityType priority)
{
    _priority = priority;
}

inline bool
NodePriorityPair::LessCompare::operator ()(const NodePriorityPair &lhs,
                                           const NodePriorityPair &rhs )
{
    return (lhs.getPriority() < rhs.getPriority());
}

} /* namespace NewActionTypes */

OSG_END_NAMESPACE

#define OSGNEWACTIONTYPES_INLINE_CVSID "@(#)$Id: OSGNewActionTypes.inl,v 1.2 2004/04/21 14:54:33 a-m-z Exp $"
