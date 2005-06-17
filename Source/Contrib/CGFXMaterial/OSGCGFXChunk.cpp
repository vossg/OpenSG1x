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
#include "CgFX/ICgFXEffect.h"

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

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CGFXChunk::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

CGFXChunk::EffectS::EffectS(void) :
    effect(NULL),
    pass(0)
{
}

void CGFXChunk::EffectS::reset(void)
{
    if(effect != NULL)
        effect->Release();
    effect = NULL;
    pass = 0;
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
#else
    if(cgfxPath != NULL)
        path_handler->push_backUnixPath(cgfxPath);
    path_handler->push_backUnixPath(".:../CgFX_textures:../textures/1D:../textures/2D:"
                                    "../textures/3D:../textures/cubemaps:"
                                    "../textures/rectangles:../default:../CgFX");
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
#else
    if(cgfxPath != NULL)
        path_handler->subUnixPath(cgfxPath);
    path_handler->subUnixPath(".:../CgFX_textures:../textures/1D:../textures/2D:"
                              "../textures/3D:../textures/cubemaps:"
                              "../textures/rectangles:../default:../CgFX");
#endif
}

void CGFXChunk::initCGFXGL(void)
{
    // ok I have to call this once before the Directory::setCurrent call,
    // without it can fail because on windows it won't find
    // the dynamicly loaded CgFXGL.dll anymore!
    if(!_initializedCGFXGL)
    {
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);
        // Set OpenGL device
        CgFXSetDevice("OpenGL", 0);
        glPopClientAttrib();
        glPopAttrib();
        _initializedCGFXGL = true;
    }
}

static Int32 totalDimension(UInt32 dim[])
{
    Int32 total = dim[0];
    
    for (Int32 i = 1; i < CGFX_MAX_DIMENSIONS; ++i)
    {
        if (dim[i] == 0)
        {
            break;
        }
    
        total *= dim[i];
    }
    
    return total;
}

