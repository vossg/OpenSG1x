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

#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

OSG_BEGIN_NAMESPACE

/** \typedef OSGVectorInterface <OSGValueTypeT,                   \
                                 OSGVecStorage3<OSGValueTypeT> >  \
     OSGQuaternionBase::OSGVectorType
  * \brief Quaternion vector type
  */

/** \typedef OSGTransformationMatrix<OSGValueTypeT>               \
     OSGQuaternionBase::OSGMatrixType;
  * \brief Quaternion matrix type
  */


/** \fn const char *OSGQuaternionBase::getClassname(void)
 *  \brief Classname
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

template <class OSGValueTypeT>
char OSGQuaternionBase<OSGValueTypeT>::cvsid[] = "@(#)$Id: $";

/** \brief Identity quaternion
 */

template <class OSGValueTypeT>
OSGQuaternionBase<OSGValueTypeT> OSGQuaternionBase<OSGValueTypeT>::_identity;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/


/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/** \brief Returns identity quaternion
 */

template <class OSGValueTypeT> inline
const OSGQuaternionBase<OSGValueTypeT> &
    OSGQuaternionBase<OSGValueTypeT>::identity(void)
{
    return _identity;
}

/** \brief Returns the slerp betweet rot0 and rot1 at t
 */

template <class OSGValueTypeT> inline
OSGQuaternionBase<OSGValueTypeT> 
    OSGQuaternionBase<OSGValueTypeT>::slerp(const OSGQuaternionBase &rot0,
                                            const OSGQuaternionBase &rot1, 
                                            const OSGValueTypeT      t)
{
    OSGQuaternionBase returnValue;

    slerp(rot0, rot1, returnValue, t);

	return returnValue;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/** \brief The actual internal slerp code
 */

template <class OSGValueTypeT> inline
void OSGQuaternionBase<OSGValueTypeT>::slerp(const OSGQuaternionBase &rot0,
                                             const OSGQuaternionBase &rot1, 
                                                   OSGQuaternionBase &result,
                                             const OSGValueTypeT      t)
{
	OSGValueTypeT rot1q[4];

	OSGReal64     omega;
    OSGReal64     cosom;
    OSGReal64     sinom;
	OSGReal64     scalerot0;
    OSGReal64     scalerot1;

	OSGUInt32 i;
    OSGUInt32 j;

	// Calculate the cosine
	cosom = 
        rot0._quat[0] * rot1._quat[0] + 
        rot0._quat[1] * rot1._quat[1] +
		rot0._quat[2] * rot1._quat[2] + 
        rot0._quat[3] * rot1._quat[3];
	
	// adjust signs if necessary
	if(cosom < 0.0) 
    {
		cosom = -cosom;

		for(j = 0; j < 4; j++)
        {
			rot1q[j] = -rot1[j];
        }
	} 
    else
    {
		for(j = 0; j < 4; j++)
        {
			rot1q[j] = rot1[j];
        }
	}

	// calculate interpolating coeffs
	if ((1.0 - cosom) > 0.00001) 
    {
		// standard case
		omega = osgacos(cosom);
		sinom = osgsin(omega);
		scalerot0 = osgsin((1.0 - t) * omega) / sinom;
		scalerot1 = osgsin(t * omega) / sinom;
	}
    else 
    {
		// rot0 and rot1 very close - just do linear interp.
		scalerot0 = 1.0 - t;
		scalerot1 = t;
	}
	
	// build the new quarternion
	for (i = 0; i < 4; i++)
		result[i] = (OSGValueTypeT) (scalerot0 * rot0._quat[i] + 
                                     scalerot1 * rot1q[i]);
}

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

template <class OSGValueTypeT> inline
OSGQuaternionBase<OSGValueTypeT>::OSGQuaternionBase(void)
{
    _quat[0] =
        _quat[1] =
        _quat[2] = OSGTypeConstants<OSGValueTypeT>::getZeroElement();

    _quat[3] = OSGTypeConstants<OSGValueTypeT>::getOneElement();
}

/** \brief Copy Constructor
 */

template <class OSGValueTypeT> inline
OSGQuaternionBase<OSGValueTypeT>::OSGQuaternionBase(
    const OSGQuaternionBase &source)
{
    OSGUInt32 i;

    for(i = 0; i < 4; i++)
    {
        _quat[i] = source._quat[i];
    }
}

/** \brief Construtor from axis and angle in degrees
 */

template <class OSGValueTypeT> inline
OSGQuaternionBase<OSGValueTypeT>::OSGQuaternionBase(OSGValueTypeT x, 
                                                    OSGValueTypeT y, 
                                                    OSGValueTypeT z,
                                                    OSGValueTypeT w)
{
    setValueAsAxis(x, y, z, w);
}

/** \brief Constructor from matrix
 */

template <class OSGValueTypeT> inline
OSGQuaternionBase<OSGValueTypeT>::OSGQuaternionBase(
    const OSGMatrixType &matrix)
{
    setValue(matrix);
}

/** \brief Constructor from 3D rotation axis vector and angle in degrees
 */

template <class OSGValueTypeT> inline
OSGQuaternionBase<OSGValueTypeT>::OSGQuaternionBase(
    const OSGVectorType &axis, 
    const OSGValueTypeT  angle)
{
    setValue(axis, angle);
}

/** \brief Constructor defined by the from and to vector
 */

template <class OSGValueTypeT> inline
OSGQuaternionBase<OSGValueTypeT>::OSGQuaternionBase(
    const OSGVectorType &rotateFrom, 
    const OSGVectorType &rotateTo)
{
    setValue(rotateFrom, rotateTo);
}


/** \brief Destructor
 */

template <class OSGValueTypeT> inline
OSGQuaternionBase<OSGValueTypeT>::~OSGQuaternionBase(void)
{
}

//@}

/*---------------------------- set functions --------------------------------*/

/** @name set functions */
//@{

/** \brief Resets the quaternion to be the identity (0., 0., 0., 1.)
 */

template <class OSGValueTypeT> inline
void OSGQuaternionBase<OSGValueTypeT>::setIdentity(void)
{
    _quat[0] =
        _quat[1] =
        _quat[2] = OSGTypeConstants<OSGValueTypeT>::getZeroElement();

    _quat[3] = OSGTypeConstants<OSGValueTypeT>::getOneElement();
}

/** \brief Sets value of rotation from array interpreted as axis and angle
 *  given in degrees
 */

template <class OSGValueTypeT> inline
void OSGQuaternionBase<OSGValueTypeT>::setValueAsAxis(
    const OSGValueTypeT *valsP)
{
    setValueAsAxis(valsP[0], valsP[1], valsP[2], valsP[3]);
}

/** \brief Sets value of rotation from array of 4 components of a quaternion
 */

template <class OSGValueTypeT> inline
void OSGQuaternionBase<OSGValueTypeT>::setValueAsQuat(
    const OSGValueTypeT *valsP)
{
    OSGUInt32 i;

    for(i = 0; i < 4; i++)
    {
        _quat[i] = valsP[i];
    }
}

/** \brief Sets value of rotation from 4 individual components interpreted as
 *  axis and angle in degrees
 */

template <class OSGValueTypeT> inline
void OSGQuaternionBase<OSGValueTypeT>::setValueAsAxis(const OSGValueTypeT x, 
                                                      const OSGValueTypeT y, 
                                                      const OSGValueTypeT z, 
                                                      const OSGValueTypeT w)
{
    OSGValueTypeT rTmp = osgsqrt(x * x + y * y + z * z);

    if(rTmp > osgEps)
    {
        rTmp = osgsin(osgdegree2rad(w) / 2.0f) / rTmp;

        _quat[0] = x * rTmp;
        _quat[1] = y * rTmp;
        _quat[2] = z * rTmp;
        _quat[3] = osgcos(osgdegree2rad(w) / 2.0f);
    }
    else
    {
        setIdentity();
    }
}

/** \brief Sets value of rotation from 4 individual components interpreted as
 *  a quaternion
 */

template <class OSGValueTypeT> inline
void OSGQuaternionBase<OSGValueTypeT>::setValueAsQuat(const OSGValueTypeT x, 
                                                      const OSGValueTypeT y, 
                                                      const OSGValueTypeT z, 
                                                      const OSGValueTypeT w)
{
    _quat[0] = x;
    _quat[1] = y;
    _quat[2] = z;
    _quat[3] = w;
}

/** \brief Sets value of rotation from a rotation matrix
 */

template <class OSGValueTypeT> inline
void OSGQuaternionBase<OSGValueTypeT>::setValue(const OSGMatrixType &matrix)
{
    OSGReal64 tr;
    OSGReal64 s;
    OSGReal64 qt[3];

    OSGUInt32 i;
    OSGUInt32 j;
    OSGUInt32 k;

    OSGUInt32 nxt[3] = { 1, 2, 0};
     
    tr = matrix[0][0] + matrix[1][1] + matrix[2][2];

    if(tr > 0.0)
    {
        s = osgsqrt(tr + 1.0);

        _quat[3] = s * 0.5;

        s = 0.5 / s;
        _quat[0] = (matrix[1][2] - matrix[2][1]) * s;
        _quat[1] = (matrix[2][0] - matrix[0][2]) * s;
        _quat[2] = (matrix[0][1] - matrix[1][0]) * s;
    }
    else
    {
        if(matrix[1][1] > matrix[0][0])
            i = 1;
        else
            i = 0;

        if(matrix[2][2] > matrix[i][i])
            i = 2;

        j = nxt[i];  
        k = nxt[j];

        s = osgsqrt(matrix[i][i] - (matrix[j][j] + matrix[k][k]) + 1.0 );

        qt[i] = s * 0.5;
        s     = 0.5 / s;

        _quat[3] = (matrix[j][k] - matrix[k][j]) * s;

        qt[j] = (matrix[i][j] + matrix[j][i]) * s;
        qt[k] = (matrix[i][k] + matrix[k][i]) * s;

        _quat[0] = qt[0];
        _quat[1] = qt[1];
        _quat[2] = qt[2];
    }
    
    if(_quat[3] > 1.0 || _quat[3] < -1.0)
    {
        if(_quat[3] > 1.0 + osgEps || _quat[3] < -1.0 - osgEps)
        {
            fprintf(stderr,
                    "\nMatToQuat: BUG: |quat[4]| (%lf) >> 1.0 !\n\n",
                    _quat[3]);
        }

        if(_quat[3] > 1.0)
        {
            _quat[3] = 1.0;
        }
        else
        {
            _quat[3] = -1.0;
        }
    }
}

/** \brief Sets value of quaternion from 3D rotation axis vector and angle in 
 *  degrees
 */

template <class OSGValueTypeT> inline
void OSGQuaternionBase<OSGValueTypeT>::setValue(const OSGVectorType &axis, 
                                                      OSGValueTypeT  angle)
{
    OSGValueTypeT rTmp = axis.length();

    if(rTmp > osgEps)
    {
        rTmp = osgsin(osgdegree2rad(angle) / 2.0f) / rTmp;

        _quat[0] = axis[0] * rTmp;
        _quat[1] = axis[1] * rTmp;
        _quat[2] = axis[2] * rTmp;
        _quat[3] = osgcos(osgdegree2rad(angle) / 2.0f);
    }
    else
    {
        setIdentity();
    }
}

/** \brief Sets rotation to rotate one direction vector to another
 */

template <class OSGValueTypeT> inline
void OSGQuaternionBase<OSGValueTypeT>::setValue(
    const OSGVectorType &rotateFrom, 
    const OSGVectorType &rotateTo)
{
	OSGVectorType from = rotateFrom;
	OSGVectorType to   = rotateTo;
	OSGVectorType axis;
	OSGValueTypeT cost;

	from.normalize();
	to.normalize();

	cost = from.dot(to);

	// check for degeneracies
	if(cost > 0.99999) 
    {	// vectors are parallel
        setIdentity();
		return;
	}
	else if(cost < -0.99999) 
    {		
        // vectors are opposite
		// find an axis to rotate around, which should be
		// perpendicular to the original axis
		// Try cross product with (1,0,0) first, if that's one of our
		// original vectors then try  (0,1,0).
		
        OSGVectorType cAxis(1.0, 0.0, 0.0);

        OSGVectorType tmp = from.cross(cAxis);

		if(tmp.length() < 0.00001)
        {
            cAxis.setValues(0.0, 1.0, 0.0);

			tmp = from.cross(cAxis);
		}

		tmp.normalize();

		setValueAsAxis(tmp[0], tmp[1], tmp[2], osgrad2degree(osgPi));

		return;
	}

	axis = rotateFrom.cross(rotateTo);
	axis.normalize();

	// use half-angle formulae
	// sin^2 t = ( 1 - cos (2t) ) / 2

	axis *= osgsqrt(0.5 * (1.0 - cost));

	// scale the axis by the sine of half the rotation angle to get
	// the normalized quaternion

	_quat[0] = axis[0];
	_quat[1] = axis[1];
	_quat[2] = axis[2];

	// cos^2 t = ( 1 + cos (2t) ) / 2
	// w part is cosine of half the rotation angle

	_quat[3] = osgsqrt(0.5 * (1.0 + cost));
}

/** \brief Sets rotation by a given str (like "0.0 1.0 0.0 3.14"), be aware
    that these values are interpreted as axis, angle in degrees    
 */

template <class OSGValueTypeT> inline
void OSGQuaternionBase<OSGValueTypeT>::setValue(const char *str)
{
	OSGUInt32 i;
    OSGUInt32 numOfToken = 4;

	char *c = const_cast<char*>(str);

	char *tokenC = 0;
	char  token[256];

	OSGValueTypeT vec[4];

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
                if (tokenC) 
                {
                    *tokenC = 0;
                    vec[i++] = 
                        OSGTypeConstants<OSGValueTypeT>::getFromString(token);
    
                }
                
                while (i < numOfToken) 
                    vec[i++] = 
                        OSGTypeConstants<OSGValueTypeT>::getZeroElement();

                break;
            case ' ':
            case '\t':
                if (tokenC) 
                {
                    *tokenC = 0;
                    vec[i++] = 
                        OSGTypeConstants<OSGValueTypeT>::getFromString(token);
                    tokenC = 0;
                }
                break;
            default:
                if (!tokenC) 
                {
                    tokenC = token;
                }
                *tokenC++ = *c;
                break;
        }
    }
    
    setValueAsAxis(vec[0], vec[1], vec[2], vec[3]);
}

