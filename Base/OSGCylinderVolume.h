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

#ifndef OSGCYLINDERVOLUME_CLASS_DECLARATION
#define OSGCYLINDERVOLUME_CLASS_DECLARATION

#include "OSGLine.h"
#include "OSGVolume.h"

OSG_BEGIN_NAMESPACE

/** 3D cylinder in space defined by axis and radius.

This class is used within other classes in ase. It contains data to
represent a cylinder by an axis and a radius. The cylinder has no
length/height value, which means it is treated as of infinite
length.

@author jbehr, dorfmuel, Thu Dec 11 16:13:53 1997

*/

class OSG_BASE_DLLMAPPING CylinderVolume : public Volume {

  /// Axis
  Line _axis;

  /// Radius
  float	_radius;

public:

  /// Default Constructor
  inline CylinderVolume(void) : Volume() {;}

  /// Construct a cylinder given its axis and radius
  inline CylinderVolume(const Line &a, float r) 
		: Volume(), _axis(a), _radius(r) {;}

  /// Copy constructor
  inline CylinderVolume(const CylinderVolume &c)
		: Volume(), _axis(c._axis), _radius(c._radius) {;}

  /// Desctructor
  inline ~CylinderVolume(void) {;}


	/*************/
	/** FEATURE **/
	/*************/
	
  /// Change the axis and radius
  inline void setValue(const Line &a, float r)
		{ _axis = a; _radius = r; }

  /// set just the axis 
  inline void setAxis(const Line &a) 
		{ _axis = a; }

  /// set just the radius
  inline void setRadius(float r) 
		{ _radius = r; }

  /// return the axis
  inline void getAxis(Line &axis) const 
		{ axis = _axis; }

  /// return the radius
  inline float getRadius(void) const 
		{ return _radius; }

	/// Returns the center
	virtual void getCenter(Vec3f &center) const;
	
  /** returns the scalar volume of the cylinder */
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

	/** extends cylinder (if necessary) to contain given cylinder */
	void extendBy (const CylinderVolume &obj);


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

  /** intersect the volume with another volume */
  virtual Bool intersect (const Volume &volume) const;

  /** intersect the volume with another volume */
	Bool intersect (const CylinderVolume &volume) const;


	/********************/
	/** TRANSFORMATION **/
	/********************/

  /** transform volume by the given matrix */
  virtual void transform (const Matrix &mat);

};

OSG_END_NAMESPACE

#endif //OSGCYLINDERVOLUME_CLASS_DECLARATION
