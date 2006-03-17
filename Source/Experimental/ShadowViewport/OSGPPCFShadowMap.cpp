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

#include "OSGPPCFShadowMap.h"
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
 
PPCFShadowMap::PPCFShadowMap(void)
{
}

PPCFShadowMap::PPCFShadowMap(ShadowViewport *source)
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
        _colorMapImage->set(GL_RGB, shadowVP->getParent()->getWidth(), shadowVP->getParent()->getHeight());
    endEditCP(_colorMapImage);

	//Sum ShadowFactorMap
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
        _shadowFactorMapImage->set(GL_RGB, shadowVP->getParent()->getWidth(), shadowVP->getParent()->getHeight());
    endEditCP(_shadowFactorMapImage);
        
	//SHL Chunk 1

	_shadowSHL = SHLChunk::create();
    beginEditCP(_shadowSHL);
        _shadowSHL->readVertexProgram("PPCF_Shadow.vert");
        _shadowSHL->readFragmentProgram("PPCF_Shadow.frag");
    endEditCP(_shadowSHL);

	//SHL Chunk 2
	_combineSHL = SHLChunk::create();

    beginEditCP(_combineSHL);
        _combineSHL->readVertexProgram("PPCF_Shadow_combine.vert");
        _combineSHL->readFragmentProgram("PPCF_Shadow_combine.frag");
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

PPCFShadowMap::~PPCFShadowMap(void)
{
	subRefCP(_tiledeco);
	subRefCP(_blender);

/*	printf("\nANFANG\n");
	printf("\nprinting refCounts:\n");
	printf("_colorMap %u\n",_colorMap.getRefCount());
	printf("_colorMapImage %u\n",_colorMapImage.getRefCount());
	printf("_shadowFactorMap %u\n",_shadowFactorMap.getRefCount());
	printf("_shadowFactorMapImage %u\n",_shadowFactorMapImage.getRefCount());
	printf("_shadowSHL %u\n",_shadowSHL.getRefCount());
	printf("_combineSHL %u\n",_combineSHL.getRefCount());
	printf("_shadowRoot %u\n",_combineRoot.getRefCount());
	printf("_shadowCmat %u\n",_shadowCmat.getRefCount());
	printf("_combineCmat %u\n",_shadowCmat.getRefCount());
	printf("_shadowShaderGroup %u\n",_shadowShaderGroup.getRefCount());
	printf("_combineShaderGroup %u\n",_combineShaderGroup.getRefCount());
	printf("_matrixCam %u\n",_matrixCam.getRefCount());*/


	subRefCP(_colorMap);
	subRefCP(_shadowFactorMap);
	subRefCP(_shadowFactorMap);
	subRefCP(_matrixCam);
	subRefCP(_shadowSHL);
	subRefCP(_combineSHL);
	subRefCP(_shadowShaderGroup);
	subRefCP(_combineShaderGroup);

	/*printf("\nMITTE\n");
	printf("\nprinting refCounts:\n");
	printf("_colorMap %u\n",_colorMap.getRefCount());
	printf("_colorMapImage %u\n",_colorMapImage.getRefCount());
	printf("_shadowFactorMap %u\n",_shadowFactorMap.getRefCount());
	printf("_shadowFactorMapImage %u\n",_shadowFactorMapImage.getRefCount());
	printf("_shadowSHL %u\n",_shadowSHL.getRefCount());
	printf("_combineSHL %u\n",_combineSHL.getRefCount());
	printf("_shadowRoot %u\n",_combineRoot.getRefCount());
	printf("_shadowCmat %u\n",_shadowCmat.getRefCount());
	printf("_combineCmat %u\n",_shadowCmat.getRefCount());
	printf("_shadowShaderGroup %u\n",_shadowShaderGroup.getRefCount());
	printf("_combineShaderGroup %u\n",_combineShaderGroup.getRefCount());
	printf("_matrixCam %u\n",_matrixCam.getRefCount());*/


	subRefCP(_shadowRoot);
	subRefCP(_combineRoot);


/*	printf("\nENDE\n");
	printf("\nprinting refCounts:\n");
	printf("_colorMap %u\n",_colorMap.getRefCount());
	printf("_colorMapImage %u\n",_colorMapImage.getRefCount());
	printf("_shadowFactorMap %u\n",_shadowFactorMap.getRefCount());
	printf("_shadowFactorMapImage %u\n",_shadowFactorMapImage.getRefCount());
	printf("_shadowSHL %u\n",_shadowSHL.getRefCount());
	printf("_combineSHL %u\n",_combineSHL.getRefCount());
	printf("_shadowRoot %u\n",_combineRoot.getRefCount());
	printf("_shadowCmat %u\n",_shadowCmat.getRefCount());
	printf("_combineCmat %u\n",_shadowCmat.getRefCount());
	printf("_shadowShaderGroup %u\n",_shadowShaderGroup.getRefCount());
	printf("_combineShaderGroup %u\n",_combineShaderGroup.getRefCount());
	printf("_matrixCam %u\n",_matrixCam.getRefCount());*/

	subRefCP(_shadowSHL);
	subRefCP(_combineSHL);

	subRefCP(boxGeo);
	subRefCP(boxNode);


/*	beginEditCP(_shadowCmat);
	beginEditCP(_combineCmat);
		_shadowCmat->getChunks().clear();
		_combineCmat->getChunks().clear();
	endEditCP(_shadowCmat);
	endEditCP(_combineCmat);*/

/*	printf("ganz ENDE\n");
	printf("_shadowSHL %u\n",_shadowSHL.getRefCount());
	printf("_combineSHL %u\n",_combineSHL.getRefCount());
	printf("_shadowCmat %u\n",_shadowCmat.getRefCount());
	printf("_combineCmat %u\n",_shadowCmat.getRefCount());

	printf("Destruktor PCF ENDE\n");*/
}

