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

#include <OSGConfig.h>
#include <OSGBaseFunctions.h>

#include "OSGSimpleSceneManager.h"

#include <OSGSolidBackground.h>
#include <OSGViewport.h>

OSG_USING_NAMESPACE

namespace
{
    static char cvsid_cpp[] = "@(#)$Id: OSGSimpleSceneManager.cpp,v 1.6 2001/10/10 10:42:57 vossg Exp $";
    static char cvsid_hpp[] = OSGSIMPLESCENEMANAGER_HEADER_CVSID;
    static char cvsid_inl[] = OSGSIMPLESCENEMANAGER_INLINE_CVSID;
}

/*! \var WindowPtr SimpleSceneManager::_win
 *  The window used to render into.
 */

/*! \var SimpleSceneManager::MouseLeft
 *  The constant for the left mouse button.
 */

/*! \var SimpleSceneManager::MouseMiddle
 *  The constant for the middle mouse button.
 */

/*! \var SimpleSceneManager::MouseRight
 *  The constant for the right mouse button.
 */

/*! \var SimpleSceneManager::MouseUp
 *  The constant for the mouse wheel up (away from the hand) motion.
 */

/*! \var SimpleSceneManager::MouseDown
 *  The constant for the mouse wheel down (towards the hand) motion.
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

/*! \var SimpleSceneManager::_highlightMaterial
 *  The material used by the highlight object.
 */

SimpleMaterialPtr SimpleSceneManager::_highlightMaterial;


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
    _mousebuttons(0), _highlight(), _highlightPoints()
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
    _action = RenderAction::create();

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
    _camera->setFov( deg2rad( 60. ) );
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

    updateHighlight();

    _win->render( _action );
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

/*! call when a mouse button is pressed. button is the number of the pressed
    button, starting at 0, ordered from left to right. A wheel should be
    mapped to buttons 3 and 4. The position is in pixel, starting at the
    upper left corner.
 */

void SimpleSceneManager::mouseButtonPress(UInt16 button, Int16 x, Int16 y)
{
    switch ( button )
    {
    case MouseLeft:     break;
    case MouseMiddle:   _trackball.setAutoPosition(true);
                        break;
    case MouseRight:    _trackball.setAutoPositionNeg(true);
                        break;
    }
    _mousebuttons |= 1 << button;
    _lastx = x;
    _lasty = y;
}


/*! call when a mouse button is released. button is the number of the pressed
    button, starting at 0, ordered from left to right. A wheel should be
    mapped to buttons 3 and 4. The position is in pixel, starting at the
    upper left corner.
 */
void SimpleSceneManager::mouseButtonRelease(UInt16 button, Int16 x, Int16 y)
{
    switch ( button )
    {
    case MouseLeft:     break;
    case MouseMiddle:   _trackball.setAutoPosition(false);
                        break;
    case MouseRight:    _trackball.setAutoPositionNeg(false);
                        break;
    }
    _mousebuttons &= ~(1 << button);
    _lastx = x;
    _lasty = y;
}

/*! The highlight is a geometry that surrounds an object in the graph.
 */
