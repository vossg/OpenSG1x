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

#ifndef _OSVRMLFONTSTYLE_HPP_
#define _OSGVRMLFONTSTYLE_HPP_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGVRMLUnlimitedNode.h>

#include <OSGSFBaseTypes.h>
#include <OSGMFBaseTypes.h>
#include <OSGSFSysTypes.h>

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

//! VRMLFontStyle
//! \ingroup VRMLNodeLib

class OSG_VRML_DLLMAPPING VRMLFontStyle : public VRMLUnlimitedNode
{
  private:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef VRMLUnlimitedNode Inherited;

  public:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef       VRMLFontStyle *Ptr;
    typedef const VRMLFontStyle *ConstPtr;

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_RC_FIRST_ELEM_IDM_DECL(FamilyField                       );

    OSG_RC_ELEM_IDM_DECL      (HorizontalField,  FamilyField     );
    OSG_RC_ELEM_IDM_DECL      (JustifyField,     HorizontalField );
    OSG_RC_ELEM_IDM_DECL      (LanguageField,    JustifyField    );
    OSG_RC_ELEM_IDM_DECL      (LeftToRightField, LanguageField   );
    OSG_RC_ELEM_IDM_DECL      (SizeField,        LeftToRightField);
    OSG_RC_ELEM_IDM_DECL      (SpacingField,     SizeField       );
    OSG_RC_ELEM_IDM_DECL      (StyleField,       SpacingField    );
    OSG_RC_ELEM_IDM_DECL      (TopToBottomField, StyleField      );

    OSG_RC_LAST_ELEM_IDM_DECL (TopToBottomField                  );

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

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

    //-----------------------------------------------------------------------
    //   friend functions                                                    
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

    //! prohibit default function (move to 'public' if needed) 
    void operator =(const VRMLFontStyle &source);

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

    static VRMLObjectType _type;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    SFString _sfFamily;
    SFBool   _sfHorizontal;
    MFString _mfJustify;
    SFString _sfLanguage;
    SFBool   _sfLeftToRight;
    SFReal32 _sfSize;
    SFReal32 _sfSpacing;
    SFString _sfStyle;
    SFBool   _sfTopToBottom;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    VRMLFontStyle(void);
    VRMLFontStyle(const VRMLFontStyle &source);

  public :

    OSG_VRMLOBJ_DECL(Ptr);

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    virtual ~VRMLFontStyle(void); 

    /*-------------------------- field access -------------------------------*/

    SFString *getSFFamily     (void);
    SFBool   *getSFHorizontal (void);
    MFString *getMFJustify    (void);
    SFString *getSFLanguage   (void);
    SFBool   *getSFLeftToRight(void);
    SFReal32 *getSFSize       (void);
    SFReal32 *getSFSpacing    (void);
    SFString *getSFStyle      (void);
    SFBool   *getSFTopToBottom(void);
};

OSG_END_NAMESPACE

#define OSGVRMLFONTSTYLE_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGVRMLFONTSTYLE_HPP_ */
