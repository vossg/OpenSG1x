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

#ifndef _OSG_MATHFIELDDATATYPE_H_
#define _OSG_MATHFIELDDATATYPE_H_

#include <OSGBase.h>
#include <OSGFieldDataType.h>
#include <OSGMatrix.h>
#include <OSGQuaternion.h>

#include <string>

OSG_BEGIN_NAMESPACE

/*! \file OSGMathFieldDataType.h
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
    \brief OpenSG Math Field Data Types  
*/

/*! \brief Matrix field traits
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields 
*/

template <>
struct FieldDataTraits<Matrix> : public FieldTraitsRecurseBase<Matrix>
{
    static DataType _type;

    enum             { StringConvertable = ToStringConvertable | 
                                           FromStringConvertable    };

    static DataType &getType      (void) { return _type;            }

    static Char8    *getSName     (void) { return "SFMatrix";       }
    static Char8    *getMName     (void) { return "MFMatrix";       }

    static Matrix    getDefault   (void) { return Matrix();         }

    static Bool      getFromString(      Matrix   &outVal,
                                   const Char8   *&inVal)
    {
        outVal.setValue(inVal);
        return true;
    }

    static void      putToString  (const Matrix &inVal,
                                         string &outVal)
    {
        typedef TypeConstants<Matrix::ValueType> TypeConst;

        outVal.assign(TypeConst::putToString((inVal.getValues())[0]));

        outVal.append(" ");
        outVal.append(TypeConst::putToString((inVal.getValues())[1]));

        outVal.append(" ");
        outVal.append(TypeConst::putToString((inVal.getValues())[2]));

        outVal.append(" ");
        outVal.append(TypeConst::putToString((inVal.getValues())[3]));


        outVal.append(" ");
        outVal.append(TypeConst::putToString((inVal.getValues())[4]));

        outVal.append(" ");
        outVal.append(TypeConst::putToString((inVal.getValues())[5]));

        outVal.append(" ");
        outVal.append(TypeConst::putToString((inVal.getValues())[6]));

        outVal.append(" ");
        outVal.append(TypeConst::putToString((inVal.getValues())[7]));


        outVal.append(" ");
        outVal.append(TypeConst::putToString((inVal.getValues())[8]));

        outVal.append(" ");
        outVal.append(TypeConst::putToString((inVal.getValues())[9]));

        outVal.append(" ");
        outVal.append(TypeConst::putToString((inVal.getValues())[10]));

        outVal.append(" ");
        outVal.append(TypeConst::putToString((inVal.getValues())[11]));


        outVal.append(" ");
        outVal.append(TypeConst::putToString((inVal.getValues())[12]));

        outVal.append(" ");
        outVal.append(TypeConst::putToString((inVal.getValues())[13]));

        outVal.append(" ");
        outVal.append(TypeConst::putToString((inVal.getValues())[14]));

        outVal.append(" ");
        outVal.append(TypeConst::putToString((inVal.getValues())[15]));
    }
};

/*! \brief Quaternion field traits 
    \ingroup FieldLib
    \ingroup SingleFields
    \ingroup MultiFields
*/

template <>
struct FieldDataTraits<Quaternion> : 
    public FieldTraitsRecurseBase<Quaternion>
{
    static DataType   _type;

    enum               { StringConvertable = ToStringConvertable | 
                                           FromStringConvertable    };

    static DataType   &getType      (void) { return _type;          }

    static Char8      *getSName     (void) { return "SFQuaternion"; }
    static Char8      *getMName     (void) { return "MFQuaternion"; }

    static Quaternion  getDefault   (void) { return Quaternion();   }

    static Bool        getFromString(      Quaternion  &outVal,
                                     const Char8      *&inVal)
    {
        // VRML requires axis and angle in radians
        outVal.setValueAsAxisRad(inVal);

        return true;
    }

    static void       putToString   (const Quaternion &inVal,
                                           string     &outVal)
    {
        typedef Quaternion::VectorType::ValueType ValueType;

        typedef TypeConstants<ValueType>          TypeConst;

        ValueType axisX;
        ValueType axisY;
        ValueType axisZ;
        ValueType angleRad;

        inVal.getValueAsAxisRad(axisX, axisY, axisZ, angleRad);

        outVal.assign(TypeConst::putToString(axisX));

        outVal.append( " " );
        outVal.append(TypeConst::putToString(axisY));

        outVal.append( " " );
        outVal.append(TypeConst::putToString(axisZ) );

        outVal.append( " " );
        outVal.append(TypeConst::putToString(angleRad) );
    }
};

OSG_END_NAMESPACE

#define OSGMATHFIELDDATATYPE_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSG_MATHFIELDDATATYPE_H_ */

