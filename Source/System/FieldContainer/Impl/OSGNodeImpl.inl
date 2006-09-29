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

#ifndef _OSGNODEIMPL_INL_
#define _OSGNODEIMPL_INL_

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGNodeImpl.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

inline
const DynamicVolume &Node::getVolume(void) const
{
    return _sfVolume.getValue();
}

inline
DynamicVolume &Node::getVolume(bool update)
{
    if(update == true)
        updateVolume();

    return _sfVolume.getValue();
}

inline
NodePtr Node::getParent(void)
{
    return _sfParent.getValue();
}

inline
UInt32 Node::getNChildren(void) const
{
    return _mfChildren.size();
}
 
inline
NodePtr Node::getChild(UInt32 childIndex)
{
    OSG_ASSERT((childIndex < _mfChildren.size()));

    return _mfChildren[childIndex];
}


inline
UInt32 Node::getTravMask(void) const
{
    return _sfTravMask.getValue();
}

inline
void  Node::setTravMask(UInt32 val)
{
    _sfTravMask.setValue(val);
}

inline
bool Node::getActive(void) const
{
    return getTravMask() == TypeTraits<UInt32>::getMax();
}

inline
void  Node::setActive(bool val)
{
    _sfTravMask.setValue(val ? TypeTraits<UInt32>::getMax()        :
                               TypeTraits<UInt32>::getZeroElement() );
}

inline
void Node::setOcclusionMask(UInt8 val)
{
    _occlusionMask = val;
}

inline
UInt8 Node::getOcclusionMask(void) const
{
    return _occlusionMask;
}

/*-------------------------------------------------------------------------*/
/*                          Access Fields                                  */

inline
SFDynamicVolume *Node::getSFVolume(void)
{
    return &_sfVolume;
}

inline
SFUInt32 *Node::getSFTravMask(void)
{
    return &_sfTravMask;
}

inline
SFNodePtr *Node::getSFParent(void)
{
    return &_sfParent;
}

inline
SFNodeCorePtr *Node::getSFCore(void)
{
    return &_sfCore;
}

inline
MFNodePtr *Node::getMFChildren(void)
{
    return &_mfChildren;
}


/*-------------------------------------------------------------------------*/
/*                              Changed                                    */

inline
void Node::changed(BitVector  whichField,
                   UInt32     origin    )
{
    Inherited::changed(whichField, origin);

    if(whichField & CoreFieldMask)
    {
        invalidateVolume();

        if(origin & ChangedOrigin::Abstract)
        {
            if(origin & ChangedOrigin::AbstrIncRefCount)
            {
                addRefCP(_sfCore.getValue());
            }
        }
    }

    if(whichField & TravMaskFieldMask)
    {
        beginEditCP(getParent(), Node::VolumeFieldMask);
        if(getParent() != NullFC)
        {
            getParent()->invalidateVolume();
        }
        else
        {
            invalidateVolume();
        }
        endEditCP(getParent(), Node::VolumeFieldMask);
    }
    
    if(whichField & ChildrenFieldMask)
    {
        invalidateVolume();

        if(origin & ChangedOrigin::Abstract)
        {
            if(origin & ChangedOrigin::AbstrIncRefCount)
            {
                MFNodePtr::iterator       vChildIt    = _mfChildren.begin();
                MFNodePtr::const_iterator endChildren = _mfChildren.end  ();
                
                while(vChildIt != endChildren)
                {
                    addRefCP(*vChildIt);

                    ++vChildIt;
                }
            }
        }
    }
}

/*-------------------------------------------------------------------------*/
/*                           Binary Interface                              */

inline
UInt32 Node::getBinSize(const BitVector &whichField)
{
    UInt32 returnValue = Inherited::getBinSize(whichField);

    if(FieldBits::NoField != (VolumeFieldMask & whichField))
    {
        returnValue += _sfVolume       .getBinSize();
    }

    if(FieldBits::NoField != (TravMaskFieldMask & whichField))
    {
        returnValue += _sfTravMask     .getBinSize();
    }

    if(FieldBits::NoField != (ParentFieldMask & whichField))
    {
        returnValue += _sfParent       .getBinSize();
    }

    if(FieldBits::NoField != (ChildrenFieldMask & whichField))
    {
        returnValue += _mfChildren     .getBinSize();
    }

    if(FieldBits::NoField != (CoreFieldMask & whichField))
    {
        returnValue += _sfCore         .getBinSize();
    }

    return returnValue;
}

