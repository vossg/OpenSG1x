/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
 *                                                                           *
 *          contact: {reiners|vossg}@igd.fhg.de, jbehr@zgdv.de               *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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


#ifndef _OSGGEOPUMPFACTORY_H_
#define _OSGGEOPUMPFACTORY_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class OSGGeometry;
typedef OSGFCPtr<OSGNodeCorePtr, OSGGeometry> OSGGeometryPtr;
class OSGDrawAction;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup Geometry
 *  \brief Pump factory. Selects a fitting pump for the given geometry.
 *
 *  It's not really a factory, as it doesn't create objects, but it's close.
 */

class OSGGeoPumpFactory
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
	
	typedef void (*Pump)( OSGDrawAction * act, OSGGeometry * geo );	
	
	// The pump selection is a two-part process. In the first step the Geometry is 
	// analyzed for its attribute bindings etc. In the second step the actual
	// pump is returned, depending on the capabilities of the Window/Context and 
	// the bindings as represented by a selection.
	
	typedef OSGUInt32 Index;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "OSGGeoPumpFactory"; }
 
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*------------------------- your_category -------------------------------*/

	Index getIndex( OSGGeometry * geo );	

	Pump getPump( OSGDrawAction * act, Index index );
	

    /*------------------------- your_operators ------------------------------*/


    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

    /*--------------------------- access ------------------------------------*/
	
	static OSGGeoPumpFactory& the( void );
	
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

	static OSGGeoPumpFactory _the;
	
    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

	// The pumps, in all their glory.
	
	// The master pump. Can render everything, but takes ages to do so.	
	static void masterPump( OSGDrawAction * act, OSGGeometry * geo );
	
    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// prohibit default functions (move to 'public' if you need one)

    OSGGeoPumpFactory(void);
    virtual ~OSGGeoPumpFactory(void); 
    OSGGeoPumpFactory(const OSGGeoPumpFactory &source);
    void operator =(const OSGGeoPumpFactory &source);
	
};

OSG_END_NAMESPACE

#include "OSGGeoPumpFactory.inl"

#endif /* _OSGGEOPUMPFACTORY_H_ */
