/* Builds/i686-pc-cygwin-icl60/Base/OSGConfigured.h.  Generated automatically by configure.  */
/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                     Copyright 2000,2001 by OpenSG Forum                   *
 *                                                                           *
 *   contact: reiners@igd.fhg.de, gerrit.voss@vossg.org, jbehr@zgdv.de       *
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

#ifndef _OSGCONFIGURED_H_
#define _OSGCONFIGURED_H_

#if defined (OSG_USE_WINTHREADS)
/* #undef OSG_ASPECT_USE_LOCALSTORAGE */
#define OSG_ASPECT_USE_DECLSPEC 1
#endif

#if defined(OSG_WIN_TYPES)
/* #undef OSG_BOOL_IS_UNSIGNED */
#endif

#define OSG_DEFAULT_LOG_LEVEL LOG_WARNING
#define OSG_DEFAULT_LOG_TYPE LOG_STDERR 

#if defined(WIN32) && ! defined(__ICL)
#pragma warning( disable : 4786 4661 4305 )
#endif

/* #undef OSG_SGI_USE_PTHREAD */
#define OSG_SGI_USE_SPROC 1

#if defined(__sgi)
#   if defined(OSG_SGI_USE_PTHREAD)
#       define OSG_USE_PTHREADS
#       define OSG_ASPECT_USE_PTHREADKEY
#   else
#       define OSG_USE_SPROC
#   endif
#endif

/* #undef OSG_USE_MPATROL */

#if defined(OSG_USE_MPATROL)
#define MP_NONEWDELETE 1
#include <mpatrol.h>
#endif

#endif


