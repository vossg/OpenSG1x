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


#ifndef _OSGTRIANGLEITERATOR_H_
#define _OSGTRIANGLEITERATOR_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGFieldContainerPtr.h>
#include <OSGNodeCore.h>
#include <OSGGeoProperty.h>
#include <OSGPrimitiveIterator.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class Geometry;
typedef FCPtr<NodeCorePtr, Geometry> GeometryPtr;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief The TriangleIterator allows iteration through triangles.
 *  \ingroup GeoIterators
 */

class OSG_SYSTEMLIB_DLLMAPPING TriangleIterator
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "TriangleIterator"; }
 
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    TriangleIterator( void );

	// used by geometry to create them. useful for seeking	
    TriangleIterator( const GeometryPtr& geo );
    TriangleIterator( const NodePtr& geo );

    TriangleIterator(const TriangleIterator &source);
	
    virtual ~TriangleIterator(void); 

    /*------------------------- access -------------------------------*/

	// get the triangle index
	inline Int32    	getIndex		( void 	      ) const;

	// type of currently processed primitive
	inline UInt32 		getType			( void ) const;

	// get the data indices/values. Indices < 0 indicate data not present
	// in that case the value will be Nullxxx

	inline Int32    	getPositionIndex	( Int32 which ) const;
	inline Pnt3f		getPosition			( Int32 which ) const;

	inline Int32    	getNormalIndex		( Int32 which ) const;
	inline Vec3f   		getNormal	 		( Int32 which ) const;

	inline Int32    	getColorIndex 		( Int32 which ) const;
	inline Color3f		getColor			( Int32 which ) const;

	inline Int32    	getTexCoordsIndex 	( Int32 which ) const;
	inline Vec2f		getTexCoords		( Int32 which ) const;


    /*------------------------- your_operators ------------------------------*/

    void operator ++( void );

	// seek from the beginning to triangle with index index
	void seek( Int32 index );

    /*------------------------- assignment ----------------------------------*/

    TriangleIterator & operator =(const TriangleIterator &source);

    /*------------------------- comparison ----------------------------------*/

    Bool operator < (const TriangleIterator &other) const;
    
	Bool operator == (const TriangleIterator &other) const;
	Bool operator != (const TriangleIterator &other) const;
 
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

	void setToBegin( void );
	void setToEnd( void );
	
  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

	friend class Geometry;
	
    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------
	
	// the primitive Iterator it's based on
	PrimitiveIterator _primIt;
	
	// the geometry (for faster access)
	GeometryPtr 	_geo;
	
	// Mainly for statistics.
	Int32 			_triIndex;
	
	// index of the first actual point within the active primitive
	// this is the index into the primitive
	UInt32 			_actPrimIndex;
	
	// indices of the actual triangels' points
	// these are indices into the primtive's indices, not actual indices
	Int32 			_triPntIndex[3];
	

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// called when stepping to next primitive, and at beginning
	void startPrim( void );
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef TriangleIterator *TriangleIteratorP;

OSG_END_NAMESPACE

#include "OSGTriangleIterator.inl"

#endif /* _OSGTRIANGLEITERATOR_H_ */
