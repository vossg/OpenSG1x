/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000-2002,2002 by the OpenSG Forum                *
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

#ifndef _OSGFIELDCONTAINERBASE_H_
#define _OSGFIELDCONTAINERBASE_H_
#ifdef __sgi
#pragma once
#endif

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGFieldContainerBase.h
    \ingroup GrpSystemFieldContainer
 */
#endif

#include <OSGBaseTypes.h>

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpSystemFieldContainer
 */

namespace FieldBits
{
#ifdef OSG_LONGLONG_HAS_LL
    const BitVector AllFields = 0xffffffffffffffffLL;
#else
    const BitVector AllFields = 0xffffffffffffffff;
#endif

    const BitVector NoField   = 0x00000000;


    const BitVector Field0    = 0x00000001;
    const BitVector Field1    = 0x00000002;
    const BitVector Field2    = 0x00000004;
    const BitVector Field3    = 0x00000008;

    const BitVector Field4    = 0x00000010;
    const BitVector Field5    = 0x00000020;
    const BitVector Field6    = 0x00000040;
    const BitVector Field7    = 0x00000080;

    const BitVector Field8    = 0x00000100;
    const BitVector Field9    = 0x00000200;
    const BitVector Field10   = 0x00000400;
    const BitVector Field11   = 0x00000800;

    const BitVector Field12   = 0x00001000;
    const BitVector Field13   = 0x00002000;
    const BitVector Field14   = 0x00004000;
    const BitVector Field15   = 0x00008000;

    const BitVector Field16   = 0x00010000;
    const BitVector Field17   = 0x00020000;
    const BitVector Field18   = 0x00040000;
    const BitVector Field19   = 0x00080000;

    const BitVector Field20   = 0x00100000;
    const BitVector Field21   = 0x00200000;
    const BitVector Field22   = 0x00400000;
    const BitVector Field23   = 0x00800000;

    const BitVector Field24   = 0x01000000;
    const BitVector Field25   = 0x02000000;
    const BitVector Field26   = 0x04000000;
    const BitVector Field27   = 0x08000000;

    const BitVector Field28   = 0x10000000;
    const BitVector Field29   = 0x20000000;
    const BitVector Field30   = 0x40000000;
    const BitVector Field31   = 0x80000000;
}

/*! \ingroup GrpSystemFieldContainer
 */

namespace ChangedOrigin
{
    const UInt32 External         = 0x0001;
    const UInt32 Sync             = 0x0002;
    const UInt32 Child            = 0x0004;
    const UInt32 Abstract         = 0x0008;

    const UInt32 AbstrIgnoreCore  = 0x0100;
    const UInt32 AbstrIgnoreChild = 0x0200;

    const UInt32 AbstrCheckValid  = 0x0400;
    const UInt32 AbstrIncRefCount = 0x0800;
}

/*! \ingroup GrpSystemFieldContainer
 */

namespace FCDumpFlags
{
    const BitVector RefCount   = 0x00000001;

    const BitVector AllAspects = 0x00000002;

    const BitVector All        = 0xFFFFFFFF;
}

OSG_END_NAMESPACE

#define OSGFIELDCONTAINERBASE_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGFIELDCONTAINERBASE_H_ */

