#ifndef FONTSTYLE_H_
#define FONTSTYLE_H_

//#ifndef WIN32
#include <OSGConfig.h>
#include <OSGBaseTypes.h>
#include <OSGGeometry.h>
#include <OSGImage.h>

#include <vector>
#include <string>

OSG_BEGIN_NAMESPACE 

class FontStyle;

enum TEXT_JUSTIFY_TYPE
{
    FIRST_JT  = 0x0000,
    BEGIN_JT  = 0x0001,
    MIDDLE_JT = 0x0002,
    END_JT    = 0x0003
};

enum FONT_STYLE_TYPE
{
    PLAIN_ST      = 0x0000,
    BOLD_ST       = 0x0001,
    ITALIC_ST     = 0x0002,
    BOLDITALIC_ST = 0x0003
};

enum MergeMode
{
    UNKNOWN_MM   = 0x0000,
    CLEAR_ADD_MM = 0x0001,
    CLEAR_CUT_MM = 0x0002,
    ADD_MM       = 0x0003,
    CUT_MM       = 0x0004
};

enum ImageCreationMode
{
    UNKNOWN_TCM = 0x0000,
    FILL_TCM    = 0x0001,
    SET_TCM     = 0x0002,
    SET_TEX_TCM = 0x0003
};

enum MeshCreationMode
{
    UNKNOWN_MCM       = 0x0000,
    OUTLINE_MCM       = 0x0001,
    FILL_MCM          = 0x0002,
    FILL_TEX_CHAR_MCM = 0x0003,
    FILL_TEX_ALL_MCM  = 0x0004
};

class OSG_SYSTEMLIB_DLLMAPPING Text
{
  
  private:

    friend class FontStyleFactory;

    Text(const Text &obj);
    void operator =(const Text &obj);

  protected:

    bool               _horizontal;
    TEXT_JUSTIFY_TYPE  _justifyMajor;
    TEXT_JUSTIFY_TYPE  _justifyMinor;
    bool               _leftToRight;
    std::string        _language;
    Real32             _size;

    Real32             _precision;
    Real32             _spacing;

    FONT_STYLE_TYPE    _style;

    bool               _topToBottom;

    FontStyle         *_fontInstance;
    bool               _smoothing;

  public:

    Text(void);

    virtual ~Text(void);

    virtual bool               horizontal     (void                         );
    virtual void               setHorizontal  (bool              horizontal );

    virtual TEXT_JUSTIFY_TYPE  justifyMajor   (void);
    virtual void               setJustifyMajor(TEXT_JUSTIFY_TYPE justify    );

    virtual TEXT_JUSTIFY_TYPE  justifyMinor   (void                         );
    virtual void               setJustifyMinor(TEXT_JUSTIFY_TYPE justify    );

    virtual bool               leftToRight    (void                         );
    virtual void               setLeftToRight (bool              leftToRight);

    virtual std::string       &language       (void                         );
    virtual void               setLanguage    (std::string       language   );

    virtual Real32             size           (void                         );
    virtual void               setSize        (Real32            size       );

    virtual Real32             spacing        (void                         );
    virtual void               setSpacing     (Real32            spacing    );

    virtual FONT_STYLE_TYPE    style          (void                         );
    virtual void               setStyle       (FONT_STYLE_TYPE   style      );

    virtual bool               topToBottom    (void                         );
    virtual void               setTopToBottom (bool              topToBottom);

            void               setFontStyle   (FontStyle        *fi         );
            FontStyle         *getFontStyle   (void                         );



    virtual bool   fillTXFImage   (ImagePtr                  &image   );
    virtual bool   fillTXFGeo     (Geometry                  &mesh, 
                                   bool                      isNew,
                                   std::vector<std::string> &lineVec  );
    
    virtual UInt32 getTXFNVertices(std::vector<std::string> &lineVec  );

    virtual bool   fillTXFArrays  (std::vector<std::string> &lineVec, 
                                   Pnt3f                    *points, 
                                   Vec2f                    *texcoords);

    virtual bool   fillImage      (ImagePtr & image, 
                                   std::vector<std::string> &lineVec, 
                                   Color4ub *fg,
                                   Color4ub *bg, 
                                   bool forcePower2, 
                                   Real32 *maxX,
                                   Real32 *maxY,
                                   ImageCreationMode creationMode,
                                   MergeMode         mergeMode, 
                                   Int32 pixelDepth,
                                   bool bConvertToBitmap) const;

    virtual bool   fillGeo        (Geometry                 &mesh, 
                                   std::vector<std::string> &lineVec,
                                   Real32           precision   = 1.f, 
                                   Real32           extFac      = 0.f,
                                   Real32           maxExtend   = 0.f,
                                   MeshCreationMode creationMode=FILL_MCM,
                                   MergeMode        mergeMode   =CLEAR_ADD_MM);
};

typedef Text *TextP;

OSG_END_NAMESPACE
//#endif
#endif // FONTSTYLE_H_
