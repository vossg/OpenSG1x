/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
 *                                                                           *
 *          contact: {reiners|vossg}@igd.fhg.de, jbehr@zgdv.de               *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#include <iomanip>
#else
#include <iostream.h>
#include <iomanip.h>
#endif

#include <OSGLog.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/** \typedef OSGTransformationMatrix::OSGValueType
 *  \brief Value type, eg OSGReal32 
 */

/** \typedef OSGVectorInterface<OSGValueTypeT, OSGVecStorage4<OSGValueTypeT> >\
     OSGTransformationMatrix::OSGVectorType; 
 *   \brief Matrix vector type, eg OSGVec4f
 */


/** \typedef OSGQuaternionBase<OSGValueType> \
    OSGTransformationMatrix::OSGQuaternionType;
 *  \brief Matrix quaternion type
 */

/** \typedef OSGVectorInterface<OSGValueTypeT, OSGVecStorage3<OSGValueTypeT> >\
    OSGTransformationMatrix::OSGVectorType3f;
 *  \brief Matrix vec3f type
 */

/** \typedef OSGPointInterface<OSGValueTypeT, OSGVecStorage3<OSGValueTypeT> >\
    OSGTransformationMatrix::OSGPointType3f;
 *  \brief Matrix pnt3f type
 */

/** \fn const char *OSGTransformationMatrix::getClassname(void)
 *  \brief Classname
 */

/** \var OSGVectorType OSGTransformationMatrix::_matrix[4];
 *  \brief Value store
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

template<class OSGValueTypeT>
char OSGTransformationMatrix<OSGValueTypeT>::cvsid[] = "@(#)$Id: $";

/** \brief Identity matrix
 */
template<class OSGValueTypeT>
OSGTransformationMatrix<OSGValueTypeT>
    OSGTransformationMatrix<OSGValueTypeT>::_identityMatrix;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/** \brief Returns identity matrix
 */

template<class OSGValueTypeT> inline
const OSGTransformationMatrix<OSGValueTypeT> &
    OSGTransformationMatrix<OSGValueTypeT>::identity(void)
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

template<class OSGValueTypeT> inline
OSGTransformationMatrix<OSGValueTypeT>::OSGTransformationMatrix(void)
{
    OSGUInt32 i;

    for(i = 0; i < 4; i++)
    {
        _matrix[i][i] = OSGTypeConstants<OSGValueType>::getOneElement();
    }
}

/** \brief Copy Constructor
 */

template<class OSGValueTypeT> inline
OSGTransformationMatrix<OSGValueTypeT>::OSGTransformationMatrix(
    const OSGTransformationMatrix &source)
{
    OSGUInt32 i;

    for(i = 0; i < 4; i++)
    {
        _matrix[i] = source._matrix[i];
    }
}

/** \brief Construtor using 3 OSGVec3f values
 */

template<class OSGValueTypeT> inline
OSGTransformationMatrix<OSGValueTypeT>::OSGTransformationMatrix(
    const OSGVectorType3f &vector1,
    const OSGVectorType3f &vector2,
    const OSGVectorType3f &vector3)
{
    _matrix[0].setValue(vector1);
    _matrix[1].setValue(vector2);
    _matrix[2].setValue(vector3);
}

/** \brief Constructor using 4 OSGVec3f values 
 */

template<class OSGValueTypeT> inline
OSGTransformationMatrix<OSGValueTypeT>::OSGTransformationMatrix(
    const OSGVectorType3f &vector1,
    const OSGVectorType3f &vector2,
    const OSGVectorType3f &vector3,
    const OSGVectorType3f &vector4)
{
    _matrix[0].setValue(vector1);
    _matrix[1].setValue(vector2);
    _matrix[2].setValue(vector3);
    _matrix[3].setValue(vector4);
}

/** \brief Construtor using 16 OSGValueTypeT values
 */

