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

#include <math.h>

#include <string.h>

#ifndef WIN32
#include <strings.h>
#include <unistd.h>
#endif

#ifdef __sun
#include <stdlib.h>
#endif

#include <OSGConfig.h>
#include <OSGBase.h>
#include <OSGBaseTypes.h>

#include <vector>

OSG_BEGIN_NAMESPACE

/*---------------------------------------------------------------------*/
/*! \name                    Base Math Functions                       */
/*! \{                                                                 */

/*! \brief osgsqrt
 *  \ingroup BaseMathFunctions
 */

template <class FloatTypeT> inline
typename TypeConstants<FloatTypeT>::RealReturnType 
    osgsqrt(const FloatTypeT rVal);

/*! \brief osgcos
 *  \ingroup BaseMathFunctions
 */

template <class FloatTypeT> inline
typename TypeConstants<FloatTypeT>::RealReturnType 
    osgcos(const FloatTypeT rVal);

/*! \brief osgsin
 *  \ingroup BaseMathFunctions
 */

template <class FloatTypeT> inline
typename TypeConstants<FloatTypeT>::RealReturnType 
    osgsin(const FloatTypeT rVal);

/*! \brief osgtan
 *  \ingroup BaseMathFunctions
 */

template <class FloatTypeT> inline
typename TypeConstants<FloatTypeT>::RealReturnType
    osgtan(const FloatTypeT rVal);

/*! \brief osgacos
 *  \ingroup BaseMathFunctions
 */

template <class FloatTypeT> inline
typename TypeConstants<FloatTypeT>::RealReturnType 
    osgacos(const FloatTypeT rVal);

/*! \brief osgasin
 *  \ingroup BaseMathFunctions
 */

template <class FloatTypeT> inline
typename TypeConstants<FloatTypeT>::RealReturnType
    osgasin(const FloatTypeT rVal);

/*! \brief osgatan
 *  \ingroup BaseMathFunctions
 */

template <class FloatTypeT> inline
typename TypeConstants<FloatTypeT>::RealReturnType 
    osgatan(const FloatTypeT rVal);

/*! \brief osgatan2
 *  \ingroup BaseMathFunctions
 */

template <class FloatTypeT> inline
typename TypeConstants<FloatTypeT>::RealReturnType 
    osgatan2(const FloatTypeT rVal1,
             const FloatTypeT rVal2);

/*! \brief osgabs
 *  \ingroup BaseMathFunctions
 */

template <class FloatTypeT> inline
FloatTypeT osgabs(const FloatTypeT rVal);

/*! \brief osgpow
 *  \ingroup BaseMathFunctions
 */

template <class FloatTypeT> inline
typename TypeConstants<FloatTypeT>::RealReturnType
    osgpow(const FloatTypeT rVal,
           const FloatTypeT rExp);

/*! \brief osglog
 *  \ingroup BaseMathFunctions
 */

template <class FloatTypeT> inline
typename TypeConstants<FloatTypeT>::RealReturnType
    osglog(const FloatTypeT rVal);

/*! \brief osgexp
 *  \ingroup BaseMathFunctions
 */

template <class FloatTypeT> inline
typename TypeConstants<FloatTypeT>::RealReturnType
    osgexp(const FloatTypeT rVal);

/*! \brief osgfloor
 *  \ingroup BaseMathFunctions
 */

template <class FloatTypeT> inline
typename TypeConstants<FloatTypeT>::RealReturnType
    osgfloor(const FloatTypeT rVal);

/*! \brief osgfinite
 *  \ingroup BaseMathFunctions
 */

template <class FloatTypeT> inline
UInt32 osgfinite(const FloatTypeT rVal);

/*! \brief osgMin
 *  \ingroup BaseMathFunctions
 */

template <class TypeT> inline
TypeT osgMin(const TypeT lVal, const TypeT rVal);

/*! \brief osgMax
 *  \ingroup BaseMathFunctions
 */

template <class TypeT> inline
TypeT osgMax(const TypeT lVal, const TypeT rVal);

/*! \brief osgdegree2rad
 *  \ingroup BaseMathFunctions
 */

template <class FloatTypeT> inline
typename TypeConstants<FloatTypeT>::RealReturnType 
    osgdegree2rad(const FloatTypeT rVal);

