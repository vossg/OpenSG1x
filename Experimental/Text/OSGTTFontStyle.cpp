#ifndef WIN32

// System declarations

#ifdef OSG_WITH_FREETYPE1

#ifdef __sgi
# include <math.h>
#else
# include <cmath>
#endif
#include <iostream>

#include <stdio.h>

// Application declarations
#include "OSGTTVectorFontGlyph.h"
#include "OSGTTImageFontGlyph.h"
#include "OSGTXFGlyphInfo.h"

// Class declarations
#include "OSGTTFontStyle.h"



OSG_USING_NAMESPACE



// Static Class Variable implementations: 


TTFontStyle::TTFontStyle (void )
: FontStyle (), _ttInstance(0)
{
	return;
}

TTFontStyle::TTFontStyle (const TTFontStyle &OSG_CHECK_ARG(obj) )
: _ttInstance(0)
{
	assert(false);
}

TTFontStyle::~TTFontStyle (void )
{
	return;
}

VectorFontGlyph * TTFontStyle::getVectorGlyph (int ascii)
{
    return _vectorGlyphs[ascii];
}

ImageFontGlyph * TTFontStyle::getImageGlyph (int ascii)
{
    return _imageGlyphs[ascii];
}

bool TTFontStyle::processChange (void)
{
	return 0;
}

bool TTFontStyle::set_ttInstance (TT_Instance *ttInstance,
					TT_Face *ttFace)
{

    TT_UShort ttPlatformID=0, ttEncodingID=0;
    TT_CharMap ttCharMap;
    TT_Face_Properties  ttFaceProps;
    TT_Instance_Metrics ttInstMetrics;
    int i;
    float scaling;

    _ttError = TT_New_Instance(*ttFace, ttInstance);
    
    if(_ttError){
	cout << "ERROR: Create TT_New_Instance failed with TT_Error=" 
	     << _ttError << endl;
	return false;
    }

    _ttError= TT_Set_Instance_Resolutions(*ttInstance, getXRes(), getYRes());
    if(_ttError){
	cout << "ERROR: Create TT_Set_Instance_Resolutions failed "
	     << "with TT_Error=" << _ttError << endl;
	return false;
    }

    _ttError= TT_Set_Instance_PointSize( *ttInstance, (int)rint(64*getSize()));
    if(_ttError){
	cout << "ERROR: Create TT_Set_Instance_PointSize failed"
	     << " with TT_Error=" << _ttError << endl;
	return false;
    }


    TT_Get_Face_Properties(*ttFace, &ttFaceProps);

    TT_Get_Instance_Metrics(* ttInstance, &ttInstMetrics );

    setMaxAscent((ttFaceProps.os2->sTypoAscender *
		  (((float)ttInstMetrics.y_scale)/65536)) / 4096);

    setMaxDescent((ttFaceProps.os2->sTypoDescender *
		   (((float)ttInstMetrics.y_scale)/65536)) / 4096);

//     setBaselineSkip(getMaxAscent() - getMaxDescent() + 
// 		    (float)ttFaceProps.os2->sTypoLineGap/4096);

//     scaling = getBaselineSkip()*getYRes();

    setBaselineSkip(getSize());

    scaling = getBaselineSkip();


    for(i= 0; i < ttFaceProps.num_CharMaps; i++) {
	TT_Get_CharMap_ID(*ttFace, i, &ttPlatformID, &ttEncodingID);
	if((ttPlatformID == 3 && ttEncodingID == 1) ||
	   (!ttPlatformID && !ttEncodingID)) {
	    TT_Get_CharMap(*ttFace, i, &ttCharMap);
	    break;
	}
    }

    if(i==ttFaceProps.num_CharMaps){
	cout << "ERROR: Font does not contain a unicode-character-map" 
	     << endl;
	return false;
    }

    TTVectorFontGlyph *vGlyphs = new TTVectorFontGlyph[256];
    TTImageFontGlyph *iGlyphs = new TTImageFontGlyph[256];
    for(int i= 0; i < 256; i++) {
	vGlyphs[i].setup(VGLYPH_FACE, i, TT_Char_Index(ttCharMap, i));
	vGlyphs[i].setFontDefs(ttFace, ttInstance);
	vGlyphs[i].setDepth(getSize());
	vGlyphs[i].setSize(getSize());
	vGlyphs[i].setScaleFactor(scaling);
	_vectorGlyphs.push_back(&vGlyphs[i]);

	iGlyphs[i].setup(IGLYPH_PIXMAP, i, TT_Char_Index(ttCharMap, i));
	iGlyphs[i].setFontDefs(ttFace, ttInstance);
	iGlyphs[i].setSize(getSize());
	_imageGlyphs.push_back(&iGlyphs[i]);
    }

    _ttInstance = ttInstance;
    _ttFace = ttFace;

    return true;
}


