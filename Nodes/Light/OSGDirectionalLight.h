/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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

#include <OSGLightBase.h>
#include <OSGSFVecTypes.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class   DirectionalLight;

//! \ingroup FieldContainerPtr
/*! the directional light pointer 
 */
typedef FCPtr<LightPtr, DirectionalLight> DirectionalLightPtr;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup NodeLib LightNodes
 *  \brief Directional light
 */

class OSG_LIGHT_DLLMAPPING DirectionalLight : public LightBase
{
  private:

    typedef LightBase Inherited;

  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_FC_FIRST_FIELD_IDM_DECL(DirectionField)

    OSG_FC_LAST_FIELD_IDM_DECL (DirectionField)

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

    OSG_FIELD_CONTAINER_DECL(DirectionalLightPtr)

    /*------------------------------- set -----------------------------------*/

    //@{ 
    //! set the light's attribute
    void setDirection(Real32 rX, Real32 rY, Real32 rZ);
    void setDirection(const Vec3f &gDirection);
    //@}

    /*------------------------------- get -----------------------------------*/

    //! get the light's field
    SFVec3f *getSFDirection(void);

    //@{ 
    //! get the light's attribute
          Vec3f &getDirection(void);
    const Vec3f &getDirection(void) const;
    //@}

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

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //! the light's field
    SFVec3f _direction;

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
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class FieldContainer;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    static char cvsid[];

    static FieldDescription   _desc[];

    static FieldContainerType _type;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static void   initMethod (void);

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

OSG_END_NAMESPACE

#include <OSGDirectionalLight.inl>

#endif /* _OSGDIRECTIONALLIGHT_H_ */
