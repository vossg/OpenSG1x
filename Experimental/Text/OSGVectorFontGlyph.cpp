
#ifndef WIN32

// System declarations
#ifdef __sgi
# include <math.h>
#else
# include <cmath>
#endif
#include <iostream>
#include <fstream>

#include <GL/gl.h>
#include <GL/glu.h>

#include <OSGLog.h>


// Class declarations
#include "OSGVectorFontGlyph.h"
#define  _BLOCK_ALLOC 300


// Application declarations
#include "OSGFontGlyphContour.h"
#include "OSGTesselationHandler.h"



OSG_USING_NAMESPACE


// Static Class Variable implementations: 


VectorFontGlyph::VectorFontGlyph (void )
: _type(VGLYPH_NONE), _depth(1), _precision(30.f),
  _points(), _numPoints(0), _indices(), _numIndices(0), _numBad(0), 
  _bad(false), _vertexBuffer()
{
    return;
}

/*
VectorFontGlyph::VectorFontGlyph (const VectorFontGlyph &obj )
{
	return;
}
*/

VectorFontGlyph::VectorFontGlyph (VGlyphType type )
: _type(type),  _depth(1.f),
  _precision(30.f), _points(), _numPoints(0), _indices(), _numIndices(0),
  _numBad(0), _bad(false), _vertexBuffer()
{
    return;
}

VectorFontGlyph::~VectorFontGlyph (void )
{
    clear();
    return;
}

bool VectorFontGlyph::clear (void )
{
    if(!_points.empty()) _points.clear();
    if(!_indices.empty()) _points.clear();

    return true;
}


void VectorFontGlyph::extrude (void )
{
    Int32 *indices, tmp;

    if(_numIndices*2 > (Int32)_indices.capacity())
	_indices.resize(_numIndices*2);
    memcpy(&(_indices[0])+_numIndices, &(_indices[0]),
	   _numIndices * sizeof(Int32));

    for(Int32 i=_numIndices+2; i<_numIndices*2; i+=3, indices+=3) {
	tmp = _indices[i] +_numPoints;
	_indices[i]=_indices[i-2] +_numPoints;
	_indices[i-2]=tmp;
	_indices[i-1]+=_numPoints;
    }

    _numIndices *= 2;
}

