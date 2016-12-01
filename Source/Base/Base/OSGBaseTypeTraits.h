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

#ifndef _OSGBASETYPETRAITS_H_
#define _OSGBASETYPETRAITS_H_
#ifdef __sgi
#pragma once
#endif

#ifndef _OSGBASETYPES_H_
#error not for direct use, please include OSGBaseTypes.h instead
#endif

#include "OSGGL.h"
#include <limits>

// The undef's are needed otherwise the numeric_limits won't work (GV)

#if defined(max)
#undef max
#endif

#if defined(min)
#undef min
#endif

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseBaseBaseTypeTraits
 */

struct OSG_BASE_DLLMAPPING TypeTraitsBase
{
#ifdef GV_CHECK_CHECK
    static const  bool               IsPOD    = true;
    static const  MathTypeProperties MathProp = BoolValue;

    static const  bool               BitsSet     = true ;
    static const  bool               BitsClear   = false;

    static        bool              getZeroElement(void)
    {
        return false;
    }

    static        bool              getOneElement (void)
    {
        return true;
    }

    static        bool              getMax        (void)
    {
        return true;
    }

    static        bool              getMin        (void)
    {
        return false;
    }
#endif
};

/*! \ingroup GrpBaseBaseBaseTypeTraits
 */

template <class LookupTypeT>
struct TypeTraits : public TypeTraitsBase
{
    static const bool IsPOD = false;

#ifdef OSG_MICROSOFT_COMPILER_HACKS
    typedef LookupTypeT RealReturnType;
#endif
};

#if defined(__hpux)
template <class LookupTypeT> 
const bool TypeTraits<LookupTypeT>::IsPOD;
#endif


/*! \ingroup GrpBaseBaseBaseTypeTraits
 */

template <>
struct TypeTraits<bool> : public TypeTraitsBase
{
    static const  bool               IsPOD     = true;
    static const  MathTypeProperties MathProp  = BoolValue;

    static const  bool               BitsSet   = true ;
    static const  bool               BitsClear = false;


    static        bool               getZeroElement(void)
    {
        return false;
    }

    static        bool               getOneElement (void)
    {
        return true;
    }

    static        bool               getMax        (void)
    {
        return true;
    }

    static        bool               getMin        (void)
    {
        return false;
    }
};


/*! \ingroup GrpBaseBaseBaseTypeTraits
 */

template <>
struct TypeTraits<UInt8> : public TypeTraitsBase
{
    typedef       Real32             RealReturnType;


    static const  bool               IsPOD     = true;
    static const  MathTypeProperties MathProp  = IntValue;

    static const  UInt8              BitsSet   = 0xFF;
    static const  UInt8              BitsClear = 0x00;


    static        UInt8              getZeroElement(void)
    {
        return 0;
    }

    static        UInt8              getOneElement (void)
    {
        return 1;
    }

    static        UInt8              getMax        (void)
    {
        return std::numeric_limits<UInt8>::max();
    }

    static        UInt8              getMin        (void)
    {
        return std::numeric_limits<UInt8>::min();
    }


    static Real32      getFraction  (UInt8 val)
    {
        return (Real32(val) / Real32(getMax()));
    };

    static UInt8       getPortion   (Real32 val)
    {
#ifdef OSG_WIN32_ICL
#pragma warning (disable : 810)
#endif
        return UInt8((val * Real32(getMax())));
#ifdef OSG_WIN32_ICL
#pragma warning (default : 810)
#endif
    };


    static UInt8       getFromString(const Char8 *szString)
    {
        if(szString != NULL)
        {
            return UInt8(strtoul(szString, NULL, 0));
        }
        else
        {
            return getZeroElement();
        }
    }

    static std::string putToString  (const UInt8 val)
    {
        Char8 buffer[10];

        sprintf(buffer, "%u", val);

        return std::string(buffer);
    }
};


/*! \ingroup GrpBaseBaseBaseTypeTraits
 */

template <>
struct TypeTraits<Int8> : public TypeTraitsBase
{
    typedef       Real32             RealReturnType;


    static const  bool               IsPOD       = true;
    static const  MathTypeProperties MathProp    = IntValue;

    static const  Int8               BitsSet     =    -1; //0xFF;
    static const  Int8               BitsClear   =  0x00;


    static        Int8               getZeroElement(void)
    {
        return 0;
    }

