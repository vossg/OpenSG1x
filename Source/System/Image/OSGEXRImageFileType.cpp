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
//      Includes
//-------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <memory.h>

#include <OSGConfig.h>

#include <iostream>
#include <fstream>
#include <errno.h>

#ifdef _WIN32
    #ifdef min
        #undef min
    #endif
    #ifdef max
        #undef max
    #endif
#endif

#ifdef OSG_WITH_IMF
 #include <OpenEXR/Iex.h>
 #include <OpenEXR/ImathBox.h>
 #include <OpenEXR/ImfIO.h>
 #include <OpenEXR/ImfHeader.h>
 #include <OpenEXR/ImfVersion.h>
 #include <OpenEXR/ImfArray.h>
 #include <OpenEXR/ImfRgba.h>
 #include <OpenEXR/ImfRgbaFile.h>
 #include <OpenEXR/ImfStandardAttributes.h>
#endif

#include <OSGLog.h>
#include <OSGImageFileHandler.h>
#include <OSGPathHandler.h>
#include <OSGFileSystem.h>

#include "OSGEXRImageFileType.h"

OSG_USING_NAMESPACE


/*! \class osg::EXRImageFileType
    \ingroup GrpSystemImage

Image File Type to read/write and store/restore Image objects as EXR data.
Does depend on external libs, namely OpenEXR (by ILM).

Needs to be build with OSG_WITH_IMF

 */

/*****************************
 *   Types
 *****************************/
// Static Class Varible implementations:

static const Char8 *suffixArray[] =
{
    "exr"
};

EXRImageFileType EXRImageFileType::_the( "image/x-exr",
                                         suffixArray, sizeof(suffixArray),
                                         OSG_READ_SUPPORTED |
                                         OSG_WRITE_SUPPORTED );


/*****************************
 *    Classvariables
 *****************************/


/********************************
 *    Class methodes
 *******************************/

#ifdef OSG_WITH_IMF

//-------------------------------------------------------------------------
/** class StdIFStream -- an implementation of
    class IStream based on class std::istream
 */
class StdIStream : public Imf::IStream
{
  public:
    /** A constructor that uses a std::istream that has already
        been opened by the caller.  The StdIStream's destructor
        will not close the std::istream.
     */
    StdIStream(std::istream &is, const char fileName[]);
    virtual ~StdIStream();

    virtual bool       read(char c[], int n);
    virtual Imf::Int64 tellg();
    virtual void       seekg(Imf::Int64 pos);
    virtual void       clear();

  private:
    bool checkError();

    std::istream *_is;
};

//-------------------------------------------------------------------------
/** class StdOStream -- an implementation of
    class OStream based on class std::ostream
 */
class StdOStream : public Imf::OStream
{
  public:
    /** A constructor that uses a std::ostream that has already
        been opened by the caller.  The StdOStream's destructor
        will not close the std::ostream.
     */
    StdOStream(std::ostream &os, const char fileName[]);
    virtual ~StdOStream();

    virtual void       write(const char c[], int n);
    virtual Imf::Int64 tellp();
    virtual void       seekp(Imf::Int64 pos);

  private:
    void checkError();

    std::ostream *_os;
};

//-------------------------------------------------------------------------
StdIStream::StdIStream(std::istream &is, const char fileName[]) :
    Imf::IStream(fileName), _is(&is) { }

StdIStream::~StdIStream() { }

bool StdIStream::read(char c[], int n)
{
    if (!*_is)
       throw Iex::InputExc("Unexpected end of file.");

    errno = 0;
    _is->read(c, n);

    return checkError();
}

Imf::Int64 StdIStream::tellg()
{
    return std::streamoff(_is->tellg());
}

void StdIStream::seekg(Imf::Int64 pos)
{
    _is->seekg(pos);
    checkError();
}

void StdIStream::clear()
{
    _is->clear();
}

