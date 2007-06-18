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

#include "OSGConfig.h"
#include "OSGBaseFunctions.h"

#include "OSGPSDImageFileType.h"

#include <OSGLog.h>


OSG_USING_NAMESPACE


/*! \class osg::PSDImageFileType
    \ingroup GrpSystemImage

Image File Type to read Image objects as Adobe Photoshop
PSD data.

All the type specific code is included in the class. Does
not depend on external libs.


*/

static UInt32 parseUInt32(char *&ptr)
{
  UInt32 result =
    (static_cast<UInt32>(static_cast<UInt8>(ptr[0])) << 24) |
    (static_cast<UInt32>(static_cast<UInt8>(ptr[1])) << 16) |
    (static_cast<UInt32>(static_cast<UInt8>(ptr[2])) <<  8) |
    (static_cast<UInt32>(static_cast<UInt8>(ptr[3])) <<  0);
  ptr += 4;
  return result;
}

static UInt16 parseUInt16(char *&ptr)
{
  UInt16 result =
    (static_cast<UInt32>(static_cast<UInt8>(ptr[0])) << 8) |
    (static_cast<UInt32>(static_cast<UInt8>(ptr[1])) << 0);
  ptr +=2;
  return result;
}

typedef struct
{
  Int8   signature[4];
  UInt16 version;
  Int8   reserved[6];
  UInt16 channels;
  UInt32 rows;
  UInt32 columns;
  UInt16 depth;
  UInt16 mode;
}
PSDHeader;

static bool readHeader(std::istream &is, PSDHeader &header)
{
  // Read the header into the buffer
  char buffer[26];
  is.read(buffer, 26);
  if (is.gcount() != 26)
    return false;

  // Parse the header
  char *ptr = buffer;
  memcpy(header.signature, ptr, 4);
  ptr += 4;
  header.version = parseUInt16(ptr);
  memcpy(header.reserved, ptr, 6);
  ptr += 6;
  header.channels = parseUInt16(ptr);
  header.rows = parseUInt32(ptr);
  header.columns = parseUInt32(ptr);
  header.depth = parseUInt16(ptr);
  header.mode = parseUInt16(ptr);

  // Check the header
  if (memcmp(header.signature, "8BPS", 4) != 0)
    return false;
  if (header.version != 1)
    return false;

  return true;
}

static bool readColorModeData(std::istream &is, const PSDHeader &header, char *colormap)
{
  // Read the length of the color mode data into the buffer
  char buffer[4];
  is.read(buffer, 4);
  if (is.gcount() != 4)
    return false;

  // Parse the length
  char *ptr = buffer;
  UInt32 length = parseUInt32(ptr);

  // Parse the color palette
  if (header.mode == 2)
  {
    if (length != 768)
      return false;
    length = 0;
    is.read(colormap, 768);
    if (static_cast<UInt32>(is.gcount()) != 768)
      return false;
  }

  // Ignore remaining data
  is.ignore(length);
  if (static_cast<UInt32>(is.gcount()) != length)
    return false;

  return true;
}

static bool readResource(std::istream &is, UInt32 &length, Int16 &transparentIndex)
{
  // Parse type, id, name and size
  if (length < 8)
    return false;
  char buffer[8];
  is.read(buffer, 6);
  if (is.gcount() != 6)
    return false;
  length -= 6;
  char *ptr = buffer + 4;
  UInt16 id = parseUInt16(ptr);
  int c = is.get();
  if (c == EOF)
    return false;
  length -= 1;
  if ((c & 1) == 0)
    ++c;
  if (static_cast<UInt32>(c) > length)
    return false;
  is.ignore(c);
  if (is.gcount() != c)
    return false;
  length -= c;
  ptr = buffer + 4;
  is.read(ptr, 4);
  if (is.gcount() != 4)
    return false;
  length -= 4;
  UInt32 size = parseUInt32(ptr);
  if (size > length)
    return false;

  if (memcmp(buffer, "8BIM", 4) == 0)
  {
    switch (id)
    {
    case 0x417:
      if (size == 2)
      {
        ptr = buffer + 4;
        is.read(ptr, 2);
        if (is.gcount() != 2)
          return false;
        size = 0;
        length -= 2;
        transparentIndex = parseUInt16(ptr);
      }
      break;
    }
  }

  if ((size & 1) != 0)
    ++size;
  is.ignore(size);
  if (static_cast<UInt32>(is.gcount()) != size)
    return false;
  length -= size;

  return true;
}

static bool readImageResources(std::istream &is, Int16 &transparentIndex)
{
  // Read the length of the image resources into the buffer
  char buffer[4];
  is.read(buffer, 4);
  if (is.gcount() != 4)
    return false;

  // Parse the length
  char *ptr = buffer;
  UInt32 length = parseUInt32(ptr);

  // Parse resources
  while (length > 0)
    if (readResource(is, length, transparentIndex) == false)
      return false;

  return true;
}

