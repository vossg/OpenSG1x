
#include <math.h>

#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <assert.h>

#include "OSGLine.h"

OSG_USING_NAMESPACE

/**
  Construct a line from two points lying on the line.  If you
  want to construct a line from a position and a direction, use
  OSGLine(p, p + d).
  Line is directed from p0 to p1.
*/
OSGLine::OSGLine(const OSGVec3f &p0, const OSGVec3f &p1)
{
	setValue(p0, p1);
}

/// Set that value!
void OSGLine::setValue(const OSGVec3f &p0, const OSGVec3f &p1)
{
	_pos = p0;
	_dir = p1-p0;
	_dir.normalize();
}

/**
    Find closest points between the two lines. Return false if they are 
    parallel, otherwise return true.
*/
OSGBool OSGLine::getClosestPoints(const OSGLine &line2,
                                OSGVec3f &ptOnThis,
                                OSGVec3f &ptOnLine2 ) const
{
	// TODO
	assert(false);
	return false;
}

/// Returns the closest point on the line to the given point.
OSGVec3f OSGLine::getClosestPoint(const OSGVec3f &point) const
{
	float cosAngle = 0.0;
	float alpha = 0.0;
	OSGVec3f vec(point - _pos);

	cosAngle = _dir.enclosedAngle(vec);

	alpha = cos(cosAngle) * vec.length();

	return (_pos + (_dir * alpha));

	// return (_pos + (_dir * (vec.dot(_dir))));
}

/// Intersect the line with a box, point, line, and triangle.
OSGBool OSGLine::intersect(const OSGBoxVolume &box, OSGVec3f &enter, OSGVec3f &exit) const
{
	// TODO
	assert(false);
	return false;
}

OSGBool OSGLine::intersect(float angle, const OSGBoxVolume &box) const
{
	// TODO
	assert(false);
	return false;
}

OSGBool OSGLine::intersect(float angle, const OSGVec3f &point) const
{
	// TODO
	assert(false);
	return false;
}

OSGBool OSGLine::intersect(float angle, const OSGVec3f &v0,
                 const OSGVec3f &v1, OSGVec3f &pt) const
{
	// TODO
	assert(false);
	return false;
}

OSGBool OSGLine::intersect(const OSGVec3f &v0, const OSGVec3f &v1,
												 const OSGVec3f &v2, OSGVec3f &pt,
												 OSGVec3f &barycentric, OSGBool &front ) const
{
	// TODO
	assert(false);
	return false;
}