void CGFXChunk::updateEffect(Window *win)
{
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

    ICgFXEffect *effect = NULL;


    initCGFXGL();

    // ----------------------

    //if(_cgfx_changed)
    {
        //printf("CGFXChunk : trying to load effect file: '%s'\n", _effectFile.c_str());
        //printf("CGFXChunk : trying to compile effect string\n");

        // Load new effect
        const char *errors = NULL;
        if(FAILED(CgFXCreateEffect(_effectString.c_str(), NULL, &effect, &errors)))
        {
            if(errors != NULL)
                FWARNING(("CGFXChunk : Cannot create effect: '%s'!\n", errors));
            return;
        }
    
        _effect[id].effect = effect;
        //printf("created new effect %u %p\n", id, effect);
    }
    // sometimes clone fails don't know why :-(
#if 0
    else
    {
        // search for the effect in the other context and clone it.
        for(UInt32 i=1;i<_effect.size();++i)
        {
            if(_effect[i].effect != NULL)
            {
                printf("cloning effect %u %p\n", i, _effect[i].effect);
                if(FAILED(_effect[i].effect->CloneEffect(&effect)))
                {
                    FWARNING(("CGFXChunk : Couldn't clone effect!\n"));
                    //Directory::setCurrent(old_current);
                    //delete [] old_current;
                    return;
                }
                printf("CGFXChunk: cloned effect for new context.\n");
                _effect[id].effect = effect;
                break;
            }
        }
    }
#endif

    // Get the effect description
    CgFXEFFECT_DESC effectDesc;
    if (FAILED(effect->GetDesc(&effectDesc)))
    {
        FWARNING(("CGFXChunk : Failed to get effect description!\n"));
        _effect[id].reset();
        return;
    }

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
    for (UInt32 i = 0; i < effectDesc.Parameters; ++i)
    {
        // Get parameter description
        CGFXHANDLE phandle = effect->GetParameter(NULL, i);
        CgFXPARAMETER_DESC param;
        if (FAILED(effect->GetParameterDesc(phandle, &param)))
            continue;

        UInt32 components = totalDimension(param.Dimension);

        HRESULT result;
        //printf("parameter: '%s' '%s'\n", param.Semantic, param.Name);
        // get tweakable parameters
        if(param.Annotations > 0) // tweakable parameters.
        {
            switch (param.Type)
            {
                case CgFXPT_BOOL:
                {
                    bool val;
                    if(!cgfxMat->getParameter(param.Name, val))
                    {
                        result = effect->GetBool(phandle, &val);
                        if(result == S_OK)
                        {
                            //printf("adding default parameter: '%s' (%d)\n", param.Name, val);
                            cgfxMat->setParameter(param.Name, val);
                        }
                    }
                    cgfxParameters.insert(param.Name);
                }
                break;
                
                case CgFXPT_INT:
                case CgFXPT_DWORD:
                {
                    Int32 val;
                    if(!cgfxMat->getParameter(param.Name, val))
                    {
                        result = effect->GetInt(phandle, &val);
                        if(result == S_OK)
                        {
                            //printf("adding default parameter: '%s' (%d)\n", param.Name, val);
                            cgfxMat->setParameter(param.Name, val);
                        }
                    }
                    cgfxParameters.insert(param.Name);
                }
                break;

                case CgFXPT_FLOAT:
                    switch(components)
                    {
                        case 1:
                        {
                            Real32 val;
                            if(!cgfxMat->getParameter(param.Name, val))
                            {
                                result = effect->GetFloat(phandle, &val);
                                if(result == S_OK)
                                {
                                    //printf("adding default parameter: '%s' (%f)\n", param.Name, val);
                                    cgfxMat->setParameter(param.Name, val);
                                }
                            }
                            cgfxParameters.insert(param.Name);
                        }
                        break;
                        case 2:
                        {
                            Vec2f val;
                            if(!cgfxMat->getParameter(param.Name, val))
                            {
                                result = effect->GetVector(phandle, val.getValues(), 2);
                                if(result == S_OK)
                                {
                                    //printf("adding default parameter: '%s' (%f, %f)\n", param.Name, val[0], val[1]);
                                    cgfxMat->setParameter(param.Name, val);
                                }
                            }
                            cgfxParameters.insert(param.Name);
                        }
                        break;
                        case 3:
                        {
                            Vec3f val;
                            if(!cgfxMat->getParameter(param.Name, val))
                            {
                                result = effect->GetVector(phandle, val.getValues(), 3);
                                if(result == S_OK)
                                {
                                    //printf("adding default parameter: '%s' (%f, %f, %f)\n", param.Name, val[0], val[1], val[2]);
                                    cgfxMat->setParameter(param.Name, val);
                                }
                            }
                            cgfxParameters.insert(param.Name);
                        }
                        break;
                        case 4:
                        {
                            Vec4f val;
                            if(!cgfxMat->getParameter(param.Name, val))
                            {
                                result = effect->GetVector(phandle, val.getValues(), 4);
                                if(result == S_OK)
                                {
                                    //printf("adding default parameter: '%s' (%f, %f, %f, %f)\n", param.Name, val[0], val[1], val[2], val[3]);
                                    cgfxMat->setParameter(param.Name, val);
                                }
                            }
                            cgfxParameters.insert(param.Name);
                        }
                        break;
                        case 16:
                        {
                            if (param.Dimension[0] == 4 &&
                                param.Dimension[1] == 4 &&
                                param.Dimension[2] == 0)
                            {
                                Matrix val;
                                if(!cgfxMat->getParameter(param.Name, val))
                                {
                                    result = effect->GetMatrix(phandle, val.getValues(), 4, 4);
                                    if(result == S_OK)
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
                                        cgfxMat->setParameter(param.Name, val);
                                    }
                                }
                                cgfxParameters.insert(param.Name);
                            }
                        }
                        break;
                    }
                break;
                case CgFXPT_STRING:
                {
                    std::string str;
                    if(!cgfxMat->getParameter(param.Name, str))
                    {
                        const char *val;
                        result = effect->GetString(phandle, &val);
                        if(result == S_OK)
                        {
                            //printf("adding default parameter: '%s' (%s)\n", param.Name, val);
                            cgfxMat->setParameter(param.Name, val);
                        }
                    }
                    cgfxParameters.insert(param.Name);
                }
                break;

                case CgFXPT_TEXTURE1D:
                case CgFXPT_TEXTURE2D:
                case CgFXPT_TEXTURERECT:
                case CgFXPT_TEXTURECUBE:
                case CgFXPT_TEXTURE3D:
                {
                    std::string filename;
                    if(!cgfxMat->getParameter(param.Name, filename))
                    {
                        // get texture filename
                        char *fname = NULL;
                        for (UInt32 j = 0; j < param.Annotations; ++j)
                        {
                            CGFXHANDLE ann = effect->GetAnnotation(effect->GetParameter(NULL, i), j);
                            CgFXPARAMETER_DESC annotation;
                            if (FAILED(effect->GetParameterDesc(ann, &annotation)))
                                continue;
            
                            if (strcmp(annotation.Name, "default") == 0 || 
                                strcmp(annotation.Name, "File") == 0)
                            {
                                effect->GetValue(ann, &fname, annotation.Bytes);
                                if(fname != NULL)
                                {
                                    filename = fname;
                                    //printf("adding default texture parameter: '%s' (%s)\n", param.Name, fname);
                                    cgfxMat->setParameter(param.Name, filename);
                                    break;
                                }
                            }
                        }
                    }

                    if(!filename.empty())
                    {
                        if(_cgfx_changed)
                        {
                            TextureChunkPtr texc = TextureChunk::create();
                            _textures.insert(std::make_pair(param.Name, std::make_pair(texc, filename)));
                        }
                        else
                        {
                            // just upload the texture for the new context.
                            TexturesMap::iterator it = _textures.find(param.Name);
                            if(it != _textures.end())
                            {
                                TextureChunkPtr texc = (*it).second.first;
                                texc->activate(_action, 0);
                                texc->deactivate(_action, 0);
                            }
                        }
                    }

                    cgfxParameters.insert(param.Name);
                }
                break;
                default:
                    FWARNING(("CGFXChunk : Unsupported parameter (%s) type (%d)!\n", param.Name, param.Type));
                break;
            }

            // now add the Annotation Attachment.

            // search for the parameter via name.
            ShaderParameterPtr sp = NullFC;
            for(UInt32 j=0;j<cgfxMat->getParameters().getSize();++j)
            {
                sp = cgfxMat->getParameters()[j];
                if(sp->getName() == param.Name)
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
                    for(UInt32 j = 0;j < param.Annotations;++j)
                    {
                        CGFXHANDLE ann = effect->GetAnnotation(phandle, j);
                        CgFXPARAMETER_DESC annotation;
                        if (FAILED(effect->GetParameterDesc(ann, &annotation)))
                            continue;
                        switch(annotation.Type)
                        {
                            case CgFXPT_INT:
                            case CgFXPT_DWORD:
                            {
                                Int32 val;
                                result = effect->GetInt(phandle, &val);
                                if(result == S_OK)
                                {
                                    //printf("\t '%s' (%d)\n", annotation.Name, val);
                                    ShaderParameterIntPtr p = ShaderParameterInt::create();
                                    beginEditCP(p);
                                        p->setName(annotation.Name);
                                        p->setValue(val);
                                    endEditCP(p);
                                    osgAnnotation->getParameters().push_back(p);
                                }
                            }
                            break;
                            case CgFXPT_FLOAT:
                            {
                                Real32 val;
                                result = effect->GetFloat(ann, &val);
                                if(result == S_OK)
                                {
                                    //printf("\t '%s' (%f)\n", annotation.Name, val);
                                    ShaderParameterRealPtr p = ShaderParameterReal::create();
                                    beginEditCP(p);
                                        p->setName(annotation.Name);
                                        p->setValue(val);
                                    endEditCP(p);
                                    osgAnnotation->getParameters().push_back(p);
                                }
                            }
                            break;
                            case CgFXPT_STRING:
                            {
                                const char *val;
                                result = effect->GetString(ann, &val);
                                if(result == S_OK)
                                {
                                    //printf("\t '%s' (%s)\n", annotation.Name, val);
                                    ShaderParameterStringPtr p = ShaderParameterString::create();
                                    beginEditCP(p);
                                        p->setName(annotation.Name);
                                        p->setValue(val);
                                    endEditCP(p);
                                    osgAnnotation->getParameters().push_back(p);
                                }
                            }
                            break;
                            default:
                               FWARNING(("CGFXChunk : Unsupported annotation (%s) type (%d)!\n", annotation.Name, annotation.Type));
                            break;
                        }
                    }
                endEditCP(osgAnnotation);

                // add the annotation attachment to the parameter.
                beginEditCP(sp, ShaderParameter::AttachmentsFieldMask);
                    sp->addAttachment(osgAnnotation);
                endEditCP(sp, ShaderParameter::AttachmentsFieldMask);
            }

        }
        else if (stringcasecmp(param.Semantic, "Projection") == 0)
            setStateParameter(CGFXChunk::OSG_CG_PROJECTION, param.Name);
        else if (stringcasecmp(param.Semantic, "WorldViewProjection") == 0)
            setStateParameter(CGFXChunk::OSG_CG_WORLDVIEWPROJECTION, param.Name);
        else if (stringcasecmp(param.Semantic, "World") == 0)
            setStateParameter(CGFXChunk::OSG_CG_WORLD, param.Name);
        else if (stringcasecmp(param.Semantic, "WorldI") == 0)
            setStateParameter(CGFXChunk::OSG_CG_WORLDI, param.Name);
        else if (stringcasecmp(param.Semantic, "WorldIT") == 0)
            setStateParameter(CGFXChunk::OSG_CG_WORLDIT, param.Name);
        else if (stringcasecmp(param.Semantic, "WorldView") == 0)
            setStateParameter(CGFXChunk::OSG_CG_WORLDVIEW, param.Name);
        else if (stringcasecmp(param.Semantic, "WorldViewI") == 0)
            setStateParameter(CGFXChunk::OSG_CG_WORLDVIEWI, param.Name);
        else if (stringcasecmp(param.Semantic, "View") == 0)
            setStateParameter(CGFXChunk::OSG_CG_VIEW, param.Name);
        else if (stringcasecmp(param.Semantic, "ViewI") == 0)
            setStateParameter(CGFXChunk::OSG_CG_VIEWI, param.Name);
         else if (stringcasecmp(param.Semantic, "ViewIT") == 0)
            setStateParameter(CGFXChunk::OSG_CG_VIEWIT, param.Name);
    }
    endEditCP(cgfxMat, CGFXMaterial::ParametersFieldMask);

    // remove non existing parameters this happens if you load a osb file
    // with a cgfx material and its parameters and then just load another
    // cgfx file.
    std::vector<std::string> remove_params;
    for(UInt32 i=0;i<cgfxMat->getParameters().size();++i)
    {
        // we can remove the directly in here with subParameter()!
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
    UInt32 id = win->getGLObjectId(getGLId());
    if(id == 0)
        return;

    ICgFXEffect *effect = _effect[id].effect;
    
    if(effect == NULL)
        return;

    CGFXMaterialPtr cgfxMat = CGFXMaterialPtr::dcast(_parentMat);
    MFShaderParameterPtr parameters = cgfxMat->getParameters();

    for(UInt32 i = 0; i < parameters.size(); ++i)
    {
        ShaderParameterPtr parameter = parameters[i];

        CGFXHANDLE ph = effect->GetParameterByName(NULL, parameter->getName().c_str());

        if(ph == NULL)
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
                effect->SetBool(ph, p->getValue());
            }
            break;
            case ShaderParameter::SHPTypeInt:
            {
                ShaderParameterIntPtr p = ShaderParameterIntPtr::dcast(parameter);
                effect->SetInt(ph, p->getValue());
            }
            break;
            case ShaderParameter::SHPTypeReal:
            {
                ShaderParameterRealPtr p = ShaderParameterRealPtr::dcast(parameter);
                effect->SetFloat(ph, p->getValue());
            }
            break;
            case ShaderParameter::SHPTypeVec2f:
            {
                ShaderParameterVec2fPtr p = ShaderParameterVec2fPtr::dcast(parameter);
                effect->SetVector(ph, p->getValue().getValues(), 2);
            }
            break;
            case ShaderParameter::SHPTypeVec3f:
            {
                ShaderParameterVec3fPtr p = ShaderParameterVec3fPtr::dcast(parameter);
                effect->SetVector(ph, p->getValue().getValues(), 3);
            }
            break;
            case ShaderParameter::SHPTypeVec4f:
            {
                ShaderParameterVec4fPtr p = ShaderParameterVec4fPtr::dcast(parameter);
                effect->SetVector(ph, p->getValue().getValues(), 4);
            }
            break;
            case ShaderParameter::SHPTypeMatrix:
            {
                ShaderParameterMatrixPtr p = ShaderParameterMatrixPtr::dcast(parameter);
                effect->SetMatrix(ph, p->getValue().getValues(), 4, 4);
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
                    
                    // now check if the image filename has changed or we need
                    // to create a image.
                    if(img == NullFC || filename != pfilename)
                    {
                        //printf("texture image filename changed '%s' == '%s' !!!\n",
                        //       filename.c_str(), pfilename.c_str());
                        
                        // ok now look in our own images list.

                        ImagePtr newimg = cgfxMat->findImage(pfilename);
                        if(newimg == NullFC)
                        {
                            // ok we got a new filename try to load it from disk
                            // store the index of the old image.
                            Int32 oldindex = cgfxMat->findImage(img);

                            //printf("loading image '%s' from filesystem.\n", pfilename.c_str());
                            addTextureSearchPaths();
                            img = OSG::ImageFileHandler::the().read(pfilename.c_str());
                            subTextureSearchPaths();

                            if(img != NullFC)
                            {
                                beginEditCP(img);
                                    img->setName(pfilename.c_str());
                                endEditCP(img);

                                if(oldindex != -1)
                                {
                                    // replace new image with old image
                                    beginEditCP(cgfxMat, CGFXMaterial::ImagesFieldMask);
                                        cgfxMat->getImages()[oldindex] = img;
                                    endEditCP(cgfxMat, CGFXMaterial::ImagesFieldMask);
                                    // the texc->setImage(img) call will handle the ref counting and
                                    // free the old image.
                                }
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
                            endEditCP(texc);
                            
                            texc->activate(_action, 0);
                            texc->deactivate(_action, 0);
                        }
                    }

                    effect->SetTexture(ph, texc->getGLId());
                }
                else // a string
                {
                    effect->SetString(ph, p->getValue().c_str());
                }
            }
            break;
            default:
                FWARNING(("CGFXChunk : Parameter '%s' has unknown tpye %d!\n",
                          parameter->getName().c_str(), parameter->getTypeId()));
            break;
        }
    }
}

