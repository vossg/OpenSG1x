#ifndef FONTINSTANCEFACTORY_CLASS_DECLARATION
#define FONTINSTANCEFACTORY_CLASS_DECLARATION

#ifndef WIN32

#include <OSGConfig.h>
#include <OSGPathHandler.h>

OSG_BEGIN_NAMESPACE class FontStyle; OSG_END_NAMESPACE


#include <list>


OSG_BEGIN_NAMESPACE


class FontStyleFactory {

private:

	static FontStyleFactory _the;

	list<FontStyle*> _instances;

	/** Default Constructor */
	FontStyleFactory(void);

	/** Copy Constructor */
	FontStyleFactory(const FontStyleFactory &);

	/** Copy Operator */
	const FontStyleFactory &operator=(const FontStyleFactory &);

public:

	/** Destructor */
	virtual ~FontStyleFactory();

	FontStyle *create(PathHandler & paths, const Char8 *fontName, Real32 size);

	bool  discard(FontStyle *OSG_CHECK_ARG(fs)) {return false;}

	static inline FontStyleFactory &the(void) { return _the; }

};


OSG_END_NAMESPACE


#endif
#endif // FONTINSTANCEFACTORY_CLASS_DECLARATION
