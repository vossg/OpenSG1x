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

#ifdef __hpux
#include <sys/types.h>
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
 *  \ingroup BaseDefines
 */

# define OSG_HAS_NAMESPACE

/*! \brief compiler supports std namespace
 *  \ingroup BaseDefines
 */

# define OSG_HAS_STD_NAMESPACE

/*! \brief stream->rdbuf get the new buffer as a parameter
 *  \ingroup BaseDefines
 */

# define OSG_STREAM_RDBUF_HAS_PARAM

/*! \brief stream->isopen is available
 *  \ingroup BaseDefines
 */

# define OSG_STREAM_HAS_ISOPEN

/*! \brief vsnprintf is available
 *  \ingroup BaseDefines
 */

# define OSG_HAS_VSNPRINTF

/*! \brief nilbuffer is defined in the stdlib
 *  \ingroup BaseDefines
 */

# define OSG_HAS_NILBUF

/*! \brief LongLong constants have LL suffix
 *  \ingroup BaseDefines
 */

# define OSG_LONGLONG_HAS_LL

# if __GNUC__ >= 3 
#    define OSG_HASH_MAP_AS_EXT

     /*! \brief SGI's stl implementation is available
      *  \ingroup BaseDefines
      */

#    define OSG_SGI_STL

#    define OSG_THROW_NOTHING() throw()
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
 *  \ingroup BaseDefines
 */

# define OSG_HAS_NAMESPACE

/*! \brief compiler supports std namespace
 *  \ingroup BaseDefines
 */

# define OSG_HAS_STD_NAMESPACE

# if defined(_STANDARD_C_PLUS_PLUS)

     /*! \brief streams in std namespace
      *  \ingroup BaseDefines
      */

#    define OSG_STREAM_IN_STD_NAMESPACE

# endif  /* _STANDARD_C_PLUS_PLUS */

/*! \brief stream->rdbuf get the new buffer as a parameter
 *  \ingroup BaseDefines
 */

# define OSG_STREAM_RDBUF_HAS_PARAM

/*! \brief stream->isopen is available
 *  \ingroup BaseDefines
 */

# define OSG_STREAM_HAS_ISOPEN

/*! \brief vsnprintf is available
 *  \ingroup BaseDefines
 */

# define OSG_HAS_VSNPRINTF

/*! \brief nilbuffer is defined in the stdlib
 *  \ingroup BaseDefines
 */

# define OSG_HAS_NILBUF

/*! \brief Use SGI internal types to define OpenSG base types
 *  \ingroup BaseDefines
 */

# define OSG_SGI_TYPES

/*! \brief atan2f function available
 *  \ingroup BaseDefines
 */

# define OSG_HAS_ATANF2

/*! \brief General float math
 *  \ingroup BaseDefines
 */

# define OSG_HAS_FLOATMATH

/*! \brief SGI's stl implementation is available
 *  \ingroup BaseDefines
 */

# define OSG_SGI_STL

/*! \brief Use GLX 
 *  \ingroup BaseDefines
 */

# define OSG_USE_GLX

/*! \brief LongLong constants have LL suffix
 *  \ingroup BaseDefines
 */

# define OSG_LONGLONG_HAS_LL

# define OSG_THROW_NOTHING() THROW_NOTHING()

# define OSG_USE_SPROC

# define OSG_SGI_CC

# define OSG_FOUND_OS 

# endif // defined(__sgi) && !defined(__GNUC__)




/*-------------------------------------------------------------------------*/
/*                              Linux gcc                                  */

# if defined(__GNUC__) && defined(__linux)

/*! \brief streams in std namespace
 *  \ingroup BaseDefines
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
# endif // defined(_MSC_VER) && !defined(__ICL)

/*-------------------------------------------------------------------------*/
/*                              Mac OSX gcc                                */

# if defined(darwin)

/*! \brief streams in std namespace
 *  \ingroup BaseDefines
 */

# define OSG_STREAM_IN_STD_NAMESPACE

# define OSG_LINUX_TYPES
# define OSG_NO_CONCEPT_CHECKS 
# define OSG_THROW_NOTHING() 
# define SIZE_T_NEQ_UINT32
# define OSG_NOGLSUBDIR

# define OSG_USE_PTHREADS

# endif // if defined(darwin)

/*-------------------------------------------------------------------------*/
/*                              HP-UX gcc-64                               */

#if defined(__hpux) && defined(__GNUC__)
/*! \brief streams in std namespace
 *  \ingroup BaseDefines
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
 *  \ingroup BaseDefines
 */

# define OSG_HAS_NAMESPACE

/*! \brief compiler supports std namespace
 *  \ingroup BaseDefines
 */

# define OSG_HAS_STD_NAMESPACE

# if defined(_STANDARD_C_PLUS_PLUS)

     /*! \brief streams in std namespace
      *  \ingroup BaseDefines
      */

#    define OSG_STREAM_IN_STD_NAMESPACE

# endif  /* _STANDARD_C_PLUS_PLUS */

/*! \brief stream->rdbuf get the new buffer as a parameter
 *  \ingroup BaseDefines
 */

# define OSG_STREAM_RDBUF_HAS_PARAM

/*! \brief stream->isopen is available
 *  \ingroup BaseDefines
 */

# define OSG_STREAM_HAS_ISOPEN

/*! \brief vsnprintf is available
 *  \ingroup BaseDefines
 */

# define OSG_HAS_VSNPRINTF

/*! \brief nilbuffer is defined in the stdlib
 *  \ingroup BaseDefines
 */

# define OSG_HAS_NILBUF

/*! \brief Use SGI internal types to define OpenSG base types
 *  \ingroup BaseDefines
 */

# define OSG_HPUX_TYPES

/*! \brief atan2f function available
 *  \ingroup BaseDefines
 */

# define OSG_HAS_ATANF2

/*! \brief General float math
 *  \ingroup BaseDefines
 */

# define OSG_HAS_FLOATMATH

/*! \brief SGI's stl implementation is available
 *  \ingroup BaseDefines
 */

//# define OSG_SGI_STL

/*! \brief Use GLX 
 *  \ingroup BaseDefines
 */

# define OSG_USE_GLX

/*! \brief LongLong constants have LL suffix
 *  \ingroup BaseDefines
 */

# define OSG_LONGLONG_HAS_LL

# define OSG_THROW_NOTHING() __THROWSPEC_NULL

# define OSG_USE_PTHREADS

# define OSG_HPUX_ACC

# define OSG_FOUND_OS 

# define OSG_NOGLUTSUBDIR

# endif // defined(__hpux) && !defined(__GNUC__)


#ifndef OSG_FOUND_OS
# error Could not determine compiler / os combination
#endif

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

#endif /* _OSGCONFIG_H_ */
