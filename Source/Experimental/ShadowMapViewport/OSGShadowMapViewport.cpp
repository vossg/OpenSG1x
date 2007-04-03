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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>
#include <OSGTypedFunctors.h>
#include <OSGQuaternion.h>
#include <OSGDrawAction.h>
#include <OSGMultiPassMaterial.h>

#include <OSGMatrix.h>
#include <OSGMatrixUtility.h>

#include <OSGBackground.h>
#include <OSGForeground.h>
#include <OSGImage.h>
#include <OSGMaterialGroup.h>
#include <OSGGeometry.h>

#include <OSGLight.h>

#include "OSGShadowMapViewport.h"

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

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ShadowMapViewport
Erste Version des Shadowviewports für Shadowmapping
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

UInt32 ShadowMapViewport::_depth_texture_extension;
UInt32 ShadowMapViewport::_shadow_extension;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ShadowMapViewport::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ShadowMapViewport::ShadowMapViewport(void) :
    Inherited(),
    _mapRenderSize(128),
    _mapSizeChanged(false),
    _windowW(0),
    _windowH(0),
    _texGen(NullFC),
    _poly(NullFC),
    _blender(NullFC),
    _dummy(NullFC),
    _silentBack(NullFC),
    _tiledeco(NullFC),
    _lights(),
    _oldLights(),
    _lightCameras(),
    _lightCamTrans(),
    _lightCamBeacons(),
    _lightStates(),
    _shadowImages(),
    _texChunks(),
    _unlitMat(NullFC),
    _trigger_update(false)
{
}

ShadowMapViewport::ShadowMapViewport(const ShadowMapViewport &source) :
    Inherited(source),
    _mapRenderSize(source._mapRenderSize),
    _mapSizeChanged(source._mapSizeChanged),
    _windowW(source._windowW),
    _windowH(source._windowH),
    _texGen(source._texGen),
    _poly(source._poly),
    _blender(source._blender),
    _dummy(source._dummy),
    _silentBack(source._silentBack),
    _tiledeco(source._tiledeco),
    _lights(source._lights),
    _oldLights(source._oldLights),
    _lightCameras(source._lightCameras),
    _lightCamTrans(source._lightCamTrans),
    _lightCamBeacons(source._lightCamBeacons),
    _lightStates(source._lightStates),
    _shadowImages(source._shadowImages),
    _texChunks(source._texChunks),
    _unlitMat(source._unlitMat),
    _trigger_update(source._trigger_update)
{
    _depth_texture_extension = Window::registerExtension("GL_ARB_depth_texture");
    _shadow_extension = Window::registerExtension("GL_ARB_shadow");
}

