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

#ifndef _OSGBASE_H_
#define _OSGBASE_H_
#ifdef __sgi
#pragma once
#endif

#if defined(WIN32) && defined(OSG_BUILD_DLL)
#   ifdef OSG_COMPILEBASELIB
#       define OSG_BASE_DLLMAPPING                __declspec(dllexport)
#       define OSG_BASE_DLLTMPLMAPPING            __declspec(dllexport)
#       if defined(OSG_SPEZ_IMPL_DLL_MAPPING)
#           define OSG_BASE_SPEZ_IMPL_DLLMAPPING  __declspec(dllexport)
#       elif defined(OSG_SPEZ_HEAD_DLL_MAPPING)
#           define OSG_BASE_SPEZ_HEAD_DLLMAPPING  __declspec(dllexport)
#       else
#           define OSG_BASE_SPEZ_IMPL_DLLMAPPING
#           define OSG_BASE_SPEZ_HEAD_DLLMAPPING
#       endif
#   else
#       define OSG_BASE_DLLMAPPING                __declspec(dllimport)
#       define OSG_BASE_DLLTMPLMAPPING            __declspec(dllimport)
#       if defined(OSG_SPEZ_IMPL_DLL_MAPPING)
#           define OSG_BASE_SPEZ_IMPL_DLLMAPPING  __declspec(dllimport)
#       elif defined(OSG_SPEZ_HEAD_DLL_MAPPING)
#           define OSG_BASE_SPEZ_HEAD_DLLMAPPING  __declspec(dllimport)
#       else
#           define OSG_BASE_SPEZ_IMPL_DLLMAPPING
#           define OSG_BASE_SPEZ_HEAD_DLLMAPPING
#       endif
#   endif
#   if defined(OSG_WIN32_ICL)
#       define OSG_FIELD_DLLMAPPING
#   else
#       if defined(OSG_COMPILE_FIELD_INST) 
#           define OSG_FIELD_DLLMAPPING                __declspec(dllexport)
#       else
#           define OSG_FIELD_DLLMAPPING                __declspec(dllimport)
#       endif
#   endif
#else
#define OSG_BASE_DLLMAPPING
#define OSG_BASE_DLLTMPLMAPPING
#define OSG_MS_BASE_DLLMAPPING
#define OSG_BASE_SPEZ_IMPL_DLLMAPPING
#define OSG_BASE_SPEZ_HEAD_DLLMAPPING
#endif

#endif /* _OSGBASE_H_ */
