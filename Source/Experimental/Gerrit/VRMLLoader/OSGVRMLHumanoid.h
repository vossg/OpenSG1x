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

#ifndef _OSGVRMLHUMANOID_HPP_
#define _OSGVRMLHUMANOID_HPP_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGVRMLTransform.h>

#include <OSGSFBaseTypes.h>
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

//! VRMLHumanoid
//! \ingroup VRMLNodeLib

class OSG_VRML_DLLMAPPING VRMLHumanoid : public VRMLTransform
{
  private:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef VRMLTransform Inherited;

  public:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef       VRMLHumanoid *Ptr;
    typedef const VRMLHumanoid *ConstPtr;

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_RC_FIRST_ELEM_IDM_DECL(InfoField                       );

    OSG_RC_ELEM_IDM_DECL      (JointsField,     InfoField      );
    OSG_RC_ELEM_IDM_DECL      (NameField,       JointsField    );
    OSG_RC_ELEM_IDM_DECL      (SegmentsField,   NameField      );
    OSG_RC_ELEM_IDM_DECL      (SitesField,      SegmentsField  );

    OSG_RC_ELEM_IDM_DECL      (SkeletonField,   SitesField     );
    OSG_RC_ELEM_IDM_DECL      (SkinField,       SkeletonField  );
    OSG_RC_ELEM_IDM_DECL      (SkinCoordField,  SkinField      );
    OSG_RC_ELEM_IDM_DECL      (SkinNormalField, SkinCoordField );

    OSG_RC_ELEM_IDM_DECL      (VersionField,    SkinNormalField);
    OSG_RC_ELEM_IDM_DECL      (ViewpointsField, VersionField   );

    OSG_RC_LAST_ELEM_IDM_DECL (ViewpointsField                 );

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
    void operator =(const VRMLHumanoid &source);

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

    MFString   _mfInfo;
    MFVRMLNode _mfJoints;
    SFString   _sfName;
    MFVRMLNode _mfSegments;
    MFVRMLNode _mfSites;

    MFVRMLNode _mfSkeleton;
    MFVRMLNode _mfSkin;
    SFVRMLNode _sfSkinCoord;
    SFVRMLNode _sfSkinNormal;

    SFString   _sfVersion;
    MFVRMLNode _mfViewpoints;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    VRMLHumanoid(void);
    VRMLHumanoid(const VRMLHumanoid &source);

  public :

    OSG_VRMLOBJ_DECL(Ptr);

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    virtual ~VRMLHumanoid(void); 

    /*-------------------------- field access -------------------------------*/

    /*------------------------------ Caches ---------------------------------*/

    /*------------------------------ Caches ---------------------------------*/

    /*-------------------------- field access -------------------------------*/

    /*-------------------------- field access -------------------------------*/

    MFString   *getMFInfo      (void);
    MFVRMLNode *getMFJoints    (void);
    SFString   *getSFName      (void);
    MFVRMLNode *getMFSegments  (void);
    MFVRMLNode *getMFSites     (void);

    MFVRMLNode *getMFSkeleton  (void);
    MFVRMLNode *getMFSkin      (void);
    SFVRMLNode *getSFSkinCoord (void);
    SFVRMLNode *getSFSkinNormal(void);

    SFString   *getSFVersion   (void);
    MFVRMLNode *getMFViewpoints(void);
};

OSG_END_NAMESPACE

#define OSGVRMLHUMANOID_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGVRMLHUMANOID_HPP_ */

