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


#ifndef _OSG_VECFIELDDATATYPE_H_
#define _OSG_VECFIELDDATATYPE_H_

#include <OSGBase.h>
#include <OSGFieldDataType.h>
#include <OSGVector.h>

#include <string>

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGVecFieldDataType.h
    \ingroup GrpBaseField
    \ingroup GrpBaseFieldTraits
*/
#endif


/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template<class ValueTypeT>
struct FieldTraitsRecurseVecStoreBase : public FieldTraits
{
    enum                     { bHasParent = 0x00 };

#ifndef __hpux
    static const UInt32 uiTest = TypeTraits<ValueTypeT>::IsPOD == false;

    typedef typename 
    osgIF<uiTest == 1, 
          const ValueTypeT  , 
          const ValueTypeT & >::_IRet  ArgumentType;
#else
    typedef typename 
    osgIF<!TypeTraits<ValueTypeT>::IsPOD, 
          const ValueTypeT  , 
          const ValueTypeT & >::_IRet  ArgumentType;
#endif

    static UInt32 getBinSize (const ValueTypeT &)
    {
        return sizeof(ValueTypeT);
    }

    static UInt32 getBinSize (const ValueTypeT *,
                                    UInt32      uiNumObjects)
    {
        return sizeof(ValueTypeT) * uiNumObjects;
    }

    static void   copyToBin  (      BinaryDataHandler &pMem, 
                              const ValueTypeT        &oObject)
    {
        pMem.putValues(&oObject[0], ValueTypeT::_iSize);
    }

    static void   copyToBin  (      BinaryDataHandler &pMem, 
                              const ValueTypeT        *pObjectStore,
                                    UInt32             uiNumObjects)
    {
        pMem.putValues(&pObjectStore[0][0], ValueTypeT::_iSize*uiNumObjects);
    }

    static void   copyFromBin(      BinaryDataHandler &pMem, 
                                    ValueTypeT        &oObject)
    {
        pMem.getValues(&oObject[0], ValueTypeT::_iSize);
    }

    static void   copyFromBin(      BinaryDataHandler &pMem, 
                                    ValueTypeT        *pObjectStore,
                                    UInt32             uiNumObjects)
    {
        pMem.getValues(&pObjectStore[0][0], ValueTypeT::_iSize*uiNumObjects);
    }
};

#if defined(__hpuxX)
template<class ValueTypeT> 
const UInt32 FieldTraitsRecurseVecStoreBase<ValueTypeT>::uiTest;
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template<class ValueTypeT>
struct FieldTraitsRecurseVecStore2Base : 
    public FieldTraitsRecurseVecStoreBase<ValueTypeT> 
{
    enum               { bHasParent = 0x00 };
};

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template<class ValueTypeT>
struct FieldTraitsRecurseVecStore3Base : 
    public FieldTraitsRecurseVecStoreBase<ValueTypeT>
{
    enum              { bHasParent = 0x00 };
};

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template<class ValueTypeT>
struct FieldTraitsRecurseVecStore4Base : 
    public FieldTraitsRecurseVecStoreBase<ValueTypeT>
{
    enum              { bHasParent = 0x00 };
};


