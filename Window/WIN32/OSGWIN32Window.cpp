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

#define OSG_COMPILEWINDOWWIN32INST

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

// Forget everything if we're not doing a windows compile
#ifdef WIN32

#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGBackground.h"
#include "OSGWIN32Window.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::WIN32Window
    \ingroup Windows

The WIN32Window class.

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char WIN32Window::cvsid[] = "@(#)$Id: $";

// Static Class Varible implementations: 

FieldContainerType WIN32Window::_type(
    "WIN32Window",
    "Window",
    0,
    (PrototypeCreateF) &WIN32Window::createEmpty,
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

OSG_FIELD_CONTAINER_DEF(WIN32Window, WIN32WindowPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

WIN32Window::WIN32Window( void ) :
    Inherited()
{
}

WIN32Window::WIN32Window( const WIN32Window& source ) :
    Inherited(source)
{
}

/** \brief Destructor
 */

WIN32Window::~WIN32Window(void)
{
    // delete the ports and the context
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/


// init the window: create the HDC and context
void WIN32Window::init( void )
{
    _hdc = GetDC(_hwin);

    if ( _glcx == NULL && ! ( _glcx = wglCreateContext( _hdc ) ) )
    {
        cout << "WIN32Window::init: failed: " << GetLastError() << endl;        
    }

    ReleaseDC(_hwin,_hdc);
    activate();
    setupGL();
    deactivate();
}

// activate the window: bind the OGL context
void WIN32Window::activate( void )
{    
    _hdc = GetDC(_hwin);

    if ( ! wglMakeCurrent( _hdc, _glcx ) )
    {
        cout << "WIN32Window::activate: failed: " << GetLastError() << endl;        
    }
}

void WIN32Window::deactivate ( void )
{
    // unbind the context
    wglMakeCurrent(NULL, NULL);

    // release the hardware device context
    ReleaseDC(_hwin,_hdc);
}

// swap front and back buffers
void WIN32Window::swap( void )
{
    SwapBuffers( _hdc );
}

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/*------------------------------- dump ----------------------------------*/

void WIN32Window::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                       const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump WIN32Window NI" << endLog;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

#endif  // Windows compile?


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

