#ifndef TXFIMAGEGLYPH_CLASS_DECLARATION
#define TXFIMAGEGLYPH_CLASS_DECLARATION

#ifndef WIN32

#include <OSGConfig.h>

#include "OSGImageFontGlyph.h"
#include "OSGTXFFontGlyph.h"



OSG_BEGIN_NAMESPACE


class TXFImageFontGlyph : public ImageFontGlyph, public virtual TXFFontGlyph {
/* 	typedef ImageFontGlyph ParentClass; */

private:

  unsigned char *_srcImage;
  int _srcWidth, _srcHeight;

  int _xOff, _yOff;

protected:

public:

  /** Default Constructor */
  TXFImageFontGlyph (void);

  /** Copy Constructor */
  TXFImageFontGlyph (const TXFImageFontGlyph &obj);

  /** Constructor */
  TXFImageFontGlyph (IGlyphType type, int ascii, int unicode);

  /** Destructor */
  virtual ~TXFImageFontGlyph (void);

  /** Constructor */
  void setup(IGlyphType type, int ascii, int unicode);

  void setFontDefs(short x, short y, char *dimensions);

  void setFontSource(unsigned char *srcImage, int width, int height);

  /** creates desired representation */
  virtual bool create (void);

};

typedef TXFImageFontGlyph* TXFImageFontGlyphP;


OSG_END_NAMESPACE



#endif
#endif // TXFIMAGEGLYPH_CLASS_DECLARATION