/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Vec2ub> :
    public FieldTraitsRecurseVecStore2Base<Vec2ub>
{
    static  DataType                _type;
    typedef FieldDataTraits<Vec2ub>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFVec2ub";           }
    static Char8    *getMName     (void) { return "MFVec2ub";           }

    static Vec2ub    getDefault   (void) { return Vec2ub();             }

    static bool      getFromString(      Vec2ub  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Vec2ub &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Vec2ub::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Vec2ub> */
/*! \hideinhierarchy                               */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Vec3ub> :
    public FieldTraitsRecurseVecStore2Base<Vec3ub>
{
    static  DataType                _type;
    typedef FieldDataTraits<Vec3ub>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFVec3ub";           }
    static Char8    *getMName     (void) { return "MFVec3ub";           }

    static Vec3ub    getDefault   (void) { return Vec3ub();             }

    static bool      getFromString(      Vec3ub  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Vec3ub &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Vec3ub::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[2]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Vec3ub> */
/*! \hideinhierarchy                               */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Vec4ub> :
    public FieldTraitsRecurseVecStore2Base<Vec4ub>
{
    static  DataType                _type;
    typedef FieldDataTraits<Vec4ub>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFVec4ub";           }
    static Char8    *getMName     (void) { return "MFVec4ub";           }

    static Vec4ub    getDefault   (void) { return Vec4ub();             }

    static bool      getFromString(      Vec4ub  &outVal,
                                   const Char8  *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Vec4ub &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Vec4ub::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[2]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[3]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Vec4ub> */
/*! \hideinhierarchy                               */
#endif



#ifndef OSG_NO_INT8_PNT
/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Vec2b> :
    public FieldTraitsRecurseVecStore2Base<Vec2b>
{
    static  DataType                _type;
    typedef FieldDataTraits<Vec2b>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFVec2b";           }
    static Char8    *getMName     (void) { return "MFVec2b";           }

    static Vec2b    getDefault   (void) { return Vec2b();             }

    static bool      getFromString(      Vec2b  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Vec2b &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Vec2b::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Vec2b> */
/*! \hideinhierarchy                               */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Vec3b> :
    public FieldTraitsRecurseVecStore2Base<Vec3b>
{
    static  DataType                _type;
    typedef FieldDataTraits<Vec3b>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFVec3b";           }
    static Char8    *getMName     (void) { return "MFVec3b";           }

    static Vec3b    getDefault   (void) { return Vec3b();             }

    static bool      getFromString(      Vec3b  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Vec3b &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Vec3b::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[2]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Vec3b> */
/*! \hideinhierarchy                               */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Vec4b> :
    public FieldTraitsRecurseVecStore2Base<Vec4b>
{
    static  DataType                _type;
    typedef FieldDataTraits<Vec4b>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFVec4b";           }
    static Char8    *getMName     (void) { return "MFVec4b";           }

    static Vec4b    getDefault   (void) { return Vec4b();             }

    static bool      getFromString(      Vec4b  &outVal,
                                   const Char8  *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Vec4b &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Vec4b::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[2]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[3]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Vec4b> */
/*! \hideinhierarchy                               */
#endif
#endif


/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Vec2us> :
    public FieldTraitsRecurseVecStore2Base<Vec2us>
{
    static  DataType                _type;
    typedef FieldDataTraits<Vec2us>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFVec2us";           }
    static Char8    *getMName     (void) { return "MFVec2us";           }

    static Vec2us    getDefault   (void) { return Vec2us();             }

    static bool      getFromString(      Vec2us  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Vec2us &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Vec2us::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Vec2us> */
/*! \hideinhierarchy                               */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Vec3us> :
    public FieldTraitsRecurseVecStore2Base<Vec3us>
{
    static  DataType                _type;
    typedef FieldDataTraits<Vec3us>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFVec3us";           }
    static Char8    *getMName     (void) { return "MFVec3us";           }

    static Vec3us    getDefault   (void) { return Vec3us();             }

    static bool      getFromString(      Vec3us  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Vec3us &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Vec3us::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[2]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Vec3us> */
/*! \hideinhierarchy                               */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Vec4us> :
    public FieldTraitsRecurseVecStore2Base<Vec4us>
{
    static  DataType                _type;
    typedef FieldDataTraits<Vec4us>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFVec4us";           }
    static Char8    *getMName     (void) { return "MFVec4us";           }

    static Vec4us    getDefault   (void) { return Vec4us();             }

    static bool      getFromString(      Vec4us  &outVal,
                                   const Char8  *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Vec4us &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Vec4us::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[2]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[3]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Vec4us> */
/*! \hideinhierarchy                               */
#endif



/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Vec2s> :
    public FieldTraitsRecurseVecStore2Base<Vec2s>
{
    static  DataType                _type;
    typedef FieldDataTraits<Vec2s>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFVec2s";           }
    static Char8    *getMName     (void) { return "MFVec2s";           }

    static Vec2s    getDefault   (void) { return Vec2s();             }

    static bool      getFromString(      Vec2s  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Vec2s &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Vec2s::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Vec2s> */
/*! \hideinhierarchy                               */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Vec3s> :
    public FieldTraitsRecurseVecStore2Base<Vec3s>
{
    static  DataType                _type;
    typedef FieldDataTraits<Vec3s>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFVec3s";           }
    static Char8    *getMName     (void) { return "MFVec3s";           }

    static Vec3s    getDefault   (void) { return Vec3s();             }

    static bool      getFromString(      Vec3s  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Vec3s &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Vec3s::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[2]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Vec3s> */
/*! \hideinhierarchy                               */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Vec4s> :
    public FieldTraitsRecurseVecStore2Base<Vec4s>
{
    static  DataType                _type;
    typedef FieldDataTraits<Vec4s>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFVec4s";           }
    static Char8    *getMName     (void) { return "MFVec4s";           }

    static Vec4s    getDefault   (void) { return Vec4s();             }

    static bool      getFromString(      Vec4s  &outVal,
                                   const Char8  *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Vec4s &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Vec4s::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[2]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[3]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Vec4s> */
/*! \hideinhierarchy                               */
#endif



/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Vec2f> :
    public FieldTraitsRecurseVecStore2Base<Vec2f>
{
    static  DataType                _type;
    typedef FieldDataTraits<Vec2f>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFVec2f";           }
    static Char8    *getMName     (void) { return "MFVec2f";           }

    static Vec2f    getDefault   (void) { return Vec2f();             }

    static bool      getFromString(      Vec2f  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Vec2f &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Vec2f::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Vec2f> */
/*! \hideinhierarchy                               */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Vec3f> :
    public FieldTraitsRecurseVecStore2Base<Vec3f>
{
    static  DataType                _type;
    typedef FieldDataTraits<Vec3f>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFVec3f";           }
    static Char8    *getMName     (void) { return "MFVec3f";           }

    static Vec3f    getDefault   (void) { return Vec3f();             }

    static bool      getFromString(      Vec3f  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Vec3f &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Vec3f::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[2]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Vec3f> */
/*! \hideinhierarchy                               */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Vec4f> :
    public FieldTraitsRecurseVecStore2Base<Vec4f>
{
    static  DataType                _type;
    typedef FieldDataTraits<Vec4f>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFVec4f";           }
    static Char8    *getMName     (void) { return "MFVec4f";           }

    static Vec4f    getDefault   (void) { return Vec4f();             }

    static bool      getFromString(      Vec4f  &outVal,
                                   const Char8  *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Vec4f &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Vec4f::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[2]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[3]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Vec4f> */
/*! \hideinhierarchy                               */
#endif



/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Vec2d> :
    public FieldTraitsRecurseVecStore2Base<Vec2d>
{
    static  DataType                _type;
    typedef FieldDataTraits<Vec2d>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFVec2d";           }
    static Char8    *getMName     (void) { return "MFVec2d";           }

    static Vec2d    getDefault   (void) { return Vec2d();             }

    static bool      getFromString(      Vec2d  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Vec2d &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Vec2d::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Vec2d> */
/*! \hideinhierarchy                               */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Vec3d> :
    public FieldTraitsRecurseVecStore2Base<Vec3d>
{
    static  DataType                _type;
    typedef FieldDataTraits<Vec3d>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFVec3d";           }
    static Char8    *getMName     (void) { return "MFVec3d";           }

    static Vec3d    getDefault   (void) { return Vec3d();             }

    static bool      getFromString(      Vec3d  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Vec3d &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Vec3d::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[2]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Vec3d> */
/*! \hideinhierarchy                               */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Vec4d> :
    public FieldTraitsRecurseVecStore2Base<Vec4d>
{
    static  DataType                _type;
    typedef FieldDataTraits<Vec4d>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFVec4d";           }
    static Char8    *getMName     (void) { return "MFVec4d";           }

    static Vec4d    getDefault   (void) { return Vec4d();             }

    static bool      getFromString(      Vec4d  &outVal,
                                   const Char8  *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Vec4d &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Vec4d::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[2]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[3]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Vec4d> */
/*! \hideinhierarchy                               */
#endif



/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Vec2ld> :
    public FieldTraitsRecurseVecStore2Base<Vec2ld>
{
    static  DataType                _type;
    typedef FieldDataTraits<Vec2ld>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFVec2ld";           }
    static Char8    *getMName     (void) { return "MFVec2ld";           }

    static Vec2ld    getDefault   (void) { return Vec2ld();             }

    static bool      getFromString(      Vec2ld  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Vec2ld &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Vec2ld::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Vec2ld> */
/*! \hideinhierarchy                               */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Vec3ld> :
    public FieldTraitsRecurseVecStore2Base<Vec3ld>
{
    static  DataType                _type;
    typedef FieldDataTraits<Vec3ld>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFVec3ld";           }
    static Char8    *getMName     (void) { return "MFVec3ld";           }

    static Vec3ld    getDefault   (void) { return Vec3ld();             }

    static bool      getFromString(      Vec3ld  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Vec3ld &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Vec3ld::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[2]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Vec3ld> */
/*! \hideinhierarchy                               */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Vec4ld> :
    public FieldTraitsRecurseVecStore2Base<Vec4ld>
{
    static  DataType                _type;
    typedef FieldDataTraits<Vec4ld>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFVec4ld";           }
    static Char8    *getMName     (void) { return "MFVec4ld";           }

    static Vec4ld    getDefault   (void) { return Vec4ld();             }

    static bool      getFromString(      Vec4ld  &outVal,
                                   const Char8  *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Vec4ld &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Vec4ld::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[2]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[3]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Vec4ld> */
/*! \hideinhierarchy                               */
#endif



/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Pnt2ub> :
    public FieldTraitsRecurseVecStore2Base<Pnt2ub>
{
    static  DataType                _type;
    typedef FieldDataTraits<Pnt2ub>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFPnt2ub";           }
    static Char8    *getMName     (void) { return "MFPnt2ub";           }

    static Pnt2ub    getDefault   (void) { return Pnt2ub();             }

    static bool      getFromString(      Pnt2ub  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Pnt2ub &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Pnt2ub::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Pnt2ub> */
/*! \hideinhierarchy                               */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Pnt3ub> :
    public FieldTraitsRecurseVecStore2Base<Pnt3ub>
{
    static  DataType                _type;
    typedef FieldDataTraits<Pnt3ub>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFPnt3ub";           }
    static Char8    *getMName     (void) { return "MFPnt3ub";           }

    static Pnt3ub    getDefault   (void) { return Pnt3ub();             }

    static bool      getFromString(      Pnt3ub  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Pnt3ub &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Pnt3ub::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[2]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Pnt3ub> */
/*! \hideinhierarchy                               */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Pnt4ub> :
    public FieldTraitsRecurseVecStore2Base<Pnt4ub>
{
    static  DataType                _type;
    typedef FieldDataTraits<Pnt4ub>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFPnt4ub";           }
    static Char8    *getMName     (void) { return "MFPnt4ub";           }

    static Pnt4ub    getDefault   (void) { return Pnt4ub();             }

    static bool      getFromString(      Pnt4ub  &outVal,
                                   const Char8  *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Pnt4ub &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Pnt4ub::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[2]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[3]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Pnt4ub> */
/*! \hideinhierarchy                               */
#endif


#ifndef OSG_NO_INT8_PNT
/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Pnt2b> :
    public FieldTraitsRecurseVecStore2Base<Pnt2b>
{
    static  DataType                _type;
    typedef FieldDataTraits<Pnt2b>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFPnt2b";           }
    static Char8    *getMName     (void) { return "MFPnt2b";           }

    static Pnt2b    getDefault   (void) { return Pnt2b();             }

    static bool      getFromString(      Pnt2b  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Pnt2b &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Pnt2b::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Pnt2b> */
/*! \hideinhierarchy                               */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Pnt3b> :
    public FieldTraitsRecurseVecStore2Base<Pnt3b>
{
    static  DataType                _type;
    typedef FieldDataTraits<Pnt3b>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFPnt3b";           }
    static Char8    *getMName     (void) { return "MFPnt3b";           }

    static Pnt3b    getDefault   (void) { return Pnt3b();             }

    static bool      getFromString(      Pnt3b  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Pnt3b &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Pnt3b::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[2]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Pnt3b> */
/*! \hideinhierarchy                               */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Pnt4b> :
    public FieldTraitsRecurseVecStore2Base<Pnt4b>
{
    static  DataType                _type;
    typedef FieldDataTraits<Pnt4b>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFPnt4b";           }
    static Char8    *getMName     (void) { return "MFPnt4b";           }

    static Pnt4b    getDefault   (void) { return Pnt4b();             }

    static bool      getFromString(      Pnt4b  &outVal,
                                   const Char8  *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Pnt4b &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Pnt4b::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[2]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[3]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Pnt4b> */
/*! \hideinhierarchy                               */
#endif
#endif


/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Pnt2us> :
    public FieldTraitsRecurseVecStore2Base<Pnt2us>
{
    static  DataType                _type;
    typedef FieldDataTraits<Pnt2us>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFPnt2us";           }
    static Char8    *getMName     (void) { return "MFPnt2us";           }

    static Pnt2us    getDefault   (void) { return Pnt2us();             }

    static bool      getFromString(      Pnt2us  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Pnt2us &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Pnt2us::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Pnt2us> */
/*! \hideinhierarchy                               */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Pnt3us> :
    public FieldTraitsRecurseVecStore2Base<Pnt3us>
{
    static  DataType                _type;
    typedef FieldDataTraits<Pnt3us>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFPnt3us";           }
    static Char8    *getMName     (void) { return "MFPnt3us";           }

    static Pnt3us    getDefault   (void) { return Pnt3us();             }

    static bool      getFromString(      Pnt3us  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Pnt3us &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Pnt3us::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[2]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Pnt3us> */
/*! \hideinhierarchy                               */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Pnt4us> :
    public FieldTraitsRecurseVecStore2Base<Pnt4us>
{
    static  DataType                _type;
    typedef FieldDataTraits<Pnt4us>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFPnt4us";           }
    static Char8    *getMName     (void) { return "MFPnt4us";           }

    static Pnt4us    getDefault   (void) { return Pnt4us();             }

    static bool      getFromString(      Pnt4us  &outVal,
                                   const Char8  *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Pnt4us &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Pnt4us::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[2]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[3]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Pnt4us> */
/*! \hideinhierarchy                               */
#endif



/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Pnt2s> :
    public FieldTraitsRecurseVecStore2Base<Pnt2s>
{
    static  DataType                _type;
    typedef FieldDataTraits<Pnt2s>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFPnt2s";           }
    static Char8    *getMName     (void) { return "MFPnt2s";           }

    static Pnt2s    getDefault   (void) { return Pnt2s();             }

    static bool      getFromString(      Pnt2s  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Pnt2s &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Pnt2s::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Pnt2s> */
/*! \hideinhierarchy                               */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Pnt3s> :
    public FieldTraitsRecurseVecStore2Base<Pnt3s>
{
    static  DataType                _type;
    typedef FieldDataTraits<Pnt3s>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFPnt3s";           }
    static Char8    *getMName     (void) { return "MFPnt3s";           }

    static Pnt3s    getDefault   (void) { return Pnt3s();             }

    static bool      getFromString(      Pnt3s  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Pnt3s &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Pnt3s::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[2]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Pnt3s> */
/*! \hideinhierarchy                               */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Pnt4s> :
    public FieldTraitsRecurseVecStore2Base<Pnt4s>
{
    static  DataType                _type;
    typedef FieldDataTraits<Pnt4s>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFPnt4s";           }
    static Char8    *getMName     (void) { return "MFPnt4s";           }

    static Pnt4s    getDefault   (void) { return Pnt4s();             }

    static bool      getFromString(      Pnt4s  &outVal,
                                   const Char8  *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Pnt4s &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Pnt4s::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[2]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[3]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Pnt4s> */
/*! \hideinhierarchy                               */
#endif



/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Pnt2f> :
    public FieldTraitsRecurseVecStore2Base<Pnt2f>
{
    static  DataType                _type;
    typedef FieldDataTraits<Pnt2f>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFPnt2f";           }
    static Char8    *getMName     (void) { return "MFPnt2f";           }

    static Pnt2f    getDefault   (void) { return Pnt2f();             }

    static bool      getFromString(      Pnt2f  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Pnt2f &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Pnt2f::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Pnt2f> */
/*! \hideinhierarchy                               */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Pnt3f> :
    public FieldTraitsRecurseVecStore2Base<Pnt3f>
{
    static  DataType                _type;
    typedef FieldDataTraits<Pnt3f>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFPnt3f";           }
    static Char8    *getMName     (void) { return "MFPnt3f";           }

    static Pnt3f    getDefault   (void) { return Pnt3f();             }

    static bool      getFromString(      Pnt3f  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Pnt3f &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Pnt3f::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[2]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Pnt3f> */
/*! \hideinhierarchy                               */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Pnt4f> :
    public FieldTraitsRecurseVecStore2Base<Pnt4f>
{
    static  DataType                _type;
    typedef FieldDataTraits<Pnt4f>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFPnt4f";           }
    static Char8    *getMName     (void) { return "MFPnt4f";           }

    static Pnt4f    getDefault   (void) { return Pnt4f();             }

    static bool      getFromString(      Pnt4f  &outVal,
                                   const Char8  *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Pnt4f &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Pnt4f::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[2]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[3]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Pnt4f> */
/*! \hideinhierarchy                               */
#endif



/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Pnt2d> :
    public FieldTraitsRecurseVecStore2Base<Pnt2d>
{
    static  DataType                _type;
    typedef FieldDataTraits<Pnt2d>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFPnt2d";           }
    static Char8    *getMName     (void) { return "MFPnt2d";           }

    static Pnt2d    getDefault   (void) { return Pnt2d();             }

    static bool      getFromString(      Pnt2d  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Pnt2d &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Pnt2d::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Pnt2d> */
/*! \hideinhierarchy                               */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Pnt3d> :
    public FieldTraitsRecurseVecStore2Base<Pnt3d>
{
    static  DataType                _type;
    typedef FieldDataTraits<Pnt3d>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFPnt3d";           }
    static Char8    *getMName     (void) { return "MFPnt3d";           }

    static Pnt3d    getDefault   (void) { return Pnt3d();             }

    static bool      getFromString(      Pnt3d  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Pnt3d &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Pnt3d::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[2]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Pnt3d> */
/*! \hideinhierarchy                               */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Pnt4d> :
    public FieldTraitsRecurseVecStore2Base<Pnt4d>
{
    static  DataType                _type;
    typedef FieldDataTraits<Pnt4d>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFPnt4d";           }
    static Char8    *getMName     (void) { return "MFPnt4d";           }

    static Pnt4d    getDefault   (void) { return Pnt4d();             }

    static bool      getFromString(      Pnt4d  &outVal,
                                   const Char8  *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Pnt4d &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Pnt4d::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[2]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[3]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Pnt4d> */
/*! \hideinhierarchy                               */
#endif



/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Pnt2ld> :
    public FieldTraitsRecurseVecStore2Base<Pnt2ld>
{
    static  DataType                _type;
    typedef FieldDataTraits<Pnt2ld>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFPnt2ld";           }
    static Char8    *getMName     (void) { return "MFPnt2ld";           }

    static Pnt2ld    getDefault   (void) { return Pnt2ld();             }

    static bool      getFromString(      Pnt2ld  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Pnt2ld &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Pnt2ld::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Pnt2ld> */
/*! \hideinhierarchy                               */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Pnt3ld> :
    public FieldTraitsRecurseVecStore2Base<Pnt3ld>
{
    static  DataType                _type;
    typedef FieldDataTraits<Pnt3ld>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFPnt3ld";           }
    static Char8    *getMName     (void) { return "MFPnt3ld";           }

    static Pnt3ld    getDefault   (void) { return Pnt3ld();             }

    static bool      getFromString(      Pnt3ld  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Pnt3ld &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Pnt3ld::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[2]));
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Pnt3ld> */
/*! \hideinhierarchy                               */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Pnt4ld> :
    public FieldTraitsRecurseVecStore2Base<Pnt4ld>
{
    static  DataType                _type;
    typedef FieldDataTraits<Pnt4ld>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFPnt4ld";           }
    static Char8    *getMName     (void) { return "MFPnt4ld";           }

    static Pnt4ld    getDefault   (void) { return Pnt4ld();             }

    static bool      getFromString(      Pnt4ld  &outVal,
                                   const Char8  *&inVal)
    {
        outVal.setValueFromCString(inVal);
        
        return true;
    }

    static void      putToString  (const      Pnt4ld &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Pnt4ld::ValueType> TypeTrait;
        
        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[2]));
        outStr.append("  ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[3]));
   }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseVecStore2Base<Pnt4ld> */
/*! \hideinhierarchy                               */
#endif


#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

OSG_END_NAMESPACE

#define OSGVECFIELDDATATYPE_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSG_VECFIELDDATATYPE_H_ */



