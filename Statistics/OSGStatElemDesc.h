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


#ifndef _STATELEMDESC_H_
#define _STATELEMDESC_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGBaseTypes.h>
#include <OSGSystemDef.h>

#include <OSGIDString.h>

OSG_BEGIN_NAMESPACE

class StatElemCollector;
class StatElemDesc;
class StatElem;

typedef StatElem * (*CreateStatElemMethod) ( StatElemDesc *desc );

/*! \ingroup baselib
 *  \brief Brief
 *
 *  detailed
 */

class OSG_SYSTEMLIB_DLLMAPPING StatElemDesc
{
  friend class StatCollector;

    /*==========================  PUBLIC  =================================*/
  public:

   /*---------------------------------------------------------------------*/
   /*! \name                    instance                                  */
   /*! \{                                                                 */

    inline  static Bool isValidID (Int32 ID);

    inline  static StatElemDesc *getDesc (Int32 ID);

    static StatElemDesc *findDescByName (const Char8 *name);

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

    StatElemDesc( const Char8 *name, const Char8 *description,
                  CreateStatElemMethod createMethod );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~StatElemDesc(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Comparison                                 */
    /*! \{                                                                 */

         Bool operator < (const StatElemDesc &other) const;

    //OSGBool operator == (const CLASSNAME &other) const;
    //OSGBool operator != (const CLASSNAME &other) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:


    /*==========================  PRIVATE  ================================*/
  private:


    // typedef PARENTCLASS Inherited;

    static vector<StatElemDesc*> *_descVec;

    static char cvsid[];


    Int32                _ID;

    IDString             _name;

    IDString             _description;

    CreateStatElemMethod _createMethod;

    // prohibit default functions (move to 'public' if you need one)

    // only called by OSGStatCollector friend
    inline StatElem* createElem ( void );

    StatElemDesc (const StatElemDesc &source);
    StatElemDesc& operator =(const StatElemDesc &source);
};

typedef StatElemDesc *StatElemDescP;

OSG_END_NAMESPACE

#include <OSGStatElemDesc.inl>

#endif /* _CLASSNAME_H_ */
