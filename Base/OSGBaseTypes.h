
/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGConfig.h>
#include <OSGBase.h>

#if defined(OSG_SGI_TYPES) || defined (OSG_LINUX_TYPES) || \
    defined (OSG_SUNOS_TYPES)
#include <sys/types.h>
#endif

#include <stdlib.h>

#include <utility>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

#if defined(OSG_SGI_TYPES)

/*! \var typedef bool Bool;
 *  \brief Bool
 *  \ingroup BaseTypes
 */

typedef bool          Bool;

/*! \var typedef char Char8;
 *  \brief Char8
 *  \ingroup BaseTypes
 */

typedef char          Char8;

/*! \var typedef unsigned char UChar8;
 *  \brief UChar8
 *  \ingroup BaseTypes
 */

typedef unsigned char UChar8;

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

/*! \var typedef bool Bool;
 *  \brief Bool
 *  \ingroup BaseTypes
 */

typedef bool          Bool;

/*! \var typedef char Char8;
 *  \brief Char8
 *  \ingroup BaseTypes
 */

typedef char          Char8;

/*! \var typedef unsigned char UChar8;
 *  \brief UChar8
 *  \ingroup BaseTypes
 */

typedef unsigned char UChar8;

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

#elif defined(OSG_WIN_TYPES)

/*! \var typedef bool Bool;
 *  \brief Bool
 *  \ingroup BaseTypes
 */

#ifdef OSG_BOOL_IS_UNSIGNED
#ifndef Bool
typedef unsigned      Bool;
#endif
#else
typedef bool          Bool;
#endif

/*! \var typedef char Char8;
 *  \brief Char8
 *  \ingroup BaseTypes
 */

typedef char          Char8;

/*! \var typedef unsigned char UChar8;
 *  \brief UChar8
 *  \ingroup BaseTypes
 */

typedef unsigned char UChar8;

/*! \var typedef CHAR Int8;
 *  \brief Int8
 *  \ingroup BaseTypes
 */

typedef CHAR    Int8;

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

/*! \var typedef bool Bool;
 *  \brief Bool
 *  \ingroup BaseTypes
 */

typedef bool          Bool;

/*! \var typedef charChar8;
 *  \brief Char8
 *  \ingroup BaseTypes
 */

typedef char          Char8;

/*! \var typedef unsigned char UChar8;
 *  \brief UChar8
 *  \ingroup BaseTypes
 */

typedef unsigned char UChar8;

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

/*! \brief Eps
 *  \ingroup BaseConstants
 */

const Real32 Eps = 1E-7f;

/*! \brief Eps
 *  \ingroup BaseConstants
 */

const Real32 Pi  = (Real32) 3.141592653589797;

/*! \brief MathTypeProperties
 *  \ingroup BaseConstants
 */

enum MathTypeProperties
{
    RealValue,
    IntValue
};

/*! \brief TypeConstantsBase, documentation dummy
 *  \ingroup BaseConstants
 */

struct OSG_BASE_DLLMAPPING TypeConstantsBase
{
};

/*! \brief TypeConstants
 *  \ingroup BaseConstants
 */

template <class LookupTypeT>
struct OSG_BASE_DLLMAPPING TypeConstants : public TypeConstantsBase
{
};

/*! \brief TypeConstants<UInt8>
 *  \ingroup BaseConstants
 */

template <> 
struct TypeConstants<UInt8> : public TypeConstantsBase
{
    typedef       Real32 RealReturnType;

    static inline UInt8 getZeroElement(void) { return 0; };
    static inline UInt8 getOneElement (void) { return 1; };

    static inline UInt8 getAllSet     (void) { return 0xFF; };
    static inline UInt8 getAllClear   (void) { return 0x00; };

    static inline UInt8 getMax        (void) { return 0xFF; }; 
    static inline UInt8 getMin        (void) { return 0x00; }; 


    static inline Real32 getFraction   (UInt8 val) 
    {
        return (Real32(val) / Real32(getMax())); 
    };
    static inline UInt8 getPortion    (Real32 val) 
    {
        return (UInt8) (val * Real32(getMax())); 
    };


    static inline MathTypeProperties getProp(void) { return IntValue; };


    static inline UInt8 getFromString (const Char8 *szString)
    {
        if(szString != NULL)
            return atoi(szString);
        else
            return getZeroElement();
    }
};

/*! \brief TypeConstants<Int8>
 *  \ingroup BaseConstants
 */

template <> 
struct TypeConstants<Int8> : public TypeConstantsBase
{
    typedef       Real32 RealReturnType;

    static inline Int8 getZeroElement(void) { return 0; };
    static inline Int8 getOneElement (void) { return 1; };

    static inline Int8 getAllSet     (void) { return 0xFF; };
    static inline Int8 getAllClear   (void) { return 0x00; };

    static inline Int8 getMax        (void) { return  0x7F; }; 
    static inline Int8 getMin        (void) { return -0x7F; }; 


