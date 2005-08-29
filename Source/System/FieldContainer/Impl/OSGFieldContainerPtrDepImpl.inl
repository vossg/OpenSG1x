/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000-2002,2002 by the OpenSG Forum                *
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

#ifndef _OSGFIELDCONTAINERPTRDEPIMPL_INL_
#define _OSGFIELDCONTAINERPTRDEPIMPL_INL_

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGFieldContainerPtrDepImpl.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

template <class BasePtrTypeT, class FieldContainerTypeT> inline
std::ostream &operator <<(
          std::ostream                             &os,
    const FCPtr<BasePtrTypeT, FieldContainerTypeT> &fc)
{
    if(fc == NullFC)
    {
        os << std::hex << "FCPtr 0x" << &fc << std::dec << ":NullFC";
    }
    else
    {
        os << std::hex 
           << "FCPtr 0x"
           << &fc 
           << std::dec 
           << ":" 
           << fc->getType().getName() 
           << "Ptr(0x"
           << std::hex 
           << (&(*fc)) 
           << std::dec 
           << ")";
    }

    return os;
}

inline
void FieldContainerPtrBase::deleteContainers(void) const
{
//    dump(0, FCDumpFlags::RefCount);

    Thread::getCurrentChangeList()->addDestroyed(*getIdP());
    
    if (FieldContainerFactory::the()->unregisterFieldContainer(
            *((const FieldContainerPtr *) this)))
    {
        return;
    }
    
    UInt8 *pTmp = getFirstElemP();
    
    ((FieldContainer *) pTmp)->onDestroy();
    
#if defined(OSG_GV_BETA) && defined(OSG_DBG_MEM)

    fprintf(stderr, "GV_MEM_FC_DBG : (%u) d (%p|%u)\n", 
            Thread::getAspect(),
            pTmp,
//            ((FieldContainer *) pTmp)->getType().getCName(),
            ((FieldContainer *) pTmp)->getType().getId());
#endif
 
#if defined(OSG_FIXED_MFIELDSYNC)
    ((FieldContainer *) pTmp)->~FieldContainer();
#endif
   
    for(UInt32 i = 0; i < ThreadManager::getNumAspects(); i++)
    {
#if defined(OSG_FIXED_MFIELDSYNC)
        ((FieldContainer *) pTmp)->onDestroyAspect(*(getIdP()), i);
#endif

#if !defined(OSG_FIXED_MFIELDSYNC)
        ((FieldContainer *) pTmp)->~FieldContainer();
#endif

        pTmp += _containerSize;
    }
    
    operator delete(_storeP + getRefCountOff());
}

inline
void FieldContainerPtrBase::subRef(void) const
{
#if !defined(OSG_FIXED_MFIELDSYNC)
    _pRefCountLock->aquire(_storeP);

    (*getRefCountP())--;

    if((*getRefCountP()) <= 0)
    {
        _pRefCountLock->release(_storeP);

        deleteContainers();
        
         // Clean up a little.
        const_cast<FieldContainerPtrBase*>(this)->_storeP = NULL;
    }
    else
    {
        _pRefCountLock->release(_storeP);

        Thread::getCurrentChangeList()->addSubRefd(
            *(static_cast<const FieldContainerPtr *>(this)));
    }
#else
    Thread::getCurrentChangeList()->addSubRefd(
        *(static_cast<const FieldContainerPtr *>(this)));
#endif
}

#if defined(OSG_FIXED_MFIELDSYNC)
inline
void FieldContainerPtrBase::doSubRef(void) const
{
    _pRefCountLock->aquire(_storeP);

    (*getRefCountP())--;

    if((*getRefCountP()) <= 0)
    {
        _pRefCountLock->release(_storeP);

        deleteContainers();
    }
    else
    {
        _pRefCountLock->release(_storeP);
    }
}
#endif

OSG_END_NAMESPACE

#define OSGFIELDCONTAINERPTRDEPIMPL_INLINE_CVSID "@(#)$Id: $"

#endif /* _OSGFIELDCONTAINERPTRDEPIMPL_INL_ */
