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


#ifndef _OSGBASEFUNCTIONS_H_
#define _OSGBASEFUNCTIONS_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <math.h>

#define __EXTENSIONS__ 1

#include <string.h>

#ifndef WIN32
#include <strings.h>
#endif

#include <OSGConfig.h>
#include <OSGBaseTypes.h>


#ifndef WIN32
#endif

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//   Base Math Functions
//---------------------------------------------------------------------------

/*! @name Generall Desclarations
 */

/*@{*/

/*! \brief osgsqrt
 *  \ingroup BaseMathFunctions
 */

template <class OSGFloatTypeT>
OSGFloatTypeT osgsqrt(const OSGFloatTypeT &rVal);

/*! \brief osgcos
 *  \ingroup BaseMathFunctions
 */

template <class OSGFloatTypeT> 
OSGFloatTypeT osgcos(const OSGFloatTypeT &rVal);

/*! \brief osgsin
 *  \ingroup BaseMathFunctions
 */

template <class OSGFloatTypeT> 
OSGFloatTypeT osgsin(const OSGFloatTypeT &rVal);

/*! \brief osgtan
 *  \ingroup BaseMathFunctions
 */

template <class OSGFloatTypeT> 
OSGFloatTypeT osgtan(const OSGFloatTypeT &rVal);

/*! \brief osgacos
 *  \ingroup BaseMathFunctions
 */

template <class OSGFloatTypeT> 
OSGFloatTypeT osgacos(const OSGFloatTypeT &rVal);

/*! \brief osgasin
 *  \ingroup BaseMathFunctions
 */

template <class OSGFloatTypeT> 
OSGFloatTypeT osgasin(const OSGFloatTypeT &rVal);

/*! \brief osgatan
 *  \ingroup BaseMathFunctions
 */

template <class OSGFloatTypeT> 
OSGFloatTypeT osgatan(const OSGFloatTypeT &rVal);

/*! \brief osgratan2
 *  \ingroup BaseMathFunctions
 */

template <class OSGFloatTypeT> 
OSGFloatTypeT osgatan2(const OSGFloatTypeT &rVal1, 
                       const OSGFloatTypeT &rVal2);

/*! \brief osgdegree2rad
 *  \ingroup BaseMathFunctions
 */

template <class OSGFloatTypeT> 
OSGFloatTypeT osgdegree2rad(const OSGFloatTypeT &rVal);

/*! \brief osgrad2degree
 *  \ingroup BaseMathFunctions
 */

template <class OSGFloatTypeT> 
OSGFloatTypeT osgrad2degree(const OSGFloatTypeT &rVal);

/*! \brief osgabs
 *  \ingroup BaseMathFunctions
 */

template <class OSGFloatTypeT> 
OSGFloatTypeT osgabs(const OSGFloatTypeT &rVal);

/*! \brief osgpow
 *  \ingroup BaseMathFunctions
 */

template <class OSGFloatTypeT> 
OSGFloatTypeT osgpow(const OSGFloatTypeT &rVal, const OSGFloatTypeT &rExp);

/*! \brief osgfloor
 *  \ingroup BaseMathFunctions
 */

template <class OSGFloatTypeT> 
OSGFloatTypeT osgfloor(const OSGFloatTypeT &rVal);

/*@}*/

/*! @name Real32 Specializations
 */

/*@{*/

/*! \brief osgsqrt
 *  \ingroup BaseMathFunctions
 */

template <> inline 
OSGReal32 osgsqrt(const OSGReal32 &rVal)
{
#ifdef OSG_HAS_FLOATMATH
    return sqrtf(rVal);
#else
    return (OSGReal32) sqrt((OSGReal32) rVal);
#endif
}

