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

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief Matrix field traits 
 */

template <>
struct FieldDataTraits<Matrix> : public FieldTraitsRecurseBase<Matrix>
{
    static DataType              _type;

    enum                         { StringConvertable = ToStringConvertable | 
                                                       FromStringConvertable };

    static DataType         &getType (void) { return _type;                  }

    static Char8            *getSName(void) { return "SFMatrix";             }
    static Char8            *getMName(void) { return "MFMatrix";             }

//    static Matrix        getDefault(void)    { return Matrix; }

    static Bool              getFromString(      Matrix   &,
                                           const Char8   *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void             putToString(const Matrix &inVal,
                                              std::string &outVal)
    {
       outVal.assign( TypeConstants<Matrix::ValueType>::putToString((inVal.getValues())[0]) );
      outVal.append( " " );
	  outVal.append( TypeConstants<Matrix::ValueType>::putToString((inVal.getValues())[1]) );
      outVal.append( " " );
	  outVal.append( TypeConstants<Matrix::ValueType>::putToString((inVal.getValues())[2]) );
      outVal.append( " " );
	  outVal.append( TypeConstants<Matrix::ValueType>::putToString((inVal.getValues())[3]) );
	  outVal.append( " " );
      
	  outVal.append( TypeConstants<Matrix::ValueType>::putToString((inVal.getValues())[4]) );
      outVal.append( " " );
	  outVal.append( TypeConstants<Matrix::ValueType>::putToString((inVal.getValues())[5]) );
      outVal.append( " " );
	  outVal.append( TypeConstants<Matrix::ValueType>::putToString((inVal.getValues())[6]) );
      outVal.append( " " );
	  outVal.append( TypeConstants<Matrix::ValueType>::putToString((inVal.getValues())[7]) );
      outVal.append( " " );
	  
      outVal.append( TypeConstants<Matrix::ValueType>::putToString((inVal.getValues())[8]) );
      outVal.append( " " );
	  outVal.append( TypeConstants<Matrix::ValueType>::putToString((inVal.getValues())[9]) );
      outVal.append( " " );
	  outVal.append( TypeConstants<Matrix::ValueType>::putToString((inVal.getValues())[10]) );
      outVal.append( " " );
	  outVal.append( TypeConstants<Matrix::ValueType>::putToString((inVal.getValues())[11]) );
	  outVal.append( " " );
	  
      outVal.append( TypeConstants<Matrix::ValueType>::putToString((inVal.getValues())[12]) );
      outVal.append( " " );
	  outVal.append( TypeConstants<Matrix::ValueType>::putToString((inVal.getValues())[13]) );
      outVal.append( " " );
	  outVal.append( TypeConstants<Matrix::ValueType>::putToString((inVal.getValues())[14]) );
      outVal.append( " " );
	  outVal.append( TypeConstants<Matrix::ValueType>::putToString((inVal.getValues())[15]) );
    }
};

/** \ingroup FieldLib
 *  \ingroup SingleFields
 *  \ingroup MultiFields
 *  \brief Quaternion field traits 
 */

template <>
struct FieldDataTraits<Quaternion> : 
    public FieldTraitsRecurseBase<Quaternion>
{
    static DataType              _type;

    enum                         { StringConvertable = ToStringConvertable | 
                                                       FromStringConvertable };

    static DataType        &getType (void) { return _type;                   }

    static Char8           *getSName(void) { return "SFQuaternion";          }
    static Char8           *getMName(void) { return "MFQuaternion";          }

//    static Quaternion    getDefault(void)    { return Quaternion; }

    static Bool             getFromString(      Quaternion  &outVal,
                                          const Char8      *&inVal)
    {

        // VRML requires axis and angle in radians

        outVal.setValueAsAxisRad(inVal);
        return true;
    }

    static void             putToString(const Quaternion &inVal,
                                              std::string     &outVal)
    {
        Quaternion::VectorType::ValueType axisX;
		Quaternion::VectorType::ValueType axisY;
		Quaternion::VectorType::ValueType axisZ;
		Quaternion::VectorType::ValueType angleRad;
		inVal.getValueAsAxisRad( axisX, axisY, axisZ, angleRad );
		outVal.assign( TypeConstants<Quaternion::VectorType::ValueType>::putToString(axisX) );
		outVal.append( " " );
		outVal.append( TypeConstants<Quaternion::VectorType::ValueType>::putToString(axisY) );
		outVal.append( " " );
		outVal.append( TypeConstants<Quaternion::VectorType::ValueType>::putToString(axisZ) );
		outVal.append( " " );
		outVal.append( TypeConstants<Quaternion::VectorType::ValueType>::putToString(angleRad) );
    }
};

OSG_END_NAMESPACE

#endif /* _OSG_MATHFIELDDATATYPE_H_ */

