#ifndef GLYPHCONTOUR_CLASS_DECLARATION
#define GLYPHCONTOUR_CLASS_DECLARATION

#include <OSGConfig.h>

#include <vector>




OSG_BEGIN_NAMESPACE


class FontGlyphContour {

private:

  /** Point List of this contour */
  vector<float*> _points;

  vector<float*> _normals;

  int _numPoints;

  int _numNormals;

  /** ordering of points for outer or inner contours */
  bool _isClockwise;

  float  _orderingBuffer;

  int _startContour;

protected:

  float _bb[4];

  int _contour;

public:

  /** Default Constructor */
  FontGlyphContour (void);

  /** Copy Constructor */
  FontGlyphContour (const FontGlyphContour &obj);

  /** Destructor */
  virtual ~FontGlyphContour (void);

  /** get method for attribute points */
  virtual float * getPoint (int which)
     { return _points[which]; }

  /** get method for attribute points */
  virtual vector<float *> & getPoints(void)
     { return _points; }

  /** get method for attribute points */
  virtual int getNumPoints (void)
     { return _numPoints;}

  /** get method for attribute points */
  virtual float * getNormal (int which)
     { return _normals[which]; }

  /** get method for attribute normals */
  virtual vector<float *> & getNormals(void);

  /** get method for attribute normals */
  virtual int getNumNormals (void)
     { return _numNormals;}

  /** set method for attribute points */
  virtual void addPoint (float *point, float *normal, bool copy=false);

  /** get method for attribute isClockwise */
  virtual bool isClockwise (void)
     { return _isClockwise; }

  virtual float getArea(void)
      { return _orderingBuffer;}

  virtual void setOrdering(float ordering)
      { _orderingBuffer = ordering;}

  virtual void setBB(float* bb)
      { _bb[0]=bb[0];_bb[1]=bb[1];_bb[2]=bb[2];_bb[3]=bb[3];}

  virtual float* getBB(void)
      { return _bb;}

  void setWhichTTContour(int which)
      {_contour=which;}

  int getWhichTTContour(void)
      {return _contour;}

  virtual int getStart(void) {return _startContour;}

  virtual void setStart(int start) {_startContour = start;}

  bool inside(FontGlyphContour *contour);

  /** set method for attribute isClockwise */
  virtual void setIsClockwise (void)
     { _isClockwise = true; }

  /** set method for attribute isClockwise */
  virtual void setIsNotClockwise (void)
     { _isClockwise = false; }

  virtual void setNumPoints(int num)
      { _points.resize(num);_normals.resize(num);}

  virtual int  getNumPointsExpected(void)
      { return _points.size();}

};

typedef FontGlyphContour* FontGlyphContourP;


OSG_END_NAMESPACE


#endif // GLYPHCONTOUR_CLASS_DECLARATION
