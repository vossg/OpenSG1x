#ifndef VECTORGLYPH_CLASS_DECLARATION
#define VECTORGLYPH_CLASS_DECLARATION


enum VGlyphType { VGLYPH_NONE=0, VGLYPH_FACE, VGLYPH_OUTLINE};


#include <OSGConfig.h>

#include <list>
#include <vector>
#include "OSGFontGlyph.h"


/** Vector Representation of a Glyph.
*
* Defines the 3D-Data-Interface to Glyphs and implements GLU-Tesselation
*
*/



OSG_BEGIN_NAMESPACE  class FontGlyphContour; OSG_END_NAMESPACE


OSG_BEGIN_NAMESPACE

class VectorFontGlyph : public virtual FontGlyph {
	typedef FontGlyph ParentClass;

private:

  /** wether its outline or face (different number of indices) */
  VGlyphType _type;

  /** adding Points is done with this */
  void addPoint(float *point, bool lower=false);

  /** look if given point already exist and return its index */
  int findPoint(float *point, int lower, int upper);

  void extrude(void);

protected:

  /** desired Z-depth of glyph */
  float _depth;

  float _precision;

  /** All Points that Make up the Glyph */
  vector<float*> _points;

  vector<float *> _normals;
  
  int _numPoints;

  int _numNormals;

  int _pointBufferSize;

  /** The indices defining the order of points */
  vector<int> _indices;

  vector<int> _normalIndices;

  int _numIndices, _numBad;

  bool _bad;

  int _numFrontFaces;

  int _indexBufferSize;

  int _contourStart;

  vector<FontGlyphContour *> _contours;

  class FloatBuffer {

  private:
      
      float **_fBuffer;

      int _fBuffSize, _fBuffNext, _fWhichBuffer;

      void fBuffAlloc(int size);

  public:

      FloatBuffer(void);

      float *allocFloat(int num);

      int getBufferForPointer(float *pointer);

      float *getBuffer(int which) 
	  {return (which <= _fWhichBuffer ? _fBuffer[which] : 0);}

  };

  FloatBuffer _vertexBuffer, _normalBuffer;

  float _boundingBox[6];
  
  float _advance;

  /** creates triangle-list */
  bool createTriangles(void);

  friend void tessVertex(void *);

  void pushIt(float ** &stack, int & num, float* & elem);
  
  void calcNormal(float ** &stack, int num, float* result);

  bool checkAngle(float **joint);

public:

  /** Default Constructor */
  VectorFontGlyph (void);

  /** Copy Constructor */
  VectorFontGlyph (const VectorFontGlyph &obj);

  /** Constructor */
  VectorFontGlyph (VGlyphType type);

  /** Destructor */
  virtual ~VectorFontGlyph (void);

  /** get method for attribute points */
  virtual vector<float*> & getPoints (void)
     { return _points; }

  /** get method for attribute normals */
  virtual vector<float*> & getNormals (void)
     { return _normals; }

  /** get method for attribute indices */
  virtual vector<int> & getIndices (void)
     { return _indices; }

  /** get method for attribute indices */
  virtual vector<int> & getNormalIndices (void)
     { return _normalIndices; }

  /** get method for attribute numPoints */
  virtual int getNumPoints (void)
     { return _numPoints; }

  /** get method for attribute numNormals */
  virtual int getNumNormals (void)
     { return _numNormals; }

  /** get method for attribute numIndices */
  virtual int getNumIndices (void)
     { return _numIndices; }

  virtual int getNumFrontFaces(void)
      { return _numFrontFaces; }

  /** clears 3D-data */
  virtual bool clear (void);

  const float* getBoundingBox(void) { return _boundingBox;}

  const float getAdvance(void) { return _advance;}

  /** set method for attribute depth */
  virtual void setDepth (float size)
     { _depth = size; }

  /** get method for attribute depth */
  virtual float getDepth (void)
     { return _depth; }

  /** set method for attribute depth */
  virtual void setPrecision (float precision)
     { _precision = precision; }

  /** get method for attribute type */
  virtual VGlyphType getType (void)
     { return _type; }

  /** set method for attribute type */
  virtual void setType (VGlyphType type)
     { _type = type; }

};

OSG_END_NAMESPACE


typedef osg::VectorFontGlyph* VectorFontGlyphP;




#endif // VECTORGLYPH_CLASS_DECLARATION
