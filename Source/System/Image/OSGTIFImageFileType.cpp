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

#ifdef __hpux // prevent int32 clash (model.h/tiff.h)  
#define _INT32
#endif

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "OSGTIFImageFileType.h"

#ifdef OSG_WITH_TIF
#include <tiffio.h>
#endif
#include <OSGLog.h>

#ifndef OSG_DO_DOC
#    ifdef OSG_WITH_TIF
#        define OSG_TIF_ARG(ARG) ARG
#    else
#        define OSG_TIF_ARG(ARG)
#    endif
#else
#    define OSG_TIF_ARG(ARG) ARG
#endif


OSG_USING_NAMESPACE


/*! \class osg::TIFImageFileType 
    \ingroup GrpSystemImage
  
Image File Type to read/write and store/restore Image objects as
TIF (tif/tiff suffix) data.

To be able to load TIFF images you need the IJG TIFF library, 
(check the Prerequisites page on www.opensg.org). 
The lib comes with all Linux distributions.

You have to --enable-tif in the configure line to enable
the singleton object.
      
*/

// Static Class Varible implementations:
static const Char8 *suffixArray[] = {
  "tif", "tiff"
};

TIFImageFileType TIFImageFileType:: _the("tiff",
                                         suffixArray, sizeof(suffixArray),
                                         OSG_READ_SUPPORTED | 
                                         OSG_WRITE_SUPPORTED);

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
 *  Classvariables
 *****************************/

/********************************
 *  Class methodes
 *******************************/

//-------------------------------------------------------------------------
/*!
Class method to get the singleton Object
*/
TIFImageFileType& TIFImageFileType::the (void)
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
bool TIFImageFileType::read(      ImagePtr &OSG_TIF_ARG(image), 
                            const Char8    *OSG_TIF_ARG(fileName))
{
    bool    valid = false;

#ifdef OSG_WITH_TIF
    TIFF    *in = TIFFOpen(fileName, "r");
    UChar8  *data = 0, *line = 0, *dest;
    UInt32  w, h, u, v;
    UInt16  bpp;
    Char8   errorMessage[1024];
    UInt16  *sampleinfo;
    UInt16  extrasamples;
    UInt16  si;
    UInt16  red, green, blue, alpha;

    if(in)
    {
        TIFFGetField(in, TIFFTAG_IMAGEWIDTH, &w);

        TIFFGetField(in, TIFFTAG_IMAGELENGTH, &h);

        TIFFGetFieldDefaulted(in, TIFFTAG_SAMPLESPERPIXEL, &bpp);

        if(bpp == 4)
        {   // accept unspecified extra samples as associated alpha
            TIFFGetFieldDefaulted(in, TIFFTAG_EXTRASAMPLES, &extrasamples,
                                  &sampleinfo);

            if(sampleinfo && sampleinfo[0] == EXTRASAMPLE_UNSPECIFIED)
            {
                si = EXTRASAMPLE_ASSOCALPHA;
                TIFFSetField(in, TIFFTAG_EXTRASAMPLES, 1, &si);
            }
        }

        data = new UChar8[w * h * 4];
        if(TIFFRGBAImageOK(in, errorMessage) &&
           TIFFReadRGBAImage(in, w, h, (uint32 *) data, 1))
            valid = true;
        else
        {
            SWARNING << "Tiff reader failed: " << errorMessage << std::endl;
            valid = false;
        }

        if(valid)
        {
            Image::PixelFormat  type;
            switch(bpp)
            {
            case 1:
                type = Image::OSG_L_PF;
                break;
            case 2:
                type = Image::OSG_LA_PF;
                break;
            case 3:
                type = Image::OSG_RGB_PF;
                break;
            case 4:
                type = Image::OSG_RGBA_PF;
                break;
            }

            image->set(type, w, h);
            dest = image->getData();

#if defined(__linux) || defined(_WIN32)
            red = 0;
            green = 1;
            blue = 2;
            alpha = 3;

#else
            red = 3;
            green = 2;
            blue = 1;
            alpha = 0;
#endif
            for(v = 0; v < h; v++)
            {
                line = data + ((v) * (w * 4));
                for(u = 0; u < w; u++)
                {
                    switch(bpp)
                    {
                    case 4:
                        *dest++ = line[red];
                        *dest++ = line[green];
                        *dest++ = line[blue];
                        *dest++ = line[alpha];
                        break;
                    case 3:
                        *dest++ = line[red];
                        *dest++ = line[green];
                        *dest++ = line[blue];
                        break;
                    case 2:
                        *dest++ = line[red];
                        *dest++ = line[green];
                        break;
                    case 1:
                        *dest++ = line[red];
                        break;
                    }

                    line += 4;
                }
            }

            TIFFClose(in);
            delete[] data;
            data = 0;
        }
    }

#else
    SWARNING <<
        getMimeType() <<
        " read is not compiled into the current binary " <<
        std::endl;
#endif
    return valid;
}

//-------------------------------------------------------------------------
/*!
Tries to write the image object to the given fileName.
Returns true on success.
*/
bool TIFImageFileType::write(const ImagePtr &OSG_TIF_ARG(image),
                             const Char8    *OSG_TIF_ARG(fileName))
{
    bool                retCode = false;

#ifdef OSG_WITH_TIF
    TIFF                *out = TIFFOpen(fileName, "w");
    int                 lineSize = image->getWidth() * image->getBpp();
    int                 photometric, samplesPerPixel;
    const UChar8       *data;
    int                 row;

    // TODO: implemet all cases correct
    switch(image->getBpp())
    {
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

    if(out)
    {
        TIFFSetField(out, TIFFTAG_IMAGEWIDTH, image->getWidth());
        TIFFSetField(out, TIFFTAG_IMAGELENGTH, image->getHeight());
        TIFFSetField(out, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
        TIFFSetField(out, TIFFTAG_SAMPLESPERPIXEL, samplesPerPixel);
        TIFFSetField(out, TIFFTAG_BITSPERSAMPLE, 8);
        TIFFSetField(out, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
        TIFFSetField(out, TIFFTAG_PHOTOMETRIC, photometric);
        TIFFSetField(out, TIFFTAG_COMPRESSION, COMPRESSION_NONE);
        TIFFSetField(out, TIFFTAG_ROWSPERSTRIP, TIFFDefaultStripSize(out, 0));

        for(row = 0; row < image->getHeight(); row++)
        {
            data = image->getData() + ((image->getHeight() - row - 1) * lineSize);
            if(TIFFWriteScanline(out, 
                                 (tdata_t) const_cast<UChar8 *>(data), 
                                 row, 
                                 0) < 0)
                break;
        }

        TIFFClose(out);
    }

#else
    SWARNING <<
        getMimeType() <<
        " write is not compiled into the current binary " <<
        std::endl;
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

//-------------------------------------------------------------------------
/*!
Constructor used for the singleton object
*/
TIFImageFileType::TIFImageFileType(const Char8 *mimeType,
                                   const Char8 *suffixArray[],
                                   UInt16 suffixByteCount,
                                   UInt32 flags) :
    ImageFileType(mimeType,suffixArray, suffixByteCount, flags)
{
    return;
}

//-------------------------------------------------------------------------
/*!
Dummy Copy Constructor
*/
TIFImageFileType::TIFImageFileType(const TIFImageFileType &obj) :
    ImageFileType(obj)
{
    return;
}

//-------------------------------------------------------------------------
/*!
Destructor
*/
TIFImageFileType::~TIFImageFileType(void)
{
    return;
}
