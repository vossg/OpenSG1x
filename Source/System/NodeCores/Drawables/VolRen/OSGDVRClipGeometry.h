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

#ifndef _OSGDVRCLIPGEOMETRY_H_
#define _OSGDVRCLIPGEOMETRY_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGGeometry.h>
#include <OSGPlane.h>

#include <OSGDVRClipGeometryBase.h>
#include <OSGDVRVertex.h>
#include <OSGDVRTriangle.h>

OSG_BEGIN_NAMESPACE

/*! \brief *put brief class description here* 
 */

class OSG_SYSTEMLIB_DLLMAPPING DVRClipGeometry : public DVRClipGeometryBase
{
  private:

    typedef DVRClipGeometryBase Inherited;

    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Clipping                                  */
    /*! \{                                                                 */

    //! Prepare the object for clipping a volume's slices (transform it to 
    //! volume's space)
    void initialize            (const Matrix &volumeToWorld                );

    //! Reset local data of vertices and triangles
    void resetLocalData        (      void                                 );

    //! Set the reference plane used in the clipping algorithm
    void setReferencePlane     (const Plane  &referencePlane               );
  
    //! set the number of additional per vertex attributes 
    /*!
        basically there are two attributes available, the vertex position and a
        3D texture coordinate. If one needs additional attributes, e.g.
        color, texture coordinates,.., the number of (double) values needed 
        has to be set with this function.
    */
    bool setNumAddPerVertexAttr(      UInt32  additionalPerVertexAttributes);
  
    //! Compute the seed vertex set
    void computeSeedVertices   (      void                                 );
    
    //! find contour made up by triangles which are cut by the current slice
    const DVRTriangleList &getContours(      float dist2RefPlane, 
                                             bool positiveWinding, 
                                       const Vec3f &sliceNormal);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Locals                                    */
    /*! \{                                                                 */

    //! is the clip geometry initialized?
    bool                       initialized;

    //! the core of the geometry node
    GeometryPtr                geometry;

    //! list of vertices in the triangulated clip geometry
    std::vector<DVRVertex>     _mfVertices;

    //! list of triangles in the triangulated clip geometry
    std::vector<DVRTriangle>   _mfTriangles;

    //! The transformation matrix needed to transform the clip geoemtry to 
    //! the volume's space.
    Matrix                     toVolumeSpace;

    //! the triangles which are cut by the current slice
    DVRTriangle              **activeTriangles;
    UInt32                     activeTrianglesCount;
    UInt32                     maxActiveTrianglesCount;

    //! the vertices which are closest to the reference plane
    DVRVertex                **seedVertices;
    UInt32                     seedVerticesCount;
    UInt32                     maxSeedVerticesCount;

    //! the start triangles of all contours made up by intersections with 
    //! the current slice
    DVRTriangleList            contours;
  
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DVRClipGeometry(void);
    DVRClipGeometry(const DVRClipGeometry &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DVRClipGeometry(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Vertices                                   */
    /*! \{                                                                 */

    //! Insert a vertex in the vertex list
    /*!
      if there already exists a vertex at the position of the new vertex
      they get unified, i.e. the index of the already existent vertex is 
      returned, else a new one is inserted
    */
    Int32 insertVertex (Int32      idx   );

    //! returns true, iff this vertex is a local minimum 
    //! with respect to refPlaneDistance.
    bool isLocalMinimum(DVRVertex &vertex);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Triangles                                  */
    /*! \{                                                                 */

    //! returns true, iff the plane with distance dist2RefPlane to the ref 
    //! plane cuts the triangle.
    bool isCut         (      DVRTriangle *tri, 
                              Real32       dist2RefPlane, 
                              DVRVertex   *switchedVertices[3]);

    //! returns true, iff dist2RefPlane is bigger than the distance to the 
    //! reference plane of all vertices within the triangle.
    bool isBehindPlane (      DVRTriangle &tri, 
                              Real32       dist2RefPlane      );

    //! Use OpenGL to render the triangle
    void renderTriangle(const DVRTriangle &tri                ) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name              Triangle Geometry Setup                         */
    /*! \{                                                                 */

    //! create the triangled geometry data structure
    bool buildTriangledGeometry(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Clipping                                  */
    /*! \{                                                                 */

    //! Identifies all contours and links them
    void buildContours        (      Real32       dist2RefPlane, 
                                     bool         positiveWinding, 
                               const Vec3f       &sliceNormal    );
    
    //! Identifies and links a contour starting with the given triangle
    void linkContour          (      DVRTriangle *startTriangle,
                                     Real32       dist2RefPlane,
                               const Vec3f       &viewDir, 
                                     bool         positiveWinding);
    
    //! updates the active triangle list
    void updateActiveTriangles(      Real32       dist2RefPlane, 
                               const Vec3f       &sliceNormal    );
    
    //!
    void addActiveTriangle    (      DVRTriangle *tri            );

    //!
    void addNewActiveTriangles(      DVRVertex   *vertex,
                                     Real32       dist2RefPlane  );
    
    //! 
    Pnt3f interpolate         (      DVRTriangle *tri, 
                                     Int32        v1, 
                                     Int32        v2, 
                                     Real32       dist2RefPlane  );
    
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DVRClipGeometryBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DVRClipGeometry &source);
};

typedef DVRClipGeometry *DVRClipGeometryP;

OSG_END_NAMESPACE

#include <OSGDVRClipGeometryBase.inl>
#include <OSGDVRClipGeometry.inl>

#define OSGDVRCLIPGEOMETRY_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGDVRCLIPGEOMETRY_H_ */
