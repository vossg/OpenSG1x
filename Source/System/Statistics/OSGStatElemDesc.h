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


#ifndef _OSGSTATELEMDESC_H_
#define _OSGSTATELEMDESC_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGBaseTypes.h"
#include "OSGSystemDef.h"

#include "OSGIDString.h"

OSG_BEGIN_NAMESPACE

class StatElemCollector;
class StatElem;

/*! \ingroup baselib
 *  \brief Brief
 *
 *  detailed
 */
 
class OSG_SYSTEMLIB_DLLMAPPING StatElemDescBase
{
  friend class StatCollector;

    /*==========================  PUBLIC  =================================*/
  public:

   /*---------------------------------------------------------------------*/
   /*! \name                    instance                                  */
   /*! \{                                                                 */

    inline  static bool isValidID (Int32 descId);

    inline  static StatElemDescBase *getDesc (Int32 descId);

    static StatElemDescBase *findDescByName (const Char8 *name);

    inline  static Int32 getNumOfDescs(void);

    inline  static const Char8 *getClassname(void);

    static void printAll (void);

    void print(void);

    inline        Int32   getID(void);

    inline  const IDString &getName(void);

    inline  const IDString &getDescription (void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    Constructors                              */
    /*! \{                                                                 */

    StatElemDescBase( const Char8 *name, const Char8 *description);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~StatElemDescBase(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Comparison                                 */
    /*! \{                                                                 */

    bool operator < (const StatElemDescBase &other) const;

    //OSGbool operator == (const CLASSNAME &other) const;
    //OSGbool operator != (const CLASSNAME &other) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:


    /*==========================  PRIVATE  ================================*/
  private:


    // typedef PARENTCLASS Inherited;

    static std::vector<StatElemDescBase*> *_descVec;

    static char cvsid[];


    Int32                _id;

    IDString             _name;

    IDString             _description;

    // prohibit default functions (move to 'public' if you need one)

    // only called by OSGStatCollector friend
    virtual StatElem* createElem(void) = 0;

    StatElemDescBase (const StatElemDescBase &source);
    StatElemDescBase& operator =(const StatElemDescBase &source);

};

template <class Type>
class StatElemDesc : public StatElemDescBase
{
    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                    Constructors                              */
    /*! \{                                                                 */

    StatElemDesc( const Char8 *name, const Char8 *description );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~StatElemDesc(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:


    /*==========================  PRIVATE  ================================*/
  private:


    // typedef PARENTCLASS Inherited;

    static char cvsid[];

    virtual StatElem* createElem(void);

    StatElemDesc (const StatElemDesc &source);
    StatElemDesc& operator =(const StatElemDesc &source);
};

typedef StatElemDescBase *StatElemDescBaseP;

OSG_END_NAMESPACE

#include "OSGStatElemDesc.inl"

#define OSGSTATELEMDESC_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGSTATELEMDESC_H_ */
