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


#ifndef _OSG_FIELDDATATYPE_H_
#define _OSG_FIELDDATATYPE_H_

#include <OSGBase.h>
#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>
#include <OSGDataType.h>
#include <OSGBinaryDataHandler.h>

OSG_BEGIN_NAMESPACE

/** \file OSGFieldDataType.h
 *  \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief OpenSG Field Data Types  
*/

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief Documentation dummy
 */

struct Traits
{
    enum 
    {
        ToStringConvertable   = 0x01,
        FromStringConvertable = 0x02
    };

    static const Char8 *getPName(void) { return "Field"; }
};

template<class FieldTypeT>
struct FieldDataTraits;

template<class FieldTypeT>
struct FieldDataTraits1;

template<class FieldTypeT>
struct FieldDataTraits2;

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief Base template to store the required information to instantiate
 *   fields
 */

template<class FieldTypeT>
struct FieldTraitsRecurseBase : public Traits
{
    enum { bHasParent = 0x00 };

    static UInt32 getBinSize(const FieldTypeT &)
    {
        return sizeof(FieldTypeT);
    }

    static UInt32 getBinSize(const FieldTypeT   *pObjectStore,
                                   UInt32        uiNumObjects)
    {
        typedef FieldDataTraits<FieldTypeT> MappedTrait;

        UInt32 size = 0;

        // defaut: individual field sizes
        for(UInt32 i=0; i <uiNumObjects; ++i)
        {
            size += MappedTrait::getBinSize(pObjectStore[i]);
        }

        return size;
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const FieldTypeT        &oObject)
    {
        typedef FieldDataTraits<FieldTypeT> MappedTrait;
        pMem.put(&oObject, MappedTrait::getBinSize(oObject));
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const FieldTypeT        *pObjectStore,
                                UInt32             uiNumObjects)
    {
        typedef FieldDataTraits<FieldTypeT> MappedTrait;

        // defaut: copy each element
        for(UInt32 i=0; i < uiNumObjects; ++i)
        {
            MappedTrait::copyToBin(pMem, pObjectStore[i]);
        }
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            FieldTypeT        &oObject)
    {
        typedef FieldDataTraits<FieldTypeT> MappedTrait;

        pMem.get(&oObject, MappedTrait::getBinSize(oObject));
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            FieldTypeT        *pObjectStore,
                            UInt32             uiNumObjects)
    {
        typedef FieldDataTraits<FieldTypeT> MappedTrait;

        // defaut: copy each element
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            MappedTrait::copyFromBin(pMem, pObjectStore[i]);
        }
    }
};

template <class FieldTypeT>
struct FieldTraitsIntegralRecurseMapper : 
    public FieldTraitsRecurseBase<FieldTypeT>
{
    static UInt32 getBinSize(const FieldTypeT &)
    {
        return sizeof(FieldTypeT);
    }

    static UInt32 getBinSize(const FieldTypeT   *,
                                   UInt32        uiNumObjects)
    {
        return sizeof(FieldTypeT) * uiNumObjects;
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const FieldTypeT        &oObject)
    {
        pMem.put(&oObject, getBinSize(oObject));
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const FieldTypeT        *pObjectStore,
                                UInt32             uiNumObjects)
    {
        pMem.put(&pObjectStore[0], getBinSize(pObjectStore, uiNumObjects));
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            FieldTypeT        &oObject)
    {
        pMem.get(&oObject, getBinSize(oObject));
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            FieldTypeT        *pObjectStore,
                            UInt32             uiNumObjects)
    {
        pMem.get(&pObjectStore[0], getBinSize(pObjectStore, uiNumObjects));
    }
};

template <class FieldTypeT>
struct FieldTraitsRecurseMapper : public FieldTraitsRecurseBase<FieldTypeT>
{
    static UInt32 getBinSize(const FieldTypeT &oObject)
    {
        typedef typename FieldTypeT::Inherited       Inherited;
        typedef          FieldDataTraits<FieldTypeT> FieldTypeTraits;

        typedef typename osgIF<FieldTypeTraits::bHasParent == 1,
                               FieldDataTraits<Inherited>, 
                               FieldTraitsRecurseBase<FieldTypeT> >::_IRet 
            MappedTrait;

        return MappedTrait::getBinSize(oObject);
    }

