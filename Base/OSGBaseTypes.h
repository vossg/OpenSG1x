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

#ifndef _OSGBASETYPES_H_
#define _OSGBASETYPES_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGBase.h>

#if defined(OSG_SGI_TYPES) || defined (OSG_LINUX_TYPES) || \
    defined (OSG_SUNOS_TYPES)
#include <sys/types.h>
#endif

#include <stdlib.h>

#include <utility>

#include <float.h>
#include <string>
#include <stdio.h>

OSG_BEGIN_NAMESPACE

#if defined(OSG_SGI_TYPES)

/*! \var typedef char Char8;
 *  \brief Char8
 *  \ingroup BaseTypes
 */

typedef char           Char8;

/*! \var typedef unsigned char UChar8;
 *  \brief UChar8
 *  \ingroup BaseTypes
 */

typedef unsigned char UChar8;

/*! \var typedef signed signed char SChar8;
 *  \brief UChar8
 *  \ingroup BaseTypes
 */

typedef signed char   SChar8;

/*! \var typedef int8_t Int8;
 *  \brief Int8
 *  \ingroup BaseTypes
 */

typedef int8_t    Int8;

/*! \var typedef uint8_t UInt8;
 *  \brief UInt8
 *  \ingroup BaseTypes
 */

typedef uint8_t   UInt8;

/*! \var typedef int16_t Int16;
 *  \brief Int16
 *  \ingroup BaseTypes
 */

typedef int16_t   Int16;

/*! \var typedef uint16_t UInt16;
 *  \brief UInt16
 *  \ingroup BaseTypes
 */

typedef uint16_t  UInt16;

/*! \var typedef int32_t Int32;
 *  \brief Int32
 *  \ingroup BaseTypes
 */

typedef int32_t   Int32;

/*! \var typedef uint32_t UInt32;
 *  \brief UInt32
 *  \ingroup BaseTypes
 */

typedef uint32_t  UInt32;

/*! \var typedef int64_t Int64;
 *  \brief Int64
 *  \ingroup BaseTypes
 */

typedef int64_t   Int64;

/*! \var typedef uint64_t UInt64;
 *  \brief UInt64
 *  \ingroup BaseTypes
 */

typedef uint64_t  UInt64;

/*! \var typedef float Real32;
 *  \brief Real32
 *  \ingroup BaseTypes
 */

typedef float     Real32;

/*! \var typedef double Real64;
 *  \brief Real64
 *  \ingroup BaseTypes
 */

typedef double    Real64;

#elif defined(OSG_LINUX_TYPES)

/*! \var typedef char Char8;
 *  \brief Char8
 *  \ingroup BaseTypes
 */

typedef char           Char8;

/*! \var typedef unsigned char UChar8;
 *  \brief UChar8
 *  \ingroup BaseTypes
 */

typedef unsigned char UChar8;

/*! \var typedef signed char SChar8;
 *  \brief UChar8
 *  \ingroup BaseTypes
 */

typedef signed char   SChar8;

/*! \var typedef int8_t Int8;
 *  \brief Int8
 *  \ingroup BaseTypes
 */

typedef int8_t     Int8;

/*! \var typedef u_int8_t UInt8;
 *  \brief UInt8
 *  \ingroup BaseTypes
 */

typedef u_int8_t   UInt8;

/*! \var typedef int16_t Int16;
 *  \brief Int16
 *  \ingroup BaseTypes
 */

typedef int16_t    Int16;

/*! \var typedef u_int16_t UInt16;
 *  \brief UInt16
 *  \ingroup BaseTypes
 */

typedef u_int16_t  UInt16;

/*! \var typedef int32_t Int32;
 *  \brief Int32
 *  \ingroup BaseTypes
 */

typedef int32_t    Int32;

/*! \var typedef u_int32_t UInt32;
 *  \brief UInt32
 *  \ingroup BaseTypes
 */

typedef u_int32_t  UInt32;

/*! \var typedef int64_t Int64;
 *  \brief Int64
 *  \ingroup BaseTypes
 */

typedef int64_t    Int64;

