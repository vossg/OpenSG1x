#ifndef WIN32

// System declarations
#include <iostream>
#ifdef __sgi
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
#else
# include <cmath>
# include <cstdlib>
# include <cstdio>
#endif
#include <assert.h>


// Application declarations
#include <OSGConfig.h>
#include <OSGSimpleGeometry.h>
#include <OSGBaseFunctions.h>
#include <OSGGeometry.h>
#include <OSGColor.h>
#include <OSGImage.h>

#include <OSGSimpleTexturedMaterial.h>

// Class declarations
#include "OSGText.h"
#include "OSGFontStyle.h"
#include "OSGVectorFontGlyph.h"
#include "OSGImageFontGlyph.h"
#include "OSGTXFGlyphInfo.h"



OSG_USING_NAMESPACE




// Static Class Variable implementations: 


Text::Text (void )
: _horizontal(true), _justifyMajor(BEGIN_JT), _justifyMinor(FIRST_JT),
  _leftToRight(true), _size(1),  _precision(1.f), _spacing(1),
  _style(PLAIN_ST), _topToBottom(true), _fontInstance(0),
  _smoothing(false), _txfNode(NULL), _txfGeo(NULL), _txfTexture(NULL)
  
{
    return;
}


Text::Text(const Text &OSG_CHECK_ARG(obj))
{
    assert(false);
}

Text::~Text(void)
{
    return;
}





