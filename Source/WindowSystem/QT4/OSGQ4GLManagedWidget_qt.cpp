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

#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>

#include "OSGConfig.h"

#include "OSGQ4GLManagedWidget_qt.h"

#include "OSGQT4Window.h"
//Added by qt3to4:
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QCloseEvent>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/*! Constructor
*/

OSGQGLManagedWidget::OSGQGLManagedWidget ( QWidget *parent, 
                                           const char *name,
                                           SimpleSceneManager *manager ) 
  : Inherited(parent,name)
{
    FDEBUG(("OSGQGLManagedWidget constructor called\n"));

    OSG::QTWindowPtr qtWinPtr = OSG::QTWindow::create();

    OSG::beginEditCP(qtWinPtr);
    {
        qtWinPtr->setGlWidget(this);
    }
    OSG::endEditCP(qtWinPtr);

    if(manager != NULL)
    {
        _manager = manager;
    }
    else
    {
        _manager = new SimpleSceneManager; // mem leak here
    }
  
    _manager->setWindow ( qtWinPtr );
}


OSGQGLManagedWidget::OSGQGLManagedWidget(
    const OSGQGLManagedWidget &OSG_CHECK_ARG(source) ):

    Inherited()
{
    FDEBUG(("OSGQGLManagedWidget copy constructor called\n"));
}

/*! Destructor
*/

OSGQGLManagedWidget::~OSGQGLManagedWidget(void)
{
    FDEBUG(("OSGQGLManagedWidget destructor called\n"));
}

/*! assignment
*/
OSGQGLManagedWidget& OSGQGLManagedWidget::operator = (const OSGQGLManagedWidget &source)
{
    if (this != &source)
    {
        ;     // TODO; copy parts inherited from parent
    }

    return *this;
}

/*-------------------------- comparison -----------------------------------*/

bool OSGQGLManagedWidget::operator < (const OSGQGLManagedWidget &other) const
{
    return this < &other;
}

SimpleSceneManager & OSGQGLManagedWidget::getManager ( void )
{
    return *_manager;
}

/*! initialize the OpenGL part of the OpenSG window 
*/
void OSGQGLManagedWidget::initializeGL(void)
{
    FDEBUG(("OSGQGLManagedWidget::initializeGL()\n"));

    _manager->getWindow()->init();      // create the context
 
    FDEBUG (("after init()\n"));
}


void OSGQGLManagedWidget::paintGL(void)
{
    FDEBUG(("OSGQGLManagedWidget::paintGL() \n"));

    _manager->getWindow()->activate(); // and activate it

    _manager->redraw();
}

void OSGQGLManagedWidget::resizeGL(int w, int h)
{   
    FDEBUG (("OSGQGLManagedWidget::resizeGL()\n"));

    _manager->resize(w,h);
    paintGL();
}

void OSGQGLManagedWidget::mousePressEvent(QMouseEvent *me)
{
    FDEBUG(("OSGQGLManagedWidget::mousePressEvent()\n"));
  
    switch(me->button()) 
    {
    case Qt::LeftButton:
        _manager->mouseButtonPress(SimpleSceneManager::MouseLeft, 
                                        me->x(), me->y()); 
        break;
    case Qt::MidButton:
        _manager->mouseButtonPress(SimpleSceneManager::MouseMiddle, 
                                        me->x(), me->y()); 
        break;
    case Qt::RightButton:
        _manager->mouseButtonPress(SimpleSceneManager::MouseRight, 
                                        me->x(), me->y()); 
        break;
    default:
        break;
    }
  
    paintGL();
}

void OSGQGLManagedWidget::mouseReleaseEvent(QMouseEvent *me)
{
    FDEBUG(("OSGQGLManagedWidget::mouseReleaseEvent()\n"));
  
    switch(me->button()) 
    {
    case Qt::LeftButton:
        _manager->mouseButtonRelease(SimpleSceneManager::MouseLeft, 
                                        me->x(), me->y()); 
        break;
    case Qt::MidButton:
        _manager->mouseButtonRelease(SimpleSceneManager::MouseMiddle, 
                                        me->x(), me->y()); 
        break;
    case Qt::RightButton:
        _manager->mouseButtonRelease(SimpleSceneManager::MouseRight, 
                                        me->x(), me->y()); 
        break;
    default:
        break;
    }
   
    paintGL();
}

void OSGQGLManagedWidget::mouseMoveEvent ( QMouseEvent *me )
{
    FDEBUG(("OSGQGLManagedWidget::mouseMoveEvent()\n"));
  
    _manager->mouseMove(me->pos().x(), me->pos().y());
  
    paintGL();
}

void OSGQGLManagedWidget::wheelEvent ( QWheelEvent* we)
{
    int button;

     FDEBUG (("OSGQGLManagedWidget::wheelEvent()\n"));

    if(we->delta() > 0)
    {
        button = SimpleSceneManager::MouseUp;
    }
    else
    {
        button = SimpleSceneManager::MouseDown;
    }

    _manager->mouseButtonPress(button, we->x(), we->y());

    paintGL();
}

void OSGQGLManagedWidget::keyPressEvent(QKeyEvent *OSG_CHECK_ARG(ke))
{
    FDEBUG(("OSGQGLManagedWidget::keyPressEvent()\n"));
}

void OSGQGLManagedWidget::closeEvent(QCloseEvent *event)
{
    FDEBUG(("OSGQGLManagedWidget::closeEvent()\n"));
  
    emit closed(this);

    Inherited::closeEvent(event);
}

#ifdef __sgi
#pragma set woff 1375
#endif

#include "OSGQ4GLManagedWidget_qt_moc.cpp"

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
    static char cvsid_cpp[] = "@(#)$Id: OSGQ4GLManagedWidget_qt.cpp,v 1.1 2006/03/10 18:30:35 a-m-z Exp $";
    static char cvsid_hpp[] = OSGQGLMANAGEDWIDGET_HEADER_CVSID;
}
