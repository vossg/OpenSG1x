/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
 *                                                                           *
 *          contact: {reiners|vossg}@igd.fhg.de, jbehr@zgdv.de               *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

#ifdef OSG_WIN_TYPES
#include <winsock2.h>
#include <windows.h>
#endif

#if defined(OSG_SGI_TYPES) || defined (OSG_LINUX_TYPES) || \
    defined (OSG_SUNOS_TYPES)
#include <sys/types.h>
#endif

#include <stdlib.h>

#include <utility>

OSG_BEGIN_NAMESPACE

/** \defgroup BaseLib BaseLib
 *  \brief This lib contains all base elements like vectors, matrices.
 */

/** OSG Base Types 
 */

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

#if defined(OSG_SGI_TYPES)

/// OSGBool
typedef bool          OSGBool;

/// OSGChar 
typedef char          OSGChar;

/// OSGUChar 
typedef unsigned char OSGUChar;

/// OSGChar8 
typedef char          OSGChar8;

// OSGUChar8
typedef unsigned char OSGUChar8;

// OSGInt8
typedef int8_t    OSGInt8;

// OSGUInt8
typedef uint8_t   OSGUInt8;

// OSGInt16
typedef int16_t   OSGInt16;

// OSGUInt16
typedef uint16_t  OSGUInt16;

// OSGInt32
typedef int32_t   OSGInt32;

// OSGUInt32
typedef uint32_t  OSGUInt32;

// OSGInt64
typedef int64_t   OSGInt64;

// OSGUInt64
typedef uint64_t  OSGUInt64;

// OSGReal32
typedef float     OSGReal32;

//  OSGReal64
typedef double    OSGReal64;

#elif defined(OSG_LINUX_TYPES)

typedef bool          OSGBool;
typedef char          OSGChar;
typedef unsigned char OSGUChar;
typedef char          OSGChar8;
typedef unsigned char OSGUChar8;

typedef int8_t     OSGInt8;
typedef u_int8_t   OSGUInt8;
typedef int16_t    OSGInt16;
typedef u_int16_t  OSGUInt16;
typedef int32_t    OSGInt32;
typedef u_int32_t  OSGUInt32;
typedef int64_t    OSGInt64;
typedef u_int64_t  OSGUInt64;

typedef float      OSGReal32;
typedef double     OSGReal64;

#elif defined(OSG_WIN_TYPES)

typedef bool          OSGBool;
typedef char          OSGChar;
typedef unsigned char OSGUChar;
typedef char          OSGChar8;
typedef unsigned char OSGUChar8;

typedef CHAR    OSGInt8;
typedef UCHAR   OSGUInt8;
typedef SHORT   OSGInt16;
typedef USHORT  OSGUInt16;
typedef INT32   OSGInt32;
typedef UINT32  OSGUInt32;
typedef INT64   OSGInt64;
typedef UINT64  OSGUInt64;

typedef DWORD   OSGDWord;
typedef HANDLE  OSGHandle;

typedef float     OSGReal32;
typedef double    OSGReal64;

#elif defined(OSG_SUNOS_TYPES)

typedef bool          OSGBool;
typedef char          OSGChar;
typedef unsigned char OSGUChar;
typedef char          OSGChar8;
typedef unsigned char OSGUChar8;

typedef int8_t     OSGInt8;
typedef uint8_t   OSGUInt8;
typedef int16_t    OSGInt16;
typedef uint16_t  OSGUInt16;
typedef int32_t    OSGInt32;
typedef uint32_t  OSGUInt32;
typedef long long    OSGInt64;
typedef unsigned long long  OSGUInt64;

typedef float      OSGReal32;
typedef double     OSGReal64;

#else
#error "Could not define base types, check your system/compiler combination"
#endif

typedef OSGUInt32 OSGBitVector;

const OSGReal32 osgEps = 1E-7f;
const OSGReal32 osgPi  = (OSGReal32) 3.14159265359797;

