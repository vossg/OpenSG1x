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

#include <set>

// CgFX
/*
#include <Cg/cg.h>
#include <Cg/cgGL.h>
*/

#include <OSGConfig.h>

#include <OSGGL.h>
#include <OSGGLU.h>
#include <OSGGLEXT.h>
#include <OSGRemoteAspect.h>
#include <OSGCamera.h>
#include <OSGViewport.h>
#include <OSGRenderAction.h>
#include <OSGImage.h>
#include <OSGTextureChunk.h>
#include <OSGFileSystem.h>
#include <OSGImageFileHandler.h>
#include <OSGPathHandler.h>
#include <OSGSceneFileHandler.h>

#include <OSGShaderParameter.h>
#include <OSGShaderParameterBool.h>
#include <OSGShaderParameterInt.h>
#include <OSGShaderParameterReal.h>
#include <OSGShaderParameterVec2f.h>
#include <OSGShaderParameterVec3f.h>
#include <OSGShaderParameterVec4f.h>
#include <OSGShaderParameterMatrix.h>
#include <OSGShaderParameterString.h>

#include "OSGCGFXChunk.h"
#include "OSGCGFXMaterial.h"
#include "OSGCGFXAnnotation.h"

#include <Cg/cgGL.h>

#ifndef GL_CLIENT_ALL_ATTRIB_BITS
#define GL_CLIENT_ALL_ATTRIB_BITS 0xffffffff
#endif

OSG_USING_NAMESPACE

/*! \class osg::CGFXChunk

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

// Techniques
#define EFFECT_TECHNIQUE_NUM_MAX 256

StateChunkClass CGFXChunk::_class("CGFX");

bool CGFXChunk::_initializedCGFXGL = false;
Real64  CGFXChunk::_time = -1.0;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CGFXChunk::initMethod (void)
{
}

void CGFXChunk::cgErrorCallback(void)
{
    FWARNING(("CGFXChunk: Cg error: %s\n", cgGetErrorString(cgGetError())));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

CGFXChunk::EffectS::EffectS(void) :
    context(NULL),
    effect(NULL),
    pass(NULL)
{
}

void CGFXChunk::EffectS::reset(void)
{
    if(effect != NULL)
        cgDestroyEffect(effect);
    effect = NULL;
    if(context != NULL)
        cgDestroyContext(context);
    context = NULL;
    pass = NULL;
}

/*----------------------- constructors & destructors ----------------------*/

CGFXChunk::CGFXChunk(void) :
    Inherited(),
    _effect(),
    _textures(),
    _cgfx_changed(false),
    _npasses(1),
    _state_parameters(),
    _action(NULL),
    _parentMat(NullFC),
    _effectFile(),
    _effectFilePath(),
    _technique(0)
{
}

CGFXChunk::CGFXChunk(const CGFXChunk &source) :
    Inherited(source),
    _effect(source._effect),
    _textures(source._textures),
    _cgfx_changed(source._cgfx_changed),
    _npasses(source._npasses),
    _state_parameters(source._state_parameters),
    _action(source._action),
    _parentMat(source._parentMat),
    _effectFile(source._effectFile),
    _effectFilePath(source._effectFilePath),
    _technique(source._technique)
{
}

CGFXChunk::~CGFXChunk(void)
{
}

void CGFXChunk::onCreate(const CGFXChunk *source)
{
    Inherited::onCreate(source);

    // ignore prototypes.
    if(GlobalSystemState == Startup)
        return;

    _state_parameters.resize(CGFXChunk::OSG_CG_LAST);

    // we need this for clustering without it handleGL is never called.
    RemoteAspect::addFieldFilter(CGFXChunk::getClassType().getId(),
                                 CGFXChunk::GLIdFieldMask);

    CGFXChunkPtr tmpPtr(*this);
    beginEditCP(tmpPtr, CGFXChunk::GLIdFieldMask);
        setGLId(Window::registerGLObject(osgTypedMethodVoidFunctor2ObjCPtrPtr<CGFXChunkPtr,
                                         Window , UInt32>(tmpPtr, &CGFXChunk::handleGL), 1));
    endEditCP(tmpPtr, CGFXChunk::GLIdFieldMask);
}

void CGFXChunk::onDestroy(void)
{
    Inherited::onDestroy();

    for(UInt32 i=1;i<_effect.size();++i)
        _effect[i].reset();
    _effect.clear();

    for(TexturesMap::iterator it = _textures.begin();it != _textures.end();++it)
        subRefCP((*it).second.first);
    _textures.clear();

    if(getGLId() > 0)
        Window::destroyGLObject(getGLId(), 1);
}

const StateChunkClass *CGFXChunk::getClass(void) const
{
    return &_class;
}

/*----------------------------- class specific ----------------------------*/

void CGFXChunk::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void CGFXChunk::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CGFXChunk NI" << std::endl;
}

/*! GL object handler
    create the program and destroy it
*/
void CGFXChunk::handleGL(Window *win, UInt32 idstatus)
{
    Window::GLObjectStatusE mode;
    UInt32 id;

    Window::unpackIdStatus(idstatus, id, mode);

    //printf("CGFXChunk::handleGL\n");

    if(mode == Window::destroy)
    {
        UInt32 effect_id = win->getGLObjectId(id);
        if(effect_id > 0)
        {
            //printf("destroing effect and textures: id = %u\n", effect_id);
            // delete old effect and the textures.
            win->setGLObjectId(id, 0);
        }
    }
    else if(mode == Window::finaldestroy)
    {
        ;//SWARNING << "Last program user destroyed" << std::endl;
    }
    else if(mode == Window::initialize || mode == Window::reinitialize ||
            mode == Window::needrefresh)
    {
        if(mode != Window::needrefresh)
        {
            updateEffect(win);
        }

        updateParameters(win);
        updateTechnique(win);
    }
    else
    {
        SWARNING << "CGFXChunk(" << this << "::handleGL: Illegal mode: "
             << mode << " for id " << id << std::endl;
    }
}

void CGFXChunk::addTextureSearchPaths(void)
{
    PathHandler *path_handler = ImageFileHandler::the().getPathHandler();
    if(path_handler == NULL)
        return;

    char *cgfxPath = getenv("CGFX_TEXTURE_PATH");

#ifdef WIN32
    if(cgfxPath != NULL)
        path_handler->push_backWin32Path(cgfxPath);
    path_handler->push_backWin32Path(".;..\\CgFX_textures;..\\textures\\1D;..\\textures\\2D;"
                                     "..\\textures\\3D;..\\textures\\cubemaps;"
                                     "..\\textures\\rectangles;..\\default;..\\CgFX");
    path_handler->push_backWin32Path(_effectFilePath.c_str());
#else
    if(cgfxPath != NULL)
        path_handler->push_backUnixPath(cgfxPath);
    path_handler->push_backUnixPath(".:../CgFX_textures:../textures/1D:../textures/2D:"
                                    "../textures/3D:../textures/cubemaps:"
                                    "../textures/rectangles:../default:../CgFX");
    path_handler->push_backUnixPath(_effectFilePath.c_str());
#endif
}

