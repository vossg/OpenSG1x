/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
 *                                                                           *
 *          contact: {reiners|vossg}@igd.fhg.de, jbehr@zgdv.de               *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

#ifndef _OSGLINE_H_
#define _OSGLINE_H_

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------


#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>
#include "OSGVector.h"



OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class OSG_BASE_DLLMAPPING BoxVolume;
class OSG_BASE_DLLMAPPING SphereVolume;
class OSG_BASE_DLLMAPPING CylinderVolume;


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/** Directed line in 3D space defined by pos and dir.

Parametric description: l(t) = pos + t * dir

@author jbehr, dorfmuel, Mon Dec 22 11:32:31 1997

*/

class OSG_BASE_DLLMAPPING Line {

public:

	//-------------------------------------------------------
	//enums   
	//-------------------------------------------------------


	//-------------------------------------------------------
	//types 
	//-------------------------------------------------------


	//-------------------------------------------------------
	//class functions 
	//-------------------------------------------------------

	/*-------------------------- constructor ----------------------------------*/

	/** Default Constructor
	*/
	Line(void);

	/** Copy Constructor
	*/
	Line(const Line &obj);

	/**
	  Construct a line from two points lying on the line.
	  Line is directed from p0 to p1.
	*/
	Line(const Pnt3f &p0, const Pnt3f &p1);

	/**
	  Construct a line from a basepoint and a direction
	*/
	Line(const Pnt3f &pos, const Vec3f &dir);

	/*------------------------- set values -------------------------------*/

	/** Set that value!
	*/
	void setValue(const Pnt3f &p0, const Pnt3f &p1);

	/** Set that value!
	*/
	void setValue(const Pnt3f &pos, const Vec3f &dir);

	/*---------------------------- properties ---------------------------------*/

	/**
	  Find closest points between the two lines. Return false if they are 
	  parallel, otherwise return true.
	*/
	Bool getClosestPoints(const Line &line2,
	               Pnt3f &ptOnThis, Pnt3f &ptOnLine2) const;

	/** Returns the closest point on the line to the given point.
	*/
	Pnt3f getClosestPoint(const Pnt3f &point) const;

	/** Returns the distance of the given point to the line.
	*/
	Real32 distance(const Pnt3f &point) const;

	/** Accessors for position
	*/
	inline const Pnt3f &getPosition(void) const; 

	/** Accessors for direction
	*/
	inline const Vec3f &getDirection(void) const; 


	/*-------------------------- intersection ---------------------------------*/

	/** Intersect the line with a sphere.
	*/
	Bool intersect(const SphereVolume &sphere) const;

	/** Intersect the line with a sphere.
	*/
	Bool intersect(const SphereVolume &sphere,
			          Real32 &enter, Real32 &exit) const;

	/** Intersect the line with a cylinder.
	*/
	Bool intersect(const CylinderVolume &cyl) const;

	/** Intersect the line with a cylinder.
	*/
	Bool intersect(const CylinderVolume &cyl,
			          Real32 &enter, Real32 &exit) const;

	/** Intersect the line with a box.
	*/
	Bool intersect(const BoxVolume &box,
	                 Real32 &enter, Real32 &exit) const;

	/** Intersect the line with a box.
	*/
	Bool intersect(float angle, const BoxVolume &box) const;
	
	/** Intersect the line with a point.
	*/
	Bool intersect(float angle, const Vec3f &point) const;
	
	/** Intersect the line with a line.
	*/
	Bool intersect(float angle, const Vec3f &v0,
	                 const Vec3f &v1, Vec3f &pt) const;

	/** Intersect the line with a triangle.
	*/
	Bool intersect(const Pnt3f &v0, const Pnt3f &v1,
	                 const Pnt3f &v2, Real32 &t ) const;

	//-----------------------------------------------------------------------
	//   instance variables                                                  
	//-----------------------------------------------------------------------

	//-----------------------------------------------------------------------
	//   instance functions                                                  
	//-----------------------------------------------------------------------

private:

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

	//-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

	/// Position
	Pnt3f	_pos;

	/// Direction
	Vec3f	_dir;

	//-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

};

OSG_END_NAMESPACE

#include <OSGLine.inl>

#endif // LINE_CLASS_DECLARATION
