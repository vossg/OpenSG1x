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

#ifndef WIN32
#include <unistd.h>
#endif

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//   Base Math Functions
//---------------------------------------------------------------------------

/*! \brief osgispower2
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSG_BASE_SPEZ_IMPL_DLLMAPPING
Bool osgispower2(UInt32 rValue)
{
    // find the lowest 1 bit
    while ( rValue && ! ( rValue & 1 ) )
        rValue >>= 1;

    // shift the 1 bit out
    rValue >>= 1;

    // if another 1 left => not 2^
    if ( rValue )   return false;
    else            return true;
}

/*! \brief osgispower2
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSG_BASE_SPEZ_IMPL_DLLMAPPING
Bool osgispower2(Int32 rValue)
{
    // find the lowest 1 bit
    while ( rValue && ! ( rValue & 1 ) )
        rValue >>= 1;

    // shift the 1 bit out
    rValue >>= 1;

    // if another 1 left => not 2^
    if ( rValue )   return false;
    else            return true;
}


/*! \brief osgnextpower2
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSG_BASE_SPEZ_IMPL_DLLMAPPING
UInt32 osgnextpower2(UInt32 rValue)
{
    UInt32 result = 1;

    while ( result < rValue )
        result <<= 1;

    return result;
}

/*! \brief osgnextpower2
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSG_BASE_SPEZ_IMPL_DLLMAPPING
Int32 osgnextpower2(Int32 rValue)
{
    Int32 result = 1;

    while ( result < rValue )
        result <<= 1;

    return result;
}


/*! \brief osgabs
 *  \ingroup BaseMathFunctions
 */

template <class TypeT> inline
OSG_BASE_SPEZ_IMPL_DLLMAPPING
TypeT osgabs(const TypeT rValue)
{
    return (rValue > 0) ? rValue : -rValue;
}

/*! \brief deg2rad
 *  \ingroup BaseMathFunctions
 */

template <class FloatTypeT> inline
typename TypeConstants<FloatTypeT>::RealReturnType
    deg2rad(const FloatTypeT rValue)
{
   return osgdegree2rad(rValue);
}

/*! \brief rad2deg
 *  \ingroup BaseMathFunctions
 */

template <class FloatTypeT> inline
typename TypeConstants<FloatTypeT>::RealReturnType 
    rad2deg(const FloatTypeT rValue)
{
   return osgrad2degree(rValue);
}



/*! @name Default Implementation
 */

template <class FloatTypeT> inline
OSG_BASE_SPEZ_HEAD_DLLMAPPING
typename TypeConstants<FloatTypeT>::RealReturnType 
    osgsqrt(const FloatTypeT rVal)
{
    typedef typename TypeConstants<FloatTypeT>::RealReturnType RealType;

    return  osgsqrt(RealType(rVal));
}

template <class FloatTypeT> inline
OSG_BASE_SPEZ_HEAD_DLLMAPPING
typename TypeConstants<FloatTypeT>::RealReturnType 
    osgcos(const FloatTypeT rVal)
{
    typedef typename TypeConstants<FloatTypeT>::RealReturnType RealType;

    return  osgcos(RealType(rVal));
}

template <class FloatTypeT> inline
OSG_BASE_SPEZ_HEAD_DLLMAPPING
typename TypeConstants<FloatTypeT>::RealReturnType 
    osgsin(const FloatTypeT rVal)
{
    typedef typename TypeConstants<FloatTypeT>::RealReturnType RealType;

    return  osgsin(RealType(rVal));
}

template <class FloatTypeT> inline
OSG_BASE_SPEZ_HEAD_DLLMAPPING
typename TypeConstants<FloatTypeT>::RealReturnType
    osgtan(const FloatTypeT rVal)
{
    typedef typename TypeConstants<FloatTypeT>::RealReturnType RealType;

    return  osgtan(RealType(rVal));
}

template <class FloatTypeT> inline
OSG_BASE_SPEZ_HEAD_DLLMAPPING
typename TypeConstants<FloatTypeT>::RealReturnType 
    osgacos(const FloatTypeT rVal)
{
    typedef typename TypeConstants<FloatTypeT>::RealReturnType RealType;

    return  osgacos(RealType(rVal));
}

template <class FloatTypeT> inline
OSG_BASE_SPEZ_HEAD_DLLMAPPING
typename TypeConstants<FloatTypeT>::RealReturnType
    osgasin(const FloatTypeT rVal)
{
    typedef typename TypeConstants<FloatTypeT>::RealReturnType RealType;

    return  osgasin(RealType(rVal));
}

