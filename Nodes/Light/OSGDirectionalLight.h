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


#ifndef _OSGDIRECTIONALLIGHT_H_
#define _OSGDIRECTIONALLIGHT_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGConfig.h>

#include <OSGDirectionalLightBase.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup LightNodes
 *  \brief Directional light
 */

class OSG_SYSTEMLIB_DLLMAPPING DirectionalLight : public DirectionalLightBase
{
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

    static const char *getClassname(void) { return "DirectionalLight"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    /*--------------------------- access fields ----------------------------*/

    /*----------------------------- access ----------------------------------*/

    /*------------------------------- set -----------------------------------*/

    //@{ 
    //! set the light's attribute
    void setDirection(Real32 rX, Real32 rY, Real32 rZ);
    void setDirection(const Vec3f &gDirection);
    //@}

    virtual void changed(BitVector  whichField, 
                         ChangeMode from);
 
    /*------------------------------ volume -------------------------------*/

    /*------------------------------ dump -----------------------------------*/

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector &bvFlags  = 0) const;

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

#ifdef OSG_NOFUNCTORS
    static Action::ResultE DLightDrawEnter(CNodePtr &cnode, 
                                           Action   *pAction);
#endif

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    // They should all be in DirectionalLightBase.

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    DirectionalLight(void);
    DirectionalLight(const DirectionalLight &source);
    virtual ~DirectionalLight(void); 
    
    // ----------------------------- Actions ---------------------------------
    
    // execute the OpenGL commands to draw the geometry 
    Action::ResultE draw(Action * action );

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef DirectionalLightBase Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class FieldContainer;
    friend class DirectionalLightBase;

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

    static void initMethod( void );

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const DirectionalLight &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------


/** \brief class pointer
 */
typedef DirectionalLight *DirectionalLightP;

OSG_END_NAMESPACE

#include <OSGDirectionalLight.inl>
#include <OSGDirectionalLightBase.inl>

#endif /* _OSGDIRECTIONALLIGHT_H_ */
