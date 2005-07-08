/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000-2002 by OpenSG Forum                   *
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

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGNodeCore.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

OSG_BEGIN_NAMESPACE

OSG_ABSTR_FIELD_CONTAINER_INL_DEF(NodeCore, NodeCorePtr)

/*-------------------------------------------------------------------------*/
/*                              Parents                                    */

inline
MFNodePtr &NodeCore::getParents(void)
{
    return _parents;
}

inline
const MFNodePtr &NodeCore::getParents(void) const
{
    return _parents;
}

inline
MFNodePtr *NodeCore::getMFParents(void)
{
    return &_parents;
}

/*-------------------------------------------------------------------------*/
/*                         Binary Interface                                */

inline
UInt32 NodeCore::getBinSize(const BitVector &whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (ParentsFieldMask & whichField))
    {
        returnValue += _parents.getBinSize();
    }

    return returnValue;
}

inline
void NodeCore::copyToBin(      BinaryDataHandler &pMem,
                         const BitVector         &whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (ParentsFieldMask & whichField))
    {
        _parents.copyToBin(pMem);
    }
}

inline
void NodeCore::copyFromBin(      BinaryDataHandler &pMem,
                           const BitVector         &whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (ParentsFieldMask & whichField))
    {
        _parents.copyFromBin(pMem);
    }
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

inline
NodeCore::NodeCore(void) :
     Inherited(),
    _parents  ()
{
}

inline
NodeCore::NodeCore(const NodeCore &obj) :
     Inherited(obj),
    _parents  (   )
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

inline
NodeCore::~NodeCore(void)
{
}

/*-------------------------------------------------------------------------*/
/*                          MT Destruction                                 */

inline
void NodeCore::onDestroy(void)
{
}

/*-------------------------------------------------------------------------*/
/*                              Parents                                    */

inline
void NodeCore::addParent(const NodePtr &parent)
{
    _parents.push_back(parent);
}

inline
void NodeCore::subParent(const NodePtr &parent)
{
    MFNodePtr::iterator parentIt = _parents.find(parent);

    if(parentIt != _parents.end())
    {
        _parents.erase(parentIt);
    }
}

/*-------------------------------------------------------------------------*/
/*                              Pointer                                    */

inline
NodeCorePtr NodeCore::getPtr(void) const
{
    return NodeCorePtr(*this);
}

/*-------------------------------------------------------------------------*/
/*                                Sync                                     */

#if !defined(OSG_FIXED_MFIELDSYNC)
inline
void NodeCore::executeSyncImpl(      NodeCore  *pOther,
                               const BitVector &whichField)
{
    Inherited::executeSyncImpl(pOther, whichField);

    if(FieldBits::NoField != (ParentsFieldMask & whichField))
    {
        _parents.syncWith(pOther->_parents);
    }
}

inline
void NodeCore::executeSync(      FieldContainer &other,
                           const BitVector      &whichField)
{
    this->executeSyncImpl((NodeCore *) &other, whichField);
}
#else
inline
void NodeCore::executeSyncImpl(      NodeCore  *pOther,
                               const BitVector &whichField,
                               const SyncInfo  &sInfo     )
{
    Inherited::executeSyncImpl(pOther, whichField, sInfo);

    if(FieldBits::NoField != (ParentsFieldMask & whichField))
    {
        _parents.syncWith(pOther->_parents, sInfo);
    }
}

inline
void NodeCore::executeSync(      FieldContainer &other,
                           const BitVector      &whichField,
                           const SyncInfo       &sInfo     )
{
    this->executeSyncImpl((NodeCore *) &other, whichField, sInfo);
}
#endif

/*-------------------------------------------------------------------------*/
/*                              Matrix                                     */

inline
void NodeCore::accumulateMatrix(Matrix &)
{
}

/*-------------------------------------------------------------------------*/
/*                              Volume                                     */

inline
void NodeCore::adjustVolume(Volume &)
{
}

inline
void NodeCore::invalidateVolume(void)
{
    for(UInt32 i = 0; i < _parents.size(); i++)
    {
        _parents[i]->invalidateVolume();
    }
}


OSG_END_NAMESPACE

#define OSGNODECORE_INLINE_CVSID "@(#)$Id: $"

