#ifndef FONTINSTANCEFACTORY_CLASS_DECLARATION
#define FONTINSTANCEFACTORY_CLASS_DECLARATION

#include <OSGConfig.h>
#include <OSGPathHandler.h>

#include <list>

OSG_BEGIN_NAMESPACE 

class FontStyle;

class FontStyleFactory
{
  private:

    FontStyleFactory(const FontStyleFactory &);
    void operator =(const FontStyleFactory &);

  protected:

    static FontStyleFactory       _the;

           std::list<FontStyle *> _instances;

    FontStyleFactory(void);
  
  public:

    static FontStyleFactory &the(void);

    virtual ~FontStyleFactory(void);

    FontStyle *create (      PathHandler &paths,
                       const Char8       *fontName,
                             Real32       size    );
    
    bool       discard(      FontStyle   *        );
};

OSG_END_NAMESPACE

#endif // FONTINSTANCEFACTORY_CLASS_DECLARATION
