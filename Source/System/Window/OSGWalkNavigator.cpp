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

#include "OSGWalkNavigator.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::WalkNavigator
    \ingroup GrpSystemWindowNavigators


*/

/*------------------------- constructors ----------------------------------*/

/*! Constructor
 */

WalkNavigator::WalkNavigator(): FlyNavigator(),
    _ground(NullFC),
    _world(NullFC),
    _groundDistance(0.1),
    _wallDistance(0.1),
    _height(1),
    _width(0.1),
    _fatness(0.1)
{
}

/*-------------------------- destructors ----------------------------------*/

/*! Destructor
 */

WalkNavigator::~WalkNavigator()
{
}


/*------------------------------ get --------------------------------------*/




/*------------------------------ set --------------------------------------*/


void WalkNavigator::setGround(NodePtr &new_ground)
{
    _ground=new_ground;
}

void WalkNavigator::setWorld(NodePtr &new_world)
{
    _world=new_world;
}

void WalkNavigator::setGroundDistance(Real32 groundDistance)
{
    _groundDistance=groundDistance;
}

void WalkNavigator::setMinWallDistance (Real32 wallDistance)
{
    _wallDistance=wallDistance;
}
    
void WalkNavigator::setPersonDimensions(Real32 height,Real32 width,Real32 fatness)
{
    _height  = height;
    _width   = width;
    _fatness = fatness;
}

/*---------------------- Flyer Transformations ----------------------------*/

/*! makes a rotation
 */

void WalkNavigator::rotate (Real32 deltaX, Real32 deltaY)
{
    FlyNavigator::rotate(deltaX,deltaY);
}
   
/*! "walks" forward
 */

void WalkNavigator::forward(Real32 step)
{
    Vec3f lv;
    lv=_rFrom-_rAt;
    lv.normalize();
    Vec3f upn=_vUp;
    upn.normalize();
    
    Vec3f mv;
    mv=lv-upn.dot(lv)*upn;
    mv.normalize();
   
    mv*=(step);
    Matrix transl;
    transl.setIdentity();
    transl.setTranslate(mv);
    transl.multMatrixPnt(_rAt);
    transl.multMatrixPnt(_rFrom);
    
    IntersectAction *act=IntersectAction::create();
    Line line;
    line.setValue(_rFrom,-_vUp);
    
    act->setLine(line);
    act->apply(_ground);
    if (act->didHit())
    {
        Pnt3f p1=act->getHitPoint();
        Real32 dist=_rFrom.dist(p1);
        upn=_vUp;
        upn.normalize();
        _rFrom = _rFrom+(_groundDistance-dist+_height)*upn;
        _rAt   = _rAt+(_groundDistance-dist+_height)*upn;            
    }    
}
    
/*! "walks" on the right
 */

void WalkNavigator::right  (Real32 step)
{
    Vec3f lv;
    lv=_rFrom-_rAt;
    lv.normalize();
    Vec3f upn=_vUp;
    upn.normalize();
    
    Vec3f sv;
    sv=lv-upn.dot(lv)*upn;
    sv.crossThis(_vUp);
    sv.normalize();
    sv*=(step);
    Matrix transl;
    transl.setIdentity();
    transl.setTranslate(sv);
    transl.multMatrixPnt(_rAt);
    transl.multMatrixPnt(_rFrom);
    
    IntersectAction *act=IntersectAction::create();
    Line line;
    line.setValue(_rFrom,-_vUp);
    
    act->setLine(line);
    act->apply(_ground);
    if (act->didHit())
    {
        Pnt3f p1=act->getHitPoint();
        Real32 dist=_rFrom.dist(p1);
        upn=_vUp;
        upn.normalize();
        _rFrom = _rFrom+(_groundDistance-dist+_height)*upn;
        _rAt   = _rAt+(_groundDistance-dist+_height)*upn;            
    }    
}