/** \brief Sets rotation by three given euler angles
 */

template <class OSGValueTypeT> inline
void OSGQuaternionBase<OSGValueTypeT>::setValue(const OSGValueTypeT alpha, 
                                                const OSGValueTypeT beta,
                                                const OSGValueTypeT gamma)
{
    OSGValueTypeT sx = osgsin(alpha * 0.5);
    OSGValueTypeT cx = osgcos(alpha * 0.5);

    OSGValueTypeT sy = osgsin(beta  * 0.5);
    OSGValueTypeT cy = osgcos(beta  * 0.5);

    OSGValueTypeT sz = osgsin(gamma * 0.5);
    OSGValueTypeT cz = osgcos(gamma * 0.5);

	_quat[0] = (sx * cy * cz) - (cx * sy * sz);
	_quat[1] = (cx * sy * cz) + (sx * cy * sz);
	_quat[2] = (cx * cy * sz) - (sx * sy * cz);
	_quat[3] = (cx * cy * cz) + (sx * sy * sz);
}

//@}

/*--------------------------- get functions ---------------------------------*/

/** @name get functions */
//@{

/** \brief  Returns pointer to array of 4 components defining quaternion
 */

template <class OSGValueTypeT> inline
const OSGValueTypeT *OSGQuaternionBase<OSGValueTypeT>::getValues(void) const
{
    return _quat;
}

