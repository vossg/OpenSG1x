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

#ifndef _OSGCONFIG_H_
#define _OSGCONFIG_H_
#ifdef __sgi
#pragma once
#endif

#if defined(__sgi)
#include <standards.h>
#include <sys/endian.h>
#elif defined(__hpux)
#include <arpa/nameser.h>
#elif defined(darwin)
#include <machine/endian.h>
#elif defined(__linux)
#include <endian.h>
#elif defined(WIN32) // HACK until I find a better solution
#define LITTLE_ENDIAN 1234
#define BIG_ENDIAN 4321
#define BYTE_ORDER LITTLE_ENDIAN
#else
#error Endian determination : could not guess your plattform
#endif

/** \namespace osg 
    \brief OpenSG namespace    
 */

/** \defgroup BaseLib OpenSG Base Library
    OpenSG Base Library
*/

/*! \defgroup BaseConstants OpenSG Base Library - Constants
    \ingroup BaseLib
    OpenSG Base Library - Constants
*/

/*! \defgroup BaseColors OpenSG Base Library - Colors
    \ingroup BaseLib
    OpenSG Base Library - Colors
*/

/*! \defgroup BaseDefines OpenSG Base Library - Defines
    \ingroup BaseLib
    OpenSG Base Library - Defines
*/

/*! \defgroup BaseFunctions OpenSG Base Library - Functions
    \ingroup BaseLib
    OpenSG Base Library - Functions
*/

/*! \defgroup BaseMathFunctions OpenSG Base Library - Math Functions
    \ingroup BaseLib
    OpenSG Base Library - Math Functions
*/

/*! \defgroup BaseMathMatrices OpenSG Base Library - Math Matrices
    \ingroup BaseLib
    OpenSG Base Library - Math Matrices
*/

/*! \defgroup BaseMathQuaternions OpenSG Base Library - Math Quaternions
    \ingroup BaseLib
    OpenSG Base Library - Math Quaternions
*/

/*! \defgroup BaseMathVectors OpenSG Base Library - Math Vectors
    \ingroup BaseLib
    OpenSG Base Library - Math Vectors
*/

/*! \defgroup BaseTypes OpenSG Base Library - Types
    \ingroup BaseLib
    OpenSG Base Library - Types, this lib contains all base elements like 
    vectors, matrices.
*/

/*! \defgroup BaseThreading OpenSG Base Library - Threading
    \ingroup BaseLib
    OpenSG Base Library - Threading
*/

/** \file OSGConfig.h
    \brief OpenSG Configuration file.

    This file sets the basic defines describing the available feature of a
    given system. Later on mainly those defines should be used to distinguish
    different implementations and system features. The current set of defines
    depends on the underlying hardware and the used compiler environment.
    On a SGI machine you will get different defines if you are using the 
    gcc compiler suite as you get if you are using the MipsPro suite.
*/

//---------------------------------------------------------------------------
//  Defines
//---------------------------------------------------------------------------

/* name SGI MipsPro Compiler Defines (NOT gcc) */ 
# if defined(__sgi) && !defined(__GNUC__)

#   if !defined(_BOOL)
#   endif  /* _BOOL */

#   if defined(_MIPS_SIM) && _MIPS_SIM == _ABIO32
#   endif  /* _MIPS_SIM */

#   if defined(_WCHAR_T_IS_KEYWORD)
#   endif  /* _WCHAR_T_IS_KEYWORD */

#   if !defined(_TYPENAME_IS_KEYWORD)
#   endif  /* _TYPENAME_IS_KEYWORD */

#   ifdef _PARTIAL_SPECIALIZATION_OF_CLASS_TEMPLATES
#   endif  /* _PARTIAL_SPECIALIZATION_OF_CLASS_TEMPLATES */

#   if (_COMPILER_VERSION >= 730) && defined(_MIPS_SIM) && _MIPS_SIM != _ABIO32
#   endif /* (_COMPILER_VERSION >= 730) && defined(_MIPS_SIM) */

#   ifdef _MEMBER_TEMPLATES
#   endif  /* _MEMBER_TEMPLATES */

#   if defined(_MEMBER_TEMPLATE_KEYWORD)
#   endif  /* _MEMBER_TEMPLATE_KEYWORD */

#   if defined(_STANDARD_C_PLUS_PLUS)
#   endif  /* _STANDARD_C_PLUS_PLUS */

#   if (_COMPILER_VERSION >= 730) && defined(_MIPS_SIM) && _MIPS_SIM != _ABIO32
#   endif  /* _COMPILER_VERSION >= 730 */

#   if defined(_MIPS_SIM) && _MIPS_SIM == _ABIO32
#   endif  /* _MIPS_SIM == _ABIO32 */

#   if !defined(_EXPLICIT_IS_KEYWORD)
#   endif  /* _EXPLICIT_IS_KEYWORD */

#   ifdef __EXCEPTIONS
#   endif  /* __EXCEPTIONS */

#   if (_COMPILER_VERSION >= 721) && defined(_NAMESPACES)
        /*! \brief compiler supports namespaces
         *  \ingroup BaseDefines
         */

#       define OSG_HAS_NAMESPACE

        /*! \brief compiler supports std namespace
         *  \ingroup BaseDefines
         */

#       define OSG_HAS_STD_NAMESPACE

#   endif  /* _COMPILER_VERSION >= 721 */

#   if (_COMPILER_VERSION < 721)
#   endif /*  */

#   if _COMPILER_VERSION < 730 || !defined(_STANDARD_C_PLUS_PLUS) || \
      !defined(_NAMESPACES)
#   endif  /*  */

