#ifndef TTVECTORGLYPH_H_
#define TTVECTORGLYPH_H_

#include <OSGConfig.h>
#include <OSGBaseTypes.h>

#ifdef OSG_WITH_FREETYPE1

#include "OSGVectorFontGlyph.h"
#include "OSGTTFontGlyph.h"


OSG_BEGIN_NAMESPACE 

class OSG_SYSTEMLIB_DLLMAPPING TTVectorFontGlyph :
    public virtual FontGlyph,
    public         VectorFontGlyph,
    public         TTFontGlyph
{

  private:

    TTVectorFontGlyph(const TTVectorFontGlyph &obj);
    void operator =(const TTVectorFontGlyph &obj);

  protected:

    static Real64  _ttScale;

           Real32  _ttScaleToVRML;
           Real32 *_tmpNormalBuffer;



    Int32 processArc  (FontGlyphContour  *glyphContour,
                       TT_Outline         outline, 
                       Int32              start,
                       Int32              contour, 
                       Real32           **normalStack,
                       Int32             &numnStack, 
                       Int32             &counter,
                       Int32              step   = 1, 
                       bool               dryRun = false);
    
    Int32 sortContours(TT_Outline         outline       );

    void  cleanup     (void                             );

  public:

    TTVectorFontGlyph(void);
    TTVectorFontGlyph(VGlyphType type, Int32 ascii, Int32 unicode);

    virtual ~TTVectorFontGlyph(void);

            void setup         (VGlyphType type, 
                                Int32      ascii, 
                                Int32      unicode    );
            void setScaleFactor(Real32     scaleFactor);
    virtual bool create        (void                  );
};

OSG_END_NAMESPACE

#endif // OSG_WITH_FREETYPE1
#endif // TTVECTORGLYPH_H_
