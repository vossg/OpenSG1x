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

#include "OSGVarianceShadowMap.h"
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

#define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF


OSG_USING_NAMESPACE


static std::string _depth_vp =
    "varying vec3 lightVec;\n"
    "varying vec4 screenPos;\n"
    "\n"
    "void main(void)\n"
    "{\n"
    "  lightVec = (gl_ModelViewMatrix * gl_Vertex).xyz;\n"
    "  screenPos = gl_ModelViewProjectionMatrix * gl_Vertex;\n"
    "  gl_Position = ftransform();\n"
    "}\n";

static std::string _depth_fp =
    "uniform float sceneDiagLength;\n"
    "uniform bool isDirLight;\n"
    "varying vec3 lightVec;\n"
    "varying vec4 screenPos;\n"
    "\n"
    "const float dist_fact = 32.0;\n"
    "\n"
    "void main(void)\n"
    "{\n"
    "	float x;\n"
    "	if(isDirLight) x = gl_FragCoord.z;\n"
    "	else x = ((length(lightVec)/sceneDiagLength)*2.0)-1.0;\n"
    "	vec2 moments = vec2(x, x*x);\n"
    "	vec2 m1,m2;\n"
    "	m2 = fract(moments * dist_fact);\n"
    "	m1 = moments - (m2 / dist_fact);\n"
    "	gl_FragColor = vec4(m1,m2);\n"
    "}\n";

static std::string _variance_vp =
    "uniform float shadowBias;\n"
    "uniform mat4 lightPM;\n"
    "uniform mat4 lightPM2;\n"
    "uniform float texFactor;\n"
    "varying vec4 projCoord;\n"
    "varying vec4 projCoord2;\n"
    "varying vec4 texPos;\n"
    "varying vec4 realPos;\n"
    "\n"
#ifndef NO_CONST_GLSL_VAR
    "const "
#endif
    "mat4 bias = mat4(0.5,0.0,0.0,0.0,0.0,0.5,0.0,0.0,0.0,0.0,0.5,0.0,0.5,0.5,0.5,1.0);\n""\n"
    "\n"
    "void main(void)\n"
    "{\n"
    "  realPos = gl_ModelViewMatrix * gl_Vertex;\n"
    "  projCoord = lightPM * realPos;\n"
    "  projCoord.x *= texFactor;\n"
    "  projCoord2 = lightPM2 * realPos;\n"
    "  texPos = gl_ModelViewProjectionMatrix * gl_Vertex;\n"
    "  projCoord = bias * projCoord;\n"
    "  texPos = bias * texPos;\n"
    "  gl_Position = ftransform();\n"
    "}\n";

static std::string _variance_fp =
    "uniform sampler2D shadowMap;\n"
    "uniform sampler2D oldFactorMap;\n"
    "uniform float intensity;\n"
    "uniform int firstRun;\n"
    "uniform float xFactor;\n"
    "uniform float yFactor;\n"
    "uniform float sceneDiagLength;\n"
    "uniform float Lod;\n"
    "uniform bool isDirLight;\n"
    "\n"
    "varying vec4 projCoord;\n"
    "varying vec4 projCoord2;\n"
    "varying vec4 texPos;\n"
    "varying vec4 realPos;\n"
    "\n"
    "const float epsilon = 0.00025;\n"
    "const float dist_factor = 32.0;\n"
    "\n"
    "void main(void)\n"
    "{\n"
    "	vec4 projectiveBiased = vec4((projCoord.xyz / projCoord.q),1.0);\n"
    "	float shadowed = 0.0;\n"
    "\n"
    "	vec2 moments = texture2DLod(shadowMap,projectiveBiased.xy,Lod).xy;\n"
    "	moments += texture2DLod(shadowMap,projectiveBiased.xy,Lod).zw / dist_factor;\n"
    "	\n"
    "	float distL;\n"
    "	if(isDirLight) distL = projectiveBiased.z;\n"
    "	else distL = ((length(projCoord2.xyz)/sceneDiagLength)*2.0)-1.0;\n"
    "\n"
    "	if(distL  < moments.x) shadowed = 0.0;\n"
    "	else\n"
    "	{\n"
    "		float E_x2 = moments.y;\n"
    "		float Ex_2 = moments.x * moments.x;\n"
    "		float variance = min(max(E_x2 - Ex_2,epsilon), 1.0);\n"
    "		float m_d = moments.x - distL;\n"
    "		float p_max = variance / (variance + m_d * m_d);\n"
    "		shadowed = 1.0 - p_max;\n"
    "	}\n"
    "	shadowed *= intensity;\n"
    "	if(firstRun == 0) shadowed += texture2DProj(oldFactorMap,vec3(texPos.xy * vec2(xFactor,yFactor),texPos.w)).x;\n"
    "	gl_FragColor = vec4(shadowed,0.0,0.0,1.0);\n"
    "}\n";

