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
class OSG_SYSTEMLIB_DLLMAPPING ExtrusionSurface
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
     *            with respect to the generated normals. Currently not used.
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

    /** 
     * \brief Default Constructor.
     */
    ExtrusionSurface();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    /** 
     * \brief Destructor.
     */
    virtual ~ExtrusionSurface();

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Access                                    */
    /*! \{                                                                 */

    /**
     * \brief Sets the cross section.
     * \param crossSection The cross section.
     */
    inline void setCrossSection(const std::vector<Pnt2f> &crossSection);

    /**
     * \brief Returns the cross section for editing.
     * \return The cross section.
     */
    std::vector<Pnt2f> &editCrossSection();

    /**
     * \brief Returns the cross section.
     * \return The cross section.
     */
    inline const std::vector<Pnt2f> &getCrossSection() const;

    /**
     * \brief Sets the orientation.
     * \param orientation The orientation values.
     */
    inline void setOrientation(const std::vector<Quaternion> &orientation);

    /**
     * \brief Returns the orientation for editing.
     * \return The orientation values.
     */
    std::vector<Quaternion> &editOrientation();

    /**
     * \brief Returns the orientation.
     * \return The orientation values.
     */
    inline const std::vector<Quaternion> &getOrientation() const;

    /**
     * \brief Sets the scale.
     * \param scale The scale values.
     */
    inline void setScale(const std::vector<Vec2f> &scale);

    /**
     * \brief Returns the scale for editing.
     * \return The scale values.
     */
    std::vector<Vec2f> &editScale();

    /**
     * \brief Returns the scale.
     * \return The scale values.
     */
    inline const std::vector<Vec2f> &getScale() const;

    /**
     * \brief Sets the spine.
     * \param spine The spine positions.
     */
    inline void setSpine(const std::vector<Pnt3f> &spine);

    /**
     * \brief Returns the spine for editing.
     * \return The spine positions.
     */
    std::vector<Pnt3f> &editSpine();

    /**
     * \brief Returns the spine.
     * \return The spine positions.
     */
    inline const std::vector<Pnt3f> &getSpine() const;

    /**
     * \brief Sets the crease angle.
     * \param creaseAngle The crease angle.
     */
    inline void setCreaseAngle(Real32 creaseAngle);

    /**
     * \brief Returns the crease angle.
     * \return The crease angle.
     */
    inline Real32 getCreaseAngle() const;

    /**
     * \brief Switches the cap at the beginning on or off.
     * \param beginCap When true, switches on the cap.
     */
    inline void setBeginCap(bool beginCap);

    /**
     * \brief Returns whether to draw a cap at the beginning.
     * \return True when a cap is drawn.
     */
    inline bool getBeginCap() const;

    /**
     * \brief Switches the cap at the end on or off.
     * \param endCap When true, switches on the cap.
     */
    inline void setEndCap(bool endCap);

    /**
     * \brief Returns whether to draw a cap at the end.
     * \return True when a cap is drawn.
     */
    inline bool getEndCap() const;

    /**
     * \brief Sets the vertex order of faces. Currently not
     * used.
     * \param ccw When true, the order is counterclockwise.
     */
    inline void setCcw(bool ccw);

    /**
     * \brief Returns the vertex order of faces.
     * \return True when the order is counterclockwise.
     */
    inline bool getCcw() const;

    /**
     * \brief Sets whether the cross section is convex.
     * \param convex When true, the cross section is convex.
     */
    inline void setConvex(bool convex);

    /**
     * \brief Returns whether the cross section is convex.
     * \return True when the cross section is convex.
     */
    inline bool getConvex() const;

    /**
     * \brief Switches normal generation on or off.
     * \param buildNormal When true, creates normals.
     */
    inline void setBuildNormal(bool buildNormal);

    /**
     * \brief Returns whether normals should be generated.
     * \return True when normals should be generated.
     */
    inline bool getBuildNormal() const;

    /**
     * \brief Switches texture coordinate generation on or off.
     * \param buildTexCoord When true, creates texture coordinates.
     */
    inline void setBuildTexCoord(bool buildTexCoord);

    /**
     * \brief Returns whether texture coordinates should be generated.
     * \return True when texture coordinates should be generated.
     */
    inline bool getBuildTexCoord() const;

    /** 
     * \brief Creates a multi-indexed %Geometry representing the
     * extrusion surface
     * Invoked by the construction function makeExtrusionGeo and makeExtrusion
     * 
     * \param nSubDivisions The number of subdivisions to apply. Not used anymore.
     * \return A pointer to a newly created geometry containing the surface
     */
    GeometryPtr createGeometry(UInt32 nSubDivisions = 0);

    /** 
     * \brief Fills an existing %Geometry with the extrusion surface
     * 
     * \param geoPtr The geometry that gets filled
     */
    void fillGeometry(GeometryPtr &geoPtr);

    /*! \}                                                                 */

    /*==========================  PRIVATE  =================================*/
private:

    /*!\brief prohibit default function (move to 'public' if needed) */
    ExtrusionSurface(const ExtrusionSurface &source);

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const ExtrusionSurface &source);

    /*---------------------------------------------------------------------*/
    /*                      Internally Used Types                          */
    /*---------------------------------------------------------------------*/

    typedef std::vector<Pnt3f>::const_iterator Pnt3fConstIt;
    typedef std::vector<Matrix>::const_iterator MatrixConstIt;
    typedef std::pair<Pnt3fConstIt, Pnt3fConstIt> Pnt3fConstItPair;

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

    /** The cosinus of the crease angle */
    Real32 _cosCreaseAngle;

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

    /**
     * If true, the order of the cross section is counterclockwise
     */
    bool _crossSectionCcw;

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
    std::vector<Matrix> _cp2scp;

    /**
     * CP to SCP transformation + scale + orientation
     */
    std::vector<Matrix> _transform;

    /**
     * The normals of all faces
     */
    std::vector<Vec3f> _faceNormals;

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

//-----------------------------------------------------------------------------

    /** The lengths of the cross section geometry */
    std::vector<UInt32> _crossSectionLengths;

    /** The indices of the cross section geometry */
    std::vector<UInt32> _crossSectionIndices;

    /** The GL primitive types of the cross section geometry */
    std::vector<UInt8>  _crossSectionTypes;

    /** The tesselator object used to create the cross section geometry */
    GLUtesselator *_tess;

    /** Gets called by the tesselator when beginning a new primitive */
    static void OSG_APIENTRY gluTessBeginDataCB(GLenum type, void *polygonData);

    /** Gets called by the tesselator when ending a primitive */
    static void OSG_APIENTRY gluTessEndDataCB(void *polygonData);

    /** Gets called by the tesselator to add a vertex to the current primitive */
    static void OSG_APIENTRY gluTessVertexDataCB(void *vertexData, void *polygonData);
};


OSG_END_NAMESPACE


#define OSGEXTRUSIONGEOMETRY_HEADER_CVSID "@(#)$Id: $"

#include "OSGExtrusionGeometry.inl"

#endif /* _OSGEXTRUSIONGEOMETRY_H_ */
