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
#else
#include <iostream.h>
#endif

#ifdef   OSG_SGI_LIB
#include <limits>
#endif

#ifdef JPEG_LIB
extern "C" {
#include <setjmp.h>
#include <jpeglib.h>
}
#endif     

#define OSG_COMPILEIMAGE

#include "OSGJPGImageFileType.h"
#include <OSGLog.h>

OSG_USING_NAMESPACE

/*****************************
 *   Types
 *****************************/


/*****************************
 *	  Classvariables
 *****************************/

// Static Class Varible implementations:
static const char *suffixArray[] = {
  "jpg", "jpeg"
};

JPGImageFileType JPGImageFileType::_the ( suffixArray,
                                                sizeof(suffixArray),
                                                'J', 'J' );

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
//d: read the the image from the given filename
//SeeAlso:
//s:
//
//------------------------------
bool JPGImageFileType::read (Image &image, const char *fileName )
{
#ifdef JPEG_LIB
    bool retCode = false;

  struct my_error_mgr {
    struct jpeg_error_mgr pub;
    jmp_buf setjmp_buffer;
  };

  unsigned char *destData;
	Image::PixelFormat pixelFormat;
  typedef struct my_error_mgr * my_error_ptr;
  struct my_error_mgr jerr;
  struct jpeg_decompress_struct cinfo;
  FILE * infile;
  JSAMPARRAY buffer;

  int row_stride;
  if ((infile = fopen(fileName, "rb")) == NULL) {
    fprintf(stderr, "can't open %s\n", fileName);
    return retCode;
  }

  cinfo.err = jpeg_std_error(&jerr.pub);
  if (setjmp(jerr.setjmp_buffer)) {
    jpeg_destroy_decompress(&cinfo);
    fclose(infile);
    return 0;
  }
  jpeg_create_decompress(&cinfo);
  jpeg_stdio_src(&cinfo, infile);
  jpeg_read_header(&cinfo, TRUE);
  jpeg_start_decompress(&cinfo);
	
	switch (cinfo.output_components) {
	case 1:
		pixelFormat = Image::OSG_L_PF;
		break;
	case 2:
		pixelFormat = Image::OSG_LA_PF;
		break;
	case 3:
		pixelFormat = Image::OSG_RGB_PF;
		break;
	case 4:
		pixelFormat = Image::OSG_RGBA_PF;
		break;
	};

  if ( image.set(pixelFormat,cinfo.output_width,cinfo.output_height)) {
		destData = image.getData() + image.getSize();
		row_stride = cinfo.output_width * cinfo.output_components;
		buffer = (*cinfo.mem->alloc_sarray)
			((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride,1 );
		while (cinfo.output_scanline < cinfo.output_height) {
			destData -= row_stride;
			jpeg_read_scanlines(&cinfo, buffer,1);
			memcpy(destData, *buffer, row_stride);
		}
		retCode = true;
	}
  else
    retCode = false;

  jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);
  fclose(infile);
	
  return retCode;

#else

	SWARNING << getName() 
					 << " read is not compiled into the current binary " 
					 << endl;

  return false;

#endif                     

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
//r:bool
// Caution
//c: 
//Assumations:
//a: 
//Describtions:
//d: write the the image to the given filename
//SeeAlso:
//s:
//
//------------------------------
bool JPGImageFileType::write (const Image &image, const char *fileName )
{
#ifdef JPEG_LIB

	if ( ( image.getBpp() != 1 && image.getBpp() != 3 ) ||
			image.getDepth() != 1
	   )
	{
		SWARNING 	<< getName() 
		 			<< " JPEG write only works for 2D 1 or 3 bpp images " 
		 			<< endl;
		return false;
	}

	bool retCode = false;

	struct my_error_mgr 
	{
		struct jpeg_error_mgr pub;
		jmp_buf setjmp_buffer;
	};
	typedef struct my_error_mgr * my_error_ptr;

	struct my_error_mgr jerr;
	struct jpeg_compress_struct cinfo;
	FILE * outfile;
	JSAMPARRAY buffer;
	UChar8 * data;
	
	if ((outfile = fopen(fileName, "wb")) == NULL) 
	{
		fprintf(stderr, "can't open %s\n", fileName);
		return retCode;
	}

	cinfo.err = jpeg_std_error(&jerr.pub);
	if (setjmp(jerr.setjmp_buffer)) 
	{
		jpeg_destroy_compress(&cinfo);
		fclose(outfile);
		return 0;
	}
	jpeg_create_compress(&cinfo);
	jpeg_stdio_dest(&cinfo, outfile);

	cinfo.image_width = image.getWidth();
	cinfo.image_height = image.getHeight();
	cinfo.input_components = image.getBpp();	
	cinfo.in_color_space = (image.getBpp()==1)?JCS_GRAYSCALE:JCS_RGB;

	jpeg_set_defaults(&cinfo);
	jpeg_set_quality(&cinfo, 90, TRUE);
	jpeg_start_compress(&cinfo, TRUE);

	buffer = &data;
	while (cinfo.next_scanline < cinfo.image_height) 
	{
		data = image.getData() + ( image.getHeight() - cinfo.next_scanline ) * 
					image.getWidth() * image.getBpp();
		jpeg_write_scanlines(&cinfo, buffer,1);
	}

	jpeg_finish_compress(&cinfo);
	jpeg_destroy_compress(&cinfo);
	fclose(outfile);

	return true;

#else

	SWARNING << getName() 
					 << " write is not compiled into the current binary " 
					 << endl;

  return false;

#endif                     

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
// Function name: JPGImageFileType
//----------------------------
//
//Parameters:
//p: cinst char *suffixArray[], UInit16 suffixByteCount, Init16 majorMagic, Init16 minorMagic
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
JPGImageFileType::JPGImageFileType ( const char *suffixArray[], 
																					 UInt16 suffixByteCount, 
																					 Int16 majorMagic, 
																					 Int16 minorMagic )
: ImageFileType ( suffixArray, suffixByteCount, majorMagic, minorMagic)
{
	return;
}

//----------------------------
// Function name: JPGImageFileType
//----------------------------
//
//Parameters:
//p: const JPGImageFileType &obj
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
JPGImageFileType::JPGImageFileType (const JPGImageFileType &obj )
	: ImageFileType(obj)
{
	return;
}

//----------------------------
// Function name: ~JPGImageFileType
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
JPGImageFileType::~JPGImageFileType (void )
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