    static UInt32 getBinSize(const FieldTypeT   *pObjectStore,
                                   UInt32        uiNumObjects)
    {
        typedef typename FieldTypeT::Inherited       Inherited;
        typedef          FieldDataTraits<FieldTypeT> FieldTypeTraits;

        typedef typename osgIF<FieldTypeTraits::bHasParent == 1,
                               FieldDataTraits<Inherited>, 
                               FieldTraitsRecurseBase<FieldTypeT> >::_IRet 
            MappedTrait;

        return MappedTrait::getBinSize(pObjectStore, uiNumObjects);
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const FieldTypeT        &oObject)
    {
        typedef typename FieldTypeT::Inherited       Inherited;
        typedef          FieldDataTraits<FieldTypeT> FieldTypeTraits;

        typedef typename osgIF<FieldTypeTraits::bHasParent == 1,
                               FieldDataTraits<Inherited>, 
                               FieldTraitsRecurseBase<FieldTypeT> >::_IRet 
            MappedTrait;

        MappedTrait::copyToBin(pMem, oObject);
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const FieldTypeT        *pObjectStore,
                                UInt32             uiNumObjects)
    {
        typedef typename FieldTypeT::Inherited       Inherited;
        typedef          FieldDataTraits<FieldTypeT> FieldTypeTraits;

        typedef typename osgIF<FieldTypeTraits::bHasParent == 1,
                               FieldDataTraits<Inherited>, 
                               FieldTraitsRecurseBase<FieldTypeT> >::_IRet 
            MappedTrait;

        MappedTrait::copyToBin(pMem, pObjectStore, uiNumObjects);
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            FieldTypeT        &oObject)
    {
        typedef typename FieldTypeT::Inherited       Inherited;
        typedef          FieldDataTraits<FieldTypeT> FieldTypeTraits;

        typedef typename osgIF<FieldTypeTraits::bHasParent == 1,
                               FieldDataTraits<Inherited>, 
                               FieldTraitsRecurseBase<FieldTypeT> >::_IRet 
            MappedTrait;

        MappedTrait::copyFromBin(pMem, oObject);
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            FieldTypeT        *pObjectStore,
                            UInt32             uiNumObjects)
    {
        typedef typename FieldTypeT::Inherited       Inherited;
        typedef          FieldDataTraits<FieldTypeT> FieldTypeTraits;

        typedef typename osgIF<FieldTypeTraits::bHasParent == 1,
                               FieldDataTraits<Inherited>, 
                               FieldTraitsRecurseBase<FieldTypeT> >::_IRet 
            MappedTrait;

        MappedTrait::copyFromBin(pMem, pObjectStore, uiNumObjects);
    }
};

template <class FieldTypeT>
struct FieldTraitsRecurseMapper1 : public FieldTraitsRecurseBase<FieldTypeT>
{
    static UInt32 getBinSize(const FieldTypeT &oObject)
    {
        typedef typename FieldTypeT::Inherited        Inherited;
        typedef          FieldDataTraits1<FieldTypeT> FieldTypeTraits;

        typedef typename osgIF<FieldTypeTraits::bHasParent == 1,
                               FieldDataTraits1<Inherited>, 
                               FieldTraitsRecurseBase<FieldTypeT> >::_IRet 
            MappedTrait;

        return MappedTrait::getBinSize(oObject);
    }

    static UInt32 getBinSize(const FieldTypeT   *pObjectStore,
                                   UInt32        uiNumObjects)
    {
        typedef typename FieldTypeT::Inherited       Inherited;
        typedef          FieldDataTraits<FieldTypeT> FieldTypeTraits;

        typedef typename osgIF<FieldTypeTraits::bHasParent == 1,
                               FieldDataTraits1<Inherited>, 
                               FieldTraitsRecurseBase<FieldTypeT> >::_IRet 
            MappedTrait;

        return MappedTrait::getBinSize(pObjectStore, uiNumObjects);
    }
    static void copyToBin(      BinaryDataHandler &pMem, 
                          const FieldTypeT        &oObject)
    {
        typedef typename FieldTypeT::Inherited       Inherited;
        typedef          FieldDataTraits1<FieldTypeT> FieldTypeTraits;

        typedef typename osgIF<FieldTypeTraits::bHasParent == 1,
                               FieldDataTraits1<Inherited>, 
                               FieldTraitsRecurseBase<FieldTypeT> >::_IRet 
            MappedTrait;

        MappedTrait::copyToBin(pMem, oObject);
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const FieldTypeT        *pObjectStore,
                                UInt32             uiNumObjects)
    {
        typedef typename FieldTypeT::Inherited       Inherited;
        typedef          FieldDataTraits1<FieldTypeT> FieldTypeTraits;

        typedef typename osgIF<FieldTypeTraits::bHasParent == 1,
                               FieldDataTraits1<Inherited>, 
                               FieldTraitsRecurseBase<FieldTypeT> >::_IRet 
            MappedTrait;

        MappedTrait::copyToBin(pMem, pObjectStore, uiNumObjects);
    }

