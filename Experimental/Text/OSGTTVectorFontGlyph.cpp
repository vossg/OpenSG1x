// System declarations

#ifdef OSG_WITH_FREETYPE1

#ifdef __sgi
# include <math.h>
#else
# include <cmath>
#endif
#include <iostream>

#include "OSGBaseTypes.h"


// Application declarations
#include "freetype1/freetype/freetype.h"
#include "OSGTTFontGlyphContour.h"

// Class declarations
#include "OSGTTVectorFontGlyph.h"



OSG_USING_NAMESPACE



// Static Class Variable implementations: 

double TTVectorFontGlyph::_ttScale =  1.f / 64;

TTVectorFontGlyph::TTVectorFontGlyph (void )
 : VectorFontGlyph(), TTFontGlyph(), _ttScaleToVRML(1.f)
{
	return;
}

TTVectorFontGlyph::TTVectorFontGlyph (const TTVectorFontGlyph
                                      &OSG_CHECK_ARG(obj) )
{
	assert(false);
}

TTVectorFontGlyph::TTVectorFontGlyph (VGlyphType type, int ascii, int unicode)
: VectorFontGlyph(type),  TTFontGlyph(ascii, unicode)
{
	return;
}


TTVectorFontGlyph::~TTVectorFontGlyph (void )
{
	return;
}

void TTVectorFontGlyph::setup (VGlyphType type, int ascii, int unicode)
{
    setupGlyph(ascii, unicode);
    setType(type);
}