void CGFXChunk::subTextureSearchPaths(void)
{
    PathHandler *path_handler = ImageFileHandler::the().getPathHandler();
    if(path_handler == NULL)
        return;

    char *cgfxPath = getenv("CGFX_TEXTURE_PATH");

#ifdef WIN32
    if(cgfxPath != NULL)
        path_handler->subWin32Path(cgfxPath);
    path_handler->subWin32Path(".;..\\CgFX_textures;..\\textures\\1D;..\\textures\\2D;"
                               "..\\textures\\3D;..\\textures\\cubemaps;"
                               "..\\textures\\rectangles;..\\default;..\\CgFX");
    path_handler->subWin32Path(_effectFilePath.c_str());
#else
    if(cgfxPath != NULL)
        path_handler->subUnixPath(cgfxPath);
    path_handler->subUnixPath(".:../CgFX_textures:../textures/1D:../textures/2D:"
                              "../textures/3D:../textures/cubemaps:"
                              "../textures/rectangles:../default:../CgFX");
    path_handler->subUnixPath(_effectFilePath.c_str());
#endif
}

void CGFXChunk::initCGFXGL(void)
{
}

void CGFXChunk::updateEffect(Window *win)
{
    //printf("CGFXChunk::updateEffect\n");

    if(_effectString.empty())
        return;

    if(_effect.empty())
    {
        // our null effect!
        EffectS e;
        _effect.push_back(e);
    }
    
    UInt32 id = win->getGLObjectId(getGLId());
    if(id > 0 && id < _effect.size())
    {
        //printf("deleting old id %u\n", id);
        // delete old effect
        _effect[id].reset();
    }
    else
    {
        // first look for a free id.
        for(UInt32 i=1;i<_effect.size();++i)
        {
            if(_effect[i].effect == NULL)
            {
                id = i;
                break;
            }
        }

        if(id == 0)
        {
            id = _effect.size(); // create new id!
            //printf("new id %p %u\n", this, id);
            EffectS e;
            _effect.push_back(e);
        }
        else
        {
            ; //printf("re-using id %u\n", id);
        }
        
        win->setGLObjectId(getGLId(), 0);
    }

    CGcontext context = cgCreateContext();

    cgSetErrorCallback(cgErrorCallback);
    cgGLRegisterStates(context);
    //cgGLSetManageTextureParameters(context, CG_TRUE);

    CGeffect effect = NULL;

    //printf("CGFXChunk : trying to load effect file: '%s'\n", _effectFile.c_str());
    //printf("CGFXChunk : trying to compile effect string\n");

    // Load new effect
    const char *errors = NULL;
    effect = cgCreateEffect(context, _effectString.c_str(), NULL);

    if(effect == NULL)
    {
        const char *listing = cgGetLastListing(context);
        if(listing != NULL)
        {
            FWARNING(("CGFXChunk : Couldn't create effect: '%s'!\n", listing));
        }
        else
        {
            FWARNING(("CGFXChunk : Couldn't create effect!\n"));
        }
        cgDestroyContext(context);
        return;
    }

    _effect[id].context = context;
    _effect[id].effect = effect;
    //printf("created new effect %u %p\n", id, effect);

    // clear old parameter states.
    for(UInt32 i=0;i<_state_parameters.size();++i)
        _state_parameters[i] = "";

    CGFXMaterialPtr cgfxMat = CGFXMaterialPtr::dcast(_parentMat);

    if(_cgfx_changed)
    {
        // ok the whole cgfx file changed destroy old textures.
        for(TexturesMap::iterator it = _textures.begin();it != _textures.end();++it)
            subRefCP((*it).second.first);
        _textures.clear();
    }

    std::set<std::string> cgfxParameters;

    beginEditCP(cgfxMat, CGFXMaterial::ParametersFieldMask);
    // Search for known parameters
    
    
    //for (UInt32 i = 0; i < effectDesc.Parameters; ++i)
    CGparameter param = cgGetFirstEffectParameter(effect);
    while(param)
    {
        UInt32 nrows = cgGetParameterRows(param);
        UInt32 ncols = cgGetParameterColumns(param);
        UInt32 components = nrows * ncols;

        std::string paramName = cgGetParameterName(param) ? cgGetParameterName(param) : "";
        std::string paramSemantic = cgGetParameterSemantic(param) ? cgGetParameterSemantic(param) : "";
        CGtype paramType = cgGetParameterType(param);

        //printf("parameter: '%s' '%s'\n", paramSemantic.c_str(), paramName.c_str());
        // get tweakable parameters
        //if(cgGetFirstParameterAnnotation(param) != NULL) // tweakable parameters.
        //if(paramSemantic.empty())

        if (stringcasecmp(paramSemantic.c_str(), "Projection") == 0)
            setStateParameter(CGFXChunk::OSG_CG_PROJECTION, paramName);
        else if (stringcasecmp(paramSemantic.c_str(), "WorldViewProjection") == 0)
            setStateParameter(CGFXChunk::OSG_CG_WORLDVIEWPROJECTION, paramName);
        else if (stringcasecmp(paramSemantic.c_str(), "World") == 0)
            setStateParameter(CGFXChunk::OSG_CG_WORLD, paramName);
        else if (stringcasecmp(paramSemantic.c_str(), "WorldI") == 0)
            setStateParameter(CGFXChunk::OSG_CG_WORLDI, paramName);
        else if (stringcasecmp(paramSemantic.c_str(), "WorldIT") == 0)
            setStateParameter(CGFXChunk::OSG_CG_WORLDIT, paramName);
        else if (stringcasecmp(paramSemantic.c_str(), "WorldInverseTranspose") == 0)
            setStateParameter(CGFXChunk::OSG_CG_WORLDIT, paramName);
        else if (stringcasecmp(paramSemantic.c_str(), "WorldView") == 0)
            setStateParameter(CGFXChunk::OSG_CG_WORLDVIEW, paramName);
        else if (stringcasecmp(paramSemantic.c_str(), "WorldViewI") == 0)
            setStateParameter(CGFXChunk::OSG_CG_WORLDVIEWI, paramName);
        else if (stringcasecmp(paramSemantic.c_str(), "WorldViewInverse") == 0)
            setStateParameter(CGFXChunk::OSG_CG_WORLDVIEWI, paramName);
        else if (stringcasecmp(paramSemantic.c_str(), "View") == 0)
            setStateParameter(CGFXChunk::OSG_CG_VIEW, paramName);
        else if (stringcasecmp(paramSemantic.c_str(), "ViewI") == 0)
            setStateParameter(CGFXChunk::OSG_CG_VIEWI, paramName);
        else if (stringcasecmp(paramSemantic.c_str(), "ViewInverse") == 0)
            setStateParameter(CGFXChunk::OSG_CG_VIEWI, paramName);
        else if (stringcasecmp(paramSemantic.c_str(), "ViewIT") == 0)
            setStateParameter(CGFXChunk::OSG_CG_VIEWIT, paramName);
        else if (stringcasecmp(paramSemantic.c_str(), "ViewInverseTranspose") == 0)
            setStateParameter(CGFXChunk::OSG_CG_VIEWIT, paramName);
        else if (stringcasecmp(paramSemantic.c_str(), "Time") == 0)
            setStateParameter(CGFXChunk::OSG_CG_TIME, paramName);
        else
        {
            switch(paramType)
            {
                case CG_BOOL:
                {
                    Int32 val;
                    if(!cgfxMat->getParameter(paramName.c_str(), val))
                    {
                        if(cgGetParameterValueir(param, 1, &val) == 1)
                        {
                            //printf("adding default parameter: '%s' (%d)\n", param.Name, val);
                            cgfxMat->setParameter(paramName.c_str(), (val > 0));
                        }
                    }
                    cgfxParameters.insert(paramName);
                }
                break;
                
                case CG_INT:
                {
                    Int32 val;
                    if(!cgfxMat->getParameter(paramName.c_str(), val))
                    {
                        if(cgGetParameterValueir(param, 1, &val) == 1)
                        {
                            //printf("adding default parameter: '%s' (%d)\n", param.Name, val);
                            cgfxMat->setParameter(paramName.c_str(), val);
                        }
                    }
                    cgfxParameters.insert(paramName);
                }
                break;

                case CG_FLOAT:
                case CG_FLOAT2:
                case CG_FLOAT3:
                case CG_FLOAT4:
                case CG_FLOAT4x4:
                    switch(components)
                    {
                        case 1:
                        {
                            Real32 val;
                            if(!cgfxMat->getParameter(paramName.c_str(), val))
                            {
                                if(cgGetParameterValuefr(param, 1, &val) == 1)
                                {
                                    //printf("adding default parameter: '%s' (%f)\n", param.Name, val);
                                    cgfxMat->setParameter(paramName.c_str(), val);
                                }
                            }
                            cgfxParameters.insert(paramName);
                        }
                        break;
                        case 2:
                        {
                            Vec2f val;
                            if(!cgfxMat->getParameter(paramName.c_str(), val))
                            {
                                if(cgGetParameterValuefr(param, 2, val.getValues()) == 2)
                                {
                                    //printf("adding default parameter: '%s' (%f, %f)\n", param.Name, val[0], val[1]);
                                    cgfxMat->setParameter(paramName.c_str(), val);
                                }
                            }
                            cgfxParameters.insert(paramName);
                        }
                        break;
                        case 3:
                        {
                            Vec3f val;
                            if(!cgfxMat->getParameter(paramName.c_str(), val))
                            {
                                if(cgGetParameterValuefr(param, 3, val.getValues()) == 3)
                                {
                                    //printf("adding default parameter: '%s' (%f, %f, %f)\n", param.Name, val[0], val[1], val[2]);
                                    cgfxMat->setParameter(paramName.c_str(), val);
                                }
                            }
                            cgfxParameters.insert(paramName);
                        }
                        break;
                        case 4:
                        {
                            Vec4f val;
                            if(!cgfxMat->getParameter(paramName.c_str(), val))
                            {
                                if(cgGetParameterValuefr(param, 4, val.getValues()) == 4)
                                {
                                    //printf("adding default parameter: '%s' (%f, %f, %f, %f)\n", param.Name, val[0], val[1], val[2], val[3]);
                                    cgfxMat->setParameter(paramName.c_str(), val);
                                }
                            }
                            cgfxParameters.insert(paramName);
                        }
                        break;
                        case 16:
                        {
                            // CHECK cgSetParameterValuefr or cgSetParameterValuefc
                            Matrix val;
                            if(!cgfxMat->getParameter(paramName.c_str(), val))
                            {
                                if(cgGetParameterValuefr(param, 16, val.getValues()) == 16)
                                {
                                    /*
                                    printf("adding default parameter: '%s' (%f, %f, %f, %f,  "
                                           "%f, %f, %f, %f,  %f, %f, %f, %f,  %f, %f, %f, %f)\n",
                                            param.Name, val[0][0], val[0][1], val[0][2], val[0][3],
                                                        val[1][0], val[1][1], val[1][2], val[1][3],
                                                        val[2][0], val[2][1], val[2][2], val[2][3],
                                                        val[3][0], val[3][1], val[3][2], val[3][3]);
                                    */
                                    val.transpose();
                                    cgfxMat->setParameter(paramName.c_str(), val);
                                }
                            }
                            cgfxParameters.insert(paramName);
                        }
                        break;
                    }
                break;
                case CG_STRING:
                    // ignore strings for now
#if 0
                {
                    std::string str;
                    if(!cgfxMat->getParameter(paramName.c_str(), str))
                    {
                        const char *val = cgGetStringParameterValue(param);
                        if(val != NULL)
                        {
                            //printf("adding default parameter: '%s' (%s)\n", param.Name, val);
                            cgfxMat->setParameter(paramName.c_str(), val);
                        }
                    }
                    cgfxParameters.insert(paramName);
                }
#endif
                break;

                case CG_TEXTURE:
                // we look for this one in CG_SAMPLER2D ...
                break;
                case CG_SAMPLER1D:
                case CG_SAMPLER2D:
                case CG_SAMPLER3D:
                case CG_SAMPLERRECT:
                case CG_SAMPLERCUBE:
                {
                    std::string filename;
                    if(!cgfxMat->getParameter(paramName.c_str(), filename))
                    {
                        // ok first look for a tweakable File parameter in the sampler itself.
                        // get texture filename
                        if(cgGetFirstParameterAnnotation(param) != NULL)
                        {
                            CGannotation anno = cgGetNamedParameterAnnotation(param, "File");
                            if(anno == NULL)
                                anno = cgGetNamedParameterAnnotation(param, "ResourceName");

                            if(anno != NULL)
                            {
                                filename = cgGetStringAnnotationValue(anno);
                                
                                cgfxMat->setParameter(paramName.c_str(), filename);
                            }
                        }
        
                        if(filename.empty())
                        {
                            // ok second look for a tweakable parameter in the texture parameter.
                            CGstateassignment ss = cgGetFirstSamplerStateAssignment(param);
                            if(ss)
                            {
                                // cgGetSamplerStateAssignmentValue
                                CGparameter tparam = cgGetTextureStateAssignmentValue(ss);
                                if(tparam)
                                {
                                    CGtype tparamType = cgGetParameterType(tparam);
                        
                                    // get tweakable parameters
                                    if(cgGetFirstParameterAnnotation(tparam) != NULL &&
                                       tparamType == CG_TEXTURE)
                                    {
                                        CGannotation anno = cgGetNamedParameterAnnotation(tparam, "File");
                                        if(anno == NULL)
                                            anno = cgGetNamedParameterAnnotation(tparam, "ResourceName");

                                        if(anno != NULL)
                                        {
                                            filename = cgGetStringAnnotationValue(anno);
                                            cgfxMat->setParameter(paramName.c_str(), filename);
                                        }
                                    }
                                }
                            }
                        }
                    }
        
                    if(!filename.empty())
                    {
                        if(_cgfx_changed)
                        {
                            TextureChunkPtr texc = TextureChunk::create();
                            _textures.insert(std::make_pair(paramName, std::make_pair(texc, filename)));
                        }
                        else
                        {
                            // just upload the texture for the new context.
                            TexturesMap::iterator it = _textures.find(paramName);
                            if(it != _textures.end())
                            {
                                TextureChunkPtr texc = (*it).second.first;
                                texc->activate(_action, 0);
                                texc->deactivate(_action, 0);
                            }
                        }
                    }
        
                    cgfxParameters.insert(paramName);
                }
                break;
                default:
                    FWARNING(("CGFXChunk : Unsupported parameter (%s) type (%d)!\n", paramName.c_str(), paramType));
                break;
            }

            if(cgGetFirstParameterAnnotation(param) != NULL) // tweakable parameters.
            {
                // now add the Annotation Attachment.
    
                // search for the parameter via name.
                ShaderParameterPtr sp = NullFC;
                for(UInt32 j=0;j<cgfxMat->getParameters().getSize();++j)
                {
                    sp = cgfxMat->getParameters()[j];
                    if(sp->getName() == paramName)
                        break;
                }
                
                if(sp != NullFC)
                {
                    CGFXAnnotationPtr osgAnnotation = CGFXAnnotationPtr::dcast(sp->findAttachment(CGFXAnnotation::getClassType()));
    
                    if(osgAnnotation == NullFC)
                        osgAnnotation = CGFXAnnotation::create();
                    else
                        osgAnnotation->getParameters().clear();
    
                    //printf("Annoation of '%s'\n", param.Name);
                    beginEditCP(osgAnnotation);
                        CGannotation anno = cgGetFirstParameterAnnotation(param);
                        while(anno != NULL)
                        {
                            CGtype annoType = cgGetAnnotationType(anno);
                            std::string annoName = cgGetAnnotationName(anno);
    
                            switch(annoType)
                            {
                                case CG_BOOL:
                                {
                                    Int32 n;
                                    const int *values = cgGetBooleanAnnotationValues(anno, &n);
                                    if(n > 0)
                                    {
                                        bool val = (values[0] > 0);
                                        //printf("\t '%s' (%d)\n", annotation.Name, val);
                                        ShaderParameterIntPtr p = ShaderParameterInt::create();
                                        beginEditCP(p);
                                            p->setName(annoName);
                                            p->setValue(val);
                                        endEditCP(p);
                                        osgAnnotation->getParameters().push_back(p);
                                    }
                                }
                                break;
                                case CG_INT:
                                {
                                    Int32 n;
                                    const int *values = cgGetIntAnnotationValues(anno, &n);
                                    if(n > 0)
                                    {
                                        Int32 val = values[0];
                                        //printf("\t '%s' (%d)\n", annotation.Name, val);
                                        ShaderParameterIntPtr p = ShaderParameterInt::create();
                                        beginEditCP(p);
                                            p->setName(annoName);
                                            p->setValue(val);
                                        endEditCP(p);
                                        osgAnnotation->getParameters().push_back(p);
                                    }
                                }
                                break;
                                case CG_FLOAT:
                                {
                                    Int32 n;
                                    const float *values = cgGetFloatAnnotationValues(anno, &n);
                                    if(n > 0)
                                    {
                                        Real32 val = values[0];
                                        //printf("\t '%s' (%f)\n", annotation.Name, val);
                                        ShaderParameterRealPtr p = ShaderParameterReal::create();
                                        beginEditCP(p);
                                            p->setName(annoName);
                                            p->setValue(val);
                                        endEditCP(p);
                                        osgAnnotation->getParameters().push_back(p);
                                    }
                                }
                                break;
                                case CG_STRING:
                                {
                                    const char *val = cgGetStringAnnotationValue(anno);
                                    if(val != NULL)
                                    {
                                        //printf("\t '%s' (%s)\n", annotation.Name, val);
                                        ShaderParameterStringPtr p = ShaderParameterString::create();
                                        beginEditCP(p);
                                            p->setName(annoName);
                                            p->setValue(val);
                                        endEditCP(p);
                                        osgAnnotation->getParameters().push_back(p);
                                    }
                                }
                                break;
                                default:
                                   FWARNING(("CGFXChunk : Unsupported annotation (%s) type (%d)!\n", annoName.c_str(), annoType));
                                break;
                            }
    
                            anno = cgGetNextAnnotation(anno);
                        }
                    endEditCP(osgAnnotation);
    
                    // add the annotation attachment to the parameter.
                    beginEditCP(sp, ShaderParameter::AttachmentsFieldMask);
                        sp->addAttachment(osgAnnotation);
                    endEditCP(sp, ShaderParameter::AttachmentsFieldMask);
                }
            }
        }

        param = cgGetNextParameter(param);
    } // param while

    endEditCP(cgfxMat, CGFXMaterial::ParametersFieldMask);

    // remove non existing parameters this happens if you load a osb file
    // with a cgfx material and its parameters and then just load another
    // cgfx file.
    std::vector<std::string> remove_params;
    for(UInt32 i=0;i<cgfxMat->getParameters().size();++i)
    {
        // we can not remove them directly in here with subParameter()!
        ShaderParameterPtr p = ShaderParameterPtr::dcast(cgfxMat->getParameters()[i]);
        if(cgfxParameters.count(p->getName()) == 0)
            remove_params.push_back(p->getName());
    }
    beginEditCP(cgfxMat, CGFXMaterial::ParametersFieldMask);
        for(UInt32 i=0;i<remove_params.size();++i)
            cgfxMat->subParameter(remove_params[i].c_str());
    endEditCP(cgfxMat, CGFXMaterial::ParametersFieldMask);

    if(!updateTechnique(win, effect))
    {
        FWARNING(("CGFXChunk : Couldn't find a valid technique!\n"));
        _effect[id].reset();
        return;
    }

    _cgfx_changed = false;
    // ok effect is valid set id.
    win->setGLObjectId(getGLId(), id);
    //printf("updateEffect ready\n");
}

void CGFXChunk::setParentMaterial(const MultiPassMaterialPtr &parentMat)
{
    _parentMat = parentMat;
}

void CGFXChunk::updateParameters(Window *win)
{
    //printf("CGFXChunk::updateParameters\n");
    UInt32 id = win->getGLObjectId(getGLId());
    if(id == 0)
        return;

    if(id >= _effect.size())
    {
        FFATAL(("CGFXChunk::updateParameters id (%u) >= effect size (%u)!\n", id, _effect.size()));
        return;
    }

    CGeffect effect = _effect[id].effect;
    
    if(effect == NULL)
        return;

    CGFXMaterialPtr cgfxMat = CGFXMaterialPtr::dcast(_parentMat);
    MFShaderParameterPtr parameters = cgfxMat->getParameters();

    std::vector<std::string> image_filenames;

    for(UInt32 i = 0; i < parameters.size(); ++i)
    {
        ShaderParameterPtr parameter = parameters[i];

        CGparameter param = cgGetNamedEffectParameter(effect, parameter->getName().c_str());

        if(param == NULL)
        {
            FWARNING(("CGFXChunk : Ignoring unknown parameter '%s'!\n",
                      parameter->getName().c_str()));
            continue;
        }
        
        switch(parameter->getTypeId())
        {
            case ShaderParameter::SHPTypeBool:
            {
                ShaderParameterBoolPtr p = ShaderParameterBoolPtr::dcast(parameter);
                cgSetParameter1i(param, p->getValue() ? 1 : 0);
            }
            break;
            case ShaderParameter::SHPTypeInt:
            {
                ShaderParameterIntPtr p = ShaderParameterIntPtr::dcast(parameter);
                cgSetParameter1i(param, p->getValue());
            }
            break;
            case ShaderParameter::SHPTypeReal:
            {
                ShaderParameterRealPtr p = ShaderParameterRealPtr::dcast(parameter);
                cgSetParameter1f(param, p->getValue());
            }
            break;
            case ShaderParameter::SHPTypeVec2f:
            {
                ShaderParameterVec2fPtr p = ShaderParameterVec2fPtr::dcast(parameter);
                cgSetParameter2fv(param, p->getValue().getValues());
            }
            break;
            case ShaderParameter::SHPTypeVec3f:
            {
                ShaderParameterVec3fPtr p = ShaderParameterVec3fPtr::dcast(parameter);
                cgSetParameter3fv(param, p->getValue().getValues());
            }
            break;
            case ShaderParameter::SHPTypeVec4f:
            {
                ShaderParameterVec4fPtr p = ShaderParameterVec4fPtr::dcast(parameter);
                cgSetParameter4fv(param, p->getValue().getValues());
            }
            break;
            case ShaderParameter::SHPTypeMatrix:
            {
                ShaderParameterMatrixPtr p = ShaderParameterMatrixPtr::dcast(parameter);
                // CHECK cgSetMatrixParameterfr or cgSetMatrixParameterfc!!!!
                cgSetMatrixParameterfr(param, p->getValue().getValues());
            }
            break;
            case ShaderParameter::SHPTypeString:
            {
                ShaderParameterStringPtr p = ShaderParameterStringPtr::dcast(parameter);
                TexturesMap::iterator it = _textures.find(parameter->getName());
                if(it != _textures.end()) // ok it was a texture
                {
                    TextureChunkPtr texc = (*it).second.first;
                    std::string filename = (*it).second.second;

                    ImagePtr img = texc->getImage();
                    std::string pfilename = p->getValue();
                    image_filenames.push_back(pfilename);

                    std::string filename2 = filename;
                    for(UInt32 i=0;i<filename2.size();++i)
                    {
                        if(filename2[i] == '\\')
                            filename2[i] = '/';
                    }

                    std::string pfilename2 = pfilename;
                    for(UInt32 i=0;i<pfilename2.size();++i)
                    {
                        if(pfilename2[i] == '\\')
                            pfilename2[i] = '/';
                    }

                    // now check if the image filename has changed or we need
                    // to create a image.
                    if(img == NullFC || filename2 != pfilename2)
                    {
                        //printf("texture image filename changed '%s' == '%s' !!!\n",
                        //       filename.c_str(), pfilename.c_str());
                        
                        // ok now look in our own images list.

                        ImagePtr newimg = cgfxMat->findImage(pfilename);
                        if(newimg == NullFC)
                        {
                            //printf("loading image '%s' from filesystem.\n", pfilename.c_str());
                            addTextureSearchPaths();
                            img = OSG::ImageFileHandler::the().read(pfilename.c_str());
                            subTextureSearchPaths();

                            if(img != NullFC)
                            {
                                beginEditCP(img);
                                    img->setName(pfilename.c_str());
                                endEditCP(img);

                                beginEditCP(cgfxMat, CGFXMaterial::ImagesFieldMask);
                                    cgfxMat->getImages().push_back(img);
                                endEditCP(cgfxMat, CGFXMaterial::ImagesFieldMask);
                            }
                        }
                        else
                        {
                            //printf("using image '%s' from cgfxMat images.\n", pfilename.c_str());
                            img = newimg;
                        }

                        if(img != NullFC)
                        {
                            beginEditCP(texc);
                                texc->setImage(img);
#if 0
                                if(img->getDataType() == Image::OSG_FLOAT16_IMAGEDATA ||
                                    img->getDataType() == Image::OSG_FLOAT32_IMAGEDATA)
                                {
                                    texc->setInternalFormat(GL_RGBA16F_ARB);
                                }
#endif
                            endEditCP(texc);

                            if(_action != NULL)
                            {
                                texc->activate(_action, 0);
                                texc->deactivate(_action, 0);
                            }
                        }
                    }

                    //cgGLSetupSampler(param, win->getGLObjectId(texc->getGLId()));
                    cgGLSetTextureParameter(param, win->getGLObjectId(texc->getGLId()));
                }
                else // a string
                {
                    cgSetStringParameterValue(param, p->getValue().c_str());
                }
            }
            break;
            default:
                FWARNING(("CGFXChunk : Parameter '%s' has unknown tpye %d!\n",
                          parameter->getName().c_str(), parameter->getTypeId()));
            break;
        }
    }

    // remove unused images.
    std::vector<ImagePtr> used_images;
    for(UInt32 i=0;i<image_filenames.size();++i)
    {
        ImagePtr img = cgfxMat->findImage(image_filenames[i]);
        if(img != NullFC)
            used_images.push_back(img);
    }

    //printf("used images %u\n", used_images.size());
    if(used_images.size() != cgfxMat->getImages().size())
    {
        //printf("recreating images list!\n");

        // destroy old images.
#if 0
        for(UInt32 i=0;i<cgfxMat->getImages().size();++i)
        {
            ImagePtr img = cgfxMat->getImages()[i];
            bool found = false;
            for(UInt32 j=0;j<used_images.size();++j)
            {
                if(img == used_images[j])
                {
                    found = true;
                    break;
                }
            }
            if(!found)
                subRefCP(img);
        }
#endif

        // recreate new image list.
        beginEditCP(cgfxMat, CGFXMaterial::ImagesFieldMask);
            cgfxMat->getImages().clear();
            for(UInt32 i=0;i<used_images.size();++i)
                cgfxMat->getImages().push_back(used_images[i]);
        endEditCP(cgfxMat, CGFXMaterial::ImagesFieldMask);
    }

}

