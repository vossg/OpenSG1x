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
#include "OSGFontGlyphContour.h"


// Static Class Variable implementations: 



OSG_USING_NAMESPACE



FontGlyphContour::FontGlyphContour (void )
: _points(), _numPoints(0), _numNormals(0), _isClockwise(false),
  _orderingBuffer(0)
{
    _bb[0] =  HUGE_VAL;
    _bb[1] = -HUGE_VAL;
    _bb[2] =  HUGE_VAL;
    _bb[3] = -HUGE_VAL;
    return;
}

/*
FontGlyphContour::FontGlyphContour (const FontGlyphContour &obj )
{
	return;
}
*/

FontGlyphContour::~FontGlyphContour (void )
{
    _points.resize(0);
    _normals.resize(0);
	return;
}

vector<float *> & FontGlyphContour::getNormals(void)
{
    while(_numNormals != _numPoints) {
	_normals[_numNormals] = _normals[_numNormals-1];
	_numNormals++;
    }
    return _normals;
}


void FontGlyphContour::addPoint (float *point, float *normal, bool copy)
{
    if(_numPoints==(int)_points.size())
	_points.push_back(point);
    else
	_points[_numPoints] = point;

    if(normal) {
	if(_numNormals==(int)_normals.size())
	    _normals.push_back(normal);
	else
	    _normals[_numNormals] = normal;
	if(_numPoints>_numNormals && copy) {
	    _numNormals++;
	    if(_numNormals==(int)_normals.size())
		_normals.push_back(normal);
	    else
		_normals[_numNormals] = normal;
	}
	_numNormals++;
    }
    _numPoints++;
}



bool FontGlyphContour::inside (FontGlyphContour *contour)
{
    if((_bb[0] > contour->getBB()[0]) && (_bb[1] > contour->getBB()[1]) && 
       (_bb[2] < contour->getBB()[2]) && (_bb[3] < contour->getBB()[3]))
	return true;

    return false;
}

#endif
