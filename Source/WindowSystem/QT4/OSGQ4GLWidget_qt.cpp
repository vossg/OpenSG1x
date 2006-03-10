/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#ifdef OSG_WITH_QT

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGQ4GLWidget_qt.h"

OSG_USING_NAMESPACE

/*! \class osg::QTWindow

The class for QT-based windows. See \ref PageWindowQT for a description.

*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/*! Constructor
*/


OSGQGLWidget::OSGQGLWidget( QWidget *parent, const char *name, 
                    const QGLWidget * shareWidget, Qt::WFlags f ) :
    QGLWidget( parent, name, shareWidget, f ) 
{
}
                    
OSGQGLWidget::OSGQGLWidget( const QGLFormat & format,
                  QWidget *parent, const char *name, 
                  const QGLWidget * shareWidget, Qt::WFlags f       
                ) :
    QGLWidget( format, parent, name, shareWidget, f ) 
{
}


/*! Destructor
*/

OSGQGLWidget::~OSGQGLWidget( void )
{
}


/*------------------------------ access -----------------------------------*/

void OSGQGLWidget::initializeGL(void) 
{
}

void OSGQGLWidget::paintGL(void) 
{
}

void OSGQGLWidget::resizeGL(int, int) 
{
}

void OSGQGLWidget::makeCurrent(void)
{
}

void OSGQGLWidget::swapBuffers(void)
{
}

#ifdef __sgi
#pragma set woff 1375
#endif

#include "OSGQ4GLWidget_qt_moc.cpp"

#ifdef __sgi
#pragma reset woff 1375
#endif

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
    static char cvsid_cpp[] = "@(#)$Id: OSGQ4GLWidget_qt.cpp,v 1.1 2006/03/10 18:30:35 a-m-z Exp $";
    static char cvsid_hpp[] = OSGQGLWIDGET_HEADER_CVSID;
    static char cvsid_inl[] = OSGQGLWIDGET_INLINE_CVSID;
}

#endif /* OSG_WITH_QT */
