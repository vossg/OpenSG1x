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

#ifndef _OSGVRMLEXTRUSION_HPP_
#define _OSGVRMLEXTRUSION_HPP_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGVRMLGeometry.h>
#include <OSGMFVecTypes.h>
#include <OSGSFSysTypes.h>
#include <OSGMFMathTypes.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

typedef MFQuaternion MFRotation;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! Brief VRMLExtrusion
//! \ingroup 

class OSG_VRML_DLLMAPPING VRMLExtrusion : public VRMLGeometry
{
  private:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef VRMLGeometry Inherited;

  public:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef       VRMLExtrusion *Ptr;
    typedef const VRMLExtrusion *ConstPtr;

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_RC_FIRST_ELEM_IDM_DECL(BeginCapField                       );

    OSG_RC_ELEM_IDM_DECL      (CcwField,          BeginCapField    );
    OSG_RC_ELEM_IDM_DECL      (ConvexField,       CcwField         );
    OSG_RC_ELEM_IDM_DECL      (CreaseAngleField,  ConvexField      );
    OSG_RC_ELEM_IDM_DECL      (CrossSectionField, CreaseAngleField );
    OSG_RC_ELEM_IDM_DECL      (EndCapField,       CrossSectionField);
    OSG_RC_ELEM_IDM_DECL      (OrientationField,  EndCapField      );
    OSG_RC_ELEM_IDM_DECL      (ScaleField,        OrientationField );
    OSG_RC_ELEM_IDM_DECL      (SolidField,        ScaleField       );
    OSG_RC_ELEM_IDM_DECL      (SpineField,        SolidField       );

    OSG_RC_LAST_ELEM_IDM_DECL (SpineField                          );

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
    void operator =(const VRMLExtrusion &source);

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

    SFBool     _sfBeginCap;
    SFBool     _sfCcw;
    SFBool     _sfConvex;
    SFReal32   _sfCreaseAngle;
    MFVec2f    _mfCrossSection;
    SFBool     _sfEndCap;
    MFRotation _mfOrientation;
    MFVec2f    _mfScale;
    SFBool     _sfSolid;
    MFVec3f    _mfSpine;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    VRMLExtrusion(void);
    VRMLExtrusion(const VRMLExtrusion &source);

  public :

    OSG_VRMLOBJ_DECL(Ptr);

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    virtual ~VRMLExtrusion(void); 

    /*-------------------------- field access -------------------------------*/

    SFBool     *getSFBeginCap    (void);
    SFBool     *getSFCcw         (void);
    SFBool     *getSFConvex      (void);
    SFReal32   *getSFCreaseAngle (void);
    MFVec2f    *getMFCrossSection(void);
    SFBool     *getSFEndCap      (void);
    MFRotation *getMFOrientation (void);
    MFVec2f    *getMFScale       (void);
    SFBool     *getSFSolid       (void);
    MFVec3f    *getMFSpine       (void);
};

OSG_END_NAMESPACE

#define OSGVRMLEXTRUSION_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGVRMLEXTRUSION_HPP_ */
