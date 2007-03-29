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
#include "OSGPCSSShadowMap.h"
#include "OSGShadowViewport.h"
#include "OSGTreeRenderer.h"

//#define USE_FBO_FOR_COLOR_AND_FACTOR_MAP

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
#define GL_RENDERBUFFERwidth_EXT 0x8D42
#define GL_RENDERBUFFERheight_EXT 0x8D43
#define GL_RENDERBUFFER_INTERNAL_FORMAT_EXT 0x8D44
#define GL_STENCIL_INDEX_EXT 0x8D45
#define GL_STENCIL_INDEX1_EXT 0x8D46
#define GL_STENCIL_INDEX4_EXT 0x8D47
#define GL_STENCIL_INDEX8_EXT 0x8D48
#define GL_STENCIL_INDEX16_EXT 0x8D49
#endif

// Some installations have a typo in the name for this one
#ifndef GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT 0x8CD6
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

static std::string _pcss_shadow_vp =
    "uniform mat4 lightPM;\n"
    "uniform float texFactor;\n"
    "varying vec4 projCoord;\n"
    "varying vec4 texPos;\n"
    "\n"
#ifndef NO_CONST_GLSL_VAR
    "const "
#endif
    "mat4 bias = mat4(0.5,0.0,0.0,0.0,0.0,0.5,0.0,0.0,0.0,0.0,0.5,0.0,0.5,0.5,0.5,1.0);\n""\n"
    "void main(void)\n"
    "{\n"
    "  vec4 realPos = gl_ModelViewMatrix * gl_Vertex;\n"
    "  projCoord = lightPM * realPos;\n"
    "  projCoord.x *= texFactor;\n"
    "  texPos = gl_ModelViewProjectionMatrix * gl_Vertex;\n"
    "\n"
    "  projCoord = bias * projCoord;\n"
    "  texPos = bias * texPos;\n"
    "  gl_Position = ftransform();\n"
    "}\n";

static std::string _pcss_shadow_fp =
    "uniform sampler2D shadowMap;\n"
    "uniform sampler2D oldFactorMap;\n"
    "uniform float intensity;\n"
    "uniform int firstRun;\n"
    "uniform float mapSize;\n"
    "uniform float lightSize;\n"
    "uniform float xFactor;\n"
    "uniform float yFactor;\n"
    "varying vec4 projCoord;\n"
    "varying vec4 texPos;\n"
    "const float blockerSamples = 6.0;\n"
    "const float PCFsamples = 8.0;\n"
    "\n"
    "float sumBlocker(vec3 projectiveBiased, float filterWidth, float samples)\n"
    "{\n"
    "	float stepSize = 2.0 * filterWidth / samples;\n"
    "\n"
    "	projectiveBiased.xy -= vec2(filterWidth,filterWidth);\n"
    "\n"
    "      float blockerCount = 0.0;\n"
    "	float blockerSum = 0.0;\n"
    "\n"
    "	for (float i=0.0; i<samples; i += 1.0) \n"
    "	{\n"
    "           for (float j=0.0; j<samples; j += 1.0) \n"
    "		{\n"
    "			if(projectiveBiased.z > texture2D(shadowMap, projectiveBiased.xy + vec2(i*stepSize,j*stepSize)).x) \n"
    "			{\n"
    "				blockerCount += 1.0;\n"
    "				blockerSum += texture2D(shadowMap, projectiveBiased.xy + vec2(i*stepSize,j*stepSize)).x;\n"
    "			}\n"
    "       }\n"
    "	}\n"
    "\n"
    "	float result;\n"
    "	if(blockerCount > 0.0) result = blockerSum / blockerCount;\n"
    "	else result = 0.0;\n"
    "	return result;\n"
    "}\n"
    "\n"
    "float PCF(vec3 projectiveBiased, float filterWidth, float samples)\n"
    "{\n"
    "	float stepSize = 2.0 * filterWidth / samples;\n"
    "\n"
    "	projectiveBiased.xy -= vec2(filterWidth,filterWidth);\n"
    "\n"
    "   float blockerCount = 0.0;\n"
    "\n"
    "	for (float i=0.0; i<samples; i += 1.0) \n"
    "	{\n"
    "            for (float j=0.0; j<samples; j += 1.0) \n"
    "		{\n"
    "			if(projectiveBiased.z > texture2D(shadowMap, projectiveBiased.xy + vec2(i*stepSize,j*stepSize)).x) \n"
    "			{\n"
    "				blockerCount += 1.0;\n"
    "			}\n"
    "       }\n"
    "	}\n"
    "\n"
    "	float result = 1.0-((blockerCount/(samples*samples)));\n"
    "	\n"
    "	return result;\n"
    "}\n"
    "\n"
    "float estimatePenumbra(vec3 projectiveBiased, float blocker)\n"
    "{\n"
    "	float penumbra;\n"
    "	if (blocker == 0.0) penumbra = 0.0;\n"
    "	else penumbra = ((projectiveBiased.z - blocker) * lightSize) / blocker;\n"
    "\n"
    "     return penumbra;\n"
    "}\n"
    "\n"
    "\n"
    "void main(void)\n"
    "{\n"
    "	vec3 projectiveBiased = (projCoord.xyz / projCoord.q);\n"
    "\n"
    "	float blockerSearchWidth = 0.01/projectiveBiased.z;\n"
    "	float blocker = sumBlocker(projectiveBiased,blockerSearchWidth,blockerSamples);\n"
    "\n"
    "	float penumbra;\n"
    "	float shadowed;\n"
    "\n"
    "	penumbra = estimatePenumbra(projectiveBiased,blocker);\n"
    "	float maxpen = PCFsamples*(1.0/mapSize);\n"
    "	if(penumbra > maxpen) penumbra = maxpen;\n"
    "	shadowed = PCF(projectiveBiased,penumbra,PCFsamples);\n"
    "\n"
    "	shadowed = (1.0-shadowed) * intensity;\n"
    "\n"
    "	if(firstRun == 0) shadowed += texture2DProj(oldFactorMap,vec3(texPos.xy * vec2(xFactor,yFactor),texPos.w)).x;\n"
    "	\n"
    "	gl_FragColor = vec4(shadowed,0.0,0.0,1.0);\n"
    "}\n";

