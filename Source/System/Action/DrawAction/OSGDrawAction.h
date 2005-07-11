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

#ifndef _OSGDRAWACTION_H_
#define _OSGDRAWACTION_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <vector>

#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGDrawActionBase.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class Material;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief DrawAction class
 */

class OSG_SYSTEMLIB_DLLMAPPING DrawAction : public DrawActionBase
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "DrawAction"; };

    // create a new DrawAction by cloning the prototype
    static DrawAction * create( void );
    
    // prototype access
    // after setting the prototype all new DrawActions are clones of it
    static void        setPrototype( DrawAction * proto );
    static DrawAction *getPrototype( void );

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    virtual ~DrawAction(void); 

    // default registration. static, so it can be called during static init
    
    static void registerEnterDefault(   const FieldContainerType &type, 
                                        const Action::Functor    &func);
    
    static void registerLeaveDefault(   const FieldContainerType &type, 
                                        const Action::Functor    &func);

    /*------------------------- your_category -------------------------------*/
    
    UInt32      getLightCount(void) const;
    void        incLightCount(void);
    void        decLightCount(void);


    // initialisation
    virtual Action::ResultE start( void );

    /*------------------------- your_operators ------------------------------*/

    // test a single node
    bool            isVisible( Node* node );
    
    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

    bool operator < (const DrawAction &other) const;
    
    bool operator == (const DrawAction &other) const;
    bool operator != (const DrawAction &other) const;

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

    DrawAction(void);
    DrawAction(const DrawAction &source);

    // access default functors

    virtual std::vector<Functor>* getDefaultEnterFunctors(void);
    virtual std::vector<Functor>* getDefaultLeaveFunctors(void);

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef DrawActionBase Inherited;

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

    // the prototype which is copied to create new actions
    static DrawAction * _prototype;

    // default functors for instantiation
    static std::vector<Functor> *_defaultEnterFunctors;
    static std::vector<Functor> *_defaultLeaveFunctors;
    
    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------
    
    UInt32 _lightCount;
    
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    // prohibit default functions (move to 'public' if you need one)

    DrawAction& operator =(const DrawAction &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef DrawAction *DrawActionP;

OSG_END_NAMESPACE

#include "OSGDrawAction.inl"

#endif /* _OSGDRAWACTION_H_ */


