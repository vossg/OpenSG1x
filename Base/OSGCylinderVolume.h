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


#ifndef CYLINDERVOLUME_CLASS_DECLARATION
#define CYLINDERVOLUME_CLASS_DECLARATION

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGLine.h"
#include "OSGVolume.h"
#include "OSGVector.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/** 3D cylinder in space defined by axis and radius.

This class is used within other classes in ase. It contains data to
represent a cylinder by an axis and a radius. The height of the 
cylinder is defined by the length of the axis, i.e. its apex is at 
_axisPos + _axisDir.

*/

class OSG_BASE_DLLMAPPING CylinderVolume : public Volume {

public:

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

	/*-------------------------- constructor ----------------------------------*/

	/*! Default Constructor
	*/
	inline CylinderVolume(void);

  /// Construct a cylinder given its axis and radius
	inline CylinderVolume(const Pnt3f &p, const Vec3f &d, float r);

  /// Copy constructor
	inline CylinderVolume(const CylinderVolume &c);

  /// Desctructor
	inline ~CylinderVolume(void); // {;}


	
/*------------------------------ feature ----------------------------------*/
	
  /// Change the axis and radius
  inline void setValue(const Pnt3f &p, const Vec3f &d, float r);

  /// set just the axis 
  inline void setAxis(const Pnt3f &p, const Vec3f &d); 

  /// set just the radius
  inline void setRadius(float r);

  /// return the axis
  inline void getAxis(Pnt3f &apos, Vec3f &adir) const;

  /// return the radius
  inline float getRadius(void) const;

	/// Returns the center
	virtual void getCenter(Pnt3f &center) const;
	
  /** returns the scalar volume of the cylinder */
  virtual float getScalarVolume (void) const;

  /** gives the boundaries of the volume */
  virtual void getBounds( Pnt3f &min, Pnt3f &max ) const;



/*-------------------------- extending ------------------------------------*/

  /** extends (if necessary) to contain the given 3D point */
  virtual void extendBy (const Pnt3f &pt);

  /** extend the volume by the given volume */
  virtual void extendBy (const Volume &volume);

	/** extends cylinder (if necessary) to contain given cylinder */
	void extendBy (const CylinderVolume &obj);



/*-------------------------- intersection ---------------------------------*/

	/** Returns true if intersection of given point and CylinderVolume is not empty */
  virtual Bool intersect (const Pnt3f &point) const;	

	/** intersect the CylinderVolume with the given Line */
	Bool intersect (const Line &line) const;

	/** intersect the CylinderVolume with the given Line */
	virtual Bool intersect ( const Line &line, 
							 Real32 &enter, Real32 &exit  ) const;

	/** intersect the CylinderVolume with another Volume */
  	virtual Bool intersect (const Volume &volume) const;

	/** intersect the CylinderVolume with another CylinderVolume */
	virtual Bool intersect (const CylinderVolume &volume) const;

  /** check if the point is on the volume's surface */
  virtual Bool isOnSurface (const Pnt3f &point) const;



/*-------------------------- transformation -------------------------------*/

  /** transform volume by the given matrix */
  virtual void transform (const Matrix &mat);

//-----------------------------------------------------------------------
//   instance variables                                                  
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
//   instance functions                                                  
//-----------------------------------------------------------------------

private:

	/// axis startpoint
	Pnt3f _axisPos;

	// axis direction
	Vec3f _axisDir;

  /// Radius
  float	_radius;

};

OSG_END_NAMESPACE

#include <OSGCylinderVolume.inl>

#endif //CYLINDERVOLUME_CLASS_DECLARATION