PCSSShadowMap::PCSSShadowMap(ShadowViewport *source) :
    TreeRenderer(source),
    _tiledeco(NullFC),
    _colorMap(NullFC),
    _shadowFactorMap(NullFC),
    _colorMapImage(NullFC),
    _shadowFactorMapImage(NullFC),
    _shadowCmat(NullFC),
    _shadowSHL(NullFC),
    _combineSHL(NullFC),
    _combineDepth(NullFC),
    _pf(NullFC),
    _firstRun(1),
    _width(1),
    _height(1),
    _widthHeightPOT(0),
    _fb(0),
    _fb2(0),
    _rb_depth(0),
    _initTexturesDone(false)
{
    if(_shadowVP->getParent() != NullFC)
    {
        _width = _shadowVP->getPixelWidth();
        _height = _shadowVP->getPixelHeight();
    }

    if(_width == 0)
        _width = 1;
    if(_height == 0)
        _height = 1;

    if(_width > _height)
        _widthHeightPOT = osgnextpower2(_width - 1);
    else
        _widthHeightPOT = osgnextpower2(_height - 1);

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

    if(_useNPOTTextures)
    {
        beginEditCP(_colorMapImage);
        _colorMapImage->set(GL_RGB, _width, _height);
        endEditCP(_colorMapImage);
    }
    else
    {
        beginEditCP(_colorMapImage);
        _colorMapImage->set(GL_RGB, _widthHeightPOT, _widthHeightPOT);
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

    if(_useNPOTTextures)
    {
        beginEditCP(_shadowFactorMapImage);
        _shadowFactorMapImage->set(GL_RGB, _width, _height);
        endEditCP(_shadowFactorMapImage);
    }
    else
    {
        beginEditCP(_shadowFactorMapImage);
        _shadowFactorMapImage->set(GL_RGB, _widthHeightPOT, _widthHeightPOT);
        endEditCP(_shadowFactorMapImage);
    }

    //SHL Chunk 1

    _shadowSHL = SHLChunk::create();
    beginEditCP(_shadowSHL);
    //_shadowSHL->readVertexProgram("PCSS_Shadow.vert");
    //_shadowSHL->readFragmentProgram("PCSS_Shadow.frag");
    _shadowSHL->setVertexProgram(_pcss_shadow_vp);
    _shadowSHL->setFragmentProgram(_pcss_shadow_fp);
    endEditCP(_shadowSHL);

    //SHL Chunk 2
    _combineSHL = SHLChunk::create();

    beginEditCP(_combineSHL);
    //_combineSHL->readVertexProgram("PCSS_Shadow_combine.vert");
    //_combineSHL->readFragmentProgram("PCSS_Shadow_combine.frag");
    _combineSHL->setVertexProgram(_shadow_combine_vp);
    _combineSHL->setFragmentProgram(_shadow_combine_fp);
    endEditCP(_combineSHL);

    _combineDepth = DepthChunk::create();
    beginEditCP(_combineDepth);
        _combineDepth->setReadOnly(true);
    endEditCP(_combineDepth);

    //Shadow Shader
    _shadowCmat = ChunkMaterial::create();

    //Combine Shader
    _combineCmat = ChunkMaterial::create();
    beginEditCP(_combineCmat);
    _combineCmat->addChunk(_combineSHL);
    _combineCmat->addChunk(_colorMap);
    _combineCmat->addChunk(_shadowFactorMap);
    _combineCmat->addChunk(_combineDepth);
    endEditCP(_combineCmat);

    _pf = PolygonForeground::create();
    beginEditCP(_pf);
    // ref counting is not supported in the polygon foreground!
    _pf->setMaterial(_combineCmat);
    _pf->getTexCoords().push_back(Vec3f(0.0f, 0.0f, 0.0f));
    _pf->getPositions().push_back(Pnt2f(0.0f, 0.0f));

    _pf->getTexCoords().push_back(Vec3f(1.0f, 0.0f, 0.0f));
    _pf->getPositions().push_back(Pnt2f(1.0f, 0.0f));

    _pf->getTexCoords().push_back(Vec3f(1.0f, 1.0f, 0.0f));
    _pf->getPositions().push_back(Pnt2f(1.0f, 1.0f));

    _pf->getTexCoords().push_back(Vec3f(0.0f, 1.0f, 0.0f));
    _pf->getPositions().push_back(Pnt2f(0.0f, 1.0f));

    _pf->setNormalizedX(true);
    _pf->setNormalizedY(true);
    endEditCP(_pf);

    addRefCP(_colorMap);
    addRefCP(_shadowFactorMap);
    addRefCP(_shadowSHL);
    addRefCP(_shadowCmat);
    addRefCP(_combineSHL);
    addRefCP(_combineDepth);
    addRefCP(_combineCmat);
    addRefCP(_pf);
}

PCSSShadowMap::~PCSSShadowMap(void)
{
    if(_tiledeco != NullFC)
        subRefCP(_tiledeco);

    subRefCP(_colorMap);
    subRefCP(_shadowFactorMap);
    subRefCP(_shadowSHL);
    subRefCP(_shadowCmat);
    subRefCP(_combineSHL);
    subRefCP(_combineDepth);
    subRefCP(_combineCmat);
    subRefCP(_pf);

#ifdef USE_FBO_FOR_COLOR_AND_FACTOR_MAP
    if(_fb != 0)
        glDeleteFramebuffersEXT(1, &_fb);
    if(_rb_depth != 0)
        glDeleteRenderbuffersEXT(1, &_rb_depth);
#endif
    if(_fb2 != 0)
        glDeleteFramebuffersEXT(1, &_fb2);
}

/// Checks if FBO status is ok
bool PCSSShadowMap::checkFrameBufferStatus(Window *win)
{
    GLenum  errCode, status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);

    switch(status)
    {
        case GL_FRAMEBUFFER_COMPLETE_EXT:
            FINFO(("%x: framebuffer complete!\n", status));
            break;
        case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
            FWARNING(("%x: framebuffer GL_FRAMEBUFFER_UNSUPPORTED_EXT\n",
                      status));
            // choose different formats
            return false;
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
            FWARNING(("%x: framebuffer INCOMPLETE_ATTACHMENT\n", status));
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
            FWARNING(("%x: framebuffer FRAMEBUFFER_MISSING_ATTACHMENT\n",
                      status));
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
            FWARNING(("%x: framebuffer FRAMEBUFFER_DIMENSIONS\n", status));
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

    if((errCode = glGetError()) != GL_NO_ERROR)
    {
        const GLubyte   *errString = gluErrorString(errCode);
        FWARNING(("OpenGL Error: %s!\n", errString));
        return false;
    }
    return true;
}


bool PCSSShadowMap::initFBO(Window *win)
{
    if(_useFBO)
    {
        Int32   width = _shadowVP->getPixelWidth();
        Int32   height = _shadowVP->getPixelHeight();

        if(width <= 0 || height <= 0)
            return false;

        if(_fb2 != 0)
            return true;

#ifdef USE_FBO_FOR_COLOR_AND_FACTOR_MAP
        glGenFramebuffersEXT(1, &_fb);
        glGenRenderbuffersEXT(1, &_rb_depth);

        win->validateGLObject(_colorMap->getGLId());
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, _fb);
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,
                                  GL_TEXTURE_2D,
                                  win->getGLObjectId(_colorMap->getGLId()), 0);
        win->validateGLObject(_shadowFactorMap->getGLId());
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT1_EXT,
                                  GL_TEXTURE_2D,
                                  win->getGLObjectId(_shadowFactorMap->getGLId
                                                     ()), 0);

        //Initialize Depth Renderbuffer
        glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, _rb_depth);
        if(_useNPOTTextures)
            glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24_ARB
                                     , _shadowVP->getPixelWidth(),
                                     _shadowVP->getPixelHeight());
        else
            glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24_ARB
                                     , _widthHeightPOT, _widthHeightPOT);
        //Attach Renderbuffer to Framebuffer depth Buffer
        glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT
                                     , GL_RENDERBUFFER_EXT, _rb_depth);

        win->validateGLObject(_colorMap->getGLId());
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,
                                  GL_TEXTURE_2D,
                                  win->getGLObjectId(_colorMap->getGLId()), 0);

        win->validateGLObject(_shadowFactorMap->getGLId());
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT1_EXT,
                                  GL_TEXTURE_2D,
                                  win->getGLObjectId(_shadowFactorMap->getGLId
                                                     ()), 0);

        bool    result = checkFrameBufferStatus(win);
