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
    _groundDistance(0.75),
    _wallDistance(0.0),
    _height(0.85),
    _width(0.5),
    _fatness(0.5)
{
    _act = IntersectAction::create();
}

/*-------------------------- destructors ----------------------------------*/

/*! Destructor
 */

WalkNavigator::~WalkNavigator()
{
    delete _act;
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
    Vec3f lv = _rFrom - _rAt;
    lv.normalize();

    Vec3f upn = _vUp;
    upn.normalize();

    Vec3f mv = lv - upn.dot(lv)*upn;
    mv.normalize();

    Vec3f sv = mv;
    sv.crossThis(upn);
    sv.normalize();

    Pnt3f rFrom = _rFrom + step*mv;
    Pnt3f rAt = _rAt + step*mv;

    Line line(rFrom, -upn);
    Real32 dist;

    //keep the walker at a constant distance from the ground
    _act->setLine(line);
    _act->apply(_ground);

    if (_act->didHit()) {
        dist = _act->getHitT();
        if (dist >= _height) {
            rFrom = rFrom + (_groundDistance-dist+_height)*upn;
            rAt = rAt + (_groundDistance-dist+_height)*upn;
        }
        else return;    //can't jump so high
    }

    //check whether the move is correct
    line.setValue(_rFrom, mv);
    _act->setLine(line);
    _act->apply(_world);

    if (_act->didHit()) {
        dist = _act->getHitT();
        if (dist <= step+_fatness/2+_wallDistance)
            return;     //running against a wall
    }

    line.setValue(rFrom-mv*(_fatness/2+_wallDistance)-sv*(_width/2+_wallDistance), mv);
    _act->setLine(line);
    _act->apply(_world);

    if (_act->didHit()) {
        dist = _act->getHitT();
        if (dist <= _fatness + _wallDistance)
            return;     //too fat
    }

    line.setValue(rFrom-mv*(_fatness/2+_wallDistance)+sv*(_width/2+_wallDistance), mv);
    _act->setLine(line);
    _act->apply(_world);

    if (_act->didHit()) {
        dist = _act->getHitT();
        if (dist <= _fatness + _wallDistance)
            return;     //too fat
    }

    //move was ok, store new values
    _rFrom = rFrom;
    _rAt = rAt;
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

    Pnt3f old_rFrom = _rFrom;
    Pnt3f old_rAt   = _rAt;

    transl.multMatrixPnt(_rAt);
    transl.multMatrixPnt(_rFrom);

    Line line;

    //keep the walker at a constant distance from the ground
    line.setValue(_rFrom,-_vUp);
    _act->setLine(line);
    _act->apply(_ground);
    if (_act->didHit())
    {
        Pnt3f p1=_act->getHitPoint();
        Real32 dist=_rFrom.dist(p1);
        upn=_vUp;
        upn.normalize();
        _rFrom = _rFrom+(_groundDistance-dist+_height)*upn;
        _rAt   = _rAt+(_groundDistance-dist+_height)*upn;
    }


    //check whether the move is correct
    Vec3f mv;
    mv=lv-upn.dot(lv)*upn;
    mv.normalize();
    sv.normalize();

    line.setValue(_rFrom-mv*(_fatness/2+_wallDistance)+sv*(_width/2+_wallDistance),mv);
    _act->setLine(line,_fatness + 2*_wallDistance);
    _act->apply(_world);

    if (_act->didHit())
    {
        Pnt3f p1=_act->getHitPoint();
        Real32 dist=(_rFrom-mv*(_fatness/2+_wallDistance)+sv*(_width/2+_wallDistance)).dist(p1);
        if (dist<=_fatness + 2*_wallDistance)
        {
            _rFrom = old_rFrom;
            _rAt   = old_rAt;
            //printf("didhit:right, side line\n");
            return;
        }
    }


    line.setValue(_rFrom+mv*(_fatness/2+_wallDistance)-sv*(_width/2+_wallDistance),sv);
    _act->setLine(line,_width + 2*_wallDistance);
    _act->apply(_world);

    if (_act->didHit())
    {
        Pnt3f p1=_act->getHitPoint();
        Real32 dist=(_rFrom+mv*(_fatness/2+_wallDistance)-sv*(_width/2+_wallDistance)).dist(p1);
        if (dist<=_width + 2*_wallDistance)
        {
            _rFrom = old_rFrom;
            _rAt   = old_rAt;
            //printf("didhit:right, top line\n");
            return;
        }
    }

    line.setValue(_rFrom-mv*(_fatness/2+_wallDistance)-sv*(_width/2+_wallDistance),sv);
    _act->setLine(line,_width + 2*_wallDistance);
    _act->apply(_world);

    if (_act->didHit())
    {
        Pnt3f p1=_act->getHitPoint();
        Real32 dist=(_rFrom-mv*(_fatness/2+_wallDistance)-sv*(_width/2+_wallDistance)).dist(p1);
        if (dist<=_width + 2*_wallDistance)
        {
            _rFrom = old_rFrom;
            _rAt   = old_rAt;
            //printf("didhit:right, bottom line\n");
            return;
        }
    }

    //at the end we don't want to go through walls
    //for example: i am very small, the step is very big
    //thus we check whether the line connecting my current
    //position and my old position intersects something

    line.setValue(old_rFrom,_rFrom - old_rFrom);
    _act->setLine(line/*,_rFrom.dist(old_rFrom)*/);
    _act->apply(_world);

    if (_act->didHit())
    {
        Pnt3f p1=_act->getHitPoint();
        Real32 dist=old_rFrom.dist(p1);
        if (dist<=_rFrom.dist(old_rFrom))
        {
            _rFrom = old_rFrom;
            _rAt   = old_rAt;
            //printf("didhit:right, wall between positions\n");
            return;
        }
    }

}
