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


#ifndef _OSGSPHEREVOLUME_H_
#define _OSGSPHEREVOLUME_H_


//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGVolume.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class Line;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/** Sphere in 3D space defined by center and radius.


@author jbehr, dorfmuel, Mon Dec 22 11:32:31 1997

*/

class OSG_BASE_DLLMAPPING SphereVolume : public Volume {

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

	/** Default constructor
	*/
	SphereVolume(void);

	/** Copy Constructor
	*/
	SphereVolume(const SphereVolume &obj);

	/** Construct a sphere given center and radius
	*/
	SphereVolume(const Pnt3f &c, float r);

	/** Destructor */
	~SphereVolume();

/*------------------------------ feature ----------------------------------*/

	/// Change the center and radius
	inline void setValue(const Pnt3f &c, float r);

/*------------------------- set values -------------------------------*/

	/// set just the center
	inline void setCenter(const Pnt3f &c); 

	/// set just the radius
	inline void setRadius(float r); 

/*------------------------- get values -------------------------------*/

	/// Returns the center
	inline void getCenter(Pnt3f &center) const; 

	/// Returns the center
	inline const Pnt3f& getCenter( void ) const; 
	
	/// Returns the radius
	inline float getRadius() const;

  /** returns the scalar volume of the volume */
  virtual float getScalarVolume (void) const;

  /** gives the boundaries of the volume */
  virtual void getBounds( Pnt3f &min, Pnt3f &max ) const;


/*-------------------------- extending -----------------------------------*/

	/** extends (if necessary) to contain the given 3D point 
	*/
  virtual void extendBy (const Pnt3f &pt);

	/** extend the volume by the given volume 
	*/
	inline void extendBy (const Volume &volume);   

	/** Extends Box3f (if necessary) to contain given Box3f
	*/
  inline void extendBy(const SphereVolume &bb);


/*-------------------------- intersection ---------------------------------*/

	/** Returns true if intersection of given point and SphereVolume is not empty */
  virtual Bool intersect (const Pnt3f &point) const;

	/** intersect the SphereVolume with the given Line */
	Bool intersect (const Line &line) const;

	/** intersect the SphereVolume with the given Line */
	virtual Bool intersect ( const Line &line, 
							 Real32 &enter, Real32 &exit  ) const;

	/** intersect the SphereVolume with another volume */
	inline Bool intersect (const Volume &volume) const;

	/** Intersect sphere/sphere, returning true if there is an intersection */
	inline Bool intersect(const SphereVolume &sphere) const;

  /** check if the point is on the volume's surface */
  virtual Bool isOnSurface (const Pnt3f &point) const;

/*-------------------------- transformation ---------------------------------*/


  /// Transforms Box3f by matrix
  virtual void transform(const Matrix &mat);


/*-------------------------- output -------------------------------*/

	/** print the volume */
  virtual void dump(	UInt32				uiIndent = 0, 
						const BitVector &	bvFlags = 0) const;

	//-----------------------------------------------------------------------
	//   instance variables                                                  
	//-----------------------------------------------------------------------

	//-----------------------------------------------------------------------
	//   instance functions                                                  
	//-----------------------------------------------------------------------

private:


	//-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	/** center of the sphere
	*/
	Pnt3f _center;
	
	/** radius of the sphere
	*/
	float _radius;

	//-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

	//-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

};

OSG_END_NAMESPACE

#include <OSGSphereVolume.inl>

#endif // _OSGSPHEREVOLUME_H_