float endSeg[2], s1[2], s2[2];
int TTVectorFontGlyph::processArc(FontGlyphContour* glyphContour, 
				 TT_Outline outline, int start, int contour,
				 float ** normalStack, int & numOnStack,
				 int & counter, int step, bool dryRun)
{
    int numOffPoints = 1, s, f, result=0, steps, end, 
	step2=2*step;
    float a, *point=0, *last, *normal=0;
    double dt;
    double tt, t1, t2, t3, x, y, t;
    bool doFirst=false;

    if(step > 0) {
	f = (contour ? outline.contours[contour-1]+1 : 0);
	end = outline.contours[contour];
    }
    else {
	f = outline.contours[contour];
	end = contour ? outline.contours[contour-1]+1 : 0;
    }

    if(!(outline.flags[start]&1)) {
	if(start==f) {
	    endSeg[0] = outline.points[end].x * _ttScale;
	    endSeg[1] = outline.points[end].y * _ttScale;
	}
	else {
	    endSeg[0] = outline.points[start - step].x * _ttScale;
	    endSeg[1] = outline.points[start - step].y * _ttScale;
	}
	if(!(outline.flags[start+step]&1))
	    numOffPoints++;

    }
    else {
	endSeg[0] = outline.points[start].x * _ttScale;
	endSeg[1] = outline.points[start].y * _ttScale;
    }

    s = start;
    while(!(outline.flags[step+start]&1) && !(outline.flags[step2+s]&1) && 
	  ((step > 0 && s + step2 <= end) ||(step < 0 && s + step2 >= end))){
	numOffPoints++;
	s+=step;
    }

    s=start;
    while(numOffPoints) {
	s1[0] = endSeg[0];
	s1[1] = endSeg[1];
	if(!dryRun && s != start) {
	    point = _vertexBuffer.allocFloat(3);
	    point[0] = s1[0];
	    point[1] = s1[1];
	    point[2] = 0;
	    pushIt(normalStack, numOnStack, point);
	    if(numOnStack>=2) {
		normal = _normalBuffer.allocFloat(3);
		calcNormal(normalStack, numOnStack, normal);
	    }
	    glyphContour->addPoint(point, normal);
	}
	result++;

	if(s==start && !(outline.flags[start]&1) && 
	   !(outline.flags[start+step]&1)) {
	    endSeg[0] = ((outline.points[s].x +
			  outline.points[s+step].x)/2)
		* _ttScale;
	    endSeg[1] = ((outline.points[s].y +
			  outline.points[s+step].y)/2)
		* _ttScale;
	    doFirst = true;
	}
	else if(s==start && !(outline.flags[start]&1) && 
		(outline.flags[start+step]&1)) {
	    endSeg[0] = (outline.points[start+step].x) * _ttScale;
	    endSeg[1] = (outline.points[start+step].y) * _ttScale;
	    doFirst = true;
	}
	else if (doFirst) {
	    doFirst = false;
	    s = start;
	}

	if(numOffPoints == 1 && !doFirst) {
	    if((step > 0 && s+step2 <= end) ||
	       (step < 0 && s+step2 >= end)){
		endSeg[0] = outline.points[s+step2].x * _ttScale;
		endSeg[1] = outline.points[s+step2].y * _ttScale;
	    }
	    else {
		endSeg[0] = outline.points[f].x * _ttScale;
		endSeg[1] = outline.points[f].y * _ttScale;
	    }
	}
	else if(!doFirst){
	    endSeg[0] = ((outline.points[s+step2].x +
			  outline.points[s+step].x)/2)
		* _ttScale;
	    endSeg[1] = ((outline.points[s+step2].y +
			  outline.points[s+step].y)/2)
		* _ttScale;
	}

	if(!(outline.flags[start]&1) &&  doFirst) {
	    s2[0] = outline.points[s].x *_ttScale;
	    s2[1] = outline.points[s].y * _ttScale;
	}
	else {
	    s2[0] = outline.points[s+step].x *_ttScale;
	    s2[1] = outline.points[s+step].y * _ttScale;
	}

	a = max(fabs(max(max(s1[0], s2[0]), endSeg[0]) -
		     min(min(s1[0], s2[0]), endSeg[0])),
		fabs(max(max(s1[1], s2[1]), endSeg[1]) -
		     min(min(s1[1], s2[1]),endSeg[1])))/_precision;
	steps = (int)ceil(a);
	result += steps;

	dt= 1. / (float)steps ;
	t= dt;
	if(!dryRun) {
	    if(steps==1 && numOnStack==2) {
		point = _vertexBuffer.allocFloat(3);
		point[0] = normalStack[numOnStack-1][0];
		point[1] = normalStack[numOnStack-1][1];
		point[2] = 0.f;
		normal = _normalBuffer.allocFloat(3);
		calcNormal(normalStack, numOnStack, normal);
		glyphContour->addPoint(point, normal);
	    }
	    for(register int j= 1; j < steps; ++j, t+= dt ) {
		tt= 1. - t; t1= tt * tt;
		t2= 2. * t * tt; t3= t * t;
		x= t1 * (s1[0]) + t2 * (s2[0]) + t3 * (endSeg[0]);
		y= t1 * (s1[1]) + t2 * (s2[1]) + t3 * (endSeg[1]);
		point = _vertexBuffer.allocFloat(3);
		point[0] = x;
		point[1] = y;
		point[2] = 0;
		pushIt(normalStack, numOnStack, point);
		if(numOnStack==3 && checkAngle(normalStack)) {
		    last = _vertexBuffer.allocFloat(3);
		    last[0] = point[0];
		    last[1] = point[1];
		    point[0] = normalStack[numOnStack-2][0];
		    point[1] = normalStack[numOnStack-2][1];
		    last[2] = 0.f;
		    numOnStack = 2;
		    normal = _normalBuffer.allocFloat(3);
		    calcNormal(normalStack, numOnStack, normal);
		    glyphContour->addPoint(point, normal);
		    point = last;
		    normal= 0;
		    normalStack[0] = normalStack[1];
		    normalStack[1] = point;
		    numOnStack=2;
		}
		if(numOnStack>=2) {
		    normal = _normalBuffer.allocFloat(3);
		    calcNormal(normalStack, numOnStack, normal);
		}
		glyphContour->addPoint(point, normal);
	    }
	}
	s+=step; numOffPoints--;
    }

    counter += result;

    if(!doFirst)
	return (s-start+step);
    else
	return (s-start);
}


