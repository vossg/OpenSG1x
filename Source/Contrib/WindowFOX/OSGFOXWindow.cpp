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

#include "OSGFOXWindow.h"
#include "OSGFOXGLWidget.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id: OSGFOXWindow.cpp,v 1.1.1.1 2002/05/24 15:50:49 fuenfzig Exp $";
    static char cvsid_hpp[] = OSGFOXWINDOW_HEADER_CVSID;
    static char cvsid_inl[] = OSGFOXWINDOW_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/*! \class osg::FOXWindow
window fieldcontainer for FOX gui library
*/

/*----------------------- constructors & destructors ----------------------*/

//! Constructor

FOXWindow::FOXWindow(void) :
    Inherited()
{
}

//! Copy Constructor

FOXWindow::FOXWindow(const FOXWindow &source) :
    Inherited(source)
{
}

//! Destructor

FOXWindow::~FOXWindow(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void FOXWindow::initMethod (void)
{
}

//! react to field changes

void FOXWindow::changed(BitVector, UInt32)
{
}

//! output the instance for debug purposes

void FOXWindow::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump FOXWindow NI" << std::endl;
}

void FOXWindow::init( void )
{
   getGlWidget()->create();
}
	
// activate the window: bind the OGL context	
// set the active window, if needed
void FOXWindow::activate( void )
{
   getGlWidget()->makeCurrent();
}

// swap buffers	for this window
// does not set the active window!
void FOXWindow::swap( void )
{
   getGlWidget()->swapBuffers();
}
