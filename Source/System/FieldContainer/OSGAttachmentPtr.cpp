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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGAttachmentPtr.h"
#include "OSGThread.h"

OSG_USING_NAMESPACE

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGAttachmentPtr.cpp
    \ingroup GrpSystemFieldContainer
 */
#endif

AttachmentPtr::AttachmentPtr(const Attachment &source) :

    Inherited(source)
{
}

AttachmentPtr::AttachmentPtr(const Attachment *source) :

    Inherited(source)
{
}

AttachmentPtr::AttachmentPtr(const Attachment *source,
                             const UInt16      uiSize,
                             const UInt16      uiParentPos) :

    Inherited(source, uiSize, uiParentPos)
{
}

/*-------------------------------------------------------------------------*/
/*                               Functions                                 */

OSG_SYSTEMLIB_DLLMAPPING
std::ostream &OSG::operator <<(      std::ostream   &os,
                               const AttachmentPtr  &fc)
{
    if(fc == NullFC)
    {
        os << std::hex << "NodePtr 0x" << &fc << std::dec << ":NullFC";
    }
    else
    {
        os << std::hex 
           << "NodePtr 0x"
           << &fc 
           << std::dec << ":" 
           << fc->getType().getName() 
           << "Ptr(0x"
           << std::hex
           << (&(*fc)) 
           << std::dec
           << ")";
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
    static Char8 cvsid_hpp[] = OSGATTACHMENTPTR_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGATTACHMENTPTR_INLINE_CVSID;
}
