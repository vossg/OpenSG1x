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

#ifndef OSGPLANE_CLASS_DECLARATION
#define OSGPLANE_CLASS_DECLARATION
//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>

#include "OSGVector.h"
#include "OSGMatrix.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class Line;

#ifdef WIN32 // Workaround for a bug in Visual C++ 6.0
class Plane;
OSG_BASE_DLLMAPPING
Bool operator ==(const Plane &p1, const Plane &p2);
OSG_BASE_DLLMAPPING
Bool operator !=(const Plane &p1, const Plane &p2);
#endif


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/** Oriented plane in 3D space defined by normal and distance.

The plane is defined by a plane normal and a distance from the 
origin along that normal
Planes may be used to represent either planes or half-spaces. In
the latter case (as for the isInHalfSpace() method), the
half-space is defined to be all points on the plane or on the side
of the plane in the direction of the plane normal.

The 4 coefficients of the plane equation of an Plane can be
obtained easily as the 3 coordinates of the plane normal and the
distance, in that order. The normal is normalized.

node: Plane is all p such that normalVec . p - distance = 0

@author jbehr, dorfmuel, Mon Dec 22 11:32:31 1997

*/

class OSG_BASE_DLLMAPPING Plane {

public:

	//-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------


	/*-------------------------- constructor ----------------------------------*/

	/** Default Constructor
	*/
	Plane(void);

	/** Copy Constructor
	*/
	Plane(const Plane &obj);

	/**
	  Construct a plane given 3 points.
	  Orientation is computed by taking (p1 - p0) x (p2 - p0) and
	  pointing the normal in that direction.
	*/
	Plane(const Pnt3f &p0, const Pnt3f &p1, const Pnt3f &p2);

	/**
	  Construct a plane given normal and distance from origin along normal.
	  Orientation is given by the normal vector n.
	*/
	Plane(const Vec3f &n, float d);

	/**
	  Construct a plane given normal and a point to pass through
	  Orientation is given by the normal vector n.
	*/
	Plane(const Vec3f &n, const Pnt3f &p);


	/** Offset a plane by a given distance.
	*/
	void offset(float d);

	/*-------------------------- intersection ---------------------------------*/

	/**
	  Intersect line and plane, returning true if there is an intersection
	  false if line is parallel to plane
	*/
	Bool intersect(const Line &l, Pnt3f &intersection) const;

	/**
	  Intersect line and plane, returning true if there is an intersection
	  false if line is parallel to plane. t is the distance along
	  the line
	*/
	Bool intersect(const Line &l, Real32 &t) const;

	/** Transforms the plane by the given matrix
	*/
	void transform(const Matrix &matrix);

	/**
	  Returns true if the given point is within the half-space
	  defined by the plane
	*/
	Bool isInHalfSpace(const Pnt3f &point) const;

	/**
	  Returns true if the given point is on the plane
	*/
	Bool isOnPlane(const Pnt3f &point) const;


	/*------------------------- set values -------------------------------*/

	/// set the plane param
	void set(const Vec3f &normal, float distance);

	/*------------------------------ access -----------------------------------*/

	/// Accessors for normal
	inline const Vec3f &getNormal(void) const { return _normalVec; }

	/// Accessors for distance
	inline float getDistanceFromOrigin(void) const { return _distance; }

	/*-------------------------- comparison -----------------------------------*/

	/// Equality comparison operators
    OSG_BASE_DLLMAPPING
	friend Bool operator ==(const Plane &p1, const Plane &p2);

	/// Inequality comparison operators
	inline OSG_BASE_DLLMAPPING
    friend Bool operator !=(const Plane &p1, const Plane &p2)
	{ return !(p1 == p2); }

	//-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

	//-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

private:


	/// Normal to the plane
	Vec3f _normalVec;

	/// Distance from origin to plane: distance * normalVec is on the plane
	float _distance;

};

OSG_END_NAMESPACE

#endif // OSGPLANE_CLASS_DECLARATION
