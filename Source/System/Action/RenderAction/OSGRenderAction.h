/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#ifndef _OSGRENDERACTION_H_
#define _OSGRENDERACTION_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <vector>

#include <OSGSystemDef.h>
#include <OSGBaseTypes.h>
#include <OSGRenderActionBase.h>
#include <OSGMatrix.h>
#include <OSGMaterial.h>
#include <OSGStatElemTypes.h>

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class Material;
class DrawTreeNode;
class Geometry;
class State;
class Light;
class LightChunk;

#if defined(OSG_OPT_DRAWTREE)
class DrawTreeNodeFactory;
#endif

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief RenderAction class
 */

class OSG_SYSTEMLIB_DLLMAPPING RenderAction : public RenderActionBase
{
  public:

    typedef std::pair<UInt32      ,      Matrix                 > MatrixStore;
    typedef std::map <Material   *,      DrawTreeNode *         > MaterialMap;
    typedef std::pair<LightChunk *,      Matrix                 > LightStore;
    typedef std::map<Light       *,      UInt32                 > LightsMap;
  
    //-----------------------------------------------------------------------
    //   constants                                                               
    //-----------------------------------------------------------------------

    static StatElemDesc<StatTimeElem> statDrawTime;
    static StatElemDesc<StatIntElem > statNMaterials;
    static StatElemDesc<StatIntElem > statNMatrices;
    static StatElemDesc<StatIntElem > statNGeometries;
    static StatElemDesc<StatIntElem > statNTransGeometries;

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------
  
    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static RenderAction *create      (void                    );
    
    static void          setPrototype(RenderAction *pPrototype);
    static RenderAction *getPrototype(void                    );


    static void registerEnterDefault (const FieldContainerType &type, 
                                      const Action::Functor    &func);
    
    static void registerLeaveDefault (const FieldContainerType &type, 
                                      const Action::Functor    &func);

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    virtual ~RenderAction(void); 

    /*------------------------- your_category -------------------------------*/

    Material   *getMaterial  (void               ) const;
    void        setMaterial  (Material *pMaterial);
    
    virtual Action::ResultE start(void       );
    virtual Action::ResultE stop (ResultE res); 

    /*------------------------- your_operators ------------------------------*/

           void          push_matrix(const Matrix &matrix);
           void          pop_matrix (      void          );

    inline const Matrix &top_matrix (      void          );

    /*------------------------- assignment ----------------------------------*/

    void dropGeometry(Geometry  *pGeo);
    void dropLight     (Light     *pLight);
    void undropLight   (Light     *pLight);
    void dropFunctor (Material::DrawFunctor &func, Material *mat);

    void setStateSorting(bool s);
    bool getStateSorting(void);

    /*------------------------- comparison ----------------------------------*/

    void setSortTrans(bool bVal);
    bool getSortTrans(void);
    void setZWriteTrans(bool bVal);
    bool getZWriteTrans(void);
    void setLocalLights(bool bVal);
    bool getLocalLights(void);
    void setCorrectTwoSidedLighting(bool bVal);
    bool getCorrectTwoSidedLighting(void);

    /*------------------------- comparison ----------------------------------*/

    // test a single node
    bool            isVisible( Node* node );
    
    // visibility levels
    bool  pushVisibility(void);
    void  popVisibility(void);
    
  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef RenderActionBase Inherited;

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    static RenderAction    *_pPrototype;

    static std::vector<Functor> *_vDefaultEnterFunctors;
    static std::vector<Functor> *_vDefaultLeaveFunctors;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

#if defined(OSG_OPT_DRAWTREE)
    DrawTreeNodeFactory      *_pNodeFactory;
#endif

    Material                 *_pMaterial;

    UInt32                    _uiMatrixId;

    MatrixStore               _currMatrix;
    Matrix                    _camInverse;
    Matrix                    _accMatrix;

    std::vector<MatrixStore>  _vMatrixStack;

    MaterialMap               _mMatMap;
    
    //DrawTreeNode             *_pRoot;
    std::vector<DrawTreeNode *> _pMatRoots;
    std::vector<DrawTreeNode *> _pTransMatRoots;
    DrawTreeNode               *_pNoStateSortRoot;
    DrawTreeNode               *_pNoStateSortTransRoot;

    UInt32                    _uiActiveMatrix;
    State                    *_pActiveState;

    UInt32                    _uiNumMaterialChanges;
    UInt32                    _uiNumMatrixChanges;
    UInt32                    _uiNumGeometries;
    UInt32                    _uiNumTransGeometries;
 
    bool                      _bSortTrans;
    bool                      _bZWriteTrans;
    bool                      _bLocalLights;
    bool                      _bCorrectTwoSidedLighting;

    std::vector<LightStore>   _vLights;
    LightsMap                 _lightsMap;
    UInt64                    _lightsState;
    UInt64                    _activeLightsState;
    UInt32                    _activeLightsCount;

    bool                      _stateSorting;

    std::vector<FrustumVolume::PlaneSet>  _visibilityStack;

//    Time                 _tMatSlot

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    // prohibit default functions (move to 'public' if you need one)

    RenderAction(void);
    RenderAction(const RenderAction &source);

    void operator =(const RenderAction &source);

    // access default functors

    virtual std::vector<Functor> *getDefaultEnterFunctors(void);
    virtual std::vector<Functor> *getDefaultLeaveFunctors(void);

            void dump(DrawTreeNode *pRoot, UInt32 uiIndent);
    virtual void draw(DrawTreeNode *pRoot);

    inline  void updateTopMatrix(void);
            void activateLocalLights(DrawTreeNode *pRoot);

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

    static char cvsid[];
    
    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------
    
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

OSG_END_NAMESPACE

#include "OSGRenderAction.inl"

#endif /* _OSGRENDERACTION_H_ */


