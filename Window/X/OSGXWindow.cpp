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

#define OSG_COMPILEWINDOWXINST

#include "OSGXWindow.h"

OSG_USING_NAMESPACE

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

void XWindow::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

//! output the instance for debug purposes

void XWindow::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump XWindow NI" << std::endl;
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
        SFATAL << "Visual is not OpenGL-capable!" << std::endl;
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

#include <OSGMFieldTypeDef.inl>
#include <OSGSFieldTypeDef.inl>

OSG_BEGIN_NAMESPACE

DataType FieldDataTraits<DisplayP>  ::_type("DisplayP", NULL);
DataType FieldDataTraits<X11Window> ::_type("X11Window", NULL);
DataType FieldDataTraits<GLXContext>::_type("GLXContext", NULL);

OSG_DLLEXPORT_SFIELD_DEF1(DisplayP,   OSG_WINDOWXLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(DisplayP,   OSG_WINDOWXLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(X11Window,  OSG_WINDOWXLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(X11Window,  OSG_WINDOWXLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_SFIELD_DEF1(GLXContext, OSG_WINDOWXLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(GLXContext, OSG_WINDOWXLIB_DLLTMPLMAPPING);

OSG_END_NAMESPACE

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
    static char cvsid_hpp[] = OSGXWINDOW_HEADER_CVSID;
    static char cvsid_inl[] = OSGXWINDOW_INLINE_CVSID;

    static char cvsid_fields_hpp[] = OSGWINDOWXFIELDS_HEADER_CVSID;
}

