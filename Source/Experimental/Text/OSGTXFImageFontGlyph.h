#ifndef TXFIMAGEGLYPH_H_
#define TXFIMAGEGLYPH_H_

#include <OSGConfig.h>
#include <OSGBaseTypes.h>

#include "OSGImageFontGlyph.h"
#include "OSGTXFFontGlyph.h"

OSG_BEGIN_NAMESPACE 

class OSG_SYSTEMLIB_DLLMAPPING TXFImageFontGlyph :
    public         ImageFontGlyph,
    public virtual TXFFontGlyph
{

  private:

    TXFImageFontGlyph(const TXFImageFontGlyph &obj);
    void operator =(const TXFImageFontGlyph &obj);

  protected:


    UChar8 *_srcImage;
    Int32   _srcWidth;
    Int32   _srcHeight;

    Int32   _xOff;
    Int32   _yOff;

  public:

    TXFImageFontGlyph(void);
    TXFImageFontGlyph(IGlyphType type, Int32 ascii, Int32 unicode);

    virtual ~TXFImageFontGlyph(void);

            void setup        (IGlyphType  type, 
                               Int32       ascii, 
                               Int32       unicode   );
            void setFontDefs  (Int16       x, 
                               Int16       y, 
                               Int8       *dimensions);
            void setFontSource(UChar8     *srcImage, 
                               Int32       width, 
                               Int32       height    );
    virtual bool create       (void                  );
};

OSG_END_NAMESPACE

#endif // TXFIMAGEGLYPH_H_