#   if !defined(_NOTHREADS) && !defined(__STL_PTHREADS)
#   endif  /*  */
#   if defined(_LONGLONG) && defined(_SGIAPI) && _SGIAPI
#   endif  /*  */

#   if _COMPILER_VERSION >= 730
        /*! \brief compiler supports namespaces
         *  \ingroup BaseDefines
         */

#       define OSG_HAS_NAMESPACE

        /*! \brief compiler supports the use of template types for 
         *  return values only
         *  \ingroup BaseDefines
         */

#       define OSG_HAS_TEMPLATE_RETURNVALUES

        /*! \brief compiler supports the use of template types for 
         *  return values only on instance functions
         *  \ingroup BaseDefines
         */

#       define OSG_HAS_MEMBER_TEMPLATE_RETURNVALUES

#       if defined(_STANDARD_C_PLUS_PLUS)

            /*! \brief streams in std namespace
             *  \ingroup BaseDefines
             */

#           define OSG_STREAM_IN_STD_NAMESPACE

#       endif  /* _STANDARD_C_PLUS_PLUS */

        /*! \brief stream->rdbuf get the new buffer as a parameter
         *  \ingroup BaseDefines
         */

#       define OSG_STREAM_RDBUF_HAS_PARAM

        /*! \brief stream->isopen is available
         *  \ingroup BaseDefines
         */

#       define OSG_STREAM_HAS_ISOPEN

        /*! \brief vsnprintf is available
         *  \ingroup BaseDefines
         */

#       define OSG_HAS_VSNPRINTF

        /*! \brief nilbuffer is defined in the stdlib
         *  \ingroup BaseDefines
         */

#       define OSG_HAS_NILBUF

#   endif  /* _COMPILER_VERSION >= 730 */

    /*! \brief Use SGI internal types to define OpenSG base types
     *  \ingroup BaseDefines
     */

#   define OSG_SGI_TYPES

    /*! \brief atan2f function available
     *  \ingroup BaseDefines
     */

#   define OSG_HAS_ATANF2

    /*! \brief General float math
     *  \ingroup BaseDefines
     */

#   define OSG_HAS_FLOATMATH

    /*! \brief SGI's stl implementation is available
     *  \ingroup BaseDefines
     */

#   define OSG_SGI_STL

// Use pthreads
//# define OSG_USE_PTHREADS

    /*! \brief Use sproc
     *  \ingroup BaseDefines
     */

//#   define OSG_USE_SPROC

    /*! \brief Use GLX 
     *  \ingroup BaseDefines
     */

#   define OSG_USE_GLX

    /*! \brief LongLong constants have LL suffix
     *  \ingroup BaseDefines
     */

# define OSG_LONGLONG_HAS_LL

# define OSG_THROW_NOTHING() THROW_NOTHING()

# define OSG_SGI_CC

# endif


/* name SCO UDK 7 compiler (UnixWare 7x, OSR 5, UnixWare 2x) */ 
# if defined(__USLC__)
#     if defined(_REENTRANT)
#     endif
# endif


/* name Gnu compiler */ 
# ifdef __GNUC__
#   if __GNUC__ == 2 && __GNUC_MINOR__ <= 7
#   endif
#   if __GNUC__ < 2 
#   endif
#   if __GNUC__ == 2 && __GNUC_MINOR__ >= 8
#     if __GNUC_MINOR__ >= 9
#     endif
#   endif
#   ifdef __EXCEPTIONS
#   endif
# ifndef __sun
// streams in std namespace
# define OSG_STREAM_IN_STD_NAMESPACE
# endif

# if __GNUC__ >= 3 
# define OSG_HASH_MAP_AS_EXT
# define OSG_SGI_STL
namespace __gnu_cxx {} using namespace __gnu_cxx;
# define OSG_HAS_SSTREAM
# endif

// compiler supports namespaces
# define OSG_HAS_NAMESPACE
// Use pthreads
# define OSG_USE_PTHREADS
// compiler supports the use of template types for return values only
# define  OSG_HAS_MEMBER_TEMPLATE_RETURNVALUES
         //# define  OSG_HAS_MEMBER_TEMPLATE_RETURNVALUES
// # define OSG_HAS_TEMPLATE_RETURNVALUES
// stream->rdbuf get the new buffer as a parameter
# define OSG_STREAM_HAS_ISOPEN
# define OSG_HAS_VSNPRINTF
# define OSG_HAS_NILBUF
# define OSG_STREAM_RDBUF_HAS_PARAM
# define OSG_NEED_EXPLICIT_INST_FOR_STATIC
# define OSG_LONGLONG_HAS_LL
# define OSG_HAS_STD_NAMESPACE
# endif


#if defined __linux
// Use gcc internal types to define OpenSG base types
# define OSG_LINUX_TYPES
// Use GLX 
# define OSG_USE_GLX

# ifdef __GNUC__
#  if __GNUC__ >= 3 
#      define OSG_THROW_NOTHING() throw()
#  else
#      define OSG_THROW_NOTHING() 
#  endif
#else
# define OSG_THROW_NOTHING() 
#endif

// atan2f function available
# define OSG_HAS_ATANF2

// general float math
# define OSG_HAS_FLOATMATH
#endif

#if defined darwin
// Use gcc internal types to define OpenSG base types
# define OSG_LINUX_TYPES
# define OSG_NO_CONCEPT_CHECKS 
# if __GNUC__ >= 3
# define OSG_THROW_NOTHING() throw()
# define OSG_HAS_SSTREAM
#else
# define OSG_THROW_NOTHING()
#endif
# define SIZE_T_NEQ_UINT32
# define OSG_NOGLSUBDIR
# define OSG_NOGLUTSUBDIR
# define OSG_NO_FABSF
# define OSG_DLSYM_NEEDS_UNDERSCORE
#endif


