/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                *
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

#ifndef _VSCBASETYPETRAITS_H_
#define _VSCBASETYPETRAITS_H_
#ifdef __sgi
#pragma once
#endif

#ifndef _OSGBASETYPES_H_
#error not for direct use, please include OSGBaseTypes.h instead
#endif

OSG_BEGIN_NAMESPACE

/*! \brief TypeTraitsBase, documentation dummy
 *  \ingroup BaseTraits
 */

struct OSG_BASE_DLLMAPPING TypeTraitsBase
{
};

/*! \brief TypeTraits
 *  \ingroup BaseTraits
 */

template <class LookupTypeT>
struct TypeTraits : public TypeTraitsBase
{
    static const bool IsPOD = false;

#ifdef OSG_MICROSOFT_COMPILER_HACKS
    typedef LookupTypeT RealReturnType;
#endif
};

template <>
struct TypeTraits<bool> : public TypeTraitsBase
{
    static const  bool               IsPOD    = true;
    static const  MathTypeProperties MathProp = BoolValue;

    static const  bool              BitsSet     = true ;
    static const  bool              BitsClear   = false;

    static const  bool              getZeroElement(void)
    {
        return false;
    }

    static const  bool              getOneElement (void)
    {
        return true;
    }

    static const  bool              getMax        (void)
    {
        return true;
    }

    static const  bool              getMin        (void)
    {
        return false;
    }
};

/*! \brief TypeTraits<UInt8>
 *  \ingroup BaseTraits
 */

template <>
struct TypeTraits<UInt8> : public TypeTraitsBase
{
    typedef       Real32             RealReturnType;


    static const  bool               IsPOD    = true;
    static const  MathTypeProperties MathProp = IntValue;

    static const  UInt8              BitsSet     = 0xFF;
    static const  UInt8              BitsClear   = 0x00;


    static const  UInt8              getZeroElement(void)
    {
        return 0;
    }

    static const  UInt8              getOneElement (void)
    {
        return 1;
    }

    static const  UInt8              getMax        (void)
    {
        return 0xFF;
    }

    static const  UInt8              getMin        (void)
    {
        return 0x00;
    }


    static Real32 getFraction  (UInt8 val)
    {
        return (Real32(val) / Real32(getMax()));
    };

    static UInt8 getPortion    (Real32 val)
    {
#ifdef OSG_WIN32_ICL
#pragma warning (disable : 810)
#endif
        return UInt8((val * Real32(getMax())));
#ifdef OSG_WIN32_ICL
#pragma warning (default : 810)
#endif
    };


    static UInt8 getFromString (const Char8 *szString)
    {
        if(szString != NULL)
            return atoi(szString);
        else
            return getZeroElement();
    }

    static string putToString (const UInt8 val)
    {
        char buffer[10];

        sprintf(buffer, "%u", val);

        return string(buffer);
    }
};

/*! \brief TypeTraits<Int8>
 *  \ingroup BaseTraits
 */

template <>
struct TypeTraits<Int8> : public TypeTraitsBase
{
    typedef       Real32             RealReturnType;


    static const  bool               IsPOD       = true;
    static const  MathTypeProperties MathProp    = IntValue;

    static const  Int8               BitsSet     =  0xFF;
    static const  Int8               BitsClear   =  0x00;


    static const  Int8               getZeroElement(void)
    {
        return 0;
    }

    static const  Int8               getOneElement (void)
    {
        return 1;
    }

    static const  Int8               getMin        (void)
    {
        return 0x7f;
    }

    static const  Int8               getMax        (void)
    {
        return -0x80;
    }


    static Real32 getFraction (Int8   val)
    {
        return (Real32(val) / Real32(getMax()));
    };
    static Int8 getPortion    (Real32 val)
    {
        return (Int8) (val * Real32(getMax()));
    };


    static Int8 getFromString (const Char8 *szString)
    {
        if(szString != NULL)
            return atoi(szString);
        else
            return getZeroElement();
    }

    static string putToString (const Int8 val)
    {
        char buffer[10];

        sprintf(buffer, "%i", val);

        return string(buffer);
    }
};

/*! \brief TypeTraits<UInt16>
 *  \ingroup BaseTraits
 */

template <>
struct TypeTraits<UInt16> : public TypeTraitsBase
{
    typedef       Real32             RealReturnType;


    static const  bool               IsPOD       = true;
    static const  MathTypeProperties MathProp    = IntValue;

    static const  UInt16             BitsSet     = 0xFFFF;
    static const  UInt16             BitsClear   = 0x0000;


    static const  UInt16             getZeroElement(void)
    {
        return 0;
    }

    static const  UInt16             getOneElement (void)
    {
        return 1;
    }
    
