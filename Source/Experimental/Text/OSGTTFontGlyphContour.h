#ifndef TTGLYPHCONTOUR_CLASS_DECLARATION
#define TTGLYPHCONTOUR_CLASS_DECLARATION

#include <OSGConfig.h>

#include "OSGFontGlyphContour.h"

#include "freetype/freetype.h"

OSG_BEGIN_NAMESPACE 

class OSG_SYSTEMLIB_DLLMAPPING TTFontGlyphContour : public FontGlyphContour
{
    typedef FontGlyphContour Inherited;

  private:

    TTFontGlyphContour(const TTFontGlyphContour &obj);
    void operator =(const TTFontGlyphContour &obj);
    
  protected:
  public:
    
    TTFontGlyphContour(void);

    virtual ~TTFontGlyphContour(void);

    virtual bool inside(FontGlyphContour *contour,
                        TT_Outline        outline);
};

OSG_END_NAMESPACE

#endif // TTGLYPHCONTOUR_CLASS_DECLARATION
