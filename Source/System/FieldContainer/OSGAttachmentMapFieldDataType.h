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

#ifndef _OSG_ATTACHMENTMAPFIELDDATATYPE_H_
#define _OSG_ATTACHMENTMAPFIELDDATATYPE_H_

#include <OSGFieldDataType.h>
#include <OSGFieldContainerFieldDataType.h>
#include <OSGFieldContainerPtrForward.h>
#include <OSGAttachmentPtr.h>

#include <map>

OSG_BEGIN_NAMESPACE

typedef std::map<UInt32, AttachmentPtr>  AttachmentMap;

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGAttachmentMapFieldDataType.h
    \ingroup GrpSystemField
    \ingroup GrpSystemFieldTraits
 */
#endif

/*! \ingroup GrpSystemFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldTraitsRecurseMapper<AttachmentMap, false> : 
    public FieldTraitsRecurseBase<AttachmentMap>
{
    enum                    { bHasParent        = 0x00   };

    static UInt32 getBinSize(const AttachmentMap &oObject)
    {
        AttachmentMap::const_iterator mapIt  = oObject.begin();
        AttachmentMap::const_iterator mapEnd = oObject.end();

        UInt32 uiNumPublicObjects = 0;

        while(mapIt != mapEnd)
        {
            if(mapIt->second->getInternal().getValue() == false)
            {
                ++uiNumPublicObjects;
            }

            ++mapIt;
        }

        return sizeof(UInt32) +  // Number of elements in the map 
               uiNumPublicObjects * (sizeof(UInt16) + sizeof(UInt32));
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

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const AttachmentMap     &pObject)
    {
        UInt16 binding;
        UInt32 fcId;
        UInt32 uiNumPublicObjects = 0;

        AttachmentMap::const_iterator mapIt  = pObject.begin();
        AttachmentMap::const_iterator mapEnd = pObject.end();

        while(mapIt != mapEnd)
        {
            if(mapIt->second->getInternal().getValue() == false)
            {
                ++uiNumPublicObjects;
            }

            ++mapIt;
        }

        pMem.putValue(uiNumPublicObjects);

        mapIt = pObject.begin();

        for(; mapIt != mapEnd; ++mapIt)
        {
            if(mapIt->second->getInternal().getValue() == false)
            {
                binding = mapIt->first & 0xffff;
                fcId    = mapIt->second.getFieldContainerId();
                
                pMem.putValue(binding);
                pMem.putValue(fcId);
            }
        }
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const AttachmentMap *pObjectStore,
                                UInt32         uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            copyToBin(pMem, pObjectStore[i]);
        }
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            AttachmentMap     &pObject)
    {
        FieldContainerPtr fcp;

        UInt32 key;
        UInt16 binding;
        UInt32 fcId;
        UInt32 size;

        pMem.getValue(size);

        pObject.clear();

        for(UInt32 i = 0; i < size; ++i)
        {
            pMem.getValue(binding);
            pMem.getValue(fcId);

            fcp = FieldContainerFactory::the()->getMappedContainer(fcId);

            key = (UInt32 (fcp->getGroupId()) << 16) | binding;

            ((FieldContainerPtr &) pObject[key]) = fcp;
        }
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            AttachmentMap     *pObjectStore,
                            UInt32             uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            copyFromBin(pMem, pObjectStore[i]);
        }
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class FieldTraitsRecurseBase<AttachmentMap> */
/*! \hideinhierarchy                             */
#endif

/*! \ingroup GrpSystemFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_SYSTEMLIB_DLLMAPPING FieldDataTraits<AttachmentMap> : 
    public FieldTraitsRecurseMapper<AttachmentMap, false>
{
    static DataType                  _type;

    enum                            { StringConvertable = 0x01  };
    enum                            { bHasParent        = 0x00  };

    static DataType &getType (void) { return _type;             }
    static char     *getSName(void) { return "SFAttachmentMap"; }
    static char     *getMName(void) { return "MFAttachmentMap"; }

    static bool        getFromString(      AttachmentMap  &,
                                     const Char8         *&)
    {
        return false;
    }

    static void      putToString    (const AttachmentMap &,
                                           std::string   &outStr)
    {
        outStr.assign("AttachmentMap");
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class FieldTraitsRecurseMapper<AttachmentMap, false> */
/*! \hideinhierarchy                                      */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

OSG_END_NAMESPACE

#define OSGATTACHMENTMAPFIELDDATATYPE_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSG_ATTACHMENTMAPFIELDDATATYPE_H_ */