bool StdIStream::checkError()
{
    if (!*_is)
    {
        if (errno)
            Iex::throwErrnoExc();

        _is->clear(std::ios_base::goodbit);
        return false;
    }
    return true;
}

//-------------------------------------------------------------------------
StdOStream::StdOStream(std::ostream &os, const char fileName[]) :
    Imf::OStream(fileName), _os(&os) { }

StdOStream::~StdOStream() { }

void StdOStream::write(const char c[], int n)
{
    errno = 0;
    _os->write(c, n);
    checkError();
}

Imf::Int64 StdOStream::tellp()
{
    return std::streamoff(_os->tellp());
}

void StdOStream::seekp(Imf::Int64 pos)
{
    _os->seekp(pos);
    checkError();
}

void StdOStream::checkError()
{
    if (!*_os)
    {
        if (errno)
            Iex::throwErrnoExc();
        throw Iex::ErrnoExc ("Write failed.");
    }
}

#endif  //OSG_WITH_IMF

//-------------------------------------------------------------------------
/*!
Class method to get the singleton Object
*/
EXRImageFileType& EXRImageFileType::the (void)
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
bool EXRImageFileType::read(ImagePtr &image, std::istream &is, const std::string &mimetype)
{
#ifdef OSG_WITH_IMF
    if (!is.good())
        return false;

    const char *dummy = "";
    StdIStream file(is, dummy);

    Imf::Int64 pos = file.tellg();

    bool check = isOpenExrFile(is);

    file.seekg(pos);

    if (!check)
    {
        FFATAL(( "Wrong format, no %s image given!\n",
                  mimetype.c_str() ));
        return false;
    }

    // TODO: check for mipmap levels,
    // look if line order is s.th. else than INCREASING_Y
    try
    {
        Int32 width, height, numImg = 1;
        Imf::RgbaInputFile stream(file);

        Imath::Box2i dw = stream.dataWindow();
        Imf::Array2D<Imf::Rgba> pixels;

        const Imf::Header &header = stream.header();
        const Imf::LineOrder &order = header.lineOrder();

        const Imf::EnvmapAttribute *envmap =
                   header.findTypedAttribute<Imf::EnvmapAttribute>("envmap");

        width  = dw.max.x - dw.min.x + 1;
        height = dw.max.y - dw.min.y + 1;

        pixels.resizeErase(height, width);

        if (envmap && envmap->value() == Imf::ENVMAP_CUBE)
        {
            numImg = 6;
            height /= numImg;

            if (width != height)
            {
                FFATAL(( "Cubemaps must have squared size, but w=%d and h=%d!\n",
                          width, height ));
                return false;
            }
        }

        stream.setFrameBuffer(&pixels[0][0] - dw.min.x - dw.min.y * width, 1, width);
        stream.readPixels(dw.min.y, dw.max.y);

        image->set( Image::OSG_RGBA_PF, width, height, 1, 1, 1, 0, 0,
                    Image::OSG_FLOAT16_IMAGEDATA, true, numImg );
        image->clearHalf();

        Real16 *data = (Real16*)(image->getData());

        for (Int32 side=numImg-1; side >=0; side--)
        {
            Int32 i, j, size = side * width * height * 4;

            for (Int32 y=side*height; y<(side+1)*height; y++)
            {
                for (Int32 x=0; x<width; x++)
                {
                    if (numImg == 1 || side == 2 || side == 3)
                    {
                        i = (2 * side + 1) * height - (y + 1); // new y
                        j = x;
                    }
                    else
                    {
                        i = y;
                        j = width - x - 1; // new x
                    }

                    *(data + size++) = (Real16)pixels[i][j].r;
                    *(data + size++) = (Real16)pixels[i][j].g;
                    *(data + size++) = (Real16)pixels[i][j].b;
                    *(data + size++) = (Real16)pixels[i][j].a;
                }
            }
        }

        return true;
    }
    catch(std::exception &e)
    {
        FFATAL(( "Error while trying to read OpenEXR Image from stream: %s\n",
                  e.what() ));
        return false;
    }

#else
    SWARNING << getMimeType()
             << " read is not compiled into the current binary "
             << std::endl;
    return false;
#endif
}

