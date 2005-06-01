/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000,2001,2002 by the OpenSG Forum                *
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

//-----------------------------------------------------------------------------
//                                 Includes                                    
//-----------------------------------------------------------------------------


#ifndef _OSGEXTRUSIONGEOMETRY_H_
#define _OSGEXTRUSIONGEOMETRY_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGQuaternion.h>
#include <OSGNode.h>
#include <OSGGeoPropPtrs.h>
#include <OSGGeometry.h>

#include <vector>
#include <map>


OSG_BEGIN_NAMESPACE


//-----------------------------------------------------------------------------
//                      Exported Construction Functions                        
//-----------------------------------------------------------------------------


OSG_SYSTEMLIB_DLLMAPPING 
NodePtr    makeExtrusion    (const std::vector<Pnt2f> &crossSection,
                             const std::vector<Quaternion> &orientation,
                             const std::vector<Vec2f> &scale,
                             const std::vector<Pnt3f> &spine,
                             Real32 creaseAngle,
                             bool beginCap, 
                             bool endCap,
                             bool ccw, 
                             bool convex,
                             bool buildNormal,
                             bool buildTexCoord,
                             UInt32 numOfSubdivision);

OSG_SYSTEMLIB_DLLMAPPING 
GeometryPtr makeExtrusionGeo(const std::vector<Pnt2f> &crossSection,
                             const std::vector<Quaternion> &orientation,
                             const std::vector<Vec2f> &scale,
                             const std::vector<Pnt3f> &spine,
                             Real32 creaseAngle,
                             bool beginCap,
                             bool endCap, 
                             bool ccw,
                             bool convex,
                             bool buildNormal,
                             bool buildTexCoord,
                             UInt32 numOfSubdivision);


//-----------------------------------------------------------------------------
//                             X3D Default Data                                
//-----------------------------------------------------------------------------

/** \brief The default number of points in the cross-section */
static const UInt32 DEF_N_CROSS_SECTION_POINTS = 5;

/** \brief The default number of scale parameters */
static const UInt32 DEF_N_SCALE_PARAMS = 1;

/** \brief The default number of points in the spine */
static const UInt32 DEF_N_SPINE_POINTS = 2;

/** \brief The default number of orientation parameters */
static const UInt32 DEF_N_ORIENTATION_PARAMS = 1;

/** \brief The default cross-section */
static const Real32 
DEF_CROSS_SECTION[DEF_N_CROSS_SECTION_POINTS][2] = {{ 1.0,  1.0}, 
                                                    { 1.0, -1.0},
                                                    {-1.0, -1.0},
                                                    {-1.0,  1.0},
                                                    { 1.0,  1.0}};
/** \brief The default scale parameters */
static const Real32 
DEF_SCALE[DEF_N_SCALE_PARAMS][2] = {{ 1.f, 1.f }};

/** \brief The default spine */
static const Real32 
DEF_SPINE[DEF_N_SPINE_POINTS][3] = {{ 0.f, 0.f, 0.f}, 
                                    { 0.f, 1.f, 0.f}};

/** \brief The default orientation parameters */
static const Real32 
DEF_ORIENTATION[DEF_N_ORIENTATION_PARAMS][4] = {{0.f, 0.f, 1.f, 0.f}};


/** \brief Encapsulates the data of an X3D extrusion surface
 *  Not intended to be directly used. Use construction functions
 *  \ref makeExtrusion and \ref makeExtrusionGeo instead
 */
class ExtrusionSurface
{

    /*==========================  PUBLIC  =================================*/
public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Constructors                              */
    /*! \{                                                                 */
    
    /** 
     * \brief Constructor initializing an extrusion surface.
     *
     * @param crossSection The cross-section of the sweep surface
     * @param orientation The orientation rotating the cross-section out of the
     *                    XZ-plane
     * @param scale The scale values scaling the cross-section
     * @param spine The spine curve along which the cross-section is extruded
     * @param creaseAngle Determines when normals are smoothed between
     *                    adjacent quads
     * @param beginCap Determines whether a begin cap is to created 
     * @param endCap   Determines whether an end cap is to be created
     *
     * @param ccw Determines the ordering of the primitive vertices
     *            with respect to the generated normals
     * @param convex Determines whether the cross-section is convex
     * @param buildNormal Determines  whether normals are calculated
     * @param buildTexCoord Determines whether texture coordinates are created
     */
    ExtrusionSurface(const std::vector<Pnt2f> &crossSection,
                     const std::vector<Quaternion> &orientation,
                     const std::vector<Vec2f> &scale,
                     const std::vector<Pnt3f> &spine,
                     Real32 creaseAngle  = 0.f,
                     bool beginCap       = true,
                     bool endCap         = true,
                     bool ccw            = true,
                     bool convex         = true,
                     bool buildNormal    = true,
                     bool buildTexCoord  = true);
    
