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

#ifdef OSG_WITH_JPG
extern "C" {
#include <setjmp.h>
#include <jpeglib.h>
}
#endif

#ifdef   OSG_SGI_LIB
#include <limits>
#endif
#include "OSGJPGImageFileType.h"
#include <OSGLog.h>

#ifndef OSG_DO_DOC
#    ifdef OSG_WITH_JPG
#        define OSG_JPG_ARG(ARG) ARG
#    else
#        define OSG_JPG_ARG(ARG)
#    endif
#else
#    define OSG_JPG_ARG(ARG) ARG
#endif

OSG_USING_NAMESPACE

/*! \class osg::JPGImageFileType 
    \ingroup GrpSystemImage

Image File Type to read/write and store/restore Image objects as
JPEG data.

To be able to load JPEG images you need the IJG JPEG library, 
version 6 or later (check the Prerequisites page on www.opensg.org). 
The lib comes with all Linux distributions.

You have to --enable-jpg in the configure line to enable
the singleton object.
    
*/

#ifdef OSG_WITH_JPG

struct
{
    struct jpeg_destination_mgr dest;
    struct jpeg_source_mgr      src;
    UChar8                      *buffer;
    UInt32                      memSize;
    UInt32                      dataSize;
} jpeg_mem;

/* */
static void jpeg_mem_init_source(j_decompress_ptr OSG_CHECK_ARG(cinfo))
{
    jpeg_mem.src.next_input_byte = (JOCTET *) jpeg_mem.buffer;
    jpeg_mem.src.bytes_in_buffer = (size_t) jpeg_mem.dataSize;
}

/* */
static boolean jpeg_mem_fill_input_buffer(j_decompress_ptr OSG_CHECK_ARG(cinfo))
{
    SFATAL << "Missing data. Given data block to small." << std::endl;
    return false;
}

/* */
static void jpeg_mem_skip_input_data(j_decompress_ptr OSG_CHECK_ARG(cinfo    ),
                              long             OSG_CHECK_ARG(num_bytes))
{
}

/* */
static boolean jpeg_mem_resync_to_restart(j_decompress_ptr OSG_CHECK_ARG(cinfo  ),
                                   int              OSG_CHECK_ARG(desired))
{
    return false;
}

/* */
static void jpeg_mem_term_source(j_decompress_ptr OSG_CHECK_ARG(cinfo))
{
}

/* */
static void jpeg_mem_init_destination(j_compress_ptr OSG_CHECK_ARG(cinfo))
{
    jpeg_mem.dest.next_output_byte = (JOCTET *) jpeg_mem.buffer;
    jpeg_mem.dest.free_in_buffer = (size_t) jpeg_mem.memSize;
}

/* */
static boolean jpeg_mem_empty_output_buffer(j_compress_ptr OSG_CHECK_ARG(cinfo))
{
    SFATAL << "Not enough space left in buffer." << std::endl;
    return false;
}

/* */
static void jpeg_mem_term_destination(j_compress_ptr OSG_CHECK_ARG(cinfo))
{
    jpeg_mem.dataSize = ((UChar8 *) jpeg_mem.dest.next_output_byte) - ((UChar8 *) jpeg_mem.buffer);
}

/* */
static void jpeg_memory_dest(struct jpeg_compress_struct *cinfo, 
                             UChar8               *buffer,
                             UInt32                memSize)
{
    jpeg_mem.buffer=buffer;
    jpeg_mem.memSize=memSize;
    jpeg_mem.dest.init_destination    = jpeg_mem_init_destination;
    jpeg_mem.dest.empty_output_buffer = jpeg_mem_empty_output_buffer;
    jpeg_mem.dest.term_destination    = jpeg_mem_term_destination;
    cinfo->dest=&jpeg_mem.dest;
}

/* */
static void jpeg_memory_src(struct jpeg_decompress_struct *cinfo, 
                     const  UChar8                 *buffer,
                            UInt32                  dataSize)
{
    jpeg_mem.buffer = const_cast < UChar8 * > (buffer);
    jpeg_mem.dataSize = dataSize;
    jpeg_mem.src.init_source       = jpeg_mem_init_source;
    jpeg_mem.src.fill_input_buffer = jpeg_mem_fill_input_buffer;
    jpeg_mem.src.skip_input_data   = jpeg_mem_skip_input_data;
    jpeg_mem.src.resync_to_restart = jpeg_mem_resync_to_restart;
    jpeg_mem.src.term_source       = jpeg_mem_term_source;
    cinfo->src = &jpeg_mem.src;
}
#endif

/*****************************
 *   Types
 *****************************/
