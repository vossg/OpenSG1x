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

#ifndef _OSGVRMLELEVATIONGRID_HPP_
#define _OSGVRMLELEVATIONGRID_HPP_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGBaseTypes.h>
#include <OSGVRMLGeometry.h>
#include <OSGSFSysTypes.h>
#include <OSGMFSysTypes.h>

#include <OSGGeometry.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class VRMLToOSGAction;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! VRMLElevationGrid
//! \ingroup VRMLNodeLib

class OSG_VRML_DLLMAPPING VRMLElevationGrid : public VRMLGeometry
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

    typedef       VRMLElevationGrid *Ptr;
    typedef const VRMLElevationGrid *ConstPtr;

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_RC_FIRST_ELEM_IDM_DECL(ColorField          );

    OSG_RC_ELEM_IDM_DECL      (NormalField, 
                               ColorField          );
    OSG_RC_ELEM_IDM_DECL      (TexCoordField, 
                               NormalField         );
    OSG_RC_ELEM_IDM_DECL      (HeightField, 
                               TexCoordField       );
    OSG_RC_ELEM_IDM_DECL      (CcwField, 
                               HeightField         );
    OSG_RC_ELEM_IDM_DECL      (ColorPerVertexField, 
                               CcwField            );
    OSG_RC_ELEM_IDM_DECL      (CreaseAngleField, 
                               ColorPerVertexField );
    OSG_RC_ELEM_IDM_DECL      (NormalPerVertexField, 
                               CreaseAngleField    );
    OSG_RC_ELEM_IDM_DECL      (SolidField,           
                               NormalPerVertexField);
    OSG_RC_ELEM_IDM_DECL      (XDimensionField, 
                               SolidField          );
    OSG_RC_ELEM_IDM_DECL      (XSpacingField, 
                               XDimensionField     );
    OSG_RC_ELEM_IDM_DECL      (ZDimensionField, 
                               XSpacingField       );
    OSG_RC_ELEM_IDM_DECL      (ZSpacingField, 
                               ZDimensionField     );

    OSG_RC_LAST_ELEM_IDM_DECL (ZSpacingField       );

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
    void operator =(const VRMLElevationGrid &source);

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

    static void init(void);

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    SFVRMLNode _sfColor;
    SFVRMLNode _sfNormal;
    SFVRMLNode _sfTexCoord;
    
    MFReal32   _mfHeight;
    SFBool     _sfCcw;
    SFBool     _sfColorPerVertex;
    SFReal32   _sfCreaseAngle;
    SFBool     _sfNormalPerVertex;
    SFBool     _sfSolid;
    SFInt32    _sfXDimension;
    SFReal32   _sfXSpacing;
    SFInt32    _sfZDimension;
    SFReal32   _sfZSpacing;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    VRMLElevationGrid(void);
    VRMLElevationGrid(const VRMLElevationGrid &source);

  public :

    OSG_VRMLOBJ_DECL(Ptr);

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    virtual ~VRMLElevationGrid(void); 

    /*-------------------------- field access -------------------------------*/

    SFVRMLNode *getSFColor          (void);
    SFVRMLNode *getSFNormal         (void);
    SFVRMLNode *getSFTexCoord       (void);
    
    MFReal32   *getMFHeight         (void);
    SFBool     *getSFCcw            (void);
    SFBool     *getSFColorPerVertex (void);
    SFReal32   *getSFCreaseAngle    (void);
    SFBool     *getSFNormalPerVertex(void);
    SFBool     *getSFSolid          (void);
    SFInt32    *getSFXDimension     (void);
    SFReal32   *getSFXSpacing       (void);
    SFInt32    *getSFZDimension     (void);
    SFReal32   *getSFZSpacing       (void);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! VRMLElevationGridBinder
//! \ingroup VRMLOSGBindingLib

class OSG_VRML_DLLMAPPING VRMLElevationGridBinder : 
    public VRMLGeometryBinder
{
  private:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef VRMLGeometryBinder Inherited;

  public:

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

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
    VRMLElevationGridBinder(const VRMLElevationGridBinder &source);
    //! prohibit default function (move to 'public' if needed) 
    void operator =(const VRMLElevationGridBinder &source);

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

    VRMLElevationGridBinder(void);

    virtual ~VRMLElevationGridBinder(void); 

    /*------------------------- your_category -------------------------------*/

    void init        (VRMLToOSGAction *pAction        );

    void setNormals  (VRMLNodeBinder  *pNormalBinder  );
    void setColors   (VRMLNodeBinder  *pColorBinder   );
    void setTexCoords(VRMLNodeBinder  *pTexCoordBinder);

    void finish      (VRMLToOSGAction *pAction        );
};

OSG_END_NAMESPACE

#define OSGVRMLELEVATIONGRID_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGVRMLELEVATIONGRID_HPP_ */
