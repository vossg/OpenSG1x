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

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGTIFImageFileType.h"

#ifdef OSG_WITH_TIF
#include <tiffio.h>
#endif

#include <OSGLog.h>

OSG_USING_NAMESPACE

// Static Class Varible implementations:
static const Char8 *suffixArray[] = {
  "tif", "tiff"
};

TIFImageFileType TIFImageFileType::_the ( suffixArray, sizeof(suffixArray) );


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
// Function name: read
//----------------------------
//
//Parameters:
//p: Image &image, const char *fileName
//GlobalVars:
//g: 
//Returns:
//r:Bool
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
Bool TIFImageFileType::read (Image &image, const Char8 *fileName )
{
		Bool valid = false;

#ifdef OSG_WITH_TIF

	TIFF *in = TIFFOpen(fileName, "r");
	UChar8 *data = 0, *line = 0, *dest;
	UInt32 w, h, u, v;
	UInt16 bpp;
	Char8 errorMessage[1024];
	UInt16* sampleinfo;
	UInt16 extrasamples;
	UInt16 si;
	UInt16 red,green,blue,alpha;

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

		data = new UChar8 [w*h*4];
		if ( TIFFRGBAImageOK( in, errorMessage ) &&
				 TIFFReadRGBAImage(in, w, h, (uint32*)data, 1)) 
			valid = true;
		else 
		{
			SWARNING << "Tiff reader failed: " << errorMessage << endl;
			valid = false;
		}
	
		if (valid) 
		{
			Image::PixelFormat type;
			switch ( bpp )
			{
			case 1: 	type = Image::OSG_L_PF; break;
			case 2: 	type = Image::OSG_LA_PF; break;
			case 3: 	type = Image::OSG_RGB_PF; break;
			case 4: 	type = Image::OSG_RGBA_PF; break;
			}
			
			image.set( type, w, h );
			dest = image.getData();
			
#if defined(__linux) || defined(_WIN32)

   red   = 0;
   green = 1;
   blue  = 2;
   alpha = 3;

#else

   red   = 3;
   green = 2;
   blue  = 1;
   alpha = 0;

#endif

			for (v = 0; v < h; v++) 
			{
				line = data + ((v) * (w * 4));				
				for (u = 0; u < w; u++) 
				{
					switch ( bpp )
					{
					case 4: 	*dest++ = line[red];
							 	*dest++ = line[green];
							 	*dest++ = line[blue];
							 	*dest++ = line[alpha];
								 break;
					case 3: 	*dest++ = line[red];
							 	*dest++ = line[green];
							 	*dest++ = line[blue];
								 break;
					case 2: 	*dest++ = line[red];
							 	*dest++ = line[green];
								 break;
					case 1: 	*dest++ = line[red];
								 break;
					}
					line += 4;
				}
			}

			TIFFClose(in);
			delete [] data;
			data = 0;
		}
	}

#else

	SWARNING << getMimeType() 
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
//p: const Image &image, const char *fileName
//GlobalVars:
//g: 
//Returns:
//r:Bool
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
Bool TIFImageFileType::write (const Image &image, const Char8 *fileName )
{
	Bool retCode = false;

#ifdef OSG_WITH_TIF

	TIFF *out = TIFFOpen(fileName, "w");
	int lineSize = image.getWidth() * image.getBpp();
	int photometric, samplesPerPixel;
	const unsigned char *data;
	int row;
	
	// TODO: implemet all cases correct 
	
	switch (image.getBpp()) 	{
	case 1:
		samplesPerPixel = 1;
		photometric = PHOTOMETRIC_MINISBLACK;
		break;
	case 2:
		samplesPerPixel = 2;
		photometric = PHOTOMETRIC_MINISBLACK;
		break;
	case 3:
		samplesPerPixel = 3;
		photometric = PHOTOMETRIC_RGB;
		break;
	case 4:
		samplesPerPixel = 4;
		photometric = PHOTOMETRIC_RGB;
		break;
	}
	
	if (out) {
		TIFFSetField(out, TIFFTAG_IMAGEWIDTH,  image.getWidth());
		TIFFSetField(out, TIFFTAG_IMAGELENGTH, image.getHeight());
		TIFFSetField(out, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
		TIFFSetField(out, TIFFTAG_SAMPLESPERPIXEL, samplesPerPixel);
		TIFFSetField(out, TIFFTAG_BITSPERSAMPLE, 8);
		TIFFSetField(out, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
		TIFFSetField(out, TIFFTAG_PHOTOMETRIC, photometric);
		TIFFSetField(out, TIFFTAG_COMPRESSION, COMPRESSION_NONE);
		TIFFSetField(out, TIFFTAG_ROWSPERSTRIP, TIFFDefaultStripSize(out, -1));
		
		for (row = 0; row < image.getHeight(); row++) {
			data = image.getData() + ((image.getHeight() - row - 1) * lineSize);
			if (TIFFWriteScanline(out, (tdata_t)data, row, 0) < 0)
				break;
		}
		
		TIFFClose(out);
	}
	
#else
	
	SWARNING << getMimeType() 
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
// Function name: TIFImageFileType
//----------------------------
//
//Parameters:
//p: cinst char *suffixArray[], UInit16 suffixByteCount, Init16 majorMagic, Init minorMagic
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
TIFImageFileType::TIFImageFileType ( const Char8 *suffixArray[], 
																		 UInt16 suffixByteCount )
	: ImageFileType ( suffixArray, suffixByteCount )
{
	return;
}

//----------------------------
// Function name: TIFImageFileType
//----------------------------
//
//Parameters:
//p: const TIFImageFileType &obj
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
TIFImageFileType::TIFImageFileType (const TIFImageFileType &obj )
: ImageFileType(obj)
{
	return;
}

//----------------------------
// Function name: ~TIFImageFileType
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
TIFImageFileType::~TIFImageFileType (void )
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


