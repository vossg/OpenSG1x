/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/


//-------------------------------
// 	Includes 					 			    
//-------------------------------

#define OSG_COMPILESYSTEMLIB
#define OSG_COMPILEIMAGEINST

#include "OSGConfig.h"

#include <math.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>     

#include <OSGLog.h>

#include "OSGImage.h"
#include "OSGImageFileHandler.h"
#include "OSGSFImageTypes.h"
#include "OSGMFImageTypes.h"


/*
#include "OSGSFImageTypes.h"
#include "OSGMFImageTypes.h"
*/

OSG_USING_NAMESPACE

Int32 Image::_formatMap[][2] = {
	{ OSG_L_PF, 1 },
	{ OSG_LA_PF, 2 },
	{ OSG_RGB_PF, 3 },
	{ OSG_RGBA_PF, 4 },
};


/* enum VecBase::VectorSizeE
 * brief 
*/


/* var VecBase::VectorSizeE VecBase::_iSize
 *
*/


/* const Char8 *VecBase::getClassName(void)
 *  brief Classname
*/


/* var ValueTypeT VecBase:: _value[Size];
 * brief value store
*/


/*****************************
 *   Types
 *****************************/


/*****************************
 *	  Classvariables
 *****************************/


/********************************
 *	  Class methodes
 *******************************/


/*******************************
*public
*******************************/


//----------------------------
// Function name: set
//----------------------------
//
//Parameters:
//p: PixelFormat pixelFormat, Int32 width, Int32 height, Int32 depth, Int32 mipmapCount, Int32 frameCount, Time frameDelay, UChar8 *data
//GlobalVars:
//g: 
//Returns:
//r:bool
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: set methode wich sets the image data
//SeeAlso:
//s:
//
//------------------------------
Bool Image::set ( PixelFormat pF,
									Int32 w, Int32 h, Int32 d, 
									Int32 mmS, Int32 fS,
									Time fD,
									UChar8 *da)
{
	_pixelFormat = pF;

	_width = w;
	_height = h;
	_depth = d;

	_mipmapCount = mmS;

	_frameCount = fS;
	_frameDelay = fD;

	return createData(da);
}

//----------------------------
// Function name: reformat
//----------------------------
//
//Parameters:
//p: const Char8 *pixelFormat, Image *destination = 0
//GlobalVars:
//g: 
//Returns:
//r:bool
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: reformate the image to the given pixelFormat
//SeeAlso:
//s:
//
//------------------------------
Bool Image::reformat (const PixelFormat pF, Image *destination )
{
		/*
	UChar8 *data;
	int srcI, destI, DestSize;
	Bool valid = false;
	int sum;

	cout << "INFO: Try to reformat image from pixelDepth " 
			 << int(_pixelDepth) << " to " << int(pixelDepth) << " ... ";
	cout.flush();

	// TODO !!! code all the cases !!!
	if ( size() && pixelDepth && (pixelDepth != _pixelDepth) ) {
		DestSize = pixelDepth * _width * _height * _depth;
		data = new UChar8[DestSize];
		if (data) 
			switch (_pixelDepth) {
			case 1: // source pixelDepth == 1
				switch (pixelDepth) {
				case 1:
					break;
				case 2:
					for (srcI = destI = 0; destI < DestSize; ) {
						data[destI++] = _data[srcI];
						data[destI++] = _data[srcI++];
					}
					valid = true;
					break;
				case 3:
					for (srcI = destI = 0; destI < DestSize; ) {
						data[destI++] = _data[srcI];
						data[destI++] = _data[srcI];
						data[destI++] = _data[srcI++];
					}
					break;
				case 4:
					for (srcI = destI = 0; destI < DestSize; ) {
						data[destI++] = _data[srcI];
						data[destI++] = _data[srcI];
						data[destI++] = _data[srcI];
						data[destI++] = _data[srcI++];
					}
					break;
				}
				break;
			case 2: // source pixelDepth == 2
				switch (pixelDepth) {
				case 1:
					for (srcI = destI = 0; destI < DestSize; ) {
						data[destI++] = _data[srcI++];
						srcI++;
					}
					break;
				case 2:
					break;
				case 3:
					for (srcI = destI = 0; destI < DestSize; ) {
						data[destI++] = _data[srcI];
						data[destI++] = _data[srcI];
						data[destI++] = _data[srcI++];
						srcI++;
					}
					break;
				case 4:
					for (srcI = destI = 0; destI < DestSize; ) {
						data[destI++] = _data[srcI];
						data[destI++] = _data[srcI];
						data[destI++] = _data[srcI++];
						data[destI++] = _data[srcI++];
					}
					break;
				}
				break;
			case 3: // source pixelDepth == 3
				switch (pixelDepth) {
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					for (srcI = destI = 0; destI < DestSize; ) {
						sum = 0;
						sum += data[destI++] = _data[srcI++];
						sum += data[destI++] = _data[srcI++];
						sum += data[destI++] = _data[srcI++];
						data[destI++] = sum / 3;
					}
					valid = true;
					break;
				}
				break;
			case 4: // source pixelDepth == 4
				switch (pixelDepth) {
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				}
				break;
			default:
			  SWARNING << "Unvalid pixeldepth (" << pixelDepth
				         << " ) in Image::reformat() !\n" << endl;
			}
		if (valid) {
			delete [] _data;
			_data = data;
			_pixelDepth = pixelDepth;
		}
	}
	cout << (valid ? " done" : " failed") << endl;

	return valid;

	*/

	return false;

}

