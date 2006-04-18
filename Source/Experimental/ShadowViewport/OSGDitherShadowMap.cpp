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
#include <OSGGrabForeground.h>
#include <OSGPolygonForeground.h>
#include <OSGPolygonBackground.h>
#include <OSGTextureGrabForeground.h>
#include <OSGFileGrabForeground.h>
#include <OSGImageForeground.h>
#include <OSGImage.h>
#include <OSGGeometry.h>
#include <OSGSimpleGeometry.h>

#include <OSGLight.h>
#include <OSGMaterialGroup.h>

#include "OSGDitherShadowMap.h"
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


static std::string _Dither_shadow_vp =
"uniform float shadowBias;\n"
"uniform mat4 lightPM;\n"
"uniform float texFactor;\n"
"varying vec4 projCoord;\n"
"varying vec4 texPos;\n"
"\n"
"const mat4 bias = {vec4(0.5,0.0,0.0,0.0), vec4(0.0,0.5,0.0,0.0), vec4(0.0,0.0,0.5,0.0), vec4(0.5,0.5,0.5,1.0)};\n"
"void main(void)\n"
"{\n"
"  vec4 realPos = gl_ModelViewMatrix * gl_Vertex;\n"
"  projCoord = lightPM * realPos;\n"
"  projCoord.x *= texFactor;\n"
"  texPos = gl_ModelViewProjectionMatrix * gl_Vertex;\n"
"  projCoord = bias * projCoord;\n"
"  texPos = bias * texPos;\n"
"  gl_Position = ftransform();\n"
"}\n";

static std::string _Dither_shadow_fp =
"uniform sampler2D shadowMap;\n"
"uniform sampler2D oldFactorMap;\n"
"uniform float intensity;\n"
"uniform int firstRun;\n"
"uniform float mapSize;\n"
"\n"
"varying vec4 projCoord;\n"
"varying vec4 texPos;\n"
"\n"
"float depthTest(vec2 texC, vec3 projC)\n"
"{\n"
"	float result = shadow2D(shadowMap, vec3(projC.xy + texC, projC.z)).x;\n"
"	return result;\n"
"}\n"
"\n"
"void main(void)\n"
"{\n"
"	vec4 projectiveBiased = vec4((projCoord.xyz / projCoord.q),1.0);\n"
"	float shadowed;\n"
"	float pixSize = 1.0/mapSize;\n"
"	vec2 o = mod(floor(gl_FragCoord.xy),2.0)*pixSize;\n"
"	shadowed += depthTest(vec2(-1.5*pixSize,1.5*pixSize) + o, projectiveBiased.xyz);\n"
"	shadowed += depthTest(vec2(0.5*pixSize,1.5*pixSize) + o, projectiveBiased.xyz);\n"
"	shadowed += depthTest(vec2(-1.5*pixSize,-0.5*pixSize) + o, projectiveBiased.xyz);\n"
"	shadowed += depthTest(vec2(0.5*pixSize,-0.5*pixSize) + o, projectiveBiased.xyz);\n"
"	shadowed = shadowed * intensity * 0.25;\n"
"	if(firstRun == 0) shadowed += texture2DProj(oldFactorMap,texPos.xyw).x;\n"
"	gl_FragColor = vec4(shadowed,0.0,0.0,1.0);\n"
"}\n";


static std::string _Dither_shadow_combine_vp =
"varying vec4 projCoord;\n"
"\n"
"void main(void)\n"
"{\n"
"  projCoord = gl_Vertex;\n"
"  gl_Position = ftransform();\n"
"}\n";

static std::string _Dither_shadow_combine_fp =
"uniform sampler2D colorMap;\n"
"uniform sampler2D shadowFactorMap;\n"
"varying vec4 projCoord;\n"
"\n"
"const mat4 bias = {vec4(0.5,0.0,0.0,0.0), vec4(0.0,0.5,0.0,0.0), vec4(0.0,0.0,0.5,0.0), vec4(0.5,0.5,0.5,1.0)};\n"
"\n"
"void main(void)\n"
"{\n"
"    vec4 colorProj = bias * projCoord;\n"
"\n"
"    vec3 color = texture2DProj(colorMap, colorProj.xyw).xyz;\n"
"\n"
"    color *= texture2DProj(shadowFactorMap, colorProj.xyw).x;\n"
"    gl_FragColor = vec4(color, 1.0);\n"
"}\n";


