/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *         contact: dirk@opensg.org, vossg@igd.fhg.de, jbehr@zgdv.de         *
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

class   OSGPointLight;

//! \ingroup FieldContainerPtr
/*! the point light pointer 
 */
typedef OSGFCPtr<OSGLightPtr, OSGPointLight> OSGPointLightPtr;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup NodeLib LightNodes
 *  \brief Point light
 */

class OSGPointLight : public OSGLightBase
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_FC_FIRST_FIELD_IDM_DECL(OSGPositionField  )

    OSG_FC_FIELD_IDM_DECL      (OSGConstAttenField)  
    OSG_FC_FIELD_IDM_DECL      (OSGLinAttenField  )  
    OSG_FC_FIELD_IDM_DECL      (OSGQuadAttenField )  

    OSG_FC_LAST_FIELD_IDM_DECL

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

    OSG_FIELD_CONTAINER_DECL(OSGPointLightPtr)

    /*------------------------------- set -----------------------------------*/

    //@{ 
    //! set the light's attributes
    void setPosition(OSGReal32 rX, OSGReal32 rY, OSGReal32 rZ);
    void setPosition(const OSGPnt3f &gPosition);

    void setAttenuation(OSGReal32 rConstant, 
                        OSGReal32 rLinear, 
                        OSGReal32 rQuadratic);
    //@}


    /*------------------------------- get -----------------------------------*/

    //@{ 
    //! get the light's fields
    OSGSFPnt3f  *getSFPosition(void);

    OSGSFReal32 *getSFConstantAttenuation (void);
    OSGSFReal32 *getSFLinearAttenuation   (void);
    OSGSFReal32 *getSFQuadraticAttenuation(void);
    //@}
 
    //@{ 
    //! get the light's attributes
          OSGPnt3f &getPosition(void);
    const OSGPnt3f &getPosition(void) const;

    OSGReal32 &getConstantAttenuation (void);
    OSGReal32  getConstantAttenuation (void) const;

    OSGReal32 &getLinearAttenuation   (void);
    OSGReal32  getLinearAttenuation   (void) const;

    OSGReal32 &getQuadraticAttenuation(void);
    OSGReal32  getQuadraticAttenuation(void) const;
    //@}

    /*------------------------------ dump -----------------------------------*/

    virtual void dump(void) const;

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
    OSGSFPnt3f  _position;

    OSGSFReal32 _constantAttenuation;
    OSGSFReal32 _linearAttenuation;
    OSGSFReal32 _quadraticAttenuation;
    //@}

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGPointLight(void);
    OSGPointLight(const OSGPointLight &source);
    virtual ~OSGPointLight(void); 
    
    // ------------------------------ Actions ----------------------------
    
     OSGAction::ResultE draw(OSGAction * action );

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGLightBase Inherited;

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

    friend class OSGFieldContainer;

    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    static char cvsid[];

    static OSGFieldDescription   _desc[];

    static OSGFieldContainerType _type;

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

    void operator =(const OSGPointLight &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

OSG_END_NAMESPACE

#include <OSGPointLight.inl>

#endif /* _CLASSNAME_H_ */