bool VectorFontGlyph::createTriangles(void)
{
    vector<FontGlyphContour *>::iterator cIter;
    FontGlyphContour * doThis;
    GLUtriangulatorObj *triangulator  = gluNewTess();
    GLdouble vertex[3];
    Real32 *point, tmpDepth;
    Int32 totalPoints =0, last, tmp, i, j, k;
    bool lastOrdering=false;

    tmTesselator = this;
    gluTessCallback(triangulator, (GLenum)GLU_BEGIN,
		     (void (OSG_SYSTEMLIB_DLLMAPPING *)()) tessBegin );
    gluTessCallback(triangulator, (GLenum)GLU_VERTEX,
		     (void (OSG_SYSTEMLIB_DLLMAPPING *)()) tessVertex );
    gluTessCallback(triangulator, (GLenum)GLU_EDGE_FLAG,
		     (void (OSG_SYSTEMLIB_DLLMAPPING *)()) tessEdgeFlag );
    gluTessCallback(triangulator, (GLenum)GLU_END,
		     (void (OSG_SYSTEMLIB_DLLMAPPING *)()) tessEnd );
//     gluTessCallback(triangulator, (GLenum)GLU_ERROR,
// 		     (void (OSG_SYSTEMLIB_DLLMAPPING *)()) tessError );

    totalPoints = 0;
    for(cIter = _contours.begin(); cIter != _contours.end(); cIter++) {
	last = totalPoints;
	totalPoints += (*cIter)->getNumPoints();
	_points.resize(totalPoints);
	_normals.resize(totalPoints);
	memcpy(&(_points[0])+last, &((*cIter)->getPoints()[0]),
	       (totalPoints-last) * sizeof(Real32 *));
	memcpy(&(_normals[0])+last, &((*cIter)->getNormals()[0]),
	       (totalPoints-last) * sizeof(Real32 *));
    }

    _depth/=10;
    if(_depth==-0.0) _depth *= -1;
    totalPoints=0;

    tmpDepth = _depth;
    for(k=0;k < (Int32)_contours.size();k++) {
	doThis = _contours[k];
	
	last = totalPoints;
	j =  doThis->getNumPoints();
	totalPoints += j;

	_numPoints=totalPoints;

	if(!k) {
	    lastOrdering =  doThis->isClockwise();
	    gluBeginPolygon(triangulator);
	    gluNextContour(triangulator, (GLenum)GLU_EXTERIOR);
	}
	else {
	    if(doThis->isClockwise() == lastOrdering) {
		gluEndPolygon(triangulator);
		gluBeginPolygon(triangulator);
		gluNextContour(triangulator, (GLenum)GLU_EXTERIOR);
	    }
	    else
		gluNextContour(triangulator, (GLenum)GLU_INTERIOR);
	}

	for(i=0; i < doThis->getNumPoints(); i++) {
	    point = doThis->getPoint(i);
	    vertex[0] = point[0];
	    vertex[1] = point[1];
	    vertex[2] = point[2] = tmpDepth;
	    gluTessVertex(triangulator, vertex, (void *) _points[last +i]);
	}
    }


    if(_depth==-0.0) _depth *=-1;
    _depth*=10;

    if(_numPoints) {
	gluEndPolygon(triangulator);
	gluDeleteTess(triangulator);
	tmTesselator = 0;
    }
    _numFrontFaces = _numIndices/3;

    if(_depth != 0.f) {
 	_indices.resize(_numIndices*2+totalPoints*6+6);
	last = _numPoints;
	extrude();
	
	totalPoints = 0;
	
	for(j=0; j < (Int32)_contours.size(); j++) {
	    tmp = totalPoints;
	    doThis = _contours[j];
	    for(i=0; i < doThis->getNumPoints()-1; i++, totalPoints++) {
		_indices[_numIndices] = totalPoints;
		_indices[_numIndices+1] = totalPoints+last;
		_indices[_numIndices+2] = totalPoints+1;
		
		_indices[_numIndices+3] = totalPoints+last;
		_indices[_numIndices+4] = totalPoints+1+last;
		_indices[_numIndices+5] = totalPoints+1;
		_numIndices +=6;
	    }
	    _indices[_numIndices] = totalPoints;
	    _indices[_numIndices+1] = totalPoints+last;
	    _indices[_numIndices+2] = tmp;
      
	    _indices[_numIndices+3] = totalPoints+last;
	    _indices[_numIndices+4] = tmp+last;
	    _indices[_numIndices+5] = tmp;
	    _numIndices +=6;
	    totalPoints++;
	    tmp +=doThis->getNumPoints();
	}
    }
    return true;
}



Int32 VectorFontGlyph::findPoint(Real32 *point, Int32 lower, Int32 upper)
{
    Int32 l=lower, u=upper, m,f=-1;

    while(!(l>u)) {
	m = (u+l)/2;
	if(point < _points[m]) {
	    u=m-1; continue;
	}
	else if(point > _points[m]) {
	    l = m+1; continue;
	}

	return m;
    }

     for(Int32 i = _numPoints-1; i >= 0; i--)
  	if(point[0] == _points[i][0] && point[1] == _points[i][1])
 	    return(i);

    return f;
}

