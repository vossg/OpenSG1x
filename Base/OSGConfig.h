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


#ifndef _OSGCONFIG_H_
#define _OSGCONFIG_H_
#ifdef __sgi
#pragma once
#endif

/** \defgroup baselib OpenSG Base Library
    OpenSG Base Library
 */

/** \namespace osg 
    \brief OpenSG namespace    
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
#   include <standards.h>

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
// compiler supports namespaces
# define OSG_HAS_NAMESPACE
// compiler supports std namespace
# define OSG_HAS_STD_NAMESPACE
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
// compiler supports namespaces
# define OSG_HAS_NAMESPACE
// compiler supports the use of template types for return values only
# define OSG_HAS_TEMPLATE_RETURNVALUES
# define  OSG_HAS_MEMBER_TEMPLATE_RETURNVALUES
# if defined(_STANDARD_C_PLUS_PLUS)
// streams in std namespace
# define OSG_STREAM_IN_STD_NAMESPACE
#   endif  /* _STANDARD_C_PLUS_PLUS */

// stream->rdbuf get the new buffer as a parameter
# define OSG_STREAM_RDBUF_HAS_PARAM
# define OSG_STREAM_HAS_ISOPEN
# define OSG_HAS_VSNPRINTF
# define OSG_HAS_NILBUF
#   endif  /* _COMPILER_VERSION >= 730 */

// Use SGI internal types to define OpenSG base types
# define OSG_SGI_TYPES
// atan2f function available
# define OSG_HAS_ATANF2
// General float math
# define OSG_HAS_FLOATMATH
// SGI STL available
# define OSG_SGI_STL
// Use pthreads
//# define OSG_USE_PTHREADS
// Use sproc
# define OSG_USE_SPROC

// Use GLX 
# define OSG_USE_GLX

# define OSG_LONGLONG_HAS_LL

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
// atan2f function available
# define OSG_HAS_ATANF2
// general float math
# define OSG_HAS_FLOATMATH
// streams in std namespace
# define OSG_STREAM_IN_STD_NAMESPACE
# endif

// compiler supports namespaces
# define OSG_HAS_NAMESPACE
// Use pthreads
# define OSG_USE_PTHREADS
// compiler supports the use of template types for return values only
//# define  OSG_HAS_MEMBER_TEMPLATE_RETURNVALUES
// # define OSG_HAS_TEMPLATE_RETURNVALUES
// stream->rdbuf get the new buffer as a parameter
# define OSG_STREAM_HAS_ISOPEN
# define OSG_HAS_VSNPRINTF
# define OSG_HAS_NILBUF
# define OSG_STREAM_RDBUF_HAS_PARAM
# define OSG_NEED_EXPLICIT_INST_FOR_STATIC
# define OSG_LONGLONG_HAS_LL
# endif

#if defined __linux
// Use gcc internal types to define OpenSG base types
# define OSG_LINUX_TYPES
// Use GLX 
# define OSG_USE_GLX
#endif

#if defined __sun
# define OSG_SUNOS_TYPES
		 //# define __EXTENSIONS__
/* name SunPro Compiler */ 
# if defined(__SUNPRO_CC) 
#   ifdef _REENTRANT
#   endif
# endif
// Use GLX 
# define OSG_USE_GLX
#endif


/* name Intel compiler, which uses the EDG front end. */ 
# if defined(__ICL)
#   ifdef _CPPUNWIND
#   endif
#   ifdef _MT
#   endif
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
# define OSG_HAS_TEMPLATE_RETURNVALUES
# define OSG_HAS_MEMBER_TEMPLATE_RETURNVALUES
# define OSG_NEED_EXPLICIT_INST_FOR_STATIC
# define OSG_LONGLONG_HAS_LL
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

// Use WGL 
# define OSG_USE_WGL

//# define OSG_HAS_TEMPLATE_RETURNVALUES

# define OSG_NEED_EXPLICIT_INST_FOR_STATIC
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
# define OSG_HAS_FLOATMATH

// Use WGL 
# define OSG_USE_WGL
# endif  /*  */


#if defined(OSG_HAS_STD_NAMESPACE)
# define OSG_USING_STD_NAMESPACE namespace std {} using namespace std;
# define OSG_STD std

OSG_USING_STD_NAMESPACE

#endif

#if defined(OSG_HAS_NAMESPACE)
# define OSG_BEGIN_NAMESPACE namespace osg { 
# define OSG_END_NAMESPACE }
# define OSG osg
# define OSG_USING_OSG_NAMESPACE namespace osg {} using namespace osg;
# define OSG_USING_NAMESPACE namespace osg {} using namespace osg;
# else /* Use std::rel_ops namespace */
# define OSG_BEGIN_NAMESPACE 
# define OSG_END_NAMESPACE 
# define OSG 
# define OSG_USING_OSG_NAMESPACE
#endif /*  */


#if defined (OSG_USE_PTHREADS)

#define OSG_ASPECT_USE_PTHREADKEY
//#define OSG_ASPECT_USE_PTHREADSELF
//#define OSG_ASPECT_USE_CUSTOMSELF

#endif /* OSG_USE_PTHREADS */

#if defined (OSG_USE_WINTHREADS)
//#define OSG_ASPECT_USE_LOCALSTORAGE
#define OSG_ASPECT_USE_DECLSPEC
#endif

#define OSG_COMPILETIME_NUM_ASPECTS
//#define OSG_RUNTIME_NUM_ASPECTS
//#define OSG_MTHREADED_FCS

#define OSG_NUM_ASPECTS 4

/* Ok, I am sorry to do it but otherwies it is a big
 * pain ita to get the include order right, even so it is still 
 * hard to do :-(( (GV)
 */

#ifdef OSG_WIN_TYPES
#include <winsock2.h>
#include <windows.h>
#endif

#ifndef OSG_WIN_TYPES
#define APIENTRY
#endif


#ifdef OSG_DEBUG
#define OSG_DEBUG_TYPED_FCPTR
#define OSG_DEBUG_LOCK_STAT
#endif

#endif /* _OSGCONFIG_H_ */



