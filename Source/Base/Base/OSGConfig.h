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

#ifndef _OSGCONFIG_H_
#define _OSGCONFIG_H_

#ifdef __sgi
#pragma once
#endif

#ifdef __hpux
#include <sys/types.h>
#endif

/*-------------------------------------------------------------------------*/
/*                                Versioning                               */

/*! @name Version Defines
 */

/*!{*/

/*! The printable Version string. Includes the full version with specifiers,
    e.g. "1.3.0pre1"
 */

#define OSG_VERSION_STRING      "1.8.1Alpha"

/*! The numeric full version, with two digits per major/minor/release, e.g.
    010300
 */

#define OSG_VERSION             0x010801

/*! The numeric major version number, e.g. 1
 */

#define OSG_MAJOR_VERSION       1

/*! The numeric minor version number, e.g. 4
 */

#define OSG_MINOR_VERSION       8

/*! The numeric release version number, e.g. 0
 */

#define OSG_RELEASE_VERSION     1


/*!}*/

// Mac Hack

#ifdef __APPLE__
#define darwin
#endif

/*-------------------------------------------------------------------------*/
/*                              endian general                             */

#if defined(__sgi)
#include <standards.h>
#include <sys/endian.h>
// Some systems (notably VRJuggler) screw up the environment, so kludge it
#  ifndef BYTE_ORDER
#    define LITTLE_ENDIAN  _LITTLE_ENDIAN
#    define BIG_ENDIAN     _BIG_ENDIAN
#    define BYTE_ORDER     _BYTE_ORDER
#  endif
#elif defined(__hpux)
#include <arpa/nameser.h>
#include <pthread.h>
#elif defined(__sun)
#include <arpa/nameser_compat.h>
#elif defined(__APPLE__)
#include <machine/endian.h>
#elif defined(__linux)
#include <endian.h>
#ifndef __USE_BSD
# define LITTLE_ENDIAN  __LITTLE_ENDIAN
# define BIG_ENDIAN     __BIG_ENDIAN
# define PDP_ENDIAN     __PDP_ENDIAN
# define BYTE_ORDER     __BYTE_ORDER
#endif
#elif defined(WIN32) // HACK until I find a better solution
#define LITTLE_ENDIAN 1234
#define BIG_ENDIAN 4321
#define BYTE_ORDER LITTLE_ENDIAN
#else
#error Endian determination : could not guess your plattform
#endif


/*-------------------------------------------------------------------------*/
/*                              icc general                                */


#ifdef __ICL
#ifndef __INTEL_COMPILER
#define __INTEL_COMPILER __ICL
#endif
#endif


/*-------------------------------------------------------------------------*/
/*                              gcc general                                */


# ifdef __GNUC__

/*! \brief compiler supports namespaces
 *  \ingroup GrpBaseDefines
 */

# define OSG_HAS_NAMESPACE

/*! \brief compiler supports std namespace
 *  \ingroup GrpBaseDefines
 */

# define OSG_HAS_STD_NAMESPACE

/*! \brief stream->rdbuf get the new buffer as a parameter
 *  \ingroup GrpBaseDefines
 */

# define OSG_STREAM_RDBUF_HAS_PARAM

/*! \brief stream->isopen is available
 *  \ingroup GrpBaseDefines
 */

# define OSG_STREAM_HAS_ISOPEN

/*! \brief vsnprintf is available
 *  \ingroup GrpBaseDefines
 */

# define OSG_HAS_VSNPRINTF

/*! \brief nilbuffer is defined in the stdlib
 *  \ingroup GrpBaseDefines
 */

# define OSG_HAS_NILBUF

/*! \brief LongLong constants have LL suffix
 *  \ingroup GrpBaseDefines
 */

# define OSG_LONGLONG_HAS_LL

# if __GNUC__ >= 3
#    define OSG_HASH_MAP_AS_EXT

     /*! \brief SGI's stl implementation is available
      *  \ingroup GrpBaseDefines
      */

#    define OSG_SGI_STL

#    define OSG_THROW_NOTHING() throw()

#    define OSG_STDEXCEPTION_NAMESPACE    std

