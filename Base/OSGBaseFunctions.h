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
OSG_BASE_DLLMAPPING void osgstringDup(const char *szInput, char *&szOutput);

/*! \brief limited string compare
 *  \ingroup BaseFunctions
 */

inline 
OSG_BASE_DLLMAPPING
Int32 osgstrncmp(const char *string1, const char *string2, size_t count);

/*! \brief limited string compare
 *  \ingroup BaseFunctions
 */


inline 
OSG_BASE_DLLMAPPING Int32 osgstrlen(const char *string1);


/*! \brief string compare
 *  \ingroup BaseFunctions
 */

inline 
OSG_BASE_DLLMAPPING Int32 osgstrcmp(const char *string1, const char *string2);

/*! \brief string case compare
 *  \ingroup BaseFunctions
 */

inline 
OSG_BASE_DLLMAPPING Int32 osgstrcasecmp(const char *string1, 
                                        const char *string2);

/*! \brief String less than compare functor used for a STL weak ordering
 *  \ingroup BaseFunctions
 */

OSG_BASE_DLLMAPPING struct LTString
{
    Bool operator()(const char* s1, const char* s2) const
    {
        return strcmp(s1, s2) < 0;
    }
};

/*! \brief String equal compare functor
 *  \ingroup BaseFunctions
 */

OSG_BASE_DLLMAPPING struct EQString
{
    Bool operator()(const char* s1, const char* s2) const
    {
        return strcmp(s1, s2) == 0;
    }
};

/*@}*/

/*! @name Sleep
 */

/*@{*/

inline
OSG_BASE_DLLMAPPING void osgsleep(UInt32 usecs);

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

#include "OSGBaseFunctions.inl"

#endif /* OSGBASEFUNCTIONS_H */
