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

#ifndef _OSG_FIELDCONTAINERFIELDDATATYPE_H_
#define _OSG_FIELDCONTAINERFIELDDATATYPE_H_

#include <OSGFieldDataType.h>
#include <OSGFieldContainerPtr.h>
#include <OSGFieldContainerFactory.h>
#include <OSGFieldContainerType.h>

OSG_BEGIN_NAMESPACE

/*! \file OSGFieldContainerFieldDataType.h
    \ingroup GrpBaseField
    \ingroup GrpBaseFieldSingle
    \ingroup GrpBaseFieldMulti
    \brief OpenSG FieldContainer Field Data Types  
*/

/*! \brief FieldContainerPtr field traits 
    \ingroup GrpBaseField
    \ingroup GrpBaseFieldSingle
    \ingroup GrpBaseFieldMulti
*/

template <>
struct FieldTraitsRecurseMapper<FieldContainerPtr, false> : 
    public FieldTraitsRecurseBase<FieldContainerPtr>
{
    enum                    { bHasParent = 0x00       };

    static UInt32 getBinSize(const FieldContainerPtr &)
    {
        return sizeof(UInt32);
    }

    static UInt32 getBinSize(const FieldContainerPtr *,
                                   UInt32             uiNumObjects)
    {
        return sizeof(UInt32) * uiNumObjects;
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
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

        pMem.putValue(id);
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const FieldContainerPtr *pObjectStore,
                                UInt32             uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; i++)
        {
            copyToBin(pMem, pObjectStore[i]);
        }
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            FieldContainerPtr &pObject)
    {
        UInt32 id;

        pMem.getValue(id);

        if(0 != id)
        {
            pObject = FieldContainerFactory::the()->getMappedContainer(id);
        }
        else
        {
            pObject = NullFC;
        }
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            FieldContainerPtr *pObjectStore,
                            UInt32             uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; i++)
        {
            copyFromBin(pMem, pObjectStore[i]);
        }
    }
};

/*! \brief FieldContainerPtr field traits 
    \ingroup GrpBaseField
    \ingroup GrpBaseFieldSingle
    \ingroup GrpBaseFieldMulti
*/

template <>
struct OSG_SYSTEMLIB_DLLMAPPING FieldDataTraits<FieldContainerPtr> : 
    public FieldTraitsRecurseMapper<FieldContainerPtr, false>
{
    static DataType                 _type;

    enum                            { StringConvertable = 0x00  };

    static DataType &getType (void) { return _type;                 }
 
    static char     *getSName(void) { return "SFFieldContainerPtr"; }
    static char     *getMName(void) { return "MFFieldContainerPtr"; }
    
    static bool      getFromString(FieldContainerPtr& OSG_CHECK_ARG(outVal),
                                   const Char8     *& OSG_CHECK_ARG(inVal ) )
    {
        //TO_BE_DONE
        return false;
    }
    
    static void      putToString  (const FieldContainerPtr &inVal,
                                         std::string       &outVal)
    {
        typedef TypeTraits<UInt16> TypeTrait;

        outVal.assign( FieldContainerFactory::the()->findType(
                                inVal.getFieldContainerId())->getName().str());
        outVal.append(" ");
        outVal.append(TypeTrait::putToString(inVal.getContainerSize()));
        outVal.append(" ");
        outVal.append(TypeTrait::putToString(inVal.getParentFieldPos()));
        outVal.append(" ");
        //outVal.append(TypeTraits<UInt32>::putToString(
        //                                           (UInt32)inVal._storeP));
    }
        
                        
};

OSG_END_NAMESPACE

#define OSGFIELDCONTAINERFIELDDATATYPE_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSG_FIELDCONTAINERDATATYPE_H_ */







