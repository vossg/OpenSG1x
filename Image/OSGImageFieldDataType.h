/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

#ifndef _OSG_IMAGEFIELDDATATYPE_H_
#define _OSG_IMAGEFIELDDATATYPE_H_

#include "OSGFieldDataType.h"
#include "OSGImageFileHandler.h"
#include <string>

OSG_BEGIN_NAMESPACE

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief  base field traits 
 */

template <>
struct FieldDataTraits<ImageP> : public FieldTraitsRecurseBase<ImageP>
{
    static DataType                      _type;
    enum             { StringConvertable = ToStringConvertable   |
                                           FromStringConvertable };


    static DataType &getType      (void) { return _type;         }

    static Char8    *getSName     (void) { return "SFImageP";    }
    static Char8    *getMName     (void) { return "MFImageP";    }

    static ImageP    getDefault   (void) { return NULL;          }

    
    //Attention: This does expect a filename as arg inVal not a string with
    //the complete image data in it.
    static Bool      getFromString(      ImageP  &outVal,
                                   const Char8   *&inVal)
    {
        outVal = new Image();
        cerr << "Reading from File: " << inVal;
        cerr << " " << outVal->read( inVal ) << endl;
        return true;
    }

    //This image into a file and returns the name in outVal
    static void             putToString(const ImageP &inVal,
                                              string &outVal)
    {
        static UInt32 counter = 0;
        string fileName;
        fileName.assign("Image");
        fileName.append( TypeConstants<UInt32>::putToString(counter++) );
        fileName.append(".ppm");
        inVal->write(fileName.c_str());
        outVal.assign( "\"" );
        outVal.append( fileName );
        outVal.append( "\"" );
    }

    static UInt32 getBinSize(const ImageP &oObject)
    {
        ImageFileType *type;

        type = ImageFileHandler::the().getFileType("MTD");
        if(oObject)
        {
            return type->maxBufferSize(*oObject) + 
                   sizeof(UInt64);
        }
        return sizeof(UInt64);
    }

    static UInt32 getBinSize(const ImageP   *pObjectStore,
                                   UInt32    uiNumObjects)
    {
        UInt32 size = 0;

        // defaut: individual field sizes
        for(UInt32 i=0; i <uiNumObjects; ++i)
        {
            size += getBinSize(pObjectStore, uiNumObjects);
        }

        return size;
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const ImageP   &oObject)
    {
        UInt32 imgSize=0;
        ImageFileType *type;

        type = ImageFileHandler::the().getFileType("MTD");
        if(oObject)
        {
            imgSize=(UInt32)type->maxBufferSize(*oObject);
        }
        pMem.put(&imgSize,sizeof(imgSize));
        if(oObject)
        {
            UInt8 *image = new UInt8 [imgSize];
            type->store(*oObject,image);
            pMem.putAndFree(image,imgSize);
        }
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const ImageP            *pObjectStore,
                                UInt32             uiNumObjects)
    {
        // defaut: copy each element
        for(UInt32 i=0; i < uiNumObjects; ++i)
        {
            copyToBin(pMem, pObjectStore[i]);
        }
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            ImageP       &oObject)
    {
        ImageFileType *type;
        UInt32 imgSize=0;

        type = ImageFileHandler::the().getFileType("MTD");
        if(oObject)
        {
            delete oObject;
            oObject=NULL;
        }
        pMem.get(&imgSize,sizeof(imgSize));
        if(imgSize)
        {
            UInt8 *image;
            oObject=new Image();
            pMem.getAndAlloc(image,imgSize);
            type->restore(*oObject,image);
            delete [] image;
        }
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            ImageP            *pObjectStore,
                            UInt32             uiNumObjects)
    {
        // defaut: copy each element
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            copyFromBin(pMem, pObjectStore[i]);
        }
    }

};

OSG_END_NAMESPACE

#endif /* _OSG_IMAGEFIELDDATATYPE_H_ */




