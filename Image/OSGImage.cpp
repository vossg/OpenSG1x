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

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif


#include "OSGImage.h"
#include "OSGImageFileHandler.h"

OSG_USING_NAMESPACE

/* enum VecBase::VectorSizeE
 * brief 
*/


/* var VecBase::VectorSizeE VecBase::_iSize
 *
*/


/* const char *VecBase::getClassName(void)
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
//p: int width, int height, const char *pixelFormat, unsigned char *data = 0
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
bool Image::set ( int width, int height, 
										 const char *pixelFormat, unsigned char *data  )
{
	_width = width;
	_height = height;
	_depth = 1;
	_pixelDepth = 0;
	_pixelFormat.set(pixelFormat);

	return createData(data);
}
//----------------------------
// Function name: set
//----------------------------
//
//Parameters:
//p: int width, int height, int depth,const char *pixelFormat, unsigned char *data = 0
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
bool Image::set ( int width, int height, int depth, 
										 const char *pixelFormat, unsigned char *data )
{
	_width = width;
	_height = height;
	_depth = depth;
	_pixelDepth = 0;
	_pixelFormat.set(pixelFormat);
	
	return createData(data);
}

//----------------------------
// Function name: reformat
//----------------------------
//
//Parameters:
//p: const char *pixelFormat, Image *destination = 0
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
bool Image::reformat (const char *pixelFormat, Image *destination )
{
		/*
	unsigned char *data;
	int srcI, destI, DestSize;
	bool valid = false;
	int sum;

	cout << "INFO: Try to reformat image from pixelDepth " 
			 << int(_pixelDepth) << " to " << int(pixelDepth) << " ... ";
	cout.flush();

	// TODO !!! code all the cases !!!
	if ( size() && pixelDepth && (pixelDepth != _pixelDepth) ) {
		DestSize = pixelDepth * _width * _height * _depth;
		data = new unsigned char[DestSize];
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
//p: unsigned char pixelValue
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
void Image::clear(unsigned char pixelValue)
{
	unsigned long n = size();
	unsigned char *data = _data;

	if (n && data) 
		while (n--) 
			*data++ = pixelValue;
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
bool Image::scale (int width, int height, int depth,
											Image *destination )
{
	bool retCode = true;
	unsigned char *data, *dest, *slice, *line, *pixel;
	float sx, sy, sz, p;
	int x,y,z;
  
	if (width != _width || height != _height || depth != _depth) {
		sx = float(_width) / float(width);
		sy = float(_height) / float(height);
		sz = float(_depth) / float(depth);
		if (destination) {
			destination->set(width,height,depth,_pixelFormat.str());
			dest = data = destination->data();
		}
		else
			dest = data = new unsigned char[width * height * depth * _pixelDepth];

		if (data) {			
			for ( z = 0; z < depth; z++) {
				slice = _data + int(sz * z + 0.5) * _pixelDepth * _width * _height;
				for ( y = 0; y < height; y++) {
					line = slice + int (sy * y + 0.5) * _pixelDepth * _width;
					for ( x = 0; x < width; x++) {
						pixel = line + int(sx * x + 0.5) * _pixelDepth;
						p = _pixelDepth;
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
//p: const char *fileName
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
bool Image::write (const char *fileName )
{
  return ImageFileHandler::the().write(*this, fileName);
}

//----------------------------
// Function name: read
//----------------------------
//
//Parameters:
//p: const char *fileName
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
bool Image::read (const char *fileName )
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
//p: const unsigned char *data
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
bool Image::createData (const unsigned char *data )
{
		int i, bitCount = 0, c;
	unsigned long size;
	bool expectDigit;
	const char *format = _pixelFormat.str();

	if (!_pixelFormat.empty()) {
		expectDigit = false;
		for (i = 0; (c = format[i]); i++) {
			if (expectDigit)
				if (isdigit(c))
					bitCount += (c - '0');
			  else {
					bitCount = 0;
					break;
				}
			else {
				if (!isalpha(c)) {
					bitCount = 0;
					break;
				}
			}
			expectDigit = !expectDigit;
		}
	}

	if (!bitCount || (bitCount & 7)) {
		SWARNING << "Invalid pixelFormat string in Image::createData()" << endl;
	}
	else {
		_pixelDepth = bitCount >> 3;
		size = _width * _height * _depth *  _pixelDepth;
	}

	_dimension = 0;

	if (_data)
		delete [] _data;

	if (size) {
		_data = new unsigned char[size];
		if (_data) {
			if (data)
				memcpy(_data, data, size);

			if (_depth == 1)
				if (_height == 1)
					_dimension = 1;
				else
					_dimension = 2;
			else
				_dimension = 3;

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
: _dimension(0), _width(0), _height(0), _depth(0), _pixelDepth(0),
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
Image::Image (const Image &obj, bool copy )
: _dimension(0), _width(obj._width), _height(obj._height), _depth(obj._depth),
  _pixelDepth(0), _pixelFormat(obj._pixelFormat), _data(0)

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
	if (_data) 
	{
		delete [] _data;
		_data = 0;
	}	
}

//----------------------------
// Function name: Image
//----------------------------
//
//Parameters:
//p: int width, int height, int depth, const char *pixelFormat, unsigned char *data = 0
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
Image::Image ( int width, int height, int depth, 
										 const char *pixelFormat, unsigned char *data )
: _dimension(0), _width(width), _height(height), _depth(depth), 
	_pixelDepth(0), _pixelFormat(pixelFormat), _data(0)
{
	createData(data);
}

//----------------------------
// Function name: Image
//----------------------------
//
//Parameters:
//p: int width, int height, const char *pixelFormat, unsigned char *data = 0
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
Image::Image ( int width, int height, const char *pixelFormat, 
										 unsigned char *data )
: _dimension(0),
  _width(width), _height(height), _depth(1),
  _pixelDepth(0), _pixelFormat(pixelFormat),
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
bool Image::operator == (const Image &image )
{
 unsigned long i, size = _width * _height * _depth * _pixelDepth;

  if ((_width == image._width) &&
      (_height == image._height) &&
      (_depth == image._depth) &&
      (_pixelDepth == image._pixelDepth)) {
    for (i = 0; i < size; ++i)
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
bool Image::operator < (const Image &image )
{
	return (size() < image.size()) ? true : false;
}


/****************************
*protected	
****************************/


/****************************
*private
****************************/


