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

#ifdef   OSG_SGI_LIB
#include <limits>
#endif

#ifdef JPEG_LIB
extern "C" {
#include <setjmp.h>
#include <jpeglib.h>
}
#endif     


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

OSGJPGImageFileType OSGJPGImageFileType::_the ( suffixArray,
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
//d: read the the image from the given filename
//SeeAlso:
//s:
//
//------------------------------
bool OSGJPGImageFileType::read (OSGImage &image, const char *fileName )
{
	  bool retCode = false;

#ifdef JPEG_LIB

  struct my_error_mgr {
    struct jpeg_error_mgr pub;
    jmp_buf setjmp_buffer;
  };

  unsigned char *destData;
	const char * pixelFormat;
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
		pixelFormat = "L8";
		break;
	case 2:
		pixelFormat = "L8A8";
		break;
	case 3:
		pixelFormat = "R8B8G8";
		break;
	case 4:
		pixelFormat = "R8B8G8L8";
		break;
	};

  if ( image.set(cinfo.output_width,cinfo.output_height,pixelFormat)) {
		destData = image.data()
			+(image.width()*image.height()*image.pixelDepth());
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

#endif                     

  return false;

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
//d: write the the image to the given filename
//SeeAlso:
//s:
//
//------------------------------
bool OSGJPGImageFileType::write (const OSGImage &image, const char *fileName )
{
	SWARNING << getName() << " write is not implemented" << endl;

	return false;
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
// Function name: OSGJPGImageFileType
//----------------------------
//
//Parameters:
//p: cinst char *suffixArray[], OSGUInit16 suffixByteCount, OSGInit16 majorMagic, OSGInit16 minorMagic
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
OSGJPGImageFileType::OSGJPGImageFileType ( const char *suffixArray[], 
																					 OSGUInt16 suffixByteCount, 
																					 OSGInt16 majorMagic, 
																					 OSGInt16 minorMagic )
: OSGImageFileType ( suffixArray, suffixByteCount, majorMagic, minorMagic)
{
	return;
}

//----------------------------
// Function name: OSGJPGImageFileType
//----------------------------
//
//Parameters:
//p: const OSGJPGImageFileType &obj
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
OSGJPGImageFileType::OSGJPGImageFileType (const OSGJPGImageFileType &obj )
	: OSGImageFileType(obj)
{
	return;
}

//----------------------------
// Function name: ~OSGJPGImageFileType
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
OSGJPGImageFileType::~OSGJPGImageFileType (void )
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