void CGFXChunk::setEffectFile(const std::string &effectFile)
{
    //printf("CGFXChunk::setEffectFile\n");
    _effectFile = effectFile;

    // now try to load the effect and the textures.

    ICgFXEffect *effect = NULL;
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

    // ok without setting the current path relative includes in the cgfx file
    // doesn't work!
    if(!Directory::setCurrent(path.c_str()))
        FWARNING(("CGFXChunk : Couldn't change dir to: '%s'!\n", path.c_str()));

    // ----------------------
    CGFXMaterialPtr cgfxMat = CGFXMaterialPtr::dcast(_parentMat);

    // create cgfx string.
    std::string effectString;
    if(!read(fullFilePath, effectString))
    {
        //FWARNING(("CGFXChunk : Couldn't read cgfx file '%s'!\n", effectFile.c_str()));
        Directory::setCurrent(old_current.c_str());
        return;
    }

    //printf("CGFXChunk : trying to load effect file: '%s'\n", _effectFile.c_str());

    // Load new effect
    const char *errors = NULL;
    if(FAILED(CgFXCreateEffectFromFileA(fullFilePath.c_str(), NULL, &effect, &errors)))
    {
        if(errors != NULL)
            FWARNING(("CGFXChunk : Cannot create effect: '%s'!\n", errors));
        if(effect != NULL)
            effect->Release();
        Directory::setCurrent(old_current.c_str());
        return;
    }

    // Get the effect description
    CgFXEFFECT_DESC effectDesc;
    if (FAILED(effect->GetDesc(&effectDesc)))
    {
        FWARNING(("CGFXChunk : Failed to get effect description!\n"));
        if(effect != NULL)
            effect->Release();
        Directory::setCurrent(old_current.c_str());
        return;
    }

    bool error = false;

    std::vector<ImagePtr> newimages;
    // get the texture parameters.
    for (UInt32 i = 0; i < effectDesc.Parameters; ++i)
    {
        // Get parameter description
        CGFXHANDLE phandle = effect->GetParameter(NULL, i);
        CgFXPARAMETER_DESC param;
        if (FAILED(effect->GetParameterDesc(phandle, &param)))
            continue;

        HRESULT result;
        if(param.Annotations > 0) // tweakable parameters.
        {
            switch (param.Type)
            {
                case CgFXPT_TEXTURE1D:
                case CgFXPT_TEXTURE2D:
                case CgFXPT_TEXTURERECT:
                case CgFXPT_TEXTURECUBE:
                case CgFXPT_TEXTURE3D:
                {
                    std::string filename;
                    // get texture filename
                    char *fname = NULL;
                    for (UInt32 j = 0; j < param.Annotations; ++j)
                    {
                        CGFXHANDLE ann = effect->GetAnnotation(effect->GetParameter(NULL, i), j);
                        CgFXPARAMETER_DESC annotation;
                        if (FAILED(effect->GetParameterDesc(ann, &annotation)))
                            continue;
        
                        if (strcmp(annotation.Name, "default") == 0 || 
                            strcmp(annotation.Name, "File") == 0)
                        {
                            effect->GetValue(ann, &fname, annotation.Bytes);
                            if(fname != NULL)
                            {
                                addTextureSearchPaths();
                                ImagePtr img = OSG::ImageFileHandler::the().read(fname);
                                subTextureSearchPaths();
                                if(img != NullFC)
                                {
                                    beginEditCP(img);
                                        img->setName(fname);
                                    endEditCP(img);
                                    
                                    newimages.push_back(img);
                                    //printf("CGFXChunk::setEffectFile : created image with name '%s'.\n", fname);
                                }
                                else
                                {
                                    error = true;
                                }
                                break;
                            }
                        }
                    }
                }
                break;
                default:
                break;
            }
        }
    }

    Directory::setCurrent(old_current.c_str());

    if(effect != NULL)
        effect->Release();

    if(!error)
    {
        // ok only if we could load the cgfx file with all textures we update
        // everything.
        beginEditCP(cgfxMat, CGFXMaterial::EffectStringFieldMask |
                             CGFXMaterial::ImagesFieldMask);
            // clearing the list is enough the old images and textures
            // will be deleted in updateEffect
            cgfxMat->getImages().clear();
            for(UInt32 i=0;i<newimages.size();++i)
                cgfxMat->getImages().push_back(newimages[i]);
            cgfxMat->setEffectString(effectString);
        endEditCP(cgfxMat, CGFXMaterial::EffectStringFieldMask |
                           CGFXMaterial::ImagesFieldMask);
    }
    else
    {
        // ok something went wrong free the images and try to use the
        // cgfx effect in the effectString ...
        for(UInt32 i=0;i<newimages.size();++i)
            subRefCP(newimages[i]);
        //printf("CGFXChunk::setEffectFile : got errors ignoring cgfx file.\n");
    }
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

    ICgFXEffect *effect = _effect[1].effect;

    if(effect == NULL)
        return "";

    // Get the effect description
    CgFXEFFECT_DESC effectDesc;
    if(FAILED(effect->GetDesc(&effectDesc)))
        return "";

    Int32 techniqueNum = effectDesc.Techniques;

    if(index >= techniqueNum)
        return "";

    CGFXHANDLE technique = effect->GetTechnique(index);
    CgFXTECHNIQUE_DESC technique_desc;
    if(FAILED(effect->GetTechniqueDesc(technique, &technique_desc)))
        return "";

    return technique_desc.Name;
}