template<class OSGValueTypeT> inline
OSGTransformationMatrix<OSGValueTypeT>::OSGTransformationMatrix(
    const OSGValueTypeT rVal00,
    const OSGValueTypeT rVal10,
    const OSGValueTypeT rVal20,
    const OSGValueTypeT rVal30,
    
    const OSGValueTypeT rVal01,
    const OSGValueTypeT rVal11,
    const OSGValueTypeT rVal21,
    const OSGValueTypeT rVal31,
    
    const OSGValueTypeT rVal02,
    const OSGValueTypeT rVal12,
    const OSGValueTypeT rVal22,
    const OSGValueTypeT rVal32,
    
    const OSGValueTypeT rVal03,
    const OSGValueTypeT rVal13,
    const OSGValueTypeT rVal23,
    const OSGValueTypeT rVal33)
{
    _matrix[0].setValues(rVal00, rVal01, rVal02, rVal03);
    _matrix[1].setValues(rVal10, rVal11, rVal12, rVal13);
    _matrix[2].setValues(rVal20, rVal21, rVal22, rVal23);
    _matrix[3].setValues(rVal30, rVal31, rVal32, rVal33);
}

/** \brief Destructor
 */

template<class OSGValueTypeT> inline
OSGTransformationMatrix<OSGValueTypeT>::~OSGTransformationMatrix(void)
{
}

//@}

/*------------------------- set functions -------------------------------*/

/** @name set functions */
//@{

/** \brief Resets the matrix to identity
 */

template<class OSGValueTypeT> inline
void OSGTransformationMatrix<OSGValueTypeT>::setIdentity(void)
{
    OSGUInt32 i;

    for(i = 0; i < 4; i++)
    {
        _matrix[i].setNull();
        _matrix[i][i] = OSGTypeConstants<OSGValueType>::getOneElement();
    }
}


/** \brief Set values from a given matrix
 */

template<class OSGValueTypeT> inline
void OSGTransformationMatrix<OSGValueTypeT>::setValue(
    const OSGTransformationMatrix &mat)
{
    for(OSGUInt32 i = 0; i < 4; i++)
    {
        _matrix[i] = mat._matrix[i];
    }
}

/** \brief Set values from 3 OSGVec3f vectors
 */

template<class OSGValueTypeT> inline
void OSGTransformationMatrix<OSGValueTypeT>::setValue(
    const OSGVectorType3f &vector1,
    const OSGVectorType3f &vector2,
    const OSGVectorType3f &vector3)
{
    _matrix[0].setValue(vector1);
    _matrix[1].setValue(vector2);
    _matrix[2].setValue(vector3);
}

/** \brief Set values from 4 OSGVec3f vectors
 */

template<class OSGValueTypeT> inline
void OSGTransformationMatrix<OSGValueTypeT>::setValue(
    const OSGVectorType3f &vector1,
    const OSGVectorType3f &vector2,
    const OSGVectorType3f &vector3,
    const OSGVectorType3f &vector4)
{
    _matrix[0].setValue(vector1);
    _matrix[1].setValue(vector2);
    _matrix[2].setValue(vector3);
    _matrix[3].setValue(vector4);
}

/** \brief Set values from 16 OSGValueTypeT values
 */

template<class OSGValueTypeT> inline
void OSGTransformationMatrix<OSGValueTypeT>::setValue(
    const OSGValueTypeT rVal00,
    const OSGValueTypeT rVal10,
    const OSGValueTypeT rVal20,
    const OSGValueTypeT rVal30,
    
    const OSGValueTypeT rVal01,
    const OSGValueTypeT rVal11,
    const OSGValueTypeT rVal21,
    const OSGValueTypeT rVal31,
    
    const OSGValueTypeT rVal02,
    const OSGValueTypeT rVal12,
    const OSGValueTypeT rVal22,
    const OSGValueTypeT rVal32,
    
    const OSGValueTypeT rVal03,
    const OSGValueTypeT rVal13,
    const OSGValueTypeT rVal23,
    const OSGValueTypeT rVal33)
{
    _matrix[0].setValues(rVal00, rVal01, rVal02, rVal03);
    _matrix[1].setValues(rVal10, rVal11, rVal12, rVal13);
    _matrix[2].setValues(rVal20, rVal21, rVal22, rVal23);
    _matrix[3].setValues(rVal30, rVal31, rVal32, rVal33);
}

/** \brief Set values from 16 OSGValueTypeT values, the matrix is transposed
 */

