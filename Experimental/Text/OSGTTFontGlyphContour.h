#ifndef TTGLYPHCONTOUR_CLASS_DECLARATION
#define TTGLYPHCONTOUR_CLASS_DECLARATION

#include <OSGConfig.h>

#include "OSGFontGlyphContour.h"



OSG_BEGIN_NAMESPACE


class TTFontGlyphContour : public FontGlyphContour {
	typedef FontGlyphContour ParentClass;

private:

protected:

public:

  /** Default Constructor */
  TTFontGlyphContour (void);

  /** Copy Constructor */
  TTFontGlyphContour (const TTFontGlyphContour &obj);

  /** Destructor */
  virtual ~TTFontGlyphContour (void);

  /** does intersection check for given contours */
  virtual bool inside (FontGlyphContour *contour, TT_Outline outline);

};

typedef TTFontGlyphContour* TTFontGlyphContourP;


OSG_END_NAMESPACE


#endif // TTGLYPHCONTOUR_CLASS_DECLARATION
