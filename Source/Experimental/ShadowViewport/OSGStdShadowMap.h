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

#include <OSGPassiveBackground.h>
#include <OSGDynamicVolume.h>


#include <OSGTexGenChunk.h>
#include <OSGTextureTransformChunk.h>
#include <OSGPolygonChunk.h>
#include <OSGBlendChunk.h>
#include <OSGTileCameraDecorator.h>
#include "OSGTreeRenderer.h"


OSG_BEGIN_NAMESPACE

class ShadowViewport;
class TreeRenderer;

class OSG_SYSTEMLIB_DLLMAPPING StdShadowMap : public TreeRenderer
{
  private:

	bool initFBO(Window *win);

	GLuint fb2;

	bool checkFrameBufferStatus(Window *win);

	void createShadowMapsFBO(RenderActionBase* action);


    TileCameraDecoratorPtr  _tiledeco;
	BlendChunkPtr           _blender;

    void createShadowMaps(RenderActionBase* action);
	void projectShadowMaps(RenderActionBase* action);

  protected:

  public:

	  StdShadowMap(void);
      StdShadowMap(ShadowViewport *source);
	  ~StdShadowMap(void);


	  virtual void render(RenderActionBase* action);

};

OSG_END_NAMESPACE

#endif /* _OSGSHADOWVIEWPORT_H_ */

