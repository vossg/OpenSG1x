#ifndef OSGDVRTRIANGLE_H
#define OSGDVRTRIANGLE_H

#include <list>
#include <vector>

#include <OSGVector.h>
#include <OSGGL.h>

OSG_BEGIN_NAMESPACE

//! A triangle of a triangled clipping geometry object

class DVRTriangle
{
  public:

    //! Constructor
    DVRTriangle(void);

    //! Copy
    DVRTriangle(const DVRTriangle &tri);
    
    //! Destructor
    ~DVRTriangle(void);

    //! Usefull for debugging
    void dump(void) const;

    //! set the number of additional per vertex attributes for the cutpoint
    /*!
      basically there are two attributes available, the vertex position and a
      3D texture coordinate, if one needs additional attributes, e.g. color, 
      texture coordinates,.., the number of (double) values needed has to be 
      set with this function. 
    */
    bool setNumAddPerVertexAttr(UInt32 additionalPerVertexAttributes);

    // public attributes
  public: 

    //! Indices of the neighbour triangles of this triangle
    Int32 neighbours[3];

    //! Indices of the vertices of this triangle
    Int32 vertices[3];

    //! The triangles normal
    Vec3f normal;

    // local variables
  public: 

    //! The triangles normal
    Vec3f transformedNormal;

    //! A Flag. True, iff the triangle has been processed.
    bool visited;

    //! True if the triangle belongs to a contour
    bool inContour;

    //! the next triangle in the contour
    DVRTriangle *contourNeighbour;

    //! The intersection point of the triangle and the current slice that 
    //! contributes to the contour
    Pnt3f cutPnt;

    //! The intersection point of the triangle and the current 
    //! slice that contributes to the contour with additional texture 
    //! coordinates, needed because GLUTesselator needs an opaque pointer.
    //! The first three values represent the vertex position, the next
    //! three the (always available) first texture coordinate for this point 
    //! and the following values the additional per vertex attributes (if any) 

    GLdouble *cutPoint;

    //! Indicates which edges are cut by the currently processed slice
    bool edgeCut[3];
};

//! A list of pointers to triangles, for local usage only
typedef std::vector<DVRTriangle *> DVRTriangleList;

OSG_END_NAMESPACE

#endif
