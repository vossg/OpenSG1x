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

/*! \var typedef bool OSGBool;
 *  \brief OSGBool
 *  \ingroup BaseTypes
 */

typedef bool          OSGBool;

/*! \var typedef char OSGChar8;
 *  \brief OSGChar8
 *  \ingroup BaseTypes
 */

typedef char          OSGChar8;

/*! \var typedef unsigned char OSGUChar8;
 *  \brief OSGUChar8
 *  \ingroup BaseTypes
 */

typedef unsigned char OSGUChar8;

/*! \var typedef int8_t OSGInt8;
 *  \brief OSGInt8
 *  \ingroup BaseTypes
 */

typedef int8_t    OSGInt8;

/*! \var typedef uint8_t OSGUInt8;
 *  \brief OSGUInt8
 *  \ingroup BaseTypes
 */

typedef uint8_t   OSGUInt8;

/*! \var typedef int16_t OSGInt16;
 *  \brief OSGInt16
 *  \ingroup BaseTypes
 */

typedef int16_t   OSGInt16;

/*! \var typedef uint16_t OSGUInt16;
 *  \brief OSGUInt16
 *  \ingroup BaseTypes
 */

typedef uint16_t  OSGUInt16;

/*! \var typedef int32_t OSGInt32;
 *  \brief OSGInt32
 *  \ingroup BaseTypes
 */

typedef int32_t   OSGInt32;

/*! \var typedef uint32_t OSGUInt32;
 *  \brief OSGUInt32
 *  \ingroup BaseTypes
 */

typedef uint32_t  OSGUInt32;

/*! \var typedef int64_t OSGInt64;
 *  \brief OSGInt64
 *  \ingroup BaseTypes
 */

typedef int64_t   OSGInt64;

/*! \var typedef uint64_t OSGUInt64;
 *  \brief OSGUInt64
 *  \ingroup BaseTypes
 */

typedef uint64_t  OSGUInt64;

/*! \var typedef float OSGReal32;
 *  \brief OSGReal32
 *  \ingroup BaseTypes
 */

typedef float     OSGReal32;

/*! \var typedef double OSGReal64;
 *  \brief OSGReal64
 *  \ingroup BaseTypes
 */

typedef double    OSGReal64;

#elif defined(OSG_LINUX_TYPES)

/*! \var typedef bool OSGBool;
 *  \brief OSGBool
 *  \ingroup BaseTypes
 */

typedef bool          OSGBool;

/*! \var typedef char OSGChar8;
 *  \brief OSGChar8
 *  \ingroup BaseTypes
 */

typedef char          OSGChar8;

/*! \var typedef unsigned char OSGUChar8;
 *  \brief OSGUChar8
 *  \ingroup BaseTypes
 */

typedef unsigned char OSGUChar8;

/*! \var typedef int8_t OSGInt8;
 *  \brief OSGInt8
 *  \ingroup BaseTypes
 */

typedef int8_t     OSGInt8;

/*! \var typedef u_int8_t OSGUInt8;
 *  \brief OSGUInt8
 *  \ingroup BaseTypes
 */

typedef u_int8_t   OSGUInt8;

/*! \var typedef int16_t OSGInt16;
 *  \brief OSGInt16
 *  \ingroup BaseTypes
 */

typedef int16_t    OSGInt16;

/*! \var typedef u_int16_t OSGUInt16;
 *  \brief OSGUInt16
 *  \ingroup BaseTypes
 */

typedef u_int16_t  OSGUInt16;

/*! \var typedef int32_t OSGInt32;
 *  \brief OSGInt32
 *  \ingroup BaseTypes
 */

typedef int32_t    OSGInt32;

/*! \var typedef u_int32_t OSGUInt32;
 *  \brief OSGUInt32
 *  \ingroup BaseTypes
 */

typedef u_int32_t  OSGUInt32;

/*! \var typedef int64_t OSGInt64;
 *  \brief OSGInt64
 *  \ingroup BaseTypes
 */

typedef int64_t    OSGInt64;

/*! \var typedef u_int64_t OSGUInt64;
 *  \brief OSGUInt64
 *  \ingroup BaseTypes
 */