#    if __GNUC__ >= 4 || __GNUC_MINOR__ >=1
#        define OSG_STDEXTENSION_NAMESPACE  __gnu_cxx
#        define OSG_HAS_SSTREAM
#    else
#        define OSG_STDEXTENSION_NAMESPACE  std
#    endif

#    define OSG_STL_HAS_HASH_MAP

# else
#     define OSG_THROW_NOTHING()
#     if __GNUC_MINOR__ <= 96
#         define OSG_GCC_NO_IOS_BASE
#     endif
# endif

# endif


/*-------------------------------------------------------------------------*/
/*                              sgi CC                                     */

# if defined(__sgi) && !defined(__GNUC__)

# if _COMPILER_VERSION < 730
# error compiler version < 730 not supported, please upgrade
# endif

/*! \brief compiler supports namespaces
 *  \ingroup GrpBaseDefines
 */

# define OSG_HAS_NAMESPACE

/*! \brief compiler supports std namespace
 *  \ingroup GrpBaseDefines
 */

# define OSG_HAS_STD_NAMESPACE

# if defined(_STANDARD_C_PLUS_PLUS)

# endif  /* _STANDARD_C_PLUS_PLUS */

/*! \brief stream->rdbuf get the new buffer as a parameter
 *  \ingroup GrpBaseDefines
 */

# define OSG_STREAM_RDBUF_HAS_PARAM

/*! \brief stream->isopen is available
 *  \ingroup GrpBaseDefines
 */

# define OSG_STREAM_HAS_ISOPEN

/*! \brief vsnprintf is available
 *  \ingroup GrpBaseDefines
 */

# define OSG_HAS_VSNPRINTF

/*! \brief nilbuffer is defined in the stdlib
 *  \ingroup GrpBaseDefines
 */

# define OSG_HAS_NILBUF

/*! \brief Use SGI internal types to define OpenSG base types
 *  \ingroup GrpBaseDefines
 */

# define OSG_SGI_TYPES

/*! \brief atan2f function available
 *  \ingroup GrpBaseDefines
 */

# define OSG_HAS_ATANF2

/*! \brief General float math
 *  \ingroup GrpBaseDefines
 */

# define OSG_HAS_FLOATMATH

/*! \brief SGI's stl implementation is available
 *  \ingroup GrpBaseDefines
 */

# define OSG_SGI_STL

# define OSG_STL_HAS_HASH_MAP

/*! \brief Use GLX
 *  \ingroup GrpBaseDefines
 */

# define OSG_USE_GLX

/*! \brief LongLong constants have LL suffix
 *  \ingroup GrpBaseDefines
 */

# define OSG_LONGLONG_HAS_LL

# define OSG_THROW_NOTHING() THROW_NOTHING()

# define OSG_SGI_CC

# define OSG_FOUND_OS

# define OSG_STDEXCEPTION_NAMESPACE std

# endif // defined(__sgi) && !defined(__GNUC__)




/*-------------------------------------------------------------------------*/
/*                              Linux gcc                                  */

# if defined(__GNUC__) && defined(__linux)

/*! \brief streams in std namespace
 *  \ingroup GrpBaseDefines
 */

# define OSG_LINUX_TYPES

# define OSG_HAS_ATANF2

# define OSG_HAS_FLOATMATH


/*! \brief Use the math functions from the std:: namespace
 *  \ingroup GrpBaseDefines
    The std:: namespace has a set of overloaded functions for many
    math operations, up to and including long double versions.
 */

# define OSG_USE_STDMATH

# define OSG_USE_GLX

# define OSG_USE_PTHREADS

# define OSG_LINUX_GCC

# define OSG_FOUND_OS

# endif // defined(__GNUC__) && defined(__linux)

/*-------------------------------------------------------------------------*/
/*                              Linux gcc ia64                             */

# if defined(__GNUC__) && defined(__linux) && defined(__ia64)

# define SIZE_T_NEQ_UINT32

# endif // defined(__GNUC__) && defined(__linux) && defined(__ia64)

