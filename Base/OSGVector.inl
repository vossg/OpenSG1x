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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdio.h>

OSG_BEGIN_NAMESPACE

/** \enum VecStorage2::VectorSizeE
 *  \brief To be able to use the storage size
 */

/** \var VecStorage2::VectorSizeE VecStorage2::_iSize
 *  \brief Storage size.
 */

/** \fn const char *VecStorage2::getClassname(void)
 *  \brief Classname.
 */

/** \var ValueTypeT VecStorage2::_values[iSize];
 *  \brief Value store
 */

/** \fn VecStorage2::VecStorage2(const VecStorage2 &source)
 *  \brief Not implemented.
 */

/** \fn void VecStorage2::operator =(const VecStorage2 &source)
 *  \brief Not implemented.
 */


/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

template <class ValueTypeT>
char VecStorage2<ValueTypeT>::cvsid[] = "@(#)$Id: $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

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

/** \brief Constructor
 */

template <class ValueTypeT> inline
VecStorage2<ValueTypeT>::VecStorage2(void)
{
}

/** \brief Destructor
 */

template <class ValueTypeT> inline
VecStorage2<ValueTypeT>::~VecStorage2(void)
{
}

/*------------------------------ access -----------------------------------*/

/** \brief Set values
 */

template <class ValueTypeT> inline
void VecStorage2<ValueTypeT>::setValues(const ValueTypeT &rVal1, 
                                        const ValueTypeT &rVal2)
{
    _values[0] = rVal1;
    _values[1] = rVal2;
}

/** \brief Get values
 */

template <class ValueTypeT> inline
void VecStorage2<ValueTypeT>::getValues(ValueTypeT &rVal1, 
                                        ValueTypeT &rVal2) const
{
    rVal1 = _values[0];
    rVal2 = _values[1];    
}

/** \brief Get the first value
 */

template <class ValueTypeT> inline
ValueTypeT VecStorage2<ValueTypeT>::x(void) const
{
    return _values[0];
}

/** \brief Get the second value
 */

