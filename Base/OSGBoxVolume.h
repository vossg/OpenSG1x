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

#ifndef OSGBOX3F_CLASS_DECLARATION
#define OSGBOX3F_CLASS_DECLARATION

#include "OSGConfig.h"
#include "OSGVolume.h"

OSG_BEGIN_NAMESPACE

#ifdef WIN32 // Workaround for a bug in Visual C++ 6.0
class BoxVolume;
Bool operator ==(const BoxVolume &b1, const BoxVolume &b2);
Bool operator !=(const BoxVolume &b1, const BoxVolume &b2);
ostream& operator<< (ostream & os, const BoxVolume &obj);
#endif

/** 3D box defined by min and max point.

This box class is used by other classes in ase for data exchange
and storage. It provides representation of the defining corners of a
box in 3D space.

@author jbehr, Mon Dec 22 11:32:31 1997

*/

class OSG_BASE_DLLMAPPING BoxVolume : public Volume {

  /// Minimum point
  Vec3f _min;

  /// Maximum point
  Vec3f _max;

public:

  /// Default constructor - leaves box totally empty
  inline BoxVolume() : Volume() {;}

  /// Constructor given bounds 
  inline BoxVolume ( float xmin, float ymin, float zmin,
									  float xmax, float ymax, float zmax) 
		: Volume(), _min(xmin, ymin, zmin), _max(xmax, ymax, zmax) {;}

  /// Constructor given minimum and maximum points 
  inline BoxVolume(const Vec3f &min, const Vec3f &max)
		: Volume(), _min(min), _max(max) {;}

  /// Copy Constructor
  inline BoxVolume(const BoxVolume &obj)
		: Volume(obj), _min(obj._min), _max(obj._max) {;}

  /// Destructor
  inline ~BoxVolume() {}


	/*************/
	/** FEATURE **/
	/*************/

  /// Returns the min and max points
  inline const Vec3f &getMin() const { return _min; }
  inline const Vec3f &getMax() const { return _max; }

  /// Returns the center of a box
  void getCenter(Vec3f &center) const;

  /** gives the scalar volume of the volume */
  virtual float getVolume (void) const;

  /// set method with center 0,0,0
  inline void setBounds(float w, float h, float d)
  {
    _min.setValues(-w / 2.0, -h / 2.0, -d / 2.0);
    _max.setValues( w / 2.0,  h / 2.0,  d / 2.0);

		Volume::setValid(true);
		Volume::setEmpty(false);
		Volume::setInfinite(true);
  }

  /// set method
  inline void setBounds(float xmin, float ymin, float zmin,
                        float xmax, float ymax, float zmax)
  {
    _min.setValues(xmin, ymin, zmin);
    _max.setValues(xmax, ymax, zmax);

		Volume::setValid(true);
		Volume::setEmpty(false);
		Volume::setInfinite(true);
  }

  /// set method
  inline void setBounds(const Vec3f &min, const Vec3f &max)
		{ 
			_min = min; _max = max; 
			
			Volume::setValid(true);
			Volume::setEmpty(false);
			Volume::setInfinite(true);
		}

  /// set method
  void setBoundsByCenterAndSize(const Vec3f &center, const Vec3f &size);

  /// get method
  inline void getBounds(float &xmin, float &ymin, float &zmin,
                        float &xmax, float &ymax, float &zmax ) const
		{ _min.getValues(xmin, ymin, zmin); _max.getValues(xmax, ymax, zmax); }

  /// get method
  inline void getBounds(Vec3f &min, Vec3f &max) const
		{ min = _min; max = _max; }
    
  /// Returns origin (minimum point) of box
  inline void getOrigin(float &originX, float &originY, float &originZ) const
  { originX = _min[0]; originY = _min[1]; originZ = _min[2]; }

  /// Returns size of box
  inline void getSize(float &sizeX, float &sizeY, float &sizeZ) const
  {
    sizeX = _max[0] - _min[0];
    sizeY = _max[1] - _min[1]; 
    sizeZ = _max[2] - _min[2]; 
  }

  /// Returns the size of the box as vector
  inline void getSize(Vec3f &vec) const
		{ vec.setValues(_max[0] - _min[0], _max[1] - _min[1], _max[2] - _min[2]); }

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
  void extendBy(const BoxVolume &bb);


	/*******************/
	/** INTERSECTTION **/
	/*******************/	

  /// Returns true if intersection of given point and Box3f is not empty
  Bool intersect(const Vec3f &point) const;

	/** intersect the volume with the given Line */
	Bool intersect (const Line &line) const;

	/** intersect the volume with the given Line */
	virtual Bool intersect ( const Line &line, 
														  Vec3f &min, Vec3f &max  ) const;

  /// intersect the volume with another volume 
  virtual Bool intersect (const Volume &volume) const;

  /// Returns true if intersection of given Box3f and Box3f is not empty
  Bool intersect(const BoxVolume &bb) const;


	/********************/
	/** TRANSFORMATION **/
	/********************/

  /// Transforms Box3f by matrix
  virtual void transform(const Matrix &m);

	
	/***************/
	/** OPERATION **/
	/***************/

  /// Equality comparisons
  friend Bool operator ==(const BoxVolume &b1, const BoxVolume &b2);

  /// Unequality comparisons
  inline friend Bool operator != (const BoxVolume &b1, 
																  const BoxVolume &b2)
		{ return !(b1 == b2); }

  /// Assignment operator
  const BoxVolume &operator =(const BoxVolume &b1);

  /// write values in stream
  friend ostream &operator <<(ostream            &os, 
                              const BoxVolume &obj);

};

OSG_END_NAMESPACE

#endif // OSGBOX_CLASS_DECLARATION