#if defined __sun
# define OSG_SUNOS_TYPES
/* name SunPro Compiler */ 
# if defined(__SUNPRO_CC) 
#   ifdef _REENTRANT
#   endif
# endif
// Use GLX 
# define OSG_USE_GLX
# define OSG_THROW_NOTHING()
#endif

#ifdef __ICL
#ifndef __INTEL_COMPILER
#define __INTEL_COMPILER __ICL
#endif
#endif

/* name Intel compiler, which uses the EDG front end. */ 
# if defined(__INTEL_COMPILER) && !defined(__linux)
#   ifdef _CPPUNWIND
#   endif
#   ifdef _MT
#   endif
# ifndef __ICL
# define __ICL __INTEL_COMPILER
# endif
# if __INTEL_COMPILER_VERSION >= 501
# define OSG_BASE_SPEZ_IMPL_DLLMAPPING 
# else
# define OSG_BASE_SPEZ_HEAD_DLLMAPPING 
# endif

// Use windows internal types to define OpenSG base types
# define OSG_WIN_TYPES
// Use windows threads
# define OSG_USE_WINTHREADS
//# define OSG_WINLOCK_USE_MUTEX
// compiler supports namespaces
# define OSG_HAS_NAMESPACE
// compiler supports std namespace
# define OSG_HAS_STD_NAMESPACE
// streams in std namespace
# define OSG_STREAM_IN_STD_NAMESPACE
// general float math
# define OSG_HAS_FLOATMATH
// Use WGL 
# define OSG_USE_WGL
# define OSG_STREAM_HAS_ISOPEN
//# define OSG_HAS_VSNPRINTF
# define OSG_HAS_NILBUF
# define OSG_STREAM_RDBUF_HAS_PARAM
# define OSG_HAS_TEMPLATE_RETURNVALUES
# define OSG_HAS_MEMBER_TEMPLATE_RETURNVALUES
# define OSG_NEED_EXPLICIT_INST_FOR_STATIC
# define OSG_LONGLONG_HAS_LL
# define OSG_THROW_NOTHING()
# define OSG_WIN32_ICL
# endif


/* name Intel compiler, which uses the EDG front end. */ 
# if defined(__INTEL_COMPILER) && defined(__linux)
#   ifdef _CPPUNWIND
#   endif
#   ifdef _MT
#   endif
# ifndef __ICL
# define __ICL __INTEL_COMPILER
# endif
# if __INTEL_COMPILER_VERSION >= 501
# define OSG_BASE_SPEZ_IMPL_DLLMAPPING 
# else
# define OSG_BASE_SPEZ_HEAD_DLLMAPPING 
# endif

// Use windows internal types to define OpenSG base types
# define OSG_LINUX_TYPES
// Use windows threads
# define OSG_USE_PTHREADS
//# define OSG_WINLOCK_USE_MUTEX
// compiler supports namespaces
# define OSG_HAS_NAMESPACE
// compiler supports std namespace
# define OSG_HAS_STD_NAMESPACE
// streams in std namespace
# define OSG_STREAM_IN_STD_NAMESPACE
// general float math
# define OSG_HAS_FLOATMATH
// Use WGL 
# define OSG_USE_WGL
# define OSG_STREAM_HAS_ISOPEN
//# define OSG_HAS_VSNPRINTF
# define OSG_HAS_NILBUF
# define OSG_STREAM_RDBUF_HAS_PARAM
# define OSG_STREAM_HAS_IOPEN
# define OSG_HAS_TEMPLATE_RETURNVALUES
# define OSG_HAS_MEMBER_TEMPLATE_RETURNVALUES
# define OSG_NEED_EXPLICIT_INST_FOR_STATIC
# define OSG_LONGLONG_HAS_LL
//# define OSG_THROW_NOTHING()
//# define OSG_WIN32_ICL

#define OSG_LINUX_ICC
# endif


/* name Mingw32, EGCS compiler using the Microsoft C runtime */ 
# if defined(__MINGW32__)
// Use gcc internal types to define OpenSG base types
# define OSG_GNU_TYPES
// atan2f function available
# define OSG_HAS_ATANF2
// compiler supports namespaces
# define OSG_HAS_NAMESPACE
// Use pthreads
# define OSG_USE_PTHREADS
// compiler supports std namespace
#define OSG_HAS_STD_NAMESPACE
// general float math
# define OSG_HAS_FLOATMATH
// Use WGL 
# define OSG_USE_WGL
# define OSG_STREAM_HAS_ISOPEN
//# define OSG_HAS_VSNPRINTF
# define OSG_HAS_NILBUF
# define OSG_STREAM_RDBUF_HAS_PARAM
# endif


/* name Microsoft Visual C++ compiler. */ 
# if defined(_MSC_VER) && !defined(__ICL)
#   if _MSC_VER > 1000
#   endif
#   if _MSC_VER < 1100  /* 1000 is version 4.0, 1100 is 5.0, 1200 is 6.0. */
#   endif
#   if _MSC_VER >= 1200
#   endif
#   ifdef _CPPUNWIND
#   endif
#   ifdef _MT
#   endif

# define OSG_SPEZ_IMPL_DLLMAPPING 
// Use windows internal types to define OpenSG base types
# define OSG_WIN_TYPES
// compiler supports namespaces
# define OSG_HAS_NAMESPACE
// Use windows threads
# define OSG_USE_WINTHREADS
// compiler supports std namespace
# define OSG_HAS_STD_NAMESPACE
// streams in std namespace
# define OSG_STREAM_IN_STD_NAMESPACE
// general float math
# define OSG_HAS_FLOATMATH

