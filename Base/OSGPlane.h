#ifndef OSGPLANE_CLASS_DECLARATION
#define OSGPLANE_CLASS_DECLARATION

#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>

#include "OSGVector.h"

OSG_BEGIN_NAMESPACE

class OSGLine;
class OSGMatrix;

#ifdef WIN32 // Workaround for a bug in Visual C++ 6.0
class OSGPlane;
bool operator ==(const OSGPlane &p1, const OSGPlane &p2);
bool operator !=(const OSGPlane &p1, const OSGPlane &p2);
#endif

/** Oriented plane in 3D space defined by normal and distance.

The plane is defined by a plane normal and a distance from the 
origin along that normal
OSGPlanes may be used to represent either planes or half-spaces. In
the latter case (as for the isInHalfSpace() method), the
half-space is defined to be all points on the plane or on the side
of the plane in the direction of the plane normal.

The 4 coefficients of the plane equation of an OSGPlane can be
obtained easily as the 3 coordinates of the plane normal and the
distance, in that order.

node: Plane is all p such that normalVec . p - distance = 0

@author jbehr, dorfmuel, Mon Dec 22 11:32:31 1997

*/

class OSGPlane {

	/// Normal to the plane
	OSGVec3f _normalVec;

	/// Distance from origin to plane: distance * normalVec is on the plane
	float _distance;

public:

	/// Default Constructor
	OSGPlane(void);

	/// Copy Constructor
	OSGPlane(const OSGPlane &obj);

	/**
	  Construct a plane given 3 points.
	  Orientation is computed by taking (p1 - p0) x (p2 - p0) and
	  pointing the normal in that direction.
	*/
	OSGPlane(const OSGVec3f &p0, const OSGVec3f &p1, const OSGVec3f &p2);

	/**
	  Construct a plane given normal and distance from origin along normal.
	  Orientation is given by the normal vector n.
	*/
	OSGPlane(const OSGVec3f &n, float d);

	/**
	  Construct a plane given normal and a point to pass through
	  Orientation is given by the normal vector n.
	*/
	OSGPlane(const OSGVec3f &n, const OSGVec3f &p);

	/// Offset a plane by a given distance.
	void offset(float d);

	/**
	  Intersect line and plane, returning true if there is an intersection
	  false if line is parallel to plane
	*/
	OSGBool intersect(const OSGLine &l, OSGVec3f &intersection) const;

	/// Transforms the plane by the given matrix
	void transform(const OSGMatrix &matrix);

	/**
	  Returns true if the given point is within the half-space
	  defined by the plane
	*/
	OSGBool isInHalfSpace(const OSGVec3f &point) const;

	/// set the plane param
	void set(const OSGVec3f &normal, float distance);

	/// Accessors for normal
	inline const OSGVec3f &getNormal(void) const { return _normalVec; }

	/// Accessors for distance
	inline float getDistanceFromOrigin(void) const { return _distance; }

	/// Equality comparison operators
	friend bool operator ==(const OSGPlane &p1, const OSGPlane &p2);

	/// Inequality comparison operators
	inline friend bool operator !=(const OSGPlane &p1, const OSGPlane &p2)
	{ return !(p1 == p2); }

};

OSG_END_NAMESPACE

#endif // OSGPLANE_CLASS_DECLARATION
