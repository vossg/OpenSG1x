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
