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


#ifndef _OSG_VECFIELDDATATYPE_H_
#define _OSG_VECFIELDDATATYPE_H_

#include <OSGBase.h>
#include <OSGFieldDataType.h>
#include <OSGVector.h>

#include <string>

OSG_BEGIN_NAMESPACE

/*! \file OSGVecFieldDataType.h
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
    \brief OpenSG Vec Field Data Types  
*/

/*! \brief VecStorage field traits recurse base
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
*/

template<class ValueTypeT>
struct FieldTraitsRecurseVecStoreBase : public Traits
{
    enum                     { bHasParent = 0x00 };

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
        pMem.put(&oObject, getBinSize(oObject));
    }

    static void   copyToBin  (      BinaryDataHandler &pMem, 
                              const ValueTypeT        *pObjectStore,
                                    UInt32             uiNumObjects)
    {
        pMem.put(&pObjectStore[0], getBinSize(pObjectStore, uiNumObjects));
    }

    static void   copyFromBin(      BinaryDataHandler &pMem, 
                                    ValueTypeT        &oObject)
    {
        pMem.get(&oObject, getBinSize(oObject));
    }

    static void   copyFromBin(      BinaryDataHandler &pMem, 
                                    ValueTypeT        *pObjectStore,
                                    UInt32             uiNumObjects)
    {
        pMem.get(&pObjectStore[0], getBinSize(pObjectStore, uiNumObjects));
    }
};

/*! \brief VecStorage2 field traits recurse base
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
*/

template<class ValueTypeT>
struct FieldTraitsRecurseVecStore2Base : 
    public FieldTraitsRecurseVecStoreBase<ValueTypeT> 
{
    enum { bHasParent = 0x00 };
};

/*! \brief VecStorage3 field traits recurse base
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
*/

template<class ValueTypeT>
struct FieldTraitsRecurseVecStore3Base : 
    public FieldTraitsRecurseVecStoreBase<ValueTypeT>
{
    enum { bHasParent = 0x00 };
};

/*! \brief VecStorage4 field traits recurse base
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
*/

template<class ValueTypeT>
struct FieldTraitsRecurseVecStore4Base : 
    public FieldTraitsRecurseVecStoreBase<ValueTypeT>
{
    enum { bHasParent = 0x00 };
};

/*! \brief Vec2f field traits 
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
*/

template <>
struct FieldDataTraits<Vec2f> : public FieldTraitsRecurseVecStore2Base<Vec2f>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable   | 
                                           FromStringConvertable };
    enum             { bHasParent        = 0x01                  };

    static DataType &getType      (void) { return _type;         }

    static Char8    *getSName     (void) { return "SFVec2f";     }
    static Char8    *getMName     (void) { return "MFVec2f";     }

    static Vec2f     getDefault   (void) { return Vec2f();       }

    static bool      getFromString(      Vec2f  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValue(inVal);
        
        return true;
    }

    static void      putToString  (const Vec2f  &inVal,
                                         string &outStr)
    {
        typedef TypeConstants<Vec2f::ValueType> TypeConst;
        
        outStr.assign(TypeConst::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeConst::putToString((inVal.getValues())[1]));
    }
};


/*! \brief Vec3f field traits 
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
*/

template <>
struct FieldDataTraits<Vec3f> : public FieldTraitsRecurseVecStore3Base<Vec3f>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable   | 
                                           FromStringConvertable };
    enum             { bHasParent        = 0x01                  };

    static DataType &getType      (void) { return _type;         }

    static Char8    *getSName     (void) { return "SFVec3f";     }
    static Char8    *getMName     (void) { return "MFVec3f";     }

    static Vec3f     getDefault   (void) { return Vec3f();       }

    static bool      getFromString(      Vec3f  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValue(inVal);
        
        return true;
    }

    static void      putToString  (const Vec3f  &inVal,
                                         string &outStr)
    {
        typedef TypeConstants<Vec3f::ValueType> TypeConst;

        outStr.assign(TypeConst::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeConst::putToString((inVal.getValues())[1]));
        outStr.append("  ");
        outStr.append(TypeConst::putToString((inVal.getValues())[2]));
    }
};


/*! \brief Vec4f field traits
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
*/

