
#include <OSGConfig.h>

#ifdef __sgi
#include <math.h>
#else
#include <cmath>
#endif

#include <iostream>

#include "OSGFontGlyphContour.h"

OSG_USING_NAMESPACE 

FontGlyphContour::FontGlyphContour(void) :
    _points(),
    _numPoints(0),
    _numNormals(0),
    _isClockwise(false),
    _orderingBuffer(0)
{
    _bb[0] = TypeTraits<Real32>::getMax();
    _bb[1] = TypeTraits<Real32>::getMin();
    _bb[2] = TypeTraits<Real32>::getMax();
    _bb[3] = TypeTraits<Real32>::getMin();
    return;
}

FontGlyphContour::~FontGlyphContour(void)
{
    _points.resize(0);
    _normals.resize(0);
    return;
}

Real32 *FontGlyphContour::getPoint(Int32 which)
{
    return _points[which];
}

std::vector<Real32 *> &FontGlyphContour::getPoints(void)
{
    return _points;
}

Int32 FontGlyphContour::getNumPoints(void)
{
    return _numPoints;
}

Real32 *FontGlyphContour::getNormal(Int32 which)
{
    return _normals[which];
}

std::vector<Real32 *> &FontGlyphContour::getNormals(void)
{
    while(_numNormals != _numPoints)
    {
        _normals[_numNormals] = _normals[_numNormals - 1];
        _numNormals++;
    }

    return _normals;
}

Int32 FontGlyphContour::getNumNormals(void)
{
    return _numNormals;
}

void FontGlyphContour::addPoint(Real32 *point, Real32 *normal, bool copy)
{
    if(_numPoints == (int) _points.size())
        _points.push_back(point);
    else
        _points[_numPoints] = point;

    if(normal)
    {
        if(_numNormals == (int) _normals.size())
            _normals.push_back(normal);
        else
            _normals[_numNormals] = normal;
        if(_numPoints > _numNormals && copy)
        {
            _numNormals++;
            if(_numNormals == (int) _normals.size())
                _normals.push_back(normal);
            else
                _normals[_numNormals] = normal;
        }

        _numNormals++;
    }

    _numPoints++;
}

bool FontGlyphContour::isClockwise(void)
{
    return _isClockwise;
}

Real32 FontGlyphContour::getArea(void)
{
    return _orderingBuffer;
}

void FontGlyphContour::setOrdering(Real32 ordering)
{
    _orderingBuffer = ordering;
}

void FontGlyphContour::setBB(Real32 *bb)
{
    _bb[0] = bb[0];
    _bb[1] = bb[1];
    _bb[2] = bb[2];
    _bb[3] = bb[3];
}

Real32 *FontGlyphContour::getBB(void)
{
    return _bb;
}

void FontGlyphContour::setWhichTTContour(Int32 which)
{
    _contour = which;
}

Int32 FontGlyphContour::getWhichTTContour(void)
{
    return _contour;
}

Int32 FontGlyphContour::getStart(void)
{
    return _startContour;
}

void FontGlyphContour::setStart(Int32 start)
{
    _startContour = start;
}

bool FontGlyphContour::inside(FontGlyphContour *contour)
{
    if((_bb[0] > contour->getBB()[0]) &&
       (_bb[1] > contour->getBB()[1]) &&
       (_bb[2] < contour->getBB()[2]) &&
       (_bb[3] < contour->getBB()[3]))
    {
        return true;
    }

    return false;
}

void FontGlyphContour::setIsClockwise(void)
{
    _isClockwise = true;
}

void FontGlyphContour::setIsNotClockwise(void)
{
    _isClockwise = false;
}

void FontGlyphContour::setNumPoints(Int32 num)
{
    _points.resize(num);
    _normals.resize(num);
}

Int32 FontGlyphContour::getNumPointsExpected(void)
{
    return _points.size();
}
