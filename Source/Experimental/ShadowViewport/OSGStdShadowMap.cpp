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
#if 1 //GL_ARB_texture_float
#	define	GL_RGBA32F_ARB                      0x8814
#	define	GL_RGB32F_ARB                       0x8815
#	define	GL_ALPHA32F_ARB                     0x8816
#	define	GL_INTENSITY32F_ARB                 0x8817
#	define	GL_LUMINANCE32F_ARB                 0x8818
#	define	GL_LUMINANCE_ALPHA32F_ARB           0x8819
#	define	GL_RGBA16F_ARB                      0x881A
#	define	GL_RGB16F_ARB                       0x881B
#	define	GL_ALPHA16F_ARB                     0x881C
#	define	GL_INTENSITY16F_ARB                 0x881D
#	define	GL_LUMINANCE16F_ARB                 0x881E
#	define	GL_LUMINANCE_ALPHA16F_ARB           0x881F
#endif

/* ----------------------- GL_EXT_framebuffer_object ----------------------- */

#ifndef GL_ARB_draw_buffers
    #define GL_ARB_draw_buffers 1
#endif

#ifndef GL_EXT_framebuffer_object
    #define GL_INVALID_FRAMEBUFFER_OPERATION_EXT 0x0506
    #define GL_MAX_RENDERBUFFER_SIZE_EXT 0x84E8
    #define GL_FRAMEBUFFER_BINDING_EXT 0x8CA6
    #define GL_RENDERBUFFER_BINDING_EXT 0x8CA7
    #define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE_EXT 0x8CD0
    #define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME_EXT 0x8CD1
    #define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL_EXT 0x8CD2
    #define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE_EXT 0x8CD3
    #define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_3D_ZOFFSET_EXT 0x8CD4
    #define GL_FRAMEBUFFER_COMPLETE_EXT 0x8CD5
    #define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT 0x8CD6
    #define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT 0x8CD7
    #define GL_FRAMEBUFFER_INCOMPLETE_DUPLICATE_ATTACHMENT_EXT 0x8CD8
    #define GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT 0x8CD9
    #define GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT 0x8CDA
    #define GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT 0x8CDB
    #define GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT 0x8CDC
    #define GL_FRAMEBUFFER_UNSUPPORTED_EXT 0x8CDD
    #define GL_FRAMEBUFFER_STATUS_ERROR_EXT 0x8CDE
    #define GL_MAX_COLOR_ATTACHMENTS_EXT 0x8CDF
    #define GL_COLOR_ATTACHMENT0_EXT 0x8CE0
    #define GL_COLOR_ATTACHMENT1_EXT 0x8CE1
    #define GL_COLOR_ATTACHMENT2_EXT 0x8CE2
    #define GL_COLOR_ATTACHMENT3_EXT 0x8CE3
    #define GL_COLOR_ATTACHMENT4_EXT 0x8CE4
    #define GL_COLOR_ATTACHMENT5_EXT 0x8CE5
    #define GL_COLOR_ATTACHMENT6_EXT 0x8CE6
    #define GL_COLOR_ATTACHMENT7_EXT 0x8CE7
    #define GL_COLOR_ATTACHMENT8_EXT 0x8CE8
    #define GL_COLOR_ATTACHMENT9_EXT 0x8CE9
    #define GL_COLOR_ATTACHMENT10_EXT 0x8CEA
    #define GL_COLOR_ATTACHMENT11_EXT 0x8CEB
    #define GL_COLOR_ATTACHMENT12_EXT 0x8CEC
    #define GL_COLOR_ATTACHMENT13_EXT 0x8CED
    #define GL_COLOR_ATTACHMENT14_EXT 0x8CEE
    #define GL_COLOR_ATTACHMENT15_EXT 0x8CEF
    #define GL_DEPTH_ATTACHMENT_EXT 0x8D00
    #define GL_STENCIL_ATTACHMENT_EXT 0x8D20
    #define GL_FRAMEBUFFER_EXT 0x8D40
    #define GL_RENDERBUFFER_EXT 0x8D41
    #define GL_RENDERBUFFER_WIDTH_EXT 0x8D42
    #define GL_RENDERBUFFER_HEIGHT_EXT 0x8D43
    #define GL_RENDERBUFFER_INTERNAL_FORMAT_EXT 0x8D44
    #define GL_STENCIL_INDEX_EXT 0x8D45
    #define GL_STENCIL_INDEX1_EXT 0x8D46
    #define GL_STENCIL_INDEX4_EXT 0x8D47
    #define GL_STENCIL_INDEX8_EXT 0x8D48
    #define GL_STENCIL_INDEX16_EXT 0x8D49
#endif