DitherShadowMap::DitherShadowMap(void)
{
}

DitherShadowMap::DitherShadowMap(ShadowViewport *source)
: TreeRenderer(source)
{
	fb = NULL;
	rb_depth = NULL;

    width = 1;
    height = 1;
    //width = shadowVP->getParent()->getWidth();
    //height = shadowVP->getParent()->getHeight();
    if(shadowVP->getParent() != NullFC)
    {
        width = shadowVP->getPixelWidth();
        height = shadowVP->getPixelHeight();
    }

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

    //Prepare Color Map grabbing
    _colorMap = TextureChunk::create();
    _colorMapImage = Image::create();

    beginEditCP(_colorMap);
        _colorMap->setImage(_colorMapImage);
        _colorMap->setInternalFormat(GL_RGB);
        _colorMap->setExternalFormat(GL_RGB);
        _colorMap->setMinFilter(GL_NEAREST);
        _colorMap->setMagFilter(GL_NEAREST);
        _colorMap->setWrapS(GL_REPEAT);
        _colorMap->setWrapT(GL_REPEAT);
        _colorMap->setTarget(GL_TEXTURE_2D);
    endEditCP(_colorMap);


    beginEditCP(_colorMapImage);
        _colorMapImage->set(GL_RGB, width, height);
    endEditCP(_colorMapImage);

    //Prepare Shadow Factor Map grabbing
    _shadowFactorMap = TextureChunk::create();
    _shadowFactorMapImage = Image::create();

    beginEditCP(_shadowFactorMap);
        _shadowFactorMap->setImage(_shadowFactorMapImage);
        _shadowFactorMap->setInternalFormat(GL_RGB);
        _shadowFactorMap->setExternalFormat(GL_RGB);
        _shadowFactorMap->setMinFilter(GL_LINEAR);
        _shadowFactorMap->setMagFilter(GL_LINEAR);
        _shadowFactorMap->setWrapS(GL_REPEAT);
        _shadowFactorMap->setWrapT(GL_REPEAT);
        _shadowFactorMap->setTarget(GL_TEXTURE_2D);
    endEditCP(_shadowFactorMap);

    beginEditCP(_shadowFactorMapImage);
        _shadowFactorMapImage->set(GL_RGB, width, height);
    endEditCP(_shadowFactorMapImage);
        
    //SHL Chunk 1

    _shadowSHL = SHLChunk::create();
    beginEditCP(_shadowSHL);
        //_shadowSHL->readVertexProgram("Dither_Shadow.vert");
		//_shadowSHL->readFragmentProgram("Dither_Shadow.frag");
		_shadowSHL->setVertexProgram(_Dither_shadow_vp);
		_shadowSHL->setFragmentProgram(_Dither_shadow_fp);
    endEditCP(_shadowSHL);

    //SHL Chunk 2
    _combineSHL = SHLChunk::create();

    beginEditCP(_combineSHL);
        //_combineSHL->readVertexProgram("Dither_Shadow_combine.vert");
        //_combineSHL->readFragmentProgram("Dither_Shadow_combine.frag");
		_combineSHL->setVertexProgram(_Dither_shadow_combine_vp);
		_combineSHL->setFragmentProgram(_Dither_shadow_combine_fp);
    endEditCP(_combineSHL);

    _shadowCmat = ChunkMaterial::create();
    _shadowRoot = Node::create();

    _shadowShaderGroup = MaterialGroup::create();
    beginEditCP(_shadowShaderGroup, Geometry::MaterialFieldMask);
        _shadowShaderGroup->setMaterial(_shadowCmat);
    endEditCP(_shadowShaderGroup, Geometry::MaterialFieldMask);

    //Combine Shader
    _combineCmat = ChunkMaterial::create();
    _combineRoot = Node::create();

    _combineShaderGroup = MaterialGroup::create();
    beginEditCP(_combineShaderGroup, Geometry::MaterialFieldMask);
        _combineShaderGroup->setMaterial(_combineCmat);
    endEditCP(_combineShaderGroup, Geometry::MaterialFieldMask);

    beginEditCP(_combineRoot);
        _combineRoot->setCore(_combineShaderGroup);
    endEditCP(_combineRoot);

    //Kamera um Texturewürfel zu rendern
    _matrixCam = MatrixCamera::create();
    MatrixOrthogonal(textureVM,-1,1,-1,1,-1,1);
    MatrixLookAt(texturePM,0,1,0,0,0,0,0,1,0);
    _matrixCam->setNear(-1.0);
    _matrixCam->setFar(1.0);
    _matrixCam->setProjectionMatrix(textureVM);
    _matrixCam->setModelviewMatrix(texturePM);

    //Box zum Texturzeichnen
    boxGeo = makeBoxGeo(2,2,2, 1, 1, 1);
    boxNode = Node::create();
    beginEditCP(boxNode, Node::CoreFieldMask);
        boxNode->setCore(boxGeo);
    endEditCP(boxNode, Node::CoreFieldMask);


    addRefCP(_shadowSHL);
    addRefCP(_combineSHL);
    addRefCP(_shadowRoot);
    addRefCP(_combineRoot);
    addRefCP(_shadowCmat);
    addRefCP(_combineCmat);
    addRefCP(_shadowShaderGroup);
    addRefCP(_combineShaderGroup);
    addRefCP(_matrixCam);
    addRefCP(shadowVP->getRoot());
    addRefCP(boxGeo);
    addRefCP(boxNode);

}

