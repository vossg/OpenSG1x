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

#ifndef _OSG_FIELDCONTAINERFIELDDATATYPE_H_
#define _OSG_FIELDCONTAINERFIELDDATATYPE_H_

#include <OSGFieldDataType.h>
#include <OSGFieldContainerPtr.h>
#include <OSGFieldContainerFactory.h>

OSG_BEGIN_NAMESPACE

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief FieldContainerPtr field traits 
 */

template <>
struct FieldTraitsRecurseMapper<FieldContainerPtr> : 
    public FieldTraitsRecurseBase<FieldContainerPtr>
{
    enum                           { bHasParent = 0x00 };

    static UInt32 getBinSize(const FieldContainerPtr &)
    {
        return sizeof(UInt32);
    }

    static UInt32 getBinSize(const FieldContainerPtr *,
                                   UInt32             uiNumObjects)
    {
        return sizeof(UInt32) * uiNumObjects;
    }

    static MemoryHandle copyToBin(      MemoryHandle       pMem, 
                                  const FieldContainerPtr &pObject)
    {
        UInt32 id;

        if(pObject==NullFC)
        {
            // id=0 indicates an Null Ptr
            id = 0;
        }
        else
        {
            id = pObject.getFieldContainerId();
        }

        memcpy(pMem, &id, sizeof(UInt32));

        return pMem + sizeof(UInt32);
    }

    static MemoryHandle copyToBin(      MemoryHandle       pMem, 
                                  const FieldContainerPtr *pObjectStore,
                                        UInt32             uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; i++)
        {
            pMem = copyToBin(pMem, pObjectStore[i]);
        }

        return pMem;
    }

    static MemoryHandle copyFromBin(const MemoryHandle       pMem, 
                                          FieldContainerPtr &pObject)
    {
        UInt32 id;

        memcpy(&id, pMem, sizeof(UInt32));

        if(0 != id)
        {
            pObject = FieldContainerFactory::the()->getMappedContainer(id);
        }
        else
        {
            pObject = NullFC;
        }

        return pMem + sizeof(UInt32);
    }

    static MemoryHandle copyFromBin(const MemoryHandle       pMem, 
                                          FieldContainerPtr *pObjectStore,
                                          UInt32             uiNumObjects)
    {
        MemoryHandle mem = pMem;

        for(UInt32 i = 0; i < uiNumObjects; i++)
        {
            mem = copyFromBin(mem, pObjectStore[i]);
        }

        return mem;
    }
};

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief FieldContainerPtr field traits 
 */

template <>
struct FieldDataTraits<FieldContainerPtr> : 
    public FieldTraitsRecurseMapper<FieldContainerPtr>
{
    static DataType                 _type;

    enum                            { StringConvertable = 0x00      };

    static DataType &getType (void) { return _type;                 }
 
    static char     *getSName(void) { return "SFFieldContainerPtr"; }
    static char     *getMName(void) { return "MFFieldContainerPtr"; }
};

OSG_END_NAMESPACE

#define OSGFIELDCONTAINERFIELDDATATYPE_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSG_FIELDCONTAINERDATATYPE_H_ */