/** \brief Returns 4 individual components of rotation quaternion as axis and
 *  angle in degrees
 */

template <class OSGValueTypeT> inline
void OSGQuaternionBase<OSGValueTypeT>::getValueAsAxis(OSGValueTypeT &x, 
                                                      OSGValueTypeT &y, 
                                                      OSGValueTypeT &z,
                                                      OSGValueTypeT &w) const
{
	OSGValueTypeT len;

	OSGVectorType q(_quat[0], _quat[1], _quat[2]);
	 
    len = q.length();

	if(len > osgEps) 
    {
		q *= (OSGTypeConstants<OSGValueTypeT>::getOneElement() / len);

        x = q[0];
        y = q[1];
        z = q[2];

		w = osgrad2degree(2.0 * osgacos(_quat[3]));
	}
	else 
    {
        x = OSGTypeConstants<OSGValueTypeT>::getZeroElement();
        y = OSGTypeConstants<OSGValueTypeT>::getZeroElement();
        z = OSGTypeConstants<OSGValueTypeT>::getOneElement();

        w = OSGTypeConstants<OSGValueTypeT>::getZeroElement();
	}          
}

/** \brief Returns 4 individual components of rotation quaternion
 */

template <class OSGValueTypeT> inline
void OSGQuaternionBase<OSGValueTypeT>::getValueAsQuat(OSGValueTypeT &x, 
                                                      OSGValueTypeT &y, 
                                                      OSGValueTypeT &z,
                                                      OSGValueTypeT &w) const
{
    x = _quat[0];
    y = _quat[1];
    z = _quat[2];
    w = _quat[3];
}

