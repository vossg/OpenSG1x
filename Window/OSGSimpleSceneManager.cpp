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

#define OSG_SYSTEMLIB

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>
#include <OSGBaseFunctions.h>

#include "OSGSimpleSceneManager.h"

#include <OSGSolidBackground.h>
#include <OSGViewport.h>

OSG_USING_NAMESPACE

namespace 
{
    static char cvsid_cpp[] = "@(#)$Id: OSGSimpleSceneManager.cpp,v 1.2 2001/09/28 07:56:59 vossg Exp $";
    static char cvsid_hpp[] = OSGSIMPLESCENEMANAGER_HEADER_CVSID;
    static char cvsid_inl[] = OSGSIMPLESCENEMANAGER_INLINE_CVSID;
}

/*! \var WindowPtr SimpleSceneManager::_win
 *  The window used ot render into.
 */

/**
 *  SimpleSceneManager manages the OpenSG components that are needed to do simple
 *  applications that just wnat to display some geometry.
 *  It takes the window to render into and the root node of the graph to
 *  display and takes care of creating the necessary additional OpenSG objects,
 *  like a viewport for the window,
 */


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

SimpleSceneManager::SimpleSceneManager(void) :
    _win(), _root(), _internalRoot(), _headlight(), _action(), _trackball(),
    _lastx(TypeConstants<Int16>::getMax()),
    _lasty(TypeConstants<Int16>::getMax()),
    _mousebuttons(0)
{
}


/** \brief Destructor
 */

SimpleSceneManager::~SimpleSceneManager(void)
{
    if ( _action )
        delete _action;
}

/*--------------------------- Updates ---------------------------------*/

/*! create the parts that the app needs: viewport, camera,
 *  base graph etc.
 */

void SimpleSceneManager::initialize(void)
{
    // the rendering action
    _action = DrawAction::create();

    // the camera and light beacon
    NodePtr cartN = Node::create();
    _cart = Transform::create();

    beginEditCP(cartN);
    cartN->setCore( _cart );
    endEditCP(cartN);

    // the headlight
    _internalRoot = Node::create();
    _headlight    = DirectionalLight::create();

    addRefCP(_internalRoot);
    beginEditCP(_internalRoot);
    _internalRoot->setCore( _headlight );
    _internalRoot->addChild(cartN);
    endEditCP(_internalRoot);

    beginEditCP(_headlight);
    _headlight->setAmbient  (.3, .3, .3, 1);
    _headlight->setDiffuse  ( 1,  1,  1, 1);
    _headlight->setSpecular ( 1,  1,  1, 1);
    _headlight->setDirection( 0,  0,  1);
    _headlight->setBeacon   (cartN);
    endEditCP(_headlight);

    // the trackball
    _trackball.setMode( Trackball::OSGObject );
    _trackball.setSum( true );
    _trackball.setTranslationMode( Trackball::OSGFree );

    // the camera
    _camera = PerspectiveCamera::create();
    beginEditCP(_camera);
    _camera->setBeacon( cartN );
    _camera->setFov( deg2rad( 60 ) );
    _camera->setNear( 0.1 );
    _camera->setFar( 10000 );
    endEditCP(_camera);

    // need a viewport?
    if ( _win->getPort().getSize() == 0 )
    {
        // I'd like this to be a gradient background, but it still has
        // problems on Linux/nVidia

        SolidBackgroundPtr bg = SolidBackground::create();
        beginEditCP(bg);
        bg->setColor( Color3f(0, 0, 0) );
        endEditCP(bg);

        ViewportPtr vp = Viewport::create();
        beginEditCP(vp);
        vp->setCamera( _camera );
        vp->setBackground( bg );
        vp->setRoot( _internalRoot );
        vp->setSize( 0,0, 1,1 );
        endEditCP(vp);

        beginEditCP(_win);
        _win->addPort(vp);
        endEditCP(_win);
    }
}

/*! show the whole scene: move out far enough  to see everything
 */
void SimpleSceneManager::showAll(void)
{
    if ( _root == NullFC )
        return;

    _root->updateVolume();

    Vec3f min,max;
    _root->getVolume().getBounds( min, max );
    Vec3f d = max - min;

    Real32 dist = osgMax(d[0],d[1]) / (2 * osgtan(_camera->getFov() / 2.f));

    Vec3f pos(0, 0, max[2] + dist );

    _trackball.setStartPosition(pos, true);
    _trackball.setRotationCenter(Pnt3f((min[0] + max[0]) * .5,
                                       (min[1] + max[1]) * .5,
                                       (min[2] + max[2]) * .5));

    // set the camera to go from 1% of the object to twice its size
    Real32 diag = osgMax(osgMax(d[0], d[1]), d[2]);
    beginEditCP(_camera);
    _camera->setNear(diag / 100.f);
    _camera->setFar(3 * diag);
    endEditCP(_camera);
}

/*! draw the next frame, update if needed
 */
void SimpleSceneManager::redraw(void)
{
    if ( _internalRoot == NullFC )
    {
        initialize();
        showAll();
    }

    _cart->getSFMatrix()->setValue( _trackball.getFullTrackballMatrix() );

    _win->draw( _action );
}


/*! resize
 */
void SimpleSceneManager::resize(UInt16 width, UInt16 height)
{
    _win->resize( width, height );
}

/*! motion
 */
void SimpleSceneManager::mouseMove(Int16 x, Int16 y)
{
    OSG::Real32 w = _win->getWidth(), h = _win->getHeight();

    OSG::Real32 a = -2. * ( _lastx / w - .5 ),
                b = -2. * ( .5 - _lasty / h ),
                c = -2. * ( x / w - .5 ),
                d = -2. * ( .5 - y / h );

    if ( _lastx != TypeConstants<Int16>::getMax() )
    {
        if ( _mousebuttons & 1 )
        {
            _trackball.updateRotation( a, b, c, d );
        }
        else if ( _mousebuttons & 2 )
        {
            _trackball.updatePosition( a, b, c, d );
        }
        else if ( _mousebuttons & 4 )
        {
            _trackball.updatePositionNeg( a, b, c, d );
        }
    }
    _lastx = x;
    _lasty = y;
}

/*! buttonpress
 */
void SimpleSceneManager::mouseButtonPress(UInt16 button, Int16 x, Int16 y)
{
    switch ( button )
    {
    case 1: break;
    case 2: _trackball.setAutoPosition(true);
            break;
    case 4: _trackball.setAutoPositionNeg(true);
            break;
    }
    _mousebuttons |= 1 << button;
    _lastx = x;
    _lasty = y;
}

/*! buttonrelease
 */
void SimpleSceneManager::mouseButtonRelease(UInt16 button, Int16 x, Int16 y)
{
    switch ( button )
    {
    case 1: break;
    case 2: _trackball.setAutoPosition(false);
            break;
    case 4: _trackball.setAutoPositionNeg(false);
            break;
    }
    _mousebuttons &= ~(1 << button);
    _lastx = x;
    _lasty = y;
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/** \brief less
 */

Bool SimpleSceneManager::operator < (const SimpleSceneManager &other) const
{
    return this < &other;
}
