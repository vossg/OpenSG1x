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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>

#include "OSGPassiveWindow.h"

#if !defined(WIN32) && !defined(darwin)
#include <GL/glx.h>
#endif

#if defined(__sgi) || defined(darwin) || defined(__hpux)
#include <dlfcn.h>
#endif

OSG_USING_NAMESPACE

/*! \class osg::PassiveWindow

*/

/*----------------------- constructors & destructors ----------------------*/

//! Constructor

PassiveWindow::PassiveWindow(void) :
    Inherited()
{
}

//! Copy Constructor

PassiveWindow::PassiveWindow(const PassiveWindow &source) :
    Inherited(source)
{
}

//! Destructor

PassiveWindow::~PassiveWindow(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void PassiveWindow::initMethod (void)
{
}

//! react to field changes

void PassiveWindow::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

//! output the instance for debug purposes

void PassiveWindow::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PassiveWindow NI" << endl;
}

// init the window: create the context  
void PassiveWindow::init( void )
{
    setupGL();
}
    
// activate the window: bind the OGL context    
void PassiveWindow::activate( void )
{
}
    
// swap front and back buffers  
void PassiveWindow::swap( void )
{
}

// Query for a GL extension function
PassiveWindow::PassiveWindowExtFunc PassiveWindow::getFunctionByName(const Char8 *s)
{
#ifdef __sgi
    static void *libHandle = NULL;
    if(libHandle == NULL)
        libHandle = dlopen("libgl.so", RTLD_LAZY);
    void *func = dlsym( libHandle, s );
    return (void (*)(void))func;         
#elif defined( WIN32 )
    return PassiveWindowExtFunc(wglGetProcAddress(s));
#elif defined(__hpux)
    static void *libHandle = NULL;

    if(libHandle == NULL)
    {
        // HACK, but we link against libGL anyway
        libHandle = dlopen(NULL, RTLD_GLOBAL);
    }

    return (void (*)(void)) dlsym(libHandle, s);
#else
// UGLY HACK: SGI/NVidia header don't define GLX_ARB_get_proc_address,
// but they use __GLX_glx_h__ instead of GLX_H as an include guard.
#if defined(GLX_ARB_get_proc_address) || defined(__GLX_glx_h__)
    return glXGetProcAddressARB((const GLubyte *) s);
#else
    return NULL;
#endif
#endif
    
//    return PassiveWindowExtFunc(s);
}


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
    static char cvsid_cpp[] = "@(#)$Id: OSGPassiveWindow.cpp,v 1.10 2002/08/07 04:04:13 vossg Exp $";
    static char cvsid_hpp[] = OSGPASSIVEWINDOW_HEADER_CVSID;
    static char cvsid_inl[] = OSGPASSIVEWINDOW_INLINE_CVSID;
}
