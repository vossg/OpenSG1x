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

#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <iomanip>

#include "OSGLog.h"

OSG_BEGIN_NAMESPACE

/*! \typedef TransformationMatrix::ValueType
    \brief Value type, eg Real32
*/

/*! \typedef VectorInterface<ValueTypeT, VecStorage4<ValueTypeT> >    \
             TransformationMatrix::VectorType;
    \brief Matrix vector type, eg Vec4f
*/

/*! \typedef QuaternionBase<ValueType> TransformationMatrix::QuaternionType;
    \brief Matrix quaternion type
*/

/*! \typedef VectorInterface<ValueTypeT, VecStorage3<ValueTypeT> >    \
             TransformationMatrix::VectorType3f;
    \brief Matrix vec3f type
*/

/*! \typedef PointInterface<ValueTypeT, VecStorage3<ValueTypeT> >     \
             TransformationMatrix::PointType3f;
    \brief Matrix pnt3f type
*/

/*! \var VectorType TransformationMatrix::_matrix[4];
    \brief Value store
*/

#if defined(__hpux)
template<class ValueTypeT> 
const UInt32 TransformationMatrix<ValueTypeT>::JacobiRank;
#endif

template<class ValueTypeT>
TransformationMatrix<ValueTypeT> 
    TransformationMatrix<ValueTypeT>::_identityMatrix;

/*-------------------------------------------------------------------------*/
/*                            Class Get                                    */

