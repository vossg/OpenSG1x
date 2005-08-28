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

#ifndef _OSGFIELDCONTAINERPTRIMPL_INL_
#define _OSGFIELDCONTAINERPTRIMPL_INL_

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGFieldContainerPtrImpl.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------


/*-------------------------------------------------------------------------*/
/*                         Get Memory Locations                            */

inline
Int32 *FieldContainerPtrBase::getRefCountP(void)
{
    return (Int32 *) (_storeP - sizeof(Int32) - sizeof(UInt32));
}

inline
Int32 *FieldContainerPtrBase::getRefCountP(void) const
{
    return (Int32 *) (_storeP - sizeof(Int32) - sizeof(UInt32));
}

inline
UInt32 *FieldContainerPtrBase::getIdP(void)
{
    return (UInt32 *) (_storeP - sizeof(UInt32));
}

inline
UInt32 *FieldContainerPtrBase::getIdP(void) const
{
    return (UInt32 *) (_storeP - sizeof(UInt32));
}

inline
UInt8 *FieldContainerPtrBase::getElemP(UInt32 uiElemNum)
{
    return (_storeP + (_containerSize * uiElemNum));
}

inline
UInt8 *FieldContainerPtrBase::getElemP(UInt32 uiElemNum) const
{
    return (_storeP + (_containerSize * uiElemNum));
}

inline
UInt8 *FieldContainerPtrBase::getFirstElemP(void)
{
    return _storeP;
}

inline
UInt8 *FieldContainerPtrBase::getFirstElemP(void) const
{
    return _storeP;
}

/*-------------------------------------------------------------------------*/
/*                         Get Memory Offsets                              */

inline
Int32  FieldContainerPtrBase::getRefCountOff(void) const
{
    return -Int32((sizeof(Int32) + sizeof(UInt32)));
}

inline
Int32  FieldContainerPtrBase::getIdOff(void) const
{
    return -Int32(sizeof(UInt32));
}

inline
Int32  FieldContainerPtrBase::getFirstElemOff(void) const
{
    return 0;
}