/*-------------------------------------------------------------------------*/
/*                              Linux icc                                  */

# if defined(__INTEL_COMPILER) && defined(__linux)

# ifndef __ICL
#    define __ICL __INTEL_COMPILER
# endif

# ifndef __INTEL_COMPILER_VERSION
#    define __INTEL_COMPILER_VERSION __INTEL_COMPILER
# endif

# define OSG_HAS_NAMESPACE

# define OSG_HAS_STD_NAMESPACE

# define OSG_STREAM_RDBUF_HAS_PARAM

# define OSG_STREAM_HAS_IOPEN

# define OSG_HAS_NILBUF

# define OSG_LINUX_TYPES

# define OSG_HAS_ATANF2

# define OSG_HAS_FLOATMATH

# define OSG_USE_STDMATH

# define OSG_USE_GLX

# define OSG_LONGLONG_HAS_LL

# if __INTEL_COMPILER_VERSION >= 710
#     define OSG_THROW_NOTHING() throw()
# else
#     define OSG_THROW_NOTHING()
# endif

// # define OSG_NO_INT8_PNT This works fine now. Why prevent it? DR

# define OSG_USE_PTHREADS

# define OSG_LINUX_ICC

# define OSG_FOUND_OS

// icc >=8.1 uses gnu headers anyway, use gnu defines set above
#if __INTEL_COMPILER_VERSION < 810 || ! defined(__GNUC__)
# define OSG_STDEXTENSION_NAMESPACE std
# define OSG_STDEXCEPTION_NAMESPACE std
#endif

# define OSG_STL_HAS_HASH_MAP

# define OSG_HAS_SSTREAM

# define OSG_HAS_VSNPRINTF

# if __INTEL_COMPILER_VERSION >= 800 
# define OSG_USE_HASH_COMPARE
# endif

#if defined(__GNUC__)
#if __INTEL_COMPILER_VERSION >= 900 && __GNUC__ >= 4
#define __builtin_powi(x,i) pow(x, i)
#define __builtin_powif(x,i) pow(x, i)
#define __builtin_powil(x,i) pow(x, i)
#endif
#endif

# endif // defined(__INTEL_COMPILER) && defined(__linux)

# if defined(__INTEL_COMPILER) && defined(__linux) && defined(__ia64)

# define OSG_NO_INT8_PNT

# endif // defined(__GNUC__) && defined(__linux) && defined(__ia64)

/*-------------------------------------------------------------------------*/
/*                              Windows icc                                */

// intel compiler with vc6 headers.
# if defined(__INTEL_COMPILER) && !defined(__linux) && defined(_MSC_VER) && _MSC_VER < 1300

# ifndef __ICL
#    define __ICL __INTEL_COMPILER
# endif

// Use windows internal types to define OpenSG base types
# define OSG_WIN_TYPES

// Use windows threads
# define OSG_USE_WINTHREADS

// compiler supports namespaces
# define OSG_HAS_NAMESPACE

// compiler supports std namespace
# define OSG_HAS_STD_NAMESPACE

// general float math
# define OSG_HAS_FLOATMATH

// Use WGL
# define OSG_USE_WGL

# define OSG_STREAM_HAS_ISOPEN

// it's there, it's just called something else
# define OSG_HAS_VSNPRINTF
# define vsnprintf _vsnprintf

# define OSG_HAS_NILBUF
# define OSG_STREAM_RDBUF_HAS_PARAM

# define OSG_LONGLONG_HAS_LL

# define OSG_THROW_NOTHING()

# define OSG_WIN32_ICL

# define OSG_FOUND_OS

# endif // defined(__INTEL_COMPILER) && !defined(__linux)

/*-------------------------------------------------------------------------*/
/*                              Windows vc7/8                              */

// vc7/8 and icl9/10 (with vc8 headers)
# if defined(_MSC_VER) && _MSC_VER >= 1300

# define OSG_SPEZ_IMPL_DLLMAPPING
// Use windows internal types to define OpenSG base types
# define OSG_WIN_TYPES
// compiler supports namespaces
# define OSG_HAS_NAMESPACE
// Use windows threads
# define OSG_USE_WINTHREADS
// compiler supports std namespace
# define OSG_HAS_STD_NAMESPACE
// general float math
# define OSG_HAS_FLOATMATH

