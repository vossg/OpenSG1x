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

#include <OSGConfig.h>
#include <OSGBaseTypes.h>
#include <OSGMatrix.h>
#include <OSGMatrixUtility.h>
#include <OSGCamera.h>

#include "OSGNavigator.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGNavigator.cpp,v 1.6 2002/05/24 14:45:11 istoynov Exp $";
    static Char8 cvsid_hpp       [] = OSGNAVIGATOR_HEADER_CVSID;
    //static Char8 cvsid_inl       [] = OSGNAVIGATOR_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGNAVIGATOR_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/*------------------------- constructors ----------------------------------*/

/*! Constructor
 */

Navigator::Navigator(): _currentState(IDLE),
                        _currentMode(TRACKBALL),
                        _rMotionFactor(0.04f),
                        _vp(NullFC),
                        _ip(0,0,0),
                        _lastX(0),
                        _lastY(0),
                        _moved(false),
                        _clickCenter(true)
{
}

/*-------------------------- destructors ----------------------------------*/

/*! Destructor
 */
 
Navigator::~Navigator()
{
}

/*-------------------------- Notificators ---------------------------------*/

/*! Notifies for mouse button press.
 */

void Navigator::buttonPress(Int16 button, Int16 x, Int16 y)
{
    _lastX=x; _lastY=y;
    _moved=false;
    
    switch (_currentMode)
    {
        case TRACKBALL:
        {
            switch (button)
            {
                case LEFT_MOUSE:   {_currentState=ROTATING;      } break;
                case MIDDLE_MOUSE: {_currentState=TRANSLATING_XY;
                                     getIntersectionPoint(x,y);  } break;
                case RIGHT_MOUSE:  {_currentState=TRANSLATING_Z; } break;
            }
        } break;
        
        case FLY: 
        {
            switch (button)
            {
                case LEFT_MOUSE:   {_currentState=TRANSLATING_ZPLUS; } break;
                case MIDDLE_MOUSE: {_currentState=ROTATING;          } break;
                case RIGHT_MOUSE:  {_currentState=TRANSLATING_ZMINUS;} break;
            }
        } break;                
    }
}


/*! Notifies for mouse button release
 */

void Navigator::buttonRelease(Int16 , Int16 x, Int16 y)
{
    switch (_currentMode)
    {
        case TRACKBALL:
        {
            if (!_moved && _clickCenter)
            {
              	IntersectAction * act = IntersectAction::create();        
                Line line;
                _vp->getCamera()->calcViewRay(line, x, y, *_vp);

                Pnt3f lp1=line.getPosition();
                Vec3f ld1=line.getDirection();
        
                act->setLine(line);
                act->apply(_vp->getRoot());
                if (act->didHit())
                {
                    Pnt3f p1=act->getHitPoint();
                    _trackball.setFrom(p1);            
                }
            }
        } break;
        case FLY:
        {
        } break;
    }
    _currentState=IDLE;
}

/*! Notifies for key press
 */

void Navigator::keyPress(Int16 key, Int16 , Int16 )
{
    switch (_currentMode)
    {
        case TRACKBALL:
        {
        } break;
        
        case FLY:
        {
            switch (key)
            {
                case LEFT      : _flyer.right(-_rMotionFactor); break;
                case RIGHT     : _flyer.right(_rMotionFactor); break;
                case FORWARDS  : _flyer.forward(-_rMotionFactor); break;
                case BACKWARDS : _flyer.forward(_rMotionFactor); break;
            }            
        } break;
    }    
}

/*! Notifies for mouse motion
 */

template <typename t>
t osgsgn(t val)
{
    if(val < 0) return -1;
    if(val > 0) return  1;
    return 0;
}