bool Text::fillTxfNode(NodePtr node, vector<string*> lineVec)
{
  int i, j, k, sStart, sStop, sStep, lStart, lStop, lStep;
  int numChars, numLineChars, vertOff, stride=0, width, height;
  float xOff, yOff, scale, tmpWidth, oaWidth;
  TXFGlyphInfo *currentGlyph;
  GeoPositionsPtr points;
  GeoNormalsPtr normals;
  GeoTexCoordsPtr texCoords;
  GeoPTypesPtr ftypes;        
  GeoPLengthsPtr flengths;    
  GeoIndicesPtr faces;
  bool isNew=false;

  numChars = 0;
  for(i=0; i < lineVec.size(); i++)
    numChars += strlen(lineVec[i]->c_str());

  if(!_txfGeo) {
    _txfGeo = Geometry::create();
    points = GeoPositions3f::create();
    normals = GeoNormals3f::create();
    texCoords = GeoTexCoords2f::create();

    ftypes = GeoPTypesUI8::create();        
    flengths = GeoPLengthsUI32::create();    
    faces = GeoIndicesUI32::create();

    normals->resize(1);
    normals->setValue(Vec3f(0.0, 0.0, -1.0), 0);

    isNew = true;
  }
  else {
    points = _txfGeo->getPositions();
    texCoords = _txfGeo->getTexCoords();

    ftypes = _txfGeo->getTypes();
    flengths = _txfGeo->getLengths();
    faces = _txfGeo->getIndices();
  }

  faces->resize(numChars*8);
  points->resize(numChars*4);
  texCoords->resize(numChars*4);
  flengths->resize(numChars);
  ftypes->resize(numChars);

  
  beginEditCP(ftypes, GeoPTypesUI8::GeoPropDataFieldMask);
  beginEditCP(flengths, GeoPLengthsUI32::GeoPropDataFieldMask);
  beginEditCP(points, GeoPositions3f::GeoPropDataFieldMask);
  beginEditCP(normals, GeoNormals3f::GeoPropDataFieldMask);
  beginEditCP(texCoords, GeoNormals3f::GeoPropDataFieldMask);
  beginEditCP(faces, GeoIndicesUI32::GeoPropDataFieldMask);

  scale = ((float)_fontInstance->getBaselineSkip()*_fontInstance->getYRes());

  oaWidth=0.f;
  tmpWidth=0.f;
  for(i=0; i<lineVec.size(); i++) {
    const char *text = lineVec[i]->c_str();
    numLineChars = strlen(text);
    for(j=0; j< numLineChars; j++)
      tmpWidth += _fontInstance->getTXFGlyphInfo(text[j])->getAdvance()/scale;
    oaWidth = tmpWidth > oaWidth ? tmpWidth : oaWidth;
    tmpWidth = 0;
  }


  vertOff=0;
  yOff = 0.0;
  if(_topToBottom) {
    lStart=0;
    lStop = lineVec.size();
    lStep = 1;
  }
  else {
    lStart=lineVec.size()-1;
    lStop = -1;
    lStep = -1;
  }
  for(k=lStart; k != lStop; k+=lStep) {
    numLineChars = strlen(lineVec[k]->c_str());
    const char *text = lineVec[k]->c_str();

    if(_justifyMajor == MIDDLE_JT || _justifyMajor == END_JT)
      for(j=0; j< numLineChars; j++)
	tmpWidth += _fontInstance->getTXFGlyphInfo(text[j])->getAdvance()/scale;

    switch(_justifyMajor) {
    case FIRST_JT:
    case BEGIN_JT:
      xOff=0.0;
      break;
    case MIDDLE_JT:
      xOff= tmpWidth/-2;
      break;
    case END_JT:
      xOff=-tmpWidth;
      break;
    }
    tmpWidth = 0;

    if(_leftToRight) {
      sStart = 0;
      sStop  = numLineChars;
      sStep  = 1;
    }
    else {
      sStart = numLineChars-1;
      sStop  = -1;
      sStep  = -1;
    }
    for (i=sStart; i != sStop; i+=sStep) {
      for(j=0; j<4;j++, vertOff++) {
	currentGlyph = _fontInstance->getTXFGlyphInfo(text[i]);
	points->setValue(Vec3f(currentGlyph->getVertexCoords(j)[0]/scale+xOff,
			       currentGlyph->getVertexCoords(j)[1]/scale+yOff, 0.0),
			 vertOff);

	texCoords->setValue(Vec2f(currentGlyph->getTextureCoords(j)[0],
				  currentGlyph->getTextureCoords(j)[1]),
			    vertOff);
      }
      xOff += currentGlyph->getAdvance()/scale;
    }
    yOff -= (float)_fontInstance->getBaselineSkip();
  }


  for (i=0; i< numChars; i++) {
    ftypes->setValue(GL_QUADS, i);
    flengths->setValue(4, i);
  }

  for(i = 0; i < numChars*4; i++, stride+=2) {
    faces->setValue(i, stride);
    faces->setValue(0, stride+1);
  }
    
  endEditCP(faces, GeoIndicesUI32::GeoPropDataFieldMask);
  endEditCP(texCoords, GeoNormals3f::GeoPropDataFieldMask);
  endEditCP(normals, GeoNormals3f::GeoPropDataFieldMask);
  endEditCP(points, GeoPositions3f::GeoPropDataFieldMask);
  endEditCP(flengths, GeoPLengthsUI32::GeoPropDataFieldMask);
  endEditCP(ftypes, GeoPTypesUI8::GeoPropDataFieldMask);

  beginEditCP(_txfGeo, Geometry::TypesFieldMask          |
	      Geometry::LengthsFieldMask        |
	      Geometry::IndicesFieldMask        |
	      Geometry::IndexMappingFieldMask   |
	      Geometry::PositionsFieldMask      |
	      Geometry::NormalsFieldMask        |
	      Geometry::MaterialFieldMask       );

    
  if(isNew) {
    _txfGeo->setPositions(points);
    _txfGeo->setTexCoords(texCoords);
    _txfGeo->setNormals(normals);
    
    _txfGeo->setTypes(ftypes);
    _txfGeo->setLengths(flengths);
    _txfGeo->setIndices(faces);

    _txfGeo->getIndexMapping().addValue(Geometry::MapPosition |
				   Geometry::MapTexcoords);
    _txfGeo->getIndexMapping().addValue(Geometry::MapNormal);

    SimpleTexturedMaterialPtr mat = SimpleTexturedMaterial::create();

    Image *txfTexture = new Image();
    _fontInstance->getTXFImageSizes(width, height);
    txfTexture->set(Image::OSG_LA_PF, width, height, 1, 1, 1, 0.0,
		    _fontInstance->getTXFImageMap(), false);

    beginEditCP(mat);
    {
      mat->setImage(txfTexture);
    }
    endEditCP(mat);

    _txfGeo->setMaterial(mat);

    node->setCore(_txfGeo);

  }
  endEditCP(_txfGeo, Geometry::TypesFieldMask          |
	    Geometry::LengthsFieldMask        |
	    Geometry::IndicesFieldMask        |
	    Geometry::IndexMappingFieldMask   |
	    Geometry::PositionsFieldMask      |
	    Geometry::NormalsFieldMask        |
	    Geometry::MaterialFieldMask       );



  return true;
}