// HACK need this for the x64 build on windows with the platform sdk compiler
// it uses the old vc 6.0 headers. amz
# ifndef OSG_PSDK_COMPILER
# define OSG_USE_STDMATH
# endif

# define OSG_STREAM_HAS_ISOPEN

// it's there, it's just called something else
# define OSG_HAS_VSNPRINTF
// vc 9.0 finally supports vsnprintf!
# if _MSC_VER < 1500
# define vsnprintf _vsnprintf
# endif

# define OSG_HAS_NILBUF
# define OSG_STREAM_RDBUF_HAS_PARAM

# define OSG_MICROSOFT_COMPILER_ALERT
# define OSG_MICROSOFT_COMPILER_HACKS
// Use WGL
# define OSG_USE_WGL

//# define OSG_HAS_TEMPLATE_RETURNVALUES

# define OSG_NEED_EXPLICIT_INST_FOR_STATIC

# define OSG_THROW_NOTHING()

# define OSG_WIN32_CL

# define OSG_FOUND_OS

# if _MSC_VER >= 1300 && _MSC_VER < 1310
#    define OSG_WIN32_CL_NET70 1
# endif

# if _MSC_VER > 1300
# define OSG_NEED_BOOL_MFIELD_SPEZ
# endif

// vc 8.0
# if _MSC_VER >= 1400
# define OSG_STDEXCEPTION_NAMESPACE std
# endif

# endif // defined(_MSC_VER) && !defined(__ICL)

/*-------------------------------------------------------------------------*/
/*                              Mac OSX gcc                                */

# if defined(__APPLE__)

# define darwin

# define OSG_LINUX_TYPES
# define OSG_NO_CONCEPT_CHECKS
# define SIZE_T_NEQ_UINT32
# include <AvailabilityMacros.h>
# if !defined(MAC_OS_X_VERSION_10_5) || (MAC_OS_X_VERSION_MAX_ALLOWED < MAC_OS_X_VERSION_10_5)
#  define OSG_GLENUM_NEQ_UINT32
# endif

# define OSG_USE_PTHREADS

# define OSG_DLSYM_NEEDS_UNDERSCORE

# define OSG_USE_STDMATH

#define OSG_FOUND_OS

# endif // if defined(__APPLE__)

/*-------------------------------------------------------------------------*/
/*                              HP-UX gcc-64                               */

#if defined(__hpux) && defined(__GNUC__)
/*! \brief streams in std namespace
 *  \ingroup GrpBaseDefines
 */

# define OSG_HPUX_TYPES

# define OSG_USE_PTHREADS

# define OSG_FOUND_OS

#endif

/*-------------------------------------------------------------------------*/
/*                               HP-UX aC++                                */

# if defined(__hpux) && !defined(__GNUC__)

/*! \brief compiler supports namespaces
 *  \ingroup GrpBaseDefines
 */

# define OSG_HAS_NAMESPACE

/*! \brief compiler supports std namespace
 *  \ingroup GrpBaseDefines
 */

# define OSG_HAS_STD_NAMESPACE

# if defined(_STANDARD_C_PLUS_PLUS)

# endif  /* _STANDARD_C_PLUS_PLUS */

/*! \brief stream->rdbuf get the new buffer as a parameter
 *  \ingroup GrpBaseDefines
 */

# define OSG_STREAM_RDBUF_HAS_PARAM

/*! \brief stream->isopen is available
 *  \ingroup GrpBaseDefines
 */

# define OSG_STREAM_HAS_ISOPEN

/*! \brief vsnprintf is available
 *  \ingroup GrpBaseDefines
 */

# define OSG_HAS_VSNPRINTF

/*! \brief nilbuffer is defined in the stdlib
 *  \ingroup GrpBaseDefines
 */

# define OSG_HAS_NILBUF

/*! \brief Use SGI internal types to define OpenSG base types
 *  \ingroup GrpBaseDefines
 */

