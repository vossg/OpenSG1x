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

#ifndef _OSGVRMLTOOSGACTION_HPP_
#define _OSGVRMLTOOSGACTION_HPP_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGVRMLAction.h>
#include <OSGIDString.h>

#include <map>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

struct ToOpenSGActionDesc
{
};

typedef VRMLStaticActionMixin<ToOpenSGActionDesc> VRMLToOSGMixin; 

#ifndef OSG_COMPILEVRMLTOOSGACTIONINST

#ifdef __sgi

#pragma do_not_instantiate VRMLStaticActionMixin<ToOpenSGActionDesc>

#else

extern template class OSG_VRML_DLLMAPPING 
     VRMLStaticActionMixin<ToOpenSGActionDesc>;

#endif

#endif

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! VRMLToOSGAction
//! \ingroup VRMLOSGBindingLib
//! \ingroup VRMLActionLib

class OSG_VRML_DLLMAPPING VRMLToOSGAction : public VRMLToOSGMixin
{
  private:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef VRMLToOSGMixin Inherited;

  public:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef map<IDStringLink, VRMLNode *> NameNodeMap;

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    enum ConvertOptions
    {
        CreateNormals  = 0x0001,
        StripeGeometry = 0x0002
    };

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
    VRMLToOSGAction(const VRMLToOSGAction &source);
    //! prohibit default function (move to 'public' if needed) 
    void operator =(const VRMLToOSGAction &source);

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

    UInt32       _uiOptions;
    NameNodeMap *_pNameNodeMap;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

  public :

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    VRMLToOSGAction(void);
    virtual ~VRMLToOSGAction(void); 

    /*------------------------- your_operators ------------------------------*/

    void         setOptions    (UInt32 uiOptions );
    UInt32       getOptions    (void                );

    void         setNameNodeMap(NameNodeMap *pMap);
    NameNodeMap *getNameNodeMap(void                );
};

//---------------------------------------------------------------------------
//  Callbacks
//---------------------------------------------------------------------------

#if 0
void vscInitToOpenSGAction(void);


VSCVRMLAction::VSCActionResult vscVRMLSwitchToOpenSG(VSCVRMLNode   &oNode,
                                                     VSCVRMLAction *pAction);

VSCVRMLAction::VSCActionResult vscVRMLLODToOpenSG(VSCVRMLNode   &oNode,
                                                  VSCVRMLAction *pAction);

VSCVRMLAction::VSCActionResult vscVRMLInlineToOpenSG(VSCVRMLNode   &oNode,
                                                     VSCVRMLAction *pAction);





VSCVRMLAction::VSCActionResult vscVRMLIndexedLineSetToOpenSG(
    VSCVRMLNode   &oNode,
    VSCVRMLAction *pAction);




VSCVRMLAction::VSCActionResult vscVRMLScalarInterpolatorToOpenSG(
    VSCVRMLNode   &oNode,
    VSCVRMLAction *pAction);

VSCVRMLAction::VSCActionResult vscVRMLPositionInterpolatorToOpenSG(
    VSCVRMLNode   &oNode,
    VSCVRMLAction *pAction);

VSCVRMLAction::VSCActionResult vscVRMLOrientationInterpolatorToOpenSG(
    VSCVRMLNode   &oNode,
    VSCVRMLAction *pAction);

VSCVRMLAction::VSCActionResult vscVRMLTimeSensorToOpenSG(
    VSCVRMLNode   &oNode,
    VSCVRMLAction *pAction);


VSCVRMLAction::VSCActionResult vscVRMLBoxToOpenSG(VSCVRMLNode   &oNode,
                                                  VSCVRMLAction *pAction);

VSCVRMLAction::VSCActionResult vscVRMLConeToOpenSG(VSCVRMLNode   &oNode,
                                                   VSCVRMLAction *pAction);

VSCVRMLAction::VSCActionResult vscVRMLCylinderToOpenSG(VSCVRMLNode   &oNode,
                                                       VSCVRMLAction *pAction);

VSCVRMLAction::VSCActionResult vscVRMLSphereToOpenSG(VSCVRMLNode   &oNode,
                                                     VSCVRMLAction *pAction);

VSCVRMLAction::VSCActionResult vscVRMLBillboardToOpenSG(
    VSCVRMLNode   &oNode,
    VSCVRMLAction *pAction);


VSCVRMLAction::VSCActionResult vscVRMLHumanoidToOpenSG(VSCVRMLNode   &oNode,
                                                       VSCVRMLAction *pAction);
#endif

OSG_END_NAMESPACE

#define OSGVRMLTOOSGACTION_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGVRMLTOOSGACTION_HPP_ */