template <class FloatTypeT> inline
OSG_BASE_SPEZ_HEAD_DLLMAPPING
typename TypeConstants<FloatTypeT>::RealReturnType 
    osgatan(const FloatTypeT rVal)
{
    typedef typename TypeConstants<FloatTypeT>::RealReturnType RealType;

    return  osgatan(RealType(rVal));
}

template <class FloatTypeT> inline
OSG_BASE_SPEZ_HEAD_DLLMAPPING
typename TypeConstants<FloatTypeT>::RealReturnType 
    osgatan2(const FloatTypeT rVal1,
             const FloatTypeT rVal2)
{
    typedef typename TypeConstants<FloatTypeT>::RealReturnType RealType;

    return  osgatan2(RealType(rVal1), RealType(rVal2));
}

template <class FloatTypeT> inline
OSG_BASE_SPEZ_HEAD_DLLMAPPING
typename TypeConstants<FloatTypeT>::RealReturnType 
    osgdegree2rad(const FloatTypeT rVal)
{
    typedef typename TypeConstants<FloatTypeT>::RealReturnType RealType;

    return  osgdegree2rad(RealType(rVal));
}

template <class FloatTypeT> inline
OSG_BASE_SPEZ_HEAD_DLLMAPPING
typename TypeConstants<FloatTypeT>::RealReturnType
    osgrad2degree(const FloatTypeT rVal)
{
    typedef typename TypeConstants<FloatTypeT>::RealReturnType RealType;

    return  osgrad2degree(RealType(rVal));
}

template <class FloatTypeT> inline
OSG_BASE_SPEZ_HEAD_DLLMAPPING
typename TypeConstants<FloatTypeT>::RealReturnType
    osgpow(const FloatTypeT rVal,
           const FloatTypeT rExp)
{
    typedef typename TypeConstants<FloatTypeT>::RealReturnType RealType;

    return  osgpow(RealType(rVal), RealType(rExp));
}

template <class FloatTypeT> inline
OSG_BASE_SPEZ_HEAD_DLLMAPPING
typename TypeConstants<FloatTypeT>::RealReturnType
    osglog(const FloatTypeT rVal)
{
    typedef typename TypeConstants<FloatTypeT>::RealReturnType RealType;

    return  osglog(RealType(rVal));
}

template <class FloatTypeT> inline
OSG_BASE_SPEZ_HEAD_DLLMAPPING
typename TypeConstants<FloatTypeT>::RealReturnType
    osgexp(const FloatTypeT rVal)
{
    typedef typename TypeConstants<FloatTypeT>::RealReturnType RealType;

    return  osgexp(RealType(rVal));
}

template <class FloatTypeT> inline
OSG_BASE_SPEZ_HEAD_DLLMAPPING
typename TypeConstants<FloatTypeT>::RealReturnType
    osgfloor(const FloatTypeT rVal)
{
    typedef typename TypeConstants<FloatTypeT>::RealReturnType RealType;

    return  osgfloor(RealType(rVal));
}


/*! @name Real32 Specializations
 */

/*@{*/

