#ifndef IMAGEGLYPH_H_
#define IMAGEGLYPH_H_

#include <OSGConfig.h>
#include <OSGBaseTypes.h>

#include "OSGFontGlyph.h"

enum IGlyphType
{
    IGLYPH_NONE   = 0x0000,
    IGLYPH_BIAP   = 0x0001,
    IGLYPH_PIXMAP = 0x0002
};

OSG_BEGIN_NAMESPACE 

class OSG_SYSTEMLIB_DLLMAPPING ImageFontGlyph : public virtual FontGlyph
{
    typedef FontGlyph Inherited;

  private:

    ImageFontGlyph(const ImageFontGlyph &obj);
    void operator =(const ImageFontGlyph &obj);
    
  protected:
    
    IGlyphType  _type;
    Int32       _boundingBox[4];
    Int32       _imageSize[3];
    Int32       _advance;
    UChar8     *_bitmapBuffer;
    UChar8     *_pixmapBuffer;

  public:

    ImageFontGlyph(void);
    ImageFontGlyph(IGlyphType type);

    virtual ~ImageFontGlyph(void);

    virtual bool        clear         (void           );

    const   Int32      *getBoundingBox(void           );
    const   Int32      *getImageSize  (void           );
            Int32       getAdvance    (void           );
            UChar8     *getImage      (void           );
    virtual IGlyphType  getType       (void           );
    virtual void        setType       (IGlyphType type);
};

OSG_END_NAMESPACE

#endif // IMAGEGLYPH_H_
