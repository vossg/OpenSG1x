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

#ifndef _OSG_ATTACHMENTMAPFIELDDATATYPE_H_
#define _OSG_ATTACHMENTMAPFIELDDATATYPE_H_

#include <OSGFieldDataType.h>
#include <OSGFieldContainerFieldDataType.h>
#include <OSGAttachmentPtr.h>
#include <OSGFieldContainer.h>

#include <map>

OSG_BEGIN_NAMESPACE

typedef map<UInt32, AttachmentPtr>  AttachmentMap;

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief FieldContainerPtr field traits 
 */

template <>
struct FieldTraitsRecurseMapper<AttachmentMap> : 
    public FieldTraitsRecurseBase<AttachmentMap>
{
    enum                        { bHasParent        = 0x00      };

    static UInt32 getBinSize(const AttachmentMap &oObject)
    {
        return sizeof(UInt32) +  // Number of elements in the map 
               oObject.size() * (sizeof(UInt16) + sizeof(UInt32));
    }

    static UInt32 getBinSize(const AttachmentMap *pObjectStore,
                                   UInt32         uiNumObjects)
    {
        UInt32 size = 0;

        // defaut: individual field sizes

        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            size += getBinSize(pObjectStore[i]);
        }

        return size;
    }

    static MemoryHandle copyToBin(      MemoryHandle   pMem, 
                                  const AttachmentMap &pObject)
    {
        UInt16 binding;
        UInt32 id;
        UInt32 size;

        AttachmentMap::const_iterator mapIt  = pObject.begin();
        AttachmentMap::const_iterator mapEnd = pObject.end();


        size = pObject.size();

        memcpy(pMem, &size, sizeof(UInt32));

        pMem += sizeof(UInt32);

        for(; mapIt != mapEnd; ++mapIt)
        {
            binding = mapIt->first & 0xffff;

            id      = mapIt->second.getFieldContainerId();

            memcpy(pMem, &binding, sizeof(UInt16));
            pMem += sizeof(UInt16);

            memcpy(pMem, &id, sizeof(UInt32));
            pMem += sizeof(UInt32);
        }

        return pMem;
    }

    static MemoryHandle copyToBin(      MemoryHandle   pMem, 
                                  const AttachmentMap *pObjectStore,
                                        UInt32         uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            pMem = copyToBin(pMem, pObjectStore[i]);
        }

        return pMem;
    }

    static MemoryHandle copyFromBin(const MemoryHandle   pMem, 
                                          AttachmentMap &pObject)
    {
        FieldContainerPtr fcp;

        MemoryHandle mem = pMem;

        UInt32 key;
        UInt16 binding;
        UInt32 id;
        UInt32 size;
        
        memcpy(&size, mem, sizeof(UInt32));

        mem += sizeof(UInt32);

        pObject.clear();

        for(UInt32 i = 0; i < size; ++i)
        {
            memcpy(&binding, mem, sizeof(UInt16));
            mem += sizeof(UInt16);


            memcpy(&id, mem, sizeof(UInt32));
            mem+=sizeof(UInt32);

            fcp = FieldContainerFactory::the()->getMappedContainer(id);

            key = (UInt32 (fcp->getGroupId()) << 16) | binding;

            ((FieldContainerPtr &) pObject[key]) = fcp;
        }

        return mem;
    }

    static MemoryHandle copyFromBin(const MemoryHandle   pMem, 
                                          AttachmentMap *pObjectStore,
                                          UInt32         uiNumObjects)
    {
        MemoryHandle mem = pMem;

        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            mem = copyFromBin(mem, pObjectStore[i]);
        }

        return mem;
    }
};

template <>
struct FieldDataTraits<AttachmentMap> : 
    public FieldTraitsRecurseMapper<AttachmentMap>
{
    static DataType                 _type;

    enum                            { StringConvertable = 0x00  };
    enum                            { bHasParent        = 0x00  };

    static DataType &getType (void) { return _type;             }
    static char     *getSName(void) { return "SFAttachmentMap"; }
    static char     *getMName(void) { return "MFAttachmentMap"; }
};

OSG_END_NAMESPACE

#endif /* _OSG_ATTACHMENTMAPFIELDDATATYPE_H_ */