    /*! \}                                                                 */

    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    /** 
     * \brief Creates a multi-indexed %Geometry representing the
     * extrusion surface
     * Invoked by the construction function makeExtrusionGeo and makeExtrusion
     * 
     * \param nSubDivisions The number of subdivisions to apply
     * \return A pointer to a newly created geometry containing the surface
     */
    GeometryPtr createGeometry(UInt32 nSubDivisions);

    /*! \}                                                                 */

    /*==========================  PROTECTED  ===============================*/
protected:


    /*==========================  PRIVATE  =================================*/
private:

    /*---------------------------------------------------------------------*/
    /*! \name                    Constructors                              */
    /*! \{                                                                 */

    /*!\brief prohibit default function (move to 'public' if needed) */
    ExtrusionSurface(void);    

    /*! \}                                                                 */

    /*!\brief prohibit default function (move to 'public' if needed) */
    ExtrusionSurface(const ExtrusionSurface &source);

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const ExtrusionSurface &source);

#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)
    
/*! \ingroup STLHelpers
  vector comparison */

    template<class type>
        struct vecless
        {
            inline bool operator () (const type &a, const type &b) const;
        };

#endif

    /*---------------------------------------------------------------------*/
    /*                      Internally Used Types                          */
    /*---------------------------------------------------------------------*/

    /** A vertex of the sweep surface */
    struct Vertex
    {
        Pnt3f position;
        Vec3f normal;
        Vec2f texCoord;

        /** The adjacent face normals */
        Vec3f adjFaceNormals[4];
    };

    typedef std::vector<Pnt3f>::const_iterator Pnt3fConstIt;
    typedef std::vector<Matrix>::const_iterator MatrixConstIt;
    typedef std::pair<Pnt3fConstIt, Pnt3fConstIt> Pnt3fConstItPair;

    typedef std::vector< std::vector< Vertex > >  VertexGrid;

    typedef std::map<Pnt3f, UInt32, vecless<Pnt3f> > PositionMap;
    typedef std::map<Vec3f, UInt32, vecless<Vec3f> > NormalMap;
    typedef std::map<Vec2f, UInt32, vecless<Vec2f> > TexCoordMap;


//-----------------------------------------------------------------------------
//                              Private Fields                                 
//-----------------------------------------------------------------------------

    /** The cross section of the extrusion surface */
    std::vector<Pnt2f> _crossSection;

    /** The orientation values rotating the cross section plane (CP) in R^3*/
    std::vector<Quaternion> _orientation;

    /** The cross-section scale parameters of the extrusion surface */
    std::vector<Vec2f> _scale;

    /** The spine of the extrusion surface */
    std::vector<Pnt3f> _spine;

    /** The crease angle of the extrusion surface */
    Real32 _creaseAngle;

    /** If true, a begin cap is to be generated */
    bool _beginCap;

    /** If true, an end cap is to be generated */
    bool _endCap;

    /** If true, the ordering of the generated primitives is ccw w.r.t.
     *  the generated normals
     */
    bool _ccw;

    /** If true, the cross section is assumed to be convex */
    bool _convex;

    /**
     *  If true, the cross section of the extrusion surface is assumend to be
     *  closed
     */
    bool _crossSectionClosed;

    /** If true, the spine of the extrusion surface is assumed to be closed */
    bool _spineClosed;

    /** If true, the spine contains at least one non-trivial collinear
     *  segment and all other parts consist of coinciding points
     */
    bool _spineCollinear;

    /** If true, all points of the spine coincide */
    bool _revolutionSurface;

    /** If true, normals are generated */
    bool _createNormals;

    /** If true, texture coordinates are generated */
    bool _createTexCoords;

    /**
     * The affine transformations from the crossection plane to the
     * spine aligned crossection planes
     */
    std::vector<Matrix> _transform;

    /** The grid data structure containing the generated vertex data */
    VertexGrid _grid;

    /** The map containing (position, index) pairs for the extrusion surface */
    PositionMap _posMap;

    /** The map containing (vertex normal, index) pairs for the extrusion
     *  surface
     */
    NormalMap   _normalMap;

    /** The map containing (tex coord, index) pairs for the extrusion
     *  surface
     */
    TexCoordMap _texCoordMap;

    /** The number of vertices stored in the current primitive */
    UInt32 _vertexCount;

    /** The total number of vertices which have been stored until now */
    UInt32 _totalVertexCount;

    /** The total number of primitives stored in the geometry */
    UInt32 _primitiveCount;