template<class OSGValueTypeT> inline
void OSGTransformationMatrix<OSGValueTypeT>::setValueTransposed(
    const OSGValueTypeT rVal00,
    const OSGValueTypeT rVal01,
    const OSGValueTypeT rVal02,
    const OSGValueTypeT rVal03,
    
    const OSGValueTypeT rVal10,
    const OSGValueTypeT rVal11,
    const OSGValueTypeT rVal12,
    const OSGValueTypeT rVal13,
    
    const OSGValueTypeT rVal20,
    const OSGValueTypeT rVal21,
    const OSGValueTypeT rVal22,
    const OSGValueTypeT rVal23,
    
    const OSGValueTypeT rVal30,
    const OSGValueTypeT rVal31,
    const OSGValueTypeT rVal32,
    const OSGValueTypeT rVal33)
{
    _matrix[0].setValues(rVal00, rVal01, rVal02, rVal03);
    _matrix[1].setValues(rVal10, rVal11, rVal12, rVal13);
    _matrix[2].setValues(rVal20, rVal21, rVal22, rVal23);
    _matrix[3].setValues(rVal30, rVal31, rVal32, rVal33);
}

/** \brief Set value from an OSGValueTypeT array, be shure the sizes match
 */

template<class OSGValueTypeT> inline
void OSGTransformationMatrix<OSGValueTypeT>::setValue(
    const OSGValueTypeT *pMat, OSGBool bTransposed)
{
    const OSGValueTypeT *pTmpMat = pMat;

    if(bTransposed == true)
    {
        for(OSGUInt32 i = 0; i < 4; i++)
        {
            _matrix[i].setValue(pTmpMat);
            pTmpMat += 4;
        }
    }
    else
    {
        for(OSGUInt32 i = 0; i < 4; i++)
        {
            for(OSGUInt32 j = 0; j < 4; j++)
            {
                _matrix[i][j] = pTmpMat[j * 4 + i];
            }
        }
    }
}

/** \brief Set value from an OSGVectorTypeT array, be shure the sizes match
 */

template<class OSGValueTypeT> inline
void OSGTransformationMatrix<OSGValueTypeT>::setValue(
    const OSGVectorType *pMat)
{
    for(OSGUInt32 i = 0; i < 4; i++)
    {
        _matrix[i] = pMat[i];
    }
}

#ifndef WIN32

/** \brief Set value from an OSGVectorType3f array, be shure the sizes match
 */