void CGFXChunk::setEffectFile(const std::string &effectFile)
{
    //printf("CGFXChunk::setEffectFile\n");
    _effectFile = effectFile;

    const Char8 *tmp_current = Directory::getCurrent();
    std::string old_current = tmp_current;
    delete [] tmp_current;

    // try to handle relativ fx file paths.
    PathHandler *pathHandler = SceneFileHandler::the().getPathHandler();
    std::string fullFilePath;
    if(pathHandler != NULL)
    {
        pathHandler->push_backPath(".");
        pathHandler->push_backPath(old_current.c_str());
        fullFilePath = pathHandler->findFile(_effectFile.c_str());
        pathHandler->subPath(".");
        pathHandler->subPath(old_current.c_str());
    }
    else
        fullFilePath = _effectFile.c_str();
    
    std::string path = fullFilePath;
    while(path.length() > 0 &&
          path[path.length()-1] != '/' &&
          path[path.length()-1] != '\\')
    {
        path.resize(path.length()-1);
    }

    if(path.empty())
        path = ".";

    _effectFilePath = path;

    // ok without setting the current path relative includes in the cgfx file
    // doesn't work!
    if(!Directory::setCurrent(path.c_str()))
        FWARNING(("CGFXChunk : Couldn't change dir to: '%s'!\n", path.c_str()));

    // ----------------------

    // create cgfx string.
    std::string effectString;
    if(!read(fullFilePath, effectString))
    {
        //FWARNING(("CGFXChunk : Couldn't read cgfx file '%s'!\n", effectFile.c_str()));
        Directory::setCurrent(old_current.c_str());
        return;
    }

    Directory::setCurrent(old_current.c_str());

    CGFXMaterialPtr cgfxMat = CGFXMaterialPtr::dcast(_parentMat);
    beginEditCP(cgfxMat, CGFXMaterial::EffectStringFieldMask);
        cgfxMat->setEffectString(effectString);
    endEditCP(cgfxMat, CGFXMaterial::EffectStringFieldMask);
}

