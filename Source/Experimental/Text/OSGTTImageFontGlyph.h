#ifndef TTIMAGEGLYPH_CLASS_DECLARATION
#define TTIMAGEGLYPH_CLASS_DECLARATION

#include <OSGConfig.h>
#include <OSGBaseTypes.h>

#ifdef OSG_WITH_FREETYPE1

#include "OSGImageFontGlyph.h"
#include "OSGTTFontGlyph.h"

OSG_BEGIN_NAMESPACE 

class TTImageFontGlyph :
    public         ImageFontGlyph,
    public virtual TTFontGlyph
{

  private:

    TTImageFontGlyph(const TTImageFontGlyph &obj);
    void operator =(const TTImageFontGlyph &obj);

  protected:
  public:

    TTImageFontGlyph(void);
    TTImageFontGlyph(IGlyphType type, Int32 ascii, Int32 unicode);

    virtual ~TTImageFontGlyph(void);

            void setup (IGlyphType type, Int32 ascii, Int32 unicode);
    virtual bool create(void                                       );
};

OSG_END_NAMESPACE

#endif // OSG_WITH_FREETYPE1
#endif // TTIMAGEGLYPH_CLASS_DECLARATION
