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

class OSG_BASE_DLLMAPPING Volume {

private:

	enum State 
	{
		OSGVALID    = 1,
		OSGEMPTY    = 2,
		OSGSTATIC   = 4,
		OSGINFINITE = 8
	};

protected:

	UInt16 _state;

  /** Default Constructor */
  Volume (void ) : _state( OSGVALID | OSGEMPTY) {;}

  /** Copy Constructor */
  Volume (const Volume &obj) : _state(obj._state) {;}

public:

  /** Destructor */
  virtual ~Volume (void) {;}

	/***********/
	/** STATE **/
	/***********/

  /** set the volume to contain nothing */
  inline void setValid (const Bool value = true) 
		{ _state = value ? (_state | OSGVALID) : (_state & ~OSGVALID); }

  /**  Checks if the volume is valid */
  inline Bool isValid (void) const 
		{ return ( _state & OSGVALID ) ? true : false; }

  /** set the volume to contain nothing */
  inline void setEmpty (const Bool value = true) 
		{ _state = value ? (_state | OSGEMPTY) : ( _state & ~OSGEMPTY); }

  /**  Checks if the volume is empty */
  inline Bool isEmpty (void) const 
		{ return ( _state & OSGEMPTY ) ? true : false; }

  /** set the volume to contain nothing */
  inline void setStatic (const Bool value = true) 
		{ _state = value ? (_state | OSGSTATIC) : ( _state & ~OSGSTATIC); }

  /**  Checks if the volume is static */
  inline Bool isStatic (void) const
		{ return ( _state & OSGSTATIC ) ? true : false; }

  /** set the volume to contain nothing */
  inline void setInfinite (const Bool value = true) 
		{ _state = value ? (_state | OSGINFINITE) : ( _state & ~OSGINFINITE); }

  /**  Checks if the volume is infinite */
  inline Bool isInfinite (void) const 
		{ return ( _state & OSGINFINITE ) ? true : false; }


	/*********************/
	/** GENERIC FEATURE **/
	/*********************/

  /** the the center of the volume */
  virtual void getCenter (Vec3f &center) const = 0;

  /** gives the scalar volume of the volume */
  virtual float getVolume (void) const = 0;

	/****************/
	/** Initialize **/
	/****************/

	/** init the object by enclosing the given volume */
	virtual void initEnclose (const Volume &volume) = 0;

	/** init the object by fitting into the given volume */
	virtual void initInside (const Volume &volume) = 0;

  /***************/
  /** EXTENDING **/
  /***************/

  /** extends (if necessary) to contain the given 3D point */
  virtual void extendBy (const Pnt3f &pt) = 0;

  /** extend the volume by the given volume */
  virtual void extendBy (const Volume &volume) = 0;   

	/*******************/
	/** INTERSECTTION **/
	/*******************/

  /** Returns true if intersection of given point and Volume is not empty */
  virtual Bool intersect (const Vec3f &point) const = 0;

	/** intersect the volume with the given Line */
	virtual Bool intersect (const Line &line ) const = 0;

	/** intersect the volume with the given Line */
	virtual Bool intersect ( const Line &line, 
														  Vec3f &min, Vec3f &max  ) const = 0;

  /** intersect the volume with another volume */
  virtual Bool intersect (const Volume &volume) const = 0;


	/********************/
	/** TRANSFORMATION **/
	/********************/

	/** transform the volume bye the given matrix*/
  virtual void transform (const Matrix &matrix) = 0;

			
};

typedef Volume* VolumeP;

OSG_END_NAMESPACE

#endif // OSGVOLUME_CLASS_DECLARATION