    static inline Real32 getFraction   (Int8 val) 
    {
        return (Real32(val) / Real32(getMax())); 
    };
    static inline Int8 getPortion    (Real32 val) 
    {
        return (Int8) (val * Real32(getMax())); 
    };


    static inline MathTypeProperties getProp(void) { return IntValue; };


    static inline Int8 getFromString (const Char8 *szString)
    {
        if(szString != NULL)
            return atoi(szString);
        else
            return getZeroElement();
    }
};

/*! \brief TypeConstants<UInt16>
 *  \ingroup BaseConstants
 */

template <> 
struct TypeConstants<UInt16> : public TypeConstantsBase
{
    typedef       Real32 RealReturnType;

    static inline UInt16 getZeroElement(void) { return 0; };
    static inline UInt16 getOneElement (void) { return 1; };

    static inline UInt16 getAllSet     (void) { return 0xFFFF; };
    static inline UInt16 getAllClear   (void) { return 0x0000; };

    static inline UInt16 getMax        (void) { return 0xFFFF; };
    static inline UInt16 getMin        (void) { return 0x0000; };


    static inline Real32 getFraction   (UInt16 val) 
    {
        return (Real32(val) / Real32(getMax())); 
    };
    static inline UInt16 getPortion    (Real32 val) 
    {
        return (UInt16) (val * Real32(getMax())); 
    };


    static inline MathTypeProperties getProp(void) { return IntValue; };


    static inline UInt16 getFromString (const Char8 *szString)
    {
        if(szString != NULL)
            return atoi(szString);
        else
            return getZeroElement();
    }
};

/*! \brief TypeConstants<Int16>
 *  \ingroup BaseConstants
 */

template <> 
struct TypeConstants<Int16> : public TypeConstantsBase
{
    typedef       Real32 RealReturnType;

    static inline Int16 getZeroElement(void) { return 0; };
    static inline Int16 getOneElement (void) { return 1; };

    static inline Int16 getAllSet(void)      { return 0xFFFF; };
    static inline Int16 getAllClear(void)    { return 0x0000; };

    static inline Int16 getMax(void)         { return  0x7FFF; };
    static inline Int16 getMin(void)         { return -0x7FFF; };


    static inline Real32 getFraction   (Int16 val) 
    {
        return (Real32(val) / Real32(getMax())); 
    };
    static inline Int16 getPortion    (Real32 val) 
    {
        return (Int16) (val * Real32(getMax())); 
    };


    static inline MathTypeProperties getProp(void) { return IntValue; };


    static inline Int16 getFromString (const Char8 *szString)
    {
        if(szString != NULL)
            return atoi(szString);
        else
            return getZeroElement();
    }
};

/*! \brief TypeConstants<UInt32>
 *  \ingroup BaseConstants
 */

template <> 
struct TypeConstants<UInt32> : public TypeConstantsBase
{
    typedef       Real32 RealReturnType;

    static inline UInt32 getZeroElement(void) { return 0; };
    static inline UInt32 getOneElement (void) { return 1; };

    static inline UInt32 getAllSet(void)      { return 0xFFFFFFFF; };
    static inline UInt32 getAllClear(void)    { return 0x00000000; };

    static inline UInt32 getMax(void)         { return 0xFFFFFFFF; };
    static inline UInt32 getMin(void)         { return 0x00000000; };


    static inline Real32 getFraction   (UInt32 val) 
    {
        return (Real32(val) / Real32(getMax())); 
    };
    static inline UInt32 getPortion    (Real32 val) 
    {
        return (UInt32) (val * Real32(getMax())); 
    };


    static inline MathTypeProperties getProp(void) { return IntValue; };


    static inline UInt32 getFromString (const Char8 *szString)
    {
        if(szString != NULL)
            return atol(szString);
        else
            return getZeroElement();
    }
};

/*! \brief TypeConstants<Int32>
 *  \ingroup BaseConstants
 */

template <> 
struct TypeConstants<Int32> : public TypeConstantsBase
{
    typedef       Real32 RealReturnType;

    static inline Int32 getZeroElement(void) { return 0; };
    static inline Int32 getOneElement (void) { return 1; };

    static inline Int32 getAllSet     (void) { return 0xFFFFFFFF; };
    static inline Int32 getAllClear   (void) { return 0x00000000; };

    static inline Int32 getMax        (void) { return  0x7FFFFFFF; };
    static inline Int32 getMin        (void) { return -0x7FFFFFFF; };


    static inline Real32 getFraction   (Int32 val) 
    {
        return (Real32(val) / Real32(getMax())); 
    };
    static inline Int32 getPortion    (Real32 val) 
    {
        return (Int32) (val * Real32(getMax())); 
    };


    static inline MathTypeProperties getProp(void) { return IntValue; };


    static inline Int32 getFromString (const Char8 *szString)
    {
        if(szString != NULL)
            return atol(szString);
        else
            return getZeroElement();
    }
};

/*! \brief TypeConstants<UInt64>
 *  \ingroup BaseConstants
 */

