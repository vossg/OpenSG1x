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

#ifndef DYNAMICVOLUME_CLASS_DECLARATION
#define DYNAMICVOLUME_CLASS_DECLARATION

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>

#include <OSGVolume.h>


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

/** 3D base volume.
*/

class OSG_BASE_DLLMAPPING DynamicVolume : public Volume {
		
public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

	enum Type { BOX_VOLUME, SPHERE_VOLUME };    

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

	Type _type;

	UChar8 _volumeMem [32];

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

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

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

/*-------------------------- constructor ----------------------------------*/

  /** Default Constructor */
  DynamicVolume (Type type = BOX_VOLUME );

  /** Copy Constructor */
    DynamicVolume (const DynamicVolume &obj);

/*-------------------------- destructor -----------------------------------*/

  /** Destructor */
  virtual ~DynamicVolume (void) {;}

/*------------------------------ feature ----------------------------------*/

	/** */
	Volume & getInstance (void) const { return *((OSG::Volume*)(_volumeMem)); }

	/** */
	Type getType (void) const { return _type; }

	/** */
	void setVolumeType (Type type);

	/** */
	void morphToType (Type type);

	/** */
	DynamicVolume & operator = (const DynamicVolume &source);


/*------------------------- get values -------------------------------*/

  /** gives the center of the volume */
  virtual void getCenter (Pnt3f &center) const ;

  /** gives the scalar volume of the volume */
  virtual float getScalarVolume (void) const ;

  /** gives the boundaries of the volume */
  virtual void getBounds( Pnt3f &min, Pnt3f &max ) const ;


/*-------------------------- extending ------------------------------------*/

  /** extends (if necessary) to contain the given 3D point */
  virtual void extendBy (const Pnt3f &pt) ;

  /** extend the volume by the given volume */
  virtual void extendBy (const Volume &volume) ;   

/*-------------------------- intersection ---------------------------------*/

  /** Returns true if intersection of given point and Volume is not empty */
  virtual Bool intersect (const Pnt3f &point) const ;

	/** intersect the volume with the given Line */
	virtual Bool intersect (const Line &line ) const ;

	/** intersect the volume with the given Line */
	virtual Bool intersect ( const Line &line, 
													 Real32 &enter, Real32 &exit  ) const ;

  /** intersect the volume with another volume */
  virtual Bool intersect (const Volume &volume) const ;

  /** check if the point is on the volume's surface */
  virtual Bool isOnSurface (const Pnt3f &point) const ;

/*-------------------------- transformation -------------------------------*/


	/** transform the volume bye the given matrix*/
  virtual void transform (const Matrix &matrix);


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

};

OSG_BASE_DLLMAPPING
ostream &operator <<(ostream &outStream,
                     const DynamicVolume &vol);

typedef DynamicVolume* DynamicVolumeP;

OSG_END_NAMESPACE

#include "OSGDynamicVolume.inl"

#endif // OSGDYNAMICVOLUME_CLASS_DECLARATION