/*! \brief osgrad2degree
 *  \ingroup BaseMathFunctions
 */

template <class FloatTypeT> inline
typename TypeConstants<FloatTypeT>::RealReturnType
    osgrad2degree(const FloatTypeT rVal);


/*! \brief deg2rad
 *  \ingroup BaseMathFunctions
 */

template <class FloatTypeT> inline
typename TypeConstants<FloatTypeT>::RealReturnType
    deg2rad(const FloatTypeT rVal);

/*! \brief rad2deg
 *  \ingroup BaseMathFunctions
 */

template <class FloatTypeT> inline
typename TypeConstants<FloatTypeT>::RealReturnType
    rad2deg(const FloatTypeT rVal);

/*! \brief osgispower2
 *  \ingroup BaseMathFunctions
 */

template <class TypeT> inline
bool osgispower2(TypeT rVal);

/*! \brief osgnextpower2
 *  \ingroup BaseMathFunctions
 */

template <class TypeT> inline
TypeT osgnextpower2(TypeT rVal);


/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name            Static (compile time) functions                   */
/*! \{                                                                 */

/*! \brief osgStaticMax
 *  \ingroup BaseMathFunctions
 */

template <Int32 uiValue1, Int32 uiValue2>
struct OSG_BASE_DLLMAPPING osgStaticMax
{
    enum _iMax { iMax = uiValue1 < uiValue2 ? uiValue2 : uiValue1 };
};

#if defined(__sgi) || defined(__linux) || defined(__sun) || defined(darwin)

/*
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

#else

/*! \ingroup BaseMathFunctions
 *  \brief osgIFGen
 */

template <bool IConditionV>
struct osgIFGen
{
    template<class IThenT, class IElseT>
    struct osgIFSwitch
    {
        typedef IThenT _IRet;
        typedef IElseT _IDummyRef;
    };
};

/*! \ingroup BaseMathFunctions
 *  \brief osgIFGen<false>
 */

template <>
struct osgIFGen<false>
{
    template<class IThenT, class IElseT>
    struct osgIFSwitch
    {
        typedef IElseT _IRet;
        typedef IThenT _IDummyRef;
    };
};


/*! \ingroup BaseMathFunctions
 *  \brief osgIF
 */

template<bool IConditionV, class IThenT, class IElseT>
struct osgIF
{
    typedef osgIFGen<IConditionV>::osgIFSwitch<IThenT, IElseT>::_IRet _IRet;
};

#endif

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name                    String Functions                          */
/*! \{                                                                 */

/*! \brief copy c strings, allocate new memory using new []
 *  \ingroup BaseFunctions
 */

inline
void stringDup(const Char8 *szInput, Char8 *&szOutput);

/*! \brief limited string compare
 *  \ingroup BaseFunctions
 */

inline
Int32 stringncmp(const Char8 *string1, const Char8 *string2, size_t count);

/*! \brief string length
 *  \ingroup BaseFunctions
 */

inline
Int32 stringlen(const Char8 *string1);


/*! \brief string compare
 *  \ingroup BaseFunctions
 */

inline
Int32 stringcmp(const Char8 *string1, const Char8 *string2);

/*! \brief string case compare
 *  \ingroup BaseFunctions
 */

inline
Int32 stringcasecmp(const Char8 *string1,
                    const Char8 *string2);

/*! \brief String less than compare functor used for a STL weak ordering
 *  \ingroup BaseFunctions
 */

struct LTString
{
    bool operator()(const Char8 *s1, const Char8 *s2) const
    {
        return ::strcmp(s1, s2) < 0;
    }
};

/*! \brief String equal compare functor
 *  \ingroup BaseFunctions
 */

struct EQString
{
    bool operator()(const Char8 *s1, const Char8 *s2) const
    {
        return ::strcmp(s1, s2) == 0;
    }
};

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name                     Misc Functions                           */
/*! \{                                                                 */

/*! \brief find the index that has the largest absolute value for a vec3
 *  \ingroup BaseFunctions
 */

template<class VecPntT> inline
UInt32 getMaxIndexAbs3(const VecPntT &v);

/*! \brief set the value of an environment variable
 *  \ingroup BaseFunctions
 */

inline
Int32 putenv(Char8 *string);


