#ifndef OSGBOX3F_CLASS_DECLARATION
#define OSGBOX3F_CLASS_DECLARATION

#include "OSGConfig.h"
#include "OSGVolume.h"

OSG_BEGIN_NAMESPACE

#ifdef WIN32 // Workaround for a bug in Visual C++ 6.0
class OSGBoxVolume;
bool operator ==(const OSGBoxVolume &b1, const OSGBoxVolume &b2);
bool operator !=(const OSGBoxVolume &b1, const OSGBoxVolume &b2);
ostream& operator<< (ostream & os, const OSGBoxVolume &obj);
#endif

/** 3D box defined by min and max point.

This box class is used by other classes in OSGase for data exchange
and storage. It provides representation of the defining corners of a
box in 3D space.

@author jbehr, Mon Dec 22 11:32:31 1997

*/

class OSGBoxVolume : public OSGVolume {

  /// Minimum point
  OSGVec3f _min;

  /// Maximum point
  OSGVec3f _max;

public:

  /// Default constructor - leaves box totally empty
  inline OSGBoxVolume() : OSGVolume() {;}

  /// Constructor given bounds 
  inline OSGBoxVolume ( float xmin, float ymin, float zmin,
									  float xmax, float ymax, float zmax) 
		: OSGVolume(), _min(xmin, ymin, zmin), _max(xmax, ymax, zmax) {;}

  /// Constructor given minimum and maximum points 
  inline OSGBoxVolume(const OSGVec3f &min, const OSGVec3f &max)
		: OSGVolume(), _min(min), _max(max) {;}

  /// Copy Constructor
  inline OSGBoxVolume(const OSGBoxVolume &obj)
		: OSGVolume(obj), _min(obj._min), _max(obj._max) {;}

  /// Destructor
  inline ~OSGBoxVolume() {}


	/*************/
	/** FEATURE **/
	/*************/

  /// Returns the min and max points
  inline const OSGVec3f &getMin() const { return _min; }
  inline const OSGVec3f &getMax() const { return _max; }

  /// Returns the center of a box
  void getCenter(OSGVec3f &center) const;

  /** gives the scalar volume of the volume */
  virtual float getVolume (void) const;

  /// set method with center 0,0,0
  inline void setBounds(float w, float h, float d)
  {
    _min.setValues(-w / 2.0, -h / 2.0, -d / 2.0);
    _max.setValues( w / 2.0,  h / 2.0,  d / 2.0);

		OSGVolume::setValid(true);
		OSGVolume::setEmpty(false);
		OSGVolume::setInfinite(true);
  }

  /// set method
  inline void setBounds(float xmin, float ymin, float zmin,
                        float xmax, float ymax, float zmax)
  {
    _min.setValues(xmin, ymin, zmin);
    _max.setValues(xmax, ymax, zmax);

		OSGVolume::setValid(true);
		OSGVolume::setEmpty(false);
		OSGVolume::setInfinite(true);
  }

  /// set method
  inline void setBounds(const OSGVec3f &min, const OSGVec3f &max)
		{ 
			_min = min; _max = max; 
			
			OSGVolume::setValid(true);
			OSGVolume::setEmpty(false);
			OSGVolume::setInfinite(true);
		}

  /// set method
  void setBoundsByCenterAndSize(const OSGVec3f &center, const OSGVec3f &size);

  /// get method
  inline void getBounds(float &xmin, float &ymin, float &zmin,
                        float &xmax, float &ymax, float &zmax ) const
		{ _min.getValues(xmin, ymin, zmin); _max.getValues(xmax, ymax, zmax); }

  /// get method
  inline void getBounds(OSGVec3f &min, OSGVec3f &max) const
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
  inline void getSize(OSGVec3f &vec) const
		{ vec.setValues(_max[0] - _min[0], _max[1] - _min[1], _max[2] - _min[2]); }

	/****************/
	/** Initialize **/
	/****************/

	/** init the object by enclosing the given volume */
	virtual void initEnclose (const OSGVolume &volume);

	/** init the object by fitting into the given volume */
	virtual void initInside (const OSGVolume &volume);

  /***************/
  /** EXTENDING **/
  /***************/

  /** extends (if necessary) to contain the given 3D point */
  virtual void extendBy (const OSGPnt3f &pt);

  /** extend the volume by the given volume */
  virtual void extendBy (const OSGVolume &volume);   

  /// Extends Box3f (if necessary) to contain given Box3f
  void extendBy(const OSGBoxVolume &bb);


	/*******************/
	/** INTERSECTTION **/
	/*******************/	

  /// Returns true if intersection of given point and Box3f is not empty
  OSGBool intersect(const OSGVec3f &point) const;

	/** intersect the volume with the given Line */
	OSGBool intersect (const OSGLine &line) const;

	/** intersect the volume with the given Line */
	virtual OSGBool intersect ( const OSGLine &line, 
														  OSGVec3f &min, OSGVec3f &max  ) const;

  /// intersect the volume with another volume 
  virtual OSGBool intersect (const OSGVolume &volume) const;

  /// Returns true if intersection of given Box3f and Box3f is not empty
  OSGBool intersect(const OSGBoxVolume &bb) const;


	/********************/
	/** TRANSFORMATION **/
	/********************/

  /// Transforms Box3f by matrix
  virtual void transform(const OSGMatrix &m);

	
	/***************/
	/** OPERATION **/
	/***************/

  /// Equality comparisons
  friend bool operator ==(const OSGBoxVolume &b1, const OSGBoxVolume &b2);

  /// Unequality comparisons
  inline friend bool operator != (const OSGBoxVolume &b1, 
																  const OSGBoxVolume &b2)
		{ return !(b1 == b2); }

  /// Assignment operator
  const OSGBoxVolume &operator =(const OSGBoxVolume &b1);

  /// write values in stream
  friend ostream &operator <<(ostream            &os, 
                              const OSGBoxVolume &obj);

};

OSG_END_NAMESPACE

#endif // OSGBOX_CLASS_DECLARATION