DitherShadowMap::~DitherShadowMap(void)
{
    subRefCP(_tiledeco);
    subRefCP(_blender);

    subRefCP(_colorMap);
    subRefCP(_shadowFactorMap);
    subRefCP(_shadowFactorMap);
    subRefCP(_matrixCam);
    subRefCP(_shadowSHL);
    subRefCP(_combineSHL);
    subRefCP(_shadowShaderGroup);
    subRefCP(_combineShaderGroup);

    subRefCP(_shadowRoot);
    subRefCP(_combineRoot);
    subRefCP(_shadowSHL);
    subRefCP(_combineSHL);

    subRefCP(boxGeo);
    subRefCP(boxNode);

	glDeleteFramebuffersEXT(1, &fb);
	glDeleteRenderbuffersEXT( 1, &rb_depth);
	glDeleteFramebuffersEXT(1, &fb2);
}

/// Checks if FBO status is ok
bool DitherShadowMap::checkFrameBufferStatus(Window *win)
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


bool DitherShadowMap::initFBO(Window *win)
{
	initialize(win);

    Int32 width  = shadowVP->getPixelWidth();
    Int32 height = shadowVP->getPixelHeight();

    if (width <= 0 || height <= 0)
        return false;
        
    if (fb != NULL)
        return true;

    glGenFramebuffersEXT(1, &fb);
	glGenRenderbuffersEXT( 1, &rb_depth);

	win->validateGLObject(_colorMap->getGLId());
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, win->getGLObjectId(_colorMap->getGLId()), 0);
	win->validateGLObject(_shadowFactorMap->getGLId());
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT1_EXT, GL_TEXTURE_2D, win->getGLObjectId(_shadowFactorMap->getGLId()), 0);

	//Initialize Depth Renderbuffer
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, rb_depth);
	glRenderbufferStorageEXT( GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24_ARB, shadowVP->getPixelWidth(), shadowVP->getPixelHeight() );

	//Attach Renderbuffer to Framebuffer depth Buffer
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT,  GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, rb_depth);

	win->validateGLObject(_colorMap->getGLId());
	//setTarget(win, win->getGLObjectId(_colorMap->getGLId()), 0, GL_TEXTURE_2D);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, win->getGLObjectId(_colorMap->getGLId()), 0);

	win->validateGLObject(_shadowFactorMap->getGLId());
	//setTarget(win, win->getGLObjectId(_shadowFactorMap->getGLId()), 1, GL_TEXTURE_2D);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT1_EXT, GL_TEXTURE_2D, win->getGLObjectId(_shadowFactorMap->getGLId()), 0);


	bool result = checkFrameBufferStatus(win);

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);

	glGenFramebuffersEXT(1, &fb2);

	win->validateGLObject(shadowVP->_texChunks[0]->getGLId());

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb2);

	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, win->getGLObjectId(shadowVP->_texChunks[0]->getGLId()), 0);

	glDrawBuffer(GL_NONE);	// no color buffer dest
	glReadBuffer(GL_NONE);	// no color buffer src

	result = checkFrameBufferStatus(win);

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);

	return result;
}