//----------------------------
// Function name: clear
//----------------------------
//
//Parameters:
//p: UChar8 pixelValue
//GlobalVars:
//g: 
//Returns:
//r:void
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: method to load the image data from the given file
//SeeAlso:
//s:
//----------------------------------------------------------------------
void Image::clear(UChar8 pixelValue)
{
	unsigned long n = getSize();
	UChar8 *d = _data;

	if (n && d) 
		while (n--) 
			*d++ = pixelValue;
}

//----------------------------
// Function name: scale
//----------------------------
//
//Parameters:
//p: int width, int height, int depth =1, Image *destination = 0
//GlobalVars:
//g: 
//Returns:
//r:bool
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: scale the image to the given dimension
//SeeAlso:
//s:
//
//------------------------------
Bool Image::scale ( int width, int height, int depth, Image *destination )
{
	Image *destImage = destination ? destination : new Image;
	Bool retCode = true;
	Int32 sw,sh,sd,dw,dh,dd;
	Int32 frame, mipmap;
	UChar8 *src, *dest;
  
	if (width != _width || height != _height || depth != _depth) {

		// set image data
		destImage->set ( _pixelFormat, width, height, depth,
										 _mipmapCount, _frameCount, _frameDelay, 0 );
		
		// copy every mipmap in every frame
		for (frame = 0; frame < _frameCount; frame++) {
			for (mipmap = 0; mipmap < _mipmapCount; mipmap++) {

				// get the memory pointer
				src  = this->getData(mipmap,frame);
				dest = destImage->getData(mipmap,frame);

				// calc the mipmap size
				this->calcMipmapGeometry(mipmap,sw,sh,sd);
				destImage->calcMipmapGeometry(mipmap,dw,dh,dd);

				// copy and scale the data
				scaleData (src,sw,sh,sd,dest,dw,dh,dd);
			}
		}
	}
	else { // same size; just copy the data necessary
		if (destination)
			*destination = *this;
	}

	// rip the data from the local destImage if necessary
	if (!destination) {
		delete [] _data;
		_data = destImage->_data;
		destImage->_data = 0;
		delete destImage;
	}

	return retCode;
}

