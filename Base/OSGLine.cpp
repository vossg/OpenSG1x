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

#include <math.h>

#include "OSGConfig.h"

#include <assert.h>

#include "OSGLine.h"
#include "OSGPlane.h"
#include "OSGBoxVolume.h"
#include "OSGSphereVolume.h"
#include "OSGCylinderVolume.h"

OSG_USING_NAMESPACE

/*! \class osg::Line
    A line starting at a point p and extending infinitely far into the direction d.
    This will probably split up into multiple classes for dual-inifinite and non-
    infinite lines
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*-------------------------- constructor ----------------------------------*/

Line::Line(const Pnt3f &p0, const Pnt3f &p1)
{
    setValue(p0, p1);
}

Line::Line(const Pnt3f &pos, const Vec3f &dir)
{
    setValue(pos, dir);
}

Line::Line( void ) : _pos(0,0,0), _dir(0,0,0)
{}

Line::Line( const Line &obj ) : _pos(obj._pos), _dir(obj._dir)
{}


/*------------------------------ feature ----------------------------------*/

/** Set that value!
*/
void Line::setValue(const Pnt3f &p0, const Pnt3f &p1)
{
    _pos = p0;
    _dir = p1-p0;
    _dir.normalize();
}

/** Set that value!
*/
void Line::setValue(const Pnt3f &pos, const Vec3f &dir)
{
    _pos = pos;
    _dir = dir;
    _dir.normalize();
}

/** Find closest points between the two lines. Return false if they are
    parallel, otherwise return true.
*/
Bool Line::getClosestPoints(const Line &line2,
                                Pnt3f &ptOnThis,
                                Pnt3f &ptOnLine2 ) const
{
    // TODO
    assert(false);
    return false;
}

/** Returns the closest point on the line to the given point.
*/
Pnt3f Line::getClosestPoint(const Pnt3f &point) const
{
    Vec3f vec(point - _pos);

    return _pos + _dir * vec.dot(_dir);
}


/** Returns the distance of the given point to the line.
*/
Real32 Line::distance(const Pnt3f &point) const
{
    return ( point - getClosestPoint( point ) ).length();
}


/*-------------------------- intersection ---------------------------------*/

/** Intersect the Line with a Sphere
*/
Bool Line::intersect(const SphereVolume &sphere) const
{
    Real32 ent, ex;
    return this->intersect( sphere, ent, ex);
}

/** Intersect the line with a sphere, returns points of intersection
*/
Bool Line::intersect(const SphereVolume &sphere,
                     Real32& enter, Real32& exit) const
{

    Vec3f v;
    Pnt3f center;

    sphere.getCenter(center);

    Real32 radius, h, b, d, t1, t2;

    radius = sphere.getRadius();

    v = center - _pos;

    h = (v.dot(v))-radius;
    b = (v.dot(_dir));

    if (h >= 0 && b <= 0)
        return false;

    d = b * b - h;

    if (d < 0)
        return false;

    d = sqrt(d);
    t1 = b - d;

//    if (t1 > 1)
//        return false;

    t2 = b + d;

    if ( t1 < Eps )
    {
        if ( t2 < Eps /*|| t2 > 1*/ )
        {
            return false;
        }
    }
    enter = t1;
    exit = t2;
    return true;
}


/**Intersect the line with a cylinder
*/
Bool Line::intersect(const CylinderVolume &cyl) const
{
    Real32 ent, ex;
    return this->intersect(cyl, ent, ex);
}


/**Intersect the line with a cylinder, returns points of intersection
  based on GGems IV
*/
Bool Line::intersect(const CylinderVolume &cyl, Real32 &enter, Real32 &exit) const
{
    Real32 radius = cyl.getRadius();

    Vec3f adir, o_adir;
    Pnt3f apos;
    cyl.getAxis(apos, adir);

    o_adir = adir;
    adir.normalize();

    Bool isect;

    Real32 ln, dl;
    Vec3f RC, n, D;

    RC = _pos - apos;

    n = _dir.cross(adir);
    ln = n.length();
    if (ln == 0)    // IntersectionLine is parallel to CylinderAxis
    {
        D = RC - ( RC.dot(adir) ) * adir;
        dl = D.length();

        if (dl <= radius)   // line lies in cylinder
        {
            enter = 0;
            exit = Inf;
        }
        else
            return false;
    }
    else
    {
        n.normalize();
        dl = osgabs (RC.dot(n));        //shortest distance
        isect = (dl <= radius);

        if (isect){                 // if ray hits cylinder

            float t, s;
            Vec3f O;

            O = RC.cross(adir);
            t = - (O.dot(n)) / ln;
            O = n.cross(adir);
            O.normalize();
            s = osgabs (
                (sqrt ((radius * radius) - (dl * dl))) / (_dir.dot(O)));

            exit = t + s;
            if ( exit < 0 )
                return false;

            enter = t - s;
            if ( enter < 0 )
                enter = 0;
        }
        else
            return false;
    }

    Real32 t;

    Plane bottom( -adir, apos );
    if ( bottom.intersect( *this, t ) )
    {
        if ( bottom.isInHalfSpace( _pos ) )
        {
            if ( t > enter ) enter = t;
        }
        else
        {
            if ( t < exit ) exit = t;
        }
    }

    Plane top( adir, apos + o_adir );
    if ( top.intersect( *this, t ) )
    {
        if ( top.isInHalfSpace( _pos ) )
        {
            if ( t > enter ) enter = t;
        }
        else
        {
            if ( t < exit ) exit = t;
        }
    }

    return (enter < exit);
}

