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
#include <OSGAction.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class Camera;
class Background;
class Window;
class Node;
class Action;
class Material;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief DrawAction class
 */

class OSG_SYSTEMLIB_DLLMAPPING DrawAction : public Action
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

    /*------------------------- your_category -------------------------------*/
    
    // default registration. static, so it can be called during static init
    
    static void registerEnterDefault(   const FieldContainerType &type, 
                                        const Functor            &func);
    
    static void registerLeaveDefault(   const FieldContainerType &type, 
                                        const Functor            &func);

    
    // rendering state handling
    
    Camera     *getCamera( void ) const;    
    void        setCamera( Camera * cam );
    
    Background *getBackground( void ) const;
    void        setBackground( Background * background );
    
    Window     *getWindow( void ) const;
    void        setWindow( Window * window );
    
    Material   *getMaterial(void) const;
    void        setMaterial(Material *material);

    /*------------------------- your_operators ------------------------------*/


    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

    Bool operator < (const DrawAction &other) const;
    
    Bool operator == (const DrawAction &other) const;
    Bool operator != (const DrawAction &other) const;

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

	// access default functors

	virtual vector<Functor>* getDefaultEnterFunctors( void );
	virtual vector<Functor>* getDefaultLeaveFunctors( void );

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef Action Inherited;

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
    static vector<Functor> *_defaultEnterFunctors;
    static vector<Functor> *_defaultLeaveFunctors;
    
    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    Camera * _camera;
    
    Background * _background;
    
    Window * _window;

    Material *_material;
    
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    // prohibit default functions (move to 'public' if you need one)

    DrawAction(void);
    DrawAction(const DrawAction &source);
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