static bool readLayerAndMaskInformation(std::istream &is)
{
  // Read the length of the layer and mask information into the buffer
  char buffer[4];
  is.read(buffer, 4);
  if (is.gcount() != 4)
    return false;

  // Parse the length
  char *ptr = buffer;
  UInt32 length = parseUInt32(ptr);

  // Ignore data
  is.ignore(length);
  if (static_cast<UInt32>(is.gcount()) != length)
    return false;

  return true;
}

static bool readImageData(std::istream &is, const PSDHeader &header, UInt16 relevantChannels, char *colormap, Int16 &transparentIndex, UInt8 *data)
{
  // Read the compression into the buffer
  std::vector<char> buffer;
  buffer.resize(2);
  char *ptr = &(buffer.front());
  is.read(ptr, 2);
  if (is.gcount() != 2)
    return false;

  // Parse the compression
  UInt16 compression = parseUInt16(ptr);
  if (compression > 1)
    return false;

  // Calculate the bytes per line
  UInt32 bpl = (header.columns * header.depth + 7) / 8;
  UInt32 dstBpl;
  if (header.mode == 2) // Indexed color
    dstBpl = header.columns * (transparentIndex != -1 ? 4 : 3);
  else
    dstBpl = header.columns * relevantChannels;

  // When the image data is compressed, we have to read the
  // lengths of the lines
  std::vector<UInt16> lineLength;
  if (compression == 1)
  {
    UInt32 numLines = header.rows * header.channels;
    lineLength.resize(numLines);
    UInt32 size = numLines * 2;
    buffer.resize(size);
    ptr = &(buffer.front());
    is.read(ptr, size);
    if (static_cast<UInt32>(is.gcount()) != size)
      return false;
    UInt16 maxLength = 0;
    for (UInt32 i = 0; i < numLines; ++i)
    {
      UInt16 length = parseUInt16(ptr);
      lineLength[i] = length;
      if (length > maxLength)
        maxLength = length;
    }
    buffer.resize(maxLength);
  }
  else
    buffer.resize(bpl);

  UInt32 lineNumber = 0;
  std::vector<char> line(bpl);
  UInt8 *dstPtr;
  for (UInt16 c = 0; c < header.channels; ++c)
  {
    dstPtr = data + c + dstBpl * (header.rows - 1);
    for (UInt32 y = 0; y < header.rows; ++y)
    {
      // Read the line
      UInt32 size;
      if (compression == 1)
      {
        ptr = &(buffer.front());
        size = lineLength[lineNumber];
      }
      else
      {
        ptr = &(line.front());
        size = bpl;
      }
      is.read(ptr, size);
      if (static_cast<UInt32>(is.gcount()) != size)
        return false;

      if (c < relevantChannels)
      {
        // Decompress the line
        if (compression == 1)
        {
          UInt32 src = 0, dst = 0;
          while (src < size)
          {
            UInt8 runCount = buffer[src++];
            if (runCount & 0x80)
            {
              runCount = -runCount + 1;
              if (dst + runCount > bpl)
                return false;
              for (; runCount > 0; --runCount)
                line[dst++] = buffer[src];
              ++src;
            }
            else
            {
              ++runCount;
              if (dst + runCount > bpl)
                return false;
              for (; runCount > 0; --runCount)
                line[dst++] = buffer[src++];
            }
          }
          if (dst != bpl)
            return false;
        }

        // Copy the line into the image
        UInt8 *lineDstPtr = dstPtr;
        switch (header.depth)
        {
        case 1:
          for (UInt32 x = 0; x < header.columns; ++x)
          {
            UInt8 v = line[x / 8] & (1 << (7 - (x & 7)));
            *lineDstPtr = v != 0 ? 0 : 255;
            lineDstPtr += relevantChannels;
          }
          break;
        case 8:
          if (header.mode == 2)
            for (UInt32 x = 0; x < header.columns; ++x)
            {
              UInt8 index = line[x];
              *lineDstPtr++ = colormap[index];
              *lineDstPtr++ = colormap[index + 256];
              *lineDstPtr++ = colormap[index + 512];
              if (transparentIndex != -1)
                *lineDstPtr++ = index == transparentIndex ? 0 : 255;
            }
          else
            for (UInt32 x = 0; x < header.columns; ++x)
            {
              *lineDstPtr = line[x];
              lineDstPtr += relevantChannels;
            }
          break;
        case 16:
          for (UInt32 x = 0; x < header.columns; ++x)
          {
            *lineDstPtr = line[x * 2];
            lineDstPtr += relevantChannels;
          }
          break;
        }
      }
      dstPtr -= dstBpl;

      ++lineNumber;
    }
  }

  return true;
}