# define OSG_STREAM_HAS_ISOPEN
//# define OSG_HAS_VSNPRINTF
# define OSG_HAS_NILBUF
# define OSG_STREAM_RDBUF_HAS_PARAM

# define OSG_MICROSOFT_COMPILER_ALERT
# define OSG_MICROSOFT_COMPILER_HACKS
// Use WGL 
# define OSG_USE_WGL

//# define OSG_HAS_TEMPLATE_RETURNVALUES

# define OSG_NEED_EXPLICIT_INST_FOR_STATIC

# define OSG_THROW_NOTHING()
# endif


/* name Borland Compiler */ 
# if defined(__BORLANDC__)
#   ifdef _CPPUNWIND
#   endif
#   ifdef __MT__
#   endif
// Use windows internal types to define OpenSG base types
# define OSG_WIN_TYPES
// compiler supports namespaces
# define OSG_HAS_NAMESPACE
// Use windows threads
# define OSG_USE_WINTHREADS
// general float math
//# define OSG_HAS_FLOATMATH
# define BCC
// Use WGL 
# define OSG_STREAM_RDBUF_HAS_PARAM
# define OSG_HAS_NILBUF
# define OSG_USE_WGL

# define OSG_THROW_NOTHING()
# endif  /*  */


#if defined(OSG_HAS_STD_NAMESPACE)
# define OSG_USING_STD_NAMESPACE namespace std {} using namespace std;
# define OSG_STD std

OSG_USING_STD_NAMESPACE

#endif

#if defined(OSG_HAS_NAMESPACE)

/*! @name Namespace Defines
 */

/*@{*/

/** \brief Begin the osg namespace
 *  \ingroup BaseDefines
 */

# define OSG_BEGIN_NAMESPACE namespace osg { 

/** \brief End the osg namespace
 *  \ingroup BaseDefines
 */

# define OSG_END_NAMESPACE }

/** \brief osg namespace, use to reference a object within the namespace, like
 *  \ingroup BaseDefines
    OSG::OSGUInt32.
*/

# define OSG osg

/** \brief Use the osg namespace throughout the following code.
 *  \ingroup BaseDefines
 */

# define OSG_USING_NAMESPACE namespace osg {} using namespace osg;

/*@}*/

# else /* OSG_HAS_NAMESPACE */

# define OSG_BEGIN_NAMESPACE 
# define OSG_END_NAMESPACE 
# define OSG 
# define OSG_USING_OSG_NAMESPACE

#endif /*  */

#if defined(OSG_DLSYM_NEEDS_UNDERSCORE)
#define OSG_DLSYM_UNDERSCORE "_"
#else
#define OSG_DLSYM_UNDERSCORE
#endif

#if defined (OSG_USE_PTHREADS)

#define OSG_ASPECT_USE_PTHREADKEY
//#define OSG_ASPECT_USE_PTHREADSELF
//#define OSG_ASPECT_USE_CUSTOMSELF

#endif /* OSG_USE_PTHREADS */

#ifndef _OSG_HAVE_CONFIGURED_H_
#   if defined (OSG_USE_WINTHREADS)
//#define OSG_ASPECT_USE_LOCALSTORAGE
#   define OSG_ASPECT_USE_DECLSPEC
#   endif
#endif

#define OSG_COMPILETIME_NUM_ASPECTS
//#define OSG_RUNTIME_NUM_ASPECTS
//#define OSG_MTHREADED_FCS

#define OSG_NUM_ASPECTS 2

#ifdef OSG_WIN_TYPES
#ifndef OSG_NO_WINDOWD_H_INCLUDE
#include <windows.h>
#endif
#endif

#ifndef OSG_WIN_TYPES
#define OSG_APIENTRY
#else
#define OSG_APIENTRY APIENTRY
#ifndef _OSG_HAVE_CONFIGURED_H_
//#   define OSG_BOOL_IS_UNSIGNED
#endif
#endif


#ifdef OSG_DEBUG
//#define OSG_DEBUG_TYPED_FCPTR
#define OSG_DEBUG_LOCK_STAT
#endif

#ifdef OSG_DEBUG_ARG
#define OSG_CHECK_ARG(ARG) ARG
#else
#define OSG_CHECK_ARG(ARG)
#endif

#ifdef OSG_DEBUG
#define OSG_DEBUG_CHECK_ARG(ARG) ARG
#else
#define OSG_DEBUG_CHECK_ARG(ARG)
#endif

#ifndef WIN32
#define OSG_DLLEXPORT_DECL1(CLASSNAME, T1, DLLMAPPING)

#define OSG_DLLEXPORT_DECL2(CLASSNAME, T1, T2, DLLMAPPING)
#else
#ifdef OSG_WIN32_ICL
#define OSG_EXPORT_TYPE_DECL1(CLASSNAME, T1, DLLMAPPING)                     \
    extern template DLLMAPPING                                               \
        const FieldType  CLASSNAME<T1>::_fieldType;
#define OSG_EXPORT_TYPE_DECL2(CLASSNAME, T1, T2, DLLMAPPING)                 \
    extern template DLLMAPPING                                               \
        const FieldType  CLASSNAME<T1, T2>::_fieldType;

#define OSG_EXPORT_GETTYPE_DECL1(CLASSNAME, T1, DLLMAPPING)                  \
    extern template DLLMAPPING                                               \
        const FieldType &CLASSNAME<T1>::getType    (void) const;
#define OSG_EXPORT_GETTYPE_DECL2(CLASSNAME, T1, T2, DLLMAPPING)              \
    extern template DLLMAPPING                                               \
        const FieldType &CLASSNAME<T1, T2>::getType(void) const;

