/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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


#ifndef _STATTIMEELEM_H_
#define _STATTIMEELEM_H_
#ifdef __sgi
#pragma once
#endif


#include <OSGBaseTypes.h>
#include <OSGSystemDef.h>

#include <OSGStatElem.h>

#include <OSGTime.h>

OSG_BEGIN_NAMESPACE


/*! \ingroup baselib
 *  \brief Brief
 *
 *  detailed
 */

class StatElemDescBase;

class OSG_SYSTEMLIB_DLLMAPPING StatTimeElem : public StatElem {

    /*==========================  PUBLIC  =================================*/
 public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */
    
    static const char *getClassname(void) { return "StatTimeElem"; }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    your_category                             */
    /*! \{                                                                 */
 
    static StatElem *create ( StatElemDescBase *desc );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    instance                                  */
    /*! \{                                                                 */

    inline void reset(void);
    
    inline const Time &start(void);
      
    inline const Time &stop(void);

    inline const Time & getTime(void);
        
    virtual void putToString(std::string &str, const char *format = NULL);

    virtual bool getFromString(const Char8 *&inVal);

    virtual Real64 getValue(void);

    virtual ~StatTimeElem(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    comparison                                */
    /*! \{                                                                 */

    bool operator < (const StatTimeElem &other) const;
    
    //OSGbool operator == (const StatTimeElem &other) const;
    //OSGbool operator != (const StatTimeElem &other) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
 protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
  
    StatTimeElem ( StatElemDescBase *desc );

    /*! \}                                                                 */
    /*=========================  PRIVATE    ===============================*/
 private:

    typedef StatElem Inherited;

    static char cvsid[];

    Time _time;

    StatTimeElem            (const StatTimeElem &source);
  
    StatTimeElem& operator =(const StatTimeElem &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef StatTimeElem *StatTimeElemP;

OSG_END_NAMESPACE

#include <OSGStatTimeElem.inl>

#define OSGSTATTIMEELEM_HEADER_CVSID "@(#)$Id:$"

#endif /* _STATTIMEELEM_H_ */
