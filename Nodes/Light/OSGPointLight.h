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


#ifndef _OSGPOINTLIGHT_H_
#define _OSGPOINTLIGHT_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGLightBase.h>
#include <OSGSFVecTypes.h>
#include <OSGSFSysTypes.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class   PointLight;

//! \ingroup FieldContainerPtr
/*! the point light pointer 
 */
typedef FCPtr<LightPtr, PointLight> PointLightPtr;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup NodeLib LightNodes
 *  \brief Point light
 */

class OSG_LIGHT_DLLMAPPING PointLight : public LightBase
{
  private:

    typedef LightBase Inherited;

  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_FC_FIRST_FIELD_IDM_DECL(PositionField                   )

    OSG_FC_FIELD_IDM_DECL      (ConstAttenField, PositionField  )
    OSG_FC_FIELD_IDM_DECL      (LinAttenField,   ConstAttenField)  
    OSG_FC_FIELD_IDM_DECL      (QuadAttenField,  LinAttenField  )

    OSG_FC_LAST_FIELD_IDM_DECL (QuadAttenField                  )  

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "PointLight"; };
 
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_FIELD_CONTAINER_DECL(PointLightPtr)

    /*------------------------------- set -----------------------------------*/

    //@{ 
    //! set the light's attributes
    void setPosition(Real32 rX, Real32 rY, Real32 rZ);
    void setPosition(const Pnt3f &gPosition);

    void setAttenuation(Real32 rConstant, 
                        Real32 rLinear, 
                        Real32 rQuadratic);
    //@}


    /*------------------------------- get -----------------------------------*/

    //@{ 
    //! get the light's fields
    SFPnt3f  *getSFPosition(void);

    SFReal32 *getSFConstantAttenuation (void);
    SFReal32 *getSFLinearAttenuation   (void);
    SFReal32 *getSFQuadraticAttenuation(void);
    //@}
 
    //@{ 
    //! get the light's attributes
          Pnt3f &getPosition(void);
    const Pnt3f &getPosition(void) const;

    Real32 &getConstantAttenuation (void);
    Real32  getConstantAttenuation (void) const;

    Real32 &getLinearAttenuation   (void);
    Real32  getLinearAttenuation   (void) const;

    Real32 &getQuadraticAttenuation(void);
    Real32  getQuadraticAttenuation(void) const;
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
    SFPnt3f  _position;

    SFReal32 _constantAttenuation;
    SFReal32 _linearAttenuation;
    SFReal32 _quadraticAttenuation;
    //@}

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    PointLight(void);
    PointLight(const PointLight &source);
    virtual ~PointLight(void); 
    
    // ------------------------------ Actions ----------------------------
    
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

    void operator =(const PointLight &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

OSG_END_NAMESPACE

#include <OSGPointLight.inl>

#endif /* _OSGPOINTLIGHT_H_ */