#define OSG_EXPORT_GETCLASSTYPE_DECL1(CLASSNAME, T1, DLLMAPPING)             \
    extern template DLLMAPPING                                               \
        const FieldType &CLASSNAME<T1>::getClassType(void);
#define OSG_EXPORT_GETCLASSTYPE_DECL2(CLASSNAME, T1, T2, DLLMAPPING)         \
    extern template DLLMAPPING                                               \
        const FieldType &CLASSNAME<T1, T2>::getClassType(void);

#define OSG_DLLEXPORT_DECL1(CLASSNAME, T1, DLLMAPPING)                       \
    OSG_EXPORT_GETTYPE_DECL1     (CLASSNAME, T1, DLLMAPPING)                 \
    OSG_EXPORT_TYPE_DECL1        (CLASSNAME, T1, DLLMAPPING)                 \
    OSG_EXPORT_GETCLASSTYPE_DECL1(CLASSNAME, T1, DLLMAPPING)

#define OSG_DLLEXPORT_DECL2(CLASSNAME, T1, T2, DLLMAPPING)                   \
    OSG_EXPORT_TYPE_DECL2        (CLASSNAME, T1, T2, DLLMAPPING)             \
    OSG_EXPORT_GETTYPE_DECL2     (CLASSNAME, T1, T2, DLLMAPPING)             \
    OSG_EXPORT_GETCLASSTYPE_DECL2(CLASSNAME, T1, T2, DLLMAPPING)
#else
#define OSG_DLLEXPORT_DECL1(CLASSNAME, T1, DLLMAPPING)                       \
    extern template class DLLMAPPING CLASSNAME<T1>;

#define OSG_DLLEXPORT_DECL2(CLASSNAME, T1, T2, DLLMAPPING)                   \
    extern template class DLLMAPPING CLASSNAME<T1, T2>;
#endif
#endif

#ifndef WIN32
#define OSG_ABSTR_FC_DLLEXPORT_DECL(CLASSNAME, T1, DLLMAPPING)

#define OSG_FC_DLLEXPORT_DECL(CLASSNAME, T1, DLLMAPPING)
#else
#ifdef OSG_WIN32_ICL
#define OSG_FC_EXPORT_TYPE_DECL(CLASSNAME, T1, DLLMAPPING)                   \
    extern template                                                          \
        FieldContainerType CLASSNAME<T1>::_type;

#define OSG_FC_EXPORT_GETTYPE_DECL(CLASSNAME, T1, DLLMAPPING)                \
    extern template DLLMAPPING                                               \
              FieldContainerType &CLASSNAME<T1>::getType(void);              \
    extern template DLLMAPPING                                               \
        const FieldContainerType &CLASSNAME<T1>::getType(void) const;        \
    extern template DLLMAPPING                                               \
              FieldContainerType &CLASSNAME<T1>::getClassType(void);         \
    extern template DLLMAPPING                                               \
              UInt32              CLASSNAME<T1>::getClassTypeId(void);

#define OSG_FC_DLLEXPORT_DECL(CLASSNAME, T1, DLLMAPPING)                     \
    OSG_FC_EXPORT_TYPE_DECL   (CLASSNAME, T1, DLLMAPPING)                    \
    OSG_FC_EXPORT_GETTYPE_DECL(CLASSNAME, T1, DLLMAPPING)     

#define OSG_ABSTR_FC_DLLEXPORT_DECL(CLASSNAME, T1, DLLMAPPING)               \
    OSG_FC_EXPORT_TYPE_DECL   (CLASSNAME, T1, DLLMAPPING)                    \
    OSG_FC_EXPORT_GETTYPE_DECL(CLASSNAME, T1, DLLMAPPING)     
#else
#define OSG_FC_EXPORT_TYPE_DECL(CLASSNAME, T1, DLLMAPPING)                   \

#define OSG_FC_EXPORT_GETTYPE_DECL(CLASSNAME, T1, DLLMAPPING)                \
    extern template DLLMAPPING                                               \
              FieldContainerType &CLASSNAME<T1>::getType(void);              \
    extern template DLLMAPPING                                               \
        const FieldContainerType &CLASSNAME<T1>::getType(void) const;        \
    extern template DLLMAPPING                                               \
              FieldContainerType &CLASSNAME<T1>::getClassType(void);         \
    extern template DLLMAPPING                                               \
              UInt32              CLASSNAME<T1>::getClassTypeId(void);

#define OSG_FC_DLLEXPORT_DECL(CLASSNAME, T1, DLLMAPPING)                     \
    extern template class DLLMAPPING CLASSNAME<T1>;

#define OSG_ABSTR_FC_DLLEXPORT_DECL(CLASSNAME, T1, DLLMAPPING)               \
    extern template class DLLMAPPING CLASSNAME<T1>;
#endif
#endif

#ifdef WIN32
#ifdef OSG_WIN32_ICL
#define  OSG_FC_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING)         \
template<>                                                       \
FieldContainerType CLASSNAME< T1 >::_type =                      \
    FieldContainerType(                                          \
        T1::getTypeName(),                                       \
        T1::getParentTypeName(),                                 \
        T1::getGroupName(),                                      \
        (PrototypeCreateF) &CLASSNAME< T1 >::createEmpty,        \
        T1::getInitMethod(),                                     \
        T1::getDesc(),                                           \
        sizeof(FieldDescription *));                             \
                                                                 \
template DLLMAPPING                                              \
FieldContainerType &CLASSNAME< T1 >::getClassType(void);         \
                                                                 \
template DLLMAPPING                                              \
UInt32 CLASSNAME< T1 >::getClassTypeId(void);                    \
                                                                 \
