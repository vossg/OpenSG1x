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


#ifndef _OSGLIGHTBASE_H_
#define _OSGLIGHTBASE_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#if defined(WIN32) && defined(OSG_BUILD_DLL)
#   ifdef OSG_COMPILELIGHT
#       define OSG_LIGHT_DLLMAPPING __declspec(dllexport)
#   else
#       define OSG_LIGHT_DLLMAPPING __declspec(dllimport)
#   endif
#else
#define OSG_LIGHT_DLLMAPPING
#endif

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

class LightBase;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//! \ingroup FieldContainerPtr

typedef FCPtr<NodeCorePtr, LightBase> LightPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------
 
/*! \defgroup LightNodes
 *  Group for the different light nodes.
 */

/*! \ingroup LightNodes
 *  \brief Base for the different OGL lights.
 */

class OSG_LIGHT_DLLMAPPING LightBase : public NodeCore
{
  private:

    typedef NodeCore Inherited;

  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_FC_FIRST_FIELD_IDM_DECL(AmbientField                )

    OSG_FC_FIELD_IDM_DECL      (DiffuseField,  AmbientField )  
    OSG_FC_FIELD_IDM_DECL      (SpecularField, DiffuseField )  
    OSG_FC_FIELD_IDM_DECL      (BeaconField,   SpecularField)

    OSG_FC_LAST_FIELD_IDM_DECL (BeaconField                 )

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

    OSG_ABSTR_FIELD_CONTAINER_DECL(LightPtr)

    /*------------------------- set color terms -----------------------------*/

    //@{ 
    //! set the light's attributes
    void setAmbientColor(Real32 rRed, Real32 rGreen, Real32 rBlue, 
                         Real32 rAlpha);
    void setAmbientColor(const Color4f &color);

    void setDiffuseColor(Real32 rRed, Real32 rGreen, Real32 rBlue, 
                         Real32 rAlpha);
    void setDiffuseColor(const Color4f &color);

    void setSpecularColor(Real32 rRed, Real32 rGreen, Real32 rBlue, 
                          Real32 rAlpha);
    void setSpecularColor(const Color4f &color);

    void setBeacon(const NodePtr &beacon);
    //@}

    /*------------------------- get color terms fields ----------------------*/

    //@{ 
    //! get the light's fields
    SFColor4f *getSFAmbientColor (void);
    SFColor4f *getSFDiffuseColor (void);
    SFColor4f *getSFSpecularColor(void);
    SFNodePtr *getSFBeacon       (void);
    //@}
   
    /*------------------------- get color terms -----------------------------*/

    //@{ 
    //! get the light's attributes
          Color4f &getAmbientColor(void);
    const Color4f &getAmbientColor(void) const;

          Color4f &getDiffuseColor(void);
    const Color4f &getDiffuseColor(void) const;

          Color4f &getSpecularColor(void);
    const Color4f &getSpecularColor(void) const;

          NodePtr &getBeacon(void);
    const NodePtr &getBeacon(void) const;
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
    SFColor4f _ambientTerm;
    SFColor4f _diffuseTerm;
    SFColor4f _specularTerm;
    SFNodePtr _beacon;
    //@}

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    LightBase(void);
    LightBase(const LightBase &source);
    virtual ~LightBase(void); 
    
    // ------------------------------ Actions ------------------------------
    
    /*! \ingroup ActionFunctions
     *  Draw action: execute the OpenGL commands to set the light's
     *  parameters. Right now only into \c GL_LIGHT0!
     */
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

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const NodeCore &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

OSG_END_NAMESPACE

#include <OSGLightBase.inl>

#endif /* _OSGLIGHTBASE_H_ */