void DitherShadowMap::reInit(Window *win)
{
    Int32 width  = shadowVP->getPixelWidth();
    Int32 height = shadowVP->getPixelHeight();

	win->validateGLObject(_colorMap->getGLId());
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, win->getGLObjectId(_colorMap->getGLId()), 0);
	win->validateGLObject(_shadowFactorMap->getGLId());
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT1_EXT, GL_TEXTURE_2D, win->getGLObjectId(_shadowFactorMap->getGLId()), 0);

	//Initialize Depth Renderbuffer
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, rb_depth);
	glRenderbufferStorageEXT( GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24_ARB, shadowVP->getPixelWidth(), shadowVP->getPixelHeight() );

	//Attach Renderbuffer to Framebuffer depth Buffer
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT,  GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, rb_depth);
}

void DitherShadowMap::drawTextureBoxShader(RenderActionBase* action, ChunkMaterialPtr cmat)
{
	glClearColor(0.0,0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable( GL_DEPTH_TEST );

    addRefCP(cmat);

    beginEditCP(boxGeo, Geometry::MaterialFieldMask);
        boxGeo->setMaterial(cmat);
    endEditCP(boxGeo, Geometry::MaterialFieldMask);

    action->setCamera(_matrixCam.getCPtr());

    //Render Texturebox
    action->apply(boxNode);

    //Restore old Parameters
    action->setCamera    (shadowVP->getCamera().getCPtr());

    subRefCP(cmat);
}

void DitherShadowMap::createShadowMaps(RenderActionBase* action)
{
        Real32 vpTop,vpBottom,vpLeft,vpRight;
    
    //------Setting up Window to fit size of ShadowMap----------------

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
            Real32 winHeight = shadowVP->getPixelHeight();
            Real32 imgWidth = shadowVP->getMapSize();
            Real32 winWidth = shadowVP->getPixelWidth();
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
                            _tiledeco->setSize(  x1/(Real32)imgWidth,     y1/(Real32)imgHeight,    (x2+1)/(Real32)imgWidth, (y2+1)/(Real32)imgHeight);
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

void DitherShadowMap::createShadowMapsFBO(RenderActionBase* action)
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


void DitherShadowMap::createColorMap(RenderActionBase* action)
{
    shadowVP->getBackground()->clear(action, shadowVP);

    action->apply(shadowVP->getRoot());

    action->getWindow()->validateGLObject(_colorMap->getGLId());

    glBindTexture(GL_TEXTURE_2D, action->getWindow()->getGLObjectId(_colorMap->getGLId()));
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, shadowVP->getPixelWidth(), shadowVP->getPixelHeight());
    glBindTexture(GL_TEXTURE_2D,0);
}

void DitherShadowMap::createColorMapFBO(RenderActionBase* action)
{

	glClearColor(0.0,0.0,0.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Window *win = action->getWindow();

	GLenum *buffers = NULL;
	buffers = new GLenum[1];
	buffers[0] = GL_COLOR_ATTACHMENT0_EXT;

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb);
	
	glDrawBuffersARB(1, buffers);

	shadowVP->getBackground()->clear(action, shadowVP);
    action->apply(shadowVP->getRoot());

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	
	delete[] buffers;

}


void DitherShadowMap::createShadowFactorMap(RenderActionBase* action, UInt32 num)
{
    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Finde alle aktiven Lichtquellen
    Real32 activeLights = 0;
    for (UInt32 i = 0; i<shadowVP->_lights.size();i++)
    {
        if (shadowVP->_lightStates[i] != 0) activeLights++;
    }
    Color4f shadowColor = shadowVP->getShadowColor(); 
    activeLights = (1.0-shadowColor[0])/activeLights;

    Matrix LVM,LPM,CVM;
    shadowVP->_lightCameras[num]->getViewing(LVM, shadowVP->getPixelWidth(), shadowVP->getPixelHeight());
    shadowVP->_lightCameras[num]->getProjection(LPM, shadowVP->getPixelWidth(), shadowVP->getPixelHeight());
    PerspectiveCameraPtr::dcast(shadowVP->getCamera())->getViewing(CVM, shadowVP->getPixelWidth(), shadowVP->getPixelHeight());
    Matrix iCVM = CVM;
    iCVM.invert();
    Matrix iLVM = LVM;
    iLVM.invert();

	Real32 texFactor;
	if(shadowVP->_lights[num]->getType() == SpotLight::getClassType() || shadowVP->_lights[num]->getType() == PointLight::getClassType())
		texFactor = Real32(width)/Real32(height);
	else texFactor = 1.0;

    Matrix shadowMatrix = LPM;
    shadowMatrix.mult(LVM);
    shadowMatrix.mult(iCVM);

	Real32 shadowRange = floor(shadowVP->getRange());
	if(shadowRange == 0.0) shadowRange = 1.0;

    beginEditCP(_shadowSHL, ShaderChunk::ParametersFieldMask);
        _shadowSHL->setUniformParameter("shadowMap", 0);
        _shadowSHL->setUniformParameter("oldFactorMap", 1);
        _shadowSHL->setUniformParameter("firstRun", firstRun);
        _shadowSHL->setUniformParameter("intensity", activeLights);
		_shadowSHL->setUniformParameter("texFactor", texFactor);
        //_shadowSHL->setUniformParameter("shadowBias", 0.0075f);
        _shadowSHL->setUniformParameter("lightPM", shadowMatrix);
        _shadowSHL->setUniformParameter("mapSize", Real32(shadowVP->getMapSize()));
    endEditCP(_shadowSHL, ShaderChunk::ParametersFieldMask);

    beginEditCP(_shadowCmat);
        _shadowCmat->getChunks().clear();
        _shadowCmat->addChunk(_shadowSHL);
        _shadowCmat->addChunk(shadowVP->_texChunks[num]);
        _shadowCmat->addChunk(_shadowFactorMap);
    endEditCP(_shadowCmat);

    /////////////
    subRefCP(_shadowSHL);
    subRefCP(_shadowFactorMap);

    addRefCP(shadowVP->getRoot());

    beginEditCP(_shadowRoot, Node::CoreFieldMask | Node::ChildrenFieldMask);
        _shadowRoot->setCore(_shadowShaderGroup);
        _shadowRoot->addChild(shadowVP->getRoot());
    endEditCP(_shadowRoot, Node::ChildrenFieldMask | Node::ChildrenFieldMask);
    
    //draw the Scene
    
    action->apply(_shadowRoot);

    action->getWindow()->validateGLObject(_shadowFactorMap->getGLId());

    glBindTexture(GL_TEXTURE_2D, action->getWindow()->getGLObjectId(_shadowFactorMap->getGLId()));
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, shadowVP->getPixelWidth(), shadowVP->getPixelHeight());
    glBindTexture(GL_TEXTURE_2D,0);

    beginEditCP(_shadowRoot, Node::CoreFieldMask | Node::ChildrenFieldMask);
        _shadowRoot->subChild(shadowVP->getRoot());
    endEditCP(_shadowRoot, Node::ChildrenFieldMask | Node::ChildrenFieldMask);

    subRefCP(shadowVP->getRoot());

    glClearColor(0.0,0.0,0.0,1.0);
}

void DitherShadowMap::createShadowFactorMapFBO(RenderActionBase* action, UInt32 num)
{
    glClearColor(1.0,1.0,1.0,1.0);

    //Finde alle aktiven Lichtquellen
    Real32 activeLights = 0;
    for (UInt32 i = 0; i<shadowVP->_lights.size();i++)
    {
        if (shadowVP->_lightStates[i] != 0) activeLights++;
    }
    Color4f shadowColor = shadowVP->getShadowColor(); 
    activeLights = (1.0-shadowColor[0])/activeLights;

    Matrix LVM,LPM,CVM;
    shadowVP->_lightCameras[num]->getViewing(LVM, shadowVP->getPixelWidth(), shadowVP->getPixelHeight());
    shadowVP->_lightCameras[num]->getProjection(LPM, shadowVP->getPixelWidth(), shadowVP->getPixelHeight());
    PerspectiveCameraPtr::dcast(shadowVP->getCamera())->getViewing(CVM, shadowVP->getPixelWidth(), shadowVP->getPixelHeight());
    Matrix iCVM = CVM;
    iCVM.invert();

	Real32 texFactor;
	if(shadowVP->_lights[num]->getType() == SpotLight::getClassType() || shadowVP->_lights[num]->getType() == PointLight::getClassType())
		texFactor = Real32(width)/Real32(height);
	else texFactor = 1.0;

    Matrix shadowMatrix = LPM;
    shadowMatrix.mult(LVM);
    shadowMatrix.mult(iCVM);

	Real32 shadowRange = floor(shadowVP->getRange());
	if(shadowRange == 0.0) shadowRange = 1.0;

    beginEditCP(_shadowSHL, ShaderChunk::ParametersFieldMask);
        _shadowSHL->setUniformParameter("shadowMap", 0);
        _shadowSHL->setUniformParameter("oldFactorMap", 1);
        _shadowSHL->setUniformParameter("firstRun", firstRun);
        _shadowSHL->setUniformParameter("intensity", activeLights);
		_shadowSHL->setUniformParameter("texFactor", texFactor);
        //_shadowSHL->setUniformParameter("shadowBias", 0.0075f);
        _shadowSHL->setUniformParameter("lightPM", shadowMatrix);
        _shadowSHL->setUniformParameter("mapSize", Real32(shadowVP->getMapSize()));
    endEditCP(_shadowSHL, ShaderChunk::ParametersFieldMask);

    beginEditCP(_shadowCmat);
        _shadowCmat->getChunks().clear();
        _shadowCmat->addChunk(_shadowSHL);
        _shadowCmat->addChunk(shadowVP->_texChunks[num]);
        _shadowCmat->addChunk(_shadowFactorMap);
    endEditCP(_shadowCmat);

    /////////////
    subRefCP(_shadowSHL);
    subRefCP(_shadowFactorMap);

    addRefCP(shadowVP->getRoot());

    beginEditCP(_shadowRoot, Node::CoreFieldMask | Node::ChildrenFieldMask);
        _shadowRoot->setCore(_shadowShaderGroup);
        _shadowRoot->addChild(shadowVP->getRoot());
    endEditCP(_shadowRoot, Node::ChildrenFieldMask | Node::ChildrenFieldMask);
    
    	GLenum *buffers = NULL;
	buffers = new GLenum[1];
	buffers[0] = GL_COLOR_ATTACHMENT1_EXT;
    
	//Setup FBO
	//bind(action->getWindow(),fb);
	glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, fb);

	//setTarget(action->getWindow(), action->getWindow()->getGLObjectId(_shadowFactorMap->getGLId()), 1, GL_TEXTURE_2D);
	glDrawBuffersARB(1, buffers);

    //draw the Scene
	if(firstRun) glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    action->apply(_shadowRoot);

	//stop();
	glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0);

    beginEditCP(_shadowRoot, Node::CoreFieldMask | Node::ChildrenFieldMask);
        _shadowRoot->subChild(shadowVP->getRoot());
    endEditCP(_shadowRoot, Node::ChildrenFieldMask | Node::ChildrenFieldMask);

    subRefCP(shadowVP->getRoot());

    glClearColor(0.0,0.0,0.0,1.0);
	delete[] buffers;
}