template <class ValueTypeT> inline
ValueTypeT VecStorage2<ValueTypeT>::y(void) const
{
    return _values[1];    
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/


/** \enum VecStorage3::VectorSizeE
 *  \brief To be able to use the storage size
 */

/** \var VecStorage3::VectorSizeE VecStorage3::_iSize
 *  \brief Storage size.
 */

/** \fn const char *VecStorage3::getClassname(void)
 *  \brief Classname.
 */

/** \var ValueTypeT VecStorage3::_values[iSize];
 *  \brief Value store
 */

/** \fn VecStorage3::VecStorage3(const VecStorage3 &source)
 *  \brief Not implemented.
 */

/** \fn void VecStorage3::operator =(const VecStorage3 &source)
 *  \brief Not implemented.
 */


/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

template <class ValueTypeT>
char VecStorage3<ValueTypeT>::cvsid[] = "@(#)$Id: $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

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

/** \brief Constructor
 */

template <class ValueTypeT> inline
VecStorage3<ValueTypeT>::VecStorage3(void)
{
}

/** \brief Destructor
 */

template <class ValueTypeT> inline
VecStorage3<ValueTypeT>::~VecStorage3(void)
{
}

/*------------------------------ access -----------------------------------*/

/** \brief Set values
 */

template <class ValueTypeT> inline
void VecStorage3<ValueTypeT>::setValues(const ValueTypeT &rVal1, 
                                        const ValueTypeT &rVal2, 
                                        const ValueTypeT &rVal3)
{
    _values[0] = rVal1;
    _values[1] = rVal2;
    _values[2] = rVal3;
}

/** \brief Get values
 */

template <class ValueTypeT> inline
void VecStorage3<ValueTypeT>::getValues(ValueTypeT &rVal1, 
                                        ValueTypeT &rVal2, 
                                        ValueTypeT &rVal3) const
{
    rVal1 = _values[0];
    rVal2 = _values[1];    
    rVal3 = _values[2];    
}

/** \brief Get the first value
 */

template <class ValueTypeT> inline
ValueTypeT VecStorage3<ValueTypeT>::x(void) const
{
    return _values[0];
}

/** \brief Get the second value
 */

template <class ValueTypeT> inline
ValueTypeT VecStorage3<ValueTypeT>::y(void) const
{
    return _values[1];    
}

/** \brief Get the third value  
 */

template <class ValueTypeT> inline
ValueTypeT VecStorage3<ValueTypeT>::z(void) const
{
    return _values[2];    
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/



/** \enum VecStorage4::VectorSizeE
 *  \brief To be able to use the storage size
 */

/** \var VecStorage4::VectorSizeE VecStorage4::_iSize
 *  \brief Storage size.
 */

/** \fn const char *VecStorage4::getClassname(void)
 *  \brief Classname.
 */

/** \var ValueTypeT VecStorage4::_values[iSize];
 *  \brief Value store
 */

/** \fn VecStorage4::VecStorage4(const VecStorage4 &source)
 *  \brief Not implemented.
 */

/** \fn void VecStorage4::operator =(const VecStorage4 &source)
 *  \brief Not implemented.
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

template <class ValueTypeT>
char VecStorage4<ValueTypeT>::cvsid[] = "@(#)$Id: $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

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

/** \brief Constructor
 */

template <class ValueTypeT> inline
VecStorage4<ValueTypeT>::VecStorage4(void)
{
}

/** \brief Destructor
 */

template <class ValueTypeT> inline
VecStorage4<ValueTypeT>::~VecStorage4(void)
{
}

/*------------------------------ access -----------------------------------*/

/** \brief Set values
 */

template <class ValueTypeT> inline
void VecStorage4<ValueTypeT>::setValues(const ValueTypeT &rVal1, 
                                        const ValueTypeT &rVal2, 
                                        const ValueTypeT &rVal3, 
                                        const ValueTypeT &rVal4)
{
    _values[0] = rVal1;
    _values[1] = rVal2;
    _values[2] = rVal3;
    _values[3] = rVal4;
}

/** \brief Get values
 */

template <class ValueTypeT> inline
void VecStorage4<ValueTypeT>::getValues(ValueTypeT &rVal1, 
                                        ValueTypeT &rVal2, 
                                        ValueTypeT &rVal3, 
                                        ValueTypeT &rVal4) const
{
    rVal1 = _values[0];    
    rVal2 = _values[1];    
    rVal3 = _values[2];    
    rVal4 = _values[3];    
}

/** \brief Get the first value
 */

template <class ValueTypeT> inline
ValueTypeT VecStorage4<ValueTypeT>::x(void) const
{
    return _values[0];
}

/** \brief Get the second value
 */

template <class ValueTypeT> inline
ValueTypeT VecStorage4<ValueTypeT>::y(void) const
{
    return _values[1];    
}

/** \brief Get the third value  
 */

template <class ValueTypeT> inline
ValueTypeT VecStorage4<ValueTypeT>::z(void) const
{
    return _values[2];    
}

/** \brief Get the fourth value
 */

template <class ValueTypeT> inline
ValueTypeT VecStorage4<ValueTypeT>::w(void) const
{
    return _values[3];    
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/


/** \typedef PointInterface::RealReturnType
 *  \brief Used type if the returnvalue must be a real value.
 */

/** \typedef PointInterface::ValueType
 *  \brief Value type
 */

/** \typedef PointInterface::Inherited
 *  \brief Parent type
 */

/** \fn const char *PointInterface::getClassname(void)
 *  \brief Classname.
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

template<class ValueTypeT, class StorageInterfaceT>
char PointInterface<ValueTypeT, StorageInterfaceT>::cvsid[] = 
    "@(#)$Id: $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


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


/** \brief Constructor
 */

template <class ValueTypeT, 
          class StorageInterfaceT> inline
PointInterface<ValueTypeT, StorageInterfaceT>::PointInterface(
    void) : Inherited()
{
    UInt32 i;

    for(i = 0; i < _iSize; i++)
    {
        _values[i] = TypeConstants<ValueTypeT>::getZeroElement();
    }
}

/** \brief Copy Constructor
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
PointInterface<ValueTypeT, StorageInterfaceT>::PointInterface(
    const PointInterface &source) : Inherited()
{
    UInt32 i;

    for(i = 0; i < _iSize; i++)
    {
        _values[i] = source._values[i];
    }
}

/** \brief Constructor which takes a const value array.
 *
 *  Be shure the array size at least as large as the vector size.
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
PointInterface<ValueTypeT, StorageInterfaceT>::PointInterface(
    const ValueTypeT *pVals) : Inherited()
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

/** \brief Constructor which takes a value array.
 *
 *  Be shure the array size at least as large as the vector size.
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
PointInterface<ValueTypeT, StorageInterfaceT>::PointInterface(
    ValueTypeT *pVals) : Inherited()
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

/** \brief Constructor which takes two values, remaining entries will be zero
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
PointInterface<ValueTypeT, StorageInterfaceT>::PointInterface(
    const ValueTypeT rVal1, 
    const ValueTypeT rVal2) : Inherited()
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

/** \brief Constructor which takes three values, remaining entries will be zero
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
PointInterface<ValueTypeT, StorageInterfaceT>::PointInterface(
    const ValueTypeT rVal1, 
    const ValueTypeT rVal2, 
    const ValueTypeT rVal3) : Inherited()
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

/** \brief Constructor which takes four values, remaining entries will be zero
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
PointInterface<ValueTypeT, StorageInterfaceT>::PointInterface(
    const ValueTypeT rVal1, 
    const ValueTypeT rVal2, 
    const ValueTypeT rVal3, 
    const ValueTypeT rVal4) : Inherited()
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

/** \brief Destructor
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
PointInterface<ValueTypeT, StorageInterfaceT>::~PointInterface(
    void)
{
}

/*------------------------- set values -------------------------------*/

/** \brief Set all values to zero
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
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

/** \brief Set values from the given point
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
void PointInterface<ValueTypeT, StorageInterfaceT>::setValue(
    const PointInterface &vec)
{
    UInt32 i;
    
    for(i = 0; i < _iSize; i++)
    {
        _values[i] = vec._values[i];
    }    
}


/** \brief Set value from a given array, be sure to match sizes
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
void PointInterface<ValueTypeT, StorageInterfaceT>::setValue(
    const ValueTypeT *pVals)
{
    UInt32 i;
    
    for(i = 0; i < _iSize; i++)
    {
        _values[i] = pVals[i];
    }    
}

/** \brief Extract values from given string, where both (const and not const)
    must be present, otherwise \b the \b compiler \b strikes \b back :-) (GV)
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
void PointInterface<ValueTypeT, StorageInterfaceT>::setValue(
    const char *szString)
{
    UInt32 i;
    UInt32 numOfToken = _iSize;

    char *c      = const_cast<char*>(szString);
    char *tokenC = 0;

    char  token[256];

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

/** \brief Extract values from given string, where both (const and not const)
    must be present, otherwise \b the \b compiler \b strikes \b back :-) (GV)
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
void PointInterface<ValueTypeT, StorageInterfaceT>::setValue(
    char *szString)
{
    setValue(static_cast<const char *>(szString));
}

/*------------------------- get values -------------------------------*/

/** \brief Get a pointer to the value storage
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
ValueTypeT *PointInterface<ValueTypeT, 
                                  StorageInterfaceT>::getValues(void)
{
    return _values;
}

/** \brief Get a const pointer to the value storage
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
const ValueTypeT *PointInterface<ValueTypeT, 
                                        StorageInterfaceT>::getValues(
   void) const
{
    return _values;
}

/*--------------------------- common math -------------------------------*/

/** \brief Returns true iff the norm of each value is less than Eps
*/

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
Bool PointInterface<ValueTypeT, StorageInterfaceT>::isZero(
    void) const
{
    UInt32 i;
    Bool returnValue = true;

    for(i = 0; i < _iSize; i++)
    {
        returnValue &= ((_values[i] <=  Eps) && 
                        (_values[i] >= -Eps));
    }

    return returnValue;
}

/** \brief Negates each value of the point in place
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
void PointInterface<ValueTypeT, StorageInterfaceT>::negate(void)
{
    UInt32 i;

    for(i = 0; i < _iSize; i++)
    {
        _values[i] = -_values[i];
    }
}

/** \brief Returns true iff the two points are eual within a given tolerance
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
Bool PointInterface<ValueTypeT, StorageInterfaceT>::equals(
    const PointInterface &vec, 
    const ValueTypeT       tolerance) const
{
    UInt32 i; 
    Bool   returnValue = true;

    for(i = 0; i < _iSize; i++)
    {
        returnValue &= ( (_values[i]     - vec._values[i] <= tolerance) && 
                         (vec._values[i] - _values[i]     <= tolerance));
    }

    return returnValue;
}

/*------------------------------ math -----------------------------------*/

/** \brief Component wise scalar multiplication
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
void PointInterface<ValueTypeT, StorageInterfaceT>::operator *=(
    const ValueTypeT  val)
{
    UInt32 i;

    for(i = 0; i < _iSize; i++)
    {
        _values[i] *= val;
    }
}

/** \brief Component wise scalar division
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
void PointInterface<ValueTypeT, StorageInterfaceT>::operator /=(
    const ValueTypeT  val)
{
    UInt32 i;

    for(i = 0; i < _iSize; i++)
    {
        _values[i] /= val;
    }
}

/** \brief Point substraction, returns a new vector
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
VectorInterface<ValueTypeT, StorageInterfaceT> 
    PointInterface<ValueTypeT, StorageInterfaceT>::operator -(
        const PointInterface &vec) const
{
    UInt32 i;

    VectorInterface<ValueTypeT, StorageInterfaceT> 
        returnValue(*this);

    for(i = 0; i < _iSize; i++)
    {
        returnValue[i] -= vec[i];
    }

    return returnValue;
}

/** \brief Component wise binary vector addition operator
 */
template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
PointInterface <ValueTypeT, StorageInterfaceT>
    PointInterface<ValueTypeT, StorageInterfaceT>::operator + (
        const VectorInterface<ValueTypeT, StorageInterfaceT> &vec) const
{
	PointInterface<ValueTypeT, StorageInterfaceT> returnValue;

    UInt32 i;

    for(i = 0; i < StorageInterfaceT::_iSize; i++)
    {
		returnValue[i] = _values[i] + vec[i];
	}

	return returnValue;
}

/** \brief Component wise binary vector addition operator
 */
template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
PointInterface <ValueTypeT, StorageInterfaceT>
    PointInterface<ValueTypeT, StorageInterfaceT>::operator - (
        const VectorInterface<ValueTypeT, StorageInterfaceT> &vec) const
{
	PointInterface<ValueTypeT, StorageInterfaceT> returnValue;

    UInt32 i;

    for(i = 0; i < StorageInterfaceT::_iSize; i++)
    {
		returnValue[i] = _values[i] - vec[i];
	}

	return returnValue;
}

/** \brief Component wise binary scalar multiplication
 */
template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
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

/** \brief Nondestructive unary negation, returns new point
 */
template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
PointInterface<ValueTypeT, StorageInterfaceT> 
    PointInterface<ValueTypeT, StorageInterfaceT>::operator -(
        void)
{
    UInt32 i;

    PointInterface<ValueTypeT, StorageInterfaceT> returnValue;

    for(i = 0; i < _iSize; i++)
    {
        returnValue._values[i] = - _values[i];
    }

    return returnValue;
}

/*------------------------- element access ------------------------------*/

/** \brief Indexed element access
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
ValueTypeT &
    PointInterface<ValueTypeT, StorageInterfaceT>::operator[](
        const UInt32 uiVal)
{
    return _values[uiVal];
}

/** \brief Const indexed element access
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
const ValueTypeT &
    PointInterface<ValueTypeT, StorageInterfaceT>::operator[](
        const UInt32 uiVal) const
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

/*------------------------- assignment ----------------------------------*/

/** \brief Assignment operator
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
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

/*------------------------- comparison ----------------------------------*/

/** \brief Less than, not implemented
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
Bool PointInterface<ValueTypeT, StorageInterfaceT>::operator < (
    const PointInterface &other) const
{
    missing;
}

/** \brief Equal operator, using Eps as the tolerance
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
Bool PointInterface<ValueTypeT, StorageInterfaceT>::operator == (
    const PointInterface &other) const
{
	return equals(other, Eps);
}

/** \brief Not equal operator, using Eps as the tolerance
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
Bool PointInterface<ValueTypeT, StorageInterfaceT>::operator != (
    const PointInterface &other) const
{
    return ! (*this == other);
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  friend operators                                                       -
\*-------------------------------------------------------------------------*/

/** \brief Component wise binary scalar multiplication
 */
template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
PointInterface<ValueTypeT, StorageInterfaceT>
    operator *(const ValueTypeT                             val, 
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

/** \brief Write point to the given stream
 */
template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
ostream &operator <<(ostream                                          &os,
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


/** \typedef VectorInterface::RealReturnType
 *  \brief Used type if the returnvalue must be a real value.
 */

/** \typedef VectorInterface::ValueType
 *  \brief Value type
 */

/** \typedef VectorInterface::Inherited
 *  \brief Parent type
 */

/** \fn const char *VectorInterface::getClassname(void)
 *  \brief Classname.
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

template<class ValueTypeT, class StorageInterfaceT>
char VectorInterface<ValueTypeT, StorageInterfaceT>::cvsid[] = 
    "@(#)$Id: $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

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


/** \brief Constructor
 */

template <class ValueTypeT, 
          class StorageInterfaceT> inline
VectorInterface<ValueTypeT, StorageInterfaceT>::VectorInterface(
    void) : Inherited()
{
    UInt32 i;

    for(i = 0; i < _iSize; i++)
    {
        _values[i] = TypeConstants<ValueTypeT>::getZeroElement();
    }
}

/** \brief Copy Constructor
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
VectorInterface<ValueTypeT, StorageInterfaceT>::VectorInterface(
    const VectorInterface &source) : Inherited(source)
{
}

/** \brief Constructor which takes a const value array.
 *
 *  Be shure the array size at least as large as the vector size.
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
VectorInterface<ValueTypeT, StorageInterfaceT>::VectorInterface(
    const ValueTypeT *pVals) : Inherited(pVals)
{
}

/** \brief Constructor which takes a const value array.
 *
 *  Be shure the array size at least as large as the vector size.
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
VectorInterface<ValueTypeT, StorageInterfaceT>::VectorInterface(
    ValueTypeT *pVals) : Inherited(pVals)
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
 
/** \brief Constructor which takes two values, remaining entries will be zero
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
VectorInterface<ValueTypeT, StorageInterfaceT>::VectorInterface(
    const ValueTypeT rVal1, 
    const ValueTypeT rVal2) :
    
    Inherited(rVal1, rVal2)
{
}

/** \brief Constructor which takes three values, remaining entries will be zero
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
VectorInterface<ValueTypeT, StorageInterfaceT>::VectorInterface(
    const ValueTypeT rVal1, 
    const ValueTypeT rVal2, 
    const ValueTypeT rVal3) :
    
    Inherited(rVal1, rVal2, rVal3)
{
}

/** \brief Constructor which takes four values, remaining entries will be zero
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
VectorInterface<ValueTypeT, StorageInterfaceT>::VectorInterface(
    const ValueTypeT rVal1, 
    const ValueTypeT rVal2, 
    const ValueTypeT rVal3, 
    const ValueTypeT rVal4) :

    Inherited(rVal1, rVal2, rVal3, rVal4)
{
}


/** \brief Destructor
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
VectorInterface<ValueTypeT, StorageInterfaceT>::~VectorInterface(
    void)
{
}

/*------------------------- set values -------------------------------*/

/** \brief Euclidean length of the vector 
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
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

/** \brief Changes vector to be of unit length
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
void VectorInterface<ValueTypeT, StorageInterfaceT>::normalize(void)
{
    UInt32 i;

    ValueTypeT rLength = length();

    if(osgabs(rLength) < Eps)
        rLength = TypeConstants<ValueTypeT>::getOneElement();
    else
        rLength = TypeConstants<ValueTypeT>::getOneElement() / rLength;
     
    for(i = 0; i < _iSize; i++)
    {
        _values[i] *= rLength;
    }
}

#ifdef __sgi
#pragma set woff 1209
#endif

/** \brief Returns the right handed cross-product for a given vector; 
 *  This function is implemented for size 3 vectors only.
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
VectorInterface<ValueTypeT, StorageInterfaceT> 
    VectorInterface<ValueTypeT, StorageInterfaceT>::cross(
        const VectorInterface &vec) const
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

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
VectorInterface<ValueTypeT, StorageInterfaceT> 
	VectorInterface<ValueTypeT, StorageInterfaceT>::operator % (
			const VectorInterface &vec) const
{
	return this->cross( vec );
}

/** \brief Calculates the right handed cross-product with a given vector; 
 *  This function is implemented for size 3 vectors only.
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
void VectorInterface<ValueTypeT, StorageInterfaceT>::crossThis(
    const VectorInterface &vec)
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

/** \brief Return the dot (inner) product for a given vector
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
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

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
ValueTypeT VectorInterface<ValueTypeT, StorageInterfaceT>::operator * (
	const VectorInterface &vec) const
{
	return this->dot( vec );
}

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
ValueTypeT VectorInterface<ValueTypeT, StorageInterfaceT>::dot (
		const PointInterface<ValueTypeT, StorageInterfaceT> &pnt) const
{
    UInt32 i;

    ValueTypeT rTmpVal = _values[0] * pnt[0];

    for(i = 1; i < _iSize; i++)
    {
        rTmpVal += _values[i] * pnt[i];
    }
    
    return rTmpVal;
}

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
ValueTypeT VectorInterface<ValueTypeT, StorageInterfaceT>::operator * (
		const PointInterface<ValueTypeT, StorageInterfaceT> &pnt) const
{
     return this->dot( pnt );
}

/** \brief Returns the angle between this and another vector
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
VectorInterface<ValueTypeT, StorageInterfaceT>::RealReturnType
     VectorInterface<ValueTypeT, StorageInterfaceT>::enclosedAngle(
         const VectorInterface &vec) const
{
    RealReturnType returnValue;

    if(isZero() || vec.isZero())
        returnValue = TypeConstants<RealReturnType>::getZeroElement();
    else
    {
        returnValue  = dot(vec);
        returnValue /= (length() * vec.length());

        if((returnValue - Eps) < -1.)
            returnValue = Pi;
        else if((returnValue + Eps) > 1.)
            returnValue = TypeConstants<RealReturnType>::getZeroElement();
        else
        {
            returnValue = osgacos(returnValue);
        }
    }
    
    return returnValue;
}

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
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
            this->setValues(0., 0., 0.);
            rDot = TypeConstants<RealReturnType>::getZeroElement();
        }
    }
    else
    {
        rDot = TypeConstants<RealReturnType>::getOneElement();
    }
    
    return rDot;
}

/*------------------------------ math -----------------------------------*/

/** \brief Component wise vector addition
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
void VectorInterface<ValueTypeT, StorageInterfaceT>::operator +=(
    const VectorInterface    &vec)
{
    UInt32 i;

    for(i = 0; i < _iSize; i++)
    {
        _values[i] += vec._values[i];
    }
}

/** \brief Component wise vector substraction
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
void VectorInterface<ValueTypeT, StorageInterfaceT>::operator -=(
    const VectorInterface    &vec)
{
    UInt32 i;

    for(i = 0; i < _iSize; i++)
    {
        _values[i] -= vec._values[i];
    }
}

/** \brief Component wise binary vector addition operator
 */
template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
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

/** \brief Component wise binary vector subtraction operator
 */
template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
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


/** \brief Component wise binary scalar multiplication
 */
template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
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

/** \brief Nondestructive unary negation, returns new vector
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
VectorInterface<ValueTypeT, StorageInterfaceT> 
    VectorInterface<ValueTypeT, StorageInterfaceT>::operator -(
        void) const
{
    UInt32 i;

    VectorInterface<ValueTypeT, StorageInterfaceT> returnValue;

    for(i = 0; i < _iSize; i++)
    {
        returnValue._values[i] = - _values[i];
    }

    return returnValue;
}

/*------------------------- assignment ----------------------------------*/

/** \brief Assignment operator
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
VectorInterface<ValueTypeT, StorageInterfaceT> &
    VectorInterface<ValueTypeT, StorageInterfaceT>::operator =(
        const VectorInterface &source)
{
	if(this == &source)
		return *this;

    *(static_cast<Inherited *>(this)) = source;

	return *this;
}

/*------------------------- comparison ----------------------------------*/

/** \brief Less than, not implemented
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
Bool VectorInterface<ValueTypeT, StorageInterfaceT>::operator < (
    const VectorInterface &other) const
{
    missing;
}

/** \brief Equal operator, using Eps as the tolerance
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
Bool VectorInterface<ValueTypeT, StorageInterfaceT>::operator == (
    const VectorInterface &other) const
{
	return equals(other, Eps);
}

/** \brief Not eual operator, using Eps as the tolerance
 */

template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
Bool VectorInterface<ValueTypeT, StorageInterfaceT>::operator != (
    const VectorInterface &other) const
{
    return ! (*this == other);
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  friend operators                                                       -
\*-------------------------------------------------------------------------*/

/** \brief Component wise binary scalar multiplication
 */
template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
OSG_BASE_DLLMAPPING
VectorInterface<ValueTypeT, StorageInterfaceT>
    operator *(const ValueTypeT                             val, 
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

/** \brief Write vector to stream
 */
template <class    ValueTypeT, 
          class    StorageInterfaceT> inline
ostream &operator <<(ostream                                  &os,
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



