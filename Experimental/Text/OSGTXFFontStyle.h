#ifndef TXFFONTINSTANCE_CLASS_DECLARATION
#define TXFFONTINSTANCE_CLASS_DECLARATION

#ifndef WIN32

#include <OSGConfig.h>

#include "OSGFontStyle.h"
#include "OSGTXFFont.h"


OSG_BEGIN_NAMESPACE


class TXFFontStyle : public FontStyle {
	typedef FontStyle ParentClass;

private:
	
protected:

  /** rerenders stored glyphs in case of resize */
  virtual bool processChange (void);

  virtual bool buildGlyphInfos (TXFFont::txfChar *txfGlyphs);

public:

  /** Default Constructor */
  TXFFontStyle (void);

  /** Copy Constructor */
  TXFFontStyle (const TXFFontStyle &obj);

  /** Destructor */
  virtual ~TXFFontStyle (void);

  /** set method for image map and glyph-info */
  virtual bool setTXFInstance (int width, int height,
			       TXFFont::txfChar *glyphList,
			       unsigned char *imageMap);

  /** set method for image map and glyph-info */
  virtual TXFGlyphInfo *getTXFGlyphInfo (int which);

  /** return specified (ASCII-) Glyph */
  virtual VectorFontGlyph * getVectorGlyph (int OSG_CHECK_ARG(which)) 
    {return NULL;}

  virtual ImageFontGlyph * getImageGlyph (int which);

};

OSG_END_NAMESPACE


typedef osg::TXFFontStyle* TXFFontStyleP;




#endif
#endif // TXFFONTINSTANCE_CLASS_DECLARATION