#endif

        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
        glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);

        glGenFramebuffersEXT(1, &_fb2);
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, _fb2);

        glDrawBuffer(GL_NONE);	// no color buffer dest
        glReadBuffer(GL_NONE);	// no color buffer src

        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
        glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);

    }

    return true;
}

void PCSSShadowMap::reInit(Window *win)
{
#ifdef USE_FBO_FOR_COLOR_AND_FACTOR_MAP
    Int32   width = _shadowVP->getPixelWidth();
    Int32   height = _shadowVP->getPixelHeight();

    win->validateGLObject(_colorMap->getGLId());
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, _fb);
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,
                              GL_TEXTURE_2D,
                              win->getGLObjectId(_colorMap->getGLId()), 0);
    win->validateGLObject(_shadowFactorMap->getGLId());
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT1_EXT,
                              GL_TEXTURE_2D,
                              win->getGLObjectId(_shadowFactorMap->getGLId()),
                              0);

    //Initialize Depth Renderbuffer
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, _rb_depth);
    if(_useNPOTTextures)
        glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24_ARB,
                                 _shadowVP->getPixelWidth(),
                                 _shadowVP->getPixelHeight());
    else
        glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24_ARB,
                                 _widthHeightPOT, _widthHeightPOT);
    //Attach Renderbuffer to Framebuffer depth Buffer
    glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT
                                 , _rb_depth);
#endif
}