#ifndef GL_TEXTURE_RECTANGLE_ARB
    #define GL_TEXTURE_RECTANGLE_ARB 0x84F5
#endif

#ifndef GL_DEPTH_COMPONENT_ARB
    #define GL_DEPTH_COMPONENT_ARB 0x1902
#endif

#ifndef GL_ARB_depth_texture
    #define GL_DEPTH_COMPONENT16_ARB 0x81A5
    #define GL_DEPTH_COMPONENT24_ARB 0x81A6
    #define GL_DEPTH_COMPONENT32_ARB 0x81A7
    #define GL_TEXTURE_DEPTH_SIZE_ARB 0x884A
    #define GL_DEPTH_TEXTURE_MODE_ARB 0x884B
#endif

#ifndef GL_ARB_shadow
    #define GL_TEXTURE_COMPARE_MODE_ARB 0x884C
    #define GL_TEXTURE_COMPARE_FUNC_ARB 0x884D
    #define GL_COMPARE_R_TO_TEXTURE_ARB 0x884E
#endif


OSG_USING_NAMESPACE


StdShadowMap::StdShadowMap(void)
{
}

StdShadowMap::StdShadowMap(ShadowViewport *source)
: TreeRenderer(source)
{
	fb2 = 0;

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

}

StdShadowMap::~StdShadowMap(void)
{
	subRefCP(_tiledeco);
	subRefCP(_blender);
    if(fb2 != 0)
        glDeleteFramebuffersEXT(1, &fb2);
}

/// Checks if FBO status is ok
bool StdShadowMap::checkFrameBufferStatus(Window *win)
{
    GLenum errCode, status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);

    switch(status)
    {
        case GL_FRAMEBUFFER_COMPLETE_EXT:
        FINFO(("%x: framebuffer complete!\n", status));
        break;
        case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
        FWARNING(("%x: framebuffer GL_FRAMEBUFFER_UNSUPPORTED_EXT\n", status));
        // choose different formats
        return false;
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
        FWARNING(("%x: framebuffer INCOMPLETE_ATTACHMENT\n", status));
        break;
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
        FWARNING(("%x: framebuffer FRAMEBUFFER_MISSING_ATTACHMENT\n", status));
        break;
        case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
        FWARNING(("%x: framebuffer FRAMEBUFFER_DIMENSIONS\n", status));
        break;
        case GL_FRAMEBUFFER_INCOMPLETE_DUPLICATE_ATTACHMENT_EXT:
        FWARNING(("%x: framebuffer INCOMPLETE_DUPLICATE_ATTACHMENT\n", status));
        break;
        case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
        FWARNING(("%x: framebuffer INCOMPLETE_FORMATS\n", status));
        break;
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
        FWARNING(("%x: framebuffer INCOMPLETE_DRAW_BUFFER\n", status));
        break;
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
        FWARNING(("%x: framebuffer INCOMPLETE_READ_BUFFER\n", status));
        break;
        case GL_FRAMEBUFFER_BINDING_EXT:
        FWARNING(("%x: framebuffer BINDING_EXT\n", status));
        break;
        default:
        return false;
    }

    if ((errCode = glGetError()) != GL_NO_ERROR)
    {
        const GLubyte *errString = gluErrorString(errCode);
        FWARNING(("OpenGL Error: %s!\n", errString));
        return false;
    }
    return true;
}


