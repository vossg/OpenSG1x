#ifndef OSGLINE_CLASS_DECLARATION
#define OSGLINE_CLASS_DECLARATION


#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>
#include "OSGVector.h"

OSG_BEGIN_NAMESPACE

class OSGBoxVolume;

/** Directed line in 3D space defined by pos and dir.

Parametric description: l(t) = pos + t * dir

@author jbehr, dorfmuel, Mon Dec 22 11:32:31 1997

*/

class OSGLine {

	/// Position
	OSGVec3f	_pos;

	/// Direction
	OSGVec3f	_dir;

public:

	/// Default Constructor
	OSGLine(void) : _pos(0,0,0), _dir(0,0,0) {}

	/// Copy Constructor
	OSGLine(const OSGLine &obj) : _pos(obj._pos), _dir(obj._dir) {}

	/**
	  Construct a line from two points lying on the line.  If you
	  want to construct a line from a position and a direction, use
	  OSGLine(p, p + d).
	  Line is directed from p0 to p1.
	*/
	OSGLine(const OSGVec3f &p0, const OSGVec3f &p1);

	/// Set that value!
	void setValue(const OSGVec3f &p0, const OSGVec3f &p1);

	/**
	  Find closest points between the two lines. Return false if they are 
	  parallel, otherwise return true.
	*/
	OSGBool getClosestPoints(const OSGLine &line2,
	                        OSGVec3f &ptOnThis,
	                        OSGVec3f &ptOnLine2) const;

	/// Returns the closest point on the line to the given point.
	OSGVec3f getClosestPoint(const OSGVec3f &point) const;

	/// Accessors for position
	inline const OSGVec3f &getPosition(void) const { return _pos; }

	/// Accessors for direction
	inline const OSGVec3f &getDirection(void) const { return _dir; }

	/// Intersect the line with a box, point, line, and triangle.
	OSGBool intersect(const OSGBoxVolume &box,
	                 OSGVec3f &enter, OSGVec3f &exit) const;
	OSGBool intersect(float angle, const OSGBoxVolume &box) const;
	OSGBool intersect(float angle, const OSGVec3f &point) const;
	OSGBool intersect(float angle, const OSGVec3f &v0,
	                 const OSGVec3f &v1, OSGVec3f &pt) const;
	OSGBool intersect(const OSGVec3f &v0, const OSGVec3f &v1,
	                 const OSGVec3f &v2, OSGVec3f &pt,
	                 OSGVec3f &barycentric, OSGBool &front ) const;

};

OSG_END_NAMESPACE

#endif // OSGLINE_CLASS_DECLARATION
