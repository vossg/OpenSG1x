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

#ifndef _OSGVRMLINDEXEDFACESET_HPP_
#define _OSGVRMLINDEXEDFACESET_HPP_
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
#include <OSGSFBaseTypes.h>
#include <OSGGeometry.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class VRMLCoordinateBinder;
class VRMLNormalBinder;
class VRMLColorBinder;
class VRMLTextureCoordinateBinder;
class VRMLToOSGAction;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! VRMLIndexedFaceSet
//! \ingroup VRMLNodeLib

class OSG_VRML_DLLMAPPING VRMLIndexedFaceSet : public VRMLGeometry
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

    typedef       VRMLIndexedFaceSet *Ptr;
    typedef const VRMLIndexedFaceSet *ConstPtr;

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_RC_FIRST_ELEM_IDM_DECL(ColorField           );

    OSG_RC_ELEM_IDM_DECL      (CoordField, 
                               ColorField           );
    OSG_RC_ELEM_IDM_DECL      (NormalField, 
                               CoordField           );
    OSG_RC_ELEM_IDM_DECL      (TexCoordField, 
                               NormalField          );

    OSG_RC_ELEM_IDM_DECL      (CcwField, 
                               TexCoordField        );
    OSG_RC_ELEM_IDM_DECL      (ColorIndexField, 
                               CcwField             );
    OSG_RC_ELEM_IDM_DECL      (ColorPerVertexField, 
                               ColorIndexField      );
    OSG_RC_ELEM_IDM_DECL      (ConvexField, 
                               ColorPerVertexField  );
    OSG_RC_ELEM_IDM_DECL      (CoordIndexField, 
                               ConvexField          );
    OSG_RC_ELEM_IDM_DECL      (CreaseAngleField, 
                               CoordIndexField      );
    OSG_RC_ELEM_IDM_DECL      (NormalIndexField, 
                               CreaseAngleField     );
    OSG_RC_ELEM_IDM_DECL      (NormalPerVertexField, 
                               NormalIndexField     );
    OSG_RC_ELEM_IDM_DECL      (SolidField,
                               NormalPerVertexField );
    OSG_RC_ELEM_IDM_DECL      (TexCoordIndexField, 
                               SolidField           );

    OSG_RC_ELEM_IDM_DECL      (UpdateNormalModeField,
                               TexCoordIndexField   );

    OSG_RC_LAST_ELEM_IDM_DECL (UpdateNormalModeField);

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
    void operator =(const VRMLIndexedFaceSet &source);

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
    SFVRMLNode _sfCoord;
    SFVRMLNode _sfNormal;
    SFVRMLNode _sfTexCoord;

    SFBool     _sfCcw;
    MFInt32    _mfColorIndex;
    SFBool     _sfColorPerVertex;
    SFBool     _sfConvex;
    MFInt32    _mfCoordIndex;
    SFReal32   _sfCreaseAngle;
    MFInt32    _mfNormalIndex;
    SFBool     _sfNormalPerVertex;
    SFBool     _sfSolid;
    MFInt32    _mfTexCoordIndex;

    SFString   _sfUpdateNormalMode;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    VRMLIndexedFaceSet(void);
    VRMLIndexedFaceSet(const VRMLIndexedFaceSet &source);

  public :

    OSG_VRMLOBJ_DECL(Ptr);

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    virtual ~VRMLIndexedFaceSet(void); 

    /*-------------------------- field access -------------------------------*/

    SFVRMLNode *getSFColor           (void);
    SFVRMLNode *getSFCoord           (void);
    SFVRMLNode *getSFNormal          (void);
    SFVRMLNode *getSFTexCoord        (void);

    SFBool     *getSFCcw             (void);
    MFInt32    *getMFColorIndex      (void);
    SFBool     *getSFColorPerVertex  (void);
    SFBool     *getSFConvex          (void);
    MFInt32    *getMFCoordIndex      (void);
    SFReal32   *getSFCreaseAngle     (void);
    MFInt32    *getMFNormalIndex     (void);
    SFBool     *getSFNormalPerVertex (void);
    SFBool     *getSFSolid           (void);
    MFInt32    *getMFTexCoordIndex   (void);

    SFString   *getSFUpdateNormalMode(void);
};


//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

//! VRMLIndexedFaceSetBinder
//! \ingroup VRMLOSGBindingLib

class OSG_VRML_DLLMAPPING VRMLIndexedFaceSetBinder : 
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
    VRMLIndexedFaceSetBinder(const VRMLIndexedFaceSetBinder &source);
    //! prohibit default function (move to 'public' if needed) 
    void operator =(const VRMLIndexedFaceSetBinder &source);

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

    VRMLIndexedFaceSetBinder(void);

    virtual ~VRMLIndexedFaceSetBinder(void); 

    /*------------------------- your_category -------------------------------*/

    void init        (VRMLToOSGAction *pAction        );

    void setCoords   (VRMLNodeBinder  *pCoordBinder   );
    void setNormals  (VRMLNodeBinder  *pNormalBinder  );
    void setColors   (VRMLNodeBinder  *pColorBinder   );
    void setTexCoords(VRMLNodeBinder  *pTexCoordBinder);

    void finish      (VRMLToOSGAction *pAction        );
};

OSG_END_NAMESPACE

#define OSGVRMLINDEXEDFACESET_HEADER_CVSID "@(#)$Id: $"

#endif /* _OSGVRMLINDEXEDFACESET_HPP_ */