inline
void Node::copyToBin(      BinaryDataHandler &pMem,
                     const BitVector         &whichField)
{
    Inherited::copyToBin(pMem, whichField);

    if(FieldBits::NoField != (VolumeFieldMask & whichField))
    {
        _sfVolume.copyToBin(pMem);
    }

    if(FieldBits::NoField != (TravMaskFieldMask & whichField))
    {
        _sfTravMask.copyToBin(pMem);
    }

    if(FieldBits::NoField != (ParentFieldMask & whichField))
    {
        _sfParent.copyToBin(pMem);
    }

    if(FieldBits::NoField != (ChildrenFieldMask & whichField))
    {
        _mfChildren.copyToBin(pMem);
    }

    if(FieldBits::NoField != (CoreFieldMask & whichField))
    {
        _sfCore.copyToBin(pMem);
    }
}

inline
void Node::copyFromBin(      BinaryDataHandler &pMem,
                       const BitVector         &whichField)
{
    Inherited::copyFromBin(pMem, whichField);

    if(FieldBits::NoField != (VolumeFieldMask & whichField))
    {
        _sfVolume.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (TravMaskFieldMask & whichField))
    {
        _sfTravMask.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (ParentFieldMask & whichField))
    {
        _sfParent.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (ChildrenFieldMask & whichField))
    {
        _mfChildren.copyFromBin(pMem);
    }

    if(FieldBits::NoField != (CoreFieldMask & whichField))
    {
        _sfCore.copyFromBin(pMem);
    }
}


/*-------------------------------------------------------------------------*/
/*                           MT Construction                               */

inline
void Node::setParent(const NodePtr &parent)
{
    _sfParent.setValue(parent);
}

/*-------------------------------------------------------------------------*/
/*                                Sync                                     */

#if !defined(OSG_FIXED_MFIELDSYNC)
inline
void Node::executeSyncImpl(      Node      *pOther,
                           const BitVector &whichField)
{
    Inherited::executeSyncImpl(pOther, whichField);

    if (FieldBits::NoField != (VolumeFieldMask & whichField))
    {
        _sfVolume.syncWith(pOther->_sfVolume);
    }

    if (FieldBits::NoField != (TravMaskFieldMask & whichField))
    {
        _sfTravMask.syncWith(pOther->_sfTravMask);
    }

    if (FieldBits::NoField != (ParentFieldMask & whichField))
    {
        _sfParent.syncWith(pOther->_sfParent);
    }

    if (FieldBits::NoField != (ChildrenFieldMask & whichField))
    {
        _mfChildren.syncWith(pOther->_mfChildren);
    }

    if (FieldBits::NoField != (CoreFieldMask & whichField))
    {
        _sfCore.syncWith(pOther->_sfCore);
    }
}

inline
void Node::executeSync(      FieldContainer &other,
                       const BitVector      &whichField)
{
    this->executeSyncImpl((Node *) &other, whichField);
}
#else
inline
void Node::executeSyncImpl(      Node      *pOther,
                           const BitVector &whichField,
                           const SyncInfo  &sInfo     )
{
    Inherited::executeSyncImpl(pOther, whichField, sInfo);

    if (FieldBits::NoField != (VolumeFieldMask & whichField))
    {
        _sfVolume.syncWith(pOther->_sfVolume);
    }

    if (FieldBits::NoField != (TravMaskFieldMask & whichField))
    {
        _sfTravMask.syncWith(pOther->_sfTravMask);
    }

    if (FieldBits::NoField != (ParentFieldMask & whichField))
    {
        _sfParent.syncWith(pOther->_sfParent);
    }

    if (FieldBits::NoField != (ChildrenFieldMask & whichField))
    {
        _mfChildren.syncWith(pOther->_mfChildren, sInfo);
    }

    if (FieldBits::NoField != (CoreFieldMask & whichField))
    {
        _sfCore.syncWith(pOther->_sfCore);
    }
}

inline
void Node::executeSync(      FieldContainer &other,
                       const BitVector      &whichField,
                       const SyncInfo       &sInfo     )
{
    this->executeSyncImpl((Node *) &other, whichField, sInfo);
}

inline
void Node::execBeginEditImpl (const BitVector &whichField, 
                                    UInt32     uiAspect,
                                    UInt32     uiContainerSize)
{
    Inherited::execBeginEditImpl(whichField, uiAspect, uiContainerSize);

    if (FieldBits::NoField != (ChildrenFieldMask & whichField))
    {
        _mfChildren.beginEdit(uiAspect, uiContainerSize);
    }
}

inline
void Node::execBeginEdit(const BitVector &whichField, 
                               UInt32     uiAspect,
                               UInt32     uiContainerSize) 
{
    this->execBeginEditImpl(whichField, uiAspect, uiContainerSize);
}


#endif

OSG_END_NAMESPACE

#define OSGNODE_INLINE_CVSID "@(#)$Id: $"

#endif /* _OSGNODEIMPL_INL_ */