bool TTVectorFontGlyph::create (void )
{
    FontGlyphContour *glyphContour=0;
    TT_Outline ttOutline;
    int i = 0, j, k, numOnStack=0, numPoints=0, step;
    float *point=0, *last, *first=0,  firstX, firstY, *normal=0, **normalStack,
	length, lastN[3];
    bool retVal, dontAddFirst=false;
    vector<FontGlyphContour *>::iterator gIter;

    if(_numPoints) return true;

    if(!createGlyph()) return(false);

    if(!getOutline(ttOutline)) return false;

    normalStack = new float *[3];

    i=j=0;
    while(j < ttOutline.n_contours) {
	glyphContour = new TTFontGlyphContour;
	_contours.push_back(glyphContour);
	while(i <= ttOutline.contours[j]) {
	    if(i < ttOutline.contours[j] && (ttOutline.flags[i]&1) &&
	       !(ttOutline.flags[i+1]&1)) {
		numPoints+=2;
		i += processArc(glyphContour, ttOutline, i, j, normalStack,
				numOnStack, numPoints, 1, true);
 		if(i==ttOutline.contours[j] && (ttOutline.flags[i]&1))
		    numPoints++;
	    }
	    else {
		numPoints+=2;
		i++;
	    }
	}
     
  	numPoints+=2;
	glyphContour->setNumPoints(numPoints);
	numPoints=0;
	j++;
    }
    step = sortContours(ttOutline);

    k = j = i = 0; first=0;
    gIter = _contours.begin();
    normal = 0;
    while(k < ttOutline.n_contours) {
	glyphContour = *gIter;
	i = glyphContour->getStart();
	j = glyphContour->getWhichTTContour();
	firstX = ttOutline.points[i].x*_ttScale;
	firstY = ttOutline.points[i].y*_ttScale;
	
	while(step > 0 && i <= ttOutline.contours[j] ||
	      step < 0 && i >= (j ? ttOutline.contours[j-1]+1 : 0)) {
	    if((step < 0 && i == glyphContour->getStart() &&
		!(ttOutline.flags[i]&1))) {
		point = _vertexBuffer.allocFloat(3);
		if(step<0) {
		    point[0] = 
			(ttOutline.points[(j?ttOutline.contours[j-1]+1:0)].x
			 *_ttScale);
		    point[1] = 		  
			(ttOutline.points[(j?ttOutline.contours[j-1]+1:0)].y
			 *_ttScale);
		}
		first = point;
		firstX = first[0];
		firstY = first[1];
		glyphContour->addPoint(point, normal);
		pushIt(normalStack, numOnStack, point);
		i += processArc(glyphContour, ttOutline, i, j, normalStack,
				numOnStack, numPoints, step);
		dontAddFirst = true;
	    }
	    else if((step > 0 && i < ttOutline.contours[j] &&
		     (ttOutline.flags[i]&1) && !(ttOutline.flags[i+step]&1)) ||
		    (step < 0 && i > (j ? ttOutline.contours[j-1]+1 : 0) &&
		     (ttOutline.flags[i]&1) && !(ttOutline.flags[i+step]&1))) {
		point = _vertexBuffer.allocFloat(3);
		point[0] = (ttOutline.points[i].x*_ttScale);
		point[1] = (ttOutline.points[i].y*_ttScale);
		point[2] = 0;
		pushIt(normalStack, numOnStack, point);
		if(numOnStack==3 && checkAngle(normalStack)) {
		    last = _vertexBuffer.allocFloat(3);
		    last[0] = point[0];
		    last[1] = point[1];
		    point[0] = normalStack[1][0];
		    point[1] = normalStack[1][1];
		    last[2] = 0.f;
		    normalStack[0] = normalStack[1];
		    normalStack[1] = last;
		    numOnStack = 2;
		    normal = _normalBuffer.allocFloat(3);
		    calcNormal(normalStack, numOnStack, normal);
		    glyphContour->addPoint(point, normal, true);
		    point = last;
		    numOnStack=1;
		    pushIt(normalStack, numOnStack, point);
		    normal=0;
		}
		else if(numOnStack>=2) {
		    normal = _normalBuffer.allocFloat(3);
		    calcNormal(normalStack, numOnStack, normal);
		}
		if(!first) {
		    first = point;
		    firstX = first[0];
		    firstY = first[1];
		}
		glyphContour->addPoint(point, normal);

		i += processArc(glyphContour, ttOutline, i, j, normalStack,
				numOnStack, numPoints, step);

 		if((step > 0 && i == ttOutline.contours[j] && 
		    (ttOutline.flags[i]&1)) ||
		   (step < 0 && i == (j ? ttOutline.contours[j-1]+1 : 0) &&
		    (ttOutline.flags[i]&1))) {
		    point = _vertexBuffer.allocFloat(3);
		    point[0] = (ttOutline.points[i].x*_ttScale);
		    point[1] = (ttOutline.points[i].y*_ttScale);
		    point[2] = 0;
		    pushIt(normalStack, numOnStack, point);
		    if(numOnStack>=2) {
			normal = _normalBuffer.allocFloat(3);
			calcNormal(normalStack, numOnStack, normal);
		    }
		    glyphContour->addPoint(point, normal);
		    if(numOnStack) {
			normalStack[0] = normalStack[numOnStack-1];
			numOnStack = 2;
			normalStack[numOnStack-1] = point;
		    }
		    i+=step;
		}
	    }
	    else {
		if(numOnStack==2) {
		    normal= 0;
		    last = _vertexBuffer.allocFloat(3);
		    last[0] = normalStack[numOnStack-1][0];
		    last[1] = normalStack[numOnStack-1][1];
		    last[2] = 0.f;
		    normalStack[0] = normalStack[numOnStack-1];
		    numOnStack = 1;
		    glyphContour->addPoint(last, normal, true);
		}
		point = _vertexBuffer.allocFloat(3);
		point[0] = (ttOutline.points[i].x*_ttScale);
		point[1] = (ttOutline.points[i].y*_ttScale);
		point[2] = 0;
		pushIt(normalStack, numOnStack, point);

		if(numOnStack==3 && checkAngle(normalStack)) {
		    normal= 0;
		    last = _vertexBuffer.allocFloat(3);
		    last[0] = point[0];
		    last[1] = point[1];
		    point[0] = normalStack[numOnStack-2][0];
		    point[1] = normalStack[numOnStack-2][1];
		    last[2] = 0.f;
		    normalStack[0] = normalStack[numOnStack-2];
		    numOnStack = 1;
		    glyphContour->addPoint(point, normal);
		    point = last;
		    pushIt(normalStack, numOnStack, point);
		}

		if(numOnStack>=2) {
		    normal = _normalBuffer.allocFloat(3);
		    calcNormal(normalStack, numOnStack, normal);
		}

		if(!first)
		    first = point;

		glyphContour->addPoint(point, normal, true);
		i+=step;
	    }
	}

	if(!dontAddFirst) {
	    point = _vertexBuffer.allocFloat(3);
	    point[0] = firstX;
	    point[1] = firstY;
	    point[2] = 0;
	    
	    if(numOnStack==2) {
		normalStack[0] = normalStack[numOnStack-1];
		numOnStack = 1;
		normal= 0;
		last = _vertexBuffer.allocFloat(3);
		last[0] = point[0];
		last[1] = point[1];
		point[0] = normalStack[0][0];
		point[1] = normalStack[0][1];
		last[2] = 0.f;
		glyphContour->addPoint(point, normal);
		normalStack[1] = last;
		point = last;
		numOnStack++;
		normal = _normalBuffer.allocFloat(3);
		calcNormal(normalStack, numOnStack, normal);
	    }
	    else {
		calcNormal(normalStack, numOnStack, lastN);

		pushIt(normalStack, numOnStack, point);
		first = glyphContour->getPoint(1);
		pushIt(normalStack, numOnStack, first);
		
		normal = _normalBuffer.allocFloat(3);
		calcNormal(normalStack, numOnStack, normal);
		
		if(!checkAngle(normalStack))
		    glyphContour->getNormals()[0] = normal;
		else {
		    last = _vertexBuffer.allocFloat(3);
		    last[0] = point[0];
		    last[1] = point[1];
		    point[0] = first[0];
		    point[1] = first[1];
		    normalStack[1] = last;
		    numOnStack = 2;
		    glyphContour->addPoint(last, 0);
		    point = last;
		    calcNormal(normalStack, numOnStack, normal);
		}
	    }
	    glyphContour->addPoint(point, normal, true);
	}
	else {
	    normal = glyphContour->getNormal(0);
	    last  = glyphContour->getNormal(glyphContour->getNumNormals()-1);
	    if((normal[0]*last[0] + normal[1]*last[1]) > 0.86) {
		normal = _normalBuffer.allocFloat(3);
		normal[0] = glyphContour->getNormal(1)[0];
		normal[1] = glyphContour->getNormal(1)[1];
		normal[2] = 0.f;
		normal[0] += last[0];
		normal[1] += last[1];
	        length = sqrt(normal[0]*normal[0] + normal[1]*normal[1]);
		normal[0]/=length;
		normal[1]/=length;
		glyphContour->getNormals()[0] = normal;
		glyphContour->getNormals()[glyphContour->getNumNormals()-1]
		    = normal;
	    }
	}
	first=point=normal=0;
	dontAddFirst=false;
	numOnStack=0;
	gIter++;
	k++;
    }

    if(!setSizes(_boundingBox, _advance)) return false;
    _boundingBox[4]= -_depth;
    _boundingBox[5]= _depth;

    retVal = createTriangles();
    
    if(retVal) {
	cleanup();
	for(i=0; i<_numPoints; i++) {
	    _points[i][0] /= _ttScaleToVRML;
	    _points[i][1] /= _ttScaleToVRML;
	}
	_advance /= _ttScaleToVRML;
	
	_boundingBox[0] /= _ttScaleToVRML;
	_boundingBox[1] /= _ttScaleToVRML;
	_boundingBox[2] /= _ttScaleToVRML;
	_boundingBox[3] /= _ttScaleToVRML;
    }

    glyphDone();

    for(i=0; i < (int)_contours.size(); i++) delete _contours[i];

    _contours.resize(0);

    delete normalStack;

    return retVal;

}

