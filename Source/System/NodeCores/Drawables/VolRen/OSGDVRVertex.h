#ifndef OSGDVRVertex_H
#define OSGDVRVertex_H

#include <vector>
#include <list>

#include <OSGVector.h>
#include <OSGPlane.h>

OSG_BEGIN_NAMESPACE

//! A single Vertex of the triangled clip geometry
class DVRVertex 
{

public: // public methods
  
    //! Construct a new vertex 
    DVRVertex(void);
  
    //! Copy
    DVRVertex(const DVRVertex &vertex);

    //! Destructor
    ~DVRVertex(void);
  
    //! calculates the distance of the vertex to a reference plane.
    /*!
      uses the vertex position 
    */
    void calculatePlaneDistance(const Plane &plane);
  
    //! calculates the distance of the vertex to a reference plane.
    /*!
      uses the transformed vertex position
    */
    void calculatePlaneDistanceTransformed(const Plane &plane);

    //! calculates the distance of the vertex to a reference plane.
    /*!
      uses the vertex position transformed with 'transform'
    */
    void calculatePlaneDistance(const Plane &plane, const Matrix &transform);

    //! returns true, iff dist2RefPlane ist bigger than this->refPlaneDistance
    //! switched will be set, if the vertex was till yet in front of each of 
    //! the tested planes 
    bool isBehindPlane(float dist2RefPlane, bool &switched);

    //! returns true, iff dist2RefPlane ist bigger than this->refPlaneDistance
    bool isBehindPlane(float dist2RefPlane);

    //! Returns true, if the vertex is closer to the ref plane 
    //! than (distance). If not, the notMinimumValue flag is set 
    //! to true.
    /*!
      One of the calculatePlaneDistance(..) functions has to be called before!
    */
    bool isCloser(float distance);

    //! Usefull for debugging
    void dump(void) const;

  public: // public attributes

    //! The vertex index in the parent geometry. 
    Pnt3f pos;

    //! The adjacent triangles of this vertex
    std::vector<Int32> adjacentTriangles;

  public: // local public attributes

    //! 
    bool behindPlane;

    //!
    //bool notMinimumValue;

    //!
    Real32 refPlaneDistance;

    //! The position of this vertex in volume coords
    Pnt3f transformedPos;
};

OSG_END_NAMESPACE

#endif




