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


#ifndef _OSGDATE_INL_
#define _OSGDATE_INL_
#ifdef  __sgi
#pragma  once 
#endif 



//-------------------------------------------------------
//Includes
//-------------------------------------------------------


#include<OSGBaseTypes.h>

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

  /** set method for attribute second */
  inline void Date::setSecond (unsigned int second)
		{ _second = second; }

  /** get method for attribute second */
	inline unsigned int Date::getSecond (void) 
		{ return _second;}
	
  /** set method for attribute minute */
	inline void Date::setMinute (unsigned int minute)
		{ _minute = minute; }
	
  /** get method for attribute minute */
  inline unsigned int Date::getMinute (void)
		{ return _minute; }

  /** get method for attribute hour */
  inline unsigned int Date::getHour (void)
		{ return _hour; }
	
  /** set method for attribute hour */
  inline void Date::setHour (unsigned int hour)
		{ _hour = hour; }
	
  /** get method for attribute day */
  inline unsigned int Date::getDay (void)
		{ return _day; }
	
  /** set method for attribute day */
  inline void Date::setDay (unsigned int day)
		{ _day = day; }
	
  /** get method for attribute year */
  inline int Date::getYear (void)
		{ return _year; }

  /** set method for attribute year */
  inline void Date::setYear (int year)
		{ _year = year; }

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/
 
OSG_END_NAMESPACE

#endif // DATE_CLASS_DECLARATION
