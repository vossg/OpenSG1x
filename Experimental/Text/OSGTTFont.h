#ifndef TTFONT_CLASS_DECLARATION
#define TTFONT_CLASS_DECLARATION

#include <OSGConfig.h>

#include "OSGFont.h"
#include "freetype1/freetype/freetype.h.h"




OSG_BEGIN_NAMESPACE


class TTFont : public virtual Font {
    
    typedef Font ParentClass;

private:

    TT_Engine _ttEngine;

    TT_Face _ttFace;

    TT_Error _ttError;

protected:

public:

  /** Default Constructor */
  TTFont (void);

  /** Copy Constructor */
  TTFont (const TTFont &obj);

  /** Constructor */
  TTFont (const char *name, string path);

  /** Destructor */
  virtual ~TTFont (void);

  /** loading and storing of font-contents */
  bool initFont (void);

  /** creates FontStyle aka FontStyle */
  virtual bool createInstance (Text *text);

  /** creates FontStyle */
  virtual FontStyle *createInstance (float size);

};


OSG_END_NAMESPACE

typedef osg::TTFont* TTFontP;


#endif // TTFONT_CLASS_DECLARATION
