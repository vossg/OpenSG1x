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

#include "math.h"

#include "OSGConfig.h"

#include <assert.h>

#include "OSGPlane.h"
#include "OSGLine.h"

OSG_USING_NAMESPACE

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

/// Default Constructor
Plane::Plane(void)
: _normalVec(0, 0, 0), _distance(0)
{}

/// Copy Constructor
Plane::Plane(const Plane &obj)
: _normalVec(obj._normalVec), _distance(obj._distance)
{}

/**
  Construct a plane given 3 points.
  Orientation is computed by taking (p1 - p0) x (p2 - p0) and
  pointing the normal in that direction.
*/
Plane::Plane(const Pnt3f &p0, const Pnt3f &p1, const Pnt3f &p2)
{
    Vec3f vec1(p1 - p0), vec2(p2 - p0);

    vec1.crossThis(vec2);
    _distance = vec1.dot(p0);

    _normalVec.setValues(vec1[0], vec1[1], vec1[2]);
    _normalVec.normalize();
}

/**
  Construct a plane given normal and distance from origin along normal.
  Orientation is given by the normal vector n.
*/
Plane::Plane(const Vec3f &normal, Real32 distance)
: _normalVec(normal), _distance(distance)
{
    _normalVec.normalize();
}

/**
  Construct a plane given normal and a point to pass through
  Orientation is given by the normal vector n.
*/
Plane::Plane(const Vec3f &normal, const Pnt3f &point)
: _normalVec(normal)
{
    _normalVec.normalize();
    _distance = _normalVec.dot(point);
}

/// Offset a plane by a given distance.
void Plane::offset(Real32 d)
{
    _distance += d;
}

/*-------------------------- intersection ---------------------------------*/

/**
  Intersect plane and plane, returning true if there is an intersection
  false if planes are parallel
  taken from Steve Baker's SG library, used with permission. Algorithm
  explanation can be found at 
  http://geometryalgorithms.com/Archive/algorithm_0104/algorithm_0104.htm
*/
Bool Plane::intersect(const Plane &pl, Line &is) const
{
    Vec3f dir = _normalVec.cross( pl.getNormal() );
    Pnt3f pnt;

    Real32 len = dir.length();

    if ( len < Eps ) return false;

    /* Determine intersection point with the best suited coordinate plane. */

    Real32 abs ;
    Real32 maxabs = osgabs(dir[0]);
    UInt16 index = 0;

    if (( abs = osgabs(dir[1])) > maxabs) { maxabs = abs ; index = 1; }
    if (( abs = osgabs(dir[2])) > maxabs) { maxabs = abs ; index = 2; }

    switch ( index )
    {
    case 0: pnt.setValues(  0.f,
                            (pl.getNormal()[2] * _distance - 
                             _normalVec[2] * pl.getDistanceFromOrigin()
                             ) / dir[0],
                            (_normalVec[1] * pl.getDistanceFromOrigin() -
                             pl.getNormal()[1] * _distance
                            ) / dir[0]
                        );
            break;
    case 1: pnt.setValues(   (_normalVec[2] * pl.getDistanceFromOrigin() -
                              pl.getNormal()[2] * _distance
                             ) / dir[1],
                             0.f,
                             (pl.getNormal()[0] * _distance -
                              _normalVec[0] * pl.getDistanceFromOrigin()
                             ) / dir[1]
                        );
            break;
    case 2: pnt.setValues(   (pl.getNormal()[1] * _distance -
                              _normalVec[1] * pl.getDistanceFromOrigin()
                             ) / dir[2],
                             (_normalVec[0] * pl.getDistanceFromOrigin() -
                              pl.getNormal()[0] * _distance
                             ) / dir[2],
                             0.f
                        );
            break;
    default: return false ;  /* Impossible */
    }

    /* Normalize the direction */

    dir *= 1./len;

    is.setValue( pnt, dir );
    return true;
}

/**
  Intersect line and plane, returning true if there is an intersection
  in the positive part of the line
  false if line is parallel to plane
*/
Bool Plane::intersect(const Line &line, Pnt3f &point) const
{
    Real32 t;

    if ( intersect( line, t ) )
    {
        point = line.getPosition() + t * line.getDirection();
        return true;
    }
    else
        return false;
}

/**
  Intersect line and plane, returning true if there is an intersection
  false if line is parallel to plane. t is the distance along the line.
*/
Bool Plane::intersect(const Line &line, Real32 &t) const
{
    if ( intersectInfinite(line,t) == false || t < 0 )
        return false;

    return true;
}

/**
  Intersect line and plane, returning true if there is an intersection
  false if line is parallel to plane
*/
Bool Plane::intersectInfinite(const Line &line, Pnt3f &point) const
{
    Real32 t;

    if ( intersectInfinite( line, t ) )
    {
        point = line.getPosition() + t * line.getDirection();
        return true;
    }
    else
        return false;
}

/**
  Intersect line and plane, returning true if there is an intersection
  false if line is parallel to plane. t is the distance along
  the line, which may be negative, i.e. the check is against a double
  infinite line. 
*/
Bool Plane::intersectInfinite(const Line &line, Real32 &t) const
{
    Real32 a;

    if ( ( a = _normalVec.dot(line.getDirection()) ) != 0.0)
    {
        t = _normalVec.dot(Pnt3f(_normalVec * _distance) -  line.getPosition()
                          ) / a;

        return true;
    }
    else
    {
        if ( _normalVec.dot(line.getPosition()) - _distance == 0)
        {
            t = 0;
            return true;
        }
    }
    return false;
}

/// Transforms the plane by the given matrix
void Plane::transform(const Matrix &matrix)
{
    // TODO
//  assert(false);

    matrix.mult(_normalVec);
    _normalVec.normalize();

    Vec3f trans;

    trans[0] = matrix[3][0];
    trans[1] = matrix[3][1];
    trans[2] = matrix[3][2];

    trans.projectTo(_normalVec);

    UInt32 uiValNorm  = getMaxIndexAbs3(_normalVec);
    UInt32 uiValPoint = getMaxIndexAbs3( trans);

    if(trans[uiValPoint] >  Eps ||
       trans[uiValPoint] < -Eps)
    {
        if((_normalVec[uiValNorm ] < 0. &&
             trans    [uiValPoint] < 0. ) ||
           (_normalVec[uiValNorm ] > 0. &&
             trans    [uiValPoint] > 0. ))
        {
            _distance -= trans.length();
        }
        else
        {
            _distance += trans.length();
        }

    }
}

/*! Returns true if the given point is within the half-space
    defined by the plane
*/
Bool Plane::isInHalfSpace(const Pnt3f &point) const
{
    Real32 scalar = _normalVec.dot(point) - _distance;

    return scalar <= 0 ? true : false;
}

/**
  Returns true if the given point is on the plane
*/
Bool Plane::isOnPlane(const Pnt3f &point) const
{
    Real32 scalar = _normalVec.dot(point) - _distance;

    return osgabs(scalar) < Eps ? true : false;
}

OSG_BEGIN_NAMESPACE

/// Equality comparison operators
OSG_BASE_DLLMAPPING
Bool operator ==(const Plane &p1, const Plane &p2)
{
    return ((p1._distance == p2._distance) &&
             (p1._normalVec == p2._normalVec));
}

OSG_END_NAMESPACE

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

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/
