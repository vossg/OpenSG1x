// System declarations
#include <iostream>


// Application declarations


// Class declarations
#include "OSGFont.h"



OSG_USING_NAMESPACE


// Static Class Variable implementations: 


Font::Font (void )
: _fontPath(NULL), _fontName(NULL), _valid(false)
{
    return;
}

/*
Font::Font (const Font &obj)
: _fontPath(obj.__fontPath), _fontName(obj._fontName), _valid(false)
{
	return;
}
*/

Font::Font (const char *name)
: _fontName(name), _valid(false)
{
    return;
}


Font::Font (const char *name, string path )
: _fontPath(path), _fontName(name), _valid(false)
{
    return;
}


Font::~Font (void )
{
	return;
}