template<class ValueTypeT> inline
const TransformationMatrix<ValueTypeT> &
    TransformationMatrix<ValueTypeT>::identity(void)
{
    return _identityMatrix;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template<class ValueTypeT> inline
TransformationMatrix<ValueTypeT>::TransformationMatrix(void)
{
    for(UInt32 i = 0; i < 4; i++)
    {
        _matrix[i][i] = TypeTraits<ValueType>::getOneElement();
    }
}

template<class ValueTypeT> inline
TransformationMatrix<ValueTypeT>::TransformationMatrix(
    const TransformationMatrix &source)
{
    for(UInt32 i = 0; i < 4; i++)
    {
        _matrix[i] = source._matrix[i];
    }
}

template<class ValueTypeT> inline
TransformationMatrix<ValueTypeT>::TransformationMatrix(
    const VectorType3f &vector1,
    const VectorType3f &vector2,
    const VectorType3f &vector3)
{
    _matrix[0].setValue(vector1);
    _matrix[1].setValue(vector2);
    _matrix[2].setValue(vector3);
}

template<class ValueTypeT> inline
TransformationMatrix<ValueTypeT>::TransformationMatrix(
    const VectorType3f &vector1,
    const VectorType3f &vector2,
    const VectorType3f &vector3,
    const VectorType3f &vector4)
{
    _matrix[0].setValue(vector1);
    _matrix[1].setValue(vector2);
    _matrix[2].setValue(vector3);
    _matrix[3].setValue(vector4);
}

template<class ValueTypeT> inline
TransformationMatrix<ValueTypeT>::TransformationMatrix(
    const ValueTypeT rVal00,
    const ValueTypeT rVal10,
    const ValueTypeT rVal20,
    const ValueTypeT rVal30,

    const ValueTypeT rVal01,
    const ValueTypeT rVal11,
    const ValueTypeT rVal21,
    const ValueTypeT rVal31,

    const ValueTypeT rVal02,
    const ValueTypeT rVal12,
    const ValueTypeT rVal22,
    const ValueTypeT rVal32,

    const ValueTypeT rVal03,
    const ValueTypeT rVal13,
    const ValueTypeT rVal23,
    const ValueTypeT rVal33)
{
    _matrix[0].setValues(rVal00, rVal01, rVal02, rVal03);
    _matrix[1].setValues(rVal10, rVal11, rVal12, rVal13);
    _matrix[2].setValues(rVal20, rVal21, rVal22, rVal23);
    _matrix[3].setValues(rVal30, rVal31, rVal32, rVal33);
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

template<class ValueTypeT> inline
TransformationMatrix<ValueTypeT>::~TransformationMatrix(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Set                                      */

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setIdentity(void)
{
    for(UInt32 i = 0; i < 4; i++)
    {
        _matrix[i].setNull();
        _matrix[i][i] = TypeTraits<ValueType>::getOneElement();
    }
}

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setValue(
    const TransformationMatrix &mat)
{
    for(UInt32 i = 0; i < 4; i++)
    {
        _matrix[i] = mat._matrix[i];
    }
}

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setValue(const VectorType3f &vector1,
                                                const VectorType3f &vector2,
                                                const VectorType3f &vector3)
{
    _matrix[0].setValue(vector1);
    _matrix[1].setValue(vector2);
    _matrix[2].setValue(vector3);
}

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setValue(const VectorType3f &vector1,
                                                const VectorType3f &vector2,
                                                const VectorType3f &vector3,
                                                const VectorType3f &vector4)
{
    _matrix[0].setValue(vector1);
    _matrix[1].setValue(vector2);
    _matrix[2].setValue(vector3);
    _matrix[3].setValue(vector4);
}

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setValue(const ValueTypeT rVal00,
                                                const ValueTypeT rVal10,
                                                const ValueTypeT rVal20,
                                                const ValueTypeT rVal30,
                                                
                                                const ValueTypeT rVal01,
                                                const ValueTypeT rVal11,
                                                const ValueTypeT rVal21,
                                                const ValueTypeT rVal31,
                                                
                                                const ValueTypeT rVal02,
                                                const ValueTypeT rVal12,
                                                const ValueTypeT rVal22,
                                                const ValueTypeT rVal32,
                                                
                                                const ValueTypeT rVal03,
                                                const ValueTypeT rVal13,
                                                const ValueTypeT rVal23,
                                                const ValueTypeT rVal33)
{
    _matrix[0].setValues(rVal00, rVal01, rVal02, rVal03);
    _matrix[1].setValues(rVal10, rVal11, rVal12, rVal13);
    _matrix[2].setValues(rVal20, rVal21, rVal22, rVal23);
    _matrix[3].setValues(rVal30, rVal31, rVal32, rVal33);
}

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setValueTransposed(
    const ValueTypeT rVal00,
    const ValueTypeT rVal01,
    const ValueTypeT rVal02,
    const ValueTypeT rVal03,

    const ValueTypeT rVal10,
    const ValueTypeT rVal11,
    const ValueTypeT rVal12,
    const ValueTypeT rVal13,

    const ValueTypeT rVal20,
    const ValueTypeT rVal21,
    const ValueTypeT rVal22,
    const ValueTypeT rVal23,

    const ValueTypeT rVal30,
    const ValueTypeT rVal31,
    const ValueTypeT rVal32,
    const ValueTypeT rVal33)
{
    _matrix[0].setValues(rVal00, rVal01, rVal02, rVal03);
    _matrix[1].setValues(rVal10, rVal11, rVal12, rVal13);
    _matrix[2].setValues(rVal20, rVal21, rVal22, rVal23);
    _matrix[3].setValues(rVal30, rVal31, rVal32, rVal33);
}

//! Set value from an ValueTypeT array, be shure the sizes match

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setValue(const ValueTypeT *pMat, 
                                                      bool        bTransposed)
{
    const ValueTypeT *pTmpMat = pMat;

    if(bTransposed == true)
    {
        for(UInt32 i = 0; i < 4; i++)
        {
            _matrix[i].setValue(pTmpMat);

            pTmpMat += 4;
        }
    }
    else
    {
        for(UInt32 i = 0; i < 4; i++)
        {
            for(UInt32 j = 0; j < 4; j++)
            {
                _matrix[i][j] = pTmpMat[j * 4 + i];
            }
        }
    }
}

//! Set value from an VectorTypeT array, be shure the sizes match

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setValue(const VectorType *pMat)
{
    for(UInt32 i = 0; i < 4; i++)
    {
        _matrix[i] = pMat[i];
    }
}

#ifndef WIN32

//! Set value from an VectorType3f array, be shure the sizes match

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setValue(const VectorType3f *pMat)
{
    for(UInt32 i = 0; i < 4; i++)
    {
        _matrix[i].setValue(pMat[i]);
    }
}

#endif

/*! \brief Set matrix by a given str (like "1.0 0.0 0.0 0.0 ... 
    (16 entries at all)"), be shure the size matches
*/

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setValue(const Char8 *str,
                                                      bool   bTransposed)
{
    UInt32 i;
    UInt32 numOfToken = 16;
    
    Char8 *c = const_cast<char*>(str);

    Char8 *token = 0;

    ValueTypeT vec[16];
    
    if( (str  == NULL) ||
        (*str == '\0') )
    {
        setIdentity();
        return;
    }
    
    for(i = 0; i < numOfToken; c++)
    {
        switch (*c)
        {
            case '\0':
                if (token)
                {
                     vec[i++] = TypeTraits<ValueTypeT>::getFromString(token);
                }

                while (i < numOfToken)
                {
                    vec[i++] = TypeTraits<ValueTypeT>::getZeroElement();
                }

                break;
            case ' ':
            case '\t':
            case '\n':
            case ',':
                if (token)
                {
                     vec[i++] = TypeTraits<ValueTypeT>::getFromString(token);
                     token    = 0;
                }
                break;
            default:
                if (!token)
                {
                    token = c;
                }
                break;
        }
    }

    if(bTransposed == true)
    {
        setValueTransposed(vec[0],  vec[1],  vec[2],  vec[3],
                           vec[4],  vec[5],  vec[6],  vec[7],
                           vec[8],  vec[9],  vec[10], vec[11],
                           vec[12], vec[13], vec[14], vec[15]);
    }
    else
    {
        setValue(vec[0],  vec[1],  vec[2],  vec[3],
                 vec[4],  vec[5],  vec[6],  vec[7],
                 vec[8],  vec[9],  vec[10], vec[11],
                 vec[12], vec[13], vec[14], vec[15]);
    }
}

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

//! Returns an C++ pointer to the value store

template<class ValueTypeT> inline
ValueTypeT *TransformationMatrix<ValueTypeT>::getValues(void)
{
    return _matrix[0].getValues();
}

template<class ValueTypeT> inline
const ValueTypeT *TransformationMatrix<ValueTypeT>::getValues(void) const
{
    return _matrix[0].getValues();
}

/*-------------------------------------------------------------------------*/
/*                       Set Transformation                                */

//! Sets matrix to scale by given uniform factor

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setScale(const ValueTypeT s)
{
    _matrix[0][0] = s;
    _matrix[1][1] = s;
    _matrix[2][2] = s;
}

//! Sets matrix to scale by given uniform factor

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setScale(const ValueTypeT sx,
                                                const ValueTypeT sy, 
                                                const ValueTypeT sz)
{
    _matrix[0][0] = sx;
    _matrix[1][1] = sy;
    _matrix[2][2] = sz;
}

//! Sets matrix to scale by given vector

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setScale(const VectorType3f &s)
{
    _matrix[0][0] = s[0];
    _matrix[1][1] = s[1];
    _matrix[2][2] = s[2];
}

//! Sets matrix to translate by given values

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setTranslate(const ValueTypeT tx,
                                                    const ValueTypeT ty,
                                                    const ValueTypeT tz)
{
    _matrix[3][0] = tx;
    _matrix[3][1] = ty;
    _matrix[3][2] = tz;
}

//! Sets matrix to translate by given vector

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setTranslate(const VectorType3f &t)
{
    _matrix[3].setValue(t);
}

//! Sets matrix to translate by given point

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setTranslate(const PointType3f &t)
{
    _matrix[3].setValue(t);
}

//! Sets matrix to rotate by given rotation

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setRotate(const QuaternionType &q)
{
    q.getValuesOnly(*this);
}

//! Composes the matrix based on a translation

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setTransform(const VectorType3f &t)
{
    setIdentity();

    _matrix[3][0] = t[0];
    _matrix[3][1] = t[1];
    _matrix[3][2] = t[2];

}

//! Composes the matrix based on a rotation

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setTransform(const QuaternionType &r)
{
    // Calculate the 4x4 rotation matrix
    r.getValue(*this);
}

//! Composes the matrix based on a translation and rotation

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setTransform(const VectorType3f   &t,
                                                    const QuaternionType &r)
{
    r.getValuesOnly(*this);

    // Calculate the resulting transformation matrix
    _matrix[0][3] = 0.0;
    _matrix[1][3] = 0.0;
    _matrix[2][3] = 0.0;

    _matrix[3][0] = t[0];
    _matrix[3][1] = t[1];
    _matrix[3][2] = t[2];
    _matrix[3][3] = 1.0;
}

//! Composes the matrix based on a translation, rotation and scale

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setTransform(const VectorType3f   &t,
                                                    const QuaternionType &r,
                                                    const VectorType3f   &s)
{
    // Calculate the 3x3 rotation matrix
    r.getValuesOnly(*this);

    // Calculate the resulting transformation matrix
    _matrix[0][0] *= s[0]; _matrix[0][1] *= s[0]; _matrix[0][2] *=s[0];
    _matrix[1][0] *= s[1]; _matrix[1][1] *= s[1]; _matrix[1][2] *=s[1];
    _matrix[2][0] *= s[2]; _matrix[2][1] *= s[2]; _matrix[2][2] *=s[2];

    _matrix[0][3] = 0.0;
    _matrix[1][3] = 0.0;
    _matrix[2][3] = 0.0;

    _matrix[3][0] = t[0];
    _matrix[3][1] = t[1];
    _matrix[3][2] = t[2];
    _matrix[3][3] = 1.0;
}

//! Composes the matrix based on a translation, rotation, scale and orientation

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setTransform(const VectorType3f   &t,
                                                    const QuaternionType &r,
                                                    const VectorType3f   &s,
                                                    const QuaternionType &so)
{
    Matrix tmpMat1;
    Matrix tmpMat2;

    // Concatenate the rotations r and so
    QuaternionType rg(r);
    rg.mult(so);

    // Calculate the inverse of so
    QuaternionType soi(so);
    soi.invert();

    // Calculate the 3x3 rotation matrix
    rg. getValue(tmpMat1);
    soi.getValue(tmpMat2);

    // Calculate the resulting transformation matrix
    tmpMat1[0][0] *= s[0]; tmpMat1[0][1] *= s[0]; tmpMat1[0][2] *=s[0];
    tmpMat1[1][0] *= s[1]; tmpMat1[1][1] *= s[1]; tmpMat1[1][2] *=s[1];
    tmpMat1[2][0] *= s[2]; tmpMat1[2][1] *= s[2]; tmpMat1[2][2] *=s[2];

    _matrix[0][0] =
        tmpMat2[0][0] * tmpMat1[0][0] +
        tmpMat2[0][1] * tmpMat1[1][0] +
        tmpMat2[0][2] * tmpMat1[2][0];

    _matrix[0][1] =
        tmpMat2[0][0] * tmpMat1[0][1] +
        tmpMat2[0][1] * tmpMat1[1][1] +
        tmpMat2[0][2] * tmpMat1[2][1];

    _matrix[0][2] =
        tmpMat2[0][0] * tmpMat1[0][2] +
        tmpMat2[0][1] * tmpMat1[1][2] +
        tmpMat2[0][2] * tmpMat1[2][2];

    _matrix[0][3] = 0.0;


    _matrix[1][0] =
        tmpMat2[1][0] * tmpMat1[0][0] +
        tmpMat2[1][1] * tmpMat1[1][0] +
        tmpMat2[1][2] * tmpMat1[2][0];

    _matrix[1][1] =
        tmpMat2[1][0] * tmpMat1[0][1] +
        tmpMat2[1][1] * tmpMat1[1][1] +
        tmpMat2[1][2] * tmpMat1[2][1];

    _matrix[1][2] =
        tmpMat2[1][0] * tmpMat1[0][2] +
        tmpMat2[1][1] * tmpMat1[1][2] +
        tmpMat2[1][2] * tmpMat1[2][2];

    _matrix[1][3] = 0.0;


    _matrix[2][0] =
        tmpMat2[2][0] * tmpMat1[0][0] +
        tmpMat2[2][1] * tmpMat1[1][0] +
        tmpMat2[2][2] * tmpMat1[2][0];

    _matrix[2][1] =
        tmpMat2[2][0] * tmpMat1[0][1] +
        tmpMat2[2][1] * tmpMat1[1][1] +
        tmpMat2[2][2] * tmpMat1[2][1];

    _matrix[2][2] =
        tmpMat2[2][0] * tmpMat1[0][2] +
        tmpMat2[2][1] * tmpMat1[1][2] +
        tmpMat2[2][2] * tmpMat1[2][2];

    _matrix[2][3] = 0.0;

    _matrix[3][0] = t[0];
    _matrix[3][1] = t[1];
    _matrix[3][2] = t[2];
    _matrix[3][3] = 1.0;
}

/*! Composes the matrix based on a translation, rotation, scale,
   orientation for scale, and center.  The "center" is the
   center point for scaling and rotation.  The "scaleOrientation"
   chooses the primary axes for the scale.
*/

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setTransform(
    const VectorType3f   &translation,
    const QuaternionType &rotation,
    const VectorType3f   &scaleFactor,
    const QuaternionType &scaleOrientation,
    const VectorType3f   &center)
{
    Matrix tmpMat1;
    Matrix tmpMat2;

    // Concatenate the translations t and c
    VectorType3f tg(translation);
    tg += center;

    // Concatenate the rotations r and so
    QuaternionType rg(rotation);
    rg *= scaleOrientation;

    // Calculate the inverse of so
    QuaternionType soi(scaleOrientation);
    soi.invert();

    // Calculate the 3x3 rotation matrix
    rg. getValue(tmpMat1);
    soi.getValue(tmpMat2);

    // Calculate the resulting transformation matrix

    tmpMat1[0][0] *= scaleFactor[0];
    tmpMat1[0][1] *= scaleFactor[0];
    tmpMat1[0][2] *= scaleFactor[0];

    tmpMat1[1][0] *= scaleFactor[1];
    tmpMat1[1][1] *= scaleFactor[1];
    tmpMat1[1][2] *= scaleFactor[1];

    tmpMat1[2][0] *= scaleFactor[2];
    tmpMat1[2][1] *= scaleFactor[2];
    tmpMat1[2][2] *= scaleFactor[2];

    _matrix[0][0] =
        tmpMat2[0][0] * tmpMat1[0][0] +
        tmpMat2[0][1] * tmpMat1[1][0] +
        tmpMat2[0][2] * tmpMat1[2][0];

    _matrix[0][1] =
        tmpMat2[0][0] * tmpMat1[0][1] +
        tmpMat2[0][1] * tmpMat1[1][1] +
        tmpMat2[0][2] * tmpMat1[2][1];

    _matrix[0][2] =
        tmpMat2[0][0] * tmpMat1[0][2] +
        tmpMat2[0][1] * tmpMat1[1][2] +
        tmpMat2[0][2] * tmpMat1[2][2];

    _matrix[0][3] = 0.0;


    _matrix[1][0] =
        tmpMat2[1][0] * tmpMat1[0][0] +
        tmpMat2[1][1] * tmpMat1[1][0] +
        tmpMat2[1][2] * tmpMat1[2][0];

    _matrix[1][1] =
        tmpMat2[1][0] * tmpMat1[0][1] +
        tmpMat2[1][1] * tmpMat1[1][1] +
        tmpMat2[1][2] * tmpMat1[2][1];

    _matrix[1][2] =
        tmpMat2[1][0] * tmpMat1[0][2] +
        tmpMat2[1][1] * tmpMat1[1][2] +
        tmpMat2[1][2] * tmpMat1[2][2];

    _matrix[1][3] = 0.0;


    _matrix[2][0] =
        tmpMat2[2][0] * tmpMat1[0][0] +
        tmpMat2[2][1] * tmpMat1[1][0] +
        tmpMat2[2][2] * tmpMat1[2][0];

    _matrix[2][1] =
        tmpMat2[2][0] * tmpMat1[0][1] +
        tmpMat2[2][1] * tmpMat1[1][1] +
        tmpMat2[2][2] * tmpMat1[2][1];

    _matrix[2][2] =
        tmpMat2[2][0] * tmpMat1[0][2] +
        tmpMat2[2][1] * tmpMat1[1][2] +
        tmpMat2[2][2] * tmpMat1[2][2];

    _matrix[2][3] = 0.0;


    _matrix[3][0] =
        _matrix[0][0] * -center[0] +
        _matrix[1][0] * -center[1] +
        _matrix[2][0] * -center[2] + tg[0];

    _matrix[3][1] =
        _matrix[0][1] * -center[0] +
        _matrix[1][1] * -center[1] +
        _matrix[2][1] * -center[2] + tg[1];

    _matrix[3][2] =
        _matrix[0][2] * -center[0] +
        _matrix[1][2] * -center[1] +
        _matrix[2][2] * -center[2] + tg[2];

    _matrix[3][3] = 1.0;

}

/*-------------------------------------------------------------------------*/
/*                           Get Transform                                 */

/*! \brief Decomposes the matrix into a translation, rotation, scale,
    and scale orientation.  Any projection information is discarded.
    The decomposition depends upon choice of center point for
    rotation and scaling, which is optional as the last parameter.
    Note that if the center is 0, decompose() is the same as
    factor() where "t" is translation, "u" is rotation, "s" is
    scaleFactor, and "r" is ScaleOrientattion.
*/

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::getTransform(
          VectorType3f   &translation,
          QuaternionType &rotation,
          VectorType3f   &scaleFactor,
          QuaternionType &scaleOrientation,
    const VectorType3f   &center          ) const
{
    TransformationMatrix m;
    TransformationMatrix c;
    
    m.setTranslate(-center);
    
    m.mult(*this);
    
    c.setTranslate(center);
    
    m.mult(c);
    
    m.getTransform(translation, rotation, scaleFactor, scaleOrientation);
}

//! Decomposes the matrix into a translation, rotation  and scale

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::getTransform(
    VectorType3f   &translation,
    QuaternionType &rotation,
    VectorType3f   &scaleFactor,
    QuaternionType &scaleOrientation) const
{
    ValueType            flip;
    TransformationMatrix so;
    TransformationMatrix rot;
    TransformationMatrix proj;

    this->decompose(translation, flip, rotation, scaleOrientation, scaleFactor);
    scaleFactor *= flip;
}

/*! \brief Factors a matrix m into 5 pieces: m = r s rt u t, where rt
    means transpose of r, and r and u are rotations, s is a scale,
    and t is a translation. Any projection information is returned
    in proj.
    
    \bug This function seems to be BROKEN.
*/

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::factor(TransformationMatrix &r,
                                              VectorType3f         &s,
                                              TransformationMatrix &u,
                                              VectorType3f         &t,
                                              TransformationMatrix &proj) const
{
    Real64               det;       
    Real64               det_sign;   
    Real64               scratch;
    Int32                i;
    Int32                j;
    Int32                junk;
    TransformationMatrix a;
    TransformationMatrix aT;
    TransformationMatrix rT;
    TransformationMatrix b;
    TransformationMatrix si;
    ValueTypeT           evalues [3];
    VectorType3f         evectors[3];
    
    a = *this;

    proj.setIdentity();

    scratch = 1.0;
    
    for (i = 0; i < 3; i++) 
    {
        for (j = 0; j < 3; j++) 
        {
            a._matrix[i][j] *= ValueTypeT(scratch);
        }

        t[i] = _matrix[3][i] * ValueTypeT(scratch);

        a._matrix[3][i] = a._matrix[i][3] = 0.0;
    }

    a._matrix[3][3] = 1.0;
    
    /* (3) Compute det A. If negative, set sign = -1, else sign = 1 */

    det      = a.det3();

    det_sign = (det < 0.0 ? -1.0 : 1.0);

    if(det_sign * det < 1e-12)
        return false;      // singular
    
    /* (4) B = A * A^  (here A^ means A transpose) */
    
    aT.transposeFrom(a);
    b = a;
    b.mult(aT);
    
    b.jacobi(evalues, evectors, junk);
    
    r.setValue(evectors[0][0], evectors[0][1], evectors[0][2], 0.0, 
               evectors[1][0], evectors[1][1], evectors[1][2], 0.0, 
               evectors[2][0], evectors[2][1], evectors[2][2], 0.0, 
                          0.0,            0.0,            0.0, 1.0);
    
    /* Compute s = sqrt(evalues), with sign. Set si = s-inverse */

    si.setIdentity();

    for(i = 0; i < 3; i++) 
    {
        s[i] = ValueTypeT(det_sign * osgsqrt(evalues[i]));

        si._matrix[i][i] = 1.0f / s[i];
    }
    
    /* (5) Compute U = RT S! R A. */

    rT.transposeFrom(r);
    u = r;
    u.mult(si);
    u.mult(rT);
    u.mult(a);
    
    return true;
}

/*---------------------------- transform objects ---------------------------*/

#ifndef OSG_2_PREP_FULL

/*! \brief Multiplies matrix by given column point, where the resulting point
    is given
*/

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multMatrixPnt(
    const PointType3f &src,
          PointType3f &dst) const
{
    dst.setValues((src[0] * _matrix[0][0] +
                   src[1] * _matrix[1][0] +
                   src[2] * _matrix[2][0] +
                            _matrix[3][0]),
                  (src[0] * _matrix[0][1] +
                   src[1] * _matrix[1][1] +
                   src[2] * _matrix[2][1] +
                            _matrix[3][1]),
                  (src[0] * _matrix[0][2] +
                   src[1] * _matrix[1][2] +
                   src[2] * _matrix[2][2] +
                            _matrix[3][2]));
}

//! Multiplies matrix by given column point

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multMatrixPnt(PointType3f &pnt) const
{
    multMatrixPnt(pnt, pnt);
}

/*! \brief Multiplies matrix by given column point, where the resulting point
    is given. The full (4x4) matrix is used.
*/

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multFullMatrixPnt(
    const PointType3f &src,
          PointType3f &dst) const
{
    ValueTypeT w =  src[0] * _matrix[0][3] +
                    src[1] * _matrix[1][3] +
                    src[2] * _matrix[2][3] +
                             _matrix[3][3];

    if( w == 0.0f )
    {
        SINFO << "multFullMatrixPnt: w == 0.0f!" << std::endl;

        dst.setValues(0, 0, 0);

        return;
    }

    //CHECK
    w = ValueTypeT(1.)/w;
    dst.setValues((src[0] * _matrix[0][0] +
                   src[1] * _matrix[1][0] +
                   src[2] * _matrix[2][0] +
                            _matrix[3][0]) * w,
                  (src[0] * _matrix[0][1] +
                   src[1] * _matrix[1][1] +
                   src[2] * _matrix[2][1] +
                            _matrix[3][1]) * w,
                  (src[0] * _matrix[0][2] +
                   src[1] * _matrix[1][2] +
                   src[2] * _matrix[2][2] +
                            _matrix[3][2]) * w);
}

//! Multiplies matrix by given column point. The full (4x4) matrix is used.
 
template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multFullMatrixPnt(PointType3f &pnt)const
{
    multFullMatrixPnt(pnt, pnt);
}

/*! \brief Multiplies matrix by given column vector,  where the resulting
    vector is given
*/

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multMatrixVec(
    const VectorType3f &src,
          VectorType3f &dst) const
{
    dst.setValues((src[0] * _matrix[0][0] +
                   src[1] * _matrix[1][0] +
                   src[2] * _matrix[2][0]),
                  (src[0] * _matrix[0][1] +
                   src[1] * _matrix[1][1] +
                   src[2] * _matrix[2][1]),
                  (src[0] * _matrix[0][2] +
                   src[1] * _matrix[1][2] +
                   src[2] * _matrix[2][2]));
}


//! Multiplies matrix by given column vector

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multMatrixVec(VectorType3f &vec) const
{
    multMatrixVec(vec, vec);
}

/*! \brief Multiplies matrix by given column vector,  where the resulting
    vector is given
*/

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multMatrixVec(
    const VectorType &src,
          VectorType &dst) const
{
    dst.setValues((src[0] * _matrix[0][0] +
                   src[1] * _matrix[1][0] +
                   src[2] * _matrix[2][0] +
                   src[3] * _matrix[3][0]),
                  (src[0] * _matrix[0][1] +
                   src[1] * _matrix[1][1] +
                   src[2] * _matrix[2][1] +
                   src[3] * _matrix[3][1]),
                  (src[0] * _matrix[0][2] +
                   src[1] * _matrix[1][2] +
                   src[2] * _matrix[2][2] +
                   src[3] * _matrix[3][2]),
                  (src[0] * _matrix[0][3] +
                   src[1] * _matrix[1][3] +
                   src[2] * _matrix[2][3] +
                   src[3] * _matrix[3][3]));
}


//! Multiplies matrix by given column vector

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multMatrixVec(VectorType &vec) const
{
    multMatrixVec(vec, vec);
}


//! Transforms the given point by the matrix

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::mult(PointType3f &pnt) const
{
    multMatrixPnt(pnt, pnt);
}

//! Transforms the given vector by the matrix

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::mult(VectorType3f &vec) const
{
    multMatrixVec(vec, vec);
}



/*! \brief Multiplies given row point by matrix, where the resulting point
    is given (pT * M)
*/

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multPntMatrix(
    const PointType3f &src,
          PointType3f &dst) const
{
    dst.setValues((src[0] * _matrix[0][0] +
                   src[1] * _matrix[0][1] +
                   src[2] * _matrix[0][2] +
                            _matrix[0][3]),
                  (src[0] * _matrix[1][0] +
                   src[1] * _matrix[1][1] +
                   src[2] * _matrix[1][2] +
                            _matrix[1][3]),
                  (src[0] * _matrix[2][0] +
                   src[1] * _matrix[2][1] +
                   src[2] * _matrix[2][2] +
                            _matrix[2][3]));
}

//! Multiplies given row point by matrix (pT * M) 

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multPntMatrix(PointType3f &pnt) const
{
    multPntMatrix(pnt, pnt);
}

/*! \brief Multiplies given row point by matrix, where the resulting point
    is given. The full (4x4) matrix is used (pT * M).
*/

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multPntFullMatrix(
    const PointType3f &src,
          PointType3f &dst) const
{
    ValueTypeT w =  src[0] * _matrix[3][0] +
                    src[1] * _matrix[3][1] +
                    src[2] * _matrix[3][2] +
                             _matrix[3][3];

    if( w == 0.0f )
    {
        SINFO << "multFullMatrixPnt: w == 0.0f!" << std::endl;

        dst.setValues(0, 0, 0);

        return;
    }

    w = 1./w;

    dst.setValues((src[0] * _matrix[0][0] +
                   src[1] * _matrix[0][1] +
                   src[2] * _matrix[0][2] +
                            _matrix[0][3]) * w,
                  (src[0] * _matrix[1][0] +
                   src[1] * _matrix[1][1] +
                   src[2] * _matrix[1][2] +
                            _matrix[1][3]) * w,
                  (src[0] * _matrix[2][0] +
                   src[1] * _matrix[2][1] +
                   src[2] * _matrix[2][2] +
                            _matrix[2][3]) * w);
}

//! Multiplies given row point by matrix. The full (4x4) matrix is used (pT*M).
 
template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multPntFullMatrix(PointType3f &pnt)const
{
    multPntFullMatrix(pnt, pnt);
}

/*! \brief Multiplies given row vector by matrix,  where the resulting
    vector is given (vT * M)
*/

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multVecMatrix(
    const VectorType3f &src,
          VectorType3f &dst) const
{
    dst.setValues((src[0] * _matrix[0][0] +
                   src[1] * _matrix[0][1] +
                   src[2] * _matrix[0][2]),
                  (src[0] * _matrix[1][0] +
                   src[1] * _matrix[1][1] +
                   src[2] * _matrix[1][2]),
                  (src[0] * _matrix[2][0] +
                   src[1] * _matrix[2][1] +
                   src[2] * _matrix[2][2]));
}

//! Multiplies given row vector by matrix

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multVecMatrix(VectorType3f &vec) const
{
    multVecMatrix(vec, vec);
}

#endif  // OSG_2_PREP_FULL

/*! Multiply the point \a pIn by this complete 4x4 matrix and store
    the result in \a pntOut.

    \note The resulting point can have a \c w coordinate different from 1.
    \note It is valid for parameters to be aliased, i.e. &pntIn == &pntOut.
 */
template <class ValueTypeT>
inline void
    TransformationMatrix<ValueTypeT>::mult(
        const PointType &pntIn, PointType &pntOut) const
{
    pntOut.setValues(
        (_matrix[0][0] * pntIn[0] +
         _matrix[1][0] * pntIn[1] +
         _matrix[2][0] * pntIn[2] +
         _matrix[3][0] * pntIn[3]  ),
        (_matrix[0][1] * pntIn[0] +
         _matrix[1][1] * pntIn[1] +
         _matrix[2][1] * pntIn[2] +
         _matrix[3][1] * pntIn[3]  ),
        (_matrix[0][2] * pntIn[0] +
         _matrix[1][2] * pntIn[1] +
         _matrix[2][2] * pntIn[2] +
         _matrix[3][2] * pntIn[3]  ),
        (_matrix[0][3] * pntIn[0] +
         _matrix[1][3] * pntIn[1] +
         _matrix[2][3] * pntIn[2] +
         _matrix[3][3] * pntIn[3]  ) );
}

/*! Multiply the 3 point \a pntIn by this complete 4x4 matrix and store
    the result in \a pntOut.

    \note Both \a pntIn and \a pntOut are treated as having w = 1 and
          \a pntOut is scaled correctly to satisfy this.          
    \note It is valid for parameters to be aliased, i.e. &pntIn == &pntOut.
 */
template <class ValueTypeT>
inline void
    TransformationMatrix<ValueTypeT>::multFull(
        const PointType3f &pntIn, PointType3f  &pntOut) const
{
    ValueType w = _matrix[0][3] * pntIn[0] +
                  _matrix[1][3] * pntIn[1] +
                  _matrix[2][3] * pntIn[2] +
                  _matrix[3][3];
                  
    if(w == TypeTraits<ValueType>::getZeroElement())
    {
        FWARNING(("TransformationMatrix<>::multFull(Pnt3, Pnt3): w == 0.0\n"));
    
        pntOut.setValues(
            (_matrix[0][0] * pntIn[0] +
             _matrix[1][0] * pntIn[1] +
             _matrix[2][0] * pntIn[2] +
             _matrix[3][0]             ),
            (_matrix[0][1] * pntIn[0] +
             _matrix[1][1] * pntIn[1] +
             _matrix[2][1] * pntIn[2] +
             _matrix[3][1]             ),
            (_matrix[0][2] * pntIn[0] +
             _matrix[1][2] * pntIn[1] +
             _matrix[2][2] * pntIn[2] +
             _matrix[3][2]             ) );
    }
    else
    {
        w = TypeTraits<ValueType>::getOneElement() / w;
        
        pntOut.setValues(
            (_matrix[0][0] * pntIn[0] +
             _matrix[1][0] * pntIn[1] +
             _matrix[2][0] * pntIn[2] +
             _matrix[3][0]             ) * w,
            (_matrix[0][1] * pntIn[0] +
             _matrix[1][1] * pntIn[1] +
             _matrix[2][1] * pntIn[2] +
             _matrix[3][1]             ) * w,
            (_matrix[0][2] * pntIn[0] +
             _matrix[1][2] * pntIn[1] +
             _matrix[2][2] * pntIn[2] +
             _matrix[3][2]             ) * w );
    }
}

/*! Multiply the 3 point \a pntIn by this matrix (considering only the 3x4 part)
    and store the result in \a pntOut.
    
    \note \a pntIn is treated as having w = 1.
    \note It is valid for parameters to be aliased, i.e. &pntIn == &pntOut.
 */
template <class ValueTypeT>
inline void
    TransformationMatrix<ValueTypeT>::mult(
        const PointType3f &pntIn, PointType3f &pntOut) const
{
    pntOut.setValues(
        (_matrix[0][0] * pntIn[0] +
         _matrix[1][0] * pntIn[1] +
         _matrix[2][0] * pntIn[2] +
         _matrix[3][0]             ),
        (_matrix[0][1] * pntIn[0] +
         _matrix[1][1] * pntIn[1] +
         _matrix[2][1] * pntIn[2] +
         _matrix[3][1]             ),
        (_matrix[0][2] * pntIn[0] +
         _matrix[1][2] * pntIn[1] +
         _matrix[2][2] * pntIn[2] +
         _matrix[3][2]             ) );
        
}
    
/*! Multiply the vector \a vecIn by this complete 4x4 matrix and store
    the result in \a vecOut.
    
    \note The resulting vector can have a \c w coordinate different from 0.
    \note It is valid for parameters to be aliased, i.e. &vecIn == &vecOut.
 */
template <class ValueTypeT>
inline void
    TransformationMatrix<ValueTypeT>::mult(
        const VectorType &vecIn, VectorType &vecOut) const
{
    vecOut.setValues(
        (_matrix[0][0] * vecIn[0] +
         _matrix[1][0] * vecIn[1] +
         _matrix[2][0] * vecIn[2]  ),
        (_matrix[0][1] * vecIn[0] +
         _matrix[1][1] * vecIn[1] +
         _matrix[2][1] * vecIn[2]  ),
        (_matrix[0][2] * vecIn[0] +
         _matrix[1][2] * vecIn[1] +
         _matrix[2][2] * vecIn[2]  ),
        (_matrix[0][3] * vecIn[0] +
         _matrix[1][3] * vecIn[1] +
         _matrix[2][3] * vecIn[2] +
         _matrix[3][3] * vecIn[3]  ) );
}

/*! Multiply the 3 vector \a vecIn by this complete 4x4 matrix and store
    the result in \a vecOut.
    
    \note Both \a vecIn and \a vecOut are treated as having w = 0, so actually
          only the 4x3 part of this matrix is applied.
    \note It is valid for parameters to be aliased, i.e. &vecIn == &vecOut.
 */
template <class ValueTypeT>
inline void
    TransformationMatrix<ValueTypeT>::multFull(
        const VectorType3f &vecIn, VectorType3f &vecOut) const
{
    ValueType w = _matrix[0][3] * vecIn[0] +
                  _matrix[1][3] * vecIn[1] +
                  _matrix[2][3] * vecIn[2];    

    if(w == TypeTraits<ValueType>::getZeroElement())
    {
        FWARNING(("TransformationMatrix<>::multFull(Vec3, Vec3): w == 0.0\n"));
    
        vecOut.setValues(
            (_matrix[0][0] * vecIn[0] +
             _matrix[1][0] * vecIn[1] +
             _matrix[2][0] * vecIn[2]  ),
            (_matrix[0][1] * vecIn[0] +
             _matrix[1][1] * vecIn[1] +
             _matrix[2][1] * vecIn[2]  ),
            (_matrix[0][2] * vecIn[0] +
             _matrix[1][2] * vecIn[1] +
             _matrix[2][2] * vecIn[2]  ) );
    }
    else
    {
        w = TypeTraits<ValueType>::getOneElement() / w;
        
        vecOut.setValues(
            (_matrix[0][0] * vecIn[0] +
             _matrix[1][0] * vecIn[1] +
             _matrix[2][0] * vecIn[2]  ) * w,
            (_matrix[0][1] * vecIn[0] +
             _matrix[1][1] * vecIn[1] +
             _matrix[2][1] * vecIn[2]  ) * w,
            (_matrix[0][2] * vecIn[0] +
             _matrix[1][2] * vecIn[1] +
             _matrix[2][2] * vecIn[2]  ) * w );
    }
}

/*! Multiply the 3 vector \a vecIn by this matrix (considering only the 3x4 part)
    and store the result in \a vecOut.
    
    \note \a vecIn is treated as having w = 0, so actually only the 3x3 part
          of this matrix is applied.
    \note It is valid for parameters to be aliased, i.e. &vecIn == &vecOut.
 */
template <class ValueTypeT>
inline void
    TransformationMatrix<ValueTypeT>::mult(
        const VectorType3f &vecIn, VectorType3f &vecOut) const
{
    vecOut.setValues(
        (_matrix[0][0] * vecIn[0] +
         _matrix[1][0] * vecIn[1] +
         _matrix[2][0] * vecIn[2]  ),
        (_matrix[0][1] * vecIn[0] +
         _matrix[1][1] * vecIn[1] +
         _matrix[2][1] * vecIn[2]  ),
        (_matrix[0][2] * vecIn[0] +
         _matrix[1][2] * vecIn[1] +
         _matrix[2][2] * vecIn[2]  ) );
}

/*! Multiply the 3 point \a pntIn by the 3x3 part of this matrix and store
    the result in \a pntOut.
    
    \note It is valid for parameters to be aliased, i.e. &pntIn == &pntOut.
 */
template <class ValueTypeT>
inline void
    TransformationMatrix<ValueTypeT>::mult3x3(
        const PointType3f &pntIn, PointType3f &pntOut) const
{
    pntOut.setValues(
        (_matrix[0][0] * pntIn[0] +
         _matrix[1][0] * pntIn[1] +
         _matrix[2][0] * pntIn[2]  ),
        (_matrix[0][1] * pntIn[0] +
         _matrix[1][1] * pntIn[1] +
         _matrix[2][1] * pntIn[2]  ),
        (_matrix[0][2] * pntIn[0] +
         _matrix[1][2] * pntIn[1] +
         _matrix[2][2] * pntIn[2]  ) );
}

/*! Multiply the 3 vector \a vecIn by the 3x3 part of this matrix and store
    the result in \a vecOut.
    
    \note It is valid for parameters to be aliased, i.e. &vecIn == &vecOut.
 */
template <class ValueTypeT>
inline void
    TransformationMatrix<ValueTypeT>::mult3x3(
        const VectorType3f &vecIn, VectorType3f &vecOut) const
{
    vecOut.setValues(
        (_matrix[0][0] * vecIn[0] +
         _matrix[1][0] * vecIn[1] +
         _matrix[2][0] * vecIn[2]  ),
        (_matrix[0][1] * vecIn[0] +
         _matrix[1][1] * vecIn[1] +
         _matrix[2][1] * vecIn[2]  ),
        (_matrix[0][2] * vecIn[0] +
         _matrix[1][2] * vecIn[1] +
         _matrix[2][2] * vecIn[2]  ) );
}

/*! \brief Multiplies given row point by matrix, where the resulting point
    is given (pT * M)
*/

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multLeft(
    const PointType3f &src,
          PointType3f &dst) const
{
    dst.setValues((src[0] * _matrix[0][0] +
                   src[1] * _matrix[0][1] +
                   src[2] * _matrix[0][2] +
                            _matrix[0][3]),
                  (src[0] * _matrix[1][0] +
                   src[1] * _matrix[1][1] +
                   src[2] * _matrix[1][2] +
                            _matrix[1][3]),
                  (src[0] * _matrix[2][0] +
                   src[1] * _matrix[2][1] +
                   src[2] * _matrix[2][2] +
                            _matrix[2][3]));
}

/*! \brief Multiplies given row point by matrix, where the resulting point
    is given. The full (4x4) matrix is used (pT * M).
*/

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multLeftFull(
    const PointType3f &src,
          PointType3f &dst) const
{
    ValueTypeT w =  src[0] * _matrix[3][0] +
                    src[1] * _matrix[3][1] +
                    src[2] * _matrix[3][2] +
                             _matrix[3][3];

    if( w == 0.0f )
    {
        SINFO << "multFullMatrixPnt: w == 0.0f!" << std::endl;

        dst.setValues(0, 0, 0);

        return;
    }

    w = 1./w;

    dst.setValues((src[0] * _matrix[0][0] +
                   src[1] * _matrix[0][1] +
                   src[2] * _matrix[0][2] +
                            _matrix[0][3]) * w,
                  (src[0] * _matrix[1][0] +
                   src[1] * _matrix[1][1] +
                   src[2] * _matrix[1][2] +
                            _matrix[1][3]) * w,
                  (src[0] * _matrix[2][0] +
                   src[1] * _matrix[2][1] +
                   src[2] * _matrix[2][2] +
                            _matrix[2][3]) * w);
}

/*! Multiply the 3 vector \a vecIn by this complete 4x4 matrix and store
    the result in \a vecOut.
    
    \note Both \a vecIn and \a vecOut are treated as having w = 0, so actually
          only the 4x3 part of this matrix is applied.
    \note It is valid for parameters to be aliased, i.e. &vecIn == &vecOut.
 */
template <class ValueTypeT>
inline void
    TransformationMatrix<ValueTypeT>::multLeftFull(
        const VectorType3f &vecIn, VectorType3f &vecOut) const
{
    ValueType w = _matrix[3][0] * vecIn[0] +
                  _matrix[3][1] * vecIn[1] +
                  _matrix[3][2] * vecIn[2];    

    if(w == TypeTraits<ValueType>::getZeroElement())
    {
        FWARNING(("TransformationMatrix<>::multFull(Vec3, Vec3): w == 0.0\n"));
    
        vecOut.setValues(
            (_matrix[0][0] * vecIn[0] +
             _matrix[0][1] * vecIn[1] +
             _matrix[0][2] * vecIn[2]  ),
            (_matrix[1][0] * vecIn[0] +
             _matrix[1][1] * vecIn[1] +
             _matrix[1][2] * vecIn[2]  ),
            (_matrix[2][0] * vecIn[0] +
             _matrix[2][1] * vecIn[1] +
             _matrix[2][2] * vecIn[2]  ) );
    }
    else
    {
        w = TypeTraits<ValueType>::getOneElement() / w;
        
        vecOut.setValues(
            (_matrix[0][0] * vecIn[0] +
             _matrix[0][1] * vecIn[1] +
             _matrix[0][2] * vecIn[2]  ) * w,
            (_matrix[1][0] * vecIn[0] +
             _matrix[1][1] * vecIn[1] +
             _matrix[1][2] * vecIn[2]  ) * w,
            (_matrix[2][0] * vecIn[0] +
             _matrix[2][1] * vecIn[1] +
             _matrix[2][2] * vecIn[2]  ) * w );
    }
}

/*! \brief Multiplies given row vector by matrix,  where the resulting
    vector is given (vT * M)
*/

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multLeft(
    const VectorType3f &src,
          VectorType3f &dst) const
{
    dst.setValues((src[0] * _matrix[0][0] +
                   src[1] * _matrix[0][1] +
                   src[2] * _matrix[0][2]),
                  (src[0] * _matrix[1][0] +
                   src[1] * _matrix[1][1] +
                   src[2] * _matrix[1][2]),
                  (src[0] * _matrix[2][0] +
                   src[1] * _matrix[2][1] +
                   src[2] * _matrix[2][2]));
}

/*! Multiply the point \a pntIn by this complete 4x4 matrix and return
    the result.

    \note The resulting point can have a \c w coordinate different from 1.

 */
template <class ValueTypeT>
inline typename TransformationMatrix<ValueTypeT>::PointType
    TransformationMatrix<ValueTypeT>::operator *(
        const PointType &pntIn) const
{
    PointType pntOut;
    
    this->mult(pntIn, pntOut);
    
    return pntOut;
}

/*! Multiply the 3 point \a pntIn by this matrix (considering only the 3x4 part)
    and return the result.
    
    \note \a pntIn is treated as having w = 1.
 */
template <class ValueTypeT>
inline typename TransformationMatrix<ValueTypeT>::PointType3f
    TransformationMatrix<ValueTypeT>::operator *(
        const PointType3f &pntIn) const
{
    PointType3f pntOut;
    
    this->mult(pntIn, pntOut);
    
    return pntOut;
}

/*! Multiply the vector \a vecIn by this complete 4x4 matrix and return
    the result.
    
    \note The resulting vector can have a \c w coordinate different from 1.
 */
template <class ValueTypeT>
inline typename TransformationMatrix<ValueTypeT>::VectorType
    TransformationMatrix<ValueTypeT>::operator *(
        const VectorType &vecIn) const
{
    VectorType vecOut;
    
    this->mult(vecIn, vecOut);
    
    return vecOut;
}

/*! Multiply the 3 vector \a vecIn by this matrix (considering only the 3x4 part)
    and return the result.
    
    \note \a vecIn is treated as having w = 0, so actually only the 3x3 part
          of this matrix is applied.
 */
template <class ValueTypeT>
inline typename TransformationMatrix<ValueTypeT>::VectorType3f
    TransformationMatrix<ValueTypeT>::operator *(
        const VectorType3f &vecIn) const
{
    VectorType3f vecOut;
    
    this->mult(vecIn, vecOut);
    
    return vecOut;
}

//#endif // OSG_2_PREP

/*---------------------------- simple math ---------------------------------*/

/*! \brief Returns true iff all matrix elements are equal within the given
    tolerance
*/

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::equals(
    const TransformationMatrix &matrix,
    const ValueType             tolerance) const
{
    UInt32 i;
    bool returnValue = true;

    for(i = 0; i < 4; i++)
    {
        returnValue &= _matrix[i].equals(matrix._matrix[i], tolerance);

        if(returnValue == false)
            break;
    }

    return returnValue;
}

//! Returns the determinat of the upper 3x3 submatrix

template<class ValueTypeT> inline
ValueTypeT TransformationMatrix<ValueTypeT>::det3(void) const
{
    return (_matrix[0][0] * _matrix[1][1] * _matrix[2][2] +
            _matrix[0][1] * _matrix[1][2] * _matrix[2][0] +
            _matrix[0][2] * _matrix[1][0] * _matrix[2][1] -
            _matrix[0][2] * _matrix[1][1] * _matrix[2][0] -
            _matrix[0][1] * _matrix[1][0] * _matrix[2][2] -
            _matrix[0][0] * _matrix[1][2] * _matrix[2][1]);
}

//! Returns the determinat of the whole 4x4 matrix

template<class ValueTypeT> inline
ValueTypeT TransformationMatrix<ValueTypeT>::det (void) const
{
    ValueTypeT
        a1, a2, a3, a4,
        b1, b2, b3, b4,
        c1, c2, c3, c4,
        d1, d2, d3, d4;

    a1 = _matrix[0][0];
    b1 = _matrix[1][0];
    c1 = _matrix[2][0];
    d1 = _matrix[3][0];

    a2 = _matrix[0][1];
    b2 = _matrix[1][1];
    c2 = _matrix[2][1];
    d2 = _matrix[3][1];

    a3 = _matrix[0][2];
    b3 = _matrix[1][2];
    c3 = _matrix[2][2];
    d3 = _matrix[3][2];

    a4 = _matrix[0][3];
    b4 = _matrix[1][3];
    c4 = _matrix[2][3];
    d4 = _matrix[3][3];

    return(   a1 * det3(b2, b3, b4, c2, c3, c4, d2, d3, d4)
            - b1 * det3(a2, a3, a4, c2, c3, c4, d2, d3, d4)
            + c1 * det3(a2, a3, a4, b2, b3, b4, d2, d3, d4)
            - d1 * det3(a2, a3, a4, b2, b3, b4, c2, c3, c4));

}

// This inverse stuff should be grouped in a better way :-). It's just a
// Cut&Paste section. I will have a look at it lateron (GV)

/*! \brief Stores the inverse of the matrix into result, returns true if the
     matrix is not singular
*/

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::inverse(
    TransformationMatrix &result) const
{
    ValueTypeT rDet;

    ValueTypeT
        a1, a2, a3, a4,
        b1, b2, b3, b4,
        c1, c2, c3, c4,
        d1, d2, d3, d4;

    a1 = _matrix[0][0];
    b1 = _matrix[1][0];
    c1 = _matrix[2][0];
    d1 = _matrix[3][0];

    a2 = _matrix[0][1];
    b2 = _matrix[1][1];
    c2 = _matrix[2][1];
    d2 = _matrix[3][1];

    a3 = _matrix[0][2];
    b3 = _matrix[1][2];
    c3 = _matrix[2][2];
    d3 = _matrix[3][2];

    a4 = _matrix[0][3];
    b4 = _matrix[1][3];
    c4 = _matrix[2][3];
    d4 = _matrix[3][3];

    rDet = det();

    if(osgabs(rDet) < 1E-30)
    {
#ifdef OSG_PRINT_MATHERR
        fprintf(stderr, "invertMatrix: Singular matrix, no inverse!\n");
#endif
        result.setIdentity();

        return false;
    }

    rDet = 1.f / rDet;

    result[0][0]  =   det3(b2, b3, b4, c2, c3,
                           c4, d2, d3, d4) * rDet;
    result[0][1]  = - det3(a2, a3, a4, c2, c3, c4,
                           d2, d3, d4) * rDet;
    result[0][2]  =   det3(a2, a3, a4, b2, b3, b4,
                           d2, d3, d4) * rDet;
    result[0][3]  = - det3(a2, a3, a4, b2, b3, b4,
                           c2, c3, c4) * rDet;

    result[1][0]  = - det3(b1, b3, b4, c1, c3, c4,
                           d1, d3, d4) * rDet;
    result[1][1]  =   det3(a1, a3, a4, c1, c3, c4,
                           d1, d3, d4) * rDet;
    result[1][2]  = - det3(a1, a3, a4, b1, b3, b4,
                           d1, d3, d4) * rDet;
    result[1][3]  =   det3(a1, a3, a4, b1, b3, b4,
                           c1, c3, c4) * rDet;

    result[2][0]  =   det3(b1, b2, b4, c1, c2, c4,
                           d1, d2, d4) * rDet;
    result[2][1]  = - det3(a1, a2, a4, c1, c2, c4,
                           d1, d2, d4) * rDet;
    result[2][2]  =   det3(a1, a2, a4, b1, b2, b4,
                           d1, d2, d4) * rDet;
    result[2][3]  = - det3(a1, a2, a4, b1, b2, b4,
                           c1, c2, c4) * rDet;

    result[3][0]  = - det3(b1, b2, b3, c1, c2, c3,
                           d1, d2, d3) * rDet;
    result[3][1]  =   det3(a1, a2, a3, c1, c2, c3,
                           d1, d2, d3) * rDet;
    result[3][2]  = - det3(a1, a2, a3, b1, b2, b3,
                           d1, d2, d3) * rDet;
    result[3][3]  =   det3(a1, a2, a3, b1, b2, b3,
                           c1, c2, c3) * rDet;

    return true;
}

/*! \brief Inverts the matrix, returns true if the
     matrix is not singular
*/

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::invert(void)
{
    ValueTypeT           rDet;
    TransformationMatrix result;

    ValueTypeT
        a1, a2, a3, a4,
        b1, b2, b3, b4,
        c1, c2, c3, c4,
        d1, d2, d3, d4;

    a1 = _matrix[0][0];
    b1 = _matrix[1][0];
    c1 = _matrix[2][0];
    d1 = _matrix[3][0];

    a2 = _matrix[0][1];
    b2 = _matrix[1][1];
    c2 = _matrix[2][1];
    d2 = _matrix[3][1];

    a3 = _matrix[0][2];
    b3 = _matrix[1][2];
    c3 = _matrix[2][2];
    d3 = _matrix[3][2];

    a4 = _matrix[0][3];
    b4 = _matrix[1][3];
    c4 = _matrix[2][3];
    d4 = _matrix[3][3];

    rDet = det();

    if(osgabs(rDet) < 1E-30)
    {
#ifdef OSG_PRINT_MATHERR
        fprintf(stderr, "invertMatrix: Singular matrix, no inverse!\n");
#endif
        setIdentity();

        return false;
    }

    rDet = 1.f / rDet;

    result[0][0]  =   det3(b2, b3, b4, c2, c3,
                           c4, d2, d3, d4) * rDet;
    result[0][1]  = - det3(a2, a3, a4, c2, c3, c4,
                           d2, d3, d4) * rDet;
    result[0][2]  =   det3(a2, a3, a4, b2, b3, b4,
                           d2, d3, d4) * rDet;
    result[0][3]  = - det3(a2, a3, a4, b2, b3, b4,
                           c2, c3, c4) * rDet;

    result[1][0]  = - det3(b1, b3, b4, c1, c3, c4,
                           d1, d3, d4) * rDet;
    result[1][1]  =   det3(a1, a3, a4, c1, c3, c4,
                           d1, d3, d4) * rDet;
    result[1][2]  = - det3(a1, a3, a4, b1, b3, b4,
                           d1, d3, d4) * rDet;
    result[1][3]  =   det3(a1, a3, a4, b1, b3, b4,
                           c1, c3, c4) * rDet;

    result[2][0]  =   det3(b1, b2, b4, c1, c2, c4,
                           d1, d2, d4) * rDet;
    result[2][1]  = - det3(a1, a2, a4, c1, c2, c4,
                           d1, d2, d4) * rDet;
    result[2][2]  =   det3(a1, a2, a4, b1, b2, b4,
                           d1, d2, d4) * rDet;
    result[2][3]  = - det3(a1, a2, a4, b1, b2, b4,
                           c1, c2, c4) * rDet;

    result[3][0]  = - det3(b1, b2, b3, c1, c2, c3,
                           d1, d2, d3) * rDet;
    result[3][1]  =   det3(a1, a2, a3, c1, c2, c3,
                           d1, d2, d3) * rDet;
    result[3][2]  = - det3(a1, a2, a3, b1, b2, b3,
                           d1, d2, d3) * rDet;
    result[3][3]  =   det3(a1, a2, a3, b1, b2, b3,
                           c1, c2, c3) * rDet;

    *this = result;

    return true;
}

/*! \brief Set the matrix to be the inverse of the given one, returns true if
     the matrix is not singular
*/

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::invertFrom(
    const TransformationMatrix &matrix)
{
    ValueTypeT rDet;

    ValueTypeT
        a1, a2, a3, a4,
        b1, b2, b3, b4,
        c1, c2, c3, c4,
        d1, d2, d3, d4;

    a1 = matrix._matrix[0][0];
    b1 = matrix._matrix[1][0];
    c1 = matrix._matrix[2][0];
    d1 = matrix._matrix[3][0];

    a2 = matrix._matrix[0][1];
    b2 = matrix._matrix[1][1];
    c2 = matrix._matrix[2][1];
    d2 = matrix._matrix[3][1];

    a3 = matrix._matrix[0][2];
    b3 = matrix._matrix[1][2];
    c3 = matrix._matrix[2][2];
    d3 = matrix._matrix[3][2];

    a4 = matrix._matrix[0][3];
    b4 = matrix._matrix[1][3];
    c4 = matrix._matrix[2][3];
    d4 = matrix._matrix[3][3];

    rDet = matrix.det();

    if (osgabs(rDet) < 1E-30)
    {
#ifdef OSG_PRINT_MATHERR
        fprintf(stderr, "invertMatrix: Singular matrix, no inverse!\n");
#endif
        setIdentity();

        return false;
    }

    rDet = 1.f / rDet;

    _matrix[0][0]  =   det3(b2, b3, b4, c2, c3,
                            c4, d2, d3, d4) * rDet;
    _matrix[0][1]  = - det3(a2, a3, a4, c2, c3, c4,
                            d2, d3, d4) * rDet;
    _matrix[0][2]  =   det3(a2, a3, a4, b2, b3, b4,
                            d2, d3, d4) * rDet;
    _matrix[0][3]  = - det3(a2, a3, a4, b2, b3, b4,
                            c2, c3, c4) * rDet;

    _matrix[1][0]  = - det3(b1, b3, b4, c1, c3, c4,
                            d1, d3, d4) * rDet;
    _matrix[1][1]  =   det3(a1, a3, a4, c1, c3, c4,
                            d1, d3, d4) * rDet;
    _matrix[1][2]  = - det3(a1, a3, a4, b1, b3, b4,
                            d1, d3, d4) * rDet;
    _matrix[1][3]  =   det3(a1, a3, a4, b1, b3, b4,
                            c1, c3, c4) * rDet;

    _matrix[2][0]  =   det3(b1, b2, b4, c1, c2, c4,
                            d1, d2, d4) * rDet;
    _matrix[2][1]  = - det3(a1, a2, a4, c1, c2, c4,
                            d1, d2, d4) * rDet;
    _matrix[2][2]  =   det3(a1, a2, a4, b1, b2, b4,
                            d1, d2, d4) * rDet;
    _matrix[2][3]  = - det3(a1, a2, a4, b1, b2, b4,
                            c1, c2, c4) * rDet;

    _matrix[3][0]  = - det3(b1, b2, b3, c1, c2, c3,
                            d1, d2, d3) * rDet;
    _matrix[3][1]  =   det3(a1, a2, a3, c1, c2, c3,
                            d1, d2, d3) * rDet;
    _matrix[3][2]  = - det3(a1, a2, a3, b1, b2, b3,
                            d1, d2, d3) * rDet;
    _matrix[3][3]  =   det3(a1, a2, a3, b1, b2, b3,
                            c1, c2, c3) * rDet;

    return true;
}

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::inverse3(
    TransformationMatrix &result) const
{
    ValueTypeT rDet = det3();

    if(osgabs(rDet) < 1E-20)
    {
#ifdef OSG_PRINT_MATHERR
        fprintf(stderr, "inverse3: matrix singular, no inverse!\n");
#endif

        result.setIdentity();

        return false;
    }

    rDet = 1.0f / rDet;

    result[0][0]  =   det2(_matrix[1][1],
                           _matrix[1][2],
                           _matrix[2][1],
                           _matrix[2][2]) * rDet;
    result[0][1]  = - det2(_matrix[0][1],
                           _matrix[0][2],
                           _matrix[2][1],
                           _matrix[2][2]) * rDet;
    result[0][2]  =   det2(_matrix[0][1],
                           _matrix[0][2],
                           _matrix[1][1],
                           _matrix[1][2]) * rDet;

    result[1][0]  = - det2(_matrix[1][0],
                           _matrix[1][2],
                           _matrix[2][0],
                           _matrix[2][2]) * rDet;
    result[1][1]  =   det2(_matrix[0][0],
                           _matrix[0][2],
                           _matrix[2][0],
                           _matrix[2][2]) * rDet;
    result[1][2]  = - det2(_matrix[0][0],
                           _matrix[0][2],
                           _matrix[1][0],
                           _matrix[1][2]) * rDet;

    result[2][0]  =   det2(_matrix[1][0],
                           _matrix[1][1],
                           _matrix[2][0],
                           _matrix[2][1]) * rDet;
    result[2][1]  = - det2(_matrix[0][0],
                           _matrix[0][1],
                           _matrix[2][0],
                           _matrix[2][1]) * rDet;
    result[2][2]  =   det2(_matrix[0][0],
                           _matrix[0][1],
                           _matrix[1][0],
                           _matrix[1][1]) * rDet;

    result[3][0] =
        result[3][1] =
        result[3][2] = TypeTraits<ValueType>::getZeroElement();

    result[3][3] = TypeTraits<ValueType>::getOneElement();

    return true;
}

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::invert3(void)
{
    ValueTypeT           rDet    = det3();
    TransformationMatrix result;

    if(osgabs(rDet) < 1E-20)
    {
#ifdef OSG_PRINT_MATHERR
        fprintf(stderr, "invert3: matrix singular, no inverse!\n");
#endif
        result.setIdentity();

        return false;
    }

    rDet = 1.0f / rDet;

    result[0][0]  =   det2(_matrix[1][1],
                           _matrix[1][2],
                           _matrix[2][1],
                           _matrix[2][2]) * rDet;
    result[0][1]  = - det2(_matrix[0][1],
                           _matrix[0][2],
                           _matrix[2][1],
                           _matrix[2][2]) * rDet;
    result[0][2]  =   det2(_matrix[0][1],
                           _matrix[0][2],
                           _matrix[1][1],
                           _matrix[1][2]) * rDet;

    result[1][0]  = - det2(_matrix[1][0],
                           _matrix[1][2],
                           _matrix[2][0],
                           _matrix[2][2]) * rDet;
    result[1][1]  =   det2(_matrix[0][0],
                           _matrix[0][2],
                           _matrix[2][0],
                           _matrix[2][2]) * rDet;
    result[1][2]  = - det2(_matrix[0][0],
                           _matrix[0][2],
                           _matrix[1][0],
                           _matrix[1][2]) * rDet;

    result[2][0]  =   det2(_matrix[1][0],
                           _matrix[1][1],
                           _matrix[2][0],
                           _matrix[2][1]) * rDet;
    result[2][1]  = - det2(_matrix[0][0],
                           _matrix[0][1],
                           _matrix[2][0],
                           _matrix[2][1]) * rDet;
    result[2][2]  =   det2(_matrix[0][0],
                           _matrix[0][1],
                           _matrix[1][0],
                           _matrix[1][1]) * rDet;

    result[3][0] =
        result[3][1] =
        result[3][2] = TypeTraits<ValueType>::getZeroElement();

    result[3][3] = TypeTraits<ValueType>::getOneElement();

    *this = result;

    return true;
}

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::invertFrom3(
    const TransformationMatrix &matrix)
{
    ValueTypeT rDet = matrix.det3();

    if(osgabs(rDet) < 1E-20)
    {
#ifdef OSG_PRINT_MATHERR
        fprintf(stderr, "invertFrom3: matrix singular, no inverse!\n");
#endif

        setIdentity();

        return false;
    }

    rDet = 1.0f / rDet;

    _matrix[0][0]  =   det2(matrix._matrix[1][1],
                            matrix._matrix[1][2],
                            matrix._matrix[2][1],
                            matrix._matrix[2][2]) * rDet;
    _matrix[0][1]  = - det2(matrix._matrix[0][1],
                            matrix._matrix[0][2],
                            matrix._matrix[2][1],
                            matrix._matrix[2][2]) * rDet;
    _matrix[0][2]  =   det2(matrix._matrix[0][1],
                            matrix._matrix[0][2],
                            matrix._matrix[1][1],
                            matrix._matrix[1][2]) * rDet;

    _matrix[1][0]  = - det2(matrix._matrix[1][0],
                            matrix._matrix[1][2],
                            matrix._matrix[2][0],
                            matrix._matrix[2][2]) * rDet;
    _matrix[1][1]  =   det2(matrix._matrix[0][0],
                            matrix._matrix[0][2],
                            matrix._matrix[2][0],
                            matrix._matrix[2][2]) * rDet;
    _matrix[1][2]  = - det2(matrix._matrix[0][0],
                            matrix._matrix[0][2],
                            matrix._matrix[1][0],
                            matrix._matrix[1][2]) * rDet;

    _matrix[2][0]  =   det2(matrix._matrix[1][0],
                            matrix._matrix[1][1],
                            matrix._matrix[2][0],
                            matrix._matrix[2][1]) * rDet;
    _matrix[2][1]  = - det2(matrix._matrix[0][0],
                            matrix._matrix[0][1],
                            matrix._matrix[2][0],
                            matrix._matrix[2][1]) * rDet;
    _matrix[2][2]  =   det2(matrix._matrix[0][0],
                            matrix._matrix[0][1],
                            matrix._matrix[1][0],
                            matrix._matrix[1][1]) * rDet;

    _matrix[3][0] =
        _matrix[3][1] =
        _matrix[3][2] = TypeTraits<ValueType>::getZeroElement();

    _matrix[3][3] = TypeTraits<ValueType>::getOneElement();

    return true;
}

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::transposed(
        TransformationMatrix &result) const
{
    result.setValueTransposed(
        (*this)[0][0], (*this)[1][0], (*this)[2][0], (*this)[3][0],
        (*this)[0][1], (*this)[1][1], (*this)[2][1], (*this)[3][1],
        (*this)[0][2], (*this)[1][2], (*this)[2][2], (*this)[3][2],
        (*this)[0][3], (*this)[1][3], (*this)[2][3], (*this)[3][3]);

    return true;
}

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::transpose(void)
{
    ValueTypeT tmp;

    tmp = (*this)[1][0]; (*this)[1][0] = (*this)[0][1]; (*this)[0][1] = tmp;
    tmp = (*this)[2][0]; (*this)[2][0] = (*this)[0][2]; (*this)[0][2] = tmp;
    tmp = (*this)[3][0]; (*this)[3][0] = (*this)[0][3]; (*this)[0][3] = tmp;
    tmp = (*this)[2][1]; (*this)[2][1] = (*this)[1][2]; (*this)[1][2] = tmp;
    tmp = (*this)[3][1]; (*this)[3][1] = (*this)[1][3]; (*this)[1][3] = tmp;
    tmp = (*this)[3][2]; (*this)[3][2] = (*this)[2][3]; (*this)[2][3] = tmp;

    return true;
}

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::transposeFrom(
    const TransformationMatrix &matrix)
{
    this->setValueTransposed(
        matrix[0][0], matrix[1][0], matrix[2][0], matrix[3][0],
        matrix[0][1], matrix[1][1], matrix[2][1], matrix[3][1],
        matrix[0][2], matrix[1][2], matrix[2][2], matrix[3][2],
        matrix[0][3], matrix[1][3], matrix[2][3], matrix[3][3]);
    
    return true;
}

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::mult(const TransformationMatrix &matrix)
{
    ValueTypeT rTmpMat[4][4];

    (rTmpMat)[0][0] = rowMulCol4((*this), 0, (matrix), 0);
    (rTmpMat)[0][1] = rowMulCol4((*this), 1, (matrix), 0);
    (rTmpMat)[0][2] = rowMulCol4((*this), 2, (matrix), 0);
    (rTmpMat)[0][3] = rowMulCol4((*this), 3, (matrix), 0);

    (rTmpMat)[1][0] = rowMulCol4((*this), 0, (matrix), 1);
    (rTmpMat)[1][1] = rowMulCol4((*this), 1, (matrix), 1);
    (rTmpMat)[1][2] = rowMulCol4((*this), 2, (matrix), 1);
    (rTmpMat)[1][3] = rowMulCol4((*this), 3, (matrix), 1);

    (rTmpMat)[2][0] = rowMulCol4((*this), 0, (matrix), 2);
    (rTmpMat)[2][1] = rowMulCol4((*this), 1, (matrix), 2);
    (rTmpMat)[2][2] = rowMulCol4((*this), 2, (matrix), 2);
    (rTmpMat)[2][3] = rowMulCol4((*this), 3, (matrix), 2);

    (rTmpMat)[3][0] = rowMulCol4((*this), 0, (matrix), 3);
    (rTmpMat)[3][1] = rowMulCol4((*this), 1, (matrix), 3);
    (rTmpMat)[3][2] = rowMulCol4((*this), 2, (matrix), 3);
    (rTmpMat)[3][3] = rowMulCol4((*this), 3, (matrix), 3);

    _matrix[0][0] = rTmpMat[0][0];
    _matrix[0][1] = rTmpMat[0][1];
    _matrix[0][2] = rTmpMat[0][2];
    _matrix[0][3] = rTmpMat[0][3];

    _matrix[1][0] = rTmpMat[1][0];
    _matrix[1][1] = rTmpMat[1][1];
    _matrix[1][2] = rTmpMat[1][2];
    _matrix[1][3] = rTmpMat[1][3];

    _matrix[2][0] = rTmpMat[2][0];
    _matrix[2][1] = rTmpMat[2][1];
    _matrix[2][2] = rTmpMat[2][2];
    _matrix[2][3] = rTmpMat[2][3];

    _matrix[3][0] = rTmpMat[3][0];
    _matrix[3][1] = rTmpMat[3][1];
    _matrix[3][2] = rTmpMat[3][2];
    _matrix[3][3] = rTmpMat[3][3];
}

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multLeft(
    const TransformationMatrix &matrix)
{
    ValueTypeT rTmpMat[4][4];

    (rTmpMat)[0][0] = rowMulCol4((matrix), 0, (*this), 0);
    (rTmpMat)[0][1] = rowMulCol4((matrix), 1, (*this), 0);
    (rTmpMat)[0][2] = rowMulCol4((matrix), 2, (*this), 0);
    (rTmpMat)[0][3] = rowMulCol4((matrix), 3, (*this), 0);

    (rTmpMat)[1][0] = rowMulCol4((matrix), 0, (*this), 1);
    (rTmpMat)[1][1] = rowMulCol4((matrix), 1, (*this), 1);
    (rTmpMat)[1][2] = rowMulCol4((matrix), 2, (*this), 1);
    (rTmpMat)[1][3] = rowMulCol4((matrix), 3, (*this), 1);

    (rTmpMat)[2][0] = rowMulCol4((matrix), 0, (*this), 2);
    (rTmpMat)[2][1] = rowMulCol4((matrix), 1, (*this), 2);
    (rTmpMat)[2][2] = rowMulCol4((matrix), 2, (*this), 2);
    (rTmpMat)[2][3] = rowMulCol4((matrix), 3, (*this), 2);

    (rTmpMat)[3][0] = rowMulCol4((matrix), 0, (*this), 3);
    (rTmpMat)[3][1] = rowMulCol4((matrix), 1, (*this), 3);
    (rTmpMat)[3][2] = rowMulCol4((matrix), 2, (*this), 3);
    (rTmpMat)[3][3] = rowMulCol4((matrix), 3, (*this), 3);

    _matrix[0][0] = rTmpMat[0][0];
    _matrix[0][1] = rTmpMat[0][1];
    _matrix[0][2] = rTmpMat[0][2];
    _matrix[0][3] = rTmpMat[0][3];

    _matrix[1][0] = rTmpMat[1][0];
    _matrix[1][1] = rTmpMat[1][1];
    _matrix[1][2] = rTmpMat[1][2];
    _matrix[1][3] = rTmpMat[1][3];

    _matrix[2][0] = rTmpMat[2][0];
    _matrix[2][1] = rTmpMat[2][1];
    _matrix[2][2] = rTmpMat[2][2];
    _matrix[2][3] = rTmpMat[2][3];

    _matrix[3][0] = rTmpMat[3][0];
    _matrix[3][1] = rTmpMat[3][1];
    _matrix[3][2] = rTmpMat[3][2];
    _matrix[3][3] = rTmpMat[3][3];
}

//! Adds the given matrix to this matrix

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::add(const TransformationMatrix &matrix)
{
    _matrix[0][0] += matrix._matrix[0][0];
    _matrix[0][1] += matrix._matrix[0][1];
    _matrix[0][2] += matrix._matrix[0][2];
    _matrix[0][3] += matrix._matrix[0][3];

    _matrix[1][0] += matrix._matrix[1][0];
    _matrix[1][1] += matrix._matrix[1][1];
    _matrix[1][2] += matrix._matrix[1][2];
    _matrix[1][3] += matrix._matrix[1][3];

    _matrix[2][0] += matrix._matrix[2][0];
    _matrix[2][1] += matrix._matrix[2][1];
    _matrix[2][2] += matrix._matrix[2][2];
    _matrix[2][3] += matrix._matrix[2][3];

    _matrix[3][0] += matrix._matrix[3][0];
    _matrix[3][1] += matrix._matrix[3][1];
    _matrix[3][2] += matrix._matrix[3][2];
    _matrix[3][3] += matrix._matrix[3][3];
}

//! Scales the elements of this matrix

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::scale(ValueTypeT s)
{
    _matrix[0][0] *= s;
    _matrix[0][1] *= s;
    _matrix[0][2] *= s;
    _matrix[0][3] *= s;

    _matrix[1][0] *= s;
    _matrix[1][1] *= s;
    _matrix[1][2] *= s;
    _matrix[1][3] *= s;

    _matrix[2][0] *= s;
    _matrix[2][1] *= s;
    _matrix[2][2] *= s;
    _matrix[2][3] *= s;

    _matrix[3][0] *= s;
    _matrix[3][1] *= s;
    _matrix[3][2] *= s;
    _matrix[3][3] *= s;
}

//! Adds a scaled version of the given matrix to this matrix

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::addScaled(
    const TransformationMatrix &matrix, 
          ValueTypeT            s)
{
    _matrix[0][0] += s*matrix._matrix[0][0];
    _matrix[0][1] += s*matrix._matrix[0][1];
    _matrix[0][2] += s*matrix._matrix[0][2];
    _matrix[0][3] += s*matrix._matrix[0][3];

    _matrix[1][0] += s*matrix._matrix[1][0];
    _matrix[1][1] += s*matrix._matrix[1][1];
    _matrix[1][2] += s*matrix._matrix[1][2];
    _matrix[1][3] += s*matrix._matrix[1][3];

    _matrix[2][0] += s*matrix._matrix[2][0];
    _matrix[2][1] += s*matrix._matrix[2][1];
    _matrix[2][2] += s*matrix._matrix[2][2];
    _matrix[2][3] += s*matrix._matrix[2][3];

    _matrix[3][0] += s*matrix._matrix[3][0];
    _matrix[3][1] += s*matrix._matrix[3][1];
    _matrix[3][2] += s*matrix._matrix[3][2];
    _matrix[3][3] += s*matrix._matrix[3][3];
}

//! Negates the matrix in place

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::negate(void)
{
    _matrix[0][0] *= -1.0;
    _matrix[0][1] *= -1.0;
    _matrix[0][2] *= -1.0;
    _matrix[0][3] *= -1.0;

    _matrix[1][0] *= -1.0;
    _matrix[1][1] *= -1.0;
    _matrix[1][2] *= -1.0;
    _matrix[1][3] *= -1.0;

    _matrix[2][0] *= -1.0;
    _matrix[2][1] *= -1.0;
    _matrix[2][2] *= -1.0;
    _matrix[2][3] *= -1.0;

    _matrix[3][0] *= -1.0;
    _matrix[3][1] *= -1.0;
    _matrix[3][2] *= -1.0;
    _matrix[3][3] *= -1.0;
}

/*! Returns the sum of absolute values of the entries in this matrix.

    \note This is \em NOT the usual 1-norm for matrices.
 */
template<class ValueTypeT> inline
ValueTypeT TransformationMatrix<ValueTypeT>::norm1(void) const
{
    ValueType m = TypeTraits<ValueType>::getZeroElement();

    m += osgabs(_matrix[0][0]);
    m += osgabs(_matrix[0][1]);
    m += osgabs(_matrix[0][2]);
    m += osgabs(_matrix[0][3]);
    m += osgabs(_matrix[1][0]);
    m += osgabs(_matrix[1][1]);
    m += osgabs(_matrix[1][2]);
    m += osgabs(_matrix[1][3]);
    m += osgabs(_matrix[2][0]);
    m += osgabs(_matrix[2][1]);
    m += osgabs(_matrix[2][2]);
    m += osgabs(_matrix[2][3]);
    m += osgabs(_matrix[3][0]);
    m += osgabs(_matrix[3][1]);
    m += osgabs(_matrix[3][2]);
    m += osgabs(_matrix[3][3]);

    return m;
}

/*! Returns the square root of the sum of squared entries in the matrix.

    \note This is \em NOT the usual 2-norm for matrices.
 */
template<class ValueTypeT> inline
ValueTypeT TransformationMatrix<ValueTypeT>::norm2(void) const
{
    ValueType m = TypeTraits<ValueType>::getZeroElement();
    ValueType t;

    t = _matrix[0][0]; m += t*t;
    t = _matrix[0][1]; m += t*t;
    t = _matrix[0][2]; m += t*t;
    t = _matrix[0][3]; m += t*t;
    t = _matrix[1][0]; m += t*t;
    t = _matrix[1][1]; m += t*t;
    t = _matrix[1][2]; m += t*t;
    t = _matrix[1][3]; m += t*t;
    t = _matrix[2][0]; m += t*t;
    t = _matrix[2][1]; m += t*t;
    t = _matrix[2][2]; m += t*t;
    t = _matrix[2][3]; m += t*t;
    t = _matrix[3][0]; m += t*t;
    t = _matrix[3][1]; m += t*t;
    t = _matrix[3][2]; m += t*t;
    t = _matrix[3][3]; m += t*t;

    return osgsqrt(m);
}

/*! Returns the largest absolute value of all entries in the matrix.

    \note This is \em NOT the usual Infinity-norm for matrices.
 */
template<class ValueTypeT> inline
ValueTypeT TransformationMatrix<ValueTypeT>::normInfinity(void) const
{
    ValueType m = TypeTraits<ValueType>::getZeroElement();
    ValueType t;

    if((t = osgabs(_matrix[0][0])) > m)
        m = t;
    if((t = osgabs(_matrix[0][1])) > m)
        m = t;
    if((t = osgabs(_matrix[0][2])) > m)
        m = t;
    if((t = osgabs(_matrix[0][3])) > m)
        m = t;
    if((t = osgabs(_matrix[1][0])) > m)
        m = t;
    if((t = osgabs(_matrix[1][1])) > m)
        m = t;
    if((t = osgabs(_matrix[1][2])) > m)
        m = t;
    if((t = osgabs(_matrix[1][3])) > m)
        m = t;
    if((t = osgabs(_matrix[2][0])) > m)
        m = t;
    if((t = osgabs(_matrix[2][1])) > m)
        m = t;
    if((t = osgabs(_matrix[2][2])) > m)
        m = t;
    if((t = osgabs(_matrix[2][3])) > m)
        m = t;
    if((t = osgabs(_matrix[3][0])) > m)
        m = t;
    if((t = osgabs(_matrix[3][1])) > m)
        m = t;
    if((t = osgabs(_matrix[3][2])) > m)
        m = t;
    if((t = osgabs(_matrix[3][3])) > m)
        m = t;

    return m;
}

/*! \brief Computes the square root of the matrix and stores it in
    result, assumes det > 0
*/

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::sqrt(TransformationMatrix &result) const
{
    TransformationMatrix iX;
    TransformationMatrix  Y;
    TransformationMatrix iY;

    ValueTypeT  g;
    ValueTypeT ig;

    result.setValue(*this);

    Y.setIdentity();

    for(UInt32 i = 0; i < 6; i++)
    {
        result.inverse(iX);

        Y.inverse(iY);

        g = osgabs(osgpow(result.det() * Y.det(), ValueTypeT(-0.125)));

        ig = ValueTypeT(1.0 / g);

        result.scale    (g     );
        result.addScaled(iY, ig);
        result.scale    (0.5   );

        Y.scale    (g     );
        Y.addScaled(iX, ig);
        Y.scale    (0.5   );
    }

    // ToDo: return should depend on achieved accuracy
    return true;
}

/*! \brief Sets this matrix to the square root of the given matrix,
     assumes det > 0
*/

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::sqrtOf(
    const TransformationMatrix &matrix)
{
    TransformationMatrix iX;
    TransformationMatrix  Y;
    TransformationMatrix iY;

    ValueTypeT  g;
    ValueTypeT ig;

    setValue(matrix);

    Y.setIdentity();

    for(Int32 i = 0; i < 6; i++)
    {
        inverse(iX);

        Y.inverse(iY);

        g = osgabs(osgpow(det() * Y.det(), ValueTypeT(-0.125)));

        ig = ValueTypeT(1.0 / g);

        scale    (g     );
        addScaled(iY, ig);
        scale    (0.5   );

        Y.scale    (g     );
        Y.addScaled(iX, ig);
        Y.scale    (0.5);
    }

    // ToDo: return should depend on achieved accuracy
    return true;
}

//! Sets this matrix to its square root, assumes det > 0

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::sqrt(void)
{
    TransformationMatrix iX;
    TransformationMatrix  Y;
    TransformationMatrix iY;

    ValueTypeT  g;
    ValueTypeT ig;

    Y.setIdentity();

    for(Int32 i = 0; i < 6; i++)
    {
        inverse(iX);

        Y.inverse(iY);

        g = osgabs(osgpow(det() * Y.det(), ValueTypeT(-0.125)));

        ig = ValueTypeT(1.0 / g);

        scale    (g     );
        addScaled(iY, ig);
        scale    (0.5   );

        Y.scale    (g     );
        Y.addScaled(iX, ig);
        Y.scale    (0.5   );
    }

    // ToDo: return should depend on achieved accuracy
    return true;
}

/*! \brief Computes the logarithm of this matrix and stores it in
    result, assumes det > 0
*/

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::log(TransformationMatrix &result) const
{
    const Int32      maxiter = 12;
          Int32      k       = 0;
          Int32      i       = 0;
    const ValueTypeT eps     = 1e-12;

    TransformationMatrix A(*this);
    TransformationMatrix Z;

    // Take repeated square roots to reduce spectral radius
    Z.setValue(A);

    Z[0][0] -= TypeTraits<ValueType>::getOneElement();
    Z[1][1] -= TypeTraits<ValueType>::getOneElement();
    Z[2][2] -= TypeTraits<ValueType>::getOneElement();
    Z[3][3] -= TypeTraits<ValueType>::getOneElement();

    while(Z.normInfinity() > 0.5)
    {
        A.sqrt    ( );
        Z.setValue(A);

        Z[0][0] -= TypeTraits<ValueType>::getOneElement();
        Z[1][1] -= TypeTraits<ValueType>::getOneElement();
        Z[2][2] -= TypeTraits<ValueType>::getOneElement();
        Z[3][3] -= TypeTraits<ValueType>::getOneElement();

        k++;
    }

    A[0][0] -= TypeTraits<ValueType>::getOneElement();
    A[1][1] -= TypeTraits<ValueType>::getOneElement();
    A[2][2] -= TypeTraits<ValueType>::getOneElement();
    A[3][3] -= TypeTraits<ValueType>::getOneElement();

    A.negate();

    result.setValue(A);

    Z.setValue(A);

    i = 1;

    while(Z.normInfinity() > eps && i < maxiter)
    {
        Z.mult(A);

        i++;

        result.addScaled(Z, ValueTypeT(1.0) / ValueTypeT(i));
    }

    result.scale(ValueTypeT(-1.0) * ValueTypeT(1 << k));

    return (i < maxiter);
}

/*! \brief Sets this matrix to the logarithm of the given matrix,
    assumes det > 0
*/

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::logOf(
    const TransformationMatrix &matrix)
{
    const Int32      maxiter = 12;
          Int32      k       = 0;
          Int32      i       = 0;
    const ValueTypeT eps     = 1e-12;

    TransformationMatrix<ValueTypeT> A(matrix),Z;

    // Take repeated square roots to reduce spectral radius
    Z.setValue(A);

    Z[0][0] -= TypeTraits<ValueType>::getOneElement();
    Z[1][1] -= TypeTraits<ValueType>::getOneElement();
    Z[2][2] -= TypeTraits<ValueType>::getOneElement();
    Z[3][3] -= TypeTraits<ValueType>::getOneElement();

    while(Z.normInfinity() > 0.5)
    {
        A.sqrt();

        Z.setValue(A);

        Z[0][0] -= TypeTraits<ValueType>::getOneElement();
        Z[1][1] -= TypeTraits<ValueType>::getOneElement();
        Z[2][2] -= TypeTraits<ValueType>::getOneElement();
        Z[3][3] -= TypeTraits<ValueType>::getOneElement();

        k++;
    }

    A[0][0] -= TypeTraits<ValueType>::getOneElement();
    A[1][1] -= TypeTraits<ValueType>::getOneElement();
    A[2][2] -= TypeTraits<ValueType>::getOneElement();
    A[3][3] -= TypeTraits<ValueType>::getOneElement();

    A.negate();

    setValue(A);

    Z.setValue(A);

    i = 1;
    while(Z.normInfinity() > eps && i < maxiter)
    {
        Z.mult(A);

        i++;

        addScaled(Z, ValueTypeT(1.0) / ValueTypeT(i));
    }

    scale(ValueTypeT(-1.0) * ValueTypeT(1 << k));

    return (i<maxiter);
}

/*! \brief Computes the exponential of this matrix and stores it in
    result
*/

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::exp(TransformationMatrix &result) const
{
    const Int32                q = 6;

          TransformationMatrix A(*this);
          TransformationMatrix D;
          TransformationMatrix N;

          Int32                j = 1;
          Int32                k;

          ValueTypeT           c(1.0);

    j += Int32(osglog(A.normInfinity() / 0.693));

    if(j < 0) 
        j = 0;

    A.scale(ValueTypeT(1.0f / (1 << j)));

    result.setIdentity();

    for(k = 1; k <= q; k++)
    {
        c *= ValueTypeT(q - k + 1) / ValueTypeT(k * (2 * q - k + 1));

        result.multLeft(A);

        N.addScaled(result, c);

        if(k % 2) 
        {
            D.addScaled(result, -c);
        }
        else
        {
            D.addScaled(result,  c);
        }
    }

    result.invertFrom(D);
    result.mult      (N);

    for(k = 0; k < j; k++)
        result.mult(result);

    // ToDo: return value
    return true;
}

/** \brief Sets this matrix to the exponential of the given matrix
*/

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::expOf(
    const TransformationMatrix &matrix)
{
    const Int32                q = 6;

          TransformationMatrix A(matrix);
          TransformationMatrix D;
          TransformationMatrix N;

          Int32                j = 1;
          Int32                k;

          ValueTypeT           c(1.0);

    j += int(osglog(A.normInfinity() / 0.693));

    if(j < 0) 
        j = 0;

    A.scale(1.0 / (ValueTypeT(1 << j)));

    setIdentity();

    for(k = 1; k <= q; k++)
    {
        c *= ValueTypeT(q - k + 1) / ValueTypeT(k * (2 *q - k + 1));

        multLeft(A);

        N.addScaled(*this,c);

        if(k % 2) 
        {
            D.addScaled(*this, -c);
        }
        else 
        {
            D.addScaled(*this,  c);
        }
    }

    invertFrom(D);
    mult      (N);

    for(k = 0; k < j; k++)
        mult(*this);

    // ToDo: return value
    return true;
}

/*-------------------------------------------------------------------------*/
/*                          Element Access                                 */

template<class ValueTypeT> inline
typename TransformationMatrix<ValueTypeT>::VectorType &
    TransformationMatrix<ValueTypeT>::operator [](UInt32 uiIndex)
{
    return _matrix[uiIndex];
}

template<class ValueTypeT> inline
const typename TransformationMatrix<ValueTypeT>::VectorType &
    TransformationMatrix<ValueTypeT>::operator [](UInt32 uiIndex) const
{
    return _matrix[uiIndex];
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

template<class ValueTypeT> inline
TransformationMatrix<ValueTypeT> &
    TransformationMatrix<ValueTypeT>::operator = (
        const TransformationMatrix &source)
{
    UInt32 i;

    if (this == &source)
        return *this;

    for(i = 0; i < 4; i++)
        _matrix[i] = source._matrix[i];

    return *this;
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

/*! \brief equal, returns true if all matrix elements are equal with
    the tolerance of Eps
 */

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::operator == (
    const TransformationMatrix &other) const
{
    return equals(other, Eps);
}

/*! \brief not equal, returns true if all matrix elements are not equal with
    the tolerance of Eps
 */

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::operator != (
    const TransformationMatrix &other) const
{
    return ! (*this == other);
}

/*-------------------------------------------------------------------------*/
/*                               Helper                                    */

template<class ValueTypeT> inline
ValueTypeT TransformationMatrix<ValueTypeT>::rowMulCol4(
    const TransformationMatrix &gRowMat, UInt32 iRow,
    const TransformationMatrix &gColMat, UInt32 iColumn) const
{
    return
        gRowMat[0][iRow] * gColMat[iColumn][0] +
        gRowMat[1][iRow] * gColMat[iColumn][1] +
        gRowMat[2][iRow] * gColMat[iColumn][2] +
        gRowMat[3][iRow] * gColMat[iColumn][3];
}


template<class ValueTypeT> inline
ValueTypeT TransformationMatrix<ValueTypeT>::det2(
    const ValueTypeT a1, const ValueTypeT a2,
    const ValueTypeT b1, const ValueTypeT b2) const
{
    return (a1 * b2) - (a2 * b1);
}

template<class ValueTypeT> inline
ValueTypeT TransformationMatrix<ValueTypeT>::det3(
    const ValueTypeT a1,
    const ValueTypeT a2,
    const ValueTypeT a3,
    const ValueTypeT b1,
    const ValueTypeT b2,
    const ValueTypeT b3,
    const ValueTypeT c1,
    const ValueTypeT c2,
    const ValueTypeT c3) const
{
    return
        (a1 * b2 * c3) + (a2 * b3 * c1) + (a3 * b1 * c2) -
        (a1 * b3 * c2) - (a2 * b1 * c3) - (a3 * b2 * c1);
}

/*! Returns the 1-norm of the upper left 3x3 part of this matrix.
    The 1-norm is also known as maximum absolute column sum norm.
    
    \return 1-norm of \a matrix.
 */
template <class ValueTypeT>
inline typename TransformationMatrix<ValueTypeT>::ValueType
    TransformationMatrix<ValueTypeT>::norm1_3x3(void) const
{
    ValueType max;
    ValueType t;
    
    max = osgabs(_matrix[0][0]) + 
          osgabs(_matrix[0][1]) +
          osgabs(_matrix[0][2]);
    
    if((t = osgabs(_matrix[1][0]) +
            osgabs(_matrix[1][1]) +
            osgabs(_matrix[1][2])  ) > max)
    {
        max = t;
    }
    
    if((t = osgabs(_matrix[2][0]) +
            osgabs(_matrix[2][1]) +
            osgabs(_matrix[2][2])  ) > max)
    {
        max = t;
    }
    
    return max;
}

/*! Returns the infinity-norm of the upper left 3x3 part of this matrix.
    The infinity-norm is also known as maximum absolute row sum norm.
    
    \return infinity-norm of \a matrix.
 */
template <class ValueTypeT>
inline typename TransformationMatrix<ValueTypeT>::ValueType
    TransformationMatrix<ValueTypeT>::normInf_3x3(void) const
{
    ValueType max;
    ValueType t;
    
    max = osgabs(_matrix[0][0]) +
          osgabs(_matrix[1][0]) +
          osgabs(_matrix[2][0]);
    
    if((t = osgabs(_matrix[0][1]) +
            osgabs(_matrix[1][1]) +
            osgabs(_matrix[2][1])  ) > max)
    {
        max = t;
    }
    
    if((t = osgabs(_matrix[0][2]) +
            osgabs(_matrix[1][2]) +
            osgabs(_matrix[2][2])  ) > max)
    {
        max = t;
    }
    
    return max;
}

/*! Computes the transpose of the adjoint of the upper left 3x3 part of
    this matrix and stores it in \a result.
    This is used in polarDecomposition.
    
    \param[out] Transpose of adjoint.
 */
template <class ValueTypeT>
inline void
    TransformationMatrix<ValueTypeT>::adjointT_3x3(
        TransformationMatrix<ValueTypeT> &result) const
{
    result[0][0] = _matrix[1][1] * _matrix[2][2] - _matrix[2][1] * _matrix[1][2];
    result[1][0] = _matrix[2][1] * _matrix[0][2] - _matrix[0][1] * _matrix[2][2];
    result[2][0] = _matrix[0][1] * _matrix[1][2] - _matrix[1][1] * _matrix[0][2];
    
    result[0][1] = _matrix[1][2] * _matrix[2][0] - _matrix[2][2] * _matrix[1][0];
    result[1][1] = _matrix[2][2] * _matrix[0][0] - _matrix[0][2] * _matrix[2][0];
    result[2][1] = _matrix[0][2] * _matrix[1][0] - _matrix[1][2] * _matrix[0][0];
    
    result[0][2] = _matrix[1][0] * _matrix[2][1] - _matrix[2][0] * _matrix[1][1];
    result[1][2] = _matrix[2][0] * _matrix[0][1] - _matrix[0][0] * _matrix[2][1];
    result[2][2] = _matrix[0][0] * _matrix[1][1] - _matrix[1][0] * _matrix[0][1];
}

/*! Computes the decomposition M = QS of a non-singular, affine matrix \a M 
    (\c this) into an orthogonal matrix \a Q (basically a rotation, but may
    also reflect) and a symmetric positive semi-definite matrix \a S (basically
    a non-uniform scaling in \em some orthonormal basis).
    The sign of the determinant of Q can be used to distinguish the case where
    \a Q contains a reflection (det(Q) < 0).
        
    \param[out] Q Rotation and reflection component.
    \param[out] S Scaling component.
    \param[out] det Determinant of Q. 
    
    Code taken from Graphics Gems IV article III.4 "Polar Matrix Decomposition".
 */
template <class ValueTypeT>
inline void
    TransformationMatrix<ValueTypeT>::polarDecompose(
        TransformationMatrix &Q,
        TransformationMatrix &S,
        ValueType            &det) const
{
    ValueType const TOL = 1.0e-6;

    TransformationMatrix const &M = *this;
    TransformationMatrix        Mk;
    TransformationMatrix        Ek;
    TransformationMatrix        MkAdjT;
    
    Mk.transposeFrom(M);
    
    ValueType Mk_one = Mk.norm1_3x3  ();
    ValueType Mk_inf = Mk.normInf_3x3();
    
    ValueType MkAdjT_one;
    ValueType MkAdjT_inf;
    
    ValueType Ek_one;
    ValueType Mk_det;
       
    do
    {
        // compute transpose of adjoint
        Mk.adjointT_3x3(MkAdjT);
        
        // Mk_det = det(Mk) -- computed from the adjoint        
        Mk_det = Mk[0][0] * MkAdjT[0][0] + 
                 Mk[1][0] * MkAdjT[1][0] +
                 Mk[2][0] * MkAdjT[2][0];
        
        // should this be a close to zero test ?
        if(Mk_det == TypeTraits<ValueType>::getZeroElement())
        {
            FWARNING(("polarDecompose: Mk_det == 0.0\n"));
            break;
        }
        
        MkAdjT_one = MkAdjT.norm1_3x3  ();
        MkAdjT_inf = MkAdjT.normInf_3x3();
        
        // compute update factors
        ValueType gamma =
            osgsqrt(
                osgsqrt((MkAdjT_one * MkAdjT_inf) / (Mk_one * Mk_inf)) /
                osgabs(Mk_det));
        
        ValueType g1 = 0.5 * gamma;
        ValueType g2 = 0.5 / (gamma * Mk_det);
           
        Ek = Mk;
        Mk.scale    (g1          ); // this does:
        Mk.addScaled(MkAdjT, g2  ); // Mk = g1 * Mk + g2 * MkAdjT
        Ek.addScaled(Mk,     -1.0); // Ek -= Mk;
        
        Ek_one = Ek.norm1_3x3  ();
        Mk_one = Mk.norm1_3x3  ();
        Mk_inf = Mk.normInf_3x3();
        
    } while(Ek_one > (Mk_one * TOL));
    
    Q = Mk;
    Q.transpose();
    
    S = Mk;
    S.mult(M);
    
    for(UInt32 i = 0; i < 3; ++i)
    {
        for(UInt32 j = i; j < 3; ++j)
        {
            S[j][i] = S[i][j] = 0.5 * (S[j][i] + S[i][j]);
        }
    }
    
    det = Mk_det;
}

/*! Computes a spectral decomposition of a symmetric positive
    semi-definite matrix \a S (\c this) into a rotation matrix \a SO and
    a vector of scaling values \a k.
    The decomposition satisfies S = SO K SO^t, where K is the diagonal matrix
    of scaling factors.    
    
    \param[out] SO Scale orientation rotation matrix.
    \param[out] k Scaling factors.
    
    Code taken from Graphics Gems IV article III.4 "Polar Matrix Decomposition".
 */
template <class ValueTypeT>
inline void
    TransformationMatrix<ValueTypeT>::spectralDecompose(
        TransformationMatrix &SO,
        VectorType3f         &k  ) const
{
    UInt32 const next[3]       = {1, 2, 0};
    UInt32 const maxIterations = 20;
    
    TransformationMatrix const &S = *this;
    
    ValueType diag[3];
    ValueType offDiag[3];
    
    diag[0] = S[0][0];
    diag[1] = S[1][1];
    diag[2] = S[2][2];
    
    offDiag[0] = S[2][1];
    offDiag[1] = S[0][2];
    offDiag[2] = S[1][0];
    
    for(UInt32 iter = 0; iter < maxIterations; ++iter)
    {
        ValueType sm = osgabs(offDiag[0]) + osgabs(offDiag[1]) + osgabs(offDiag[2]);
        
        if(sm == TypeTraits<ValueType>::getZeroElement())
        {        
            break;
        }
        
        for(Int32 i = 2; i >= 0; --i)
        {
            UInt32 p = next[i];
            UInt32 q = next[p];
            
            ValueType absOffDiag = osgabs(offDiag[i]);
            ValueType g          = 100.0 * absOffDiag; 
            
            if(absOffDiag > 0.0)
            {
                ValueType t;
                ValueType h    = diag[q] - diag[p];
                ValueType absh = osgabs(h);
                
                if(absh + g == absh)
                {
                    t = offDiag[i] / h;
                }
                else
                {
                    ValueType theta = 0.5 * h / offDiag[i];
                    t = 1.0 / (osgabs(theta) + osgsqrt(theta * theta + 1.0));
                    
                    t = theta < 0.0 ? -t : t;
                }
            
                ValueType c = 1.0 / osgsqrt(t * t + 1.0);
                ValueType s = t * c;
                
                ValueType tau = s / (c + 1.0);
                ValueType ta  = t * offDiag[i];
                
                offDiag[i] = 0.0;
                
                diag[p] -= ta;
                diag[q] += ta;
                
                ValueType offDiagq = offDiag[q];
                
                offDiag[q] -= s * (offDiag[p] + tau * offDiag[q]);
                offDiag[p] += s * (offDiagq   - tau * offDiag[p]);
                
                for(Int32 j = 2; j >= 0; --j)
                {
                    ValueType a = SO[p][j];
                    ValueType b = SO[q][j];
                    
                    SO[p][j] -= s * (b + tau * a);
                    SO[q][j] += s * (a - tau * b);
                }
            }
        }
    }
    
    k[0] = diag[0];
    k[1] = diag[1];
    k[2] = diag[2];
}

/*! Computes the decomposition of the 4x4 affine matrix \a M (\c this) as
    M = T F R SO S SO^t, where T is a translation matrix, F is +/- I
    (a reflection), R is a rotation matrix, SO is a rotation matrix and S
    is a (nonuniform) scale matrix.
    The results of the decomposition are not returned as matrices but as more
    appropriate types.
    
    Code taken from Graphics Gems IV article III.4 "Polar Matrix Decomposition".
    Note: The "spectral axis adjustment" part, i.e. the "snuggle" function,
          is not implemented here.
 */
template <class ValueTypeT>
inline void
    TransformationMatrix<ValueTypeT>::decompose(
        VectorType3f   &t,
        ValueType      &f,
        QuaternionType &r,
        QuaternionType &so,
        VectorType3f   &s  ) const
{
    TransformationMatrix A = *this;
    TransformationMatrix Q;
    TransformationMatrix S;
    TransformationMatrix SO;
    ValueType            det;

    t[0] = A[3][0];
    t[1] = A[3][1];
    t[2] = A[3][2];
    
    A[3][0] = 0.0;
    A[3][1] = 0.0;
    A[3][2] = 0.0;
    
    A[0][3] = 0.0;
    A[1][3] = 0.0;
    A[2][3] = 0.0;
    
    A.polarDecompose(Q, S, det);
    
    if(det < 0.0)
    {
        Q.negate();
        f = - 1.0;
    }
    else
    {
        f = 1.0;
    }
    
    r.setValue(Q);
    
    S.spectralDecompose(SO, s);
    
    so.setValue(SO);
}

#ifdef __sgi
#pragma set woff 1424
#endif

template<class ValueTypeT> inline
bool TransformationMatrix<ValueTypeT>::jacobi(
    ValueTypeT    evalues [JacobiRank],
    VectorType3f  evectors[JacobiRank],
    Int32        &rots)
{
    Real64  sm;         
    Real64  theta;      
    Real64  c, s, t;    
    Real64  tau;        
    Real64  h, g;       
    Real64  thresh;     
    Real64  b[JacobiRank]; 
    Real64  z[JacobiRank]; 
    UInt32  p, q, i, j;
    Real64  a[JacobiRank][JacobiRank];
    
    // initializations
    for (i = 0; i < JacobiRank; i++) 
    {
        b[i] = evalues[i] = _matrix[i][i];
        z[i] = 0.0;

        for (j = 0; j < JacobiRank; j++) 
        {
            evectors[i][j] = (i == j) ? 1.0f : 0.0f;
            a[i][j] = _matrix[i][j];
        }
    }
    
    rots = 0;

    for(i = 0; i < 50; i++) 
    {
        sm = 0.0;
        
        for(p = 0; p < JacobiRank - 1; p++)
        {
            for(q = p+1; q < JacobiRank; q++)
            {
                sm += osgabs(a[p][q]);
            }
        }

        if (sm == 0.0)
            return false;
        
        thresh = (i < 3 ?
                  (.2 * sm / (JacobiRank * JacobiRank)) :
                  0.0);
        
        for (p = 0; p < JacobiRank - 1; p++) 
        {
            for (q = p + 1; q < JacobiRank; q++) 
            {
                g = 100.0 * osgabs(a[p][q]);
                
                if (i > 3                                          && 
                    (osgabs(evalues[p]) + g == osgabs(evalues[p])) &&
                    (osgabs(evalues[q]) + g == osgabs(evalues[q])))
                {
                    a[p][q] = 0.0;
                }
                else if (osgabs(a[p][q]) > thresh) 
                {
                    h = evalues[q] - evalues[p];
                    
                    if (osgabs(h) + g == osgabs(h))
                    {
                        t = a[p][q] / h;
                    }
                    else 
                    {
                        theta = .5 * h / a[p][q];
                        t = 1.0 / (osgabs(theta) + osgsqrt(1 + theta * theta));
                        if (theta < 0.0)  t = -t;
                    }
                    // End of computing tangent of rotation angle
                    
                    c = 1.0 / osgsqrt(1.0 + t * t);
                    s = t * c;

                    tau = s / (1.0 + c);
                    h   = t * a[p][q];

                    z[p]    -= h;
                    z[q]    += h;

                    evalues[p] -= ValueTypeT(h);
                    evalues[q] += ValueTypeT(h);

                    a[p][q] = 0.0;
                    
                    for (j = 0; j < p; j++) 
                    {
                        g = a[j][p];
                        h = a[j][q];

                        a[j][p] = g - s * (h + g * tau);
                        a[j][q] = h + s * (g - h * tau);
                    }
                    
                    for (j = p+1; j < q; j++) 
                    {
                        g = a[p][j];
                        h = a[j][q];

                        a[p][j] = g - s * (h + g * tau);
                        a[j][q] = h + s * (g - h * tau);
                    }
                    
                    for (j = q+1; j < JacobiRank; j++) 
                    {
                        g = a[p][j];
                        h = a[q][j];

                        a[p][j] = g - s * (h + g * tau);
                        a[q][j] = h + s * (g - h * tau);
                    }
                    
                    for (j = 0; j < JacobiRank; j++) 
                    {
                        g = evectors[j][p];
                        h = evectors[j][q];

                        evectors[j][p] = ValueTypeT(g - s * (h + g * tau));
                        evectors[j][q] = ValueTypeT(h + s * (g - h * tau));
                    }
                }
                rots++;
            }
        }
        for (p = 0; p < JacobiRank; p++) 
        {
            evalues[p] = ValueTypeT(b[p] += z[p]);

            z[p] = 0;
        }
    }

    return true;
}

#ifdef __sgi
#pragma reset woff 1424
#endif

/*-------------------------------------------------------------------------*/
/*                               Functions                                 */

//! write matrix to stream

template<class ValueTypeT> inline
std::ostream &operator <<(      std::ostream                     &os,
                          const TransformationMatrix<ValueTypeT> &obj)
{
    UInt32 i;
    UInt32 j;

    std::ios::fmtflags oldflags = os.flags(std::ios::showpoint | 
                                           std::ios::fixed);

    Int32 pr    = os.precision(3  );
    Char8 fill  = os.fill     (' ');
    Int32 width = os.width    (8  );

    for(j = 0; j < 4; j++)
    {
        for(i = 0; i < 4; i++)
        {
            os << std::setw(8) << obj[i][j] << " ";
        }

        os << "\n";
    }

    os.flags    (oldflags);
    os.precision(pr      );
    os.fill     (fill    );
    os.width    (width   );

    return os;
}

OSG_END_NAMESPACE

#define OSGMATRIX_INLINE_CVSID "@(#)$Id: $"
