
#include <OSGConfig.h>

#include <iostream>

#ifdef OSG_WITH_FREETYPE1

#include "OSGTTFontGlyphContour.h"

OSG_USING_NAMESPACE 

TTFontGlyphContour::TTFontGlyphContour(void) :
    Inherited()
{
}

TTFontGlyphContour::~TTFontGlyphContour(void)
{
}

bool TTFontGlyphContour::inside(FontGlyphContour *contour, TT_Outline outline)
{
    Real64  x, y, x1, x2 = 0.0, y1, y2 = 0.0, ix;
    Int32   intersections = 0, i, i2, which, start, end, off;
    if(!
       (
           (_bb[0] > contour->getBB()[0]) &&
           (_bb[1] > contour->getBB()[1]) &&
           (_bb[2] < contour->getBB()[2]) &&
           (_bb[3] < contour->getBB()[3])
           ))
    {
        return false;
    }

    which = _contour;

    x = outline.points[which ? outline.contours[which - 1] + 1 : 0].x;
    y = outline.points[which ? outline.contours[which - 1] + 1 : 0].y;

    which = contour->getWhichTTContour();
    off = which ? outline.contours[which - 1] + 1 : 0;
    x1 = outline.points[off].x;
    y1 = outline.points[off].y;

    start = off;
    end = outline.contours[which];

    for(i = start; i <= end; i++, x1 = x2, y1 = y2)
    {
        i2 = i + 1 > end ? off : i + 1;

        x2 = outline.points[i2].x;
        y2 = outline.points[i2].y;

        if((y1 > y && y2 > y) || (y1 < y && y2 < y))
            continue;

        if(y1 == y2)
        {
            if(y1 == y && (x1 < x || x2 < x))
                intersections++;
            continue;
        }

        ix = x1 + (y - y1) * (x2 - x1) / (y2 - y1);
        if(ix <= x)
            intersections++;
    }

    if(!(intersections % 2))
        return false;

    return true;
}
#endif // OSG_WITH_FREETYPE1
