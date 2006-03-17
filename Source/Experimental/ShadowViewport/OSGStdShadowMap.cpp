#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>
#include <OSGTypedFunctors.h>
#include <OSGQuaternion.h>
#include <OSGDrawAction.h>

#include <OSGMatrix.h>
#include <OSGMatrixUtility.h>

#include <OSGBackground.h>
#include <OSGForeground.h>
#include <OSGImage.h>

#include <OSGLight.h>

#include "OSGStdShadowMap.h"
#include "OSGShadowViewport.h"
#include "OSGTreeRenderer.h"


//--------------------------------------------------------------------
#ifndef GL_CLAMP_TO_EDGE
#   define GL_CLAMP_TO_EDGE    0x812F
#endif
#ifndef GL_CLAMP_TO_BORDER_ARB
#   define GL_CLAMP_TO_BORDER_ARB  0x812D
#endif
#ifndef GL_ARB_depth_texture
#   define GL_DEPTH_COMPONENT16_ARB    0x81A5
#   define GL_DEPTH_COMPONENT24_ARB    0x81A6
#   define GL_DEPTH_COMPONENT32_ARB    0x81A7
#   define GL_TEXTURE_DEPTH_SIZE_ARB   0x884A
#   define GL_DEPTH_TEXTURE_MODE_ARB   0x884B
#endif
#ifndef GL_ARB_shadow
#   define GL_TEXTURE_COMPARE_MODE_ARB 0x884C
#   define GL_TEXTURE_COMPARE_FUNC_ARB 0x884D
#   define GL_COMPARE_R_TO_TEXTURE_ARB 0x884E
#endif
#ifndef GL_SGIX_depth_texture
#   define GL_DEPTH_COMPONENT16_SGIX   0x81A5
#   define GL_DEPTH_COMPONENT24_SGIX   0x81A6
#   define GL_DEPTH_COMPONENT32_SGIX   0x81A7
#endif
#ifndef GL_SGIX_shadow
#   define GL_TEXTURE_COMPARE_SGIX             0x819A
#   define GL_TEXTURE_COMPARE_OPERATOR_SGIX    0x819B
#   define GL_TEXTURE_LEQUAL_R_SGIX            0x819C
#   define GL_TEXTURE_GEQUAL_R_SGIX            0x819D
#endif
#ifndef GL_DEPTH_COMPONENT_ARB
#   define GL_DEPTH_COMPONENT_ARB            0x1902
#endif


//--------------------------------------------------------------------

OSG_USING_NAMESPACE

StdShadowMap::StdShadowMap(void)
{
}

StdShadowMap::StdShadowMap(ShadowViewport *source)
: TreeRenderer(source)
{
    _tiledeco = TileCameraDecorator::create();
    addRefCP(_tiledeco);

    _blender = BlendChunk::create();
    addRefCP(_blender);
    beginEditCP(_blender);
    {
        _blender->setAlphaFunc(GL_GEQUAL);
        _blender->setAlphaValue(0.99);
    }
    endEditCP(_blender);

	printf("Constructor StdShadowMap 2\n");
}

StdShadowMap::~StdShadowMap(void)
{
	subRefCP(_tiledeco);
	subRefCP(_blender);
}