/*! \brief osgcos
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSGReal32 osgcos(const OSGReal32 &rVal)
{
#ifdef OSG_HAS_FLOATMATH
    return cosf(rVal);
#else
    return (OSGReal32) cos((OSGReal32) rVal);
#endif
}

/*! \brief osgsin
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSGReal32 osgsin(const OSGReal32 &rVal)
{
#ifdef OSG_HAS_FLOATMATH
    return sinf(rVal);
#else
    return (OSGReal32) sin((OSGReal32) rVal);
#endif
}

/*! \brief osgtan
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSGReal32 osgtan(const OSGReal32 &rVal)
{
#ifdef OSG_HAS_FLOATMATH
    return tanf(rVal);
#else
    return (OSGReal32) tan((OSGReal32) rVal);
#endif
}

/*! \brief osgacos
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSGReal32 osgacos(const OSGReal32 &rVal)
{
#ifdef OSG_HAS_FLOATMATH
    return acosf(rVal);
#else
    return (OSGReal32) acos((OSGReal32) rVal);
#endif
}

/*! \brief osgasin
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSGReal32 osgasin(const OSGReal32 &rVal)
{
#ifdef OSG_HAS_FLOATMATH
    return asinf(rVal);
#else
    return (OSGReal32) asin((OSGReal32) rVal);
#endif
}

/*! \brief osgatan
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSGReal32 osgatan(const OSGReal32 &rVal)
{
#ifdef OSG_HAS_FLOATMATH
    return atanf(rVal);
#else
    return (OSGReal32) atan((OSGReal32) rVal);
#endif
}

/*! \brief osgatan2
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSGReal32 osgatan2(const OSGReal32 &rVal1, const OSGReal32 &rVal2)
{
#ifdef OSG_HAS_FLOATMATH
#ifndef _OSG_HAS_ATANF2__
    return atan2f(rVal1, rVal2);
#else
	return (OSGReal32) atan2((OSGReal32) rVal1, (OSGReal32) rVal2);
#endif
#else
	return (OSGReal32) atan2((OSGReal32) rVal1, (OSGReal32) rVal2);
#endif
}

/*! \brief osgdegree2rad
 *  \ingroup BaseMathFunctions
 */

template <> inline 
OSGReal32 osgdegree2rad(const OSGReal32 &rValue)
{
   return (rValue/360.f) * 2.f * 3.1415926535f;
}

/*! \brief osgrad2degree
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSGReal32 osgrad2degree(const OSGReal32 &rValue)
{
   return (rValue/(2.f * 3.1415926535f)) * 360.f;
}

/*! \brief osgabs
 *  \ingroup BaseMathFunctions
 */

template <> inline 
OSGReal32 osgabs(const OSGReal32 &rValue)
{
#ifdef OSG_HAS_FLOATMATH
    return fabsf(rValue);
#else
    return (OSGReal32) fabs((OSGReal32) rValue);
#endif
}

/*! \brief osgpow
 *  \ingroup BaseMathFunctions
 */

template <> inline 
OSGReal32 osgpow(const OSGReal32 &rValue, const OSGReal32 &rExp)
{
#ifdef OSG_HAS_FLOATMATH
    return powf(rValue, rExp);
#else
    return (OSGReal32) pow((OSGReal32) rValue, (OSGReal32) rExp);
#endif
}

/*! \brief osgfloor
 *  \ingroup BaseMathFunctions
 */

template <> inline 
OSGReal32 osgfloor(const OSGReal32 &rValue)
{
#ifdef OSG_HAS_FLOATMATH
    return floorf(rValue);
#else
    return (OSGReal32) floor((OSGReal32) rValue);
#endif
}

/*@}*/

/*! @name Real64 Specializations
 */

/*@{*/

/*! \brief osgsqrt
 *  \ingroup BaseMathFunctions
 */

template <> inline 
OSGReal64 osgsqrt(const OSGReal64 &rVal)
{
    return sqrt(rVal);
}