/*! \brief osgsqrt
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSG_BASE_SPEZ_IMPL_DLLMAPPING
Real32 osgsqrt<Real32>(const Real32 rVal)
{
#ifdef OSG_HAS_FLOATMATH
    return sqrtf(rVal);
#else
    return (Real32) sqrt((Real32) rVal);
#endif
}

/*! \brief osgcos
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSG_BASE_SPEZ_IMPL_DLLMAPPING
Real32 osgcos(const Real32 rVal)
{
#ifdef OSG_HAS_FLOATMATH
    return cosf(rVal);
#else
    return (Real32) cos((Real32) rVal);
#endif
}

template <> inline
OSG_BASE_SPEZ_IMPL_DLLMAPPING
Real32 osgsin(const Real32 rVal)
{
#ifdef OSG_HAS_FLOATMATH
    return sinf(rVal);
#else
    return (Real32) sin((Real32) rVal);
#endif
}

/*! \brief osgtan
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSG_BASE_SPEZ_IMPL_DLLMAPPING
Real32 osgtan(const Real32 rVal)
{
#ifdef OSG_HAS_FLOATMATH
    return tanf(rVal);
#else
    return (Real32) tan((Real32) rVal);
#endif
}

/*! \brief osgacos
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSG_BASE_SPEZ_IMPL_DLLMAPPING
Real32 osgacos(const Real32 rVal)
{
#ifdef OSG_HAS_FLOATMATH
    return acosf(rVal);
#else
    return (Real32) acos((Real32) rVal);
#endif
}

/*! \brief osgasin
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSG_BASE_SPEZ_IMPL_DLLMAPPING
Real32 osgasin(const Real32 rVal)
{
#ifdef OSG_HAS_FLOATMATH
    return asinf(rVal);
#else
    return (Real32) asin((Real32) rVal);
#endif
}

/*! \brief osgatan
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSG_BASE_SPEZ_IMPL_DLLMAPPING
Real32 osgatan(const Real32 rVal)
{
#ifdef OSG_HAS_FLOATMATH
    return atanf(rVal);
#else
    return (Real32) atan((Real32) rVal);
#endif
}

/*! \brief osgatan2
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSG_BASE_SPEZ_IMPL_DLLMAPPING
Real32 osgatan2(const Real32 rVal1, const Real32 rVal2)
{
#ifdef OSG_HAS_FLOATMATH
#ifndef _OSG_HAS_ATANF2__
    return atan2f(rVal1, rVal2);
#else
    return (Real32) atan2((Real32) rVal1, (Real32) rVal2);
#endif
#else
    return (Real32) atan2((Real32) rVal1, (Real32) rVal2);
#endif
}

/*! \brief osgdegree2rad
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSG_BASE_SPEZ_IMPL_DLLMAPPING
Real32 osgdegree2rad(const Real32 rValue)
{
   return (rValue/360.f) * 2.f * 3.1415926535f;
}

/*! \brief osgrad2degree
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSG_BASE_SPEZ_IMPL_DLLMAPPING
Real32 osgrad2degree(const Real32 rValue)
{
   return (rValue/(2.f * 3.1415926535f)) * 360.f;
}

/*! \brief osgabs
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSG_BASE_SPEZ_IMPL_DLLMAPPING
Real32 osgabs(const Real32 rValue)
{
#ifdef OSG_HAS_FLOATMATH
    return fabsf(rValue);
#else
    return (Real32) fabs((Real32) rValue);
#endif
}

/*! \brief osgpow
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSG_BASE_SPEZ_IMPL_DLLMAPPING
Real32 osgpow(const Real32 rValue, const Real32 rExp)
{
#ifdef OSG_HAS_FLOATMATH
    return powf(rValue, rExp);
#else
    return (Real32) pow((Real32) rValue, (Real32) rExp);
#endif
}

/*! \brief osglog
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSG_BASE_SPEZ_IMPL_DLLMAPPING
Real32 osglog(const Real32 rVal)
{
#ifdef OSG_HAS_FLOATMATH
    return logf(rVal);
#else
    return (Real32) log((Real32) rVal);
#endif
}

/*! \brief osgexp
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSG_BASE_SPEZ_IMPL_DLLMAPPING
Real32 osgexp(const Real32 rVal)
{
#ifdef OSG_HAS_FLOATMATH
    return expf(rVal);
#else
    return (Real32) exp((Real32) rVal);
#endif
}

/*! \brief osgfloor
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSG_BASE_SPEZ_IMPL_DLLMAPPING
Real32 osgfloor(const Real32 rValue)
{
#ifdef OSG_HAS_FLOATMATH
    return floorf(rValue);
#else
    return (Real32) floor((Real32) rValue);
#endif
}

/*@}*/

/*! \brief osgMin
 *  \ingroup BaseMathFunctions
 */

template <class TypeT> inline
TypeT osgMin(const TypeT lVal, const TypeT rVal)
{
    return ((lVal < rVal) ? lVal : rVal);
}

/*! \brief osgMax
 *  \ingroup BaseMathFunctions
 */

template <class TypeT> inline
TypeT osgMax(const TypeT lVal, const TypeT rVal)
{
    return ((lVal > rVal) ? lVal : rVal);
}

template <class FloatTypeT>
UInt32 osgfinite(const FloatTypeT rVal)
{
#ifdef WIN32
    return _finite(rVal);
#else
    return  finite(rVal);
#endif
}

/*! @name Real64 Specializations
 */

/*@{*/