//----------------------------
// Function name: scale
//----------------------------
//
//Parameters:
//p: int width, int height, int depth =1, Image *destination = 0
//GlobalVars:
//g: 
//Returns:
//r:bool
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: scale the image to the given dimension
//SeeAlso:
//s:
//
//------------------------------
Bool Image::createMipmap ( Int32 level, Image *destination)
{
	struct Offset { 
		Int32 w;
		Int32 h;
		Int32 d;
	};
	Offset offset[][8] = { 
		{ // 000
			{ 0,0,0 }, { 0,0,0 }, { 0,0,0 }, { 0,0,0 },
			{ 0,0,0 }, { 0,0,0 }, { 0,0,0 }, { 0,0,0 }
		},
		{ // 100
			{ 0,0,0 }, { 1,0,0 }, { 0,0,0 }, { 0,0,0 },
			{ 0,0,0 }, { 0,0,0 }, { 0,0,0 }, { 0,0,0 }
		},
		{ // 010
			{ 0,0,0 }, { 0,1,0 }, { 0,0,0 }, { 0,0,0 },
			{ 0,0,0 }, { 0,0,0 }, { 0,0,0 }, { 0,0,0 }
		},
		{ // 110
			{ 0,0,0 }, { 0,1,0 }, { 1,0,0 }, { 1,1,0 },
			{ 0,0,0 }, { 0,0,0 }, { 0,0,0 }, { 0,0,0 }
		},
		{ // 001
			{ 0,0,0 }, { 0,0,1 }, { 0,0,0 }, { 0,0,0 },
			{ 0,0,0 }, { 0,0,0 }, { 0,0,0 }, { 0,0,0 }
		},
		{ // 101
			{ 0,0,0 }, { 1,0,0 }, { 0,0,1 }, { 1,0,1 },
			{ 0,0,0 }, { 0,0,0 }, { 0,0,0 }, { 0,0,0 }
		},
		{ // 110
			{ 0,0,0 }, { 1,0,0 }, { 0,1,0 }, { 0,1,1 },
			{ 0,0,0 }, { 0,0,0 }, { 0,0,0 }, { 0,0,0 }
		},
		{ // 111
			{ 0,0,0 }, { 1,0,0 }, { 0,1,0 }, { 1,1,0 },
			{ 0,0,1 }, { 1,0,1 }, { 0,1,1 }, { 1,1,1 }
		}
	};
	Int32 offsetSize[] = { 0,2,2,4,2,4,4,8 };
	Image  *destImage = destination ? destination : new Image;
	Int32  w = _width, h = _height, d = _depth;
	Int32  wm, hm, dm, wi, hi, di;
	UChar8 *src,*dest;
    /* ,*pixel; */
	Int32  value, i, elem, dim, frame, size, mipmap;
	Int32  channel, lineSize, sliceSize;
	
	// calc the level count
	if (level < 0) {
		for (level = 0; true; level++) {
			if ((w == 1) && (h == 1) && (d == 1))
				break;
			else {
				w = (w >>= 1) ? w : 1;
				h = (h >>= 1) ? h : 1;
				d = (d >>= 1) ? d : 1;
			}
		}
	}

	// create destination image
	destImage->set( _pixelFormat, _width, _height, _depth,
									level, _frameCount, _frameDelay, 0 );

	// copy the data;
	for (frame = 0; frame < _frameCount; frame++) {
		src = this->getData(0,frame);
		dest = destImage->getData(0,frame);
		size = _width * _height * _depth * _bpp;
		memcpy ( src, dest, size);
		src = dest;
		dest = src + size;
		w = _width;
		h = _height;
		d = _depth;
		for (mipmap = 1; mipmap < level; mipmap++) {
			dim = (d>dm)*1 + (h>hm)*2 + (w>wm)*4;
			elem = offsetSize[dim];
			lineSize = w * _bpp;
			sliceSize = w * h * _bpp;
			wm = (w == 1) ? w : (w >> 1);
			hm = (h == 1) ? h : (h >> 1);
			dm = (d == 1) ? d : (d >> 1);			
		  for (di = 0; di < dm; di++) {
				for (hi = 0; hi < hm; hi++) {
					for (wi = 0; wi < wm; wm++) {
						for (channel = _bpp; channel < _bpp; channel++) {
							value = 0;
							for (i = 0; i < elem; i++) {
								value += src[ ((wi*2)+offset[dim][i].w)*_bpp +
														  ((hi*2)+offset[dim][i].h)*lineSize +
														  ((di*2)+offset[dim][i].d)*sliceSize +
														  channel 
														];
							}
							*dest++ = value / elem;
						}
						
					}
				}
			}
			src += sliceSize;
			w = wm;
			h = hm;
			d = dm;
		}
	}

	// rip the data from the local destImage if necessary
	if (!destination) {
		delete [] _data;
		_data = destImage->_data;
		destImage->_data = 0;
		delete destImage;
	}
	
	return true;
}

