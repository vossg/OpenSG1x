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

/*! \page vecpointmat Vector, Point and Matrix Design
 *  to be done soon, so stay tuned :-)) (GV)
 *
 * Important :
 *
 * \li vectors and points are different classes
 * \li M * v | M * p semantics
 * \li M transposed is stored
 */

#include <stdio.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class VecStorage2
 */

/*! \enum VecStorage2::VectorSizeE
    \brief To be able to use the storage size
*/

/*! \var VecStorage2::VectorSizeE VecStorage2::_iSize
    \brief Storage size.
*/

/*! \var ValueTypeT VecStorage2::_values[iSize];
    \brief Value store
*/

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class ValueTypeT> inline
VecStorage2<ValueTypeT>::VecStorage2(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

template <class ValueTypeT> inline
VecStorage2<ValueTypeT>::~VecStorage2(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Access                                    */

template <class ValueTypeT> inline
void VecStorage2<ValueTypeT>::setValues(const ValueTypeT rVal1,
                                        const ValueTypeT rVal2)
{
    _values[0] = rVal1;
    _values[1] = rVal2;
}

template <class ValueTypeT> inline
void VecStorage2<ValueTypeT>::getSeparateValues(ValueTypeT &rVal1,
                                                ValueTypeT &rVal2) const
{
    rVal1 = _values[0];
    rVal2 = _values[1];
}

template <class ValueTypeT> inline
ValueTypeT VecStorage2<ValueTypeT>::x(void) const
{
    return _values[0];
}

template <class ValueTypeT> inline
ValueTypeT VecStorage2<ValueTypeT>::y(void) const
{
    return _values[1];
}



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class VecStorage3
 */

/*! \enum VecStorage3::VectorSizeE
    \brief To be able to use the storage size
*/

/*! \var VecStorage3::VectorSizeE VecStorage3::_iSize
    \brief Storage size.
*/

/*! \var ValueTypeT VecStorage3::_values[iSize];
    \brief Value store
*/

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class ValueTypeT> inline
VecStorage3<ValueTypeT>::VecStorage3(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

template <class ValueTypeT> inline
VecStorage3<ValueTypeT>::~VecStorage3(void)
{
}

/*-------------------------------------------------------------------------*/
/*                               Access                                    */

template <class ValueTypeT> inline
void VecStorage3<ValueTypeT>::setValues(const ValueTypeT rVal1,
                                        const ValueTypeT rVal2,
                                        const ValueTypeT rVal3)
{
    _values[0] = rVal1;
    _values[1] = rVal2;
    _values[2] = rVal3;
}

template <class ValueTypeT> inline
void VecStorage3<ValueTypeT>::getSeparateValues(ValueTypeT &rVal1,
                                                ValueTypeT &rVal2,
                                                ValueTypeT &rVal3) const
{
    rVal1 = _values[0];
    rVal2 = _values[1];
    rVal3 = _values[2];
}

template <class ValueTypeT> inline
ValueTypeT VecStorage3<ValueTypeT>::x(void) const
{
    return _values[0];
}

template <class ValueTypeT> inline
ValueTypeT VecStorage3<ValueTypeT>::y(void) const
{
    return _values[1];
}

template <class ValueTypeT> inline
ValueTypeT VecStorage3<ValueTypeT>::z(void) const
{
    return _values[2];
}



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class VecStorage4
 */

/*! \enum VecStorage4::VectorSizeE
    \brief To be able to use the storage size
*/

/*! \var VecStorage4::VectorSizeE VecStorage4::_iSize
    \brief Storage size.
*/

/*! \var ValueTypeT VecStorage4::_values[iSize];
    \brief Value store
*/

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class ValueTypeT> inline
VecStorage4<ValueTypeT>::VecStorage4(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

template <class ValueTypeT> inline
VecStorage4<ValueTypeT>::~VecStorage4(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Access                                   */

template <class ValueTypeT> inline
void VecStorage4<ValueTypeT>::setValues(const ValueTypeT rVal1,
                                        const ValueTypeT rVal2,
                                        const ValueTypeT rVal3,
                                        const ValueTypeT rVal4)
{
    _values[0] = rVal1;
    _values[1] = rVal2;
    _values[2] = rVal3;
    _values[3] = rVal4;
}

template <class ValueTypeT> inline
void VecStorage4<ValueTypeT>::getSeparateValues(ValueTypeT &rVal1,
                                                ValueTypeT &rVal2,
                                                ValueTypeT &rVal3,
                                                ValueTypeT &rVal4) const
{
    rVal1 = _values[0];
    rVal2 = _values[1];
    rVal3 = _values[2];
    rVal4 = _values[3];
}

template <class ValueTypeT> inline
ValueTypeT VecStorage4<ValueTypeT>::x(void) const
{
    return _values[0];
}

template <class ValueTypeT> inline
ValueTypeT VecStorage4<ValueTypeT>::y(void) const
{
    return _values[1];
}

template <class ValueTypeT> inline
ValueTypeT VecStorage4<ValueTypeT>::z(void) const
{
    return _values[2];
}

template <class ValueTypeT> inline
ValueTypeT VecStorage4<ValueTypeT>::w(void) const
{
    return _values[3];
}



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class PointInterface
 */

/*! \typedef PointInterface::RealReturnType
    \brief Used type if the returnvalue must be a real value.
*/

/*! \typedef PointInterface::ValueType
    \brief Value type
*/

/*! \typedef PointInterface::Inherited
    \brief Parent type
*/

template <class ValueTypeT,
          class StorageInterfaceT>
const PointInterface<ValueTypeT, StorageInterfaceT>
    PointInterface<ValueTypeT, StorageInterfaceT>::Null;

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class ValueTypeT,
          class StorageInterfaceT> inline
PointInterface<ValueTypeT, StorageInterfaceT>::PointInterface(void) : 
    Inherited()
{
    UInt32 i;

    for(i = 0; i < _iSize; i++)
    {
        _values[i] = TypeConstants<ValueTypeT>::getZeroElement();
    }
}

/*! \brief Constructor which takes a const value array.
  
    Be shure the array size at least as large as the vector size.
*/

template <class ValueTypeT,
          class StorageInterfaceT> inline
PointInterface<ValueTypeT, 
               StorageInterfaceT>::PointInterface(const ValueTypeT *pVals) : 
    Inherited()
{
    UInt32 i;

    if(pVals == NULL)
    {
        for(i = 0; i < _iSize; i++)
        {
            _values[i] = TypeConstants<ValueTypeT>::getZeroElement();
        }
    }
    else
    {
        for(i = 0; i < _iSize; i++)
        {
            _values[i] = pVals[i];
        }
    }
}

/*! \brief Constructor which takes a value array.
  
    Be shure the array size at least as large as the vector size.
*/

template <class ValueTypeT,
          class StorageInterfaceT> inline
PointInterface<ValueTypeT, 
               StorageInterfaceT>::PointInterface(ValueTypeT *pVals) : 
    Inherited()
{
    UInt32 i;

    if(pVals == NULL)
    {
        for(i = 0; i < _iSize; i++)
        {
            _values[i] = TypeConstants<ValueTypeT>::getZeroElement();
        }
    }
    else
    {
        for(i = 0; i < _iSize; i++)
        {
            _values[i] = pVals[i];
        }
    }
}

template <class ValueTypeT,
          class StorageInterfaceT> inline
PointInterface<ValueTypeT, StorageInterfaceT>::PointInterface(
    const PointInterface &source) : 

    Inherited()
{
    UInt32 i;

    for(i = 0; i < _iSize; i++)
    {
        _values[i] = source._values[i];
    }
}

/*
template <class    ValueTypeT,
          class    StorageInterfaceT> inline
PointInterface<ValueTypeT, StorageInterfaceT>::PointInterface(
    const ValueTypeT rVal1)
{
    UInt32 i;

    _values[0] = rVal1;

    for(i = 1; i < _iSize; i++)
    {
        _values[i] = TypeConstants<ValueTypeT>::getZeroElement();
    }
}
*/

#ifdef __sgi
#pragma set woff 1209
#endif

//! Constructor which takes two values, remaining entries will be zero

template <class ValueTypeT,
          class StorageInterfaceT> inline
PointInterface<ValueTypeT, 
               StorageInterfaceT>::PointInterface(const ValueTypeT rVal1,
                                                  const ValueTypeT rVal2) : 
    Inherited()
{
    UInt32 i;

    _values[0] = rVal1;

    if(_iSize == 2)
    {
        _values[1] = rVal2;
    }
    else if(_iSize >= 3)
    {
        _values[1] = rVal2;

        for(i = 2; i < _iSize; i++)
        {
            _values[i] = TypeConstants<ValueTypeT>::getZeroElement();
        }
    }
}

#ifdef __sgi
#pragma reset woff 1209

#pragma set woff 1209
#endif

//! Constructor which takes three values, remaining entries will be zero

template <class ValueTypeT,
          class StorageInterfaceT> inline
PointInterface<ValueTypeT, 
               StorageInterfaceT>::PointInterface(const ValueTypeT rVal1,
                                                  const ValueTypeT rVal2,
                                                  const ValueTypeT rVal3) : 
    Inherited()
{
    UInt32 i;

    _values[0] = rVal1;

    if(_iSize == 2)
    {
        _values[1] = rVal2;
    }
    else if(_iSize == 3)
    {
        _values[1] = rVal2;
        _values[2] = rVal3;
    }
    else if(_iSize >= 4)
    {
        _values[1] = rVal2;
        _values[2] = rVal3;

        for(i = 3; i < _iSize; i++)
        {
            _values[i] = TypeConstants<ValueTypeT>::getZeroElement();
        }
    }
}

#ifdef __sgi
#pragma reset woff 1209

#pragma set woff 1209
#endif

//! Constructor which takes four values, remaining entries will be zero

template <class ValueTypeT,
          class StorageInterfaceT> inline
PointInterface<ValueTypeT, 
               StorageInterfaceT>::PointInterface(const ValueTypeT rVal1,
                                                  const ValueTypeT rVal2,
                                                  const ValueTypeT rVal3,
                                                  const ValueTypeT rVal4) : 
    Inherited()
{
    UInt32 i;

    _values[0] = rVal1;

    if(_iSize == 2)
    {
        _values[1] = rVal2;
    }
    else if(_iSize == 3)
    {
        _values[1] = rVal2;
        _values[2] = rVal3;
    }
    else if(_iSize == 4)
    {
        _values[1] = rVal2;
        _values[2] = rVal3;
        _values[3] = rVal4;
    }
    else if(_iSize >= 5)
    {
        _values[1] = rVal2;
        _values[2] = rVal3;
        _values[3] = rVal4;

        for(i = 4; i < _iSize; i++)
        {
            _values[i] = TypeConstants<ValueTypeT>::getZeroElement();
        }
    }
}

#ifdef __sgi
#pragma reset woff 1209
#endif

/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

template <class ValueTypeT,
          class StorageInterfaceT> inline
PointInterface<ValueTypeT, StorageInterfaceT>::~PointInterface(void)
{
}

/*-------------------------------------------------------------------------*/
/*                                Set                                      */

template <class ValueTypeT,
          class StorageInterfaceT> inline
void PointInterface<ValueTypeT, StorageInterfaceT>::setNull(void)
{
    UInt32 i;

    for(i = 0; i < _iSize; i++)
    {
        _values[i] = TypeConstants<ValueTypeT>::getZeroElement();
    }
}

/*
template <class    ValueTypeT,
          class    StorageInterfaceT> inline
void PointInterface<ValueTypeT, StorageInterfaceT>::setValue(
    const ValueTypeT &rVal1)
{
    _values[0] = rVal1;
}
*/

template <class ValueTypeT,
          class StorageInterfaceT> inline
void PointInterface<ValueTypeT, 
                    StorageInterfaceT>::setValue(const PointInterface &vec)
{
    UInt32 i;

    for(i = 0; i < _iSize; i++)
    {
        _values[i] = vec._values[i];
    }
}


//! Set value from a given array, be sure to match sizes

template <class ValueTypeT,
          class StorageInterfaceT> inline
void PointInterface<ValueTypeT, 
                    StorageInterfaceT>::setValue(const ValueTypeT *pVals)
{
    UInt32 i;

    for(i = 0; i < _iSize; i++)
    {
        _values[i] = pVals[i];
    }
}

/*! \brief Extract values from given string, where both (const and not const)
    must be present, otherwise \b the \b compiler \b strikes \b back :-) (GV)
*/

template <class ValueTypeT,
          class StorageInterfaceT> inline
void PointInterface<ValueTypeT, 
                    StorageInterfaceT>::setValue(const Char8 *szString)
{
    UInt32 i;
    UInt32 numOfToken = _iSize;

    Char8 *c      = const_cast<Char8 *>(szString);
    Char8 *tokenC = 0;

    Char8  token[256];

    if(szString == NULL || (*szString) == '\0')
    {
        for(i = 0; i < _iSize; i++)
            _values[i] = TypeConstants<ValueTypeT>::getZeroElement();

        return;
    }

    for (i = 0; i < numOfToken; c++)
    {
        switch (*c)
        {
            case '\0':
                if(tokenC)
                {
                    *tokenC = 0;
                    _values[i++] =
                        TypeConstants<ValueTypeT>::getFromString(token);
                }

                while (i < numOfToken)
                {
                    _values[i++] =
                        TypeConstants<ValueTypeT>::getZeroElement();
                }
                break;

            case ' ':
            case '\t':
                if(tokenC)
                {
                    *tokenC = 0;
                    _values[i++] =
                        TypeConstants<ValueTypeT>::getFromString(token);
                    tokenC = 0;
                }
                break;
            default:
                if(!tokenC)
                {
                    tokenC = token;
                }
                *tokenC++ = *c;
                break;
        }
    }
}

/*! \brief Extract values from given string, where both (const and not const)
    must be present, otherwise \b the \b compiler \b strikes \b back :-) (GV)
 */

template <class ValueTypeT,
          class StorageInterfaceT> inline
void PointInterface<ValueTypeT, 
                    StorageInterfaceT>::setValue(Char8 *szString)
{
    setValue(static_cast<const Char8 *>(szString));
}

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

//! Get a pointer to the value storage

template <class ValueTypeT,
          class StorageInterfaceT> inline
ValueTypeT *PointInterface<ValueTypeT,
                           StorageInterfaceT>::getValues(void)
{
    return _values;
}

//! Get a const pointer to the value storage

template <class ValueTypeT,
          class StorageInterfaceT> inline
const ValueTypeT *PointInterface<ValueTypeT,
                                 StorageInterfaceT>::getValues(void) const
{
    return _values;
}

/*-------------------------------------------------------------------------*/
/*                        Common Math                                      */

//! Returns true iff the norm of each value is less than Eps

template <class ValueTypeT,
          class StorageInterfaceT> inline
Bool PointInterface<ValueTypeT, 
                    StorageInterfaceT>::isZero(void) const
{
    UInt32 i;
    Bool   returnValue = true;

    for(i = 0; i < _iSize; i++)
    {
        returnValue &= ((_values[i] <=  Eps) &&
                        (_values[i] >= -Eps));
    }

    return returnValue;
}

//! Negates each value of the point in place

template <class ValueTypeT,
          class StorageInterfaceT> inline
void PointInterface<ValueTypeT, StorageInterfaceT>::negate(void)
{
    UInt32 i;

    for(i = 0; i < _iSize; i++)
    {
        _values[i] = -_values[i];
    }
}

//! Returns true iff the two points are eual within a given tolerance

template <class ValueTypeT,
          class StorageInterfaceT> inline
Bool PointInterface<ValueTypeT, StorageInterfaceT>::equals(
    const PointInterface &vec,
    const ValueTypeT       tolerance) const
{
    UInt32 i;
    Bool   returnValue = true;

    for(i = 0; i < _iSize; i++)
    {
        returnValue &= ( (    _values[i] - vec._values[i] <= tolerance) &&
                         (vec._values[i] -     _values[i] <= tolerance));
    }

    return returnValue;
}

//! Returns the corrosponding vector by subtracting zero

template <class ValueTypeT,
          class StorageInterfaceT> inline
PointInterface<ValueTypeT, 
               StorageInterfaceT>::VecInterface &
    PointInterface<ValueTypeT, 
                   StorageInterfaceT>::subZero(void)
{
    return *(static_cast<VecInterface *>(this));
}

//! Returns the corrosponding vector by subtracting zero

template <class ValueTypeT,
          class StorageInterfaceT> inline
const PointInterface<ValueTypeT, 
                     StorageInterfaceT>::VecInterface &
    PointInterface<ValueTypeT, 
                   StorageInterfaceT>::subZero(void) const
{
    return *(static_cast<const VecInterface *>(this));
}

/*-------------------------------------------------------------------------*/
/*                                Math                                     */

//! Component wise scalar multiplication

template <class ValueTypeT,
          class StorageInterfaceT> inline
void PointInterface<ValueTypeT, 
                    StorageInterfaceT>::operator *=(const ValueTypeT  val)
{
    UInt32 i;

    for(i = 0; i < _iSize; i++)
    {
        _values[i] *= val;
    }
}

//! Component wise scalar division

template <class ValueTypeT,
          class StorageInterfaceT> inline
void PointInterface<ValueTypeT, 
                    StorageInterfaceT>::operator /=(const ValueTypeT  val)
{
    UInt32 i;

    for(i = 0; i < _iSize; i++)
    {
        _values[i] /= val;
    }
}

//! Point substraction, returns a new vector

template <class ValueTypeT,
          class StorageInterfaceT> inline
PointInterface<ValueTypeT, StorageInterfaceT>::VecInterface
    PointInterface<ValueTypeT, StorageInterfaceT>::operator -(
        const PointInterface &vec) const
{
    UInt32 i;

    VecInterface returnValue(*this);

    for(i = 0; i < _iSize; i++)
    {
        returnValue[i] -= vec[i];
    }

    return returnValue;
}

//! Component wise binary vector addition operator

template <class ValueTypeT,
          class StorageInterfaceT> inline
PointInterface<ValueTypeT, StorageInterfaceT>
    PointInterface<ValueTypeT, StorageInterfaceT>::operator + (
        const VecInterface &vec) const
{
    PointInterface<ValueTypeT, StorageInterfaceT> returnValue;

    UInt32 i;

    for(i = 0; i < StorageInterfaceT::_iSize; i++)
    {
        returnValue[i] = _values[i] + vec[i];
    }

    return returnValue;
}

//! Component wise binary vector addition operator

template <class ValueTypeT,
          class StorageInterfaceT> inline
PointInterface<ValueTypeT, StorageInterfaceT>
    PointInterface<ValueTypeT, StorageInterfaceT>::operator - (
        const VecInterface &vec) const
{
    PointInterface<ValueTypeT, StorageInterfaceT> returnValue;

    UInt32 i;

    for(i = 0; i < StorageInterfaceT::_iSize; i++)
    {
        returnValue[i] = _values[i] - vec[i];
    }

    return returnValue;
}

//! Component wise binary scalar multiplication

template <class ValueTypeT,
          class StorageInterfaceT> inline
PointInterface <ValueTypeT, StorageInterfaceT>
    PointInterface<ValueTypeT, StorageInterfaceT>::operator * (
        const ValueTypeT rVal) const
{
    PointInterface<ValueTypeT, StorageInterfaceT> returnValue;

    UInt32 i;

    for(i = 0; i < StorageInterfaceT::_iSize; i++)
    {
        returnValue[i] = _values[i] * rVal;
    }

    return returnValue;
}

//! Nondestructive unary negation, returns new point

template <class ValueTypeT,
          class StorageInterfaceT> inline
PointInterface<ValueTypeT, StorageInterfaceT>
    PointInterface<ValueTypeT, StorageInterfaceT>::operator -(void)
{
    UInt32 i;

    PointInterface<ValueTypeT, StorageInterfaceT> returnValue;

    for(i = 0; i < _iSize; i++)
    {
        returnValue._values[i] = - _values[i];
    }

    return returnValue;
}

/*-------------------------------------------------------------------------*/
/*                          Element Access                                 */

template <class ValueTypeT,
          class StorageInterfaceT> inline
ValueTypeT &PointInterface<ValueTypeT, 
                           StorageInterfaceT>::operator[](const UInt32 uiVal)
{
    return _values[uiVal];
}

template <class ValueTypeT,
          class StorageInterfaceT> inline
const ValueTypeT &
    PointInterface<ValueTypeT, 
                   StorageInterfaceT>::operator[](const UInt32 uiVal) const
{
    return _values[uiVal];
}

#if 0
template <class    ValueTypeT,
          class    StorageInterfaceT> inline
PointInterface<ValueTypeT, StorageInterfaceT>::operator
    ValueTypeT *(void)
{
    return _values;
}

template <class    ValueTypeT,
          class    StorageInterfaceT> inline
PointInterface<ValueTypeT, StorageInterfaceT>::operator
    const ValueTypeT *(void)
{
    return _values;
}
#endif

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

template <class ValueTypeT,
          class StorageInterfaceT> inline
PointInterface<ValueTypeT, StorageInterfaceT> &
    PointInterface<ValueTypeT, StorageInterfaceT>::operator =(
        const PointInterface &source)
{
    UInt32 i;

    if(this == &source)
        return *this;

    for(i = 0; i < _iSize; i++)
    {
        _values[i] = source._values[i];
    }

    return *this;
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

template <class ValueTypeT,
          class StorageInterfaceT> inline
Bool PointInterface<ValueTypeT, StorageInterfaceT>::operator < (
    const PointInterface &other) const
{
    UInt32 i;
    Bool ret = true;

    for(i = 0; i < _iSize; i++)
    {
        if(_values[i] >= other._values[i])
        {
            ret = false;
            break;
        }
    }

    return ret;
}

//! Equal operator, using Eps as the tolerance

template <class ValueTypeT,
          class StorageInterfaceT> inline
Bool PointInterface<ValueTypeT, StorageInterfaceT>::operator == (
    const PointInterface &other) const
{
    return equals(other, Eps);
}

//! Not equal operator, using Eps as the tolerance

template <class ValueTypeT,
          class StorageInterfaceT> inline
Bool PointInterface<ValueTypeT, StorageInterfaceT>::operator != (
    const PointInterface &other) const
{
    return ! (*this == other);
}

/*-------------------------------------------------------------------------*/
/*                               Functions                                 */

//! Component wise binary scalar multiplication

template <class ValueTypeT,
          class StorageInterfaceT> inline
PointInterface<ValueTypeT, StorageInterfaceT>
    operator *(const ValueTypeT                         val,
               const PointInterface<ValueTypeT,
                                    StorageInterfaceT> &vec)
{
    PointInterface<ValueTypeT, StorageInterfaceT> returnValue;

    UInt32 i;

    for(i = 0; i < StorageInterfaceT::_iSize; i++)
    {
        returnValue[i] = vec[i] * val;
    }

    return returnValue;
}

//! Write point to the given stream

template <class ValueTypeT,
          class StorageInterfaceT> inline
ostream &operator <<(ostream                                   &os,
                     const   PointInterface<ValueTypeT,
                                            StorageInterfaceT> &obj)
{

    UInt32 i;

    for(i = 0; i < StorageInterfaceT::_iSize; i++)
    {
        os << obj[i];

        if(i != StorageInterfaceT::_iSize - 1)
            os << ", ";
    }

    return os;
}



//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \class VectorInterface
 */

/*! \typedef VectorInterface::RealReturnType
    \brief Used type if the returnvalue must be a real value.
 */

/*! \typedef VectorInterface::ValueType
    \brief Value type
 */

/*! \typedef VectorInterface::Inherited
    \brief Parent type
 */

template <class ValueTypeT,
          class StorageInterfaceT>
const VectorInterface<ValueTypeT, StorageInterfaceT>
    VectorInterface<ValueTypeT, StorageInterfaceT>::Null;

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

template <class ValueTypeT,
          class StorageInterfaceT> inline
VectorInterface<ValueTypeT, StorageInterfaceT>::VectorInterface(void) : 
    Inherited()
{
    UInt32 i;

    for(i = 0; i < _iSize; i++)
    {
        _values[i] = TypeConstants<ValueTypeT>::getZeroElement();
    }
}


/*! \brief Constructor which takes a const value array.
 
    Be shure the array size at least as large as the vector size.
*/

template <class ValueTypeT,
          class StorageInterfaceT> inline
VectorInterface<ValueTypeT, 
                StorageInterfaceT>::VectorInterface(const ValueTypeT *pVals) :
    Inherited(pVals)
{
}

/*! \brief Constructor which takes a const value array.
  
    Be shure the array size at least as large as the vector size.
*/

template <class ValueTypeT,
          class StorageInterfaceT> inline
VectorInterface<ValueTypeT, 
                StorageInterfaceT>::VectorInterface(ValueTypeT *pVals) : 
    Inherited(pVals)
{
}

template <class ValueTypeT,
          class StorageInterfaceT> inline
VectorInterface<ValueTypeT, StorageInterfaceT>::VectorInterface(
    const VectorInterface &source) : 

    Inherited(source)
{
}

/*
template <class    ValueTypeT,
          class    StorageInterfaceT> inline
VectorInterface<ValueTypeT, StorageInterfaceT>::VectorInterface(
    const ValueTypeT rVal1)
{
    UInt32 i;

    _values[0] = rVal1;

    for(i = 1; i < _iSize; i++)
    {
        _values[i] = TypeConstants<ValueTypeT>::getZeroElement();
    }
}
*/

template <class ValueTypeT,
          class StorageInterfaceT> inline
VectorInterface<ValueTypeT, 
                StorageInterfaceT>::VectorInterface(const ValueTypeT rVal1,
                                                    const ValueTypeT rVal2) :

    Inherited(rVal1, rVal2)
{
}

template <class ValueTypeT,
          class StorageInterfaceT> inline
VectorInterface<ValueTypeT, 
                StorageInterfaceT>::VectorInterface(const ValueTypeT rVal1,
                                                    const ValueTypeT rVal2,
                                                    const ValueTypeT rVal3) :

    Inherited(rVal1, rVal2, rVal3)
{
}

template <class ValueTypeT,
          class StorageInterfaceT> inline
VectorInterface<ValueTypeT, 
                StorageInterfaceT>::VectorInterface(const ValueTypeT rVal1,
                                                    const ValueTypeT rVal2,
                                                    const ValueTypeT rVal3,
                                                    const ValueTypeT rVal4) :

    Inherited(rVal1, rVal2, rVal3, rVal4)
{
}


/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

template <class ValueTypeT,
          class StorageInterfaceT> inline
VectorInterface<ValueTypeT, 
                StorageInterfaceT>::~VectorInterface(void)
{
}

/*-------------------------------------------------------------------------*/
/*                          Common Math                                    */

//! Euclidean length of the vector

template <class ValueTypeT,
          class StorageInterfaceT> inline
VectorInterface<ValueTypeT, StorageInterfaceT>::RealReturnType
    VectorInterface<ValueTypeT, StorageInterfaceT>::length(void) const
{
    UInt32 i;

    RealReturnType rTmpVal = _values[0] * _values[0];

    for(i = 1; i < _iSize; i++)
    {
        rTmpVal += _values[i] * _values[i];
    }

    return osgsqrt(rTmpVal);
}

//! Changes vector to be of unit length

template <class ValueTypeT,
          class StorageInterfaceT> inline
void VectorInterface<ValueTypeT, StorageInterfaceT>::normalize(void)
{
    UInt32 i;

    ValueTypeT rLength = length();

    if(osgabs(rLength) < Eps)
    {
        rLength = TypeConstants<ValueTypeT>::getOneElement();
    }
    else
    {
        rLength = TypeConstants<ValueTypeT>::getOneElement() / rLength;
    }

    for(i = 0; i < _iSize; i++)
    {
        _values[i] *= rLength;
    }
}

#ifdef __sgi
#pragma set woff 1209
#endif

/*! \brief Returns the right handed cross-product for a given vector;
    This function is implemented for size 3 vectors only.
*/

template <class ValueTypeT,
          class StorageInterfaceT> inline
VectorInterface<ValueTypeT, StorageInterfaceT>
    VectorInterface<ValueTypeT, 
                    StorageInterfaceT>::cross(const VectorInterface &vec) const
{
    VectorInterface<ValueTypeT, StorageInterfaceT> returnValue;

    if(_iSize >= 3)
    {
        returnValue[0] =
            _values[1] * vec._values[2] - _values[2] * vec._values[1];
        returnValue[1] =
            _values[2] * vec._values[0] - _values[0] * vec._values[2];
        returnValue[2] =
            _values[0] * vec._values[1] - _values[1] * vec._values[0];
    }
    else
    {
        // Must be changed
        fprintf(stderr, "cross only implemented for size 3\n");
    }

    return returnValue;
}

template <class ValueTypeT,
          class StorageInterfaceT> inline
VectorInterface<ValueTypeT, StorageInterfaceT>
    VectorInterface<ValueTypeT, StorageInterfaceT>::operator % (
        const VectorInterface &vec) const
{
    return this->cross(vec);
}

/*! \brief Calculates the right handed cross-product with a given vector;
    This function is implemented for size 3 vectors only.
*/

template <class ValueTypeT,
          class StorageInterfaceT> inline
void VectorInterface<ValueTypeT, 
                     StorageInterfaceT>::crossThis(const VectorInterface &vec)
{
    if(_iSize >= 3)
    {
        ValueTypeT rTmp[2];

        rTmp[0] = _values[1] * vec._values[2] - _values[2] * vec._values[1];
        rTmp[1] = _values[2] * vec._values[0] - _values[0] * vec._values[2];

        _values[2] =
            _values[0] * vec._values[1] - _values[1] * vec._values[0];

        _values[0] = rTmp[0];
        _values[1] = rTmp[1];
    }
    else
    {
        // Must be changed
        fprintf(stderr, "crossThis only implemented for size 3\n");
    }
}

#ifdef __sgi
#pragma reset woff 1209
#endif

//! \brief Return the dot (inner) product for a given vector

template <class ValueTypeT,
          class StorageInterfaceT> inline
ValueTypeT VectorInterface<ValueTypeT, StorageInterfaceT>::dot(
    const VectorInterface &vec) const
{
    UInt32 i;

    ValueTypeT rTmpVal = _values[0] * vec._values[0];

    for(i = 1; i < _iSize; i++)
    {
        rTmpVal += _values[i] * vec._values[i];
    }

    return rTmpVal;
}

template <class ValueTypeT,
          class StorageInterfaceT> inline
ValueTypeT VectorInterface<ValueTypeT, StorageInterfaceT>::operator * (
    const VectorInterface &vec) const
{
    return this->dot(vec);
}

template <class ValueTypeT,
          class StorageInterfaceT> inline
ValueTypeT VectorInterface<ValueTypeT, StorageInterfaceT>::dot (
        const PntInterface &pnt) const
{
    UInt32 i;

    ValueTypeT rTmpVal = _values[0] * pnt[0];

    for(i = 1; i < _iSize; i++)
    {
        rTmpVal += _values[i] * pnt[i];
    }

    return rTmpVal;
}

template <class ValueTypeT,
          class StorageInterfaceT> inline
ValueTypeT VectorInterface<ValueTypeT, StorageInterfaceT>::operator * (
    const PntInterface &pnt) const
{
     return this->dot(pnt);
}

//! Returns the angle between this and another vector

template <class ValueTypeT,
          class StorageInterfaceT> inline
VectorInterface<ValueTypeT, StorageInterfaceT>::RealReturnType
     VectorInterface<ValueTypeT, StorageInterfaceT>::enclosedAngle(
         const VectorInterface &vec) const
{
    RealReturnType returnValue;

    if(isZero() || vec.isZero())
    {
        returnValue = TypeConstants<RealReturnType>::getZeroElement();
    }
    else
    {
        returnValue  = dot(vec);
        returnValue /= (length() * vec.length());

        if((returnValue - Eps) < -1.)
        {
            returnValue = Pi;
        }
        else if((returnValue + Eps) > 1.)
        {
            returnValue = TypeConstants<RealReturnType>::getZeroElement();
        }
        else
        {
            returnValue = osgacos(returnValue);
        }
    }

    return returnValue;
}

template <class ValueTypeT,
          class StorageInterfaceT> inline
VectorInterface<ValueTypeT, StorageInterfaceT>::RealReturnType
    VectorInterface<ValueTypeT, StorageInterfaceT>::projectTo(
        const VectorInterface &toVec)
{
    RealReturnType rDot       = dot(toVec);
    RealReturnType rSquareDot = toVec.dot(toVec);

    if(rSquareDot > Eps)
    {
        rDot /= rSquareDot;

        if(osgabs(rDot) > Eps)
        {
            *this  = toVec;
            *this *= rDot;
        }
        else
        {
            this->setNull();
            rDot = TypeConstants<RealReturnType>::getZeroElement();
        }
    }
    else
    {
        rDot = TypeConstants<RealReturnType>::getOneElement();
    }

    return rDot;
}

/*-------------------------------------------------------------------------*/
/*                                Math                                     */

//! Component wise vector addition

template <class ValueTypeT,
          class StorageInterfaceT> inline
void VectorInterface<ValueTypeT, StorageInterfaceT>::operator +=(
    const VectorInterface &vec)
{
    UInt32 i;

    for(i = 0; i < _iSize; i++)
    {
        _values[i] += vec._values[i];
    }
}

//! Component wise vector substraction

template <class ValueTypeT,
          class StorageInterfaceT> inline
void VectorInterface<ValueTypeT, StorageInterfaceT>::operator -=(
    const VectorInterface &vec)
{
    UInt32 i;

    for(i = 0; i < _iSize; i++)
    {
        _values[i] -= vec._values[i];
    }
}

//! Component wise binary vector subtraction operator

template <class ValueTypeT,
          class StorageInterfaceT> inline
VectorInterface <ValueTypeT, StorageInterfaceT>
    VectorInterface<ValueTypeT, StorageInterfaceT>::operator - (
        const VectorInterface &vec) const
{
    VectorInterface<ValueTypeT, StorageInterfaceT> returnValue;

    UInt32 i;

    for(i = 0; i < StorageInterfaceT::_iSize; i++)
    {
        returnValue[i] = _values[i] - vec[i];
    }

    return returnValue;
}

//! Component wise binary vector addition operator

template <class ValueTypeT,
          class StorageInterfaceT> inline
VectorInterface <ValueTypeT, StorageInterfaceT>
    VectorInterface<ValueTypeT, StorageInterfaceT>::operator + (
        const VectorInterface &vec) const
{
    VectorInterface<ValueTypeT, StorageInterfaceT> returnValue;

    UInt32 i;

    for(i = 0; i < StorageInterfaceT::_iSize; i++)
    {
        returnValue[i] = _values[i] + vec[i];
    }

    return returnValue;
}


//! Component wise binary scalar multiplication

template <class ValueTypeT,
          class StorageInterfaceT> inline
VectorInterface <ValueTypeT, StorageInterfaceT>
    VectorInterface<ValueTypeT, StorageInterfaceT>::operator * (
        const ValueTypeT rVal) const
{
    VectorInterface<ValueTypeT, StorageInterfaceT> returnValue;

    UInt32 i;

    for(i = 0; i < StorageInterfaceT::_iSize; i++)
    {
        returnValue[i] = _values[i] * rVal;
    }

    return returnValue;
}

//! Nondestructive unary negation, returns new vector

template <class ValueTypeT,
          class StorageInterfaceT> inline
VectorInterface<ValueTypeT, StorageInterfaceT>
    VectorInterface<ValueTypeT, StorageInterfaceT>::operator -(void) const
{
    UInt32 i;

    VectorInterface<ValueTypeT, StorageInterfaceT> returnValue;

    for(i = 0; i < _iSize; i++)
    {
        returnValue._values[i] = - _values[i];
    }

    return returnValue;
}

/*-------------------------------------------------------------------------*/
/*                             Assignment                                  */

template <class ValueTypeT,
          class StorageInterfaceT> inline
VectorInterface<ValueTypeT, StorageInterfaceT> &
    VectorInterface<ValueTypeT, StorageInterfaceT>::operator =(
        const VectorInterface &source)
{
    if(this == &source)
        return *this;

    *(static_cast<Inherited *>(this)) = source;

    return *this;
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

template <class ValueTypeT,
          class StorageInterfaceT> inline
Bool VectorInterface<ValueTypeT, StorageInterfaceT>::operator < (
    const VectorInterface &other) const
{
    UInt32 i;
    Bool   ret = true;

    for(i = 0; i < _iSize; i++)
    {
        if( _values[i] > other._values[i])
        {
            ret = false;
            break;
        }

        if(_values[i] < other._values[i])
            break;
    }

    return ret;
}

//! Equal operator, using Eps as the tolerance

template <class ValueTypeT,
          class StorageInterfaceT> inline
Bool VectorInterface<ValueTypeT, StorageInterfaceT>::operator == (
    const VectorInterface &other) const
{
    return equals(other, Eps);
}

//! Not eual operator, using Eps as the tolerance

template <class ValueTypeT,
          class StorageInterfaceT> inline
Bool VectorInterface<ValueTypeT, StorageInterfaceT>::operator != (
    const VectorInterface &other) const
{
    return ! (*this == other);
}

/*-------------------------------------------------------------------------*/
/*                               Functions                                 */

//! Component wise binary scalar multiplication

template <class ValueTypeT,
          class StorageInterfaceT> inline
VectorInterface<ValueTypeT, StorageInterfaceT>
    operator *(const ValueTypeT                          val,
               const VectorInterface<ValueTypeT,
                                     StorageInterfaceT> &vec)
{
    VectorInterface<ValueTypeT, StorageInterfaceT> returnValue;

    UInt32 i;

    for(i = 0; i < StorageInterfaceT::_iSize; i++)
    {
        returnValue[i] = vec[i] * val;
    }

    return returnValue;
}

//! Write vector to stream

template <class ValueTypeT,
          class StorageInterfaceT> inline
ostream &operator <<(        ostream                            &os,
                     const   VectorInterface<ValueTypeT,
                                             StorageInterfaceT> &obj)
{
    UInt32 i;

    for(i = 0; i < StorageInterfaceT::_iSize; i++)
    {
        os << obj[i];

        if(i != StorageInterfaceT::_iSize - 1)
            os << ", ";
    }

    return os;
}

OSG_END_NAMESPACE

#define OSGVECTOR_INLINE_CVSID "@(#)$Id: $"