void Navigator::moveTo(Int16 x, Int16 y)
{
    _moved=true;
    
    Real32 width=_vp->getPixelWidth();
    Real32 height=_vp->getPixelHeight();
    
    Real32 fromX=(2.0f * _lastX - width) / width;
    Real32 fromY=(height - 2.0f * _lastY) / height;
    Real32 toX=(2.0f * x - width) / width;
    Real32 toY=(height - 2.0f * y) / height;    
            
    switch (_currentMode)
    {
        case TRACKBALL:
        {     
            switch (_currentState)
            {
                case ROTATING:
                    {
                        _trackball.rotate(fromX, fromY, toX, toY);
                    } break;
                case TRANSLATING_XY: 
                    {
                        Real32 distanceX=0,distanceY=0;
                        calcDeltas(_lastX, _lastY, x, y, distanceX, distanceY);
                        _trackball.translateXY(distanceX, distanceY); 
                    } break;        
                case TRANSLATING_Z:
                    {
                        Real32 distance=osgsgn(toY-fromY)*
                                        100.f * osgpow(osgabs(toY-fromY),2.f);
                        _trackball.translateZ(distance * _rMotionFactor);
                    } break;
            }
        } break;
        
        case FLY:
        {
            Real32 distanceX=-(fromX-toX);
            Real32 distanceY=(fromY-toY);
            _flyer.rotate(distanceX, distanceY);
            
            switch (_currentState)
            {                
                case TRANSLATING_ZPLUS:  
                    {
                        _flyer.forward(-_rMotionFactor); 
                    } break;
                case TRANSLATING_ZMINUS: 
                    {
                        _flyer.forward(_rMotionFactor);
                    } break;
                case ROTATING:           
                    {
                    } break;
            }
        } break;        
    }
    _lastX=x;
    _lastY=y;   
}

/*------------------------------ set --------------------------------------*/

/*! Sets the navigator mode (Trackball or Flyer)
 */

void Navigator::setMode(Navigator::Mode new_mode)
{	
	if (_currentMode==new_mode) return;

	if (_currentMode==TRACKBALL)
	{
	}
	else
	{
	}

    _currentMode=new_mode;
}

/*! Sets the motion factor
 */

void Navigator::setMotionFactor(Real32 new_factor)
{
    _rMotionFactor=new_factor;
}

/*! Sets the viewport
 */

void Navigator::setViewport(ViewportPtr new_viewport)
{
    _vp=new_viewport;
}

/*! Sets the from of the navigator (actually this is its center)
 */

void Navigator::setFrom(Pnt3f new_from)
{
    switch (_currentMode)
    {
        case TRACKBALL: { _trackball.setFrom(new_from); } break;
        
        case FLY:       { _flyer.setFrom(new_from);  } break;
    }
}

/*! Sets where the from is looking
 */

void Navigator::setAt(Pnt3f new_at)
{
    switch (_currentMode)
    {
        case TRACKBALL: { _trackball.setAt(new_at); } break;
        
        case FLY:       { _flyer.setAt(new_at);  } break;
    }
}

/*! Sets the distance from the from in the view direction
 */

void Navigator::setDistance(Real32 new_distance)
{
    switch (_currentMode)
    {
        case TRACKBALL: { _trackball.setDistance(new_distance); } break;
        
        case FLY:       { _flyer.forward(new_distance);  } break;
    }    
}


/*! Sets the up vector
 */

void Navigator::setUp(Vec3f new_up)
{
    switch (_currentMode)
    {
        case TRACKBALL: { _trackball.setUp(new_up); } break;
        
        case FLY:       { _flyer.setUp(new_up);  } break;
    }        
}

/*! Sets the 
 */

void Navigator::set(Pnt3f new_from, Pnt3f new_at, Vec3f new_up)
{
    switch (_currentMode)
    {
        case TRACKBALL: { _trackball.set(new_from, new_at, new_up); } break;
        
        case FLY:       { _flyer.set(new_from, new_at, new_up);  } break;
    }        
}

/*------------------------------ get --------------------------------------*/

/*! Gets the transformation matrix
 */

Matrix &Navigator::getMatrix()
{
    switch (_currentMode)
    {
        case TRACKBALL: return _trackball.getMatrix();
        case FLY:       return _flyer.getMatrix();
    }
    
    return _trackball.getMatrix();
}