/*! \brief osgsqrt
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSG_BASE_SPEZ_IMPL_DLLMAPPING
Real64 osgsqrt(const Real64 rVal)
{
    return sqrt(rVal);
}

/*! \brief osgcos
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSG_BASE_SPEZ_IMPL_DLLMAPPING
Real64 osgcos(const Real64 rVal)
{
    return cos(rVal);
}

/*! \brief osgsin
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSG_BASE_SPEZ_IMPL_DLLMAPPING
Real64 osgsin(const Real64 rVal)
{
    return sin(rVal);
}

/*! \brief osgtan
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSG_BASE_SPEZ_IMPL_DLLMAPPING
Real64 osgtan(const Real64 rVal)
{
    return tan(rVal);
}

/*! \brief osgacos
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSG_BASE_SPEZ_IMPL_DLLMAPPING
Real64 osgacos(const Real64 rVal)
{
    return acos(rVal);
}

/*! \brief osgasin
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSG_BASE_SPEZ_IMPL_DLLMAPPING
Real64 osgasin(const Real64 rVal)
{
    return asin(rVal);
}

/*! \brief osgatan
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSG_BASE_SPEZ_IMPL_DLLMAPPING
Real64 osgatan(const Real64 rVal)
{
    return atan(rVal);
}

/*! \brief osgatan2
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSG_BASE_SPEZ_IMPL_DLLMAPPING
Real64 osgatan2(const Real64 rVal1, const Real64 rVal2)
{
    return atan2(rVal1, rVal2);
}

/*! \brief osgdegree2rad
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSG_BASE_SPEZ_IMPL_DLLMAPPING
Real64 osgdegree2rad(const Real64 rValue)
{
   return (rValue/360) * 2 * 3.1415926535;
}

/*! \brief osgrad2degree
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSG_BASE_SPEZ_IMPL_DLLMAPPING
Real64 osgrad2degree(const Real64 rValue)
{
   return (rValue/(2 * 3.1415926535)) * 360;
}

/*! \brief osgabs
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSG_BASE_SPEZ_IMPL_DLLMAPPING
Real64 osgabs(const Real64 rValue)
{
    return fabs(rValue);
}

/*! \brief osgpow
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSG_BASE_SPEZ_IMPL_DLLMAPPING
Real64 osgpow(const Real64 rValue, const Real64 rExp)
{
    return pow(rValue, rExp);
}

/*! \brief osglog
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSG_BASE_SPEZ_IMPL_DLLMAPPING
Real64 osglog(const Real64 rVal)
{
    return log(rVal);
}

/*! \brief osgexp
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSG_BASE_SPEZ_IMPL_DLLMAPPING
Real64 osgexp(const Real64 rVal)
{
    return exp(rVal);
}

/*! \brief osgfloor
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSG_BASE_SPEZ_IMPL_DLLMAPPING
Real64 osgfloor(const Real64 rValue)
{
    return floor(rValue);
}

/*@}*/

/*! \brief copy c strings, allocate new memory using new []
 *  \ingroup BaseFunctions
 */

inline
OSG_BASE_DLLMAPPING
void stringDup(const char *szInput, char *&szOutput)
{
    delete [] szOutput;
    szOutput = NULL;

    if(szInput != NULL)
    {
        szOutput = new char[::strlen(szInput) + 1];
        ::strcpy(szOutput, szInput);
    }
}

inline
OSG_BASE_DLLMAPPING
Int32 stringncmp(const char *string1, const char *string2, size_t count)
{
    return ::strncmp(string1, string2, count);
}

/*! \brief limited string compare
 *  \ingroup BaseFunctions
 */


inline
OSG_BASE_DLLMAPPING
Int32 stringlen(const char *string1)
{
    return ::strlen(string1);
}


/*! \brief string compare
 *  \ingroup BaseFunctions
 */

inline
OSG_BASE_DLLMAPPING
Int32 stringcmp(const char *string1, const char *string2)
{
    return ::strcmp(string1, string2);
}

/*! \brief string case compare
 *  \ingroup BaseFunctions
 */

inline
OSG_BASE_DLLMAPPING
Int32 stringcasecmp(const char *string1,
                    const char *string2)
{
#if !defined(WIN32)
    return ::strcasecmp(string1, string2);
#else
    return _stricmp  (string1, string2);
#endif
}

inline
OSG_BASE_DLLMAPPING
int putenv(char *string)
{
#if !defined(WIN32) || defined(BCC)
    return ::putenv(string);
#else
    return ::_putenv(string);
#endif
}

inline
OSG_BASE_DLLMAPPING
void osgsleep(UInt32 millisecs)
{
#ifdef WIN32
    Sleep(millisecs);
#else

    // Rough aproximation, have to find a better way soon (GV)

    if( (millisecs * 1000) > 1000000)
    {
        ::sleep(millisecs / 1000);
    }
    else
    {
        ::usleep(millisecs * 1000);
    }
#endif
}

OSG_END_NAMESPACE
