/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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
// Includes  
//-------------------------------
#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#ifdef   OSG_SGI_LIB
#include <limits>
#endif
#ifdef OSG_WITH_PNG
#include <png.h>
#endif 

#include "OSGPNGImageFileType.h"
#include <OSGLog.h>

#ifndef OSG_DO_DOC
#    ifdef OSG_WITH_PNG
#        define OSG_PNG_ARG(ARG) ARG
#    else
#        define OSG_PNG_ARG(ARG)
#    endif
#else
#    define OSG_PNG_ARG(ARG) ARG
#endif

OSG_USING_NAMESPACE

/*! \class osg::PNGImageFileType 
    \ingroup GrpSystemImage

Image File Type to read/write and store/restore Image objects as
PNG data.

To be able to load PNG images you need the PNG library, 
(check the Prerequisites page on www.opensg.org). 
The lib comes with all Linux distributions.

You have to --enable-png in the configure line to enable
the singleton object.
        
*/

/*****************************
 *   Types
 *****************************/
/*****************************
 *  Classvariables
 *****************************/
// Static Class Varible implementations:
static const Char8 *suffixArray[] = {
  "png"
};

/*****************************
 *  PNG lib helper
 *****************************/

#ifdef OSG_WITH_PNG

static void errorOutput (png_structp png_ptr, const char *message)
{
  FFATAL   (("PNG: %s\n", message ));

  longjmp(png_ptr->jmpbuf, 1);
}

static void warningOutput (png_structp OSG_CHECK_ARG(png_ptr), 
                           const char *message)
{
  FWARNING (("PNG: %s\n", message )); 
}

#endif

PNGImageFileType PNGImageFileType:: _the("png",
                                         suffixArray, sizeof(suffixArray),
                                         OSG_READ_SUPPORTED | 
                                         OSG_WRITE_SUPPORTED);

/********************************
 *  Class methodes
 *******************************/

PNGImageFileType& PNGImageFileType::the (void)
{
  return _the;
}

/*******************************
*public
*******************************/

