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


#ifndef _OSGPRIMITIVEITERATOR_H_
#define _OSGPRIMITIVEITERATOR_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGFieldContainerPtr.h>
#include <OSGNodeCore.h>
#include <OSGSystemDef.h>
#include <OSGGeoProperty.h>

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
 
/*! \brief The PrimitiveIterator iterates through a geometry one primitive
 *  at a time.
 *  \ingroup GeoIterators
 */

class OSG_SYSTEMLIB_DLLMAPPING PrimitiveIterator 
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

    static const char *getClassname(void) { return "PrimitiveIterator"; }
 
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    PrimitiveIterator( void );
 
    PrimitiveIterator(const PrimitiveIterator &source);

    PrimitiveIterator( const GeometryPtr& geo );
    PrimitiveIterator( const NodePtr& geo );
 
    virtual ~PrimitiveIterator(void); 


	void setGeo(  const GeometryPtr& geo );
	void setGeo(  const NodePtr& geo );

	void setToBegin( void );
	void setToEnd( void );
	
    /*------------------------- access -------------------------------*/

	// check for end
	inline Bool    		isAtEnd			( void 	      ) const;

	// get the primitive information
	inline Int32    	getIndex		( void 	      ) const;
	inline UInt32    	getLength		( void 	      ) const;
	inline UInt32    	getType			( void 	      ) const;

	// get the data indices/values. Indices < 0 indicate data not present
	// in that case the value will be Nullxxx

	inline Int32    	getPositionIndex( Int32 which ) const;
	inline Pnt3f		getPosition		( Int32 which ) const;

	inline Int32    	getNormalIndex	( Int32 which ) const;
	inline Vec3f   		getNormal	 	( Int32 which ) const;

	inline Int32    	getColorIndex 	( Int32 which ) const;
	inline Color3f		getColor		( Int32 which ) const;

	inline Int32    	getTexCoordsIndex 	( Int32 which ) const;
	inline Vec2f		getTexCoords		( Int32 which ) const;

	inline Int32    	getIndexIndex	( Int32 which ) const;

	// TODO add texture coordinates

    /*------------------------- your_operators ------------------------------*/

    void operator ++( void );
	
	// seek the iterator to the index-th primitive
	void seek( Int32 index );

    /*------------------------- assignment ----------------------------------*/

    PrimitiveIterator & operator =(const PrimitiveIterator &source);

    /*------------------------- comparison ----------------------------------*/

    Bool operator < (const PrimitiveIterator &other) const;
    
	Bool operator == (const PrimitiveIterator &other) const;
	Bool operator != (const PrimitiveIterator &other) const;

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

	// The geometry being iterated.
	GeometryPtr 	_geo; 

	// Flag for having reached the end.
	// isAtEnd() caught some very strange compiler bug on sgi, 
	// so this is a workaround. Try it again with the next version.
	Bool 			_ended; 

	// index of the active primitive
	UInt32 			_primIndex;
	
	// index of the first actual point within the active primitive
	// this is an index into the index field, not an actual index
	UInt32 			_actPointIndex;
	
	// type and length of the active primitive
	UInt32  		_actPrimType;
	UInt32 			_actPrimLength;
	
	// cached for speed
	// Not using the direct fields to allow passing the iterator between 
	// processes
	GeoPTypePtr 	_types;
	GeoPLengthPtr 	_lengths;
	GeoIndexPtr 	_indices;

	// inverse mappings for faster access
	UInt16 _nmappings;
	Int16  _positionIndex;
	Int16  _normalIndex;
	Int16  _colorIndex;
	Int16  _texcoordsIndex;
	

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef PrimitiveIterator *PrimitiveIteratorP;

OSG_END_NAMESPACE

#include "OSGPrimitiveIterator.inl"

#endif /* _OSGPRIMITIVEITERATOR_H_ */
