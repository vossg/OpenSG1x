
// System declarations

#ifdef WIN32
//#include <iosfwd>
#endif

#include "OSGConfig.h"

#include <OSGLog.h>  

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <assert.h>

#include <OSGLine.h>
#include <OSGMatrix.h>

#ifdef WIN32
#define MAXFLOAT (float)1E+30
#define MINFLOAT (float)-1E+30
#else
#include <values.h>
#endif

// Application declarations


// Class declarations
#include "OSGBoxVolume.h"

OSG_USING_NAMESPACE

// Static Class Varible implementations: 


/* *********** */
/* * FEATURE * */
/* *********** */


/// Returns the center of a box
void OSGBoxVolume::getCenter(OSGVec3f &center) const
{
	if (isEmpty())
		center.setValues(0.0, 0.0, 0.0);
	else {
		center = _min;
		center += _max;
		center /= 2.0;
	}
}

/// Gives the volume of the box (0 for an empty box)
float OSGBoxVolume::getVolume() const
{
	return isEmpty() ? 0.0 : (_max[0] - _min[0]) *
	                         (_max[1] - _min[1]) *
	                         (_max[2] - _min[2]);
}

/// set method
void OSGBoxVolume::setBoundsByCenterAndSize(const OSGVec3f &center,
                                            const OSGVec3f &size)
{
	_min.setValues(center.x() - size.x() / 2.0,
                   center.y() - size.y() / 2.0,
                   center.z() - size.z() / 2.0);
	_max.setValues(center.x() + size.x() / 2.0,
                   center.y() + size.y() / 2.0,
                   center.z() + size.z() / 2.0);

	OSGVolume::setValid(true);
	OSGVolume::setEmpty(false);
	OSGVolume::setInfinite(true);
}                                          

/****************/
/** Initialize **/
/****************/

/// init the object by enclosing the given volume 
void OSGBoxVolume::initEnclose (const OSGVolume &volume) 
{
	const OSGBoxVolume *box = dynamic_cast<const OSGBoxVolume *>(&volume);

	if (box)
		*this = *box;
	else
		cerr << "OSGBoxVolume::initEnclose NOT IMPLEMENTED" << endl;
}

/// init the object by fitting into the given volume 
void OSGBoxVolume::initInside (const OSGVolume &volume)
{
	const OSGBoxVolume *box = dynamic_cast<const OSGBoxVolume *>(&volume);

	if (box)
		*this = *box;
	else
		cerr << "OSGBoxVolume::initInside NOT IMPLEMENTED" << endl;
}

/***************/
/** EXTENDING **/
/***************/

/// Extends Box3f (if necessary) to contain given 3D point
void OSGBoxVolume::extendBy(const OSGPnt3f &pt)
{
	if ( ! isValid() || isInfinite() || isStatic() )
		return;
		
	if ( isEmpty() )
	{
		_min[0] = _max[0] = pt[0];
		_min[1] = _max[1] = pt[1];
		_min[2] = _max[2] = pt[2];
		setEmpty( false );

		return;
	}
	
	if (pt[0] < _min[0])
		_min[0] = pt[0];
	else 
		if (pt[0] > _max[0])
			_max[0] = pt[0];
				 	
	if (pt[1] < _min[1])
		_min[1] = pt[1];
	else 
		if (pt[1] > _max[1])
			_max[1] = pt[1];

	if (pt[2] < _min[2])
		_min[2] = pt[2];
	else 
		if (pt[2] > _max[2])
			_max[2] = pt[2];
}

/** extend the volume by the given volume */
void OSGBoxVolume::extendBy (const OSGVolume &volume)
{
	OSGBoxVolume const *box = dynamic_cast<const OSGBoxVolume *>(&volume);

	if (box)
		extendBy(*box);
	else
		cerr << "OSGBoxVolume::extendBy NOT IMPLEMENTED" << endl;
}
	

/// Extends Box3f (if necessary) to contain given Box3f
void OSGBoxVolume::extendBy(const OSGBoxVolume &bb)
{
	if ( (! isValid() && ! isEmpty()) || isInfinite() || isStatic() )
		return;

	if ( ! bb.isValid() || bb.isInfinite() )
		return;
	
	if (isEmpty())
		if (bb.isEmpty())
			return;
		else {
			*this = bb;
			return;
		}
	else
		if (bb.isEmpty())
			return;
			
	if (bb._min[0] < _min[0])
		_min[0] = bb._min[0];

	if (bb._max[0] > _max[0])
		_max[0] = bb._max[0];
				 	
	if (bb._min[1] < _min[1])
		_min[1] = bb._min[1];

	if (bb._max[1] > _max[1])
		_max[1] = bb._max[1];

	if (bb._min[2] < _min[2])
		_min[2] = bb._min[2];
	
	if (bb._max[2] > _max[2])
		_max[2] = bb._max[2];
}


/*******************/
/** INTERSECTTION **/
/*******************/	