/*! \var typedef u_int64_t UInt64;
 *  \brief UInt64
 *  \ingroup BaseTypes
 */

typedef u_int64_t  UInt64;

/*! \var typedef float Real32;
 *  \brief Real32
 *  \ingroup BaseTypes
 */

typedef float      Real32;

/*! \var typedef double Real64;
 *  \brief Real64
 *  \ingroup BaseTypes
 */

typedef double     Real64;

#elif defined(OSG_HPUX_TYPES)

/*! \var typedef char Char8;
 *  \brief Char8
 *  \ingroup BaseTypes
 */

typedef char           Char8;

/*! \var typedef unsigned char UChar8;
 *  \brief UChar8
 *  \ingroup BaseTypes
 */

typedef unsigned char UChar8;

/*! \var typedef signed char SChar8;
 *  \brief UChar8
 *  \ingroup BaseTypes
 */

typedef signed char   SChar8;

/*! \var typedef int8_t Int8;
 *  \brief Int8
 *  \ingroup BaseTypes
 */

typedef int8_t     Int8;

/*! \var typedef u_int8_t UInt8;
 *  \brief UInt8
 *  \ingroup BaseTypes
 */

typedef uint8_t   UInt8;

/*! \var typedef int16_t Int16;
 *  \brief Int16
 *  \ingroup BaseTypes
 */

typedef int16_t    Int16;

/*! \var typedef u_int16_t UInt16;
 *  \brief UInt16
 *  \ingroup BaseTypes
 */

typedef uint16_t  UInt16;

/*! \var typedef int32_t Int32;
 *  \brief Int32
 *  \ingroup BaseTypes
 */

typedef int32_t    Int32;

/*! \var typedef u_int32_t UInt32;
 *  \brief UInt32
 *  \ingroup BaseTypes
 */

typedef uint32_t  UInt32;

/*! \var typedef int64_t Int64;
 *  \brief Int64
 *  \ingroup BaseTypes
 */

typedef int64_t    Int64;

/*! \var typedef u_int64_t UInt64;
 *  \brief UInt64
 *  \ingroup BaseTypes
 */

typedef uint64_t  UInt64;

/*! \var typedef float Real32;
 *  \brief Real32
 *  \ingroup BaseTypes
 */

typedef float      Real32;

/*! \var typedef double Real64;
 *  \brief Real64
 *  \ingroup BaseTypes
 */

typedef double     Real64;

#elif defined(OSG_WIN_TYPES)

/*! \var typedef bool bool;
 *  \brief bool
 *  \ingroup BaseTypes
 */

#ifdef OSG_BOOL_IS_UNSIGNED
#ifndef bool
typedef unsigned      bool;
#endif
#endif

/*! \var typedef unsigned char Char8;
 *  \brief Char8
 *  \ingroup BaseTypes
 */

typedef CHAR           Char8;

/*! \var typedef unsigned char UChar8;
 *  \brief UChar8
 *  \ingroup BaseTypes
 */

typedef UCHAR         UChar8;

/*! \var typedef signed char SChar8;
 *  \brief UChar8
 *  \ingroup BaseTypes
 */

typedef signed char   SChar8;

/*! \var typedef CHAR Int8;
 *  \brief Int8
 *  \ingroup BaseTypes
 */

typedef signed char   Int8;

/*! \var typedef UCHAR UInt8;
 *  \brief UInt8
 *  \ingroup BaseTypes
 */

typedef UCHAR   UInt8;

/*! \var typedef SHORT Int16;
 *  \brief Int16
 *  \ingroup BaseTypes
 */

typedef SHORT   Int16;

/*! \var typedef USHORT UInt16;
 *  \brief UInt16
 *  \ingroup BaseTypes
 */

typedef USHORT  UInt16;

/*! \var typedef INT32 Int32;
 *  \brief Int32
 *  \ingroup BaseTypes
 */

typedef INT32   Int32;

/*! \var typedef UINT32 UInt32;
 *  \brief UInt32
 *  \ingroup BaseTypes
 */

typedef UINT32  UInt32;

/*! \var typedef INT64 Int64;
 *  \brief Int64
 *  \ingroup BaseTypes
 */

typedef INT64   Int64;

/*! \var typedef UINT64 UInt64;
 *  \brief UInt64
 *  \ingroup BaseTypes
 */

typedef UINT64  UInt64;

/*! \var typedef DWORD DWord;
 *  \brief DWord
 *  \ingroup BaseTypes
 */

typedef DWORD   DWord;

/*! \var typedef HANDLE Handle;
 *  \brief Handle
 *  \ingroup BaseTypes
 */

typedef HANDLE  Handle;

/*! \var typedef float Real32;
 *  \brief Real32
 *  \ingroup BaseTypes
 */

typedef float     Real32;

/*! \var typedef double Real64;
 *  \brief Real64
 *  \ingroup BaseTypes
 */

typedef double    Real64;

#elif defined(OSG_SUNOS_TYPES)

/*! \var typedef char Char8;
 *  \brief Char8
 *  \ingroup BaseTypes
 */

typedef char           Char8;

/*! \var typedef unsigned char UChar8;
 *  \brief UChar8
 *  \ingroup BaseTypes
 */

typedef unsigned char UChar8;

/*! \var typedef signed char SChar8;
 *  \brief UChar8
 *  \ingroup BaseTypes
 */

typedef signed char   SChar8;

/*! \var typedef int8_t Int8;
 *  \brief Int8
 *  \ingroup BaseTypes
 */

typedef int8_t     Int8;

/*! \var typedef uint8_t UInt8;
 *  \brief UInt8
 *  \ingroup BaseTypes
 */

typedef uint8_t   UInt8;

/*! \var typedef int16_t Int16;
 *  \brief Int16
 *  \ingroup BaseTypes
 */

typedef int16_t    Int16;

/*! \var typedef uint16_t UInt16;
 *  \brief UInt16
 *  \ingroup BaseTypes
 */

typedef uint16_t  UInt16;

/*! \var typedef int32_t Int32;
 *  \brief Int32
 *  \ingroup BaseTypes
 */

typedef int32_t    Int32;

/*! \var typedef uint32_t UInt32;
 *  \brief UInt32
 *  \ingroup BaseTypes
 */

typedef uint32_t  UInt32;

/*! \var typedef long long Int64;
 *  \brief Int64
 *  \ingroup BaseTypes
 */

typedef long long    Int64;

/*! \var typedef unsigned long long UInt64;
 *  \brief UInt64
 *  \ingroup BaseTypes
 */

typedef unsigned long long  UInt64;

/*! \var typedef float Real32;
 *  \brief Real32
 *  \ingroup BaseTypes
 */

typedef float      Real32;

/*! \var typedef double Real64;
 *  \brief Real64
 *  \ingroup BaseTypes
 */

typedef double     Real64;

#else
#error "Could not define base types, check your system/compiler combination"
#endif

/*! \var UInt32 BitVector;
 *  \brief BitVector
 *  \ingroup BaseTypes
 */

typedef UInt32 BitVector;

/*! \var UInt8 *MemoryHandle;
 *  \brief Handle to raw memory
 *  \ingroup BaseTypes
 */

typedef UInt8 *MemoryHandle;

/*! \brief Eps
 *  \ingroup BaseConstants
 */

const Real32 Eps = 1E-6f;

/*! \brief Pi
 *  \ingroup BaseConstants
 */

const Real32 Pi  = (Real32) 3.141592653589793;

/*! \brief sqrt(2)
 *  \ingroup BaseConstants
 */

const Real32 Sqrt2  = (Real32) 1.41421356237309504;

/*! positive infinity
 *  \ingroup BaseConstants
 */

const Real32 Inf = 1E30;

/*! negative infinity
 *  \ingroup BaseConstants
 */

const Real32 NegInf = - 1E30;

/*! \brief MathTypeProperties
 *  \ingroup BaseConstants
 */

enum MathTypeProperties
{
    RealValue,
    IntValue,
    BoolValue
};

OSG_END_NAMESPACE

#include <OSGBaseTypeTraits.h>

#define OSGBASETPYES_HEADER_CVSID "@(#)$Id: $"

#endif /* OSGBASETYPES_H */
