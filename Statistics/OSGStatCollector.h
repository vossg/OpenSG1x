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


#ifndef _STATCOLLECTOR_H_
#define _STATCOLLECTOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBaseTypes.h>
#include <OSGSystemDef.h>

#include <OSGStatElemDesc.h>

OSG_BEGIN_NAMESPACE

class StatElem;
class StatElemDesc;


/*! \ingroup baselib
 *  \brief Brief
 *
 *  detailed
 */

class OSG_SYSTEMLIB_DLLMAPPING StatCollector {

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */

    static const char *getClassname(void) { return "StatCollector"; }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Instance                                 */
    /*! \{                                                                 */

    inline  UInt32   getNumOfElems (void);

    inline  Bool     isValidID     (Int32 ID);

    inline  StatElem *getElem      (Int32 ID, Bool create = true);

    inline  StatElem *getElem      (StatElemDesc &desc, Bool create = true );


    template <class T> 
    inline  T        *getElem      (Int32 id, T *q=0);

    template <class T> 
    inline  T        *getElem      (StatElemDesc &desc, T *q=0);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructor                                 */
    /*! \{                                                                 */

    StatCollector(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~StatCollector(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Comparison                                  */
    /*! \{                                                                 */

         Bool operator <  (const StatCollector &other) const;

    //OSGBool operator == (const StatCollector &other) const;
    //OSGBool operator != (const StatCollector &other) const;

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/
  protected:

    /*==========================  PRIVATE  ================================*/
  private:


    //typedef PARENTCLASS Inherited;

    static char cvsid[];

    vector<StatElem*> _elemVec;

    // prohibit default functions (move to 'public' if you need one)

    StatCollector            (const StatCollector &source);
    StatCollector& operator =(const StatCollector &source);
};

typedef StatCollector *StatCollectorP;


OSG_END_NAMESPACE

#include <OSGStatCollector.inl>

#endif /* _STATCOLLECTOR_H_ */