void PPCFShadowMap::drawTextureBoxShader(RenderActionBase* action, ChunkMaterialPtr cmat)
{
	addRefCP(cmat);

	//GeometryPtr boxGeo = makeBoxGeo(2,2,2, 1, 1, 1);

	beginEditCP(boxGeo, Geometry::MaterialFieldMask);
        boxGeo->setMaterial(cmat);
    endEditCP(boxGeo, Geometry::MaterialFieldMask);

	/*NodePtr boxNode = Node::create();

    beginEditCP(boxNode, Node::CoreFieldMask);
        boxNode->setCore(boxGeo);
    endEditCP(boxNode, Node::CoreFieldMask);*/

	action->setCamera(_matrixCam.getCPtr());

	//Render Texturebox
	action->apply(boxNode);

	//Restore old Parameters
	action->setCamera    (shadowVP->getCamera().getCPtr());

	//subRefCP(boxNode);
	subRefCP(cmat);
}


void PPCFShadowMap::createShadowMaps(RenderActionBase* action)
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


void PPCFShadowMap::createColorMap(RenderActionBase* action)
{
	shadowVP->getBackground()->clear(action, shadowVP);

	action->apply(shadowVP->getRoot());

	action->getWindow()->validateGLObject(_colorMap->getGLId());

	//glBindTexture(GL_TEXTURE_2D,_colorMap->getGLId());
    glBindTexture(GL_TEXTURE_2D, action->getWindow()->getGLObjectId(_colorMap->getGLId()));
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, shadowVP->getParent()->getWidth(), shadowVP->getParent()->getHeight());
	glBindTexture(GL_TEXTURE_2D,0);
}

void PPCFShadowMap::createShadowFactorMap(RenderActionBase* action, UInt32 num)
{
	glClearColor(1.0,1.0,1.0,1.0);
	if(firstRun) glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Finde alle aktiven Lichtquellen
	Real32 activeLights = 0;
	for (int i = 0; i<shadowVP->_lights.size();i++)
	{
		if (shadowVP->_lightStates[i] != 0) activeLights++;
	}
	Color4f shadowColor = shadowVP->getShadowColor(); 
	activeLights = (1.0-shadowColor[0])/activeLights;

	Matrix LVM,LPM,CVM;
	shadowVP->_lightCameras[num]->getViewing(LVM, shadowVP->getParent()->getWidth(), shadowVP->getParent()->getHeight());
	shadowVP->_lightCameras[num]->getProjection(LPM, shadowVP->getParent()->getWidth(), shadowVP->getParent()->getHeight());
	PerspectiveCameraPtr::dcast(shadowVP->getCamera())->getViewing(CVM, shadowVP->getParent()->getWidth(), shadowVP->getParent()->getHeight());
	Matrix iCVM = CVM;
	iCVM.invert();
	Matrix iLVM = LVM;
	iLVM.invert();

	Matrix shadowMatrix = LPM;
	shadowMatrix.mult(LVM);
	shadowMatrix.mult(iCVM);

	//ChunkMaterialPtr _shadowCmat = ChunkMaterial::create();

	beginEditCP(_shadowSHL, ShaderChunk::ParametersFieldMask);
		_shadowSHL->setUniformParameter("shadowMap", 0);
		_shadowSHL->setUniformParameter("oldFactorMap", 1);
		_shadowSHL->setUniformParameter("firstRun", firstRun);
		_shadowSHL->setUniformParameter("intensity", activeLights);
		_shadowSHL->setUniformParameter("shadowBias", 0.0075f);
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
	
	//glBindTexture(GL_TEXTURE_2D,_shadowFactorMap->getGLId());
    glBindTexture(GL_TEXTURE_2D, action->getWindow()->getGLObjectId(_shadowFactorMap->getGLId()));
	glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, shadowVP->getParent()->getWidth(), shadowVP->getParent()->getHeight());
	glBindTexture(GL_TEXTURE_2D,0);

	beginEditCP(_shadowRoot, Node::CoreFieldMask | Node::ChildrenFieldMask);
		_shadowRoot->subChild(shadowVP->getRoot());
	endEditCP(_shadowRoot, Node::ChildrenFieldMask | Node::ChildrenFieldMask);

	subRefCP(shadowVP->getRoot());

	glClearColor(0.0,0.0,0.0,1.0);
}

void PPCFShadowMap::drawCombineMap(RenderActionBase* action)
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

void PPCFShadowMap::render(RenderActionBase* action)
{

	GLfloat globalAmbient[] = {0.0,0.0,0.0,1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,globalAmbient);
	firstRun = 1;

    if(shadowVP->getMapAutoUpdate())
    {
		createColorMap(action);
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
}