void PCSSShadowMap::initTextures(Window *win)
{
    _initTexturesDone = true;

    Int32   width = _shadowVP->getPixelWidth();
    Int32   height = _shadowVP->getPixelHeight();

    //if no NPOTTextures supported, resize images
    if(!_useNPOTTextures)
    {
        if(width > height)
            _widthHeightPOT = osgnextpower2(width - 1);
        else
            _widthHeightPOT = osgnextpower2(height - 1);

        beginEditCP(_colorMap);
        beginEditCP(_colorMapImage);
        _colorMapImage->set(GL_RGB, _widthHeightPOT, _widthHeightPOT);
        endEditCP(_colorMapImage);
        endEditCP(_colorMap);

        beginEditCP(_shadowFactorMap);
        beginEditCP(_shadowFactorMapImage);
        _shadowFactorMapImage->set(GL_RGB, _widthHeightPOT, _widthHeightPOT);
        endEditCP(_shadowFactorMapImage);
        endEditCP(_shadowFactorMap);
    }
}

void PCSSShadowMap::createShadowMaps(RenderActionBase *action)
{
    if(_tiledeco == NullFC)
    {
        _tiledeco = TileCameraDecorator::create();
        addRefCP(_tiledeco);
    }

    //Checking for the smallest Window-Dimension
    UInt32  minSize = _shadowVP->getPixelWidth();

    if(_shadowVP->getPixelHeight() < minSize)
        minSize = _shadowVP->getPixelHeight();

    //Checking for biggest PowerOf2 that fits in smallest Window-Dimension
    UInt32  _mapRenderSize = osgnextpower2(minSize + 1) / 2;
    if(_mapRenderSize == 0)
        _mapRenderSize = 128;

    Real32  vpTop, vpBottom, vpLeft, vpRight;

    //------Setting up Window to fit size of ShadowMap----------------

    // Saving original Viewport-Dimensions
    vpTop = _shadowVP->getTop();
    vpBottom = _shadowVP->getBottom();
    vpLeft = _shadowVP->getLeft();
    vpRight = _shadowVP->getRight();

    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glShadeModel(GL_FLAT);
    glDisable(GL_LIGHTING);
    glDepthMask(GL_TRUE);

    // disable all lights more speed
    std::vector<bool> lightStates;
    for(UInt32 i = 0;i < _shadowVP->_lights.size();++i)
    {
        // store old states.
        lightStates.push_back(_shadowVP->_lights[i].second->getOn());
        _shadowVP->_lights[i].second->setOn(false);
    }

    // deactivate exclude nodes:
    for(UInt32 i = 0;i < _shadowVP->getExcludeNodes().getSize();++i)
    {
        NodePtr exnode = _shadowVP->getExcludeNodes()[i];
        if(exnode != NullFC)
            exnode->setActive(false);
    }

    for(UInt32 i = 0;i < _shadowVP->_lights.size();++i)
    {
        if(_shadowVP->_lightStates[i] != 0)
        {
            if(_shadowVP->getGlobalShadowIntensity() != 0.0 ||
               _shadowVP->_lights[i].second->getShadowIntensity() != 0.0)
            {
                if(_mapRenderSize > _shadowVP->getMapSize())
                    _mapRenderSize = _shadowVP->getMapSize();
                _shadowVP->setVPSize(0, 0, _mapRenderSize - 1, _mapRenderSize -
                                     1);
                // we use a tiledecorator to create shadow maps with
                // a higher resolutions than the viewport or the screen.
                beginEditCP(_tiledeco);
                _tiledeco->setDecoratee(_shadowVP->_lightCameras[i]);
                _tiledeco->setFullSize(_shadowVP->getMapSize(),
                                       _shadowVP->getMapSize());
                endEditCP(_tiledeco);

                action->setCamera(_tiledeco.getCPtr());

                Real32  step = (1.0 / Real32(_shadowVP->getMapSize())) *
                    Real32(_mapRenderSize);

                UInt32  ypos = 0;
                for(Real32 y = 0;y < 1.0;y += step)
                {
                    UInt32  xpos = 0;
                    for(Real32 x = 0;x < 1.0;x += step)
                    {
                        beginEditCP(_tiledeco);
                        _tiledeco->setSize(x, y, x + step, y + step);
                        endEditCP(_tiledeco);

                        glClear(GL_DEPTH_BUFFER_BIT);
                        glPolygonOffset(_shadowVP->getOffFactor(),
                                        _shadowVP->getOffBias());
                        glEnable(GL_POLYGON_OFFSET_FILL);

                        _shadowVP->renderLight(action, _unlitMat.getCPtr(), i);

                        action->getWindow()->validateGLObject(
                            _shadowVP->_texChunks[i]->getGLId());

                        glDisable(GL_POLYGON_OFFSET_FILL);

                        //----------Shadow-Texture-Parameters and Indices-------------

                        glBindTexture(GL_TEXTURE_2D,
                                      action->getWindow()->getGLObjectId(
                                      _shadowVP->_texChunks[i]->getGLId()));
                        if(glGetError() != GL_NO_ERROR)
                            SWARNING << "Error on binding Texture!" << endLog;

                        glCopyTexSubImage2D(GL_TEXTURE_2D, 0, xpos, ypos, 0, 0,
                                            _mapRenderSize, _mapRenderSize);

                        if(glGetError() != GL_NO_ERROR)
                            SWARNING << "Error on copying Texture!" << endLog;

                        glBindTexture(GL_TEXTURE_2D, 0);
                        if(glGetError() != GL_NO_ERROR)
                            SWARNING << "Error on releasing Texture!" <<
                                endLog;

                        if(glGetError() != GL_NO_ERROR)
                            SWARNING << "Error while Texture-Creation!" <<
                                endLog;

                        xpos += _mapRenderSize;
                    }
                    ypos += _mapRenderSize;
                }
            }
        }
    }


    // enable all lights.
    for(UInt32 i = 0;i < _shadowVP->_lights.size();++i)
    {
        // restore old states.
        _shadowVP->_lights[i].second->setOn(lightStates[i]);
    }

    // activate exclude nodes:
    for(UInt32 i = 0;i < _shadowVP->getExcludeNodes().getSize();++i)
    {
        NodePtr exnode = _shadowVP->getExcludeNodes()[i];
        if(exnode != NullFC)
            if(_shadowVP->_excludeNodeActive[i])
                exnode->setActive(true);
    }
    //-------Restoring old states of Window and Viewport----------

    beginEditCP(_shadowVP->getCamera(),
                _shadowVP->LeftFieldMask | _shadowVP->RightFieldMask |
                _shadowVP->BottomFieldMask | _shadowVP->TopFieldMask);
    {
        _shadowVP->setSize(vpLeft, vpBottom, vpRight, vpTop);
    }
    endEditCP(_shadowVP->getCamera(),
              _shadowVP->LeftFieldMask | _shadowVP->RightFieldMask |
              _shadowVP->BottomFieldMask | _shadowVP->TopFieldMask);

    action->setCamera(_shadowVP->getCamera().getCPtr());

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
}

