#ifndef _OSGPERSPECTIVESHADOWMAP_H_
#define _OSGPERSPECTIVESHADOWMAP_H_
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
#include <OSGMatrixCameraDecorator.h>
#include "OSGTreeRenderer.h"

OSG_BEGIN_NAMESPACE

class ShadowViewport;
class TreeRenderer;

class OSG_SYSTEMLIB_DLLMAPPING PerspectiveShadowMap : public TreeRenderer
{
  private:

	bool initFBO(Window *win);
	void reInit(Window *win);
	GLuint fb;
	GLuint fb2;
	GLuint rb_depth;
	UInt32 widthHeightPOT;
	UInt32					activeFactorMap;
	Matrix transforms[6];

	void printMatrix(Matrix m);
	void printPoint(Pnt3f p);

    TileCameraDecoratorPtr		_tiledeco;
	BlendChunkPtr				_blender;
	MatrixCameraPtr				matrixCam2;
    TextureChunkPtr			    _colorMap;
    TextureChunkPtr				_shadowFactorMap;
    ImagePtr					_colorMapImage;
    ImagePtr					_shadowFactorMapImage;
	TextureChunkPtr				_shadowFactorMap2;
	ImagePtr					_shadowFactorMapImage2;
    ChunkMaterialPtr			_shadowCmat;
    ChunkMaterialPtr			_combineCmat;
	SHLChunkPtr					_shadowSHL;
    SHLChunkPtr					_shadowCubeSHL;
	SHLChunkPtr					_shadowSHL2;
	SHLChunkPtr					_shadowSHL3;
	SHLChunkPtr					_shadowSHL4;
	SHLChunkPtr					_shadowSHL5;
	SHLChunkPtr					_shadowSHL6;
	SHLChunkPtr					_shadowSHL7;
    SHLChunkPtr					_combineSHL;
    SimpleMaterialPtr			_unlitMat;
    PolygonForegroundPtr		_pf;

    UInt32						width;
    UInt32						height;
	Int32	                    firstRun;
	
	bool checkFrameBufferStatus(Window *win);
	void createShadowMapsFBO(RenderActionBase* action);
	bool initTexturesDone;
	void initTextures(Window *win);

	std::vector<Matrix>			_perspectiveLPM;
	std::vector<Matrix>			_perspectiveLVM;

    void createShadowMaps(RenderActionBase* action);
	void createShadowMapsNOGLSL(RenderActionBase* action);
	void projectShadowMaps(RenderActionBase* action);
    void createColorMapFBO(RenderActionBase* action);
    void createShadowFactorMapFBO(RenderActionBase* action);
    void createShadowFactorMap(RenderActionBase* action);
    void createColorMap(RenderActionBase* action);
    void drawCombineMap(RenderActionBase* action);
	void calcPerspectiveSpot(Matrix &_LPM, Matrix &_LVM, UInt32 num);
	bool bbInsideFrustum(Pnt3f sceneMin, Pnt3f sceneMax, Matrix LPVM);
	void calcHull2(std::vector<Pnt3f> *points, Matrix invEyeProjMatrix, Pnt3f sceneMin, Pnt3f sceneMax, Matrix LPVM);
	void calcUpVec2(Vec3f &up99,Vec3f viewDir,Vec3f lightDir);
	void calcCubicHull2(Pnt3f &min99, Pnt3f &max99, std::vector<Pnt3f> *points);
	void scaleTranslateToFit2(Matrix &mat, const Pnt3f vMin, const Pnt3f vMax); 
	void calcBodyVec(Vec3f &dir, Pnt3f eyePos, std::vector<Pnt3f> *points);
	bool pntInFrontOf(Pnt3f p1, Pnt3f p2, Pnt3f p3, Pnt3f p);

  public:

	  PerspectiveShadowMap(void);
      PerspectiveShadowMap(ShadowViewport *source);
	  ~PerspectiveShadowMap(void);
	  virtual void render(RenderActionBase* action);
};

OSG_END_NAMESPACE

#endif /* _OSGPERSPECTIVESHADOWMAP_H_ */

