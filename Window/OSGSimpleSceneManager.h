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

#ifndef _OSGSIMPLESCENEMANAGER_H_
#define _OSGSIMPLESCENEMANAGER_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBaseTypes.h>
#include <OSGWindow.h>          

#include <OSGDrawAction.h>
#include <OSGRenderAction.h>
#include <OSGNode.h>
#include <OSGWindow.h>
#include <OSGTransform.h>
#include <OSGPerspectiveCamera.h>
#include <OSGDirectionalLight.h>
#include <OSGTrackball.h>

OSG_BEGIN_NAMESPACE

/*! \ingroup SystemLib
 *  \brief A helper class to simplify managing simple applications.
 */

class OSG_SYSTEMLIB_DLLMAPPING SimpleSceneManager
{
    /*==========================  PUBLIC  =================================*/
  public:
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    SimpleSceneManager(void);
    SimpleSceneManager *create( void );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~SimpleSceneManager(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Get                                     */
    /*! \{                                                                 */

    inline NodePtr     getRoot    ( void );
    inline WindowPtr   getWindow  ( void );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    inline void  setRoot    ( NodePtr root );
    inline void  setWindow  ( WindowPtr win );
    inline void  setHeadlight   ( Bool on );
    inline void  turnHeadlightOn ( void );
    inline void  turnHeadlightOff ( void );

           void  showAll ( void );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Interaction handling                           */
    /*! \{                                                                 */

    void resize(UInt16 width, UInt16 height);
    void mouseMove(Int16 x, Int16 y);
    void mouseButtonPress(UInt16 button, Int16 x, Int16 y);
    void mouseButtonRelease(UInt16 button, Int16 x, Int16 y);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Actions                                  */
    /*! \{                                                                 */

    void redraw( void );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                 Container Access                             */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Binary Access                              */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   your_operators                             */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Assignment                                */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    Bool operator < (const SimpleSceneManager &other) const;

    //Bool operator == (const SimpleSceneManager &other) const;
    //Bool operator != (const SimpleSceneManager &other) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Dump                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                  Type information                            */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Updates                                  */
    /*! \{                                                                 */

    void  initialize( void );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Changed                               */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                MT Destruction                                */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Sync                                     */
    /*! \{                                                                 */

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:

    WindowPtr            _win;
    NodePtr              _root;

    NodePtr              _internalRoot;
    DirectionalLightPtr  _headlight;
    DrawAction *       _action;
    TransformPtr         _cart;
    PerspectiveCameraPtr _camera;

    Trackball            _trackball;

    Int16                _lastx;
    Int16                _lasty;
    UInt16               _mousebuttons;
    
    /*!\brief prohibit default function (move to 'public' if needed) */

    SimpleSceneManager(const SimpleSceneManager &source);
    void operator =(const SimpleSceneManager &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef SimpleSceneManager *SimpleSceneManagerP;

OSG_END_NAMESPACE

#include "OSGSimpleSceneManager.inl"

#define OSGSIMPLESCENEMANAGER_HEADER_CVSID "@(#)$Id: OSGSimpleSceneManager.h,v 1.2 2001/09/28 07:57:00 vossg Exp $"

#endif /* _OSGSIMPLESCENEMANAGER_H_ */
