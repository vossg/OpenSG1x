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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>

#include <OSGThread.h>

OSG_BEGIN_NAMESPACE

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
      FieldContainerTypeT>::FCPtr(const NullFieldContainerPtr &source) :

    Inherited(source)
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
    return (FieldContainerTypeT *) getElemP(Thread::getAspect());
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FieldContainerTypeT *FCPtr<BasePtrTypeT,
                            FieldContainerTypeT>::operator ->(void) const
{
    return (FieldContainerTypeT *) getElemP(Thread::getAspect());
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FieldContainerTypeT &FCPtr<BasePtrTypeT, 
                           FieldContainerTypeT>::operator *(void)
{
    return *((FieldContainerTypeT *) getElemP(Thread::getAspect()));
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FieldContainerTypeT &FCPtr<BasePtrTypeT,
                            FieldContainerTypeT>::operator *(void) const
{
    return *((FieldContainerTypeT *) getElemP(Thread::getAspect()));
}


template <class BasePtrTypeT, class FieldContainerTypeT> inline
FieldContainerTypeT *FCPtr<BasePtrTypeT, FieldContainerTypeT>::getCPtr(void)

{
    return (FieldContainerTypeT *) getElemP(Thread::getAspect());
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
FieldContainerTypeT *
    FCPtr<BasePtrTypeT, FieldContainerTypeT>::getCPtr(void) const
{
    return (FieldContainerTypeT *) getElemP(Thread::getAspect());
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
    const NullFieldContainerPtr &source)
{
    // copy parts inherited from parent
    *(static_cast<Inherited *>(this)) = source;
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
               const NullFieldContainerPtr &source) :

    Inherited(source)
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
    return (FieldContainerTypeT *) getElemP(Thread::getAspect());
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
const FieldContainerTypeT *ConstFCPtr<BasePtrTypeT,
                                      FieldContainerTypeT>::operator ->(
                                           void) const
{
    return (FieldContainerTypeT *) getElemP(Thread::getAspect());
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
const FieldContainerTypeT &ConstFCPtr<BasePtrTypeT,
                                      FieldContainerTypeT>::operator *(void)
{
    return *((FieldContainerTypeT *) getElemP(Thread::getAspect()));
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
const FieldContainerTypeT &ConstFCPtr<BasePtrTypeT,
                                      FieldContainerTypeT>::operator *(
                                           void) const
{
    return *((FieldContainerTypeT *) getElemP(Thread::getAspect()));
}


template <class BasePtrTypeT, class FieldContainerTypeT> inline
const FieldContainerTypeT *ConstFCPtr<BasePtrTypeT,
                                      FieldContainerTypeT>::getCPtr(void)

{
    return (FieldContainerTypeT *) getElemP(Thread::getAspect());
}

template <class BasePtrTypeT, class FieldContainerTypeT> inline
const FieldContainerTypeT *
    ConstFCPtr<BasePtrTypeT, FieldContainerTypeT>::getCPtr(void) const
{
    return (FieldContainerTypeT *) getElemP(Thread::getAspect());
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
    const NullFieldContainerPtr &source)
{
    // copy parts inherited from parent
    *(static_cast<Inherited *>(this)) = source;
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

OSG_END_NAMESPACE

#define OSGFIELDCONTAINERPTR_INLINE_CVSID "@(#)$Id: $"