bool CGFXChunk::updateTechnique(Window *win, ICgFXEffect *effect)
{
    if(effect == NULL)
    {
        UInt32 id = win->getGLObjectId(getGLId());
        if(id == 0)
            return false;
    
        effect = _effect[id].effect;
    }

    if(effect == NULL)
        return false;

    // Get the effect description
    CgFXEFFECT_DESC effectDesc;
    if (FAILED(effect->GetDesc(&effectDesc)))
    {
        FWARNING(("CGFXChunk : Failed to get effect description!\n"));
        return false;
    }
    
    // Search for valid techniques and chooses one
    bool techniqueIsValid[EFFECT_TECHNIQUE_NUM_MAX];
    Int32 techniqueNum;
    Int32 currentTechnique;

    techniqueNum = effectDesc.Techniques;
    currentTechnique = -1;

    if(_technique >= techniqueNum)
        _technique = techniqueNum;

    for(Int32 t = 0; t < techniqueNum; ++t)
    {
        currentTechnique = t;
        //printf("setting technique %d %d\n", t, _technique);
        // Set technique
        if(FAILED(effect->SetTechnique(effect->GetTechnique(t))))
        {
            const char *errstr = NULL;
            if (FAILED(CgFXGetErrors(&errstr)))
            {
                FWARNING(("CGFXChunk : Failed to set technique (unknown error)!\n"));
            }
            else
            {
                FWARNING(("CGFXChunk : Failed to set technique (%s)!\n", errstr));
            }
            continue;
        }

        // Validate the technique
        if(!FAILED(effect->ValidateTechnique(effect->GetCurrentTechnique())))
        {
            currentTechnique = t;
            // if _technique is -1 use the first valid technique.
            if(_technique == -1)
                break;
            if(_technique == currentTechnique)
                break;
        }
    }

    // Leave if there is no valid technique
    if(currentTechnique < 0)
    {
        FWARNING(("CGFXChunk : Couldn't find a valid technique!\n"));
        return false;
    }
    else
    {
        effect->ValidateTechnique(effect->GetCurrentTechnique());
    }

    // get number of passes.
    CgFXTECHNIQUE_DESC techniqueDesc;
    if(FAILED(effect->GetTechniqueDesc(effect->GetCurrentTechnique(), &techniqueDesc)))
    {
        FWARNING(("CGFXChunk : Failed to get technique description!\n"));
        return false;
    }
    else
    {
        _npasses = techniqueDesc.Passes;
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
        _effect[id].effect->SetMatrix(_effect[id].effect->GetParameterByName(NULL,
            _state_parameters[OSG_CG_PROJECTION].c_str()), m.getValues(), 4, 4);
    }

    if(!_state_parameters[OSG_CG_WORLDVIEWPROJECTION].empty())
    {
        m = projection;
        m.mult(translation);
        m.mult(viewing);
        m.mult(world);
        m.transpose();
        _effect[id].effect->SetMatrix(_effect[id].effect->GetParameterByName(NULL,
            _state_parameters[OSG_CG_WORLDVIEWPROJECTION].c_str()), m.getValues(), 4, 4);
    }

    if(!_state_parameters[OSG_CG_WORLD].empty())
    {
        m = world;
        m.transpose();
        _effect[id].effect->SetMatrix(_effect[id].effect->GetParameterByName(NULL,
            _state_parameters[OSG_CG_WORLD].c_str()), m.getValues(), 4, 4);
    }

    if(!_state_parameters[OSG_CG_WORLDI].empty())
    {
        m = world;
        m.invert();
        m.transpose();
        _effect[id].effect->SetMatrix(_effect[id].effect->GetParameterByName(NULL,
            _state_parameters[OSG_CG_WORLDI].c_str()), m.getValues(), 4, 4);
    }

    if(!_state_parameters[OSG_CG_WORLDIT].empty())
    {
        m = world;
        m.invert();
        _effect[id].effect->SetMatrix(_effect[id].effect->GetParameterByName(NULL,
            _state_parameters[OSG_CG_WORLDIT].c_str()), m.getValues(), 4, 4);
    }

    if(!_state_parameters[OSG_CG_WORLDVIEW].empty())
    {
        m = viewing;
        m.mult(world);
        m.transpose();
        _effect[id].effect->SetMatrix(_effect[id].effect->GetParameterByName(NULL,
            _state_parameters[OSG_CG_WORLDVIEW].c_str()), m.getValues(), 4, 4);
    }
    
    if(!_state_parameters[OSG_CG_WORLDVIEWI].empty())
    {
        m = viewing;
        m.mult(world);
        m.invert();
        m.transpose();
        _effect[id].effect->SetMatrix(_effect[id].effect->GetParameterByName(NULL,
            _state_parameters[OSG_CG_WORLDVIEWI].c_str()), m.getValues(), 4, 4);
    }
    
    if(!_state_parameters[OSG_CG_VIEW].empty())
    {
        m = viewing;
        m.transpose();
        _effect[id].effect->SetMatrix(_effect[id].effect->GetParameterByName(NULL,
            _state_parameters[OSG_CG_VIEW].c_str()), m.getValues(), 4, 4);
    }

    if(!_state_parameters[OSG_CG_VIEWI].empty())
    {
        m = viewingI;
        m.transpose();
        _effect[id].effect->SetMatrix(_effect[id].effect->GetParameterByName(NULL,
            _state_parameters[OSG_CG_VIEWI].c_str()), m.getValues(), 4, 4);
    }

    if(!_state_parameters[OSG_CG_VIEWIT].empty())
    {
        m = viewingI;
        _effect[id].effect->SetMatrix(_effect[id].effect->GetParameterByName(NULL,
            _state_parameters[OSG_CG_VIEWIT].c_str()), m.getValues(), 4, 4);
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

    if(_effect[id].effect == NULL)
        return;

    if(_effect[id].pass == 0)
    {
        // GL_ENABLE_BIT GL_LIGHTING_BIT
        // well that's not fast but safe.
        // ok man koennte die RenderAction so erweitern dass alle cgfx materialien
        // unter einer eigenen draw tree root gehaengt werden (wie trans root) dann
        // wird fuer alle cgfx materialien nur ein activate/deactivate aufgerufen der
        // rest waeren nur noch changeFrom.
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);

        UInt32 numPasses;
        _effect[id].effect->Begin(&numPasses, 0);
        //printf("activate %p %u: begin pass 0 from %u\n", this, id, numPasses);

        // Set parameters
        updateStateParameters(action);
    }

    // Setup the pass
    //printf("activate %p %u: rendering pass %u\n", this, id, _effect[id].pass);
    _effect[id].effect->Pass(_effect[id].pass);
    _effect[id].pass++;
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
               old->_effect[oldid].pass >= old->getNPasses())
            {
                //printf("changeFrom %p %u: rendering end pass.\n", old, oldid);
                old->_effect[oldid].effect->End();
                old->_effect[oldid].pass = 0;
            }
        }
    }

    UInt32 id = action->getWindow()->getGLObjectId(getGLId());

    if(id == 0)
        return;

    if(_effect[id].effect == NULL)
        return;

    if(_effect[id].pass == 0)
    {
        UInt32 numPasses;
        _effect[id].effect->Begin(&numPasses, 0);
        //printf("changeFrom %p %u: begin pass 0 from %u\n", this, id, numPasses);
    
        // Set parameters
        updateStateParameters(action);
    }

    // Setup the pass
    //printf("changeFrom %p %u: rendering pass %u\n", this, id, _effect[id].pass);
    _effect[id].effect->Pass(_effect[id].pass);
    _effect[id].pass++;
}


void CGFXChunk::deactivate(DrawActionBase *action, UInt32 OSG_CHECK_ARG(idx))
{
    _action = action;

    //printf("CGFXChunk::deactivate\n");
    UInt32 id = action->getWindow()->getGLObjectId(getGLId());
    if(id == 0)
        return;

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
    _effect[id].effect->End();
    _effect[id].pass = 0;

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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGCGFXChunk.cpp,v 1.3 2005/06/17 15:13:38 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGCGFXCHUNKBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCGFXCHUNKBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCGFXCHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif
