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

#ifndef _OSGBASETYPES_H_
#define _OSGBASETYPES_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGBase.h"
#include "OSGReal16.h"

#if defined(OSG_SGI_TYPES) || defined (OSG_LINUX_TYPES) || \
    defined(OSG_SUNOS_TYPES)
#include <sys/types.h>
#endif

#include <stdlib.h>

#include <utility>

#include <float.h>
#include <string>
#include <stdio.h>

#if defined(OSG_LINUX_TYPES)
#    include <inttypes.h>
#endif

OSG_BEGIN_NAMESPACE

#if defined(OSG_SGI_TYPES)

/*! \var typedef char Char8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef char           Char8;

/*! \var typedef unsigned char UChar8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef unsigned char UChar8;

/*! \var typedef signed signed char SChar8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef signed char   SChar8;

/*! \var typedef int8_t Int8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef int8_t    Int8;

/*! \var typedef uint8_t UInt8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef uint8_t   UInt8;

/*! \var typedef int16_t Int16;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef int16_t   Int16;

/*! \var typedef uint16_t UInt16;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef uint16_t  UInt16;

/*! \var typedef int32_t Int32;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef int32_t   Int32;

/*! \var typedef uint32_t UInt32;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef uint32_t  UInt32;

/*! \var typedef int64_t Int64;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef int64_t   Int64;

/*! \var typedef uint64_t UInt64;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef uint64_t  UInt64;

/*! \var typedef float Real32;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef float     Real32;

/*! \var typedef double Real64;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef double    Real64;

/*! \var typedef long double Real128;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef long double Real128;

#elif defined(OSG_LINUX_TYPES)

/*! \var typedef char Char8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef char           Char8;

/*! \var typedef unsigned char UChar8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef unsigned char UChar8;

/*! \var typedef signed char SChar8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef signed char   SChar8;

/*! \var typedef int8_t Int8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef int8_t     Int8;

/*! \var typedef u_int8_t UInt8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef uint8_t   UInt8;

/*! \var typedef int16_t Int16;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef int16_t    Int16;

/*! \var typedef u_int16_t UInt16;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef uint16_t  UInt16;

/*! \var typedef int32_t Int32;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef int32_t    Int32;

/*! \var typedef u_int32_t UInt32;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef uint32_t  UInt32;

/*! \var typedef int64_t Int64;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef int64_t    Int64;

/*! \var typedef u_int64_t UInt64;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef uint64_t  UInt64;

/*! \var typedef float Real32;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef float      Real32;

/*! \var typedef double Real64;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef double     Real64;

/*! \var typedef long double Real128;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef long double Real128;

#elif defined(OSG_HPUX_TYPES)

/*! \var typedef char Char8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef char           Char8;

/*! \var typedef unsigned char UChar8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef unsigned char UChar8;

/*! \var typedef signed char SChar8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef signed char   SChar8;

/*! \var typedef int8_t Int8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef int8_t     Int8;

/*! \var typedef u_int8_t UInt8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef uint8_t   UInt8;

/*! \var typedef int16_t Int16;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef int16_t    Int16;

/*! \var typedef u_int16_t UInt16;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef uint16_t  UInt16;

/*! \var typedef int32_t Int32;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef int32_t    Int32;

/*! \var typedef u_int32_t UInt32;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef uint32_t  UInt32;

/*! \var typedef int64_t Int64;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef int64_t    Int64;

/*! \var typedef u_int64_t UInt64;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef uint64_t  UInt64;

/*! \var typedef float Real32;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef float      Real32;

/*! \var typedef double Real64;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef double     Real64;

/*! \var typedef long double Real128;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef long double Real128;

#elif defined(OSG_WIN_TYPES)

/*! \var typedef bool bool;
 *  \ingroup GrpBaseBaseBaseTypes
 */

#ifdef OSG_BOOL_IS_UNSIGNED
#ifndef bool
typedef unsigned      bool;
#endif
#endif