    static void copyFromBin(const BinaryDataHandler &pMem, 
                                  FieldTypeT        &oObject)
    {
        typedef typename FieldTypeT::Inherited       Inherited;
        typedef          FieldDataTraits1<FieldTypeT> FieldTypeTraits;

        typedef typename osgIF<FieldTypeTraits::bHasParent == 1,
                               FieldDataTraits1<Inherited>, 
                               FieldTraitsRecurseBase<FieldTypeT> >::_IRet 
            MappedTrait;

        MappedTrait::copyFromBin(pMem, oObject);
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            FieldTypeT        *pObjectStore,
                            UInt32             uiNumObjects)
    {
        typedef typename FieldTypeT::Inherited       Inherited;
        typedef          FieldDataTraits1<FieldTypeT> FieldTypeTraits;

        typedef typename osgIF<FieldTypeTraits::bHasParent == 1,
                               FieldDataTraits1<Inherited>, 
                               FieldTraitsRecurseBase<FieldTypeT> >::_IRet 
            MappedTrait;

        MappedTrait::copyFromBin(pMem, pObjectStore, uiNumObjects);
    }
};

template <class FieldTypeT>
struct FieldTraitsRecurseMapper2 : public FieldTraitsRecurseBase<FieldTypeT>
{
    static UInt32 getBinSize(const FieldTypeT &oObject)
    {
        typedef typename FieldTypeT::Inherited        Inherited;
        typedef          FieldDataTraits2<FieldTypeT> FieldTypeTraits;

        typedef typename osgIF<FieldTypeTraits::bHasParent == 1,
                               FieldDataTraits2<Inherited>, 
                               FieldTraitsRecurseBase<FieldTypeT> >::_IRet 
            MappedTrait;

        return MappedTrait::getBinSize(oObject);
    }

    static UInt32 getBinSize(const FieldTypeT   *pObjectStore,
                                   UInt32        uiNumObjects)
    {
        typedef typename FieldTypeT::Inherited       Inherited;
        typedef          FieldDataTraits<FieldTypeT> FieldTypeTraits;

        typedef typename osgIF<FieldTypeTraits::bHasParent == 1,
                               FieldDataTraits2<Inherited>, 
                               FieldTraitsRecurseBase<FieldTypeT> >::_IRet 
            MappedTrait;

        return MappedTrait::getBinSize(pObjectStore, uiNumObjects);
    }
    static void copyToBin(      BinaryDataHandler &pMem, 
                          const FieldTypeT        &oObject)
    {
        typedef typename FieldTypeT::Inherited       Inherited;
        typedef          FieldDataTraits2<FieldTypeT> FieldTypeTraits;

        typedef typename osgIF<FieldTypeTraits::bHasParent == 1,
                               FieldDataTraits2<Inherited>, 
                               FieldTraitsRecurseBase<FieldTypeT> >::_IRet 
            MappedTrait;

        MappedTrait::copyToBin(pMem, oObject);
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const FieldTypeT        *pObjectStore,
                                UInt32             uiNumObjects)
    {
        typedef typename FieldTypeT::Inherited       Inherited;
        typedef          FieldDataTraits2<FieldTypeT> FieldTypeTraits;

        typedef typename osgIF<FieldTypeTraits::bHasParent == 1,
                               FieldDataTraits2<Inherited>, 
                               FieldTraitsRecurseBase<FieldTypeT> >::_IRet 
            MappedTrait;

        MappedTrait::copyToBin(pMem, pObjectStore, uiNumObjects);
    }

    static void copyFromBin(const BinaryDataHandler &pMem, 
                                  FieldTypeT        &oObject)
    {
        typedef typename FieldTypeT::Inherited       Inherited;
        typedef          FieldDataTraits2<FieldTypeT> FieldTypeTraits;

        typedef typename osgIF<FieldTypeTraits::bHasParent == 1,
                               FieldDataTraits2<Inherited>, 
                               FieldTraitsRecurseBase<FieldTypeT> >::_IRet 
            MappedTrait;

        MappedTrait::copyFromBin(pMem, oObject);
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            FieldTypeT        *pObjectStore,
                            UInt32             uiNumObjects)
    {
        typedef typename FieldTypeT::Inherited       Inherited;
        typedef          FieldDataTraits2<FieldTypeT> FieldTypeTraits;

        typedef typename osgIF<FieldTypeTraits::bHasParent == 1,
                               FieldDataTraits2<Inherited>, 
                               FieldTraitsRecurseBase<FieldTypeT> >::_IRet 
            MappedTrait;

        MappedTrait::copyFromBin(pMem, pObjectStore, uiNumObjects);
    }
};

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief Base template to store the required information to instantiate
 *   fields
 */

template <class FieldTypeT>
struct FieldDataTraits : public FieldTraitsRecurseMapper<FieldTypeT>
{
};

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief Base template to store the required information to instantiate
 *   fields
 */

template <class FieldTypeT>
struct FieldDataTraits1 : public FieldTraitsRecurseMapper1<FieldTypeT>
{
};

template <class FieldTypeT>
struct FieldDataTraits2 : public FieldTraitsRecurseMapper2<FieldTypeT>
{
};

OSG_END_NAMESPACE

#endif /* _OSG_FIELDDATATYPE_H_ */


