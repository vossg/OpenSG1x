#ifndef WIN32

// System declarations
#ifdef __sgi
# include <math.h>
#else
# include <cmath>
#endif
#include <iostream>


// Application declarations


// Class declarations
#include "OSGTXFFontGlyph.h"




OSG_USING_NAMESPACE



// Static Class Variable implementations: 

TXFFontGlyph::TXFFontGlyph (void )
 : FontGlyph()
{
	return;
}

/*
TXFFontGlyph::TXFFontGlyph (const TXFFontGlyph &obj )
{
	return;
}
*/

TXFFontGlyph::TXFFontGlyph (int ascii, int unicode)
: FontGlyph(ascii, unicode)
{
	return;
}


TXFFontGlyph::~TXFFontGlyph (void )
{
	return;
}

void TXFFontGlyph::setupGlyph (int ascii, int unicode)
{
    setAsciiCode(ascii);
    setUniCode(unicode);
}



bool TXFFontGlyph::createGlyph (void )
{
    if(!isValid()) return false;

    // TODO
    // create image from global image map, set sizes

    return true;
}




bool TXFFontGlyph::setSizes (float *OSG_CHECK_ARG(_boundingBox), 
                             float &OSG_CHECK_ARG(_advance) )
{

    return true;
}



bool TXFFontGlyph::setSizes (int *OSG_CHECK_ARG(_boundingBox), 
                             int &OSG_CHECK_ARG(_advance) )
{
    return true;
}

#endif