void SimpleSceneManager::highlightChanged(void)
{
    // init as needed
    if(_highlightMaterial == NullFC)
    {
        _highlightMaterial = SimpleMaterial::create();

        beginEditCP(_highlightMaterial);
        _highlightMaterial->setDiffuse(Color3f(0,1,0));
        _highlightMaterial->setLit(false);
        endEditCP(_highlightMaterial);
    }
    if(_highlightNode == NullFC)
    {
        GeoPTypesPtr type = GeoPTypesUI8::create();
        beginEditCP(type);
        type->addValue( GL_LINE_STRIP );
        type->addValue( GL_LINES );
        endEditCP(type);

        GeoPLengthsPtr lens = GeoPLengthsUI32::create();
        beginEditCP(lens);
        lens->addValue( 10 );
        lens->addValue( 6 );
        endEditCP(lens);

        GeoIndicesUI32Ptr index = GeoIndicesUI32::create();
        beginEditCP(index);
        index->getFieldPtr()->addValue( 0 );
        index->getFieldPtr()->addValue( 1 );
        index->getFieldPtr()->addValue( 3 );
        index->getFieldPtr()->addValue( 2 );
        index->getFieldPtr()->addValue( 0 );
        index->getFieldPtr()->addValue( 4 );
        index->getFieldPtr()->addValue( 5 );
        index->getFieldPtr()->addValue( 7 );
        index->getFieldPtr()->addValue( 6 );
        index->getFieldPtr()->addValue( 4 );

        index->getFieldPtr()->addValue( 1 );
        index->getFieldPtr()->addValue( 5 );
        index->getFieldPtr()->addValue( 2 );
        index->getFieldPtr()->addValue( 6 );
        index->getFieldPtr()->addValue( 3 );
        index->getFieldPtr()->addValue( 7 );
        endEditCP(index);

        _highlightPoints = GeoPositions3f::create();
        beginEditCP(_highlightPoints);
        _highlightPoints->addValue( Pnt3f( -1, -1, -1) );
        _highlightPoints->addValue( Pnt3f(  1, -1, -1) );
        _highlightPoints->addValue( Pnt3f( -1,  1, -1) );
        _highlightPoints->addValue( Pnt3f(  1,  1, -1) );
        _highlightPoints->addValue( Pnt3f( -1, -1,  1) );
        _highlightPoints->addValue( Pnt3f(  1, -1,  1) );
        _highlightPoints->addValue( Pnt3f( -1,  1,  1) );
        _highlightPoints->addValue( Pnt3f(  1,  1,  1) );
        endEditCP(_highlightPoints);

        GeometryPtr geo=Geometry::create();
        beginEditCP(geo);
        geo->setTypes(type);
        geo->setLengths(lens);
        geo->setIndices(index);
        geo->setPositions(_highlightPoints);
        geo->setMaterial(_highlightMaterial);
        endEditCP(geo);
        addRefCP(geo);

        _highlightNode = Node::create();
        beginEditCP(_highlightNode);
        _highlightNode->setCore(geo);
        endEditCP(_highlightNode);
        addRefCP(_highlightNode);
    }

    // attach the hightlight node to the root if the highlight is active
    if(getHighlight() != NullFC)
    {
        if(_highlightNode->getParent() == NullFC)
        {
            beginEditCP(_internalRoot);
            _internalRoot->addChild(_highlightNode);
            endEditCP(_internalRoot);
        }
    }
    else
    {
        if(_highlightNode->getParent() != NullFC)
        {
            beginEditCP(_internalRoot);
            _internalRoot->subChild(_highlightNode);
            endEditCP(_internalRoot);
        }

    }
    // update the highlight geometry
    updateHighlight();
}

void SimpleSceneManager::updateHighlight(void)
{
    if(_highlight==NullFC)
        return;

    // calc the world bbox of the highlight object
    DynamicVolume vol;
    _highlight->getWorldVolume( vol );

    Pnt3f min,max;
    vol.getBounds(min, max);

    beginEditCP(_highlightPoints);
    _highlightPoints->setValue(Pnt3f( min[0], min[1], min[2]), 0);
    _highlightPoints->setValue(Pnt3f( max[0], min[1], min[2]), 1);
    _highlightPoints->setValue(Pnt3f( min[0], max[1], min[2]), 2);
    _highlightPoints->setValue(Pnt3f( max[0], max[1], min[2]), 3);
    _highlightPoints->setValue(Pnt3f( min[0], min[1], max[2]), 4);
    _highlightPoints->setValue(Pnt3f( max[0], min[1], max[2]), 5);
    _highlightPoints->setValue(Pnt3f( min[0], max[1], max[2]), 6);
    _highlightPoints->setValue(Pnt3f( max[0], max[1], max[2]), 7);
    endEditCP(_highlightPoints);

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
