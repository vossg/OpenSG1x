#ifndef TTGLYPH_CLASS_DECLARATION
#define TTGLYPH_CLASS_DECLARATION

#ifdef OSG_WITH_FREETYPE1

#include <OSGConfig.h>
#include <OSGBaseTypes.h>

#include "OSGFontGlyph.h"

#include "freetype/freetype.h"

OSG_BEGIN_NAMESPACE 

class OSG_SYSTEMLIB_DLLMAPPING TTFontGlyph : public virtual FontGlyph
{
    typedef FontGlyph Inherited;

  private:

    TTFontGlyph(const TTFontGlyph &obj);
    void operator =(const TTFontGlyph &obj);

  protected:

//    static Real64            _ttScale;

           TT_Error          _ttError;
           TT_Glyph          _ttGlyph;
           TT_Glyph_Metrics  _ttGlyphMetrics;
           TT_Face          *_ttFace;
           TT_Instance      *_ttInstance;

  public:
    
    TTFontGlyph(void);
    TTFontGlyph(Int32 ascii, Int32 unicode);

    virtual ~TTFontGlyph(void);

            void setupGlyph (Int32          ascii, 
                             Int32          unicode     );
    virtual void setFontDefs(TT_Face       *ttFacte, 
                             TT_Instance   *ttInstance  );
    virtual bool createGlyph(void                       );
    virtual bool getOutline (TT_Outline    &ttOutline   );
    virtual bool setSizes   (Real32        *_boundingBox, 
                             Real32        &_advance    );
    virtual bool setSizes   (Int32         *_boundingBox, 
                             Int32         &_advance    );
    virtual void glyphDone  (void                       );
    virtual bool renderGlyph(TT_Raster_Map   map, 
                             Int32           xOff, 
                             Int32           yOff       );
};

OSG_END_NAMESPACE

#endif // OSG_WITH_FREETYPE1
#endif // TTGLYPH_CLASS_DECLARATION
