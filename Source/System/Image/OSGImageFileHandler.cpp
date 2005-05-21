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
//  Includes          
//-------------------------------
#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <OSGLog.h>
#include <OSGBaseTypes.h>
#include <OSGPathHandler.h>
#include <OSGBaseFunctions.h>
#include <OSGFileSystem.h>

#include "OSGImageFileHandler.h"


OSG_USING_NAMESPACE

/*! \class osg::ImageFileHandler 
    \ingroup GrpSystemImage

Singelton Object/Class which holds all known ImageFileTypes.
The class is used to write/read Image objects to/from
files and to store/restore image data to/from memory blocks.
Utilizes the local pathHandler for file path handler and
construction. The PathHandler can be set from the application.

See \ref PageSystemImage for details.
    
*/

/*****************************
 *   Types
 *****************************/
/*****************************
 *   Classvariables
 *****************************/
ImageFileHandler *ImageFileHandler::_the = 0;
const std::string ImageFileHandler::_fileNameKey("fileName");
const std::string ImageFileHandler::_fullFilePathKey("fullFilePath");

/********************************
 *   Class methodes
 *******************************/

/*******************************
*public
*******************************/

//-------------------------------------------------------------------------
/*!
Method to find a ImageFileHandler for the given mimeType for 
fileName suffix. Returns the ImageFileHandler object or Null.
*/
ImageFileType *ImageFileHandler::getFileType(const char *mimeType,
                                             const char *fileName)
{
    IDString                                       suffix;
    ImageFileType                                 *type = 0;
    std::map<IDString, ImageFileType *>::iterator  sI;
    const char                                     separator = '.';
    int                                            i, l;
    std::ifstream                                  fin;
    const char                                     *mtPrefix = "image/";
    size_t                                          mtLen = strlen(mtPrefix);

    if(mimeType && *mimeType)
    {
        if ( (strlen(mimeType) > mtLen) && 
             !strncmp (mimeType, mtPrefix, mtLen) )
            mimeType += mtLen;

        // check mime type
        for(sI = _suffixTypeMap.begin(); sI != _suffixTypeMap.end(); ++sI)
        {
            if(!stringcasecmp(sI->second->getMimeType(), mimeType))
            {
                type = sI->second;
                break;
            }
        }
        if (!type) {
          FWARNING (("Invalid mimeType %s in getFileType()\n", mimeType));
        }
    }

    if(!type && fileName && *fileName)
    {
        // check file suffix
        if(!type)
        {
            l = strlen(fileName);
            for(i = l - 1; i >= 0; i--)
            {
                if(fileName[i] == separator)
                    break;
            }

            if(i >= 0)
            {
                suffix.set(&(fileName[i + 1]));
                suffix.toLower();
                sI = _suffixTypeMap.find(suffix);
                type = (sI == _suffixTypeMap.end()) ? 0 : sI->second;
            }
        }
    }

    // now validate the header of the file
    bool implemented = false;
    if(fileName && *fileName &&
       type != NULL && !type->validateHeader(fileName, implemented))
    {
        FWARNING (("Found wrong image header trying to autodetect image type!\n"));
        for(sI = _suffixTypeMap.begin(); sI != _suffixTypeMap.end(); ++sI)
        {
            type = sI->second;
            if(type != NULL && type->validateHeader(fileName, implemented))
            {
                if(implemented)
                {
                    FWARNING (("Autodetected '%s' image type!\n", sI->first.str()));
                    return type;
                }
            }
        }
        FWARNING (("Couldn't autodetect image type!\n"));
        return NULL;
    }

    return type;
}

//-------------------------------------------------------------------------
/*!
Returns the default OpenSG ImageFileType
*/
ImageFileType *ImageFileHandler::getDefaultType(void)
{
  IDString        dSuffix("opensg");
  
  std::map<IDString, 
    ImageFileType *>::iterator sI = _suffixTypeMap.find(dSuffix);
  
  
  ImageFileType *type = (sI == _suffixTypeMap.end()) ? 0 : sI->second;
  
  if(!type)
    {
      FFATAL(("Can not find any default (suffix:%s) image handler\n",
              dSuffix.str()));
    }
  
  return type;
}