void VectorFontGlyph::addPoint(Real32 *point, bool OSG_CHECK_ARG(lower) )
{
    Int32 pointIndex=-1, tmp, begin, end, bad=0;

    if(!point || _numBad) {
	_bad = true;
	if(!_numBad) {
	    bad = _numIndices%3;
	    _numBad = 3-bad;
	    _numIndices -= bad;
	}

	_numBad--;

	return;
    }

    tmp = _vertexBuffer.getBufferForPointer(point);
    begin = tmp * (_BLOCK_ALLOC/3);
    end = (begin + (_BLOCK_ALLOC/3) >= (Int32)_points.size() ?
	   _points.size()-1 : begin + (_BLOCK_ALLOC/3)-1);

    if(tmp<0 || (pointIndex = findPoint(point, begin, end)) < 0) {
      FWARNING(("failed in finding point (%f, %f, %f) within point-list of %d points.",
		point[0], point[1], point[2], _numPoints));
	
      return;
    }

    _numIndices++;
    if(_numIndices > (Int32)_indices.size()) 
	_indices.resize(_indices.capacity()+_BLOCK_ALLOC);
    _indices[_numIndices-1] = pointIndex;
}



VectorFontGlyph::FloatBuffer::FloatBuffer(void)
    : _fBuffer(NULL), _fBuffSize(0), _fBuffNext(0), _fWhichBuffer(-1)
{
    return;
}

Real32 *VectorFontGlyph::FloatBuffer::allocFloat(Int32 num)
{
    Real32 *retPtr;
    if(_fWhichBuffer < 0 || num + _fBuffNext > _BLOCK_ALLOC) 
	fBuffAlloc(_BLOCK_ALLOC);

    retPtr = (_fBuffer[_fWhichBuffer]) + _fBuffNext;
    _fBuffNext += num;
    
    return retPtr;
}

void VectorFontGlyph::FloatBuffer::fBuffAlloc(Int32 OSG_CHECK_ARG(size) )
{
    Real32 *nBuf = new Real32[_BLOCK_ALLOC];
    Real32 **buffers = new Real32*[_fWhichBuffer+2];

    _fWhichBuffer++;
    if(_fBuffer) {
	for(Int32 i=0; i< _fWhichBuffer; i++)
	    buffers[i] = _fBuffer[i];
	delete [] _fBuffer;
    }
    _fBuffer = buffers;

    _fBuffer[_fWhichBuffer] = nBuf;
    _fBuffNext=0;
}


Int32 VectorFontGlyph::FloatBuffer::getBufferForPointer(Real32 *pointer)
{
    Int32 tmp=0;
    
    while(tmp <= _fWhichBuffer && !((pointer >= _fBuffer[tmp]) && 
	    (pointer < _fBuffer[tmp]+(_BLOCK_ALLOC*sizeof(Real32)))))
	tmp++;

    if(tmp > _fWhichBuffer) return -1;

    return tmp;
}


void VectorFontGlyph::pushIt(Real32 ** &stack, Int32 & num, Real32 * &elem)
{
    if(num == 3)
	for(Int32 i=1; i<num;i++) stack[i-1] = stack[i];
    num = num !=3 ? num+1 : num;
    stack[num-1]=elem;
}

void VectorFontGlyph::calcNormal(Real32 **&stack, Int32 num, Real32* result)
{
    Real32 length;

    result[0] = -1*(stack[0][1]) + stack[num-1][1];
    result[1] = (-1*(stack[0][0]) + stack[num-1][0])*-1;

    if(fabs(result[0])  == 0.0 && fabs(result[1]) == 0.0) {
	result[0]=-1;
	result[1]=0;
    }
    else {
	length = sqrt(result[0]*result[0]+result[1]*result[1]);
	result[0] /= length;
	result[1] /= length;
    }
    result[2]=0;
}



bool VectorFontGlyph::checkAngle(Real32 **joint)
{
    Real32 v1[3], v2[3], angle, l;

    v1[0] = joint[0][0]-joint[1][0];
    v1[1] = joint[0][1]-joint[1][1];
    l = sqrt(v1[0]*v1[0] + v1[1]*v1[1]);

    v2[0] = joint[2][0]-joint[1][0];
    v2[1] = joint[2][1]-joint[1][1];
    v1[2] = v2[2] = 0;
    l *= sqrt(v2[0]*v2[0] + v2[1]*v2[1]);

    angle = v1[0]*v2[0] + v1[1]*v2[1];

    return (angle/l > -0.86);
}

#endif
