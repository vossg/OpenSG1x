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

#include "OSGPCFShadowMap.h"
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

static std::string _pcf_shadow_vp =
"//uniform float shadowBias;\n"
"uniform mat4 lightPM;\n"
"uniform float texFactor;\n"
"varying vec4 projCoord;\n"
"varying vec4 texPos;\n"
"\n"
"const mat4 bias = {vec4(0.5,0.0,0.0,0.0), vec4(0.0,0.5,0.0,0.0), vec4(0.0,0.0,0.5,0.0), vec4(0.5,0.5,0.5,1.0)};\n"
"\n"
"void main(void)\n"
"{\n"
"  vec4 realPos = gl_ModelViewMatrix * gl_Vertex;\n"
"  projCoord = lightPM * realPos;\n"
"  projCoord.x *= texFactor;\n"
"  texPos = gl_ModelViewProjectionMatrix * gl_Vertex;\n"
"\n"
"  //projCoord.z -= shadowBias;\n"
"  projCoord = bias * projCoord;\n"
"  texPos = bias * texPos;\n"
"  gl_Position = ftransform();\n"
"}\n";

static std::string _pcf_shadow_fp =
"uniform sampler2D shadowMap;\n"
"uniform sampler2D oldFactorMap;\n"
"uniform float intensity;\n"
"uniform int firstRun;\n"
"uniform float shadowRange;\n"
"varying vec4 projCoord;\n"
"varying vec4 texPos;\n"
"\n"
"float PCF_Filter(vec4 projectiveBiased, float filterWidth, float samples)\n"
"{\n"
"    float stepSize = 2.0 * filterWidth / samples;\n"
"\n"
"    projectiveBiased.x -= filterWidth;\n"
"    projectiveBiased.y -= filterWidth;\n"
"\n"
"    float blockerCount = 0.0;\n"
"\n"
"    for (float i=0.0; i<samples; i+=1.0)\n"
"    {\n"
"            for (float j=0.0; j<samples; j+=1.0)\n"
"        {\n"
"            projectiveBiased.x += (j*stepSize);\n"
"            projectiveBiased.y += (i*stepSize);\n"
"\n"
"            blockerCount += shadow2D(shadowMap, projectiveBiased.xyz).x;\n"
"\n"
"            projectiveBiased.x -= (j*stepSize);\n"
"            projectiveBiased.y -= (i*stepSize);\n"
"        }\n"
"    }\n"
"\n"
"    float result = ((blockerCount)/(samples*samples)) * intensity;\n"
"    return result;\n"
"}\n"
"\n"
"void main(void)\n"
"{\n"
"    vec4 projectiveBiased = vec4((projCoord.xyz / projCoord.q),1.0);\n"
"\n"
"    float shadowed;\n"
"\n"
"    shadowed = PCF_Filter(projectiveBiased, shadowRange, 4.0);\n"
"\n"
"    if(firstRun == 0)\n"
"        shadowed += texture2DProj(oldFactorMap,texPos.xyw).x;\n"
"\n"
"    gl_FragColor = vec4(shadowed,0.0,0.0,1.0);\n"
"}\n";

static std::string _pcf_shadow_combine_vp =
"varying vec4 projCoord;\n"
"\n"
"void main(void)\n"
"{\n"
"  projCoord = gl_Vertex;\n"
"  gl_Position = ftransform();\n"
"}\n";

static std::string _pcf_shadow_combine_fp =
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


PCFShadowMap::PCFShadowMap(void)
{
}

PCFShadowMap::PCFShadowMap(ShadowViewport *source)
: TreeRenderer(source)
{
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
        //_shadowSHL->readVertexProgram("PCF_Shadow.vert");
		//_shadowSHL->readFragmentProgram("PCF_Shadow.frag");
		_shadowSHL->setVertexProgram(_pcf_shadow_vp);
		_shadowSHL->setFragmentProgram(_pcf_shadow_fp);
    endEditCP(_shadowSHL);

    //SHL Chunk 2
    _combineSHL = SHLChunk::create();

    beginEditCP(_combineSHL);
        //_combineSHL->readVertexProgram("PCF_Shadow_combine.vert");
        //_combineSHL->readFragmentProgram("PCF_Shadow_combine.frag");
		_combineSHL->setVertexProgram(_pcf_shadow_combine_vp);
		_combineSHL->setFragmentProgram(_pcf_shadow_combine_fp);
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

PCFShadowMap::~PCFShadowMap(void)
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
}