bool Text::fillImage (Image &image, 
		      vector<string*> lineVec,
		      Color4ub *fg, Color4ub *bg, 
		      bool forcePower2, Real32 *maxX, Real32 *maxY,
		      ImageCreationMode OSG_CHECK_ARG(creationMode),
		      MergeMode OSG_CHECK_ARG(mergeMode),
		      int pixelDepth
		      ) const
    
{
    ImageFontGlyph ***g;
    unsigned char *img=0;
    const int *res;
    const char *text;
    int pen_x, pen_y, line, xoff, yoff, width=0, overallWidth=0, height=0;
    int overallHeight=0, i, j, k, l, tmpMinY, tmpMaxY, strStart, strEnd, strStep;
    int p, tmpWidth;
    unsigned char *srcPixel, *imageBuffer=0, *row=0, *dstPixel;
    bool retVal;

    if(forcePower2 && (!maxX || !maxY)) return false;

    if(_fontInstance) {
	g = new ImageFontGlyph **[lineVec.size()];
	for(line = 0; line < (int)lineVec.size(); line++) {
	    text = lineVec[line]->c_str();
	    g[line] = new ImageFontGlyph*[strlen(text)];
	    tmpMinY =  INT_MAX;
	    tmpMaxY = -INT_MAX;
	    for(i=0; i< (int)strlen(text); i++) {
		g[line][i] = _fontInstance->getImageGlyph(text[i]);
		if(g[line][i]) {
		    retVal =  g[line][i]->create();
		    if(!retVal) {cout << "whoops" <<endl;exit(false);}
 		    width += g[line][i]->getAdvance();
		    tmpMinY = g[line][i]->getBoundingBox()[2] < tmpMinY ?
			g[line][i]->getBoundingBox()[2] : tmpMinY;
		    tmpMaxY = g[line][i]->getBoundingBox()[3] > tmpMaxY ?
			g[line][i]->getBoundingBox()[3] : tmpMaxY;
		}
	    }
	    if(width > overallWidth) overallWidth = width;

	    if(!tmpMinY && !tmpMaxY) // TXF-character not present -> all blanks..
	      tmpMaxY = (int)rint((float)_fontInstance->getBaselineSkip());
 	    overallHeight += (line+1 == lineVec.size() ?
			      (int)rint((abs(tmpMaxY) + abs(tmpMinY))*_spacing) :
			      (int)rint((float)_fontInstance->getBaselineSkip()*
					(float)_fontInstance->getYRes()*_spacing));
	    width=0;
	}

	if(forcePower2) {
	  height = 1;
	  while(height < overallHeight) height *=2;
	  *maxY = ((float) height) / ((float)overallHeight);
	  overallHeight = height;

	  width = 1;
	  while(width < overallWidth) width *=2;
	  *maxX = ((float)width) / ((float)overallWidth);
	  overallWidth = width;
	}

	imageBuffer = new unsigned char[overallWidth*overallHeight*pixelDepth];
	row = new unsigned char[overallWidth*pixelDepth];

	for(i=0; i<overallWidth*pixelDepth;)
	  for(l=0; l < pixelDepth; l++, i++)
	    row[i] = (*bg)[l];

	for(i=0; i<overallHeight; i++) 
	    memcpy(imageBuffer+i*overallWidth*pixelDepth, 
		   row, overallWidth*pixelDepth);

	delete row;

	tmpMinY =  INT_MAX;
	tmpMaxY = -INT_MAX;

	tmpWidth=0;
	line=0;
	for(i=0; i!=(int)strlen(lineVec[line]->c_str()); i++) {
	  tmpMinY = g[line][i]->getBoundingBox()[2] < tmpMinY ?
	    g[line][i]->getBoundingBox()[2] : tmpMinY;
	  tmpMaxY = g[line][i]->getBoundingBox()[3] > tmpMaxY ?
	    g[line][i]->getBoundingBox()[3] : tmpMaxY;
	  tmpWidth += (g[line][i]->getAdvance());
	}



	height = abs(tmpMaxY) + abs(tmpMinY);
	yoff = _topToBottom ? overallHeight-height : 0;

	switch(_justifyMajor) {
	case FIRST_JT:
	case BEGIN_JT:
	  xoff=0;
	  break;
	case MIDDLE_JT:
	  xoff = (overallWidth-tmpWidth)/2*pixelDepth;
	  break;
	case END_JT:
	  xoff = (overallWidth-tmpWidth)*pixelDepth;
	  break;
	}
// 	xoff-=g[line][0]->getBoundingBox()[0]*pixelDepth;
	tmpWidth = 0;

	for(line = 0; line < (int)lineVec.size(); line++) {
	  text = lineVec[line]->c_str();

	    if(_leftToRight) {
		strStart = 0;
		strEnd = strlen(text);
		strStep = 1;
	    }
	    else {
		strStart = strlen(text)-1;
		strEnd = -1;
		strStep = -1;
	    }

	    for(i=strStart; i!=strEnd; i+=strStep) {
		pen_y=yoff+abs(tmpMinY)+g[line][i]->getBoundingBox()[2];
		pen_x=xoff+(g[line][i]->getBoundingBox()[0]*pixelDepth);
		img = g[line][i]->getImage();
		res = g[line][i]->getImageSize();

		for(j=res[1]-1;j>=0;j--) {
		    srcPixel = img+((res[1]-j-1)*res[2]);

		    dstPixel = imageBuffer +
			((pen_y+j)*overallWidth*pixelDepth)+pen_x;

		    for(k=0;k<res[0];k++, srcPixel++) {
			if(!(p = *(srcPixel))) {
			    dstPixel += pixelDepth;
			    continue;
			}
			for(l=0; l < pixelDepth; l++, dstPixel++)
			  *(dstPixel) = ((*fg)[l]*p + (*bg)[l]*(4-p)) >> 2;
		    }
		}
		xoff += (g[line][i]->getAdvance()*pixelDepth);
	    }

	    if(line+1 < (int)lineVec.size()) {
	      tmpWidth = 0;
	      if(_justifyMajor == MIDDLE_JT || _justifyMajor == END_JT)
		for(i=0; i!=(int)strlen(lineVec[line+1]->c_str()); i++)
		  tmpWidth += (int)rint(g[line+1][i]->getAdvance());

	      switch(_justifyMajor) {
	      case FIRST_JT:
	      case BEGIN_JT:
		xoff=0;
		break;
	      case MIDDLE_JT:
		xoff= (overallWidth-tmpWidth)/2*pixelDepth;
		break;
	      case END_JT:
		xoff=(overallWidth-tmpWidth)*pixelDepth;
		break;
	      }

	      if(line+1 == (int)lineVec.size()-1)
		yoff = _topToBottom ? 0 : overallHeight-height;
	      else 
		yoff += (_topToBottom ? -1 : 1) *
		  (int)rint((float)_fontInstance->getBaselineSkip()*
			    _fontInstance->getYRes()*_spacing);
	    }
	}

	for(line = 0; line < (int)lineVec.size(); line++)
	    delete [] g[line];
	delete []g;

	return (image.set(Image::OSG_RGB_PF, overallWidth, overallHeight, 1, 1, 1, 0.0,
			  imageBuffer, false));
    }

    return false;
}


