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

//---------------------------------------------------------
// 	Includes  
//---------------------------------------------------------


#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#include <iomanip>
#else
#include <iostream.h>
#include <iomanip.h>
#endif

#include <strstream>

#include <time.h>

#include "OSGDate.h"

OSG_USING_NAMESPACE

/* enum OSGVecBase::VectorSizeE
 * brief 
*/

/* var OSGVecBase::VectorSizeE OSGVecBase::_iSize
 *
*/

/* const char *OSGVecBase::getClassName(void)
 *  brief Classname
*/

/* var OSGValueTypeT OSGVecBase:: _value[Size];
 * brief value store
*/


/********************************************************/
/**   Types                                            **/
/********************************************************/


/********************************************************/
/**	  Classvariables                                   **/
/********************************************************/


/********************************************************/
/**	  Class methodes  **/
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
void OSGDate::set (unsigned int day, unsigned int month, int year, 
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
void OSGDate::set (const char *string )
{
	if (string && *string) {
    istrstream is(string);
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
bool OSGDate::isLeapYear (void )
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
bool OSGDate::valid (void )
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
void OSGDate::setSystemDate (void )
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
// Function name: OSGDate
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
OSGDate::OSGDate (void )
: _second(0), _minute(0), _hour(0), _day(0), _month(0), _year(0)
{
	return;
}

//--------------------------------------------------------
// Function name: OSGDate
//--------------------------------------------------------
//
//Parameters:
//p: const OSGDate &obj
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
OSGDate::OSGDate (const OSGDate &obj )
: _second(obj._second), _minute(obj._minute), _hour(obj._hour),
  _day(obj._day), _month(obj._month), _year(obj._year)    
{
	return;
}

//--------------------------------------------------------
// Function name: ~OSGDate
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
OSGDate::~OSGDate (void )
{
	return;
}

ostream &OSG::operator << (ostream &outStream, const OSGDate &obj)
{
  return  outStream << setfill('0')
                    << setw(2) << obj._day << '.'
                    << setw(2) << obj._month << '.'
                    << obj._year << ' '
                    << setw(2) << obj._hour << ':'
                    << setw(2) << obj._minute << ':'
                    << setw(2) << obj._second;
}

istream &OSG::operator >>(istream &inStream, OSGDate &obj)
{
  char c;

  return inStream >> obj._day  >> c >> obj._month  >> c >> obj._year
                  >> obj._hour >> c >> obj._minute >> c >> obj._second;
}                                            

/*----------------------access----------------------------*/

/*----------------------properies-------------------------*/

/*----------------------your Category---------------------*/

/*----------------------Operators-------------------------*/

/*

//--------------------------------------------------------
// Function name: ~OSGDate
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
bool operator ==(const OSGDate &v1, const OSGDate &v2)
{
  return ((v1._day == v2._day) &&
          (v1._month == v2._month) &&
          (v1._year == v2._year) &&
          (v1._hour == v2._hour) &&
          (v1._minute == v2._minute) &&
          (v1._second == v2._second));
}

//--------------------------------------------------------
// Function name: ~OSGDate
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
bool operator <(const OSGDate &v1, const OSGDate &v2)
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
// Function name: ~OSGDate
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
// Function name: ~OSGDate
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