bool CGFXChunk::read(const std::string &filename, std::string &data)
{
    if(filename.empty())
        return false;

    FILE *f = fopen(filename.c_str(), "rb");
    if(f == NULL)
        return false;

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);

    data.erase();
    data.resize(size);
    int r = fread(&data[0], 1, size, f);
    fclose(f);

    if(r <= 0)
        return false;

    // ok now replace CR/LF with LF on some strings with CR/LF I get this error
    // Failed to set technique (Error(s) in DX vertex shader: (2) : Error : Illegal character: 13 decimal.
    // (2) : Error : Syntax Error.
    // the easy way just replace CR with a space ...
    for(UInt32 i=0;i<data.size();++i)
    {
        if(data[i] == '\r')
            data[i] = ' ';
    }

    // parse the cgfx string for #include statements and inline the code.
    std::string::size_type pos;
    while((pos = data.find("#include")) != std::string::npos)
    {
        std::string::size_type p = pos;
        std::string line;
        while(true)
        {
            std::string str = data.substr(p++, 1);
            if(str == "\n")
                break;
            line += str;
        }

        // now exclude the filename everything between "" or <>
        std::string filename;
        bool found_open = false;
        for(std::string::size_type i=0;i<line.size();++i)
        {
            std::string str = line.substr(i, 1);

            if(!found_open)
            {
                if(str == "\"" || str == "<")
                    found_open = true;
            }
            else
            {
                if(str == "\"" || str == "<")
                    break;
            }

            if(found_open && str != "\"" && str != "<")
                filename += str;
        }

        std::string inline_str;
        // read the include file and inline the code.
        read(filename, inline_str);
        data.replace(pos, p - pos, inline_str);
    }

    return true;
}

