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

class Geometry;
typedef FCPtr<NodeCorePtr, Geometry> GeometryPtr;
class DrawAction;

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

class OSG_GEOMETRY_DLLMAPPING GeoPumpFactory
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------
	
	// It would be nicer and more flexible if the pump took the arrays separately,
	// but that would a LOT of parameters, which is not a good idea for Intel
	// systems, AFAIK.
	
	typedef void (*Pump)( DrawAction * act, Geometry * geo );	
	
	// The pump selection is a two-part process. In the first step the Geometry is 
	// analyzed for its attribute bindings etc. In the second step the actual
	// pump is returned, depending on the capabilities of the Window/Context and 
	// the bindings as represented by a selection.
	
	typedef UInt32 Index;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "GeoPumpFactory"; }
 
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*------------------------- your_category -------------------------------*/

	Index getIndex( Geometry * geo );	

	Pump getPump( DrawAction * act, Index index );
	

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
	static void masterPump( DrawAction * act, Geometry * geo );
	
    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// prohibit default functions (move to 'public' if you need one)

    GeoPumpFactory(void);
    virtual ~GeoPumpFactory(void); 
    GeoPumpFactory(const GeoPumpFactory &source);
    void operator =(const GeoPumpFactory &source);
	
};

OSG_END_NAMESPACE

#include "OSGGeoPumpFactory.inl"

#endif /* _OSGGEOPUMPFACTORY_H_ */
