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


#ifndef FRUSTUMVOLUME_CLASS_DECLARATION
#define FRUSTUMVOLUME_CLASS_DECLARATION

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGConfig.h"
#include "OSGVolume.h"
#include "OSGPlane.h"

OSG_BEGIN_NAMESPACE

#ifdef WIN32 // Workaround for a bug in Visual C++ 6.0
class FrustumVolume;
Bool operator ==(const FrustumVolume &b1, const FrustumVolume &b2);
Bool operator !=(const FrustumVolume &b1, const FrustumVolume &b2);
ostream& operator<< (ostream & os, const FrustumVolume &obj);
#endif

/** 
@brief 3D frustum defined by 6 planes.
@author jbehr

This box class is used by other classes in ase for data exchange
and storage. It provides representation of the defining corners of a
box in 3D space.

*/

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------
class OSG_BASE_DLLMAPPING FrustumVolume : public Volume {

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

/*! Default constructor - leaves box totally empty
*/
  inline FrustumVolume(); 

  /// Constructor obj from 6 planes
  inline FrustumVolume ( const Plane &near, const Plane &far,
												 const Plane &left, const Plane &right,
												 const Plane &top,  const Plane &bottom );


  /// Copy Constructor
  inline FrustumVolume(const FrustumVolume &obj);


  /// Destructor
  inline ~FrustumVolume(); 


/*------------------------------ feature ----------------------------------*/

	/** return the near plane */
	inline const Plane & getNear   (void) const;

	/** return the far plane */
	inline const Plane & getFar    (void) const;

	/** return the left plane */
	inline const Plane & getLeft   (void) const;

	/** return the right plane */
	inline const Plane & getRight  (void) const;

	/** return the top plane */
	inline const Plane & getTop    (void) const;

	/** return the bottom plane */
	inline const Plane & getBottom (void) const;

	/** set method for all planes */
	inline
	void FrustumVolume::setPlanes( const Plane &near, const Plane &far,
																 const Plane &left, const Plane &right,
																 const Plane &top,  const Plane &bottom);

 /** gives the center of the volume */
  virtual void getCenter (Pnt3f &center) const;

  /** gives the scalar volume of the volume */
  virtual float getScalarVolume (void) const;

  /** gives the boundaries of the volume */
  virtual void getBounds( Pnt3f &minPnt, Pnt3f &maxPnt ) const;

/*-------------------------- extending ------------------------------------*/

  /** extends (if necessary) to contain the given 3D point */
  virtual void extendBy (const Pnt3f &pt);

  /** extend the volume by the given volume */
	inline void extendBy (const Volume &volume);   

  /// Extends Frustum3f (if necessary) to contain given Frustum3f
  inline void extendBy ( const FrustumVolume &bb);

/*-------------------------- intersection ---------------------------------*/

  /// Returns true if intersection of given point and Frustum3f is not empty
  Bool intersect(const Pnt3f &point) const;

	/** Returns true if intersection of given Line with the box is not empty */  
	Bool intersect (const Line &line) const;

	/** intersect the box with the given Line */
	Bool intersect ( const Line &line, 
									 Real32 &minDist, Real32 &maxDist  ) const;

  /// intersect the volume with another volume 
	inline Bool intersect (const Volume &volume) const;

  /// Returns true if intersection of given Frustum3f and Frustum3f is not empty
	inline Bool intersect(const FrustumVolume &bb) const;

  /** check if the point is on the volume's surface */
  virtual Bool isOnSurface (const Pnt3f &point) const;


/*-------------------------- transformation -------------------------------*/

  /// Transforms Frustum3f by matrix
  virtual void transform(const Matrix &m);

	
/*-------------------------- operation ------------------------------------*/

  /// Equality comparisons
  friend Bool operator ==(const FrustumVolume &b1, const FrustumVolume &b2);

  /// Unequality comparisons
  inline friend Bool operator !=(const FrustumVolume &b1, const FrustumVolume &b2);

  /// Assignment operator
  const FrustumVolume &operator =(const FrustumVolume &b1);


/*-------------------------- output -------------------------------*/

	/** print the volume */
  virtual void dump(	UInt32				uiIndent = 0, 
						const BitVector &	bvFlags = 0) const;

private:

  /// holds the 6 planes (near,far,left,right,top,bottom)
	Plane _planeVec[6];

};

OSG_END_NAMESPACE

#include <OSGFrustumVolume.inl>

#endif // FRUSTUMVOLUME_CLASS_DECLARATION