//-------------------------------------------------------------------------
/*!
Tries to fill the image object with the data read from
the given fileName. Returns true on success.
*/
bool PNGImageFileType::read(      ImagePtr &OSG_PNG_ARG(image), 
                            const Char8    *OSG_PNG_ARG(fileName))
{

#ifdef OSG_WITH_PNG

    bool                retCode;
    Image::PixelFormat  pixelFormat;
    png_structp         png_ptr;
    png_infop           info_ptr;
    png_uint_32         width, wc, height, h, i;
    png_byte            bit_depth, channels, color_type;
    png_bytep           *row_pointers, base;
    FILE                *fd;

    if((fd = fopen(fileName, "rb")) == NULL)
        return false;

    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
    if(!png_ptr)
    {
        fclose(fd);
        return false;
    }

    png_set_error_fn(png_ptr, 0, &errorOutput, &warningOutput);

    info_ptr = png_create_info_struct(png_ptr);
    if(!info_ptr)
    {
        fclose(fd);
        png_destroy_read_struct(&png_ptr, 0, 0);
        return false;
    }

    if(setjmp(png_ptr->jmpbuf))
    {
        png_destroy_read_struct(&png_ptr, &info_ptr, 0);
        fclose(fd);
        return false;
    }

    png_init_io(png_ptr, fd);

    png_read_info(png_ptr, info_ptr);

    width = png_get_image_width(png_ptr, info_ptr);
    height = png_get_image_height(png_ptr, info_ptr);
    bit_depth = png_get_bit_depth(png_ptr, info_ptr);
    channels = png_get_channels(png_ptr, info_ptr);
    color_type = png_get_color_type(png_ptr, info_ptr);

    switch(channels)
    {
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

    if(image->set(pixelFormat, width, height))
    {
        // Convert paletted images to RGB
        if(color_type == PNG_COLOR_TYPE_PALETTE && bit_depth <= 8)
            png_set_expand(png_ptr);

        // Convert < 8 bit to 8 bit
        if(color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
            png_set_expand(png_ptr);

        // Add a full alpha channel if there is transparency
        // information in a tRNS chunk
        if(png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
            png_set_expand(png_ptr);

        // Convert 16 bit to 8 bit
        if(bit_depth == 16)
            png_set_strip_16(png_ptr);

        // Calculate the row pointers
        row_pointers = new png_bytep[height];
        wc = width * channels;
        h = height - 1;
        base = image->getData();
        for(i = 0; i < height; ++i)
            row_pointers[i] = base + (h - i) * wc;

        // Read the image data
        png_read_image(png_ptr, row_pointers);

        delete[] row_pointers;

        retCode = true;
    }
    else
        retCode = false;

    png_destroy_read_struct(&png_ptr, &info_ptr, 0);

    fclose(fd);

    return retCode;

#else

    SWARNING <<
        getMimeType() <<
        " read is not compiled into the current binary " <<
        std::endl;
    return false;

#endif

}

//-------------------------------------------------------------------------
/*!
Tries to write the image object to the given fileName.
Returns true on success. Based on the public domain example.c
from the PNG dist.
*/
bool PNGImageFileType::write(const ImagePtr &img, 
                             const Char8 *fileName)
{
#ifdef OSG_WITH_PNG

    FILE *fp;
    png_structp png_ptr;
    png_infop info_ptr;
    png_colorp palette;

    if(img->getDimension() < 1 || img->getDimension() > 2)
    {
        FWARNING(("PNGImageFileType::write: invalid dimension %d!\n",
            img->getDimension()));
        return false;
    }
    
    /* open the file */
    fp = fopen(fileName, "wb");
    if (fp == NULL)
    {
        FWARNING(("PNGImageFileType::write: couldn't open %s for writing!\n",
            fileName));
        return false;
    }

    /* Create and initialize the png_struct with the desired error handler
    * functions.  If you want to use the default stderr and longjump method,
    * you can supply NULL for the last three parameters.  We also check that
    * the library version is compatible with the one used at compile time,
    * in case we are using dynamically linked libraries.  REQUIRED.
    */
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,
                                0, &errorOutput, &warningOutput);

    if (png_ptr == NULL)
    {
      fclose(fp);
      return false;
    }

    /* Allocate/initialize the image information data.  REQUIRED */
    info_ptr = png_create_info_struct(png_ptr);
    if (info_ptr == NULL)
    {
      fclose(fp);
      png_destroy_write_struct(&png_ptr,  png_infopp_NULL);
      return false;
    }

    /* set up the output control if you are using standard C streams */
    png_init_io(png_ptr, fp);

    /* This is the hard way */

    /* Set the image information here.  Width and height are up to 2^31,
    * bit_depth is one of 1, 2, 4, 8, or 16, but valid values also depend on
    * the color_type selected. color_type is one of PNG_COLOR_TYPE_GRAY,
    * PNG_COLOR_TYPE_GRAY_ALPHA, PNG_COLOR_TYPE_PALETTE, PNG_COLOR_TYPE_RGB,
    * or PNG_COLOR_TYPE_RGB_ALPHA.  interlace is either PNG_INTERLACE_NONE or
    * PNG_INTERLACE_ADAM7, and the compression_type and filter_type MUST
    * currently be PNG_COMPRESSION_TYPE_BASE and PNG_FILTER_TYPE_BASE. REQUIRED
    */
    Int32 ctype, ncomp;
    switch(img->getPixelFormat())
    {
    case Image::OSG_L_PF:       ctype = PNG_COLOR_TYPE_GRAY;        
                                break;
                                
    case Image::OSG_LA_PF:      ctype = PNG_COLOR_TYPE_GRAY_ALPHA;          
                                break;
                                
    case Image::OSG_BGR_PF:
    case Image::OSG_RGB_PF:     ctype = PNG_COLOR_TYPE_RGB;                 
                                break;
                                
    case Image::OSG_BGRA_PF:
    case Image::OSG_RGBA_PF:    ctype = PNG_COLOR_TYPE_RGB_ALPHA;           
                                break;

    default:
        FWARNING(("PNGImageFileType::write: unknown pixel format %d!\n",
            img->getPixelFormat()));
        png_destroy_write_struct(&png_ptr,  png_infopp_NULL);
        return false;
        
    }
    
    png_set_IHDR(png_ptr, info_ptr, img->getWidth(), img->getHeight(),
        8, ctype,      
        PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

#if 0
    /* optional significant bit chunk */
    /* if we are dealing with a grayscale image then */
    sig_bit.gray = true_bit_depth;
    /* otherwise, if we are dealing with a color image then */
    sig_bit.red = true_red_bit_depth;
    sig_bit.green = true_green_bit_depth;
    sig_bit.blue = true_blue_bit_depth;
    /* if the image has an alpha channel then */
    sig_bit.alpha = true_alpha_bit_depth;
    png_set_sBIT(png_ptr, info_ptr, sig_bit);


    /* Optional gamma chunk is strongly suggested if you have any guess
    * as to the correct gamma of the image.
    */
    png_set_gAMA(png_ptr, info_ptr, gamma);

    /* Optionally write comments into the image */
    text_ptr[0].key = "Title";
    text_ptr[0].text = "Mona Lisa";
    text_ptr[0].compression = PNG_TEXT_COMPRESSION_NONE;
    text_ptr[1].key = "Author";
    text_ptr[1].text = "Leonardo DaVinci";
    text_ptr[1].compression = PNG_TEXT_COMPRESSION_NONE;
    text_ptr[2].key = "Description";
    text_ptr[2].text = "<long text>";
    text_ptr[2].compression = PNG_TEXT_COMPRESSION_zTXt;
#ifdef PNG_iTXt_SUPPORTED
    text_ptr[0].lang = NULL;
    text_ptr[1].lang = NULL;
    text_ptr[2].lang = NULL;
#endif
    png_set_text(png_ptr, info_ptr, text_ptr, 3);
#endif
    /* other optional chunks like cHRM, bKGD, tRNS, tIME, oFFs, pHYs, */
    /* note that if sRGB is present the gAMA and cHRM chunks must be ignored
    * on read and must be written in accordance with the sRGB profile */

    /* Write the file header information.  REQUIRED */
    png_write_info(png_ptr, info_ptr);

#if 0
    /* invert monochrome pixels */
    png_set_invert_mono(png_ptr);

    /* Shift the pixels up to a legal bit depth and fill in
    * as appropriate to correctly scale the image.
    */
    png_set_shift(png_ptr, &sig_bit);

    /* pack pixels into bytes */
    png_set_packing(png_ptr);

    /* Get rid of filler (OR ALPHA) bytes, pack XRGB/RGBX/ARGB/RGBA into
    * RGB (4 channels -> 3 channels). The second parameter is not used.
    */
    png_set_filler(png_ptr, 0, PNG_FILLER_BEFORE);

    /* swap bytes of 16-bit files to most significant byte first */
    png_set_swap(png_ptr);

    /* swap bits of 1, 2, 4 bit packed pixel formats */
    png_set_packswap(png_ptr);
#endif

    if(img->getPixelFormat() == Image::OSG_BGR_PF ||
       img->getPixelFormat() == Image::OSG_BGRA_PF
      )
    {
        /* flip BGR pixels to RGB */
        png_set_bgr(png_ptr);

        /* swap location of alpha bytes from ARGB to RGBA */
        png_set_swap_alpha(png_ptr);
    }
    
    /* The easiest way to write the image (you may have a different memory
    * layout, however, so choose what fits your needs best).  You need to
    * use the first method if you aren't handling interlacing yourself.
    */
    png_bytep *row_pointers = new png_bytep [img->getHeight()];
    
    for(UInt32 k = 0; k < img->getHeight(); k++)
    {
        row_pointers[k] = img->getData() + 
                          (img->getHeight() - 1 - k) * 
                            img->getWidth() * img->getBpp();
    }
    
    /* write out the entire image data in one call */
    png_write_image(png_ptr, row_pointers);

    /* It is REQUIRED to call this to finish writing the rest of the file */
    png_write_end(png_ptr, info_ptr);
    
    /* clean up after the write, and free any memory allocated */
    png_destroy_write_struct(&png_ptr, &info_ptr);

    delete [] row_pointers;

    /* close the file */
    fclose(fp);

    /* that's it */
    return true;

#else
    SWARNING <<
        getMimeType() <<
        " write is not compiled into the current binary " <<
        endLog;
    return false;
#endif
}

//-------------------------------------------------------------------------
/*!
Constructor used for the singleton object
*/
PNGImageFileType::PNGImageFileType ( const Char8 *mimeType,
                                     const Char8 *suffixArray[],
                                     UInt16 suffixByteCount,
                                     UInt32 flags) :
    ImageFileType(mimeType, suffixArray, suffixByteCount, flags)
{
    return;
}

//-------------------------------------------------------------------------
/*!
Dummy Copy Constructor
*/
PNGImageFileType::PNGImageFileType(const PNGImageFileType &obj) :
    ImageFileType(obj)
{
    return;
}


//-------------------------------------------------------------------------
/*!
Destructor
*/
PNGImageFileType::~PNGImageFileType(void)
{
    return;
}