    static        Int8               getOneElement (void)
    {
        return 1;
    }

    static        Int8               getMin        (void)
    {
        return std::numeric_limits<Int8>::min();
    }

    static        Int8               getMax        (void)
    {
        return std::numeric_limits<Int8>::max();
    }


    static Real32      getFraction  (Int8   val)
    {
        return (Real32(val) / Real32(getMax()));
    };

    static Int8        getPortion   (Real32 val)
    {
        return Int8(val * Real32(getMax()));
    };


    static Int8        getFromString(const Char8 *szString)
    {
        if(szString != NULL)
        {
            return Int8(strtol(szString, NULL, 0));
        }
        else
        {
            return getZeroElement();
        }
    }

    static std::string putToString  (const Int8 val)
    {
        Char8 buffer[10];

        sprintf(buffer, "%i", val);

        return std::string(buffer);
    }
};


/*! \ingroup GrpBaseBaseBaseTypeTraits
 */

template <>
struct TypeTraits<UInt16> : public TypeTraitsBase
{
    typedef       Real32             RealReturnType;


    static const  bool               IsPOD       = true;
    static const  MathTypeProperties MathProp    = IntValue;

    static const  UInt16             BitsSet     = 0xFFFF;
    static const  UInt16             BitsClear   = 0x0000;


    static        UInt16             getZeroElement(void)
    {
        return 0;
    }

    static        UInt16             getOneElement (void)
    {
        return 1;
    }
    
    static        UInt16             getMax        (void)
    {
        return std::numeric_limits<UInt16>::max();
    }

    static        UInt16             getMin        (void)
    {
        return std::numeric_limits<UInt16>::min();
    }


    static Real32      getFraction  (UInt16 val)
    {
        return (Real32(val) / Real32(getMax()));
    };

    static UInt16      getPortion   (Real32 val)
    {
        return UInt16(val * Real32(getMax()));
    };


    static UInt16      getFromString(const Char8 *szString)
    {
        if(szString != NULL)
        {
            return UInt16(strtoul(szString, NULL, 0));
        }
        else
        {
            return getZeroElement();
        }
    }

    static std::string putToString  (const UInt16 val)
    {
        Char8 buffer[10];

//      Check WIN32 Version
#ifdef WIN32
        sprintf(buffer, "%u", UInt32(val));
#else
        sprintf(buffer, "%u", val);
#endif

        return std::string(buffer);
    }
};


/*! \ingroup GrpBaseBaseBaseTypeTraits
 */

template <>
struct TypeTraits<Int16> : public TypeTraitsBase
{
    typedef       Real32             RealReturnType;


    static const  bool               IsPOD       = true;
    static const  MathTypeProperties MathProp    = IntValue;

    static const  Int16              BitsSet     =      -1; //0xFFFF;
    static const  Int16              BitsClear   =  0x0000;


    static        Int16              getZeroElement(void)
    {
        return 0;
    }

    static        Int16              getOneElement (void)
    {
        return 1;
    }

    static        Int16              getMax        (void)
    {
        return std::numeric_limits<Int16>::max();
    }

    static        Int16              getMin        (void)
    {
        return std::numeric_limits<Int16>::min();
    }


    static Real32      getFraction  (Int16  val)
    {
        return (Real32(val) / Real32(getMax()));
    };

    static Int16       getPortion   (Real32 val)
    {
        return Int16(val * Real32(getMax()));
    };


    static Int16       getFromString(const Char8 *szString)
    {
        if(szString != NULL)
        {
            return Int16(strtol(szString, NULL, 0));
        }
        else
        {
            return getZeroElement();
        }
    }

    static std::string putToString  (const Int16 val)
    {
        Char8 buffer[10];

        sprintf(buffer, "%i", val);

        return std::string(buffer);
    }
};


/*! \ingroup GrpBaseBaseBaseTypeTraits
 */

template <>
struct TypeTraits<UInt32> : public TypeTraitsBase
{
    typedef       Real32                RealReturnType;


    static const  bool               IsPOD       = true;
    static const  MathTypeProperties MathProp    = IntValue;

    static const  UInt32             BitsSet     = 0xFFFFFFFF;
    static const  UInt32             BitsClear   = 0x00000000;


    static        UInt32             getZeroElement(void)
    {
        return 0;
    }

    static        UInt32             getOneElement (void)
    {
        return 1;
    }

