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

#ifndef _OSG_QGLWIDGET_H_
#define _OSG_QGLWIDGET_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#ifdef OSG_WITH_QT

#include <stdlib.h>
#include <stdio.h>

#ifdef __sgi
#pragma set woff 1375
#endif

#ifdef OSG_WIN32_ICL
#pragma warning (disable : 171)
#endif

#include <qgl.h>

#ifdef OSG_WIN32_ICL
#pragma warning (error : 171)
#endif

#ifdef __sgi
#pragma reset woff 1375
#endif

#include "OSGConfig.h"
#include <OSGWindowQTDef.h>
#include <OSGBaseTypes.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! OSGQGL widget class
 */

class OSG_WINDOWQTLIB_DLLMAPPING OSGQGLWidget : public QGLWidget
{
  Q_OBJECT

  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    OSGQGLWidget(       QWidget   *parent, 
                  const Char8     *name        = 0, 
                  const QGLWidget *shareWidget = 0, 
                        WFlags     f           = 0);
                    
    OSGQGLWidget(const QGLFormat &format      = QGLFormat::defaultFormat(),
                       QWidget   *parent      = 0, 
                 const Char8     *name        = 0, 
                 const QGLWidget *shareWidget = 0, 
                       WFlags     f           = 0);

    virtual ~OSGQGLWidget();
    
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*------------------------- your_category -------------------------------*/
    
    // the main point of these is to prevent QT from interfering with OpenGL 
    virtual void makeCurrent( void );
    virtual void swapBuffers( void );
    
    /*------------------------- your_operators ------------------------------*/

    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

    /*------------------------------ dump -----------------------------------*/

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------
    
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    virtual void initializeGL( void );
    virtual void paintGL( void );
    virtual void resizeGL( int w, int h );

    private:

    /* prohibit default function (move to 'public' if needed) */
    OSGQGLWidget(const OSGQGLWidget &source);
    /* prohibit default function (move to 'public' if needed) */
    void operator =(const OSGQGLWidget &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

/** \brief class pointer
 */

typedef OSGQGLWidget *OSGQGLWidgetP;

OSG_END_NAMESPACE

#include <OSGQGLWidget_qt.inl>

#endif /* OSG_WITH_QT */

#endif /* _OSG_QGLWIDGET_H_ */