void DitherShadowMap::drawCombineMap(RenderActionBase* action)
{
    beginEditCP(_combineSHL, ShaderChunk::ParametersFieldMask);
        _combineSHL->setUniformParameter("colorMap", 0);
        _combineSHL->setUniformParameter("shadowFactorMap", 1);
    endEditCP(_combineSHL, ShaderChunk::ParametersFieldMask);

    beginEditCP(_combineCmat);
        _combineCmat->getChunks().clear();
        _combineCmat->addChunk(_combineSHL);
        _combineCmat->addChunk(_colorMap);
        _combineCmat->addChunk(_shadowFactorMap);
    endEditCP(_combineCmat);

    //draw the Scene
    drawTextureBoxShader(action, _combineCmat);

    subRefCP(_colorMap);
    subRefCP(_shadowFactorMap);
    subRefCP(_combineSHL);
}

void DitherShadowMap::render(RenderActionBase* action)
{
	Window *win = action->getWindow();

	if(!initFBO(win)) printf("ERROR with FBOBJECT\n");

	/*if(shadowVP->getQualityMode())
	{
		useFBO = true;
		if(glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) == GL_FRAMEBUFFER_UNSUPPORTED_EXT) useFBO=false;
	}
	else useFBO = false;*/


	GLfloat globalAmbient[] = {0.0,0.0,0.0,1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,globalAmbient);
    firstRun = 1;

    if(shadowVP->getPixelWidth() != width ||
       shadowVP->getPixelHeight() != height)
    {
        width = shadowVP->getPixelWidth();
        height = shadowVP->getPixelHeight();
    
        beginEditCP(_colorMap);
        beginEditCP(_colorMapImage);
            _colorMapImage->set(GL_RGB, width, height);
        endEditCP(_colorMapImage);
        endEditCP(_colorMap);

        beginEditCP(_shadowFactorMap);
        beginEditCP(_shadowFactorMapImage);
            _shadowFactorMapImage->set(GL_RGB, width, height);
        endEditCP(_shadowFactorMapImage);
        endEditCP(_shadowFactorMap);

		reInit(win);
    }

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
		if(useFBO) createColorMapFBO(action);
		else createColorMap(action);

		//deactivate transparent Nodes
		for(UInt32 t=0;t<shadowVP->_transparent.size();++t)
			shadowVP->_transparent[t]->setActive(false);
        
		if(useFBO) createShadowMapsFBO(action);
		else createShadowMaps(action);

       
        for(UInt32 i = 0; i<shadowVP->_lights.size();i++)
        {
            if(shadowVP->_lightStates[i] != 0)
            {
				if(useFBO) createShadowFactorMapFBO(action, i);
				else createShadowFactorMap(action, i);
                firstRun = 0;
			}
        }
    }
    else
    {
        if(shadowVP->_trigger_update)
        {
			if(useFBO) createColorMapFBO(action);
			else createColorMap(action);

			//deactivate transparent Nodes
			for(UInt32 t=0;t<shadowVP->_transparent.size();++t)
				shadowVP->_transparent[t]->setActive(false);

            if(useFBO) createShadowMapsFBO(action);
			else createShadowMaps(action);
			
            for(UInt32 i = 0; i<shadowVP->_lights.size();i++)
            {
                if(shadowVP->_lightStates[i] != 0)
                {
					if(useFBO) createShadowFactorMapFBO(action, i);
					else createShadowFactorMap(action, i);
                    firstRun = 0;
                }
            }
            shadowVP->_trigger_update = false;
        }
    }

	drawCombineMap(action);

	// switch on all transparent geos
    for(UInt32 t=0;t<shadowVP->_transparent.size();++t)
        shadowVP->_transparent[t]->setActive(true);

	for(UInt32 i = 0; i<shadowVP->_lights.size();i++)
    {
		shadowVP->_texChunks[i]->deactivate(action, action->getWindow()->getGLObjectId(shadowVP->_texChunks[i]->getGLId()));
	}
}
