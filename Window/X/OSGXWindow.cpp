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

#ifdef sgi
#include <dlfcn.h>
#endif

#define OSG_COMPILEWINDOWXINST

#include "OSGXWindow.h"

OSG_BEGIN_NAMESPACE

DataType FieldDataTraits<DisplayP>  ::_type("DisplayP", NULL, true);
DataType FieldDataTraits<X11Window> ::_type("X11Window", NULL, true);
DataType FieldDataTraits<GLXContext>::_type("GLXContext", NULL, true);

#if defined(__sgi)

#pragma instantiate SField<DisplayP>  ::_fieldType
#pragma instantiate MField<DisplayP>  ::_fieldType
#pragma instantiate SField<X11Window> ::_fieldType
#pragma instantiate MField<X11Window> ::_fieldType
#pragma instantiate SField<GLXContext>::_fieldType
#pragma instantiate MField<GLXContext>::_fieldType

#else

OSG_DLLEXPORT_DEF1(SField, DisplayP,   OSG_WINDOWXLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, DisplayP,   OSG_WINDOWXLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, X11Window,  OSG_WINDOWXLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, X11Window,  OSG_WINDOWXLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(SField, GLXContext, OSG_WINDOWXLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, GLXContext, OSG_WINDOWXLIB_DLLTMPLMAPPING)

#endif

OSG_END_NAMESPACE

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id: $";
    static char cvsid_hpp[] = OSGXWINDOW_HEADER_CVSID;
    static char cvsid_inl[] = OSGXWINDOW_INLINE_CVSID;

    static char cvsid_fields_hpp[] = OSGWINDOWXFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/*! \class osg::XWindow
The class windows on X.
*/

/*----------------------- constructors & destructors ----------------------*/

//! Constructor

XWindow::XWindow(void) :
    Inherited()
{
}

//! Copy Constructor

XWindow::XWindow(const XWindow &source) :
    Inherited(source)
{
}

//! Destructor

XWindow::~XWindow(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void XWindow::initMethod (void)
{
}

//! react to field changes

void XWindow::changed(BitVector, ChangeMode)
{
}

//! output the instance for debug purposes

void XWindow::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump XWindow NI" << endl;
}



// init the window: create the context  
void XWindow::init( void )
{    
    XVisualInfo       *vi, visInfo;
    XWindowAttributes winAttr;

    XGetWindowAttributes( getDisplay(), getWindow(), &winAttr );

    // get the existing glWidget's visual-id
    memset( &visInfo, 0, sizeof(XVisualInfo) );
    visInfo.visualid = XVisualIDFromVisual( winAttr.visual );

    // get new display-variable
    setDisplay(XOpenDisplay(DisplayString(getDisplay())));  

    // get a visual for the glx context
    int nvis;
    vi = XGetVisualInfo( getDisplay(), VisualIDMask, &visInfo, &nvis );

    // is the visual GL-capable ?
    int useGL;
    glXGetConfig( getDisplay(), 
                  vi, 
                  GLX_USE_GL, 
                  &useGL );
    if ( !useGL )
    {
        SFATAL << "Visual is not OpenGL-capable!" << endl;
    }    
  
    XWindowPtr win(*this);
    beginEditCP(win, ContextFieldMask);
    // create the new context
    setContext(glXCreateContext( getDisplay(), vi, None, GL_TRUE ));
    endEditCP  (win, ContextFieldMask);

    glXMakeCurrent( getDisplay(), getWindow(), getContext() );
    setupGL();
}
    
// activate the window: bind the OGL context    
void XWindow::activate( void )
{
    glXMakeCurrent( getDisplay(), getWindow(), getContext() );
}
    
// activate the window: bind the OGL context    
void XWindow::deactivate( void )
{
    glXMakeCurrent( getDisplay(), None, NULL );
}
    
// swap front and back buffers  
void XWindow::swap( void )
{
    glXSwapBuffers( getDisplay(), getWindow() );
}

// Query for a GL extension function
void (*XWindow::getFunctionByName( const Char8 *s ))(void)
{
#ifdef __sgi
    void *libHandle = dlopen("libgl.so", RTLD_LAZY);
    void *func = dlsym( libHandle, s );
    dlclose(libHandle);
    return (void (*)(void))func;         
#else
    return glXGetProcAddressARB((const GLubyte *) s);
#endif
}


