#ifndef OSGVOLUME_CLASS_DECLARATION
#define OSGVOLUME_CLASS_DECLARATION

#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>

#include "OSGVector.h"
#include "OSGMatrix.h"
#include "OSGLine.h"

OSG_BEGIN_NAMESPACE

/* 3D base volume.
 *
 *
 * @author jbehr, Wed Feb 16 20:04:15 2000
 */

class OSGVolume {

private:

	enum State 
	{
		OSGVALID    = 1,
		OSGEMPTY    = 2,
		OSGSTATIC   = 4,
		OSGINFINITE = 8
	};

protected:

	OSGUInt16 _state;

  /** Default Constructor */
  OSGVolume (void ) : _state( OSGVALID | OSGEMPTY) {;}

  /** Copy Constructor */
  OSGVolume (const OSGVolume &obj) : _state(obj._state) {;}

public:

  /** Destructor */
  virtual ~OSGVolume (void) {;}

	/***********/
	/** STATE **/
	/***********/

  /** set the volume to contain nothing */
  inline void setValid (const OSGBool value = true) 
		{ _state = value ? (_state | OSGVALID) : (_state & ~OSGVALID); }

  /**  Checks if the volume is valid */
  inline OSGBool isValid (void) const 
		{ return ( _state & OSGVALID ) ? true : false; }

  /** set the volume to contain nothing */
  inline void setEmpty (const OSGBool value = true) 
		{ _state = value ? (_state | OSGEMPTY) : ( _state & ~OSGEMPTY); }

  /**  Checks if the volume is empty */
  inline OSGBool isEmpty (void) const 
		{ return ( _state & OSGEMPTY ) ? true : false; }

  /** set the volume to contain nothing */
  inline void setStatic (const OSGBool value = true) 
		{ _state = value ? (_state | OSGSTATIC) : ( _state & ~OSGSTATIC); }

  /**  Checks if the volume is static */
  inline OSGBool isStatic (void) const
		{ return ( _state & OSGSTATIC ) ? true : false; }

  /** set the volume to contain nothing */
  inline void setInfinite (const OSGBool value = true) 
		{ _state = value ? (_state | OSGINFINITE) : ( _state & ~OSGINFINITE); }

  /**  Checks if the volume is infinite */
  inline OSGBool isInfinite (void) const 
		{ return ( _state & OSGINFINITE ) ? true : false; }


	/*********************/
	/** GENERIC FEATURE **/
	/*********************/

  /** the the center of the volume */
  virtual void getCenter (OSGVec3f &center) const = 0;

  /** gives the scalar volume of the volume */
  virtual float getVolume (void) const = 0;

	/****************/
	/** Initialize **/
	/****************/

	/** init the object by enclosing the given volume */
	virtual void initEnclose (const OSGVolume &volume) = 0;

	/** init the object by fitting into the given volume */
	virtual void initInside (const OSGVolume &volume) = 0;

  /***************/
  /** EXTENDING **/
  /***************/

  /** extends (if necessary) to contain the given 3D point */
  virtual void extendBy (const OSGPnt3f &pt) = 0;

  /** extend the volume by the given volume */
  virtual void extendBy (const OSGVolume &volume) = 0;   

	/*******************/
	/** INTERSECTTION **/
	/*******************/

  /** Returns true if intersection of given point and Volume is not empty */
  virtual OSGBool intersect (const OSGVec3f &point) const = 0;

	/** intersect the volume with the given Line */
	virtual OSGBool intersect (const OSGLine &line ) const = 0;

	/** intersect the volume with the given Line */
	virtual OSGBool intersect ( const OSGLine &line, 
														  OSGVec3f &min, OSGVec3f &max  ) const = 0;

  /** intersect the volume with another volume */
  virtual OSGBool intersect (const OSGVolume &volume) const = 0;


	/********************/
	/** TRANSFORMATION **/
	/********************/

	/** transform the volume bye the given matrix*/
  virtual void transform (const OSGMatrix &matrix) = 0;

			
};

typedef OSGVolume* OSGVolumeP;

OSG_END_NAMESPACE

#endif // OSGVOLUME_CLASS_DECLARATION
