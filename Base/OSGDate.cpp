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

//---------------------------------------------------------
//  Includes
//---------------------------------------------------------


//#include <stdlib.h>
//#include <stdio.h>

//#include "OSGConfig.h"

#include <iostream>
#include <iomanip>
//#include <strstream>

#include <time.h>

#include "OSGDate.h"

OSG_USING_NAMESPACE

/* enum VecBase::VectorSizeE
 * brief
*/

/* var VecBase::VectorSizeE VecBase::_iSize
 *
*/

/* const char *VecBase::getClassName(void)
 *  brief Classname
*/

/* var ValueTypeT VecBase:: _value[Size];
 * brief value store
*/


/********************************************************/
/**   Types                                            **/
/********************************************************/


/********************************************************/
/**   Classvariables                                   **/
/********************************************************/


/********************************************************/
/**   Class methodes  **/
/********************************************************/


//--------------------------------------------------------
// Function name: set
//--------------------------------------------------------
//
//Parameters:
//p: unsigned int day, unsigned int month, int year, unsigned int hour=0,unsigned int minute=0,  unsigned int second=0
//GlobalVars:
//g:
//Returns:
//r:void
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: set all elements at once
//SeeAlso:
//s:
//
//--------------------------------------------------------
void Date::set (unsigned int day,  unsigned int month,  int year,
                unsigned int hour, unsigned int minute, unsigned int sec  )
{
    _day = day;
    _month = month;
    _year = year;
    _hour = hour;
    _minute = minute;
    _second = sec;
}

//--------------------------------------------------------
// Function name: set
//--------------------------------------------------------
//
//Parameters:
//p: const char *string
//GlobalVars:
//g:
//Returns:
//r:void
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: check if it is a leap year
//SeeAlso:
//s:
//
//--------------------------------------------------------
void Date::set (const char *string )
{
    if (string && *string)
    {
//        istrstream is(string);
        // is >> *this;
    }
}

//--------------------------------------------------------
// Function name: isLeapYear
//--------------------------------------------------------
//
//Parameters:
//p: void
//GlobalVars:
//g:
//Returns:
//r:bool
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d:
//SeeAlso:
//s:
//
//--------------------------------------------------------
bool Date::isLeapYear (void )
{
    if (_year & 3)
        return false;
    if ((_year % 100) || !(_year % 400))
        return true;
    return false;
}

//--------------------------------------------------------
// Function name: valid
//--------------------------------------------------------
//
//Parameters:
//p: void
//GlobalVars:
//g:
//Returns:
//r:bool
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: check if the date valid
//SeeAlso:
//s:
//
//--------------------------------------------------------
bool Date::valid (void )
{
    static const unsigned int daysPerMonth[12] =
    { 31, 28, 31, 30, 31, 30, 30, 31, 30, 31, 30, 31 };

    if ((_hour > 23) || (_minute > 59) || (_second > 59))
        return false;
    if ((_month < 1) || (_day < 1) || (_month > 12))
        return false;
    if (_day <= daysPerMonth[_month - 1])
        return true;
    if ((_month == 2) && (_day == 29))
        return isLeapYear();
    return false;
}

/********************************************************/
/** public                                             **/
/********************************************************/


//--------------------------------------------------------
// Function name: getSystemDate
//--------------------------------------------------------
//
//Parameters:
//p: void
//GlobalVars:
//g:
//Returns:
//r:void
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: set the object with current system date
//SeeAlso:
//s:
//
//--------------------------------------------------------
void Date::setSystemDate (void )
{
    time_t clock;
    struct tm *tm_time;

    time(&clock);
    tm_time = localtime(&clock);

    _second = tm_time->tm_sec;
    _minute = tm_time->tm_min;
    _hour = tm_time->tm_hour;
    _day = tm_time->tm_mday;
    _month = tm_time->tm_mon + 1;
    _year = tm_time->tm_year + 1900;
}

//--------------------------------------------------------
// Function name: Date
//--------------------------------------------------------
//
//Parameters:
//p: void
//GlobalVars:
//g:
//Returns:
//r:
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: Default Constructor
//SeeAlso:
//s:
//
//---------------------------------------------------------
Date::Date (void )
: _second(0), _minute(0), _hour(0), _day(0), _month(0), _year(0)
{
    return;
}

//--------------------------------------------------------
// Function name: Date
//--------------------------------------------------------
//
//Parameters:
//p: const Date &obj
//GlobalVars:
//g:
//Returns:
//r:
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: Copy Constructor
//SeeAlso:
//s:
//
//---------------------------------------------------------
Date::Date (const Date &obj )
: _second(obj._second), _minute(obj._minute), _hour(obj._hour),
  _day(obj._day), _month(obj._month), _year(obj._year)
{
    return;
}

//--------------------------------------------------------
// Function name: ~Date
//--------------------------------------------------------
//
//Parameters:
//p: void
//GlobalVars:
//g:
//Returns:
//r:
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: Destructor
//SeeAlso:
//s:
//
//---------------------------------------------------------
Date::~Date (void )
{
    return;
}

ostream &OSG::operator << (ostream &outStream, const Date &obj)
{
  return  outStream << setfill('0')
                    << setw(2) << obj._day << '.'
                    << setw(2) << obj._month << '.'
                    << obj._year << ' '
                    << setw(2) << obj._hour << ':'
                    << setw(2) << obj._minute << ':'
                    << setw(2) << obj._second;
}

#if 0

istream &OSG::operator >>(istream &inStream, Date &obj)
{
  char c;

  return inStream >> obj._day  >> c >> obj._month  >> c >> obj._year
                  >> obj._hour >> c >> obj._minute >> c >> obj._second;
}
#endif


/*----------------------access----------------------------*/

/*----------------------properies-------------------------*/

/*----------------------your Category---------------------*/

/*----------------------Operators-------------------------*/

/*

//--------------------------------------------------------
// Function name: ~Date
//--------------------------------------------------------
//
//Parameters:
//p: void
//GlobalVars:
//g:
//Returns:
//r:
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: Destructor
//SeeAlso:
//s:
//
//---------------------------------------------------------
bool operator ==(const Date &v1, const Date &v2)
{
  return ((v1._day == v2._day) &&
          (v1._month == v2._month) &&
          (v1._year == v2._year) &&
          (v1._hour == v2._hour) &&
          (v1._minute == v2._minute) &&
          (v1._second == v2._second));
}

//--------------------------------------------------------
// Function name: ~Date
//--------------------------------------------------------
//
//Parameters:
//p: void
//GlobalVars:
//g:
//Returns:
//r:
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: Destructor
//SeeAlso:
//s:
//
//---------------------------------------------------------
bool operator <(const Date &v1, const Date &v2)
{
    if (v1._year < v2._year)
        return true;
    if (v1._year > v2._year)
        return false;

    // v1._year == v2._year

    if (v1._month < v2._month)
        return true;
    if (v1._month > v2._month)
        return false;

    // v1._month == v2._month

    if (v1._day < v2._day)
        return true;
    if (v1._day > v2._day)
        return false;

    // v1._day == v2._day

    if (v1._hour < v2._hour)
        return true;
    if (v1._hour > v2._hour)
        return false;

    // v1._hour == v2._hour

    if (v1._minute < v2._minute)
        return true;
    if (v1._minute > v2._minute)
        return false;

    // v1._minute == v2._minute

    if (v1._second < v2._second)
        return true;
    return false;
}

//--------------------------------------------------------
// Function name: ~Date
//--------------------------------------------------------
//
//Parameters:
//p: void
//GlobalVars:
//g:
//Returns:
//r:
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: Destructor
//SeeAlso:
//s:
//
//---------------------------------------------------------

//--------------------------------------------------------
// Function name: ~Date
//--------------------------------------------------------
//
//Parameters:
//p: void
//GlobalVars:
//g:
//Returns:
//r:
// Caution
//c:
//Assumations:
//a:
//Describtions:
//d: Destructor
//SeeAlso:
//s:
//
//---------------------------------------------------------

*/
