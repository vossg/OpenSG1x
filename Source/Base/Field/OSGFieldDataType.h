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


#ifndef _OSG_FIELDDATATYPE_H_
#define _OSG_FIELDDATATYPE_H_

#include <OSGBase.h>
#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>
#include <OSGDataType.h>
#include <OSGBinaryDataHandler.h>

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGFieldDataType.h
    \ingroup GrpBaseField
    \ingroup GrpBaseFieldTraits
*/
#endif


/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

struct FieldTraits
{
    enum 
    {
        ToStringConvertable   = 0x01,
        FromStringConvertable = 0x02
    };

    static const Char8 *getPName(void) { return "Field"; }
};

struct InvalidTrait 
{
};

/*! \ingroup GrpBaseFieldTraits */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy            */
#endif

template<class FieldTypeT>
struct FieldDataTraits;

/*! \ingroup GrpBaseFieldTraits */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy            */
#endif

template<class FieldTypeT>
struct FieldDataTraits1;

/*! \ingroup GrpBaseFieldTraits */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy            */
#endif

template<class FieldTypeT>
struct FieldDataTraits2;

/*! \ingroup GrpBaseFieldTraits */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy            */
#endif

template<class FieldTypeT>
struct FieldTraitsRecurseBase : public FieldTraits
{
    enum              { bHasParent = 0x00 };

#ifndef __hpux
    static const UInt32 uiTest = TypeTraits<FieldTypeT>::IsPOD == true;

    typedef typename 
    osgIF<uiTest == 1, 
          const FieldTypeT  , 
          const FieldTypeT & >::_IRet  ArgumentType;
#else
    typedef typename 
    osgIF<TypeTraits<FieldTypeT>::IsPOD, 
          const FieldTypeT  , 
          const FieldTypeT & >::_IRet  ArgumentType;
#endif

    static       UInt32    getBinSize (const FieldTypeT &oObject)
    {
        typedef FieldDataTraits<FieldTypeT> MappedTrait;

        std::string value;

        MappedTrait::putToString(oObject, value);

        return value.length() + 1 + sizeof(UInt32);
    }

    static       UInt32    getBinSize (const FieldTypeT    *pObjectStore,
                                             UInt32         uiNumObjects)
    {
        typedef FieldDataTraits<FieldTypeT> MappedTrait;

        UInt32 size = 0;

        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            size += MappedTrait::getBinSize(pObjectStore[i]);
        }

        return size;
    }

    static void copyToBin(      BinaryDataHandler   &pMem, 
                          const FieldTypeT          &oObject)
    {
        typedef FieldDataTraits<FieldTypeT> MappedTrait;
        
        std::string value;

        MappedTrait::putToString(oObject, value);

    	pMem.putValue(value);
    }


    static void copyToBin(      BinaryDataHandler &pMem, 
                          const FieldTypeT        *pObjectStore,
                                UInt32             uiNumObjects)
    {
        typedef FieldDataTraits<FieldTypeT> MappedTrait;

        // defaut: copy each element
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            MappedTrait::copyToBin(pMem, pObjectStore[i]);
        }
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            FieldTypeT        &oObject)
    {
        typedef FieldDataTraits<FieldTypeT> MappedTrait;

        const Char8 *c = NULL;

        std::string value;

        pMem.getValue(value);
        c = value.c_str();
        MappedTrait::getFromString(oObject, c);
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

    static bool getFromString(      FieldTypeT &outVal,
                              const Char8      *inVal  )
    {
        typedef FieldDataTraits<FieldTypeT> MappedTrait;

        return MappedTrait::getFromString(outVal, inVal);
    }

    static void putToString  (const FieldTypeT  &inVal,
                                    std::string &outStr)
    {
        typedef FieldDataTraits<FieldTypeT> MappedTrait;

        MappedTrait::putToString(inVal, outStr);
    }
};

#if defined(__hpuxX)
template <class FieldTypeT> inline
const UInt32 FieldTraitsRecurseBase<FieldTypeT>::uiTest;
#endif

/*! \ingroup GrpBaseFieldTraits */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy            */
#endif

template<class FieldTypeT>
struct FieldTraitsRecurseBase1 : public FieldTraits
{
    enum              { bHasParent = 0x00 };

#ifndef __hpux
    static const UInt32 uiTest = TypeTraits<FieldTypeT>::IsPOD == true;

    typedef typename 
    osgIF<uiTest == 1, 
          const FieldTypeT  , 
          const FieldTypeT & >::_IRet  ArgumentType;
#else
    typedef typename 
    osgIF<TypeTraits<FieldTypeT>::IsPOD, 
          const FieldTypeT  , 
          const FieldTypeT & >::_IRet  ArgumentType;
#endif

    static       UInt32    getBinSize (const FieldTypeT &oObject)
    {
        typedef FieldDataTraits1<FieldTypeT> MappedTrait;

        std::string value;

        MappedTrait::putToString(oObject, value);

        return value.length() + 1 + sizeof(UInt32);
    }

