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

#ifndef _OSGVRMLVIEWPOINT_HPP_
#define _OSGVRMLVIEWPOINT_HPP_
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
#include <OSGSFBaseTypes.h>
#include <OSGSFMathTypes.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

typedef SFQuaternion SFRotation;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! VRMLViewpoint
//! \ingroup VRMLNodeLib

class OSG_VRML_DLLMAPPING VRMLViewpoint : public VRMLUnlimitedNode
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

    typedef       VRMLViewpoint *Ptr;
    typedef const VRMLViewpoint *ConstPtr;

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_RC_FIRST_ELEM_IDM_DECL(FieldOfViewField                  );

    OSG_RC_ELEM_IDM_DECL      (JumpField       , FieldOfViewField);
    OSG_RC_ELEM_IDM_DECL      (OrientationField, JumpField       );
    OSG_RC_ELEM_IDM_DECL      (PositionField   , OrientationField);
    OSG_RC_ELEM_IDM_DECL      (DescriptionField, PositionField   );

    OSG_RC_LAST_ELEM_IDM_DECL (DescriptionField                  );

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
    void operator =(const VRMLViewpoint &source);

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
    
    SFReal32   _sfFieldOfView;
    SFBool     _sfJump;
    SFRotation _sfOrientation;
    SFVec3f    _sfPosition;
    SFString   _sfDescription;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    VRMLViewpoint(void); 
    VRMLViewpoint(const VRMLViewpoint &source);

  public :

    OSG_VRMLOBJ_DECL(Ptr);

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    virtual ~VRMLViewpoint(void); 

    /*-------------------------- field access -------------------------------*/

    SFReal32   *getSFFieldOfView (void);
    SFBool     *getSFJump        (void);
    SFRotation *getSFOrientation (void);
    SFVec3f    *getSFPosition    (void);
    SFString   *getSFDescription (void);
};

OSG_END_NAMESPACE

#define OSGVRMLVIEWPOINT_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGVRMLVIEWPOINT_HPP_ */
