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
"uniform float xFactor;\n"
"uniform float yFactor;\n"
"\n"
"varying vec4 projCoord;\n"
"varying vec4 texPos;\n"
"\n"
"float depthTest(vec2 texC, vec3 projC)\n"
"{\n"
"	texC.x *= xFactor;\n"
"	texC.y *= yFactor;\n"
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
"	shadowed = (1.0-(shadowed * 0.25))*intensity;\n"
"	if(firstRun == 0) shadowed += texture2DProj(oldFactorMap,vec3(texPos.xy * vec2(xFactor,yFactor),texPos.w)).x;\n"
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
"uniform float xFactor;\n"
"uniform float yFactor;\n"
"varying vec4 projCoord;\n"
"\n"
"const mat4 bias = {vec4(0.5,0.0,0.0,0.0), vec4(0.0,0.5,0.0,0.0), vec4(0.0,0.0,0.5,0.0), vec4(0.5,0.5,0.5,1.0)};\n"
"\n"
"void main(void)\n"
"{\n"
"    vec4 colorProj = bias * projCoord;\n"
"	 vec2 cp = colorProj.xy * vec2(xFactor,yFactor);\n"
"	 vec3 color = texture2DProj(colorMap, vec3(cp,colorProj.w)).xyz;\n"
" 	 color *= 1.0-texture2DProj(shadowFactorMap, vec3(cp,colorProj.w)).x;\n"
"    gl_FragColor = vec4(color, 1.0);\n"
"}\n";


DitherShadowMap::DitherShadowMap(void)
{
}

