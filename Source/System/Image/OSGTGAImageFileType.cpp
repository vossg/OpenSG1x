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
#include "OSGBaseFunctions.h"

#include "OSGTGAImageFileType.h"

#ifdef OSG_WITH_TGA
#include <tiffio.h>
#endif
#include <OSGLog.h>


OSG_USING_NAMESPACE


/*! \class osg::TGAImageFileType 
    \ingroup GrpSystemImage

Image File Type to read/write and store/restore Image objects as 
TGA data.

All the type specific code is included in the class. Does
not depend on external libs.
        
    
*/

// Static Class Varible implementations:
static const Char8 *suffixArray[] = {
  "tga"
};


void TGAImageFileType::readHeader(std::istream &in, TGAHeader &header)
{
    UInt8 dum[18];
    
    in.read(reinterpret_cast<char *>(dum), 18);

    header.idLength      = dum[ 0];
    header.colorMapType  = dum[ 1];
    header.imageType     = dum[ 2];
    header.cmapEntrySize = dum[ 7];
    header.depth         = dum[16];
    header.descriptor    = dum[17];
   
    if(osgIsBigEndian())
    {
        header.cmapFirst  = dum[ 4] + dum[ 3] * 256;
        header.cmapLength = dum[ 6] + dum[ 5] * 256;
        header.xOrigin    = dum[ 9] + dum[ 8] * 256;
        header.yOrigin    = dum[11] + dum[10] * 256;
        header.width      = dum[13] + dum[12] * 256;
        header.height     = dum[15] + dum[14] * 256;
    }
    else
    {
        header.cmapFirst  = dum[ 3] + dum[ 4] * 256;
        header.cmapLength = dum[ 5] + dum[ 6] * 256;
        header.xOrigin    = dum[ 8] + dum[ 9] * 256;
        header.yOrigin    = dum[10] + dum[11] * 256;
        header.width      = dum[12] + dum[13] * 256;
        header.height     = dum[14] + dum[15] * 256;
    }
}

bool TGAImageFileType::readCompressedImageData(std::istream &in, Image &image)
{
    UInt32 npix = image.getWidth() * image.getHeight();
    UInt8   rep;
    UChar8 *data = image.getData();
    UInt16 bpp = image.getBpp();
    UChar8 r,g,b,a;
        
    while(npix)
    {
        in.read(reinterpret_cast<char *>(&rep), 1);
        
        if(rep & 0x80)
        {
            rep = (rep & 0x7f) + 1;
            npix -= rep;
            
            switch(image.getPixelFormat())
            {
                case Image::OSG_L_PF:
                    in.read(reinterpret_cast<char *>(&a), 1);
                    while(rep--)
                    {
                        *data++ = a;
                    }
                    break;
                case Image::OSG_RGB_PF:     
                    in.read(reinterpret_cast<char *>(&b), 1);
                    in.read(reinterpret_cast<char *>(&g), 1);
                    in.read(reinterpret_cast<char *>(&r), 1);
                    while(rep--)
                    {
                        *data++ = b;
                        *data++ = g;
                        *data++ = r;
                    }
                    break;
                case Image::OSG_RGBA_PF:
                    in.read(reinterpret_cast<char *>(&b), 1);
                    in.read(reinterpret_cast<char *>(&g), 1);
                    in.read(reinterpret_cast<char *>(&r), 1);
                    in.read(reinterpret_cast<char *>(&a), 1);
                    while(rep--)
                    {
                        *data++ = b;
                        *data++ = g;
                        *data++ = r;
                        *data++ = a;
                    }
                    break;
                default:
                    FWARNING(("TGA: unknown pixel "
                              "format!?!\n"));
                    return false;
            }
        }
        else // raw packet
        {
            rep = (rep & 0x7f) + 1;
            in.read(reinterpret_cast<char *>(data), bpp * rep);
            data += rep * bpp;
            npix -= rep;
        }   
    }
    return true;
}


TGAImageFileType TGAImageFileType::_the(suffixArray, sizeof(suffixArray));