template DLLMAPPING                                              \
FieldContainerType &CLASSNAME< T1 >::getType(void);              \
template DLLMAPPING                                              \
const FieldContainerType &CLASSNAME< T1 >::getType(void) const


#define  OSG_ABSTR_FC_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING) \
template<>                                                     \
FieldContainerType CLASSNAME< T1 >::_type =                    \
    FieldContainerType(                                        \
        T1::getTypeName(),                                     \
        T1::getParentTypeName(),                               \
        T1::getGroupName(),                                    \
        (PrototypeCreateF) &CLASSNAME< T1 >::createEmpty,      \
        T1::getInitMethod(),                                   \
        T1::getDesc(),                                         \
        sizeof(FieldDescription *));                           \
                                                               \
template DLLMAPPING                                            \
FieldContainerType &CLASSNAME< T1 >::getClassType(void);       \
                                                               \
template DLLMAPPING                                            \
UInt32 CLASSNAME< T1 >::getClassTypeId(void);                  \
                                                               \
template DLLMAPPING                                            \
FieldContainerType &CLASSNAME< T1 >::getType(void);            \
template DLLMAPPING                                            \
const FieldContainerType &CLASSNAME< T1 >::getType(void) const

#define  OSG_DYNFIELD_FC_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING) \
template<>                                                     \
FieldContainerType CLASSNAME< T1 >::_type =                    \
    FieldContainerType(                                        \
        T1::getTypeName(),                                     \
        T1::getParentTypeName(),                               \
        T1::getGroupName(),                                    \
        (PrototypeCreateF) &CLASSNAME< T1 >::createEmpty,      \
        T1::getInitMethod(),                                   \
        NULL,                                                  \
        0,                                                     \
        true);                                                 \
                                                               \
template DLLMAPPING                                            \
FieldContainerType &CLASSNAME< T1 >::getClassType(void);       \
                                                               \
template DLLMAPPING                                            \
UInt32 CLASSNAME< T1 >::getClassTypeId(void);                  \
                                                               \
template DLLMAPPING                                            \
FieldContainerType &CLASSNAME< T1 >::getType(void);            \
template DLLMAPPING                                            \
const FieldContainerType &CLASSNAME< T1 >::getType(void) const
#else
#define  OSG_FC_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING)         \
template<>                                                       \
FieldContainerType CLASSNAME< T1 >::_type =                      \
    FieldContainerType(                                          \
        T1::getTypeName(),                                       \
        T1::getParentTypeName(),                                 \
        T1::getGroupName(),                                      \
        (PrototypeCreateF) &CLASSNAME< T1 >::createEmpty,        \
        T1::getInitMethod(),                                     \
        T1::getDesc(),                                           \
        sizeof(FieldDescription *));                             \
template class DLLMAPPING CLASSNAME< T1 >

#define  OSG_DYNFIELD_FC_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING) \
template<>                                                     \
FieldContainerType CLASSNAME< T1 >::_type =                    \
    FieldContainerType(                                        \
        T1::getTypeName(),                                     \
        T1::getParentTypeName(),                               \
        T1::getGroupName(),                                    \
        (PrototypeCreateF) &CLASSNAME< T1 >::createEmpty,      \
        T1::getInitMethod(),                                   \
        NULL,                                                  \
        0,                                                     \
        true);                                                 \
template class DLLMAPPING CLASSNAME< T1 >
#endif
#else
#define  OSG_FC_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING)         \
template<>                                                       \
FieldContainerType CLASSNAME< T1 >::_type =                      \
    FieldContainerType(                                          \
        T1::getTypeName(),                                       \
        T1::getParentTypeName(),                                 \
        T1::getGroupName(),                                      \
        (PrototypeCreateF) &CLASSNAME< T1 >::createEmpty,        \
        T1::getInitMethod(),                                     \
        T1::getDesc(),                                           \
        sizeof(FieldDescription *))

#define  OSG_ABSTR_FC_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING) \
template<>                                                     \
FieldContainerType CLASSNAME< T1 >::_type =                    \
    FieldContainerType(                                        \
        T1::getTypeName(),                                     \
        T1::getParentTypeName(),                               \
        T1::getGroupName(),                                    \
        (PrototypeCreateF) &CLASSNAME< T1 >::createEmpty,      \
        T1::getInitMethod(),                                   \
        T1::getDesc(),                                         \
        sizeof(FieldDescription *))

#define  OSG_DYNFIELD_FC_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING) \
template<>                                                     \
FieldContainerType CLASSNAME< T1 >::_type =                    \
    FieldContainerType(                                        \
        T1::getTypeName(),                                     \
        T1::getParentTypeName(),                               \
        T1::getGroupName(),                                    \
        (PrototypeCreateF) &CLASSNAME< T1 >::createEmpty,      \
        T1::getInitMethod(),                                   \
        NULL,                                                  \
        0,                                                     \
        true)
#endif

#ifdef WIN32
#ifdef OSG_WIN32_ICL
#define  OSG_ABSTR_GEOPROP_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING) \
template <>                                                         \
FieldContainerType AbstractGeoProperty< T1 >::_type(                \
        T1                ::getTypeName  (),                        \
        LocalInheritedDesc::getTypeName  (),                        \
        T1                ::getGroupName (),                        \
        NULL,                                                       \
        T1                ::getInitMethod(),                        \
        NULL,                                                       \
        0);                                                         \
                                                                    \
template DLLMAPPING                                                 \
FieldContainerType &AbstractGeoProperty< T1 >::getClassType(void);  \
                                                                    \
template DLLMAPPING                                                 \
UInt32 AbstractGeoProperty< T1 >::getClassTypeId(void);             \
                                                                    \
