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

#include "OSGConfig.h"

#include <stdlib.h>
#include <stdio.h>

#include <iostream>

#include "OSGMemoryObject.h"

OSG_USING_NAMESPACE

/*! \var Int32 MemoryObject::_refCount
 *  \brief reference count
 */

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

MemoryObject::~MemoryObject(void)
{
}

/*-------------------------------------------------------------------------*/
/*                        Reference Counting                               */

void MemoryObject::addRef(void)
{
    _refCount++;
}

void MemoryObject::subRef(void)
{
    _refCount--;

    if(_refCount <= 0)
        delete this;
}

Int32 MemoryObject::getRefCount(void)
{
    return _refCount;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

MemoryObject::MemoryObject(void) :
    _refCount(0)
{
}

MemoryObject::MemoryObject(const MemoryObject &) :
    _refCount(0)
{
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
    static Char8 cvsid_hpp[] = OSGMEMORYOBJECT_HEADER_CVSID;
}
