/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2002 by the OpenSG Forum                 *
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

#ifndef _OSGSHADOWVIEWPORT_H_
#define _OSGSHADOWVIEWPORT_H_
#ifdef __sgi
#pragma once
#endif

#include <vector>
#include <utility>

#include <OSGConfig.h>
#include <OSGAction.h>
#include <OSGRenderActionBase.h>
#include <OSGSpotLight.h>
#include <OSGDirectionalLight.h>
#include <OSGNode.h>
#include "OSGShadowViewportBase.h"
#include <OSGPerspectiveCamera.h>
#include <OSGMatrixCamera.h>
#include <OSGTransform.h>
#include <OSGTextureChunk.h>
#include <OSGPassiveBackground.h>
#include <OSGDynamicVolume.h>
#include <OSGTexGenChunk.h>
#include <OSGTextureTransformChunk.h>
#include <OSGPolygonChunk.h>
#include <OSGBlendChunk.h>
#include <OSGTileCameraDecorator.h>
#include "OSGTreeRenderer.h"

OSG_BEGIN_NAMESPACE

class OSG_SYSTEMLIB_DLLMAPPING ShadowViewport : public ShadowViewportBase
{
  private:

    friend class FieldContainer;
    friend class ShadowViewportBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ShadowViewport &source);

    bool            _GLSLsupported;
    bool            _initDone;
    bool            _restart;
    TreeRenderer    *_treeRenderer;

    typedef ShadowViewportBase Inherited;

    void checkLights(RenderActionBase* action);
    void updateLights(void);
    void initializeLights(RenderActionBase *action);
    void clearLights(UInt32 size);

    Action::ResultE findLight(NodePtr& node);
    Action::ResultE findTransparent(NodePtr& node);

    /*==========================  PUBLIC  =================================*/
  public:

    enum Mode
    {
        NO_SHADOW=0,
        STD_SHADOW_MAP,
        PERSPECTIVE_SHADOW_MAP,
        DITHER_SHADOW_MAP,
        PCF_SHADOW_MAP,
        PCSS_SHADOW_MAP,
        VARIANCE_SHADOW_MAP
    };

    UInt32                  _mapRenderSize;
    bool                    _mapSizeChanged;

    TexGenChunkPtr          _texGen;
    PolygonChunkPtr         _poly;
    PolygonChunkPtr         _offset;
    NodePtr                 _dummy;
    PassiveBackgroundPtr    _silentBack;
    UInt32                  _windowW;
    UInt32                  _windowH;

    std::vector<NodePtr>                        _transparent;
    std::vector<std::pair<NodePtr, LightPtr> >  _lights;
    std::vector<std::pair<NodePtr, LightPtr> >  _oldLights;
    std::vector<CameraPtr>                      _lightCameras;
    std::vector<TransformPtr>                   _lightCamTrans;
    std::vector<NodePtr>                        _lightCamBeacons;
    std::vector<UInt32>                         _lightStates;
    std::vector<ImagePtr>                       _shadowImages;
    std::vector<TextureChunkPtr>                _texChunks;
    std::vector<bool>                           _excludeNodeActive;
    std::vector<bool>                           _realPointLight;
    std::vector<bool*>                          _renderSide;

    bool                            _trigger_update;
    Matrix                          _transforms[6];

    NodePtr                         _light_render_transform;
    GLuint                          _occlusionQuery;

    virtual void setVPSize   (Real32 a,Real32 b, Real32 c, Real32 d);
    virtual void activateSize(void);
    virtual void activate    (void);
    virtual void deactivate  (void);
    virtual void render      (RenderActionBase* action);

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    void triggerMapUpdate(void);

    void renderLight(RenderActionBase *action, Material *mat, UInt32 index);
    NodePtr getLightRoot(UInt32 index);

    void checkLightsOcclusion(RenderActionBase *action);
    void setReadBuffer(void);

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:


    // Variables should all be in ShadowViewportBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ShadowViewport(void);
    ShadowViewport(const ShadowViewport &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShadowViewport(void); 

    void onCreate(const ShadowViewport *source = NULL);
    void onDestroy(void);


    /*! \}                                                                 */
    
};

typedef ShadowViewport *ShadowViewportP;

OSG_END_NAMESPACE

#include <OSGShadowViewportBase.inl>
#include <OSGShadowViewport.inl>

#define OSGSHADOWVIEWPORT_HEADER_CVSID "@(#)$Id: OSGShadowViewport.h,v 1.14 2007/04/03 03:16:54 dirk Exp $"

#endif /* _OSGSHADOWVIEWPORT_H_ */