// txf-stuff


// compare glyph height

int cmpIGlyphs(void *g1, void *g2)
{
  return (((ImageFontGlyph *)g2)->getImageSize()[1] -
	  ((ImageFontGlyph *)g1)->getImageSize()[1]);
}


void qsortIGlyphs(int numGlyphs, unsigned char *indices,
		  vector<ImageFontGlyph *> iGlyphs)
{
  unsigned char split, *upper, *lower, up=1;

  if(numGlyphs <= 1) return;
   
  lower = indices;
  upper = lower+numGlyphs - 1;
  split = *upper;
   
  while(lower != upper) {
    if(up) {
      if(cmpIGlyphs(iGlyphs[*lower], iGlyphs[split]) > 0) {
	*upper = *lower; up=0;
      }
    }
    else {
      if(cmpIGlyphs(iGlyphs[*upper], iGlyphs[split]) < 0) {
	*lower = *upper; up=1;
      }
    }
    if(up)lower++; else upper--;
  }
  *upper++=split;

  qsortIGlyphs(lower-indices, indices, iGlyphs);
  qsortIGlyphs(indices+numGlyphs-upper, upper, iGlyphs);
}



bool TTFontStyle::createTXFMap(char *characters, int gap)
{
  int i, j, k numChars, numCreated=0, width, height, x, y;
  int start, current, rowHeight, spaceLeft, numSorted;
  const int *res, *bb;
  unsigned char *createdIndices=NULL, *sortedIndices=NULL, *imageBuffer=NULL;
  unsigned char *img, *srcPixel, *dstPixel;
  TXFGlyphInfo *glyph=NULL;
  float x_f, y_f, xstep, ystep, scale;
  bool retVal;
  char *dims;

  if(characters) {
    numChars = strlen(characters);
    start = 0;
  }
  else {
    numChars = 256;
    start = 1;
  }

  createdIndices = new unsigned char[numChars];
    
  for(i=start; i<numChars; i++) {
    retVal = _imageGlyphs[characters ? characters[i] : i]->create();
    if(retVal) {
      createdIndices[numCreated++]=
	(unsigned char)(characters ? characters[i] : i);
    }
  }

  qsortIGlyphs(numCreated, createdIndices,  _imageGlyphs);


  for(i=0; i<256; i++) {
    glyph = new TXFGlyphInfo;
    glyph->remap('?');
    _txfGlyphInfos.push_back(glyph);
  }

  width = 512;
  i=0; x=gap; y=gap;

  sortedIndices = new unsigned char[numCreated];
  numSorted = 0;
  while (true) {
    current = createdIndices[i];
    if(!current) {
      if(++i >= numCreated) break;
      continue;
    }

    res = _imageGlyphs[current]->getImageSize();

    if(res[0] && res[1] ||  current == ' ') {
      if(res[0]+x >= width) {
	spaceLeft = width -x;
	for (j=i+1;j<numCreated;j++) {
	  if(createdIndices[j] &&
	     _imageGlyphs[createdIndices[j]]->getImageSize()[0] < spaceLeft) {
	    current = createdIndices[j];
	    createdIndices[j] = 0;
	    res = _imageGlyphs[current]->getImageSize();
	    i--;
	    break;
	  }
	}
	if(current ==  createdIndices[i]) x = gap;
      }
    
      if(x==gap) {
	if(i) y += rowHeight + gap;
	rowHeight = res[1];
      }

      sortedIndices[numSorted++] = current;

      x += res[0]+gap;
    }
    if(current == createdIndices[i])
      createdIndices[i] = 0;
    if(++i >= numCreated) break;
  }

  height = 1;
  while(height < y+rowHeight+gap) height *=2;
  imageBuffer= new unsigned char [width*height*2];

  i=0; x=gap; y=gap;
  xstep = 0.5 / width;
  ystep = 0.5 / height;
  scale = (float)getMaxAscent() - (float)getMaxDescent();

  for(i=0;i<numSorted;i++) {
    current = sortedIndices[i];

    res = _imageGlyphs[current]->getImageSize();

    if(res[0]+x >= width) x = gap;

    if(x==gap) {
      if(i) y += rowHeight + gap;
      rowHeight = res[1];
    }

    // copy image
    img = _imageGlyphs[current]->getImage();
    for(j=res[1]-1;j>=0;j--) {
      srcPixel = img+((res[1]-j-1)*res[2]);
      dstPixel = imageBuffer + ((y+j)*width+x)*2;

      for(k=0;k<res[0];k++, srcPixel++, dstPixel+=2) {
	if(!(*srcPixel)) continue;
	*dstPixel =  *(dstPixel+1) = (255*(*srcPixel)) >> 2;
      }
    }

    glyph=_txfGlyphInfos[current];
    glyph->remap(0);

    dims = new char[2];
    dims[0] = (char) x;
    dims[1] = (char) y;
    glyph->setDimensions(dims);

    x_f  = ((float)(x))/width+xstep;
    y_f  = ((float)(y))/height+ystep;
    glyph->setTextureCoords(0, x_f, y_f);

    x_f += ((float)(res[0]))/width;
    glyph->setTextureCoords(1, x_f, y_f);

    y_f += ((float)(res[1]))/height;
    glyph->setTextureCoords(2, x_f, y_f);

    x_f  = ((float)(x))/width+xstep;
    glyph->setTextureCoords(3, x_f, y_f);

    bb = _imageGlyphs[current]->getBoundingBox();

    x_f = (float)bb[0]/scale;
    y_f = (float)bb[2]/scale;
    glyph->setVertexCoords(0, x_f, y_f);

    x_f = (float)bb[1]/scale;
    glyph->setVertexCoords(1, x_f, y_f);

    y_f = (float)bb[3]/scale;
    glyph->setVertexCoords(2, x_f, y_f);

    x_f = (float)bb[0]/scale;
    glyph->setVertexCoords(3, x_f, y_f);

    glyph->setAdvance((float) _imageGlyphs[current]->getAdvance()/scale);

    x += res[0]+gap;
  }

  _txfImageMap = imageBuffer;
  _txfFontWidth = width;
  _txfFontHeight = height;

  delete createdIndices;
  delete sortedIndices;

  return retVal;
}



