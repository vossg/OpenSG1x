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


#ifndef _OSGVOLRENDEF_H_
#define _OSGVOLRENDEF_H_
#ifdef __sgi
#pragma once
#endif


//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGConfig.h>

//---------------------------------------------------------------------------
//  Defines
//---------------------------------------------------------------------------

#if defined(WIN32) && defined(OSG_BUILD_DLL)
#   ifdef OSG_COMPILEVOLRENLIB
#       define OSG_VOLRENLIB_DLLMAPPING        __declspec(dllexport)
#       define OSG_VOLRENLIB_DLLTMPLMAPPING    __declspec(dllexport)
#       if defined(_MSC_VER) && defined(__ICL)
#           define OSG_MS_VOLRENLIB_DLLMAPPING 
#       else
#           define OSG_MS_VOLRENLIB_DLLMAPPING __declspec(dllexport)
#       endif
#   else
#       define OSG_VOLRENLIB_DLLMAPPING        __declspec(dllimport)
#       define OSG_VOLRENLIB_DLLTMPLMAPPING    __declspec(dllimport)
#       if defined(_MSC_VER) && defined(__ICL)
#           define OSG_MS_VOLRENLIB_DLLMAPPING 
#       else
#           define OSG_MS_VOLRENLIB_DLLMAPPING __declspec(dllimport)
#       endif
#   endif
#else
#define OSG_VOLRENLIB_DLLMAPPING
#define OSG_VOLRENLIB_DLLTMPLMAPPING
#define OSG_MS_VOLRENLIB_DLLMAPPING
#endif

#endif /* _OSGVOLREN_H_ */


