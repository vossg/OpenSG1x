/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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

#include "OSGConfig.h"

#include <math.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>     

#include <OSGLog.h>

#define OSG_COMPILEIMAGE
#define OSG_COMPILEIMAGEINST

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif


#include "OSGImage.h"
#include "OSGImageFileHandler.h"

/*
#include "OSGSFImageTypes.h"
#include "OSGMFImageTypes.h"
*/

OSG_USING_NAMESPACE


#if defined(__sgi)

#pragma instantiate SField<Image*>::_fieldType
#pragma instantiate MField<Image*>::_fieldType

#else

/* jbehr; shouldn't this be done outside of OSGImage ?!?
OSG_DLLEXPORT_DEF1(SField, Image*, OSG_IMAGE_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, Image*, OSG_IMAGE_DLLTMPLMAPPING)
*/

#endif

UInt32 Image::_formatMap[][2] = {
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
//p: PixelFormat pixelFormat, Int32 width, Int32 height, Int32 depth, Int32 mipmapSize, Int32 frameSize, Time frameDelay, UChar8 *data
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

	_mipmapSize = mmS;

	_frameSize = fS;
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
	unsigned long n = size();
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
Bool Image::scale (int width, int height, int depth, Image *destination )
{
	Bool retCode = true;
	UChar8 *data, *dest, *slice, *line, *pixel;
	float sx, sy, sz, p;
	int x,y,z;
  
	if (width != _width || height != _height || depth != _depth) {
		sx = float(_width) / float(width);
		sy = float(_height) / float(height);
		sz = float(_depth) / float(depth);
		if (destination) {
			destination->set(_pixelFormat,width,height,depth);
			dest = data = destination->data();
		}
		else
			dest = data = new UChar8[width * height * depth * _bpp];

		if (data) {			
			for ( z = 0; z < depth; z++) {
				slice = _data + int(sz * z + 0.5) * _bpp * _width * _height;
				for ( y = 0; y < height; y++) {
					line = slice + int (sy * y + 0.5) * _bpp * _width;
					for ( x = 0; x < width; x++) {
						pixel = line + int(sx * x + 0.5) * _bpp;
						p = _bpp;
						while (p--)
							*dest++ = *pixel++;
					}
				}
			}
			if (!destination) {
				delete [] _data;
				_data = data;
				_width = width;
				_height = height;
				_depth = depth;
			}
			retCode = true;
		}
	}
	else { // same size; just copy the data
		if (destination)
			*destination = *this;
	}

	return retCode;
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
	for (i = 0; i < mapSize; mapSize++)
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

	// delete old data
	if (_data)
		delete [] _data;

	// copy new data
	if ((byteCount = size())) {
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
	_width(0), _height(0), _depth(0), _mipmapSize(0), 
	_frameSize(0), _frameDelay(0),
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
Image::Image (const Image &obj, Bool copy )
: _pixelFormat(obj._pixelFormat),
	_width(obj._width), _height(obj._height), _depth(obj._depth),
	_mipmapSize(obj._mipmapSize), 
	_frameSize(obj._frameSize), _frameDelay(obj._frameDelay),
	_bpp(0), _dimension(0),
	_data(0)
{
	createData ( copy ? obj._data : 0 );
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
							 Int32 mipmapSize, Int32 frameSize, Time frameDelay,
							 UChar8 *data)
	: _pixelFormat(pixelFormat),
		_width(width), _height(height), _depth(depth),
		_mipmapSize(mipmapSize), 
		_frameSize(frameSize), _frameDelay(frameDelay),
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
 unsigned long i, s = size();

  if ((_width == image._width) &&
      (_height == image._height) &&
      (_depth == image._depth) &&
			(_mipmapSize == image._mipmapSize) &&
			(_frameSize == image._frameSize) &&
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
	return (size() < image.size()) ? true : false;
}


/****************************
*protected	
****************************/


/****************************
*private
****************************/


