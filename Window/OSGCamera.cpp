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

#include "OSGConfig.h"
#include "OSGLog.h"

#include <GL/gl.h>

#include "OSGNode.h"
#include "OSGFieldContainerPtr.h"
#include "OSGViewport.h"
#include "OSGCamera.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \defgroup Cameras OpenSG Cameras
    \ingroup WindowLib

The Camera group includes all the Camera and camera enhancement objects.

*/

/*! \class osg::Camera
    \ingroup Cameras

The Camera base class.

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char Camera::cvsid[] = "@(#)$Id: $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

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

/** \brief initialize the static features of the class, e.g. action callbacks
 */

void Camera::initMethod (void)
{
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

Camera::Camera(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

Camera::Camera(const Camera &source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

Camera::~Camera(void)
{
}


/** \brief react to field changes
 */

void Camera::changed(BitVector, ChangeMode)
{
}
    

/*-------------------------- your_category---------------------------------*/

/** setup the GL for rendering and tell the Action what it needs to know */

void Camera::setup(      DrawActionBase *OSG_CHECK_ARG(action), 
                   const Viewport       &port                 )
{
    Matrix m;

    // set the projection

    getProjection( m, port.getPixelWidth(), port.getPixelHeight() );

    //SDEBUG << "Projection matrix: " << m << endl;

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glLoadMatrixf( m.getValues() );

    // set the viewing

    getViewing( m, port.getPixelWidth(), port.getPixelHeight() );

    //SDEBUG << "Viewing matrix: " << m << endl;
    
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    glLoadMatrixf( m.getValues() );
}

void Camera::setupProjection(      DrawActionBase *OSG_CHECK_ARG(action),
                             const Viewport       &port                 )
{
    Matrix m;

    // set the projection

    getProjection( m, port.getPixelWidth(), port.getPixelHeight() );

    //SDEBUG << "Projection matrix: " << m << endl;

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glLoadMatrixf( m.getValues() );
}



/** draw the camera's geometry (if any). Usually there is none. */
void Camera::draw(      DrawAction *OSG_CHECK_ARG(action), 
                  const Viewport   &OSG_CHECK_ARG(port  ))
{
}

/** get the separate elements needed for rendering */

void Camera::getProjection(Matrix &OSG_CHECK_ARG(result),
                           UInt32  OSG_CHECK_ARG(width ),
                           UInt32  OSG_CHECK_ARG(height))
{
    SFATAL << "Camera::getProjection: NIY" << endl;
    abort();
}

void Camera::getProjectionTranslation(Matrix &result, 
                                      UInt32  OSG_CHECK_ARG(width ), 
                                      UInt32  OSG_CHECK_ARG(height))
{
    result.setIdentity();
}

void Camera::getViewing(Matrix &result, 
                        UInt32  OSG_CHECK_ARG(width ),
                        UInt32  OSG_CHECK_ARG(height))
{
    if ( getBeacon() == NullFC )
    {
        SWARNING << "Camera::setup: no beacon!" << endl;
        return;
    }   

    getBeacon()->getToWorld( result );  
    result.invert();
}

void Camera::getFrustum( FrustumVolume& result, const Viewport& port )
{
    Matrix mv,prt,pr;
    
    getProjection( pr, port.getPixelWidth(), port.getPixelHeight() );
    getViewing   ( mv, port.getPixelWidth(), port.getPixelHeight() );

    pr.mult( mv );
    
    result.setPlanes( pr );
}

Bool Camera::calcViewRay( Line & line, Int32 x, Int32 y, const Viewport& port)
{
    Matrix proj, projtrans, view;

    getProjection( proj, port.getPixelWidth(), port.getPixelHeight() );
    getProjectionTranslation( projtrans, port.getPixelWidth(), 
                                port.getPixelHeight() );
    getViewing( view, port.getPixelWidth(), port.getPixelHeight() );
    
    Matrix wctocc = proj;
    wctocc.mult( projtrans );
    wctocc.mult( view );

    Matrix cctowc;
    cctowc.invertFrom( wctocc );
    
    Real32  rx = ( x / (Real32) port.getPixelWidth() ) * 2. - 1.,
            ry = 1.f - ( y / (Real32) port.getPixelHeight() ) * 2.;
    
    view.invert();
    Pnt3f from( view[3][0], view[3][1], view[3][2] );
            
    Pnt3f at;
    cctowc.multFullMatrixPnt( Pnt3f( rx, ry, 1 ), at );
    
    line.setValue( from, at-from );
    
    return true;
}

/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */

void Camera::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                  const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump Camera NI" << endl;
}

    

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