/*! \brief osgcos
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSGReal64 osgcos(const OSGReal64 &rVal)
{
    return cos(rVal);
}

/*! \brief osgsin
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSGReal64 osgsin(const OSGReal64 &rVal)
{
    return sin(rVal);
}

/*! \brief osgtan
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSGReal64 osgtan(const OSGReal64 &rVal)
{
    return tan(rVal);
}

/*! \brief osgacos
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSGReal64 osgacos(const OSGReal64 &rVal)
{
    return acos(rVal);
}

/*! \brief osgasin
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSGReal64 osgasin(const OSGReal64 &rVal)
{
    return asin(rVal);
}

/*! \brief osgatan
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSGReal64 osgatan(const OSGReal64 &rVal)
{
    return atan(rVal);
}

/*! \brief osgatan2
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSGReal64 osgatan2(const OSGReal64 &rVal1, const OSGReal64 &rVal2)
{
    return atan2(rVal1, rVal2);
}

/*! \brief osgdegree2rad
 *  \ingroup BaseMathFunctions
 */

template <> inline 
OSGReal64 osgdegree2rad(const OSGReal64 &rValue)
{
   return (rValue/360) * 2 * 3.1415926535;
}

/*! \brief osgrad2degree
 *  \ingroup BaseMathFunctions
 */

template <> inline
OSGReal64 osgrad2degree(const OSGReal64 &rValue)
{
   return (rValue/(2 * 3.1415926535)) * 360;
}

/*! \brief osgabs
 *  \ingroup BaseMathFunctions
 */

template <> inline 
OSGReal64 osgabs(const OSGReal64 &rValue)
{
    return fabs(rValue);
}

/*! \brief osgpow
 *  \ingroup BaseMathFunctions
 */

template <> inline 
OSGReal64 osgpow(const OSGReal64 &rValue, const OSGReal64 &rExp)
{
    return pow(rValue, rExp);
}

/*! \brief osgfloor
 *  \ingroup BaseMathFunctions
 */

template <> inline 
OSGReal64 osgfloor(const OSGReal64 &rValue)
{
    return floor(rValue);
}

/*! \brief OSGMax
 *  \ingroup BaseMathFunctions
 */

template <OSGInt32 uiValue1, OSGInt32 uiValue2>
struct OSGMax
{
    enum _iMax { iMax = uiValue1 < uiValue2 ? uiValue2 : uiValue1 };
};

/*@}*/

/*! @name String Functions 
 */

/*@{*/

/*! \brief copy c strings, allocate new memory using new []
 *  \ingroup BaseFunctions
 */

inline
void stringDup(const char *szInput, char *&szOutput)
{
    delete [] szOutput;
    szOutput = NULL;

    if(szInput != NULL)
    {
        szOutput = new char[strlen(szInput) + 1];
        strcpy(szOutput, szInput);
    }
}

/*! \brief string case compare
 *  \ingroup BaseFunctions
 */

inline 
OSGInt32 osgstrcasecmp(const char *string1, const char *string2)
{
#ifndef WIN32
	return strcasecmp(string1, string2);
#else
	return _stricmp(string1, string2);
#endif
}

/*! \brief String compare used fo a STL weak ordering
 *  \ingroup BaseFunctions
 */

struct OSGLTString
{
    bool operator()(const char* s1, const char* s2) const
    {
        return strcmp(s1, s2) < 0;
    }
};

/*@}*/

/*! @name Initialization
 */

/*@{*/

/*! \var OSGBool (*OSGInitFuncF)(int argc, char **argv);
 *  \brief OSGInitFuncF
 *  \ingroup BaseFunctions
 */

typedef OSGBool (*OSGInitFuncF)(int argc, char **argv);

/*! \var OSGBool (*OSGExitFuncF)(void);
 *  \brief OSGExitFuncF
 *  \ingroup BaseFunctions
 */

typedef OSGBool (*OSGExitFuncF)(void);

/*! \brief osgAddInitFunction
 *  \ingroup BaseFunctions
 */

void osgAddInitFunction(OSGInitFuncF initFunc);

/*! \brief osgAddExitFunction
 *  \ingroup BaseFunctions
 */

void osgAddExitFunction(OSGExitFuncF exitFunc);

/*! \brief osgInit
 *  \ingroup BaseFunctions
 */

OSGBool osgInit(int argc, char **argv);

/*! \brief osgExit  
 *  \ingroup BaseFunctions
 */

OSGBool osgExit(void);

/*@}*/

OSG_END_NAMESPACE

#endif /* OSGBASEFUNCTIONS_H */
