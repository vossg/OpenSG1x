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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGSystemDef.h>

#include <OSGStatElemDesc.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class StatElem;
class StatElemDesc;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup baselib
 *  \brief Brief
 *
 *  detailed
 */

class OSG_SYSTEMLIB_DLLMAPPING StatCollector {

  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "StatCollector"; }
 
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

		inline
			UInt32 getNumOfElems (void) 
			{ return _elemVec.size(); }

    inline
      Bool isValidID (Int32 ID) 
      { return ((ID >= 0) && (ID < Int32(_elemVec.size()))); }

    inline
      StatElem *getElem (Int32 ID, Bool create = true) 
      { 
        StatElem *elem = _elemVec[ID]; 
        
        if (!elem && create) {
          StatElemDesc *desc = StatElemDesc::getDesc(ID);
          elem =_elemVec[ID] = desc->createElem();          
        }
        
        return elem;
      }

    inline
      StatElem *getElem (StatElemDesc &desc, Bool create = true )
      { return getElem(desc.getID(),create); }

    template<class T> T* getElem(int id) 
      { return ((T*)(this->getElem(id))); }

    template<class T> T* getElem(StatElemDesc &desc) 
      { return ((T*)(this->getElem(desc))); }
      
    StatCollector(void);

    virtual ~StatCollector(void); 

    /*------------------------- your_category -------------------------------*/


    /*------------------------- your_operators ------------------------------*/


    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

    Bool operator < (const StatCollector &other) const;
    
	//OSGBool operator == (const StatCollector &other) const;
	//OSGBool operator != (const StatCollector &other) const;

  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //typedef PARENTCLASS Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------
  
  vector<StatElem*> _elemVec;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// prohibit default functions (move to 'public' if you need one)

    StatCollector(const StatCollector &source);
    StatCollector& operator =(const StatCollector &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef StatCollector *StatCollectorP;

OSG_END_NAMESPACE

#endif /* _STATCOLLECTOR_H_ */
