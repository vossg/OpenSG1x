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
#include <unistd.h>
#endif

#include <OSGConfig.h>
#include <OSGBase.h>
#include <OSGBaseTypes.h>

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

template <class FloatTypeT>
OSG_BASE_DLLMAPPING FloatTypeT osgsqrt(const FloatTypeT &rVal);

/*! \brief osgcos
 *  \ingroup BaseMathFunctions
 */

template <class FloatTypeT> 
OSG_BASE_DLLMAPPING FloatTypeT osgcos(const FloatTypeT &rVal);

/*! \brief osgsin
 *  \ingroup BaseMathFunctions
 */

template <class FloatTypeT> 
OSG_BASE_DLLMAPPING FloatTypeT osgsin(const FloatTypeT &rVal);

/*! \brief osgtan
 *  \ingroup BaseMathFunctions
 */

template <class FloatTypeT> 
OSG_BASE_DLLMAPPING FloatTypeT osgtan(const FloatTypeT &rVal);

/*! \brief osgacos
 *  \ingroup BaseMathFunctions
 */

template <class FloatTypeT> 
OSG_BASE_DLLMAPPING FloatTypeT osgacos(const FloatTypeT &rVal);

/*! \brief osgasin
 *  \ingroup BaseMathFunctions
 */

template <class FloatTypeT> 
OSG_BASE_DLLMAPPING FloatTypeT osgasin(const FloatTypeT &rVal);

/*! \brief osgatan
 *  \ingroup BaseMathFunctions
 */

template <class FloatTypeT> 
OSG_BASE_DLLMAPPING FloatTypeT osgatan(const FloatTypeT &rVal);

/*! \brief osgratan2
 *  \ingroup BaseMathFunctions
 */

template <class FloatTypeT> 
OSG_BASE_DLLMAPPING FloatTypeT osgatan2(const FloatTypeT &rVal1, 
                                        const FloatTypeT &rVal2);

/*! \brief osgdegree2rad
 *  \ingroup BaseMathFunctions
 */

template <class FloatTypeT> 
OSG_BASE_DLLMAPPING FloatTypeT osgdegree2rad(const FloatTypeT &rVal);

/*! \brief osgrad2degree
 *  \ingroup BaseMathFunctions
 */

template <class FloatTypeT> 
OSG_BASE_DLLMAPPING FloatTypeT osgrad2degree(const FloatTypeT &rVal);

/*! \brief osgabs
 *  \ingroup BaseMathFunctions
 */

template <class FloatTypeT> 
OSG_BASE_DLLMAPPING FloatTypeT osgabs(const FloatTypeT &rVal);

/*! \brief osgpow
 *  \ingroup BaseMathFunctions
 */

template <class FloatTypeT> 
OSG_BASE_DLLMAPPING FloatTypeT osgpow(const FloatTypeT &rVal, 
                                      const FloatTypeT &rExp);

/*! \brief osgfloor
 *  \ingroup BaseMathFunctions
 */

template <class FloatTypeT> 
OSG_BASE_DLLMAPPING FloatTypeT osgfloor(const FloatTypeT &rVal);

/*@}*/

/*! @name Real32 Specializations
 */

/*@{*/

/*! \brief osgsqrt
 *  \ingroup BaseMathFunctions
 */

template <> inline 
Real32 osgsqrt(const Real32 &rVal)
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
Real32 osgcos(const Real32 &rVal)
{
#ifdef OSG_HAS_FLOATMATH
    return cosf(rVal);
#else
    return (Real32) cos((Real32) rVal);
#endif
}

/*! \brief osgsin
 *  \ingroup BaseMathFunctions
 */

template <> inline
Real32 osgsin(const Real32 &rVal)
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
Real32 osgtan(const Real32 &rVal)
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
Real32 osgacos(const Real32 &rVal)
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
Real32 osgasin(const Real32 &rVal)
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
Real32 osgatan(const Real32 &rVal)
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
Real32 osgatan2(const Real32 &rVal1, const Real32 &rVal2)
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
Real32 osgdegree2rad(const Real32 &rValue)
{
   return (rValue/360.f) * 2.f * 3.1415926535f;
}

/*! \brief osgrad2degree
 *  \ingroup BaseMathFunctions
 */

template <> inline
Real32 osgrad2degree(const Real32 &rValue)
{
   return (rValue/(2.f * 3.1415926535f)) * 360.f;
}

/*! \brief osgabs
 *  \ingroup BaseMathFunctions
 */

template <> inline 
Real32 osgabs(const Real32 &rValue)
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
Real32 osgpow(const Real32 &rValue, const Real32 &rExp)
{
#ifdef OSG_HAS_FLOATMATH
    return powf(rValue, rExp);
#else
    return (Real32) pow((Real32) rValue, (Real32) rExp);
#endif
}

/*! \brief osgfloor
 *  \ingroup BaseMathFunctions
 */

