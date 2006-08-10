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

#ifdef OSG_WITH_JASPER
#include <jasper/jasper.h>
#endif // OSG_WITH_JASPER

#include "OSGJP2ImageFileType.h"
#include <OSGLog.h>

#include <iostream>

#ifndef OSG_DO_DOC
#    ifdef OSG_WITH_JASPER
#        define OSG_JP2_ARG(ARG) ARG
#    else
#        define OSG_JP2_ARG(ARG)
#    endif
#else
#    define OSG_JP2_ARG(ARG) ARG
#endif

OSG_USING_NAMESPACE

/*! \class osg::JP2ImageFileType 
    \ingroup GrpSystemImage

Image File Type to read/write and store/restore Image objects as
JPEG-2000 data.

To be able to load JP2 images you need the Jasper library.
The lib comes with all Linux distributions.
http://www.ece.uvic.ca/~mdadams/jasper/

You have to --enable-jasper in the configure line to enable
the singleton object.

@author Patrick D&auml;hne    
*/

#ifdef OSG_WITH_JASPER

/* Read characters from a file object. */
static int readIStream(jas_stream_obj_t *obj, char *buf, int cnt)
{
    std::istream *is = reinterpret_cast<std::istream*>(obj);
    is->read(buf, cnt);
    return is->gcount();
}

/* Write characters to a file object. */
static int writeIStream(jas_stream_obj_t *obj, char *buf, int cnt)
{
    // We cannot write into an input stream
    return 0;
}

/* Set the position for a file object. */
static long seekIStream(jas_stream_obj_t *obj, long offset, int origin)
{
    std::istream *is = reinterpret_cast<std::istream*>(obj);
    std::ios_base::seekdir seekdir;
    switch (origin)
    {
    case SEEK_SET: seekdir = std::ios::beg; break;
    case SEEK_CUR: seekdir = std::ios::cur; break;
    case SEEK_END: seekdir = std::ios::end; break;
    default:
        return -1;
    }
    is->seekg(offset, seekdir);
    return is->tellg();
}

/* Close a file object. */
static int closeIStream(jas_stream_obj_t *obj)
{
    // We do not really close the input stream
    return 0;
}

static jas_stream_ops_t istream_ops =
{
    readIStream,
    writeIStream,
    seekIStream,
    closeIStream
};

#endif // OSG_WITH_JASPER

/*****************************
 *   Types
 *****************************/
/*****************************
 *  Classvariables
 *****************************/
// Static Class Varible implementations:
static const Char8                  *suffixArray[] = { "jp2" };

JP2ImageFileType JP2ImageFileType:: _the("image/jpeg2000",
                                         suffixArray, sizeof(suffixArray),
                                         OSG_READ_SUPPORTED);

/********************************
 *  Class methodes
 *******************************/


//-------------------------------------------------------------------------
/*!
Class method to get the singleton Object
*/
JP2ImageFileType& JP2ImageFileType::the (void)
{
    return _the;
}

/*******************************
*public
*******************************/