ShadowMapViewport::~ShadowMapViewport(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ShadowMapViewport::changed(BitVector whichField, UInt32 origin)
{
    if(whichField & OffBiasFieldMask ||
       whichField & OffFactorFieldMask)
    {
        FDEBUG(("ShadowMapViewport::changed : ofsset bias/factor changed.\n"));
        // Setting up Polygon-Chunk with Depth-Offset
        beginEditCP(_poly);
        {
            _poly->setOffsetBias(getOffBias());
            _poly->setOffsetFactor(getOffFactor());
            _poly->setOffsetFill(true);
        }
        endEditCP(_poly);
    }

    if(whichField & MapSizeFieldMask)
    {
        FDEBUG(("ShadowMapViewport::changed : map size changed.\n"));
        _mapSizeChanged = true;
    }

    if(whichField & LightNodesFieldMask)
    {
        FDEBUG(("ShadowMapViewport::changed : light nodes changed.\n"));
        _lights.clear();
        for(UInt32 i=0;i<getLightNodes().getSize();++i)
            _lights.push_back(LightPtr::dcast(getLightNodes()[i]->getCore()));
    }

    if(whichField & MapAutoUpdateFieldMask)
    {
        _trigger_update = true;
    }

    Inherited::changed(whichField, origin);
}


void ShadowMapViewport::dump(      UInt32    ,
                         const BitVector ) const
{
    FDEBUG(("Dump ShadowMapViewport NI\n"));
}

void ShadowMapViewport::triggerMapUpdate(void)
{
    ShadowMapViewportPtr tmpPtr(*this);
    beginEditCP(tmpPtr, MapAutoUpdateFieldMask);
    endEditCP(tmpPtr, MapAutoUpdateFieldMask);
}


void ShadowMapViewport::onCreate(const ShadowMapViewport *)
{
    // if we're in startup this is the prototype ...
    if(OSG::GlobalSystemState == OSG::Startup)
        return;

    _mapRenderSize = 128;

    _dummy = makeCoredNode<Group>();
    addRefCP(_dummy);

    _texGen = TexGenChunk::create();
    addRefCP(_texGen);
    beginEditCP(_texGen);//------Setting up TexGen--------------
    {
        _texGen->setSBeacon(_dummy);
        _texGen->setTBeacon(_dummy);
        _texGen->setRBeacon(_dummy);
        _texGen->setQBeacon(_dummy);
            
        _texGen->setGenFuncS(GL_EYE_LINEAR);
        _texGen->setGenFuncT(GL_EYE_LINEAR);
        _texGen->setGenFuncR(GL_EYE_LINEAR);
        _texGen->setGenFuncQ(GL_EYE_LINEAR);
    }
    endEditCP(_texGen);

    _poly = PolygonChunk::create();
    addRefCP(_poly);

    _offset = PolygonChunk::create();
    addRefCP(_offset);

    _blender = BlendChunk::create();
    addRefCP(_blender);

    _silentBack = PassiveBackground::create();
    addRefCP(_silentBack);
    
    _tiledeco = TileCameraDecorator::create();
    addRefCP(_tiledeco);

    beginEditCP(_blender);
    {
        _blender->setAlphaFunc(GL_GEQUAL);
        _blender->setAlphaValue(0.99);
    }
    endEditCP(_blender);

    _unlitMat = SimpleMaterial::create();
    addRefCP(_unlitMat);
    beginEditCP(_unlitMat);
        _unlitMat->setLit(false);
    endEditCP(_unlitMat);
}

void ShadowMapViewport::onDestroy(void)
{
    clearLights(_lights.size());
    subRefCP(_tiledeco);
    subRefCP(_silentBack);
    subRefCP(_blender);
    subRefCP(_poly);
    subRefCP(_texGen);
    subRefCP(_dummy);
    subRefCP(_unlitMat);
}

void ShadowMapViewport::activateSize(void)
{
    Inherited::activateSize();
}

void ShadowMapViewport::activate(void)
{
    Inherited::activate();
}

void ShadowMapViewport::deactivate(void)
{
    Inherited::deactivate();
}

void ShadowMapViewport::render(RenderActionBase* action)
{
    if(getCamera() == NullFC)
    {
        SWARNING << "ShadowMapViewport::render: no camera!" << std::endl;
        return;
    }
    if(getBackground() == NullFC)
    {
        SWARNING << "ShadowMapViewport::render: no Background!" << std::endl;
        return;
    }
    if(getRoot() == NullFC)
    {
        SWARNING << "ShadowMapViewport::render: no root!" << std::endl;
        return;
    }

    if(!getShadowOn())
    {
        StereoBufferViewport::render(action);
        return;
    }

    activate();

    GLfloat globalAmbient[] = {0.0,0.0,0.0,1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,globalAmbient);

    if(!extensionCheck())
    {
        SWARNING << "No Shadowmap-Extensions available!" << endLog;
    }
    else
    {
        if(getSceneRoot() == NullFC)
        {
            beginEditCP(getPtr(), SceneRootFieldMask);
                setSceneRoot(getRoot());
            endEditCP(getPtr(), SceneRootFieldMask);
        }

        action->setCamera    (getCamera().getCPtr());
        action->setBackground(_silentBack.getCPtr());
        action->setViewport  (this);
        action->setTravMask  (getTravMask());

        checkMapResolution();
        checkLights(action);

        // find transparent nodes
        _transparent.clear();
        traverse(getRoot(), osgTypedMethodFunctor1ObjPtrCPtrRef
             <Action::ResultE, ShadowMapViewport, NodePtr>
             (this, &ShadowMapViewport::findTransparent));

        if(getMapAutoUpdate())
        {
            createShadowMaps(action);
        }
        else
        {
            if(_trigger_update)
            {
                createShadowMaps(action);
                _trigger_update = false;
            }
        }
    }
    

    if(!_lights.empty() && !_lightCameras.empty())
    {
        projectShadowMaps(action);
    }
    else
    {
        FDEBUG(("Rendering without Shadows\n"));
        Viewport::render(action);
    }

    // render the foregrounds.
    for(UInt16 i=0; i < getForegrounds().size(); ++i)
        getForegrounds(i)->draw(action, this);

    deactivate();
}

//Checks if the needed OpenGL-Extensions are supported
bool ShadowMapViewport::extensionCheck()
{
    if(!this->getParent()->hasExtension(_depth_texture_extension))
    {
        SWARNING << "I need ARB_depth_texture-Extension!" << endLog;
    }
    else if(!this->getParent()->hasExtension(_shadow_extension))
    {
        SWARNING << "I need ARB_shadow-Extension!" << endLog;
    }
    else
    {
        FDEBUG((" Extensions-Check done!\n"));
        return true;
    }
    
    return false;
}

// Checks window-Size and determines best size of ShadowMap. Default is 128
void ShadowMapViewport::checkMapResolution()
{
    UInt32 minSize = 0;
    
    if(this->getParent() != NullFC)
    {
        //Checking for the smallest Window-Dimension
        minSize = this->getPixelWidth();

        if(this->getPixelHeight() < minSize)
            minSize = this->getPixelHeight();

        //Checking for biggest PowerOf2 that fits in smallest Window-Dimension
        _mapRenderSize = osgnextpower2(minSize + 1) / 2;
        if(_mapRenderSize == 0)
            _mapRenderSize = 128;
    }
    else
    {
        _mapRenderSize = 128;
        FDEBUG(("Could not find Window. Map will be set to 128\n"));
    }

    UInt32 mapSize = osgnextpower2(getMapSize() + 1) / 2;
    if(mapSize < _mapRenderSize)
        mapSize = _mapRenderSize;

    GLint max_tex_size = 0;
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_tex_size);
    
    if(mapSize > max_tex_size)
        mapSize = max_tex_size;
    
    beginEditCP(getPtr(), ShadowMapViewport::MapSizeFieldMask);
        setMapSize(mapSize);
    beginEditCP(getPtr(), ShadowMapViewport::MapSizeFieldMask);
}

