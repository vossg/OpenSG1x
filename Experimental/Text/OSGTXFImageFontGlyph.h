#ifndef TXFIMAGEGLYPH_CLASS_DECLARATION
#define TXFIMAGEGLYPH_CLASS_DECLARATION

#ifndef WIN32

#include <OSGConfig.h>
#include <OSGBaseTypes.h>

#include "OSGImageFontGlyph.h"
#include "OSGTXFFontGlyph.h"



OSG_BEGIN_NAMESPACE


class TXFImageFontGlyph : public ImageFontGlyph, public virtual TXFFontGlyph {
/* 	typedef ImageFontGlyph ParentClass; */

private:

  UChar8 *_srcImage;
  Int32 _srcWidth, _srcHeight;

  Int32 _xOff, _yOff;

protected:

public:

  /** Default Constructor */
  TXFImageFontGlyph (void);

  /** Copy Constructor */
  TXFImageFontGlyph (const TXFImageFontGlyph &obj);

  /** Constructor */
  TXFImageFontGlyph (IGlyphType type, Int32 ascii, Int32 unicode);

  /** Destructor */
  virtual ~TXFImageFontGlyph (void);

  /** Constructor */
  void setup(IGlyphType type, Int32 ascii, Int32 unicode);

  void setFontDefs(short x, short y, Int8 *dimensions);

  void setFontSource(UChar8 *srcImage, Int32 width, Int32 height);

  /** creates desired representation */
  virtual bool create (void);

};

typedef TXFImageFontGlyph* TXFImageFontGlyphP;


OSG_END_NAMESPACE



#endif
#endif // TXFIMAGEGLYPH_CLASS_DECLARATION

