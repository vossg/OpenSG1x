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
class OSGDate;
bool operator==(const OSGDate &v1, const OSGDate &v2);
bool operator< (const OSGDate &v1, const OSGDate &v2);
ostream& operator<< (ostream & os, const OSGDate &obj);
istream& operator>> (istream & is, OSGDate &obj);
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

class OSGDate 
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
  OSGDate (void);

  /** Copy Constructor */
  OSGDate (const OSGDate &obj);

  /** Destructor */
  virtual ~OSGDate (void);

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
  friend bool operator == (const OSGDate &v1,const OSGDate &v2);
  
  /** lower comparison operator */
  friend bool operator < (const OSGDate &v1,const OSGDate &v2);
  
  /** write values from stream */
  friend ostream &operator << (ostream &os, const OSGDate &obj);
  
  /** read value from stream */
  friend istream &operator >> (istream &is, OSGDate &obj);

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

typedef OSGDate* OSGDateP;

ostream &operator << (ostream &outStream, const OSGDate &obj);
istream &operator >> (istream &inStream,        OSGDate &obj);

OSG_END_NAMESPACE

#endif // OSGDATE_CLASS_DECLARATION