//-------------------------------------------------------------------------
/*!
Tries to fill the image object with the data read from
the given fileName. Returns true on success.
*/
bool TGAImageFileType::read(      Image &image, 
                            const Char8 *fileName)
{
    std::ifstream  in(fileName, std::ios::in | std::ios::binary);
    
    if(! in.rdbuf()->is_open())
    {
        FWARNING(("Error opening TGA file %s!\n", fileName));
        return false;
    }

    TGAHeader header;   
    readHeader(in, header);
    
    Image::PixelFormat format = Image::OSG_INVALID_PF;
 
    bool    compressed = header.imageType & 0x8;
    
    switch(header.imageType & ~0x8)
    {
    case 1:     FWARNING(("TGA: 8-bit image not supported!\n"));
                break;
                
    case 2:     switch(header.depth)
                {
                case 24:    format = Image::OSG_RGB_PF;
                            break;
                case 32:    format = Image::OSG_RGBA_PF;
                            break;
                default:    FWARNING(("TGA: Unknown pixel depth %s!\n", 
                                    header.depth));
                            break;
                }
                break;
                
    case 3:     format = Image::OSG_L_PF;
                break;
    }

    if(format == Image::OSG_INVALID_PF)
    {
       FWARNING(("Unsupported image type for TGA file %s!\n", fileName));
       return false; 
    }
    
    image.set(format, header.width, header.height);

    // read the image ID
    UInt8 imageid[256];
    in.read(reinterpret_cast<char *>(imageid), header.idLength);
    imageid[header.idLength] = 0;
    
    FDEBUG(("TGA: Image ID '%s'\n", imageid));
    
    // read color map data
    if(header.colorMapType == 1)
    {
        UInt32 len = osgMin(header.cmapEntrySize / 3, 8) * header.cmapLength;
        
        UInt8 * dum = new UInt8 [len];
        
        in.read(reinterpret_cast<char *>(dum), len);
    
        delete [] dum;
    }
    
    // read image data
    if(compressed)
    {
        if(!readCompressedImageData(in, image))
        {
            FWARNING(("Unsupported image type for TGA file %s!\n", fileName));
            return false; 
        }
    }
    else
    {
        in.read(reinterpret_cast<char *>(image.getData()), 
                static_cast<int>(image.getSize()));
    }

    // check origin
    switch(header.descriptor & 0x30)
    {
    case 0x00:  // bottom left, ok!
                break;
    case 0x10:  // bottom right
    case 0x20:  // top left
    case 0x30:  // top right
                FWARNING(("TGA: origin 0x%d not supported!\n", 
                          header.descriptor & 0x30));
                return false;
    }

    // do BGR -> RGB swap, as GL_BGR_EXT is not supported everywhere
    if(image.getPixelFormat() == Image::OSG_RGB_PF ||
       image.getPixelFormat() == Image::OSG_RGBA_PF)
    {
        UChar8 *d    = image.getData(), dum;
        UInt32  npix = image.getWidth() * image.getHeight();
        UInt8   bpp  = image.getBpp();
        
        while(npix--)
        {
            dum  = d[2];
            d[2] = d[0];
            d[0] = dum;
            d += bpp;
        }
    }
   
    return true;
}

//-------------------------------------------------------------------------
/*!
Tries to write the image object to the given fileName.
Returns true on success.
*/
bool TGAImageFileType::write(const Image &OSG_CHECK_ARG(image),
                             const Char8 *OSG_CHECK_ARG(fileName))
{
    SWARNING <<
        getMimeType() <<
        " write is not compiled into the current binary " <<
        std::endl;

    return true;
}

//-------------------------------------------------------------------------
/*!
Constructor used for the singleton object
*/
TGAImageFileType::TGAImageFileType(const Char8 *suffixArray[],
                                   UInt16 suffixByteCount) :
    ImageFileType(suffixArray, suffixByteCount)
{
    return;
}

//-------------------------------------------------------------------------
/*!
Dummy Copy Constructor
*/
TGAImageFileType::TGAImageFileType(const TGAImageFileType &obj) :
    ImageFileType(obj)
{
    return;
}

//-------------------------------------------------------------------------
/*!
Destructor
*/
TGAImageFileType::~TGAImageFileType(void)
{
    return;
}
