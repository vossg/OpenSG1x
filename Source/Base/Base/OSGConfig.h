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
/*                              endian general                             */

#if defined(__sgi)
#include <standards.h>
#include <sys/endian.h>
#elif defined(__hpux)
#include <arpa/nameser.h>
#include <pthread.h>
#elif defined(darwin)
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

#    if __GNUC_MINOR__ >=1
#        define OSG_STDEXTENSION_NAMESPACE  __gnu_cxx
#    else
#        define OSG_STDEXTENSION_NAMESPACE  std
#    endif

#    define OSG_STL_HAS_HASH_MAP

# else
#     define OSG_THROW_NOTHING() 
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

     /*! \brief streams in std namespace
      *  \ingroup GrpBaseDefines
      */

#    define OSG_STREAM_IN_STD_NAMESPACE

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

# define OSG_STREAM_IN_STD_NAMESPACE

# define OSG_LINUX_TYPES

# define OSG_HAS_ATANF2

# define OSG_HAS_FLOATMATH

# define OSG_USE_GLX

# define OSG_USE_PTHREADS

# define OSG_LINUX_GCC

# define OSG_FOUND_OS
 
# endif // defined(__GNUC__) && defined(__linux)

/*-------------------------------------------------------------------------*/
/*                              Linux icc                                  */

# if defined(__INTEL_COMPILER) && defined(__linux)

# ifndef __ICL
#    define __ICL __INTEL_COMPILER
# endif

# define OSG_HAS_NAMESPACE

# define OSG_HAS_STD_NAMESPACE

# define OSG_STREAM_IN_STD_NAMESPACE

# define OSG_STREAM_RDBUF_HAS_PARAM

# define OSG_STREAM_HAS_IOPEN

# define OSG_HAS_NILBUF

# define OSG_LINUX_TYPES

# define OSG_HAS_ATANF2

# define OSG_HAS_FLOATMATH

# define OSG_USE_GLX

# define OSG_LONGLONG_HAS_LL

# define OSG_THROW_NOTHING() 

# define OSG_USE_PTHREADS

# define OSG_LINUX_ICC

# define OSG_FOUND_OS

# define OSG_STDEXCEPTION_NAMESPACE std

# define OSG_STL_HAS_HASH_MAP

# endif // defined(__INTEL_COMPILER) && defined(__linux)

/*-------------------------------------------------------------------------*/
/*                              Windows icc                                */

# if defined(__INTEL_COMPILER) && !defined(__linux)

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

# define OSG_LONGLONG_HAS_LL

# define OSG_THROW_NOTHING()

# define OSG_WIN32_ICL

# define OSG_FOUND_OS

# endif // defined(__INTEL_COMPILER) && !defined(__linux)

/*-------------------------------------------------------------------------*/
/*                              Windows vc7                                */

# if defined(_MSC_VER) && !defined(__ICL)

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

# define OSG_WIN32_CL

# define OSG_FOUND_OS
 
# endif // defined(_MSC_VER) && !defined(__ICL)

/*-------------------------------------------------------------------------*/
/*                              Mac OSX gcc                                */

# if defined(darwin)

/*! \brief streams in std namespace
 *  \ingroup GrpBaseDefines
 */

# define OSG_STREAM_IN_STD_NAMESPACE

# define OSG_LINUX_TYPES
# define OSG_NO_CONCEPT_CHECKS 
# define SIZE_T_NEQ_UINT32

# define OSG_NOGLSUBDIR
# define OSG_NO_GLUT_GLSUBDIR
 
# define OSG_USE_PTHREADS

# define OSG_DLSYM_NEEDS_UNDERSCORE

#define OSG_FOUND_OS

# endif // if defined(darwin)

/*-------------------------------------------------------------------------*/
/*                              HP-UX gcc-64                               */

#if defined(__hpux) && defined(__GNUC__)
/*! \brief streams in std namespace
 *  \ingroup GrpBaseDefines
 */

# define OSG_HPUX_TYPES

# define OSG_STREAM_IN_STD_NAMESPACE
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

     /*! \brief streams in std namespace
      *  \ingroup GrpBaseDefines
      */

#    define OSG_STREAM_IN_STD_NAMESPACE

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


#ifndef OSG_FOUND_OS
# error Could not determine compiler / os combination
#endif

#if defined(OSG_HAS_STD_NAMESPACE)
# define OSG_USING_STD_NAMESPACE namespace std {} using namespace std;
# define OSG_STD std

//OSG_USING_STD_NAMESPACE

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
# define OSG_USING_OSG_NAMESPACE

#endif /*  */


#if defined(OSG_DLSYM_NEEDS_UNDERSCORE)
#define OSG_DLSYM_UNDERSCORE "_"
#else
#define OSG_DLSYM_UNDERSCORE
#endif

#if defined (OSG_USE_PTHREADS)

#define OSG_ASPECT_USE_PTHREADKEY

#endif /* OSG_USE_PTHREADS */

#ifndef _OSG_HAVE_CONFIGURED_H_
#   if defined (OSG_USE_WINTHREADS)
#       define OSG_ASPECT_USE_DECLSPEC
#   endif
#endif

#define OSG_COMPILETIME_NUM_ASPECTS
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


#include <OSGExportDefines.h>

#ifdef _OSG_HAVE_CONFIGURED_H_
#include <OSGConfigured.h>
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

#endif /* _OSGCONFIG_H_ */
