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
                                         suffixArray, sizeof(suffixArray));

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

    if((fd = fopen(fileName, "rb")))
    {
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
    }

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
Returns true on success.
*/
bool PNGImageFileType::write(const ImagePtr &, 
                             const Char8 *OSG_CHECK_ARG(fileName))
{
#ifdef PNG_LIB
    SWARNING << getMimeType() << " write is not implemented " << endLog;

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
                                     UInt16 suffixByteCount) :
    ImageFileType(mimeType, suffixArray, suffixByteCount)
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
