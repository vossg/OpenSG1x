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
#include <ieeefp.h>
#endif

#ifdef __sgi
#include <ieeefp.h>
#endif

#include <OSGConfig.h>
#include <OSGBase.h>
#include <OSGBaseTypes.h>

#include <vector>
#include <string>
#include <iterator>

#ifdef OSG_STL_HAS_HASH_MAP
#ifdef OSG_USE_HASH_COMPARE
#include <hash_map>
#endif
#endif

OSG_BEGIN_NAMESPACE

/*---------------------------------------------------------------------*/
/*                        Base Math Runtime Functions                  */

template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgsqrt(const FloatTypeT rVal);


template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgcos(const FloatTypeT rVal);


template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgsin(const FloatTypeT rVal);


template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgtan(const FloatTypeT rVal);


template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgacos(const FloatTypeT rVal);


template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgasin(const FloatTypeT rVal);


template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgatan(const FloatTypeT rVal);


template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgatan2(const FloatTypeT rVal1,
             const FloatTypeT rVal2);


template <class FloatTypeT> inline
FloatTypeT osgabs(const FloatTypeT rVal);


template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgpow(const FloatTypeT rVal,
           const FloatTypeT rExp);


template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osglog(const FloatTypeT rVal);


template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgexp(const FloatTypeT rVal);


template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgfloor(const FloatTypeT rVal);

template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgceil(const FloatTypeT rVal);


template <class FloatTypeT> inline
UInt32 osgfinite(const FloatTypeT rVal);

/*---------------------------------------------------------------------*/
/*                           Min / Max Functions                       */

template <class TypeT> inline
TypeT osgMin(const TypeT lVal, const TypeT rVal);


template <class TypeT> inline
TypeT osgMax(const TypeT lVal, const TypeT rVal);


template <class TypeT> inline
TypeT osgClamp(const TypeT minVal, const TypeT val, const TypeT maxVal);

/*---------------------------------------------------------------------*/
/*                               Swap Functions                        */

template <class TypeT> inline
void osgSwap(TypeT & lVal, TypeT & rVal);

/*---------------------------------------------------------------------*/
/*                               Sign Functions                        */

template <class TypeT> inline
Int8 osgSgn(TypeT val);

/*---------------------------------------------------------------------*/
/*                           Rad / Degree Functions                    */

template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgdegree2rad(const FloatTypeT rVal);


template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    osgrad2degree(const FloatTypeT rVal);


template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    deg2rad(const FloatTypeT rVal);


template <class FloatTypeT> inline
typename TypeTraits<FloatTypeT>::RealReturnType
    rad2deg(const FloatTypeT rVal);

/*---------------------------------------------------------------------*/
/*                             Power 2 Functions                       */

template <class TypeT> inline
bool osgispower2(TypeT rVal);


template <class TypeT> inline
TypeT osgnextpower2(TypeT rVal);


/*---------------------------------------------------------------------*/
/*                   Ccompile Time Functions                           */

/*---------------------------------------------------------------------*/
/*! \defgroup GrpCMax compile time max
    \ingroup GrpBaseBaseCmpTimeFn
 */

/*! \ingroup GrpBaseBaseCmpTimeFn
    \ingroup GrpCMax
    \hideinhierarchy
 */

template <Int32 uiValue1, Int32 uiValue2>
struct OSG_BASE_DLLMAPPING osgStaticMax
{
    enum _iMax { iMax = uiValue1 < uiValue2 ? uiValue2 : uiValue1 };
};


#if defined(__sgi) || defined(__linux) || defined(__sun) || defined(darwin) ||\
    defined(__hpux)

/*---------------------------------------------------------------------*/
/*! \defgroup GrpCIFTBased compile time if, type based
    \ingroup GrpBaseBaseCmpTimeFn
 */

/*! \ingroup GrpBaseBaseCmpTimeFn
    \ingroup GrpCIFTBased
    \hideinhierarchy
 */

struct TrueType  {};

/*! \ingroup GrpBaseBaseCmpTimeFn
    \ingroup GrpCIFTBased
    \hideinhierarchy
 */

struct FalseType {};

/*! Compile time if, true case, type based
    \ingroup GrpBaseBaseCmpTimeFn
    \ingroup GrpCIFTBased
    \hideinhierarchy
 */

template<class IConditionV, class IThenT, class IElseT>
struct osgTypeIF
{
    typedef IThenT _IRet;
    typedef IElseT _IDummyRef;
};

