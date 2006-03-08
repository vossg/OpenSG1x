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

#ifndef _OSG_MATHFIELDDATATYPE_H_
#define _OSG_MATHFIELDDATATYPE_H_

#include <OSGBase.h>
#include <OSGFieldDataType.h>
#include <OSGMatrix.h>
#include <OSGQuaternion.h>

#include <string>

OSG_BEGIN_NAMESPACE

#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGMathFieldDataType.h
    \ingroup GrpBaseField
    \ingroup GrpBaseFieldTraits
*/
#endif


/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Matrix> :
    public FieldTraitsRecurseBase<Matrix>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable | 
                                           FromStringConvertable    };

    static DataType &getType      (void) { return _type;            }

    static Char8    *getSName     (void) { return "SFMatrix";       }
    static Char8    *getMName     (void) { return "MFMatrix";       }

    static Matrix    getDefault   (void) { return Matrix();         }

    static bool      getFromString(      Matrix   &outVal,
                                   const Char8   *&inVal)
    {
        outVal.setValue(inVal, false);
        return true;
    }

    static void      putToString  (const      Matrix &inVal,
                                         std::string &outStr)
    {
        typedef TypeTraits<Matrix::ValueType> TypeTrait;

        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append(" ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[4]));
        outStr.append(" ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[8]));
        outStr.append(" ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[12]));

        outStr.append(" ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
        outStr.append(" ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[5]));
        outStr.append(" ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[9]));
        outStr.append(" ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[13]));

        outStr.append(" ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[2]));
        outStr.append(" ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[6]));
        outStr.append(" ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[10]));
        outStr.append(" ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[14]));

        outStr.append(" ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[3]));
        outStr.append(" ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[7]));
        outStr.append(" ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[11]));
        outStr.append(" ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[15]));
    }

    static       UInt32    getBinSize (const Matrix &)
    {
        return sizeof(Real32) * 16;
    }

    static       UInt32    getBinSize (const Matrix  *,
                                             UInt32  uiNumObjects)
    {
        return sizeof(Real32) * 16 * uiNumObjects;
    }

    static void   copyToBin  (      BinaryDataHandler &pMem, 
                              const Matrix           &oObject)
    {
        pMem.putValues(&oObject[0][0], 16);
    }


    static void   copyFromBin(      BinaryDataHandler &pMem, 
                                    Matrix           &oObject)
    {
        pMem.getValues(&oObject[0][0], 16);
    }

    static void copyToBin(      BinaryDataHandler &pMem,
                                const Matrix     *pObjectStore,
                                UInt32             uiNumObjects)
    {
        pMem.putValues(&pObjectStore[0][0][0], uiNumObjects * 16);
    }
    
    static void copyFromBin(    BinaryDataHandler &pMem,
                                Matrix           *pObjectStore,
                                UInt32             uiNumObjects)
    {
        pMem.getValues(&pObjectStore[0][0][0], uiNumObjects * 16);
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseBase<Matrix> */
/*! \hideinhierarchy                       */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Matrix4d> :
    public FieldTraitsRecurseBase<Matrix4d>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable | 
                                           FromStringConvertable    };

    static DataType &getType      (void) { return _type;            }

    static Char8    *getSName     (void) { return "SFMatrix4d";       }
    static Char8    *getMName     (void) { return "MFMatrix4d";       }

    static Matrix4d  getDefault   (void) { return Matrix4d();         }

    static bool      getFromString(      Matrix4d   &outVal,
                                   const Char8     *&inVal)
    {
        outVal.setValue(inVal, false);
        return true;
    }

    static void      putToString  (const      Matrix4d &inVal,
                                         std::string   &outStr)
    {
        typedef TypeTraits<Matrix4d::ValueType> TypeTrait;

        outStr.assign(TypeTrait::putToString((inVal.getValues())[0]));
        outStr.append(" ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[4]));
        outStr.append(" ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[8]));
        outStr.append(" ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[12]));

        outStr.append(" ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[1]));
        outStr.append(" ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[5]));
        outStr.append(" ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[9]));
        outStr.append(" ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[13]));

        outStr.append(" ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[2]));
        outStr.append(" ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[6]));
        outStr.append(" ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[10]));
        outStr.append(" ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[14]));

        outStr.append(" ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[3]));
        outStr.append(" ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[7]));
        outStr.append(" ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[11]));
        outStr.append(" ");
        outStr.append(TypeTrait::putToString((inVal.getValues())[15]));
    }

    static       UInt32    getBinSize (const Matrix4d &)
    {
        return sizeof(Real64) * 16;
    }

    static       UInt32    getBinSize (const Matrix4d  *,
                                             UInt32  uiNumObjects)
    {
        return sizeof(Real64) * 16 * uiNumObjects;
    }

    static void   copyToBin  (      BinaryDataHandler &pMem, 
                              const Matrix4d          &oObject)
    {
        pMem.putValues(&oObject[0][0], 16);
    }


    static void   copyFromBin(      BinaryDataHandler &pMem, 
                                    Matrix4d          &oObject)
    {
        pMem.getValues(&oObject[0][0], 16);
    }

    static void copyToBin(      BinaryDataHandler &pMem,
                                const Matrix4d    *pObjectStore,
                                UInt32             uiNumObjects)
    {
        pMem.putValues(&pObjectStore[0][0][0], uiNumObjects * 16);
    }
    
    static void copyFromBin(    BinaryDataHandler &pMem,
                                Matrix4d          *pObjectStore,
                                UInt32             uiNumObjects)
    {
        pMem.getValues(&pObjectStore[0][0][0], uiNumObjects * 16);
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseBase<Matrix4d> */
/*! \hideinhierarchy                       */
#endif

/*! \ingroup GrpBaseFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

template <>
struct OSG_BASE_DLLMAPPING FieldDataTraits<Quaternion> : 
    public FieldTraitsRecurseBase<Quaternion>
{
    static DataType   _type;

    enum               { StringConvertable = ToStringConvertable | 
                                           FromStringConvertable    };

    static DataType   &getType      (void) { return _type;          }

    static Char8      *getSName     (void) { return "SFQuaternion"; }
    static Char8      *getMName     (void) { return "MFQuaternion"; }

    static Quaternion  getDefault   (void) { return Quaternion();   }

    static bool        getFromString(      Quaternion  &outVal,
                                     const Char8      *&inVal)
    {
        // VRML requires axis and angle in radians
        outVal.setValueAsAxisRad(inVal);

        return true;
    }

    static void       putToString   (const      Quaternion &inVal,
                                           std::string     &outStr)
    {
        typedef Quaternion::VectorType::ValueType ValueType;
        typedef TypeTraits<ValueType>             TypeTrait;

        ValueType axisX;
        ValueType axisY;
        ValueType axisZ;
        ValueType angleRad;

        inVal.getValueAsAxisRad(axisX, axisY, axisZ, angleRad);

        outStr.assign(TypeTrait::putToString(axisX));

        outStr.append( " " );
        outStr.append(TypeTrait::putToString(axisY));

        outStr.append( " " );
        outStr.append(TypeTrait::putToString(axisZ) );

        outStr.append( " " );
        outStr.append(TypeTrait::putToString(angleRad) );
    }

    static       UInt32    getBinSize (const Quaternion &)
    {
        return sizeof(Real32) * 4;
    }

    static       UInt32    getBinSize (const Quaternion *,
                                             UInt32      uiNumObjects)
    {
        return sizeof(Real32)* 4 *uiNumObjects;
    }

    static void   copyToBin  (      BinaryDataHandler &pMem, 
                              const Quaternion        &oObject)
    {
        pMem.putValues(&oObject[0], 4);
    }


    static void   copyFromBin(      BinaryDataHandler &pMem, 
                                    Quaternion        &oObject)
    {
        pMem.getValues(&oObject[0], 4);
    }

    static void copyToBin(      BinaryDataHandler &pMem, 
                          const Quaternion        *pObjectStore,
                                UInt32             uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            copyToBin(pMem, pObjectStore[i]);
        }
    }
    
    static void copyFromBin(BinaryDataHandler &pMem, 
                            Quaternion        *pObjectStore,
                            UInt32             uiNumObjects)
    {
        for(UInt32 i = 0; i < uiNumObjects; ++i)
        {
            copyFromBin(pMem, pObjectStore[i]);
        }
    }
};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class  FieldTraitsRecurseBase<Quaternion> */
/*! \hideinhierarchy                           */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

OSG_END_NAMESPACE

#define OSGMATHFIELDDATATYPE_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSG_MATHFIELDDATATYPE_H_ */