// Static Class Varible implementations:
static const Char8 *suffixArray[] = {
  "psd"
};

PSDImageFileType PSDImageFileType::_the("image/x-photoshop",
                                        suffixArray, sizeof(suffixArray),
                                        OSG_READ_SUPPORTED);

//-------------------------------------------------------------------------
/*!
Class method to get the singleton Object
*/
PSDImageFileType& PSDImageFileType::the (void)
{
  return _the;
}

//-------------------------------------------------------------------------
/*!
Tries to fill the image object with the data read from
the given input stream. Returns true on success.
*/
bool PSDImageFileType::read(ImagePtr &image, std::istream &is,
                            const std::string &mimetype)
{
    PSDHeader header;
    if (readHeader(is, header) == false)
    {
        FWARNING(("PSD file is corrupt!\n"));
        return false;
    }

    char colormap[768];
    if (readColorModeData(is, header, colormap) == false)
    {
        FWARNING(("PSD file is corrupt!\n"));
        return false;
    }

    Int16 transparentIndex = -1;
    if (readImageResources(is, transparentIndex) == false)
    {
        FWARNING(("PSD file is corrupt!\n"));
        return false;
    }

    if (readLayerAndMaskInformation(is) == false)
    {
        FWARNING(("PSD file is corrupt!\n"));
        return false;
    }

    Image::PixelFormat format = Image::OSG_INVALID_PF;
    UInt16 relevantChannels = header.channels;
    switch (header.mode)
    {
    case 0: // Bitmap (monochrome)
        if ((header.channels != 1) || (header.depth != 1))
            break;
        format = Image::OSG_L_PF;
        break;
    case 1: // Gray-scale
        if ((header.depth != 8) && (header.depth != 16))
            break;
        switch (header.channels)
        {
        case 1:
            format = Image::OSG_L_PF;
            break;
        case 2:
            format = Image::OSG_LA_PF;
            break;
        default:
            break;
        }
        break;
    case 2: // Indexed color (palette color)
        if ((header.channels != 1) || (header.depth != 8))
            break;
        format = transparentIndex != -1 ? Image::OSG_RGBA_PF : Image::OSG_RGB_PF;
        break;
    case 3: // RGB color
        if ((header.depth != 8) && (header.depth != 16))
            break;
        if (header.channels < 3)
            break;
        if (header.channels == 3)
            format = Image::OSG_RGB_PF;
        else
        {
            format = Image::OSG_RGBA_PF;
            relevantChannels = 4;
        }
        break;
    case 4: // CMYK color
        if ((header.depth != 8) && (header.depth != 16))
            break;
        // TODO
        break;
    case 7: // Multichannel color
        // TODO
        break;
    case 8: // Duotone (halftone)
        if (header.depth != 8)
            break;
        switch (header.channels)
        {
        case 1:
            format = Image::OSG_L_PF;
            break;
        case 2:
            format = Image::OSG_LA_PF;
            break;
        default:
            break;
        }
        break;
    case 9: // Lab color
        if ((header.depth != 8) && (header.depth != 16))
            break;
        // TODO
        break;
    default:
        break;
    }

    if (format == Image::OSG_INVALID_PF)
    {
       FWARNING(("Unsupported image type for PSD file!\n"));
       return false;
    }

    image->set(format, header.columns, header.rows);
    UChar8 *data = image->getData();

    if (readImageData(is, header, relevantChannels, colormap, transparentIndex, data) == false)
    {
        FWARNING(("PSD file is corrupt!\n"));
        return false;
    }

    return true;
}

//-------------------------------------------------------------------------
/*!
Tries to determine the mime type of the data provided by an input stream
by searching for magic bytes. Returns the mime type or an empty string
when the function could not determine the mime type.
*/
std::string PSDImageFileType::determineMimetypeFromStream(std::istream &is)
{
    char filecode[4];
    is.read(filecode, 4);
    is.seekg(-4, std::ios::cur);
    return strncmp(filecode, "8BPS", 4) == 0 ?
        std::string(getMimeType()) : std::string();
}

//-------------------------------------------------------------------------
/*!
Constructor used for the singleton object
*/
PSDImageFileType::PSDImageFileType(const Char8 *mimeType,
                                   const Char8 *suffixArray[],
                                   UInt16 suffixByteCount,
                                   UInt32 flags) :
    ImageFileType(mimeType,suffixArray, suffixByteCount, flags)
{}

//-------------------------------------------------------------------------
/*!
Destructor
*/
PSDImageFileType::~PSDImageFileType(void) {}
