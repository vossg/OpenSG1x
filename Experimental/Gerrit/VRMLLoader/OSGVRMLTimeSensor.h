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

#ifndef _OSGVRMLTIMESENSOR_HPP_
#define _OSGVRMLTIMESENSOR_HPP_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGVRMLSensor.h>
#include <OSGSFBaseTypes.h>
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

//! VRMLTimeSensor
//! \ingroup VRMLNodeLib

class OSG_VRML_DLLMAPPING VRMLTimeSensor : public VRMLSensor
{
  private:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef VRMLSensor Inherited;

  public:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef       VRMLTimeSensor *Ptr;
    typedef const VRMLTimeSensor *ConstPtr;

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_RC_FIRST_ELEM_IDM_DECL(CycleIntervalField  );

    OSG_RC_ELEM_IDM_DECL      (LoopField,      
                               CycleIntervalField  );
    OSG_RC_ELEM_IDM_DECL      (StartTimeField, 
                               LoopField           );
    OSG_RC_ELEM_IDM_DECL      (StopTimeField,  
                               StartTimeField      );

    OSG_RC_ELEM_IDM_DECL      (CycleTimeField,        
                               StopTimeField       );
    OSG_RC_ELEM_IDM_DECL      (FractionChangedField,  
                               CycleTimeField      );
    OSG_RC_ELEM_IDM_DECL      (IsActiveField,         
                               FractionChangedField);
    OSG_RC_ELEM_IDM_DECL      (TimeField,  
                               IsActiveField       );

    OSG_RC_LAST_ELEM_IDM_DECL (TimeField           );

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
    void operator =(const VRMLTimeSensor &source);

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

    SFTime   _sfCycleInterval;
    SFBool   _sfLoop;
    SFTime   _sfStartTime;
    SFTime   _sfStopTime;

    SFTime   _sfCycleTime;
    SFReal32 _sfFractionChanged;
    SFBool   _sfIsActive;
    SFTime   _sfTime;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    VRMLTimeSensor(void);
    VRMLTimeSensor(const VRMLTimeSensor &source);

  public :

    OSG_VRMLOBJ_DECL(Ptr);

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    virtual ~VRMLTimeSensor(void); 

    /*------------------------- your_category -------------------------------*/

    virtual void evaluate(Time tTime);

    /*-------------------------- field access -------------------------------*/

    SFTime   *getSFCycleInterval  (void);
    SFBool   *getSFLoop           (void);
    SFTime   *getSFStartTime      (void);
    SFTime   *getSFStopTime       (void);

    SFTime   *getSFCycleTime      (void);
    SFReal32 *getSFFractionChanged(void);
    SFBool   *getSFIsActive       (void);
    SFTime   *getSFTime           (void);
};

OSG_END_NAMESPACE

#define OSGVRMLTIMESENSOR_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGVRMLTIMESENSOR_HPP_ */
