#ifndef OSGSPHEREVOLUME_CLASS_DECLARATIONS
#define OSGSPHEREVOLUME_CLASS_DECLARATIONS


#include <OSGVolume.h>

OSG_BEGIN_NAMESPACE

class OSGLine;

/** Sphere in 3D space defined by center and radius.


@author jbehr, dorfmuel, Mon Dec 22 11:32:31 1997

*/

class OSGSphereVolume : public OSGVolume {

	/// center of the sphere
	OSGVec3f _center;
	
	/// radius of the sphere
	float _radius;

public:

	/// Default constructor
	OSGSphereVolume(void) : OSGVolume(), _radius(0) {;}

	/// Copy Constructor
	OSGSphereVolume(const OSGSphereVolume &obj) 
		: OSGVolume(),	_center(obj._center), _radius(obj._radius) {;}

	/// Construct a sphere given center and radius
	OSGSphereVolume(const OSGVec3f &c, float r)
		: OSGVolume(), _center(c), _radius(r) {;}


	/*************/
	/** FEATURE **/
	/*************/	

	/// Change the center and radius
	inline void setValue(const OSGVec3f &c, float r)
		{ _center = c; _radius = r; }

	/// set just the center
	inline void setCenter(const OSGVec3f &c) 
		{ _center = c; }

	/// set just the radius
	inline void setRadius(float r) 
		{ _radius = r; }

	/// Returns the center
	inline void getCenter(OSGVec3f &center) const 
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
  void extendBy(const OSGSphereVolume &bb);


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

  /// intersect the volume with another volume 
  virtual OSGBool intersect (const OSGVolume &volume) const;

	/// Intersect sphere and sphere, returning true if there is an intersection
	OSGBool intersect(const OSGSphereVolume &sphere) const;

	/********************/
	/** TRANSFORMATION **/
	/********************/

  /// Transforms Box3f by matrix
  virtual void transform(const OSGMatrix &mat);

};

OSG_END_NAMESPACE

#endif // OSGSPHEREVOLUME_CLASS_DECLARATIONS