int TTVectorFontGlyph::sortContours(TT_Outline outline)
{
    int i,j, largestIsClockwise=-1;
    float bb[4], order;
    float last[2];
    bool clockwise=false;
    vector<FontGlyphContour *> contourList, contourLeftList;
    FontGlyphContour *doThis=NULL, *cIter=NULL;
    int ret=1;

    j=0;
    for(i=0; i < outline.n_contours; i++) {
	order = 0.0;
	bb[0] = bb[1]=  HUGE_VAL;
	bb[2] = bb[3]= -HUGE_VAL;
	clockwise = false;
	
	for(;j <= outline.contours[i]; j++) {
        Real32 x = static_cast<Real32>(outline.points[j].x);
        Real32 y = static_cast<Real32>(outline.points[j].y);
	    if(x < bb[0]) 
            bb[0] = x;
	    if(x > bb[2]) 
            bb[2] = x;
	    if(y < bb[1])    
            bb[1] = y;
	    if(y > bb[3]) 
            bb[3] = y;

	    if(j!= (i ? outline.contours[i-1]+1 : 0)) {
		order += (x * last[1] - y * last[0]);
		clockwise = order < 0.f;
	    }
	    last[0] = x;
	    last[1] = y;
	}
	order +=
	    (static_cast<Real32>(outline.points[i ? outline.contours[i-1]+1 : 0].x)
             * last[1] - 
	     static_cast<Real32>(outline.points[i ? outline.contours[i-1]+1 : 0].y)
             * last[0]);
	clockwise = order < 0.f;

	if(clockwise) {
	    _contours[i]->setIsClockwise();
	}
	_contours[i]->setWhichTTContour(i);;
	_contours[i]->setBB(bb);
	_contours[i]->setOrdering(order);
    }


    contourList.resize(_contours.size());
    contourLeftList.resize(_contours.size());

    if(_contours.size() != 1) {
	int total, left=_contours.size();
	float area=0.0;
	for(i=0; i<(int)_contours.size(); i++) {
	    contourLeftList[i]  = _contours[i];
	    contourList[i]  = 0;
	}
	
 	while(left) {
	    total = left;
	    for(i=0; i<(int)_contours.size(); i++) {
		cIter = contourLeftList[i];
		if(cIter==0) continue;
		if(fabs(cIter->getArea()) > area ) {
		    if(largestIsClockwise == -1 ||
		       (int)cIter->isClockwise() == largestIsClockwise) {
			doThis = contourList[_contours.size()-total];
			contourList[_contours.size()-total] = 
			    contourLeftList[i];
			if(area != 0.0)
			    contourLeftList[i] = doThis;
			else contourLeftList[i] = 0;
			left = total-1;
			area = fabs(cIter->getArea());
			doThis = contourList[_contours.size()-total];
		    }
		}
	    }
	    if(largestIsClockwise==-1)  
		largestIsClockwise=doThis->isClockwise();

	    for(i=0; i<(int)_contours.size(); i++) {
		cIter = contourLeftList[i];
		if(cIter==0) continue;
		if(((int)cIter->isClockwise() == largestIsClockwise) &&
		   fabs(cIter->getArea()) < area) {
		    doThis = contourList[_contours.size()-total];
		    contourList[_contours.size()-total] = 
			contourLeftList[i];
		    contourLeftList[i] = doThis;
		    area = fabs(cIter->getArea());
		    doThis = contourList[_contours.size()-total];
		}
	    }

	    for(i=0; i<(int)_contours.size(); i++) {
		cIter = contourLeftList[i];
		if(!cIter) continue;
		if(cIter->isClockwise() != doThis->isClockwise() &&
		   ((TTFontGlyphContour*)cIter)->inside(doThis, outline)) {
		    contourList[_contours.size()-left] = contourLeftList[i];
		    contourLeftList[i] = 0;
		    left--;
		}
	    }

	    if(left==total) {
		for(i=0; i<(int)_contours.size(); i++) {
		    cIter = contourLeftList[i];
		    if(!cIter) continue;
		    contourList[_contours.size()-left] = contourLeftList[i];
		    contourLeftList[i] = 0;
		    left--;
		}
	    }
	    area = 0;
 	}
    }
    else contourList[0] = _contours[0];

    for(i=0; i < outline.n_contours; i++) {
     _contours[i] = contourList[i];

     if(!_contours[0]->isClockwise()) {
         _contours[i]->
     	setStart(outline.contours[_contours[i]->getWhichTTContour()]);
         ret = -1;
     }
     else {
         _contours[i]->
	     setStart(_contours[i]->getWhichTTContour() ? outline.
		      contours[_contours[i]->getWhichTTContour()-1]+1 : 0);
     }
    }

    contourList.resize(0);
    contourLeftList.resize(0);

    return ret;
}


