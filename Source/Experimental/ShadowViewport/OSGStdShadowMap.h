#ifndef _OSGSTDSHADOWMAP_H_
#define _OSGSTDSHADOWMAP_H_
#ifdef __sgi
#pragma once
#endif

#include <vector>
#include <OSGConfig.h>
#include <OSGAction.h>
#include <OSGRenderActionBase.h>
#include <OSGSpotLight.h>
#include <OSGDirectionalLight.h>
#include <OSGPerspectiveCamera.h>
#include <OSGMatrixCamera.h>
#include <OSGTransform.h>
#include <OSGTextureChunk.h>
#include <OSGSimpleMaterial.h>
#include <OSGPassiveBackground.h>
#include <OSGSolidBackground.h>
#include <OSGDynamicVolume.h>
#include <OSGChunkMaterial.h>
#include <OSGMaterialChunk.h>
#include <OSGMaterialGroup.h>
#include <OSGSHLChunk.h>
#include <OSGForeground.h>
#include <OSGPolygonForeground.h>
#include <OSGGrabForeground.h>
#include <OSGTextureGrabForeground.h>
#include <OSGFileGrabForeground.h>
#include <OSGImageForeground.h>
#include <OSGTexGenChunk.h>
#include <OSGTextureTransformChunk.h>
#include <OSGPolygonChunk.h>
#include <OSGBlendChunk.h>
#include <OSGSimpleTexturedMaterial.h>
#include <OSGTileCameraDecorator.h>
#include <OSGPolygonForeground.h>
#include <OSGDepthChunk.h>

#include "OSGTreeRenderer.h"

OSG_BEGIN_NAMESPACE

class ShadowViewport;
class TreeRenderer;

class OSG_SYSTEMLIB_DLLMAPPING StdShadowMap : public TreeRenderer
{
  public:

    StdShadowMap(ShadowViewport *source);
    ~StdShadowMap(void);
    virtual void render(RenderActionBase* action);

  private:

    bool initFBO(Window *win);
    void reInit(Window *win);
    
    void initTextures(Window *win);
    bool checkFrameBufferStatus(Window *win);
    void createShadowMapsFBO(RenderActionBase* action);
    void createShadowMaps(RenderActionBase* action);
    void createShadowMapsNOGLSL(RenderActionBase* action);
    void projectShadowMaps(RenderActionBase* action);
    void createColorMapFBO(RenderActionBase* action);
    void createShadowFactorMapFBO(RenderActionBase* action);
    void createShadowFactorMap(RenderActionBase* action);
    void createColorMap(RenderActionBase* action);
    void drawCombineMap(RenderActionBase* action);

    GLuint _fb;
    GLuint _fb2;
    GLuint _rb_depth;
    UInt32 _activeFactorMap;
    UInt32 _widthHeightPOT;
    Matrix _transforms[6];
    
    TileCameraDecoratorPtr  _tiledeco;
    BlendChunkPtr           _blender;
    TextureChunkPtr         _colorMap;
    TextureChunkPtr         _shadowFactorMap;
    ImagePtr                _colorMapImage;
    ImagePtr                _shadowFactorMapImage;
    TextureChunkPtr         _shadowFactorMap2;
    ImagePtr                _shadowFactorMapImage2;
    ChunkMaterialPtr        _shadowCmat;
    ChunkMaterialPtr        _combineCmat;
    SHLChunkPtr             _shadowSHL;
    SHLChunkPtr             _shadowCubeSHL;
    SHLChunkPtr             _shadowSHL2;
    SHLChunkPtr             _shadowSHL3;
    SHLChunkPtr             _shadowSHL4;
    SHLChunkPtr             _shadowSHL5;
    SHLChunkPtr             _shadowSHL6;
    SHLChunkPtr             _shadowSHL7;
    SHLChunkPtr             _combineSHL;
    DepthChunkPtr           _combineDepth;
    PolygonForegroundPtr    _pf;
    Int32                   _firstRun;
    UInt32                  _width;
    UInt32                  _height;
    bool                    _initTexturesDone;
};

OSG_END_NAMESPACE

#endif /* _OSGSTDSHADOWMAP_H_ */

