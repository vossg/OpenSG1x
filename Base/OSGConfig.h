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

#   define OSG_USE_SPROC

    /*! \brief Use GLX 
     *  \ingroup BaseDefines
     */

#   define OSG_USE_GLX

    /*! \brief LongLong constants have LL suffix
     *  \ingroup BaseDefines
     */

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

#   define OSG_SGI_STL
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
# define OSG_HAS_STD_NAMESPACE
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

#ifdef OSG_WIN_TYPES
#include <windows.h>
#endif

#ifndef OSG_WIN_TYPES
#define OSG_APIENTRY
#else
#define OSG_APIENTRY APIENTRY
//#define OSG_BOOL_IS_UNSIGNED
#endif


#ifdef OSG_DEBUG
//#define OSG_DEBUG_TYPED_FCPTR
#define OSG_DEBUG_LOCK_STAT
#endif


#if defined(WIN32)
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



#define OSG_EXPORT_TYPE_DEF1(CLASSNAME, T1, DLLMAPPING)                      \
    template DLLMAPPING                                                      \
        const FieldType  CLASSNAME<T1>::_fieldType;
#define OSG_EXPORT_TYPE_DEF2(CLASSNAME, T1, T2, DLLMAPPING)                  \
    template DLLMAPPING                                                      \
        const FieldType  CLASSNAME<T1, T2>::_fieldType;

#define OSG_EXPORT_GETTYPE_DEF1(CLASSNAME, T1, DLLMAPPING)                   \
    template DLLMAPPING                                                      \
        const FieldType &CLASSNAME<T1>::getType    (void) const;
#define OSG_EXPORT_GETTYPE_DEF2(CLASSNAME, T1, T2, DLLMAPPING)               \
    template DLLMAPPING                                                      \
        const FieldType &CLASSNAME<T1, T2>::getType(void) const;

#define OSG_EXPORT_GETCLASSTYPE_DEF1(CLASSNAME, T1, DLLMAPPING)              \
    template DLLMAPPING                                                      \
        const FieldType &CLASSNAME<T1>::getClassType    (void);
#define OSG_EXPORT_GETCLASSTYPE_DEF2(CLASSNAME, T1, T2, DLLMAPPING)          \
    template DLLMAPPING                                                      \
        const FieldType &CLASSNAME<T1, T2>::getClassType(void);

#define OSG_DLLEXPORT_DEF1(CLASSNAME, T1, DLLMAPPING)                        \
    OSG_EXPORT_TYPE_DEF1        (CLASSNAME, T1, DLLMAPPING)                  \
    OSG_EXPORT_GETTYPE_DEF1     (CLASSNAME, T1, DLLMAPPING)                  \
    OSG_EXPORT_GETCLASSTYPE_DEF1(CLASSNAME, T1, DLLMAPPING)


#define OSG_DLLEXPORT_DEF2(CLASSNAME, T1, T2, DLLMAPPING)                    \
    OSG_EXPORT_TYPE_DEF2        (CLASSNAME, T1, T2, DLLMAPPING)              \
    OSG_EXPORT_GETTYPE_DEF2     (CLASSNAME, T1, T2, DLLMAPPING)              \
    OSG_EXPORT_GETCLASSTYPE_DEF2(CLASSNAME, T1, T2, DLLMAPPING)



#define OSG_FC_EXPORT_TYPE_DECL(CLASSNAME, T1, DLLMAPPING)                   \
    extern template DLLMAPPING                                               \
        FieldContainerType CLASSNAME<T1>::_type;

#define OSG_FC_EXPORT_DESC_DECL(CLASSNAME, T1, DLLMAPPING)                   \
    extern template DLLMAPPING                                               \
        FieldDescription   CLASSNAME<T1>::_desc[];

#define OSG_FC_EXPORT_GETTYPE_DECL(CLASSNAME, T1, DLLMAPPING)                \
    extern template DLLMAPPING                                               \
              FieldContainerType &CLASSNAME<T1>::getType(void);              \
    extern template DLLMAPPING                                               \
        const FieldContainerType &CLASSNAME<T1>::getType(void) const;        \
    extern template DLLMAPPING                                               \
              FieldContainerType &CLASSNAME<T1>::getStaticType(void);        \
    extern template DLLMAPPING                                               \
              UInt32              CLASSNAME<T1>::getStaticTypeId(void);

#define OSG_FC_DLLEXPORT_DECL(CLASSNAME, T1, DLLMAPPING)                     \
    OSG_FC_EXPORT_TYPE_DECL   (CLASSNAME, T1, DLLMAPPING)                    \
    OSG_FC_EXPORT_DESC_DECL   (CLASSNAME, T1, DLLMAPPING)                    \
    OSG_FC_EXPORT_GETTYPE_DECL(CLASSNAME, T1, DLLMAPPING)     

#define OSG_ABSTR_FC_DLLEXPORT_DECL(CLASSNAME, T1, DLLMAPPING)               \
    OSG_FC_EXPORT_TYPE_DECL   (CLASSNAME, T1, DLLMAPPING)                    \
    OSG_FC_EXPORT_GETTYPE_DECL(CLASSNAME, T1, DLLMAPPING)     