Action::ResultE ShadowMapViewport::findLight(NodePtr& node)
{
    if(node->getCore()->getType().isDerivedFrom(Light::getClassType()))
        _allLights.push_back(LightPtr::dcast(node->getCore()));

    return Action::Continue;
}

Action::ResultE ShadowMapViewport::findTransparent(NodePtr& node)
{
    // ignore invisible nodes.
    if(!node->getActive())
        return Action::Continue;

    if(node->getCore() != NullFC)
    {
        if(node->getCore()->getType() == Geometry::getClassType() ||
           node->getCore()->getType() == MaterialGroup::getClassType())
        {
            MaterialPtr mat;
            MultiPassMaterialPtr multiMat;
            osg::GeometryPtr geo = osg::GeometryPtr::dcast(node->getCore());
            osg::MaterialGroupPtr matGroup = osg::MaterialGroupPtr::dcast(node->getCore());
            if(geo != NullFC)
                mat = geo->getMaterial();
            if(matGroup != NullFC)
                mat = matGroup->getMaterial();
            if(mat != NullFC)
            {
                /* isTransparent in MultiPassMaterial returns false,
                   if one Material is not transparent. Here we need
                   to know if one Material is transparent so we can't
                   use isTransparent for MultiPassMaterials. */
                multiMat = MultiPassMaterialPtr::dcast(mat);
                if(multiMat != NullFC)
                {
                    MFMaterialPtr::const_iterator it = multiMat->getMaterials().begin();
                    MFMaterialPtr::const_iterator matsEnd = multiMat->getMaterials().end();
                    for(; it != matsEnd; ++it)
                    {
                        if((*it) == NullFC)
                            continue;
                        if((*it)->isTransparent())
                        {
                            _transparent.push_back(node);
                            break;
                        }
                    }
                }
                else
                {
                    if(mat->isTransparent())
                        _transparent.push_back(node);
                }
            }

        }

        if(node->getCore()->getType() == Geometry::getClassType())
        {
            osg::GeometryPtr geo = osg::GeometryPtr::dcast(node->getCore());
            if(geo->getMaterial() != NullFC &&
               geo->getMaterial()->isTransparent())
                _transparent.push_back(node);
        }
        else if(node->getCore()->getType() == MaterialGroup::getClassType())
        {
            osg::MaterialGroupPtr matGroup = osg::MaterialGroupPtr::dcast(node->getCore());
            if(matGroup->getMaterial() != NullFC &&
               matGroup->getMaterial()->isTransparent())
                _transparent.push_back(node);
        }
    }
    return Action::Continue;
}