void CGFXChunk::setEffectString(const std::string &effectString)
{
    //printf("CGFXChunk::setEffectString\n");
    
    if(_effectString == effectString)
    {
        //printf("CGFXChunk::setEffectString : cgfx string didn't change ignoring.\n");
        return;
    }

    CGFXMaterialPtr cgfxMat = CGFXMaterialPtr::dcast(_parentMat);
    beginEditCP(cgfxMat, CGFXMaterial::ParametersFieldMask);
        cgfxMat->getParameters().clear();
    endEditCP(cgfxMat, CGFXMaterial::ParametersFieldMask);

    _effectString = effectString;
    if(_effectString.empty())
    {
        FWARNING(("CGFXChunk : effect string is empty!\n"));
        return;
    }

    _cgfx_changed = true;
    _technique = 0;
    Window::reinitializeGLObject(getGLId());
}

void CGFXChunk::setTechnique(Int32 technique)
{
    if(_technique == technique)
        return;

    _technique = technique;

    Window::refreshGLObject(getGLId());
}

std::string CGFXChunk::getTechniqueString(Int32 index)
{
    if(_effect.empty())
        return "";

    CGeffect effect = _effect[1].effect;

    if(effect == NULL)
        return "";

    CGtechnique technique = cgGetFirstTechnique(effect);
    for(Int32 i=1;i<=index;++i)
        technique = cgGetNextTechnique(technique);

    if(technique == NULL)
        return "";

    return cgGetTechniqueName(technique);
}