void PCSSShadowMap::createShadowMapsFBO(RenderActionBase *action)
{
    UInt32  oldWidth, oldHeight;
    oldWidth = _shadowVP->getPixelWidth();
    oldHeight = _shadowVP->getPixelHeight();

    //------Setting up Window to fit size of ShadowMap----------------

    _shadowVP->setVPSize(0, 0, _shadowVP->getMapSize() - 1,
                         _shadowVP->getMapSize() - 1);

    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glShadeModel(GL_FLAT);
    glDisable(GL_LIGHTING);
    glDepthMask(GL_TRUE);

    // disable all lights more speed
    std::vector<bool> lightStates;
    for(UInt32 i = 0;i < _shadowVP->_lights.size();++i)
    {
        // store old states.
        lightStates.push_back(_shadowVP->_lights[i].second->getOn());
        _shadowVP->_lights[i].second->setOn(false);
    }

    // deactivate exclude nodes:
    for(UInt32 i = 0;i < _shadowVP->getExcludeNodes().getSize();++i)
    {
        NodePtr exnode = _shadowVP->getExcludeNodes()[i];
        if(exnode != NullFC)
            exnode->setActive(false);
    }

    for(UInt32 i = 0;i < _shadowVP->_lights.size();++i)
    {
        if(_shadowVP->_lightStates[i] != 0)
        {
            if(_shadowVP->getGlobalShadowIntensity() != 0.0 ||
               _shadowVP->_lights[i].second->getShadowIntensity() != 0.0)
            {

                action->getWindow()->validateGLObject(
                    _shadowVP->_texChunks[i]->getGLId());

                glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, _fb2);

                glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT
                                          , GL_TEXTURE_2D,
                                          action->getWindow()->getGLObjectId(
                                          _shadowVP->_texChunks[i]->getGLId()),
                                          0);

                glDrawBuffer(GL_NONE);
                glReadBuffer(GL_NONE);

                glPolygonOffset(_shadowVP->getOffFactor(),
                                _shadowVP->getOffBias());
                glEnable(GL_POLYGON_OFFSET_FILL);

                glClearColor(1.0, 1.0, 1.0, 1.0);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                action->setCamera(_shadowVP->_lightCameras[i].getCPtr());

                _shadowVP->renderLight(action, _unlitMat.getCPtr(), i);

                glDisable(GL_POLYGON_OFFSET_FILL);

                glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

                glClearColor(0.0, 0.0, 0.0, 1.0);

                action->setCamera(_shadowVP->getCamera().getCPtr());
            }
        }
    }

    //-------Restoring old states of Window and Viewport----------
    // enable all lights.
    for(UInt32 i = 0;i < _shadowVP->_lights.size();++i)
    {
        // restore old states.
        _shadowVP->_lights[i].second->setOn(lightStates[i]);
    }

    // activate exclude nodes:
    for(UInt32 i = 0;i < _shadowVP->getExcludeNodes().getSize();++i)
    {
        NodePtr exnode = _shadowVP->getExcludeNodes()[i];
        if(exnode != NullFC)
            if(_shadowVP->_excludeNodeActive[i])
                exnode->setActive(true);
    }

    _shadowVP->setVPSize(0, 0, oldWidth - 1, oldHeight - 1);
    _shadowVP->setVPSize(0, 0, 1, 1);

    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
}

void PCSSShadowMap::createColorMap(RenderActionBase *action)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _shadowVP->getBackground()->clear(action, _shadowVP);

    action->apply(_shadowVP->getRoot());

    // disable occluded lights.
    _shadowVP->checkLightsOcclusion(action);

    action->getWindow()->validateGLObject(_colorMap->getGLId());

    _shadowVP->setReadBuffer(); // set the right read buffer for the copy texture.
    glBindTexture(GL_TEXTURE_2D,
                  action->getWindow()->getGLObjectId(_colorMap->getGLId()));
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0,
                        _shadowVP->getPixelWidth(),
                        _shadowVP->getPixelHeight());
    glBindTexture(GL_TEXTURE_2D, 0);

}

void PCSSShadowMap::createColorMapFBO(RenderActionBase *action)
{

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Window  *win = action->getWindow();

    GLenum  *buffers = NULL;
    buffers = new GLenum[1];
    buffers[0] = GL_COLOR_ATTACHMENT0_EXT;

    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, _fb);
	
    glDrawBuffer(*buffers);

    _shadowVP->getBackground()->clear(action, _shadowVP);
    action->apply(_shadowVP->getRoot());

    // disable occluded lights.
    _shadowVP->checkLightsOcclusion(action);

    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	
    delete[] buffers;

}

