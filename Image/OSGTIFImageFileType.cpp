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
#else
#include <iostream.h>
#endif

#include "OSGTIFImageFileType.h"

#ifdef TIFF_LIB
#include <tiffio.h>
#endif

#include <OSGLog.h>

OSG_USING_OSG_NAMESPACE;

// Static Class Varible implementations:
static const char *suffixArray[] = {
  "tif", "tiff"
};

OSGTIFImageFileType OSGTIFImageFileType::_the ( suffixArray,
                                                sizeof(suffixArray),
                                                'T', 'T' );


/* enum OSGVecBase::VectorSizeE
 * brief 
*/


/* var OSGVecBase::VectorSizeE OSGVecBase::_iSize
 *
*/


/* const char *OSGVecBase::getClassName(void)
 *  brief Classname
*/


/* var OSGValueTypeT OSGVecBase:: _value[Size];
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
bool OSGTIFImageFileType::read (OSGImage &image, const char *fileName )
{
		bool valid = false;

#ifdef TIFF_LIB

	TIFF *in = TIFFOpen(fileName, "r");
	OSGUChar *data = 0, *line = 0, *dest;
	OSGUInt32 w, h, u, v;
	ushort bpp;
	OSGChar errorMessage[1024];
	OSGUInt16* sampleinfo;
	OSGUInt16 extrasamples;
	OSGUInt16 si;
	OSGUInt16 red,green,blue,alpha;

	if (in) {

		TIFFGetField(in, TIFFTAG_IMAGEWIDTH, &w);

		TIFFGetField(in, TIFFTAG_IMAGELENGTH, &h);

		TIFFGetFieldDefaulted(in, TIFFTAG_SAMPLESPERPIXEL, &bpp);

		if ( bpp == 4 )	{ // accept unspecified extra samples as associated alpha 
	    TIFFGetFieldDefaulted ( in, TIFFTAG_EXTRASAMPLES, 
															&extrasamples, &sampleinfo);
		
			if ( sampleinfo[0] == EXTRASAMPLE_UNSPECIFIED ) {
				si = EXTRASAMPLE_ASSOCALPHA;
				TIFFSetField(in, TIFFTAG_EXTRASAMPLES, 1, &si);
			}
		}

		data = new OSGUChar [w*h*4];
		if ( TIFFRGBAImageOK( in, errorMessage ) &&
				 TIFFReadRGBAImage(in, w, h, (uint32*)data, 1)) 
			valid = true;
		else {
			SWARNING << "Tiff reader failed: " << errorMessage << endl;
			valid = false;
		}
	
		if (valid) {
			image.set(w,h, ((bpp == 3) ? "R8G8B8" : "R8G8B8A8"));
			dest = image.data();
			
			red   = 3; 
			green = 2; 
			blue  = 1; 
			alpha = 0;

			for (v = 0; v < h; v++) {
				line = data + ((v) * (w * 4));				
				for (u = 0; u < w; u++) {
					*dest++ = line[red];
					*dest++ = line[green];
					*dest++ = line[blue];
					if (bpp == 4) 
						*dest++ = line[alpha] ^ 255;
					line += 4;
				}
			}

			TIFFClose(in);
			delete [] data;
			data = 0;
		}
	}

#else

	SWARNING << getName() 
					 << " read is not compiled into the current binary " 
					 << endl;

#endif

	return valid; 

}

//----------------------------
// Function name: write
//----------------------------
//
//Parameters:
//p: const OSGImage &image, const char *fileName
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
bool OSGTIFImageFileType::write (const OSGImage &image, const char *fileName )
{
		bool retCode = false;

#ifdef TIFF_LIB

  TIFF *out = TIFFOpen(fileName, "w");
  int lineSize = image.width() * image.pixelDepth();
	int photoMetric, samplesPerPixel;
	unsigned char *data;
  int row;

	// TODO: implemet all cases correct 

	switch (image.pixelDepth()) {
	case 1:
		samplesPerPixel = 1;
		photoMetric = PHOTOMETRIC_MINISBLACK;
		break;
	case 2:
		samplesPerPixel = 2;
		photoMetric = PHOTOMETRIC_MINISBLACK;
		break;
	case 3:
		samplesPerPixel = 3;
		photoMetric = PHOTOMETRIC_RGB;
		break;
	case 4:
		samplesPerPixel = 4;
		photoMetric = PHOTOMETRIC_RGB;
		break;
	}

	if (out) {
		TIFFSetField(out, TIFFTAG_IMAGEWIDTH,  image.width());
		TIFFSetField(out, TIFFTAG_IMAGELENGTH, image.height());
		TIFFSetField(out, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
		TIFFSetField(out, TIFFTAG_SAMPLESPERPIXEL, samplesPerPixel);
		TIFFSetField(out, TIFFTAG_BITSPERSAMPLE, 8);
		TIFFSetField(out, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
		TIFFSetField(out, TIFFTAG_PHOTOMETRIC, photoMetric);
		TIFFSetField(out, TIFFTAG_COMPRESSION, COMPRESSION_LZW);
		TIFFSetField(out, TIFFTAG_ROWSPERSTRIP, TIFFDefaultStripSize(out, -1));
		
		for (row = 0; row < image.height(); row++) {
			data = image.data() + 
				((image.height() - row - 1) * (image.width() * image.pixelDepth()));
			if (TIFFWriteScanline(out, data, row, 0) < 0)
				break;
		}
		
		TIFFClose(out);
	}

#else

	SWARNING << getName() 
					 << " write is not compiled into the current binary " 
					 << endl;

#endif

	return retCode;
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
// Function name: OSGTIFImageFileType
//----------------------------
//
//Parameters:
//p: cinst char *suffixArray[], OSGUInit16 suffixByteCount, OSGInit16 majorMagic, OSGInit minorMagic
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
OSGTIFImageFileType::OSGTIFImageFileType ( const char *suffixArray[], 
																					 OSGUInt16 suffixByteCount, 
																					 OSGInt16 majorMagic, 
																					 OSGInt16 minorMagic )
	: OSGImageFileType ( suffixArray, suffixByteCount, majorMagic, minorMagic)
{
	return;
}

//----------------------------
// Function name: OSGTIFImageFileType
//----------------------------
//
//Parameters:
//p: const OSGTIFImageFileType &obj
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
OSGTIFImageFileType::OSGTIFImageFileType (const OSGTIFImageFileType &obj )
: OSGImageFileType(obj)
{
	return;
}

//----------------------------
// Function name: ~OSGTIFImageFileType
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
OSGTIFImageFileType::~OSGTIFImageFileType (void )
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


