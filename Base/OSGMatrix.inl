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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------


#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <iomanip>

#include <OSGLog.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/** \typedef TransformationMatrix::ValueType
 *  \brief Value type, eg Real32 
 */

/** \typedef VectorInterface<ValueTypeT, VecStorage4<ValueTypeT> >\
     TransformationMatrix::VectorType; 
 *   \brief Matrix vector type, eg Vec4f
 */


/** \typedef QuaternionBase<ValueType> \
    TransformationMatrix::QuaternionType;
 *  \brief Matrix quaternion type
 */

/** \typedef VectorInterface<ValueTypeT, VecStorage3<ValueTypeT> >\
    TransformationMatrix::VectorType3f;
 *  \brief Matrix vec3f type
 */

/** \typedef PointInterface<ValueTypeT, VecStorage3<ValueTypeT> >\
    TransformationMatrix::PointType3f;
 *  \brief Matrix pnt3f type
 */

/** \fn const char *TransformationMatrix::getClassname(void)
 *  \brief Classname
 */

/** \var VectorType TransformationMatrix::_matrix[4];
 *  \brief Value store
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

template<class ValueTypeT>
char TransformationMatrix<ValueTypeT>::cvsid[] = "@(#)$Id: $";

/** \brief Identity matrix
 */
template<class ValueTypeT>
TransformationMatrix<ValueTypeT>
    TransformationMatrix<ValueTypeT>::_identityMatrix;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/** \brief Returns identity matrix
 */