/// Returns corresponding 3D rotation axis vector and angle in degrees
template <class OSGValueTypeT> inline
void OSGQuaternionBase<OSGValueTypeT>::getValue(OSGVectorType &axis, 
                                                OSGValueTypeT &radians) const
{
	OSGValueTypeT len;

	OSGVectorType q(_quat[0], _quat[1], _quat[2]);
	 
    len = q.length();

	if(len > osgEps) 
    {
		axis  = q * (OSGTypeConstants<OSGValueTypeT>::getOneElement() / len);

		radians = osgrad2degree(2.0 * osgacos(_quat[3]));
	}
	else 
    {
		axis.setValues(OSGTypeConstants<OSGValueTypeT>::getZeroElement(), 
                       OSGTypeConstants<OSGValueTypeT>::getZeroElement(),
                       OSGTypeConstants<OSGValueTypeT>::getOneElement());
		radians = OSGTypeConstants<OSGValueTypeT>::getZeroElement();
	}          
}

/// Returns corresponding 4x4 rotation matrix
template <class OSGValueTypeT> inline
void OSGQuaternionBase<OSGValueTypeT>::getValue(OSGMatrixType &matrix) const
{
    matrix[0][0] = 1.0f - 2.0f * (_quat[Q_Y] * _quat[Q_Y] + 
                                  _quat[Q_Z] * _quat[Q_Z]);
    matrix[0][1] =        2.0f * (_quat[Q_X] * _quat[Q_Y] + 
                                  _quat[Q_Z] * _quat[Q_W]);
    matrix[0][2] =         2.0f * (_quat[Q_Z] * _quat[Q_X] - 
                                   _quat[Q_Y] * _quat[Q_W]);
    matrix[0][3] = 0.0f;

    matrix[1][0] =        2.0f * (_quat[Q_X] * _quat[Q_Y] - 
                                  _quat[Q_Z] * _quat[Q_W]);
    matrix[1][1] = 1.0f - 2.0f * (_quat[Q_Z] * _quat[Q_Z] + 
                                  _quat[Q_X] * _quat[Q_X]);
    matrix[1][2] =         2.0f * (_quat[Q_Y] * _quat[Q_Z] + 
                                   _quat[Q_X] * _quat[Q_W]);
    matrix[1][3] = 0.0f;


    matrix[2][0] =        2.0f * (_quat[Q_Z] * _quat[Q_X] + 
                                 _quat[Q_Y] * _quat[Q_W]);
    matrix[2][1] =        2.0f * (_quat[Q_Y] * _quat[Q_Z] - 
                                  _quat[Q_X] * _quat[Q_W]);
    matrix[2][2] =  1.0f - 2.0f * (_quat[Q_Y] * _quat[Q_Y] + 
                                   _quat[Q_X] * _quat[Q_X]);
    matrix[2][3] = 0.0f;

    matrix[3][0] = 0.0f;
    matrix[3][1] = 0.0f;
    matrix[3][2] = 0.0f;
    matrix[3][3] = 1.0f;
}

