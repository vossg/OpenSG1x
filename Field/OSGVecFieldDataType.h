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

template<class ValueTypeT>
struct FieldTraitsRecurseVecStoreBase : public Traits
{
    enum                         { bHasParent        = 0x00 };

    static UInt32 getBinSize(const ValueTypeT &)
    {
        return sizeof(ValueTypeT);
    }

    static UInt32 getBinSize(const ValueTypeT *,
                                   UInt32      uiNumObjects)
    {
        return sizeof(ValueTypeT) * uiNumObjects;
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const ValueTypeT        &oObject)
    {
        pMem.put(&oObject, getBinSize(oObject));
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const ValueTypeT        *pObjectStore,
                                UInt32             uiNumObjects)
    {
        pMem.put(&pObjectStore[0], getBinSize(pObjectStore, uiNumObjects));
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            ValueTypeT        &oObject)
    {
        pMem.get(&oObject, getBinSize(oObject));
    }

    static void copyFromBin(BinaryDataHandler &pMem, 
                            ValueTypeT        *pObjectStore,
                            UInt32             uiNumObjects)
    {
        pMem.get(&pObjectStore[0], getBinSize(pObjectStore, uiNumObjects));
    }
};

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief VecStorage4 field traits 
 */

template<class ValueTypeT>
struct FieldTraitsRecurseVecStore2Base : 
    public FieldTraitsRecurseVecStoreBase<ValueTypeT> 
{
    enum { bHasParent = 0x00 };
};

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief VecStorage4 field traits 
 */

template<class ValueTypeT>
struct FieldTraitsRecurseVecStore3Base : 
    public FieldTraitsRecurseVecStoreBase<ValueTypeT>
{
    enum { bHasParent = 0x00 };
};

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief VecStorage4 field traits 
 */

template<class ValueTypeT>
struct FieldTraitsRecurseVecStore4Base : 
    public FieldTraitsRecurseVecStoreBase<ValueTypeT>
{
    enum { bHasParent = 0x00 };
};

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief Vec2f field traits 
 */

template <>
struct FieldDataTraits<Vec2f> : public FieldTraitsRecurseVecStore2Base<Vec2f>
{
    static DataType                _type;

    enum                           { StringConvertable = ToStringConvertable | 
                                                       FromStringConvertable };
    enum                           { bHasParent        = 0x01                };

    static DataType &getType      (void) { return _type;     }

    static Char8    *getSName     (void) { return "SFVec2f"; }
    static Char8    *getMName     (void) { return "MFVec2f"; }
    static Vec2f     getDefault   (void) { return Vec2f();   }

    static Bool      getFromString(      Vec2f  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValue(inVal);
        
        return true;
    }

    static void   putToString(const Vec2f  &inVal,
                                    string &outVal)
    {
        outVal.assign( TypeConstants<Vec2f::ValueType>::putToString((inVal.getValues())[0]) );
      outVal.append( "  " );
      outVal.append( TypeConstants<Vec2f::ValueType>::putToString((inVal.getValues())[1]) );
    }
};


/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief Vec3f field traits 
 */

template <>
struct FieldDataTraits<Vec3f> : public FieldTraitsRecurseVecStore3Base<Vec3f>
{
    static DataType              _type;

    enum                         { StringConvertable = ToStringConvertable | 
                                                       FromStringConvertable };
    enum                         { bHasParent        = 0x01                  };

    static DataType &getType      (void) { return _type;     }
    static Char8    *getSName     (void) { return "SFVec3f"; }
    static Char8    *getMName     (void) { return "MFVec3f"; }

    static Vec3f     getDefault   (void) { return Vec3f();   }

    static Bool      getFromString(      Vec3f  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValue(inVal);

        return true;
    }

    static void   putToString(const Vec3f  &inVal,
                                    string &outVal)
    {
       outVal.assign( TypeConstants<Vec3f::ValueType>::putToString((inVal.getValues())[0]) );
      outVal.append( "  " );
      outVal.append( TypeConstants<Vec3f::ValueType>::putToString((inVal.getValues())[1]) );
      outVal.append( "  " );
      outVal.append( TypeConstants<Vec3f::ValueType>::putToString((inVal.getValues())[2]) );
    }
};


/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief Vec4f field traits 
 */

template <>
struct FieldDataTraits<Vec4f> : public FieldTraitsRecurseVecStore4Base<Vec4f>
{
    static DataType              _type;

    enum                         { StringConvertable = ToStringConvertable | 
                                                       FromStringConvertable };
    enum                         { bHasParent        = 0x01                  };

    static DataType &getType      (void) { return _type;     }

    static Char8    *getSName     (void) { return "SFVec4f"; }

    static Char8    *getMName     (void) { return "MFVec4f"; }

    static Vec4f     getDefault   (void) { return Vec4f();   }

    static Bool      getFromString(      Vec4f  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValue(inVal);

        return true;
    }

    static void   putToString(const Vec4f  &inVal,
                                    string &outVal)
    {
      outVal.assign( TypeConstants<Vec4f::ValueType>::putToString((inVal.getValues())[0]) );
      outVal.append( "  " );
      outVal.append( TypeConstants<Vec4f::ValueType>::putToString((inVal.getValues())[1]) );
      outVal.append( "  " );
      outVal.append( TypeConstants<Vec4f::ValueType>::putToString((inVal.getValues())[2]) );
      outVal.append( "  " );
      outVal.append( TypeConstants<Vec4f::ValueType>::putToString((inVal.getValues())[3]) );
    }
};

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief Vec4ub field traits 
 */