/*! Gets the navigator's current state
 */

Navigator::State Navigator::getState()
{
    return _currentState;
}

/*! Gets the navigator's current mode
 */

Navigator::Mode Navigator::getMode()
{
    return _currentMode;
}

/*! sets the clickCenter current state
 */

bool Navigator::setClickCenter(bool state)
{   
    bool old = _clickCenter;
    
    _clickCenter = state;
    return old;
}

/*! Calculates the transformation matrix from CC to WC using actuall view
    matrix 
 */

static void calcCCtoWCMatrix(Matrix &cctowc, const Matrix &view, 
                             const ViewportPtr port)
{
    Matrix proj, projtrans;

    port->getCamera()->getProjection( proj, port->getPixelWidth(), 
                                            port->getPixelHeight());
    port->getCamera()->getProjectionTranslation( projtrans, 
                                                 port->getPixelWidth(), 
                                                 port->getPixelHeight());
    
    Matrix wctocc = proj;
    wctocc.mult( projtrans );
    wctocc.mult( view );
    
    cctowc.invertFrom( wctocc );
}

/*! Calculates the intesection point of a ray that starts at the from and goes
    through the position on the screen given by x,y with the world, if no
    intersection point exists the intersection is set to (0,0,0)
 */

void Navigator::getIntersectionPoint(Int16 x, Int16 y)
{
  	IntersectAction * act = IntersectAction::create();        
    Line line;
    _vp->getCamera()->calcViewRay(line,x,y, *_vp);
    
    act->setLine(line);
    act->apply(_vp->getRoot());    
    
    Matrix cctowc,view;
    Int16 width=_vp->getPixelWidth();
    Int16 height=_vp->getPixelHeight();
   
    _vp->getCamera()->getViewing(view, width, height);
    
    calcCCtoWCMatrix(cctowc, view, _vp);
                   
    Pnt3f at,to;
        
    cctowc.multFullMatrixPnt( Pnt3f( 0, 0, 0.5f ), to );            
    cctowc.multFullMatrixPnt( Pnt3f( 0, 0, 1 ), at );
        
    _dir=to-at;            
    
    if (act->didHit())
    {
        _ip=act->getHitPoint();
    }
    else
    {
        Real32 u=(_dir.dot(Pnt3f(0.0f,0.0f,0.0f)-line.getPosition())) /
                 (_dir.dot(line.getDirection()));
        _ip=line.getPosition() + u*line.getDirection();
    }    
}

/*! Calculate the real translation that have to be done, so that the
    trackball can actually drag the object in the plane parallel to the
    screen.
 */

void Navigator::calcDeltas(Int16 , Int16 , Int16 toX, Int16 toY, 
                                  Real32 &distanceX, Real32 &distanceY)
{        
    Matrix view;
       
    view=_trackball.getMatrix();
    
    Pnt3f from( view[3][0], view[3][1], view[3][2] );
        
    view.invert();
    Matrix cctowc;
    calcCCtoWCMatrix(cctowc, view, _vp);
    
    Real32  rx = ( toX / (Real32) _vp->getPixelWidth() ) * 2. - 1.,
            ry = 1.f - ( toY / (Real32) _vp->getPixelHeight() ) * 2.;
        
    Pnt3f at;
    cctowc.multFullMatrixPnt( Pnt3f( rx, ry, 1 ), at );    
        
    Line line2;
    line2.setValue(from, at-from);
          
    Real32 u=(_dir.dot(_ip-line2.getPosition())) /
             (_dir.dot(line2.getDirection()));
          
    Pnt3f p2=line2.getPosition() + u*line2.getDirection();
        
    Vec3f transl;
    transl[0]=-p2[0]+_ip[0];
    transl[1]=-p2[1]+_ip[1];
    transl[2]=-p2[2]+_ip[2];        

    view.multMatrixVec(transl);
     
    distanceX=transl[0];
    distanceY=transl[1];    
}
