#ifndef FONTSTYLE_CLASS_DECLARATION
#define FONTSTYLE_CLASS_DECLARATION

#ifndef WIN32
#include <OSGConfig.h>
#include <OSGBaseTypes.h>
#include <OSGGeometry.h>
#include <OSGImage.h>

#include <vector>
#include <string>

OSG_BEGIN_NAMESPACE 

class   FontStyle;

enum TEXT_JUSTIFY_TYPE
{
    FIRST_JT    = 0,
    BEGIN_JT,
    MIDDLE_JT,
    END_JT
};
enum FONT_STYLE_TYPE
{
    PLAIN_ST,
    BOLD_ST,
    ITALIC_ST,
    BOLDITALIC_ST
};

enum MergeMode
{
    UNKNOWN_MM      = 0,
    CLEAR_ADD_MM,
    CLEAR_CUT_MM,
    ADD_MM,
    CUT_MM
};

enum ImageCreationMode
{
    UNKNOWN_TCM     = 0,
    FILL_TCM,
    SET_TCM,
    SET_TEX_TCM
};

enum MeshCreationMode
{
    UNKNOWN_MCM         = 0,
    OUTLINE_MCM,
    FILL_MCM,
    FILL_TEX_CHAR_MCM,
    FILL_TEX_ALL_MCM
};

class   Text
{
    friend class        FontStyleFactory;
private:

    bool                _horizontal;

    TEXT_JUSTIFY_TYPE   _justifyMajor;

    TEXT_JUSTIFY_TYPE   _justifyMinor;

    bool                _leftToRight;

    string              _language;

    Real32              _size;

    /** For Bezier-Interpolation */
    Real32              _precision;

    Real32              _spacing;

    FONT_STYLE_TYPE     _style;

    bool                _topToBottom;

    FontStyle           *_fontInstance;

    bool                _smoothing;
protected:

    /** Copy Constructor */
    Text(const Text &obj);
public:

    /** Default Constructor */
    Text(void);

    /** Destructor */
    virtual             ~Text(void);

    /** get method for attribute horizontal */
    virtual bool horizontal(void)
    {
        return _horizontal;
    }

    /** set method for attribute horizontal */
    virtual void setHorizontal(bool horizontal)
    {
        _horizontal = horizontal;
    }

    /** get method for attribute justify */
    virtual TEXT_JUSTIFY_TYPE justifyMajor(void)
    {
        return _justifyMajor;
    }

    /** set method for attribute justify */
    virtual void setJustifyMajor(TEXT_JUSTIFY_TYPE justify)
    {
        _justifyMajor = justify;
    }

    /** get method for attribute justify */
    virtual TEXT_JUSTIFY_TYPE justifyMinor(void)
    {
        return _justifyMinor;
    }

    /** set method for attribute justify */
    virtual void setJustifyMinor(TEXT_JUSTIFY_TYPE justify)
    {
        _justifyMinor = justify;
    }

    /** get method for attribute leftToRight */
    virtual bool leftToRight(void)
    {
        return _leftToRight;
    }

    /** set method for attribute leftToRight */
    virtual void setLeftToRight(bool leftToRight)
    {
        _leftToRight = leftToRight;
    }

    /** get method for attribute language */
    virtual string &language(void)
    {
        return _language;
    }

    /** set method for attribute language */
    virtual void setLanguage(string language)
    {
        _language = string(language);
    }

    /** get method for attribute size */
    virtual Real32 size(void)
    {
        return _size;
    }

    /** set method for attribute size */
    virtual void setSize(Real32 size)
    {
        _size = size;
    }

    /** get method for attribute spacing */
    virtual Real32 spacing(void)
    {
        return _spacing;
    }

    /** set method for attribute spacing */
    virtual void setSpacing(Real32 spacing)
    {
        _spacing = spacing;
    }

    /** get method for attribute style */
    virtual FONT_STYLE_TYPE style(void)
    {
        return _style;
    }

    /** set method for attribute style */
    virtual void setStyle(FONT_STYLE_TYPE style)
    {
        _style = style;
    }

    /** get method for attribute topToBottom */
    virtual bool topToBottom(void)
    {
        return _topToBottom;
    }

    /** set method for attribute topToBottom */
    virtual void setTopToBottom(bool topToBottom)
    {
        _topToBottom = topToBottom;
    }

    /** set method for attribute fontInstance */
    void setFontStyle(FontStyle *fi)
    {
        _fontInstance = fi;
    }

    FontStyle *getFontStyle(void)
    {
        return _fontInstance;
    }

    virtual bool    fillTXFImage(Image &image);

    virtual bool    fillTXFGeo(Geometry &mesh, bool isNew,
                                   vector<string> &lineVec);

    virtual UInt32  getTXFNVertices(vector<string> &lineVec);

    virtual bool    fillTXFArrays(vector<string> &lineVec, 
                                  Pnt3f *points, Vec2f *texcoords);

    virtual bool    fillImage(Image &image, vector<string> &lineVec,
                                  Color4ub *fg = 0, Color4ub *bg = 0,
                                  bool forcePower2 = false, Real32 *maxX = 0,
                                  Real32 *maxY = 0,
                                  ImageCreationMode creationMode = SET_TEX_TCM,
                                  MergeMode mergeMode = CLEAR_ADD_MM,
                                  Int32 pixelDepth = 3) const;

    virtual bool    fillGeo(Geometry &mesh, vector<string> &lineVec,
                                Real32 precision = 1.f, Real32 extFac = 0.f,
                                Real32 maxExtend = 0.f,
                                MeshCreationMode creationMode = FILL_MCM,
                                MergeMode mergeMode = CLEAR_ADD_MM);
};

typedef Text    *TextP;

OSG_END_NAMESPACE
#endif
#endif // FONTSTYLE_CLASS_DECLARATION
