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

#include <OpenSG/OSGBaseTypes.h>

#include <OpenSG/OSGQGLWidget_qt.h>
#include <OpenSG/OSGWindow.h>
#include <OpenSG/OSGSimpleSceneManager.h>


//OSG_BEGIN_NAMESPACE
namespace osg {

/*! \ingroup baselib
 *  \brief Brief
 */

class OSGQGLManagedWidget : public OSGQGLWidget
{

  Q_OBJECT

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
 
    OSGQGLManagedWidget(QWidget *parent =0, const char *name = 0);

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

    Bool operator < (const OSGQGLManagedWidget &other) const;
    
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

    SimpleSceneManager _manager;

    virtual void initializeGL (void);
    virtual void paintGL (void);
    virtual void resizeGL (int w, int h);
    virtual void mousePressEvent ( QMouseEvent* );
    virtual void mouseReleaseEvent ( QMouseEvent* );
    virtual void mouseMoveEvent ( QMouseEvent* );
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

//OSG_END_NAMESPACE
}; // namespace osg

#define OSG_HEADER_CVSID "@(#)$Id: OSGQGLManagedWidget_qt.h,v 1.2 2001/10/09 13:37:29 jbehr Exp $"
#define OSG_INLINE_CVSID "@(#)$Id: OSGQGLManagedWidget_qt.h,v 1.2 2001/10/09 13:37:29 jbehr Exp $"

#endif /* _OSGQGLManagedWidget_H_ */