VarianceShadowMap::VarianceShadowMap(ShadowViewport *source) :
    TreeRenderer(source),
    _tiledeco(NullFC),
    _colorMap(NullFC),
    _shadowFactorMap(NullFC),
    _colorMapImage(NullFC),
    _shadowFactorMapImage(NullFC),
    _shadowSHL(NullFC),
    _combineSHL(NullFC),
    _combineDepth(NullFC),
    _depthCmat(NullFC),
    _depthSHL(NullFC),
    _combineCmat(NullFC),
    _shadowCmat(NullFC),
    _pf(NullFC),
    _firstRun(1),
    _width(1),
    _height(1),
    _fb(0),
    _fb2(0),
    _rb_depth(0),
    _rb_depth2(0),
    _texChanged(false),
    _widthHeightPOT(0),
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
    //_shadowSHL->readVertexProgram("Variance_Shadow.vert");
    //_shadowSHL->readFragmentProgram("Variance_Shadow.frag");
    _shadowSHL->setVertexProgram(_variance_vp);
    _shadowSHL->setFragmentProgram(_variance_fp);
    endEditCP(_shadowSHL);

    //SHL Chunk 2
    _combineSHL = SHLChunk::create();

    beginEditCP(_combineSHL);
    //_combineSHL->readVertexProgram("Variance_Shadow_combine.vert");
    //_combineSHL->readFragmentProgram("Variance_Shadow_combine.frag");
    _combineSHL->setVertexProgram(_shadow_combine_vp);
    _combineSHL->setFragmentProgram(_shadow_combine_fp);
    endEditCP(_combineSHL);

    _combineDepth = DepthChunk::create();
    beginEditCP(_combineDepth);
        _combineDepth->setReadOnly(true);
    endEditCP(_combineDepth);

    _shadowCmat = ChunkMaterial::create();

    //Combine Shader
    _combineCmat = ChunkMaterial::create();
    beginEditCP(_combineCmat);
    _combineCmat->addChunk(_combineSHL);
    _combineCmat->addChunk(_colorMap);
    _combineCmat->addChunk(_shadowFactorMap);
    _combineCmat->addChunk(_combineDepth);
    endEditCP(_combineCmat);

    //SHL Depth
    _depthSHL = SHLChunk::create();

    beginEditCP(_depthSHL);
    //_depthSHL->readVertexProgram("depth.vert");
    //_depthSHL->readFragmentProgram("depth.frag");
    _depthSHL->setVertexProgram(_depth_vp);
    _depthSHL->setFragmentProgram(_depth_fp);
    endEditCP(_depthSHL);

    _depthCmat = ChunkMaterial::create();

    _pf = PolygonForeground::create();
    beginEditCP(_pf);
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
    addRefCP(_depthSHL);
    addRefCP(_combineSHL);
    addRefCP(_combineDepth);
    addRefCP(_combineCmat);
    addRefCP(_shadowCmat);
    addRefCP(_depthCmat);
    addRefCP(_pf);

}

VarianceShadowMap::~VarianceShadowMap(void)
{
    if(_tiledeco != NullFC)
        subRefCP(_tiledeco);

    subRefCP(_colorMap);
    subRefCP(_shadowFactorMap);
    subRefCP(_shadowSHL);
    subRefCP(_depthSHL);
    subRefCP(_combineSHL);
    subRefCP(_combineDepth);
    subRefCP(_combineCmat);
    subRefCP(_shadowCmat);
    subRefCP(_depthCmat);
    subRefCP(_pf);

#ifdef USE_FBO_FOR_COLOR_AND_FACTOR_MAP
    if(_fb != 0)
        glDeleteFramebuffersEXT(1, &_fb);
    if(_rb_depth != 0)
        glDeleteRenderbuffersEXT(1, &_rb_depth);
#endif
    if(_fb2 != 0)
        glDeleteFramebuffersEXT(1, &_fb2);
    if(_rb_depth2 != 0)
        glDeleteRenderbuffersEXT(1, &_rb_depth2);
}

