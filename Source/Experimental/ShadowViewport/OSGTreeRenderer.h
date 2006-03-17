
#ifndef _OSGTREERENDERER_H_
#define _OSGTREERENDERER_H_
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


OSG_BEGIN_NAMESPACE

class ShadowViewport;

class OSG_SYSTEMLIB_DLLMAPPING TreeRenderer
{
  private:
 
/*==========================  PUBLIC  =================================*/
  public:

  TreeRenderer(void);
  TreeRenderer(ShadowViewport *source);

  virtual ~TreeRenderer(void);

  virtual void render(RenderActionBase *action)=0;


  protected:

  ShadowViewport *shadowVP;

};

OSG_END_NAMESPACE


#endif /* _OSGTREERENDERER_H_ */
