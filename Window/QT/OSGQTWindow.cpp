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

#define OSG_COMPILEWINDOWQTINST

#include "OSGQTWindow.h"


OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id: $";
    static char cvsid_hpp[] = OSGQTWINDOW_HEADER_CVSID;
    static char cvsid_inl[] = OSGQTWINDOW_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif



/*! \class osg::QTWindow
The class for QT windows. 	
*/

/*----------------------- constructors & destructors ----------------------*/

//! Constructor

QTWindow::QTWindow(void) :
    Inherited()
{
}

//! Copy Constructor

QTWindow::QTWindow(const QTWindow &source) :
    Inherited(source)
{
}

//! Destructor

QTWindow::~QTWindow(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void QTWindow::initMethod (void)
{
}

//! react to field changes

void QTWindow::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

//! output the instance for debug purposes

void QTWindow::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump QTWindow NI" << endl;
}


/*-------------------------- your_category---------------------------------*/

    
// init the window: create the context  
void QTWindow::init( void )
{
#ifdef WIN32
    if(getGlWidget() != NULL)
    {
        setHwnd ( getGlWidget()->winId() );
//        setHDC    ( GetDC(_glWidget->winId()) );
        
        Inherited::init();
    }
#else
    XVisualInfo *vi;

    ///// create a new GLX context
    setDisplay( XOpenDisplay(NULL) );
    setWindow( ((QWidget*)getGlWidget())->winId() );

    // get the existing glWidget's visual-id and a visual for the new context
    XVisualInfo visInfo;
    memset( &visInfo, 0, sizeof(XVisualInfo) );
    visInfo.visualid = XVisualIDFromVisual( ((Visual*)getGlWidget()->context()->device()->x11Visual()) );
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


#include <OSGMFieldTypeDef.inl>
#include <OSGSFieldTypeDef.inl>

OSG_BEGIN_NAMESPACE

DataType FieldDataTraits<OSGQGLWidgetP>::_type("OSGQGLWidgetP", NULL);

OSG_DLLEXPORT_SFIELD_DEF1(OSGQGLWidgetP, OSG_WINDOWQTLIB_DLLTMPLMAPPING);
OSG_DLLEXPORT_MFIELD_DEF1(OSGQGLWidgetP, OSG_WINDOWQTLIB_DLLTMPLMAPPING);

OSG_END_NAMESPACE
