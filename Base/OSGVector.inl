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

/*! \page vecpointmat Vector, Point and Matrix Design
 *  to be done soon, so stay tuned :-)) (GV)
 *
 * Important : 
 *
 * - vectors and points are different classes
 * - M * v | M * p semantics
 * - M transposed is stored
 */

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdio.h>

OSG_BEGIN_NAMESPACE

/** \enum OSGVecStorage2::VectorSizeE
 *  \brief To be able to use the storage size
 */

/** \var OSGVecStorage2::VectorSizeE OSGVecStorage2::_iSize
 *  \brief Storage size.
 */

/** \fn const char *OSGVecStorage2::getClassname(void)
 *  \brief Classname.
 */

/** \var OSGValueTypeT OSGVecStorage2::_values[iSize];
 *  \brief Value store
 */

/** \fn OSGVecStorage2::OSGVecStorage2(const OSGVecStorage2 &source)
 *  \brief Not implemented.
 */

/** \fn void OSGVecStorage2::operator =(const OSGVecStorage2 &source)
 *  \brief Not implemented.
 */


/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

template <class OSGValueTypeT>
char OSGVecStorage2<OSGValueTypeT>::cvsid[] = "@(#)$Id: $";

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

template <class OSGValueTypeT> inline
OSGVecStorage2<OSGValueTypeT>::OSGVecStorage2(void)
{
}

/** \brief Destructor
 */

template <class OSGValueTypeT> inline
OSGVecStorage2<OSGValueTypeT>::~OSGVecStorage2(void)
{
}

/*------------------------------ access -----------------------------------*/

/** \brief Set values
 */

template <class OSGValueTypeT> inline
void OSGVecStorage2<OSGValueTypeT>::setValues(const OSGValueTypeT &rVal1, 
                                              const OSGValueTypeT &rVal2)
{
    _values[0] = rVal1;
    _values[1] = rVal2;
}

/** \brief Get values
 */

template <class OSGValueTypeT> inline
void OSGVecStorage2<OSGValueTypeT>::getValues(OSGValueTypeT &rVal1, 
                                              OSGValueTypeT &rVal2) const
{
    rVal1 = _values[0];
    rVal2 = _values[1];    
}

/** \brief Get the first value
 */

template <class OSGValueTypeT> inline
OSGValueTypeT OSGVecStorage2<OSGValueTypeT>::x(void) const
{
    return _values[0];
}

/** \brief Get the second value
 */