typedef u_int64_t  OSGUInt64;

/*! \var typedef float OSGReal32;
 *  \brief OSGReal32
 *  \ingroup BaseTypes
 */

typedef float      OSGReal32;

/*! \var typedef double OSGReal64;
 *  \brief OSGReal64
 *  \ingroup BaseTypes
 */

typedef double     OSGReal64;

#elif defined(OSG_WIN_TYPES)

/*! \var typedef bool OSGBool;
 *  \brief OSGBool
 *  \ingroup BaseTypes
 */

typedef bool          OSGBool;

/*! \var typedef char OSGChar8;
 *  \brief OSGChar8
 *  \ingroup BaseTypes
 */

typedef char          OSGChar8;

/*! \var typedef unsigned char OSGUChar8;
 *  \brief OSGUChar8
 *  \ingroup BaseTypes
 */

typedef unsigned char OSGUChar8;

/*! \var typedef CHAR OSGInt8;
 *  \brief OSGInt8
 *  \ingroup BaseTypes
 */

typedef CHAR    OSGInt8;

/*! \var typedef UCHAR OSGUInt8;
 *  \brief OSGUInt8
 *  \ingroup BaseTypes
 */

typedef UCHAR   OSGUInt8;

/*! \var typedef SHORT OSGInt16;
 *  \brief OSGInt16
 *  \ingroup BaseTypes
 */

typedef SHORT   OSGInt16;

/*! \var typedef USHORT OSGUInt16;
 *  \brief OSGUInt16
 *  \ingroup BaseTypes
 */

typedef USHORT  OSGUInt16;

/*! \var typedef INT32 OSGInt32;
 *  \brief OSGInt32
 *  \ingroup BaseTypes
 */

typedef INT32   OSGInt32;

/*! \var typedef UINT32 OSGUInt32;
 *  \brief OSGUInt32
 *  \ingroup BaseTypes
 */

typedef UINT32  OSGUInt32;

/*! \var typedef INT64 OSGInt64;
 *  \brief OSGInt64
 *  \ingroup BaseTypes
 */

typedef INT64   OSGInt64;

/*! \var typedef UINT64 OSGUInt64;
 *  \brief OSGUInt64
 *  \ingroup BaseTypes
 */

typedef UINT64  OSGUInt64;

/*! \var typedef DWORD OSGDWord;
 *  \brief OSGDWord
 *  \ingroup BaseTypes
 */

typedef DWORD   OSGDWord;

/*! \var typedef HANDLE OSGHandle;
 *  \brief OSGHandle
 *  \ingroup BaseTypes
 */

typedef HANDLE  OSGHandle;

/*! \var typedef float OSGReal32;
 *  \brief OSGReal32
 *  \ingroup BaseTypes
 */

typedef float     OSGReal32;

/*! \var typedef double OSGReal64;
 *  \brief OSGReal64
 *  \ingroup BaseTypes
 */

typedef double    OSGReal64;

#elif defined(OSG_SUNOS_TYPES)

/*! \var typedef bool OSGBool;
 *  \brief OSGBool
 *  \ingroup BaseTypes
 */

typedef bool          OSGBool;

/*! \var typedef charOSGChar8;
 *  \brief OSGChar8
 *  \ingroup BaseTypes
 */

typedef char          OSGChar8;

/*! \var typedef unsigned char OSGUChar8;
 *  \brief OSGUChar8
 *  \ingroup BaseTypes
 */

typedef unsigned char OSGUChar8;

/*! \var typedef int8_t OSGInt8;
 *  \brief OSGInt8
 *  \ingroup BaseTypes
 */

typedef int8_t     OSGInt8;

/*! \var typedef uint8_t OSGUInt8;
 *  \brief OSGUInt8
 *  \ingroup BaseTypes
 */

typedef uint8_t   OSGUInt8;

/*! \var typedef int16_t OSGInt16;
 *  \brief OSGInt16
 *  \ingroup BaseTypes
 */

typedef int16_t    OSGInt16;

/*! \var typedef uint16_t OSGUInt16;
 *  \brief OSGUInt16
 *  \ingroup BaseTypes
 */

typedef uint16_t  OSGUInt16;

