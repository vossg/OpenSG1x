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

/*! \brief Manager for Stat elements, see \ref PageSystemStatistics for details.
*/
class OSG_SYSTEMLIB_DLLMAPPING StatCollector 
{

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

    
    inline  UInt32   getNumOfElems (void) const;

            void     refitElemNum  (void);

            void     clearElems    (void);

    inline  bool     isValidID     (Int32 elemId) const;

            void     reset         (void);

    inline  StatElem *getElem      (Int32 elemId) const;

    inline  StatElem *getElem      (Int32 elemId, bool create = true);

    inline  StatElem *getElem      (StatElemDescBase &desc, bool create = true);


    template <class T> 
    inline  T        *getElem      (StatElemDesc<T> &desc, bool create = true);


            void      putToString  (std::string &outVal) const;
     
            bool      getFromString(const Char8 *&inVal);

            bool      getValue     (std::string &name, Real64 &val);
            
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Constructor                                 */
    /*! \{                                                                 */

    StatCollector(void);

    StatCollector(const StatCollector &source);

    static StatCollector *create(void);

    const StatCollector& operator =(const StatCollector &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructor                                 */
    /*! \{                                                                 */

    virtual ~StatCollector(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                  Comparison                                  */
    /*! \{                                                                 */

         bool operator <  (const StatCollector &other) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Operators                                */
    /*! \{                                                                 */

          StatCollector  operator +  (const StatCollector &other);
          StatCollector &operator += (const StatCollector &other);

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/
  protected:

    /*==========================  PRIVATE  ================================*/
  private:

    std::vector<StatElem*> _elemVec;
};

typedef StatCollector *StatCollectorP;


#if !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)

/*! \ingroup GrpSystemFieldTraits
 */
#if !defined(OSG_DOC_DEV_TRAITS)
/*! \hideinhierarchy */
#endif

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

    static bool            getFromString(      StatCollector  &outVal,
                                         const Char8         *&inVal)
    {
        return outVal.getFromString(inVal);
    }

    static void            putToString  (const StatCollector &inVal,
                                               std::string   &outVal)
    {
        inVal.putToString(outVal);
    }

};

#if !defined(OSG_DOC_DEV_TRAITS)
/*! \class FieldTraitsRecurseBase<StatCollector> */
/*! \hideinhierarchy                             */
#endif

#endif // !defined(OSG_DO_DOC) || (OSG_DOC_LEVEL >= 3)


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_FIELD_TYPEDEFS) 
/*! \ingroup GrpSystemFieldSingle */

typedef SField<StatCollector> SFStatCollector;
#endif

#ifndef OSG_COMPILESTATCOLLECTORINST
OSG_DLLEXPORT_DECL1(SField, StatCollector, OSG_SYSTEMLIB_DLLTMPLMAPPING)
#endif


OSG_END_NAMESPACE

#include <OSGStatCollector.inl>

#define OSGSTATCOLLECTOR_HEADER_CVSID "@(#)$Id:$"

#endif /* _OSGSTATCOLLECTOR_H_ */