//-------------------------------------------------------------------------
/*!
Returns the list of supported image suffixes
*/
Int32 ImageFileHandler::getSuffixList(std::list<const Char8 *> & suffixList,
                                      UInt32 flags)
{
    Int32                                         count = 0;
    std::map<IDString, ImageFileType *>::iterator sI;

    suffixList.clear();
    
    for ( sI = _suffixTypeMap.begin(); sI != _suffixTypeMap.end(); ++sI)
    {
        ImageFileType *type = sI->second;
        if(type->getFlags() & flags)
        {
            suffixList.push_back(sI->first.str());
            count++;
        }
    }

  return count;
}

//-------------------------------------------------------------------------
/*!
Creates a new image and tries to read the raster data from
the given fileName. If the mimeType is not Null the method
will try to find the according ImageFileType. Otherwise it
will try to use the fileName suffix to determine the mimeType
*/
ImagePtr ImageFileHandler::read(const char *fileName, const char *mimeType)
{
    ImagePtr image = Image::create();

    if(read(image, fileName, mimeType) == false)
    {
        subRefCP(image);
        image = NullFC;
    }
    return image;
}

//-------------------------------------------------------------------------
/*!
Tries to read the raster data from
the given fileName into the given Image. 
If the mimeType is not Null the method
will try to find the according ImageFileType. Otherwise it
will try to use the fileName suffix to determine the mimeType
*/
bool ImageFileHandler::read(ImagePtr &image, const char *fileName,
                            const char *mimeType)
{
    bool        retCode = false;
    std::string fullFilePath;
    
    if( _pPathHandler != NULL )
    {
        fullFilePath = _pPathHandler->findFile(fileName);
    }
    else
    {
        fullFilePath = fileName;
    }
    
    if(fullFilePath.empty())
    {
        SWARNING << "couldn't find image file " << fileName << std::endl;
        return false;
    }

    ImageFileType   *type = getFileType(mimeType, fullFilePath.c_str());

    if(type)
    {
        FDEBUG(("try to image read %s as %s\n", 
                fullFilePath.c_str(), 
                type->getMimeType()));

        std::string fixedpath = fullFilePath;
        Path::fixWinNetworkPath(fixedpath);

        retCode = type->read(image, fixedpath.c_str());

        if(retCode)
        {
            FDEBUG(("image: %dx%d\n", image->getWidth(), image->getHeight()));
            image->setAttachmentField(_fileNameKey, fileName);
            image->setAttachmentField(_fullFilePathKey, fullFilePath);
        }
        else
        {
            SWARNING << "could not read " << fullFilePath << std::endl;
        }
    }
    else
    {
        SWARNING << "could not read " << fullFilePath
                 << "; unknown image format" << std::endl;
    }

    return retCode;
}

//-------------------------------------------------------------------------
/*!
Tries to write the raster data (from the given Image) to 
the given fileName.
If the mimeType is not Null the method
will try to find the according ImageFileType. Otherwise it
will try to use the fileName suffix to determine the mimeType
*/
bool ImageFileHandler::write(const ImagePtr &image, const char *fileName,
                             const char *mimeType)
{
    bool            retCode = false;
    ImageFileType   *type;
    const std::string     *fNAttachment;
    
    if (!fileName && (fNAttachment = image->findAttachmentField(_fileNameKey)))
      fileName = fNAttachment->c_str();

    if ((type = getFileType(mimeType, fileName)))
    {
        SINFO << "try to write " << fileName << " as "
              << type->getMimeType() << std::endl;
        retCode = type->write(image, fileName);
    }
    else
    {
        SWARNING << "can't write " << fileName 
                 << "; unknown image format" << std::endl;
    }

    return retCode;
}

//-------------------------------------------------------------------------
/*!
Returns the path handler used
*/
PathHandler* ImageFileHandler::getPathHandler(void)
{
    return _pPathHandler;
}

//-------------------------------------------------------------------------
/*!
Method to set the path handler. 
*/
void ImageFileHandler::setPathHandler(PathHandler *pPathHandler)
{
    _pPathHandler = pPathHandler;
}