/// Checks if FBO status is ok
bool VarianceShadowMap::checkFrameBufferStatus(Window *win)
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


bool VarianceShadowMap::initFBO(Window *win)
{
    if(!_texChanged)
    {
        //Set Shadow Map Texture to the needed Format
        Real32  maximumAnistropy;
        glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maximumAnistropy);
        maximumAnistropy = osgMin(maximumAnistropy, Real32(8.0));

        for(UInt32 i = 0;i < _shadowVP->_lights.size();i++)
        {
            beginEditCP(_shadowVP->_texChunks[i]);
            _shadowVP->_texChunks[i]->setImage(_shadowVP->_shadowImages[i]);
            _shadowVP->_texChunks[i]->setInternalFormat(GL_RGBA16F_ARB);
            _shadowVP->_texChunks[i]->setExternalFormat(GL_RGBA);
            _shadowVP->_texChunks[i]->setMinFilter(GL_LINEAR_MIPMAP_LINEAR);
            //_shadowVP->_texChunks[i]->setMinFilter(GL_LINEAR);
            _shadowVP->_texChunks[i]->setMagFilter(GL_LINEAR);
            _shadowVP->_texChunks[i]->setAnisotropy(maximumAnistropy);
            _shadowVP->_texChunks[i]->setWrapS(GL_REPEAT);
            _shadowVP->_texChunks[i]->setWrapT(GL_REPEAT);
            _shadowVP->_texChunks[i]->setTarget(GL_TEXTURE_2D);
            endEditCP(_shadowVP->_texChunks[i]);

            UInt32  mSize = _shadowVP->getMapSize();
            if(mSize > 2048)
                mSize = 2048;
            beginEditCP(_shadowVP->_shadowImages[i]);
            _shadowVP->_shadowImages[i]->set(Image::OSG_RGBA_PF, mSize, mSize,
                                             1, 1, 1, 0, 0,
                                             Image::OSG_FLOAT16_IMAGEDATA,
                                             false);
            endEditCP(_shadowVP->_shadowImages[i]);
        }
        _texChanged = true;
    }

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
        //setTarget(win, win->getGLObjectId(_colorMap->getGLId()), 0, GL_TEXTURE_2D);
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT,
                                  GL_TEXTURE_2D,
                                  win->getGLObjectId(_colorMap->getGLId()), 0);

        win->validateGLObject(_shadowFactorMap->getGLId());
        //setTarget(win, win->getGLObjectId(_shadowFactorMap->getGLId()), 1, GL_TEXTURE_2D);
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT1_EXT,
                                  GL_TEXTURE_2D,
                                  win->getGLObjectId(_shadowFactorMap->getGLId
                                                     ()), 0);

        bool    result = checkFrameBufferStatus(win);
#endif
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
        glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);

        //Variance Shadow Map Grabbing
        glGenFramebuffersEXT(1, &_fb2);
        glGenRenderbuffersEXT(1, &_rb_depth2);

        UInt32  mSize = _shadowVP->getMapSize();
        if(mSize > 2048)
            mSize = 2048;

        //Initialize Depth Renderbuffer
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, _fb2);
        glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, _rb_depth2);
        glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24_ARB,
                                 mSize, mSize);

        //Attach Renderbuffer to Framebuffer depth Buffer
        glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT
                                     , GL_RENDERBUFFER_EXT, _rb_depth2);

        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
        glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);

    }

    return true;
}

void VarianceShadowMap::reInit(Window *win)
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

void VarianceShadowMap::initTextures(Window *win)
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

