/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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

#ifdef OSG_WITH_GLUT

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <GL/glut.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#define OSG_COMPILEGLUTWINDOW
#define OSG_COMPILEGLUTWINDOWINST

#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGBackground.h"
#include "OSGGLUTWindow.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::GLUTWindow
    \ingroup Windows

The GLUTWindow class.

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

OSG_BEGIN_NAMESPACE

#if defined(__sgi)

#pragma instantiate SField<GLUTWindowPtr>::_fieldType
#pragma instantiate MField<GLUTWindowPtr>::_fieldType

#else

OSG_DLLEXPORT_DEF1(SField, GLUTWindowPtr, OSG_GLUTWINDOW_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, GLUTWindowPtr, OSG_GLUTWINDOW_DLLTMPLMAPPING)

#endif

OSG_END_NAMESPACE

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char GLUTWindow::cvsid[] = "@(#)$Id: $";

// Static Class Varible implementations: 

FieldContainerType GLUTWindow::_type(
    "GLUTWindow", 
    "Window", 
    0,
    (PrototypeCreateF) &GLUTWindow::createEmpty,
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

OSG_FIELD_CONTAINER_DEF(GLUTWindow, GLUTWindowPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

GLUTWindow::GLUTWindow( void ) :
	Inherited(), _winid( 0 )
{
}

GLUTWindow::GLUTWindow( const GLUTWindow& source ) :
	Inherited( source ), _winid( source._winid )
{
}

/** \brief Destructor
 */

GLUTWindow::~GLUTWindow(void)
{
	// delete the ports and the context
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

	
// init the window: create the context	
void GLUTWindow::init( void )
{
	setupGL();
}
	
// activate the window: bind the OGL context	
void GLUTWindow::activate( void )
{
	if ( glutGetWindow() != _winid )
		glutSetWindow( _winid );
}
	
// swap front and back buffers	
void GLUTWindow::swap( void )
{
	glutSwapBuffers();
}


/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/*------------------------------- dump ----------------------------------*/

void GLUTWindow::dump(      UInt32     uiIndent, 
                      const BitVector &bvFlags) const
{
	SLOG << "Dump GLUTWindow NI" << endl;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/



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

#endif // OSG_WITH_GLUT
