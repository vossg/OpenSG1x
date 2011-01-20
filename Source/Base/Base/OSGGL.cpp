/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                  Copyright (C) 2011 by the OpenSG Forum                   *
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

#include "OSGGL.h"
#include "OSGLog.h"

OSG_BEGIN_NAMESPACE

/*! Checks for OpenGL errors, prints a warning for all that are
    currently queued and returns false if any errors where detected.
    The arguments can be used to identify the location of the error,
    file and line are usually __FILE__ and __LINE__ respectively.

    Only in debug builds (preprocessor token OSG_DEBUG defined) the
    actual error checking is performed.
 */
bool osgGlCheckError(const char *file, int line, const char *msg)
{
    bool retVal = true;

#ifdef OSG_DEBUG
    GLenum glErr;

    while((glErr = glGetError()) != GL_NO_ERROR)
    {
        FWARNING(("(%s,%d): %s failed: %s (%#x)\n",
                  file, line, msg,
                  gluErrorString(glErr), glErr));

        retVal = false;
    }
#endif

    return retVal;
}

OSG_END_NAMESPACE