/**Intersect the line with a frustum
*/
Bool Line::intersect(const FrustumVolume &cyl) const
{
    Real32 ent, ex;
    return this->intersect(cyl, ent, ex);
}


/**Intersect the line with a frustum, returns points of intersection
  based on GGems IV
*/
Bool Line::intersect(const FrustumVolume &cyl, Real32 &enter, Real32 &exit) const
{
    // not implemented;
    return false;
}

/**Intersect the line with a box, returns points of intersection
*/
Bool Line::intersect(const BoxVolume &box,
                     Real32 &enter, Real32 &exit) const
{
    Pnt3f low, high;
    box.getBounds( low, high );

    float r, te, tl;
    Real32 in = 0, out = Inf;

    if ( _dir[0] > Eps || _dir[0] < -Eps )
    {
        r=1.f/_dir[0];

        if ( _dir[0] > 0 )
        {
            te=( low [0] - _pos[0] ) * r;
            tl=( high[0] - _pos[0] ) * r;
        }
        else
        {
            te=( high[0] - _pos[0] ) * r;
            tl=( low [0] - _pos[0] ) * r;
        }

//        if (te > 1)   return false;

        if (tl < out)   out = tl;
        if (te > in)    in = te;
    }
    else if ( _pos[0] < low[0] || _pos[0] > high[0] )
        return false;


    if ( _dir[1] > Eps || _dir[1] < -Eps )
    {
        r=1.f/_dir[1];

        if ( _dir[1] > 0 )
        {
            te=( low [1] - _pos[1] ) * r;
            tl=( high[1] - _pos[1] ) * r;
        }
        else
        {
            te=( high[1] - _pos[1] ) * r;
            tl=( low [1] - _pos[1] ) * r;
        }

//      if (te > 1)   return false;

        if (tl < out)   out = tl;
        if (te > in)    in = te;
    }
    else if ( _pos[1] < low[1] || _pos[1] > high[1] )
        return false;


    if ( _dir[2] > Eps || _dir[2] < -Eps )
    {
        r=1.f/_dir[2];

        if ( _dir[2] > 0 )
        {
            te=( low [2] - _pos[2] ) * r;
            tl=( high[2] - _pos[2] ) * r;
        }
        else
        {
            te=( high[2] - _pos[2] ) * r;
            tl=( low [2] - _pos[2] ) * r;
        }

//        if (te > 1)   return false;

        if (tl < out)   out = tl;
        if (te > in)    in = te;
    }
    else if ( _pos[2] < low[2] || _pos[2] > high[2] )
        return false;

    enter = in;
    exit = out;

    return true;
}


/**Intersect the line with a box.
*/
Bool Line::intersect(float angle, const BoxVolume &box) const
{
    // TODO
    assert(false);
    return false;
}

/** Intersect the line with a point.
*/
Bool Line::intersect(float angle, const Vec3f &point) const
{
    // TODO
    assert(false);
    return false;
}

/** Intersect the line with a line.
*/
Bool Line::intersect(float angle, const Vec3f &v0,
                 const Vec3f &v1, Vec3f &pt) const
{
    // TODO
    assert(false);
    return false;
}

/** Intersect the line with a triangle.
*/
Bool Line::intersect(   const Pnt3f &v0, const Pnt3f &v1,
                        const Pnt3f &v2, Real32 &t ) const
{
    Vec3f dir1, dir2;

    dir1 = v1 - v0;
    dir2 = v2 - v0;

    Vec3f a = _dir.cross( dir2 );
    Vec3f b = _pos - v0;
    Vec3f c;

    Real32  d = dir1.dot( a ),
            u =    b.dot( a ),
            v;

    if ( d > Eps )
    {
        if ( u < 0 || u > d )
            return false;

        c = b.cross( dir1 );
        v = _dir.dot( c );
        if ( v < 0 || u + v > d )
            return false;
    }
    else if ( d < -Eps )
    {
        if ( u > 0 || u < d )
            return false;

        c = b.cross( dir1 );
        v = _dir.dot( c );
        if ( v > 0 || u + v < d )
            return false;
    }
    else
        return false;

    Real32 id = 1.f / d;

    t = dir2.dot( c ) * id;

    return true;
}


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