template DLLMAPPING                                                 \
FieldContainerType &AbstractGeoProperty< T1 >::getType(void);       \
template DLLMAPPING                                                 \
const FieldContainerType &AbstractGeoProperty< T1 >::getType(void) const


#define  OSG_GEOPROP_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING) \
template <>                                                   \
FieldContainerType GeoProperty< T1 >::_type(                  \
    T1                ::getTypeName(),                        \
    LocalInheritedDesc::getTypeName(),                        \
    T1                ::getGroupName(),                       \
    (PrototypeCreateF) &GeoProperty< T1 >::createEmpty,       \
    T1                ::getInitMethod(),                      \
    T1                ::getDesc(),                            \
    sizeof(FieldDescription *));                              \
                                                              \
template DLLMAPPING                                           \
FieldContainerType &GeoProperty< T1 >::getClassType(void);    \
                                                              \
template DLLMAPPING                                           \
UInt32 GeoProperty< T1 >::getClassTypeId(void);               \
                                                              \
template DLLMAPPING                                           \
FieldContainerType &GeoProperty< T1 >::getType(void);         \
template DLLMAPPING                                           \
const FieldContainerType &GeoProperty< T1 >::getType(void) const
#else
#define  OSG_ABSTR_GEOPROP_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING) \
template <>                                                         \
FieldContainerType AbstractGeoProperty< T1 >::_type(                \
        T1                ::getTypeName  (),                        \
        LocalInheritedDesc::getTypeName  (),                        \
        T1                ::getGroupName (),                        \
        NULL,                                                       \
        T1                ::getInitMethod(),                        \
        NULL,                                                       \
        0);                                                         \
                                                                    \
template class DLLMAPPING AbstractGeoProperty< T1 >

#define  OSG_GEOPROP_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING) \
template <>                                                   \
FieldContainerType GeoProperty< T1 >::_type(                  \
    T1                ::getTypeName(),                        \
    LocalInheritedDesc::getTypeName(),                        \
    T1                ::getGroupName(),                       \
    (PrototypeCreateF) &GeoProperty< T1 >::createEmpty,       \
    T1                ::getInitMethod(),                      \
    T1                ::getDesc(),                            \
    sizeof(FieldDescription *));                              \
                                                              \
template class DLLMAPPING GeoProperty< T1 >
#endif
#else
#define  OSG_ABSTR_GEOPROP_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING) \
template <>                                                         \
FieldContainerType AbstractGeoProperty< T1 >::_type(                \
        T1                ::getTypeName  (),                        \
        LocalInheritedDesc::getTypeName  (),                        \
        T1                ::getGroupName (),                        \
        NULL,                                                       \
        T1                ::getInitMethod(),                        \
        NULL,                                                       \
        0)

#define  OSG_GEOPROP_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING) \
template <>                                                   \
FieldContainerType GeoProperty< T1 >::_type(                  \
    T1                ::getTypeName(),                        \
    LocalInheritedDesc::getTypeName(),                        \
    T1                ::getGroupName(),                       \
    (PrototypeCreateF) &GeoProperty< T1 >::createEmpty,       \
    T1                ::getInitMethod(),                      \
    T1                ::getDesc(),                            \
    sizeof(FieldDescription *))
#endif

#define OSG_DLLEXPORT_SFIELD_TYPE_DEF1(T1,     DLLMAPPING) \
template <>                                                \
const FieldType SField< T1, 0 >::_fieldType(               \
    SFieldTraits::getSName(),                              \
    SFieldTraits::getPName (),                             \
    SFieldTraits::getType(),                               \
    SField< T1, 0 >::create,                               \
    FieldType::SINGLE_FIELD)

#define OSG_DLLEXPORT_SFIELD_TYPE_DEF2(T1, T2, DLLMAPPING) \
template <>                                                \
const FieldType SField< T1, T2 >::_fieldType(              \
    SFieldTraits::getSName(),                              \
    SFieldTraits::getPName (),                             \
    SFieldTraits::getType(),                               \
    SField< T1, T2 >::create,                              \
    FieldType::SINGLE_FIELD)

#define OSG_DLLEXPORT_MFIELD_TYPE_DEF1(T1,     DLLMAPPING) \
template <>                                                \
const FieldType MField< T1, 0 >::_fieldType(               \
    MFieldTraits::getMName(),                              \
    MFieldTraits::getPName (),                             \
    MFieldTraits::getType(),                               \
    MField< T1 >::create,                                  \
    FieldType::MULTI_FIELD)

#define OSG_DLLEXPORT_MFIELD_TYPE_DEF2(T1, T2, DLLMAPPING) \
template <>                                                \
const FieldType MField< T1, T2 >::_fieldType(              \
    MFieldTraits::getMName(),                              \
    MFieldTraits::getPName (),                             \
    MFieldTraits::getType(),                               \
    MField< T1, T2 >::create,                              \
    FieldType::MULTI_FIELD)


#if defined(OSG_WIN32_ICL)
#define OSG_DLLEXPORT_SFIELD_GET_TYPE_DEF1(T1,     DLLMAPPING) \
template DLLMAPPING                                            \
const FieldType  SField< T1, 0 >::_fieldType;                  \
template DLLMAPPING                                            \
const FieldType &SField< T1, 0 >::getClassType(void);          \
template DLLMAPPING                                            \
const FieldType &SField< T1, 0 >::getType(void) const

#define OSG_DLLEXPORT_SFIELD_GET_TYPE_DEF2(T1, T2, DLLMAPPING) \
template DLLMAPPING                                            \
const FieldType  SField< T1, T2 >::_fieldType;                 \
template DLLMAPPING                                            \
const FieldType &SField< T1, T2 >::getClassType(void);         \
template DLLMAPPING                                            \
const FieldType &SField< T1, T2 >::getType(void) const

