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

#ifndef _OSGATTACHMENTCONTAINERPTRIMPL_INL_
#define _OSGATTACHMENTCONTAINERPTRIMPL_INL_

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGAttachmentContainerPtrImpl.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

inline
AttachmentContainerPtr::AttachmentContainerPtr(void) :
    Inherited()
{
}

inline
AttachmentContainerPtr::AttachmentContainerPtr(
    const AttachmentContainerPtr &source) :

    Inherited(source)
{
}

inline
AttachmentContainerPtr::AttachmentContainerPtr(
    const NullFieldContainerPtr &source) :

    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

inline
AttachmentContainerPtr::~AttachmentContainerPtr(void)
{
}

/*-------------------------------------------------------------------------*/
/*                            Container Access                             */

inline
AttachmentContainer *AttachmentContainerPtr::operator->(void)
{
#if 0
    return (AttachmentContainer *) getElemP(Thread::getAspect());
#else
    return (AttachmentContainer *) Inherited::operator ->();
#endif
}

inline
AttachmentContainer *AttachmentContainerPtr::operator->(void) const
{
#if 0
    return (AttachmentContainer *) getElemP(Thread::getAspect());
#else
    return (AttachmentContainer *) Inherited::operator ->();
#endif
}

inline
AttachmentContainer &AttachmentContainerPtr::operator *(void)
{
#if 0
    return *((AttachmentContainer *) getElemP(Thread::getAspect()));
#else
    return (AttachmentContainer &) Inherited::operator *();
#endif
}

inline
AttachmentContainer &AttachmentContainerPtr::operator *(void) const
{
#if 0
    return *((AttachmentContainer *) getElemP(Thread::getAspect()));
#else
    return (AttachmentContainer &) Inherited::operator *();
#endif
}

inline
AttachmentContainer *AttachmentContainerPtr::getCPtr(void)
{
#if 0
    return (AttachmentContainer *) getElemP(Thread::getAspect());
#else
    return (AttachmentContainer *) Inherited::getCPtr();
#endif
}

inline
AttachmentContainer *AttachmentContainerPtr::getCPtr(void) const
{
#if 0
    return (AttachmentContainer *) getElemP(Thread::getAspect());
#else
    return (AttachmentContainer *) Inherited::getCPtr();
#endif
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

inline
void AttachmentContainerPtr::operator =(const AttachmentContainerPtr &source)
{
    // copy parts inherited from parent
    *(static_cast<Inherited *>(this)) = source;
}

inline
void AttachmentContainerPtr::operator = (const NullFieldContainerPtr &source)
{
    // copy parts inherited from parent
    *(static_cast<Inherited *>(this)) = source;
}

OSG_END_NAMESPACE

#define OSGATTACHMENTCONTAINERPTR_INLINE_CVSID "@(#)$Id: $"

#endif /*_OSGATTACHMENTCONTAINERPTRIMPL_INL_ */

