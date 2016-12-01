#ifndef TTFONTINSTANCE_H_
#define TTFONTINSTANCE_H_

#include "OSGConfig.h"
#include "OSGBaseTypes.h"

#ifdef OSG_WITH_FREETYPE1

#include "freetype.h"

#include "OSGFontStyle.h"

OSG_BEGIN_NAMESPACE


class OSG_SYSTEMLIB_DLLMAPPING TTFontStyle : public FontStyle
{
    typedef FontStyle Inherited;

  private:

    TTFontStyle(const TTFontStyle &obj);
    void operator =(const TTFontStyle &obj);

  protected:

            TT_Instance *_ttInstance;
            TT_Face     *_ttFace;
            TT_Error     _ttError;

    virtual bool          processChange(void);
  
  public:

    TTFontStyle(void);

    virtual ~TTFontStyle(void);

    virtual bool             set_ttInstance (TT_Instance *ttInstance,
                                             TT_Face     *ttFace      );

    virtual VectorFontGlyph *getVectorGlyph (UInt8 which              );
    virtual ImageFontGlyph  *getImageGlyph  (UInt8 which              );
    virtual TXFGlyphInfo    *getTXFGlyphInfo(UInt8 ascii              );

    virtual bool             createTXFMap   (UChar8 *characters = NULL, 
                                             Int32   gap        = 1   );

    virtual UChar8          *getTXFImageMap (void                     );

    virtual bool             dump           (std::ostream &out        );
};

OSG_END_NAMESPACE 

#endif // OSG_WITH_FREETYPE1
#endif // TTFONTINSTANCE_H_
