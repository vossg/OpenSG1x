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


#ifndef _OSGSPOTLIGHT_H_
#define _OSGSPOTLIGHT_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGPointLight.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class   SpotLight;

//! \ingroup FieldContainerPtr
/*! the spot light pointer 
 */
typedef FCPtr<PointLightPtr, SpotLight> SpotLightPtr;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup LightNodes
 *  \brief Spotlight
 */

class OSG_LIGHT_DLLMAPPING SpotLight : public PointLight
{
  private:

    typedef PointLight Inherited;

  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_FC_FIRST_FIELD_IDM_DECL(DirectionField                 )

    OSG_FC_FIELD_IDM_DECL      (SpotExpField,    DirectionField)  
    OSG_FC_FIELD_IDM_DECL      (SpotCutOffField, SpotExpField  )  

    OSG_FC_LAST_FIELD_IDM_DECL (SpotCutOffField                )

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "SpotLight"; };
 
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_FIELD_CONTAINER_DECL(SpotLightPtr)

    /*------------------------------- set -----------------------------------*/

    //@{ 
    //! set the light's attributes
    void setSpotDirection(Real32 rX, Real32 rY, Real32 rZ);
    void setSpotDirection(const Vec3f &gDirection);

    void setSpotExponent(Real32 rSpotExponent);
    void setSpotCutOff  (Real32 rSpotCutOff);
    //@}

    /*------------------------------- get -----------------------------------*/

    //@{ 
    //! get the light's fields
    SFVec3f  *getSFDirection(void);

    SFReal32 *getSFSpotExponent(void);
    SFReal32 *getSFSpotCutOff  (void);
    //@}
 
    //@{ 
    //! get the light's attributes
          Vec3f &getDirection  (void);
    const Vec3f &getDirection  (void) const;

    Real32 &getSpotExponent    (void);
    Real32  getSpotExponent    (void) const;

    Real32 &getSpotCutOff      (void);
    Real32  getSpotCutOff      (void) const;
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

    //@{ 
    //! the light's fields
    SFVec3f  _direction;

    SFReal32 _spotExponent;
    SFReal32 _spotCutOff;
    //@}

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    SpotLight(void);
    SpotLight(const SpotLight &source);
    virtual ~SpotLight(void); 
    
    // ----------------------------- Actions --------------------------------
    
    Action::ResultE draw(Action * action );

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
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

    void operator =(const SpotLight &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

OSG_END_NAMESPACE

#include <OSGSpotLight.inl>

#endif /* _OSGSPOTLIGHT_H_ */