#define OSG_DLLEXPORT_MFIELD_GET_TYPE_DEF1(T1,     DLLMAPPING) \
template DLLMAPPING                                            \
const FieldType  MField< T1, 0 >::_fieldType;                  \
template DLLMAPPING                                            \
const FieldType &MField< T1, 0 >::getClassType(void);          \
template DLLMAPPING                                            \
const FieldType &MField< T1, 0 >::getType(void) const

#define OSG_DLLEXPORT_MFIELD_GET_TYPE_DEF2(T1, T2, DLLMAPPING) \
template DLLMAPPING                                            \
const FieldType  MField< T1, T2 >::_fieldType;                 \
template DLLMAPPING                                            \
const FieldType &MField< T1, T2 >::getClassType(void);         \
template DLLMAPPING                                            \
const FieldType &MField< T1, T2 >::getType(void) const
#else
#define OSG_DLLEXPORT_SFIELD_GET_TYPE_DEF1(T1,     DLLMAPPING) \
template class DLLMAPPING SField< T1 >
#define OSG_DLLEXPORT_MFIELD_GET_TYPE_DEF1(T1,     DLLMAPPING) \
template class DLLMAPPING MField< T1 >                           
#define OSG_DLLEXPORT_SFIELD_GET_TYPE_DEF2(T1, T2, DLLMAPPING) \
template class DLLMAPPING SField< T1, T2 >                          
#define OSG_DLLEXPORT_MFIELD_GET_TYPE_DEF2(T1, T2, DLLMAPPING) \
template class DLLMAPPING MField< T1, T2 >
#endif

#ifdef WIN32
#define OSG_DLLEXPORT_SFIELD_DEF1(T1,     DLLMAPPING)      \
    OSG_DLLEXPORT_SFIELD_GET_TYPE_DEF1(T1,     DLLMAPPING)

#define OSG_DLLEXPORT_SFIELD_DEF2(T1, T2, DLLMAPPING)      \
    OSG_DLLEXPORT_SFIELD_GET_TYPE_DEF2(T1, T2, DLLMAPPING)

#define OSG_DLLEXPORT_MFIELD_DEF1(T1,     DLLMAPPING)      \
    OSG_DLLEXPORT_MFIELD_GET_TYPE_DEF1(T1,     DLLMAPPING) 

#define OSG_DLLEXPORT_MFIELD_DEF2(T1, T2, DLLMAPPING)      \
    OSG_DLLEXPORT_MFIELD_GET_TYPE_DEF2(T1, T2, DLLMAPPING)

#define OSG_ABSTR_GEO_PROP_INL_TMPL_DEF(OSG_CLASS,            \
                                        OSG_TMPL_PARAM,       \
                                        OSG_CLASS_PTR)        \
    OSG_FC_SIZE_FUNCTIONS_INL_TMPL_DEF  (OSG_TMPL_PARAM, OSG_CLASS)

#define OSG_GEO_PROP_INL_TMPL_DEF(OSG_CLASS,                         \
                                  OSG_TMPL_PARAM,                    \
                                  OSG_CLASS_PTR)                     \
    OSG_FC_SIZE_FUNCTIONS_INL_TMPL_DEF  (OSG_TMPL_PARAM, OSG_CLASS)  \
    OSG_FC_CREATE_FUNCTIONS_INL_TMPL_DEF(OSG_TMPL_PARAM,             \
                                         OSG_CLASS,                  \
                                         OSG_CLASS_PTR)

#define OSG_GEO_PROP_TYPE_TMPL_DEF(OSG_CLASS,                         \
                                   OSG_TMPL_PARAM,                    \
                                   OSG_CLASS_PTR)                     \
    OSG_FC_TYPE_FUNCTIONS_INL_TMPL_DEF(OSG_TMPL_PARAM, OSG_CLASS)

#else
#define OSG_DLLEXPORT_SFIELD_DEF1(T1,     DLLMAPPING)      \
    OSG_DLLEXPORT_SFIELD_TYPE_DEF1(T1,     DLLMAPPING)

#define OSG_DLLEXPORT_SFIELD_DEF2(T1, T2, DLLMAPPING)      \
    OSG_DLLEXPORT_SFIELD_TYPE_DEF2(T1, T2, DLLMAPPING)

#define OSG_DLLEXPORT_MFIELD_DEF1(T1,     DLLMAPPING)      \
    OSG_DLLEXPORT_MFIELD_TYPE_DEF1(T1,     DLLMAPPING)

#define OSG_DLLEXPORT_MFIELD_DEF2(T1, T2, DLLMAPPING)      \
    OSG_DLLEXPORT_MFIELD_TYPE_DEF2(T1, T2, DLLMAPPING)


#define OSG_ABSTR_GEO_PROP_INL_TMPL_DEF(OSG_CLASS,            \
                                        OSG_TMPL_PARAM,       \
                                        OSG_CLASS_PTR)

#define OSG_GEO_PROP_INL_TMPL_DEF(OSG_CLASS,                         \
                                  OSG_TMPL_PARAM,                    \
                                  OSG_CLASS_PTR)

#define OSG_GEO_PROP_TYPE_TMPL_DEF(OSG_CLASS,                         \
                                   OSG_TMPL_PARAM,                    \
                                   OSG_CLASS_PTR)
#endif

#ifdef _OSG_HAVE_CONFIGURED_H_
#include <OSGConfigured.h>
#endif

#define OSG_ASSERT(expr) assert(expr)

#define OSG_DBG_MEM
#define OSG_DBG_LCK

#endif /* _OSGCONFIG_H_ */
