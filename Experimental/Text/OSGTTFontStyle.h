#ifndef TTFONTINSTANCE_CLASS_DECLARATION
#define TTFONTINSTANCE_CLASS_DECLARATION

#include <OSGConfig.h>

#ifdef FREETYPE1_LIB

#include "OSGFontStyle.h"
#include "freetype1/freetype/freetype.h"


OSG_BEGIN_NAMESPACE


class TTFontStyle : public FontStyle {
	typedef FontStyle ParentClass;

private:

  /** The FreeType instance of given font */
  TT_Instance * _ttInstance;

  /** The given font */
  TT_Face *_ttFace;

  /** Error container */
  TT_Error _ttError;

protected:

  /** rerenders stored glyphs in case of resize */
  virtual bool processChange (void);

public:

  /** Default Constructor */
  TTFontStyle (void);

  /** Copy Constructor */
  TTFontStyle (const TTFontStyle &obj);

  /** Destructor */
  virtual ~TTFontStyle (void);

  /** set method for attribute _ttInstance */
  virtual bool set_ttInstance (TT_Instance *ttInstance, TT_Face *ttFace);

  /** return specified (ASCII-) Glyph */
  virtual VectorFontGlyph * getVectorGlyph (int which);

  virtual ImageFontGlyph * getImageGlyph (int which);

  virtual bool createTXFMap(char *characters=NULL, int gap=1);

  virtual unsigned char *getTXFImageMap (void);

  virtual TXFGlyphInfo *getTXFGlyphInfo (int ascii);

  virtual bool dump(ostream & out);

};

OSG_END_NAMESPACE


typedef osg::TTFontStyle* TTFontStyleP;

#endif // FREETYPE1_LIB


#endif // TTFONTINSTANCE_CLASS_DECLARATION
