#ifndef _OSGDITHERSHADOWMAP_H_
#define _OSGDITHERSHADOWMAP_H_
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
#include <OSGTileCameraDecorator.h>
#include <OSGDepthChunk.h>

#include "OSGTreeRenderer.h"

OSG_BEGIN_NAMESPACE

class ShadowViewport;
class TreeRenderer;

class OSG_SYSTEMLIB_DLLMAPPING DitherShadowMap : public TreeRenderer
{
public:

    DitherShadowMap(ShadowViewport *source);
    ~DitherShadowMap(void);
    virtual void render(RenderActionBase* action);

  private:

    void createShadowMaps(RenderActionBase* action);
    void createColorMap(RenderActionBase* action);
    void drawCombineMap(RenderActionBase* action);
    void createShadowFactorMap(RenderActionBase* action);
    void createColorMapFBO(RenderActionBase* action);
    void createShadowFactorMapFBO(RenderActionBase* action);
    void createShadowMapsFBO(RenderActionBase* action);
    bool initFBO(Window *win);
    void reInit(Window *win);
    bool checkFrameBufferStatus(Window *win);
    void initTextures(Window *win);

    GLuint                  _fb;
    GLuint                  _fb2;
    GLuint                  _rb_depth;
    Matrix                  _transforms[6];
    TileCameraDecoratorPtr  _tiledeco;
    BlendChunkPtr           _blender;
    TextureChunkPtr         _colorMap;
    TextureChunkPtr         _shadowFactorMap;
    ImagePtr                _colorMapImage;
    ImagePtr                _shadowFactorMapImage;
    ChunkMaterialPtr        _shadowCmat;
    ChunkMaterialPtr        _combineCmat;
    SHLChunkPtr             _shadowSHL;
    SHLChunkPtr             _shadowSHL2;
    SHLChunkPtr             _shadowSHL3;
    SHLChunkPtr             _shadowSHL4;
    SHLChunkPtr             _shadowCubeSHL;
    SHLChunkPtr             _combineSHL;
    DepthChunkPtr           _combineDepth;
    PolygonForegroundPtr    _pf;
    Int32                   _firstRun;
    UInt32                  _width;
    UInt32                  _height;
    UInt32                  _widthHeightPOT;
    UInt32                  _activeFactorMap;
    TextureChunkPtr         _shadowFactorMap2;
    ImagePtr                _shadowFactorMapImage2;
    bool                    _initTexturesDone;
};

OSG_END_NAMESPACE

#endif /* _OSGDITHERSHADOWMAP_H_ */

