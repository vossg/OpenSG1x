/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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
#include <OSGDrawActionBase.h>
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

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

typedef std::pair<UInt32      ,      Matrix                 > MatrixStore;
typedef std::map <Material   *, std::vector<DrawTreeNode *> > MaterialMap;
typedef std::pair<LightChunk *,      Matrix                 > LightStore;

/*! \brief DrawAction class
 */

class OSG_SYSTEMLIB_DLLMAPPING RenderAction : public DrawActionBase
{
  public:

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

    const Matrix &top_matrix (      void          );

    /*------------------------- assignment ----------------------------------*/

    void dropGeometry(Geometry  *pGeo);
    void dropLight   (Light     *pLight);
    void dropFunctor (Material::DrawFunctor &func, Material *mat);

    /*------------------------- comparison ----------------------------------*/

    void setSortTrans(bool bVal);

    /*------------------------- comparison ----------------------------------*/

    // test a single node
    bool            isVisible( Node* node );
    
  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef DrawActionBase Inherited;

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

    Material                 *_pMaterial;

    UInt32                    _uiMatrixId;

    MatrixStore               _currMatrix;
    Matrix                    _camInverse;
    Matrix                    _accMatrix;

    std::vector<MatrixStore>  _vMatrixStack;

    MaterialMap               _mMatMap;
    
    DrawTreeNode             *_pRoot;
    DrawTreeNode             *_pMatRoot;
    DrawTreeNode             *_pTransMatRoot;

    UInt32                    _uiActiveMatrix;
    State                    *_pActiveState;

    UInt32                    _uiNumMaterialChanges;
    UInt32                    _uiNumMatrixChanges;
    UInt32                    _uiNumGeometries;
    UInt32                    _uiNumTransGeometries;
 
    bool                      _bSortTrans;

    std::vector<LightStore>   _vLights;

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
    void draw(DrawTreeNode *pRoot);

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

// class pointer

typedef RenderAction *RenderActionP;

OSG_END_NAMESPACE

#include "OSGRenderAction.inl"

#endif /* _OSGRENDERACTION_H_ */


