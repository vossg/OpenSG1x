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

#include <math.h>

#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <assert.h>

#define OSG_COMPILEBASE

#include "OSGLine.h"

OSG_USING_NAMESPACE

/**
  Construct a line from two points lying on the line.  If you
  want to construct a line from a position and a direction, use
  Line(p, p + d).
  Line is directed from p0 to p1.
*/
Line::Line(const Vec3f &p0, const Vec3f &p1)
{
	setValue(p0, p1);
}

/// Set that value!
void Line::setValue(const Vec3f &p0, const Vec3f &p1)
{
	_pos = p0;
	_dir = p1-p0;
	_dir.normalize();
}

/**
    Find closest points between the two lines. Return false if they are 
    parallel, otherwise return true.
*/
Bool Line::getClosestPoints(const Line &line2,
                                Vec3f &ptOnThis,
                                Vec3f &ptOnLine2 ) const
{
	// TODO
	assert(false);
	return false;
}

/// Returns the closest point on the line to the given point.
Vec3f Line::getClosestPoint(const Vec3f &point) const
{
	float cosAngle = 0.0;
	float alpha = 0.0;
	Vec3f vec(point - _pos);

	cosAngle = _dir.enclosedAngle(vec);

	alpha = cos(cosAngle) * vec.length();

	return (_pos + (_dir * alpha));

	// return (_pos + (_dir * (vec.dot(_dir))));
}

/// Intersect the line with a box, point, line, and triangle.
Bool Line::intersect(const BoxVolume &box, Vec3f &enter, Vec3f &exit) const
{
	// TODO
	assert(false);
	return false;
}

Bool Line::intersect(float angle, const BoxVolume &box) const
{
	// TODO
	assert(false);
	return false;
}

Bool Line::intersect(float angle, const Vec3f &point) const
{
	// TODO
	assert(false);
	return false;
}

Bool Line::intersect(float angle, const Vec3f &v0,
                 const Vec3f &v1, Vec3f &pt) const
{
	// TODO
	assert(false);
	return false;
}

Bool Line::intersect(const Vec3f &v0, const Vec3f &v1,
												 const Vec3f &v2, Vec3f &pt,
												 Vec3f &barycentric, Bool &front ) const
{
	// TODO
	assert(false);
	return false;
}