//----------------------------
// Function name: write
//----------------------------
//
//Parameters:
//p: const Char8 *fileName
//GlobalVars:
//g: 
//Returns:
//r:bool
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: methode to write the image data to the given File
//SeeAlso:
//s:
//
//------------------------------
Bool Image::write (const Char8 *fileName )
{
  return ImageFileHandler::the().write(*this, fileName);
}

//----------------------------
// Function name: read
//----------------------------
//
//Parameters:
//p: const Char8 *fileName
//GlobalVars:
//g: 
//Returns:
//r:bool
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: methode to read the image data from the given File
//SeeAlso:
//s:
//
//------------------------------
Bool Image::read (const Char8 *fileName )
{
	return ImageFileHandler::the().read(*this, fileName);
}
/******************************
*protected
******************************/


/******************************
*private	
******************************/

//----------------------------
// Function name: createData
//----------------------------
//
//Parameters:
//p: const UChar88 *data
//GlobalVars:
//g: 
//Returns:
//r:bool
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: internal method to alloc and copy the image data
//SeeAlso:
//s:
//
//------------------------------
Bool Image::createData (const UChar8 *data )
{
	Int32 i, byteCount = 0, mapSize = sizeof(_formatMap)/sizeof(UInt32[2]);

	// set bbp
	for (i = 0; i < mapSize; i++)
		if (_formatMap[i][0] == _pixelFormat)
			_bpp = _formatMap[i][1];

	// set dimension
	_dimension = 0;
	if (_depth == 1)
		if (_height == 1)
			_dimension = 1;
		else
			_dimension = 2;
	else
		_dimension = 3;

	// set frameSize
	_frameSize = calcMipmapSumSize(_mipmapCount);  

	// delete old data
	if (_data)
		delete [] _data;

	// copy new data
	if ((byteCount = getSize())) {
		_data = new UChar8[byteCount];
		if (_data) {
			if (data)
				memcpy(_data, data, byteCount);
		}
		else
			SWARNING << "Couldn't alloc image data in Image::createData()!\n";
	}
	else
		_data = 0;
		
	return _data;
}

//----------------------------
// Function name: createData
//----------------------------
//
//Parameters:
//p: UChar8* srcData, Int32 srcW, Int32 srcH, Int32 srcD, UChar8* destData, Int32 destW, Int32 destH, Int32 destD
//GlobalVars:
//g: 
//Returns:
//r:bool
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: Internal medhot to copy&scale image data 
//SeeAlso:
//s:
//
//------------------------------
Bool Image::scaleData ( UChar8* srcData, 
												Int32 srcW, Int32 srcH, Int32 srcD,
												UChar8* destData, 
												Int32 destW, Int32 destH, Int32 destD)
{
	Real32 sx = Real32(srcW) / Real32(destW);
	Real32 sy = Real32(srcH) / Real32(destH);
	Real32 sz = Real32(srcD) / Real32(destD);
	Int32 srcSize = srcW * srcH * srcD;
//	Int32 destDize = destW * destH * destD;
	Int32 x,y,z,p;
	UChar8 *slice,*line,*pixel;

	if (destW == srcW && destH == srcH && destD == srcD) {
		// same size, just copy
		memcpy(destData,srcData,srcSize);
	}
	else		
		// different size, to 'nearest' copy
		for ( z = 0; z < destD; z++) {
			slice = srcData + int(sz * z + 0.5) * _bpp * srcW * srcH;
			for ( y = 0; y < destH; y++) {
				line = slice + int (sy * y + 0.5) * _bpp * srcW;
				for ( x = 0; x < destW; x++) {
					pixel = line + int(sx * x + 0.5) * _bpp;
					p = _bpp;
					while (p--)
						*destData++ = *pixel++;
				}
			}
		}

	return true;
}

/***************************
*instance methodes 
***************************/


