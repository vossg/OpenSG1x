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

#ifndef _OSGGEOPUMPFACTORY_H_
#define _OSGGEOPUMPFACTORY_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGGeometry.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class Window;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup GeometryLib
 *  \brief Pump factory. Selects a fitting pump for the given geometry.
 *
 *  It's not really a factory, as it doesn't create objects, but it's close.
 */

class OSG_SYSTEMLIB_DLLMAPPING GeoPumpFactory
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------
	
	// The pump selection is a two-part process. In the first step the Geometry is 
	// analyzed for its attribute bindings etc. In the second step the actual
	// pump is returned, depending on the capabilities of the Window/Context and 
	// the bindings as represented by a selection.
	
	typedef UInt32 Index;
	
	// The simple pump type. Draws the whole geometry. Useful as it uses
	// the minimal number of parameters.
	
	typedef void (*GeoPump)( Window *win, Geometry * geo );	
	
	// The partial pump type. Draws a part of the geometry. 
	
	typedef void (*PartialGeoPump)( Window *win, Geometry * geo,
	    UInt32 primtype, UInt32 firstvert, UInt32 nvert );	
	
	// The interface pump type. Draws the whole geometry. More flexible
	// than the GeoPump, as the interfaces can originate in different 
	// objects.
	
	typedef void (*InterfacePump)( Window *win, 
	    GeoPositionInterface *pos, GeoNormalInterface *norm,
	    GeoColorInterface *col, GeoTexCoordsInterface *texcoords,
	    GeoTexCoordsInterface *texcoords2,
	    GeoTexCoordsInterface *texcoords3,
	    GeoTexCoordsInterface *texcoords4,
	    GeoPTypeInterface *type, GeoPLengthInterface *len,
	    GeoIndexInterface *ind, UInt16 *map, UInt16 nmap );	
	
	// The partial interface pump type. Similar to the interface pump, but 
	// it can draw parts of the object.
	
	typedef void (*PartialInterfacePump)( Window *win, 
	    GeoPositionInterface *pos, GeoNormalInterface *norm,
	    GeoColorInterface *col, GeoTexCoordsInterface *texcoords,
	    GeoTexCoordsInterface *texcoords2,
	    GeoTexCoordsInterface *texcoords3,
	    GeoTexCoordsInterface *texcoords4,
	    GeoPTypeInterface *type, GeoPLengthInterface *len,
	    GeoIndexInterface *ind, UInt16 *map, UInt16 nmap,
	    UInt32 primtype, UInt32 firstvert, UInt32 nvert );	

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "GeoPumpFactory"; }
 
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    virtual ~GeoPumpFactory(void); 

    /*------------------------- your_category -------------------------------*/

	Index                getIndex( Geometry * geo );	

	GeoPump              getGeoPump      ( Window *win, Index index );

	PartialGeoPump       getPartialGeoPump(Window *win, Index index );

	InterfacePump        getInterfacePump( Window *win, Index index );

	PartialInterfacePump getPartialInterfacePump( Window *win, 
	                                                Index index );
	

    /*------------------------- your_operators ------------------------------*/


    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

    /*--------------------------- access ------------------------------------*/
	
	static GeoPumpFactory& the( void );
	
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

	// To allow cascading of pump factories the next one in the chain needs to 
	// know how many indices are used up by the lower one. This function 
	// returns the number of indices used (i.e. the max used index + 1).
	
	Index numIndices( void );

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    GeoPumpFactory(void);

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

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

	static GeoPumpFactory _the;
	
    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

	// The pumps, in all their glory.
	
	// The master pump. Can render everything, but takes ages to do so.	
	static void masterGeoPump( Window *win, Geometry *geo );
		
	static void masterPartialGeoPump( Window *win, Geometry *geo,
	    UInt32 primtype, UInt32 firstvert, UInt32 nvert );	
	
	static void masterInterfacePump( Window *win, 
	    GeoPositionInterface *pos, GeoNormalInterface *norm,
	    GeoColorInterface *col, GeoTexCoordsInterface *texcoords,
	    GeoTexCoordsInterface *texcoords2,
	    GeoTexCoordsInterface *texcoords3,
	    GeoTexCoordsInterface *texcoords4,
	    GeoPTypeInterface *type, GeoPLengthInterface*len,
	    GeoIndexInterface *ind, UInt16 *map, UInt16 nmap );	
	
	static void masterPartialInterfacePump( Window *win, 
	    GeoPositionInterface *pos, GeoNormalInterface *norm,
	    GeoColorInterface *col, GeoTexCoordsInterface *texcoords,
	    GeoTexCoordsInterface *texcoords2,
	    GeoTexCoordsInterface *texcoords3,
	    GeoTexCoordsInterface *texcoords4,
	    GeoPTypeInterface *type, GeoPLengthInterface*len,
	    GeoIndexInterface *ind, UInt16 *map, UInt16 nmap,
	    UInt32 primtype, UInt32 firstvert, UInt32 nvert );	
	
    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// prohibit default functions (move to 'public' if you need one)

    GeoPumpFactory(const GeoPumpFactory &source);
    void operator =(const GeoPumpFactory &source);
	
};

OSG_END_NAMESPACE

#include "OSGGeoPumpFactory.inl"

#endif /* _OSGGEOPUMPFACTORY_H_ */