inline
Int32  FieldContainerPtrBase::getElemOff(UInt32 uiElemNum) const
{
    return (_containerSize * uiElemNum);
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */


inline 
FieldContainerPtrBase::FieldContainerPtrBase(void) :
    _containerSize(0               ),
    _uiParentEPos(InvalidParentEPos),
    _storeP      (NULL             ) 
{
#ifdef OSG_DEBUG_FCPTR
    _typedStoreP = reinterpret_cast<FieldContainer *>(getFirstElemP());
#endif
}

inline
FieldContainerPtrBase::FieldContainerPtrBase(
    const NullFieldContainerPtr &) :

    _containerSize(0                ),
    _uiParentEPos (InvalidParentEPos),
    _storeP       (NULL             )
{
#ifdef OSG_DEBUG_FCPTR
    _typedStoreP = reinterpret_cast<FieldContainer *>(getFirstElemP());
#endif
}

inline
FieldContainerPtrBase::FieldContainerPtrBase(
    const FieldContainerPtrBase &source) :

    _containerSize(source._containerSize),
    _uiParentEPos (source._uiParentEPos ),
    _storeP       (source._storeP       )
{
#ifdef OSG_DEBUG_FCPTR
    _typedStoreP = reinterpret_cast<FieldContainer *>(getFirstElemP());
#endif
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

inline
FieldContainerPtrBase::~FieldContainerPtrBase(void)
{
#ifdef OSG_DEBUG
    _storeP = NULL;
    _containerSize = 65535;
    _uiParentEPos = 65535;
#ifdef OSG_DEBUG_FCPTR
    _typedStoreP = NULL;
#endif
#endif
}

/*-------------------------------------------------------------------------*/
/*                         Parent Field Pos                                */

inline
void FieldContainerPtrBase::setParentFieldPos(UInt16 uiParentEPos)
{
    _uiParentEPos = uiParentEPos;
}

inline
UInt16 FieldContainerPtrBase::getParentFieldPos(void) const
{
    return _uiParentEPos;
}

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

inline
Int32 FieldContainerPtrBase::getRefCount(void) const
{
    if(_storeP == NULL)
        return 0;
        
    return (*getRefCountP());
}

inline
UInt32 FieldContainerPtrBase::getFieldContainerId(void) const
{
    return (*getIdP());
}

inline
UInt16 FieldContainerPtrBase::getContainerSize(void) const
{
    return _containerSize;
}

inline
FieldContainer *FieldContainerPtrBase::getBaseCPtr(void) const
{
    return reinterpret_cast<FieldContainer *>(getFirstElemP());
}

inline
FieldContainer *FieldContainerPtrBase::getAspectCPtr(UInt32 uiAspectId) const
{
    return reinterpret_cast<FieldContainer *>(getElemP(uiAspectId));
}
/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

inline
void FieldContainerPtrBase::operator =(const NullFieldContainerPtr &)
{
    _containerSize = 0;
    _uiParentEPos  = InvalidParentEPos;
    _storeP        = NULL;

#ifdef OSG_DEBUG_FCPTR
    _typedStoreP   = NULL;
#endif
}

inline
void FieldContainerPtrBase::operator =(const FieldContainerPtrBase &source)
{
    if (this == &source)
        return;

    _containerSize = source._containerSize;
    _uiParentEPos  = source._uiParentEPos;
    _storeP        = source._storeP;

#ifdef OSG_DEBUG_FCPTR
    _typedStoreP   = reinterpret_cast<FieldContainer *>(getFirstElemP());
#endif
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

inline
bool FieldContainerPtrBase::operator < (
    const NullFieldContainerPtr &) const
{
    return false;
}

inline
bool FieldContainerPtrBase::operator ==(
    const NullFieldContainerPtr &) const
{
    return _storeP == NULL;
}

inline
bool FieldContainerPtrBase::operator !=(
    const NullFieldContainerPtr &) const
{
    return _storeP != NULL;
}


inline
bool FieldContainerPtrBase::operator < (
    const FieldContainerPtrBase &other)const
{
    return _storeP < other._storeP;
}

inline
bool FieldContainerPtrBase::operator ==(
    const FieldContainerPtrBase &other) const
{
    return _storeP == other._storeP;
}

inline
bool FieldContainerPtrBase::operator !=(
    const FieldContainerPtrBase &other) const
{
    return ! (*this == other);
}

inline
bool FieldContainerPtrBase::operator ! (void) const
{
    return _storeP == NULL;
}

inline
FieldContainerPtrBase::operator FieldContainerPtrBase::unspecified_bool_type() const
{
    return !*this ? 0 : &FieldContainerPtrBase::_storeP;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

inline
FieldContainerPtrBase::FieldContainerPtrBase(const FieldContainer *source,
                                             const UInt16         uiSize,
                                             const UInt16         uiParentEPos)
{
    _uiParentEPos  = uiParentEPos;
    _containerSize = uiSize;

    if(source != NULL)
    {
        _storeP  = (UInt8 *) (const_cast<FieldContainer *>(source));
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
        _storeP -= getElemOff(Thread::getAspect());
#endif
    }
    else
    {
        _storeP  = NULL;
    }

#ifdef OSG_DEBUG_FCPTR
    _typedStoreP = reinterpret_cast<FieldContainer *>(getFirstElemP());
#endif
}

/*-------------------------------------------------------------------------*/
/*                                Sync                                     */


/*-------------------------------------------------------------------------*/
/*                               Some ptr stuff                            */

inline
FieldContainerPtrBase::FieldContainerPtrBase(const FieldContainer &source)
{
    _containerSize   = source.getContainerSize();
    _uiParentEPos    = InvalidParentEPos;
    _storeP          = (UInt8 *) (const_cast<FieldContainer *>(&source));
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    _storeP         -= getElemOff(Thread::getAspect());
#endif

#ifdef OSG_DEBUG_FCPTR
    _typedStoreP     = reinterpret_cast<FieldContainer *>(getFirstElemP());
#endif
}

inline
FieldContainerPtrBase::FieldContainerPtrBase(const FieldContainer *source)
{
    _uiParentEPos    = InvalidParentEPos;

    if(source != NULL)
    {
        _containerSize = source->getContainerSize();
        _storeP          = (UInt8 *) (const_cast<FieldContainer *>(source));
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
        _storeP         -= getElemOff(Thread::getAspect());
#endif
    }
    else
    {
        _containerSize = 0;
        _storeP          = NULL;
    }

#ifdef OSG_DEBUG_FCPTR
    _typedStoreP = reinterpret_cast<FieldContainer *>(getFirstElemP());
#endif
}

/*-------------------------------------------------------------------------*/
/*                           Reference Counting                            */

inline
void FieldContainerPtrBase::addRef(void) const
{
    _pRefCountLock->aquire(_storeP);

    (*getRefCountP())++;

    _pRefCountLock->release(_storeP);

    Thread::getCurrentChangeList()->addAddRefd(
        *(static_cast<const FieldContainerPtr *>(this)));
}

inline
void FieldContainerPtrBase::setNull(void)
{
    _containerSize = 0;
    _uiParentEPos  = InvalidParentEPos;
    _storeP        = NULL;

#ifdef OSG_DEBUG_FCPTR
    _typedStoreP = reinterpret_cast<FieldContainer *>(getFirstElemP());
#endif
}


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------


/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

inline
FieldContainerPtr::FieldContainerPtr(void) :
    Inherited()
{
}

inline
FieldContainerPtr::FieldContainerPtr(const NullFieldContainerPtr &) :
    Inherited()
{
}

inline
FieldContainerPtr::FieldContainerPtr(const FieldContainerPtr &source) :
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

inline
FieldContainerPtr::~FieldContainerPtr(void)
{
}

/*-------------------------------------------------------------------------*/
/*                        Container Access                                 */

inline
FieldContainer *FieldContainerPtr::operator->(void)
{
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return (FieldContainer *) (getElemP(Thread::getAspect()));
#else
    return (FieldContainer *) (getFirstElemP());
#endif
}

inline
FieldContainer *FieldContainerPtr::operator->(void) const
{
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return (FieldContainer *) (getElemP(Thread::getAspect()));
#else
    return (FieldContainer *) (getFirstElemP());
#endif
}

inline
FieldContainer &FieldContainerPtr::operator *(void)
{ 
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return *((FieldContainer *) (getElemP(Thread::getAspect())));
#else
    return *((FieldContainer *) (getFirstElemP()));
#endif
}

inline
FieldContainer &FieldContainerPtr::operator *(void) const
{
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return *((FieldContainer *) (getElemP(Thread::getAspect())));
#else
    return *((FieldContainer *) (getFirstElemP()));
#endif
}

inline
FieldContainer *FieldContainerPtr::getCPtr(void)
{
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return (FieldContainer *) (getElemP(Thread::getAspect()));
#else
    return (FieldContainer *) (getFirstElemP());
#endif
}

inline
FieldContainer *FieldContainerPtr::getCPtr(void) const
{
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return (FieldContainer *) (getElemP(Thread::getAspect()));
#else
    return (FieldContainer *) (getFirstElemP());
#endif
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

inline
void FieldContainerPtr::operator =(const NullFieldContainerPtr &)
{
    setNull();
}

inline
void FieldContainerPtr::operator =(const FieldContainerPtr &source)
{
    *(static_cast<Inherited *>(this)) = source;
}

/*-------------------------------------------------------------------------*/
/*                             MT Edit                                     */

#ifdef OSG_FIXED_MFIELDSYNC 
inline
void FieldContainerPtr::beginEdit(BitVector whichField,
                                  UInt32    OSG_CHECK_ARG(origin)) const
{
    (*this)->execBeginEdit(whichField,
                           Thread::getAspect(), 
                           getContainerSize());
}
#else
inline
void FieldContainerPtr::beginEdit(BitVector OSG_CHECK_ARG(whichField),
                                  UInt32    OSG_CHECK_ARG(origin)) const
{
}
#endif

inline
void FieldContainerPtr::endEditNotChanged(BitVector whichField,
                                          UInt32              ) const
{
    Thread::getCurrentChangeList()->addChanged(*this, whichField);
}

inline
void FieldContainerPtr::changed(BitVector whichField, UInt32 origin) const
{
    (*this)->changed(whichField, origin);
}

inline
void FieldContainerPtr::endEdit(BitVector whichField, UInt32 origin) const
{
    endEditNotChanged(whichField, origin);
    changed(whichField, origin);
}


/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

inline
FieldContainerPtr::FieldContainerPtr(const FieldContainer &source) :
    Inherited(source)
{
}

inline
FieldContainerPtr::FieldContainerPtr(const FieldContainer *source) :
    Inherited(source)
{
}

inline
FieldContainerPtr::FieldContainerPtr(const FieldContainer *source,
                                     const UInt16          uiSize,
                                     const UInt16          uiParentEPos) :
    Inherited(source, uiSize, uiParentEPos)
{
}



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

inline
ConstFieldContainerPtr::ConstFieldContainerPtr(void) :
    Inherited()
{
}

inline
ConstFieldContainerPtr::ConstFieldContainerPtr(
    const NullFieldContainerPtr &) :
    Inherited()
{
}

inline
ConstFieldContainerPtr::ConstFieldContainerPtr(
    const FieldContainerPtr &source) :
    Inherited(source)
{
}

inline
ConstFieldContainerPtr::ConstFieldContainerPtr(
    const ConstFieldContainerPtr &source):
    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

inline
ConstFieldContainerPtr::~ConstFieldContainerPtr(void)
{
}

/*-------------------------------------------------------------------------*/
/*                           Container Access                              */

inline
const FieldContainer *ConstFieldContainerPtr::operator->(void)
{
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return (const FieldContainer *) (getElemP(Thread::getAspect()));
#else
    return (const FieldContainer *) (getFirstElemP());
#endif
}

inline
const FieldContainer *ConstFieldContainerPtr::operator->(void) const
{
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return (const FieldContainer *) (getElemP(Thread::getAspect()));
#else
    return (const FieldContainer *) (getFirstElemP());
#endif
}

inline
const FieldContainer &ConstFieldContainerPtr::operator *(void)
{
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return *((const FieldContainer *) (getElemP(Thread::getAspect())));
#else
    return *((const FieldContainer *) (getFirstElemP()));
#endif
}

inline
const FieldContainer &ConstFieldContainerPtr::operator *(void) const
{
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return *((const FieldContainer *) (getElemP(Thread::getAspect())));
#else
    return *((const FieldContainer *) (getFirstElemP()));
#endif
}

inline
const FieldContainer *ConstFieldContainerPtr::getCPtr(void)
{
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return (const FieldContainer *) (getElemP(Thread::getAspect()));
#else
    return (const FieldContainer *) (getFirstElemP());
#endif
}

inline
const FieldContainer *ConstFieldContainerPtr::getCPtr(void) const
{
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return (const FieldContainer *) (getElemP(Thread::getAspect()));
#else
    return (const FieldContainer *) (getFirstElemP());
#endif
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

inline
void ConstFieldContainerPtr::operator =(const NullFieldContainerPtr &)
{
    setNull();
}

inline
void ConstFieldContainerPtr::operator =(const FieldContainerPtr &source)
{
    *(static_cast<Inherited *>(this)) = source;
}

inline
void ConstFieldContainerPtr::operator =(const ConstFieldContainerPtr &source)
{
    *(static_cast<Inherited *>(this)) = source;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

inline
ConstFieldContainerPtr::ConstFieldContainerPtr(const FieldContainer &source) :
    Inherited(source)
{
}

inline
ConstFieldContainerPtr::ConstFieldContainerPtr(const FieldContainer *source) :
    Inherited(source)
{
}

inline
ConstFieldContainerPtr::ConstFieldContainerPtr(
    const FieldContainer *source,
    const UInt16          uiSize,
    const UInt16          uiParentEPos) :

    Inherited(source, uiSize, uiParentEPos)
{
}


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

inline
NullFieldContainerPtr::NullFieldContainerPtr(void) : 
    Inherited()
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

inline
NullFieldContainerPtr::~NullFieldContainerPtr(void)
{
}



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FCPtr<BasePtrTypeT, FieldContainerTypeT>::FCPtr(void) :
    Inherited()
{
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FCPtr<BasePtrTypeT, FieldContainerTypeT>::FCPtr(const FCPtr &source):
    Inherited(source)
{
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FCPtr<BasePtrTypeT, 
      FieldContainerTypeT>::FCPtr(const NullFieldContainerPtr &) :

    Inherited()
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FCPtr<BasePtrTypeT, FieldContainerTypeT>::~FCPtr(void)
{
}

/*-------------------------------------------------------------------------*/
/*                            Container Access                             */

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FieldContainerTypeT *FCPtr<BasePtrTypeT, 
                           FieldContainerTypeT>::operator ->(void)
{
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return (FieldContainerTypeT *) Self::getElemP(Thread::getAspect());
#else
    return (FieldContainerTypeT *) Self::getFirstElemP();
#endif
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FieldContainerTypeT *FCPtr<BasePtrTypeT,
                            FieldContainerTypeT>::operator ->(void) const
{
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return (FieldContainerTypeT *) Self::getElemP(Thread::getAspect());
#else
    return (FieldContainerTypeT *) Self::getFirstElemP();
#endif
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FieldContainerTypeT &FCPtr<BasePtrTypeT, 
                           FieldContainerTypeT>::operator *(void)
{
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return *((FieldContainerTypeT *) Self::getElemP(Thread::getAspect()));
#else
    return *((FieldContainerTypeT *) Self::getFirstElemP());
#endif
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FieldContainerTypeT &FCPtr<BasePtrTypeT,
                            FieldContainerTypeT>::operator *(void) const
{
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return *((FieldContainerTypeT *) Self::getElemP(Thread::getAspect()));
#else
    return *((FieldContainerTypeT *) Self::getFirstElemP());
#endif
}


template <class BasePtrTypeT, class FieldContainerTypeT> inline
FieldContainerTypeT *FCPtr<BasePtrTypeT, FieldContainerTypeT>::getCPtr(void)

{
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return (FieldContainerTypeT *) Self::getElemP(Thread::getAspect());
#else
    return (FieldContainerTypeT *) Self::getFirstElemP();
#endif
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FieldContainerTypeT *
    FCPtr<BasePtrTypeT, FieldContainerTypeT>::getCPtr(void) const
{
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return (FieldContainerTypeT *) Self::getElemP(Thread::getAspect());
#else
    return (FieldContainerTypeT *) Self::getFirstElemP();
#endif
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

template <class BasePtrTypeT, class FieldContainerTypeT> inline
void FCPtr<BasePtrTypeT, 
           FieldContainerTypeT>::operator = (const FCPtr &source)
{
    // copy parts inherited from parent
    *(static_cast<Inherited *>(this)) = source;
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
void FCPtr<BasePtrTypeT, FieldContainerTypeT>::operator = (
    const NullFieldContainerPtr &)
{
    Self::setNull();
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FCPtr<BasePtrTypeT, 
      FieldContainerTypeT>::FCPtr(const FieldContainerTypeT &source) :

    Inherited(source)
{
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FCPtr<BasePtrTypeT, 
      FieldContainerTypeT>::FCPtr(const FieldContainerTypeT *source) :

    Inherited(source)
{
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FCPtr<BasePtrTypeT, 
      FieldContainerTypeT>::FCPtr(const FieldContainerTypeT *source,
                                  const UInt16               uiSize,
                                  const UInt16               uiParentEPos) :

    Inherited(source, uiSize, uiParentEPos)
{
}




//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class BasePtrTypeT, class FieldContainerTypeT> inline
ConstFCPtr<BasePtrTypeT, FieldContainerTypeT>::ConstFCPtr(void) :
    Inherited()
{
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
ConstFCPtr<BasePtrTypeT, 
           FieldContainerTypeT>::ConstFCPtr(
               const NullFieldContainerPtr &) :

    Inherited()
{
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
ConstFCPtr<BasePtrTypeT, 
           FieldContainerTypeT>::ConstFCPtr(const NCFCPtr &source) :

    Inherited(source)
{
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
ConstFCPtr<BasePtrTypeT, 
           FieldContainerTypeT>::ConstFCPtr(const ConstFCPtr &source) :

    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

template <class BasePtrTypeT, class FieldContainerTypeT> inline
ConstFCPtr<BasePtrTypeT, FieldContainerTypeT>::~ConstFCPtr(void)
{
}

/*-------------------------------------------------------------------------*/
/*                        Container Access                                 */

template <class BasePtrTypeT, class FieldContainerTypeT> inline
const FieldContainerTypeT *ConstFCPtr<BasePtrTypeT,
                                      FieldContainerTypeT>::operator ->(void)
{
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return (const FieldContainerTypeT *) Self::getElemP(Thread::getAspect());
#else
    return (const FieldContainerTypeT *) Self::getFirstElemP();
#endif
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
const FieldContainerTypeT *ConstFCPtr<BasePtrTypeT,
                                      FieldContainerTypeT>::operator ->(
                                           void) const
{
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return (const FieldContainerTypeT *) Self::getElemP(Thread::getAspect());
#else
    return (const FieldContainerTypeT *) Self::getFirstElemP();
#endif
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
const FieldContainerTypeT &ConstFCPtr<BasePtrTypeT,
                                      FieldContainerTypeT>::operator *(void)
{
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
   return *((const FieldContainerTypeT *) Self::getElemP(Thread::getAspect()));
#else
   return *((const FieldContainerTypeT *) Self::getFirstElemP());
#endif
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
const FieldContainerTypeT &ConstFCPtr<BasePtrTypeT,
                                      FieldContainerTypeT>::operator *(
                                           void) const
{
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
   return *((const FieldContainerTypeT *) Self::getElemP(Thread::getAspect()));
#else
   return *((const FieldContainerTypeT *) Self::getFirstElemP());
#endif
}


template <class BasePtrTypeT, class FieldContainerTypeT> inline
const FieldContainerTypeT *ConstFCPtr<BasePtrTypeT,
                                      FieldContainerTypeT>::getCPtr(void)

{
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return (const FieldContainerTypeT *) Self::getElemP(Thread::getAspect());
#else
    return (const FieldContainerTypeT *) Self::getFirstElemP();
#endif
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
const FieldContainerTypeT *
    ConstFCPtr<BasePtrTypeT, FieldContainerTypeT>::getCPtr(void) const
{
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return (const FieldContainerTypeT *) Self::getElemP(Thread::getAspect());
#else
    return (const FieldContainerTypeT *) Self::getFirstElemP();
#endif
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

template <class BasePtrTypeT, class FieldContainerTypeT> inline
void ConstFCPtr<BasePtrTypeT, 
                FieldContainerTypeT>::operator = (const NCFCPtr &source)
{
    // copy parts inherited from parent
    *(static_cast<Inherited *>(this)) = source;
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
void ConstFCPtr<BasePtrTypeT, 
                FieldContainerTypeT>::operator = (const ConstFCPtr &source)
{
    // copy parts inherited from parent
    *(static_cast<Inherited *>(this)) = source;
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
void ConstFCPtr<BasePtrTypeT, FieldContainerTypeT>::operator = (
    const NullFieldContainerPtr &)
{
    Self::setNull();
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class BasePtrTypeT, class FieldContainerTypeT> inline
ConstFCPtr<BasePtrTypeT, 
           FieldContainerTypeT>::ConstFCPtr(const FieldContainerTypeT &source):

    Inherited(source)
{
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
ConstFCPtr<BasePtrTypeT, 
           FieldContainerTypeT>::ConstFCPtr(const FieldContainerTypeT *source):

    Inherited(source)
{
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
ConstFCPtr<BasePtrTypeT, FieldContainerTypeT>::ConstFCPtr(
    const FieldContainerTypeT *source,
    const UInt16               uiSize,
    const UInt16               uiParentEPos) :

    Inherited(source, uiSize, uiParentEPos)
{
}

#if 0
#ifdef __sgi
#pragma set woff 1424
#endif

template <class RetTypeT, class InTypeT> inline
RetTypeT dcast(const InTypeT oIn)
{
    return RetTypeT(
        (dynamic_cast<const typename RetTypeT::ObjectType *>(oIn.getCPtr())),
        oIn.getContainerSize,
        oIn.getParentFieldPos);
}

template <class RetTypeT, class InTypeT> inline
RetTypeT dyncast(const InTypeT oIn)
{
    return RetTypeT(
        (dynamic_cast<const typename RetTypeT::ObjectType *>(oIn.getCPtr())),
        oIn._containerSize,
        oIn._uiParentEPos);
}

#ifdef __sgi
#pragma reset woff 1424
#endif
#endif

inline
void FieldContainerPtrBase::executeSync(UInt32    uiFromAspect,
                                        UInt32    uiToAspect,
                                        BitVector whichField)
{
#if defined(OSG_FIXED_MFIELDSYNC)
    SyncInfo sInfo;

    sInfo.syncMode     = 0x0000;
    sInfo.uiSyncInfo   = (uiFromAspect << 24) | (uiToAspect << 16);
    sInfo.uiCopyOffset = getContainerSize();
#endif

    FieldContainer *pTo = ((FieldContainer *) getElemP(uiToAspect));
    
#if !defined(OSG_FIXED_MFIELDSYNC)
    pTo->executeSync(*((FieldContainer *) getElemP(uiFromAspect)), 
                     whichField);
#else
    pTo->executeSync(*((FieldContainer *) getElemP(uiFromAspect)), 
                     whichField,
                     sInfo);
#endif

    pTo->changed(whichField, ChangedOrigin::Sync);
}

// CPEditor definition
inline
CPEditor::CPEditor(void) : 
    _fc  (NullFC), 
    _mask(      0)
{
}
    
inline
CPEditor::CPEditor(const FieldContainerPtr fc, const BitVector mask) :
    _fc  (fc  ), 
    _mask(mask)
{
    beginEditCP(fc, mask);
}
    
inline
CPEditor::~CPEditor()
{
    if(_fc != NullFC)
        endEditCP(_fc, _mask);
}

OSG_END_NAMESPACE

#define OSGFIELDCONTAINERPTR_INLINE_CVSID "@(#)$Id: $"

#endif /* _OSGFIELDCONTAINERPTRIMPL_INL_ */
