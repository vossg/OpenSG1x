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
#include "OSGShadowViewport.h"
#include "OSGStdShadowMap.h"
#include "OSGPerspectiveShadowMap.h"
#include "OSGDitherShadowMap.h"
#include "OSGPCFShadowMap.h"
#include "OSGPCSSShadowMap.h"
#include "OSGVarianceShadowMap.h"
#include "OSGRenderAction.h"

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

/***************************************************************************\
*                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
*                           Class methods                                 *
\***************************************************************************/

void ShadowViewport::initMethod(void)
{
}


/***************************************************************************\
*                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
   -  private                                                                 -
   \*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ShadowViewport::ShadowViewport(void) :
    Inherited(),
    _GLSLsupported(false),
    _initDone(false),
    _restart(false),
    _treeRenderer(NULL),
    _mapRenderSize(128),
    _mapSizeChanged(false),
    _texGen(NullFC),
    _poly(NullFC),
    _offset(NullFC),
    _dummy(NullFC),
    _silentBack(NullFC),
    _windowW(0),
    _windowH(0),
    _transparent(),
    _lights(),
    _oldLights(),
    _lightCameras(),
    _lightCamTrans(),
    _lightCamBeacons(),
    _lightStates(),
    _shadowImages(),
    _texChunks(),
    _excludeNodeActive(),
    _realPointLight(),
    _renderSide(),
    _trigger_update(false),
    _transforms(),
    _light_render_transform(NullFC)
{
    _transforms[0] = Matrix(1, 0, 0, 0,
                            0, -1, 0, 0,
                            0, 0, -1, 0,
                            0, 0, 0, 1);

    _transforms[1] = Matrix(1, 0, 0, 0,
                            0, 1, 0, 0,
                            0, 0, 1, 0,
                            0, 0, 0, 1);

    _transforms[2] = Matrix(1, 0, 0, 0,
                            0, 0, 1, 0,
                            0, -1, 0, 0,
                            0, 0, 0, 1);

    _transforms[3] = Matrix(1, 0, 0, 0,
                            0, 0, -1, 0,
                            0, 1, 0, 0,
                            0, 0, 0, 1);

    _transforms[4] = Matrix(0, 0, 1, 0,
                            0, 1, 0, 0,
                            -1, 0, 0, 0,
                            0, 0, 0, 1);

    _transforms[5] = Matrix(0, 0, -1, 0,
                            0, 1, 0, 0,
                            1, 0, 0, 0,
                            0, 0, 0, 1);
}

ShadowViewport::ShadowViewport(const ShadowViewport &source) :
    Inherited(source),
    _GLSLsupported(source._GLSLsupported),
    _initDone(source._initDone),
    _restart(source._restart),
    _treeRenderer(source._treeRenderer),
    _mapRenderSize(source._mapRenderSize),
    _mapSizeChanged(source._mapSizeChanged),
    _texGen(source._texGen),
    _poly(source._poly),
    _offset(source._offset),
    _dummy(source._dummy),
    _silentBack(source._silentBack),
    _windowW(source._windowW),
    _windowH(source._windowH),
    _transparent(source._transparent),
    _lights(source._lights),
    _oldLights(source._oldLights),
    _lightCameras(source._lightCameras),
    _lightCamTrans(source._lightCamTrans),
    _lightCamBeacons(source._lightCamBeacons),
    _lightStates(source._lightStates),
    _shadowImages(source._shadowImages),
    _texChunks(source._texChunks),
    _excludeNodeActive(source._excludeNodeActive),
    _realPointLight(source._realPointLight),
    _renderSide(source._renderSide),
    _trigger_update(source._trigger_update),
    _transforms(),
    _light_render_transform(source._light_render_transform)
{
    _treeRenderer = NULL;
    _initDone = false;
    _restart = false;

    _transforms[0] = Matrix(1, 0, 0, 0,
                            0, -1, 0, 0,
                            0, 0, -1, 0,
                            0, 0, 0, 1);

    _transforms[1] = Matrix(1, 0, 0, 0,
                            0, 1, 0, 0,
                            0, 0, 1, 0,
                            0, 0, 0, 1);

    _transforms[2] = Matrix(1, 0, 0, 0,
                            0, 0, 1, 0,
                            0, -1, 0, 0,
                            0, 0, 0, 1);

    _transforms[3] = Matrix(1, 0, 0, 0,
                            0, 0, -1, 0,
                            0, 1, 0, 0,
                            0, 0, 0, 1);

    _transforms[4] = Matrix(0, 0, 1, 0,
                            0, 1, 0, 0,
                            -1, 0, 0, 0,
                            0, 0, 0, 1);

    _transforms[5] = Matrix(0, 0, -1, 0,
                            0, 1, 0, 0,
                            1, 0, 0, 0,
                            0, 0, 0, 1);

}

ShadowViewport::~ShadowViewport(void)
{
    if(_light_render_transform != NullFC)
        subRefCP(_light_render_transform);
}

/*----------------------------- class specific ----------------------------*/