bool Text::fillGeo ( GeometryPtr mesh,
			     vector<string*> lineVec,
			     float precision,
			     float extFac,
			     float OSG_CHECK_ARG(maxExtend),
			     MeshCreationMode creationMode,
			     MergeMode OSG_CHECK_ARG(mergeMode)
			     ) 
{
    int i, j, line, vertOff=0, faceOff=0, strOff=0, glyphOff=0, diff=0,
	numVertices=0, numFaces=0, numFrontFaces=0, numNormals=0, strStart,
	strEnd, strStep, lastVert=0, lastFace=0, lastNormal=0, normalOff=0,
      glyphNOff=2, reuseNormals, nstride, facestride=2, f_norm=1;
    bool retVal=false;
    float lineOff=0.f, off=0.f, zCoord, bb[4], trX=0.0, trY=0.0, maxWidth=0.0,
	tmpMinY=HUGE_VAL, tmpMaxY=-HUGE_VAL, localWidth, localHeight, descent;
    VectorFontGlyph ***g=0;
    const char *text;


    if(creationMode != FILL_TEX_CHAR_MCM &&
       creationMode != FILL_TEX_ALL_MCM &&
       creationMode != FILL_MCM) return false;


    GeoPositions3fPtr points = GeoPositions3f::create();
    GeoNormals3fPtr normals = GeoNormals3f::create();
    GeoTexCoords2fPtr texCoords;
    if(creationMode == FILL_TEX_CHAR_MCM || creationMode == FILL_TEX_ALL_MCM)
      texCoords = GeoTexCoords2f::create();

    GeoPTypesPtr ftypes = GeoPTypesUI8::create();        
    GeoPLengthsPtr flengths = GeoPLengthsUI32::create();    
    GeoIndicesUI32Ptr faces = GeoIndicesUI32::create();

    beginEditCP(ftypes, GeoPTypesUI8::GeoPropDataFieldMask);
    beginEditCP(flengths, GeoPLengthsUI32::GeoPropDataFieldMask);
    beginEditCP(points, GeoPositions3f::GeoPropDataFieldMask);
    beginEditCP(normals, GeoNormals3f::GeoPropDataFieldMask);
    if(creationMode == FILL_TEX_CHAR_MCM || creationMode == FILL_TEX_ALL_MCM)
      beginEditCP(texCoords, GeoNormals3f::GeoPropDataFieldMask);
    beginEditCP(faces, GeoIndicesUI32::GeoPropDataFieldMask);




    if(_fontInstance) {
	bb[2] = 0;
	bb[3] = 0;
	g = new VectorFontGlyph **[lineVec.size()];

	for(line = 0; line < (int)lineVec.size(); line++) {
	  text = lineVec[line]->c_str();
	    g[line] = new VectorFontGlyph*[strlen(text)];

	    for(i=0; i< (int)strlen(text); i++) {
 		g[line][i] = _fontInstance->getVectorGlyph(text[i]);
		if(g[line][i]) {
		    g[line][i]->setPrecision(precision*2);
		    g[line][i]->setDepth(extFac*g[line][i]->getDepth());
		    retVal =  g[line][i]->create();
		    if(!retVal) exit(false);
		    numVertices += g[line][i]->getNumPoints() *
			(extFac != 0.0 ? 2 : 1);
		    if(extFac != 0.0)
 			numFaces += (g[line][i]->getNumIndices())/3;
		    else
			numFaces += g[line][i]->getNumFrontFaces();
		    numFrontFaces += g[line][i]->getNumFrontFaces();
		    if(extFac != 0.0)
			numNormals += g[line][i]->getNumNormals();
		}
		else return false;
	    }

	    if(_leftToRight) {
		strStart = 0;
		strEnd = strlen(text);
		strStep = 1;
	    }
	    else {
		strStart = strlen(text)-1;
		strEnd = -1;
		strStep = -1;
	    }
	    
	    if(!line)
	      numNormals += 2;

	    if(extFac != 0.0)
		numFrontFaces *=2;

	    if(numNormals) {
		if(extFac != 0.0)
		    normals->resize(lastNormal+numNormals);
		else if(!line)
		    normals->resize(2);

		if(!line) {
		    j=-1;
		    while(!g[line][++j]->getNumPoints());
		    zCoord= g[line][j]->getPoints()[0][2] != 0.0 ? 
		      g[line][j]->getPoints()[0][2] /
		      fabs(g[line][j]->getPoints()[0][2]) : -1;
 
		    if(extFac == 0.0) zCoord *= -1;
		    normals->setValue(Vec3f(0.0,0.0,zCoord), 0);
		    normals->setValue(Vec3f(0.0,0.0,zCoord*-1), 1);
		    normalOff =2;
		}
	    }


	    faces->resize((lastFace+numFaces)*3*facestride);
	    flengths->resize(lastFace+numFaces);
	    ftypes->resize(lastFace+numFaces);
	    
	    points->resize(lastVert+numVertices);

	    if(creationMode == FILL_TEX_CHAR_MCM ||
	       creationMode == FILL_TEX_ALL_MCM)
	      texCoords->resize(lastVert+numVertices);


	    bb[0] = g[line][0]->getBoundingBox()[0];
	    tmpMinY = g[line][0]->getBoundingBox()[2];
	    tmpMaxY = g[line][0]->getBoundingBox()[3];

	    for (strOff=strStart; strOff != strEnd; strOff+=strStep) {
		tmpMinY = g[line][strOff]->getBoundingBox()[2] < tmpMinY ?
		    g[line][strOff]->getBoundingBox()[2] : tmpMinY;
		tmpMaxY = g[line][strOff]->getBoundingBox()[3] > tmpMaxY ?
		    g[line][strOff]->getBoundingBox()[3] : tmpMaxY;

		if(!g[line][strOff]) continue;

		for(i = 0; i < g[line][strOff]->getNumPoints(); i++, vertOff++)
		  points->setValue(Vec3f((g[line][strOff]->getPoints())[i][0]+off,
					 (g[line][strOff]->getPoints())[i][1]+lineOff,
					 (g[line][strOff]->getPoints())[i][2]), vertOff);

		if(extFac != 0.0) {
		  for(i = 0; i < g[line][strOff]->getNumPoints(); i++, vertOff++)
		      points->setValue(Vec3f((g[line][strOff]->getPoints())[i][0]+off,
					     (g[line][strOff]->getPoints())[i][1]+lineOff,
					     (g[line][strOff]->getPoints())[i][2]*-1), vertOff);


		    for(i = 0; i < g[line][strOff]->getNumNormals(); i++, normalOff++)
		      normals->setValue(Vec3f((g[line][strOff]->getNormals())[i][0],
					      (g[line][strOff]->getNormals())[i][1],
					      (g[line][strOff]->getNormals())[i][2]), normalOff);
		}


		for(i = lastFace; i < lastFace+numFaces; i++) {
		    ftypes->setValue(GL_TRIANGLES, i);
		    flengths->setValue(3, i);
		}

		reuseNormals = g[line][strOff]->getNumNormals();
		for(i = 0; i < g[line][strOff]->getNumIndices(); i++, faceOff+=facestride) {

		    faces->setValue((g[line][strOff]->getIndices()[i]+glyphOff), faceOff);

		    if(i >= g[line][strOff]->getNumFrontFaces()*6) {
		      nstride = g[line][strOff]->getNormalIndices()[i];
		      if(nstride >= reuseNormals) 
			nstride -= reuseNormals;
		      faces->setValue(nstride+glyphNOff, faceOff+f_norm);
		    }
		    else {
		      if(i < g[line][strOff]->getNumFrontFaces()*3)
			faces->setValue(0, faceOff+f_norm);
		      else
			faces->setValue(1, faceOff+f_norm);
		    }
		}


		
		if(creationMode == FILL_TEX_CHAR_MCM) {
 		    localWidth = (g[line][strOff]->getAdvance());
		    localHeight = fabs(g[line][strOff]->getBoundingBox()[3]) +
			fabs(g[line][strOff]->getBoundingBox()[2]);
		    descent = fabs(g[line][strOff]->getBoundingBox()[2]);
		    diff = extFac == 0.0 ? vertOff : 
			glyphOff+(vertOff - glyphOff)/2;


		    for(i = glyphOff; i < diff; i++)
			texCoords->setValue(Vec2f((g[line][strOff]->getPoints())[i-glyphOff][0]/ localWidth,
				     ((g[line][strOff]->getPoints())[i-glyphOff][1]+descent)/ localHeight),i);
		    for(i = diff; i < vertOff; i++)
			texCoords->setValue(Vec2f((g[line][strOff]->getPoints())[i-diff][0]/ localWidth,
				     ((g[line][strOff]->getPoints())[i-diff][1]+descent)/ localHeight),i);
			    
		}
		glyphOff = vertOff;
		glyphNOff = normalOff;
		off += (g[line][strOff]->getAdvance());
	    }

	    if(_topToBottom) {
		bb[3] = line ? bb[3] : tmpMaxY;
 		bb[3] = line ? tmpMaxY : bb[3];
		lineOff -= _size*_spacing;
		bb[2] = lineOff;
	    }
	    else {
		bb[2] = line ? tmpMinY : bb[2];;
		lineOff += _size*_spacing;
		bb[3] = lineOff;
	    }

	    off -= (g[line][strOff-strStep]->getAdvance());
	    off += (g[line][strOff-strStep]->getBoundingBox()[1]);
	    bb[1] = off;

	    switch(_justifyMajor) {
	    case FIRST_JT:
	    case BEGIN_JT:
		trX=0.0;
		break;
	    case MIDDLE_JT:
		trX=-(fabs(bb[0])+fabs(bb[1]))/2;
		break;
	    case END_JT:
		trX=-bb[1];
		break;
	    }

	    if(trX != 0.0)
		for(i=0; i<numVertices; i++)
		    points->setValue(points->getValue(lastVert+i) + Vec3f(trX, 0.0, 0.0), lastVert+i);
	    lastVert += numVertices;
	    lastFace += numFaces;
	    numVertices = numFaces = 0;

	    if(numNormals) {
		lastNormal += numNormals;
		numNormals = 0;
	    }
	    maxWidth = off > maxWidth ? off : maxWidth;
	    off=0;
	}

	if(_topToBottom)
	    bb[3] -= (fabs(tmpMaxY) + fabs(tmpMinY))*_spacing;
	else
	    bb[2] += (fabs(tmpMaxY) + fabs(tmpMinY))*_spacing;

	switch(_justifyMinor) {
	case FIRST_JT:
	    trY=0.0;
	    break;
	case BEGIN_JT:
	    trY=-bb[3];
	    break;
	case MIDDLE_JT:
	    trY=-(bb[2]+bb[3])/2;
	    break;
	case END_JT:
	    trY=-bb[2];
	    break;
	}
	
	if(trY != 0.0) {
	    for(i=0; i<(int)points->getSize(); i++)
		    points->setValue(points->getValue(lastVert+i) + Vec3f(0.0, trY, 0.0), i);
	}


	if(creationMode == FILL_TEX_ALL_MCM) {
	    localHeight = fabs(bb[2])+fabs(bb[3]);

	    for(i = 0; i < (int)points->getSize(); i++)
	      texCoords->setValue(Vec2f(points->getValue(i)[0] / maxWidth,
				  fabs(points->getValue(i)[1]-trY) / localHeight),i);
	}


	endEditCP(faces, GeoIndicesUI32::GeoPropDataFieldMask);
	if(creationMode == FILL_TEX_CHAR_MCM || creationMode == FILL_TEX_ALL_MCM)
	  endEditCP(texCoords, GeoNormals3f::GeoPropDataFieldMask);
	endEditCP(normals, GeoNormals3f::GeoPropDataFieldMask);
	endEditCP(points, GeoPositions3f::GeoPropDataFieldMask);
	endEditCP(flengths, GeoPLengthsUI32::GeoPropDataFieldMask);
	endEditCP(ftypes, GeoPTypesUI8::GeoPropDataFieldMask);


	beginEditCP(mesh, Geometry::TypesFieldMask          |
		          Geometry::LengthsFieldMask        |
		          Geometry::IndicesFieldMask        |
		          Geometry::IndexMappingFieldMask   |
		          Geometry::PositionsFieldMask      |
		          Geometry::NormalsFieldMask        |
		          Geometry::MaterialFieldMask       );

        mesh->setPositions(points);
        mesh->setNormals(normals);


        mesh->setTypes(ftypes);
        mesh->setLengths(flengths);
        mesh->setIndices(faces);

	if(creationMode == FILL_TEX_CHAR_MCM ||
	   creationMode == FILL_TEX_ALL_MCM)
	  mesh->getIndexMapping().addValue(Geometry::MapPosition |
					   Geometry::MapTexcoords);
	else
	  mesh->getIndexMapping().addValue(Geometry::MapPosition);

        mesh->getIndexMapping().addValue(Geometry::MapNormal);



	if(creationMode == FILL_TEX_CHAR_MCM ||
	   creationMode == FILL_TEX_ALL_MCM)
	  mesh->setTexCoords(texCoords);

	
	for(line = 0; line < (int)lineVec.size(); line++)
	    delete [] g[line];
	delete []g;


	mesh->setMaterial (getDefaultMaterial());   

	endEditCP (mesh, Geometry::TypesFieldMask          |
		         Geometry::LengthsFieldMask        |
		         Geometry::IndicesFieldMask        |
		         Geometry::IndexMappingFieldMask   |
		         Geometry::PositionsFieldMask      |
		         Geometry::NormalsFieldMask        |
		         Geometry::MaterialFieldMask       );


	return true;
    }
    return false;
}





#endif
