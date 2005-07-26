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

#ifndef _OSGFIELDCONTAINERIMPL_INL_
#define _OSGFIELDCONTAINERIMPL_INL_

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGFieldContainerImpl.inl
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
FieldContainerType &FieldContainer::getClassType(void)
{
    return _type;
}

inline
UInt32 FieldContainer::getClassTypeId(void)
{
    return _type.getId();
}

inline
UInt16 FieldContainer::getClassGroupId(void)
{
    return _type.getGroupId();
}

inline
UInt32 FieldContainer::getTypeId(void) const
{
    return getType().getId();
}

inline
UInt16 FieldContainer::getGroupId(void) const
{
    return getType().getGroupId();
}

inline
const Char8 *FieldContainer::getTypeName(void) const
{
    return getType().getCName();
}

inline
Field *FieldContainer::getField(UInt32 fieldId)
{
    const FieldDescription *desc = getType().getFieldDescription(fieldId);

    return desc ? desc->getField(*this) : NULL;
}

inline
Field *FieldContainer::getField(const Char8 *fieldName)
{
    const FieldDescription *desc =getType().findFieldDescription(fieldName);

    return desc ? desc->getField(*this) : NULL;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

inline
FieldContainer::FieldContainer(void) :
    _shares(0)
{
}

inline
FieldContainer::FieldContainer(const FieldContainer &) :
    _shares(0)

{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

inline
FieldContainer::~FieldContainer(void)
{
}

/*-------------------------------------------------------------------------*/
/*                         Create Fieldcontainer                           */

template <class ObjectPtrT> inline
void FieldContainer::newPtr(      
                   ObjectPtrT                   &result, 
    const typename ObjectPtrT::StoredObjectType *prototypeP)
{
    typedef typename ObjectPtrT::StoredObjectType ObjectType;
    
    UInt8 *pTmp;
    
    result._containerSize = sizeof(ObjectType);
    
    pTmp        = 
        static_cast<UInt8 *>(operator new(
            sizeof(Int32)      + // ReferenceCount
            sizeof(UInt32)     + // ContainerId
            sizeof(ObjectType) * ThreadManager::getNumAspects()));
    
    *(reinterpret_cast<Int32 *>(pTmp)) = 0;
    
    pTmp += sizeof(Int32);
    
    result._storeP = (pTmp + sizeof(UInt32));

#ifdef OSG_DEBUG_FCPTR
    result._typedStoreP = reinterpret_cast<FieldContainer *>(result._storeP);
#endif

    *(reinterpret_cast<UInt32 *>(pTmp)) = 
        FieldContainerFactory::the()->registerFieldContainer(result);
    
    Thread::getCurrentChangeList()->addCreated(
        *(reinterpret_cast<UInt32 *>(pTmp)));
    
    pTmp += sizeof(UInt32);
    
    ObjectType *aObject = reinterpret_cast<ObjectType *>(pTmp);

    for(UInt32 i = 0; i < ThreadManager::getNumAspects(); i++)
    {
        pTmp = 
            reinterpret_cast<UInt8 *>(new (pTmp) ObjectType(*prototypeP));
        
        pTmp += sizeof(ObjectType);
    }
    
    result->onCreate(prototypeP);

    for(UInt32 i = 0; i < ThreadManager::getNumAspects(); i++)
    {
        aObject[i].onCreateAspect(aObject, prototypeP);
    }

#if defined(OSG_GV_BETA) && defined(OSG_DBG_MEM)

    fprintf(stderr, "GV_MEM_FC_DBG : (%u) cc (%p|%u)\n", 
            Thread::getAspect(),
            result._storeP,
//            ObjectType::getClassType().getCName(),
            ObjectType::getClassType().getId());
#endif

#ifdef OSG_DEBUG_TYPED_FCPTR
    result.updateTypedStore();
#endif
}

template <class ObjectPtrT> inline
void FieldContainer::newPtr(ObjectPtrT &result)
{
    typedef typename ObjectPtrT::StoredObjectType ObjectType;
    
    UInt8 *pTmp;
    
    result._containerSize = sizeof(ObjectType);
    
    pTmp        =             
        static_cast<UInt8 *>(operator new(
            sizeof(Int32)      + // ReferenceCount
            sizeof(UInt32)     + // ContainerId
            sizeof(ObjectType) * ThreadManager::getNumAspects()));
    
    *(reinterpret_cast<Int32 *>(pTmp)) = 0;
    
    pTmp  += sizeof(Int32);
    
    result._storeP = (pTmp + sizeof(UInt32));
    
#ifdef OSG_DEBUG_FCPTR
    result._typedStoreP = reinterpret_cast<FieldContainer *>(result._storeP);
#endif

    *(reinterpret_cast<UInt32 *>(pTmp)) = 
        FieldContainerFactory::the()->registerFieldContainer(result);
    
    Thread::getCurrentChangeList()->addCreated(
        *(reinterpret_cast<UInt32 *>(pTmp)));
    
    pTmp += sizeof(UInt32);
    
    ObjectType *aObject = reinterpret_cast<ObjectType *>(pTmp);

    for(UInt32 i = 0; i < ThreadManager::getNumAspects(); i++)
    {
        pTmp = reinterpret_cast<UInt8 *>(new (pTmp) ObjectType());
        
        pTmp += sizeof(ObjectType);
    }
    
    result->onCreate();
    
    for(UInt32 i = 0; i < ThreadManager::getNumAspects(); i++)
    {
        aObject[i].onCreateAspect(aObject);
    }

#if defined(OSG_GV_BETA) && defined(OSG_DBG_MEM)
    fprintf(stderr, "GV_MEM_FC_DBG : (%u) c (%p|%u)\n", 
            Thread::getAspect(),
            result._storeP,
//            ObjectType::getClassType().getCName(),
            ObjectType::getClassType().getId());
#endif
    
#ifdef OSG_DEBUG_TYPED_FCPTR
    result.updateTypedStore();
#endif
}

/*
    template <class T>
    static T getPtr(const typename T::ObjectType &object)
    {
        T returnValue(object); 
        return returnValue; 
    }

    template <class T>
    static T getPtr(const typename T::ObjectType &object) 
    {
        T returnValue(object); 
        return returnValue; 
    }
*/

/*-------------------------------------------------------------------------*/
/*                               MT Edit                                   */

template<class FieldTypeT> inline
void FieldContainer::beginEditX(const BitVector &, FieldTypeT &)
{
//    fieldR.beginEdit();
}

template<class FieldTypeT> inline
void FieldContainer::endEditX(const BitVector &whichField, FieldTypeT &)
{
    FieldContainerPtr tmpPtr(this);
    endEditCP(tmpPtr, whichField);
}

/*
template <class FieldTypeT>
void beginEdit(const BitVector  &,
                     FieldTypeT &fieldR)
{
    fieldR.beginEdit();
}

template <class FieldTypeT>
void endEdit(const BitVector  &whichField,
                   FieldTypeT &)
{
    FieldContainerPtr tmpPtr(this);
    endEditCP(tmpPtr, whichField);
}
*/

/*-------------------------------------------------------------------------*/
/*                             MT Contruction                              */

inline
void FieldContainer::onCreate(const FieldContainer *)
{
}

inline
void FieldContainer::onCreateAspect(const FieldContainer *, 
                                    const FieldContainer *)
{
}

/*-------------------------------------------------------------------------*/
/*                                Sync                                     */

#if !defined(OSG_FIXED_MFIELDSYNC)
inline
void FieldContainer::executeSyncImpl(      FieldContainer *,
                                     const BitVector      &)
{
}
#else
inline
void FieldContainer::executeSyncImpl(      FieldContainer *,
                                     const BitVector      &,
                                     const SyncInfo       &)
{
}

inline
void FieldContainer::execBeginEditImpl (const BitVector &whichField, 
                                              UInt32     uiAspect,
                                              UInt32     uiContainerSize)
{
}

#endif

OSG_END_NAMESPACE

#define OSGFIELDCONTAINER_INLINE_CVSID "@(#)$Id: $"

#endif /* _OSGFIELDCONTAINERIMPL_INL_ */


