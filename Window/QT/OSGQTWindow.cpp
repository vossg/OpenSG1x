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

#define OSG_COMPILEQTWINDOWINST

#ifdef OSG_WITH_QT

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGBackground.h"
#include "OSGQTWindow.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::QTWindow
    \ingroup Windows

The QTWindow class.

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char QTWindow::cvsid[] = "@(#)$Id: $";

// Static Class Varible implementations: 

FieldContainerType QTWindow::_type(
    "QTWindow",
#ifdef WIN32
    "WIN32Window",
#else
    "XWindow",
#endif
    0,
    (PrototypeCreateF) &QTWindow::createEmpty,
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

OSG_FIELD_CONTAINER_DEF(QTWindow, QTWindowPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */


QTWindow::QTWindow( void ) :
    Inherited()
{
}

QTWindow::QTWindow(const QTWindow& source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

QTWindow::~QTWindow(void)
{
    // delete the ports and the context
}



/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

    
// init the window: create the context  
void QTWindow::init( void )
{
#ifdef WIN32
    if(_glWidget != NULL)
    {
        setWindow ( _glWidget->winId() );
//        setHDC    ( GetDC(_glWidget->winId()) );
        
        Inherited::init();
    }
#else
    XVisualInfo *vi;

    ///// create a new GLX context
    setDisplay( XOpenDisplay(NULL) );
    setWindow( ((QWidget*)_glWidget)->winId() );

    // get the existing glWidget's visual-id and a visual for the new context
    XVisualInfo visInfo;
    memset( &visInfo, 0, sizeof(XVisualInfo) );
    visInfo.visualid = XVisualIDFromVisual( ((Visual*)_glWidget->context()->device()->x11Visual()) );
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

    // create the new context
    setContext(  glXCreateContext( getDisplay(), vi, None, GL_TRUE )  );
#endif
    
    activate();
    setupGL();
}

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/*------------------------------- dump ----------------------------------*/

void QTWindow::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                    const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump QTWindow NI" << endl;
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

#endif /* OSG_WITH_QT */
