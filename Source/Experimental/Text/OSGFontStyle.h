#ifndef FONTINSTANCE_H_
#define FONTINSTANCE_H_

#include <OSGConfig.h>
#include <OSGBaseTypes.h>
#include <OSGSystemDef.h>

#include <vector>
#include <iostream>

OSG_BEGIN_NAMESPACE 

class   FontGlyph;
class   VectorFontGlyph;
class   ImageFontGlyph;
class   TXFGlyphInfo;

class OSG_SYSTEMLIB_DLLMAPPING FontStyle
{
  private:

    FontStyle(const FontStyle &obj);
    void operator =(const FontStyle &obj);

  protected:

            Int32                   _xRes;
            Int32                   _yRes;
            Real32                  _size;
            Real32                  _depth;

            Real32                  _maxDescent;
            Real32                  _maxAscent;
            Real32                  _baselineSkip;

            std::string             _fontName;

    std::vector<VectorFontGlyph *>  _vectorGlyphs;
    std::vector<ImageFontGlyph  *>  _imageGlyphs;
    std::vector<TXFGlyphInfo    *>  _txfGlyphInfos;

            UChar8                 *_txfImageMap;

            Int32                   _txfFontWidth;
            Int32                   _txfFontHeight;

    virtual bool processChange(void);

  public:

    FontStyle(void);

    virtual ~FontStyle(void);

    virtual VectorFontGlyph *getVectorGlyph (UInt8 ascii) = 0;
    virtual ImageFontGlyph  *getImageGlyph  (UInt8 ascii) = 0;
    virtual TXFGlyphInfo    *getTXFGlyphInfo(UInt8 ascii) = 0;

    virtual       void    setTXFImageMap  (      UChar8 *image       );
    virtual       UChar8 *getTXFImageMap  (      void                );

    virtual       bool    getTXFImageSizes(      Int32  &width, 
                                                 Int32  &height      );
    virtual       Int32   getXRes         (      void                );
    virtual       void    setXRes         (      Int32   xRes        );

    virtual       Int32   getYRes         (      void                );
    virtual       void    setYRes         (      Int32   yRes        );

    virtual       Real32  getSize         (      void                );
    virtual       void    setSize         (      Real32  size        );

    virtual       void    setMaxDescent   (      Real32  maxDescent  );
    virtual       Real32  getMaxDescent   (      void                );

    virtual       void    setMaxAscent    (      Real32  maxAscent   );
    virtual       Real32  getMaxAscent    (      void                );

    virtual       void    setBaselineSkip (      Real32  baselineSkip);
    virtual       Real32  getBaselineSkip (      void                );

    virtual const Char8  *getFontName     (      void                );
    virtual       void    setFontName     (const Char8  *name        );

    virtual bool dump(std::ostream &out);
};

OSG_END_NAMESPACE 

#endif // FONTINSTANCE_H_