template <> inline 
Real32 osgfloor(const Real32 &rValue)
{
#ifdef OSG_HAS_FLOATMATH
    return floorf(rValue);
#else
    return (Real32) floor((Real32) rValue);
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
Real64 osgsqrt(const Real64 &rVal)
{
    return sqrt(rVal);
}

/*! \brief osgcos
 *  \ingroup BaseMathFunctions
 */

template <> inline
Real64 osgcos(const Real64 &rVal)
{
    return cos(rVal);
}

/*! \brief osgsin
 *  \ingroup BaseMathFunctions
 */

template <> inline
Real64 osgsin(const Real64 &rVal)
{
    return sin(rVal);
}

/*! \brief osgtan
 *  \ingroup BaseMathFunctions
 */

template <> inline
Real64 osgtan(const Real64 &rVal)
{
    return tan(rVal);
}

/*! \brief osgacos
 *  \ingroup BaseMathFunctions
 */

template <> inline
Real64 osgacos(const Real64 &rVal)
{
    return acos(rVal);
}

/*! \brief osgasin
 *  \ingroup BaseMathFunctions
 */

template <> inline
Real64 osgasin(const Real64 &rVal)
{
    return asin(rVal);
}

/*! \brief osgatan
 *  \ingroup BaseMathFunctions
 */

template <> inline
Real64 osgatan(const Real64 &rVal)
{
    return atan(rVal);
}

/*! \brief osgatan2
 *  \ingroup BaseMathFunctions
 */

template <> inline
Real64 osgatan2(const Real64 &rVal1, const Real64 &rVal2)
{
    return atan2(rVal1, rVal2);
}

/*! \brief osgdegree2rad
 *  \ingroup BaseMathFunctions
 */

template <> inline 
Real64 osgdegree2rad(const Real64 &rValue)
{
   return (rValue/360) * 2 * 3.1415926535;
}

/*! \brief osgrad2degree
 *  \ingroup BaseMathFunctions
 */

template <> inline
Real64 osgrad2degree(const Real64 &rValue)
{
   return (rValue/(2 * 3.1415926535)) * 360;
}

/*! \brief osgabs
 *  \ingroup BaseMathFunctions
 */

template <> inline 
Real64 osgabs(const Real64 &rValue)
{
    return fabs(rValue);
}

/*! \brief osgpow
 *  \ingroup BaseMathFunctions
 */

template <> inline 
Real64 osgpow(const Real64 &rValue, const Real64 &rExp)
{
    return pow(rValue, rExp);
}

/*! \brief osgfloor
 *  \ingroup BaseMathFunctions
 */

template <> inline 
Real64 osgfloor(const Real64 &rValue)
{
    return floor(rValue);
}

/*! \brief osgMax
 *  \ingroup BaseMathFunctions
 */

template <Int32 uiValue1, Int32 uiValue2>
struct OSG_BASE_DLLMAPPING osgMax
{
    enum _iMax { iMax = uiValue1 < uiValue2 ? uiValue2 : uiValue1 };
};

/*! \ingroup BaseMathFunctions
 *  \brief osgIF
 */

template<bool IConditionV, class IThenT, class IElseT>
struct osgIF
{
    typedef IThenT _IRet;
    typedef IElseT _IDummyRef;
};

/*! \ingroup BaseMathFunctions
 *  \brief osgIF<false, IThenT, IElseT>
 */

template<class IThenT, class IElseT>
struct osgIF<false, IThenT, IElseT>
{
    typedef IElseT _IRet;
    typedef IThenT _IDummyRef;
};

/*@}*/

/*! @name String Functions 
 */

/*@{*/

/*! \brief copy c strings, allocate new memory using new []
 *  \ingroup BaseFunctions
 */

inline
OSG_BASE_DLLMAPPING void osgstringDup(const char *szInput, char *&szOutput)
{
    delete [] szOutput;
    szOutput = NULL;

    if(szInput != NULL)
    {
        szOutput = new char[strlen(szInput) + 1];
        strcpy(szOutput, szInput);
    }
}

/*! \brief string compare
 *  \ingroup BaseFunctions
 */

inline 
OSG_BASE_DLLMAPPING Int32 osgstrcmp(const char *string1, const char *string2)
{
	return strcmp(string1, string2);
}

/*! \brief string case compare
 *  \ingroup BaseFunctions
 */

inline 
OSG_BASE_DLLMAPPING Int32 osgstrcasecmp(const char *string1, 
                                        const char *string2)
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

OSG_BASE_DLLMAPPING struct LTString
{
    bool operator()(const char* s1, const char* s2) const
    {
        return strcmp(s1, s2) < 0;
    }
};

/*@}*/

/*! @name Sleep
 */

/*@{*/

inline
OSG_BASE_DLLMAPPING void osgsleep(UInt32 usecs)
{
#ifdef WIN32
    Sleep(usecs);
#else
    
    // Rough aproximation, have to find a better way soon (GV)

    if( (usecs * 1000) > 1000000)
    {
        sleep(usecs / 1000);
    }
    else
    {
        usleep(usecs * 1000);
    }
#endif
}

/*@}*/

/*! @name Initialization
 */

/*@{*/

/*! \var Bool (*InitFuncF)(int argc, char **argv);
 *  \brief InitFuncF
 *  \ingroup BaseFunctions
 */

typedef Bool (*InitFuncF)(int argc, char **argv);

/*! \var Bool (*ExitFuncF)(void);
 *  \brief ExitFuncF
 *  \ingroup BaseFunctions
 */

typedef Bool (*ExitFuncF)(void);

/*! \brief AddInitFunction
 *  \ingroup BaseFunctions
 */

OSG_BASE_DLLMAPPING void osgAddInitFunction(InitFuncF initFunc);

/*! \brief AddExitFunction
 *  \ingroup BaseFunctions
 */

OSG_BASE_DLLMAPPING void osgAddExitFunction(ExitFuncF exitFunc);

/*! \brief Init
 *  \ingroup BaseFunctions
 */

OSG_BASE_DLLMAPPING Bool osgInit(int argc, char **argv);

/*! \brief Exit  
 *  \ingroup BaseFunctions
 */

OSG_BASE_DLLMAPPING Bool osgExit(void);

/*@}*/

OSG_END_NAMESPACE

#endif /* OSGBASEFUNCTIONS_H */