bool CGFXChunk::updateTechnique(Window *win, CGeffect effect)
{
    if(effect == NULL)
    {
        UInt32 id = win->getGLObjectId(getGLId());
        if(id == 0)
            return false;

        if(id >= _effect.size())
        {
            FFATAL(("CGFXChunk::updateTechnique id (%u) >= effect size (%u)!\n", id, _effect.size()));
            return false;
        }

        effect = _effect[id].effect;
    }

    if(effect == NULL)
        return false;

    CGtechnique technique = cgGetFirstTechnique(effect);
    while(technique)
    {
        if(cgValidateTechnique(technique) == CG_FALSE)
        {
            FWARNING(("Technique '%s' did not validate.  Skipping.\n",
                    cgGetTechniqueName(technique)));
        }
        technique = cgGetNextTechnique(technique);
    }

    Int32 currentTechnique = 0;
    technique = cgGetFirstTechnique(effect);
    while(currentTechnique < _technique)
    {
        technique = cgGetNextTechnique(technique);
        ++currentTechnique;
    }

    if(!cgIsTechniqueValidated(technique))
    {
        // ok techique is not valid try to find a valid one.
        currentTechnique = 0;
        technique = cgGetFirstTechnique(effect);
        while(!cgIsTechniqueValidated(technique))
        {
            technique = cgGetNextTechnique(technique);
            if(technique == NULL)
                break;
        }
        if(technique == NULL)
        {
            FWARNING(("No valid techniques in effect file!\n"));
            return false;
        }
    }

    for(UInt32 i=0;i<_effect.size();++i)
    {
        if(_effect[i].effect == effect)
            _effect[i].technique = technique;
    }

    // get number of passes
    _npasses = 0;
    CGpass pass = cgGetFirstPass(technique);
    if(pass != NULL)
    {
        ++_npasses;
        while(true)
        {
            pass = cgGetNextPass(pass);
            if(pass != NULL)
                ++_npasses;
            else
                break;
        }
    }

    if(_technique != currentTechnique)
    {
        //printf("cgfx material setTechnique(%d)\n", _technique);
        _technique = currentTechnique;
        CGFXMaterialPtr cgfxMat = CGFXMaterialPtr::dcast(_parentMat);
        beginEditCP(cgfxMat, CGFXMaterial::TechniqueFieldMask);
            cgfxMat->setTechnique(_technique);
        endEditCP(cgfxMat, CGFXMaterial::TechniqueFieldMask);
    }

    return true;
}

bool CGFXChunk::isTextureParameter(const std::string &name)
{
    return (_textures.find(name) != _textures.end());
}

void CGFXChunk::setStateParameter(UInt32 type, const std::string &parameterName)
{
    if(type >= CGFXChunk::OSG_CG_LAST)
    {
        FWARNING(("CGFXChunk::setStateParameter : parameter type (%u) out of range!\n", type));
        return;
    }

    _state_parameters[type] = parameterName;
}

void CGFXChunk::updateStateParameters(DrawActionBase *action)
{
    Viewport *vp = action->getViewport();
    if(vp == NULL)
    {
        return;
    }

    UInt32 id = action->getWindow()->getGLObjectId(getGLId());
    if(id == 0)
        return;

    if(id >= _effect.size())
    {
        FFATAL(("CGFXChunk::updateStateParameters id (%u) >= effect size (%u)!\n", id, _effect.size()));
        return;
    }

    if(_effect[id].effect == NULL)
        return;

    Matrix m, world, projection, translation, viewing, viewingI;

    // ok with the new Material::NoStateSorting flags this works fine.
    RenderAction *ra = dynamic_cast<RenderAction *>(action);
    if(ra != NULL)
        world = ra->top_matrix();
    //world = action->getActNode()->getToWorld();

    action->getCamera()->getProjection(projection, vp->getPixelWidth(),
                                                   vp->getPixelHeight());
    action->getCamera()->getProjectionTranslation(translation, vp->getPixelWidth(),
                                                               vp->getPixelWidth());
    action->getCamera()->getViewing(viewing, vp->getPixelWidth(),
                                             vp->getPixelHeight());

    viewingI = viewing;
    viewingI.invert();

    if(!_state_parameters[OSG_CG_PROJECTION].empty())
    {
        m = projection;
        m.transpose();
        CGparameter param = cgGetNamedEffectParameter(_effect[id].effect,
                                _state_parameters[OSG_CG_PROJECTION].c_str());
        cgSetMatrixParameterfr(param, m.getValues());
        /*
        cgGLSetStateMatrixParameter(param, CG_GL_MODELVIEW_PROJECTION_MATRIX,
                                CG_GL_MATRIX_IDENTITY);
        */
    }

    if(!_state_parameters[OSG_CG_WORLDVIEWPROJECTION].empty())
    {
        m = projection;
        m.mult(translation);
        m.mult(viewing);
        m.mult(world);
        m.transpose();
        CGparameter param = cgGetNamedEffectParameter(_effect[id].effect,
                                _state_parameters[OSG_CG_WORLDVIEWPROJECTION].c_str());
        cgSetMatrixParameterfr(param, m.getValues());
    }

    if(!_state_parameters[OSG_CG_WORLD].empty())
    {
        m = world;
        m.transpose();
        CGparameter param = cgGetNamedEffectParameter(_effect[id].effect,
                                _state_parameters[OSG_CG_WORLD].c_str());
        cgSetMatrixParameterfr(param, m.getValues());
    }

    if(!_state_parameters[OSG_CG_WORLDI].empty())
    {
        m = world;
        m.invert();
        m.transpose();
        CGparameter param = cgGetNamedEffectParameter(_effect[id].effect,
                                _state_parameters[OSG_CG_WORLDI].c_str());
        cgSetMatrixParameterfr(param, m.getValues());
    }

    if(!_state_parameters[OSG_CG_WORLDIT].empty())
    {
        m = world;
        m.invert();
        CGparameter param = cgGetNamedEffectParameter(_effect[id].effect,
                                _state_parameters[OSG_CG_WORLDIT].c_str());
        cgSetMatrixParameterfr(param, m.getValues());
    }

    if(!_state_parameters[OSG_CG_WORLDVIEW].empty())
    {
        m = viewing;
        m.mult(world);
        m.transpose();
        CGparameter param = cgGetNamedEffectParameter(_effect[id].effect,
                                _state_parameters[OSG_CG_WORLDVIEW].c_str());
        cgSetMatrixParameterfr(param, m.getValues());
    }
    
    if(!_state_parameters[OSG_CG_WORLDVIEWI].empty())
    {
        m = viewing;
        m.mult(world);
        m.invert();
        m.transpose();
        CGparameter param = cgGetNamedEffectParameter(_effect[id].effect,
                                _state_parameters[OSG_CG_WORLDVIEWI].c_str());
        cgSetMatrixParameterfr(param, m.getValues());
    }
    
    if(!_state_parameters[OSG_CG_VIEW].empty())
    {
        m = viewing;
        m.transpose();
        CGparameter param = cgGetNamedEffectParameter(_effect[id].effect,
                                _state_parameters[OSG_CG_VIEW].c_str());
        cgSetMatrixParameterfr(param, m.getValues());
    }

    if(!_state_parameters[OSG_CG_VIEWI].empty())
    {
        m = viewingI;
        m.transpose();
        CGparameter param = cgGetNamedEffectParameter(_effect[id].effect,
                                _state_parameters[OSG_CG_VIEWI].c_str());
        cgSetMatrixParameterfr(param, m.getValues());
    }

    if(!_state_parameters[OSG_CG_VIEWIT].empty())
    {
        m = viewingI;
        CGparameter param = cgGetNamedEffectParameter(_effect[id].effect,
                                _state_parameters[OSG_CG_VIEWIT].c_str());
        cgSetMatrixParameterfr(param, m.getValues());
    }

    if(!_state_parameters[OSG_CG_TIME].empty())
    {
        Real64 systemTime = 0.0;
        if(CGFXMaterial::getTimerCB() != NULL)
            systemTime = CGFXMaterial::getTimerCB()();
        else
            systemTime = OSG::getSystemTime();
        
        if(_time == -1.0)
            _time = systemTime;

        Real32 t = Real32((OSG::getSystemTime() - _time) * 1000.0);
        CGparameter param = cgGetNamedEffectParameter(_effect[id].effect,
                                _state_parameters[OSG_CG_TIME].c_str());
        cgSetParameter1f(param, t);
    }
}