void ShadowMapViewport::checkLights(RenderActionBase* action)
{
    //Finding lights by going through whole Scenegraph
    _allLights.clear();
    traverse(getRoot(), osgTypedMethodFunctor1ObjPtrCPtrRef
             <Action::ResultE, ShadowMapViewport, NodePtr>
             (this, &ShadowMapViewport::findLight));

    //shadow for all lights
    if(getLightNodes().getSize() == 0)
        _lights = _allLights;

    _lightStates.clear();
    bool changed = false;
    if(_lights.size() > 0 && _lights.size() == _oldLights.size())
    {
        for(UInt32 i=0;i<_lights.size();++i)
        {
            _lightStates.push_back(_lights[i]->getOn()); 
            if(_lights[i] != _oldLights[i])
                changed = true;
        }
    }
    else
    {
        changed = true;
    }

    if(!changed)
    {
        if(_mapSizeChanged)
            changed = true;
    }

    if(!changed)
    {
        updateLights();
        return;
    }

    _mapSizeChanged = false;

    initializeLights(action);
}

void ShadowMapViewport::updateLights(void)
{
    SpotLightPtr tmpSpot;
    DirectionalLightPtr tmpDir;
    PointLightPtr tmpPoint;
    Matrix tmpMatrix;
    bool isSpot, isDirect;
    Real32 sceneWidth = 0.0;
    Real32 sceneHeight = 0.0;

    getSceneRoot()->updateVolume();

    for(UInt32 i = 0; i < _lights.size(); ++i)
    {
        //Giving new Camera Rotation and Position of the light it belongs to
        beginEditCP(_lightCamTrans[i]);
        {
            Quaternion q;

            tmpMatrix.setIdentity();

            //Is the Lightsource a Spotlight?
            if(_lights[i]->getType() == SpotLight::getClassType())
            {
                //Casting to Spotlight
                tmpSpot = SpotLightPtr::dcast(_lights[i]);
                FDEBUG(("Found Spotlight!\n"));
                isSpot = true;
                isDirect = false;

                Pnt3f lightpos = tmpSpot->getPosition();
                Vec3f lightdir = tmpSpot->getDirection();
                if(tmpSpot->getBeacon() != NullFC)
                {
                    Matrix m = tmpSpot->getBeacon()->getToWorld();
                    m.mult(lightpos);
                    m.mult(lightdir);
                }

                //<-- ???
                q.setValue(Vec3f(0,0,-1), lightdir);
                tmpMatrix.setTransform(Vec3f(lightpos),q);
            }
            else if(_lights[i]->getType() == DirectionalLight::getClassType())
            {
                Vec3f diff;
                Pnt3f center;

                tmpDir = DirectionalLightPtr::dcast(_lights[i]);
                FDEBUG(("Found Directionallight!\n"));
                isSpot = false;
                isDirect = true;

                diff = (getSceneRoot()->getVolume().getMax() -
                        getSceneRoot()->getVolume().getMin());

                sceneWidth = diff.length() * 0.5;
                // Not final values. May get tweaked in the future
                sceneHeight = diff.length() * 0.5;

                getSceneRoot()->getVolume().getCenter(center);

                Vec3f lightdir = tmpDir->getDirection();
                if(tmpDir->getBeacon() != NullFC)
                {
                    Matrix m = tmpDir->getBeacon()->getToWorld();
                    m.mult(lightdir);
                }
                
                MatrixLookAt(tmpMatrix,center + lightdir,
                             center,Vec3f(0,1,0));
                tmpMatrix.invert();
            }
            else // Preparation for PointLight -- In this version just a hack
            {
                Vec3f dir;
                Pnt3f center;

                tmpPoint = PointLightPtr::dcast(_lights[i]);
                FDEBUG(("Found PointLight!\n"));
                isSpot = false;
                isDirect = false;

                /* Direction of LightCam is a hack. 
                   It always looks at the center of the scene.
                   If the light is placed INSIDE of your Scene
                  (surrounded by Geometry, like a bulb in a Room)
                   the result of the Shadows may be not what you wanted.
                   So, please use the PointLight only outside of your 
                   Scene/outside the Bounding-Box of the lit geometry
                */

                Pnt3f lightpos = tmpPoint->getPosition();
                if(tmpPoint->getBeacon() != NullFC)
                {
                    Matrix m = tmpPoint->getBeacon()->getToWorld();
                    m.mult(lightpos);
                }

                getSceneRoot()->getVolume().getCenter(center);
                
                dir = lightpos - center;
                dir.normalize();
                dir.negate();

                q.setValue(Vec3f(0,0,-1),dir);

                tmpMatrix.setTransform(Vec3f(lightpos),q);

            }

            _lightCamTrans[i]->setMatrix(tmpMatrix);
        }
        endEditCP(_lightCamTrans[i]);

        //Feeding new Camera with paramters of original camera
        beginEditCP(_lightCameras[i]);
        {
            _lightCameras[i]->setNear(getCamera()->getNear());
            _lightCameras[i]->setFar(getCamera()->getFar());

            
            // Is the Lightsource a Spotlight?
            if(isSpot)
            {
                //Using Spot-angle of Spotlight as FOV for LightCamera
                PerspectiveCameraPtr::dcast(_lightCameras[i])->
                                            setFov(tmpSpot->getSpotCutOffDeg()*2);
            }
            // Is the Lightsource a Directional-Light? Setting up MatrixCamera
            else if(isDirect)
            {
                Matrix proMatrix,modMatrix;

                proMatrix.setIdentity();
                modMatrix.setIdentity();

                MatrixOrthogonal(proMatrix,-sceneWidth,sceneWidth,-sceneHeight,
                                 sceneHeight,-sceneWidth,sceneWidth);
        
                // Grabbing ModelView-Matrix from Light-Transformation
                modMatrix = _lightCamTrans[i]->getMatrix();

                MatrixCameraPtr::dcast(_lightCameras[i])->setProjectionMatrix(proMatrix);
                MatrixCameraPtr::dcast(_lightCameras[i])->setModelviewMatrix(modMatrix);
                
            }
            else // If none of above the Lightsource must be a PointLight
            {
                Vec3f dist,diff;
                Pnt3f center;
                Real32 angle;

                getSceneRoot()->getVolume().getCenter(center);
                Pnt3f lightpos = tmpPoint->getPosition();
                if(tmpPoint->getBeacon() != NullFC)
                {
                    Matrix m = tmpPoint->getBeacon()->getToWorld();
                    m.mult(lightpos);
                }
                
                dist =  (lightpos - center);
                diff = (getSceneRoot()->getVolume().getMax() -
                        getSceneRoot()->getVolume().getMin());

                angle = atan((diff.length()* 0.5)/dist.length());
                
                PerspectiveCameraPtr::dcast(_lightCameras[i])->setFov((2*angle));
            }
            
             _lightCameras[i]->setBeacon(_lightCamBeacons[i]);
        }
        endEditCP(_lightCameras[i]);
    }
}