    static        UInt32             getMax        (void) 
    { 
        return std::numeric_limits<UInt32>::max();
    }

    static        UInt32             getMin        (void)
    {
        return std::numeric_limits<UInt32>::min();
    }


    static Real32      getFraction  (UInt32 val)
    {
        return (Real32(val) / Real32(getMax()));
    };

    static UInt32      getPortion   (Real32 val)
    {
        return UInt32(val * Real32(getMax()));
    };


    static UInt32      getFromString(const Char8 *szString)
    {
        if(szString != NULL)
        {
            return UInt32(strtoul(szString, NULL, 0));
        }
        else
        {
            return getZeroElement();
        }
    }

    static std::string putToString  (const UInt32 val)
    {
        Char8 buffer[15];

        sprintf(buffer, "%u", val);

        return std::string(buffer);
    }
};


/*! \ingroup GrpBaseBaseBaseTypeTraits
 */

template <>
struct TypeTraits<Int32> : public TypeTraitsBase
{
    typedef       Real32             RealReturnType;


    static const  bool               IsPOD       = true;
    static const  MathTypeProperties MathProp    = IntValue;

    static const  Int32              BitsSet     =  0xFFFFFFFF;
    static const  Int32              BitsClear   =  0x00000000;


    static        Int32              getZeroElement(void)
    {
        return 0;
    }

    static        Int32              getOneElement (void)
    {
        return 1;
    }

    static        Int32              getMax        (void)
    {
        return std::numeric_limits<Int32>::max(); 
    }

    static        Int32              getMin        (void)
    {
        return std::numeric_limits<Int32>::min();
    }


    static Real32      getFraction  (Int32  val)
    {
        return (Real32(val) / Real32(getMax()));
    };

    static Int32       getPortion   (Real32 val)
    {
        return Int32(val * Real32(getMax()));
    };


    static Int32       getFromString(const Char8 *szString)
    {
        if(szString != NULL)
        {
            return Int32(strtol(szString, NULL, 0));
        }
        else
        {
            return getZeroElement();
        }
    }

    static std::string putToString  (const Int32 val)
    {
        Char8 buffer[15];

        sprintf(buffer, "%i", val);

        return std::string(buffer);
    }
};


/*! \ingroup GrpBaseBaseBaseTypeTraits
 */

template <>
struct TypeTraits<UInt64> : public TypeTraitsBase
{
    typedef       Real32             RealReturnType;


    static const  bool               IsPOD       = true;
    static const  MathTypeProperties MathProp    = IntValue;

#ifdef OSG_LONGLONG_HAS_LL
    static const  UInt64             BitsSet     = 0xFFFFFFFFFFFFFFFFLL;
    static const  UInt64             BitsClear   = 0x0000000000000000LL;

    static const  UInt64             Zero        = 0x0000000000000000LL;
    static const  UInt64             One         = 0x0000000000000001LL;
#else
    static const  UInt64             BitsSet     = 0xFFFFFFFFFFFFFFFF;
    static const  UInt64             BitsClear   = 0x0000000000000000;

    static const  UInt64             Zero        = 0x0000000000000000;
    static const  UInt64             One         = 0x0000000000000001;
#endif
 


    static        UInt64             getZeroElement(void)
    {
        return 0;
    }

    static        UInt64             getOneElement (void)
    {
        return 1;
    }


    static        UInt64             getMax        (void)         
    {
        return std::numeric_limits<UInt64>::max();
    }

    static        UInt64             getMin        (void)
    {
        return std::numeric_limits<UInt64>::min();
    }


    static Real32      getFraction  (UInt64 val)
    {
        return (Real32(val) / Real32(getMax()));
    };

    static UInt64      getPortion   (Real32 val)
    {
        return UInt64(val * Real32(getMax()));
    };


    static UInt64      getFromString(const Char8 *szString)
    {
        if(szString != NULL)
        {
#ifndef WIN32
#ifdef __sgi
            // on my sgi machine strtoull is defined in the header
            // but not in the lib. amz
            UInt64 r = 0;
            sscanf(szString, "%llu", &r);
            return r;
#else
            return UInt64(strtoull(szString, NULL, 0));
#endif
#else
            return _atoi64(szString);
#endif
        }
        else
        {
            return getZeroElement();
        }
    }

    static std::string putToString  (const UInt64 val)
    {
        Char8 buffer[25];
#ifdef OSG_LINUX_TYPES
        sprintf(buffer, "%" PRIu64, val );
#else
        sprintf(buffer, "%llu", val);
#endif
        return std::string(buffer);
    }
};


/*! \ingroup GrpBaseBaseBaseTypeTraits
 */

template <>
struct TypeTraits<Int64> : public TypeTraitsBase
{
    typedef       Real32 RealReturnType;


    static const  bool               IsPOD       = true;
    static const  MathTypeProperties MathProp    = IntValue;

#ifdef OSG_LONGLONG_HAS_LL
    static const  Int64              BitsSet     =  0xFFFFFFFFFFFFFFFFLL;
    static const  Int64              BitsClear   =  0x0000000000000000LL;
#else
    static const  Int64              BitsSet     =  0xFFFFFFFFFFFFFFFF;
    static const  Int64              BitsClear   =  0x0000000000000000;
#endif


    static        Int64              getZeroElement(void)
    {
        return 0;
    }

    static        Int64              getOneElement (void)
    {
        return 1;
    }

    static        Int64              getMax        (void)
    {
        return std::numeric_limits<Int64>::max();
    }

    static        Int64              getMin        (void)
    {
        return std::numeric_limits<Int64>::min();
    }


    static Real32      getFraction  (Int64  val)
    {
        return (Real32(val) / Real32(getMax()));
    };

    static Int64       getPortion   (Real32 val)
    {
        return Int64(val * Real32(getMax()));
    };


    static Int64       getFromString(const Char8 *szString)
    {
        if(szString != NULL)
        {
#ifndef WIN32
#ifdef __sgi
            // on my sgi machine strtoll is defined in the header
            // but not in the lib. amz
            Int64 r = 0;
            sscanf(szString, "%lld", &r);
            return r;
#else
            return Int64(strtoll(szString, NULL, 0));
#endif
#else
            return _atoi64(szString);
#endif
        }
        else
        {
            return getZeroElement();
        }
    }

    static std::string putToString  (const Int64 val)
    {
        Char8 buffer[25];

#ifdef OSG_LINUX_TYPES
        sprintf(buffer, "%" PRIi64, val);
#else
        sprintf(buffer, "%lli", val);
#endif

        return std::string(buffer);
    }
};

/*! \ingroup GrpBaseBaseBaseTypeTraits 
*/

template <>
struct TypeTraits<Real16> : public TypeTraitsBase
{
    typedef       Real16             RealReturnType;


    static const  bool               IsPOD       = true;
    static const  MathTypeProperties MathProp    = RealValue;

    static        Real16             getZeroElement(void)
    {
        return Real16( 0.f );
    }

    static        Real16             getOneElement (void)
    {
        return Real16( 1.f );
    }

    static        Real16             getMax        (void)
    {
        return REAL16_MAX;
    }

    static        Real16             getMin        (void)
    {
        return REAL16_MIN;
    }


    static Real16 getFraction     (Real16 rVal) { return rVal; };
    static Real16 getPortion      (Real16 rVal) { return rVal; };


    static Real16 getFromString   (const Char8 *szString)
    {
        if(szString != NULL)
        {
#if defined(__sgi) || defined(WIN32) || defined(__sun)
            return Real16(Real32(atof  (szString)));
#else
            return Real16(Real32(strtof(szString, NULL)));
#endif
        }
        else
        {
            return getZeroElement();
        }
    }

    static std::string putToString(const Real16 val)
    {
        Char8 buffer[20];

        sprintf(buffer, "%e", Real32(val));

        return std::string(buffer);
    }

};


/*! \ingroup GrpBaseBaseBaseTypeTraits 
 */

template <>
struct TypeTraits<Real32> : public TypeTraitsBase
{
    typedef       Real32             RealReturnType;


    static const  bool               IsPOD       = true;
    static const  MathTypeProperties MathProp    = RealValue;

    static        Real32             getZeroElement(void)
    {
        return 0.f;
    }

    static        Real32             getOneElement (void)
    {
        return 1.f;
    }

    static        Real32             getMax        (void)
    {
        return FLT_MAX;
    }

    static        Real32             getMin        (void)
    {
        return FLT_MIN;
    }


    static Real32 getFraction     (Real32 rVal) { return rVal; };
    static Real32 getPortion      (Real32 rVal) { return rVal; };


