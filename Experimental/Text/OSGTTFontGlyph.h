#ifndef TTGLYPH_CLASS_DECLARATION
#define TTGLYPH_CLASS_DECLARATION

#ifndef WIN32

#ifdef OSG_WITH_FREETYPE1

#include <OSGConfig.h>

#include "OSGFontGlyph.h"

#include "freetype1/freetype/freetype.h"


OSG_BEGIN_NAMESPACE


class TTFontGlyph : public virtual FontGlyph {
	typedef FontGlyph ParentClass;

private:

  TT_Error _ttError;

  TT_Glyph _ttGlyph;

  TT_Glyph_Metrics _ttGlyphMetrics;

  TT_Face *_ttFace;

  TT_Instance *_ttInstance;

  static double _ttScale;

protected:

public:

  /** Default Constructor */
  TTFontGlyph (void);

  /** Copy Constructor */
  TTFontGlyph (const TTFontGlyph &obj);

  /** Constructor */
  TTFontGlyph (int ascii, int unicode);

  /** Destructor */
  virtual ~TTFontGlyph (void);

  /** Constructor */
  void setupGlyph(int ascii, int unicode);

  /** stores needed FreeType definitions */
  virtual void setFontDefs (TT_Face *ttFacte, TT_Instance *ttInstance)
      {_ttFace = ttFacte; _ttInstance = ttInstance;}

  /** creates desired representation */
  virtual bool createGlyph (void);

  virtual bool getOutline (TT_Outline & ttOutline);

  virtual bool setSizes (float *_boundingBox, float & _advance);

  virtual bool setSizes (int *_boundingBox, int & _advance);

  virtual void glyphDone(void) { TT_Done_Glyph(_ttGlyph ); }

  virtual bool renderGlyph(TT_Raster_Map map, int xOff, int yOff);
};

typedef TTFontGlyph* TTFontGlyphP;


OSG_END_NAMESPACE

#endif // OSG_WITH_FREETYPE1


#endif
#endif // TTGLYPH_CLASS_DECLARATION