//-------------------------------------------------------------------------
/*!
    Tries to write the image object to the given output stream.
    Returns true on success.
*/
bool EXRImageFileType::write(const ImagePtr &image, std::ostream &os, const std::string &mimetype)
{
#ifdef OSG_WITH_IMF
    if (!os.good())
        return false;

    if(image->getDataType() != Image::OSG_FLOAT16_IMAGEDATA)
    {
        FWARNING(("EXRImageFileType::write: Image has non float data type!\n"));
        return false;
    }
    if (image->getSideCount() == 6)
    {
        FWARNING(("EXRImageFileType::write: NYI for cubemaps\n"));  //TODO
        return false;
    }

    try
    {
        Int32 width  = image->getWidth();
        Int32 height = image->getHeight();

        const char *dummy = "";
        StdOStream file(os, dummy);
        Imf::Header header(width, height);

        Imf::RgbaOutputFile stream(file, header, Imf::WRITE_RGBA);

        Imf::Rgba *pixels = new Imf::Rgba[width * height];

        Real16 *data = ((Real16*)(image->getData()));
        Int32 size = width * height * 4;

        for (Int32 y=0; y<height; y++)
        {
            for (Int32 x=width-1; x>=0; x--)
            {
                pixels[width * y + x].a = *(data + --size);
                pixels[width * y + x].b = *(data + --size);
                pixels[width * y + x].g = *(data + --size);
                pixels[width * y + x].r = *(data + --size);
            }
        }

        stream.setFrameBuffer(pixels, 1, (int)width);
        stream.writePixels(height);

        delete [] pixels;

        return true;
    }
    catch(std::exception &e)
    {
        FFATAL(( "Error while trying to write OpenEXR Image from stream: %s\n",
                  e.what() ));
        return false;
    }

#else
    SWARNING << getMimeType()
             << " write is not compiled into the current binary "
             << std::endl;
    return false;
#endif
}

//-------------------------------------------------------------------------
/*!
    Tries to restore the image data from the given memblock.
    Returns the amount of data read.
*/
UInt64 EXRImageFileType::restoreData(      ImagePtr &image,
                                     const UChar8   *buffer,
                                           Int32   OSG_CHECK_ARG(memSize) )
{
    image->setData(buffer);

    return image->getSize();
}

//-------------------------------------------------------------------------
/*!
    Tries to store the image data to the given memblock.
    Returns the amount of data written.
*/
UInt64 EXRImageFileType::storeData(const ImagePtr &image,
                                         UChar8   *buffer,
                                         Int32     OSG_CHECK_ARG(memSize))
{
    UInt32 dataSize = image->getSize();
    const UChar8 *src = image->getData();

    if ( dataSize && src && buffer )
        memcpy( buffer, src, dataSize);

    return dataSize;
}

//-------------------------------------------------------------------------
/*!
    Constructor used for the singleton object
*/
EXRImageFileType::EXRImageFileType ( const Char8 *mimeType,
                                     const Char8 *suffixArray[],
                                     UInt16 suffixByteCount,
                                     UInt32 flags  )
    : ImageFileType ( mimeType, suffixArray, suffixByteCount, flags )
{
    FINFO(( "EXRImageFileType: %s\n", mimeType));

    // TODO; needed for initialization of the library's global variables
    //Imf::staticInitialize();
}

//-------------------------------------------------------------------------
/*!
    Destructor
*/
EXRImageFileType::~EXRImageFileType(void)
{
}

//-------------------------------------------------------------------------
/*!
    Quick test for checking if file format is correct
*/
bool EXRImageFileType::isOpenExrFile(std::istream &is)
{
#ifdef OSG_WITH_IMF
    char bytes[4];

    is.read(bytes, sizeof(bytes));

    return !!is && Imf::isImfMagic(bytes);

#else
    return false;
#endif
}