void ShadowViewport::changed(BitVector whichField, UInt32 origin)
{
    if(whichField & OffBiasFieldMask ||
       whichField & OffFactorFieldMask)
    {
        FDEBUG(("ShadowViewport::changed : ofsset bias/factor changed.\n"));
        // Setting up Polygon-Chunk with Depth-Offset
        beginEditCP(_poly);
        {
            _poly->setOffsetBias(getOffBias());
            _poly->setOffsetFactor(getOffFactor());
            _poly->setOffsetFill(true);
        }
        endEditCP(_poly);
    }

    if(whichField & LightNodesFieldMask)
    {
        FDEBUG(("ShadowViewport::changed : light nodes changed.\n"));
        _lights.clear();
        for(UInt32 i = 0;i < getLightNodes().getSize();++i)
            _lights.push_back(std::make_pair(getLightNodes()[i], LightPtr::dcast(getLightNodes()[i]->getCore())));
    }

    if(whichField & MapAutoUpdateFieldMask)
    {
        _trigger_update = true;
    }

    if(whichField & AutoSearchForLightsFieldMask)
    {
        if(getAutoSearchForLights())
        {
            FNOTICE(("auto light search mode on\n"));
        }
        else
        {
            FNOTICE(("auto light search mode off\n"));
        }
    }

    if(whichField & ShadowSmoothnessFieldMask)
    {
        if(getShadowSmoothness() < 0.0)
        {
            FNOTICE(("No ShadowSmoothness < 0 allowed!\n"));
            setShadowSmoothness(0.0);
        }
        if(getShadowSmoothness() > 1.0)
        {
            FNOTICE(("No ShadowSmoothness > 1.0 allowed!\n"));
            setShadowSmoothness(1.0);
        }
        FNOTICE(("ShadowSmoothness set to %f\n", getShadowSmoothness()));
    }

    if(whichField & ShadowModeFieldMask || whichField & MapSizeFieldMask)
    {
        _restart = true;
    }

    Inherited::changed(whichField, origin);
}

void ShadowViewport::dump(UInt32,
                          const BitVector) const
{
    SLOG << "Dump ShadowViewport NI" << std::endl;
}

void ShadowViewport::setVPSize(Real32 a, Real32 b, Real32 c, Real32 d)
{
    beginEditCP(getPtr(), LeftFieldMask | RightFieldMask |
                BottomFieldMask | TopFieldMask);
    {
        this->setSize(a, b, c, d);
    }
    endEditCP(getPtr(), LeftFieldMask | RightFieldMask |
              BottomFieldMask | TopFieldMask);

    this->activateSize();
}

void ShadowViewport::triggerMapUpdate(void)
{
    ShadowViewportPtr   tmpPtr(*this);
    beginEditCP(tmpPtr, MapAutoUpdateFieldMask);
    endEditCP(tmpPtr, MapAutoUpdateFieldMask);
}


void ShadowViewport::onCreate(const ShadowViewport *OSG_CHECK_ARG(source))
{
    // if we're in startup this is the prototype ...
    if(OSG::GlobalSystemState == OSG::Startup)
        return;

    _treeRenderer = NULL;

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

    _silentBack = PassiveBackground::create();
    addRefCP(_silentBack);
}

void ShadowViewport::onDestroy(void)
{
    clearLights(_lights.size());
    subRefCP(_silentBack);
    subRefCP(_poly);
    subRefCP(_texGen);
    subRefCP(_dummy);
}

void ShadowViewport::activateSize(void)
{
    Inherited::activateSize();
}

void ShadowViewport::activate(void)
{
    glColorMask(getRed(), getGreen(), getBlue(), getAlpha());
    Inherited::activate();
}

void ShadowViewport::deactivate(void)
{
    Inherited::deactivate();
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
}