/** \brief Return the first component of the store quaternion
 */

template <class OSGValueTypeT> inline
OSGValueTypeT OSGQuaternionBase<OSGValueTypeT>::x(void) const
{
    return _quat[0];
}

/** \brief Return the seond component of the store quaternion
 */

template <class OSGValueTypeT> inline
OSGValueTypeT OSGQuaternionBase<OSGValueTypeT>::y(void) const
{
    return _quat[1];
}

/** \brief Return the third component of the store quaternion
 */

template <class OSGValueTypeT> inline
OSGValueTypeT OSGQuaternionBase<OSGValueTypeT>::z(void) const
{
    return _quat[2];
}

/** \brief Return the fourth component of the store quaternion
 */

template <class OSGValueTypeT> inline
OSGValueTypeT OSGQuaternionBase<OSGValueTypeT>::w(void) const
{
    return _quat[3];
}

//@}

/*----------------------------- simple math --------------------------------*/

/** @name simple math */
//@{

/** \brief Returns the 4 dimensional euclidian length of the quaternion
 */

template <class OSGValueTypeT> inline
OSGValueTypeT OSGQuaternionBase<OSGValueTypeT>::length(void)
{
    return osgsqrt(_quat[0] * _quat[0] +
                   _quat[1] * _quat[1] +
                   _quat[2] * _quat[2] +
                   _quat[3] * _quat[3]);
}

