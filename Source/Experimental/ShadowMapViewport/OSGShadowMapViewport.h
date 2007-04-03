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

#ifndef _OSGSHADOWMAPVIEWPORT_H_
#define _OSGSHADOWMAPVIEWPORT_H_
#ifdef __sgi
#pragma once
#endif

#include <vector>

#include <OSGConfig.h>
#include <OSGAction.h>
#include <OSGRenderActionBase.h>

#include <OSGSpotLight.h>
#include <OSGDirectionalLight.h>
#include <OSGNode.h>
#include "OSGShadowMapViewportBase.h"

#include <OSGPerspectiveCamera.h>
#include <OSGMatrixCamera.h>
#include <OSGTransform.h>
#include <OSGTextureChunk.h>
#include <OSGSimpleMaterial.h>

#include <OSGPassiveBackground.h>
#include <OSGDynamicVolume.h>


#include <OSGTexGenChunk.h>
#include <OSGTextureTransformChunk.h>
#include <OSGPolygonChunk.h>
#include <OSGBlendChunk.h>
#include <OSGTileCameraDecorator.h>

OSG_BEGIN_NAMESPACE


/*! \brief ShadowMapViewport class. See \ref
ShadowMapViewport for a description.
*/

class OSG_SYSTEMLIB_DLLMAPPING ShadowMapViewport : public ShadowMapViewportBase
{
  private:

    typedef ShadowMapViewportBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

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

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    virtual void checkLights(RenderActionBase* action);
    virtual void updateLights(void);
    virtual void initializeLights(RenderActionBase *action);
    virtual void clearLights(UInt32 size);
    virtual void createShadowMaps(RenderActionBase* action);
    virtual void projectShadowMaps(RenderActionBase* action);
    virtual bool extensionCheck();
    virtual void checkMapResolution();

    Action::ResultE findLight(NodePtr& node);
    Action::ResultE findTransparent(NodePtr& node);

    UInt32                  _mapRenderSize;
    bool                    _mapSizeChanged;
    UInt32                  _windowW;
    UInt32                  _windowH;

    TexGenChunkPtr          _texGen;
    PolygonChunkPtr         _poly;
    PolygonChunkPtr         _offset;
    BlendChunkPtr           _blender;
    NodePtr                 _dummy;
    PassiveBackgroundPtr    _silentBack;
    TileCameraDecoratorPtr  _tiledeco;

    std::vector<NodePtr>            _transparent;
    std::vector<LightPtr>           _allLights;
    std::vector<LightPtr>           _lights;
    std::vector<LightPtr>           _oldLights;
    std::vector<CameraPtr>          _lightCameras;
    std::vector<TransformPtr>       _lightCamTrans;
    std::vector<NodePtr>            _lightCamBeacons;
    std::vector<UInt32>             _lightStates;
    std::vector<ImagePtr>           _shadowImages;
    std::vector<TextureChunkPtr>    _texChunks;

    SimpleMaterialPtr               _unlitMat;

    bool                            _trigger_update;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ShadowMapViewport(void);
    ShadowMapViewport(const ShadowMapViewport &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ShadowMapViewport(void);
    
    void onCreate(const ShadowMapViewport *source = NULL);
    void onDestroy(void);

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ShadowMapViewportBase;

    /*---------------------------------------------------------------------*/
    /*! \name            OpenGL Extension Handling                         */
    /*! \{                                                                 */

    static UInt32 _depth_texture_extension;
    static UInt32 _shadow_extension;

    /*! \}                                                                 */

    static void initMethod(void);

    void Initialize();

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ShadowMapViewport &source);
};

typedef ShadowMapViewport *ShadowMapViewportP;

OSG_END_NAMESPACE

#include "OSGShadowMapViewportBase.inl"
#include "OSGShadowMapViewport.inl"

#define OSGSHADOWMAPVIEWPORT_HEADER_CVSID "@(#)$Id: OSGShadowMapViewport.h,v 1.9 2007/04/03 03:16:54 dirk Exp $"

#endif /* _OSGSHADOWMAPVIEWPORT_H_ */