template <class OSGValueTypeT> inline
OSGValueTypeT OSGVecStorage2<OSGValueTypeT>::y(void) const
{
    return _values[1];    
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/


/** \enum OSGVecStorage3::VectorSizeE
 *  \brief To be able to use the storage size
 */

/** \var OSGVecStorage3::VectorSizeE OSGVecStorage3::_iSize
 *  \brief Storage size.
 */

/** \fn const char *OSGVecStorage3::getClassname(void)
 *  \brief Classname.
 */

/** \var OSGValueTypeT OSGVecStorage3::_values[iSize];
 *  \brief Value store
 */

/** \fn OSGVecStorage3::OSGVecStorage3(const OSGVecStorage3 &source)
 *  \brief Not implemented.
 */

/** \fn void OSGVecStorage3::operator =(const OSGVecStorage3 &source)
 *  \brief Not implemented.
 */


/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

template <class OSGValueTypeT>
char OSGVecStorage3<OSGValueTypeT>::cvsid[] = "@(#)$Id: $";

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

template <class OSGValueTypeT> inline
OSGVecStorage3<OSGValueTypeT>::OSGVecStorage3(void)
{
}

/** \brief Destructor
 */

template <class OSGValueTypeT> inline
OSGVecStorage3<OSGValueTypeT>::~OSGVecStorage3(void)
{
}

/*------------------------------ access -----------------------------------*/

/** \brief Set values
 */

template <class OSGValueTypeT> inline
void OSGVecStorage3<OSGValueTypeT>::setValues(const OSGValueTypeT &rVal1, 
                                              const OSGValueTypeT &rVal2, 
                                              const OSGValueTypeT &rVal3)
{
    _values[0] = rVal1;
    _values[1] = rVal2;
    _values[2] = rVal3;
}

/** \brief Get values
 */

template <class OSGValueTypeT> inline
void OSGVecStorage3<OSGValueTypeT>::getValues(OSGValueTypeT &rVal1, 
                                              OSGValueTypeT &rVal2, 
                                              OSGValueTypeT &rVal3) const
{
    rVal1 = _values[0];
    rVal2 = _values[1];    
    rVal3 = _values[2];    
}

/** \brief Get the first value
 */

template <class OSGValueTypeT> inline
OSGValueTypeT OSGVecStorage3<OSGValueTypeT>::x(void) const
{
    return _values[0];
}

/** \brief Get the second value
 */

template <class OSGValueTypeT> inline
OSGValueTypeT OSGVecStorage3<OSGValueTypeT>::y(void) const
{
    return _values[1];    
}

/** \brief Get the third value  
 */

template <class OSGValueTypeT> inline
OSGValueTypeT OSGVecStorage3<OSGValueTypeT>::z(void) const
{
    return _values[2];    
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/



/** \enum OSGVecStorage4::VectorSizeE
 *  \brief To be able to use the storage size
 */

/** \var OSGVecStorage4::VectorSizeE OSGVecStorage4::_iSize
 *  \brief Storage size.
 */

/** \fn const char *OSGVecStorage4::getClassname(void)
 *  \brief Classname.
 */

/** \var OSGValueTypeT OSGVecStorage4::_values[iSize];
 *  \brief Value store
 */

/** \fn OSGVecStorage4::OSGVecStorage4(const OSGVecStorage4 &source)
 *  \brief Not implemented.
 */

/** \fn void OSGVecStorage4::operator =(const OSGVecStorage4 &source)
 *  \brief Not implemented.
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

template <class OSGValueTypeT>
char OSGVecStorage4<OSGValueTypeT>::cvsid[] = "@(#)$Id: $";

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

template <class OSGValueTypeT> inline
OSGVecStorage4<OSGValueTypeT>::OSGVecStorage4(void)
{
}

/** \brief Destructor
 */

template <class OSGValueTypeT> inline
OSGVecStorage4<OSGValueTypeT>::~OSGVecStorage4(void)
{
}

/*------------------------------ access -----------------------------------*/

/** \brief Set values
 */

template <class OSGValueTypeT> inline
void OSGVecStorage4<OSGValueTypeT>::setValues(const OSGValueTypeT &rVal1, 
                                              const OSGValueTypeT &rVal2, 
                                              const OSGValueTypeT &rVal3, 
                                              const OSGValueTypeT &rVal4)
{
    _values[0] = rVal1;
    _values[1] = rVal2;
    _values[2] = rVal3;
    _values[3] = rVal4;
}

/** \brief Get values
 */

template <class OSGValueTypeT> inline
void OSGVecStorage4<OSGValueTypeT>::getValues(OSGValueTypeT &rVal1, 
                                              OSGValueTypeT &rVal2, 
                                              OSGValueTypeT &rVal3, 
                                              OSGValueTypeT &rVal4) const
{
    rVal1 = _values[0];    
    rVal2 = _values[1];    
    rVal3 = _values[2];    
    rVal4 = _values[3];    
}

/** \brief Get the first value
 */

template <class OSGValueTypeT> inline
OSGValueTypeT OSGVecStorage4<OSGValueTypeT>::x(void) const
{
    return _values[0];
}

/** \brief Get the second value
 */

template <class OSGValueTypeT> inline
OSGValueTypeT OSGVecStorage4<OSGValueTypeT>::y(void) const
{
    return _values[1];    
}

/** \brief Get the third value  
 */

template <class OSGValueTypeT> inline
OSGValueTypeT OSGVecStorage4<OSGValueTypeT>::z(void) const
{
    return _values[2];    
}

/** \brief Get the fourth value
 */

template <class OSGValueTypeT> inline
OSGValueTypeT OSGVecStorage4<OSGValueTypeT>::w(void) const
{
    return _values[3];    
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/


/** \typedef OSGPointInterface::OSGRealReturnType
 *  \brief Used type if the returnvalue must be a real value.
 */

/** \typedef OSGPointInterface::OSGValueType
 *  \brief Value type
 */

/** \typedef OSGPointInterface::Inherited
 *  \brief Parent type
 */

/** \fn const char *OSGPointInterface::getClassname(void)
 *  \brief Classname.
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

template<class OSGValueTypeT, class OSGStorageInterfaceT>
char OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT>::cvsid[] = 
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

template <class OSGValueTypeT, 
          class OSGStorageInterfaceT> inline
OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT>::OSGPointInterface(
    void)
{
    OSGUInt32 i;

    for(i = 0; i < _iSize; i++)
    {
        _values[i] = OSGTypeConstants<OSGValueTypeT>::getZeroElement();
    }
}

/** \brief Copy Constructor
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT>::OSGPointInterface(
    const OSGPointInterface &source)
{
    OSGUInt32 i;

    for(i = 0; i < _iSize; i++)
    {
        _values[i] = source._values[i];
    }
}

/** \brief Constructor which takes a const value array.
 *
 *  Be shure the array size at least as large as the vector size.
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT>::OSGPointInterface(
    const OSGValueTypeT *pVals)
{
    OSGUInt32 i;

    if(pVals == NULL)
    {
        for(i = 0; i < _iSize; i++)
        {
            _values[i] = OSGTypeConstants<OSGValueTypeT>::getZeroElement();
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

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT>::OSGPointInterface(
    OSGValueTypeT *pVals)
{
    OSGUInt32 i;

    if(pVals == NULL)
    {
        for(i = 0; i < _iSize; i++)
        {
            _values[i] = OSGTypeConstants<OSGValueTypeT>::getZeroElement();
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
template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT>::OSGPointInterface(
    const OSGValueTypeT rVal1)
{
    OSGUInt32 i;

    _values[0] = rVal1;

    for(i = 1; i < _iSize; i++)
    {
        _values[i] = OSGTypeConstants<OSGValueTypeT>::getZeroElement();
    }    
}
*/
 
#ifdef __sgi
#pragma set woff 1209
#endif

/** \brief Constructor which takes two values, remaining entries will be zero
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT>::OSGPointInterface(
    const OSGValueTypeT rVal1, 
    const OSGValueTypeT rVal2)
{
    OSGUInt32 i;

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
            _values[i] = OSGTypeConstants<OSGValueTypeT>::getZeroElement();
        }    
    }
}

#ifdef __sgi
#pragma reset woff 1209

#pragma set woff 1209
#endif

/** \brief Constructor which takes three values, remaining entries will be zero
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT>::OSGPointInterface(
    const OSGValueTypeT rVal1, 
    const OSGValueTypeT rVal2, 
    const OSGValueTypeT rVal3)
{
    OSGUInt32 i;

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
            _values[i] = OSGTypeConstants<OSGValueTypeT>::getZeroElement();
        }    
    }
}

#ifdef __sgi
#pragma reset woff 1209

#pragma set woff 1209
#endif

/** \brief Constructor which takes four values, remaining entries will be zero
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT>::OSGPointInterface(
    const OSGValueTypeT rVal1, 
    const OSGValueTypeT rVal2, 
    const OSGValueTypeT rVal3, 
    const OSGValueTypeT rVal4)
{
    OSGUInt32 i;

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
            _values[i] = OSGTypeConstants<OSGValueTypeT>::getZeroElement();
        }    
    }
}

#ifdef __sgi
#pragma reset woff 1209
#endif

/** \brief Destructor
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT>::~OSGPointInterface(
    void)
{
}

/*------------------------- set values -------------------------------*/

/** \brief Set all values to zero
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
void OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT>::setNull(void)
{
    OSGUInt32 i;

    for(i = 0; i < _iSize; i++)
    {
        _values[i] = OSGTypeConstants<OSGValueTypeT>::getZeroElement();
    }
}

/*
template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
void OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT>::setValue(
    const OSGValueTypeT &rVal1)
{
    _values[0] = rVal1;
}
*/

/** \brief Set values from the given point
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
void OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT>::setValue(
    const OSGPointInterface &vec)
{
    OSGUInt32 i;
    
    for(i = 0; i < _iSize; i++)
    {
        _values[i] = vec._values[i];
    }    
}


/** \brief Set value from a given array, be sure to match sizes
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
void OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT>::setValue(
    const OSGValueTypeT *pVals)
{
    OSGUInt32 i;
    
    for(i = 0; i < _iSize; i++)
    {
        _values[i] = pVals[i];
    }    
}

/** \brief Extract values from given string, where both (const and not const)
    must be present, otherwise \b the \b compiler \b strikes \b back :-) (GV)
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
void OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT>::setValue(
    const char *szString)
{
    OSGUInt32 i;
    OSGUInt32 numOfToken = _iSize;

    char *c      = const_cast<char*>(szString);
    char *tokenC = 0;

    char  token[256];

    if(szString == NULL || (*szString) == '\0') 
    {
        for(i = 0; i < _iSize; i++)
            _values[i] = OSGTypeConstants<OSGValueTypeT>::getZeroElement();

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
                        OSGTypeConstants<OSGValueTypeT>::getFromString(token);
                }

                while (i < numOfToken) 
                {
                    _values[i++] = 
                        OSGTypeConstants<OSGValueTypeT>::getZeroElement();
                }
                break;

            case ' ':
            case '\t':
                if(tokenC) 
                {
                    *tokenC = 0;
                    _values[i++] = 
                        OSGTypeConstants<OSGValueTypeT>::getFromString(token);
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

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
void OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT>::setValue(
    char *szString)
{
    setValue(static_cast<const char *>(szString));
}

/*------------------------- get values -------------------------------*/

/** \brief Get a pointer to the value storage
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGValueTypeT *OSGPointInterface<OSGValueTypeT, 
                                  OSGStorageInterfaceT>::getValueRef(void)
{
    return _values;
}

/** \brief Get a const pointer to the value storage
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
const OSGValueTypeT *OSGPointInterface<OSGValueTypeT, 
                                        OSGStorageInterfaceT>::getValueRef(
   void) const
{
    return _values;
}

/*--------------------------- common math -------------------------------*/

/** \brief Returns true iff the norm of each value is less than osgEps
*/

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGBool OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT>::isZero(
    void) const
{
    OSGUInt32 i;
    OSGBool returnValue = true;

    for(i = 0; i < _iSize; i++)
    {
        returnValue &= ((_values[i] <=  osgEps) && 
                        (_values[i] >= -osgEps));
    }

    return returnValue;
}

/** \brief Negates each value of the point in place
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
void OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT>::negate(void)
{
    OSGUInt32 i;

    for(i = 0; i < _iSize; i++)
    {
        _values[i] = -_values[i];
    }
}

/** \brief Returns true iff the two points are eual within a given tolerance
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGBool OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT>::equals(
    const OSGPointInterface &vec, 
    const OSGValueTypeT       tolerance) const
{
    OSGUInt32 i; 
    OSGBool   returnValue = true;

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

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
void OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT>::operator *=(
    const OSGValueTypeT  val)
{
    OSGUInt32 i;

    for(i = 0; i < _iSize; i++)
    {
        _values[i] *= val;
    }
}

/** \brief Component wise scalar division
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
void OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT>::operator /=(
    const OSGValueTypeT  val)
{
    OSGUInt32 i;

    for(i = 0; i < _iSize; i++)
    {
        _values[i] /= val;
    }
}

/** \brief Point substraction, returns a new vector
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT> 
    OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT>::operator -(
        const OSGPointInterface &vec) const
{
    OSGUInt32 i;

    OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT> 
        returnValue(*this);

    for(i = 0; i < _iSize; i++)
    {
        returnValue._values[i] -= vec._values[i];
    }

    return returnValue;
}

/** \brief Component wise binary scalar multiplication
 */
template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGPointInterface <OSGValueTypeT, OSGStorageInterfaceT>
    OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT>::operator * (
        const OSGValueTypeT rVal) const
{
	OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT> returnValue;

    OSGUInt32 i;

    for(i = 0; i < OSGStorageInterfaceT::_iSize; i++)
    {
		returnValue[i] = _values[i] * rVal;
	}

	return returnValue;
}

/** \brief Nondestructive unary negation, returns new point
 */
template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT> 
    OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT>::operator -(
        void)
{
    OSGUInt32 i;

    OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT> returnValue;

    for(i = 0; i < _iSize; i++)
    {
        returnValue._values[i] = - _values[i];
    }

    return returnValue;
}

/*------------------------- element access ------------------------------*/

/** \brief Indexed element access
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGValueTypeT &
    OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT>::operator[](
        const OSGUInt32 uiVal)
{
    return _values[uiVal];
}

/** \brief Const indexed element access
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
const OSGValueTypeT &
    OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT>::operator[](
        const OSGUInt32 uiVal) const
{
    return _values[uiVal];
}

#if 0
template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT>::operator 
    OSGValueTypeT *(void)
{
    return _values;
}

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT>::operator 
    const OSGValueTypeT *(void)
{
    return _values;
}
#endif

/*------------------------- assignment ----------------------------------*/

/** \brief Assignment operator
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT> &
    OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT>::operator =(
        const OSGPointInterface &source)
{
    OSGUInt32 i;

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

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
bool OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT>::operator < (
    const OSGPointInterface &other) const
{
    missing;
}

/** \brief Equal operator, using osgEps as the tolerance
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGBool OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT>::operator == (
    const OSGPointInterface &other) const
{
	return equals(other, osgEps);
}

/** \brief Not equal operator, using osgEps as the tolerance
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGBool OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT>::operator != (
    const OSGPointInterface &other) const
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
template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT>
    operator *(const OSGValueTypeT                             val, 
               const OSGPointInterface<OSGValueTypeT, 
                                        OSGStorageInterfaceT> &vec)
{
	OSGPointInterface<OSGValueTypeT, OSGStorageInterfaceT> returnValue;

    OSGUInt32 i;

    for(i = 0; i < OSGStorageInterfaceT::_iSize; i++)
    {
		returnValue[i] = vec[i] * val;
	}

	return returnValue;
}

/** \brief Write point to the given stream
 */
template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
ostream &operator <<(ostream                                          &os,
                     const   OSGPointInterface<OSGValueTypeT, 
                                                OSGStorageInterfaceT> &obj)
{

    OSGUInt32 i;

    for(i = 0; i < OSGStorageInterfaceT::_iSize; i++)
    {
		os << obj[i];

        if(i != OSGStorageInterfaceT::_iSize - 1)
            os << ", ";
	}

	return os;
}


/** \typedef OSGVectorInterface::OSGRealReturnType
 *  \brief Used type if the returnvalue must be a real value.
 */

/** \typedef OSGVectorInterface::OSGValueType
 *  \brief Value type
 */

/** \typedef OSGVectorInterface::Inherited
 *  \brief Parent type
 */

/** \fn const char *OSGVectorInterface::getClassname(void)
 *  \brief Classname.
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

template<class OSGValueTypeT, class OSGStorageInterfaceT>
char OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT>::cvsid[] = 
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

template <class OSGValueTypeT, 
          class OSGStorageInterfaceT> inline
OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT>::OSGVectorInterface(
    void)
{
    OSGUInt32 i;

    for(i = 0; i < _iSize; i++)
    {
        _values[i] = OSGTypeConstants<OSGValueTypeT>::getZeroElement();
    }
}

/** \brief Copy Constructor
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT>::OSGVectorInterface(
    const OSGVectorInterface &source)
{
    OSGUInt32 i;

    for(i = 0; i < _iSize; i++)
    {
        _values[i] = source._values[i];
    }
}

/** \brief Constructor which takes a const value array.
 *
 *  Be shure the array size at least as large as the vector size.
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT>::OSGVectorInterface(
    const OSGValueTypeT *pVals)
{
    OSGUInt32 i;

    if(pVals == NULL)
    {
        for(i = 0; i < _iSize; i++)
        {
            _values[i] = OSGTypeConstants<OSGValueTypeT>::getZeroElement();
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

/** \brief Constructor which takes a const value array.
 *
 *  Be shure the array size at least as large as the vector size.
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT>::OSGVectorInterface(
    OSGValueTypeT *pVals)
{
    OSGUInt32 i;

    if(pVals == NULL)
    {
        for(i = 0; i < _iSize; i++)
        {
            _values[i] = OSGTypeConstants<OSGValueTypeT>::getZeroElement();
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
template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT>::OSGVectorInterface(
    const OSGValueTypeT rVal1)
{
    OSGUInt32 i;

    _values[0] = rVal1;

    for(i = 1; i < _iSize; i++)
    {
        _values[i] = OSGTypeConstants<OSGValueTypeT>::getZeroElement();
    }    
}
*/
 
/** \brief Constructor which takes two values, remaining entries will be zero
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT>::OSGVectorInterface(
    const OSGValueTypeT rVal1, 
    const OSGValueTypeT rVal2) :
    
    Inherited(rVal1, rVal2)
{
}

/** \brief Constructor which takes three values, remaining entries will be zero
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT>::OSGVectorInterface(
    const OSGValueTypeT rVal1, 
    const OSGValueTypeT rVal2, 
    const OSGValueTypeT rVal3) :
    
    Inherited(rVal1, rVal2, rVal3)
{
}

/** \brief Constructor which takes four values, remaining entries will be zero
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT>::OSGVectorInterface(
    const OSGValueTypeT rVal1, 
    const OSGValueTypeT rVal2, 
    const OSGValueTypeT rVal3, 
    const OSGValueTypeT rVal4) :

    Inherited(rVal1, rVal2, rVal3, rVal4)
{
}


/** \brief Destructor
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT>::~OSGVectorInterface(
    void)
{
}

/*------------------------- set values -------------------------------*/

/** \brief Euclidean length of the vector 
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT>::OSGRealReturnType 
    OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT>::length(void) const
{
    OSGUInt32 i;

    OSGRealReturnType rTmpVal = _values[0] * _values[0];

    for(i = 1; i < _iSize; i++)
    {
        rTmpVal += _values[i] * _values[i];
    }
    
    return osgsqrt(rTmpVal);
}

/** \brief Changes vector to be of unit length
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
void OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT>::normalize(void)
{
    OSGUInt32 i;

    OSGValueTypeT rLength = length();

    if(osgabs(rLength) < osgEps)
        rLength = OSGTypeConstants<OSGValueTypeT>::getOneElement();
    else
        rLength = OSGTypeConstants<OSGValueTypeT>::getOneElement() / rLength;
     
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

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT> 
    OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT>::cross(
        const OSGVectorInterface &vec) const
{
    OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT> returnValue;

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

/** \brief Calculates the right handed cross-product with a given vector; 
 *  This function is implemented for size 3 vectors only.
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
void OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT>::crossThis(
    const OSGVectorInterface &vec)
{
    if(_iSize >= 3)
    {
        OSGValueTypeT rTmp[2];
    
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

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGValueTypeT OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT>::dot(
    const OSGVectorInterface &vec) const
{
    OSGUInt32 i;

    OSGValueTypeT rTmpVal = _values[0] * vec._values[0];

    for(i = 1; i < _iSize; i++)
    {
        rTmpVal += _values[i] * vec._values[i];
    }
    
    return rTmpVal;
}

/** \brief Returns the angle between this and another vector
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT>::OSGRealReturnType
     OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT>::enclosedAngle(
         const OSGVectorInterface &vec) const
{
    OSGRealReturnType returnValue;

    if(isZero() || vec.isZero())
        returnValue = OSGTypeConstants<OSGRealReturnType>::getZeroElement();
    else
    {
        returnValue  = dot(vec);
        returnValue /= (length() * vec.length());

        if(osgabs(returnValue - 1.) < osgEps)
           returnValue = OSGTypeConstants<OSGRealReturnType>::getZeroElement();
        else if(osgabs(returnValue + 1.) < osgEps)
            returnValue = osgPi;
        else
        {
            returnValue = osgacos(returnValue);
        }
    }
    
    return returnValue;
}

/*------------------------------ math -----------------------------------*/

/** \brief Component wise vector addition
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
void OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT>::operator +=(
    const OSGVectorInterface    &vec)
{
    OSGUInt32 i;

    for(i = 0; i < _iSize; i++)
    {
        _values[i] += vec._values[i];
    }
}

/** \brief Component wise vector substraction
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
void OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT>::operator -=(
    const OSGVectorInterface    &vec)
{
    OSGUInt32 i;

    for(i = 0; i < _iSize; i++)
    {
        _values[i] -= vec._values[i];
    }
}

/** \brief Component wise binary vector addition operator
 */
template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGVectorInterface <OSGValueTypeT, OSGStorageInterfaceT>
    OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT>::operator + (
        const OSGVectorInterface &vec) const
{
	OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT> returnValue;

    OSGUInt32 i;

    for(i = 0; i < OSGStorageInterfaceT::_iSize; i++)
    {
		returnValue[i] = _values[i] + vec[i];
	}

	return returnValue;
}

/** \brief Component wise binary vector subtraction operator
 */
template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGVectorInterface <OSGValueTypeT, OSGStorageInterfaceT>
    OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT>::operator - (
        const OSGVectorInterface &vec) const
{
	OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT> returnValue;


    OSGUInt32 i;

    for(i = 0; i < OSGStorageInterfaceT::_iSize; i++)
    {
		returnValue[i] = _values[i] - vec[i];
	}

	return returnValue;
}


/** \brief Component wise binary scalar multiplication
 */
template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGVectorInterface <OSGValueTypeT, OSGStorageInterfaceT>
    OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT>::operator * (
        const OSGValueTypeT rVal) const
{
	OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT> returnValue;

    OSGUInt32 i;

    for(i = 0; i < OSGStorageInterfaceT::_iSize; i++)
    {
		returnValue[i] = _values[i] * rVal;
	}

	return returnValue;
}

/** \brief Nondestructive unary negation, returns new vector
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT> 
    OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT>::operator -(
        void)
{
    OSGUInt32 i;

    OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT> returnValue;

    for(i = 0; i < _iSize; i++)
    {
        returnValue._values[i] = - _values[i];
    }

    return returnValue;
}

/*------------------------- assignment ----------------------------------*/

/** \brief Assignment operator
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT> &
    OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT>::operator =(
        const OSGVectorInterface &source)
{
	if(this == &source)
		return *this;

    *(static_cast<Inherited *>(this)) = source;

	return *this;
}

/*------------------------- comparison ----------------------------------*/

/** \brief Less than, not implemented
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
bool OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT>::operator < (
    const OSGVectorInterface &other) const
{
    missing;
}

/** \brief Equal operator, using osgEps as the tolerance
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGBool OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT>::operator == (
    const OSGVectorInterface &other) const
{
	return equals(other, osgEps);
}

/** \brief Not eual operator, using osgEps as the tolerance
 */

template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGBool OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT>::operator != (
    const OSGVectorInterface &other) const
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
template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT>
    operator *(const OSGValueTypeT                             val, 
               const OSGVectorInterface<OSGValueTypeT, 
                                        OSGStorageInterfaceT> &vec)
{
	OSGVectorInterface<OSGValueTypeT, OSGStorageInterfaceT> returnValue;

    OSGUInt32 i;

    for(i = 0; i < OSGStorageInterfaceT::_iSize; i++)
    {
		returnValue[i] = vec[i] * val;
	}

	return returnValue;
}

/** \brief Write vector to stream
 */
template <class    OSGValueTypeT, 
          class    OSGStorageInterfaceT> inline
ostream &operator <<(ostream                                  &os,
                     const   OSGVectorInterface<OSGValueTypeT, 
                                                OSGStorageInterfaceT> &obj)
{

    OSGUInt32 i;

    for(i = 0; i < OSGStorageInterfaceT::_iSize; i++)
    {
		os << obj[i];

        if(i != OSGStorageInterfaceT::_iSize - 1)
            os << ", ";
	}

	return os;
}

OSG_END_NAMESPACE