/** \brief Norm the quaternion to be of unit length
 */

template <class OSGValueTypeT> inline
void OSGQuaternionBase<OSGValueTypeT>::normalize(void)
{
    OSGUInt32     i;

    OSGValueTypeT rLength = length();

    if(osgabs(rLength) < osgEps)
        rLength =  OSGTypeConstants<OSGValueTypeT>::getOneElement();
    else
        rLength =  OSGTypeConstants<OSGValueTypeT>::getOneElement() / rLength;

    for(i = 0; i < 4; i++)
    {
        _quat[i] *= rLength;
    }
}

/** \brief Changes a rotation to be its inverse
 */

template <class OSGValueTypeT> inline
void OSGQuaternionBase<OSGValueTypeT>::invert(void)
{
    _quat[0] = -_quat[0];
	_quat[1] = -_quat[1];
	_quat[2] = -_quat[2];
	_quat[3] =  _quat[3];
}

/** \brief Returns the inverse of a rotation
 */

template <class OSGValueTypeT> inline
const OSGQuaternionBase<OSGValueTypeT> 
    OSGQuaternionBase<OSGValueTypeT>::inverse(void) const
{
    OSGQuaternionBase returnValue(*this);

    returnValue.invert();

    return returnValue;
}

/** \brief Puts the given vector through this rotation
*/
// this one should be optimized a little bit too (GV)
template <class OSGValueTypeT> inline
void OSGQuaternionBase<OSGValueTypeT>::multVec(const OSGVectorType &src, 
                                                     OSGVectorType &dst) const
{
	OSGMatrix mat;
	getValue(mat);
	mat.transform(src, dst);
}

/** \brief Puts the given vector through this rotation
 */

template <class OSGValueTypeT> inline
void OSGQuaternionBase<OSGValueTypeT>::transform(
    const OSGVectorType &src, 
          OSGVectorType &dst) const
{
    multVec(src, dst);
}

/** \brief Keep the axis the same. Multiply the angle of rotation by 
 *   the amount 'scaleFactor'
 */

template <class OSGValueTypeT> inline
void OSGQuaternionBase<OSGValueTypeT>::scaleAngle(OSGValueTypeT scaleFactor)
{
	OSGVectorType axis;
	OSGValueTypeT radians;

	getValue(axis, radians);
	setValue(axis, radians * scaleFactor);
}

template <class OSGValueTypeT> inline
void OSGQuaternionBase<OSGValueTypeT>::slerpThis(
    const OSGQuaternionBase &rot0,
    const OSGQuaternionBase &rot1, 
    const OSGValueTypeT      t)
{
    slerp(rot0, rot1, *this, t);
}

template <class OSGValueTypeT> inline
void OSGQuaternionBase<OSGValueTypeT>::mult(const OSGQuaternionBase &other)
{
    mult(_quat, other._quat);
}

template <class OSGValueTypeT> inline
void OSGQuaternionBase<OSGValueTypeT>::multLeft(
    const OSGQuaternionBase &other)
{
    mult(other._quat, _quat);
}

template <class OSGValueTypeT> inline
OSGBool OSGQuaternionBase<OSGValueTypeT>::equals(
    const OSGQuaternionBase &rot, 
    const OSGValueTypeT tolerance) const
{
    OSGUInt32 i; 
    OSGBool   returnValue = true;

    for(i = 0; i < 4; i++)
    {
        returnValue &= ( (_quat[i]     - rot._quat[i] <= tolerance) && 
                         (rot._quat[i] - _quat[i]     <= tolerance));
    }

    return returnValue;
}

//@}

/*------------------------------ element access -----------------------------*/

/** @name element access */
//@{

/** \brief Return a reference to the element at index index
 */

template <class OSGValueTypeT> inline
OSGValueTypeT &OSGQuaternionBase<OSGValueTypeT>::operator [](
    const OSGUInt32 index)
{
    return _quat[index];
}

/** \brief Return a const reference to the element at index index
 */

