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

#ifdef OSG_WITH_GLUT

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>

#define OSG_COMPILEWINDOWGLUTINST

#include "OSGGLUTWindow.h"

#include <OSGGLUT.h>

#ifdef sgi
#include <dlfcn.h>
#endif

#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGBackground.h"
#include "OSGGLUTWindow.h"

#if !defined(WIN32) && !defined(darwin)
#include <GL/glx.h>
#endif

OSG_USING_NAMESPACE

/*! \class osg::GLUTWindow
The class for GLUT-based windows. 	
*/

/*----------------------- constructors & destructors ----------------------*/

//! Constructor

GLUTWindow::GLUTWindow(void) :
    Inherited()
{
}

//! Copy Constructor

GLUTWindow::GLUTWindow(const GLUTWindow &source) :
    Inherited(source)
{
}

//! Destructor

GLUTWindow::~GLUTWindow(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void GLUTWindow::initMethod (void)
{
}

//! react to field changes

void GLUTWindow::changed(BitVector, ChangeMode)
{
}

//! output the instance for debug purposes

void GLUTWindow::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump GLUTWindow NI" << endl;
}
    
/* ------------- Window functions -----------------------*/    
    
// init the window: create the context  
void GLUTWindow::init( void )
{
    setupGL();
}
    
// activate the window: bind the OGL context    
void GLUTWindow::activate( void )
{
    if ( glutGetWindow() != getId() )
        glutSetWindow( getId() );
}
    
// deactivate the window  
void GLUTWindow::deactivate( void )
{
}
    
// swap front and back buffers  
void GLUTWindow::swap( void )
{
    glutSwapBuffers();
}


// Query for a GL extension function
void (*GLUTWindow::getFunctionByName(const Char8 *s))(void)
{
#ifdef sgi
    static void *libHandle = NULL;
    if ( ! libHandle ) 
        libHandle = dlopen("libgl.so", RTLD_LAZY);
    return (void (*)(void)) dlsym( libHandle, s);
#elif defined( WIN32 )
    return (void (*)(void)) wglGetProcAddress(s);
#elif defined(darwin)
    return NULL;
#else
    return (  glXGetProcAddressARB((const GLubyte *)s )  );
#endif
}

#endif // OSG_WITH_GLUT


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id: $";
    static char cvsid_hpp[] = OSGGLUTWINDOW_HEADER_CVSID;
    static char cvsid_inl[] = OSGGLUTWINDOW_INLINE_CVSID;
}
