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

class Geometry;
typedef FCPtr<NodeCorePtr, Geometry> GeometryPtr;

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

class OSG_DLLEXPORT Geometry : public NodeCore
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_FC_FIRST_FIELD_IDM_DECL(TypesField          )

    OSG_FC_FIELD_IDM_DECL      (LengthsField        )
    OSG_FC_FIELD_IDM_DECL      (PositionsField      )

    OSG_FC_FIELD_IDM_DECL      (NormalsField        )
    OSG_FC_FIELD_IDM_DECL      (NormalPerVertexField)

    OSG_FC_FIELD_IDM_DECL      (ColorsField         )
    OSG_FC_FIELD_IDM_DECL      (ColorPerVertexField )

    OSG_FC_FIELD_IDM_DECL      (GeoIndexField       )

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

    static const char *getClassname(void) { return "Geometry"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSG_FIELD_CONTAINER_DECL(GeometryPtr)

    /*------------------------- your_category -------------------------------*/

    /** property access. Returns FCNULL if not set or available. */

    inline GeoPTypePtr      getTypes( void );
    inline void             setTypes( GeoPTypePtr types );

    inline GeoPLengthPtr    getLengths( void );
    inline void             setLengths( GeoPLengthPtr lengths );    
    
    inline GeoPositionPtr   getPositions( void );
    inline void             setPositions( GeoPositionPtr positions );
        
    inline GeoColorPtr      getColors( void );
    inline void             setColors( GeoColorPtr Colors );    
    inline Bool             getColorPerVertex( void );
    inline void             setColorPerVertex( Bool npv );
        
    inline GeoNormalPtr     getNormals( void );
    inline void             setNormals( GeoNormalPtr normals ); 
    inline Bool             getNormalPerVertex( void );
    inline void             setNormalPerVertex( Bool npv );
    
    // The single index for all attributes. 
    // This will probably move out into a derived class
    inline GeoIndexPtr      getIndex( void );
    inline void             setIndex( GeoIndexPtr index );
    
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

    /** pointer */

    GeometryPtr getPtr(void);
    
    /** updates */
    
    void adjustVolume( Volume & volume );
    
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

    Geometry(void);
    Geometry(const Geometry &source);
    virtual ~Geometry(void); 

    virtual void changed(BitVector whichField, ChangeMode from);
    
    /*------------------------------ Actions --------------------------------*/
    
    // execute the OpenGL commands to draw the geometry 
    Action::ResultE draw(Action * action );
    
  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef NodeCore Inherited;

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
    
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const Geometry &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

extern GeometryPtr NullGeo;


// Single index geometry  
OSG_END_NAMESPACE

#include "OSGGeometry.inl"

#endif /* _OSGTRANSFORM_H_ */
