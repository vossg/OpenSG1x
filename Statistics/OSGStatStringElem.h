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


#ifndef _OSGSTATSTRINGTELEM_H_
#define _OSGSTATSTRINGELEM_H_
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

class OSG_SYSTEMLIB_DLLMAPPING StatStringElem : public StatElem {

     /*==========================  PUBLIC  =================================*/
 public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */
    
    static const char *getClassname(void) { return "StatStringElem"; }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    your_category                             */
    /*! \{                                                                 */
    
    static StatElem *create ( StatElemDescBase *desc );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    instance                                  */
    /*! \{                                                                 */

    virtual ~StatStringElem(void); 
   
    inline void set(string value);

    inline void reset(void);

    virtual void putToString(string &str, const char *format = NULL);

    virtual bool getFromString(const Char8 *&inVal);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   comparison                                 */
    /*! \{                                                                 */
 
    bool operator < (const StatStringElem &other) const;
    
    //OSGbool operator == (const StatStringElem &other) const;
    //OSGbool operator != (const StatStringElem &other) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    StatStringElem ( StatElemDescBase *desc );

    /*! \}                                                                 */
    /*=========================  PRIVATE    ===============================*/
  private:

    typedef StatElem Inherited;

    static char cvsid[];
    
    string _value;

    StatStringElem(const StatStringElem &source);

    StatStringElem& operator =(const StatStringElem &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef StatStringElem *StatStringElemP;

OSG_END_NAMESPACE

#include <OSGStatStringElem.inl>

#define OSGSTATSTRINGELEM_HEADER_CVSID "@(#)$Id: OSGStatStringElem.h,v 1.1 2002/03/19 17:46:17 dirk Exp $"

#endif /* _OSGSTATSTRINGELEM_H_ */