bool StdShadowMap::initFBO(Window *win)
{
	initialize(win);

    if (fb2 != 0)
        return true;
	glGenFramebuffersEXT(1, &fb2);

	//win->validateGLObject(shadowVP->_texChunks[0]->getGLId());

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb2);

	//glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, win->getGLObjectId(shadowVP->_texChunks[0]->getGLId()), 0);

	glDrawBuffer(GL_NONE);	// no color buffer dest
	glReadBuffer(GL_NONE);	// no color buffer src

	//bool result = checkFrameBufferStatus(win);

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);

	return true;
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
					y2 = osgMin((Real32)(y1+winHeight-1), (Real32)(imgHeight-1));
					th = y2 - y1 + 1;

					for (x1=0; x1 < imgWidth; x1 += winWidth)
					{
						x2 = osgMin((Real32)(x1+winWidth-1), (Real32)(imgWidth-1));
						tw = x2 - x1 + 1;

						// set tile size to maximal renderable size
						beginEditCP(_tiledeco);
							_tiledeco->setSize(  x1/(Real32)imgWidth,     y1/(Real32)imgHeight,	(x2+1)/(Real32)imgWidth, (y2+1)/(Real32)imgHeight);
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

void StdShadowMap::createShadowMapsFBO(RenderActionBase* action)
{
	UInt32 oldWidth, oldHeight;
	oldWidth = shadowVP->getPixelWidth();
	oldHeight = shadowVP->getPixelHeight();

    //------Setting up Window to fit size of ShadowMap----------------

	shadowVP->setVPSize(0,0,shadowVP->getMapSize()-1,shadowVP->getMapSize()-1);

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
            action->getWindow()->validateGLObject(shadowVP->_texChunks[i]->getGLId());

			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb2);

			glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, action->getWindow()->getGLObjectId(shadowVP->_texChunks[i]->getGLId()), 0);

			glDrawBuffer(GL_NONE);
			glReadBuffer(GL_NONE);

            shadowVP->_poly->activate(action,0);

			glClearColor(1.0,1.0,1.0,1.0);
		    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			action->setCamera(shadowVP->_lightCameras[i].getCPtr());
            action->apply(shadowVP->getRoot());

			shadowVP->_poly->deactivate(action,0);

			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

			glClearColor(0.0,0.0,0.0,1.0);

			action->setCamera(shadowVP->getCamera().getCPtr());
		}
	}

    //-------Restoring old states of Window and Viewport----------

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

	//glViewport( 0, 0, oldWidth-1, oldHeight-1 );

	shadowVP->setVPSize(0,0,oldWidth-1,oldHeight-1);
	shadowVP->setVPSize(0,0,1,1);

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

    Real32 activeLights = 0;
    for (UInt32 i = 0; i<shadowVP->_lights.size();i++)
    {
        if (shadowVP->_lightStates[i] != 0) activeLights++;
    }


    for(UInt32 j=0;j<shadowVP->_lights.size();++j) // Switching off specular highlights
    {
        _light_specular.push_back(shadowVP->_lights[j]->getSpecular());
        _light_diffuse.push_back(shadowVP->_lights[j]->getDiffuse());
        _light_ambient.push_back(shadowVP->_lights[j]->getAmbient());

		Real32 shadowCol;
		if(shadowVP->getShadowIntensity().size() == 0) shadowCol = 0.0;
		else if(shadowVP->getShadowIntensity().size() < (j+1)) shadowCol = shadowVP->getShadowIntensity()[shadowVP->getShadowIntensity().size()-1] * (1.0 / activeLights);
		else shadowCol = shadowVP->getShadowIntensity()[j] * (1.0 / activeLights);

		Color4f shadow_color = Color4f(shadowCol,shadowCol,shadowCol,1.0);


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
	for(UInt32 j=0;j<shadowVP->_lights.size();++j) {
        light_state.push_back(shadowVP->_lights[j]->getOn());
        shadowVP->_lights[j]->setOn(false);
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

    for(UInt32 j=0;j<shadowVP->_lights.size();++j)
    {
        shadowVP->_lights[j]->setOn(light_state[j]);
    }
}


void StdShadowMap::render(RenderActionBase* action)
{
	Window *win = action->getWindow();
	if(!initFBO(win)) printf("ERROR with FBOBJECT\n");

	GLfloat globalAmbient[] = {0.0,0.0,0.0,1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,globalAmbient);

	/*if(shadowVP->getQualityMode())
	{
		useFBO = true;
		if(glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) == GL_FRAMEBUFFER_UNSUPPORTED_EXT) useFBO=false;
	}
	else useFBO = false;*/

	//if no lights for shadows are given
	if(shadowVP->getLightNodes().getSize() == 0) shadowVP->Viewport::render(action);
	else
	{
	for(UInt32 i = 0; i<shadowVP->_lights.size();i++)
    {
		shadowVP->_texChunks[i]->activate(action, action->getWindow()->getGLObjectId(shadowVP->_texChunks[i]->getGLId()));
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_MODE_ARB,
                        GL_COMPARE_R_TO_TEXTURE_ARB);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_FUNC_ARB,GL_LEQUAL);
        glTexParameteri(GL_TEXTURE_2D,GL_DEPTH_TEXTURE_MODE_ARB,GL_LUMINANCE);
	}



    if(shadowVP->getMapAutoUpdate())
    {
        if(useFBO) createShadowMapsFBO(action);
		else createShadowMaps(action);
    }
    else
    {
        if(shadowVP->_trigger_update)
        {
			if(useFBO) createShadowMapsFBO(action);
			else createShadowMaps(action);
            shadowVP->_trigger_update = false;
        }
    }

    if(!shadowVP->_lights.empty() || !shadowVP->_lightCameras.empty())
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

	for(UInt32 i = 0; i<shadowVP->_lights.size();i++)
    {
		shadowVP->_texChunks[i]->deactivate(action, action->getWindow()->getGLObjectId(shadowVP->_texChunks[i]->getGLId()));
	}
	}

}