# define OSG_HPUX_TYPES

/*! \brief atan2f function available
 *  \ingroup GrpBaseDefines
 */

# define OSG_HAS_ATANF2

/*! \brief General float math
 *  \ingroup GrpBaseDefines
 */

# define OSG_HAS_FLOATMATH

# define OSG_USE_STDMATH

/*! \brief SGI's stl implementation is available
 *  \ingroup GrpBaseDefines
 */

//# define OSG_SGI_STL

/*! \brief Use GLX
 *  \ingroup GrpBaseDefines
 */

# define OSG_USE_GLX

/*! \brief LongLong constants have LL suffix
 *  \ingroup GrpBaseDefines
 */

# define OSG_LONGLONG_HAS_LL

# define OSG_THROW_NOTHING() __THROWSPEC_NULL

# define OSG_USE_PTHREADS

# define OSG_HPUX_ACC

# define OSG_FOUND_OS

// # define OSG_NOGLUTSUBDIR

# define OSG_STDEXCEPTION_NAMESPACE std

# endif // defined(__hpux) && !defined(__GNUC__)


/*-------------------------------------------------------------------------*/
/*                               Sun CC                                    */

# if defined(__sun) && !defined(__GNUC__)

/*! \brief compiler supports namespaces
 *  \ingroup GrpBaseDefines
 */

# define OSG_HAS_NAMESPACE

/*! \brief compiler supports std namespace
 *  \ingroup GrpBaseDefines
 */

# define OSG_HAS_STD_NAMESPACE

# if defined(_STANDARD_C_PLUS_PLUS)

# endif  /* _STANDARD_C_PLUS_PLUS */

/*! \brief stream->rdbuf get the new buffer as a parameter
 *  \ingroup GrpBaseDefines
 */

# define OSG_STREAM_RDBUF_HAS_PARAM

/*! \brief stream->isopen is available
 *  \ingroup GrpBaseDefines
 */

# define OSG_STREAM_HAS_ISOPEN

/*! \brief vsnprintf is available
 *  \ingroup GrpBaseDefines
 */

# define OSG_HAS_VSNPRINTF

/*! \brief nilbuffer is defined in the stdlib
 *  \ingroup GrpBaseDefines
 */

# define OSG_HAS_NILBUF

/*! \brief Use SGI internal types to define OpenSG base types
 *  \ingroup GrpBaseDefines
 */

# define OSG_SUN_TYPES

/*! \brief atan2f function available
 *  \ingroup GrpBaseDefines
 */

//# define OSG_HAS_ATANF2

/*! \brief General float math
 *  \ingroup GrpBaseDefines
 */

//# define OSG_HAS_FLOATMATH

# define OSG_USE_STDMATH

/*! \brief SGI's stl implementation is available
 *  \ingroup GrpBaseDefines
 */

# define OSG_SGI_STL

/*! \brief Use GLX
 *  \ingroup GrpBaseDefines
 */

# define OSG_USE_GLX

/*! \brief LongLong constants have LL suffix
 *  \ingroup GrpBaseDefines
 */

# define OSG_LONGLONG_HAS_LL

# define OSG_THROW_NOTHING() throw()

# define OSG_USE_PTHREADS

# define OSG_SUN_CC

# define OSG_FOUND_OS

# define OSG_NO_INT8_PNT

// # define OSG_NOGLUTSUBDIR

# define OSG_STDEXCEPTION_NAMESPACE std

# endif // defined(__sun) && !defined(__GNUC__)


#ifndef OSG_FOUND_OS
# error Could not determine compiler / os combination
#endif


/* Mixed bag defines... */

// Enable printf macros used in OSGBaseTypeTraits.h
#if defined(OSG_LINUX_TYPES) && !defined(__STDC_FORMAT_MACROS)
# define __STDC_FORMAT_MACROS
#endif

// STLPORT doesn't support all of std::math
#if defined(STLPORT) ||defined(OSG_WITH_STLPORT)
#undef OSG_USE_STDMATH
#endif