enum OSGMathTypeProperties
{
    OSGRealValue,
    OSGIntValue
};

template <class OSGLookupTypeT>
struct OSGTypeConstants
{
};

template <> 
struct OSGTypeConstants<OSGUInt8>
{
    typedef       OSGReal32 OSGRealReturnType;

    static inline OSGUInt8 getZeroElement(void) { return 0; };
    static inline OSGUInt8 getOneElement (void) { return 1; };

    static inline OSGUInt8 getAllSet     (void) { return 0xFF; };
    static inline OSGUInt8 getAllClear   (void) { return 0x00; };

    static inline OSGUInt8 getMax        (void) { return 0xFF; }; 
    static inline OSGUInt8 getMin        (void) { return 0x00; }; 


    static inline OSGReal32 getFraction   (OSGUInt8 val) 
    {
        return (OSGReal32(val) / OSGReal32(getMax())); 
    };
    static inline OSGUInt8 getPortion    (OSGReal32 val) 
    {
        return (OSGUInt8) (val * OSGReal32(getMax())); 
    };


    static inline OSGMathTypeProperties getProp(void) { return OSGIntValue; };


    static inline OSGUInt8 getFromString (const char *szString)
    {
        if(szString != NULL)
            return atoi(szString);
        else
            return getZeroElement();
    }
};

template <> 
struct OSGTypeConstants<OSGInt8>
{
    typedef       OSGReal32 OSGRealReturnType;

    static inline OSGInt8 getZeroElement(void) { return 0; };
    static inline OSGInt8 getOneElement (void) { return 1; };

    static inline OSGInt8 getAllSet     (void) { return 0xFF; };
    static inline OSGInt8 getAllClear   (void) { return 0x00; };

    static inline OSGInt8 getMax        (void) { return  0x7F; }; 
    static inline OSGInt8 getMin        (void) { return -0x7F; }; 


    static inline OSGReal32 getFraction   (OSGInt8 val) 
    {
        return (OSGReal32(val) / OSGReal32(getMax())); 
    };
    static inline OSGInt8 getPortion    (OSGReal32 val) 
    {
        return (OSGInt8) (val * OSGReal32(getMax())); 
    };


    static inline OSGMathTypeProperties getProp(void) { return OSGIntValue; };


    static inline OSGInt8 getFromString (const char *szString)
    {
        if(szString != NULL)
            return atoi(szString);
        else
            return getZeroElement();
    }
};

template <> 
struct OSGTypeConstants<OSGUInt16>
{
    typedef       OSGReal32 OSGRealReturnType;

    static inline OSGUInt16 getZeroElement(void) { return 0; };
    static inline OSGUInt16 getOneElement (void) { return 1; };

    static inline OSGUInt16 getAllSet     (void) { return 0xFFFF; };
    static inline OSGUInt16 getAllClear   (void) { return 0x0000; };

    static inline OSGUInt16 getMax        (void) { return 0xFFFF; };
    static inline OSGUInt16 getMin        (void) { return 0x0000; };


    static inline OSGReal32 getFraction   (OSGUInt16 val) 
    {
        return (OSGReal32(val) / OSGReal32(getMax())); 
    };
    static inline OSGUInt16 getPortion    (OSGReal32 val) 
    {
        return (OSGUInt16) (val * OSGReal32(getMax())); 
    };


    static inline OSGMathTypeProperties getProp(void) { return OSGIntValue; };


    static inline OSGUInt16 getFromString (const char *szString)
    {
        if(szString != NULL)
            return atoi(szString);
        else
            return getZeroElement();
    }
};

template <> 
struct OSGTypeConstants<OSGInt16>
{
    typedef       OSGReal32 OSGRealReturnType;

    static inline OSGInt16 getZeroElement(void) { return 0; };
    static inline OSGInt16 getOneElement (void) { return 1; };

