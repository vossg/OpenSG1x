
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

#include <OSGPassiveBackground.h>
#include <OSGDynamicVolume.h>


#include <OSGTexGenChunk.h>
#include <OSGTextureTransformChunk.h>
#include <OSGPolygonChunk.h>
#include <OSGBlendChunk.h>
#include <OSGTileCameraDecorator.h>
#include <OSGMatrixCameraDecorator.h>

#include "OSGTreeRenderer.h"


OSG_BEGIN_NAMESPACE

class ShadowViewport;
class TreeRenderer;


class OSG_SYSTEMLIB_DLLMAPPING PerspectiveShadowMap : public TreeRenderer
{
  private:

	bool initFBO(Window *win);
	bool checkFrameBufferStatus(Window *win);

	GLuint fb2;

	void createShadowMapsFBO(RenderActionBase* action);

	void calcPerspective(Matrix &_LPM, Matrix &_LVM, UInt32 num);

	void printMatrix(Matrix m);
	void printPoint(Pnt3f p);

    TileCameraDecoratorPtr		_tiledeco;
	BlendChunkPtr				_blender;
	NodePtr						_dummy;
	MatrixCameraDecoratorPtr	_matrixdeco;
	MatrixCameraPtr				matrixCam;
	
	std::vector<Matrix>  _perspectiveLPM;
	std::vector<Matrix>  _perspectiveLVM;

    void createShadowMaps(RenderActionBase* action);
	void projectShadowMaps(RenderActionBase* action);

	void calcPerspectiveSpot(Matrix &_LPM, Matrix &_LVM, UInt32 num);
	bool bbInsideFrustum(Pnt3f sceneMin, Pnt3f sceneMax, Matrix LPVM);
	
	void calcHull2(std::vector<Pnt3f> *points, Matrix invEyeProjMatrix, Pnt3f sceneMin, Pnt3f sceneMax, Matrix LPVM);
	void calcHull(std::vector<Pnt3f> *points, Matrix invEyeProjMatrix, Pnt3f sceneMin, Pnt3f sceneMax, Vec3f lightDir);

	void calcUpVec2(Vec3f &up99,Vec3f viewDir,Vec3f lightDir);
	void calcCubicHull2(Pnt3f &min99, Pnt3f &max99, std::vector<Pnt3f> *points);
	void scaleTranslateToFit2(Matrix &mat, const Pnt3f vMin, const Pnt3f vMax); 
	void calcBodyVec(Vec3f &dir, Pnt3f eyePos, std::vector<Pnt3f> *points);
	bool pntInFrontOf(Pnt3f p1, Pnt3f p2, Pnt3f p3, Pnt3f p);


  protected:


    /*==========================  PUBLIC  =================================*/
  public:

	  PerspectiveShadowMap(void);
      PerspectiveShadowMap(ShadowViewport *source);
	  ~PerspectiveShadowMap(void);

	  virtual void render(RenderActionBase* action);
};

OSG_END_NAMESPACE

#endif /* _OSGPERSPECTIVESHADOWMAP_H_ */

