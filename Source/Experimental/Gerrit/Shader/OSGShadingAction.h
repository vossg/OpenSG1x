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

#ifndef _OSGSHADINGACTION_H_
#define _OSGSHADINGACTION_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <vector>

#include "OSGShaderBase.h"
#include "OSGBaseTypes.h"
#include "OSGRenderActionBase.h"

#include "OSGMatrix.h"
#include "OSGStatElemTypes.h"

#include "OSGShadingMaterial.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class ShadingGeometry;

class LightSet;
class Light;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

typedef std::pair<UInt32 , Matrix > MatrixStore;

/*! \brief DrawAction class
 */

class OSG_SHADER_DLLMAPPING ShadingAction : public RenderActionBase
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

    static ShadingAction *create      (     void                          );
    
    static void           setPrototype(     ShadingAction      *pPrototype);
    static ShadingAction *getPrototype(     void                          );


    static void registerEnterDefault (const FieldContainerType &type, 
                                      const Action::Functor    &func      );
    
    static void registerLeaveDefault (const FieldContainerType &type, 
                                      const Action::Functor    &func      );

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    virtual ~ShadingAction(void); 

    /*------------------------- your_category -------------------------------*/

    ShadingMaterial *getMaterial(void                      ) const;
    void             setMaterial(ShadingMaterial *pMaterial);
    
    /*------------------------- your_operators ------------------------------*/

    virtual Action::ResultE start(void       );
    virtual Action::ResultE stop (ResultE res); 

    /*------------------------- your_operators ------------------------------*/

    void          push_matrix(const Matrix &matrix);
    void          pop_matrix (      void          );

    const Matrix &top_matrix (      void          );

    /*------------------------- assignment ----------------------------------*/

    void dropGeometry(ShadingGeometry       *pGeo  );
    void dropLight   (Light                 *pLight);
    void dropFunctor (Material::DrawFunctor &func, 
                      ShadingMaterial       *mat   );

    /*------------------------- comparison ----------------------------------*/

    void setSortTrans  (bool bVal);
    void setZWriteTrans(bool bVal);

    /*------------------------- comparison ----------------------------------*/

    // test a single node
    bool isVisible(Node *node);
    
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

    static ShadingAction        *_pPrototype;

    static std::vector<Functor> *_vDefaultEnterFunctors;
    static std::vector<Functor> *_vDefaultLeaveFunctors;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

    UInt32                    _uiMatrixId;

    MatrixStore               _currMatrix;
    Matrix                    _camInverse;
    Matrix                    _accMatrix;

    std::vector<MatrixStore>  _vMatrixStack;

    UInt32                    _uiActiveMatrix;
 
    bool                      _bSortTrans;
    bool                      _bZWriteTrans;

    UInt32                    _uiNumMaterialChanges;
    UInt32                    _uiNumMatrixChanges;
    UInt32                    _uiNumGeometries;
    UInt32                    _uiNumTransGeometries;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    // prohibit default functions (move to 'public' if you need one)

    ShadingAction(void);
    ShadingAction(const ShadingAction &source);

    // access default functors

    virtual std::vector<Functor> *getDefaultEnterFunctors(void);
    virtual std::vector<Functor> *getDefaultLeaveFunctors(void);

//            void dump(DrawTreeNode *pRoot, UInt32 uiIndent);
//    virtual void draw(DrawTreeNode *pRoot);

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

    /*!\brief prohibit default function (move to 'public' if needed) */
    void operator =(const ShadingAction &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

OSG_END_NAMESPACE

#define OSGSHADINGACTION_HEADER_CVSID "@(#)$Id: $"

#include "OSGShadingAction.inl"

#endif /* _OSGSHADINGACTION_H_ */


