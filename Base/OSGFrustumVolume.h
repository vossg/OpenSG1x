#ifndef OSGFRUSTUMVOLUME_CLASS_DECLARATIONS
#define OSGFRUSTUMVOLUME_CLASS_DECLARATIONS


#include <OSGVolume.h>

OSG_BEGIN_NAMESPACE

class OSGLine;

/** Frustum, defined by 6 half-spaces.


@author jbehr, Mon Dec 22 11:32:31 1997

*/

class OSGFrustumVolume : public OSGVolume {


public:

	/// Default constructor
	OSGFrustumVolume(void) 
		: OSGVolume() {;}

	/// Copy Constructor
	OSGFrustumVolume(const OSGFrustumVolume &obj)
		: OSGVolume(obj) {;}

	/// Returns the center
	inline const OSGVec3f &getCenter(void) const { return OSGVec3f(0, 0, 0); }

	/// Returns the center
	inline void getCenter(OSGVec3f &center) const { center = OSGVec3f(0, 0, 0);}
 
	/** Returns true if intersection of given point and Volume is not empty */
    virtual OSGBool intersect (const OSGVec3f &point) const;

  /** intersect the volume with another volume */
  virtual OSGBool intersect (OSGVolume &volume) const;

	/** intersect the volume with the given Line */
	virtual OSGBool intersect (OSGLine &line) const { return false; }

  /** extends (if necessary) to contain the given 3D point */
  virtual void extendBy (const OSGPnt3f &pt);

  /** extend the volume by the given volume */
  virtual void extendBy (const OSGVolume &volume);

  /** set the volume to contain nothing */
  virtual void makeEmpty (void) ;

  /**  Checks if the volume is empty */
  virtual OSGBool isEmpty (void) const;

  /** ives the volume of the volume */
  virtual float getVolume (void) const;

  /** scale the volume */
  virtual void scale (float scaleValue);

  /** transform volume by the given matrix */
  virtual void transform (const OSGMatrix &mat);

};

OSG_END_NAMESPACE

#endif // OSGFRUSTUMVOLUME_CLASS_DECLARATIONS