void StdShadowMap::createShadowMaps(RenderActionBase* action)
{
    Real32 vpTop,vpBottom,vpLeft,vpRight;
    
    // Saving original Viewport-Dimensions
    vpTop = shadowVP->getTop();
    vpBottom = shadowVP->getBottom();
    vpLeft = shadowVP->getLeft();
    vpRight = shadowVP->getRight();

    glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
    glShadeModel(GL_FLAT);
    glDisable(GL_LIGHTING);
    glDepthMask(GL_TRUE);

    // disable all lights more speed
    for(UInt32 i = 0; i < shadowVP->_lights.size(); ++i)
    {
        if(shadowVP->_lightStates[i] != 0)
            shadowVP->_lights[i]->setOn(false);
    }
    
    // deactivate exclude nodes:
    for(UInt32 i = 0; i < shadowVP->getExcludeNodes().getSize(); ++i)
    {
        NodePtr exnode = shadowVP->getExcludeNodes()[i];
        if(exnode != NullFC)
            exnode->setActive(false);
    }
    
    for(UInt32 i = 0; i< shadowVP->_lights.size(); ++i)
    {
        if(shadowVP->_lightStates[i] != 0)
        {

            // we use a tiledecorator to create shadow maps with
            // a higher resolutions than the viewport or the screen.
			beginEditCP(_tiledeco);
            _tiledeco->setDecoratee(shadowVP->_lightCameras[i]);
            _tiledeco->setFullSize(shadowVP->getMapSize(), shadowVP->getMapSize());
			endEditCP(_tiledeco);

            action->setCamera    (_tiledeco.getCPtr());

			Real32 imgHeight = shadowVP->getMapSize();
			Real32 winHeight = shadowVP->getParent()->getHeight();
			Real32 imgWidth = shadowVP->getMapSize();
			Real32 winWidth = shadowVP->getParent()->getWidth();
			UInt32 x1, x2, y1, y2, tw, th;
				
			for (y1=0; y1 < imgHeight; y1 += winHeight)
				{
					y2 = osgMin((float)(y1+winHeight-1), (float)(imgHeight-1));
					th = y2 - y1 + 1;
					
					for (x1=0; x1 < imgWidth; x1 += winWidth)
					{
						x2 = osgMin((float)(x1+winWidth-1), (float)(imgWidth-1));
						tw = x2 - x1 + 1;
						
						// set tile size to maximal renderable size
						beginEditCP(_tiledeco);
							_tiledeco->setSize(  x1/(float)imgWidth,     y1/(float)imgHeight,	(x2+1)/(float)imgWidth, (y2+1)/(float)imgHeight);
						endEditCP(_tiledeco);
						
						beginEditCP(shadowVP->getCamera(), shadowVP->LeftFieldMask | shadowVP->RightFieldMask |
											  shadowVP->BottomFieldMask | shadowVP->TopFieldMask);
							shadowVP->setSize(0, 0, tw-1, th-1);
						endEditCP(shadowVP->getCamera(), shadowVP->LeftFieldMask | shadowVP->RightFieldMask |
											shadowVP->BottomFieldMask | shadowVP->TopFieldMask);
						
						
					glClear(GL_DEPTH_BUFFER_BIT);
                    shadowVP->_poly->activate(action,0);

                    action->apply(shadowVP->getRoot());
                    // check is this necessary.
                    action->getWindow()->validateGLObject(shadowVP->_texChunks[i]->getGLId());

                    shadowVP->_poly->deactivate(action,0);
        
                    //----------Shadow-Texture-Parameters and Indices-------------
                
                    // action->getWindow()->getGLObjectId(getGLId())
                    //glBindTexture(GL_TEXTURE_2D,shadowVP->_texChunks[i]->getGLId());
                    glBindTexture(GL_TEXTURE_2D, action->getWindow()->getGLObjectId(shadowVP->_texChunks[i]->getGLId()));
                    if(glGetError() != GL_NO_ERROR)
                        SWARNING << "Error on binding Texture!" << endLog;    

						glCopyTexSubImage2D(GL_TEXTURE_2D, 0, x1, y1, 0, 0, tw, th);
				
						if(glGetError() != GL_NO_ERROR)
                        SWARNING << "Error on copying Texture!" << endLog;    
        
                    glBindTexture(GL_TEXTURE_2D,0);
                    if(glGetError() != GL_NO_ERROR)
                        SWARNING << "Error on releasing Texture!" << endLog;    
        
                    if(glGetError() != GL_NO_ERROR)
                        SWARNING << "Error while Texture-Creation!" << endLog;
						
					}
				}

        }
    }

    // activate exclude nodes:
    for(UInt32 i = 0; i < shadowVP->getExcludeNodes().getSize(); ++i)
    {
        NodePtr exnode = shadowVP->getExcludeNodes()[i];
        if(exnode != NullFC)
            exnode->setActive(true);
    }

    // enable all lights.
    for(UInt32 i = 0; i< shadowVP->_lights.size(); ++i)
    {
        if(shadowVP->_lightStates[i] != 0)
            shadowVP->_lights[i]->setOn(true);
    }

    //-------Restoring old states of Window and Viewport----------
    
    beginEditCP(shadowVP->getCamera(), shadowVP->LeftFieldMask | shadowVP->RightFieldMask |
                          shadowVP->BottomFieldMask | shadowVP->TopFieldMask);
    {
        shadowVP->setSize(vpLeft,vpBottom,vpRight,vpTop);
    }
    endEditCP(shadowVP->getCamera(), shadowVP->LeftFieldMask | shadowVP->RightFieldMask |
                        shadowVP->BottomFieldMask | shadowVP->TopFieldMask);

    action->setCamera(shadowVP->getCamera().getCPtr());
    
    glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
}