/*! Compile time if, false case, type based
    \ingroup GrpBaseBaseCmpTimeFn
    \ingroup GrpCIFTBased
    \hideinhierarchy
 */

template<class IThenT, class IElseT>
struct osgTypeIF<FalseType, IThenT, IElseT>
{
    typedef IElseT _IRet;
    typedef IThenT _IDummyRef;
};

/*---------------------------------------------------------------------*/
/*! \defgroup GrpCIFBBased compile time if, bool based
    \ingroup GrpBaseBaseCmpTimeFn
 */

/*! Compile time if, true case, bool based
    \ingroup GrpBaseBaseCmpTimeFn
    \ingroup GrpCIFBBased
    \hideinhierarchy
 */

template<bool IConditionV, class IThenT, class IElseT>
struct osgIF
{
    typedef IThenT _IRet;
    typedef IElseT _IDummyRef;
};

/*! Compile time if, false case, bool based
    \ingroup GrpBaseBaseCmpTimeFn
    \ingroup GrpCIFBBased
    \hideinhierarchy
 */

template<class IThenT, class IElseT>
struct osgIF<false, IThenT, IElseT>
{
    typedef IElseT _IRet;
    typedef IThenT _IDummyRef;
};

/*---------------------------------------------------------------------*/

#else

/*---------------------------------------------------------------------*/
/*! \defgroup GrpCIFBBased compile time if, bool based
    \ingroup GrpBaseBaseCmpTimeFn
 */

/*! \ingroup GrpBaseBaseCmpTimeFn
    \ingroup GrpCIFBBased
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

/*! \ingroup GrpBaseBaseCmpTimeFn
    \ingroup GrpCIFBBased
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

/*! Compile time if, bool based
    \ingroup GrpBaseBaseCmpTimeFn
    \ingroup GrpCIFBBased
 */

template<bool IConditionV, class IThenT, class IElseT>
struct osgIF
{
    typedef typename osgIFGen<IConditionV>::osgIFSwitch<IThenT, 
                                                        IElseT>::_IRet _IRet;
};

#endif

/*---------------------------------------------------------------------*/
/*                   Case String Runtime Functions                     */

inline
void stringDup(const Char8 *szInput, Char8 *&szOutput);

inline
Int32 stringncmp(const Char8 *string1, const Char8 *string2, size_t count);

inline
Int32 stringlen(const Char8 *string1);


inline
Int32 stringcmp(const Char8 *string1, const Char8 *string2);

inline
Int32 stringcasecmp(const Char8 *string1,
                    const Char8 *string2);

/*! String less than compare functor used for a STL weak ordering
    \ingroup GrpBaseSTLHelpers
    \ingroup GrpBaseBaseStringFn
    \hideinhierarchy
 */

struct LTString
{
    bool operator()(const Char8 *s1, const Char8 *s2) const
    {
        return ::strcmp(s1, s2) < 0;
    }
};

/*! String equal compare functor
    \ingroup GrpBaseSTLHelpers
    \ingroup GrpBaseBaseStringFn
    \hideinhierarchy
 */

struct EQString
{
    bool operator()(const Char8 *s1, const Char8 *s2) const
    {
        return ::strcmp(s1, s2) == 0;
    }
};

struct HashCmpString : 
    public OSG_STDEXTENSION_NAMESPACE::hash_compare<const Char8 *, LTString>
{
    typedef       std::hash_compare<const Char8 *, LTString>   Inherited;
    typedef const Char8                                      *_Kty;

    HashCmpString(void) : Inherited() 
    {
    }

    size_t operator()(const _Kty& _Keyval) const
	{
        return OSG_STDEXTENSION_NAMESPACE::hash_value<const Char8 *>(_Keyval);
    }

    bool operator()(const _Kty& _Keyval1, const _Kty& _Keyval2) const
    {
        return Inherited::operator()(_Keyval1, _Keyval2);
    }
};

// String Tokenizer

struct OSG_BASE_DLLMAPPING string_token_iterator :
#if defined(__GNUC__) && __GNUC__ < 3
    public std::input_iterator<std::string, std::ptrdiff_t>
#else
    public std::iterator<std::input_iterator_tag, std::string>