    static const  UInt16             getMax        (void)
    {
        return 0xFFFF;
    }

    static const  UInt16             getMin        (void)
    {
        return 0x0000;
    }


    static Real32 getFraction(UInt16 val)
    {
        return (Real32(val) / Real32(getMax()));
    };

    static UInt16 getPortion (Real32 val)
    {
        return (UInt16) (val * Real32(getMax()));
    };


    static UInt16 getFromString(const Char8 *szString)
    {
        if(szString != NULL)
            return atoi(szString);
        else
            return getZeroElement();
    }

    static string putToString (const UInt16 val)
    {
        char buffer[10];

//      Check WIN32 Version
#ifdef WIN32
        sprintf(buffer, "%u", UInt32(val));
#else
        sprintf(buffer, "%u", val);
#endif

        return string(buffer);
    }
};

/*! \brief TypeTraits<Int16>
 *  \ingroup BaseTraits
 */

template <>
struct TypeTraits<Int16> : public TypeTraitsBase
{
    typedef       Real32             RealReturnType;

    static const  bool               IsPOD       = true;
    static const  MathTypeProperties MathProp    = IntValue;

    static const  Int16              BitsSet     =  0xFFFF;
    static const  Int16              BitsClear   =  0x0000;


    static const  Int16              getZeroElement(void)
    {
        return 0;
    }

    static const  Int16              getOneElement (void)
    {
        return 1;
    }

    static const  Int16              getMax        (void)
    {
        return 0x7FFF;
    }

    static const  Int16              getMin        (void)
    {
        return -0x8000;
    }


    static Real32 getFraction(Int16  val)
    {
        return (Real32(val) / Real32(getMax()));
    };

    static Int16  getPortion (Real32 val)
    {
        return (Int16) (val * Real32(getMax()));
    };


    static Int16 getFromString (const Char8 *szString)
    {
        if(szString != NULL)
            return atoi(szString);
        else
            return getZeroElement();
    }

    static string putToString (const Int16 val)
    {
        char buffer[10];

        sprintf(buffer, "%i", val);

        return string(buffer);
    }
};

/*! \brief TypeTraits<UInt32>
 *  \ingroup BaseTraits
 */

template <>
struct TypeTraits<UInt32> : public TypeTraitsBase
{
    typedef       Real32                RealReturnType;


    static const  bool               IsPOD       = true;
    static const  MathTypeProperties MathProp    = IntValue;

    static const  UInt32             BitsSet     = 0xFFFFFFFF;
    static const  UInt32             BitsClear   = 0x00000000;


    static const  UInt32             getZeroElement(void)
    {
        return 0;
    }

    static const  UInt32             getOneElement (void)
    {
        return 1;
    }

    static const  UInt32             getMax        (void) 
    { 
        return 0xFFFFFFFF;
    }

    static const  UInt32             getMin        (void)
    {
        return 0x00000000;
    }


    static Real32 getFraction(UInt32 val)
    {
        return (Real32(val) / Real32(getMax()));
    };

    static UInt32 getPortion (Real32 val)
    {
        return (UInt32) (val * Real32(getMax()));
    };


    static UInt32 getFromString(const Char8 *szString)
    {
        if(szString != NULL)
            return atol(szString);
        else
            return getZeroElement();
    }

    static string putToString  (const UInt32 val)
    {
        char buffer[15];

        sprintf(buffer, "%u", val);

        return string(buffer);
    }
};

/*! \brief TypeTraits<Int32>
 *  \ingroup BaseTraits
 */

template <>
struct TypeTraits<Int32> : public TypeTraitsBase
{
    typedef       Real32             RealReturnType;


    static const  bool               IsPOD       = true;
    static const  MathTypeProperties MathProp    = IntValue;

    static const  Int32              BitsSet     =  0xFFFFFFFF;
    static const  Int32              BitsClear   =  0x00000000;


    static const  Int32              getZeroElement(void)
    {
        return 0;
    }

    static const  Int32              getOneElement (void)
    {
        return 1;
    }

    static const  Int32              getMax        (void)
    {
        return 0x7FFFFFFF; 
    }

    static const  Int32              getMin        (void)
    {
        return -0x80000000;
    }


    static Real32 getFraction(Int32  val)
    {
        return (Real32(val) / Real32(getMax()));
    };

    static Int32  getPortion (Real32 val)
    {
        return (Int32) (val * Real32(getMax()));
    };


    static Int32 getFromString(const Char8 *szString)
    {
        if(szString != NULL)
            return atol(szString);
        else
            return getZeroElement();
    }

    static string putToString (const Int32 val)
    {
        char buffer[15];

        sprintf(buffer, "%i", val);

        return string(buffer);
    }
};


