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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <iostream>
#include <fstream>

#include <OSGLog.h>

#include "OSGPNMImageFileType.h"

#ifdef OSG_SGI_STL
//#include <limits>
#ifndef INT_MAX
#define INT_MAX numeric_limits<int>::max()
#endif
#else
#include <limits.h>
#endif

OSG_USING_NAMESPACE

/*****************************
 *   Types
 *****************************/
// Static Class Varible implementations: 
static const Char8 *suffixArray[] = 
{
	"pnm", "pbm", "pgm", "ppm"
};

PNMImageFileType PNMImageFileType::_the ( 	suffixArray,
																						sizeof(suffixArray) );


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
//p: Image &image, const Char8 *fileName
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
bool PNMImageFileType::read (Image &image, const Char8 *fileName )
{
	Int16 type, width, height, lineSize, maxValue = 0, value, x, y;
	UInt16 i;
    UInt8 id, commentKey = '#';
// *line;
	ifstream in(fileName, ios::in );
	
	if (in.rdbuf()->is_open()) {
		in >> id >> type;
		in.ignore(INT_MAX, '\n');
		while (in.peek() == commentKey) 
			in.ignore(INT_MAX, '\n');
		in >> width >> height;
	}

	switch (type) {
	case 1:
	case 4:
		maxValue = 1;
		image.set (Image::OSG_L_PF,width, height);
		break;
	case 2:
	case 5:
		maxValue = 0;
		image.set( Image::OSG_L_PF,width, height );
		break;
	case 3:
	case 6:
		maxValue = 0;
		image.set( Image::OSG_RGB_PF, width, height );
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
	
	
	if (maxValue && (image.getSize())) {
		
		SINFO << "read pnm file of type " << type << ", "
					<< width << "x" << height << endl;

		lineSize = width * image.getBpp();
		if (type >= 4) { // image is binary
			for (y = height - 1; y >= 0; y--) 
				in.read((Char8 *) &(image.getData()[y * lineSize]), lineSize);
		}
		else {           // image is ascii
			for (y = height - 1; y >= 0; y--) {
//				line = image.getData() + (y * lineSize);
				for (x = 0; x < lineSize; x++) {
					in >> value;
	}
			}
		}

		if (maxValue == 1) 
			for (i = 0; i < image.getSize(); i++) 
				image.getData()[i] = image.getData()[i] * 255;
		
	}

	return true;
}

//----------------------------
// Function name: write
//----------------------------
//
//Parameters:
//p: Image &image, const Char8 *fileName
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
bool PNMImageFileType::write (const Image &image, const Char8 *fileName )
{	
	Int16  p, y, x, lineSize;
	ofstream  out(fileName);
	UInt16 bpp = image.getBpp();
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
		out << image.getWidth() << " " << image.getHeight() << endl;
		out << "255" << endl;

		if (bpp & 1) {
			// with alpha
			lineSize = image.getBpp() * image.getWidth();		
			for (y = image.getHeight() - 1; y >= 0; y--) 
				out.write( (char*) (image.getData() + (lineSize * y)), lineSize);
		}
		else {
			// skip alpha
			lineSize = image.getBpp() * image.getWidth();		
			for (y = image.getHeight() - 1; y >= 0; y--) {
				data = (UInt8*)(image.getData() + (lineSize * y));
				for ( x = 0; x < image.getWidth(); x++) {
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
//p: const Char8 *suffixArray[], UInit16 suffixByteCount
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
PNMImageFileType::PNMImageFileType ( const Char8 *suffixArray[], 
																					 UInt16 suffixByteCount )
	: ImageFileType ( suffixArray, suffixByteCount )
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