    static inline OSGInt16 getAllSet(void)      { return 0xFFFF; };
    static inline OSGInt16 getAllClear(void)    { return 0x0000; };

    static inline OSGInt16 getMax(void)         { return  0x7FFF; };
    static inline OSGInt16 getMin(void)         { return -0x7FFF; };


    static inline OSGReal32 getFraction   (OSGInt16 val) 
    {
        return (OSGReal32(val) / OSGReal32(getMax())); 
    };
    static inline OSGInt16 getPortion    (OSGReal32 val) 
    {
        return (OSGInt16) (val * OSGReal32(getMax())); 
    };


    static inline OSGMathTypeProperties getProp(void) { return OSGIntValue; };


    static inline OSGInt16 getFromString (const char *szString)
    {
        if(szString != NULL)
            return atoi(szString);
        else
            return getZeroElement();
    }
};

template <> 
struct OSGTypeConstants<OSGUInt32>
{
    typedef       OSGReal32 OSGRealReturnType;

    static inline OSGUInt32 getZeroElement(void) { return 0; };
    static inline OSGUInt32 getOneElement (void) { return 1; };

    static inline OSGUInt32 getAllSet(void)      { return 0xFFFFFFFF; };
    static inline OSGUInt32 getAllClear(void)    { return 0x00000000; };

    static inline OSGUInt32 getMax(void)         { return 0xFFFFFFFF; };
    static inline OSGUInt32 getMin(void)         { return 0x00000000; };


    static inline OSGReal32 getFraction   (OSGUInt32 val) 
    {
        return (OSGReal32(val) / OSGReal32(getMax())); 
    };
    static inline OSGUInt32 getPortion    (OSGReal32 val) 
    {
        return (OSGUInt32) (val * OSGReal32(getMax())); 
    };


    static inline OSGMathTypeProperties getProp(void) { return OSGIntValue; };


    static inline OSGUInt32 getFromString (const char *szString)
    {
        if(szString != NULL)
            return atol(szString);
        else
            return getZeroElement();
    }
};

template <> 
struct OSGTypeConstants<OSGInt32>
{
    typedef       OSGReal32 OSGRealReturnType;

    static inline OSGInt32 getZeroElement(void) { return 0; };
    static inline OSGInt32 getOneElement (void) { return 1; };

    static inline OSGInt32 getAllSet     (void) { return 0xFFFFFFFF; };
    static inline OSGInt32 getAllClear   (void) { return 0x00000000; };

    static inline OSGInt32 getMax        (void) { return  0x7FFFFFFF; };
    static inline OSGInt32 getMin        (void) { return -0x7FFFFFFF; };


    static inline OSGReal32 getFraction   (OSGInt32 val) 
    {
        return (OSGReal32(val) / OSGReal32(getMax())); 
    };
    static inline OSGInt32 getPortion    (OSGReal32 val) 
    {
        return (OSGInt32) (val * OSGReal32(getMax())); 
    };


    static inline OSGMathTypeProperties getProp(void) { return OSGIntValue; };


    static inline OSGInt32 getFromString (const char *szString)
    {
        if(szString != NULL)
            return atol(szString);
        else
            return getZeroElement();
    }
};

template <> 
struct OSGTypeConstants<OSGUInt64>
{
    typedef       OSGReal32 OSGRealReturnType;

    static inline OSGUInt64 getZeroElement(void) { return 0; };
    static inline OSGUInt64 getOneElement (void) { return 1; };

#ifdef OSG_LONGLONG_HAS_LL
    static inline OSGUInt64 getAllSet  (void) { return 0xFFFFFFFFFFFFFFFFLL; };
    static inline OSGUInt64 getAllClear(void) { return 0x0000000000000000LL; };

    static inline OSGUInt64 getMin     (void) { return 0xFFFFFFFFFFFFFFFFLL; };
    static inline OSGUInt64 getMax     (void) { return 0x0000000000000000LL; };
#else
    static inline OSGUInt64 getAllSet  (void) { return 0xFFFFFFFFFFFFFFFF; };
    static inline OSGUInt64 getAllClear(void) { return 0x0000000000000000; };

