#ifndef TTVECTORGLYPH_CLASS_DECLARATION
#define TTVECTORGLYPH_CLASS_DECLARATION

#include <OSGConfig.h>

#ifdef OSG_WITH_FREETYPE1

#include "OSGVectorFontGlyph.h"
#include "OSGTTFontGlyph.h"

#include "freetype1/freetype/freetype.h"


OSG_BEGIN_NAMESPACE


class TTVectorFontGlyph : public virtual FontGlyph, 
			 public VectorFontGlyph, public TTFontGlyph {

/* 	typedef VectorFontGlyph ParentClass; */

private:

  static double _ttScale;

  float _ttScaleToVRML;

  float *_tmpNormalBuffer;

  int processArc(FontGlyphContour *glyphContour, TT_Outline outline, int start,
		int contour, float** normalStack, int & numnStack,
		int & counter, int step = 1, bool dryRun = false);

  int sortContours(TT_Outline outline);

  void cleanup(void);

  inline float max(float a, float b)
      { return ( a > b ? a : b);}

  inline float min(float a, float b)
      { return ( a < b ? a : b);}

protected:

public:

  /** Default Constructor */
  TTVectorFontGlyph (void);

  /** Copy Constructor */
  TTVectorFontGlyph (const TTVectorFontGlyph &obj);

  /** Constructor */
  TTVectorFontGlyph (VGlyphType type, int ascii, int unicode);

  /** Destructor */
  virtual ~TTVectorFontGlyph (void);

  /** Constructor */
  void setup(VGlyphType type, int ascii, int unicode);

  void setScaleFactor(float scaleFactor)
      {_ttScaleToVRML = (scaleFactor*64.0)/_size;}

  /** creates desired representation */
  virtual bool create (void);

};

typedef TTVectorFontGlyph* TTVectorFontGlyphP;


OSG_END_NAMESPACE

#endif // OSG_WITH_FREETYPE1

#endif // TTVECTORGLYPH_CLASS_DECLARATION

