/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

#ifndef _OSGFIELDCONTAINER_H_
//#warning FCPtr.inl ohne FC.h
#endif

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class osg::NullFieldContainerPtr
 */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

inline
NullFieldContainerPtr::NullFieldContainerPtr(void)
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
    return - (sizeof(Int32) + sizeof(UInt32));
}

inline
Int32  FieldContainerPtrBase::getIdOff(void) const
{
    return - sizeof(UInt32);
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
     Inherited    (                ),
    _containerSize(0               ),
    _uiParentEPos(InvalidParentEPos),
    _storeP      (NULL             ) 
{
#ifdef OSG_DEBUG_TYPED_FCPTR
    _szTypename = NULL;
#endif
}

inline
FieldContainerPtrBase::FieldContainerPtrBase(
    const NullFieldContainerPtr &) :

     Inherited    (                 ),
    _containerSize(0                ),
    _uiParentEPos (InvalidParentEPos),
    _storeP       (NULL             )
{
#ifdef OSG_DEBUG_TYPED_FCPTR
    _szTypename = NULL;
#endif
}

inline
FieldContainerPtrBase::FieldContainerPtrBase(
    const FieldContainerPtrBase &source) :

     Inherited    (                     ),
    _containerSize(source._containerSize),
    _uiParentEPos (source._uiParentEPos ),
    _storeP       (source._storeP       )
{
#ifdef OSG_DEBUG_TYPED_FCPTR
    if(_storeP == NULL)
        _szTypename = NULL;
    else
        _szTypename = ((FieldContainer *) _storeP)->getType().getName();
#endif
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

inline
FieldContainerPtrBase::~FieldContainerPtrBase(void)
{
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
UInt32 FieldContainerPtrBase::getFieldContainerId(void) const
{
    return (*getIdP());
}

inline
UInt16  FieldContainerPtrBase::getContainerSize(void) const
{
    return _containerSize;
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

inline
void FieldContainerPtrBase::operator =(const NullFieldContainerPtr &)
{
    _containerSize = 0;
    _uiParentEPos  = InvalidParentEPos;
    _storeP        = NULL;

#ifdef OSG_DEBUG_TYPED_FCPTR
    _szTypename = NULL;
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

#ifdef OSG_DEBUG_TYPED_FCPTR
    if(_storeP == NULL)
        _szTypename = NULL;
    else
        _szTypename = ((FieldContainer *) _storeP)->getType().getName();
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


#ifdef OSG_DEBUG_TYPED_FCPTR
inline
void FieldContainerPtrBase::updateTypedStore(void)
{
    if(_storeP == NULL)
        _szTypename = NULL;
    else
        _szTypename = ((FieldContainer *) _storeP)->getType().getName();
}
#endif


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
        _storeP -= getElemOff(Thread::getAspect());
    }
    else
    {
        _storeP  = NULL;
    }

#ifdef OSG_DEBUG_TYPED_FCPTR
    if(_storeP == NULL)
        _typename = NULL;
    else
        _typename = ((FieldContainer *) _storeP)->getType().getName();
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
    _storeP         -= getElemOff(Thread::getAspect());

#ifdef OSG_DEBUG_TYPED_FCPTR
    if(_storeP == NULL)
        _typename = NULL;
    else
        _typename = ((FieldContainer *) _storeP)->getType().getName();
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
        _storeP         -= getElemOff(Thread::getAspect());
    }
    else
    {
        _containerSize = 0;
        _storeP          = NULL;
    }

#ifdef OSG_DEBUG_TYPED_FCPTR
    if(_storeP == NULL)
        _typename = NULL;
    else
        _typename = ((FieldContainer *) _storeP)->getType().getName();
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

#ifdef OSG_DEBUG_TYPED_FCPTR
    _szTypename = NULL;
#endif
}


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------


/*! \class osg::FieldContainerPtr
 */

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
    return (FieldContainer *) (getElemP(Thread::getAspect()));
}

inline
FieldContainer *FieldContainerPtr::operator->(void) const
{
    return (FieldContainer *) (getElemP(Thread::getAspect()));
}

inline
FieldContainer &FieldContainerPtr::operator *(void)
{
    return *((FieldContainer *) (getElemP(Thread::getAspect())));
}

inline
FieldContainer &FieldContainerPtr::operator *(void) const
{
    return *((FieldContainer *) (getElemP(Thread::getAspect())));
}

inline
FieldContainer *FieldContainerPtr::getCPtr(void)
{
    return (FieldContainer *) (getElemP(Thread::getAspect()));
}

inline
FieldContainer *FieldContainerPtr::getCPtr(void) const
{
    return (FieldContainer *) (getElemP(Thread::getAspect()));
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

inline
void FieldContainerPtr::beginEdit(BitVector OSG_CHECK_ARG(whichField),
                                  UInt32    OSG_CHECK_ARG(origin    )) const
{
}

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

/*! \class osg::ConstFieldContainerPtr
 */

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
    return (FieldContainer *) (getElemP(Thread::getAspect()));
}

inline
const FieldContainer *ConstFieldContainerPtr::operator->(void) const
{
    return (const FieldContainer *) (getElemP(Thread::getAspect()));
}

inline
const FieldContainer &ConstFieldContainerPtr::operator *(void)
{
    return *((FieldContainer *) (getElemP(Thread::getAspect())));
}

inline
const FieldContainer &ConstFieldContainerPtr::operator *(void) const
{
    return *((const FieldContainer *) (getElemP(Thread::getAspect())));
}

inline
const FieldContainer *ConstFieldContainerPtr::getCPtr(void)
{
    return (FieldContainer *) (getElemP(Thread::getAspect()));
}

inline
const FieldContainer *ConstFieldContainerPtr::getCPtr(void) const
{
    return (const FieldContainer *) (getElemP(Thread::getAspect()));
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

/*! \class FCPtr
 */

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
    return (FieldContainerTypeT *) Self::getElemP(Thread::getAspect());
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FieldContainerTypeT *FCPtr<BasePtrTypeT,
                            FieldContainerTypeT>::operator ->(void) const
{
    return (FieldContainerTypeT *) Self::getElemP(Thread::getAspect());
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FieldContainerTypeT &FCPtr<BasePtrTypeT, 
                           FieldContainerTypeT>::operator *(void)
{
    return *((FieldContainerTypeT *) Self::getElemP(Thread::getAspect()));
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FieldContainerTypeT &FCPtr<BasePtrTypeT,
                            FieldContainerTypeT>::operator *(void) const
{
    return *((FieldContainerTypeT *) Self::getElemP(Thread::getAspect()));
}


template <class BasePtrTypeT, class FieldContainerTypeT> inline
FieldContainerTypeT *FCPtr<BasePtrTypeT, FieldContainerTypeT>::getCPtr(void)

{
    return (FieldContainerTypeT *) Self::getElemP(Thread::getAspect());
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FieldContainerTypeT *
    FCPtr<BasePtrTypeT, FieldContainerTypeT>::getCPtr(void) const
{
    return (FieldContainerTypeT *) Self::getElemP(Thread::getAspect());
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

/*! \class ConstFCPtr
 */

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
    return (FieldContainerTypeT *) Self::getElemP(Thread::getAspect());
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
const FieldContainerTypeT *ConstFCPtr<BasePtrTypeT,
                                      FieldContainerTypeT>::operator ->(
                                           void) const
{
    return (FieldContainerTypeT *) Self::getElemP(Thread::getAspect());
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
const FieldContainerTypeT &ConstFCPtr<BasePtrTypeT,
                                      FieldContainerTypeT>::operator *(void)
{
    return *((FieldContainerTypeT *) Self::getElemP(Thread::getAspect()));
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
const FieldContainerTypeT &ConstFCPtr<BasePtrTypeT,
                                      FieldContainerTypeT>::operator *(
                                           void) const
{
    return *((FieldContainerTypeT *) Self::getElemP(Thread::getAspect()));
}


template <class BasePtrTypeT, class FieldContainerTypeT> inline
const FieldContainerTypeT *ConstFCPtr<BasePtrTypeT,
                                      FieldContainerTypeT>::getCPtr(void)

{
    return (FieldContainerTypeT *) Self::getElemP(Thread::getAspect());
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
const FieldContainerTypeT *
    ConstFCPtr<BasePtrTypeT, FieldContainerTypeT>::getCPtr(void) const
{
    return (FieldContainerTypeT *) Self::getElemP(Thread::getAspect());
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
    FieldContainer *pTo = ((FieldContainer *) getElemP(uiToAspect));
    
    pTo->executeSync(*((FieldContainer *) getElemP(uiFromAspect)), whichField);
    pTo->changed(whichField, ChangedOrigin::Sync);
}

OSG_END_NAMESPACE

#define OSGFIELDCONTAINERPTR_INLINE_CVSID "@(#)$Id: $"

#endif /* _OSGFIELDCONTAINERPTRIMPL_INL_ */