/*****************************
 *  Classvariables
 *****************************/
// Static Class Varible implementations:
static const Char8                  *suffixArray[] = { "jpg", "jpeg" };

JPGImageFileType JPGImageFileType:: _the("jpeg",
                                         suffixArray, sizeof(suffixArray),
                                         OSG_READ_SUPPORTED | 
                                         OSG_WRITE_SUPPORTED );

/********************************
 *  Class methodes
 *******************************/


//-------------------------------------------------------------------------
/*!
Class method to get the singleton Object
*/
JPGImageFileType& JPGImageFileType::the (void)
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
bool JPGImageFileType::read(      ImagePtr &OSG_JPG_ARG(image), 
                            const Char8    *OSG_JPG_ARG(fileName))
{
#ifdef OSG_WITH_JPG
    bool    retCode = false;
    struct local_error_mgr
    {
        struct jpeg_error_mgr   pub;
        jmp_buf                 setjmp_buffer;
    };

    unsigned char                   *destData;
    Image::PixelFormat              pixelFormat;

    unsigned long                    imageSize;
    typedef struct local_error_mgr  *local_error_ptr;
    struct local_error_mgr          jerr;
    struct jpeg_decompress_struct   cinfo;
    FILE                            *infile;
    JSAMPARRAY                      buffer;

    int                             row_stride;

    if((infile = fopen(fileName, "rb")))
    {
        cinfo.err = jpeg_std_error(&jerr.pub);
        if(setjmp(jerr.setjmp_buffer))
        {
            jpeg_destroy_decompress(&cinfo);
            fclose(infile);
            return 0;
        }

        jpeg_create_decompress(&cinfo);
        jpeg_stdio_src(&cinfo, infile);
        jpeg_read_header(&cinfo, TRUE);
        jpeg_start_decompress(&cinfo);

        switch(cinfo.output_components)
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

        if(image->set(pixelFormat, cinfo.output_width, cinfo.output_height))
        {
            imageSize = image->getSize();
            destData = image->getData() + imageSize;
            row_stride = cinfo.output_width * cinfo.output_components;
            buffer = (*cinfo.mem->alloc_sarray) ((j_common_ptr) & cinfo, JPOOL_IMAGE, row_stride, 1);
            while(cinfo.output_scanline < cinfo.output_height)
            {
                destData -= row_stride;
                jpeg_read_scanlines(&cinfo, buffer, 1);
                memcpy(destData, *buffer, row_stride);
            }

            retCode = true;
        }
        else
            retCode = false;

        jpeg_finish_decompress(&cinfo);
        jpeg_destroy_decompress(&cinfo);
        fclose(infile);
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
bool JPGImageFileType::write(const ImagePtr &OSG_JPG_ARG(image), 
                             const Char8    *OSG_JPG_ARG(fileName))
{
#ifdef OSG_WITH_JPG
    if((image->getBpp() != 1 && 
        image->getBpp() != 3) || image->getDepth() != 1)
    {
        SWARNING <<
            getMimeType() <<
            " JPEG write only works for 2D 1 or 3 bpp images " <<
            std::endl;
        return false;
    }

    bool    retCode = false;

    struct local_error_mgr
    {
        struct jpeg_error_mgr   pub;
        jmp_buf                 setjmp_buffer;
    };

    typedef struct local_error_mgr  *local_error_ptr;

    struct local_error_mgr          jerr;
    struct jpeg_compress_struct     cinfo;
    FILE                            *outfile;
    JSAMPARRAY                      buffer;
    UChar8                          *data;

    if((outfile = fopen(fileName, "wb")) == NULL)
    {
        fprintf(stderr, "can't open %s\n", fileName);
        return retCode;
    }

    cinfo.err = jpeg_std_error(&jerr.pub);
    if(setjmp(jerr.setjmp_buffer))
    {
        jpeg_destroy_compress(&cinfo);
        fclose(outfile);
        return 0;
    }

    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, outfile);

    cinfo.image_width = image->getWidth();
    cinfo.image_height = image->getHeight();
    cinfo.input_components = image->getBpp();
    cinfo.in_color_space = (image->getBpp() == 1) ? JCS_GRAYSCALE : JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, 90, TRUE);
    jpeg_start_compress(&cinfo, TRUE);

    buffer = &data;
    while(cinfo.next_scanline < cinfo.image_height)
    {
        data = image->getData() +
            (image->getHeight() - 1 - cinfo.next_scanline) *
            image->getWidth() *
            image->getBpp();
        jpeg_write_scanlines(&cinfo, buffer, 1);
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
    fclose(outfile);

    return true;

#else
    SWARNING <<
        getMimeType() <<
        " write is not compiled into the current binary " <<
        std::endl;
    return false;
#endif
}

/* */
UInt64 JPGImageFileType::restoreData(      ImagePtr &OSG_JPG_ARG(image  ), 
                                     const UChar8   *OSG_JPG_ARG(buffer ),
                                           Int32     OSG_JPG_ARG(memSize))
{
#ifdef OSG_WITH_JPG
    bool    retCode = false;
    struct local_error_mgr
    {
        struct jpeg_error_mgr   pub;
        jmp_buf                 setjmp_buffer;
    };

    unsigned char                   *destData;
    Image::PixelFormat              pixelFormat;

    unsigned long                    imageSize;
    typedef struct local_error_mgr  *local_error_ptr;
    struct local_error_mgr          jerr;
    struct jpeg_decompress_struct   cinfo;
    JSAMPARRAY                      imagebuffer;

    int                             row_stride;

    cinfo.err = jpeg_std_error(&jerr.pub);
    if(setjmp(jerr.setjmp_buffer))
    {
        jpeg_destroy_decompress(&cinfo);
        return 0;
    }

    jpeg_create_decompress(&cinfo);
    jpeg_memory_src(&cinfo, buffer, memSize);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);

    switch(cinfo.output_components)
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

    if(image->set(pixelFormat, cinfo.output_width, cinfo.output_height))
    {
        imageSize = image->getSize();
        destData = image->getData() + imageSize;
        row_stride = cinfo.output_width * cinfo.output_components;
        imagebuffer = (*cinfo.mem->alloc_sarray) ((j_common_ptr) & cinfo, JPOOL_IMAGE, row_stride, 1);
        while(cinfo.output_scanline < cinfo.output_height)
        {
            destData -= row_stride;
            jpeg_read_scanlines(&cinfo, imagebuffer, 1);
            memcpy(destData, *imagebuffer, row_stride);
        }

        retCode = true;
    }
    else
        retCode = false;

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);

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
Tries to restore the image data from the given memblock.
Returns the amount of data read.
*/
UInt64 JPGImageFileType::storeData(const ImagePtr &OSG_JPG_ARG(image  ), 
                                   UChar8         *OSG_JPG_ARG(buffer ),
                                   Int32           OSG_JPG_ARG(memSize))
{
#ifdef OSG_WITH_JPG
    if((image->getBpp() != 1 && image->getBpp() != 3)
       || image->getDepth() != 1)
    {
        SWARNING <<
            getMimeType() <<
            " JPEG storeData only works for 2D 1 or 3 bpp images " <<
            std::endl;
        return 0;
    }

    struct local_error_mgr
    {
        struct jpeg_error_mgr   pub;
        jmp_buf                 setjmp_buffer;
    };

    typedef struct local_error_mgr  *local_error_ptr;

    struct local_error_mgr          jerr;
    struct jpeg_compress_struct     cinfo;
    JSAMPARRAY                      imagebuffer;
    UChar8                          *data;

    cinfo.err = jpeg_std_error(&jerr.pub);
    if(setjmp(jerr.setjmp_buffer))
    {
        jpeg_destroy_compress(&cinfo);
        return 0;
    }

    jpeg_create_compress(&cinfo);
    jpeg_memory_dest(&cinfo, buffer, memSize);

    cinfo.image_width = image->getWidth();
    cinfo.image_height = image->getHeight();
    cinfo.input_components = image->getBpp();
    cinfo.in_color_space = (image->getBpp() == 1) ? JCS_GRAYSCALE : JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, 90, TRUE);
    jpeg_start_compress(&cinfo, TRUE);

    imagebuffer = &data;
    while(cinfo.next_scanline < cinfo.image_height)
    {
        data = image->getData() +
            (image->getHeight() - 1 - cinfo.next_scanline) *
            image->getWidth() *
            image->getBpp();
        jpeg_write_scanlines(&cinfo, imagebuffer, 1);
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);

    return jpeg_mem.dataSize;

#else
    SWARNING <<
        getMimeType() <<
        " write is not compiled into the current binary " <<
        std::endl;
    return false;
#endif
}

//-------------------------------------------------------------------------
/*!
Constructor used for the singleton object
*/
JPGImageFileType::JPGImageFileType( const Char8 *mimeType,
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
JPGImageFileType::JPGImageFileType(const JPGImageFileType &obj) :
    ImageFileType(obj)
{
    return;
}

//-------------------------------------------------------------------------
/*!
Destructor
*/
JPGImageFileType::~JPGImageFileType(void)
{
    return;
}