    static       UInt32    getBinSize (const FieldTypeT    *pObjectStore,
                                             UInt32         uiNumObjects)
    {
        typedef FieldDataTraits1<FieldTypeT> MappedTrait;

        UInt32 size = 0;

        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            size += MappedTrait::getBinSize(pObjectStore[i]);
        }

        return size;
    }

    static void copyToBin(      BinaryDataHandler   &pMem, 
                          const FieldTypeT          &oObject)
    {
        typedef FieldDataTraits1<FieldTypeT> MappedTrait;
        
        std::string value;

        MappedTrait::putToString(oObject, value);

    	pMem.putValue(value);
    }


    static void copyToBin(      BinaryDataHandler &pMem, 
                          const FieldTypeT        *pObjectStore,
                                UInt32             uiNumObjects)
    {
        typedef FieldDataTraits1<FieldTypeT> MappedTrait;

        // defaut: copy each element
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            MappedTrait::copyToBin(pMem, pObjectStore[i]);
        }
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            FieldTypeT        &oObject)
    {
        typedef FieldDataTraits1<FieldTypeT> MappedTrait;

        const Char8 *c = NULL;

        std::string value;

        pMem.getValue(value);
        c = value.c_str();
        MappedTrait::getFromString(oObject, c);
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            FieldTypeT        *pObjectStore,
                            UInt32             uiNumObjects)
    {
        typedef FieldDataTraits1<FieldTypeT> MappedTrait;

        // defaut: copy each element
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            MappedTrait::copyFromBin(pMem, pObjectStore[i]);
        }
    }

    static bool getFromString(      FieldTypeT &outVal,
                              const Char8      *inVal  )
    {
        typedef FieldDataTraits1<FieldTypeT> MappedTrait;

        return MappedTrait::getFromString(outVal, inVal);
    }

    static void putToString  (const FieldTypeT  &inVal,
                                    std::string &outStr)
    {
        typedef FieldDataTraits1<FieldTypeT> MappedTrait;

        MappedTrait::putToString(inVal, outStr);
    }
};

#if defined(__hpuxX)
template <class FieldTypeT> inline
const UInt32 FieldTraitsRecurseBase1<FieldTypeT>::uiTest;
#endif

/*! \ingroup GrpBaseFieldTraits */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy            */
#endif

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
        pMem.putValue(oObject);
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const FieldTypeT        *pObjectStore,
                                UInt32             uiNumObjects)
    {
        pMem.putValues(&pObjectStore[0], uiNumObjects);
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            FieldTypeT        &oObject)
    {
        pMem.getValue(oObject);
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            FieldTypeT        *pObjectStore,
                            UInt32             uiNumObjects)
    {
        pMem.getValues(&pObjectStore[0], uiNumObjects);
    }
};


/*! \ingroup GrpBaseFieldTraits */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy            */
#endif

template <class FieldTypeT, bool bTypeHasParent>
struct FieldTraitsRecurseMapper : public FieldTraitsRecurseBase<FieldTypeT>
{
    typedef typename FieldTypeT::Inherited       Inherited;
    typedef          FieldDataTraits<FieldTypeT> FieldTypeTraits;

#if defined(OSG_WIN32_CL_NET70) 
#pragma warning (disable : 4806)
#endif

    typedef typename osgIF<(bTypeHasParent == true),
                           FieldDataTraits<Inherited>, 
                           FieldTraitsRecurseBase<FieldTypeT> >::_IRet 
        MappedTrait;

#if defined(OSG_WIN32_CL_NET70) 
#pragma warning (default : 4806)
#endif

    static UInt32 getBinSize(const FieldTypeT &oObject)
    {
        return MappedTrait::getBinSize(oObject);
    }

    static UInt32 getBinSize(const FieldTypeT   *pObjectStore,
                                   UInt32        uiNumObjects)
    {
        return MappedTrait::getBinSize(pObjectStore, uiNumObjects);
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const FieldTypeT        &oObject)
    {
        MappedTrait::copyToBin(pMem, oObject);
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const FieldTypeT        *pObjectStore,
                                UInt32             uiNumObjects)
    {
        MappedTrait::copyToBin(pMem, pObjectStore, uiNumObjects);
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            FieldTypeT        &oObject)
    {
        MappedTrait::copyFromBin(pMem, oObject);
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            FieldTypeT        *pObjectStore,
                            UInt32             uiNumObjects)
    {
        MappedTrait::copyFromBin(pMem, pObjectStore, uiNumObjects);
    }

    static bool getFromString(      FieldTypeT &outVal,
                              const Char8      *inVal  )
    {
        return MappedTrait::getFromString(outVal, inVal);
    }

    static void putToString  (const FieldTypeT  &inVal,
                                    std::string &outStr)
    {
        MappedTrait::putToString(inVal, outStr);
    }
};

/*! \ingroup GrpBaseFieldTraits */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy            */
#endif

template <class FieldTypeT, bool bTypeHasParent>
struct FieldTraitsRecurseMapper1 : public FieldTraitsRecurseBase<FieldTypeT>
{
    typedef typename FieldTypeT::Inherited       Inherited;
    typedef          FieldDataTraits<FieldTypeT> FieldTypeTraits;

#if defined(OSG_WIN32_CL_NET70) 
#pragma warning (disable : 4806)
#endif