void PCFShadowMap::drawTextureBoxShader(RenderActionBase* action, ChunkMaterialPtr cmat)
{
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


void PCFShadowMap::createShadowMaps(RenderActionBase* action)
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
                    y2 = osgMin((float)(y1+winHeight-1), (float)(imgHeight-1));
                    th = y2 - y1 + 1;
                    
                    for (x1=0; x1 < imgWidth; x1 += winWidth)
                    {
                        x2 = osgMin((float)(x1+winWidth-1), (float)(imgWidth-1));
                        tw = x2 - x1 + 1;
                        
                        // set tile size to maximal renderable size
                        beginEditCP(_tiledeco);
                            _tiledeco->setSize(  x1/(float)imgWidth,     y1/(float)imgHeight,    (x2+1)/(float)imgWidth, (y2+1)/(float)imgHeight);
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


void PCFShadowMap::createColorMap(RenderActionBase* action)
{
    shadowVP->getBackground()->clear(action, shadowVP);

    action->apply(shadowVP->getRoot());

    action->getWindow()->validateGLObject(_colorMap->getGLId());

    glBindTexture(GL_TEXTURE_2D, action->getWindow()->getGLObjectId(_colorMap->getGLId()));
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, shadowVP->getPixelWidth(), shadowVP->getPixelHeight());
    glBindTexture(GL_TEXTURE_2D,0);
}

void PCFShadowMap::createShadowFactorMap(RenderActionBase* action, UInt32 num)
{
    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Finde alle aktiven Lichtquellen
    Real32 activeLights = 0;
    for (int i = 0; i<shadowVP->_lights.size();i++)
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
		texFactor = float(width)/float(height);
	else texFactor = 1.0;

    Matrix shadowMatrix = LPM;
    shadowMatrix.mult(LVM);
    shadowMatrix.mult(iCVM);

    beginEditCP(_shadowSHL, ShaderChunk::ParametersFieldMask);
        _shadowSHL->setUniformParameter("shadowMap", 0);
        _shadowSHL->setUniformParameter("oldFactorMap", 1);
        _shadowSHL->setUniformParameter("firstRun", firstRun);
        _shadowSHL->setUniformParameter("intensity", activeLights);
		_shadowSHL->setUniformParameter("texFactor", texFactor);
        //_shadowSHL->setUniformParameter("shadowBias", 0.0075f);
        _shadowSHL->setUniformParameter("lightPM", shadowMatrix);
        _shadowSHL->setUniformParameter("shadowRange", Real32(1.0/Real32(shadowVP->getMapSize())*2.0));
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

void PCFShadowMap::drawCombineMap(RenderActionBase* action)
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

void PCFShadowMap::render(RenderActionBase* action)
{

    GLfloat globalAmbient[] = {0.0,0.0,0.0,1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,globalAmbient);
    firstRun = 1;

    //if(shadowVP->getParent()->getWidth() != width)
    if(shadowVP->getPixelWidth() != width ||
       shadowVP->getPixelHeight() != height)
    {
        //width = shadowVP->getParent()->getWidth();
        //height = shadowVP->getParent()->getHeight();
        width = shadowVP->getPixelWidth();
        height = shadowVP->getPixelHeight();
    
        beginEditCP(_colorMap);
        beginEditCP(_colorMapImage);
            //_colorMapImage->setHeight(height);
            //_colorMapImage->setWidth(width);
            _colorMapImage->set(GL_RGB, width, height);
        endEditCP(_colorMapImage);
        endEditCP(_colorMap);

        beginEditCP(_shadowFactorMap);
        beginEditCP(_shadowFactorMapImage);
            //_shadowFactorMapImage->setHeight(height);
            //_shadowFactorMapImage->setWidth(width);
            _shadowFactorMapImage->set(GL_RGB, width, height);
        endEditCP(_shadowFactorMapImage);
        endEditCP(_shadowFactorMap);
    }

    if(shadowVP->getMapAutoUpdate())
    {
        createColorMap(action);

		//deactivate transparent Nodes
		for(UInt32 t=0;t<shadowVP->_transparent.size();++t)
			shadowVP->_transparent[t]->setActive(false);
        
		createShadowMaps(action);
        
        for(int i = 0; i<shadowVP->_lights.size();i++)
        {
            if(shadowVP->_lightStates[i] != 0)
            {
                createShadowFactorMap(action, i);
                firstRun = 0;
            }
        }
    }
    else
    {
        if(shadowVP->_trigger_update)
        {
            createColorMap(action);

			//deactivate transparent Nodes
			for(UInt32 t=0;t<shadowVP->_transparent.size();++t)
				shadowVP->_transparent[t]->setActive(false);

            createShadowMaps(action);

            for(int i = 0; i<shadowVP->_lights.size();i++)
            {
                if(shadowVP->_lightStates[i] != 0)
                {
                    createShadowFactorMap(action, i);
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

}
