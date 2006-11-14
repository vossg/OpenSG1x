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


#ifndef _STATINTONCEELEM_H_
#define _STATINTONCEELEM_H_
#ifdef __sgi
#pragma once
#endif


#include "OSGConfig.h"
#include "OSGBaseTypes.h"
#include "OSGSystemDef.h"

#include "OSGStatElem.h"

#include "OSGTime.h"


#ifdef OSG_STL_HAS_HASH_MAP
#ifdef OSG_HASH_MAP_AS_EXT
#include <ext/hash_set>
#else
#include <hash_set>
#endif
#else
#include <set>
#endif

OSG_BEGIN_NAMESPACE

class StatElemDescBase;

/*! \brief Time Statistics element, see \ref PageSystemStatistics for details.
*/
class OSG_SYSTEMLIB_DLLMAPPING StatIntOnceElem : public StatElem 
{

    /*==========================  PUBLIC  =================================*/
 public:

#ifdef OSG_STL_HAS_HASH_MAP
    typedef OSG_STDEXTENSION_NAMESPACE::hash_set< UInt32 > IdHash;
#else
    typedef std::set< UInt32 > IdHash;
#endif
    
    /*---------------------------------------------------------------------*/
    /*! \name                    Class Get                                 */
    /*! \{                                                                 */
    
    static const char *getClassname(void) { return "StatIntOnceElem"; }

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    your_category                             */
    /*! \{                                                                 */
 
    static StatElem *create ( StatElemDescBase *desc );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    instance                                  */
    /*! \{                                                                 */

    virtual void        reset        (void);

    inline  void        add          (UInt32 contributorId, Int32 v);

    inline  void        sub          (UInt32 contributorId, Int32 v);

    inline  void        inc          (UInt32 contributorId);

    inline  void        dec          (UInt32 contributorId);

    inline  Int32       get          (void) const;
        
    virtual void        putToString  (std::string &str, 
                                      const char *format = NULL) const;
 
    virtual bool        getFromString(const Char8 *&inVal);

    virtual Real64      getValue     (void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                    comparison                                */
    /*! \{                                                                 */

    bool operator < (const StatIntOnceElem &other) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Creation                                   */
    /*! \{                                                                 */

    virtual StatElem *clone(void) const;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Operators                                */
    /*! \{                                                                 */

    virtual StatElem &operator += (const StatElem &other);

    /*! \}                                                                 */

    /*=========================  PROTECTED  ===============================*/
 protected:

    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */
  
    StatIntOnceElem(StatElemDescBase *desc);

    virtual ~StatIntOnceElem(void); 

    /*! \}                                                                 */
    /*=========================  PRIVATE    ===============================*/
 private:

    typedef StatElem Inherited;

    Int32   _value;
    
    IdHash  _ids;

    StatIntOnceElem            (const StatIntOnceElem &source);
  
    StatIntOnceElem& operator =(const StatIntOnceElem &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef StatIntOnceElem *StatIntOnceElemP;

OSG_END_NAMESPACE

#include "OSGStatIntOnceElem.inl"

#define OSGSTATINTONCEELEM_HEADER_CVSID "@(#)$Id: OSGStatIntOnceElem.h,v 1.3 2006/11/14 13:45:57 pdaehne Exp $"

#endif /* _STATINTONCEELEM_H_ */