    typedef typename osgIF<bTypeHasParent == true,
                           FieldDataTraits1<Inherited>, 
                           FieldTraitsRecurseBase<FieldTypeT> >::_IRet 
        MappedTrait;

#if defined(OSG_WIN32_CL_NET70) 
#pragma warning (default : 4806)
#endif

    static UInt32 getBinSize(const FieldTypeT &oObject)
    {
        return MappedTrait::getBinSize(oObject);
    }

    static UInt32 getBinSize(const FieldTypeT   *pObjectStore,
                                   UInt32        uiNumObjects)
    {
        return MappedTrait::getBinSize(pObjectStore, uiNumObjects);
    }
    static void copyToBin(      BinaryDataHandler &pMem, 
                          const FieldTypeT        &oObject)
    {
        MappedTrait::copyToBin(pMem, oObject);
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const FieldTypeT        *pObjectStore,
                                UInt32             uiNumObjects)
    {
        MappedTrait::copyToBin(pMem, pObjectStore, uiNumObjects);
    }

    static void copyFromBin(const BinaryDataHandler &pMem, 
                                  FieldTypeT        &oObject)
    {
        MappedTrait::copyFromBin(pMem, oObject);
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            FieldTypeT        *pObjectStore,
                            UInt32             uiNumObjects)
    {
        MappedTrait::copyFromBin(pMem, pObjectStore, uiNumObjects);
    }

    static bool getFromString(      FieldTypeT &outVal,
                              const Char8      *inVal  )
    {
        return MappedTrait::getFromString(outVal, inVal);
    }

    static void putToString  (const FieldTypeT  &inVal,
                                    std::string &outStr)
    {
        MappedTrait::putToString(inVal, outStr);
    }
};


/*! \ingroup GrpBaseFieldTraits */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy            */
#endif

template <class FieldTypeT, bool bTypeHasParent>
struct FieldTraitsRecurseMapper2 : public FieldTraitsRecurseBase<FieldTypeT>
{
    typedef typename FieldTypeT::Inherited       Inherited;
    typedef          FieldDataTraits<FieldTypeT> FieldTypeTraits;

#if defined(OSG_WIN32_CL_NET70) 
#pragma warning (disable : 4806)
#endif

    typedef typename osgIF<bTypeHasParent == true,
                           FieldDataTraits2<Inherited>, 
                           FieldTraitsRecurseBase<FieldTypeT> >::_IRet 
        MappedTrait;

#if defined(OSG_WIN32_CL_NET70) 
#pragma warning (default : 4806)
#endif

    static UInt32 getBinSize(const FieldTypeT &oObject)
    {
        return MappedTrait::getBinSize(oObject);
    }

    static UInt32 getBinSize(const FieldTypeT   *pObjectStore,
                                   UInt32        uiNumObjects)
    {
        return MappedTrait::getBinSize(pObjectStore, uiNumObjects);
    }
    static void copyToBin(      BinaryDataHandler &pMem, 
                          const FieldTypeT        &oObject)
    {
        MappedTrait::copyToBin(pMem, oObject);
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const FieldTypeT        *pObjectStore,
                                UInt32             uiNumObjects)
    {
        MappedTrait::copyToBin(pMem, pObjectStore, uiNumObjects);
    }

    static void copyFromBin(const BinaryDataHandler &pMem, 
                                  FieldTypeT        &oObject)
    {
        MappedTrait::copyFromBin(pMem, oObject);
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            FieldTypeT        *pObjectStore,
                            UInt32             uiNumObjects)
    {
        MappedTrait::copyFromBin(pMem, pObjectStore, uiNumObjects);
    }

    static bool getFromString(      FieldTypeT &outVal,
                              const Char8      *inVal  )
    {
        return MappedTrait::getFromString(outVal, inVal);
    }

    static void putToString  (const FieldTypeT  &inVal,
                                    std::string &outStr)
    {
        MappedTrait::putToString(inVal, outStr);
    }
};

/*! \ingroup GrpBaseFieldTraits */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy            */
#endif

template <class FieldTypeT>
struct FieldDataTraits : public FieldTraitsRecurseMapper<FieldTypeT, false>
{
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseMapper<FieldTypeT, false> */
/*! \hideinhierarchy                                    */
#endif
/*! \ingroup GrpBaseFieldTraits */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy            */
#endif

template <class FieldTypeT>
struct FieldDataTraits1 : public FieldTraitsRecurseMapper1<FieldTypeT, false>
{
};


#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseMapper1<FieldTypeT, false> */
/*! \hideinhierarchy                                     */
#endif
/*! \ingroup GrpBaseFieldTraits */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy            */
#endif

template <class FieldTypeT>
struct FieldDataTraits2 : public FieldTraitsRecurseMapper2<FieldTypeT, false>
{
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseMapper2<FieldTypeT, false> */
/*! \hideinhierarchy                                     */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

OSG_END_NAMESPACE

#endif /* _OSG_FIELDDATATYPE_H_ */


