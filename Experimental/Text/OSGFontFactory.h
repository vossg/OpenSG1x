#ifndef FONTFACTORY_CLASS_DECLARATION
#define FONTFACTORY_CLASS_DECLARATION

#ifndef WIN32
#include <OSGConfig.h>
#include <OSGBaseTypes.h>
#include <OSGPathHandler.h>

#include <list>

OSG_BEGIN_NAMESPACE class                   Font;
OSG_END_NAMESPACE OSG_BEGIN_NAMESPACE class FontFactory
{
private:

    static FontFactory  _the;

    /** list of known fonts */
    std::list<Font *>        _knownFonts;

protected:
public:

    /** Default Constructor */
    FontFactory(void);

    /** Copy Constructor */
    FontFactory(const FontFactory &obj);

    /** Destructor */
    virtual             ~FontFactory(void);

    /** Queries a Font */
    virtual Font        *queryFont(PathHandler &paths, const Char8 *fontName);

    /** returns the number of fonts found within path list */
    virtual Int32 getNumFonts(void)
    {
        return _knownFonts.size();
    }

    static FontFactory &the(void)
    {
        return _the;
    }
};

OSG_END_NAMESPACE typedef osg::FontFactory * FontFactoryP;
#endif
#endif // FONTFACTORY_CLASS_DECLARATION
