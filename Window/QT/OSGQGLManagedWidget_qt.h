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

#ifndef _OSGQGLManagedWidget_H_
#define _OSGQGLManagedWidget_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGWindowQTDef.h>

#include "OSGBaseTypes.h"

#include "OSGQGLWidget_qt.h"
#include "OSGWindow.h"
#include "OSGSimpleSceneManager.h"


OSG_BEGIN_NAMESPACE

/*! \ingroup baselib
 *  \brief Brief
 */

class OSG_WINDOWQTLIB_DLLMAPPING OSGQGLManagedWidget : public OSGQGLWidget
{

  Q_OBJECT

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
 
    OSGQGLManagedWidget(      QWidget            *parent  = 0, 
                        const char               *name    = 0,
                              SimpleSceneManager *manager = 0);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~OSGQGLManagedWidget(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    SimpleSceneManager &getManager(void);

    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    bool operator < (const OSGQGLManagedWidget &other) const;
    
    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                      signals                                 */
    /*! \{                                                                 */

  signals:
 
    void closed ( QWidget *object );

    /*! \}                                                                 */
    
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    SimpleSceneManager *_manager;

    virtual void initializeGL (void);
    virtual void paintGL (void);
    virtual void resizeGL (int w, int h);
    virtual void mousePressEvent ( QMouseEvent* );
    virtual void mouseReleaseEvent ( QMouseEvent* );
    virtual void mouseMoveEvent ( QMouseEvent* );
    virtual void wheelEvent ( QWheelEvent* );
    virtual void keyPressEvent ( QKeyEvent* );
    virtual void closeEvent ( QCloseEvent * );

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:

    typedef OSGQGLWidget Inherited;


    /*!\brief prohibit default function (move to 'public' if needed) */
    OSGQGLManagedWidget(const OSGQGLManagedWidget &source);
    OSGQGLManagedWidget & operator =(const OSGQGLManagedWidget &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef OSGQGLManagedWidget *OSGQGLManagedWidgetP;

OSG_END_NAMESPACE

#define OSGQGLMANAGEDWIDGET_HEADER_CVSID "@(#)$Id: OSGQGLManagedWidget_qt.h,v 1.8 2002/06/29 15:23:03 jbehr Exp $"

#endif /* _OSGQGLManagedWidget_H_ */
