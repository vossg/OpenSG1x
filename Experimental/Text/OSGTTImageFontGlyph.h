#ifndef TTIMAGEGLYPH_CLASS_DECLARATION
#define TTIMAGEGLYPH_CLASS_DECLARATION

#include <OSGConfig.h>

#ifdef OSG_WITH_FREETYPE1

#include "OSGImageFontGlyph.h"
#include "OSGTTFontGlyph.h"
#include "freetype1/freetype/freetype.h"



OSG_BEGIN_NAMESPACE


class TTImageFontGlyph : public ImageFontGlyph, public virtual TTFontGlyph {
/* 	typedef ImageFontGlyph ParentClass; */

private:

protected:

public:

  /** Default Constructor */
  TTImageFontGlyph (void);

  /** Copy Constructor */
  TTImageFontGlyph (const TTImageFontGlyph &obj);

  /** Constructor */
  TTImageFontGlyph (IGlyphType type, int ascii, int unicode);

  /** Destructor */
  virtual ~TTImageFontGlyph (void);

  /** Constructor */
  void setup(IGlyphType type, int ascii, int unicode);

  /** creates desired representation */
  virtual bool create (void);

};

typedef TTImageFontGlyph* TTImageFontGlyphP;


OSG_END_NAMESPACE

#endif // OSG_WITH_FREETYPE1

#endif // TTIMAGEGLYPH_CLASS_DECLARATION