//-------------------------------------------------------------------------
/*!
Tries to fill the image object with the data read from
the given input stream. Returns true on success.
*/
bool JP2ImageFileType::read(ImagePtr &OSG_JP2_ARG(image), std::istream &OSG_JP2_ARG(is),
                            const std::string &OSG_JP2_ARG(mimetype))
{
#ifdef OSG_WITH_JASPER

    // Initialize the JasPer library
    if (jas_init() != 0)
        return false;

    // Initialize a JasPer input stream. This is a silly hack, because
    // there is no way in the JasPer to create custom streams.
    jas_stream_t *instream = reinterpret_cast<jas_stream_t*>(jas_malloc(sizeof(jas_stream_t)));
    if (instream == 0)
    {
        jas_cleanup();
        return false;
    }
    instream->openmode_ = JAS_STREAM_READ | JAS_STREAM_BINARY;
    instream->bufmode_ = JAS_STREAM_UNBUF;
    instream->flags_ = 0;
    instream->bufbase_ = instream->tinybuf_;
    instream->bufstart_ = &instream->bufbase_[JAS_STREAM_MAXPUTBACK];
    instream->bufsize_ = 1;
    instream->ptr_ = instream->bufstart_;
    instream->cnt_ = 0;
    instream->ops_ = &istream_ops;
    instream->obj_ = &is;
    instream->rwcnt_ = 0;
    instream->rwlimit_ = -1;

    // Try to load the image from the stream
    jas_image_t *jasimage = jas_image_decode(instream, -1, 0);

    // We do not need the stream anymore
    jas_stream_close(instream);

    // Check if we successfully loaded the image
    if (jasimage == 0)
    {
        jas_cleanup();
        return false;
    }

    // Convert the image to RGB
    jas_cmprof_t *outprof = jas_cmprof_createfromclrspc(JAS_CLRSPC_SRGB);
    if (outprof == 0)
    {
        jas_image_destroy(jasimage);
        jas_cleanup();
        return false;
    }
    jas_image_t *altimage = jas_image_chclrspc(jasimage, outprof, JAS_CMXFORM_INTENT_PER);

    // We do not need the original image and the color profile anymore
    jas_image_destroy(jasimage);
    jas_cmprof_destroy(outprof);

    // Check if we successfully converted the image
    if (altimage == 0)
    {
        jas_cleanup();
        return false;
    }

    // Get the indices of the RGB components
    int cmptlut[3];
    cmptlut[0] = jas_image_getcmptbytype(altimage, JAS_IMAGE_CT_COLOR(JAS_CLRSPC_CHANIND_RGB_R));
    cmptlut[1] = jas_image_getcmptbytype(altimage, JAS_IMAGE_CT_COLOR(JAS_CLRSPC_CHANIND_RGB_G));
    cmptlut[2] = jas_image_getcmptbytype(altimage, JAS_IMAGE_CT_COLOR(JAS_CLRSPC_CHANIND_RGB_B));
    if ((cmptlut[0] < 0) || (cmptlut[0] < 0) || (cmptlut[0] < 0))
    {
        jas_image_destroy(altimage);
        jas_cleanup();
        return false;
    }

    // Get width and height of the image
    jas_image_coord_t width = jas_image_cmptwidth(altimage, cmptlut[0]);
    jas_image_coord_t height = jas_image_cmptheight(altimage, cmptlut[0]);
    if ((jas_image_cmptwidth(altimage, cmptlut[1]) != width) ||
        (jas_image_cmptwidth(altimage, cmptlut[2]) != width) ||
        (jas_image_cmptheight(altimage, cmptlut[1]) != height) ||
        (jas_image_cmptheight(altimage, cmptlut[2]) != height))
    {
        jas_image_destroy(altimage);
        jas_cleanup();
        return false;
    }

    // Initialize the OpenSG image
    if (image->set(Image::OSG_RGB_PF, width, height) == false)
    {
        jas_image_destroy(altimage);
        jas_cleanup();
        return false;
    }

    // Copy the image components into the OpenSG image buffer. This is
    // incredibly slow, but there seems to be no other way to do this.
    unsigned char *scanline = image->getData() + image->getSize();
    int row_stride = width * 3;
    for (jas_image_coord_t y = 0; y < height; ++y)
    {
        scanline -= row_stride;
        unsigned char *dst = scanline;
        for (jas_image_coord_t x = 0; x < width; ++x)
        {
            for (int c = 0; c < 3; ++c)
            {
                int sample = jas_image_readcmptsample(altimage, cmptlut[c], x, y);
                sample <<= 16 - jas_image_cmptprec(altimage, cmptlut[c]);
                if (sample < 0)
                    sample = 0;
                else if (sample > 65535)
                    sample = 65535;
                *dst++ = sample >> 8;
            }
        }
    }

    // Destroy the image
    jas_image_destroy(altimage);

    // Deinitialize the JasPer library
    jas_cleanup();

    return true;

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
Tries to determine the mime type of the data provided by an input stream
by searching for magic bytes. Returns the mime type or an empty string
when the function could not determine the mime type.
*/
std::string JP2ImageFileType::determineMimetypeFromStream(std::istream &is)
{
    char filecode[8];
    is.read(filecode, 8);
    is.seekg(-8, std::ios::cur);
    return strncmp(filecode + 4, "jP  ", 4) == 0 ?
        std::string(getMimeType()) : std::string();
}

//-------------------------------------------------------------------------
/*!
Constructor used for the singleton object
*/
JP2ImageFileType::JP2ImageFileType( const Char8 *mimeType,
                                    const Char8 *suffixArray[],
                                    UInt16 suffixByteCount,
                                    UInt32 flags) :
    ImageFileType(mimeType, suffixArray, suffixByteCount, flags)
{}

//-------------------------------------------------------------------------
/*!
Destructor
*/
JP2ImageFileType::~JP2ImageFileType(void) {}