template <> 
struct TypeConstants<UInt64> : public TypeConstantsBase
{
    typedef       Real32 RealReturnType;

    static inline UInt64 getZeroElement(void) { return 0; };
    static inline UInt64 getOneElement (void) { return 1; };

#ifdef OSG_LONGLONG_HAS_LL
    static inline UInt64 getAllSet  (void) { return 0xFFFFFFFFFFFFFFFFLL; };
    static inline UInt64 getAllClear(void) { return 0x0000000000000000LL; };

    static inline UInt64 getMin     (void) { return 0xFFFFFFFFFFFFFFFFLL; };
    static inline UInt64 getMax     (void) { return 0x0000000000000000LL; };
#else
    static inline UInt64 getAllSet  (void) { return 0xFFFFFFFFFFFFFFFF; };
    static inline UInt64 getAllClear(void) { return 0x0000000000000000; };

    static inline UInt64 getMin     (void) { return 0xFFFFFFFFFFFFFFFF; };
    static inline UInt64 getMax     (void) { return 0x0000000000000000; };
#endif

    static inline Real32 getFraction   (UInt64 val) 
    {
        return (Real32(val) / Real32(getMax())); 
    };
    static inline UInt64 getPortion    (Real32 val) 
    {
        return (UInt64) (val * Real32(getMax())); 
    };


    static inline MathTypeProperties getProp(void) { return IntValue; };


    static inline UInt64 getFromString (const Char8 *szString)
    {
#ifndef __sun
        if(szString != NULL)
#ifndef WIN32
            return atoll(szString);
#else
            return _atoi64(szString);
#endif
        else
#endif 
            return getZeroElement();
    }
};

/*! \brief TypeConstants<Int64>
 *  \ingroup BaseConstants
 */

template <> 
struct TypeConstants<Int64> : public TypeConstantsBase
{
    typedef       Real32 RealReturnType;

    static inline Int64 getZeroElement(void) { return 0; };
    static inline Int64 getOneElement (void) { return 1; };

#ifdef OSG_LONGLONG_HAS_LL
    static inline Int64 getAllSet(void)   { return 0xFFFFFFFFFFFFFFFFLL; };
    static inline Int64 getAllClear(void) { return 0x0000000000000000LL; };

    static inline Int64 getMax(void)      { return -0x7FFFFFFFFFFFFFFFLL; };
    static inline Int64 getMin(void)      { return  0x7FFFFFFFFFFFFFFFLL; };
#else
    static inline Int64 getAllSet(void)   { return 0xFFFFFFFFFFFFFFFF; };
    static inline Int64 getAllClear(void) { return 0x0000000000000000; };

    static inline Int64 getMax(void)      { return -0x7FFFFFFFFFFFFFFF; };
    static inline Int64 getMin(void)      { return  0x7FFFFFFFFFFFFFFF; };
#endif


    static inline Real32 getFraction   (Int64 val) 
    {
        return (Real32(val) / Real32(getMax())); 
    };
    static inline Int64 getPortion    (Real32 val) 
    {
        return (Int64) (val * Real32(getMax())); 
    };


    static inline MathTypeProperties getProp(void) { return IntValue; };


    static inline Int64 getFromString (const Char8 *szString)
    {
#ifndef __sun
        if(szString != NULL)
#ifndef WIN32
            return atoll(szString);
#else
            return _atoi64(szString);
#endif
        else
#endif 
            return getZeroElement();
    }
};

/*! \brief TypeConstants<Real64>
 *  \ingroup BaseConstants
 */

template <>
struct TypeConstants<Real64> : public TypeConstantsBase
{
    typedef       Real64 RealReturnType;

    static inline Real64 getZeroElement(void)           { return 0.; };
    static inline Real64 getOneElement (void)           { return 1.; };

    static inline Real64 getFraction   (Real64 rVal) { return rVal; };
    static inline Real64 getPortion    (Real64 rVal) { return rVal; };

    static inline MathTypeProperties getProp(void) { return RealValue; };

    static inline Real64 getFromString (const Char8 *szString)
    {
        if(szString != NULL)
            return atof(szString);
        else
            return getZeroElement();
    }
};

/*! \brief TypeConstants<Real32>
 *  \ingroup BaseConstants
 */

template <>
struct TypeConstants<Real32> : public TypeConstantsBase
{
    typedef       Real32 RealReturnType;

    static inline Real32 getZeroElement(void) { return 0.; };
    static inline Real32 getOneElement (void) { return 1.; };

    static inline Real32 getFraction   (Real32 rVal) { return rVal; };
    static inline Real32 getPortion    (Real32 rVal) { return rVal; };

    static inline MathTypeProperties getProp(void) { return RealValue; };

    static inline Real32 getFromString (const Char8 *szString)
    {
        if(szString != NULL)
            return atof(szString);
        else
            return getZeroElement();
    }
};

OSG_END_NAMESPACE

#endif /* OSGBASETYPES_H */