template <>
struct FieldDataTraits<Vec4ub> : public FieldTraitsRecurseVecStore4Base<Vec4ub>
{
    static DataType             _type;
    enum                        { StringConvertable = ToStringConvertable | 
                                                      FromStringConvertable };
    enum                        { bHasParent        = 0x01                  };

    static DataType &getType      (void) { return _type;      }
    static Char8    *getSName     (void) { return "SFVec4ub"; }

    static Char8    *getMName     (void) { return "MFVec4ub"; }

    static Vec4ub    getDefault   (void) { return Vec4ub();   }

    static Bool      getFromString(      Vec4ub  &outVal,
                                   const Char8  *&inVal)
    {
        outVal.setValue(inVal);

        return true;
    }

    static void   putToString(const Vec4ub &inVal,
                                    string &outVal)
    {
        outVal.assign( TypeConstants<Vec4ub::ValueType>::putToString((inVal.getValues())[0]) );
      outVal.append( "  " );
      outVal.append( TypeConstants<Vec4ub::ValueType>::putToString((inVal.getValues())[1]) );
      outVal.append( "  " );
      outVal.append( TypeConstants<Vec4ub::ValueType>::putToString((inVal.getValues())[2]) );
      outVal.append( "  " );
      outVal.append( TypeConstants<Vec4ub::ValueType>::putToString((inVal.getValues())[3]) );
    }
};

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief Pnt2f field traits 
 */

template <>
struct FieldDataTraits<Pnt2f> : public FieldTraitsRecurseVecStore2Base<Pnt2f>
{
    static DataType              _type;

    enum                         { StringConvertable = ToStringConvertable | 
                                                      FromStringConvertable  };
    enum                         { bHasParent        = 0x01                  };

    static DataType &getType      (void) { return _type;     }

    static Char8    *getSName     (void) { return "SFPnt2f"; }

    static Char8    *getMName     (void) { return "MFPnt2f"; }

    static Pnt2f     getDefault   (void) { return Pnt2f();   }

    static Bool      getFromString(      Pnt2f  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValue(inVal);

        return true;
    }

    static void   putToString(const Pnt2f  &inVal,
                                    string &outVal)
    {
        outVal.assign( TypeConstants<Pnt2f::ValueType>::putToString((inVal.getValues())[0]) ); 
      outVal.append( "  " );
      outVal.append( TypeConstants<Pnt2f::ValueType>::putToString((inVal.getValues())[1]) );
    }
};

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief Pnt3f field traits 
 */

template <>
struct FieldDataTraits<Pnt3f> : public FieldTraitsRecurseVecStore3Base<Pnt3f>
{
    static DataType             _type;

    enum                        { StringConvertable = ToStringConvertable | 
                                                      FromStringConvertable };
    enum                        { bHasParent        = 0x01                  };

    static DataType &getType      (void) { return _type;     }

    static Char8    *getSName     (void) { return "SFPnt3f"; }

    static Char8    *getMName     (void) { return "MFPnt3f"; }

    static Pnt3f     getDefault   (void) { return Pnt3f();   }

    static Bool      getFromString(      Pnt3f  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValue(inVal);
        return false;
    }

    static void   putToString(const Pnt3f  &inVal,
                                    string &outVal)
    {
        outVal.assign( TypeConstants<Pnt3f::ValueType>::putToString((inVal.getValues())[0]) );
      outVal.append( "  " );
      outVal.append( TypeConstants<Pnt3f::ValueType>::putToString((inVal.getValues())[1]) );
      outVal.append( "  " );
      outVal.append( TypeConstants<Pnt3f::ValueType>::putToString((inVal.getValues())[2]) );
    }
};

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief Pnt4f field traits 
 */

template <>
struct FieldDataTraits<Pnt4f> : public FieldTraitsRecurseVecStore4Base<Pnt4f>
{
    static DataType             _type;

    enum                        { StringConvertable = ToStringConvertable | 
                                                      FromStringConvertable };
    enum                        { bHasParent        = 0x01                  };

    static DataType &getType      (void) { return _type;     }

    static Char8    *getSName     (void) { return "SFPnt4f"; }

    static Char8    *getMName     (void) { return "MFPnt4f"; }

    static Pnt4f     getDefault   (void) { return Pnt4f();   }

    static Bool      getFromString(      Pnt4f  &outVal,
                                   const Char8 *&inVal)
    {
        outVal.setValue(inVal);
        return false;
    }

    static void   putToString(const Pnt4f  &inVal,
                                    string &outVal)
    {
        outVal.assign( TypeConstants<Pnt4f::ValueType>::putToString((inVal.getValues())[0]) );
      outVal.append( "  " );
      outVal.append( TypeConstants<Pnt4f::ValueType>::putToString((inVal.getValues())[1]) );
      outVal.append( "  " );
      outVal.append( TypeConstants<Pnt4f::ValueType>::putToString((inVal.getValues())[2]) );
      outVal.append( "  " );
      outVal.append( TypeConstants<Pnt4f::ValueType>::putToString((inVal.getValues())[3]) );
    }
};

OSG_END_NAMESPACE

#endif /* _OSG_VECFIELDDATATYPE_H_ */





