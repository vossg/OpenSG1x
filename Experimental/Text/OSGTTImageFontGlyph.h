#ifndef TTIMAGEGLYPH_CLASS_DECLARATION
#define TTIMAGEGLYPH_CLASS_DECLARATION

#ifndef WIN32
#include <OSGConfig.h>
#include <OSGBaseTypes.h>

#ifdef OSG_WITH_FREETYPE1
#include "OSGImageFontGlyph.h"
#include "OSGTTFontGlyph.h"
#include "freetype1/freetype/freetype.h"

OSG_BEGIN_NAMESPACE class TTImageFontGlyph :
    public ImageFontGlyph,
    public virtual TTFontGlyph
{
    /* 	typedef ImageFontGlyph ParentClass; */
private:
protected:
public:

    /** Default Constructor */
    TTImageFontGlyph(void);

    /** Copy Constructor */
    TTImageFontGlyph(const TTImageFontGlyph &obj);

    /** Constructor */
    TTImageFontGlyph(IGlyphType type, Int32 ascii, Int32 unicode);

    /** Destructor */
    virtual         ~TTImageFontGlyph(void);

    /** Constructor */
    void            setup(IGlyphType type, Int32 ascii, Int32 unicode);

    /** creates desired representation */
    virtual bool    create(void);
};

typedef TTImageFontGlyph    *TTImageFontGlyphP;

OSG_END_NAMESPACE
#endif // OSG_WITH_FREETYPE1
#endif
#endif // TTIMAGEGLYPH_CLASS_DECLARATION
