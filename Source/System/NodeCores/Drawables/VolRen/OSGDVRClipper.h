#ifndef OSGDVRCLIPPER_H
#define OSGDVRCLIPPER_H

#include <OSGGLU.h>
#include <OSGDVRSlice.h>
#include <OSGDVRRenderSlice.h>

OSG_BEGIN_NAMESPACE

// forward decl.
class DVRVolume;

class DVRClipper
{
  public:

    DVRClipper(void);

    ~DVRClipper(void);

    //! clips the slice
    void clipSlice(      DVRVolume      *volume,
                         DVRSlice       &slice, 
                   const Vec3f          &slicingNormal, 
                         Real32          dist2RefPlane, 
                         DVRRenderSlice &clippedSlice );

    //! initialize the clipper
    void initialize(DVRVolume *volume);
    
    //! Reset objects state 
    void reset     (DVRVolume *volume);

    //!
    void setReferencePlane(const Plane &refPlane);

    //!
    const Plane &getReferencePlane() const;

  //! set the number of additional per vertex attributes 
  /*!
      basically there are two attributes available, the vertex position and a
      3D texture coordinate. If one needs additional attributes, e.g.
      color, texture coordinates,.., the number of (double) values needed has 
      to be set with this function.
   */
    bool setNumAddPerVertexAttr(DVRVolume *volume, 
                                UInt32     additionalPerVertexAttributes);

  private:
    
    //! GLUtesselator available?
    bool           hasTesselatorSupport;

#ifdef GLU_VERSION_1_2
    //! The Tesselator object for retesselation
    GLUtesselator *myTess;
#endif

    // temporary storage used while tesselating a slice 
    // basically position and tex coord for the slice boundary 
    GLdouble      *sliceVertexData;
    
    // reference plane
    Plane          refPlane;
    
    // number of additional per vertex attributes
    UInt32         numAddPerVertexAttr;
};

OSG_END_NAMESPACE

#endif