/*------------------------------ State ------------------------------------*/

void CGFXChunk::activate(DrawActionBase *action, UInt32 OSG_CHECK_ARG(idx))
{
    _action = action;

    //printf("CGFXChunk::activate\n");
    action->getWindow()->validateGLObject(getGLId());

    UInt32 id = action->getWindow()->getGLObjectId(getGLId());
    if(id == 0)
        return;

    if(id >= _effect.size())
    {
        FFATAL(("CGFXChunk::activate id (%u) >= effect size (%u)!\n", id, _effect.size()));
        return;
    }

    if(_effect[id].effect == NULL)
        return;

    if(_effect[id].pass == NULL)
    {
        // Set parameters
        updateStateParameters(action);

        // GL_ENABLE_BIT GL_LIGHTING_BIT
        // well that's not fast but safe.
        // ok man koennte die RenderAction so erweitern dass alle cgfx materialien
        // unter einer eigenen draw tree root gehaengt werden (wie trans root) dann
        // wird fuer alle cgfx materialien nur ein activate/deactivate aufgerufen der
        // rest waeren nur noch changeFrom.
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);

        //UInt32 numPasses;
        //_effect[id].effect->Begin(&numPasses, 0);
        _effect[id].pass = cgGetFirstPass(_effect[id].technique);
    
        //printf("activate %p %u: begin pass 0 from %u\n", this, id, numPasses);
    }

    // Setup the pass
    //printf("activate %p %u: rendering pass %u\n", this, id, _effect[id].pass);
    
    //_effect[id].effect->Pass(_effect[id].pass);
    //_effect[id].pass++;
    
    cgSetPassState(_effect[id].pass);
}

void CGFXChunk::changeFrom(DrawActionBase *action, StateChunk * old_chunk,
                                UInt32 OSG_CHECK_ARG(idx))
{
    _action = action;

    //printf("CGFXChunk::changeFrom\n");
    CGFXChunk *old = dynamic_cast<CGFXChunk *>(old_chunk);

    if(old == NULL)
    {
        FWARNING(( "CGFXChunk::changeFrom: caught non-CGFXChunk!\n"));
        return;
    }

    // same state as before we can't return here we have to set
    // the parameters for the right world matrix!
#if 0
    // CGFXChunk didn't change so do nothing.
    if(old == this)
        return;
#endif

    //printf("CGFXChunk::changeFrom\n");

    action->getWindow()->validateGLObject(getGLId());

    UInt32 oldid = action->getWindow()->getGLObjectId(old->getGLId());
    // now deactivate the old.
    if(oldid != 0)
    {
        if(old->_effect[oldid].effect != NULL)
        {
            if(old != this ||
               cgGetNextPass(old->_effect[oldid].pass) == NULL)
            {
                //printf("changeFrom %p %u: rendering end pass.\n", old, oldid);
                //old->_effect[oldid].effect->End();
                cgResetPassState(old->_effect[oldid].pass);
                old->_effect[oldid].pass = NULL;
            }
        }
    }

    UInt32 id = action->getWindow()->getGLObjectId(getGLId());

    if(id == 0)
        return;

    if(id >= _effect.size())
    {
        FFATAL(("CGFXChunk::changeFrom id (%u) >= effect size (%u)!\n", id, _effect.size()));
        return;
    }

    if(_effect[id].effect == NULL)
        return;

    if(_effect[id].pass == NULL)
    {
        // Set parameters
        updateStateParameters(action);
        
        //UInt32 numPasses;
        //_effect[id].effect->Begin(&numPasses, 0);
        //printf("changeFrom %p %u: begin pass 0 from %u\n", this, id, numPasses);

        _effect[id].pass = cgGetFirstPass(_effect[id].technique);
    }

    // Setup the pass
    //printf("changeFrom %p %u: rendering pass %u\n", this, id, _effect[id].pass);
    
    _effect[id].pass = cgGetNextPass(_effect[id].pass);
    cgSetPassState(_effect[id].pass);
}


void CGFXChunk::deactivate(DrawActionBase *action, UInt32 OSG_CHECK_ARG(idx))
{
    _action = action;

    //printf("CGFXChunk::deactivate\n");
    UInt32 id = action->getWindow()->getGLObjectId(getGLId());
    if(id == 0)
        return;

    if(id >= _effect.size())
    {
        FFATAL(("CGFXChunk::deactivate id (%u) >= effect size (%u)!\n", id, _effect.size()));
        return;
    }

    if(_effect[id].effect == NULL)
        return;

#if 0
    if(_effect[id].pass < getNPasses() - 1)
    {
        // deactivate was called to early just render the missing passes
        // to keep a valid opengl state.
        for(UInt32 i=_effect[id].pass;i<getNPasses();++i)
        {
            //printf("deactivate (fix) %p %u: rendering pass %u\n", this, id, i);
            _effect[id].effect->Pass(i);
        }
    }
#endif

    // End effect
    //printf("deactivate %p %u: rendering end pass.\n", this, id);

    //_effect[id].effect->End();
    //_effect[id].pass = 0;

    cgResetPassState(_effect[id].pass);
    _effect[id].pass = NULL;

    // restore opengl state.
    glPopClientAttrib();
    glPopAttrib();
}

bool CGFXChunk::isTransparent(void) const
{
    // HACK need to test this!
    return true;
    //return false;
}

UInt32 CGFXChunk::getNPasses(void)
{
    return _npasses;
}

/*-------------------------- Comparison -----------------------------------*/

Real32 CGFXChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

bool CGFXChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool CGFXChunk::operator == (const StateChunk &other) const
{
    CGFXChunk const *tother = dynamic_cast<CGFXChunk const*>(&other);

    if(!tother)
        return false;

    if(_effectFile != tother->_effectFile)
        return false;

    return true;
}

bool CGFXChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGCGFXChunk.cpp,v 1.3 2006/04/08 11:17:10 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGCGFXCHUNKBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCGFXCHUNKBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCGFXCHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif
