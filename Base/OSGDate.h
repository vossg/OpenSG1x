/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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

#ifndef OSGDATE_CLASS_DECLARATION
#define OSGDATE_CLASS_DECLARATION
#ifdef  __sgi
#pragma  once 
#endif 



//-------------------------------------------------------
//Includes
//-------------------------------------------------------


#include<OSGBaseTypes.h>

OSG_BEGIN_NAMESPACE

//-------------------------------------------------------
//Forward References	 
//-------------------------------------------------------


#ifdef WIN32 // Workaround for a bug in Visual C++ 6.0
class Date;
bool operator==(const Date &v1, const Date &v2);
bool operator< (const Date &v1, const Date &v2);
ostream& operator<< (ostream & os, const Date &obj);
istream& operator>> (istream & is, Date &obj);
#endif


//-------------------------------------------------------
//Types		 
//-------------------------------------------------------


//-------------------------------------------------------
//Class 	   
//-------------------------------------------------------


/** Date & Time.
*
* @autor jBehr, Wed Oct 27 13:16:07
*/

class OSG_DLLEXPORT Date 
{

public:

//-------------------------------------------------------
//enums   
//-------------------------------------------------------


//-------------------------------------------------------
//types 
//-------------------------------------------------------


//-------------------------------------------------------
//class functions 
//-------------------------------------------------------


  /** Default Constructor */
  Date (void);

  /** Copy Constructor */
  Date (const Date &obj);

  /** Destructor */
  virtual ~Date (void);

  /** set method for attribute second */
  inline void setSecond (unsigned int second)
		{ _second = second; }

  /** get method for attribute second */
	inline unsigned int getSecond (void) 
		{ return _second;}
	
  /** set method for attribute minute */
	inline void setMinute (unsigned int minute)
		{ _minute = minute; }
	
  /** get method for attribute minute */
  inline unsigned int getMinute (void)
		{ return _minute; }

  /** get method for attribute hour */
  inline unsigned int getHour (void)
		{ return _hour; }
	
  /** set method for attribute hour */
  inline void setHour (unsigned int hour)
		{ _hour = hour; }
	
  /** get method for attribute day */
  inline unsigned int getDay (void)
		{ return _day; }
	
  /** set method for attribute day */
  inline void setDay (unsigned int day)
		{ _day = day; }
	
  /** get method for attribute year */
  inline int getYear (void)
		{ return _year; }

  /** set method for attribute year */
  inline void setYear (int year)
		{ _year = year; }
	
  /** cleares all entires */
  void clear (void) 
		{ set(0,0,0,0,0,0); }

  /** set the object with current system date */
  void setSystemDate (void);

  /** set all elements at once */
  void set (unsigned int day, unsigned int month, int year, 
    	    	unsigned int hour = 0, unsigned int minute = 0,  
						unsigned int second = 0 );

  /** check if it is a leap year */
  void set (const char *string);

  /** check if year is leap year */
  bool isLeapYear (void);

  /** check if the date valid */
  bool valid (void);

protected:

//-------------------------------------------------------
//enums 
//-------------------------------------------------------


//-------------------------------------------------------
//types 	 
//-------------------------------------------------------


//-------------------------------------------------------
//class Variables  
//-------------------------------------------------------


//-------------------------------------------------------
//class functions  
//-------------------------------------------------------


//-------------------------------------------------------
//instance Variables  
//-------------------------------------------------------


//-------------------------------------------------------
//instance functions  	       
//-------------------------------------------------------


private:

//-------------------------------------------------------
//enums    		 
//-------------------------------------------------------


//-------------------------------------------------------
//types 
//-------------------------------------------------------



  /** holds the second */
  unsigned int _second;

  /** holds the minute */
  unsigned int _minute;

  /** holds the hour */
  unsigned int _hour;

  /** holds the day */
  unsigned int _day;

	/** holds the month */
	unsigned int _month;

  /** holds the year */
  unsigned int _year;

//-------------------------------------------------------
//friend Classes   
//-------------------------------------------------------


//-------------------------------------------------------
//friend functions 
//-------------------------------------------------------

 public:

  /** equal comparison operator */
  friend bool operator == (const Date &v1,const Date &v2);
  
  /** lower comparison operator */
  friend bool operator < (const Date &v1,const Date &v2);
  
  /** write values from stream */
  friend ostream &operator << (ostream &os, const Date &obj);
  
  /** read value from stream */
  friend istream &operator >> (istream &is, Date &obj);

//-------------------------------------------------------
//class Variables 
//-------------------------------------------------------


//-------------------------------------------------------
//class functions
//-------------------------------------------------------


//-------------------------------------------------------
//instance Variables  
//-------------------------------------------------------


//-------------------------------------------------------
//instance functions   
//-------------------------------------------------------


};

typedef Date* DateP;

ostream &operator << (ostream &outStream, const Date &obj);
istream &operator >> (istream &inStream,        Date &obj);

OSG_END_NAMESPACE

#endif // OSGDATE_CLASS_DECLARATION
