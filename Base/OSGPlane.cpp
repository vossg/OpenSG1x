
#include "math.h"

#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <assert.h>

#include "OSGPlane.h"
#include "OSGLine.h"

OSG_USING_NAMESPACE

/// Default Constructor
OSGPlane::OSGPlane(void)
: _normalVec(0, 0, 0), _distance(0)
{}

/// Copy Constructor
OSGPlane::OSGPlane(const OSGPlane &obj)
: _normalVec(obj._normalVec), _distance(obj._distance)
{}

/**
  Construct a plane given 3 points.
  Orientation is computed by taking (p1 - p0) x (p2 - p0) and
  pointing the normal in that direction.
*/
OSGPlane::OSGPlane(const OSGVec3f &p0, const OSGVec3f &p1, const OSGVec3f &p2)
{
	OSGVec3f vec1(p1 - p0), vec2(p2 - p0);

	vec1.cross(vec2);
	_distance = fabs(vec1.dot(p0));

	_normalVec.setValues(vec1[0], vec1[1], vec1[2]);
}

/**
  Construct a plane given normal and distance from origin along normal.
  Orientation is given by the normal vector n.
*/
OSGPlane::OSGPlane(const OSGVec3f &normal, float distance)
: _normalVec(normal), _distance(distance)
{}

/**
  Construct a plane given normal and a point to pass through
  Orientation is given by the normal vector n.
*/
OSGPlane::OSGPlane(const OSGVec3f &normal, const OSGVec3f &point)
: _normalVec(normal)
{
	_distance = fabs(normal.dot(point));
}

/// Offset a plane by a given distance.
void OSGPlane::offset(float d)
{
	_distance += d;
}

/**
  Intersect line and plane, returning true if there is an intersection
  false if line is parallel to plane
*/
OSGBool OSGPlane::intersect(const OSGLine &line, OSGVec3f &point) const
{
	bool retCode = false;
	
	float condition = _normalVec.dot(line.getDirection());
	
	if (condition != 0.0){
		point = (_normalVec.dot((_normalVec * _distance) - line.getPosition()) /
						 _normalVec.dot(line.getDirection()))
			* line.getDirection() + line.getPosition();
		retCode = true;
	}
	else {
		if (_normalVec.dot(line.getPosition()) == 0){
			point = line.getPosition();
			retCode = true;
		}
		else 
			retCode = false;
	}
	return retCode;
}

/// Transforms the plane by the given matrix
void OSGPlane::transform(const OSGMatrix &/*matrix*/)
{
	// TODO
	assert(false);
}

/// set the plane param
void OSGPlane::set(const OSGVec3f &normal, float distance)
{
	_normalVec = normal;
	_distance = distance;
	if (_distance < 0) {
		_distance *= -1;
		_normalVec.negate();
	}
}

/**
  Returns true if the given point is within the half-space
  defined by the plane
*/
OSGBool OSGPlane::isInHalfSpace( const OSGVec3f &point ) const
{
	float scalar = _normalVec.dot(point - _normalVec * _distance);

	return scalar >= 0 ? true : false;
}

OSG_BEGIN_NAMESPACE

/// Equality comparison operators
bool operator ==(const OSGPlane &p1, const OSGPlane &p2)
{
	return ((p1._distance == p2._distance) &&
	        (p1._normalVec == p2._normalVec));
}

OSG_END_NAMESPACE