#endif
{
  public:
    string_token_iterator();

    string_token_iterator(const std::string & str_,
                          const char        * separator_ = " ");

    string_token_iterator(const string_token_iterator & rhs);

    string_token_iterator & operator++();

    string_token_iterator operator++(int);

    std::string operator*() const;

    bool operator==(const string_token_iterator & rhs) const;

    bool operator!=(const string_token_iterator & rhs) const;

  private:

    void find_next(void);

    const char                   * _separator;
    const std::string            * _str;
          std::string::size_type   _start;
          std::string::size_type   _end;
};



/*! Indirector
    \ingroup GrpBaseSTLHelpers
    \ingroup GrpBaseBaseStringFn 
    
    Allows using an indirection field for STL algorithms, e.g. sort.
    
    The idea is to sort an index field instead of the actual data, as the data
    might be large or immovable.
    
    Example:<tt>
    
    std::vector<float> contv;
    std::vector<int>   indv;
    indirector<std::vector<float>, int>  ind(contv);
    
    std::sort(indv.begin(), indv.end(), ind);
    </tt>
 */

template <class ContentT, class IndexT>
class indirector
{
    public:
    
        indirector(ContentT cont);
        
        bool operator()(IndexT a, IndexT b);
       
    private:
    
        ContentT _cont;
};



/*---------------------------------------------------------------------*/
/*                    Miscellaneous Functions                          */

template<class VecPntT> inline
UInt32 getMaxIndexAbs3(const VecPntT &v);

inline
Int32 putenv(Char8 *string);

inline
void osgsleep(UInt32 millisecs);

inline
Real32 osgrand(void);

inline
bool osgIsBigEndian(void);

/*---------------------------------------------------------------------*/
/*                MemoryObject Reference Count Functions               */

template <class T> inline
void setRefP  (T *&pObject, T *&pNewObject);

template <class T> inline
void addRefP  (T *&pObject);

template <class T> inline
void subRefP  (T *&pObject);

template <class T> inline
void clearRefP(T *&pObject);

template <class T> inline
void clearRefPVector (std::vector<T *> &vVector);

template <class T> inline
void clearRefPVectorP(std::vector<T *> *pVector);

/*---------------------------------------------------------------------*/
/*                           Initialization                            */

/*! \ingroup GrpBaseBaseInitExit
 */

enum SystemState
{
    Startup  = 0x01,
    Running  = 0x02,
    Shutdown = 0x03
};

extern OSG_BASE_DLLMAPPING SystemState GlobalSystemState;

/*! init function prototype
   \ingroup GrpBaseBaseInitExit

   order :

       - PreMP
       - MP
       - (Factory [GV])
       - Init
 */

typedef bool (*InitFuncF)(void);

/*! exit function prototype
    \ingroup GrpBaseBaseInitExit
    order :

       - (Factory [GV])
       - SystemExit
       - MP
       - PostMP
 */

typedef bool (*ExitFuncF)(void);


/*! \ingroup GrpBaseBaseInitExit
    \hideinhierarchy
    InitFuncWrapper is a little wrapper class that allows calling an init
    function without an associated class.
 */

struct OSG_BASE_DLLMAPPING InitFuncWrapper
{
    /*---------------------------------------------------------------------*/
    /*! \name                      Constructors                            */
    /*! \{                                                                 */

    InitFuncWrapper(const InitFuncF func);

    /*! \}                                                                 */
};

/*! \ingroup GrpBaseBaseInitExit
    \hideinhierarchy
    StaticInitFuncWrapper is a little wrapper class that allows calling a
    static init function without an associated class.
 */

struct OSG_BASE_DLLMAPPING StaticInitFuncWrapper
{
    /*---------------------------------------------------------------------*/
    /*! \name                      Constructors                            */
    /*! \{                                                                 */

    StaticInitFuncWrapper(const InitFuncF func);

    /*! \}                                                                 */
};


OSG_BASE_DLLMAPPING
void addInitFunction      (InitFuncF initFunc);

OSG_BASE_DLLMAPPING
void addSystemExitFunction(ExitFuncF exitFunc);

OSG_BASE_DLLMAPPING
void addPreMPInitFunction (InitFuncF initFunc);

OSG_BASE_DLLMAPPING
void addPostMPExitFunction(ExitFuncF exitFunc);


OSG_BASE_DLLMAPPING
bool osgInit(Int32 argc, Char8 **argv);

OSG_BASE_DLLMAPPING
bool osgExit(void);

OSG_END_NAMESPACE

#include "OSGBaseFunctions.inl"

#define OSGBASEFUNCTIONS_HEADER_CVSID "@(#)$Id: $"

#endif /* OSGBASEFUNCTIONS_H */
