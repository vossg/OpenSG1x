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
#include <OSGImageForeground.h>
#include <OSGTransform.h>
#include <OSGGeometry.h>
#include <OSGGeoPropPtrs.h>
#include <OSGSimpleMaterial.h>
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
    /*! \name                      Enums                                   */
    /*! \{                                                                 */

    enum {  MouseLeft   =  0,
            MouseMiddle =  1, 
            MouseRight  =  2,
            MouseUp     =  3,
            MouseDown   =  4
         };
         
    /*! \}                                                                 */
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

    inline NodePtr             getRoot       ( void );
    inline WindowPtr           getWindow     ( void );
    inline NodePtr             getHighlight  ( void );
    inline DrawActionBase     *getAction     ( void );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Set                                     */
    /*! \{                                                                 */

    inline void  setRoot          ( NodePtr root );
    inline void  setWindow        ( WindowPtr win );
    inline void  setHighlight     ( NodePtr obj );
    inline void  setHeadlight     ( Bool on );
    inline void  turnHeadlightOn  ( void );
    inline void  turnHeadlightOff ( void );

           void  showAll          ( void );

           void  useOpenSGLogo    ( void );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name               Interaction handling                           */
    /*! \{                                                                 */

    void resize(UInt16 width, UInt16 height);
    void mouseMove(Int16 x, Int16 y);
    void mouseButtonPress(UInt16 button, Int16 x, Int16 y);
    void mouseButtonRelease(UInt16 button, Int16 x, Int16 y);

    Line calcViewRay(Int16 x, Int16 y);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Actions                                  */
    /*! \{                                                                 */

    void redraw( void );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Comparison                                */
    /*! \{                                                                 */

    Bool operator < (const SimpleSceneManager &other) const;

    //Bool operator == (const SimpleSceneManager &other) const;
    //Bool operator != (const SimpleSceneManager &other) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                     Updates                                  */
    /*! \{                                                                 */

    void  initialize      (void);
    void  highlightChanged(void);
    void  updateHighlight (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    WindowPtr            _win;
    NodePtr              _root;

    ImageForegroundPtr   _foreground;

    NodePtr              _highlight;
    NodePtr              _highlightNode;
    GeoPositions3fPtr    _highlightPoints;
     
    NodePtr              _internalRoot;
    DirectionalLightPtr  _headlight;
    RenderAction *       _action;
    TransformPtr         _cart;
    PerspectiveCameraPtr _camera;

    Trackball            _trackball;

    Int16                _lastx;
    Int16                _lasty;
    UInt16               _mousebuttons;

    static  SimpleMaterialPtr    _highlightMaterial;
 
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/
  private:
   
    /* prohibit default function (move to 'public' if needed) */

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

#define OSGSIMPLESCENEMANAGER_HEADER_CVSID "@(#)$Id: OSGSimpleSceneManager.h,v 1.7 2001/10/16 13:22:25 dirk Exp $"

#endif /* _OSGSIMPLESCENEMANAGER_H_ */
