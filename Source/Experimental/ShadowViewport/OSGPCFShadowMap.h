#ifndef _OSGPCFSHADOWMAP_H_
#define _OSGPCFSHADOWMAP_H_
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
#include "OSGTreeRenderer.h"


OSG_BEGIN_NAMESPACE

class ShadowViewport;
class TreeRenderer;

class OSG_SYSTEMLIB_DLLMAPPING PCFShadowMap : public TreeRenderer
{
  private:

    TileCameraDecoratorPtr  _tiledeco;
    BlendChunkPtr           _blender;
    MatrixCameraPtr         _matrixCam;

    TextureChunkPtr         _colorMap;
    TextureChunkPtr         _shadowFactorMap;
    ImagePtr                _colorMapImage;
    ImagePtr                _shadowFactorMapImage;

    ChunkMaterialPtr        _shadowCmat;
    SHLChunkPtr             _shadowSHL;

    SHLChunkPtr             _combineSHL;

    Int32                   _firstRun;

    Matrix                  _textureVM; 
    Matrix                  _texturePM;

    NodePtr                 _boxNode;

    UInt32                  _width;
    UInt32                  _height;
    UInt32                  _widthHeightPOT;

    void createShadowMaps(RenderActionBase* action);
    void createColorMap(RenderActionBase* action);
    void drawCombineMap(RenderActionBase* action);
    void createShadowFactorMap(RenderActionBase* action, UInt32 num);
    void drawTextureBoxShader(RenderActionBase* action);

    void createColorMapFBO(RenderActionBase* action);
    void createShadowFactorMapFBO(RenderActionBase* action, UInt32 num);
    void createShadowMapsFBO(RenderActionBase* action);

    void getCameraViewingMatrix(Matrix &CVM);

    bool initFBO(Window *win);
    void reInit(Window *win);
    bool checkFrameBufferStatus(Window *win);

    GLuint _fb;
    GLuint _fb2;
    GLuint _rb_depth;

    Real32 _oldRange;

  protected:

    /*==========================  PUBLIC  =================================*/
  public:

    PCFShadowMap(void);
    PCFShadowMap(ShadowViewport *source);
    ~PCFShadowMap(void);

    virtual void render(RenderActionBase* action);
};






OSG_END_NAMESPACE

#endif /* _OSGPCFSHADOWMAP_H_ */