template<class OSGValueTypeT> inline
void OSGTransformationMatrix<OSGValueTypeT>::setValue(
    const OSGVectorType3f *pMat)
{
    for(OSGUInt32 i = 0; i < 4; i++)
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

template<class OSGValueTypeT> inline
OSGValueTypeT *OSGTransformationMatrix<OSGValueTypeT>::getValues(void)
{
    return _matrix[0].getValueRef();
}

//@}

/*------------------------- create transformation -------------------------*/

/** @name create transformation matrices */
//@{

/** \brief Sets matrix to scale by given uniform factor
 */
template<class OSGValueTypeT> inline
void OSGTransformationMatrix<OSGValueTypeT>::setScale(const OSGValueTypeT s)
{
    _matrix[0][0] = s;
    _matrix[1][1] = s;
    _matrix[2][2] = s;
}

/** \brief Sets matrix to scale by given uniform factor
 */
template<class OSGValueTypeT> inline
void OSGTransformationMatrix<OSGValueTypeT>::setScale(const OSGValueTypeT sx, 
			const OSGValueTypeT sy, const OSGValueTypeT sz)
{
    _matrix[0][0] = sx;
    _matrix[1][1] = sy;
    _matrix[2][2] = sz;
}

/** \brief Sets matrix to scale by given vector
 */
template<class OSGValueTypeT> inline
void OSGTransformationMatrix<OSGValueTypeT>::setScale(
    const OSGVectorType3f &s)
{
    _matrix[0][0] = s[0];
    _matrix[1][1] = s[1];
    _matrix[2][2] = s[2];
}

/** \brief Sets matrix to translate by given values
 */

template<class OSGValueTypeT> inline
void OSGTransformationMatrix<OSGValueTypeT>::setTranslate(
    const OSGValueTypeT tx,
    const OSGValueTypeT ty,
    const OSGValueTypeT tz)
{
    _matrix[3][0] = tx;
    _matrix[3][1] = ty;
    _matrix[3][2] = tz;
}


/** \brief Sets matrix to translate by given vector
 */
template<class OSGValueTypeT> inline
void OSGTransformationMatrix<OSGValueTypeT>::setTranslate(
    const OSGVectorType3f &t)
{
    _matrix[3].setValue(t);   
}

/** \brief Sets matrix to translate by given point
 */
template<class OSGValueTypeT> inline
void OSGTransformationMatrix<OSGValueTypeT>::setTranslate(
    const OSGPointType3f &t)
{
    _matrix[3].setValue(t);   
}

/** \brief Sets matrix to rotate by given rotation
 */
template<class OSGValueTypeT> inline
void OSGTransformationMatrix<OSGValueTypeT>::setRotate(
    const OSGQuaternionType &q)
{
    q.getValue(*this);
}


/** \brief Composes the matrix based on a translation, rotation, scale,
   orientation for scale, and center.  The "center" is the
   center point for scaling and rotation.  The "scaleOrientation"
   chooses the primary axes for the scale.
*/ 
template<class OSGValueTypeT> inline
void OSGTransformationMatrix<OSGValueTypeT>::setTransform(
    const OSGVectorType3f   &translation,
    const OSGQuaternionType &rotation,
    const OSGVectorType3f   &scaleFactor,
    const OSGQuaternionType &scaleOrientation,
    const OSGVectorType3f   &center)
{
    OSGMatrix tmpMat1;
    OSGMatrix tmpMat2;

	// Concatenate the translations t and c
	OSGVectorType3f tg(translation);
	tg += center;

	// Concatenate the rotations r and so
	OSGQuaternionType rg(rotation);
	rg *= scaleOrientation;

	// Calculate the inverse of so
	OSGQuaternionType soi(scaleOrientation);
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
template<class OSGValueTypeT> inline
void OSGTransformationMatrix<OSGValueTypeT>::setTransform(
    const OSGVectorType3f   &t, 
    const OSGQuaternionType &r,
    const OSGVectorType3f   &s)
{
//    OSGMatrix tmpMat;

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
template<class OSGValueTypeT> inline
void OSGTransformationMatrix<OSGValueTypeT>::setTransform(
    const OSGVectorType3f   &t, 
    const OSGQuaternionType &r,
    const OSGVectorType3f   &s, 
    const OSGQuaternionType &so)
{
    OSGMatrix tmpMat1;
    OSGMatrix tmpMat2;

	// Concatenate the rotations r and so
	OSGQuaternionType rg(r);
	rg.mult(so);

	// Calculate the inverse of so
	OSGQuaternionType soi(so);
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
template<class OSGValueTypeT> inline
void OSGTransformationMatrix<OSGValueTypeT>::getTransform(
    OSGVectorType3f   &translation, 
    OSGQuaternionType &rotation,
    OSGVectorType3f   &scaleFactor, 
    OSGQuaternionType &scaleOrientation,
    OSGVectorType3f   &center) const
{
    cerr << "OSGMatrix::getTransform not implemented yet\n";
}

/** \brief Decomposes the matrix into a translation, rotation  and scale
 */
template<class OSGValueTypeT> inline
void OSGTransformationMatrix<OSGValueTypeT>::getTransform(
    OSGVectorType3f   &translation, 
    OSGQuaternionType &rotation,
    OSGVectorType3f   &scaleFactor, 
    OSGQuaternionType &scaleOrientation) const
{
    cerr << "OSGMatrix::getTransform not implemented yet\n";
}

/** \brief Factors a matrix m into 5 pieces: m = r s rt u t, where rt
    means transpose of r, and r and u are rotations, s is a scale,
    and t is a translation. Any projection information is returned
    in proj.
*/
template<class OSGValueTypeT> inline
OSGBool OSGTransformationMatrix<OSGValueTypeT>::factor(
    OSGTransformationMatrix &r, 
    OSGVectorType3f         &s, 
    OSGTransformationMatrix &u,
    OSGVectorType3f         &t, 
    OSGTransformationMatrix &proj) const
{
    cerr << "OSGMatrix::getTransform not implemented yet\n";
}

//@}

/*---------------------------- transform objects ---------------------------*/

/** @name transform objects */
//@{

/** \brief Multiplies matrix by given column point, where the resulting point
 *  is given
 */

template<class OSGValueTypeT> inline
void OSGTransformationMatrix<OSGValueTypeT>::multMatrixPnt(
    const OSGPointType3f &src, 
          OSGPointType3f &dst) const
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

template<class OSGValueTypeT> inline
void OSGTransformationMatrix<OSGValueTypeT>::multMatrixPnt(
    OSGPointType3f &pnt) const
{
    multMatrixPnt(pnt, pnt);
}

/** \brief Multiplies matrix by given column point, where the resulting point
 *  is given. The full (4x4) matrix is used.
 */

template<class OSGValueTypeT> inline
void OSGTransformationMatrix<OSGValueTypeT>::multFullMatrixPnt(
    const OSGPointType3f &src, 
          OSGPointType3f &dst) const
{
	OSGValueTypeT w =	src[0] * _matrix[0][3] +
						src[1] * _matrix[1][3] +
						src[2] * _matrix[2][3] + 
								 _matrix[3][3];
	
	if ( w < osgEps && w > -osgEps )
	{
		SINFO << "multFullMatrixPnt: w < osgEps!" << endl;
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

template<class OSGValueTypeT> inline
void OSGTransformationMatrix<OSGValueTypeT>::multFullMatrixPnt(
    OSGPointType3f &pnt) const
{
    multFullMatrixPnt(pnt, pnt);
}

/** \brief Multiplies matrix by given column vector,  where the resulting 
 *  vector is given
 */

template<class OSGValueTypeT> inline
void OSGTransformationMatrix<OSGValueTypeT>::multMatrixVec(
    const OSGVectorType3f &src, 
          OSGVectorType3f &dst) const
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

template<class OSGValueTypeT> inline
void OSGTransformationMatrix<OSGValueTypeT>::multMatrixVec(
    OSGVectorType3f &vec) const
{
    multMatrixVec(vec, vec);
}

/** \brief Transforms the given point by the matrix and stores the result in
 *  dest
 */

template<class OSGValueTypeT> inline
void OSGTransformationMatrix<OSGValueTypeT>::transform(
    const OSGPointType3f &src, 
          OSGPointType3f &dest) const
{
    multMatrixPnt(src, dest);
}

/** \brief Transforms the given point by the matrix
 */

template<class OSGValueTypeT> inline
void OSGTransformationMatrix<OSGValueTypeT>::transform(
    OSGPointType3f &pnt) const
{
    multMatrixPnt(pnt, pnt);
}

/** \brief Transforms the given vector by the matrix and stores the result in
 *  dest
 */

template<class OSGValueTypeT> inline
void OSGTransformationMatrix<OSGValueTypeT>::transform(
    const OSGVectorType3f &src, 
          OSGVectorType3f &dest) const
{
    multMatrixVec(src, dest);
}

/** \brief Transforms the given vector by the matrix
 */

template<class OSGValueTypeT> inline
void OSGTransformationMatrix<OSGValueTypeT>::transform(
    OSGVectorType3f &vec) const
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

template<class OSGValueTypeT> inline
OSGBool OSGTransformationMatrix<OSGValueTypeT>::equals(
    const OSGTransformationMatrix &matrix, 
    const OSGValueType             tolerance) const
{
    OSGUInt32 i;
    OSGBool returnValue = true;

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

template<class OSGValueTypeT> inline
OSGValueTypeT OSGTransformationMatrix<OSGValueTypeT>::det3(void) const
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

template<class OSGValueTypeT> inline
OSGValueTypeT OSGTransformationMatrix<OSGValueTypeT>::det (void) const
{
    OSGValueTypeT 
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

template<class OSGValueTypeT> inline
OSGBool OSGTransformationMatrix<OSGValueTypeT>::inverse(
    OSGTransformationMatrix &result) const
{
    OSGValueTypeT rDet; 

    OSGValueTypeT
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

template<class OSGValueTypeT> inline
OSGBool OSGTransformationMatrix<OSGValueTypeT>::invert(void)
{
    OSGValueTypeT           rDet; 
    OSGTransformationMatrix result;

    OSGValueTypeT
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

template<class OSGValueTypeT> inline
OSGBool OSGTransformationMatrix<OSGValueTypeT>::invertFrom(
    const OSGTransformationMatrix &matrix)
{
    OSGValueTypeT rDet; 

    OSGValueTypeT
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

template<class OSGValueTypeT> inline
OSGBool OSGTransformationMatrix<OSGValueTypeT>::inverse3(
    OSGTransformationMatrix &result) const
{
    OSGValueTypeT rDet = det3(); 
    
    if(osgabs(rDet) < 1E-20)
    {
#ifdef OSG_PRINT_MATHERR
        fprintf(stderr, "invertFrom3: matrix singular, no inverse!\n");
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
        result[3][2] = OSGTypeConstants<OSGValueType>::getZeroElement();

    result[3][3] = OSGTypeConstants<OSGValueType>::getOneElement();
    
    return true;
}

template<class OSGValueTypeT> inline
OSGBool OSGTransformationMatrix<OSGValueTypeT>::invert3(void)
{
    OSGValueTypeT           rDet    = det3(); 
    OSGTransformationMatrix result;

    if(osgabs(rDet) < 1E-20)
    {
#ifdef OSG_PRINT_MATHERR
        fprintf(stderr, "invertFrom3: matrix singular, no inverse!\n");
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
        result[3][2] = OSGTypeConstants<OSGValueType>::getZeroElement();

    result[3][3] = OSGTypeConstants<OSGValueType>::getOneElement();

    *this = result;
    
    return true;
}

template<class OSGValueTypeT> inline
OSGBool OSGTransformationMatrix<OSGValueTypeT>::invertFrom3(
    const OSGTransformationMatrix &matrix)
{
    OSGValueTypeT rDet = det3(); 
    
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
        _matrix[3][2] = OSGTypeConstants<OSGValueType>::getZeroElement();

    _matrix[3][3] = OSGTypeConstants<OSGValueType>::getOneElement();
    
    return true;
}

template<class OSGValueTypeT> inline
OSGBool OSGTransformationMatrix<OSGValueTypeT>::transposed(
		OSGTransformationMatrix &result) const
{
	result.setValues(	(*this)[0][0], (*this)[1][0], (*this)[2][0], (*this)[3][0], 
						(*this)[0][1], (*this)[1][1], (*this)[2][1], (*this)[3][1], 
						(*this)[0][2], (*this)[1][2], (*this)[2][2], (*this)[3][2], 
						(*this)[0][3], (*this)[1][3], (*this)[2][3], (*this)[3][3] );
}

template<class OSGValueTypeT> inline
OSGBool OSGTransformationMatrix<OSGValueTypeT>::transpose(void)
{
	OSGValueTypeT tmp;
	tmp = (*this)[1][0]; (*this)[1][0] = (*this)[0][1]; (*this)[0][1] = tmp;
	tmp = (*this)[2][0]; (*this)[2][0] = (*this)[0][2]; (*this)[0][2] = tmp;
	tmp = (*this)[3][0]; (*this)[3][0] = (*this)[0][3]; (*this)[0][3] = tmp;
	tmp = (*this)[2][1]; (*this)[2][1] = (*this)[1][2]; (*this)[1][2] = tmp;
	tmp = (*this)[3][1]; (*this)[3][1] = (*this)[1][3]; (*this)[1][3] = tmp;
	tmp = (*this)[3][2]; (*this)[3][2] = (*this)[2][3]; (*this)[2][3] = tmp;
}

template<class OSGValueTypeT> inline
OSGBool OSGTransformationMatrix<OSGValueTypeT>::transposeFrom(
	const OSGTransformationMatrix &matrix)
{
	this->setValues(	result[0][0], result[1][0], result[2][0], result[3][0], 
						result[0][1], result[1][1], result[2][1], result[3][1], 
						result[0][2], result[1][2], result[2][2], result[3][2], 
						result[0][3], result[1][3], result[2][3], result[3][3] );
}

template<class OSGValueTypeT> inline
void OSGTransformationMatrix<OSGValueTypeT>::mult(
    const OSGTransformationMatrix &matrix)
{
    OSGValueTypeT rTmpMat[4][4];

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

template<class OSGValueTypeT> inline
void OSGTransformationMatrix<OSGValueTypeT>::multLeft(
    const OSGTransformationMatrix &matrix)
{
    OSGValueTypeT rTmpMat[4][4];

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

template<class OSGValueTypeT> inline
OSGTransformationMatrix<OSGValueTypeT>::OSGVectorType &
    OSGTransformationMatrix<OSGValueTypeT>::operator [](OSGUInt32 uiIndex)
{
    return _matrix[uiIndex]; 
}

/** \brief Returns a const reference to the element stored at the given index
 */

template<class OSGValueTypeT> inline
const OSGTransformationMatrix<OSGValueTypeT>::OSGVectorType &
   OSGTransformationMatrix<OSGValueTypeT>::operator [](OSGUInt32 uiIndex) const
{
    return _matrix[uiIndex]; 
}

//@}

/*-------------------------- assignment -----------------------------------*/

/** @name assignement */
//@{

/** \brief assignment
 */

template<class OSGValueTypeT> inline
OSGTransformationMatrix<OSGValueTypeT> & 
    OSGTransformationMatrix<OSGValueTypeT>::operator = (
        const OSGTransformationMatrix &source)
{
    OSGUInt32 i;

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

template<class OSGValueTypeT> inline
OSGBool OSGTransformationMatrix<OSGValueTypeT>::operator == (
    const OSGTransformationMatrix &other)
{
    return equals(other, osgEps);
}

/** \brief not equal, returns true if all matrix elements are equal with
 *  the tolerance of osgEps
 */

template<class OSGValueTypeT> inline
OSGBool OSGTransformationMatrix<OSGValueTypeT>::operator != (
    const OSGTransformationMatrix &other)
{
	return ! (*this == other);
}

//@}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

template<class OSGValueTypeT> inline
OSGValueTypeT OSGTransformationMatrix<OSGValueTypeT>::rowMulCol4(
    const OSGTransformationMatrix &gRowMat, OSGUInt32 iRow, 
    const OSGTransformationMatrix &gColMat, OSGUInt32 iColumn) const
{
	return 
        gRowMat[0][iRow] * gColMat[iColumn][0] +
		gRowMat[1][iRow] * gColMat[iColumn][1] +
		gRowMat[2][iRow] * gColMat[iColumn][2] +
		gRowMat[3][iRow] * gColMat[iColumn][3];
}


template<class OSGValueTypeT> inline
OSGValueTypeT OSGTransformationMatrix<OSGValueTypeT>::det2(
    const OSGValueTypeT a1, const OSGValueTypeT a2,
    const OSGValueTypeT b1, const OSGValueTypeT b2) const
{
    return (a1 * b2) - (a2 * b1);
}

template<class OSGValueTypeT> inline
OSGValueTypeT OSGTransformationMatrix<OSGValueTypeT>::det3(
    const OSGValueTypeT a1, 
    const OSGValueTypeT a2, 
    const OSGValueTypeT a3,
    const OSGValueTypeT b1, 
    const OSGValueTypeT b2, 
    const OSGValueTypeT b3,
    const OSGValueTypeT c1, 
    const OSGValueTypeT c2, 
    const OSGValueTypeT c3) const
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
template<class OSGValueTypeT> inline
ostream &operator <<(ostream                                        &os,
                     const   OSGTransformationMatrix<OSGValueTypeT> &obj)
{
    OSGUInt32 i;
    OSGUInt32 j;

#ifdef OSG_SGI_STL
    os << fixed << showpoint << setprecision(3) << setfill(' ');
#else
    os << setprecision(3) << setfill(' ');
#endif

    for(j = 0; j < 4; j++)
    {
        for(i = 0; i < 4; i++)
        {
            os << setw(8) << obj[i][j] << " ";
        }

        os << "\n";
	}

	return os;
}

OSG_END_NAMESPACE
