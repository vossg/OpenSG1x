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

/*---------------------------------------------------------------------*/
/*! \name sqrt                                                         */
/*! \{                                                                 */

/*! \ingroup GrpBaseBaseMathFn
 */

template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType 
    osgsqrt(const FloatTypeT rVal)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgsqrt(RealType(rVal));
}

/*! \ingroup GrpBaseBaseMathFn
 */

template <> inline
Real32 osgsqrt<Real32>(const Real32 rVal)
{
#ifdef OSG_HAS_FLOATMATH
    return sqrtf(rVal);
#else
    return (Real32) sqrt((Real32) rVal);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */

template <> inline
Real64 osgsqrt<Real64>(const Real64 rVal)
{
    return sqrt(rVal);
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name cos                                                          */
/*! \{                                                                 */

/*! \ingroup GrpBaseBaseMathFn
 */

template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType 
    osgcos(const FloatTypeT rVal)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgcos(RealType(rVal));
}

/*! \ingroup GrpBaseBaseMathFn
 */

template <> inline
Real32 osgcos<Real32>(const Real32 rVal)
{
#ifdef OSG_HAS_FLOATMATH
    return cosf(rVal);
#else
    return (Real32) cos((Real32) rVal);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */

template <> inline
Real64 osgcos<Real64>(const Real64 rVal)
{
    return cos(rVal);
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name sin                                                          */
/*! \{                                                                 */

/*! \ingroup GrpBaseBaseMathFn
 */

template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType 
    osgsin(const FloatTypeT rVal)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgsin(RealType(rVal));
}

/*! \ingroup GrpBaseBaseMathFn
 */

template <> inline
Real32 osgsin<Real32>(const Real32 rVal)
{
#ifdef OSG_HAS_FLOATMATH
    return sinf(rVal);
#else
    return (Real32) sin((Real32) rVal);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */

template <> inline
Real64 osgsin<Real64>(const Real64 rVal)
{
    return sin(rVal);
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name tan                                                          */
/*! \{                                                                 */

/*! \ingroup GrpBaseBaseMathFn
 */

template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgtan(const FloatTypeT rVal)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgtan(RealType(rVal));
}

/*! \ingroup GrpBaseBaseMathFn
 */

template <> inline
Real32 osgtan<Real32>(const Real32 rVal)
{
#ifdef OSG_HAS_FLOATMATH
    return tanf(rVal);
#else
    return (Real32) tan((Real32) rVal);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */

template <> inline
Real64 osgtan<Real64>(const Real64 rVal)
{
    return tan(rVal);
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name acos                                                         */
/*! \{                                                                 */

/*! \ingroup GrpBaseBaseMathFn
 */

template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType 
    osgacos(const FloatTypeT rVal)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgacos(RealType(rVal));
}

/*! \ingroup GrpBaseBaseMathFn
 */

template <> inline
Real32 osgacos<Real32>(const Real32 rVal)
{
#ifdef OSG_HAS_FLOATMATH
    return acosf(rVal);
#else
    return (Real32) acos((Real32) rVal);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */

template <> inline
Real64 osgacos<Real64>(const Real64 rVal)
{
    return acos(rVal);
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name asin                                                         */
/*! \{                                                                 */

/*! \ingroup GrpBaseBaseMathFn
 */

template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgasin(const FloatTypeT rVal)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgasin(RealType(rVal));
}

/*! \ingroup GrpBaseBaseMathFn
 */

template <> inline
Real32 osgasin<Real32>(const Real32 rVal)
{
#ifdef OSG_HAS_FLOATMATH
    return asinf(rVal);
#else
    return (Real32) asin((Real32) rVal);
#endif
}


/*! \ingroup GrpBaseBaseMathFn
 */

template <> inline
Real64 osgasin<Real64>(const Real64 rVal)
{
    return asin(rVal);
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name atan                                                         */
/*! \{                                                                 */

/*! \ingroup GrpBaseBaseMathFn
 */

template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType 
    osgatan(const FloatTypeT rVal)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgatan(RealType(rVal));
}

/*! \ingroup GrpBaseBaseMathFn
 */

template <> inline
Real32 osgatan<Real32>(const Real32 rVal)
{
#ifdef OSG_HAS_FLOATMATH
    return atanf(rVal);
#else
    return (Real32) atan((Real32) rVal);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */

template <> inline
Real64 osgatan<Real64>(const Real64 rVal)
{
    return atan(rVal);
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name atan2                                                        */
/*! \{                                                                 */

/*! \ingroup GrpBaseBaseMathFn
 */

template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType 
    osgatan2(const FloatTypeT rVal1,
             const FloatTypeT rVal2)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgatan2(RealType(rVal1), RealType(rVal2));
}

/*! \ingroup GrpBaseBaseMathFn
 */

template <> inline
Real32 osgatan2<Real32>(const Real32 rVal1, const Real32 rVal2)
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

/*! \ingroup GrpBaseBaseMathFn
 */

template <> inline
Real64 osgatan2<Real64>(const Real64 rVal1, const Real64 rVal2)
{
    return atan2(rVal1, rVal2);
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name abs                                                          */
/*! \{                                                                 */

/*! \ingroup GrpBaseBaseMathFn
 */

template <class TypeT> inline
TypeT osgabs(const TypeT rValue)
{
    return (rValue > 0) ? rValue : -rValue;
}

/*! \ingroup GrpBaseBaseMathFn
 */

template <> inline
Real32 osgabs<Real32>(const Real32 rValue)
{
#if defined(OSG_HAS_FLOATMATH) && !defined(OSG_NO_FABSF)
    return fabsf(rValue);
#else
    return (Real32) fabs((Real32) rValue);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */

template <> inline
Real64 osgabs<Real64>(const Real64 rValue)
{
    return fabs(rValue);
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name pow                                                          */
/*! \{                                                                 */

/*! \ingroup GrpBaseBaseMathFn
 */

template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgpow(const FloatTypeT rVal,
           const FloatTypeT rExp)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgpow(RealType(rVal), RealType(rExp));
}

/*! \ingroup GrpBaseBaseMathFn
 */

template <> inline
Real32 osgpow<Real32>(const Real32 rValue, const Real32 rExp)
{
#ifdef OSG_HAS_FLOATMATH
    return powf(rValue, rExp);
#else
    return (Real32) pow((Real32) rValue, (Real32) rExp);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */

template <> inline
Real64 osgpow<Real64>(const Real64 rValue, const Real64 rExp)
{
    return pow(rValue, rExp);
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name log                                                          */
/*! \{                                                                 */

/*! \ingroup GrpBaseBaseMathFn
 */

template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osglog(const FloatTypeT rVal)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osglog(RealType(rVal));
}

/*! \ingroup GrpBaseBaseMathFn
 */

template <> inline
Real32 osglog<Real32>(const Real32 rVal)
{
#ifdef OSG_HAS_FLOATMATH
    return logf(rVal);
#else
    return (Real32) log((Real32) rVal);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */

template <> inline
Real64 osglog<Real64>(const Real64 rVal)
{
    return log(rVal);
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name exp                                                          */
/*! \{                                                                 */

/*! \ingroup GrpBaseBaseMathFn
 */

template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgexp(const FloatTypeT rVal)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgexp(RealType(rVal));
}

/*! \ingroup GrpBaseBaseMathFn
 */

template <> inline
Real32 osgexp<Real32>(const Real32 rVal)
{
#ifdef OSG_HAS_FLOATMATH
    return expf(rVal);
#else
    return (Real32) exp((Real32) rVal);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */

template <> inline
Real64 osgexp<Real64>(const Real64 rVal)
{
    return exp(rVal);
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name floor                                                        */
/*! \{                                                                 */

/*! \ingroup GrpBaseBaseMathFn
 */

template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgfloor(const FloatTypeT rVal)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgfloor(RealType(rVal));
}

/*! \ingroup GrpBaseBaseMathFn
 */

template <> inline
Real32 osgfloor<Real32>(const Real32 rValue)
{
#ifdef OSG_HAS_FLOATMATH
# ifdef OSG_HPUX_ACC
    return (Real32) floor((Real32) rValue);
# else
    return floorf(rValue);
# endif
#else
    return (Real32) floor((Real32) rValue);
#endif
}

/*! \ingroup GrpBaseBaseMathFn
 */

template <> inline
Real64 osgfloor<Real64>(const Real64 rValue)
{
    return floor(rValue);
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name finite                                                       */
/*! \{                                                                 */

/*! \ingroup GrpBaseBaseMathFn
 */

template <class FloatTypeT> inline
UInt32 osgfinite(const FloatTypeT rVal)
{
#ifdef WIN32
    return _finite(rVal);
#else
#ifdef __hpux
    return  isfinite(rVal);
#else
    return  finite(rVal);
#endif
#endif
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name min / max                                                    */
/*! \{                                                                 */

/*! \ingroup GrpBaseBaseMathFn
 */

template <class TypeT> inline
TypeT osgMin(const TypeT lVal, const TypeT rVal)
{
    return ((lVal < rVal) ? lVal : rVal);
}

/*! \ingroup GrpBaseBaseMathFn
 */

template <class TypeT> inline
TypeT osgMax(const TypeT lVal, const TypeT rVal)
{
    return ((lVal > rVal) ? lVal : rVal);
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name swap                                                         */
/*! \{                                                                 */

/*! \ingroup GrpBaseBaseMathFn
 */

template <class TypeT> inline
void osgSwap(TypeT & lVal, TypeT & rVal)
{
    TypeT val(lVal);

    lVal = rVal;
    rVal = val;
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name degree2rad                                                   */
/*! \{                                                                 */

/*! \ingroup GrpBaseBaseMathFn
 */

template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType 
    osgdegree2rad(const FloatTypeT rVal)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgdegree2rad(RealType(rVal));
}

/*! \ingroup GrpBaseBaseMathFn
 */

template <> inline
Real32 osgdegree2rad<Real32>(const Real32 rValue)
{
   return (rValue/360.f) * 2.f * 3.1415926535f;
}

/*! \ingroup GrpBaseBaseMathFn
 */

template <> inline
Real64 osgdegree2rad<Real64>(const Real64 rValue)
{
   return (rValue/360) * 2 * 3.1415926535;
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name rad2degree                                                   */
/*! \{                                                                 */

/*! \ingroup GrpBaseBaseMathFn
 */

template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgrad2degree(const FloatTypeT rVal)
{
    typedef typename TypeTraits<FloatTypeT>::RealReturnType RealType;

    return  osgrad2degree(RealType(rVal));
}

/*! \ingroup GrpBaseBaseMathFn
 */

template <> inline
Real32 osgrad2degree<Real32>(const Real32 rValue)
{
    return (rValue/(2.f * 3.1415926535f)) * 360.f;
}

/*! \ingroup GrpBaseBaseMathFn
 */

template <> inline
Real64 osgrad2degree<Real64>(const Real64 rValue)
{
    return (rValue/(2 * 3.1415926535)) * 360;
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name deg2rad / rad2deg                                            */
/*! \{                                                                 */

/*! \ingroup GrpBaseBaseMathFn
 */

template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    deg2rad(const FloatTypeT rValue)
{
    return osgdegree2rad(rValue);
}

/*! \ingroup GrpBaseBaseMathFn
 */

template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType 
    rad2deg(const FloatTypeT rValue)
{
    return osgrad2degree(rValue);
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name ispower2                                                     */
/*! \{                                                                 */

/*! \ingroup GrpBaseBaseMathFn
 */

template <> inline
bool osgispower2<UInt32>(UInt32 rValue)
{
    // find the lowest 1 bit
    while(rValue && ! (rValue & 1))
    {
        rValue >>= 1;
    }

    // shift the 1 bit out
    rValue >>= 1;

    // if another 1 left => not 2^
    if(rValue)
        return false;
    else            
        return true;
}

/*! \ingroup GrpBaseBaseMathFn
 */

template <> inline
bool osgispower2<Int32>(Int32 rValue)
{
    // find the lowest 1 bit
    while(rValue && ! (rValue & 1))
    {
        rValue >>= 1;
    }

    // shift the 1 bit out
    rValue >>= 1;

    // if another 1 left => not 2^
    if(rValue)
        return false;
    else
        return true;
}

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name nextpower2                                                   */
/*! \{                                                                 */

/*! \ingroup GrpBaseBaseMathFn
 */

template <> inline
UInt32 osgnextpower2<UInt32>(UInt32 rValue)
{
    UInt32 result = 1;

    while(result < rValue)
    {
        result <<= 1;
    }

    return result;
}

/*! \ingroup GrpBaseBaseMathFn
 */

template <> inline
Int32 osgnextpower2<Int32>(Int32 rValue)
{
    Int32 result = 1;

    while(result < rValue)
    {
        result <<= 1;
    }

    return result;
}

#ifdef SIZE_T_NEQ_UINT32

/*! \ingroup GrpBaseBaseMathFn
 */

template <> inline
size_t osgnextpower2<size_t>(size_t rValue)
{
    size_t result = 1;

    while(result < rValue)
    {
        result <<= 1;
    }

    return result;
}

#endif
/*! \}                                                                 */
//-----------------------------------------------------------------------
// String Functions
//-----------------------------------------------------------------------

/*! copy c strings, allocate new memory using new []
    \ingroup GrpBaseBaseStringFn
 */

inline
void stringDup(const Char8 *szInput, Char8 *&szOutput)
{
    delete [] szOutput;

    szOutput = NULL;

    if(szInput != NULL)
    {
        szOutput = new char[::strlen(szInput) + 1];

        ::strcpy(szOutput, szInput);
    }
}

/*! limited string compare
    \ingroup GrpBaseBaseStringFn
 */

inline
Int32 stringncmp(const Char8 *string1, const Char8 *string2, size_t count)
{
    return ::strncmp(string1, string2, count);
}

/*! string length
    \ingroup GrpBaseBaseStringFn 
 */

inline
Int32 stringlen(const Char8 *string1)
{
    return ::strlen(string1);
}

/*! string compare
    \ingroup GrpBaseBaseStringFn
 */

inline
Int32 stringcmp(const Char8 *string1, const Char8 *string2)
{
    return ::strcmp(string1, string2);
}

/*! string case compare
    \ingroup GrpBaseBaseStringFn
 */

inline
Int32 stringcasecmp(const Char8 *string1,
                    const Char8 *string2)
{
#if !defined(WIN32)
    return ::strcasecmp(string1, string2);
#else
    return _stricmp  (string1, string2);
#endif
}

//---------------------------------------------------------------------------
// Misc Functions
//---------------------------------------------------------------------------

/*! find the index that has the largest absolute value for a vec3/pnt3
    \ingroup GrpBaseBaseMiscFn
 */


template<class VecPntT> inline
UInt32 getMaxIndexAbs3(const VecPntT &v)
{
    return 
        osgabs(v[0]) > osgabs(v[1]) ?
            (osgabs(v[0]) > osgabs(v[2]) ? 0 : 2) : 
            (osgabs(v[1]) > osgabs(v[2]) ? 1 : 2);
}

/*! \ingroup GrpBaseBaseMiscFn
 */


inline
Int32 putenv(Char8 *string)
{
#if !defined(WIN32) || defined(BCC)
    return ::putenv(string);
#else
    return ::_putenv(string);
#endif
}


/*! \ingroup GrpBaseBaseMiscFn
 */


inline
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

/*! get a random value between 0 and 1
    \ingroup GrpBaseBaseMiscFn
 */


inline
Real32 osgrand(void)
{
    return rand() / (Real32) RAND_MAX;
}

/*! return true if the current system is big endian
    \ingroup GrpBaseBaseMiscFn
 */

inline
bool osgIsBigEndian(void)
{
    return (BYTE_ORDER) == (BIG_ENDIAN);   
}


//---------------------------------------------------------------------------
// Reference Count Functions
//---------------------------------------------------------------------------

/*! \ingroup GrpBaseBaseRefCountFn
 */

template <class T> inline
void setRefP(T *&pObject, T *&pNewObject)
{
    if(pObject != NULL)
        pObject->subRef();

    pObject = pNewObject;

    if(pObject != NULL)
        pObject->addRef();
}

/*! \ingroup GrpBaseBaseRefCountFn
 */

template <class T> inline
void addRefP(T *&pObject)
{
    if(pObject != NULL)
        pObject->addRef();
}

/*! \ingroup GrpBaseBaseRefCountFn
 */

template <class T> inline
void subRefP(T *&pObject)
{
    if(pObject != NULL)
        pObject->subRef();
}

/*! \ingroup GrpBaseBaseRefCountFn
 */

template <class T> inline
void clearRefP(T *&pObject)
{
    if(pObject != NULL)
        pObject->subRef();

    pObject = NULL;
}

/*! \ingroup GrpBaseBaseRefCountFn
 */

template <class T> inline
void clearRefPVector(std::vector<T *> &vVector)
{
    for(UInt32 i = 0; i < vVector.size(); i++)
        vVector[i]->subRef();

    vVector.erase(vVector.begin(), vVector.end());
}

/*! \ingroup GrpBaseBaseRefCountFn
 */

template <class T> inline
void clearRefPVectorP(std::vector<T *> *pVector)
{
    if(pVector != NULL)
    {
        for(UInt32 uiIndex = 0; uiIndex < pVector->size(); uiIndex++)
            (*pVector)[uiIndex]->subRef();

        pVector->erase(pVector->begin(), pVector->end());
    }
}

OSG_END_NAMESPACE

#define OSGBASEFUNCTIONS_INLINE_CVSID "@(#)$Id: $"