/*! \brief sleep
 *  \ingroup BaseFunctions
 */

inline
void osgsleep(UInt32 millisecs);

/*! \brief get a random value between 0 and 1
 *  \ingroup BaseFunctions
 */

inline
Real32 osgrand(void);

/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name         MemoryObject Reference Count Functions               */
/*! \{                                                                 */

/*! \brief setRefP
 *  \ingroup BaseFunctions
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

/*! \brief addRefP
 *  \ingroup BaseFunctions
 */

template <class T> inline
void addRefP(T *&pObject)
{
    if(pObject != NULL)
        pObject->addRef();
}

/*! \brief subRefP
 *  \ingroup BaseFunctions
 */

template <class T> inline
void subRefP(T *&pObject)
{
    if(pObject != NULL)
        pObject->subRef();
}

/*! \brief clearRefP
 *  \ingroup BaseFunctions
 */

template <class T> inline
void clearRefP(T *&pObject)
{
    if(pObject != NULL)
        pObject->subRef();

    pObject = NULL;
}

/*! \brief clearRefPVector
 *  \ingroup BaseFunctions
 */

#if 1
template <class T> inline
void clearRefPVector(vector<T *> &gVector)
{
    for(UInt32 i = 0; i < gVector.size(); i++)
        gVector[i]->subRef();

    gVector.erase(gVector.begin(), gVector.end());
}

/*! \brief clearRefPVectorP
 *  \ingroup BaseFunctions
 */

template <class T> inline
void clearRefPVectorP(vector<T *> *pVector)
{
    if(pVector != NULL)
    {
        for(UInt32 uiIndex = 0; uiIndex < pVector->size(); uiIndex++)
            (*pVector)[uiIndex]->subRef();

        pVector->erase(pVector->begin(), pVector->end());
    }
}
#endif


/*! \}                                                                 */
/*---------------------------------------------------------------------*/
/*! \name                     Initialization                           */
/*! \{                                                                 */

enum SystemState
{
    Startup  = 0x01,
    Running  = 0x02,
    Shutdown = 0x03
};

extern OSG_BASE_DLLMAPPING SystemState GlobalSystemState;

/*! \var bool (*InitFuncF)(int argc, char **argv);
 *  \brief InitFuncF
 *  \ingroup BaseFunctions
 *
 * order :
 * 
 * PreMP
 * MP
 * (Factory [GV])
 * Init
 */

typedef bool (*InitFuncF)(void);

/*! \var bool (*ExitFuncF)(void);
 *  \brief ExitFuncF
 *  \ingroup BaseFunctions
 * order :
 * 
 * (Factory [GV])
 * SystemExit
 * MP
 * PostMP
 */

typedef bool (*ExitFuncF)(void);

/*! \brief addInitFunction, function called by osgInit after the
 *         multithreading is initialized and after dynamically loading 
 *         a shared object
 *  \ingroup BaseFunctions
 */

OSG_BASE_DLLMAPPING 
void addInitFunction      (InitFuncF initFunc);

/*! \brief addSystemExitFunction, function called by osgExit before
 *         multithreading is termininated
 *  \ingroup BaseFunctions
 */

OSG_BASE_DLLMAPPING 
void addSystemExitFunction(ExitFuncF exitFunc);

/*! \brief addMPInitFunction, function called by osgInit before
           the multithreading is initialized.
 *  \ingroup BaseFunctions
 */

OSG_BASE_DLLMAPPING 
void addPreMPInitFunction (InitFuncF initFunc);

/*! \brief addPostMPExitFunction, function called by osgExit after
 *         multithreading is terminated
 *  \ingroup BaseFunctions
 */

OSG_BASE_DLLMAPPING 
void addPostMPExitFunction(ExitFuncF exitFunc);

/*! \brief Init
 *  \ingroup BaseFunctions
 */

OSG_BASE_DLLMAPPING 
bool osgInit(Int32 argc, Char8 **argv);

/*! \brief Exit
 *  \ingroup BaseFunctions
 */

OSG_BASE_DLLMAPPING 
bool osgExit(void);

/*! \}                                                                 */

OSG_END_NAMESPACE

#include "OSGBaseFunctions.inl"

#endif /* OSGBASEFUNCTIONS_H */