void ShadowViewport::render(RenderActionBase *action)
{
    if(_restart)
    {
        if(_treeRenderer != NULL)
            delete _treeRenderer;
        _treeRenderer = NULL;

        clearLights(_oldLights.size());
        _mapSizeChanged = true;

        switch(getShadowMode())
        {
            case NO_SHADOW:
                {
                    FNOTICE(("No Shadows\n"));
                }
                break;

            case STD_SHADOW_MAP:
                {
                    FNOTICE(("using standard Shadow Mapping...\n"));
                    _treeRenderer = new StdShadowMap(this);
                }
                break;

            case PERSPECTIVE_SHADOW_MAP:
                {
                    FNOTICE(("using Lisp Perspective Shadow Mapping...\n"));
                    _treeRenderer = new PerspectiveShadowMap(this);
                }
                break;

            case DITHER_SHADOW_MAP:
                {
                    FNOTICE(("using Dither Shadow Mapping...\n"));
                    _treeRenderer = new DitherShadowMap(this);
                }
                break;

            case PCF_SHADOW_MAP:
                {
                    FNOTICE(("using PCF Shadow Mapping...\n"));
                    _treeRenderer = new PCFShadowMap(this);
                }
                break;

            case PCSS_SHADOW_MAP:
                {
                    FNOTICE(("using PCSS Shadow Mapping...\n"));
                    _treeRenderer = new PCSSShadowMap(this);
                }
                break;

            case VARIANCE_SHADOW_MAP:
                {
                    FNOTICE(("using Variance Shadow Mapping...\n"));
                    _treeRenderer = new VarianceShadowMap(this);
                }
                break;

            default:
                break;
        }
        _restart = false;
    }

    if(_treeRenderer == NULL)
    {
        StereoBufferViewport::render(action);
        return;
    }

    if(getCamera() == NullFC)
    {
        SWARNING << "ShadowViewport::render: no camera!" << std::endl;
        return;
    }
    if(getBackground() == NullFC)
    {
        SWARNING << "ShadowViewport::render: no Background!" << std::endl;
        return;
    }
    if(getRoot() == NullFC)
    {
        SWARNING << "ShadowViewport::render: no root!" << std::endl;
        return;
    }

    if(!getShadowOn())
    {
        StereoBufferViewport::render(action);
        return;
    }

    if(!_initDone)
    {
        _GLSLsupported = true;
        if(!action->getWindow()->hasExtension("GL_ARB_shading_language_100") ||
           !action->getWindow()->hasExtension("GL_ARB_fragment_shader") ||
           !action->getWindow()->hasExtension("GL_ARB_vertex_shader") ||
           !action->getWindow()->hasExtension("GL_ARB_shader_objects") )
            _GLSLsupported = false;
        _initDone = true;
    }

    if(getSceneRoot() == NullFC)
    {
        //beginEditCP(getPtr(), SceneRootFieldMask);
        setSceneRoot(getRoot());
        //endEditCP(getPtr(), SceneRootFieldMask);
    }

    _excludeNodeActive.clear();
    _realPointLight.clear();
    //get excludeNode states
    for(UInt32 i = 0;i < getExcludeNodes().getSize();i++)
    {
        NodePtr exnode = getExcludeNodes()[i];
        if(exnode != NullFC)
            _excludeNodeActive.push_back(exnode->getActive());
        else
            _excludeNodeActive.push_back(false);
    }


    action->setCamera(getCamera().getCPtr());
    action->setBackground(_silentBack.getCPtr());
    action->setViewport(this);
    action->setTravMask(getTravMask());

    checkLights(action);

    bool    allLightsZero = true;
    if(getGlobalShadowIntensity() != 0.0)
    {
        allLightsZero = false;
    }
    else
    {
        for(UInt32 i = 0;i < _lights.size();i++)
        {
            if(_lights[i].second->getShadowIntensity() != 0.0 && _lightStates[i] != 0)
                allLightsZero = false;
        }
    }

    if(_lights.size() == 0 || allLightsZero)
    {
        StereoBufferViewport::render(action);
    }
    else
    {

        //find transparent nodes
        _transparent.clear();

        if (getAutoExcludeTransparentNodes())
        {
            traverse( getRoot(), osgTypedMethodFunctor1ObjPtrCPtrRef
                      <Action::ResultE, ShadowViewport, NodePtr>
                      (this, &ShadowViewport::findTransparent) );
        }
        _windowW = getParent()->getWidth();
        _windowH = getParent()->getHeight();

        //check if excludeNodes are disabled
        for(UInt32 i = 0;i < getExcludeNodes().getSize();++i)
        {
            NodePtr exnode = getExcludeNodes()[i];
            _excludeNodeActive[i] = exnode->getActive();
        }

        //check if all sides of a pointlight are needed
        //TODO: Not implemented yet ...
        _renderSide.clear();

        // active stereo support.
        activate();
        
        _treeRenderer->render(action);

        deactivate();
    }
}

Action::ResultE ShadowViewport::findLight(NodePtr &node)
{
    if(node->getCore()->getType().isDerivedFrom(Light::getClassType()))
        _lights.push_back(std::make_pair(node, LightPtr::dcast(node->getCore())));
    return Action::Continue;
}

Action::ResultE ShadowViewport::findTransparent(NodePtr &node)
{
    if(node->getCore() != NullFC)
    {
        if(node->getCore()->getType() == Geometry::getClassType() ||
           node->getCore()->getType() == MaterialGroup::getClassType())
        {
            MaterialPtr             mat;
            MultiPassMaterialPtr    multiMat;
            osg::GeometryPtr        geo = osg::GeometryPtr::dcast(
                node->getCore());
            osg::MaterialGroupPtr   matGroup = osg::MaterialGroupPtr::dcast(
                node->getCore());
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
                    MFMaterialPtr::const_iterator   it = multiMat->getMaterials
                        ().begin();
                    MFMaterialPtr::const_iterator   matsEnd =
                        multiMat->getMaterials().end();
                    for(;it != matsEnd;++it)
                    {
                        if((*it) == NullFC)
                            continue;
                        if((*it)->isTransparent() && node->getActive())
                        {
                            _transparent.push_back(node);
                            break;
                        }
                    }
                }
                else
                {
                    if(mat->isTransparent() && node->getActive())
                        _transparent.push_back(node);
                }
            }

        }

        if(node->getCore()->getType() == Geometry::getClassType())
        {
            osg::GeometryPtr    geo = osg::GeometryPtr::dcast(node->getCore());
            if(geo->getMaterial() != NullFC &&
               geo->getMaterial()->isTransparent() &&
               node->getActive())
                _transparent.push_back(node);
        }
        else if(node->getCore()->getType() == MaterialGroup::getClassType())
        {
            osg::MaterialGroupPtr   matGroup = osg::MaterialGroupPtr::dcast(
                node->getCore());
            if(matGroup->getMaterial() != NullFC &&
               matGroup->getMaterial()->isTransparent() &&
               node->getActive())
                _transparent.push_back(node);
        }
    }
    return Action::Continue;
}



