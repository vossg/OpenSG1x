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

#ifndef OSGLINE_CLASS_DECLARATION
#define OSGLINE_CLASS_DECLARATION


#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>
#include "OSGVector.h"

OSG_BEGIN_NAMESPACE

class OSG_DLLEXPORT BoxVolume;

/** Directed line in 3D space defined by pos and dir.

Parametric description: l(t) = pos + t * dir

@author jbehr, dorfmuel, Mon Dec 22 11:32:31 1997

*/

class Line {

	/// Position
	Vec3f	_pos;

	/// Direction
	Vec3f	_dir;

public:

	/// Default Constructor
	Line(void) : _pos(0,0,0), _dir(0,0,0) {}

	/// Copy Constructor
	Line(const Line &obj) : _pos(obj._pos), _dir(obj._dir) {}

	/**
	  Construct a line from two points lying on the line.  If you
	  want to construct a line from a position and a direction, use
	  Line(p, p + d).
	  Line is directed from p0 to p1.
	*/
	Line(const Vec3f &p0, const Vec3f &p1);

	/// Set that value!
	void setValue(const Vec3f &p0, const Vec3f &p1);

	/**
	  Find closest points between the two lines. Return false if they are 
	  parallel, otherwise return true.
	*/
	Bool getClosestPoints(const Line &line2,
	                        Vec3f &ptOnThis,
	                        Vec3f &ptOnLine2) const;

	/// Returns the closest point on the line to the given point.
	Vec3f getClosestPoint(const Vec3f &point) const;

	/// Accessors for position
	inline const Vec3f &getPosition(void) const { return _pos; }

	/// Accessors for direction
	inline const Vec3f &getDirection(void) const { return _dir; }

	/// Intersect the line with a box, point, line, and triangle.
	Bool intersect(const BoxVolume &box,
	                 Vec3f &enter, Vec3f &exit) const;
	Bool intersect(float angle, const BoxVolume &box) const;
	Bool intersect(float angle, const Vec3f &point) const;
	Bool intersect(float angle, const Vec3f &v0,
	                 const Vec3f &v1, Vec3f &pt) const;
	Bool intersect(const Vec3f &v0, const Vec3f &v1,
	                 const Vec3f &v2, Vec3f &pt,
	                 Vec3f &barycentric, Bool &front ) const;

};

OSG_END_NAMESPACE

#endif // OSGLINE_CLASS_DECLARATION
