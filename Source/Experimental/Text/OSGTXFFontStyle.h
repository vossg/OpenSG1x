#ifndef TXFFONTINSTANCE_CLASS_DECLARATION
#define TXFFONTINSTANCE_CLASS_DECLARATION

#ifndef WIN32
#include <OSGConfig.h>
#include <OSGBaseTypes.h>

#include "OSGFontStyle.h"
#include "OSGTXFFont.h"

OSG_BEGIN_NAMESPACE class TXFFontStyle :
    public FontStyle
{
    typedef FontStyle       ParentClass;
private:
protected:

    /** rerenders stored glyphs in case of resize */
    virtual bool            processChange(void);

    virtual bool            buildGlyphInfos(TXFFont::txfChar * txfGlyphs);
public:

    /** Default Constructor */
    TXFFontStyle(void);

    /** Copy Constructor */
    TXFFontStyle(const TXFFontStyle &obj);

    /** Destructor */
    virtual                 ~TXFFontStyle(void);

    /** set method for image map and glyph-info */
    virtual bool            setTXFInstance(Int32 width, Int32 height,
                                               TXFFont::txfChar * glyphList,
                                               UChar8 * imageMap);

    /** set method for image map and glyph-info */
    virtual TXFGlyphInfo    *getTXFGlyphInfo(UInt8 which);

    /** return specified (ASCII-) Glyph */
    virtual VectorFontGlyph *getVectorGlyph(UInt8 OSG_CHECK_ARG(which))
    {
        return NULL;
    }

    virtual ImageFontGlyph  *getImageGlyph(UInt8 which);
};

OSG_END_NAMESPACE typedef OSG::TXFFontStyle * TXFFontStyleP;
#endif
#endif // TXFFONTINSTANCE_CLASS_DECLARATION
