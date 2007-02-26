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

#ifndef _OSGQGLManagedWidget_H_
#define _OSGQGLManagedWidget_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGWindowQT4Def.h"

#include "OSGBaseTypes.h"

#include "OSGQ4GLWidget_qt.h"
#include "OSGWindow.h"
#include "OSGSimpleSceneManager.h"


OSG_BEGIN_NAMESPACE

/*! \brief Managed QT Widget. See 
    \ref PageOSGQGLManagedWidget "OSGQGLManagedWidget" for a description. 
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

    virtual void initializeGL      (void);
    virtual void paintGL           (void);
    virtual void resizeGL          (int w, int h);
    virtual void mousePressEvent   (QMouseEvent*);
    virtual void mouseReleaseEvent (QMouseEvent*);
    virtual void mouseMoveEvent    (QMouseEvent*);
    virtual void wheelEvent        (QWheelEvent*);
    virtual void keyPressEvent     (QKeyEvent  *);
    virtual void closeEvent        (QCloseEvent*);

    /*! \}                                                                 */

    /*==========================  PRIVATE  ================================*/
  private:

    typedef OSGQGLWidget Inherited;

    /*!\brief prohibit default function (move to 'public' if needed) */
    OSGQGLManagedWidget(const OSGQGLManagedWidget &source);
    OSGQGLManagedWidget & operator =(const OSGQGLManagedWidget &source);
};

typedef OSGQGLManagedWidget *OSGQGLManagedWidgetP;

OSG_END_NAMESPACE

#define OSGQGLMANAGEDWIDGET_HEADER_CVSID "@(#)$Id: OSGQ4GLManagedWidget_qt.h,v 1.3 2007/02/26 13:37:38 yjung Exp $"

#endif /* _OSGQGLManagedWidget_H_ */
