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


#ifndef BOX3F_CLASS_DECLARATION
#define BOX3F_CLASS_DECLARATION

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

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

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------
class OSG_BASE_DLLMAPPING BoxVolume : public Volume {

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
  inline BoxVolume(); 

  /// Constructor given bounds 
  inline BoxVolume ( float xmin, float ymin, float zmin,
										 float xmax, float ymax, float zmax) ;


  /// Constructor given minimum and maximum points 
  inline BoxVolume(const Pnt3f &min, const Pnt3f &max);


  /// Copy Constructor
  inline BoxVolume(const BoxVolume &obj);


  /// Destructor
  inline ~BoxVolume(); 


/*------------------------------ feature ----------------------------------*/

  /// Returns the min and max points
  inline const Pnt3f &getMin() const; 
  inline const Pnt3f &getMax() const; 

  /// Returns the center of a box
  void getCenter(Pnt3f &center) const;

  /** gives the scalar volume of the volume */
  virtual float getScalarVolume (void) const;

  /// set method with center 0,0,0
  inline void setBounds(float w, float h, float d);

  /// set method
  inline void setBounds(float xmin, float ymin, float zmin,
                        float xmax, float ymax, float zmax);
  /// set method
  inline void setBounds(const Pnt3f &min, const Pnt3f &max);

  /// set method
  void setBoundsByCenterAndSize(const Pnt3f &center, const Vec3f &size);

  /// get method
  inline void getBounds(float &xmin, float &ymin, float &zmin,
                        float &xmax, float &ymax, float &zmax ) const;

  /// get method
  inline void getBounds(Pnt3f &min, Pnt3f &max) const;
    
  /// Returns origin (minimum point) of box
  inline void getOrigin(float &originX, float &originY, float &originZ) const;

  /// Returns size of box
  inline void getSize(float &sizeX, float &sizeY, float &sizeZ) const;

  /// Returns the size of the box as vector
  inline void getSize(Vec3f &vec) const;


/*-------------------------- extending ------------------------------------*/

  /** extends (if necessary) to contain the given 3D point */
  virtual void extendBy (const Pnt3f &pt);

  /** extend the volume by the given volume */
  virtual void extendBy (const Volume &volume);   

  /// Extends Box3f (if necessary) to contain given Box3f
  void extendBy(const BoxVolume &bb);


/*-------------------------- intersection ---------------------------------*/

  /// Returns true if intersection of given point and Box3f is not empty
  Bool intersect(const Pnt3f &point) const;

	/** Returns true if intersection of given Line with the box is not empty */  
	Bool intersect (const Line &line) const;

	/** intersect the box with the given Line */
	Bool intersect ( const Line &line, 
		Real32 &min, Real32 &max  ) const;

  /// intersect the volume with another volume 
  virtual Bool intersect (const Volume &volume) const;

  /// Returns true if intersection of given Box3f and Box3f is not empty
  Bool intersect(const BoxVolume &bb) const;

  /** check if the point is on the volume's surface */
  virtual Bool isOnSurface (const Pnt3f &point) const;


/*-------------------------- transformation -------------------------------*/

  /// Transforms Box3f by matrix
  virtual void transform(const Matrix &m);

	
/*-------------------------- operation ------------------------------------*/

  /// Equality comparisons
  friend Bool operator ==(const BoxVolume &b1, const BoxVolume &b2);

  /// Unequality comparisons
  inline friend Bool operator !=(const BoxVolume &b1, const BoxVolume &b2);

  /// Assignment operator
  const BoxVolume &operator =(const BoxVolume &b1);

  /// write values in stream
  friend ostream &operator <<(ostream &os, const BoxVolume &obj);

private:

  /// Minimum point
  Pnt3f _min;

  /// Maximum point
  Pnt3f _max;

};

OSG_END_NAMESPACE

#include <OSGBoxVolume.inl>

#endif // BOX_CLASS_DECLARATION

