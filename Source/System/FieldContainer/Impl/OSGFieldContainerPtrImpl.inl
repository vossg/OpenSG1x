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

#ifdef OSG_INVALID_PTR_CHECK
#include "OSGFieldContainerFactoryImpl.h"
#endif

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
    return reinterpret_cast<Int32 *>(_storeP - sizeof(Int32) - sizeof(UInt32));
}

inline
Int32 *FieldContainerPtrBase::getRefCountP(void) const
{
    return reinterpret_cast<Int32 *>(_storeP - sizeof(Int32) - sizeof(UInt32));
}

inline
UInt32 *FieldContainerPtrBase::getIdP(void)
{
    return reinterpret_cast<UInt32 *>(_storeP - sizeof(UInt32));
}

inline
UInt32 *FieldContainerPtrBase::getIdP(void) const
{
    return reinterpret_cast<UInt32 *>(_storeP - sizeof(UInt32));
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
#ifdef OSG_DEBUG_FCPTR
    , _typedStoreP(NULL)
#endif
#ifdef OSG_INVALID_PTR_CHECK
    , _id(0)
#endif
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
#ifdef OSG_DEBUG_FCPTR
    , _typedStoreP(NULL)
#endif
#ifdef OSG_INVALID_PTR_CHECK
    , _id(0)
#endif
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
#ifdef OSG_DEBUG_FCPTR
    , _typedStoreP(NULL)
#endif
#ifdef OSG_INVALID_PTR_CHECK
    , _id(0)
#endif
{
#ifdef OSG_DEBUG_FCPTR
    _typedStoreP = reinterpret_cast<FieldContainer *>(getFirstElemP());
#endif

#ifdef OSG_INVALID_PTR_CHECK
    _id = source._id;
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
#ifdef OSG_INVALID_PTR_CHECK
    _id = 0;
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
#ifndef OSG_INVALID_PTR_CHECK
    return (*getIdP());
#else
    if(_id != 0 && _id < FieldContainerFactory::the()->getFieldContainerStore()->size())
        return _id;

    return (*getIdP());
#endif
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

#ifdef OSG_INVALID_PTR_CHECK
    _id = 0;
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

#ifdef OSG_INVALID_PTR_CHECK
    _id = source._id;
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
        _storeP  = reinterpret_cast<UInt8 *>(
            const_cast<FieldContainer *>(source));
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

#ifdef OSG_INVALID_PTR_CHECK
    if(_storeP != NULL)
        _id = *getIdP();
    else
        _id = 0;
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
    _storeP          = reinterpret_cast<UInt8 *>(
        const_cast<FieldContainer *>(&source));
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    _storeP         -= getElemOff(Thread::getAspect());
#endif

#ifdef OSG_DEBUG_FCPTR
    _typedStoreP     = reinterpret_cast<FieldContainer *>(getFirstElemP());
#endif

#ifdef OSG_INVALID_PTR_CHECK
    if(_storeP != NULL)
        _id = *getIdP();
    else
        _id = 0;
#endif
}

inline
FieldContainerPtrBase::FieldContainerPtrBase(const FieldContainer *source)
{
    _uiParentEPos    = InvalidParentEPos;

    if(source != NULL)
    {
        _containerSize = source->getContainerSize();
        _storeP          = reinterpret_cast<UInt8 *>(
            const_cast<FieldContainer *>(source));
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

#ifdef OSG_INVALID_PTR_CHECK
    if(_storeP != NULL)
        _id = *getIdP();
    else
        _id = 0;
#endif
}

/*-------------------------------------------------------------------------*/
/*                           Reference Counting                            */

inline
void FieldContainerPtrBase::addRef(void) const
{
#ifdef OSG_INVALID_PTR_CHECK
    if(_id != 0 &&
       _id < FieldContainerFactory::the()->getFieldContainerStore()->size() &&
       FieldContainerFactory::the()->getContainer(_id) == NullFC)
    {
        FFATAL(("FieldContainerPtr::addRef: invalid pointer!\n"));
        FieldContainerFactory::the()->checkThrowInvalidPointerException();
        return;
    }
#endif

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

#ifdef OSG_INVALID_PTR_CHECK
    _id = 0;
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
#ifdef OSG_INVALID_PTR_CHECK
    if(_id != 0 &&
       _id < FieldContainerFactory::the()->getFieldContainerStore()->size() &&
       FieldContainerFactory::the()->getContainer(_id) == NullFC)
    {
        FFATAL(("FieldContainerPtr::operator->: invalid pointer (%u)!\n", _id));
        FieldContainerFactory::the()->checkThrowInvalidPointerException();
        return NULL;
    }
#endif

#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return reinterpret_cast<FieldContainer *>(getElemP(Thread::getAspect()));
#else
    return (FieldContainer *) (getFirstElemP());
#endif
}

inline
FieldContainer *FieldContainerPtr::operator->(void) const
{
#ifdef OSG_INVALID_PTR_CHECK
    if(_id != 0 &&
       _id < FieldContainerFactory::the()->getFieldContainerStore()->size() &&
       FieldContainerFactory::the()->getContainer(_id) == NullFC)
    {
        FFATAL(("FieldContainerPtr::operator->: invalid pointer (%u)!\n", _id));
        FieldContainerFactory::the()->checkThrowInvalidPointerException();
        return NULL;
    }
#endif

#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return reinterpret_cast<FieldContainer *>(getElemP(Thread::getAspect()));
#else
    return (FieldContainer *) (getFirstElemP());
#endif
}

inline
FieldContainer &FieldContainerPtr::operator *(void)
{
#ifdef OSG_INVALID_PTR_CHECK
    if(_id != 0 &&
       _id < FieldContainerFactory::the()->getFieldContainerStore()->size() &&
       FieldContainerFactory::the()->getContainer(_id) == NullFC)
    {
        FFATAL(("FieldContainerPtr::operator *: invalid pointer!\n"));
        FieldContainerFactory::the()->checkThrowInvalidPointerException();
        return *((FieldContainer *) NULL);
    }
#endif

#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return *(reinterpret_cast<FieldContainer *>(getElemP(Thread::getAspect())));
#else
    return *((FieldContainer *) (getFirstElemP()));
#endif
}

inline
FieldContainer &FieldContainerPtr::operator *(void) const
{
#ifdef OSG_INVALID_PTR_CHECK
    if(_id != 0 &&
       _id < FieldContainerFactory::the()->getFieldContainerStore()->size() &&
       FieldContainerFactory::the()->getContainer(_id) == NullFC)
    {
        FFATAL(("FieldContainerPtr::operator *: invalid pointer!\n"));
        FieldContainerFactory::the()->checkThrowInvalidPointerException();
        return *((FieldContainer *) NULL);
    }
#endif

#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return *(reinterpret_cast<FieldContainer *>(getElemP(Thread::getAspect())));
#else
    return *((FieldContainer *) (getFirstElemP()));
#endif
}

#ifndef OSG_2_PREP
inline
FieldContainer *FieldContainerPtr::getCPtr(void)
{
#ifdef OSG_INVALID_PTR_CHECK
    if(_id != 0 &&
       _id < FieldContainerFactory::the()->getFieldContainerStore()->size() &&
       FieldContainerFactory::the()->getContainer(_id) == NullFC)
    {
        FFATAL(("FieldContainerPtr::getCPtr: invalid pointer!\n"));
        FieldContainerFactory::the()->checkThrowInvalidPointerException();
        return NULL;
    }
#endif

#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return reinterpret_cast<FieldContainer *>(getElemP(Thread::getAspect()));
#else
    return (FieldContainer *) (getFirstElemP());
#endif
}

inline
FieldContainer *FieldContainerPtr::getCPtr(void) const
{
#ifdef OSG_INVALID_PTR_CHECK
    if(_id != 0 &&
       _id < FieldContainerFactory::the()->getFieldContainerStore()->size() &&
       FieldContainerFactory::the()->getContainer(_id) == NullFC)
    {
        FFATAL(("FieldContainerPtr::getCPtr: invalid pointer!\n"));
        FieldContainerFactory::the()->checkThrowInvalidPointerException();
        return NULL;
    }
#endif

#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return reinterpret_cast<FieldContainer *>(getElemP(Thread::getAspect()));
#else
    return (FieldContainer *) (getFirstElemP());
#endif
}
#endif

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
#ifdef OSG_INVALID_PTR_CHECK
    if(_id != 0 &&
       _id < FieldContainerFactory::the()->getFieldContainerStore()->size() &&
       FieldContainerFactory::the()->getContainer(_id) == NullFC)
    {
        FFATAL(("FieldContainerPtr::beginEdit: invalid pointer!\n"));
        FieldContainerFactory::the()->checkThrowInvalidPointerException();
        return;
    }
#endif
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
#ifdef OSG_INVALID_PTR_CHECK
    if(_id != 0 &&
       _id < FieldContainerFactory::the()->getFieldContainerStore()->size() &&
       FieldContainerFactory::the()->getContainer(_id) == NullFC)
    {
        FFATAL(("FieldContainerPtr::endEdit: invalid pointer!\n"));
        FieldContainerFactory::the()->checkThrowInvalidPointerException();
        return;
    }
#endif

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
#ifdef OSG_INVALID_PTR_CHECK
    if(_id != 0 &&
       _id < FieldContainerFactory::the()->getFieldContainerStore()->size() &&
       FieldContainerFactory::the()->getContainer(_id) == NullFC)
    {
        FFATAL(("FieldContainerPtr::operator->: invalid pointer (%u)!\n", _id));
        FieldContainerFactory::the()->checkThrowInvalidPointerException();
        return NULL;
    }
#endif

#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return 
        reinterpret_cast<const FieldContainer *>(getElemP(Thread::getAspect()));
#else
    return (const FieldContainer *) (getFirstElemP());
#endif
}

inline
const FieldContainer *ConstFieldContainerPtr::operator->(void) const
{
#ifdef OSG_INVALID_PTR_CHECK
    if(_id != 0 &&
       _id < FieldContainerFactory::the()->getFieldContainerStore()->size() &&
       FieldContainerFactory::the()->getContainer(_id) == NullFC)
    {
        FFATAL(("FieldContainerPtr::operator->: invalid pointer (%u)!\n", _id));
        FieldContainerFactory::the()->checkThrowInvalidPointerException();
        return NULL;
    }
#endif

#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return 
        reinterpret_cast<const FieldContainer *>(getElemP(Thread::getAspect()));
#else
    return (const FieldContainer *) (getFirstElemP());
#endif
}

inline
const FieldContainer &ConstFieldContainerPtr::operator *(void)
{
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return 
        *(reinterpret_cast<const FieldContainer *>(
              getElemP(Thread::getAspect())));
#else
    return *((const FieldContainer *) (getFirstElemP()));
#endif
}

inline
const FieldContainer &ConstFieldContainerPtr::operator *(void) const
{
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return 
        *(reinterpret_cast<const FieldContainer *>(
              getElemP(Thread::getAspect())));
#else
    return *((const FieldContainer *) (getFirstElemP()));
#endif
}

#ifndef OSG_2_PREP
inline
const FieldContainer *ConstFieldContainerPtr::getCPtr(void)
{
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return 
        reinterpret_cast<const FieldContainer *>(getElemP(Thread::getAspect()));
#else
    return (const FieldContainer *) (getFirstElemP());
#endif
}

inline
const FieldContainer *ConstFieldContainerPtr::getCPtr(void) const
{
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return 
        reinterpret_cast<const FieldContainer *>(getElemP(Thread::getAspect()));
#else
    return (const FieldContainer *) (getFirstElemP());
#endif
}
#endif

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
#ifdef OSG_INVALID_PTR_CHECK
    if(_id != 0 &&
       _id < FieldContainerFactory::the()->getFieldContainerStore()->size() &&
       FieldContainerFactory::the()->getContainer(Self::_id) == NullFC)
    {
        FFATAL(("FieldContainerPtr::operator ->: invalid pointer (%u)!\n", Self::_id));
        FieldContainerFactory::the()->checkThrowInvalidPointerException();
        return NULL;
    }
#endif

#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return 
        reinterpret_cast<FieldContainerTypeT *>(
            Self::getElemP(Thread::getAspect()));
#else
    return (FieldContainerTypeT *) Self::getFirstElemP();
#endif
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FieldContainerTypeT *FCPtr<BasePtrTypeT,
                            FieldContainerTypeT>::operator ->(void) const
{
#ifdef OSG_INVALID_PTR_CHECK
    if(_id != 0 &&
       _id < FieldContainerFactory::the()->getFieldContainerStore()->size() &&
       FieldContainerFactory::the()->getContainer(Self::_id) == NullFC)
    {
        FFATAL(("FieldContainerPtr::operator ->: invalid pointer (%u)!\n", Self::_id));
        FieldContainerFactory::the()->checkThrowInvalidPointerException();
        return NULL;
    }
#endif

#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return 
        reinterpret_cast<FieldContainerTypeT *>(Self::getElemP(Thread::getAspect()));
#else
    return (FieldContainerTypeT *) Self::getFirstElemP();
#endif
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FieldContainerTypeT &FCPtr<BasePtrTypeT, 
                           FieldContainerTypeT>::operator *(void)
{
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return 
        *(reinterpret_cast<FieldContainerTypeT *>(
              Self::getElemP(Thread::getAspect())));
#else
    return *((FieldContainerTypeT *) Self::getFirstElemP());
#endif
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FieldContainerTypeT &FCPtr<BasePtrTypeT,
                            FieldContainerTypeT>::operator *(void) const
{
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return 
        *(reinterpret_cast<FieldContainerTypeT *>(
              Self::getElemP(Thread::getAspect())));
#else
    return *((FieldContainerTypeT *) Self::getFirstElemP());
#endif
}


#ifndef OSG_2_PREP
template <class BasePtrTypeT, class FieldContainerTypeT> inline
FieldContainerTypeT *FCPtr<BasePtrTypeT, FieldContainerTypeT>::getCPtr(void)

{
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return 
        reinterpret_cast<FieldContainerTypeT *>(
            Self::getElemP(Thread::getAspect()));
#else
    return (FieldContainerTypeT *) Self::getFirstElemP();
#endif
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FieldContainerTypeT *
    FCPtr<BasePtrTypeT, FieldContainerTypeT>::getCPtr(void) const
{
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return 
        reinterpret_cast<FieldContainerTypeT *>(Self::getElemP(Thread::getAspect()));
#else
    return (FieldContainerTypeT *) Self::getFirstElemP();
#endif
}
#endif

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
#ifdef OSG_INVALID_PTR_CHECK
    if(_id != 0 &&
       _id < FieldContainerFactory::the()->getFieldContainerStore()->size() &&
       FieldContainerFactory::the()->getContainer(Self::_id) == NullFC)
    {
        FFATAL(("FieldContainerPtr::operator ->: invalid pointer (%u)!\n", Self::_id));
        FieldContainerFactory::the()->checkThrowInvalidPointerException();
        return NULL;
    }
#endif

#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return 
        static_cast<const FieldContainerTypeT *>(
            Self::getElemP(Thread::getAspect()));
#else
    return (const FieldContainerTypeT *) Self::getFirstElemP();
#endif
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
const FieldContainerTypeT *ConstFCPtr<BasePtrTypeT,
                                      FieldContainerTypeT>::operator ->(
                                           void) const
{
#ifdef OSG_INVALID_PTR_CHECK
    if(_id != 0 &&
       _id < FieldContainerFactory::the()->getFieldContainerStore()->size() &&
       FieldContainerFactory::the()->getContainer(Self::_id) == NullFC)
    {
        FFATAL(("FieldContainerPtr::operator ->: invalid pointer (%u)!\n", Self::_id));
        FieldContainerFactory::the()->checkThrowInvalidPointerException();
        return NULL;
    }
#endif

#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return 
        static_cast<const FieldContainerTypeT *>(
            Self::getElemP(Thread::getAspect()));
#else
    return (const FieldContainerTypeT *) Self::getFirstElemP();
#endif
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
const FieldContainerTypeT &ConstFCPtr<BasePtrTypeT,
                                      FieldContainerTypeT>::operator *(void)
{
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return 
        *(static_cast<const FieldContainerTypeT *>(
              Self::getElemP(Thread::getAspect())));
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
    return 
        *(static_cast<const FieldContainerTypeT *>(
              Self::getElemP(Thread::getAspect())));
#else
    return *((const FieldContainerTypeT *) Self::getFirstElemP());
#endif
}


#ifndef OSG_2_PREP
template <class BasePtrTypeT, class FieldContainerTypeT> inline
const FieldContainerTypeT *ConstFCPtr<BasePtrTypeT,
                                      FieldContainerTypeT>::getCPtr(void)

{
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return 
        static_cast<const FieldContainerTypeT *>(
            Self::getElemP(Thread::getAspect()));
#else
    return (const FieldContainerTypeT *) Self::getFirstElemP();
#endif
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
const FieldContainerTypeT *
    ConstFCPtr<BasePtrTypeT, FieldContainerTypeT>::getCPtr(void) const
{
#if !defined(OSG_DEBUG_NO_FCPTR_ARITHM) 
    return 
        static_cast<const FieldContainerTypeT *>(
            Self::getElemP(Thread::getAspect()));
#else
    return (const FieldContainerTypeT *) Self::getFirstElemP();
#endif
}
#endif

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
        (dynamic_cast<const typename RetTypeT::ObjectType *>(&*oIn)),
        oIn.getContainerSize,
        oIn.getParentFieldPos);
}

template <class RetTypeT, class InTypeT> inline
RetTypeT dyncast(const InTypeT oIn)
{
    return RetTypeT(
        (dynamic_cast<const typename RetTypeT::ObjectType *>(&*oIn)),
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

    FieldContainer *pTo = 
        (reinterpret_cast<FieldContainer *>(getElemP(uiToAspect)));
    
#if !defined(OSG_FIXED_MFIELDSYNC)
    pTo->executeSync(
        *(reinterpret_cast<FieldContainer *>(getElemP(uiFromAspect))), 
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

/*-------------------------------------------------------------------------*/
/*                      boost::bind compatibility                          */

template <class FCType, class FCPtrType>
inline FCType*
get_pointer(const FCPtr<FCPtrType, FCType>& fc)
{
    return &*fc;
}

template <class FCType, class FCPtrType>
inline const FCType *
get_pointer(const ConstFCPtr<FCPtrType, FCType>& fc)
{
    return &*fc;
}

OSG_END_NAMESPACE

#define OSGFIELDCONTAINERPTR_INLINE_CVSID "@(#)$Id: $"

#endif /* _OSGFIELDCONTAINERPTRIMPL_INL_ */