DitherShadowMap::DitherShadowMap(ShadowViewport *source)
: TreeRenderer(source)
{
	fb = 0;
    fb2 = 0;
	rb_depth = 0;

	width = 1;
    height = 1;
    //width = shadowVP->getParent()->getWidth();
    //height = shadowVP->getParent()->getHeight();
    if(shadowVP->getParent() != NullFC)
    {
        width = shadowVP->getPixelWidth();
        height = shadowVP->getPixelHeight();
    }

	if(width > height) widthHeightPOT = osgnextpower2(width);
	else widthHeightPOT = osgnextpower2(height);

    _tiledeco = NullFC;

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


	if(useNPOTTextures)
	{
		beginEditCP(_colorMapImage);
			_colorMapImage->set(GL_RGB, width, height);
		endEditCP(_colorMapImage);
	}
	else
	{
		beginEditCP(_colorMapImage);
			_colorMapImage->set(GL_RGB, widthHeightPOT, widthHeightPOT);
		endEditCP(_colorMapImage);
	}


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

	if(useNPOTTextures)
	{
	    beginEditCP(_shadowFactorMapImage);
		    _shadowFactorMapImage->set(GL_RGB, width, height);
		endEditCP(_shadowFactorMapImage);
	}
	else
	{
		beginEditCP(_shadowFactorMapImage);
		    _shadowFactorMapImage->set(GL_RGB, widthHeightPOT, widthHeightPOT);
		endEditCP(_shadowFactorMapImage);
	}
        
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
    if(_tiledeco != NullFC)
        subRefCP(_tiledeco);

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

    if(fb != 0)
        glDeleteFramebuffersEXT(1, &fb);
    if(rb_depth != 0)
        glDeleteRenderbuffersEXT( 1, &rb_depth);
    if(fb2 != 0)
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

	if(useFBO)
	{
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
	if(useNPOTTextures) glRenderbufferStorageEXT( GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24_ARB, shadowVP->getPixelWidth(), shadowVP->getPixelHeight() );
	else glRenderbufferStorageEXT( GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24_ARB, widthHeightPOT, widthHeightPOT );
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

	//win->validateGLObject(shadowVP->_texChunks[0]->getGLId());

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb2);

	//glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, win->getGLObjectId(shadowVP->_texChunks[0]->getGLId()), 0);

	glDrawBuffer(GL_NONE);	// no color buffer dest
	glReadBuffer(GL_NONE);	// no color buffer src

	//result = checkFrameBufferStatus(win);

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);

	//return result;
	}

	//if no NPOTTextures supported, resize images
	if(!useNPOTTextures)
	{
		if(width > height) widthHeightPOT = osgnextpower2(width);
		else widthHeightPOT = osgnextpower2(height);

		beginEditCP(_colorMap);
		beginEditCP(_colorMapImage);
			_colorMapImage->set(GL_RGB, widthHeightPOT, widthHeightPOT);
		endEditCP(_colorMapImage);
		endEditCP(_colorMap);

		beginEditCP(_shadowFactorMap);
		beginEditCP(_shadowFactorMapImage);
			_shadowFactorMapImage->set(GL_RGB, widthHeightPOT, widthHeightPOT);
		endEditCP(_shadowFactorMapImage);
		endEditCP(_shadowFactorMap);
	}
	return true;
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
	if(useNPOTTextures) glRenderbufferStorageEXT( GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24_ARB, shadowVP->getPixelWidth(), shadowVP->getPixelHeight() );
	else glRenderbufferStorageEXT( GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24_ARB, widthHeightPOT, widthHeightPOT );

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
    if(_tiledeco == NullFC)
    {
        _tiledeco = TileCameraDecorator::create();
        addRefCP(_tiledeco);
    }

	//Checking for the smallest Window-Dimension
    UInt32 minSize = shadowVP->getPixelWidth();

    if(shadowVP->getPixelHeight() < minSize)
		minSize = shadowVP->getPixelHeight();

    //Checking for biggest PowerOf2 that fits in smallest Window-Dimension
    UInt32 _mapRenderSize = osgnextpower2(minSize + 1) / 2;
    if(_mapRenderSize == 0)	_mapRenderSize = 128;

    Real32 vpTop,vpBottom,vpLeft,vpRight;

    //------Setting up Window to fit size of ShadowMap----------------

    // Saving original Viewport-Dimensions
    vpTop = shadowVP->getTop();
    vpBottom = shadowVP->getBottom();
    vpLeft = shadowVP->getLeft();
    vpRight = shadowVP->getRight();

    //Temporarily switching Viewports size to size of ShadowMap | OpenSG-Level
    beginEditCP(shadowVP->getCamera(), shadowVP->LeftFieldMask | shadowVP->RightFieldMask |
                          shadowVP->BottomFieldMask | shadowVP->TopFieldMask);
    {
        shadowVP->setSize(0,0,_mapRenderSize-1,_mapRenderSize-1);
    }
    endEditCP(shadowVP->getCamera(), shadowVP->LeftFieldMask | shadowVP->RightFieldMask |
                        shadowVP->BottomFieldMask | shadowVP->TopFieldMask);

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
		if(shadowVP->getGlobalShadowIntensity() != 0.0 || shadowVP->_lights[i]->getShadowIntensity() != 0.0)
        {
			// we use a tiledecorator to create shadow maps with
            // a higher resolutions than the viewport or the screen.
            beginEditCP(_tiledeco);
            _tiledeco->setDecoratee(shadowVP->_lightCameras[i]);
            _tiledeco->setFullSize(shadowVP->getMapSize(), shadowVP->getMapSize());
            endEditCP(_tiledeco);

            action->setCamera    (_tiledeco.getCPtr());

            Real32 step = (1.0 / Real32(shadowVP->getMapSize())) * Real32(_mapRenderSize);

            UInt32 ypos = 0;
            for(Real32 y=0;y<1.0;y+=step)
            {
                UInt32 xpos = 0;
                for(Real32 x=0;x<1.0;x+=step)
                {
                    beginEditCP(_tiledeco);
                        _tiledeco->setSize(x, y, x+step, y+step);
                    endEditCP(_tiledeco);
    
                    glClear(GL_DEPTH_BUFFER_BIT);
                    //shadowVP->_poly->activate(action,0);
					glPolygonOffset( shadowVP->getOffFactor(), shadowVP->getOffBias() );
					glEnable( GL_POLYGON_OFFSET_FILL );

                    action->apply(shadowVP->getRoot());
                    // check is this necessary.
                    action->getWindow()->validateGLObject(shadowVP->_texChunks[i]->getGLId());

                    //shadowVP->_poly->deactivate(action,0);
					glDisable( GL_POLYGON_OFFSET_FILL );
        
                    //----------Shadow-Texture-Parameters and Indices-------------
                
                    glBindTexture(GL_TEXTURE_2D,
                                  action->getWindow()->getGLObjectId(shadowVP->_texChunks[i]->getGLId()));
                    if(glGetError() != GL_NO_ERROR)
                        SWARNING << "Error on binding Texture!" << endLog;    

                    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, xpos, ypos, 0, 0,
                                        _mapRenderSize, _mapRenderSize);
        
                    if(glGetError() != GL_NO_ERROR)
                        SWARNING << "Error on copying Texture!" << endLog;    
        
                    glBindTexture(GL_TEXTURE_2D,0);
                    if(glGetError() != GL_NO_ERROR)
                        SWARNING << "Error on releasing Texture!" << endLog;    
        
                    if(glGetError() != GL_NO_ERROR)
                        SWARNING << "Error while Texture-Creation!" << endLog;
            
                    xpos += _mapRenderSize;
                }
                ypos += _mapRenderSize;
            }
        }
		}
    }


	// enable all lights.
    for(UInt32 i = 0; i< shadowVP->_lights.size(); ++i)
    {
        if(shadowVP->_lightStates[i] != 0)
            shadowVP->_lights[i]->setOn(true);
    }

	// activate exclude nodes:
    for(UInt32 i = 0; i < shadowVP->getExcludeNodes().getSize(); ++i)
    {
        NodePtr exnode = shadowVP->getExcludeNodes()[i];
        if(exnode != NullFC)
            if(shadowVP->_excludeNodeActive[i]) exnode->setActive(true);
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
		if(shadowVP->getGlobalShadowIntensity() != 0.0 || shadowVP->_lights[i]->getShadowIntensity() != 0.0)
        {
			action->getWindow()->validateGLObject(shadowVP->_texChunks[i]->getGLId());

			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb2);

			glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, action->getWindow()->getGLObjectId(shadowVP->_texChunks[i]->getGLId()), 0);

			glDrawBuffer(GL_NONE);
			glReadBuffer(GL_NONE);

            //shadowVP->_poly->activate(action,0);
			glPolygonOffset( shadowVP->getOffFactor(), shadowVP->getOffBias() );
			glEnable( GL_POLYGON_OFFSET_FILL );

			glClearColor(1.0,1.0,1.0,1.0);
		    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			action->setCamera(shadowVP->_lightCameras[i].getCPtr());
            action->apply(shadowVP->getRoot());
             
			//shadowVP->_poly->deactivate(action,0);
			glDisable( GL_POLYGON_OFFSET_FILL );

			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

			glClearColor(0.0,0.0,0.0,1.0);

			action->setCamera(shadowVP->getCamera().getCPtr());
		}
		}
	}
	
    //-------Restoring old states of Window and Viewport----------

	// enable all lights.
    for(UInt32 i = 0; i< shadowVP->_lights.size(); ++i)
    {
        if(shadowVP->_lightStates[i] != 0)
            shadowVP->_lights[i]->setOn(true);
    }

	// activate exclude nodes:
    for(UInt32 i = 0; i < shadowVP->getExcludeNodes().getSize(); ++i)
    {
        NodePtr exnode = shadowVP->getExcludeNodes()[i];
        if(exnode != NullFC)
            if(shadowVP->_excludeNodeActive[i]) exnode->setActive(true);
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
	glClearColor(0.0,0.0,0.0,1.0);
    if(firstRun) glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //Finde alle aktiven Lichtquellen
    Real32 activeLights = 0;
	if(shadowVP->getGlobalShadowIntensity() != 0.0) 
	{
		for (UInt32 i = 0; i<shadowVP->_lights.size();i++)
		{
			if (shadowVP->_lightStates[i] != 0) activeLights++;
		}
	}
	else
	{
		for (UInt32 i = 0; i<shadowVP->_lights.size();i++)
		{
			if (shadowVP->_lightStates[i] != 0 && shadowVP->_lights[i]->getShadowIntensity() != 0.0) activeLights++;
		}
	}

    Real32 shadowIntensity;
	if(shadowVP->getGlobalShadowIntensity() != 0.0) shadowIntensity = (shadowVP->getGlobalShadowIntensity()/activeLights);
	else  shadowIntensity = (shadowVP->_lights[num]->getShadowIntensity()/activeLights);
	
	if(shadowVP->_lights[num]->getShadowIntensity() != 0.0 || shadowVP->getGlobalShadowIntensity() != 0.0)
	{

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

	Real32 xFactor = 1.0;
	Real32 yFactor = 1.0;
	if(!useNPOTTextures)
	{
		xFactor = Real32(width)/Real32(widthHeightPOT);
		yFactor = Real32(height)/Real32(widthHeightPOT);
	}

	beginEditCP(_shadowSHL, ShaderChunk::ParametersFieldMask);
        _shadowSHL->setUniformParameter("shadowMap", 0);
        _shadowSHL->setUniformParameter("oldFactorMap", 1);
        _shadowSHL->setUniformParameter("firstRun", firstRun);
        _shadowSHL->setUniformParameter("intensity", shadowIntensity);
		_shadowSHL->setUniformParameter("texFactor", texFactor);
        //_shadowSHL->setUniformParameter("shadowBias", 0.0075f);
        _shadowSHL->setUniformParameter("lightPM", shadowMatrix);
        _shadowSHL->setUniformParameter("mapSize", Real32(shadowVP->getMapSize()));
		//_shadowSHL->setUniformParameter("shadowRange", Real32(shadowRange));
		_shadowSHL->setUniformParameter("xFactor",Real32(xFactor));
		_shadowSHL->setUniformParameter("yFactor",Real32(yFactor));
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
	firstRun = 0;
	}

}