//-----------------------------------------------------------------------------
//                              Private Methods                                
//-----------------------------------------------------------------------------
    
    /** Calculates the X-Axes of the CP to SCP transforms */
    inline void calcXAxes(void);

    /** Calculates the Y-Axes of the CP to SCP transforms */
    inline void calcYAxes(void);

    /** Calculates the Z-Axes of the CP to SCP transforms */
    inline void calcZAxes(void);
    
    /** Calculates the affine transformations from CP to SCP */
    void calcTransforms(void);

    /**
     *  Calculates the positions of the sweep surface and stores
     *  them in the _grid
     */
    void calcSweepSurfacePositions(void);

    /** Calculates the face normals of the sweep surface and
     *  stores them in the _grid
     */
    void calcSweepSurfaceFaceNormals(void);

    /* Calculates the texture coordinates of the sweep surface and
     *  stores them in the _grid
     */
    void calcSweepSurfaceTexCoords(void);

    /** Initializes the topology flags of the extrusion surface */
    void determineTopology(void);

    /** Initializes the _grid data structure */
    void initGrid(void);

    /**
     *  Returns true if an extrusion surface can be generated from the
     *  supplied data.
     */
    bool verifyInput(void);
    
    /** Subdivides the \var _crossSection n-times */
    void refineCrossSection(UInt32 nTimes);

    /** Subdivides the _orientation vector n-times */
    void refineOrientation(UInt32 nTimes);

    /** Subdivides the scale parameters vector n-times */
    void refineScale(UInt32 nTimes);

    /** Subdivides the spine n-times */
    void refineSpine(UInt32 nTimes);

    /** 
     * Stores a convex cap surface in the supplied field containers
     * 
     * @param spineIndex The spine point at which the cap is to be
     *                   created
     * @param invertNormal If true the cap normal is reversed
     */
    void storeConvexCap(UInt32 spineIndex, 
                        bool invertNormal, 
                        GeoIndicesUI32Ptr  indicesPtr,
                        GeoPLengthsUI32Ptr lensPtr,
                        GeoPTypesUI8Ptr    typesPtr);

    /**
     * Stores the sweep surface obtained by extruding the cross-section
     * along the spine into the supplied field containers. The surface
     * normals are also generated. The _creaseAngle is respected during
     * primitive generation.
     */
    void storeSweepSurfaceWithNormals(GeoIndicesUI32Ptr  indicesPtr,
                                      GeoPLengthsUI32Ptr lensPtr,
                                      GeoPTypesUI8Ptr    typesPtr);

    /**
     * Stores the sweep surface obtained by extruding the cross-section
     * along the spine into the supplied field containers. Normals
     * are not generated.
     */
    void storeSweepSurfaceWithoutNormals(GeoIndicesUI32Ptr  indicesPtr,
                                         GeoPLengthsUI32Ptr lensPtr,
                                         GeoPTypesUI8Ptr    typesPtr);

    /**
     * Stores the accumulated property data in the supplied field containers
     */
    void storeMaps(GeoPositions3fPtr positionsPtr,
                   GeoNormals3fPtr   normalsPtr,
                   GeoTexCoords2fPtr texCoordsPtr);

    /**
     * Stores a property index in the supplied field container and
     * the property itself into an internal map
     */
    inline void storeVertex(const Vertex &vertex,
                            GeoIndicesUI32Ptr indicesPtr);

    /**
     * Stores the %_vertexCount into the lengths field container
     * and the supplied primivite type into the types field container.
     * The %_vertexCount is reset to 0.
     */
    inline void storePrimitive(GLenum type,
                               GeoPLengthsUI32Ptr lensPtr, 
                               GeoPTypesUI8Ptr typesPtr);

    /**
     * Returns a new index for the supplied property and stores it
     * the given map
     */
    template <typename PType>
        inline UInt32
        store(PType property, 
              std::map<PType, UInt32, vecless<PType> > &propertyIndexMap);

    /**
     * Returns a new index for the supplied property, stores it
     * as (property -> index) in the given map. The obtained
     * index is directly stored in the supplied field container
     */    
    template <typename PType>
        inline void
        store(const PType property, 
              std::map<PType, UInt32, vecless<PType> > &propertyIndexMap,
              GeoIndicesUI32Ptr indicesPtr);
    
    /**
     * Returns a pair of iterators pointing to the previous and the
     * next spine point. The iterators are wrapped around at the ends
     * if the spine is closed and saturated otherwise
     */
    inline Pnt3fConstItPair getPrevAndNextIt(const Pnt3fConstIt &pIt);

    /**
     * Returns the non-normalized Y-Axis at pIt
     */        
    inline Vec3f calcNonUnitYAxis(const Pnt3fConstIt &pIt);

    /** Returns the non-normalized Z-Axis at pIt */        
    inline Vec3f calcNonUnitZAxis(const Pnt3fConstIt &pIt);

    /** Returns the normalized X-Axis at pIt */
    inline Vec3f calcXAxis(const MatrixConstIt &pIt);

    /**
     * Returns the non-normalized right handed face normal of the
     * three points a,b,c, if _ccw is true and the negated
     * otherwise
     */
    inline Vec3f calcTriangleFaceNormal(const Pnt3f &a,
                                        const Pnt3f &b,
                                        const Pnt3f &c);

    /**
     * Returns the normalized right handed face normal of the
     * quad given by the four points a,b,c, if _ccw is true and
     * the negated face normal otherwise
     */    
    inline Vec3f calcQuadFaceNormal(const Pnt3f &a,
                                    const Pnt3f &b,
                                    const Pnt3f &c,
                                    const Pnt3f &d);

    /**
     * Returns the normalized vertex normal obtained by averaging all
     * face normals of adjacent faces enclosing an angle less than
     * _creaseAngle with the face normal given by
     * vertexPtr->adjFaceNormals[faceIndex]
     */    
    inline void  calcVertexNormal(Vertex *vertexPtr,
                                  UInt32 faceIndex);

    
