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


#ifndef _OSGLIGHTBASE_H_
#define _OSGLIGHTBASE_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGNodeCore.h>
#include <OSGFieldContainerPtr.h>
#include <OSGSFBaseTypes.h>
#include <OSGFieldDescription.h>
#include <OSGAction.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class OSGLightBase;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//! \ingroup FieldContainerPtr

typedef OSGFCPtr<OSGNodeCorePtr, OSGLightBase> OSGLightPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------
 
/*! \defgroup LightNodes
 *  Group for the different light nodes.
 */

/*! \ingroup LightNodes
 *  \brief Base for the different OGL lights.
 */

class OSGLightBase : public OSGNodeCore
{
  private:

  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_FC_FIRST_FIELD_IDM_DECL(OSGAmbientField )

    OSG_FC_FIELD_IDM_DECL      (OSGDiffuseField )  
    OSG_FC_FIELD_IDM_DECL      (OSGSpecularField)  
    OSG_FC_FIELD_IDM_DECL      (OSGBeaconField  )

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

    static const char *getClassname(void) { return "LightBase"; };

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_ABSTR_FIELD_CONTAINER_DECL(OSGLightPtr)

    /*------------------------- set color terms -----------------------------*/

    //@{ 
    //! set the light's attributes
    void setAmbientColor(OSGReal32 rRed, OSGReal32 rGreen, OSGReal32 rBlue, 
                         OSGReal32 rAlpha);
    void setAmbientColor(const OSGColor4f &color);

    void setDiffuseColor(OSGReal32 rRed, OSGReal32 rGreen, OSGReal32 rBlue, 
                         OSGReal32 rAlpha);
    void setDiffuseColor(const OSGColor4f &color);

    void setSpecularColor(OSGReal32 rRed, OSGReal32 rGreen, OSGReal32 rBlue, 
                          OSGReal32 rAlpha);
    void setSpecularColor(const OSGColor4f &color);

    void setBeacon(const OSGNodePtr &beacon);
    //@}

    /*------------------------- get color terms fields ----------------------*/

    //@{ 
    //! get the light's fields
    OSGSFColor4f *getSFAmbientColor (void);
    OSGSFColor4f *getSFDiffuseColor (void);
    OSGSFColor4f *getSFSpecularColor(void);
    OSGSFNodePtr *getSFBeacon       (void);
    //@}
   
    /*------------------------- get color terms -----------------------------*/

    //@{ 
    //! get the light's attributes
          OSGColor4f &getAmbientColor(void);
    const OSGColor4f &getAmbientColor(void) const;

          OSGColor4f &getDiffuseColor(void);
    const OSGColor4f &getDiffuseColor(void) const;

          OSGColor4f &getSpecularColor(void);
    const OSGColor4f &getSpecularColor(void) const;

          OSGNodePtr &getBeacon(void);
    const OSGNodePtr &getBeacon(void) const;
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
    OSGSFColor4f _ambientTerm;
    OSGSFColor4f _diffuseTerm;
    OSGSFColor4f _specularTerm;
    OSGSFNodePtr _beacon;
    //@}

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGLightBase(void);
    OSGLightBase(const OSGLightBase &source);
    virtual ~OSGLightBase(void); 
    
    // ------------------------------ Actions ------------------------------
    
    /*! \ingroup ActionFunctions
     *  Draw action: execute the OpenGL commands to set the light's
     *  parameters. Right now only into \c GL_LIGHT0!
     */
    OSGAction::ResultE draw(OSGAction * action );

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef OSGNodeCore Inherited;

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

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const OSGNodeCore &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

OSG_END_NAMESPACE

#include <OSGLightBase.inl>

#endif /* _OSGLIGHTBASE_H_ */