void StdShadowMap::projectShadowMaps(RenderActionBase* action)
{
    Matrix viewMatrix, projectionMatrix, biasMatrix;
    Vec4f s,t,r,q;

    biasMatrix.setIdentity();
    biasMatrix.setScale(0.5);
    biasMatrix.setTranslate(0.5,0.5,0.5);

    GLint pl=shadowVP->getPixelLeft(), pr=shadowVP->getPixelRight(), pb=shadowVP->getPixelBottom(), 
    pt=shadowVP->getPixelTop();
    GLint pw=pr-pl+1,ph=pt-pb+1;
    bool full = shadowVP->isFullWindow();

    glViewport(pl, pb, pw, ph);
    glScissor(pl, pb, pw, ph);

    if(!full)
        glEnable(GL_SCISSOR_TEST);

    // draw background
    shadowVP->getBackground()->clear(action, shadowVP);

    //---Draw/Render-Pass with ambient light only & no shadows------

	std::vector<int>     light_state;
    std::vector<Color4f> _light_specular;
    std::vector<Color4f> _light_diffuse;
    std::vector<Color4f> _light_ambient;
    Color4f shadow_color = shadowVP->getShadowColor() * (1.0 / Real32(shadowVP->_lights.size()));

    for(UInt32 j=0;j<shadowVP->_lights.size();++j) // Switching off specular highlights
    {
        _light_specular.push_back(shadowVP->_lights[j]->getSpecular());
        _light_diffuse.push_back(shadowVP->_lights[j]->getDiffuse());
        _light_ambient.push_back(shadowVP->_lights[j]->getAmbient());

        shadowVP->_lights[j]->setSpecular(0.0,0.0,0.0,1.0);
        shadowVP->_lights[j]->setDiffuse(shadow_color);
    }

    // render
    action->apply(shadowVP->getRoot());

	// get all lights
    for(UInt32 j=0;j<shadowVP->_lights.size();++j) // Switching on specular highlights
    {
        shadowVP->_lights[j]->setSpecular(_light_specular[j]);
        shadowVP->_lights[j]->setDiffuse(_light_diffuse[j]);
        shadowVP->_lights[j]->setAmbient(0.0,0.0,0.0,1.0);
    }  
	for(UInt32 j=0;j<shadowVP->_allLights.size();++j) {
        light_state.push_back(shadowVP->_allLights[j]->getOn());
        shadowVP->_allLights[j]->setOn(false);
    }

    beginEditCP(_blender);
    {
        _blender->setSrcFactor(GL_ONE);
        _blender->setDestFactor(GL_ONE);
        _blender->setAlphaFunc(GL_GEQUAL);
        _blender->setAlphaValue(0.99);
    }
    endEditCP(_blender);

	// switch off all transparent geos
    for(UInt32 t=0;t<shadowVP->_transparent.size();++t)
        shadowVP->_transparent[t]->setActive(false);

    beginEditCP(shadowVP->_offset);
    shadowVP->_offset->setOffsetBias(-1);
    shadowVP->_offset->setOffsetFactor(0);
    shadowVP->_offset->setOffsetFill(true);
    endEditCP(shadowVP->_offset);

    glDepthFunc(GL_LESS);

    //---Render-Pass with Shadow-----------------------------    
    for(UInt32 i=0;i<shadowVP->_lights.size();++i)
    {
        if(shadowVP->_lightStates[i] != 0)
        {
            shadowVP->_lightCameras[i]->getProjection(projectionMatrix,shadowVP->getMapSize(),shadowVP->getMapSize());

            shadowVP->_lightCameras[i]->getViewing(viewMatrix,shadowVP->getPixelWidth()/*_mapRenderSize*/,
                                         shadowVP->getPixelHeight()/*_mapRenderSize*/);

            Matrix textureMatrix = biasMatrix;
            textureMatrix.mult(projectionMatrix);
            textureMatrix.mult(viewMatrix);
            
            textureMatrix.transpose();
            Vec4f ps = textureMatrix[0];
            Vec4f pt = textureMatrix[1];
            Vec4f pr = textureMatrix[2];
            Vec4f pq = textureMatrix[3];

            beginEditCP(shadowVP->_texGen);
                shadowVP->_texGen->setGenFuncSPlane(ps);
                shadowVP->_texGen->setGenFuncTPlane(pt);
                shadowVP->_texGen->setGenFuncRPlane(pr);
                shadowVP->_texGen->setGenFuncQPlane(pq);
            endEditCP(shadowVP->_texGen);
            
            shadowVP->_lights[i]->setOn(true);
        
            shadowVP->_texChunks[i]->activate(action,3);

            shadowVP->_texGen->activate(action,3);

            _blender->activate(action,0);

			shadowVP->_offset->activate(action,0);
            action->apply(shadowVP->getRoot());
			shadowVP->_offset->deactivate(action,0);

            _blender->deactivate(action,0);

            shadowVP->_texGen->deactivate(action,3);

            shadowVP->_texChunks[i]->deactivate(action,3);
        
            shadowVP->_lights[i]->setOn(false);
			
			// increase offset for next light
            beginEditCP(shadowVP->_offset);
            shadowVP->_offset->setOffsetBias(shadowVP->_offset->getOffsetBias() - 1);
            endEditCP(shadowVP->_offset);
        }
    }

	glDepthFunc(GL_LEQUAL);

    // switch on all transparent geos
    for(UInt32 t=0;t<shadowVP->_transparent.size();++t)
        shadowVP->_transparent[t]->setActive(true);

    for(UInt32 i=0;i<shadowVP->_lights.size();++i) // Switching on ambient 
    {
        shadowVP->_lights[i]->setAmbient(_light_ambient[i]);
    }

    for(UInt32 j=0;j<shadowVP->_allLights.size();++j) 
    {
        shadowVP->_allLights[j]->setOn(light_state[j]);
    }
}


void StdShadowMap::render(RenderActionBase* action)
{

	GLfloat globalAmbient[] = {0.0,0.0,0.0,1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,globalAmbient);

        if(shadowVP->getMapAutoUpdate())
        {
            createShadowMaps(action);
        }
        else
        {
            if(shadowVP->_trigger_update)
            {
                createShadowMaps(action);
                shadowVP->_trigger_update = false;
            }
        }
    //}
    

    if(!shadowVP->_lights.empty() && !shadowVP->_lightCameras.empty())
    {
        projectShadowMaps(action);
    }
    else
    {
        FDEBUG(("Rendering without Shadows\n"));
        shadowVP->Viewport::render(action);
    }

    // render the foregrounds.
    for(UInt16 i=0; i < shadowVP->getForegrounds().size(); ++i)
	{
        shadowVP->getForegrounds(i)->draw(action, shadowVP);
	}
}