//-------------------------------------------------------------------------
/*!
Tries to restore the raster data from
the given memblock into the given Image. 
If the mimeType is not Null the method
will try to find the according ImageFileType. Otherwise it
will try to use the fileName suffix to determine the mimeType
*/
UInt64 ImageFileHandler::restore(ImagePtr &image, const UChar8 *buffer,
                                 Int32 memSize)
{
    return ImageFileType::restore(image, buffer, memSize);
}

//-------------------------------------------------------------------------
/*!
Tries to store the raster data (from the given Image) to 
the given memBlock.
If the mimeType is not Null the method
will try to find the according ImageFileType. Otherwise it
will try to use the fileName suffix to determine the mimeType
*/
UInt64 ImageFileHandler::store(const ImagePtr &image, const char *mimeType,
                               UChar8 *buffer, Int32 memSize)
{
    ImageFileType   *type;

    type = mimeType ? getFileType(mimeType) : getDefaultType();

    return type->store(image, buffer, memSize);
}

//-------------------------------------------------------------------------
/*!
Tries to store the raster data (from the given Image) to 
a new memBlock. The method will automatically allocate and return a
sufficient amount of memory with new. The application has
to free the memory with 'delete [] mem'
If the mimeType is not Null the method
will try to find the according ImageFileType. Otherwise it
will try to use the fileName suffix to determine the mimeType
*/
UChar8 *ImageFileHandler::store(const ImagePtr &image, UInt64 &memSize,
                                const char *mimeType)
{
    ImageFileType   *type = 0;
    UChar8          *mem = 0;

    type = mimeType ? getFileType(mimeType) : getDefaultType();
    memSize = type->maxBufferSize(image);

    if(memSize)
    {
        mem = new UChar8[size_t(memSize)];
        memSize = type->store(image, mem, Int32(memSize));
    }
    else
    {
        FFATAL(("Can not store the image as %s\n", type->getMimeType()));
    }

    return mem;
}

//-------------------------------------------------------------------------
/*!
  The dump method just writes some object debugging info to the LOG stream
*/
void ImageFileHandler::dump(void)
{
    std::map<IDString, ImageFileType *>::iterator    sI;

    for(sI = _suffixTypeMap.begin(); sI != _suffixTypeMap.end(); sI++)
    {
      FLOG (( "Image suffix: %s, mimeType: %s\n",
              sI->first.str(), sI->second->getMimeType() ));
    }
}

//-------------------------------------------------------------------------
/*!
Internal Method to add a new ImageFileType
*/
bool ImageFileHandler::addImageFileType(ImageFileType &fileType)
{
    bool                                           retCode = false;
    std::list<IDString                 >::const_iterator sI;
    std::map <IDString, ImageFileType *>::iterator smI;
    IDString                                       suffix;

    if(!_the)
        _the = new ImageFileHandler;

    for( sI = fileType.getSuffixList().begin(); 
         sI != fileType.getSuffixList().end();
        ++sI)
    {
        suffix.set(sI->str());
        suffix.toLower();
        smI = _the->_suffixTypeMap.find(suffix);
        if(smI != _the->_suffixTypeMap.end())
        {
            SWARNING << "Can't add an image file type with suffix "
                     << suffix << " a second time" << std::endl;
        }
        else
        {
            _the->_suffixTypeMap[suffix] = &fileType;
            retCode = true;
        }
    }

    return retCode;
}

//-------------------------------------------------------------------------
/*!
Default Constructor
*/
ImageFileHandler::ImageFileHandler(void)
{
  _pPathHandler = NULL;
  return;
}

//-------------------------------------------------------------------------
/*!
Invalid Copy Constructor
*/
ImageFileHandler::ImageFileHandler(const ImageFileHandler &)
{
    FFATAL (("Run Copy Constructor on Singleton ImageFileHandler !\n"));
    
    _pPathHandler = NULL;
    return;
}

//-------------------------------------------------------------------------
/*!
Destructor
*/
ImageFileHandler::~ImageFileHandler(void)
{
    return;
}

//-------------------------------------------------------------------------
/*!
Static method the get the Singleton Object
*/
ImageFileHandler & ImageFileHandler::the(void)
{ 
  return *_the; 
}
