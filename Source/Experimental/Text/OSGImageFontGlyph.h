#ifndef IMAGEGLYPH_CLASS_DECLARATION
#define IMAGEGLYPH_CLASS_DECLARATION

#ifndef WIN32
#include <OSGConfig.h>
#include <OSGBaseTypes.h>

#include "OSGFontGlyph.h"

/** Image Representation of a FontGlyph.
*
* Defines the 3D-Data-Interface to Glyphs and implements GLU-Tesselation
*
* @author elmi, Sat Mar 11 22:23:14 2000
*/
enum IGlyphType
{
    IGLYPH_NONE     = 0,
    IGLYPH_BIAP,
    IGLYPH_PIXMAP
};

OSG_BEGIN_NAMESPACE class ImageFontGlyph :
    public virtual FontGlyph
{
private:
protected:

    /** wether its bitmap or pixmap */
    IGlyphType      _type;

    Int32           _boundingBox[4];

    Int32           _imageSize[3];

    Int32           _advance;

    UChar8          *_bitmapBuffer;

    UChar8          *_pixmapBuffer;
public:

    /** Default Constructor */
    ImageFontGlyph(void);

    /** Copy Constructor */
    ImageFontGlyph(const ImageFontGlyph &obj);

    /** Constructor */
    ImageFontGlyph(IGlyphType type);

    /** Destructor */
    virtual         ~ImageFontGlyph(void);

    /** clears image-data */
    virtual bool    clear(void);

    const Int32 *getBoundingBox(void)
    {
        return _boundingBox;
    }

    const Int32 *getImageSize(void)
    {
        return _imageSize;
    }

    Int32 getAdvance(void)
    {
        return _advance;
    }

    UChar8 *getImage(void)
    {
        return _type == IGLYPH_BIAP ? _bitmapBuffer : _pixmapBuffer;
    }

    /** get method for attribute type */
    virtual IGlyphType getType(void)
    {
        return _type;
    }

    /** set method for attribute type */
    virtual void setType(IGlyphType type)
    {
        _type = type;
    }
};

typedef ImageFontGlyph  *ImageFontGlyphP;

OSG_END_NAMESPACE
#endif
#endif // IMAGEGLYPH_CLASS_DECLARATION