void VarianceShadowMap::createShadowMapsFBO(RenderActionBase *action)
{
    UInt32  oldWidth, oldHeight;
    oldWidth = _shadowVP->getPixelWidth();
    oldHeight = _shadowVP->getPixelHeight();

    UInt32  mSize = _shadowVP->getMapSize();
    if(mSize > 2048)
        mSize = 2048;
    //------Setting up Window to fit size of ShadowMap----------------

    _shadowVP->setVPSize(0, 0, mSize - 1, mSize - 1);

    // disable all lights more speed
    std::vector<bool> lightStates;
    for(UInt32 i = 0;i < _shadowVP->_lights.size();++i)
    {
        // store old states.
        lightStates.push_back(_shadowVP->_lights[i].second->getOn());
        _shadowVP->_lights[i].second->setOn(false);
    }

    // activate exclude nodes:
    for(UInt32 i = 0;i < _shadowVP->getExcludeNodes().getSize();++i)
    {
        NodePtr exnode = _shadowVP->getExcludeNodes()[i];
        if(exnode != NullFC)
            if(_shadowVP->_excludeNodeActive[i])
                exnode->setActive(true);
    }

    for(UInt32 i = 0;i < _shadowVP->_lights.size();++i)
    {
        if(_shadowVP->_lightStates[i] != 0)
        {
            if(_shadowVP->getGlobalShadowIntensity() != 0.0 ||
               _shadowVP->_lights[i].second->getShadowIntensity() != 0.0)
            {
                //action->getWindow()->validateGLObject(_shadowVP->_texChunks[i]->getGLId());

                GLenum  *buffers = NULL;
                buffers = new GLenum[1];
                buffers[0] = GL_COLOR_ATTACHMENT0_EXT;

                action->getWindow()->validateGLObject(
                    _shadowVP->_texChunks[i]->getGLId());
                glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, _fb2);
                glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT
                                          , GL_TEXTURE_2D,
                                          action->getWindow()->getGLObjectId(
                                          _shadowVP->_texChunks[i]->getGLId()),
                                          0);

                //_shadowVP->_texChunks[i]->activate(action, action->getWindow()->getGLObjectId(_shadowVP->_texChunks[i]->getGLId()));
                glBindTexture(GL_TEXTURE_2D,
                              action->getWindow()->getGLObjectId(
                              _shadowVP->_texChunks[i]->getGLId()));
                glGenerateMipmapEXT(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, 0);
                //_shadowVP->_texChunks[i]->deactivate(action, action->getWindow()->getGLObjectId(_shadowVP->_texChunks[i]->getGLId()));

                glDrawBuffer(*buffers);

                glClearColor(1.0, 1.0, 1.0, 1.0);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                action->setCamera(_shadowVP->_lightCameras[i].getCPtr());

                Pnt3f   lPos;
                bool    isDirLight;
                Real32  sceneDiagLength;

                if(_shadowVP->_lights[i].second->getType() == PointLight::getClassType
                   ())
                {
                    PointLightPtr   tmpPoint;
                    tmpPoint = PointLightPtr::dcast(_shadowVP->_lights[i].second);

                    lPos = tmpPoint->getPosition();

                    if(tmpPoint->getBeacon() != NullFC)
                    {
                        Matrix  m = tmpPoint->getBeacon()->getToWorld();
                        m.mult(lPos);
                    }
                    isDirLight = false;

                    Pnt3f           center;
                    _shadowVP->getLightRoot(i)->getVolume().getCenter(center);

                    Vec3f           dir = lPos - center;
                    Real32          dirLength = dir.length();

                    Vec3f           diff =
                        (_shadowVP->getLightRoot(i)->getVolume().getMax() -
                         center);
                    Real32          diffLength = diff.length();

                    sceneDiagLength = dirLength + diffLength;
                }

                else if(_shadowVP->_lights[i].second->getType() ==
                        SpotLight::getClassType())
                {
                    SpotLightPtr    tmpSpot;
                    tmpSpot = SpotLightPtr::dcast(_shadowVP->_lights[i].second);
                    lPos = tmpSpot->getPosition();
                    if(tmpSpot->getBeacon() != NullFC)
                    {
                        Matrix  m = tmpSpot->getBeacon()->getToWorld();
                        m.mult(lPos);
                    }
                    isDirLight = false;
                    Pnt3f           center;
                    _shadowVP->getLightRoot(i)->getVolume().getCenter(center);

                    Vec3f           dir = lPos - center;
                    Real32          dirLength = dir.length();

                    Vec3f           diff =
                        (_shadowVP->getLightRoot(i)->getVolume().getMax() -
                         center);
                    Real32          diffLength = diff.length();

                    sceneDiagLength = dirLength + diffLength;
                }

                else
                {
                    isDirLight = true;
                    sceneDiagLength = 1.0;
                }

                beginEditCP(_depthSHL, ShaderChunk::ParametersFieldMask);
                _depthSHL->setUniformParameter("sceneDiagLength",
                                               Real32(sceneDiagLength));
                _depthSHL->setUniformParameter("isDirLight", bool(isDirLight));
                endEditCP(_depthSHL, ShaderChunk::ParametersFieldMask);

                beginEditCP(_depthCmat);
                _depthCmat->clearChunks();
                _depthCmat->addChunk(_depthSHL);
                endEditCP(_depthCmat);

                _shadowVP->renderLight(action, _depthCmat.getCPtr(), i);

                glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

                delete[] buffers;

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
}

void VarianceShadowMap::createColorMap(RenderActionBase *action)
{
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


void VarianceShadowMap::createColorMapFBO(RenderActionBase *action)
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

void VarianceShadowMap::createShadowFactorMap(RenderActionBase *action,
                                              UInt32 num)
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

        Real32  texFactor;
        if(_shadowVP->_lights[num].second->getType() == SpotLight::getClassType() ||
           _shadowVP->_lights[num].second->getType() == PointLight::getClassType())
            texFactor = Real32(_width) / Real32(_height);
        else
            texFactor = 1.0;

        Matrix  shadowMatrix = LPM;
        shadowMatrix.mult(LVM);
        shadowMatrix.mult(iCVM);

        Matrix  shadowMatrix2 = LVM;
        shadowMatrix2.mult(iCVM);


        Real32  xFactor = 1.0;
        Real32  yFactor = 1.0;
        if(!_useNPOTTextures)
        {
            xFactor = Real32(_width) / Real32(_widthHeightPOT);
            yFactor = Real32(_height) / Real32(_widthHeightPOT);
        }

        Pnt3f   lPos;
        bool    isDirLight;
        Real32  sceneDiagLength;

        if(_shadowVP->_lights[num].second->getType() == PointLight::getClassType())
        {
            PointLightPtr   tmpPoint;
            tmpPoint = PointLightPtr::dcast(_shadowVP->_lights[num].second);

            lPos = tmpPoint->getPosition();

            if(tmpPoint->getBeacon() != NullFC)
            {
                Matrix  m = tmpPoint->getBeacon()->getToWorld();
                m.mult(lPos);
            }
            isDirLight = false;
            Pnt3f           center;
            _shadowVP->getLightRoot(num)->getVolume().getCenter(center);

            Vec3f           dir = lPos - center;
            Real32          dirLength = dir.length();

            Vec3f           diff = (_shadowVP->getLightRoot(num)->getVolume
                                    ().getMax() - center);
            Real32          diffLength = diff.length();

            sceneDiagLength = dirLength + diffLength;
        }

        else if(_shadowVP->_lights[num].second->getType() == SpotLight::getClassType
                ())
        {
            SpotLightPtr    tmpSpot;
            tmpSpot = SpotLightPtr::dcast(_shadowVP->_lights[num].second);
            lPos = tmpSpot->getPosition();
            if(tmpSpot->getBeacon() != NullFC)
            {
                Matrix  m = tmpSpot->getBeacon()->getToWorld();
                m.mult(lPos);
            }
            isDirLight = false;
            Pnt3f           center;
            _shadowVP->getLightRoot(num)->getVolume().getCenter(center);

            Vec3f           dir = lPos - center;
            Real32          dirLength = dir.length();

            Vec3f           diff = (_shadowVP->getLightRoot(num)->getVolume
                                    ().getMax() - center);
            Real32          diffLength = diff.length();

            sceneDiagLength = dirLength + diffLength;
        }

        else
        {
            isDirLight = true;
            sceneDiagLength = 1.0;
        }


        Real32  lod;

        if(_shadowVP->getShadowSmoothness() <= 0.1999)
            lod = 0.5;
        else if(_shadowVP->getShadowSmoothness() <= 0.3999)
            lod = 1.5;
        else if(_shadowVP->getShadowSmoothness() <= 0.5999)
            lod = 2.5;
        else if(_shadowVP->getShadowSmoothness() <= 0.7999)
            lod = 3.5;
        else
            lod = 4.5;

        beginEditCP(_shadowSHL, ShaderChunk::ParametersFieldMask);
        _shadowSHL->setUniformParameter("shadowMap", 0);
        _shadowSHL->setUniformParameter("oldFactorMap", 1);
        _shadowSHL->setUniformParameter("firstRun", _firstRun);
        _shadowSHL->setUniformParameter("intensity", shadowIntensity);
        _shadowSHL->setUniformParameter("texFactor", texFactor);
        //_shadowSHL->setUniformParameter("shadowBias", 0.0075f);
        _shadowSHL->setUniformParameter("lightPM", shadowMatrix);
        _shadowSHL->setUniformParameter("lightPM2", shadowMatrix2);
        //_shadowSHL->setUniformParameter("shadowRange", Real32(shadowRange));
        _shadowSHL->setUniformParameter("xFactor", Real32(xFactor));
        _shadowSHL->setUniformParameter("yFactor", Real32(yFactor));
        _shadowSHL->setUniformParameter("sceneDiagLength",
                                        Real32(sceneDiagLength));
        _shadowSHL->setUniformParameter("Lod", Real32(lod));
        _shadowSHL->setUniformParameter("isDirLight", bool(isDirLight));
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

void VarianceShadowMap::createShadowFactorMapFBO(RenderActionBase *action,
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

        Matrix  shadowMatrix2 = LVM;
        shadowMatrix2.mult(iCVM);


        Real32  xFactor = 1.0;
        Real32  yFactor = 1.0;
        if(!_useNPOTTextures)
        {
            xFactor = Real32(_width) / Real32(_widthHeightPOT);
            yFactor = Real32(_height) / Real32(_widthHeightPOT);
        }

        Pnt3f   lPos;
        bool    isDirLight;
        Real32  sceneDiagLength;

        if(_shadowVP->_lights[num].second->getType() == PointLight::getClassType())
        {
            PointLightPtr   tmpPoint;
            tmpPoint = PointLightPtr::dcast(_shadowVP->_lights[num].second);

            lPos = tmpPoint->getPosition();

            if(tmpPoint->getBeacon() != NullFC)
            {
                Matrix  m = tmpPoint->getBeacon()->getToWorld();
                m.mult(lPos);
            }
            isDirLight = false;
            Pnt3f           center;
            _shadowVP->getLightRoot(num)->getVolume().getCenter(center);

            Vec3f           dir = lPos - center;
            Real32          dirLength = dir.length();

            Vec3f           diff = (_shadowVP->getLightRoot(num)->getVolume
                                    ().getMax() - center);
            Real32          diffLength = diff.length();

            sceneDiagLength = dirLength + diffLength;
        }

        else if(_shadowVP->_lights[num].second->getType() == SpotLight::getClassType
                ())
        {
            SpotLightPtr    tmpSpot;
            tmpSpot = SpotLightPtr::dcast(_shadowVP->_lights[num].second);
            lPos = tmpSpot->getPosition();
            if(tmpSpot->getBeacon() != NullFC)
            {
                Matrix  m = tmpSpot->getBeacon()->getToWorld();
                m.mult(lPos);
            }
            isDirLight = false;
            Pnt3f           center;
            _shadowVP->getLightRoot(num)->getVolume().getCenter(center);

            Vec3f           dir = lPos - center;
            Real32          dirLength = dir.length();

            Vec3f           diff = (_shadowVP->getLightRoot(num)->getVolume
                                    ().getMax() - center);
            Real32          diffLength = diff.length();

            sceneDiagLength = dirLength + diffLength;
        }

        else
        {
            isDirLight = true;
            sceneDiagLength = 1.0;
        }


        Real32  lod;

        if(_shadowVP->getShadowSmoothness() <= 0.1999)
            lod = 0.5;
        else if(_shadowVP->getShadowSmoothness() <= 0.3999)
            lod = 1.5;
        else if(_shadowVP->getShadowSmoothness() <= 0.5999)
            lod = 2.5;
        else if(_shadowVP->getShadowSmoothness() <= 0.7999)
            lod = 3.5;
        else
            lod = 4.5;

        beginEditCP(_shadowSHL, ShaderChunk::ParametersFieldMask);
        _shadowSHL->setUniformParameter("shadowMap", 0);
        _shadowSHL->setUniformParameter("oldFactorMap", 1);
        _shadowSHL->setUniformParameter("firstRun", _firstRun);
        _shadowSHL->setUniformParameter("intensity", shadowIntensity);
        _shadowSHL->setUniformParameter("texFactor", texFactor);
        //_shadowSHL->setUniformParameter("shadowBias", 0.0075f);
        _shadowSHL->setUniformParameter("lightPM", shadowMatrix);
        _shadowSHL->setUniformParameter("lightPM2", shadowMatrix2);
        //_shadowSHL->setUniformParameter("shadowRange", Real32(shadowRange));
        _shadowSHL->setUniformParameter("xFactor", Real32(xFactor));
        _shadowSHL->setUniformParameter("yFactor", Real32(yFactor));
        _shadowSHL->setUniformParameter("sceneDiagLength",
                                        Real32(sceneDiagLength));
        _shadowSHL->setUniformParameter("Lod", Real32(lod));
        _shadowSHL->setUniformParameter("isDirLight", bool(isDirLight));
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

void VarianceShadowMap::drawCombineMap(RenderActionBase *action)
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

void VarianceShadowMap::render(RenderActionBase *action)
{
    Window  *win = action->getWindow();
    initialize(win);

    if(!_useGLSL || !_useShadowExt || !_useFBO)
    {
        _shadowVP->Viewport::render(action);
    }
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
        //Used for ShadowFactorMap
        _firstRun = 1;

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
            if(_useNPOTTextures)
                createColorMapFBO(action);
            else
#endif
                createColorMap(action);

            //deactivate transparent Nodes
            for(UInt32 t = 0;t < _shadowVP->_transparent.size();++t)
                _shadowVP->_transparent[t]->setActive(false);

            createShadowMapsFBO(action);

            // switch on all transparent geos
            for(UInt32 t = 0;t < _shadowVP->_transparent.size();++t)
                _shadowVP->_transparent[t]->setActive(true);
            //filterShadowMaps(action);

            for(UInt32 i = 0;i < _shadowVP->_lights.size();i++)
            {
                if(_shadowVP->_lightStates[i] != 0)
                {
                    if(_shadowVP->getGlobalShadowIntensity() != 0.0 ||
                       _shadowVP->_lights[i].second->getShadowIntensity() != 0.0)
                    {
#ifdef USE_FBO_FOR_COLOR_AND_FACTOR_MAP
                        if(_useNPOTTextures)
                            createShadowFactorMapFBO(action, i);
                        else
#endif
                            createShadowFactorMap(action, i);
                    }
                }
            }
        }
        else
        {
            if(_shadowVP->_trigger_update)
            {
#ifdef USE_FBO_FOR_COLOR_AND_FACTOR_MAP
                if(_useNPOTTextures)
                    createColorMapFBO(action);
                else
#endif
                    createColorMap(action);

                //deactivate transparent Nodes
                for(UInt32 t = 0;t < _shadowVP->_transparent.size();++t)
                    _shadowVP->_transparent[t]->setActive(false);

                createShadowMapsFBO(action);

                // switch on all transparent geos
                for(UInt32 t = 0;t < _shadowVP->_transparent.size();++t)
                    _shadowVP->_transparent[t]->setActive(true);
                //filterShadowMaps(action);

                for(UInt32 i = 0;i < _shadowVP->_lights.size();i++)
                {
                    if(_shadowVP->_lightStates[i] != 0)
                    {
                        if(_shadowVP->getGlobalShadowIntensity() != 0.0 ||
                           _shadowVP->_lights[i].second->getShadowIntensity() != 0.0)
                        {
#ifdef USE_FBO_FOR_COLOR_AND_FACTOR_MAP
                            if(_useNPOTTextures)
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
