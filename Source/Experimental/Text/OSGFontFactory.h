#ifndef FONTFACTORY_CLASS_DECLARATION
#define FONTFACTORY_CLASS_DECLARATION

#include <OSGConfig.h>
#include <OSGBaseTypes.h>
#include <OSGPathHandler.h>

#include <list>

OSG_BEGIN_NAMESPACE 

class Font;

class FontFactory
{
  private:

    FontFactory(const FontFactory &obj);
    void operator =(const FontFactory &obj);

  protected:

    static FontFactory       _the;

           std::list<Font *> _knownFonts;
  public:
    
    static FontFactory &the(void);

    FontFactory(void);

    virtual ~FontFactory(void);

    virtual Font *queryFont  (PathHandler &paths, const Char8 *fontName);

            Int32 getNumFonts(void                                     );
};

OSG_END_NAMESPACE

#include <OSGFontFactory.inl>

#endif // FONTFACTORY_CLASS_DECLARATION
