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

#ifndef _OSGVRMLSOUND_HPP_
#define _OSGVRMLSOUND_HPP_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGVRMLUnlimitedNode.h>
#include <OSGSFSysTypes.h>
#include <OSGSFVecTypes.h>

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

//! Brief VRMLSound
//! \ingroup VRMLNodeLib

class OSG_VRML_DLLMAPPING VRMLSound : public VRMLUnlimitedNode
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

    typedef       VRMLSound *Ptr;
    typedef const VRMLSound *ConstPtr;

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_RC_FIRST_ELEM_IDM_DECL(DirectionField                 );

    OSG_RC_ELEM_IDM_DECL      (IntensityField,  DirectionField);
    OSG_RC_ELEM_IDM_DECL      (LocationField,   IntensityField);
    OSG_RC_ELEM_IDM_DECL      (MaxBackField,    LocationField );
    OSG_RC_ELEM_IDM_DECL      (MaxFrontField,   MaxBackField  );
    OSG_RC_ELEM_IDM_DECL      (MinBackField,    MaxFrontField );
    OSG_RC_ELEM_IDM_DECL      (MinFrontField,   MinBackField  );
    OSG_RC_ELEM_IDM_DECL      (PriorityField,   MinFrontField );
    OSG_RC_ELEM_IDM_DECL      (SourceField,     PriorityField );
    OSG_RC_ELEM_IDM_DECL      (SpatializeField, SourceField   );

    OSG_RC_LAST_ELEM_IDM_DECL (SpatializeField                );

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
    void operator =(const VRMLSound &source);

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

    SFVec3f    _sfDirection;
    SFReal32   _sfIntensity;
    SFVec3f    _sfLocation;
    SFReal32   _sfMaxBack;
    SFReal32   _sfMaxFront;
    SFReal32   _sfMinBack;
    SFReal32   _sfMinFront;
    SFReal32   _sfPriority;
    SFVRMLNode _sfSource;
    SFBool     _sfSpatialize;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    VRMLSound(void);
    VRMLSound(const VRMLSound &source);

  public :

    OSG_VRMLOBJ_DECL(Ptr);

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    virtual ~VRMLSound(void); 

    /*-------------------------- field access -------------------------------*/

    SFVec3f    *getSFDirection (void);
    SFReal32   *getSFIntensity (void);
    SFVec3f    *getSFLocation  (void);
    SFReal32   *getSFMaxBack   (void);
    SFReal32   *getSFMaxFront  (void);
    SFReal32   *getSFMinBack   (void);
    SFReal32   *getSFMinFront  (void);
    SFReal32   *getSFPriority  (void);
    SFVRMLNode *getSFSource    (void);
    SFBool     *getSFSpatialize(void);
};

OSG_END_NAMESPACE

#define OSGVRMLSOUND_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGVRMLSOUND_HPP_ */
