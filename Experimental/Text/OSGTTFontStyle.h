#ifndef TTFONTINSTANCE_CLASS_DECLARATION
#define TTFONTINSTANCE_CLASS_DECLARATION

#ifndef WIN32
#include <OSGConfig.h>
#include <OSGBaseTypes.h>

#ifdef OSG_WITH_FREETYPE1
#include "OSGFontStyle.h"
#include "freetype1/freetype/freetype.h"

OSG_BEGIN_NAMESPACE class TTFontStyle :
    public FontStyle
{
    typedef FontStyle       ParentClass;
private:

    /** The FreeType instance of given font */
    TT_Instance             *_ttInstance;

    /** The given font */
    TT_Face                 *_ttFace;

    /** Error container */
    TT_Error                _ttError;
protected:

    /** rerenders stored glyphs in case of resize */
    virtual bool            processChange(void);
public:

    /** Default Constructor */
    TTFontStyle(void);

    /** Copy Constructor */
    TTFontStyle(const TTFontStyle &obj);

    /** Destructor */
    virtual                 ~TTFontStyle(void);

    /** set method for attribute _ttInstance */
    virtual bool            set_ttInstance(TT_Instance *ttInstance,
                                               TT_Face *ttFace);

    /** return specified (ASCII-) Glyph */
    virtual VectorFontGlyph *getVectorGlyph(UInt8 which);

    virtual ImageFontGlyph  *getImageGlyph(UInt8 which);

    virtual bool            createTXFMap(UChar8 *characters = NULL, Int32 gap = 1);

    virtual unsigned char   *getTXFImageMap(void);

    virtual TXFGlyphInfo    *getTXFGlyphInfo(UInt8 ascii);

    virtual bool            dump(ostream &out);
};

OSG_END_NAMESPACE typedef osg::TTFontStyle * TTFontStyleP;
#endif // OSG_WITH_FREETYPE1
#endif
#endif // TTFONTINSTANCE_CLASS_DECLARATION
