#ifndef TXFFONT_CLASS_DECLARATION
#define TXFFONT_CLASS_DECLARATION

#include <OSGConfig.h>

#include "OSGFont.h"
#include "OSGTXFGlyphInfo.h"

#include <iostream>



OSG_BEGIN_NAMESPACE


class TXFFont : public virtual Font {
    
    typedef Font ParentClass;

public:

    struct txfChar {
      char           dimensions[6];
      short          x, y;
      unsigned char  remapped;
      txfChar(void) : remapped(' ') {;}
    };

private:

    int             _txfIsBitmap;
    int             _txfFontMaxAscent;
    int             _txfFontMaxDescent;
    int             _txfFontWidth;
    int             _txfFontHeight;
    int             _txfNumGlyphs;
    txfChar        *_txfGlyphs;
    unsigned char  *_txfImageMap;


protected:

    void initFromStream(istream & source);

public:

  /** Default Constructor */
  TXFFont (void);

  /** Copy Constructor */
  TXFFont (const TXFFont &obj);

  /** Constructor */
  TXFFont (const char *name, string path);

  /** Constructor */
  TXFFont (const char *name, istream & source);

  /** Destructor */
  virtual ~TXFFont (void);

  /** loading and storing of font-contents */
  bool initFont (void);

  /** creates FontStyle aka FontStyle */
  virtual bool createInstance (Text *text);

  /** creates FontStyle */
  virtual FontStyle *createInstance (float size);

};


OSG_END_NAMESPACE

typedef osg::TXFFont* TXFFontP;


#endif // TXFFONT_CLASS_DECLARATION
