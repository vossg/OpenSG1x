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

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGFieldContainer.cpp
    \ingroup GrpSystemFieldContainer
 */
#endif

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"
#include "OSGFieldContainer.h"

OSG_USING_NAMESPACE

FieldContainerType FieldContainer::_type("FieldContainer");

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

FieldContainerType &FieldContainer::getType(void)
{
    return _type;
}

const FieldContainerType &FieldContainer::getType(void) const
{
    return _type;
}

/*-------------------------------------------------------------------------*/
/*                            Binary Access                                */

UInt32 FieldContainer::getBinSize(const BitVector &)
{
    return 0;
}

void FieldContainer::copyToBin(      BinaryDataHandler &,
                               const BitVector         &)
{
}

void FieldContainer::copyFromBin(      BinaryDataHandler &,
                                 const BitVector         &)
{
}

/*-------------------------------------------------------------------------*/
/*                               Changed                                   */

void FieldContainer::changed(BitVector OSG_CHECK_ARG(whichField),
                             UInt32    OSG_CHECK_ARG(origin    ))
{
    // fprintf(stderr, "FC Changed %d %d\n", whichField, fromSync);
}

/*-------------------------------------------------------------------------*/
/*                             MT Destruction                              */

void FieldContainer::onDestroy(void)
{
}

#if defined(OSG_FIXED_MFIELDSYNC)
void FieldContainer::onDestroyAspect(UInt32 uiId, UInt32 uiAspect)
{
}
#endif

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
    static Char8 cvsid_hpp[] = OSGFIELDCONTAINER_HEADER_CVSID;
    static Char8 cvsid_inl[] = OSGFIELDCONTAINER_INLINE_CVSID;
}