/*! \var typedef int32_t OSGInt32;
 *  \brief OSGInt32
 *  \ingroup BaseTypes
 */

typedef int32_t    OSGInt32;

/*! \var typedef uint32_t OSGUInt32;
 *  \brief OSGUInt32
 *  \ingroup BaseTypes
 */

typedef uint32_t  OSGUInt32;

/*! \var typedef long long OSGInt64;
 *  \brief OSGInt64
 *  \ingroup BaseTypes
 */

typedef long long    OSGInt64;

/*! \var typedef unsigned long long OSGUInt64;
 *  \brief OSGUInt64
 *  \ingroup BaseTypes
 */

typedef unsigned long long  OSGUInt64;

/*! \var typedef float OSGReal32;
 *  \brief OSGReal32
 *  \ingroup BaseTypes
 */

typedef float      OSGReal32;

/*! \var typedef double OSGReal64;
 *  \brief OSGReal64
 *  \ingroup BaseTypes
 */

typedef double     OSGReal64;

#else
#error "Could not define base types, check your system/compiler combination"
#endif

/*! \var OSGUInt32 OSGBitVector;
 *  \brief OSGBitVector
 *  \ingroup BaseTypes
 */

typedef OSGUInt32 OSGBitVector;

/*! \brief osgEps
 *  \ingroup BaseConstants
 */

const OSGReal32 osgEps = 1E-7f;

/*! \brief osgEps
 *  \ingroup BaseConstants
 */

const OSGReal32 osgPi  = (OSGReal32) 3.141592653589797;

/*! \brief OSGMathTypeProperties
 *  \ingroup BaseConstants
 */

enum OSGMathTypeProperties
{
    OSGRealValue,
    OSGIntValue
};

/*! \brief OSGTypeConstantsBase, documentation dummy
 *  \ingroup BaseConstants
 */

struct OSGTypeConstantsBase
{
};

/*! \brief OSGTypeConstants
 *  \ingroup BaseConstants
 */

template <class OSGLookupTypeT>
struct OSGTypeConstants : public OSGTypeConstantsBase
{
};

/*! \brief OSGTypeConstants<OSGUInt8>
 *  \ingroup BaseConstants
 */

template <> 
struct OSGTypeConstants<OSGUInt8> : public OSGTypeConstantsBase
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

/*! \brief OSGTypeConstants<OSGInt8>
 *  \ingroup BaseConstants
 */

template <> 
struct OSGTypeConstants<OSGInt8> : public OSGTypeConstantsBase
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

/*! \brief OSGTypeConstants<OSGUInt16>
 *  \ingroup BaseConstants
 */

template <> 
struct OSGTypeConstants<OSGUInt16> : public OSGTypeConstantsBase
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

/*! \brief OSGTypeConstants<OSGInt16>
 *  \ingroup BaseConstants
 */

template <> 
struct OSGTypeConstants<OSGInt16> : public OSGTypeConstantsBase
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

/*! \brief OSGTypeConstants<OSGUInt32>
 *  \ingroup BaseConstants
 */

template <> 
struct OSGTypeConstants<OSGUInt32> : public OSGTypeConstantsBase
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

/*! \brief OSGTypeConstants<OSGInt32>
 *  \ingroup BaseConstants
 */

template <> 
struct OSGTypeConstants<OSGInt32> : public OSGTypeConstantsBase
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

/*! \brief OSGTypeConstants<OSGUInt64>
 *  \ingroup BaseConstants
 */

template <> 
struct OSGTypeConstants<OSGUInt64> : public OSGTypeConstantsBase
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

/*! \brief OSGTypeConstants<OSGInt64>
 *  \ingroup BaseConstants
 */

template <> 
struct OSGTypeConstants<OSGInt64> : public OSGTypeConstantsBase
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

/*! \brief OSGTypeConstants<OSGReal64>
 *  \ingroup BaseConstants
 */

template <>
struct OSGTypeConstants<OSGReal64> : public OSGTypeConstantsBase
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

/*! \brief OSGTypeConstants<OSGReal32>
 *  \ingroup BaseConstants
 */

template <>
struct OSGTypeConstants<OSGReal32> : public OSGTypeConstantsBase
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




