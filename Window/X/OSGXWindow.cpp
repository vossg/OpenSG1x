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

#define OSG_COMPILEXWINDOWLIB

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

// Forget everything if we're doing a windows compile
#ifndef WIN32

#include <GL/glx.h>
#undef Bool
#ifdef sgi
#include <dlfcn.h>
#endif

#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGBackground.h"
#include "OSGXWindow.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::XWindow
    \ingroup Windows

The XWindow class.

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char XWindow::cvsid[] = "@(#)$Id: $";

// Static Class Varible implementations: 

FieldContainerType XWindow::_type(
    "XWindow", 
    "Window", 
    0,
    (PrototypeCreateF) &XWindow::createEmpty,
    0,
    NULL, 
    0);

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/



/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/



/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

OSG_FIELD_CONTAINER_DEF(XWindow, XWindowPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

XWindow::XWindow( void ) :
    Inherited()
{
}

XWindow::XWindow( const XWindow& source ) :
	Inherited()
{
}

/** \brief Destructor
 */

XWindow::~XWindow(void)
{
	// delete the ports and the context
}


/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

// init the window: create the context	
void XWindow::init( void )
{    
    XVisualInfo       *vi, visInfo;
    XWindowAttributes winAttr;

	XGetWindowAttributes( _dpy, _hwin, &winAttr );

	// get the existing glWidget's visual-id
	memset( &visInfo, 0, sizeof(XVisualInfo) );
	visInfo.visualid = XVisualIDFromVisual( winAttr.visual );

	// get new display-variable
	_dpy = XOpenDisplay(NULL);	

	// get a visual for the glx context
	int nvis;
	vi = XGetVisualInfo( _dpy, VisualIDMask, &visInfo, &nvis );

	// is the visual GL-capable ?
	int useGL;
	glXGetConfig( _dpy, 
				  vi, 
				  GLX_USE_GL, 
				  &useGL );
	if ( !useGL )
	{
	    SFATAL << "Visual is not OpenGL-capable!" << endl;
	}    
  
	// create the new context
	_glcx = glXCreateContext( _dpy, vi, None, GL_TRUE );

    glXMakeCurrent( _dpy, _hwin, _glcx );
	setupGL();
}
	
// activate the window: bind the OGL context	
void XWindow::activate( void )
{
    glXMakeCurrent( _dpy, _hwin, _glcx );
}
	
// swap front and back buffers	
void XWindow::swap( void )
{
    glXSwapBuffers( _dpy, _hwin );
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



/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/*------------------------------- dump ----------------------------------*/

void XWindow::dump(      UInt32     uiIndent, 
                   const BitVector &bvFlags) const
{
	SLOG << "Dump XWindow NI" << endl;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

#endif


///---------------------------------------------------------------------------
///  FUNCTION: 
///---------------------------------------------------------------------------
//:  Example for the head comment of a function
///---------------------------------------------------------------------------
///
//p: Paramaters: 
//p: 
///
//g: GlobalVars:
//g: 
///
//r: Return:
//r: 
///
//c: Caution:
//c: 
///
//a: Assumptions:
//a: 
///
//d: Description:
//d: 
///
//s: SeeAlso:
//s: 
///---------------------------------------------------------------------------

