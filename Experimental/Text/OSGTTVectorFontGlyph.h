#ifndef TTVECTORGLYPH_CLASS_DECLARATION
#define TTVECTORGLYPH_CLASS_DECLARATION

#ifndef WIN32
#include <OSGConfig.h>
#include <OSGBaseTypes.h>

#ifdef OSG_WITH_FREETYPE1
#include "OSGVectorFontGlyph.h"
#include "OSGTTFontGlyph.h"

#include "freetype1/freetype/freetype.h"

OSG_BEGIN_NAMESPACE class TTVectorFontGlyph :
    public virtual FontGlyph,
    public VectorFontGlyph,
    public TTFontGlyph
{
    /* 	typedef VectorFontGlyph ParentClass; */
private:

    static Real64   _ttScale;

    Real32          _ttScaleToVRML;

    Real32          *_tmpNormalBuffer;

    Int32           processArc(FontGlyphContour *glyphContour,
                                   TT_Outline outline, Int32 start,
                                   Int32 contour, Real32 **normalStack,
                                   Int32 &numnStack, Int32 &counter,
                                   Int32 step = 1, bool dryRun = false);

    Int32           sortContours(TT_Outline outline);

    void            cleanup(void);

    inline Real32 max(Real32 a, Real32 b)
    {
        return a > b ? a : b;
    }

    inline Real32 min(Real32 a, Real32 b)
    {
        return a < b ? a : b;
    }

protected:
public:

    /** Default Constructor */
    TTVectorFontGlyph(void);

    /** Copy Constructor */
    TTVectorFontGlyph(const TTVectorFontGlyph &obj);

    /** Constructor */
    TTVectorFontGlyph(VGlyphType type, Int32 ascii, Int32 unicode);

    /** Destructor */
    virtual ~TTVectorFontGlyph(void);

    /** Constructor */
    void    setup(VGlyphType type, Int32 ascii, Int32 unicode);

    void setScaleFactor(Real32 scaleFactor)
    {
        _ttScaleToVRML = (scaleFactor * 64.0) / _size;
    }

    /** creates desired representation */
    virtual bool    create(void);
};

typedef TTVectorFontGlyph   *TTVectorFontGlyphP;

OSG_END_NAMESPACE
#endif // OSG_WITH_FREETYPE1
#endif
#endif // TTVECTORGLYPH_CLASS_DECLARATION
