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


OSG_BEGIN_NAMESPACE


/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/


/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

//---------------------------------------------------------------------------
//   Base Math Functions
//---------------------------------------------------------------------------


/*! @name UInt32 Specializations
 */

/*@{*/

/*! \brief osgispower2
 *  \ingroup BaseMathFunctions
 */

template <> inline 
Bool osgispower2(UInt32 rValue)
{
	// find the lowest 1 bit
    while ( rValue && ! ( rValue & 1 ) )
		rValue >>= 1;

	// shift the 1 bit out
	rValue >>= 1;

	// if another 1 left => not 2^
	if ( rValue )	return false;
	else			return true;
}


/*! \brief osgnextpower2
 *  \ingroup BaseMathFunctions
 */

template <> inline 
UInt32 osgnextpower2(UInt32 rValue)
{
	UInt32 result = 1;

    while ( result < rValue )
		result <<= 1;

	return result;
}

/*@}*/

/*! @name Real32 Specializations
 */

/*@{*/

/*! \brief osgsqrt
 *  \ingroup BaseMathFunctions
 */

template <> inline 
Real32 osgsqrt(const Real32 &rVal)
{
#ifdef OSG_HAS_FLOATMATH
    return sqrtf(rVal);
#else
    return (Real32) sqrt((Real32) rVal);
#endif
}

/*! \brief osgcos
 *  \ingroup BaseMathFunctions
 */

template <> inline
Real32 osgcos(const Real32 &rVal)
{
#ifdef OSG_HAS_FLOATMATH
    return cosf(rVal);
#else
    return (Real32) cos((Real32) rVal);
#endif
}

template <> inline
Real32 osgsin(const Real32 &rVal)
{
#ifdef OSG_HAS_FLOATMATH
    return sinf(rVal);
#else
    return (Real32) sin((Real32) rVal);
#endif
}

/*! \brief osgtan
 *  \ingroup BaseMathFunctions
 */

template <> inline
Real32 osgtan(const Real32 &rVal)
{
#ifdef OSG_HAS_FLOATMATH
    return tanf(rVal);
#else
    return (Real32) tan((Real32) rVal);
#endif
}

/*! \brief osgacos
 *  \ingroup BaseMathFunctions
 */

template <> inline
Real32 osgacos(const Real32 &rVal)
{
#ifdef OSG_HAS_FLOATMATH
    return acosf(rVal);
#else
    return (Real32) acos((Real32) rVal);
#endif
}

/*! \brief osgasin
 *  \ingroup BaseMathFunctions
 */

template <> inline
Real32 osgasin(const Real32 &rVal)
{
#ifdef OSG_HAS_FLOATMATH
    return asinf(rVal);
#else
    return (Real32) asin((Real32) rVal);
#endif
}

/*! \brief osgatan
 *  \ingroup BaseMathFunctions
 */

template <> inline
Real32 osgatan(const Real32 &rVal)
{
#ifdef OSG_HAS_FLOATMATH
    return atanf(rVal);
#else
    return (Real32) atan((Real32) rVal);
#endif
}

/*! \brief osgatan2
 *  \ingroup BaseMathFunctions
 */

template <> inline
Real32 osgatan2(const Real32 &rVal1, const Real32 &rVal2)
{
#ifdef OSG_HAS_FLOATMATH
#ifndef _OSG_HAS_ATANF2__
    return atan2f(rVal1, rVal2);
#else
	return (Real32) atan2((Real32) rVal1, (Real32) rVal2);
#endif
#else
	return (Real32) atan2((Real32) rVal1, (Real32) rVal2);
#endif
}

/*! \brief osgdegree2rad
 *  \ingroup BaseMathFunctions
 */

template <> inline 
Real32 osgdegree2rad(const Real32 &rValue)
{
   return (rValue/360.f) * 2.f * 3.1415926535f;
}

/*! \brief osgrad2degree
 *  \ingroup BaseMathFunctions
 */

template <> inline
Real32 osgrad2degree(const Real32 &rValue)
{
   return (rValue/(2.f * 3.1415926535f)) * 360.f;
}

/*! \brief osgabs
 *  \ingroup BaseMathFunctions
 */

template <> inline 
Real32 osgabs(const Real32 &rValue)
{
#ifdef OSG_HAS_FLOATMATH
    return fabsf(rValue);
#else
    return (Real32) fabs((Real32) rValue);
#endif
}

/*! \brief osgpow
 *  \ingroup BaseMathFunctions
 */

template <> inline 
Real32 osgpow(const Real32 &rValue, const Real32 &rExp)
{
#ifdef OSG_HAS_FLOATMATH
    return powf(rValue, rExp);
#else
    return (Real32) pow((Real32) rValue, (Real32) rExp);
#endif
}

/*! \brief osgfloor
 *  \ingroup BaseMathFunctions
 */

template <> inline 
Real32 osgfloor(const Real32 &rValue)
{
#ifdef OSG_HAS_FLOATMATH
    return floorf(rValue);
#else
    return (Real32) floor((Real32) rValue);
#endif
}

/*! \brief osgMin
 *  \ingroup BaseMathFunctions
 */

template <class TypeT> inline
OSG_BASE_DLLMAPPING TypeT osgMin ( const TypeT &lVal,
																	 const TypeT &rVal)
{
	return ((lVal < rVal) ? lVal : rVal);
}

/*! \brief osgMax
 *  \ingroup BaseMathFunctions
 */

template <class TypeT> inline
OSG_BASE_DLLMAPPING TypeT osgMax ( const TypeT &lVal,
																	 const TypeT &rVal)
{
	return ((lVal > rVal) ? lVal : rVal);
}

/*@}*/

/*! @name Real64 Specializations
 */

/*@{*/

/*! \brief osgsqrt
 *  \ingroup BaseMathFunctions
 */

template <> inline 
Real64 osgsqrt(const Real64 &rVal)
{
    return sqrt(rVal);
}

/*! \brief osgcos
 *  \ingroup BaseMathFunctions
 */

template <> inline
Real64 osgcos(const Real64 &rVal)
{
    return cos(rVal);
}

/*! \brief osgsin
 *  \ingroup BaseMathFunctions
 */

template <> inline
Real64 osgsin(const Real64 &rVal)
{
    return sin(rVal);
}

/*! \brief osgtan
 *  \ingroup BaseMathFunctions
 */

template <> inline
Real64 osgtan(const Real64 &rVal)
{
    return tan(rVal);
}

/*! \brief osgacos
 *  \ingroup BaseMathFunctions
 */

template <> inline
Real64 osgacos(const Real64 &rVal)
{
    return acos(rVal);
}

/*! \brief osgasin
 *  \ingroup BaseMathFunctions
 */

template <> inline
Real64 osgasin(const Real64 &rVal)
{
    return asin(rVal);
}

/*! \brief osgatan
 *  \ingroup BaseMathFunctions
 */

template <> inline
Real64 osgatan(const Real64 &rVal)
{
    return atan(rVal);
}

/*! \brief osgatan2
 *  \ingroup BaseMathFunctions
 */

template <> inline
Real64 osgatan2(const Real64 &rVal1, const Real64 &rVal2)
{
    return atan2(rVal1, rVal2);
}

/*! \brief osgdegree2rad
 *  \ingroup BaseMathFunctions
 */

template <> inline 
Real64 osgdegree2rad(const Real64 &rValue)
{
   return (rValue/360) * 2 * 3.1415926535;
}

/*! \brief osgrad2degree
 *  \ingroup BaseMathFunctions
 */

template <> inline
Real64 osgrad2degree(const Real64 &rValue)
{
   return (rValue/(2 * 3.1415926535)) * 360;
}

/*! \brief osgabs
 *  \ingroup BaseMathFunctions
 */

template <> inline 
Real64 osgabs(const Real64 &rValue)
{
    return fabs(rValue);
}

/*! \brief osgpow
 *  \ingroup BaseMathFunctions
 */

template <> inline 
Real64 osgpow(const Real64 &rValue, const Real64 &rExp)
{
    return pow(rValue, rExp);
}

/*! \brief osgfloor
 *  \ingroup BaseMathFunctions
 */

template <> inline 
Real64 osgfloor(const Real64 &rValue)
{
    return floor(rValue);
}

/*@}*/

/*! @name String Functions 
 */

/*@{*/

/*! \brief copy c strings, allocate new memory using new []
 *  \ingroup BaseFunctions
 */

inline
OSG_BASE_DLLMAPPING void stringDup(const char *szInput, char *&szOutput)
{
    delete [] szOutput;
    szOutput = NULL;

    if(szInput != NULL)
    {
        szOutput = new char[strlen(szInput) + 1];
        strcpy(szOutput, szInput);
    }
}

inline 
OSG_BASE_DLLMAPPING
Int32 stringncmp(const char *string1, const char *string2, size_t count)
{
	return strncmp(string1, string2, count);
}

/*! \brief limited string compare
 *  \ingroup BaseFunctions
 */


inline 
OSG_BASE_DLLMAPPING Int32 stringlen(const char *string1)
{
    return strlen(string1);
}


/*! \brief string compare
 *  \ingroup BaseFunctions
 */

inline 
OSG_BASE_DLLMAPPING Int32 stringcmp(const char *string1, const char *string2)
{
	return strcmp(string1, string2);
}

/*! \brief string case compare
 *  \ingroup BaseFunctions
 */

inline 
OSG_BASE_DLLMAPPING Int32 stringcasecmp(const char *string1, 
                                        const char *string2)
{
#ifndef WIN32
	return strcasecmp(string1, string2);
#else
	return _stricmp(string1, string2);
#endif
}

/*@}*/

inline
OSG_BASE_DLLMAPPING int putenv(char *string)
{
#ifndef WIN32
    return ::putenv(string);
#else
    return ::_putenv(string);
#endif
}

/*! @name Sleep
 */

/*@{*/

inline
OSG_BASE_DLLMAPPING void osgsleep(UInt32 millisecs)
{
#ifdef WIN32
    Sleep(millisecs);
#else
    
    // Rough aproximation, have to find a better way soon (GV)

    if( (millisecs * 1000) > 1000000)
    {
        sleep(millisecs / 1000);
    }
    else
    {
        usleep(millisecs * 1000);
    }
#endif
}

/*@}*/

OSG_END_NAMESPACE




