/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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


//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>

#include "OSGVector.h"
#include "OSGMatrix.h"
#include "OSGLine.h"

#include "OSGVolumeFunctions.h"

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

/* 3D base volume.
 *
 *
 * @author jbehr, Wed Feb 16 20:04:15 2000
 */

class OSG_BASE_DLLMAPPING Volume {

private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

	// need the prefix, collides with some compiler symbols otherwise
	
	enum State 
	{
		OSGVALID    = 1,
		OSGEMPTY    = 2,
		OSGSTATIC   = 4,
		OSGINFINITE = 8
	};

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

	//-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------


protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	UInt16 _state;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

	/*-------------------------- constructor ----------------------------------*/

  /** Default Constructor */
	Volume (void ) : _state( OSGVALID | OSGEMPTY) {;}

  /** Copy Constructor */
  Volume (const Volume &obj) : _state(obj._state) {;}

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

	//-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------


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

/*-------------------------- destructor -----------------------------------*/

  /** Destructor */
  virtual ~Volume (void) {;}


/*-------------------------- state -----------------------------------------*/

  /** set the volume to contain nothing */
	inline void setValid (const Bool value); 

  /**  Checks if the volume is valid */
	inline Bool isValid (void) const; 

  /** set the volume to contain nothing */
	inline void setEmpty (const Bool value); 

  /**  Checks if the volume is empty */
	inline Bool isEmpty (void) const; 

  /** set the volume to contain nothing */
	inline void setStatic (const Bool value); 

  /**  Checks if the volume is static */
	inline Bool isStatic (void) const;

  /** set the volume to contain nothing */
	inline void setInfinite (const Bool value); 

  /**  Checks if the volume is infinite */
	inline Bool isInfinite (void) const; 



/*------------------------- get values -------------------------------*/

  /** gives the center of the volume */
  virtual void getCenter (Pnt3f &center) const = 0;

  /** gives the scalar volume of the volume */
  virtual float getScalarVolume (void) const = 0;

  /** gives the boundaries of the volume */
  virtual void getBounds( Pnt3f &min, Pnt3f &max ) const = 0;


/*-------------------------- extending ------------------------------------*/

  /** extends (if necessary) to contain the given 3D point */
  virtual void extendBy (const Pnt3f &pt) = 0;

  /** extend the volume by the given volume */
  virtual void extendBy (const Volume &volume) = 0;   

/*-------------------------- intersection ---------------------------------*/

  /** Returns true if intersection of given point and Volume is not empty */
  virtual Bool intersect (const Pnt3f &point) const = 0;

	/** intersect the volume with the given Line */
	virtual Bool intersect (const Line &line ) const = 0;

	/** intersect the volume with the given Line */
	virtual Bool intersect ( const Line &line, 
													 Real32 &enter, Real32 &exit  ) const = 0;

  /** intersect the volume with another volume */
  virtual Bool intersect (const Volume &volume) const = 0;

  /** check if the point is on the volume's surface */
  virtual Bool isOnSurface (const Pnt3f &point) const = 0;


/*-------------------------- transformation -------------------------------*/


	/** transform the volume bye the given matrix*/
  virtual void transform (const Matrix &matrix) = 0;


/*-------------------------- output -------------------------------*/


	/** print the volume */
  virtual void dump(	UInt32				uiIndent = 0, 
						const BitVector &	bvFlags = 0) const = 0;

			
	//-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

	//-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

			
};

typedef Volume* VolumeP;

//! helper functions to dump a volume. Useful for debuggers.
OSG_BASE_DLLMAPPING void  volDump( Volume * vol );


OSG_END_NAMESPACE

#include <OSGVolume.inl>

#endif // VOLUME_CLASS_DECLARATION