unsigned char *TTFontStyle::getTXFImageMap (void)
{
  if(!_txfImageMap) createTXFMap();

  return _txfImageMap;
}


TXFGlyphInfo *TTFontStyle::getTXFGlyphInfo (int which)
{
  if(!_txfImageMap) createTXFMap();

  if(which >= _txfGlyphInfos.size())
    return _txfGlyphInfos[_txfGlyphInfos[0]->remapped()];

  if(_txfGlyphInfos[which]->remapped()) 
    return _txfGlyphInfos[_txfGlyphInfos[which]->remapped()];

  return _txfGlyphInfos[which];
}


bool TTFontStyle::dump(ostream & out)
{
  const int *bb;
  unsigned int swapit = 0x12345678;
  unsigned int zero = 0, buffer, nc=0;
  unsigned short sbuffer;
  unsigned char *oBuffer;

  out << (char)0xff << "txf";
  out.write(reinterpret_cast<char*>(&swapit),4);
  out.write(reinterpret_cast<char*>(&zero), 4);
  out.write(reinterpret_cast<char*>(&_txfFontWidth), 4);
  out.write(reinterpret_cast<char*>(&_txfFontHeight), 4);
  buffer = (int)rint(getMaxAscent()*72);
  out.write(reinterpret_cast<char*>(&buffer), 4);
  buffer = (int)rint(getMaxDescent()*72);
  out.write(reinterpret_cast<char*>(&buffer), 4);

  for(short i=0; i < _txfGlyphInfos.size(); i++)
    if(!(_txfGlyphInfos[i]->remapped())) nc++;

  out.write(reinterpret_cast<char*>(&nc), 4);


  for(short i=0; i < _txfGlyphInfos.size(); i++)
    if(!(_txfGlyphInfos[i]->remapped())) {
      bb = _imageGlyphs[i]->getBoundingBox();
      out.write(reinterpret_cast<char*>(&i), 2);
      out << (char) (bb[1] - bb[0]);
      out << (char) (bb[3] - bb[2]);
      out << (char) bb[0] << (char) bb[2];
      out << (char) _imageGlyphs[i]->getAdvance();
      out << (char) 0;
      sbuffer = (short) _txfGlyphInfos[i]->getDimensions()[0];
      out.write(reinterpret_cast<char*>(&sbuffer), 2);
      sbuffer = (short) _txfGlyphInfos[i]->getDimensions()[1];
      out.write(reinterpret_cast<char*>(&sbuffer), 2);
    }

  oBuffer = new unsigned char [_txfFontWidth*_txfFontHeight];
  for (int j=0; j< _txfFontWidth*_txfFontHeight; j++)
    oBuffer[j] = _txfImageMap[2*j];
  out.write(reinterpret_cast<char*>(oBuffer), _txfFontWidth*_txfFontHeight);

  delete oBuffer;

  return true;
}

#endif // OSG_WITH_FREETYPE1
#endif
