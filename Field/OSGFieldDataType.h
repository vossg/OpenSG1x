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
#include <OSGString.h>

OSG_BEGIN_NAMESPACE

/** \file FieldDataType.h
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
};

template<class FieldTypeT>
struct FieldDataTraits;

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

    static UInt32 getBinSize(void)
    {
        fprintf(stderr, "FieldTraitsRecurseBase<FieldTypeT>::getBinSize\n");

        return 0;
    }

    static MemoryHandle copyToBin(      MemoryHandle pMem, 
                                  const FieldTypeT   &oObject)
    {
        fprintf(stderr, "FieldTraitsRecurseBase<FieldTypeT>::copyToBin\n");

        return pMem;
    }

    static MemoryHandle copyToBin(      MemoryHandle  pMem, 
                                  const FieldTypeT   *pObjectStore,
                                        UInt32        uiNumObjects)
    {
        fprintf(stderr, "FieldTraitsRecurseBase<FieldTypeT>::mcopyToBin\n");

        return pMem;
    }
};

#if 0
template<class FieldTypeT>
struct FieldTraitsRecurseBase1 : public Traits
{
    enum { bHasParent = 0x00 };

    static void putToBin(void)
    {
        fprintf(stderr, "FieldTraitsRecurseBase1<FieldTypeT>\n");
    }
};

template<class FieldTypeT>
struct FieldTraitsRecurseBase2 : public Traits
{
    enum { bHasParent = 0x00 };

    static void putToBin(void)
    {
        fprintf(stderr, "FieldTraitsRecurseBase2<FieldTypeT>\n");
    }
};
#endif

template <class FieldTypeT>
struct FieldTraitsIntegralRecurseMapper : 
    public FieldTraitsRecurseBase<FieldTypeT>
{
/*
    static UInt32 getBinSize(void)
    {
        fprintf(stderr,
                "FieldTraitsIntegralRecurseMapper<FieldTypeT>::getBinSize\n");
        
        return 0;
    }

    static MemoryHandle copyToBin(      MemoryHandle  pMem, 
                                  const FieldTypeT   &oObject)
    {
        fprintf(stderr, 
                "FieldTraitsIntegralRecurseMapper<FieldTypeT>::copyToBin\n");

        return pMem;
    }

    static MemoryHandle copyToBin(      MemoryHandle pMem, 
                                  const FieldTypeT  *pObjectStore,
                                        UInt32       uiNumObjects)
    {
        fprintf(stderr, 
                "FieldTraitsIntegralRecurseMapper<FieldTypeT>::mcopyToBin\n");

        return pMem;
    }
*/
};

#if 0
template <class FieldTypeT>
struct FieldTraitsIntegralRecurseMapper1 : 
    public FieldTraitsRecurseBase1<FieldTypeT>
{
    static void putToBin(void)
    {
        fprintf(stderr, "FieldTraitsIntegralRecurseMapper<FieldTypeT>\n");
    }
};

template <class FieldTypeT>
struct FieldTraitsIntegralRecurseMapper2 : 
    public FieldTraitsRecurseBase2<FieldTypeT>
{
    static void putToBin(void)
    {
        fprintf(stderr, "FieldTraitsIntegralRecurseMapper<FieldTypeT>\n");
    }
};
#endif

template <class FieldTypeT>
struct FieldTraitsRecurseMapper : public FieldTraitsRecurseBase<FieldTypeT>
{
    static UInt32 getBinSize(void)
    {
        typedef typename FieldTypeT::Inherited       Inherited;
        typedef          FieldDataTraits<FieldTypeT> FieldTypeTraits;

        typedef typename osgIF<FieldTypeTraits::bHasParent == 1,
                               FieldDataTraits<Inherited >, 
                               FieldTraitsRecurseBase<FieldTypeT>   >::_IRet 
            MappedTrait;

        return MappedTrait::getBinSize();
    }

    static MemoryHandle copyToBin(      MemoryHandle  pMem, 
                                  const FieldTypeT   &oObject)
    {
        typedef typename FieldTypeT::Inherited       Inherited;
        typedef          FieldDataTraits<FieldTypeT> FieldTypeTraits;

        typedef typename osgIF<FieldTypeTraits::bHasParent == 1,
                               FieldDataTraits<Inherited >, 
                               FieldTraitsRecurseBase<FieldTypeT>   >::_IRet 
            MappedTrait;

        return MappedTrait::copyToBin(pMem, oObject);
    }

    static MemoryHandle copyToBin(      MemoryHandle pMem, 
                                  const FieldTypeT  *pObjectStore,
                                        UInt32       uiNumObjects)
    {
        typedef typename FieldTypeT::Inherited       Inherited;
        typedef          FieldDataTraits<FieldTypeT> FieldTypeTraits;

        typedef typename osgIF<FieldTypeTraits::bHasParent == 1,
                               FieldDataTraits<Inherited >, 
                               FieldTraitsRecurseBase<FieldTypeT>   >::_IRet 
            MappedTrait;

        return MappedTrait::copyToBin(pMem, pObjectStore, uiNumObjects);
    }
};

template <class FieldTypeT>
struct FieldTraitsRecurseMapper1 : public FieldTraitsRecurseBase<FieldTypeT>
{
    static UInt32 getBinSize(void)
    {
        typedef typename FieldTypeT::Inherited       Inherited;
        typedef          FieldDataTraits<FieldTypeT> FieldTypeTraits;

        typedef typename osgIF<FieldTypeTraits::bHasParent == 1,
                               FieldDataTraits1<Inherited >, 
                               FieldTraitsRecurseBase<FieldTypeT>   >::_IRet 
            MappedTrait;

        return MappedTrait::getBinSize();
    }

    static MemoryHandle copyToBin(      MemoryHandle  pMem, 
                                  const FieldTypeT   &oObject)
    {
        typedef typename FieldTypeT::Inherited       Inherited;
        typedef          FieldDataTraits<FieldTypeT> FieldTypeTraits;

        typedef typename osgIF<FieldTypeTraits::bHasParent == 1,
                               FieldDataTraits1<Inherited >, 
                               FieldTraitsRecurseBase<FieldTypeT>   >::_IRet 
            MappedTrait;

        return MappedTrait::copyToBin(pMem, oObject);
    }

    static MemoryHandle copyToBin(      MemoryHandle  pMem, 
                                  const FieldTypeT   *pObjectStore,
                                        UInt32        uiNumObjects)
    {
        typedef typename FieldTypeT::Inherited       Inherited;
        typedef          FieldDataTraits<FieldTypeT> FieldTypeTraits;

        typedef typename osgIF<FieldTypeTraits::bHasParent == 1,
                               FieldDataTraits1<Inherited >, 
                               FieldTraitsRecurseBase<FieldTypeT>   >::_IRet 
            MappedTrait;

        return MappedTrait::copyToBin(pMem, pObjectStore, uiNumObjects);
    }
};

template <class FieldTypeT>
struct FieldTraitsRecurseMapper2 : public FieldTraitsRecurseBase<FieldTypeT>
{
    static UInt32 getBinSize(void)
    {
        typedef typename FieldTypeT::Inherited       Inherited;
        typedef          FieldDataTraits<FieldTypeT> FieldTypeTraits;

        typedef typename osgIF<FieldTypeTraits::bHasParent == 1,
                               FieldDataTraits<Inherited >, 
                               FieldTraitsRecurseBase<FieldTypeT>   >::_IRet 
            MappedTrait;

        return MappedTrait::getBinSize();
    }

    static MemoryHandle copyToBin(      MemoryHandle  pMem, 
                                  const FieldTypeT   &oObject)
    {
        typedef typename FieldTypeT::Inherited       Inherited;
        typedef          FieldDataTraits<FieldTypeT> FieldTypeTraits;

        typedef typename osgIF<FieldTypeTraits::bHasParent == 1,
                               FieldDataTraits2<Inherited >, 
                               FieldTraitsRecurseBase<FieldTypeT>   >::_IRet 
            MappedTrait;

        return MappedTrait::copyToBin(pMem, oObject);
    }

    static MemoryHandle copyToBin(      MemoryHandle  pMem, 
                                  const FieldTypeT   *pObjectStore,
                                        UInt32        uiNumObjects)
    {
        typedef typename FieldTypeT::Inherited       Inherited;
        typedef          FieldDataTraits<FieldTypeT> FieldTypeTraits;

        typedef typename osgIF<FieldTypeTraits::bHasParent == 1,
                               FieldDataTraits2<Inherited >, 
                               FieldTraitsRecurseBase<FieldTypeT>   >::_IRet 
            MappedTrait;

        return MappedTrait::copyToBin(pMem, pObjectStore, uiNumObjects);
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


