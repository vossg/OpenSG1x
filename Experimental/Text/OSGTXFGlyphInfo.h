#ifndef TXFGLYPHINFO_CLASS_DECLARATION
#define TXFGLYPHINFO_CLASS_DECLARATION

#include <OSGConfig.h>



OSG_BEGIN_NAMESPACE


class TXFGlyphInfo {

private:

protected:

  //  texture coordinates  (ccw)

  float _tCoords[4][2];
  
  //  vertex coordinates  (ccw)
  
  float _vCoords[4][2];

  float _advance;

  int *_dimensions;

  int _remapped;

public:

  /** Default Constructor */
  TXFGlyphInfo (void) {_remapped=0; _dimensions=NULL;}

  /** Destructor */
  virtual ~TXFGlyphInfo (void) {;}

  void remap(int dest) { _remapped = dest;}

  int remapped(void) { return _remapped;}

  virtual bool setTextureCoords(int corner, float x, float y);

  virtual bool setVertexCoords(int corner, float x, float y);

  virtual float *getTextureCoords(int corner);
	  
  virtual float *getVertexCoords(int corner);

  virtual void setAdvance(float advance) {_advance = advance;}

  virtual float getAdvance(void) {return _advance;}

  virtual void setDimensions(int *dims) {_dimensions = dims;}

  virtual int *getDimensions(void) { return _dimensions;}

};

typedef TXFGlyphInfo* TXFGlyphInfoP;


OSG_END_NAMESPACE


#endif // TXFGLYPHINFO_CLASS_DECLARATION
