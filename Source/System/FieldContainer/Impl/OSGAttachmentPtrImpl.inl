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

#ifndef _OSGATTACHMENTPTRIMPL_INL_
#define _OSGATTACHMENTPTRIMPL_INL_

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGAttachmentPtrImpl.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

inline
AttachmentPtr::AttachmentPtr(void) :
    Inherited()
{
}

inline
AttachmentPtr::AttachmentPtr(const AttachmentPtr &source) :

    Inherited(source)
{
}

inline
AttachmentPtr::AttachmentPtr(const NullFieldContainerPtr &source) :

    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

inline
AttachmentPtr::~AttachmentPtr(void)
{
}

/*-------------------------------------------------------------------------*/
/*                        Container Access                                 */

inline
Attachment *AttachmentPtr::operator->(void)
{
#if 0
    return (Attachment *) getElemP(Thread::getAspect());
#else
    return (Attachment *) Inherited::operator ->();
#endif
}

inline
Attachment *AttachmentPtr::operator->(void) const
{
#if 0
    return (Attachment *) getElemP(Thread::getAspect());
#else
    return (Attachment *) Inherited::operator ->();
#endif
}

inline
Attachment &AttachmentPtr::operator *(void)
{
#if 0
    return *((Attachment *) getElemP(Thread::getAspect()));
#else
    return (Attachment &) Inherited::operator *();
#endif
}

inline
Attachment &AttachmentPtr::operator *(void) const
{
#if 0
    return *((Attachment *) getElemP(Thread::getAspect()));
#else
    return (Attachment &) Inherited::operator *();
#endif
}

inline
Attachment *AttachmentPtr::getCPtr(void)
{
#if 0
    return (Attachment *) getElemP(Thread::getAspect());
#else
    return (Attachment *) Inherited::getCPtr();
#endif
}

inline
Attachment *AttachmentPtr::getCPtr(void) const
{
#if 0
    return (Attachment *) getElemP(Thread::getAspect());
#else
    return (Attachment *) Inherited::getCPtr();
#endif
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

inline
void AttachmentPtr::operator = (const AttachmentPtr &source)
{
    // copy parts inherited from parent
    *(static_cast<Inherited *>(this)) = source;
}

inline
void AttachmentPtr::operator = (const NullFieldContainerPtr &source)
{
    // copy parts inherited from parent
    *(static_cast<Inherited *>(this)) = source;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

#ifdef ATTCHECK

inline
AttachmentPtr::AttachmentPtr(const Attachment &source) :

    Inherited(source)
{
}

inline
AttachmentPtr::AttachmentPtr(const Attachment *source) :

    Inherited(source)
{
}

inline
AttachmentPtr::AttachmentPtr(const Attachment *source,
                             const UInt16      uiSize,
                             const UInt16      uiParentPos) :

    Inherited(source, uiSize, uiParentPos)
{
}

#endif

OSG_END_NAMESPACE

#define OSGATTACHMENTPTR_INLINE_CVSID "@(#)$Id: $"

#endif /*_OSGATTACHMENTPTRIMPL_INL_ */