void DitherShadowMap::createShadowFactorMapFBO(RenderActionBase* action, UInt32 num)
{
	glClearColor(0.0,0.0,0.0,1.0);

    //Finde alle aktiven Lichtquellen
    Real32 activeLights = 0;
	if(shadowVP->getGlobalShadowIntensity() != 0.0) 
	{
		for (UInt32 i = 0; i<shadowVP->_lights.size();i++)
		{
			if (shadowVP->_lightStates[i] != 0) activeLights++;
		}
	}
	else
	{
		for (UInt32 i = 0; i<shadowVP->_lights.size();i++)
		{
			if (shadowVP->_lightStates[i] != 0 && shadowVP->_lights[i]->getShadowIntensity() != 0.0) activeLights++;
		}
	}
    
    Real32 shadowIntensity;
	if(shadowVP->getGlobalShadowIntensity() != 0.0) shadowIntensity = (shadowVP->getGlobalShadowIntensity()/activeLights);
	else  shadowIntensity = (shadowVP->_lights[num]->getShadowIntensity()/activeLights);
	if(shadowVP->_lights[num]->getShadowIntensity() != 0.0 || shadowVP->getGlobalShadowIntensity() != 0.0)
	{

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

	Real32 xFactor = 1.0;
	Real32 yFactor = 1.0;
	if(!useNPOTTextures)
	{
		xFactor = Real32(width)/Real32(widthHeightPOT);
		yFactor = Real32(height)/Real32(widthHeightPOT);
	}


	//Real32 shadowRange = floor(shadowVP->getRange());
	//if(shadowRange == 0.0) shadowRange = 1.0;

    beginEditCP(_shadowSHL, ShaderChunk::ParametersFieldMask);
        _shadowSHL->setUniformParameter("shadowMap", 0);
        _shadowSHL->setUniformParameter("oldFactorMap", 1);
        _shadowSHL->setUniformParameter("firstRun", firstRun);
        _shadowSHL->setUniformParameter("intensity", shadowIntensity);
		_shadowSHL->setUniformParameter("texFactor", texFactor);
        //_shadowSHL->setUniformParameter("shadowBias", 0.0075f);
        _shadowSHL->setUniformParameter("lightPM", shadowMatrix);
        _shadowSHL->setUniformParameter("mapSize", Real32(shadowVP->getMapSize()));
		//_shadowSHL->setUniformParameter("shadowRange", Real32(shadowRange));
		_shadowSHL->setUniformParameter("xFactor",Real32(xFactor));
		_shadowSHL->setUniformParameter("yFactor",Real32(yFactor));
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

	delete[] buffers;
	firstRun = 0;
	}
}