void PCSSShadowMap::createShadowFactorMapFBO(RenderActionBase *action,
                                             UInt32 num)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);

    //Finde alle aktiven Lichtquellen
    Real32  activeLights = 0;
    if(_shadowVP->getGlobalShadowIntensity() != 0.0)
    {
        for(UInt32 i = 0;i < _shadowVP->_lights.size();i++)
        {
            if(_shadowVP->_lightStates[i] != 0)
                activeLights++;
        }
    }
    else
    {
        for(UInt32 i = 0;i < _shadowVP->_lights.size();i++)
        {
            if(_shadowVP->_lightStates[i] != 0 &&
               _shadowVP->_lights[i].second->getShadowIntensity() != 0.0)
                activeLights++;
        }
    }

    Real32  shadowIntensity;
    if(_shadowVP->getGlobalShadowIntensity() != 0.0)
        shadowIntensity = (_shadowVP->getGlobalShadowIntensity() /
                           activeLights);
    else
        shadowIntensity = (_shadowVP->_lights[num].second->getShadowIntensity() /
                           activeLights);
    if(_shadowVP->_lights[num].second->getShadowIntensity() != 0.0 ||
       _shadowVP->getGlobalShadowIntensity() != 0.0)
    {

        Matrix  LVM, LPM, CVM;
        _shadowVP->_lightCameras[num]->getViewing(LVM,
                                                  _shadowVP->getPixelWidth(),
                                                  _shadowVP->getPixelHeight());
        _shadowVP->_lightCameras[num]->getProjection(LPM,
                                                     _shadowVP->getPixelWidth
                                                     (),
                                                     _shadowVP->getPixelHeight
                                                     ());
        _shadowVP->getCamera()->getViewing(CVM, _shadowVP->getPixelWidth(),
                                           _shadowVP->getPixelHeight());
        Matrix  iCVM = CVM;
        iCVM.invert();

        Real32  texFactor;
        if(_shadowVP->_lights[num].second->getType() == SpotLight::getClassType() ||
           _shadowVP->_lights[num].second->getType() == PointLight::getClassType())
            texFactor = Real32(_width) / Real32(_height);
        else
            texFactor = 1.0;

        Matrix  shadowMatrix = LPM;
        shadowMatrix.mult(LVM);
        shadowMatrix.mult(iCVM);

        Real32  xFactor = 1.0;
        Real32  yFactor = 1.0;
        if(!_useNPOTTextures)
        {
            xFactor = Real32(_width) / Real32(_widthHeightPOT);
            yFactor = Real32(_height) / Real32(_widthHeightPOT);
        }

        Real32  lightSize;
        if(_shadowVP->_lights[num].second->getType() != DirectionalLight::getClassType
           ())
            lightSize = _shadowVP->getShadowSmoothness() * 10.0;
        else
            lightSize = _shadowVP->getShadowSmoothness() / 25.0;

        beginEditCP(_shadowSHL, ShaderChunk::ParametersFieldMask);
        _shadowSHL->setUniformParameter("shadowMap", 0);
        _shadowSHL->setUniformParameter("oldFactorMap", 1);
        _shadowSHL->setUniformParameter("firstRun", _firstRun);
        _shadowSHL->setUniformParameter("intensity", shadowIntensity);
        _shadowSHL->setUniformParameter("texFactor", texFactor);
        _shadowSHL->setUniformParameter("lightPM", shadowMatrix);
        _shadowSHL->setUniformParameter("mapSize",
                                        Real32(_shadowVP->getMapSize()));
        _shadowSHL->setUniformParameter("lightSize", Real32(lightSize));
        _shadowSHL->setUniformParameter("xFactor", Real32(xFactor));
        _shadowSHL->setUniformParameter("yFactor", Real32(yFactor));
        endEditCP(_shadowSHL, ShaderChunk::ParametersFieldMask);

        beginEditCP(_shadowCmat);
        _shadowCmat->clearChunks();
        _shadowCmat->addChunk(_shadowSHL);
        _shadowCmat->addChunk(_shadowVP->_texChunks[num]);
        _shadowCmat->addChunk(_shadowFactorMap);
        endEditCP(_shadowCmat);

        GLenum  *buffers = NULL;
        buffers = new GLenum[1];
        buffers[0] = GL_COLOR_ATTACHMENT1_EXT;

        //Setup FBO
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, _fb);

        glDrawBuffer(*buffers);

        //draw the Scene
        if(_firstRun)
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        _shadowVP->renderLight(action, _shadowCmat.getCPtr(), num);

        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

        delete[] buffers;
        _firstRun = 0;
    }
}

void PCSSShadowMap::createShadowFactorMap(RenderActionBase *action, UInt32 num)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    if(_firstRun)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Finde alle aktiven Lichtquellen
    Real32  activeLights = 0;
    if(_shadowVP->getGlobalShadowIntensity() != 0.0)
    {
        for(UInt32 i = 0;i < _shadowVP->_lights.size();i++)
        {
            if(_shadowVP->_lightStates[i] != 0)
                activeLights++;
        }
    }
    else
    {
        for(UInt32 i = 0;i < _shadowVP->_lights.size();i++)
        {
            if(_shadowVP->_lightStates[i] != 0 &&
               _shadowVP->_lights[i].second->getShadowIntensity() != 0.0)
                activeLights++;
        }
    }

    Real32  shadowIntensity;
    if(_shadowVP->getGlobalShadowIntensity() != 0.0)
        shadowIntensity = (_shadowVP->getGlobalShadowIntensity() /
                           activeLights);
    else
        shadowIntensity = (_shadowVP->_lights[num].second->getShadowIntensity() /
                           activeLights);
    if(_shadowVP->_lights[num].second->getShadowIntensity() != 0.0 ||
       _shadowVP->getGlobalShadowIntensity() != 0.0)
    {

        Matrix  LVM, LPM, CVM;
        _shadowVP->_lightCameras[num]->getViewing(LVM,
                                                  _shadowVP->getPixelWidth(),
                                                  _shadowVP->getPixelHeight());
        _shadowVP->_lightCameras[num]->getProjection(LPM,
                                                     _shadowVP->getPixelWidth
                                                     (),
                                                     _shadowVP->getPixelHeight
                                                     ());
        _shadowVP->getCamera()->getViewing(CVM, _shadowVP->getPixelWidth(),
                                           _shadowVP->getPixelHeight());
        Matrix  iCVM = CVM;
        iCVM.invert();
        Matrix  iLVM = LVM;
        iLVM.invert();

        Real32  texFactor;
        if(_shadowVP->_lights[num].second->getType() == SpotLight::getClassType() ||
           _shadowVP->_lights[num].second->getType() == PointLight::getClassType())
            texFactor = Real32(_width) / Real32(_height);
        else
            texFactor = 1.0;

        Matrix  shadowMatrix = LPM;
        shadowMatrix.mult(LVM);
        shadowMatrix.mult(iCVM);

        Real32  xFactor = 1.0;
        Real32  yFactor = 1.0;
        if(!_useNPOTTextures)
        {
            xFactor = Real32(_width) / Real32(_widthHeightPOT);
            yFactor = Real32(_height) / Real32(_widthHeightPOT);
        }

        Real32  lightSize;
        if(_shadowVP->_lights[num].second->getType() != DirectionalLight::getClassType
           ())
            lightSize = _shadowVP->getShadowSmoothness() * 10.0;
        else
            lightSize = _shadowVP->getShadowSmoothness() / 25.0;

        beginEditCP(_shadowSHL, ShaderChunk::ParametersFieldMask);
        _shadowSHL->setUniformParameter("shadowMap", 0);
        _shadowSHL->setUniformParameter("oldFactorMap", 1);
        _shadowSHL->setUniformParameter("firstRun", _firstRun);
        _shadowSHL->setUniformParameter("intensity", shadowIntensity);
        _shadowSHL->setUniformParameter("texFactor", texFactor);
        _shadowSHL->setUniformParameter("lightPM", shadowMatrix);
        _shadowSHL->setUniformParameter("mapSize",
                                        Real32(_shadowVP->getMapSize()));
        _shadowSHL->setUniformParameter("lightSize", Real32(lightSize));
        _shadowSHL->setUniformParameter("xFactor", Real32(xFactor));
        _shadowSHL->setUniformParameter("yFactor", Real32(yFactor));
        endEditCP(_shadowSHL, ShaderChunk::ParametersFieldMask);

        beginEditCP(_shadowCmat);
        _shadowCmat->clearChunks();
        _shadowCmat->addChunk(_shadowSHL);
        _shadowCmat->addChunk(_shadowVP->_texChunks[num]);
        _shadowCmat->addChunk(_shadowFactorMap);
        endEditCP(_shadowCmat);

        _shadowVP->renderLight(action, _shadowCmat.getCPtr(), num);

        action->getWindow()->validateGLObject(_shadowFactorMap->getGLId());

        glBindTexture(GL_TEXTURE_2D,
                      action->getWindow()->getGLObjectId(
                      _shadowFactorMap->getGLId()));
        glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0,
                            _shadowVP->getPixelWidth(),
                            _shadowVP->getPixelHeight());
        glBindTexture(GL_TEXTURE_2D, 0);

        _firstRun = 0;
    }
}

void PCSSShadowMap::drawCombineMap(RenderActionBase *action)
{
    Real32  xFactor = 1.0;
    Real32  yFactor = 1.0;
    if(!_useNPOTTextures)
    {
        xFactor = Real32(_width) / Real32(_widthHeightPOT);
        yFactor = Real32(_height) / Real32(_widthHeightPOT);
    }

    beginEditCP(_combineSHL, ShaderChunk::ParametersFieldMask);
    _combineSHL->setUniformParameter("colorMap", 0);
    _combineSHL->setUniformParameter("shadowFactorMap", 1);
    _combineSHL->setUniformParameter("xFactor", Real32(xFactor));
    _combineSHL->setUniformParameter("yFactor", Real32(yFactor));
    _combineSHL->setUniformParameter("hasFactorMap", hasFactorMap());
    endEditCP(_combineSHL, ShaderChunk::ParametersFieldMask);

    //draw the Scene
    // glViewport is called in the render action but we don't use the renderaction here!
    GLint   pl = _shadowVP->getPixelLeft(), pr = _shadowVP->getPixelRight(),
            pb = _shadowVP->getPixelBottom(),
            pt = _shadowVP->getPixelTop();
    GLint   pw = pr - pl + 1, ph = pt - pb + 1;
    glViewport(pl, pb, pw, ph);
    glScissor(pl, pb, pw, ph);
    glEnable(GL_SCISSOR_TEST);

    // we can't use the shadowVP camera here could be a TileCameraDecorator!
    action->setCamera(_combine_camera.getCPtr());
    _pf->draw(action, _shadowVP);
    action->setCamera(_shadowVP->getCamera().getCPtr());

    glDisable(GL_SCISSOR_TEST);
}