    static inline OSGUInt64 getMin     (void) { return 0xFFFFFFFFFFFFFFFF; };
    static inline OSGUInt64 getMax     (void) { return 0x0000000000000000; };
#endif

    static inline OSGReal32 getFraction   (OSGUInt64 val) 
    {
        return (OSGReal32(val) / OSGReal32(getMax())); 
    };
    static inline OSGUInt64 getPortion    (OSGReal32 val) 
    {
        return (OSGUInt64) (val * OSGReal32(getMax())); 
    };


    static inline OSGMathTypeProperties getProp(void) { return OSGIntValue; };


    static inline OSGUInt64 getFromString (const char *szString)
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

template <> 
struct OSGTypeConstants<OSGInt64>
{
    typedef       OSGReal32 OSGRealReturnType;

    static inline OSGInt64 getZeroElement(void) { return 0; };
    static inline OSGInt64 getOneElement (void) { return 1; };

#ifdef OSG_LONGLONG_HAS_LL
    static inline OSGInt64 getAllSet(void)   { return 0xFFFFFFFFFFFFFFFFLL; };
    static inline OSGInt64 getAllClear(void) { return 0x0000000000000000LL; };

    static inline OSGInt64 getMax(void)      { return -0x7FFFFFFFFFFFFFFFLL; };
    static inline OSGInt64 getMin(void)      { return  0x7FFFFFFFFFFFFFFFLL; };
#else
    static inline OSGInt64 getAllSet(void)   { return 0xFFFFFFFFFFFFFFFF; };
    static inline OSGInt64 getAllClear(void) { return 0x0000000000000000; };

    static inline OSGInt64 getMax(void)      { return -0x7FFFFFFFFFFFFFFF; };
    static inline OSGInt64 getMin(void)      { return  0x7FFFFFFFFFFFFFFF; };
#endif


    static inline OSGReal32 getFraction   (OSGInt64 val) 
    {
        return (OSGReal32(val) / OSGReal32(getMax())); 
    };
    static inline OSGInt64 getPortion    (OSGReal32 val) 
    {
        return (OSGInt64) (val * OSGReal32(getMax())); 
    };


    static inline OSGMathTypeProperties getProp(void) { return OSGIntValue; };


    static inline OSGInt64 getFromString (const char *szString)
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

template <>
struct OSGTypeConstants<OSGReal64>
{
    typedef       OSGReal64 OSGRealReturnType;

    static inline OSGReal64 getZeroElement(void)           { return 0.; };
    static inline OSGReal64 getOneElement (void)           { return 1.; };

    static inline OSGReal64 getFraction   (OSGReal64 rVal) { return rVal; };
    static inline OSGReal64 getPortion    (OSGReal64 rVal) { return rVal; };

    static inline OSGMathTypeProperties getProp(void) { return OSGRealValue; };

    static inline OSGReal64 getFromString (const char *szString)
    {
        if(szString != NULL)
            return atof(szString);
        else
            return getZeroElement();
    }
};

template <>
struct OSGTypeConstants<OSGReal32>
{
    typedef       OSGReal32 OSGRealReturnType;

    static inline OSGReal32 getZeroElement(void) { return 0.; };
    static inline OSGReal32 getOneElement (void) { return 1.; };

    static inline OSGReal32 getFraction   (OSGReal32 rVal) { return rVal; };
    static inline OSGReal32 getPortion    (OSGReal32 rVal) { return rVal; };

    static inline OSGMathTypeProperties getProp(void) { return OSGRealValue; };

    static inline OSGReal32 getFromString (const char *szString)
    {
        if(szString != NULL)
            return atof(szString);
        else
            return getZeroElement();
    }
};

OSG_END_NAMESPACE

#endif /* OSGBASETYPES_H */




