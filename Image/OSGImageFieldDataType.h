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
    enum                                 { StringConvertable = 0 };


    static DataType &getType      (void) { return _type;         }

    static Char8    *getSName     (void) { return "SFImageP";    }
    static Char8    *getMName     (void) { return "MFImageP";    }

    static ImageP    getDefault   (void) { return NULL;          }

    static Bool      getFromString(      ImageP  &outVal,
                                   const Char8   *&inVal)
    {
        // TO_BE_DONE
		return false;
    }

    static void             putToString(const ImageP &,
                                              String  &)
    {
        // TO_BE_DONE
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

    static MemoryHandle copyToBin(      MemoryHandle  pMem, 
                                  const ImageP   &oObject)
    {
        UInt64 imgSize=0;
        ImageFileType *type;

        type = ImageFileHandler::the().getFileType("MTD");
        cout << "image copyToBin: " << endl;
        if(oObject)
        {
            imgSize=type->maxBufferSize(*oObject);
        }
        cout << "Image size " << imgSize << endl;
        memcpy(pMem,&imgSize,sizeof(imgSize));
        pMem+=sizeof(imgSize);
        if(oObject)
        {
            type->store(*oObject,pMem);
        }
        return pMem + imgSize;
    }

    static MemoryHandle copyToBin(      MemoryHandle pMem, 
                                  const ImageP      *pObjectStore,
                                        UInt32       uiNumObjects)
    {
        cout << "image mcopyToBin: " << endl;

        // defaut: copy each element
        for(UInt32 i=0; i < uiNumObjects; ++i)
        {
            pMem = copyToBin(pMem, pObjectStore[i]);
        }

        return pMem;
    }

    static MemoryHandle copyFromBin(const MemoryHandle  pMem, 
                                          ImageP       &oObject)
    {
        ImageFileType *type;
        MemoryHandle mem=pMem;
        UInt64 imgSize=0;

        type = ImageFileHandler::the().getFileType("MTD");
        if(oObject)
        {
            delete oObject;
            oObject=NULL;
        }
        memcpy(&imgSize,mem,sizeof(imgSize));
        mem+=sizeof(imgSize);
        if(imgSize)
        {
            cout << "Image size " << imgSize << endl;
            oObject=new Image();
            type->restore(*oObject,mem);
        }
        ImageFileHandler::the().write(*oObject,"xxx.jpg");

        mem+=imgSize;
        cout << "image copyFromBin: " << endl;
        return mem;
    }

    static MemoryHandle copyFromBin(const MemoryHandle  pMem, 
                                          ImageP       *pObjectStore,
                                          UInt32        uiNumObjects)
    {
        MemoryHandle mem = pMem;

        // defaut: copy each element
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            mem = copyFromBin(mem, pObjectStore[i]);
        }
        cout << "image mcopyFromBin: " << endl;

        return mem;
    }

};

OSG_END_NAMESPACE

#endif /* _OSG_IMAGEFIELDDATATYPE_H_ */




