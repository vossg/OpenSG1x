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

#ifndef _OSGVRMLBACKGROUND_HPP_
#define _OSGVRMLBACKGROUND_HPP_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGVRMLUnlimitedNode.h>

#include <OSGMFSysTypes.h>
#include <OSGMFVecTypes.h>
#include <OSGMFBaseTypes.h>

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

//! VRMLBackground
//! \ingroup VRMLNodeLib

class OSG_VRML_DLLMAPPING VRMLBackground : public VRMLUnlimitedNode
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

    typedef       VRMLBackground *Ptr;
    typedef const VRMLBackground *ConstPtr;

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_RC_FIRST_ELEM_IDM_DECL(GroundAngleField                   );

    OSG_RC_ELEM_IDM_DECL      (GroundColorField, GroundAngleField );
    OSG_RC_ELEM_IDM_DECL      (BackUrlField    , GroundColorField );
    OSG_RC_ELEM_IDM_DECL      (BottomUrlField  , BackUrlField     );
    OSG_RC_ELEM_IDM_DECL      (FrontUrlField   , BottomUrlField   );
    OSG_RC_ELEM_IDM_DECL      (LeftUrlField    , FrontUrlField    );
    OSG_RC_ELEM_IDM_DECL      (RightUrlField   , LeftUrlField     );
    OSG_RC_ELEM_IDM_DECL      (TopUrlField     , RightUrlField    );
    OSG_RC_ELEM_IDM_DECL      (SkyAngleField   , TopUrlField      );
    OSG_RC_ELEM_IDM_DECL      (SkyColorField   , SkyAngleField    );

    OSG_RC_LAST_ELEM_IDM_DECL (SkyColorField                      );

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
    void operator =(const VRMLBackground &source);

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

    MFReal32  _mfGroundAngle;
    MFColor3f _mfGroundColor;
    MFString  _mfBackUrl;
    MFString  _mfBottomUrl;
    MFString  _mfFrontUrl;
    MFString  _mfLeftUrl;
    MFString  _mfRightUrl;
    MFString  _mfTopUrl;
    MFReal32  _mfSkyAngle;
    MFColor3f _mfSkyColor;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    VRMLBackground(void);
    VRMLBackground(const VRMLBackground &source);

  public :

    OSG_VRMLOBJ_DECL(Ptr);

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    virtual ~VRMLBackground(void); 

    /*-------------------------- field access -------------------------------*/

    MFReal32  *getMFGroundAngle(void);
    MFColor3f *getMFGroundColor(void);
    MFString  *getMFBackUrl    (void);
    MFString  *getMFBottomUrl  (void);
    MFString  *getMFFrontUrl   (void);
    MFString  *getMFLeftUrl    (void);
    MFString  *getMFRightUrl   (void);
    MFString  *getMFTopUrl     (void);
    MFReal32  *getMFSkyAngle   (void);
    MFColor3f *getMFSkyColor   (void);
};

OSG_END_NAMESPACE

#define OSGVRMLBACKGROUND_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGVRMLBACKGROUND_HPP_ */
