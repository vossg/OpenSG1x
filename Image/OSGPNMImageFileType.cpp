/*------------------------------------------*
*              OpenSG                       *
*                                           *
*                                           *
*     Copyright 2000 by OpenSG Forum        *
*                                           *
* contact: {reiners|vossg}@igd.fhg.de,      *
*           jbehr@zgdv.de                   *
*-------------------------------------------*/
/*------------------------------------------*
*              Licence                      *
*                                           *
*                                           *
*                                           *
*                                           *
*                                           *
*-------------------------------------------*/
/*------------------------------------------*
*              Changes                      *
*                                           *
*                                           *
*                                           *
*                                           *
*                                           *
*-------------------------------------------*/


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

#include "OSGPNMImageFileType.h"

OSG_USING_OSG_NAMESPACE

/*****************************
 *   Types
 *****************************/
// Static Class Varible implementations: 
static const char *suffixArray[] = 
{
	"pnm", "pbm", "pgm", "ppm"
};

OSGPNMImageFileType OSGPNMImageFileType::_the ( suffixArray,
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
//p: OSGImage &image, const char *fileName
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
bool OSGPNMImageFileType::read (OSGImage &image, const char *fileName )
{
	OSGInt16 type, width, height, lineSize, maxValue = 0, value, x, y;
	OSGUInt16 i;
	OSGUInt8 magic, commentKey = '#', *line;
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
//p: OSGImage &image, const char *fileName
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
bool OSGPNMImageFileType::write (const OSGImage &image, const char *fileName )
{	
	OSGInt16  p, y, x, lineSize;
	ofstream  out(fileName);
	OSGUInt16 bpp = image.pixelDepth();
	OSGUInt8  *data = 0;

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

		out << "# OSGPNMImageFileType write" << endl;
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
				data = (OSGUInt8*)(image.data() + (lineSize * y));
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
// Function name: OSGPNMImageFileType
//----------------------------
//
//Parameters:
//p: const char *suffixArray[], OSGUInit16 suffixByteCount, OSGInit16 majorMagic, OSGInit minorMagic
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
OSGPNMImageFileType::OSGPNMImageFileType ( const char *suffixArray[], 
																					 OSGUInt16 suffixByteCount, 
																					 OSGInt16 majorMagic, 
																					 OSGInt16 minorMagic )
	: OSGImageFileType ( suffixArray, suffixByteCount, majorMagic, minorMagic)
{
	return;
}

//----------------------------
// Function name: OSGPNMImageFileType
//----------------------------
//
//Parameters:
//p: const OSGPNMImageFileType &obj
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
OSGPNMImageFileType::OSGPNMImageFileType (const OSGPNMImageFileType &obj )
	: OSGImageFileType(obj)
{
	return;
}

//----------------------------
// Function name: ~OSGPNMImageFileType
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
OSGPNMImageFileType::~OSGPNMImageFileType (void )
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


