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

#ifndef _OSGGLUTWINDOW_H_
#define _OSGGLUTWINDOW_H_
#ifdef __sgi
#pragma once
#endif

#ifdef OSG_WITH_GLUT

#include <OSGConfig.h>

#include <OSGGLUTWindowBase.h>

OSG_BEGIN_NAMESPACE

/*! \brief *put brief class description here* 
 */

class OSG_WINDOWGLUTLIB_DLLMAPPING GLUTWindow : public GLUTWindowBase
{
  private:

    typedef GLUTWindowBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         ChangeMode from);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                Window functions                              */
    /*! \{                                                                 */
    
    // query the system for a GL function
    virtual void (*getFunctionByName(const Char8 *s))(void);
    
    // init the window: create the context  
    // Nothing to do here for GLUT
    virtual void init( void );
    
    // activate the window: bind the OGL context    
    // set the active window, if needed
    virtual void activate( void );
    
    // activate the window: bind the OGL context    
    // set the active window, if needed      
    virtual void deactivate ( void );
    
    // swap buffers for this window
    // does not set the active window!
    virtual void swap( void );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in GLUTWindowBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    GLUTWindow(void);
    GLUTWindow(const GLUTWindow &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~GLUTWindow(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class GLUTWindowBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const GLUTWindow &source);
};

typedef GLUTWindow *GLUTWindowP;

OSG_END_NAMESPACE

#include <OSGGLUTWindow.inl>
#include <OSGGLUTWindowBase.inl>

#define OSGGLUTWINDOW_HEADER_CVSID "@(#)$Id: $"

#endif /* OSG_WITH_GLUT */

#endif /* _OSGGLUTWINDOW_H_ */
