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


#ifndef _OSGGEOMETRY_H_
#define _OSGGEOMETRY_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGNodeCore.h>
#include <OSGSFMathTypes.h>
#include <OSGMFMathTypes.h>
#include <OSGMFVecTypes.h>
#include <OSGMFSysTypes.h>
#include <OSGFieldContainerPtr.h>
#include <OSGFieldDescription.h>
#include <OSGGeoProperty.h>
#include <OSGAction.h>
// #include <OSGTriangleIterator.h>
// #include <OSGPrimitiveIterator.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

class OSGGeometry;
typedef OSGFCPtr<OSGNodeCorePtr, OSGGeometry> OSGGeometryPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup baselib
 *  \brief Abstract Geometry base class
 *
 *  The base class for all Geometry node types. Defines the common interface
 *  for all geometry, so for general tools use these interfaces. They are pretty general
 *  and minimal though, so don't expect them to be blindingly fast.
 */

class OSGGeometry : public OSGNodeCore
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_FC_FIRST_FIELD_IDM_DECL(OSGTypesField          )

    OSG_FC_FIELD_IDM_DECL      (OSGLengthsField        )
    OSG_FC_FIELD_IDM_DECL      (OSGPositionsField      )

    OSG_FC_FIELD_IDM_DECL      (OSGNormalsField        )
    OSG_FC_FIELD_IDM_DECL      (OSGNormalPerVertexField)

    OSG_FC_FIELD_IDM_DECL      (OSGColorsField         )
    OSG_FC_FIELD_IDM_DECL      (OSGColorPerVertexField )

    OSG_FC_FIELD_IDM_DECL      (OSGGeoIndexField       )

    OSG_FC_LAST_FIELD_IDM_DECL

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------
	
    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "OSGGeometry"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSG_FIELD_CONTAINER_DECL(OSGGeometryPtr)

    virtual ~OSGGeometry(void); 

    /*------------------------- your_category -------------------------------*/

	/** property access. Returns OSGFCNULL if not set or available. */

	inline OSGGeoPTypePtr		getTypes( void );
	inline void					setTypes( OSGGeoPTypePtr types );

	inline OSGGeoPLengthPtr		getLengths( void );
	inline void					setLengths( OSGGeoPLengthPtr lengths );	
	
	inline OSGGeoPositionPtr	getPositions( void );
	inline void					setPositions( OSGGeoPositionPtr positions );
		
	inline OSGGeoColorPtr		getColors( void );
	inline void					setColors( OSGGeoColorPtr Colors );	
	inline OSGBool				getColorPerVertex( void );
	inline void					setColorPerVertex( OSGBool npv );
		
	inline OSGGeoNormalPtr		getNormals( void );
	inline void					setNormals( OSGGeoNormalPtr normals );	
	inline OSGBool				getNormalPerVertex( void );
	inline void					setNormalPerVertex( OSGBool npv );
	
	// The single index for all attributes. 
	// This will probably move out into a derived class
	inline OSGGeoIndexPtr		getIndex( void );
	inline void					setIndex( OSGGeoIndexPtr index );
	
	// TODO: separate indices, texcoords, ...
	
	/** field access */

	OSGSFGeoPTypePtr		*getSFTypes( void );
	OSGSFGeoPLengthPtr		*getSFLengths( void );
	OSGSFGeoPositionPtr		*getSFPositions( void );
	OSGSFGeoColorPtr		*getSFColors( void );
	OSGSFBool				*getSFColorPerVertex( void );
	OSGSFGeoNormalPtr		*getSFNormals( void );
	OSGSFBool				*getSFNormalPerVertex( void );
	OSGSFGeoIndexPtr		*getSFIndex( void );

    /** pointer */

	OSGGeometryPtr getPtr(void);
	
	/** updates */
	
	void adjustVolume( OSGVolume & volume );
	
	/** Triangle iterator functions */
	
	
	/** Primitive iterator functions */

    /*------------------------------ dump -----------------------------------*/

    virtual void dump(void) const;

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

    OSGGeometry(void);
    OSGGeometry(const OSGGeometry &source);

    virtual void changed(OSGBitVector whichField, OSGChangeMode from);
	
    /*------------------------------ Actions --------------------------------*/
	
	// execute the OpenGL commands to draw the geometry	
	OSGAction::ResultE draw(OSGAction * action );
	
  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGNodeCore Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class OSGFieldContainer;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

	static OSGFieldDescription   _desc[];

	static OSGFieldContainerType _type;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

	static void   initMethod (void);
 
    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

	OSGSFGeoPTypePtr    _types;
	
	OSGSFGeoPLengthPtr  _lengths;
	
	OSGSFGeoPositionPtr _positions;
	
	OSGSFGeoNormalPtr   _normals;
	OSGSFBool           _normalsPerVertex;
	
	OSGSFGeoColorPtr    _colors;
	OSGSFBool           _colorsPerVertex;
	
	OSGSFGeoIndexPtr    _index;
	
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// prohibit default functions (move to 'public' if you need one)

    void operator =(const OSGGeometry &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

extern OSGGeometryPtr OSGNullGeo;


// Single index geometry  
OSG_END_NAMESPACE

#include "OSGGeometry.inl"

#endif /* _OSGTRANSFORM_H_ */