void ShadowMapViewport::initializeLights(RenderActionBase *action)
{
    clearLights(_oldLights.size());

    FDEBUG(("Initialising lights.\n"));

    _oldLights = _lights;

    //Setting up Light-Cameras, ShadowMaps and TextureChunks
    for(UInt32 i = 0; i < _lights.size(); ++i)
    {
        // Remembering initial state of Lights
        _lightStates.push_back(_lights[i]->getOn());
        //Fill Transformation-List, so it can be used later on
        _lightCamTrans.push_back(NullFC);
        //Creation of Lightcam-Beacon
        _lightCamBeacons.push_back(makeCoredNode<Transform>(&_lightCamTrans[i]));
        
        //Giving new Camera Rotation and Position of the light it belongs to
        beginEditCP(_lightCamTrans[i]);
        {
            //Is the Lightsource a Spotlight?
            if(_lights[i]->getType() == SpotLight::getClassType())
            {
                //Creation of new Perspective-LightCam
                _lightCameras.push_back(PerspectiveCamera::create());
            }
            else if(_lights[i]->getType() == DirectionalLight::getClassType())
            {
                _lightCameras.push_back(MatrixCamera::create());
            }
            else // Preparation for PointLight -- In this version just a hack
            {
                _lightCameras.push_back(PerspectiveCamera::create());    
            }
        }
        endEditCP(_lightCamTrans[i]);

        addRefCP(_lightCameras[i]);

        if(getRoot() == NullFC)
        {
               SFATAL << "RootNode not found!" << endLog;
        }
        else
        {
           getRoot()->addChild(_lightCamBeacons[i]);
        }

        //----------Shadowtexture-Images and Texture-Chunks-----------

        _shadowImages.push_back(Image::create());

        // creates a image without allocating main memory.
        beginEditCP(_shadowImages[i]);
            _shadowImages[i]->set(Image::OSG_L_PF,getMapSize(), getMapSize(),
                                  1, 1, 1, 0, NULL,
                                  Image::OSG_UINT8_IMAGEDATA, false);
        endEditCP(_shadowImages[i]);

        _texChunks.push_back(TextureChunk::create());
        addRefCP(_texChunks[i]);

        // Preparation of Texture be a Depth-Texture
        beginEditCP(_texChunks[i]);
        {
            _texChunks[i]->setImage(_shadowImages[i]);
            _texChunks[i]->setInternalFormat(GL_DEPTH_COMPONENT_ARB);
            _texChunks[i]->setExternalFormat(GL_DEPTH_COMPONENT_ARB);
            _texChunks[i]->setMinFilter(GL_LINEAR);
            _texChunks[i]->setMagFilter(GL_LINEAR);
            _texChunks[i]->setWrapS(GL_CLAMP_TO_BORDER_ARB);
            _texChunks[i]->setWrapT(GL_CLAMP_TO_BORDER_ARB);
            _texChunks[i]->setEnvMode(GL_MODULATE);
            _texChunks[i]->setTarget(GL_TEXTURE_2D);
        }
        endEditCP(_texChunks[i]);

        // Just a Hack until TextureChunk is ready
        // to take the following arguments
        _texChunks[i]->activate(action, getShadowMapTextureIndex());
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_MODE_ARB,
                        GL_COMPARE_R_TO_TEXTURE_ARB);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_FUNC_ARB,GL_LEQUAL);
        glTexParameteri(GL_TEXTURE_2D,GL_DEPTH_TEXTURE_MODE_ARB,GL_INTENSITY);
        _texChunks[i]->deactivate(action, getShadowMapTextureIndex());
    }

    updateLights();
}

