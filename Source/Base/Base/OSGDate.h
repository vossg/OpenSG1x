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

#ifndef OSGDATE_CLASS_DECLARATION
#define OSGDATE_CLASS_DECLARATION
#ifdef  __sgi
#pragma  once
#endif

#include <OSGConfig.h>
#include <OSGBase.h>

//#include<OSGBaseTypes.h>

OSG_BEGIN_NAMESPACE

#ifdef WIN32 // Workaround for a bug in Visual C++ 6.0
class Date;
OSG_BASE_DLLMAPPING bool          operator ==(const Date &v1, const Date &v2);
OSG_BASE_DLLMAPPING bool          operator < (const Date &v1, const Date &v2);

OSG_BASE_DLLMAPPING std::ostream &operator <<(      std::ostream & os, 
                                              const Date         &obj);
OSG_BASE_DLLMAPPING std::istream &operator >>(      std::istream &is, 
                                                    Date         &obj);
#endif

/** Date & Time.
*
* @autor jBehr, Wed Oct 27 13:16:07
*/

class OSG_BASE_DLLMAPPING Date
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    Date (void);
    Date (const Date &obj);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Date (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Access                                     */
    /*! \{                                                                 */

    inline void         setSecond     (unsigned int second);
    inline unsigned int getSecond     (void);
    inline void         setMinute     (unsigned int minute);
    inline unsigned int getMinute     (void);
    inline unsigned int getHour       (void);
    inline void         setHour       (unsigned int hour);
    inline unsigned int getDay        (void);
    inline void         setDay        (unsigned int day);
    inline int          getYear       (void);
    inline void         setYear       (int year);
           void         clear         (void) ;
           void         setSystemDate (void);
           void         set           (const char *string);
    bool                isLeapYear    (void);
    bool                valid         (void);
           void         set (unsigned int day, unsigned int month, int year,
                             unsigned int hour = 0, unsigned int minute = 0,
                             unsigned int second = 0 );
    

    /*! \}                                                                 */
    /*===========================  PRIVATE  ===============================*/    
  private:

    unsigned int _second;
    unsigned int _minute;
    unsigned int _hour;
    unsigned int _day;
    unsigned int _month;
    unsigned int _year;
    
    /*==========================  PUBLIC  =================================*/    
  public:
         
    /*---------------------------------------------------------------------*/
    /*! \name                   Operators                                  */
    /*! \{                                                                 */
         
    friend bool          operator ==(const Date &v1, const Date &v2);
    friend bool          operator < (const Date &v1, const Date &v2);

    friend std::ostream &operator <<(      std::ostream &os, 
                                     const Date         &obj);
    friend std::istream &operator >>(      std::istream &is, 
                                           Date         &obj);
    
    /*! \}                                                                 */
};

typedef Date* DateP;

std::ostream &operator <<(std::ostream &outStream, const Date &obj);
std::istream &operator >>(std::istream &inStream,        Date &obj);

OSG_END_NAMESPACE

#include <OSGDate.inl>

#endif // DATE_CLASS_DECLARATION