void DitherShadowMap::drawCombineMap(RenderActionBase* action)
{
	Real32 xFactor = 1.0;
	Real32 yFactor = 1.0;
	if(!useNPOTTextures)
	{
		xFactor = Real32(width)/Real32(widthHeightPOT);
		yFactor = Real32(height)/Real32(widthHeightPOT);
	}

	beginEditCP(_combineSHL, ShaderChunk::ParametersFieldMask);
        _combineSHL->setUniformParameter("colorMap", 0);
        _combineSHL->setUniformParameter("shadowFactorMap", 1);
		_combineSHL->setUniformParameter("xFactor",Real32(xFactor));
		_combineSHL->setUniformParameter("yFactor",Real32(yFactor));
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
	if(!useGLSL || !useShadowExt ) shadowVP->Viewport::render(action);
	else
	{


	Window *win = action->getWindow();

	if(useFBO)
	{
		if(!initFBO(win)) printf("ERROR with FBOBJECT\n");
	}

	GLfloat globalAmbient[] = {0.0,0.0,0.0,1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,globalAmbient);
	//Used for ShadowFactorMap
    firstRun = 1;

    if(shadowVP->getPixelWidth() != width ||
       shadowVP->getPixelHeight() != height)
    {
        width = shadowVP->getPixelWidth();
        height = shadowVP->getPixelHeight();
    
		if(useNPOTTextures)
		{
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
		else
		{
			if(width > height) widthHeightPOT = osgnextpower2(width);
			else widthHeightPOT = osgnextpower2(height);

			beginEditCP(_colorMap);
			beginEditCP(_colorMapImage);
				_colorMapImage->set(GL_RGB, widthHeightPOT, widthHeightPOT);
			endEditCP(_colorMapImage);
			endEditCP(_colorMap);

			beginEditCP(_shadowFactorMap);
			beginEditCP(_shadowFactorMapImage);
				_shadowFactorMapImage->set(GL_RGB, widthHeightPOT, widthHeightPOT);
			endEditCP(_shadowFactorMapImage);
			endEditCP(_shadowFactorMap);
		}
    }

	for(UInt32 i = 0; i<shadowVP->_lights.size();i++)
    {
		glBindTexture(GL_TEXTURE_2D,action->getWindow()->getGLObjectId(shadowVP->_texChunks[i]->getGLId()));
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_MODE_ARB,
			            GL_COMPARE_R_TO_TEXTURE_ARB);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_FUNC_ARB,GL_LEQUAL);
		glTexParameteri(GL_TEXTURE_2D,GL_DEPTH_TEXTURE_MODE_ARB,GL_LUMINANCE);
		glBindTexture(GL_TEXTURE_2D,0);
		/*shadowVP->_texChunks[i]->activate(action, action->getWindow()->getGLObjectId(shadowVP->_texChunks[i]->getGLId()));
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_MODE_ARB,
                        GL_COMPARE_R_TO_TEXTURE_ARB);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_FUNC_ARB,GL_LEQUAL);
        glTexParameteri(GL_TEXTURE_2D,GL_DEPTH_TEXTURE_MODE_ARB,GL_LUMINANCE);
		shadowVP->_texChunks[i]->deactivate(action, action->getWindow()->getGLObjectId(shadowVP->_texChunks[i]->getGLId()));*/
	}

	
    if(shadowVP->getMapAutoUpdate())
    {
		if(useFBO && useNPOTTextures) createColorMapFBO(action);
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
			if(shadowVP->getGlobalShadowIntensity() != 0.0 || shadowVP->_lights[i]->getShadowIntensity() != 0.0)
			{
				if(useFBO && useNPOTTextures) createShadowFactorMapFBO(action, i);
				else createShadowFactorMap(action, i);
                //firstRun = 0;
			}
			}
        }
    }
    else
    {
        if(shadowVP->_trigger_update)
        {
			if(useFBO && useNPOTTextures) createColorMapFBO(action);
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
				if(shadowVP->getGlobalShadowIntensity() != 0.0 || shadowVP->_lights[i]->getShadowIntensity() != 0.0)
				{
					if(useFBO && useNPOTTextures) createShadowFactorMapFBO(action, i);
					else createShadowFactorMap(action, i);
                    //firstRun = 0;
                }
				}
            }
            shadowVP->_trigger_update = false;
        }
    }

	drawCombineMap(action);

	// switch on all transparent geos
    for(UInt32 t=0;t<shadowVP->_transparent.size();++t)
        shadowVP->_transparent[t]->setActive(true);

    // render the foregrounds.
    for(UInt16 i=0; i < shadowVP->getForegrounds().size(); ++i)
	{
        shadowVP->getForegrounds(i)->draw(action, shadowVP);
	}

	}
}