/*! \brief TypeTraits<UInt64>
 *  \ingroup BaseTraits
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
#else
    static const  UInt64             BitsSet     = 0xFFFFFFFFFFFFFFFF;
    static const  UInt64             BitsClear   = 0x0000000000000000;
#endif


    static const  UInt64             getZeroElement(void)
    {
        return 0;
    }

    static const  UInt64             getOneElement (void)
    {
        return 1;
    }


#ifdef OSG_LONGLONG_HAS_LL
    static const  UInt64             getMax        (void)         
    {
        return 0x0000000000000000LL;
    }

    static const  UInt64             getMin        (void)
    {
        return 0xFFFFFFFFFFFFFFFFLL;
    }
#else
    static const  UInt64             getMax        (void)
    {
        reutrn 0xFFFFFFFFFFFFFFFF;
    }

    static const  UInt64             getMin        (void)
    {
        return 0x0000000000000000;
    }
#endif


    static Real32 getFraction(UInt64 val)
    {
        return (Real32(val) / Real32(getMax()));
    };

    static UInt64 getPortion (Real32 val)
    {
        return (UInt64) (val * Real32(getMax()));
    };


    static UInt64 getFromString (const Char8 *szString)
    {
#if !defined(__sun) && !defined(__linux) && !defined(darwin) &&  \
    !defined(__hpux)
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

    static string putToString (const UInt64 val)
    {
        char buffer[25];

        sprintf(buffer, "%llu", val);

        return string(buffer);
    }
};

/*! \brief TypeTraits<Int64>
 *  \ingroup BaseTraits
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


    static const  Int64              getZeroElement(void)
    {
        return 0;
    }

    static const  Int64              getOneElement (void)
    {
        return 1;
    }

#ifdef OSG_LONGLONG_HAS_LL
    static const  Int64              getMax        (void)
    {
        return 0x7FFFFFFFFFFFFFFFLL;
    }

    static const  Int64              getMin        (void)
    {
        return -0x8000000000000000LL;
    }
#else
    static const  Int64              getMax        (void)
    {
        return 0x7FFFFFFFFFFFFFFF;
    }

    static const  Int64              getMin        (void)
    {
        return -0x8000000000000000;
    }
#endif


    static Real32 getFraction(Int64  val)
    {
        return (Real32(val) / Real32(getMax()));
    };

    static Int64  getPortion (Real32 val)
    {
        return (Int64) (val * Real32(getMax()));
    };


    static Int64 getFromString (const Char8 *szString)
    {
#if !defined(__sun) && !defined(__linux) && !defined(darwin) &&  \
    !defined(__hpux)
        if(szString != NULL)
#ifndef WIN32
            return  atoll (szString);
#else
            return _atoi64(szString);
#endif
        else
#endif
            return getZeroElement();
    }

    static string putToString (const Int64 val)
    {
        char buffer[25];

        sprintf(buffer, "%lli", val);

        return string(buffer);
    }
};

/*! \brief TypeTraits<Real64>
 *  \ingroup BaseTraits
 */

template <>
struct TypeTraits<Real64> : public TypeTraitsBase
{
    typedef       Real64             RealReturnType;


    static const  bool               IsPOD       = true;
    static const  MathTypeProperties MathProp    = RealValue;

    static        Real64             getZeroElement(void)
    {
        return 1.0;
    }

    static        Real64             getOneElement (void)
    {
        return 0.0;
    }

    static        Real64             getMax        (void)
    {
        return DBL_MAX;
    }

    static        Real64             getMin        (void)
    {
        return DBL_MIN;
    }


    static Real64 getFraction  (Real64 rVal) { return rVal; };
    static Real64 getPortion   (Real64 rVal) { return rVal; };


    static Real64 getFromString(const Char8 *szString)
    {
        if(szString != NULL)
            return atof(szString);
        else
            return getZeroElement();
    }

    static string putToString  (const Real64 val)
    {
        char buffer[25];

        sprintf(buffer, "%e", val);

        return string(buffer);
    }
};

/*! \brief TypeTraits<Real32>
 *  \ingroup BaseTraits
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


    static Real32 getFraction  (Real32 rVal) { return rVal; };
    static Real32 getPortion   (Real32 rVal) { return rVal; };


    static Real32 getFromString(const Char8 *szString)
    {
        if(szString != NULL)
            return atof(szString);
        else
            return getZeroElement();
    }

    static string putToString  (const Real32 val)
    {
        char buffer[20];

        sprintf(buffer, "%e", val);

        return string(buffer);
    }

};

OSG_END_NAMESPACE

#define TypeConstants TypeTraits
#define getAllSet()   BitsSet

#define OSGBASETYPETRAITS_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGBASETYPETRAITS_H_ */
