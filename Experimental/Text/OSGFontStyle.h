#ifndef FONTINSTANCE_CLASS_DECLARATION
#define FONTINSTANCE_CLASS_DECLARATION

#ifndef WIN32
#include <OSGConfig.h>
#include <OSGBaseTypes.h>

#include <vector>
#include <iostream>

/** Abstract instance of a font at an given size.
*
*
* @author elmi, Sat Mar 11 19:24:13 2000
*/
OSG_BEGIN_NAMESPACE class   FontGlyph;
class                       VectorFontGlyph;
class                       ImageFontGlyph;
class                       TXFGlyphInfo;

class                       FontStyle
{
private:

    /** x Resolution of device */
    Int32                       _xRes;

    /** x Resolution of device */
    Int32                       _yRes;

    /** desired 'Point-Size' of font */
    Real32                      _size;

    /** desired z-dpeth of font */
    Real32                      _depth;

    Real32                      _maxDescent;

    Real32                      _maxAscent;

    Real32                      _baselineSkip;

    const char                  *_fontName;
protected:

    /** list fo created glyphs */
    std::vector<VectorFontGlyph *> _vectorGlyphs;
    std::vector<ImageFontGlyph  *> _imageGlyphs;
    std::vector<TXFGlyphInfo    *> _txfGlyphInfos;

    UChar8                      *_txfImageMap;

    Int32                       _txfFontWidth;
    Int32                       _txfFontHeight;

    /** rerenders stored glyphs in case of resize */
    virtual bool                processChange(void);
public:

    /** Default Constructor */
    FontStyle(void);

    /** Copy Constructor */
    FontStyle(const FontStyle &obj);

    /** Destructor */
    virtual                     ~FontStyle(void);

    /** get method for attribute glyphs */
    virtual VectorFontGlyph     *getVectorGlyph(UInt8 ascii) = 0;

    /** get method for attribute glyphs */
    virtual ImageFontGlyph      *getImageGlyph(UInt8 ascii) = 0;

    /** get method for attribute glyphs */
    virtual TXFGlyphInfo        *getTXFGlyphInfo(UInt8 ascii) = 0;

    /** set method for image map */
    virtual void setTXFImageMap(unsigned char *image)
    {
        _txfImageMap = image;
    }

    /** et method for image map */
    virtual unsigned char *getTXFImageMap(void)
    {
        return _txfImageMap;
    }

    /** get method for image map dimmensions */
    virtual bool    getTXFImageSizes(Int32 &width, Int32 &height);

    virtual bool dump(ostream &OSG_CHECK_ARG(out))
    {
        return false;
    }

    /** get method for attribute _xRes */
    virtual inline Int32 getXRes(void)
    {
        return _xRes;
    }

    /** set method for attribute _xRes */
    virtual void setXRes(Int32 xRes)
    {
        _xRes = xRes;
    }

    /** get method for attribute _yRes */
    virtual inline Int32 getYRes(void)
    {
        return _yRes;
    }

    /** set method for attribute _yRes */
    virtual void setYRes(Int32 yRes)
    {
        _yRes = yRes;
    }

    /** get method for attribute _size */
    virtual inline Real32 getSize(void)
    {
        return _size;
    }

    /** set method for attribute _size */
    virtual void setSize(Real32 size)
    {
        _size = size;
    }

    virtual void setMaxDescent(Real32 maxDescent)
    {
        _maxDescent = maxDescent;
    }

    virtual inline Real32 getMaxDescent(void)
    {
        return _maxDescent;
    }

    virtual void setMaxAscent(Real32 maxAscent)
    {
        _maxAscent = maxAscent;
    }

    virtual inline Real32 getMaxAscent(void)
    {
        return _maxAscent;
    }

    virtual void setBaselineSkip(Real32 baselineSkip)
    {
        _baselineSkip = baselineSkip;
    }

    virtual inline Real32 getBaselineSkip(void)
    {
        return _baselineSkip;
    }

    virtual const Char8 *getFontName(void)
    {
        return _fontName;
    }

    virtual void setFontName(const Char8 *name)
    {
        _fontName = name;
    }
};

OSG_END_NAMESPACE typedef osg::FontStyle * FontStyleP;
#endif
#endif // FONTINSTANCE_CLASS_DECLARATION
