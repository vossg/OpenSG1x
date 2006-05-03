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

//class PCSSShadowMap;

class OSG_SYSTEMLIB_DLLMAPPING ShadowViewport : public ShadowViewportBase
{
  private:

	//friend PCSSShadowMap;

    typedef ShadowViewportBase Inherited;
	TreeRenderer *treeRenderer;

    void checkLights(RenderActionBase* action);
    void updateLights(void);
    void initializeLights(RenderActionBase *action);
    void clearLights(UInt32 size);
    void checkMapResolution();

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
		PCSS_SHADOW_MAP
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

    bool                            _trigger_update;


	void setVPSize(UInt32 a,UInt32 b, UInt32 c, UInt32 d);

    void render(RenderActionBase* action);

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
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ShadowViewportBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ShadowViewport &source);
};

typedef ShadowViewport *ShadowViewportP;

OSG_END_NAMESPACE

#include <OSGShadowViewportBase.inl>
#include <OSGShadowViewport.inl>

#define OSGSHADOWVIEWPORT_HEADER_CVSID "@(#)$Id: OSGShadowViewport.h,v 1.4 2006/05/03 16:20:31 yjung Exp $"

#endif /* _OSGSHADOWVIEWPORT_H_ */
