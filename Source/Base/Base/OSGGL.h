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

#ifndef _OSGGL_H_
#define _OSGGL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"

#ifdef OSG_GL_INCLUDE_GLEW
#include "GL/glew.h"
#endif

#ifdef OSG_NOGLSUBDIR
#include <gl.h>
#elif defined(__APPLE__)
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

// Need to define a definitely unused constant
// OpenGL doesn't provide one... :(

#define OSG_GL_UNUSED 0xffff



#include "OSGGLU.h"

OSG_BEGIN_NAMESPACE

bool OSG_BASE_DLLMAPPING osgGlCheckError(const char *file, int line, const char *msg);

#ifdef OSG_DEBUG
#define glErr(text)                                     \
  {                                                     \
    osgGlCheckError(__FILE__, __LINE__, (text));        \
  }
#else
#define glErr(text)
#endif

OSG_END_NAMESPACE

#define OSGGL_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGGL_H_ */