template <>
struct FieldDataTraits<Vec4f> : public FieldTraitsRecurseVecStore4Base<Vec4f>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable   | 
                                           FromStringConvertable };
    enum             { bHasParent        = 0x01                  };

    static DataType &getType      (void) { return _type;         }

    static Char8    *getSName     (void) { return "SFVec4f";     }
    static Char8    *getMName     (void) { return "MFVec4f";     }

    static Vec4f     getDefault   (void) { return Vec4f();       }

    static bool      getFromString(      Vec4f  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValue(inVal);

        return true;
    }

    static void      putToString  (const Vec4f  &inVal,
                                         string &outStr)
    {
        typedef TypeConstants<Vec4f::ValueType> TypeConst;

        outStr.assign(TypeConst::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeConst::putToString((inVal.getValues())[1]));
        outStr.append("  ");
        outStr.append(TypeConst::putToString((inVal.getValues())[2]));
        outStr.append("  ");
        outStr.append(TypeConst::putToString((inVal.getValues())[3]));
    }
};

/*! \brief Vec4ub field traits
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields 
*/

template <>
struct FieldDataTraits<Vec4ub> : public FieldTraitsRecurseVecStore4Base<Vec4ub>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable   | 
                                           FromStringConvertable };
    enum             { bHasParent        = 0x01                  };

    static DataType &getType      (void) { return _type;         }

    static Char8    *getSName     (void) { return "SFVec4ub";    }
    static Char8    *getMName     (void) { return "MFVec4ub";    }

    static Vec4ub    getDefault   (void) { return Vec4ub();      }

    static bool      getFromString(      Vec4ub  &outVal,
                                   const Char8  *&inVal)
    {
        outVal.setValue(inVal);
        
        return true;
    }

    static void      putToString  (const Vec4ub &inVal,
                                         string &outStr)
    {
        typedef TypeConstants<Vec4ub::ValueType> TypeConst;

        outStr.assign(TypeConst::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeConst::putToString((inVal.getValues())[1]));
        outStr.append("  ");
        outStr.append(TypeConst::putToString((inVal.getValues())[2]));
        outStr.append("  ");
        outStr.append(TypeConst::putToString((inVal.getValues())[3]));
    }
};

/*! \brief Pnt2f field traits
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
*/

template <>
struct FieldDataTraits<Pnt2f> : public FieldTraitsRecurseVecStore2Base<Pnt2f>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable   | 
                                           FromStringConvertable };
    enum             { bHasParent        = 0x01                  };

    static DataType &getType      (void) { return _type;         }

    static Char8    *getSName     (void) { return "SFPnt2f";     }
    static Char8    *getMName     (void) { return "MFPnt2f";     }

    static Pnt2f     getDefault   (void) { return Pnt2f();       }

    static bool      getFromString(      Pnt2f  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValue(inVal);

        return true;
    }

    static void      putToString  (const Pnt2f  &inVal,
                                         string &outStr)
    {
        typedef TypeConstants<Pnt2f::ValueType> TypeConst;
        
        outStr.assign(TypeConst::putToString((inVal.getValues())[0])); 
        outStr.append("  ");
        outStr.append(TypeConst::putToString((inVal.getValues())[1]));
    }
};


/*! \brief Pnt2d field traits
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
*/

template <>
struct FieldDataTraits<Pnt2d> : public FieldTraitsRecurseVecStore2Base<Pnt2d>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable   | 
                                           FromStringConvertable };
    enum             { bHasParent        = 0x01                  };

    static DataType &getType      (void) { return _type;         }

    static Char8    *getSName     (void) { return "SFPnt2d";     }
    static Char8    *getMName     (void) { return "MFPnt2d";     }

    static Pnt2d     getDefault   (void) { return Pnt2d();       }

    static bool      getFromString(      Pnt2d  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValue(inVal);

        return true;
    }

    static void      putToString  (const Pnt2d  &inVal,
                                         string &outStr)
    {
        typedef TypeConstants<Pnt2d::ValueType> TypeConst;
        
        outStr.assign(TypeConst::putToString((inVal.getValues())[0])); 
        outStr.append("  ");
        outStr.append(TypeConst::putToString((inVal.getValues())[1]));
    }
};


/*! \brief Pnt3f field traits
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
*/

