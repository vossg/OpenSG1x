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

#include "OSGAttachmentContainer.h"
#include "OSGAttachmentContainerPtr.h"
#include "OSGThread.h"

OSG_USING_NAMESPACE

/*! \class osg::AttachmentContainerPtr
 */

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

AttachmentContainerPtr::AttachmentContainerPtr(void) :
    Inherited()
{
}

AttachmentContainerPtr::AttachmentContainerPtr(
    const AttachmentContainerPtr &source) :

    Inherited(source)
{
}

AttachmentContainerPtr::AttachmentContainerPtr(
    const NullFieldContainerPtr &source) :

    Inherited(source)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

AttachmentContainerPtr::~AttachmentContainerPtr(void)
{
}

/*-------------------------------------------------------------------------*/
/*                            Container Access                             */

AttachmentContainer *AttachmentContainerPtr::operator->(void)
{
    return (AttachmentContainer *) getElemP(Thread::getAspect());
}

AttachmentContainer *AttachmentContainerPtr::operator->(void) const
{
    return (AttachmentContainer *) getElemP(Thread::getAspect());
}

AttachmentContainer &AttachmentContainerPtr::operator *(void)
{
    return *((AttachmentContainer *) getElemP(Thread::getAspect()));
}

AttachmentContainer &AttachmentContainerPtr::operator *(void) const
{
    return *((AttachmentContainer *) getElemP(Thread::getAspect()));
}

AttachmentContainer *AttachmentContainerPtr::getCPtr(void)
{
    return (AttachmentContainer *) getElemP(Thread::getAspect());
}

AttachmentContainer *AttachmentContainerPtr::getCPtr(void) const
{
    return (AttachmentContainer *) getElemP(Thread::getAspect());
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

void AttachmentContainerPtr::operator =(const AttachmentContainerPtr &source)
{
    // copy parts inherited from parent
    *(static_cast<Inherited *>(this)) = source;
}

void AttachmentContainerPtr::operator = (const NullFieldContainerPtr &source)
{
    // copy parts inherited from parent
    *(static_cast<Inherited *>(this)) = source;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

AttachmentContainerPtr::AttachmentContainerPtr(
    const AttachmentContainer &source) :

    Inherited(source)
{
}

AttachmentContainerPtr::AttachmentContainerPtr(
    const AttachmentContainer *source) :

    Inherited(source)
{
}

AttachmentContainerPtr::AttachmentContainerPtr(
    const AttachmentContainer *source,
    const UInt16               uiSize,
    const UInt16               uiParentPos) :

    Inherited(source, uiSize, uiParentPos)
{
}

/*-------------------------------------------------------------------------*/
/*                               Functions                                 */

//! Write FCPtr to the given stream

OSG_SYSTEMLIB_DLLMAPPING
ostream &OSG::operator <<(      ostream                 &os,
                          const AttachmentContainerPtr  &fc)
{
    if(fc == NullFC)
    {
        os << hex << "NodePtr 0x" << &fc << dec << ":NullFC";
    }
    else
    {
        os << hex << "NodePtr 0x"
           << &fc << dec << ":" << fc->getType().getName() << "Ptr(0x"
           << hex << (&(*fc)) << dec << ")";
    }

    return os;
}


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp[] = "@(#)$Id: $";
    static Char8 cvsid_hpp[] = OSGATTACHMENTCONTAINERPTR_HEADER_CVSID;
}

