#ifndef FONT_CLASS_DECLARATION
#define FONT_CLASS_DECLARATION

#ifndef WIN32
#include <OSGConfig.h>
#include <OSGBaseTypes.h>

#include <string>
#include <list>

OSG_BEGIN_NAMESPACE class                   Text;
OSG_END_NAMESPACE OSG_BEGIN_NAMESPACE class FontStyle;
OSG_END_NAMESPACE OSG_BEGIN_NAMESPACE class Font
{
private:

    /** CompletePath To Font */
protected:

    /** CompletePath To Font */
    std::string             _fontPath;

    /** Name of Font */
    const Char8            *_fontName;

    bool                    _valid;

    std::list<FontStyle *>  _fontInstances;

public:

    /** Default Constructor */
    Font(void);

    /** Copy Constructor */
    Font(const Font &obj);

    /** Constructor */
    Font(const Char8 *name);

    /** Constructor */
    Font(const Char8 *name, std::string path);

    /** Destructor */
    virtual             ~Font(void);

    /**  **/
    virtual inline const Char8 *getName(void)
    {
        return _fontName;
    }

    /** loading and storing of font-contents */
    virtual bool        initFont(void) = 0;

    /** creates FontStyle aka Text */
    virtual bool        createInstance(Text *fontStyle) = 0;

    /** creates FontStyle */
    virtual FontStyle   *createInstance(Real32 size) = 0;
};

OSG_END_NAMESPACE typedef osg::Font * FontP;
#endif
#endif // FONT_CLASS_DECLARATION
