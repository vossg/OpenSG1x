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

/*! \file OSGVecFieldDataType.h
    \ingroup GrpBaseField
    \ingroup GrpBaseFieldTraits
*/


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
struct FieldDataTraits<Vec2f> : public FieldTraitsRecurseVecStore2Base<Vec2f>
{
    static  DataType               _type;
    typedef FieldDataTraits<Vec2f>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFVec2f";           }
    static Char8    *getMName     (void) { return "MFVec2f";           }

    static Vec2f     getDefault   (void) { return Vec2f();             }

    static bool      getFromString(      Vec2f  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValue(inVal);
        
        return true;
    }

    static void      putToString  (const      Vec2f  &inVal,
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
struct FieldDataTraits<Vec3f> : public FieldTraitsRecurseVecStore3Base<Vec3f>
{
    static  DataType               _type;
    typedef FieldDataTraits<Vec3f>  Self;


    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFVec3f";           }
    static Char8    *getMName     (void) { return "MFVec3f";           }

    static Vec3f     getDefault   (void) { return Vec3f();             }

    static bool      getFromString(      Vec3f  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValue(inVal);
        
        return true;
    }

    static void      putToString  (const      Vec3f  &inVal,
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
/*! \class  FieldTraitsRecurseVecStore3Base<Vec3f> */
/*! \hideinhierarchy                               */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldDataTraits<Vec4f> : public FieldTraitsRecurseVecStore4Base<Vec4f>
{
    static  DataType               _type;
    typedef FieldDataTraits<Vec4f>  Self;

    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFVec4f";           }
    static Char8    *getMName     (void) { return "MFVec4f";           }

    static Vec4f     getDefault   (void) { return Vec4f();             }

    static bool      getFromString(      Vec4f  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValue(inVal);

        return true;
    }

    static void      putToString  (const      Vec4f  &inVal,
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
/*! \class  FieldTraitsRecurseVecStore4Base<Vec4f> */
/*! \hideinhierarchy                               */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldDataTraits<Vec4ub> : public FieldTraitsRecurseVecStore4Base<Vec4ub>
{
    static  DataType                _type;
    typedef FieldDataTraits<Vec4ub>  Self;

    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFVec4ub";          }
    static Char8    *getMName     (void) { return "MFVec4ub";          }

    static Vec4ub    getDefault   (void) { return Vec4ub();            }

    static bool      getFromString(      Vec4ub  &outVal,
                                   const Char8  *&inVal)
    {
        outVal.setValue(inVal);
        
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
/*! \class  FieldTraitsRecurseVecStore4Base<Vec4ub> */
/*! \hideinhierarchy                                */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldDataTraits<Pnt2f> : public FieldTraitsRecurseVecStore2Base<Pnt2f>
{
    static  DataType               _type;
    typedef FieldDataTraits<Pnt2f>  Self;

    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFPnt2f";           }
    static Char8    *getMName     (void) { return "MFPnt2f";           }

    static Pnt2f     getDefault   (void) { return Pnt2f();             }

    static bool      getFromString(      Pnt2f  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValue(inVal);

        return true;
    }

    static void      putToString  (const      Pnt2f  &inVal,
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
struct FieldDataTraits<Pnt2d> : public FieldTraitsRecurseVecStore2Base<Pnt2d>
{
    static  DataType               _type;
    typedef FieldDataTraits<Pnt2d>  Self;

    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFPnt2d";           }
    static Char8    *getMName     (void) { return "MFPnt2d";           }

    static Pnt2d     getDefault   (void) { return Pnt2d();             }

    static bool      getFromString(      Pnt2d  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValue(inVal);

        return true;
    }

    static void      putToString  (const      Pnt2d  &inVal,
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
struct FieldDataTraits<Pnt3f> : public FieldTraitsRecurseVecStore3Base<Pnt3f>
{
    static  DataType               _type;
    typedef FieldDataTraits<Pnt3f>  Self;

    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFPnt3f";           }
    static Char8    *getMName     (void) { return "MFPnt3f";           }

    static Pnt3f     getDefault   (void) { return Pnt3f();             }

    static bool      getFromString(      Pnt3f  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValue(inVal);
        return false;
    }

    static void      putToString  (const      Pnt3f  &inVal,
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
/*! \class  FieldTraitsRecurseVecStore3Base<Pnt3f> */
/*! \hideinhierarchy                               */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldDataTraits<Pnt3d> : public FieldTraitsRecurseVecStore3Base<Pnt3d>
{
    static  DataType               _type;
    typedef FieldDataTraits<Pnt3d>  Self;

    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFPnt3d";           }
    static Char8    *getMName     (void) { return "MFPnt3d";           }

    static Pnt3d     getDefault   (void) { return Pnt3d();             }

    static bool      getFromString(      Pnt3d  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValue(inVal);
        return false;
    }

    static void      putToString  (const      Pnt3d  &inVal,
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
/*! \class  FieldTraitsRecurseVecStore3Base<Pnt3d> */
/*! \hideinhierarchy                               */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldDataTraits<Pnt4f> : public FieldTraitsRecurseVecStore4Base<Pnt4f>
{
    static  DataType               _type;
    typedef FieldDataTraits<Pnt4f>  Self;

    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFPnt4f";           }

    static Char8    *getMName     (void) { return "MFPnt4f";           }

    static Pnt4f     getDefault   (void) { return Pnt4f();             }

    static bool      getFromString(      Pnt4f  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValue(inVal);
        return false;
    }

    static void      putToString  (const      Pnt4f  &inVal,
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
/*! \class  FieldTraitsRecurseVecStore4Base<Pnt4f> */
/*! \hideinhierarchy                               */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct FieldDataTraits<Pnt4d> : public FieldTraitsRecurseVecStore4Base<Pnt4d>
{
    static  DataType               _type;
    typedef FieldDataTraits<Pnt4d>  Self;

    enum             { StringConvertable = Self::ToStringConvertable   | 
                                           Self::FromStringConvertable };

    enum             { bHasParent        = 0x01                        };

    static DataType &getType      (void) { return _type;               }

    static Char8    *getSName     (void) { return "SFPnt4d";           }

    static Char8    *getMName     (void) { return "MFPnt4d";           }

    static Pnt4d     getDefault   (void) { return Pnt4d();             }

    static bool      getFromString(      Pnt4d  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValue(inVal);
        return false;
    }

    static void      putToString  (const      Pnt4d  &inVal,
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
/*! \class  FieldTraitsRecurseVecStore4Base<Pnt4d> */
/*! \hideinhierarchy                               */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

OSG_END_NAMESPACE

#define OSGVECFIELDDATATYPE_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSG_VECFIELDDATATYPE_H_ */