void TTVectorFontGlyph::cleanup(void)
{
    vector <int *> offsets;
    int *offset=0, totalOffset=0, i, current=0, index, inSize, num;

    _indices.resize(_numIndices);
    _normalIndices.resize(_indices.size());
    memcpy(_normalIndices.begin(), _indices.begin(),
           (_indices.size()) * sizeof(int));
    
    _numNormals = _numPoints;

    offset = new int[2];
    offset[0] = 0;
    offset[1] = 0;
    offsets.push_back(offset);

    for(i=1; i < (int)_points.size(); i++)
        if(_points[i][0] == _points[i-1][0] &&
           _points[i][1] == _points[i-1][1] &&
           _points[i][2] == _points[i-1][2]) {
            offset = new int[2];
            totalOffset++;
            offset[0] = i;
            offset[1] = totalOffset;
            offsets.push_back(offset);
        }

    totalOffset = 0;
    for(i=0; i <(int) _points.size(); i++) {
        if(i==offsets[current][0]) {
            totalOffset = offsets[current][1];
            if(current+1 < (int)offsets.size())
                current++;
            continue;
        }
        if(!totalOffset) continue;
        _points[i-totalOffset] = _points[i];
    }
    inSize = offsets.size();
    
    for(i=0; i< inSize; i++) {
        offset = new int[2];
        offset[0] = offsets[i][0] + _numPoints;
        offset[1] = totalOffset + offsets[i][1];
        offsets.push_back(offset);
    }
    _numPoints -= totalOffset;
    _points.resize(_numPoints);

    totalOffset = 0;
    for(i=0; i < (int)_indices.size(); i++) {
        current = 0;
        index=_indices[i];
        while(index > offsets[current][0] && current != (int)offsets.size()-1)
            current++;
        if(current == (int)offsets.size()) current--;
        if(index < offsets[current][0]) current--;
        _indices[i] = index - offsets[current][1];
    }

    for(i=0; i < (int)_indices.size(); i+=3) {
        num=0;
        if(_indices[i]==_indices[i+1]) num++;;
        if(_indices[i+1]==_indices[i+2]) num++;;
        if(_indices[i]==_indices[i+2]) num++;;
        if(num) {
            _indices[i]=-1;
       }
    }
    num=0;
    for(i=0; i < (int)_indices.size(); i+=3) {
        if(_indices[i]==-1)
            num+=3;
        else if(num) {
            _indices[i-num]=_indices[i];
            _indices[i-num+1]=_indices[i+1];
            _indices[i-num+2]=_indices[i+2];
            _normalIndices[i-num]=_normalIndices[i];
            _normalIndices[i-num+1]=_normalIndices[i+1];
            _normalIndices[i-num+2]=_normalIndices[i+2];
        }
    }

    _numIndices-= num;
    _indices.resize(_numIndices);
    _normalIndices.resize(_numIndices);

    for(i=0; i< (int)offsets.size(); i++) {
        delete [] offsets[i];
        offsets[i] = 0;
    }
    offsets.resize(0);
}

#endif // OSG_WITH_FREETYPE1