void ShadowViewport::checkLights(RenderActionBase *action)
{
    if(getAutoSearchForLights())
    {
        //Finding lights by going through whole Scenegraph
        _lights.clear();
        traverse(getRoot(), osgTypedMethodFunctor1ObjPtrCPtrRef
                 <Action::ResultE, ShadowViewport, NodePtr>
                 (this, &ShadowViewport::findLight));
    }

    _lightStates.clear();
    bool    changed = false;
    if(_lights.size() > 0 && _lights.size() == _oldLights.size())
    {
        for(UInt32 i = 0;i < _lights.size();++i)
        {
            bool light_state = _lights[i].second->getOn();
            if(_lights[i].second->getShadowMode() == Light::CAST_SHADOW_ON)
                light_state = true;
            else if(_lights[i].second->getShadowMode() == Light::CAST_SHADOW_OFF)
                light_state = false;

            _lightStates.push_back(light_state ? 1 : 0);
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

void ShadowViewport::updateLights(void)
{
    SpotLightPtr        tmpSpot;
    DirectionalLightPtr tmpDir;
    PointLightPtr       tmpPoint;
    Matrix              tmpMatrix;
    bool                isSpot, isDirect;
    Real32              sceneWidth = 0.0;
    Real32              sceneHeight = 0.0;
    Real32              PLangle = 0.0;

    for(UInt32 i = 0;i < _lights.size();++i)
    {
        getLightRoot(i)->updateVolume();
        //Giving new Camera Rotation and Position of the light it belongs to
        beginEditCP(_lightCamTrans[i]);
        {
            Quaternion  q;

            tmpMatrix.setIdentity();

            //Is the Lightsource a Spotlight?
            if(_lights[i].second->getType() == SpotLight::getClassType())
            {
                //Casting to Spotlight
                tmpSpot = SpotLightPtr::dcast(_lights[i].second);
                FDEBUG(("Found Spotlight!\n"));
                isSpot = true;
                isDirect = false;

                Pnt3f   lightpos = tmpSpot->getPosition();
                Vec3f   lightdir = tmpSpot->getDirection();
                if(tmpSpot->getBeacon() != NullFC)
                {
                    Matrix  m = tmpSpot->getBeacon()->getToWorld();
                    m.mult(lightpos);
                    m.mult(lightdir);
                }

                //<-- ???
                q.setValue(Vec3f(0, 0, -1), lightdir);
                tmpMatrix.setTransform(Vec3f(lightpos), q);
                _realPointLight.push_back(false);
            }
            else if(_lights[i].second->getType() == DirectionalLight::getClassType())
            {
                Vec3f   diff;
                Pnt3f   center;

                tmpDir = DirectionalLightPtr::dcast(_lights[i].second);
                FDEBUG(("Found Directionallight!\n"));
                isSpot = false;
                isDirect = true;

                diff = (getLightRoot(i)->getVolume().getMax() -
                        getLightRoot(i)->getVolume().getMin());

                sceneWidth = diff.length() * 0.5;
                // Not final values. May get tweaked in the future
                sceneHeight = diff.length() * 0.5;

                getLightRoot(i)->getVolume().getCenter(center);

                Vec3f   lightdir = tmpDir->getDirection();
                if(tmpDir->getBeacon() != NullFC)
                {
                    Matrix  m = tmpDir->getBeacon()->getToWorld();
                    m.mult(lightdir);
                }

                MatrixLookAt(tmpMatrix, center + lightdir,
                             center, Vec3f(0, 1, 0));
                tmpMatrix.invert();
                _realPointLight.push_back(false);
            }
            else
                // Preparation for PointLight -- In this version just a hack
            {
                Vec3f   dir;
                Pnt3f   center;

                tmpPoint = PointLightPtr::dcast(_lights[i].second);
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

                Pnt3f   lightpos = tmpPoint->getPosition();
                if(tmpPoint->getBeacon() != NullFC)
                {
                    Matrix  m = tmpPoint->getBeacon()->getToWorld();
                    m.mult(lightpos);
                }

                if((getShadowMode() == STD_SHADOW_MAP ||
                    getShadowMode() == PERSPECTIVE_SHADOW_MAP ||
                    getShadowMode() == DITHER_SHADOW_MAP ||
                    getShadowMode() == PCF_SHADOW_MAP) && _GLSLsupported)
                {
                    //Lightpos inside Scene BB?
                    Pnt3f   sceneMin = getLightRoot(i)->getVolume().getMin();
                    Pnt3f   sceneMax = getLightRoot(i)->getVolume().getMax();

                    if((lightpos[0] < sceneMin[0] ||
                        lightpos[1] < sceneMin[1] ||
                        lightpos[2] < sceneMin[2]) ||
                       (lightpos[0] > sceneMax[0] ||
                        lightpos[1] > sceneMax[1] ||
                        lightpos[2] > sceneMax[2]))
                    {
                        //check if angle is ok to use one Side
                        Vec3f   dist, diff;
                        Pnt3f   center;

                        getLightRoot(i)->getVolume().getCenter(center);

                        //Scene Bounding Box Points

                        Pnt3f   bb[8];
                        bb[0] = Pnt3f(sceneMin[0], sceneMin[1], sceneMin[2]);
                        bb[1] = Pnt3f(sceneMax[0], sceneMin[1], sceneMin[2]);
                        bb[2] = Pnt3f(sceneMax[0], sceneMax[1], sceneMin[2]);
                        bb[3] = Pnt3f(sceneMin[0], sceneMax[1], sceneMin[2]);
                        bb[4] = Pnt3f(sceneMin[0], sceneMin[1], sceneMax[2]);
                        bb[5] = Pnt3f(sceneMax[0], sceneMin[1], sceneMax[2]);
                        bb[6] = Pnt3f(sceneMax[0], sceneMax[1], sceneMax[2]);
                        bb[7] = Pnt3f(sceneMin[0], sceneMax[1], sceneMax[2]);	

                        PLangle = deg2rad(0);
                        Pnt3f   maxAnglePnt1, maxAnglePnt2;

                        for(UInt32 j = 0;j < 8;j++)
                        {
                            Vec3f   vector1(lightpos - center);
                            Vec3f   vector2(lightpos - bb[j]);
                            Real32  newAngle = vector1.enclosedAngle(vector2);
                            if(osgabs(rad2deg(newAngle)) > 180)
                                newAngle = vector2.enclosedAngle(vector1);
                            if(rad2deg(newAngle) > rad2deg(PLangle))
                            {
                                PLangle = newAngle;
                                maxAnglePnt1 = bb[j];
                            }
                        }

                        for(UInt32 j = 0;j < 8;j++)
                        {
                            Vec3f   vector1(lightpos - maxAnglePnt1);
                            Vec3f   vector2(lightpos - bb[j]);
                            Real32  newAngle = vector1.enclosedAngle(vector2);
                            if(osgabs(rad2deg(newAngle)) > 180)
                                newAngle = vector2.enclosedAngle(vector1);
                            if(rad2deg(newAngle) > rad2deg(PLangle))
                            {
                                PLangle = newAngle;
                                maxAnglePnt2 = bb[j];
                            }
                        }
	
                        if(rad2deg(PLangle) < 120) //Use one Side only
                        {
                            getLightRoot(i)->getVolume().getCenter(center);
                            dir = lightpos - center;
                            dir.normalize();
                            dir.negate();
                            q.setValue(Vec3f(0, 0, -1), dir);
                            tmpMatrix.setTransform(Vec3f(lightpos), q);
                            _realPointLight.push_back(false);
                        }
                        else
                            //use 6 side Pointlight
                        {
                            dir = Vec3f(0.0, 0.0, -1.0);//lightpos - center;
                            dir.negate();
                            q.setValue(Vec3f(0, 0, -1), dir);
                            tmpMatrix.setTransform(Vec3f(lightpos), q);
                            _realPointLight.push_back(true);
                        }
                    }
                    else
                    {
                        dir = Vec3f(0.0, 0.0, -1.0);//lightpos - center;
                        dir.negate();
                        q.setValue(Vec3f(0, 0, -1), dir);
                        tmpMatrix.setTransform(Vec3f(lightpos), q);
                        _realPointLight.push_back(true);
                    }
                }
                else
                {

                    Vec3f   dist, diff;
                    Pnt3f   center;
                    Pnt3f   sceneMin = getLightRoot(i)->getVolume().getMin();
                    Pnt3f   sceneMax = getLightRoot(i)->getVolume().getMax();

                    getLightRoot(i)->getVolume().getCenter(center);

                    Pnt3f   bb[8];
                    bb[0] = Pnt3f(sceneMin[0], sceneMin[1], sceneMin[2]);
                    bb[1] = Pnt3f(sceneMax[0], sceneMin[1], sceneMin[2]);
                    bb[2] = Pnt3f(sceneMax[0], sceneMax[1], sceneMin[2]);
                    bb[3] = Pnt3f(sceneMin[0], sceneMax[1], sceneMin[2]);
                    bb[4] = Pnt3f(sceneMin[0], sceneMin[1], sceneMax[2]);
                    bb[5] = Pnt3f(sceneMax[0], sceneMin[1], sceneMax[2]);
                    bb[6] = Pnt3f(sceneMax[0], sceneMax[1], sceneMax[2]);
                    bb[7] = Pnt3f(sceneMin[0], sceneMax[1], sceneMax[2]);

                    PLangle = deg2rad(0);
                    Pnt3f   maxAnglePnt1, maxAnglePnt2;

                    for(UInt32 j = 0;j < 8;j++)
                    {
                        Vec3f   vector1(lightpos - center);
                        Vec3f   vector2(lightpos - bb[j]);
                        Real32  newAngle = vector1.enclosedAngle(vector2);
                        if(osgabs(rad2deg(newAngle)) > 180)
                            newAngle = vector2.enclosedAngle(vector1);
                        if(rad2deg(newAngle) > rad2deg(PLangle))
                        {
                            PLangle = newAngle;
                            maxAnglePnt1 = bb[j];
                        }
                    }

                    for(UInt32 j = 0;j < 8;j++)
                    {
                        Vec3f   vector1(lightpos - maxAnglePnt1);
                        Vec3f   vector2(lightpos - bb[j]);
                        Real32  newAngle = vector1.enclosedAngle(vector2);
                        if(osgabs(rad2deg(newAngle)) > 180)
                            newAngle = vector2.enclosedAngle(vector1);
                        if(rad2deg(newAngle) > rad2deg(PLangle))
                        {
                            PLangle = newAngle;
                            maxAnglePnt2 = bb[j];
                        }
                    }

                    if(rad2deg(PLangle) > 175) //Use one Side only
                    {
                        PLangle = deg2rad(175);
                    }

                    dir = lightpos - center;
                    dir.normalize();
                    dir.negate();

                    q.setValue(Vec3f(0, 0, -1), dir);

                    tmpMatrix.setTransform(Vec3f(lightpos), q);
                    _realPointLight.push_back(false);
                }
            }

            _lightCamTrans[i]->setMatrix(tmpMatrix);
        }
        endEditCP(_lightCamTrans[i]);

        //Feeding new Camera with paramters of original camera
        beginEditCP(_lightCameras[i]);
        {
            // Is the Lightsource a Spotlight?
            if(isSpot)
            {
                tmpSpot = SpotLightPtr::dcast(_lights[i].second);

                Pnt3f   lightpos = tmpSpot->getPosition();
                if(tmpSpot->getBeacon() != NullFC)
                {
                    Matrix  m = tmpSpot->getBeacon()->getToWorld();
                    m.mult(lightpos);
                }

                Pnt3f   center;
                getLightRoot(i)->getVolume().getCenter(center);
                
                Vec3f   dir = lightpos - center;
                Real64  dirLength = dir.length();

                Vec3f   diff = (getLightRoot(i)->getVolume().getMax() -
                                getLightRoot(i)->getVolume().getMin());
                Real64  diffLength = diff.length() / 2;
                
                Real64  zNearLimit, zCalcNear = 0;
                Real64  zFar = 1.2 * (dirLength + diffLength);
                Real64  zNear = getCamera()->getNear();

                if (diffLength) 
                {
                    // Camera outside of the scene
                    if (dirLength > diffLength)      
                        // Camera outside of the scene
                        zCalcNear = 0.8 * (dirLength - diffLength);
                    // else camera inside of the scene
                    
                    zNear = zCalcNear;
                    zNearLimit = osgMax( 0.01, zFar / 20000 );
                    zNear = osgMax( zNear, zNearLimit );
                }
                
                _lightCameras[i]->setNear( zNear );
                _lightCameras[i]->setFar( zFar );
                
                //Using Spot-angle of Spotlight as FOV for LightCamera
                PerspectiveCameraPtr::dcast(_lightCameras[i])->
                    setFov(tmpSpot->getSpotCutOffDeg() * 2);
            }
                // Is the Lightsource a Directional-Light? Setting up MatrixCamera
            else if(isDirect)
            {
                Matrix  proMatrix, modMatrix;

                proMatrix.setIdentity();
                modMatrix.setIdentity();

                MatrixOrthogonal(proMatrix, -sceneWidth,
                                 sceneWidth, -sceneHeight,
                                 sceneHeight, -sceneWidth, sceneWidth);

                // Grabbing ModelView-Matrix from Light-Transformation
                modMatrix = _lightCamTrans[i]->getMatrix();

                MatrixCameraPtr::dcast(_lightCameras[i])->setProjectionMatrix(
                    proMatrix);
                MatrixCameraPtr::dcast(_lightCameras[i])->setModelviewMatrix(
                    modMatrix);
            }
            else
                // If none of above the Lightsource must be a PointLight
            {
                if((getShadowMode() == STD_SHADOW_MAP ||
                    getShadowMode() == PERSPECTIVE_SHADOW_MAP ||
                    getShadowMode() == DITHER_SHADOW_MAP ||
                    getShadowMode() == PCF_SHADOW_MAP) && _realPointLight[i] &&
                   _GLSLsupported)
                {
                    Vec3f   dist, diff;
                    Pnt3f   center;
                    Real32  angle;

                    getLightRoot(i)->getVolume().getCenter(center);

                    Pnt3f   lightpos = tmpPoint->getPosition();

                    if(tmpPoint->getBeacon() != NullFC)
                    {
                        Matrix  m = tmpPoint->getBeacon()->getToWorld();
                        m.mult(lightpos);
                    }

                    dist = (lightpos - center);
                    diff = (getLightRoot(i)->getVolume().getMax() -
                            getLightRoot(i)->getVolume().getMin());

                    Real32  distLength = dist.length();
                    Real32  diffLength = diff.length();

                    _lightCameras[i]->setNear(0.01f);
                    _lightCameras[i]->setFar(distLength + diffLength);
                    PerspectiveCameraPtr::dcast(_lightCameras[i])->setFov(
                        deg2rad(91));
                }
                else
                {
                    Vec3f   dist, diff;
                    Pnt3f   center;
                    getLightRoot(i)->getVolume().getCenter(center);

                    Pnt3f   lightpos = tmpPoint->getPosition();

                    if(tmpPoint->getBeacon() != NullFC)
                    {
                        Matrix  m = tmpPoint->getBeacon()->getToWorld();
                        m.mult(lightpos);
                    }

                    dist = (lightpos - center);
                    diff = (getLightRoot(i)->getVolume().getMax() -
                            getLightRoot(i)->getVolume().getMin());

                    Pnt3f   sceneMin = getLightRoot(i)->getVolume().getMin();
                    Pnt3f   sceneMax = getLightRoot(i)->getVolume().getMax();

                    Real64  distLength = dist.length();
                    Real64  diffLength = diff.length() / 2;
                    
                    Real64  zNearLimit, zCalcNear = 0;
                    Real64  zFar = 1.2 * (distLength + diffLength);
                    Real64  zNear = getCamera()->getNear();
    
                    if (diffLength) 
                    {
                        // Camera outside of the scene
                        if (distLength > diffLength)      
                            // Camera outside of the scene
                            zCalcNear = 0.8 * (distLength - diffLength);
                        // else camera inside of the scene
                        
                        zNear = zCalcNear;
                        zNearLimit = osgMax( 0.01, zFar / 20000 );
                        zNear = osgMax( zNear, zNearLimit );
                    }
                    
                    _lightCameras[i]->setNear( zNear );
                    _lightCameras[i]->setFar( zFar );

                    PerspectiveCameraPtr::dcast(_lightCameras[i])->setFov(
                        PLangle);
                }
            }

            _lightCameras[i]->setBeacon(_lightCamBeacons[i]);
        }
        endEditCP(_lightCameras[i]);
    }
}

void ShadowViewport::initializeLights(RenderActionBase *action)
{
    clearLights(_oldLights.size());

    FDEBUG(("Initialising lights.\n"));

    _oldLights = _lights;

    //Setting up Light-Cameras, ShadowMaps and TextureChunks
    for(UInt32 i = 0;i < _lights.size();++i)
    {
        bool light_state = _lights[i].second->getOn();
        if(_lights[i].second->getShadowMode() == Light::CAST_SHADOW_ON)
            light_state = true;
        else if(_lights[i].second->getShadowMode() == Light::CAST_SHADOW_OFF)
            light_state = false;

        // Remembering initial state of Lights
        _lightStates.push_back(light_state ? 1 : 0);
        //Fill Transformation-List, so it can be used later on
        _lightCamTrans.push_back(NullFC);
        //Creation of Lightcam-Beacon
        _lightCamBeacons.push_back(makeCoredNode<Transform>
                                   (&_lightCamTrans[i]));

        //Giving new Camera Rotation and Position of the light it belongs to
        beginEditCP(_lightCamTrans[i]);
        {
            //Is the Lightsource a Spotlight?
            if(_lights[i].second->getType() == SpotLight::getClassType())
            {
                //Creation of new Perspective-LightCam
                _lightCameras.push_back(PerspectiveCamera::create());
            }
            else if(_lights[i].second->getType() == DirectionalLight::getClassType())
            {
                _lightCameras.push_back(MatrixCamera::create());
            }
            else
                // Preparation for PointLight -- In this version just a hack
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

        if(_lights[i].second->getType() != PointLight::getClassType())
        {
            _shadowImages.push_back(Image::create());

            // creates a image without allocating main memory.
            beginEditCP(_shadowImages[i]);
            _shadowImages[i]->set(Image::OSG_L_PF, getMapSize(), getMapSize(),
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
                _texChunks[i]->setWrapS(GL_CLAMP_TO_EDGE);
                _texChunks[i]->setWrapT(GL_CLAMP_TO_EDGE);
                _texChunks[i]->setEnvMode(GL_MODULATE);
                _texChunks[i]->setTarget(GL_TEXTURE_2D);
            }
            endEditCP(_texChunks[i]);
        }
        else
            //Light is a point light
        {
            //TODO: Texturgrösse anpassen, je nach Bedarf
            GLint   max_texture_size;
            glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_texture_size);

            _shadowImages.push_back(Image::create());

            // creates a image without allocating main memory.
            if((getShadowMode() == STD_SHADOW_MAP ||
                getShadowMode() == PERSPECTIVE_SHADOW_MAP ||
                getShadowMode() == DITHER_SHADOW_MAP ||
                getShadowMode() == PCF_SHADOW_MAP) && _GLSLsupported)
            {
                beginEditCP(_shadowImages[i]);
                _shadowImages[i]->set(Image::OSG_L_PF, getMapSize(),
                                      getMapSize(),
                                      1, 1, 1, 0, NULL,
                                      Image::OSG_UINT8_IMAGEDATA, false);
                endEditCP(_shadowImages[i]);
            }
            else
            {
                beginEditCP(_shadowImages[i]);
                _shadowImages[i]->set(Image::OSG_L_PF, getMapSize(),
                                      getMapSize(),
                                      1, 1, 1, 0, NULL,
                                      Image::OSG_UINT8_IMAGEDATA, false);
                endEditCP(_shadowImages[i]);
            }

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
        }

    }

    updateLights();
}

void ShadowViewport::clearLights(UInt32 size)
{
    if(size > 0)
    {
        FDEBUG(("Clearing Lightcamera-Garbage!\n"));

        for(UInt32 i = 0;i < size;++i)
        {
            if(i < _lightCamBeacons.size())
                getRoot()->subChild(_lightCamBeacons[i]);
            if(i < _lightCameras.size())
                subRefCP(_lightCameras[i]);
            if(i < _texChunks.size())
            {
                subRefCP(_texChunks[i]);
            }
        }

        _lightCameras.clear();
        _lightCamTrans.clear();
        _lightCamBeacons.clear();
        _lightStates.clear();
        _texChunks.clear();
        _shadowImages.clear();
    }
}

void ShadowViewport::renderLight(RenderActionBase *action, Material *mat, UInt32 index)
{
    if(_light_render_transform == NullFC)
    {
        _light_render_transform = Node::create();
        addRefCP(_light_render_transform);
        beginEditCP(_light_render_transform, Node::CoreFieldMask);
            _light_render_transform->setCore(Transform::create());
        endEditCP(_light_render_transform, Node::CoreFieldMask);
    }

    NodePtr light = _lights[index].first;
    NodePtr parent = light->getParent();

    if(parent != NullFC)
    {
        TransformPtr trans = TransformPtr::dcast(_light_render_transform->getCore());
        beginEditCP(trans);
            trans->setMatrix(parent->getToWorld());
        endEditCP(trans);

        addRefCP(light);
        beginEditCP(_light_render_transform, Node::ChildrenFieldMask);
            _light_render_transform->addChild(light);
        endEditCP(_light_render_transform, Node::ChildrenFieldMask);

        // ok we render only one unlit material for the whole scene in this pass.
        action->setMaterial(mat, _light_render_transform);

        // disable color mask we only need the depth values!
        action->apply(_light_render_transform);

        beginEditCP(parent, Node::ChildrenFieldMask);
            parent->addChild(light);
        endEditCP(parent, Node::ChildrenFieldMask);
        subRefCP(light);
    }
    else
    {
        // ok we render only one unlit material for the whole scene in this pass.
        action->setMaterial(mat, light);
        action->apply(light);
    }

    // reset material.
    action->setMaterial(NULL, NullFC);
}

NodePtr ShadowViewport::getLightRoot(UInt32 index)
{
    // return getSceneRoot();
    return _lights[index].first;
}

void ShadowViewport::checkLightsOcclusion(RenderActionBase *action)
{
    RenderAction *ract = dynamic_cast<RenderAction *>(action);

    if(ract == NULL)
        return;

    for(UInt32 i = 0;i < _lights.size();i++)
    {
        NodePtr node = _lights[i].first;

        // now make a occlusion test for all light sources.
        bool occluded = false;

        if(ract->_glGenQueriesARB != NULL) // occlusion queries supported?
        {
            Matrix view;
            if(ract->getCamera() != NULL)
            {
                ract->getCamera()->getViewing(view,
                                    ract->getViewport()->getPixelWidth (),
                                    ract->getViewport()->getPixelHeight());
            }

            DynamicVolume vol = node->getVolume();
            Matrix m = view;
            if(node->getParent() != NullFC)
                m.mult(node->getParent()->getToWorld());
            vol.transform(m);

            // ignore objects behind the camera.
            if(vol.getMax()[2] < 0.0f)
            {
                glDepthMask(GL_FALSE);
                glColorMask(GL_FALSE,GL_FALSE,GL_FALSE,GL_FALSE);
    
                if(ract->_occlusionQuery == 0)
                    ract->_glGenQueriesARB(1, &ract->_occlusionQuery);
    
                const DynamicVolume& vol = node->getVolume();
                Pnt3f min,max;
                vol.getBounds(min, max);
    
                ract->_glBeginQueryARB(GL_SAMPLES_PASSED_ARB, ract->_occlusionQuery);
                ract->drawOcclusionBB(min, max);
                ract->_glEndQueryARB(GL_SAMPLES_PASSED_ARB);
    
                glDepthMask(GL_TRUE);
                glColorMask(GL_TRUE,GL_TRUE,GL_TRUE,GL_TRUE);
    
                GLuint pixels = 0;
                ract->_glGetQueryObjectuivARB(ract->_occlusionQuery, GL_QUERY_RESULT_ARB, &pixels);
    
                occluded = (pixels == 0);
            }
        }

        if(occluded)
        {
            _lightStates[i] = 0;
        }
        else
        {
            bool light_state = _lights[i].second->getOn();
            if(_lights[i].second->getShadowMode() == Light::CAST_SHADOW_ON)
                light_state = true;
            else if(_lights[i].second->getShadowMode() == Light::CAST_SHADOW_OFF)
                light_state = false;

            _lightStates[i] = (light_state ? 1 : 0);
        }
    }

    //updateLights();
}

void ShadowViewport::setReadBuffer(void)
{
    if(getLeftBuffer())
    {
        if(getRightBuffer())
        {
            glReadBuffer(GL_BACK);
        }
        else
        {
            glReadBuffer(GL_BACK_LEFT);
        }
    }
    else
    {
        if(getRightBuffer())
        {
            glReadBuffer(GL_BACK_RIGHT);
        }
        else
        {
            glReadBuffer(GL_NONE);
        }
    }
}

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
static Char8 cvsid_cpp       [] =
    "@(#)$Id: OSGShadowViewport.cpp,v 1.31 2007/06/13 16:51:56 yjung Exp $";
static Char8 cvsid_hpp       [] = OSGSHADOWVIEWPORTBASE_HEADER_CVSID;
static Char8 cvsid_inl       [] = OSGSHADOWVIEWPORTBASE_INLINE_CVSID;

static Char8 cvsid_fields_hpp[] = OSGSHADOWVIEWPORTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

