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

inline
DepthFirstIterator::StackEntry::StackEntry(const NodePtr &pNode, bool bLeave)
    : _pNode (pNode ),
      _bLeave(bLeave)
{
}

inline NodePtr
DepthFirstIterator::StackEntry::getNode(void) const
{
    return _pNode;
}

inline bool
DepthFirstIterator::StackEntry::getLeave(void) const
{
    return _bLeave;
}

inline void
DepthFirstIterator::StackEntry::setLeave(bool bLeave)
{
    _bLeave = bLeave;
}

OSG_END_NAMESPACE

#define OSGDEPTHFIRSTITERATOR_INLINE_CVSID "@(#)$Id: OSGDepthFirstIterator.inl,v 1.1 2003/10/10 13:51:06 neumannc Exp $"
