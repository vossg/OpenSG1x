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

#include <unistd.h>

#include "OSGConfig.h"

#include "OSGQGLManagedWidget_qt.h"

#include "OSGQTWindow.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace 
{
    static Char8 cvsid_cpp[] = "@(#)$Id: OSGQGLManagedWidget_qt.cpp,v 1.14 2002/06/29 15:23:03 jbehr Exp $";
    static Char8 cvsid_hpp[] = OSGQGLMANAGEDWIDGET_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/** \enum OSGVecBase::VectorSizeE
 *  \brief 
 */

/** \var OSGVecBase::VectorSizeE OSGVecBase::_iSize
 * 
 */

/** \fn const char *OSGVecBase::getClassname(void)
 *  \brief Classname
 */

/** \var OSGValueTypeT OSGVecBase::_values[iSize];
 *  \brief Value store
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

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

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

OSGQGLManagedWidget::OSGQGLManagedWidget ( QWidget *parent, 
                                           const char *name,
                                           SimpleSceneManager *manager ) 
  : Inherited(parent,name)
{
  FDEBUG (("OSGQGLManagedWidget constructor called\n"));

  osg::QTWindowPtr qtWinPtr = osg::QTWindow::create();

  osg::beginEditCP(qtWinPtr);
  {
    qtWinPtr->setGlWidget( this );
  }
  osg::endEditCP(qtWinPtr);

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
  FDEBUG (("OSGQGLManagedWidget copy constructor called\n"));
}

/** Destructor
 */

OSGQGLManagedWidget::~OSGQGLManagedWidget(void)
{
  FDEBUG (("OSGQGLManagedWidget destructor called\n"));
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/** assignment
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

/** assignment
 */

bool OSGQGLManagedWidget::operator < (const OSGQGLManagedWidget &other) const
{
    return this < &other;
}

//----------------------------------------------------------------------
// Method: getManager
//----------------------------------------------------------------------
SimpleSceneManager & OSGQGLManagedWidget::getManager ( void )
{
  return *_manager;
}

//----------------------------------------------------------------------
// Method: initializeGL
//----------------------------------------------------------------------
void OSGQGLManagedWidget::initializeGL ( void )
{
  FDEBUG (("OSGQGLManagedWidget::initializeGL()\n"));

  _manager->getWindow()->init();      // create the context
 
  FDEBUG (("after init()\n"));

  _manager->getWindow()->activate();  // and activate it

  // some manual init, will be moved into StateChunks later
  glEnable( GL_LIGHTING );
  glEnable( GL_LIGHT0 );
  glEnable( GL_DEPTH_TEST );
  glEnable( GL_NORMALIZE );
  // glEnable( GL_CULL_FACE );                              not a good idea
  // glEnable ( GL_BLEND );                                 not needed
  // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);     not needed

}

//----------------------------------------------------------------------
// Method: paintGL
//----------------------------------------------------------------------
void OSGQGLManagedWidget::paintGL ( void )
{
  FDEBUG (("OSGQGLManagedWidget::paintGL() \n"));

  _manager->getWindow()->activate(); // and activate it

  _manager->redraw();
}

//----------------------------------------------------------------------
// Method: resizeGL
//----------------------------------------------------------------------
void OSGQGLManagedWidget::resizeGL ( int w, int h )
{   
  FDEBUG (("OSGQGLManagedWidget::resizeGL()\n"));

  _manager->resize(w,h);
  paintGL();
}

//----------------------------------------------------------------------
// Method: mousePressEvent
//----------------------------------------------------------------------
void OSGQGLManagedWidget::mousePressEvent ( QMouseEvent *me )
{
  FDEBUG (("OSGQGLManagedWidget::mousePressEvent()\n"));
  
  switch ( me->button() ) 
    {
    case LeftButton:
      _manager->mouseButtonPress ( SimpleSceneManager::MouseLeft, 
                                   me->x(), me->y()  );
      break;
    case MidButton:
      _manager->mouseButtonPress ( SimpleSceneManager::MouseMiddle, 
                                   me->x(), me->y()   );
      break;
    case RightButton:
      _manager->mouseButtonPress ( SimpleSceneManager::MouseRight, 
                                   me->x(), me->y() );
      break;
    }
  
  paintGL();
}

//----------------------------------------------------------------------
// Method: mouseReleaseEvent
//----------------------------------------------------------------------
void OSGQGLManagedWidget::mouseReleaseEvent ( QMouseEvent *me )
{
  FDEBUG (("OSGQGLManagedWidget::mouseReleaseEvent()\n"));
  
  switch ( me->button() ) 
    {
    case LeftButton:
      _manager->mouseButtonRelease ( SimpleSceneManager::MouseLeft, 
                                     me->x(), me->y()  );
      break;
    case MidButton:
      _manager->mouseButtonRelease ( SimpleSceneManager::MouseMiddle, 
                                     me->x(), me->y()   );
      break;
    case RightButton:
      _manager->mouseButtonRelease ( SimpleSceneManager::MouseRight, 
                                     me->x(), me->y() );
      break;
    }
  
  paintGL();
}

//----------------------------------------------------------------------
// Method: mouseMoveEvent
//----------------------------------------------------------------------
void OSGQGLManagedWidget::mouseMoveEvent ( QMouseEvent *me )
{
  FDEBUG (("OSGQGLManagedWidget::mouseMoveEvent()\n"));
  
  _manager->mouseMove ( me->pos().x(), me->pos().y());
  
  paintGL();
}

//----------------------------------------------------------------------
// Method: mouseMoveEvent
//----------------------------------------------------------------------
void OSGQGLManagedWidget::wheelEvent ( QWheelEvent* we)
{
  int button;

  FDEBUG (("OSGQGLManagedWidget::wheelEvent()\n"));

  if (we->delta() > 0)
    button = SimpleSceneManager::MouseUp;
  else
    button = SimpleSceneManager::MouseDown;

  _manager->mouseButtonPress ( button, we->x(), we->y() );

  paintGL();
}

//----------------------------------------------------------------------
// Method: keyPressEvent
//----------------------------------------------------------------------

void OSGQGLManagedWidget::keyPressEvent(QKeyEvent *OSG_CHECK_ARG(ke))
{
  FDEBUG (("OSGQGLManagedWidget::keyPressEvent()\n"));
}

//----------------------------------------------------------------------
// Method: closeEvent
//----------------------------------------------------------------------

void OSGQGLManagedWidget::closeEvent(QCloseEvent *event)
{
  FDEBUG (("OSGQGLManagedWidget::closeEvent()\n"));
  
  emit closed(this);

  Inherited::closeEvent(event);
}

#ifdef __sgi
#pragma set woff 1375
#endif

#include "OSGQGLManagedWidget_qt_moc.cpp"
