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

#ifndef _OSGVRMLSCALARINTERPOLATOR_HPP_
#define _OSGVRMLSCALARINTERPOLATOR_HPP_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGVRMLUnlimitedNode.h>
#include <OSGSFSysTypes.h>
#include <OSGMFSysTypes.h>
#include <OSGSFBaseTypes.h>
#include <OSGSFVecTypes.h>
#include <OSGMFVecTypes.h>

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

//! Brief VRMLScalarInterpolator
//! \ingroup VRMLNodeLib

class OSG_VRML_DLLMAPPING VRMLScalarInterpolator : public VRMLUnlimitedNode
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

    typedef       VRMLScalarInterpolator *Ptr;
    typedef const VRMLScalarInterpolator *ConstPtr;

    //-----------------------------------------------------------------------
    //   constants
    //-----------------------------------------------------------------------

    OSG_RC_FIRST_ELEM_IDM_DECL(KeyField);

    OSG_RC_ELEM_IDM_DECL      (KeyValueField,
                               KeyField);
    OSG_RC_ELEM_IDM_DECL      (SetFractionField,
                               KeyValueField);
    OSG_RC_ELEM_IDM_DECL      (ValueChangedField,
                               SetFractionField);

    OSG_RC_LAST_ELEM_IDM_DECL (ValueChangedField);

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
    void operator =(const VRMLScalarInterpolator &source);

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

    MFReal32    _mfKey;
    MFReal32    _mfKeyValue;
    SFReal32    _sfSetFraction;
    SFReal32    _sfValueChanged;

    //-----------------------------------------------------------------------
    //   instance functions
    //-----------------------------------------------------------------------

    VRMLScalarInterpolator(void);
    VRMLScalarInterpolator(const VRMLScalarInterpolator &source);

  public :

    OSG_VRMLOBJ_DECL(Ptr);

    //-----------------------------------------------------------------------
    //   class functions
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions
    //-----------------------------------------------------------------------

    virtual ~VRMLScalarInterpolator(void);

    /*------------------------- your_category -------------------------------*/

    virtual void evaluate(Time oTime);

    /*-------------------------- field access -------------------------------*/

    MFReal32    *getMFKey           (void);
    MFReal32    *getMFKeyValue      (void);
    SFReal32    *getSFSetFraction   (void);
    SFReal32    *getSFValueChanged  (void);

};

OSG_END_NAMESPACE

#define OSGVRMLSCALARINTERPOLATOR_HEADER_CVSID "@(#)$Id: OSGVRMLScalarInterpolator.h,v 1.1 2004/03/05 17:36:07 a-m-z Exp $"

#endif /* _OSGVRMLSCALARINTERPOLATOR_HPP_ */