/***************************
*public
***************************/


/**constructors & destructors**/


//----------------------------
// Function name: Image
//----------------------------
//
//Parameters:
//p: void
//GlobalVars:
//g: 
//Returns:
//r:
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: Default Constructor
//SeeAlso:
//s:
//
//------------------------------
Image::Image (void )
: _pixelFormat(OSG_INVALID_PF), 
	_width(0), _height(0), _depth(0), _mipmapCount(0), 
	_frameCount(0), _frameDelay(0),
	_bpp(0),_dimension(0),
	_data(0)
{
	return;
}

//----------------------------
// Function name: Image
//----------------------------
//
//Parameters:
//p: const wrw &obj
//GlobalVars:
//g: 
//Returns:
//r:
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: Copy Constructor
//SeeAlso:
//s:
//
//------------------------------
Image::Image (const Image &obj, Bool copyData )
: _pixelFormat(obj._pixelFormat),
	_width(obj._width), _height(obj._height), _depth(obj._depth),
	_mipmapCount(obj._mipmapCount), 
	_frameCount(obj._frameCount), _frameDelay(obj._frameDelay),
	_bpp(0), _dimension(0),
	_data(0)
{
	createData ( copyData ? obj._data : 0 );
}

//----------------------------
// Function name: ~Image
//----------------------------
//
//Parameters:
//p: void
//GlobalVars:
//g: 
//Returns:
//r:
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: Destructor
//SeeAlso:
//s:
//
//------------------------------
Image::~Image (void )
{
	if (_data) {
		delete [] _data;
		_data = 0;
	}	
}

//----------------------------
// Function name: Image
//----------------------------
//
//Parameters:
//p: int width, int height, int depth, const Char8 *pixelFormat, UChar8 *data = 0
//GlobalVars:
//g: 
//Returns:
//r:
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: construktor
//SeeAlso:
//s:
//
//------------------------------
Image::Image ( PixelFormat pixelFormat, 
							 Int32 width, Int32 height, Int32 depth, 
							 Int32 mipmapCount, Int32 frameCount, Time frameDelay,
							 UChar8 *data)
	: _pixelFormat(pixelFormat),
		_width(width), _height(height), _depth(depth),
		_mipmapCount(mipmapCount), 
		_frameCount(frameCount), _frameDelay(frameDelay),
		_bpp(0), _dimension(0),
		_data(0)
{
	createData(data);
}

/*------------access----------------*/

/*------------properies-------------*/

/*------------your Category---------*/

/*------------Operators-------------*/


//----------------------------
// Function name: operator ==
//----------------------------
//
//Parameters:
//p: const Image &image
//GlobalVars:
//g: 
//Returns:
//r:bool
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: equal comparison operator
//SeeAlso:
//s:
//
//------------------------------
Bool Image::operator == (const Image &image )
{
 unsigned long i, s = getSize();

  if ((_width == image._width) &&
      (_height == image._height) &&
      (_depth == image._depth) &&
			(_mipmapCount == image._mipmapCount) &&
			(_frameCount == image._frameCount) &&
			(_frameDelay == image._frameDelay) &&
      (_pixelFormat == image._pixelFormat)) {
    for (i = 0; i < s; ++i)
      if (image._data[i] != _data[i])
        return false;
    return true;
  }
  return false;
}
//----------------------------
// Function name: operator <
//----------------------------
//
//Parameters:
//p: const Image &image
//GlobalVars:
//g: 
//Returns:
//r:bool
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: lower comparison operator
//SeeAlso:
//s:
//
//------------------------------
Bool Image::operator < (const Image &image )
{
	return (getSize() < image.getSize()) ? true : false;
}


/****************************
*protected	
****************************/


/****************************
*private
****************************/

#if defined(__sgi)

#pragma instantiate SField<ImageP>::_fieldType
#pragma instantiate MField<ImageP>::_fieldType

#pragma instantiate SField<Plane>::_fieldType
#pragma instantiate MField<Plane>::_fieldType

#else

OSG_DLLEXPORT_DEF1(SField, ImageP,	OSG_SYSTEMLIB_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, ImageP,	OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