//-----------------------------------------------------------------------------
//                        Winding Number Helpers                               
//-----------------------------------------------------------------------------

    inline bool isLeft(const Pnt2f &a, const Pnt2f &b);

    Real32 computeMinYAbs(const std::vector<Pnt2f> &contour,
                          Real32 alpha);

    Real32 calcBetterRotationAngle(const std::vector<Pnt2f> &contour,
                                   UInt32 nAngles);

    bool calcOptimizedContour(const std::vector<Pnt2f> &contour, 
                              const Pnt2f &point,
                              std::vector<Pnt2f> *optimizedContour);
    
    Int32 calcWindingNumber(const std::vector<Pnt2f> &contour,
                            const Pnt2f &point);

//-----------------------------------------------------------------------------
//                             Debugging Helpers                               
//-----------------------------------------------------------------------------

    // adds face normals to geometry
    void storeFaceNormalGeo(GeoIndicesUI32Ptr  indicesPtr,
                            GeoPLengthsUI32Ptr lensPtr,
                            GeoPTypesUI8Ptr    typesPtr);

    // adds vertex normals to geometry
    void storeVertexNormalGeo(GeoIndicesUI32Ptr  indicesPtr,
                              GeoPLengthsUI32Ptr lensPtr,
                              GeoPTypesUI8Ptr    typesPtr);

};


OSG_END_NAMESPACE


#define OSGEXTRUSIONGEOMETRY_HEADER_CVSID "@(#)$Id: $"

#include "OSGExtrusionGeometry.inl"

#endif /* _OSGEXTRUSIONGEOMETRY_H_ */
