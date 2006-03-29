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

class OSG_SYSTEMLIB_DLLMAPPING DitherShadowMap : public TreeRenderer
{
  private:

    TileCameraDecoratorPtr  _tiledeco;
	BlendChunkPtr           _blender;
	MatrixCameraPtr			_matrixCam;

	TextureChunkPtr			_colorMap;
	TextureChunkPtr			_shadowFactorMap;
	ImagePtr				_colorMapImage;
	ImagePtr				_shadowFactorMapImage;

	ChunkMaterialPtr		_shadowCmat;
	SHLChunkPtr				_shadowSHL;
	NodePtr					_shadowRoot;
	MaterialGroupPtr		_shadowShaderGroup;
	
	ChunkMaterialPtr		_combineCmat;
	SHLChunkPtr				_combineSHL;
	NodePtr					_combineRoot;
	MaterialGroupPtr		_combineShaderGroup;

	FileGrabForegroundPtr	fileGrab;
	Int32					firstRun;

	Matrix					textureVM; 
	Matrix					texturePM;

	GeometryPtr				boxGeo;
	NodePtr					boxNode;

	UInt32					width;
	UInt32					height;

    void createShadowMaps(RenderActionBase* action);
	void createColorMap(RenderActionBase* action);
	void drawCombineMap(RenderActionBase* action);
	void createShadowFactorMap(RenderActionBase* action, UInt32 num);
	void drawTextureBoxShader(RenderActionBase* action, ChunkMaterialPtr cmat);


  protected:


    /*==========================  PUBLIC  =================================*/
  public:

	  DitherShadowMap(void);
      DitherShadowMap(ShadowViewport *source);
	  ~DitherShadowMap(void);


	  virtual void render(RenderActionBase* action);

};


OSG_END_NAMESPACE

#endif /* _OSGDITHERSHADOWMAP_H_ */

