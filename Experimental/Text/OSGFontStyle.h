#ifndef FONTINSTANCE_CLASS_DECLARATION
#define FONTINSTANCE_CLASS_DECLARATION

#include <OSGConfig.h>

#include <vector>
#include <iostream>

/** Abstract instance of a font at an given size.
*
*
* @author elmi, Sat Mar 11 19:24:13 2000
*/





OSG_BEGIN_NAMESPACE 

class FontGlyph;  
class VectorFontGlyph;
class ImageFontGlyph;
class TXFGlyphInfo;


class FontStyle {

private:

  /** x Resolution of device */
  int _xRes;

  /** x Resolution of device */
  int _yRes;

  /** desired 'Point-Size' of font */
  float _size;

  /** desired z-dpeth of font */
  float _depth;

  float _maxDescent;

  float _maxAscent;

  float _baselineSkip;

  const char *_fontName;

protected:

  /** list fo created glyphs */
  vector<VectorFontGlyph *> _vectorGlyphs;
  vector<ImageFontGlyph *> _imageGlyphs;
  vector<TXFGlyphInfo *> _txfGlyphInfos;

  unsigned char           *_txfImageMap;

  int                      _txfFontWidth;
  int                      _txfFontHeight;

  /** rerenders stored glyphs in case of resize */
  virtual bool processChange (void);

public:

  /** Default Constructor */
  FontStyle (void);

  /** Copy Constructor */
  FontStyle (const FontStyle &obj);

  /** Destructor */
  virtual ~FontStyle (void);

  /** get method for attribute glyphs */
  virtual VectorFontGlyph *getVectorGlyph (int ascii) = 0;

  /** get method for attribute glyphs */
  virtual ImageFontGlyph *getImageGlyph (int ascii) = 0;

  /** get method for attribute glyphs */
  virtual TXFGlyphInfo *getTXFGlyphInfo (int ascii) = 0;

  /** set method for image map */
  virtual void setTXFImageMap (unsigned char * image) {_txfImageMap = image;}

  /** et method for image map */
  virtual unsigned char *getTXFImageMap (void) {return _txfImageMap;}

  /** get method for image map dimmensions */
  virtual bool getTXFImageSizes (int &width, int &height);

  virtual bool dump(ostream & OSG_CHECK_ARG(out)) {return false;}

  /** get method for attribute _xRes */
  virtual inline int getXRes (void)
     { return _xRes; }


  /** set method for attribute _xRes */
  virtual void setXRes (int xRes)
     { _xRes = xRes; }


  /** get method for attribute _yRes */
  virtual inline int getYRes (void)
     { return _yRes; }


  /** set method for attribute _yRes */
  virtual void setYRes (int yRes)
     { _yRes = yRes; }


  /** get method for attribute _size */
  virtual inline float getSize (void)
     { return _size; }


  /** set method for attribute _size */
  virtual void setSize (float size)
      { _size = size;}

  virtual void setMaxDescent(float maxDescent)
    { _maxDescent = maxDescent; }

  virtual inline float getMaxDescent(void)
    { return _maxDescent; }

  virtual void setMaxAscent(float maxAscent)
    { _maxAscent = maxAscent; }

  virtual inline float getMaxAscent(void)
    { return _maxAscent; }

  virtual void setBaselineSkip(float baselineSkip)
    { _baselineSkip = baselineSkip ; }

  virtual inline float getBaselineSkip(void)
    { return _baselineSkip; }

  virtual const char *getFontName(void)
      { return _fontName;}

  virtual void setFontName(const char *name)
      { _fontName = name;}

 };

OSG_END_NAMESPACE



typedef osg::FontStyle* FontStyleP;




#endif // FONTINSTANCE_CLASS_DECLARATION
