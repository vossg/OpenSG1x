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


#ifndef _OSGSTATINTELEM_H_
#define _OSGSTATINTELEM_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBaseTypes.h>
#include <OSGSystemDef.h>

#include <OSGStatElem.h>

OSG_BEGIN_NAMESPACE

class StatElemDescBase;

/*! \ingroup baselib
 *  \brief Brief
 *
 *  detailed
 */

class OSG_SYSTEMLIB_DLLMAPPING StatIntElem : public StatElem {

     /*==========================  PUBLIC  =================================*/
 public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */
    
    static const char *getClassname(void) { return "StatIntElem"; }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    your_category                             */
    /*! \{                                                                 */
    
    static StatElem *create ( StatElemDescBase *desc );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    instance                                  */
    /*! \{                                                                 */
   
    inline void set (Int32 value);

    inline Int32 get (void);

    inline void add (Int32 v);
    
    inline void sub (Int32 v);

    inline void reset (void);

    inline void inc (void);

    inline void dec (void);

    virtual void putToString(string &str, const char *format = NULL);

    virtual bool getFromString(const Char8 *&inVal);

    virtual ~StatIntElem(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   comparison                                 */
    /*! \{                                                                 */
 
    bool operator < (const StatIntElem &other) const;
    
    //OSGbool operator == (const StatIntElem &other) const;
    //OSGbool operator != (const StatIntElem &other) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    StatIntElem ( StatElemDescBase *desc );

    /*! \}                                                                 */
    /*=========================  PRIVATE    ===============================*/
  private:

    typedef StatElem Inherited;

    static char cvsid[];
    
    Int32 _value;

    StatIntElem(const StatIntElem &source);

    StatIntElem& operator =(const StatIntElem &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef StatIntElem *StatIntElemP;

OSG_END_NAMESPACE

#include <OSGStatIntElem.inl>

#define OSGSTATINTELEM_HEADER_CVSID "@(#)$Id:$"

#endif /* _OSGSTATINTELEM_H_ */
