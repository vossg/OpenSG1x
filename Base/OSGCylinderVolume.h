#ifndef OSGCYLINDERVOLUME_CLASS_DECLARATION
#define OSGCYLINDERVOLUME_CLASS_DECLARATION

#include "OSGLine.h"
#include "OSGVolume.h"

OSG_BEGIN_NAMESPACE

/** 3D cylinder in space defined by axis and radius.

This class is used within other classes in OSGase. It contains data to
represent a cylinder by an axis and a radius. The cylinder has no
length/height value, which means it is treated as of infinite
length.

@author jbehr, dorfmuel, Thu Dec 11 16:13:53 1997

*/

class OSGCylinderVolume : public OSGVolume {

  /// Axis
  OSGLine _axis;

  /// Radius
  float	_radius;

public:

  /// Default Constructor
  inline OSGCylinderVolume(void) : OSGVolume() {;}

  /// Construct a cylinder given its axis and radius
  inline OSGCylinderVolume(const OSGLine &a, float r) 
		: OSGVolume(), _axis(a), _radius(r) {;}

  /// Copy constructor
  inline OSGCylinderVolume(const OSGCylinderVolume &c)
		: OSGVolume(), _axis(c._axis), _radius(c._radius) {;}

  /// Desctructor
  inline ~OSGCylinderVolume(void) {;}


	/*************/
	/** FEATURE **/
	/*************/
	
  /// Change the axis and radius
  inline void setValue(const OSGLine &a, float r)
		{ _axis = a; _radius = r; }

  /// set just the axis 
  inline void setAxis(const OSGLine &a) 
		{ _axis = a; }

  /// set just the radius
  inline void setRadius(float r) 
		{ _radius = r; }

  /// return the axis
  inline void getAxis(OSGLine &axis) const 
		{ axis = _axis; }

  /// return the radius
  inline float getRadius(void) const 
		{ return _radius; }

	/// Returns the center
	virtual void getCenter(OSGVec3f &center) const;
	
  /** returns the scalar volume of the cylinder */
  virtual float getVolume (void) const;

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

	/** extends cylinder (if necessary) to contain given cylinder */
	void extendBy (const OSGCylinderVolume &obj);


	/*******************/
	/** INTERSECTTION **/
	/*******************/	

	/** Returns true if intersection of given point and Volume is not empty */
  virtual OSGBool intersect (const OSGVec3f &point) const;	

	/** intersect the volume with the given Line */
	virtual OSGBool intersect (const OSGLine &line) const;

	/** intersect the volume with the given Line */
	virtual OSGBool intersect ( const OSGLine &line, 
														  OSGVec3f &min, OSGVec3f &max  ) const;

  /** intersect the volume with another volume */
  virtual OSGBool intersect (const OSGVolume &volume) const;

  /** intersect the volume with another volume */
	OSGBool intersect (const OSGCylinderVolume &volume) const;


	/********************/
	/** TRANSFORMATION **/
	/********************/

  /** transform volume by the given matrix */
  virtual void transform (const OSGMatrix &mat);

};

OSG_END_NAMESPACE

#endif //OSGCYLINDERVOLUME_CLASS_DECLARATION