#if defined(OSG_HAS_STD_NAMESPACE)
# define OSG_USING_STD_NAMESPACE namespace std {} using namespace std;
# define OSG_STD std
#endif

#if defined(OSG_HAS_NAMESPACE)

/*! @name Namespace Defines
 */

/*@{*/

/** \brief osg namespace, use to reference a object within the namespace, like
 *  \ingroup GrpBaseDefines
    OSG::OSGUInt32.
*/

# define OSG osg

/** \brief Begin the osg namespace
 *  \ingroup GrpBaseDefines
 */

# define OSG_BEGIN_NAMESPACE namespace OSG {

/** \brief End the osg namespace
 *  \ingroup GrpBaseDefines
 */

# define OSG_END_NAMESPACE }

/** \brief Use the osg namespace throughout the following code.
 *  \ingroup GrpBaseDefines
 */

# define OSG_USING_NAMESPACE namespace OSG {} using namespace OSG;

/*@}*/

# else /* OSG_HAS_NAMESPACE */

# define OSG 
# define OSG_BEGIN_NAMESPACE 
# define OSG_END_NAMESPACE 
# define OSG_USING_NAMESPACE

#endif /*  */


#if defined(OSG_DLSYM_NEEDS_UNDERSCORE)
#define OSG_DLSYM_UNDERSCORE "_"
#else
#define OSG_DLSYM_UNDERSCORE
#endif

#ifndef _OSG_HAVE_CONFIGURED_H_
#   if defined (OSG_USE_WINTHREADS)
#       define OSG_ASPECT_USE_DECLSPEC
#   endif
#endif

//#define OSG_COMPILETIME_NUM_ASPECTS

#define OSG_RUNTIME_NUM_ASPECTS 1

#define OSG_NUM_ASPECTS 2


#ifdef OSG_WIN_TYPES
#ifndef OSG_NO_WINDOWD_H_INCLUDE
#include <windows.h>
#endif
#endif

#ifndef OSG_WIN_TYPES
#define OSG_APIENTRY
#else
#ifdef APIENTRY
#define OSG_APIENTRY APIENTRY
#elif defined(GLAPIENTRY)
#define OSG_APIENTRY GLAPIENTRY
#else
#error "Neither APIENTRY nor GLAPIENTRY defined"
#endif
#endif

#ifdef OSG_DEBUG
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

#ifdef _OSG_HAVE_CONFIGURED_H_
#include <OSGConfigured.h>
#endif

#include <OSGBase.h>
#include <OSGExportDefines.h>

#if defined(OSG_DEBUG_NO_FCPTR_ARITHM)
# if defined(OSG_NUM_ASPECTS)
#  undef OSG_NUM_ASPECTS
# endif
# define OSG_NUM_ASPECTS 1
#endif

#define OSG_ASSERT(expr) assert(expr)

//#define OSG_DBG_MEM
//#define OSG_DBG_LCK

// ToBeChecked Defaults

#if !defined(OSG_STDEXCEPTION_NAMESPACE)
#    define OSG_STDEXCEPTION_NAMESPACE
#endif

#ifndef OSG_STDEXTENSION_NAMESPACE
#    define OSG_STDEXTENSION_NAMESPACE  std
#endif

#if !defined(OSG_DOC_LEVEL)
#    define OSG_DOC_LEVEL 0
#endif

#define OSG_FLEX_USE_IOSTREAM_INPUT 1

#if defined(OSG_ICC_GNU_COMPAT)

# undef OSG_USE_HASH_COMPARE

# if __GNUC__ >= 3
#    define OSG_HASH_MAP_AS_EXT

     /*! \brief SGI's stl implementation is available
      *  \ingroup GrpBaseDefines
      */
#    ifdef OSG_STDEXTENSION_NAMESPACE
#        undef OSG_STDEXTENSION_NAMESPACE
#    endif

#    if __GNUC__ >= 4 || __GNUC_MINOR__ >=1
#        define OSG_STDEXTENSION_NAMESPACE  __gnu_cxx
#    else
#        define OSG_STDEXTENSION_NAMESPACE  std
#    endif
# endif
#endif

#endif /* _OSGCONFIG_H_ */
