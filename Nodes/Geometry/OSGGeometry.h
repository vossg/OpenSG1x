/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
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


#ifndef _OSGGEOMETRY_H_
#define _OSGGEOMETRY_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGGeometryBase.h>
#include <OSGBaseTypes.h>
#include <OSGNodeCore.h>
#include <OSGSFMathTypes.h>
#include <OSGMFMathTypes.h>
#include <OSGMFVecTypes.h>
#include <OSGMFSysTypes.h>
#include <OSGFieldContainerPtr.h>
#include <OSGFieldDescription.h>
#include <OSGAction.h>
#include <OSGMaterial.h>

#include <OSGGeoPropFields.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

class Geometry;
typedef FCPtr<NodeCorePtr, Geometry> GeometryPtr;

// Iterators
class TriangleIterator;
class PrimitiveIterator;
class FaceIterator;

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

class OSG_GEOMETRY_DLLMAPPING Geometry : public NodeCore
{
  private:

    typedef NodeCore Inherited;

  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_FC_FIRST_FIELD_IDM_DECL(TypesField                                )

    OSG_FC_FIELD_IDM_DECL      (LengthsField,         TypesField          )
    OSG_FC_FIELD_IDM_DECL      (PositionsField,       LengthsField        )

    OSG_FC_FIELD_IDM_DECL      (NormalsField,         PositionsField      )
    OSG_FC_FIELD_IDM_DECL      (NormalPerVertexField, NormalsField        )

    OSG_FC_FIELD_IDM_DECL      (ColorsField,          NormalPerVertexField)
    OSG_FC_FIELD_IDM_DECL      (ColorPerVertexField,  ColorsField         )

    OSG_FC_FIELD_IDM_DECL      (GeoIndexField,        ColorPerVertexField )

    OSG_FC_FIELD_IDM_DECL      (MaterialField,        GeoIndexField       )

    OSG_FC_LAST_FIELD_IDM_DECL (MaterialField                              )

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------
    
    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "Geometry"; };

	// map the primitive type to a name
    static const char *mapType( UInt8 type );

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSG_FIELD_CONTAINER_DECL(GeometryPtr)

    /*------------------------- your_category -------------------------------*/

    /** property access. Returns FCNULL if not set or available. */

    inline GeoPTypePtr      getTypes( void ) const;
    inline void             setTypes( GeoPTypePtr types );

    inline GeoPLengthPtr    getLengths( void ) const;
    inline void             setLengths( GeoPLengthPtr lengths );    
    
    inline GeoPositionPtr   getPositions( void ) const;
    inline void             setPositions( GeoPositionPtr positions );
        
    inline GeoColorPtr      getColors( void ) const;
    inline void             setColors( GeoColorPtr Colors );    
    inline Bool             getColorPerVertex( void ) const;
    inline void             setColorPerVertex( Bool npv );
        
    inline GeoNormalPtr     getNormals( void ) const;
    inline void             setNormals( GeoNormalPtr normals ); 
    inline Bool             getNormalPerVertex( void ) const;
    inline void             setNormalPerVertex( Bool npv );
    
    // The single index for all attributes. 
    // This will probably move out into a derived class
    inline GeoIndexPtr      getIndex( void ) const;
    inline void             setIndex( GeoIndexPtr index );
	
	inline MaterialPtr		getMaterial( void ) const;
	inline void					setMaterial( MaterialPtr material );
    
    // TODO: separate indices, texcoords, ...
    
    /** field access */

    SFGeoPTypePtr       *getSFTypes( void );
    SFGeoPLengthPtr     *getSFLengths( void );
    SFGeoPositionPtr    *getSFPositions( void );
    SFGeoColorPtr       *getSFColors( void );
    SFBool              *getSFColorPerVertex( void );
    SFGeoNormalPtr      *getSFNormals( void );
    SFBool              *getSFNormalPerVertex( void );
    SFGeoIndexPtr       *getSFIndex( void );
	SFMaterialPtr		*getSFMaterial( void );

    /** pointer */

    GeometryPtr getPtr(void) const;
    
    /** updates */
    
    void adjustVolume( Volume & volume );
    
    /** Triangle iterator functions */
    
	TriangleIterator beginTriangles( void ) const;
	TriangleIterator endTriangles  ( void ) const;

    
    /** Primitive iterator functions */

	PrimitiveIterator beginPrimitives( void ) const;
	PrimitiveIterator endPrimitives  ( void ) const;
	
    
    /** Face iterator functions */

	FaceIterator beginFaces( void ) const;
	FaceIterator endFaces  ( void ) const;

    /*------------------------------ dump -----------------------------------*/

    virtual void dump(void) const;
	
    /*------------------------------ Actions --------------------------------*/
	
	// execute the OpenGL commands to draw the geometry	
	Action::ResultE doDraw(Action * action );
	
	// low-level OpenGL calls, ignoring materials	
	Action::ResultE draw(Action * action );

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

    Geometry(void);
    Geometry(const Geometry &source);
    virtual ~Geometry(void); 

    virtual void changed(BitVector whichField, ChangeMode from);
    
    /*------------------------------ Actions --------------------------------*/
    
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

    friend class FieldContainer;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    static char cvsid[];

    static FieldDescription   _desc[];

    static FieldContainerType _type;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static void   initMethod (void);
 
    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    SFGeoPTypePtr    _types;
    
    SFGeoPLengthPtr  _lengths;
    
    SFGeoPositionPtr _positions;
    
    SFGeoNormalPtr   _normals;
    SFBool           _normalsPerVertex;
    
    SFGeoColorPtr    _colors;
    SFBool           _colorsPerVertex;
    
    SFGeoIndexPtr    _index;
    
	SFMaterialPtr _material;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const Geometry &source);
	
	// intersect action: ray test	
	Action::ResultE intersect(Action * action );

};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

extern OSG_GEOMETRY_DLLMAPPING GeometryPtr NullGeo;

// Single index geometry  
OSG_END_NAMESPACE

#include "OSGGeometry.inl"

#endif /* _OSGTRANSFORM_H_ */
