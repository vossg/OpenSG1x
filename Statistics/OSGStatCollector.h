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


#ifndef _OSGSTATCOLLECTOR_H_
#define _OSGSTATCOLLECTOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OSGConfig.h>
#include <OSGSystemDef.h>

#include <OSGBaseTypes.h>
#include <OSGFieldDataType.h>
#include <OSGSField.h>
#include <OSGMField.h>

#include <OSGStatElemDesc.h>

OSG_BEGIN_NAMESPACE

class StatElem;
class StatElemDescBase;

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

    inline  Bool     isValidID     (Int32 id);

            void     clearElems    (void);

            void     reset         (void);

    inline  StatElem *getElem      (Int32 id, Bool create = true);

    inline  StatElem *getElem      (StatElemDescBase &desc, Bool create = true);


    template <class T> 
    inline  T        *getElem      (StatElemDesc<T> &desc, Bool create = true);


            void      putToString  (string &outVal) const;
     
            Bool      getFromString(const Char8 *&inVal);
            
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructor                                 */
    /*! \{                                                                 */

    StatCollector(void);

    StatCollector(const StatCollector &source);

    static StatCollector *create(void);

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

    vector<StatElem*> _elemVec;

    // prohibit default functions (move to 'public' if you need one)

    StatCollector& operator =(const StatCollector &source);
};

typedef StatCollector *StatCollectorP;


/*! \brief StatCollector field traits 
*/

template <>
struct FieldDataTraits<StatCollector> : 
    public FieldTraitsRecurseBase<StatCollector>
{
    static DataType       _type;

    enum                  { StringConvertable = ToStringConvertable | 
                                                FromStringConvertable    };

    static DataType       &getType      (void) { return _type;          }

    static Char8          *getSName     (void) { return "SFStatCollector"; }
    static Char8          *getMName     (void) { return "MFStatCollector"; }

    static StatCollector getDefault   (void) { return StatCollector();   }

    static Bool            getFromString(      StatCollector  &outVal,
                                         const Char8         *&inVal)
    {
        return outVal.getFromString(inVal);
    }

    static void            putToString  (const StatCollector &inVal,
                                               string        &outVal)
    {
        inVal.putToString(outVal);
    }
};

/*! \brief StatCollector fields
*/

//! SFStatCollector
//! \ingroup SingleFields

typedef SField<StatCollector> SFStatCollector;

#ifndef OSG_COMPILEPARTICLEBSPINST
#if defined(__sgi)

#pragma do_not_instantiate SField<StatCollector>::_fieldType

#else

OSG_DLLEXPORT_DECL1(SField, StatCollector, OSG_SYSTEMLIB_DLLTMPLMAPPING)

#endif
#endif


OSG_END_NAMESPACE

#include <OSGStatCollector.inl>

#define OSGSTATCOLLECTOR_HEADER_CVSID "@(#)$Id:$"

#endif /* _OSGSTATCOLLECTOR_H_ */
