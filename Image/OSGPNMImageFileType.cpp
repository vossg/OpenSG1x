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


#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#include <fstream>
#else
#include <iostream.h>
#include <fstream.h>
#endif

#ifdef OSG_SGI_STL
#include <limits>
#ifndef INT_MAX
#define INT_MAX numeric_limits<int>::max()
#endif
#else
#include <limits.h>
#endif

#include <OSGLog.h>

#define OSG_COMPILEIMAGE

#include "OSGPNMImageFileType.h"

OSG_USING_NAMESPACE

/*****************************
 *   Types
 *****************************/
// Static Class Varible implementations: 
static const char *suffixArray[] = 
{
	"pnm", "pbm", "pgm", "ppm"
};

PNMImageFileType PNMImageFileType::_the ( 	suffixArray,
											sizeof(suffixArray),
											'P', -1 );


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
// Function name: read
//----------------------------
//
//Parameters:
//p: Image &image, const char *fileName
//GlobalVars:
//g: 
//Returns:
//r:bool
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: read the image from the given file
//SeeAlso:
//s:
//
//------------------------------
bool PNMImageFileType::read (Image &image, const char *fileName )
{
	Int16 type, width, height, lineSize, maxValue = 0, value, x, y;
	UInt16 i;
	UInt8 magic, commentKey = '#', *line;
	ifstream in(fileName, ios::in );
	
	if (in.rdbuf()->is_open()) {
		in >> magic >> type;
		in.ignore(INT_MAX, '\n');
		while (in.peek() == commentKey) 
			in.ignore(INT_MAX, '\n');
		in >> width >> height;
	}

	switch (type) {
	case 1:
	case 4:
		maxValue = 1;
		image.set (width, height, "L8" );
		break;
	case 2:
	case 5:
		maxValue = 0;
		image.set( width, height, "L8" );
		break;
	case 3:
	case 6:
		maxValue = 0;
		image.set( width, height, "R8G8B8" );
		break;
	default:
		SWARNING << "unknown image format type " << type << " in " << fileName
						 << endl;
		break;
	}
	
	if (!maxValue) {
		in >> maxValue;
		if (maxValue != 255) {
			SWARNING << "unknown max value " << maxValue << " in " << fileName 
							 << ", can't read the image"
							 << endl;
			maxValue = 0;
		}
	}

	// eat the endline
	in.ignore(INT_MAX, '\n');
	
	
	if (maxValue && (image.size())) {
		
		SINFO << "read pnm file of type " << type << ", "
					<< width << "x" << height << endl;

		lineSize = width * image.pixelDepth();
		if (type >= 4) { // image is binary
			for (y = height - 1; y >= 0; y--) 
				in.read((char *) &(image.data()[y * lineSize]), lineSize);
		}
		else {           // image is ascii
			for (y = height - 1; y >= 0; y--) {
				line = image.data() + (y * lineSize);
				for (x = 0; x < lineSize; x++) {
					in >> value;
					*line++ = value;
				}
			}
		}

		if (maxValue == 1) 
			for (i = 0; i < image.size(); i++) 
				image.data()[i] = image.data()[i] * 255;
		
	}

	return true;
}

//----------------------------
// Function name: write
//----------------------------
//
//Parameters:
//p: Image &image, const char *fileName
//GlobalVars:
//g: 
//Returns:
//r:bool
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: write the image to the given file
//SeeAlso:
//s:
//
//------------------------------
bool PNMImageFileType::write (const Image &image, const char *fileName )
{	
	Int16  p, y, x, lineSize;
	ofstream  out(fileName);
	UInt16 bpp = image.pixelDepth();
	UInt8  *data = 0;

	if (out.rdbuf()->is_open()) {
		switch (bpp) {
		case 1:
		case 2:
			out << "P5" << endl;
			break;
		case 3:
		case 4:
			out << "P6" << endl;
			break;
		}

		out << "# PNMImageFileType write" << endl;
		out << image.width() << " " << image.height() << endl;
		out << "255" << endl;

		if (bpp & 1) {
			// with alpha
			lineSize = image.pixelDepth() * image.width();		
			for (y = image.height() - 1; y >= 0; y--) 
				out.write((char *) (image.data() + (lineSize * y)), lineSize);
		}
		else {
			// skip alpha
			lineSize = image.pixelDepth() * image.width();		
			for (y = image.height() - 1; y >= 0; y--) {
				data = (UInt8*)(image.data() + (lineSize * y));
				for ( x = 0; x < image.width(); x++) {
					for (p = bpp-1; p--; ) 
						out << *data++;
					data++;
				}
			}
		}

		out.close();
	}

	return data ? true : false;
}

/******************************
*protected
******************************/


/******************************
*private	
******************************/


/***************************
*instance methodes 
***************************/


/***************************
*public
***************************/


/**constructors & destructors**/


//----------------------------
// Function name: PNMImageFileType
//----------------------------
//
//Parameters:
//p: const char *suffixArray[], UInit16 suffixByteCount, Init16 majorMagic, Init minorMagic
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
PNMImageFileType::PNMImageFileType ( const char *suffixArray[], 
																					 UInt16 suffixByteCount, 
																					 Int16 majorMagic, 
																					 Int16 minorMagic )
	: ImageFileType ( suffixArray, suffixByteCount, majorMagic, minorMagic)
{
	return;
}

//----------------------------
// Function name: PNMImageFileType
//----------------------------
//
//Parameters:
//p: const PNMImageFileType &obj
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
PNMImageFileType::PNMImageFileType (const PNMImageFileType &obj )
	: ImageFileType(obj)
{
	return;
}

//----------------------------
// Function name: ~PNMImageFileType
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
PNMImageFileType::~PNMImageFileType (void )
{
	return;
}

/*------------access----------------*/

/*------------properies-------------*/

/*------------your Category---------*/

/*------------Operators-------------*/



/****************************
*protected	
****************************/


/****************************
*private
****************************/