/// Returns true if intersection of given point and Box3f is not empty
OSGBool OSGBoxVolume::intersect(const OSGVec3f &pt) const
{
	return (!isEmpty() &&
		(_min[0] < pt[0] && _max[0] > pt[0]) &&
		(_min[1] < pt[1] && _max[1] > pt[1]) &&
		(_min[2] < pt[2] && _max[2] > pt[2]));
}


/** intersect the volume with the given Line */
OSGBool OSGBoxVolume::intersect (const OSGLine &line) const 
{ 
	return false; 
}

/** intersect the volume with the given Line */
OSGBool OSGBoxVolume::intersect ( const OSGLine &line, 
																	OSGVec3f &min, OSGVec3f &max  ) const
{
	return false;
}

  /// intersect the volume with another volume 
OSGBool OSGBoxVolume::intersect (const OSGVolume &volume) const
{
	return false;
}

/// Returns true if intersection of given Box3f and Box3f is not empty
OSGBool OSGBoxVolume::intersect(const OSGBoxVolume &bb) const
{
	return (!isEmpty() &&
		(_min[0] < bb._max[0] && _max[0] > bb._min[0]) &&
		(_min[1] < bb._max[1] && _max[1] > bb._min[1]) &&
		(_min[2] < bb._max[2] && _max[2] > bb._min[2]));
}

/// Transforms Box3f by matrix, enlarging Box3f to contain result
void OSGBoxVolume::transform(const OSGMatrix &m)
{
	float xmin, ymin, zmin, xmax, ymax, zmax;
	float a, b;

	if (isEmpty())
		return;

	xmin = xmax = m[3][0]; 
	ymin = ymax = m[3][1]; 
	zmin = zmax = m[3][2]; 

	//
	// calculate xmin and xmax of new tranformed BBox
	// 
	a = _max[0] * m[0][0];
	b = _min[0] * m[0][0];

	if (a >= b) {
		xmax += a;
		xmin += b;
	}
	else {
		xmax += b;
		xmin += a;
	}

	a = _max[1] * m[1][0];
	b = _min[1] * m[1][0];

	if (a >= b) {
		xmax += a;
		xmin += b;
	}
	else {
		xmax += b;
		xmin += a;
	}

	a = _max[2] * m[2][0];
	b = _min[2] * m[2][0];

	if (a >= b) {
		xmax += a;
		xmin += b;
	}
	else {
		xmax += b;
		xmin += a;
	}

	//
	// calculate ymin and ymax of new tranformed BBox
	// 
	a = _max[0] * m[0][1];
	b = _min[0] * m[0][1];

	if (a >= b) {
		ymax += a;
		ymin += b;
	}
	else {
		ymax += b;
		ymin += a;
	}

	a = _max[1] * m[1][1];
	b = _min[1] * m[1][1];

	if (a >= b) {
		ymax += a;
		ymin += b;
	}
	else {
		ymax += b;
		ymin += a;
	}

	a = _max[2] * m[2][1];
	b = _min[2] * m[2][1];

	if (a >= b) {
		ymax += a;
		ymin += b;
	}
	else {
		ymax += b;
		ymin += a;
	}

	//
	// calculate zmin and zmax of new tranformed BBox
	// 
	a = _max[0] * m[0][2];
	b = _min[0] * m[0][2];

	if (a >= b) {
		zmax += a;
		zmin += b;
	}
	else {
		zmax += b;
		zmin += a;
	}

	a = _max[1] * m[1][2];
	b = _min[1] * m[1][2];

	if (a >= b) {
		zmax += a;
		zmin += b;
	}
	else {
		zmax += b;
		zmin += a;
	}

	a = _max[2] * m[2][2];
	b = _min[2] * m[2][2];

	if (a >= b) {
		zmax += a;
		zmin += b;
	}
	else {
		zmax += b;
		zmin += a;
	}

	_min.setValues(xmin, ymin, zmin);
	_max.setValues(xmax, ymax, zmax);
}

/// Assignment operator
const OSGBoxVolume &OSGBoxVolume::operator =(const OSGBoxVolume &b1)
{
	_min = b1._min;
	_max = b1._max;
	_state = b1._state;
	
	return *this;
}

OSG_BEGIN_NAMESPACE

/// Equality comparisons
bool operator ==(const OSGBoxVolume &b1, const OSGBoxVolume &b2)
{
	return ((b1._min[0] == b2._min[0]) &&
	        (b1._min[1] == b2._min[1]) &&
	        (b1._min[2] == b2._min[2]) &&
	        (b1._max[0] == b2._max[0]) &&
	        (b1._max[1] == b2._max[1]) &&
	        (b2._max[2] == b2._max[2]));
}


/// write values in stream
ostream &operator <<(ostream &os, const OSGBoxVolume &obj)
{
	OSGVec3f xx;

	return os << obj._min << ", " << obj._max;
}

OSG_END_NAMESPACE