#define OSG_FC_EXPORT_TYPE_DEF(CLASSNAME, T1, DLLMAPPING)                    \
    template DLLMAPPING                                                      \
        FieldContainerType CLASSNAME<T1>::_type;

#define OSG_FC_EXPORT_DESC_DEF(CLASSNAME, T1, DLLMAPPING)                    \
    template DLLMAPPING                                                      \
        FieldDescription   CLASSNAME<T1>::_desc[];

#define OSG_FC_EXPORT_GETTYPE_DEF(CLASSNAME, T1, DLLMAPPING)                 \
    template DLLMAPPING                                                      \
              FieldContainerType &CLASSNAME<T1>::getType(void);              \
    template DLLMAPPING                                                      \
        const FieldContainerType &CLASSNAME<T1>::getType(void) const;        \
    template DLLMAPPING                                                      \
              FieldContainerType &CLASSNAME<T1>::getStaticType(void);        \
    template DLLMAPPING                                                      \
              UInt32              CLASSNAME<T1>::getStaticTypeId(void);

#define OSG_FC_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING)                      \
    OSG_FC_EXPORT_TYPE_DEF   (CLASSNAME, T1, DLLMAPPING)                     \
    OSG_FC_EXPORT_DESC_DEF   (CLASSNAME, T1, DLLMAPPING)                     \
    OSG_FC_EXPORT_GETTYPE_DEF(CLASSNAME, T1, DLLMAPPING)     


#define OSG_ABSTR_FC_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING)                \
    OSG_FC_EXPORT_TYPE_DEF   (CLASSNAME, T1, DLLMAPPING)                     \
    OSG_FC_EXPORT_GETTYPE_DEF(CLASSNAME, T1, DLLMAPPING)     

#elif defined (__linux)

#define OSG_EXPORT_TYPE_DECL1(CLASSNAME, T1, DLLMAPPING)                     \
    extern template const FieldType  CLASSNAME<T1>::_fieldType;
#define OSG_EXPORT_TYPE_DECL2(CLASSNAME, T1, T2, DLLMAPPING)                 \
    extern template const FieldType  CLASSNAME<T1, T2>::_fieldType;

#define OSG_DLLEXPORT_DECL1(CLASSNAME, T1, DLLMAPPING)                       \
    OSG_EXPORT_TYPE_DECL1        (CLASSNAME, T1, DLLMAPPING)

#define OSG_DLLEXPORT_DECL2(CLASSNAME, T1, T2, DLLMAPPING)                   \
    OSG_EXPORT_TYPE_DECL2        (CLASSNAME, T1, T2, DLLMAPPING)             \


#define OSG_EXPORT_TYPE_DEF1(CLASSNAME, T1, DLLMAPPING)                      \
    template const FieldType  CLASSNAME<T1>::_fieldType;
#define OSG_EXPORT_TYPE_DEF2(CLASSNAME, T1, T2, DLLMAPPING)                  \
    template const FieldType  CLASSNAME<T1, T2>::_fieldType;

#define OSG_DLLEXPORT_DEF1(CLASSNAME, T1, DLLMAPPING)                        \
    OSG_EXPORT_TYPE_DEF1        (CLASSNAME, T1, DLLMAPPING)                  \

#define OSG_DLLEXPORT_DEF2(CLASSNAME, T1, T2, DLLMAPPING)                    \
    OSG_EXPORT_TYPE_DEF2        (CLASSNAME, T1, T2, DLLMAPPING)              \



#define OSG_FC_EXPORT_TYPE_DECL(CLASSNAME, T1, DLLMAPPING)                   \
    extern template FieldContainerType CLASSNAME<T1>::_type;

#define OSG_FC_EXPORT_DESC_DECL(CLASSNAME, T1, DLLMAPPING)                   \
    extern template FieldDescription   CLASSNAME<T1>::_desc[];


#define OSG_FC_DLLEXPORT_DECL(CLASSNAME, T1, DLLMAPPING)                     \
    OSG_FC_EXPORT_TYPE_DECL   (CLASSNAME, T1, DLLMAPPING)                    \
    OSG_FC_EXPORT_DESC_DECL   (CLASSNAME, T1, DLLMAPPING)                    \

#define OSG_ABSTR_FC_DLLEXPORT_DECL(CLASSNAME, T1, DLLMAPPING)               \
    OSG_FC_EXPORT_TYPE_DECL   (CLASSNAME, T1, DLLMAPPING)                    \



#define OSG_FC_EXPORT_TYPE_DEF(CLASSNAME, T1, DLLMAPPING)                    \
    template FieldContainerType CLASSNAME<T1>::_type;

#define OSG_FC_EXPORT_DESC_DEF(CLASSNAME, T1, DLLMAPPING)                    \
    template FieldDescription   CLASSNAME<T1>::_desc[];

#define OSG_FC_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING)                      \
    OSG_FC_EXPORT_TYPE_DEF   (CLASSNAME, T1, DLLMAPPING)                     \

#define OSG_ABSTR_FC_DLLEXPORT_DEF(CLASSNAME, T1, DLLMAPPING)                \
    OSG_FC_EXPORT_TYPE_DEF   (CLASSNAME, T1, DLLMAPPING)

#elif defined (__sgi)
#else
#error Could not determine system
#endif

#endif /* _OSGCONFIG_H_ */