    static Real32 getFromString   (const Char8 *szString)
    {
        if(szString != NULL)
        {
#if defined(__sgi) || defined(WIN32) || defined(__sun)
            return Real32(atof  (szString));
#else
            return Real32(strtof(szString, NULL));
#endif
        }
        else
        {
            return getZeroElement();
        }
    }

    static std::string putToString(const Real32 val)
    {
        Char8 buffer[20];

        sprintf(buffer, "%e", val);

        return std::string(buffer);
    }

};


/*! \ingroup GrpBaseBaseBaseTypeTraits
 */

template <>
struct TypeTraits<Real64> : public TypeTraitsBase
{
    typedef       Real64             RealReturnType;


    static const  bool               IsPOD       = true;
    static const  MathTypeProperties MathProp    = RealValue;

    static        Real64             getZeroElement(void)
    {
        return 0.0;
    }

    static        Real64             getOneElement (void)
    {
        return 1.0;
    }

    static        Real64             getMax        (void)
    {
        return DBL_MAX;
    }

    static        Real64             getMin        (void)
    {
        return DBL_MIN;
    }


    static Real64 getFraction     (Real64 rVal) { return rVal; };
    static Real64 getPortion      (Real64 rVal) { return rVal; };


    static Real64 getFromString   (const Char8 *szString)
    {
        if(szString != NULL)
        {
            return Real64(strtod(szString, NULL));
        }
        else
        {
            return getZeroElement();
        }
    }

    static std::string putToString(const Real64 val)
    {
        Char8 buffer[25];

        sprintf(buffer, "%e", val);

        return std::string(buffer);
    }
};


/*! \ingroup GrpBaseBaseBaseTypeTraits
 */

template <>
struct TypeTraits<Real128> : public TypeTraitsBase
{
    typedef       Real128             RealReturnType;


    static const  bool               IsPOD       = true;
    static const  MathTypeProperties MathProp    = RealValue;

    static        Real128             getZeroElement(void)
    {
        return 0.0;
    }

    static        Real128             getOneElement (void)
    {
        return 1.0;
    }

    static        Real128             getMax        (void)
    {
        return DBL_MAX;
    }

    static        Real128             getMin        (void)
    {
        return DBL_MIN;
    }


    static Real128 getFraction     (Real128 rVal) { return rVal; };
    static Real128 getPortion      (Real128 rVal) { return rVal; };


    static Real128 getFromString   (const Char8 *szString)
    {
        if(szString != NULL)
        {
#if defined(WIN32) || defined(__sun)
            return Real128(strtod(szString, NULL));
#else
            return Real128(strtold(szString, NULL));
#endif
        }
        else
        {
            return getZeroElement();
        }
    }

    static std::string putToString(const Real128 val)
    {
        Char8 buffer[25];

        sprintf(buffer, "%Le", val);

        return std::string(buffer);
    }
};


#ifdef OSG_GLENUM_NEQ_UINT32

/*! \ingroup GrpBaseBaseBaseTypeTraits
 */

template <>
struct TypeTraits<GLenum> : public TypeTraitsBase
{
    typedef       Real32                RealReturnType;


    static const  bool               IsPOD       = true;
    static const  MathTypeProperties MathProp    = IntValue;

    static const  UInt32             BitsSet     = 0xFFFFFFFF;
    static const  UInt32             BitsClear   = 0x00000000;


    static        GLenum             getZeroElement(void)
    {
        return 0;
    }

    static        GLenum             getOneElement (void)
    {
        return 1;
    }

    static        GLenum             getMax        (void) 
    { 
        return 0xFFFFFFFF;
    }

    static        GLenum             getMin        (void)
    {
        return 0x00000000;
    }


    static GLenum      getFromString(const Char8 *szString)
    {
        if(szString != NULL)
        {
            return GLenum(strtoul(szString, NULL, 0));
        }
        else
        {
            return getZeroElement();
        }
    }

    static std::string putToString  (const GLenum val)
    {
        Char8 buffer[15];

        sprintf(buffer, "%lu", static_cast<unsigned long>(val));

        return std::string(buffer);
    }
};

#endif

OSG_END_NAMESPACE

#ifndef OSG_DISABLE_DEPRECATED
#define TypeConstants TypeTraits
#define getAllSet()   BitsSet
#endif

#define OSGBASETYPETRAITS_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGBASETYPETRAITS_H_ */
