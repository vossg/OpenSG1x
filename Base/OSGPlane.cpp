/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <assert.h>

#define OSG_COMPILEBASE

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
Plane::Plane(const Vec3f &normal, float distance)
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
void Plane::offset(float d)
{
	_distance += d;
}


/*-------------------------- intersection ---------------------------------*/

/**
  Intersect line and plane, returning true if there is an intersection
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
	Real32 a;
	
	if ( ( a = _normalVec.dot(line.getDirection()) ) != 0.0)
	{
		t = _normalVec.dot(Pnt3f(_normalVec * _distance) -  line.getPosition()
						  ) / a;
		
		if ( t >= 0 )				
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
//	assert(false);

    matrix.transform(_normalVec);
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

/// set the plane param
void Plane::set(const Vec3f &normal, float distance)
{
	_normalVec = normal;
	_distance = distance;
}

/**
  Returns true if the given point is within the half-space
  defined by the plane
*/
Bool Plane::isInHalfSpace( const Pnt3f &point ) const
{
	float scalar = _normalVec.dot(point) - _distance;

	return scalar >= 0 ? true : false;
}


/**
  Returns true if the given point is on the plane
*/
Bool Plane::isOnPlane(const Pnt3f &point) const
{
	float scalar = _normalVec.dot(point) - _distance;

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