void ShadowMapViewport::clearLights(UInt32 size)
{
    if(size > 0)
    {
        FDEBUG(("Clearing Lightcamera-Garbage!\n"));

        for(UInt32 i=0; i < size; ++i)
        {
            getRoot()->subChild(_lightCamBeacons[i]);
            subRefCP(_lightCameras[i]);
            subRefCP(_texChunks[i]);
        }

        _lightCameras.clear();
        _lightCamTrans.clear();
        _lightCamBeacons.clear();
        _lightStates.clear();
        _texChunks.clear();
        _shadowImages.clear();
    }
}

void ShadowMapViewport::createShadowMaps(RenderActionBase* action)
{
    Real32 vpTop,vpBottom,vpLeft,vpRight;
    
    //------Setting up Window to fit size of ShadowMap----------------

    WindowPtr win = this->getParent();
    
    // Saving original Window-Dimensions
    _windowW = win->getWidth();
    _windowH = win->getHeight();

    // Saving original Viewport-Dimensions
    vpTop = this->getTop();
    vpBottom = this->getBottom();
    vpLeft = this->getLeft();
    vpRight = this->getRight();

    //Temporarily switching Viewports size to size of ShadowMap | OpenSG-Level

    beginEditCP(getPtr(), LeftFieldMask | RightFieldMask |
                          BottomFieldMask | TopFieldMask);
    {
        this->setSize(0,0,_mapRenderSize-1,_mapRenderSize-1);
    }
    endEditCP(getPtr(), LeftFieldMask | RightFieldMask |
                        BottomFieldMask | TopFieldMask);

    this->activateSize();

    // ok we render only one unlit material for the whole scene in this pass.
    action->setMaterial(_unlitMat.getCPtr(), getRoot());

    glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
    glShadeModel(GL_FLAT);
    //glDisable(GL_LIGHTING);
    glDepthMask(GL_TRUE);

    // disable all lights more speed
    for(UInt32 i = 0; i < _lights.size(); ++i)
    {
        if(_lightStates[i] != 0)
            _lights[i]->setOn(false);
    }
    
    // deactivate exclude nodes:
    for(UInt32 i = 0; i < getExcludeNodes().getSize(); ++i)
    {
        NodePtr exnode = getExcludeNodes()[i];
        if(exnode != NullFC)
            exnode->setActive(false);
    }
    
    for(UInt32 i = 0; i< _lights.size(); ++i)
    {
        if(_lightStates[i] != 0)
        {
            action->setCamera    (_tiledeco.getCPtr());

            // we use a tiledecorator to create shadow maps with
            // a higher resolutions than the viewport or the screen.
            _tiledeco->setDecoratee(_lightCameras[i]);
            _tiledeco->setFullSize(getMapSize(), getMapSize());

            Real32 step = (1.0 / Real32(getMapSize())) * Real32(_mapRenderSize);

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
                    _poly->activate(action,0);

                    action->apply(getSceneRoot());
                    // check is this necessary.
                    action->getWindow()->validateGLObject(_texChunks[i]->getGLId());

                    _poly->deactivate(action,0);
        
                    //----------Shadow-Texture-Parameters and Indices-------------
                
                    glBindTexture(GL_TEXTURE_2D,
                                  win->getGLObjectId(_texChunks[i]->getGLId()));
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

    // activate exclude nodes:
    for(UInt32 i = 0; i < getExcludeNodes().getSize(); ++i)
    {
        NodePtr exnode = getExcludeNodes()[i];
        if(exnode != NullFC)
            exnode->setActive(true);
    }

    // enable all lights.
    for(UInt32 i = 0; i< _lights.size(); ++i)
    {
        if(_lightStates[i] != 0)
            _lights[i]->setOn(true);
    }

    //-------Restoring old states of Window and Viewport----------
    
    beginEditCP(getPtr(), LeftFieldMask | RightFieldMask |
                          BottomFieldMask | TopFieldMask);
    {
        this->setSize(vpLeft,vpBottom,vpRight,vpTop);
    }
    endEditCP(getPtr(), LeftFieldMask | RightFieldMask |
                        BottomFieldMask | TopFieldMask);

    this->activateSize();

    action->setCamera(getCamera().getCPtr());
    
    glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
    glShadeModel(GL_SMOOTH);
    //glEnable(GL_LIGHTING);

    // reset the material.
    action->setMaterial(NULL, NullFC);
}
//------------------------------------------------- 


void ShadowMapViewport::projectShadowMaps(RenderActionBase* action)
{
    Matrix viewMatrix, projectionMatrix, biasMatrix;
    Vec4f s,t,r,q;

    biasMatrix.setIdentity();
    biasMatrix.setScale(0.5);
    biasMatrix.setTranslate(0.5,0.5,0.5);

    // draw background
    getBackground()->clear(action, this);

    //---Draw/Render-Pass with ambient light only & no shadows------

    std::vector<int>     light_state;
    std::vector<Color4f> light_specular;
    std::vector<Color4f> light_diffuse;
    std::vector<Color4f> light_ambient;
    Color4f shadow_color = getShadowColor() * (1.0 / Real32(_lights.size()));

    for(UInt32 j=0;j<_lights.size();++j) // Switching off specular highlights
    {
        light_specular.push_back(_lights[j]->getSpecular());
        light_diffuse.push_back(_lights[j]->getDiffuse());
        light_ambient.push_back(_lights[j]->getAmbient());

        _lights[j]->setSpecular(0.0,0.0,0.0,1.0);
        _lights[j]->setDiffuse(shadow_color);
    }

    // render
    action->apply(getRoot());

    // get all lights
    for(UInt32 j=0;j<_lights.size();++j) // Switching on specular highlights
    {
        _lights[j]->setSpecular(light_specular[j]);
        _lights[j]->setDiffuse(light_diffuse[j]);
        _lights[j]->setAmbient(0.0,0.0,0.0,1.0);
    }    
    for(UInt32 j=0;j<_allLights.size();++j) {
        light_state.push_back(_allLights[j]->getOn());
        _allLights[j]->setOn(false);
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
    for(UInt32 t=0;t<_transparent.size();++t)
        _transparent[t]->setActive(false);

    beginEditCP(_offset);
    _offset->setOffsetBias(-1);
    _offset->setOffsetFactor(0);
    _offset->setOffsetFill(true);
    endEditCP(_offset);

    glDepthFunc(GL_LESS);

    //---Render-Pass with Shadow-----------------------------    
    for(UInt32 i=0;i<_lights.size();++i)
    {
        if(_lightStates[i] != 0)
        {
            _lightCameras[i]->getProjection(projectionMatrix,_mapRenderSize,_mapRenderSize);

            _lightCameras[i]->getViewing(viewMatrix,getPixelWidth()/*_mapRenderSize*/,
                                         getPixelHeight()/*_mapRenderSize*/);

            Matrix textureMatrix = biasMatrix;
            textureMatrix.mult(projectionMatrix);
            textureMatrix.mult(viewMatrix);
            
            textureMatrix.transpose();
            Vec4f ps = textureMatrix[0];
            Vec4f pt = textureMatrix[1];
            Vec4f pr = textureMatrix[2];
            Vec4f pq = textureMatrix[3];

            beginEditCP(_texGen);
                _texGen->setGenFuncSPlane(ps);
                _texGen->setGenFuncTPlane(pt);
                _texGen->setGenFuncRPlane(pr);
                _texGen->setGenFuncQPlane(pq);
            endEditCP(_texGen);
            
            _lights[i]->setOn(true);
        
            _texChunks[i]->activate(action, getShadowMapTextureIndex());

            _texGen->activate(action, getShadowMapTextureIndex());

            _blender->activate(action,0);

            _offset->activate(action,0);
            action->apply(getRoot());
            _offset->deactivate(action,0);

            _blender->deactivate(action,0);

            _texGen->deactivate(action, getShadowMapTextureIndex());

            _texChunks[i]->deactivate(action, getShadowMapTextureIndex());
        
            _lights[i]->setOn(false);

            // increase offset for next light
            beginEditCP(_offset);
            _offset->setOffsetBias(_offset->getOffsetBias() - 1);
            endEditCP(_offset);
        }
    }

    glDepthFunc(GL_LEQUAL);

    // switch on all transparent geos
    for(UInt32 t=0;t<_transparent.size();++t)
        _transparent[t]->setActive(true);

    for(UInt32 i=0;i<_lights.size();++i) // Switching on ambient 
    {
        _lights[i]->setAmbient(light_ambient[i]);
    }

    for(UInt32 j=0;j<_allLights.size();++j) 
    {
        _allLights[j]->setOn(light_state[j]);
    }

}
//------------------------------------------------


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGShadowMapViewport.cpp,v 1.17 2007/04/03 03:16:54 dirk Exp $";
    static Char8 cvsid_hpp       [] = OSGSHADOWMAPVIEWPORTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSHADOWMAPVIEWPORTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSHADOWMAPVIEWPORTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif
