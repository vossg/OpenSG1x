#ifndef WIN32

// System declarations
#include <iostream>
#ifdef __sgi
# include <assert.h>
#else
# include <cassert>
#endif


// Application declarations
#include "OSGFontStyle.h"
#include "OSGFont.h"
#include "OSGFontFactory.h"

// Class declarations
#include "OSGFontStyleFactory.h"



OSG_USING_NAMESPACE



// Static Class Variable implementations: 
FontStyleFactory FontStyleFactory::_the;


FontStyleFactory::FontStyleFactory(void)
{
}


FontStyleFactory::~FontStyleFactory()
{
}


osg::FontStyle *FontStyleFactory::create(PathHandler & paths, 
                                         const char *fontName, float size)
{
	list<FontStyle*>::const_iterator pos;

	for (pos = _instances.begin(); pos != _instances.end(); ++pos) {
		if (((*pos)->getSize() == size) &&
		    !strcmp((*pos)->getFontName(), fontName)) {
			return (*pos);
		}
	}

	Font *font = FontFactory::the().queryFont(paths, fontName);

	if (!font) {
		cout << "ERROR: Font named " << fontName << " unknown " << endl;
		return 0;
	}

	if (!font->initFont()) {
		cout << "ERROR: Initialization failed for font "
		     << fontName << endl;
		return 0;
	}

	FontStyle *fi = font->createInstance(size);
	if (fi == 0) {
		cout << "ERROR: Instancing failed for font "
		     << fontName << endl;
		return 0;
	}

	_instances.push_back(fi);

	return fi;
}


#endif

