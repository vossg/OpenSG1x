// System declarations
#include <iostream>

// Application declarations


// Class declarations
#include "OSGFontGlyph.h"


// Static Class Variable implementations: 



OSG_USING_NAMESPACE



FontGlyph::FontGlyph (void )
: _valid(true), _asciiCode(-1), _uniCode(-1)
{
	return;
}

FontGlyph::FontGlyph (const FontGlyph &obj )
: _valid(true), _asciiCode(-1), _uniCode(-1)
{
	return;
}

FontGlyph::FontGlyph (int ascii, int unicode)
: _valid(true), _asciiCode(ascii), _uniCode(unicode)
{
	return;
}

FontGlyph::~FontGlyph (void )
{
	return;
}