template<class ValueTypeT> inline
const TransformationMatrix<ValueTypeT> &
    TransformationMatrix<ValueTypeT>::identity(void)
{
    return _identityMatrix;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** @name constructors & destructors */
//@{

/** \brief Constructor
 */

template<class ValueTypeT> inline
TransformationMatrix<ValueTypeT>::TransformationMatrix(void)
{
    UInt32 i;

    for(i = 0; i < 4; i++)
    {
        _matrix[i][i] = TypeConstants<ValueType>::getOneElement();
    }
}

/** \brief Copy Constructor
 */

template<class ValueTypeT> inline
TransformationMatrix<ValueTypeT>::TransformationMatrix(
    const TransformationMatrix &source)
{
    UInt32 i;

    for(i = 0; i < 4; i++)
    {
        _matrix[i] = source._matrix[i];
    }
}

/** \brief Construtor using 3 Vec3f values
 */

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

/** \brief Constructor using 4 Vec3f values 
 */

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

/** \brief Construtor using 16 ValueTypeT values
 */

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

/** \brief Destructor
 */

template<class ValueTypeT> inline
TransformationMatrix<ValueTypeT>::~TransformationMatrix(void)
{
}

//@}

/*------------------------- set functions -------------------------------*/

/** @name set functions */
//@{

/** \brief Resets the matrix to identity
 */

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setIdentity(void)
{
    UInt32 i;

    for(i = 0; i < 4; i++)
    {
        _matrix[i].setNull();
        _matrix[i][i] = TypeConstants<ValueType>::getOneElement();
    }
}


/** \brief Set values from a given matrix
 */

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setValue(
    const TransformationMatrix &mat)
{
    for(UInt32 i = 0; i < 4; i++)
    {
        _matrix[i] = mat._matrix[i];
    }
}

/** \brief Set values from 3 Vec3f vectors
 */

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setValue(
    const VectorType3f &vector1,
    const VectorType3f &vector2,
    const VectorType3f &vector3)
{
    _matrix[0].setValue(vector1);
    _matrix[1].setValue(vector2);
    _matrix[2].setValue(vector3);
}

/** \brief Set values from 4 Vec3f vectors
 */

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setValue(
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

/** \brief Set values from 16 ValueTypeT values
 */

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setValue(
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

/** \brief Set values from 16 ValueTypeT values, the matrix is transposed
 */

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

/** \brief Set value from an ValueTypeT array, be shure the sizes match
 */

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setValue(
    const ValueTypeT *pMat, Bool bTransposed)
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

/** \brief Set value from an VectorTypeT array, be shure the sizes match
 */

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setValue(
    const VectorType *pMat)
{
    for(UInt32 i = 0; i < 4; i++)
    {
        _matrix[i] = pMat[i];
    }
}

#ifndef WIN32

/** \brief Set value from an VectorType3f array, be shure the sizes match
 */

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setValue(
    const VectorType3f *pMat)
{
    for(UInt32 i = 0; i < 4; i++)
    {
        _matrix[i].setValue(pMat[i]);
    }
}

#endif

//@}

/*------------------------------ get Values -------------------------------*/

/** @name get functions */
//@{

/** Returns an C++ pointer to the value store
 */

template<class ValueTypeT> inline
ValueTypeT *TransformationMatrix<ValueTypeT>::getValues(void)
{
    return _matrix[0].getValues();
}

//@}

/*------------------------- create transformation -------------------------*/

/** @name create transformation matrices */
//@{

/** \brief Sets matrix to scale by given uniform factor
 */
template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setScale(const ValueTypeT s)
{
    _matrix[0][0] = s;
    _matrix[1][1] = s;
    _matrix[2][2] = s;
}

/** \brief Sets matrix to scale by given uniform factor
 */
template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setScale(const ValueTypeT sx, 
			const ValueTypeT sy, const ValueTypeT sz)
{
    _matrix[0][0] = sx;
    _matrix[1][1] = sy;
    _matrix[2][2] = sz;
}

/** \brief Sets matrix to scale by given vector
 */
template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setScale(
    const VectorType3f &s)
{
    _matrix[0][0] = s[0];
    _matrix[1][1] = s[1];
    _matrix[2][2] = s[2];
}

/** \brief Sets matrix to translate by given values
 */

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setTranslate(
    const ValueTypeT tx,
    const ValueTypeT ty,
    const ValueTypeT tz)
{
    _matrix[3][0] = tx;
    _matrix[3][1] = ty;
    _matrix[3][2] = tz;
}


/** \brief Sets matrix to translate by given vector
 */
template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setTranslate(
    const VectorType3f &t)
{
    _matrix[3].setValue(t);   
}

/** \brief Sets matrix to translate by given point
 */
template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setTranslate(
    const PointType3f &t)
{
    _matrix[3].setValue(t);   
}

/** \brief Sets matrix to rotate by given rotation
 */
template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setRotate(
    const QuaternionType &q)
{
    q.getValue(*this);
}


/** \brief Composes the matrix based on a translation, rotation, scale,
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

/** \brief Composes the matrix based on a translation, rotation and scale
 */
template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setTransform(
    const VectorType3f   &t, 
    const QuaternionType &r,
    const VectorType3f   &s)
{
//    Matrix tmpMat;

	// Calculate the 3x3 rotation matrix
    r.getValue(*this);

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

/** \brief Composes the matrix based on a translation, rotation, scale and
   orientation
*/
template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::setTransform(
    const VectorType3f   &t, 
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

/** \brief Decomposes the matrix into a translation, rotation, scale,
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
    VectorType3f   &center) const
{
    cerr << "Matrix::getTransform not implemented yet\n";
}

/** \brief Decomposes the matrix into a translation, rotation  and scale
 */
template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::getTransform(
    VectorType3f   &translation, 
    QuaternionType &rotation,
    VectorType3f   &scaleFactor, 
    QuaternionType &scaleOrientation) const
{
    cerr << "Matrix::getTransform not implemented yet\n";
}

/** \brief Factors a matrix m into 5 pieces: m = r s rt u t, where rt
    means transpose of r, and r and u are rotations, s is a scale,
    and t is a translation. Any projection information is returned
    in proj.
*/
template<class ValueTypeT> inline
Bool TransformationMatrix<ValueTypeT>::factor(
    TransformationMatrix &r, 
    VectorType3f         &s, 
    TransformationMatrix &u,
    VectorType3f         &t, 
    TransformationMatrix &proj) const
{
    cerr << "Matrix::getTransform not implemented yet\n";
}

//@}

/*---------------------------- transform objects ---------------------------*/

/** @name transform objects */
//@{

/** \brief Multiplies matrix by given column point, where the resulting point
 *  is given
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

/** \brief Multiplies matrix by given column point
 */

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multMatrixPnt(
    PointType3f &pnt) const
{
    multMatrixPnt(pnt, pnt);
}

/** \brief Multiplies matrix by given column point, where the resulting point
 *  is given. The full (4x4) matrix is used.
 */

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multFullMatrixPnt(
    const PointType3f &src, 
          PointType3f &dst) const
{
	ValueTypeT w =	src[0] * _matrix[0][3] +
						src[1] * _matrix[1][3] +
						src[2] * _matrix[2][3] + 
								 _matrix[3][3];
	
	if ( w < Eps && w > -Eps )
	{
		SINFO << "multFullMatrixPnt: w < Eps!" << endl;
		dst.setValues(0, 0, 0);
		return;		
	}

	w = 1./w;
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

/** \brief Multiplies matrix by given column point. The full (4x4) matrix is used.
 */

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multFullMatrixPnt(
    PointType3f &pnt) const
{
    multFullMatrixPnt(pnt, pnt);
}

/** \brief Multiplies matrix by given column vector,  where the resulting 
 *  vector is given
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

/** \brief Multiplies matrix by given column vector
 */

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::multMatrixVec(
    VectorType3f &vec) const
{
    multMatrixVec(vec, vec);
}

/** \brief Transforms the given point by the matrix and stores the result in
 *  dest
 */

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::transform(
    const PointType3f &src, 
          PointType3f &dest) const
{
    multMatrixPnt(src, dest);
}

/** \brief Transforms the given point by the matrix
 */

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::transform(
    PointType3f &pnt) const
{
    multMatrixPnt(pnt, pnt);
}

/** \brief Transforms the given vector by the matrix and stores the result in
 *  dest
 */

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::transform(
    const VectorType3f &src, 
          VectorType3f &dest) const
{
    multMatrixVec(src, dest);
}

/** \brief Transforms the given vector by the matrix
 */

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::transform(
    VectorType3f &vec) const
{
    multMatrixVec(vec, vec);
}

//@}

/*---------------------------- simple math ---------------------------------*/

/** @name simple math */
//@{

/** \brief Returns true iff all matrix elements are equal within the given
 *  tolerance
 */

template<class ValueTypeT> inline
Bool TransformationMatrix<ValueTypeT>::equals(
    const TransformationMatrix &matrix, 
    const ValueType             tolerance) const
{
    UInt32 i;
    Bool returnValue = true;

    for(i = 0; i < 4; i++)
    {
        returnValue &= _matrix[i].equals(matrix._matrix[i], tolerance);

        if(returnValue == false)
            break;
    }

    return returnValue;
}

/** \brief Returns the determinat of the upper 3x3 submatrix
 */

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

/** \brief Returns the determinat of the whole 4x4 matrix
 */

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

 	return(	  a1 * det3(b2, b3, b4, c2, c3, c4, d2, d3, d4)
			- b1 * det3(a2, a3, a4, c2, c3, c4, d2, d3, d4)
			+ c1 * det3(a2, a3, a4, b2, b3, b4, d2, d3, d4)
			- d1 * det3(a2, a3, a4, b2, b3, b4, c2, c3, c4));
    
}

// This inverse stuff should be grouped in a better way :-). It's just a
// Cut&Paste section. I will have a look at it lateron (GV)

/** \brief Stores the inverse of the matrix into result, returns true if the
 *   matrix is not singular 
 */

template<class ValueTypeT> inline
Bool TransformationMatrix<ValueTypeT>::inverse(
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

/** \brief Inverts the matrix, returns true if the
 *   matrix is not singular 
 */

template<class ValueTypeT> inline
Bool TransformationMatrix<ValueTypeT>::invert(void)
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

/** \brief Set the matrix to be the inverse of the given one, returns true if
 *   the matrix is not singular 
 */

template<class ValueTypeT> inline
Bool TransformationMatrix<ValueTypeT>::invertFrom(
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
Bool TransformationMatrix<ValueTypeT>::inverse3(
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
        result[3][2] = TypeConstants<ValueType>::getZeroElement();

    result[3][3] = TypeConstants<ValueType>::getOneElement();
    
    return true;
}

template<class ValueTypeT> inline
Bool TransformationMatrix<ValueTypeT>::invert3(void)
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
        result[3][2] = TypeConstants<ValueType>::getZeroElement();

    result[3][3] = TypeConstants<ValueType>::getOneElement();

    *this = result;
    
    return true;
}

template<class ValueTypeT> inline
Bool TransformationMatrix<ValueTypeT>::invertFrom3(
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
        _matrix[3][2] = TypeConstants<ValueType>::getZeroElement();

    _matrix[3][3] = TypeConstants<ValueType>::getOneElement();
    
    return true;
}

template<class ValueTypeT> inline
Bool TransformationMatrix<ValueTypeT>::transposed(
		TransformationMatrix &result) const
{
	result.setValues(	(*this)[0][0], (*this)[1][0], (*this)[2][0], (*this)[3][0], 
						(*this)[0][1], (*this)[1][1], (*this)[2][1], (*this)[3][1], 
						(*this)[0][2], (*this)[1][2], (*this)[2][2], (*this)[3][2], 
						(*this)[0][3], (*this)[1][3], (*this)[2][3], (*this)[3][3] );
	return true;
}

template<class ValueTypeT> inline
Bool TransformationMatrix<ValueTypeT>::transpose(void)
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
Bool TransformationMatrix<ValueTypeT>::transposeFrom(
	const TransformationMatrix &matrix)
{
	this->setValues(	result[0][0], result[1][0], result[2][0], result[3][0], 
						result[0][1], result[1][1], result[2][1], result[3][1], 
						result[0][2], result[1][2], result[2][2], result[3][2], 
						result[0][3], result[1][3], result[2][3], result[3][3] );
	return true;
}

template<class ValueTypeT> inline
void TransformationMatrix<ValueTypeT>::mult(
    const TransformationMatrix &matrix)
{
    ValueTypeT rTmpMat[4][4];

    (rTmpMat)[0][0] = rowMulCol4((*this),0,(matrix),0);
    (rTmpMat)[0][1] = rowMulCol4((*this),1,(matrix),0);
    (rTmpMat)[0][2] = rowMulCol4((*this),2,(matrix),0);
    (rTmpMat)[0][3] = rowMulCol4((*this),3,(matrix),0);
    
    (rTmpMat)[1][0] = rowMulCol4((*this),0,(matrix),1);
    (rTmpMat)[1][1] = rowMulCol4((*this),1,(matrix),1);
    (rTmpMat)[1][2] = rowMulCol4((*this),2,(matrix),1);
    (rTmpMat)[1][3] = rowMulCol4((*this),3,(matrix),1);

    (rTmpMat)[2][0] = rowMulCol4((*this),0,(matrix),2);
    (rTmpMat)[2][1] = rowMulCol4((*this),1,(matrix),2);
    (rTmpMat)[2][2] = rowMulCol4((*this),2,(matrix),2);
    (rTmpMat)[2][3] = rowMulCol4((*this),3,(matrix),2);

    (rTmpMat)[3][0] = rowMulCol4((*this),0,(matrix),3);
    (rTmpMat)[3][1] = rowMulCol4((*this),1,(matrix),3);
    (rTmpMat)[3][2] = rowMulCol4((*this),2,(matrix),3);
    (rTmpMat)[3][3] = rowMulCol4((*this),3,(matrix),3);

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

    (rTmpMat)[0][0] = rowMulCol4((matrix),0,(*this),0);
    (rTmpMat)[0][1] = rowMulCol4((matrix),1,(*this),0);
    (rTmpMat)[0][2] = rowMulCol4((matrix),2,(*this),0);
    (rTmpMat)[0][3] = rowMulCol4((matrix),3,(*this),0);
    
    (rTmpMat)[1][0] = rowMulCol4((matrix),0,(*this),1);
    (rTmpMat)[1][1] = rowMulCol4((matrix),1,(*this),1);
    (rTmpMat)[1][2] = rowMulCol4((matrix),2,(*this),1);
    (rTmpMat)[1][3] = rowMulCol4((matrix),3,(*this),1);

    (rTmpMat)[2][0] = rowMulCol4((matrix),0,(*this),2);
    (rTmpMat)[2][1] = rowMulCol4((matrix),1,(*this),2);
    (rTmpMat)[2][2] = rowMulCol4((matrix),2,(*this),2);
    (rTmpMat)[2][3] = rowMulCol4((matrix),3,(*this),2);

    (rTmpMat)[3][0] = rowMulCol4((matrix),0,(*this),3);
    (rTmpMat)[3][1] = rowMulCol4((matrix),1,(*this),3);
    (rTmpMat)[3][2] = rowMulCol4((matrix),2,(*this),3);
    (rTmpMat)[3][3] = rowMulCol4((matrix),3,(*this),3);

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


//@}

/*--------------------------- element access --------------------------------*/

/** @name element access */
//@{

/** \brief Returns a reference to the element stored at the given index
 */

template<class ValueTypeT> inline
TransformationMatrix<ValueTypeT>::VectorType &
    TransformationMatrix<ValueTypeT>::operator [](UInt32 uiIndex)
{
    return _matrix[uiIndex]; 
}

/** \brief Returns a const reference to the element stored at the given index
 */

template<class ValueTypeT> inline
const TransformationMatrix<ValueTypeT>::VectorType &
   TransformationMatrix<ValueTypeT>::operator [](UInt32 uiIndex) const
{
    return _matrix[uiIndex]; 
}

//@}

/*-------------------------- assignment -----------------------------------*/

/** @name assignement */
//@{

/** \brief assignment
 */

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

//@}

/*-------------------------- comparison -----------------------------------*/

/** @name comparison */
//@{

/** \brief equal
 */

template<class ValueTypeT> inline
Bool TransformationMatrix<ValueTypeT>::operator == (
    const TransformationMatrix &other)
{
    return equals(other, Eps);
}

/** \brief not equal, returns true if all matrix elements are equal with
 *  the tolerance of Eps
 */

template<class ValueTypeT> inline
Bool TransformationMatrix<ValueTypeT>::operator != (
    const TransformationMatrix &other)
{
	return ! (*this == other);
}

//@}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

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

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/** \brief write vector to stream
 */
template<class ValueTypeT> inline 
ostream &operator <<(ostream                                  &os,
                     const   TransformationMatrix<ValueTypeT> &obj)
{
    UInt32 i;
    UInt32 j;

	ios::fmtflags oldflags = os.flags(ios::showpoint | ios::fixed); 
	int pr = os.precision(3); 
	char fill = os.fill(' ');
	int width = os.width(8);

    for(j = 0; j < 4; j++)
    {
        for(i = 0; i < 4; i++)
        {
            os << setw(8) << obj[i][j] << " ";
        }

        os << "\n";
	}

	os.flags(oldflags); 
	os.precision(pr); 
	os.fill(fill);
	os.width(width);

	return os;
}

OSG_END_NAMESPACE