template <>
struct FieldDataTraits<Pnt3f> : public FieldTraitsRecurseVecStore3Base<Pnt3f>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable   | 
                                           FromStringConvertable };
    enum             { bHasParent        = 0x01                  };

    static DataType &getType      (void) { return _type;         }

    static Char8    *getSName     (void) { return "SFPnt3f";     }
    static Char8    *getMName     (void) { return "MFPnt3f";     }

    static Pnt3f     getDefault   (void) { return Pnt3f();       }

    static bool      getFromString(      Pnt3f  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValue(inVal);
        return false;
    }

    static void      putToString  (const Pnt3f  &inVal,
                                         string &outStr)
    {
        typedef TypeConstants<Pnt3f::ValueType> TypeConst;
        
        outStr.assign(TypeConst::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeConst::putToString((inVal.getValues())[1]));
        outStr.append("  ");
        outStr.append(TypeConst::putToString((inVal.getValues())[2]));
    }
};


/*! \brief Pnt3d field traits
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
*/

template <>
struct FieldDataTraits<Pnt3d> : public FieldTraitsRecurseVecStore3Base<Pnt3d>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable   | 
                                           FromStringConvertable };
    enum             { bHasParent        = 0x01                  };

    static DataType &getType      (void) { return _type;         }

    static Char8    *getSName     (void) { return "SFPnt3d";     }
    static Char8    *getMName     (void) { return "MFPnt3d";     }

    static Pnt3d     getDefault   (void) { return Pnt3d();       }

    static bool      getFromString(      Pnt3d  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValue(inVal);
        return false;
    }

    static void      putToString  (const Pnt3d  &inVal,
                                         string &outStr)
    {
        typedef TypeConstants<Pnt3d::ValueType> TypeConst;

        outStr.assign(TypeConst::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeConst::putToString((inVal.getValues())[1]));
        outStr.append("  ");
        outStr.append(TypeConst::putToString((inVal.getValues())[2]));
    }
};

/*! \brief Pnt4f field traits
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
*/

template <>
struct FieldDataTraits<Pnt4f> : public FieldTraitsRecurseVecStore4Base<Pnt4f>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable   | 
                                           FromStringConvertable };
    enum             { bHasParent        = 0x01                  };

    static DataType &getType      (void) { return _type;         }

    static Char8    *getSName     (void) { return "SFPnt4f";     }

    static Char8    *getMName     (void) { return "MFPnt4f";     }

    static Pnt4f     getDefault   (void) { return Pnt4f();       }

    static bool      getFromString(      Pnt4f  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValue(inVal);
        return false;
    }

    static void      putToString  (const Pnt4f  &inVal,
                                         string &outStr)
    {
        typedef TypeConstants<Pnt4f::ValueType> TypeConst;

        outStr.assign(TypeConst::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeConst::putToString((inVal.getValues())[1]));
        outStr.append("  ");
        outStr.append(TypeConst::putToString((inVal.getValues())[2]));
        outStr.append("  ");
        outStr.append(TypeConst::putToString((inVal.getValues())[3]));
    }
};

/*! \brief Pnt4d field traits
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
*/

template <>
struct FieldDataTraits<Pnt4d> : public FieldTraitsRecurseVecStore4Base<Pnt4d>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable   | 
                                           FromStringConvertable };
    enum             { bHasParent        = 0x01                  };

    static DataType &getType      (void) { return _type;         }

    static Char8    *getSName     (void) { return "SFPnt4d";     }

    static Char8    *getMName     (void) { return "MFPnt4d";     }

    static Pnt4d     getDefault   (void) { return Pnt4d();       }

    static bool      getFromString(      Pnt4d  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValue(inVal);
        return false;
    }

    static void      putToString  (const Pnt4d  &inVal,
                                         string &outStr)
    {
        typedef TypeConstants<Pnt4d::ValueType> TypeConst;

        outStr.assign(TypeConst::putToString((inVal.getValues())[0]));
        outStr.append("  ");
        outStr.append(TypeConst::putToString((inVal.getValues())[1]));
        outStr.append("  ");
        outStr.append(TypeConst::putToString((inVal.getValues())[2]));
        outStr.append("  ");
        outStr.append(TypeConst::putToString((inVal.getValues())[3]));
    }
};

OSG_END_NAMESPACE

#define OSGVECFIELDDATATYPE_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSG_VECFIELDDATATYPE_H_ */