template <class OSGValueTypeT> inline
const OSGValueTypeT &OSGQuaternionBase<OSGValueTypeT>::operator [](
    const OSGUInt32 index) const
{
    return _quat[index];
}

//@}

/*---------------------------- math operators -------------------------------*/

/** @name math operators */
//@{

/** \brief Multiplies by another rotation; results in product of rotations
 */

template <class OSGValueTypeT> inline
void OSGQuaternionBase<OSGValueTypeT>::operator *=(
    const OSGQuaternionBase &other)
{
    mult(_quat, other._quat);
}

//@}

/*-------------------------- assignment -----------------------------------*/

/** @name assignment */
//@{

/** \brief assignment
 */

template <class OSGValueTypeT> inline
const OSGQuaternionBase<OSGValueTypeT> &
    OSGQuaternionBase<OSGValueTypeT>::operator =(
        const OSGQuaternionBase &source)
{
    OSGUInt32 i;

	if (this == &source)
		return *this;

    for(i = 0; i < 4; i++)
    {
        _quat[i] = source._quat[i];
    }

    return *this;
}

//@}

/*-------------------------- comparison -----------------------------------*/

/** @name comparison */
//@{

/** \brief less than, compares memory adresses
 */

template <class OSGValueTypeT> inline
bool OSGQuaternionBase<OSGValueTypeT>::operator <(
    const OSGQuaternionBase &other)
{
    return this < &other;
}

/** \brief equal
 */

template <class OSGValueTypeT> inline
OSGBool OSGQuaternionBase<OSGValueTypeT>::operator ==(
    const OSGQuaternionBase &other)
{
    return equals(other, osgEps);
}

/** \brief unequal
 */

template <class OSGValueTypeT> inline
OSGBool OSGQuaternionBase<OSGValueTypeT>::operator != (
    const OSGQuaternionBase &other)
{
	return ! (*this == other);
}

//@}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/** \brief \internal Take the give buffers as quaternions and write the
 *  result to the current.
 */

template <class OSGValueTypeT> inline
void OSGQuaternionBase<OSGValueTypeT>::mult(const OSGValueTypeT rVal1[4],
                                            const OSGValueTypeT rVal2[4])
{
    OSGValueTypeT s1, s2, s3, s4, s5, s6, s7, s8, s9, t;
    
    s1 = (rVal1[2] - rVal1[1]) * (rVal2[1] - rVal2[2]);
    s2 = (rVal1[3] + rVal1[0]) * (rVal2[3] + rVal2[0]);
    s3 = (rVal1[3] - rVal1[0]) * (rVal2[1] + rVal2[2]);
    s4 = (rVal1[2] + rVal1[1]) * (rVal2[3] - rVal2[0]);
    s5 = (rVal1[2] - rVal1[0]) * (rVal2[0] - rVal2[1]);
    s6 = (rVal1[2] + rVal1[0]) * (rVal2[0] + rVal2[1]);
    s7 = (rVal1[3] + rVal1[1]) * (rVal2[3] - rVal2[2]);
    s8 = (rVal1[3] - rVal1[1]) * (rVal2[3] + rVal2[2]);

    s9 = s6 + s7 + s8;
    t  = ( s5 + s9 ) / 2.0f;
    
    _quat[3] = s1 + t - s6;
    _quat[0] = s2 + t - s9;
    _quat[1] = s3 + t - s8;
    _quat[2] = s4 + t - s7;

    normalize();
}


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

template <class OSGValueTypeT> inline
ostream &operator <<(ostream &os, const OSGQuaternionBase<OSGValueTypeT> &obj)
{
    os << fixed << showpoint << setprecision(3) << setfill(' ');

	return os << setw(8) 
              << obj.x() << " " << obj.y() << " " 
              << obj.z() << " " << obj.w();
}

OSG_END_NAMESPACE

///---------------------------------------------------------------------------
///  FUNCTION: 
///---------------------------------------------------------------------------
//:  Example for the head comment of a function
///---------------------------------------------------------------------------
///
//p: Paramaters: 
//p: 
///
//g: GlobalVars:
//g: 
///
//r: Return:
//r: 
///
//c: Caution:
//c: 
///
//a: Assumptions:
//a: 
///
//d: Description:
//d: 
///
//s: SeeAlso:
//s: 
///---------------------------------------------------------------------------