/*! \var typedef unsigned char Char8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef CHAR           Char8;

/*! \var typedef unsigned char UChar8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef UCHAR         UChar8;

/*! \var typedef signed char SChar8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef signed char   SChar8;

/*! \var typedef CHAR Int8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef signed char   Int8;

/*! \var typedef UCHAR UInt8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef UCHAR   UInt8;

/*! \var typedef SHORT Int16;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef SHORT   Int16;

/*! \var typedef USHORT UInt16;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef USHORT  UInt16;

/*! \var typedef INT32 Int32;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef INT32   Int32;

/*! \var typedef UINT32 UInt32;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef UINT32  UInt32;

/*! \var typedef INT64 Int64;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef INT64   Int64;

/*! \var typedef UINT64 UInt64;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef UINT64  UInt64;

/*! \var typedef DWORD DWord;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef DWORD   DWord;

/*! \var typedef HANDLE Handle;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef HANDLE  Handle;

/*! \var typedef float Real32;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef float     Real32;

/*! \var typedef double Real64;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef double    Real64;

/*! \var typedef long double Real128;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef long double Real128;

#elif defined(OSG_SUN_TYPES)

/*! \var typedef char Char8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef char           Char8;

/*! \var typedef unsigned char UChar8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef unsigned char UChar8;

/*! \var typedef signed char SChar8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef signed char   SChar8;

/*! \var typedef int8_t Int8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef int8_t     Int8;

/*! \var typedef uint8_t UInt8;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef uint8_t   UInt8;

/*! \var typedef int16_t Int16;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef int16_t    Int16;

/*! \var typedef uint16_t UInt16;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef uint16_t  UInt16;

/*! \var typedef int32_t Int32;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef int32_t    Int32;

/*! \var typedef uint32_t UInt32;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef uint32_t  UInt32;

/*! \var typedef long long Int64;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef long long    Int64;

/*! \var typedef unsigned long long UInt64;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef unsigned long long  UInt64;

/*! \var typedef float Real32;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef float      Real32;

/*! \var typedef double Real64;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef double     Real64;

/*! \var typedef long double Real128;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef long double Real128;

#else
#error "Could not define base types, check your system/compiler combination"
#endif

/*! \var UInt64 BitVector;
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef UInt64 BitVector;

/*! \var UInt8 *MemoryHandle;
 *  Handle to raw memory
 *  \ingroup GrpBaseBaseBaseTypes
 */

typedef UInt8 *MemoryHandle;

/*! \ingroup GrpBaseBaseConstants
 */

const Real32 Eps = 1E-6f;

/*! \ingroup GrpBaseBaseConstants
 */

const Real32 Pi  = 3.141592653589793f;

/*! \ingroup GrpBaseBaseConstants
 */

const Real32 Sqrt2  = 1.41421356237309504f;

/*! \ingroup GrpBaseBaseConstants
 */

const Real32 Inf = 1E30f;

/*! \ingroup GrpBaseBaseConstants
 */

const Real32 NegInf = - 1E30f;

#ifdef WIN32

/*! \ingroup GrpBaseBaseConstants
 */

const Char8 PluginExt[]     = ".dll";

/*! \ingroup GrpBaseBaseConstants
 */

const Char8 PluginPattern[] = "*.dll";

/*! \ingroup GrpBaseBaseConstants
 */

const Char8  DirSep    = '\\';

#elif defined(__APPLE__)

/*! \ingroup GrpBaseBaseConstants
 */

const Char8 PluginExt[]     = ".dylib";

/*! \ingroup GrpBaseBaseConstants
 */

const Char8 PluginPattern[] = "*.dylib";

/*! \ingroup GrpBaseBaseConstants
 */

const Char8  DirSep    = '/';

#else

/*! \ingroup GrpBaseBaseConstants
 */

const Char8 PluginExt[]     = ".so";

/*! \ingroup GrpBaseBaseConstants
 */

const Char8 PluginPattern[] = "*.so";

/*! \ingroup GrpBaseBaseConstants
 */

const Char8  DirSep    = '/';

#endif

/*! MathTypeProperties
 *  \ingroup GrpBaseBaseConstants
 */

enum MathTypeProperties
{
    RealValue,
    IntValue,
    BoolValue
};

struct SyncInfo
{
    BitVector syncMode;
    UInt32    uiSyncInfo;
    UInt32    uiCopyOffset;
};

OSG_END_NAMESPACE

#include "OSGBaseTypeTraits.h"

#define OSGBASETPYES_HEADER_CVSID "@(#)$Id: $"

#endif /* OSGBASETYPES_H */
