#ifndef OSGDVRSLICE_H
#define OSGDVRSLICE_H

#include <OSGVector.h>

OSG_BEGIN_NAMESPACE

class DVRSlice 
{
  public:

    //! Constructor
    DVRSlice(void);

    //! Destructor
    ~DVRSlice(void);

    //! set a new vertex 
    void setVertex(Pnt3f vertex);

    //! get a vertex
    Pnt3f getVertex(UInt32 number);
  
    //! get number of set vertices
    UInt32 getVertexCount(void);

    /*! Set the slice's normal*/
    void setNormal(Vec3f normal);

    //! reset the slice's data
    void resetSlice();

    /*! Returns the slice's normal. Returns 0 iff no normal 
      is set and there is insufficient information to calculate 
      the normal (at least three vertices set).*/
    Vec3f getNormal(void);

    //! Set the transformation parameters used to create texture coordinates
    //! from vertex positions
    void setTextureTransform(const Vec3f &scale, const Vec3f &translate);

    //! Get the scale parameters used to create texture coordinates from 
    // !vertex positions
    Vec3f getTextureScale(void) const;

    //! Get the translation parameters used to create texture coordinates 
    // from vertex positions

    Vec3f getTextureTranslate(void) const;

    void output(void);

  private:
    
    //! the number of vertices currently stored
    UInt32 numberOfVertices;

    //! the vertex data, each slice can have max. 6 vertices 
    Pnt3f *vertexData;

    //! the normal of this slice
    Vec3f  normal;

    //! the scale parameter used to create texture coordinates from vertex 
    //! positions
    Vec3f texScale;

    //! the translation parameter used to create texture coordinates from 
    //! vertex positions
    Vec3f texTranslate;
};

OSG_END_NAMESPACE

#endif
