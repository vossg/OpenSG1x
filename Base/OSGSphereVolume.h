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

#ifndef OSGSPHEREVOLUME_CLASS_DECLARATIONS
#define OSGSPHEREVOLUME_CLASS_DECLARATIONS


#include <OSGVolume.h>

OSG_BEGIN_NAMESPACE

class Line;

/** Sphere in 3D space defined by center and radius.


@author jbehr, dorfmuel, Mon Dec 22 11:32:31 1997

*/

class SphereVolume : public Volume {

	/// center of the sphere
	Vec3f _center;
	
	/// radius of the sphere
	float _radius;

public:

	/// Default constructor
	SphereVolume(void) : Volume(), _radius(0) {;}

	/// Copy Constructor
	SphereVolume(const SphereVolume &obj) 
		: Volume(),	_center(obj._center), _radius(obj._radius) {;}

	/// Construct a sphere given center and radius
	SphereVolume(const Vec3f &c, float r)
		: Volume(), _center(c), _radius(r) {;}


	/*************/
	/** FEATURE **/
	/*************/	

	/// Change the center and radius
	inline void setValue(const Vec3f &c, float r)
		{ _center = c; _radius = r; }

	/// set just the center
	inline void setCenter(const Vec3f &c) 
		{ _center = c; }

	/// set just the radius
	inline void setRadius(float r) 
		{ _radius = r; }

	/// Returns the center
	inline void getCenter(Vec3f &center) const 
		{ center = _center;}
	
	/// Returns the radius
	inline float getRadius() const 
		{ return _radius; }

  /** returns the scalar volume of the volume */
  virtual float getVolume (void) const;


	/****************/
	/** Initialize **/
	/****************/

	/** init the object by enclosing the given volume */
	virtual void initEnclose (const Volume &volume);

	/** init the object by fitting into the given volume */
	virtual void initInside (const Volume &volume);


  /***************/
  /** EXTENDING **/
  /***************/

  /** extends (if necessary) to contain the given 3D point */
  virtual void extendBy (const Pnt3f &pt);

  /** extend the volume by the given volume */
  virtual void extendBy (const Volume &volume);   

  /// Extends Box3f (if necessary) to contain given Box3f
  void extendBy(const SphereVolume &bb);


	/*******************/
	/** INTERSECTTION **/
	/*******************/		

	/** Returns true if intersection of given point and Volume is not empty */
  virtual Bool intersect (const Vec3f &point) const;

	/** intersect the volume with the given Line */
	virtual Bool intersect (const Line &line) const;

	/** intersect the volume with the given Line */
	virtual Bool intersect ( const Line &line, 
														  Vec3f &min, Vec3f &max  ) const;

  /// intersect the volume with another volume 
  virtual Bool intersect (const Volume &volume) const;

	/// Intersect sphere and sphere, returning true if there is an intersection
	Bool intersect(const SphereVolume &sphere) const;

	/********************/
	/** TRANSFORMATION **/
	/********************/

  /// Transforms Box3f by matrix
  virtual void transform(const Matrix &mat);

};

OSG_END_NAMESPACE

#endif // OSGSPHEREVOLUME_CLASS_DECLARATIONS