void PCSSShadowMap::render(RenderActionBase *action)
{
    Window  *win = action->getWindow();
    initialize(win);

    if(!_useGLSL || !_useShadowExt)
        _shadowVP->Viewport::render(action);
    else
    {
        glPushAttrib(GL_ENABLE_BIT);

        if(!_initTexturesDone)
            initTextures(win);

        if(_useFBO)
        {
            if(!initFBO(win))
                printf("ERROR with FBOBJECT\n");
        }

        GLfloat globalAmbient[] =
        {
            0.0, 0.0, 0.0, 1.0
        };
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);
        _firstRun = 1;

        for(UInt32 i = 0;i < _shadowVP->_lights.size();i++)
        {
            beginEditCP(_shadowVP->_texChunks[i]);
            {
                _shadowVP->_texChunks[i]->setMinFilter(GL_NEAREST);
                _shadowVP->_texChunks[i]->setMagFilter(GL_NEAREST);
            }
            endEditCP(_shadowVP->_texChunks[i]);
        }

        if(_shadowVP->getPixelWidth() != _width ||
           _shadowVP->getPixelHeight() != _height)
        {
            _width = _shadowVP->getPixelWidth();
            _height = _shadowVP->getPixelHeight();

            if(_useNPOTTextures)
            {
                beginEditCP(_colorMap);
                beginEditCP(_colorMapImage);
                _colorMapImage->set(GL_RGB, _width, _height);
                endEditCP(_colorMapImage);
                endEditCP(_colorMap);

                beginEditCP(_shadowFactorMap);
                beginEditCP(_shadowFactorMapImage);
                _shadowFactorMapImage->set(GL_RGB, _width, _height);
                endEditCP(_shadowFactorMapImage);
                endEditCP(_shadowFactorMap);

                reInit(win);
            }
            else
            {
                if(_width > _height)
                    _widthHeightPOT = osgnextpower2(_width - 1);
                else
                    _widthHeightPOT = osgnextpower2(_height - 1);

                beginEditCP(_colorMap);
                beginEditCP(_colorMapImage);
                _colorMapImage->set(GL_RGB, _widthHeightPOT, _widthHeightPOT);
                endEditCP(_colorMapImage);
                endEditCP(_colorMap);

                beginEditCP(_shadowFactorMap);
                beginEditCP(_shadowFactorMapImage);
                _shadowFactorMapImage->set(GL_RGB, _widthHeightPOT,
                                           _widthHeightPOT);
                endEditCP(_shadowFactorMapImage);
                endEditCP(_shadowFactorMap);
            }
        }


        if(_shadowVP->getMapAutoUpdate())
        {
#ifdef USE_FBO_FOR_COLOR_AND_FACTOR_MAP
            if(_useFBO && _useNPOTTextures)
                createColorMapFBO(action);
            else
#endif
                createColorMap(action);

            //deactivate transparent Nodes
            for(UInt32 t = 0;t < _shadowVP->_transparent.size();++t)
                _shadowVP->_transparent[t]->setActive(false);

            if(_useFBO)
                createShadowMapsFBO(action);
            else
                createShadowMaps(action);

            // switch on all transparent geos
            for(UInt32 t = 0;t < _shadowVP->_transparent.size();++t)
                _shadowVP->_transparent[t]->setActive(true);

            for(UInt32 i = 0;i < _shadowVP->_lights.size();i++)
            {
                if(_shadowVP->_lightStates[i] != 0)
                {
                    if(_shadowVP->getGlobalShadowIntensity() != 0.0 ||
                       _shadowVP->_lights[i].second->getShadowIntensity() != 0.0)
                    {
#ifdef USE_FBO_FOR_COLOR_AND_FACTOR_MAP
                        if(_useFBO && _useNPOTTextures)
                            createShadowFactorMapFBO(action, i);
                        else
#endif
                            createShadowFactorMap(action, i);
                        //_firstRun = 0;
                    }
                }
            }
        }
        else
        {
            if(_shadowVP->_trigger_update)
            {
#ifdef USE_FBO_FOR_COLOR_AND_FACTOR_MAP
                if(_useFBO && _useNPOTTextures)
                    createColorMapFBO(action);
                else
#endif
                    createColorMap(action);

                //deactivate transparent Nodes
                for(UInt32 t = 0;t < _shadowVP->_transparent.size();++t)
                    _shadowVP->_transparent[t]->setActive(false);

                if(_useFBO)
                    createShadowMapsFBO(action);
                else
                    createShadowMaps(action);

                // switch on all transparent geos
                for(UInt32 t = 0;t < _shadowVP->_transparent.size();++t)
                    _shadowVP->_transparent[t]->setActive(true);

                for(UInt32 i = 0;i < _shadowVP->_lights.size();i++)
                {
                    if(_shadowVP->_lightStates[i] != 0)
                    {
                        if(_shadowVP->getGlobalShadowIntensity() != 0.0 ||
                           _shadowVP->_lights[i].second->getShadowIntensity() != 0.0)
                        {
#ifdef USE_FBO_FOR_COLOR_AND_FACTOR_MAP
                            if(_useFBO && _useNPOTTextures)
                                createShadowFactorMapFBO(action, i);
                            else
#endif
                                createShadowFactorMap(action, i);
                        }
                    }
                }
                _shadowVP->_trigger_update = false;
            }
        }

        drawCombineMap(action);

        glPopAttrib();
        // render the foregrounds.
        for(UInt16 i = 0;i < _shadowVP->getForegrounds().size();++i)
        {
            _shadowVP->getForegrounds(i)->draw(action, _shadowVP);
        }
    }
}

