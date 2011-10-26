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
#ifdef OSG_LINUX_TYPES
#include <inttypes.h>
#endif
#include <stdlib.h>
#include <stdio.h>

#include <set>

// CgFX

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

#include <Cg/cg.h>
#include <Cg/cgGL.h>
#if CG_VERSION_NUM < 1500
#error CGFXMaterial2 needs Cg 1.5 or later
#endif

#include "OSGCGFXChunk.h"
#include "OSGCGFXMaterial.h"
#include "OSGCGFXAnnotation.h"

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

//bool CGFXChunk::_initializedCGFXGL = false;
Real64  CGFXChunk::_time = -1.0;

CGFXChunk::parametercbfp CGFXChunk::_userParametersCallback = NULL;

std::map< CGFXChunk::OSGCGcontext, CGFXChunk* > CGFXChunk::_includeCallbackInstances;

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

void CGFXChunk::cgIncludeCallback( OSGCGcontext context, const char* filename )
{
    FDEBUG(("CGFXChunk: executing callback for include: %s\n", filename));
    std::map< OSGCGcontext, CGFXChunk* >::iterator iter =
        _includeCallbackInstances.find( (OSGCGcontext)context );
    if( iter != _includeCallbackInstances.end() )
        iter->second->processIncludeCallback( (OSGCGcontext)context, filename );
    else
        FWARNING(("CGFXChunk: received CGcompilerIncludeCallback for unregistered CGcontext (for file '%s').\n", filename));
}

void CGFXChunk::registerIncludeCallback( OSGCGcontext context, CGFXChunk* chunk )
{
    // THINKABOUTME: will this leak?
    static Lock* lock = Lock::create();

    // NOTE: This map will only grow in size, since there is no
    //       unregister function. However, this is not as bad
    //       as it seems, since cg will reuse context ids and
    //       CGFXChunk makes sure all entries with _valid_
    //       contexts point to the correct chunk. (For invalid
    //       contexts the cg runtime will never issue a callback.)
    lock->aquire();
    _includeCallbackInstances[context] = chunk;
    lock->release();
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
    technique(NULL),
    pass(NULL)
{
}

void CGFXChunk::EffectS::reset(void)
{
    if(effect != NULL)
        cgDestroyEffect((CGeffect) effect);
    effect = NULL;
    if(context != NULL)
        cgDestroyContext((CGcontext) context);
    context = NULL;
    pass = NULL;
    technique = NULL;
}

/*----------------------- constructors & destructors ----------------------*/

CGFXChunk::CGFXChunk(void) :
    Inherited(),
    _effect(),
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

    if(getGLId() > 0)
        Window::destroyGLObject(getGLId(), 1);

    //_effectParameters.clear();
    //_interfaceMappings.clear();
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

void CGFXChunk::processIncludeCallback( OSGCGcontext context, const char* filename )
{
#if CG_VERSION_NUM >= 2100
    CGFXMaterialPtr cgfxMat = CGFXMaterialPtr::dcast(_parentMat);
    OSG_ASSERT( cgfxMat != NullFC );

    std::string filecontent;
    if( cgfxMat->requestVirtualIncludeFile( filename, filecontent ) )
        cgSetCompilerIncludeString( (CGcontext)context, filename, filecontent.c_str() );
    //else
    //    FWARNING(("CGFXChunk: virtual include file for file '%s' not set.\n", filename));
#else
    context; filename;
#endif
}



void CGFXChunk::notifyParametersChanged()
{
    CGFXMaterialPtr cgfxMat = CGFXMaterialPtr::dcast(_parentMat);
    OSG_ASSERT( cgfxMat != NullFC );
    bool interfaceChanged = false;
    // check interfaceMappings if interface has changed
    for( Dictionary::const_iterator iter = _interfaceImplTypes.begin();
        iter != _interfaceImplTypes.end();
        ++iter )
    {
        std::string newValue;
        cgfxMat->getParameter( iter->first.c_str(), newValue );
        if( newValue != iter->second )
            interfaceChanged = true;
    }

    if( interfaceChanged )
    {
        Window::reinitializeGLObject(getGLId());
    }
    else
    {
        Window::refreshGLObject(getGLId());
    }
}

// little helper to replace sequences in parameter names
// (needed to map interfaces to concrete params)
template< class T >
static inline
bool findandreplace( T& source, const T& find, const T& replace )
{
    bool replaced = false;
    size_t j;
    for (;(j = source.find( find )) != T::npos;)
    {
        source.replace( j, find.length(), replace );
        replaced = true;
    }

    return replaced;
}

void CGFXChunk::extractParametersRecursiveHelper(
    const OSGCGparameter &firstParam,
    EffectS& effect,
    Dictionary& interfaceNameMappings
    )
{
    CGFXMaterialPtr cgfxMat = CGFXMaterialPtr::dcast(_parentMat);
    OSG_ASSERT( cgfxMat != NullFC );
    CGparameter param = (CGparameter)( firstParam );
    while(param)
    {
        UInt32 nrows = cgGetParameterRows(param);
        UInt32 ncols = cgGetParameterColumns(param);
        UInt32 components = nrows * ncols;

        std::string paramName = cgGetParameterName(param) ? cgGetParameterName(param) : "";
        std::string paramSemantic = cgGetParameterSemantic(param) ? cgGetParameterSemantic(param) : "";
        CGtype paramType = cgGetParameterType(param);
//		CGtype paramBaseType = cgGetParameterBaseType(param);

        // save cg internal name like '$G_1_0$.position' and replace it with
        // parameter names like 'light.position'
        // interfaces need this
        std::string cgParamName = paramName;
        for( Dictionary::const_iterator iter = interfaceNameMappings.begin();
            iter != interfaceNameMappings.end();
            ++iter)
        {
            findandreplace( paramName, iter->first, iter->second );
        }

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
        else if (stringcasecmp(paramSemantic.c_str(), "WorldViewIT") == 0)
            setStateParameter(CGFXChunk::OSG_CG_WORLDVIEWIT, paramName);
        else if (stringcasecmp(paramSemantic.c_str(), "WorldViewInverseTranspose") == 0)
            setStateParameter(CGFXChunk::OSG_CG_WORLDVIEWIT, paramName);
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
        else if (stringcasecmp(paramSemantic.c_str(), "ViewProjection") == 0)
            setStateParameter(CGFXChunk::OSG_CG_VIEWPROJECTION, paramName);
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
                        // parameter not yet set.
                        // => first look for a tweakable File parameter in the sampler itself.
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
        
                        // ok, now look for a tweakable parameter in the texture parameter.
                        if(filename.empty())
                        {
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

                    TextureChunkPtr texc;
                    cgfxMat->getParameter( paramName.c_str(), texc );
                    if( !texc )
                    {
                        texc = TextureChunk::create();
                        cgfxMat->setParameter( paramName.c_str(), texc );
                    }

                    if( _action )
                    {
                        texc->activate(_action, 0);
                        texc->deactivate(_action, 0);
                    }
                }
                break;
                case CG_ARRAY:
                {
                    // THINKABOUTME: This is terribly inefficient for large arrays,
                    //               maybe use MFields for basic types...
                    //               Or better yet: cbuffers...
                    const int arrayDimension = cgGetArrayDimension( param );
                    for( int d=0; d<arrayDimension; ++d )
                    {
                        const int arraySize = cgGetArraySize( param, d );

                        for( int i=0; i<arraySize; ++i )
                        {
                            CGparameter elementParam = cgGetArrayParameter(param, i);
                            extractParametersRecursiveHelper(
                                (OSGCGparameter)elementParam, effect, interfaceNameMappings );
                        }
                    }
                }
                break;
                case CG_STRUCT:
                {
                    CGtype t = cgGetParameterNamedType( param );
                    if( cgIsInterfaceType( t ) )    // it is an interface
                    {
                        // first check if user has provided an implementing type
                        std::string implParamTypeName;
                        cgfxMat->getParameter( paramName.c_str(), implParamTypeName );
                        if( !implParamTypeName.empty() )
                        {
                            CGtype implType = cgGetNamedUserType( (CGeffect)effect.effect, implParamTypeName.c_str() );
                            if( cgIsParentType( t, implType ) )
                            {
                                CGparameter implParam = cgCreateParameter( (CGcontext)effect.context, implType );
                                std::string implParamName = cgGetParameterName( implParam );

                                _interfaceImplTypes.push_back(
                                    std::make_pair( paramName, implParamTypeName )
                                    );
                                interfaceNameMappings.push_back(
                                    std::make_pair( implParamName, paramName )
                                    );
                                
                                cgConnectParameter( implParam, param );
                                // recurse to add members of implParam (which is a struct)
                                extractParametersRecursiveHelper(
                                    (OSGCGparameter)implParam, effect, interfaceNameMappings );
                            }
                            else
                            {
                                FWARNING(("CGFXChunk : '%s' is not a valid implementation type for parameter '%s'. Ignoring parameter.\n",
                                    implParamTypeName.c_str(), paramName.c_str()));
                            }
                        }
                        else
                        {
                            FWARNING(("CGFXChunk : Couldn't retrieve implementation type of interface for parameter '%s'. (Did you forget to specify it in OSGCGFXMaterial?) Ignoring parameter.\n",
                                paramName.c_str()));
                        }
                    }
                    else    // => not an interface (so it's a struct)
                    {
                        // recursively unpack params
                        CGparameter firstMemberParam = cgGetFirstStructParameter( param );
                        extractParametersRecursiveHelper(
                            (OSGCGparameter)firstMemberParam, effect, interfaceNameMappings );
                    }

                }
                break;
                default:
                    FWARNING(("CGFXChunk : Unsupported parameter (%s) type (%d)!\n", paramName.c_str(), paramType));
                break;
            }

            if(cgGetFirstParameterAnnotation(param) != NULL) // tweakable parameters.
            {
                // now add the Annotation Attachment.
    
                // THINKABOUTME: Hmm, a bit inefficient...
                // search for the parameter via name.
                ShaderParameterPtr sp = NullFC;
                for(UInt32 j=0;j<cgfxMat->getMFParameters()->getSize();++j)
                {
                    sp = cgfxMat->getParameters(j);
                    if(sp->getName() == paramName)
                        break;
                }
                
                if(sp != NullFC)
                {
                    CGFXAnnotationPtr osgAnnotation = CGFXAnnotationPtr::dcast(sp->findAttachment(CGFXAnnotation::getClassType()));
    
                    if(osgAnnotation == NullFC)
                        osgAnnotation = CGFXAnnotation::create();
                    else
                        osgAnnotation->editMFParameters()->clear();
    
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
                                        osgAnnotation->editMFParameters()->push_back(p);
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
                                        osgAnnotation->editMFParameters()->push_back(p);
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
                                        osgAnnotation->editMFParameters()->push_back(p);
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
                                        osgAnnotation->editMFParameters()->push_back(p);
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
}
   
void CGFXChunk::prepareParameters()
{
    EffectS dummy;
    compileEffect( dummy );
    extractParametersOfEffect( dummy );
    updateImages();
}

void CGFXChunk::compileEffect( EffectS& effect )
{
    cgSetErrorCallback(cgErrorCallback);

    CGcontext context = cgCreateContext();
#if CG_VERSION_NUM >= 2100
    registerIncludeCallback( (OSGCGcontext)context, this );
    cgSetCompilerIncludeCallback( context, (CGIncludeCallbackFunc)cgIncludeCallback );
#endif

    cgGLSetManageTextureParameters(context, GL_TRUE);
    cgGLRegisterStates(context);

    CGeffect cgEffect = NULL;

    //printf("CGFXChunk : trying to load effect file: '%s'\n", _effectFile.c_str());
    //printf("CGFXChunk : trying to compile effect string\n");

    // Load new effect

    // THINKABOUTME: Is this thread save?
    const Char8 *savedWorkingDir = Directory::getCurrent();
    Directory::setCurrent( _effectFilePath.c_str() );

    // we have to transform _compilerOptions to an array of
    // const char* to feed it to cgCreateEffect
    std::vector<const char*> tmp( _compilerOptions.size() );
    for( int i=0;i<_compilerOptions.size(); ++i )
        tmp[i] = _compilerOptions[i].c_str();
    tmp.push_back( NULL );
    const char **rawP = &(tmp[0]);

//    cgSetAutoCompile( context, CG_COMPILE_MANUAL );
    cgEffect = cgCreateEffect(context, _effectString.c_str(), rawP);

    const char* lastListing = cgGetLastListing( context );
    if( lastListing )
        FWARNING(("CGFXChunk : Cg compiler complains:\n'%s'\n", lastListing));

    Directory::setCurrent( savedWorkingDir );
    delete [] savedWorkingDir;

    if(cgEffect == NULL)
    {
        FWARNING(("CGFXChunk : Couldn't create effect!\n"));
        cgDestroyContext(context);
        return;
    }

    effect.context = (OSGCGcontext) context;
    effect.effect = (OSGCGeffect) cgEffect;
    //printf("created new effect %u %p\n", id, effect);

    //if( cgGetError() != CG_NO_ERROR )
    //    FWARNING(("AHHHH!\n"));
}

void CGFXChunk::extractParametersOfEffect( EffectS& effect )
{
    // clear old parameter states.
    for(UInt32 i=0;i<_state_parameters.size();++i)
        _state_parameters[i] = "";

    CGFXMaterialPtr cgfxMat = CGFXMaterialPtr::dcast(_parentMat);

    beginEditCP(cgfxMat, CGFXMaterial::ParametersFieldMask);
    
    Dictionary interfaceNameMappings;
    CGparameter param = cgGetFirstEffectParameter( (CGeffect)effect.effect );
    extractParametersRecursiveHelper( (OSGCGparameter)param, effect, interfaceNameMappings );
    interfaceNameMappings.clear();

    endEditCP(cgfxMat, CGFXMaterial::ParametersFieldMask);
    
    // THINKABOUTME: What to do with now unused parameters??
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

    compileEffect( _effect[id] );
    extractParametersOfEffect( _effect[id] );
    
    if(!updateTechnique(win, (OSGCGeffect) _effect[id].effect))
    {
        FWARNING(("CGFXChunk : Couldn't find a valid technique!\n"));
        _effect[id].reset();
        return;
    }

    // ok effect is valid set id.
    win->setGLObjectId(getGLId(), id);
    //printf("updateEffect ready\n");
}

void CGFXChunk::setParentMaterial(const ChunkMaterialPtr &parentMat)
{
    _parentMat = parentMat;
}

void CGFXChunk::updateTextureParameter( ShaderParameterStringPtr parameter )
{
    TextureChunkPtr texc = TextureChunkPtr::dcast(
        parameter->findAttachment(TextureChunk::getClassType()));
    OSG_ASSERT( texc );

    ImagePtr img = texc->getImage();

    std::string oldname;
    if( img )
        oldname = img->getName();

    std::string newname = parameter->getValue();

#if 0
    std::string oldname2 = oldname;
    for(UInt32 i=0;i<oldname2.size();++i)
    {
        if(oldname2[i] == '\\')
            oldname2[i] = '/';
    }

    std::string newname2 = newname;
    for(UInt32 i=0;i<newname2.size();++i)
    {
        if(newname2[i] == '\\')
            newname2[i] = '/';
    }
#endif
    // now check if the image filename has changed or we need
    // to create a image.
    if( !newname.empty() )
    {
        if( img == NullFC || oldname != newname )
        {
            // filename changed or file was never loaded
            // => try to bind new image to chunk

            // first try our own images list.
            CGFXMaterialPtr cgfxMat = CGFXMaterialPtr::dcast(_parentMat);
            ImagePtr img = cgfxMat->findImage(newname);
            if(img == NullFC)
            {
                // image not found in list
                // => try to load it

                //printf("loading image '%s' from filesystem.\n", pfilename.c_str());
                addTextureSearchPaths();
                img = OSG::ImageFileHandler::the().read(newname.c_str());
                subTextureSearchPaths();

                if(img != NullFC)   // => file loaded
                {
                    // need to add some image conversion for hdr textures in
                    // CG_SAMPLERCUBE format. Actually convert the cross format
                    // in 6 images and add them as 6 sides to the image.
                    beginEditCP(img, Image::NameFieldMask);
                        img->setName(newname.c_str());
                    endEditCP(img, Image::NameFieldMask);

                    beginEditCP(cgfxMat, CGFXMaterial::ImagesFieldMask);
                        cgfxMat->addImage(img);
                    endEditCP(cgfxMat, CGFXMaterial::ImagesFieldMask);
                }
                else    // => loading failed
                {
                    FWARNING(("CGFXChunk: Couldn't load image file '%s' for parameter '%s'!\n",
                           newname.c_str(), parameter->getName().c_str()));
                }
            }

            // bind image to chunk
            // THINKABOUTME: reset chunk's state (or create new chunk)??
            beginEditCP(texc, TextureChunk::ImageFieldMask);
                texc->setImage(img);
            endEditCP(texc, TextureChunk::ImageFieldMask);
        }
        // else
        // filename not changed and image != null
        // => everything set up correctly
    }
    //else
    // new filename empty
    // => chunk is already set up correctly
    // (well, at least we're not responsible, but the user...)
}

void CGFXChunk::updateImages(void)
{
    CGFXMaterialPtr cgfxMat = CGFXMaterialPtr::dcast(_parentMat);
    const MFShaderParameterPtr parameters = *(cgfxMat->getMFParameters());
    for(UInt32 i = 0; i < parameters.size(); ++i)
    {
        ShaderParameterPtr parameter = parameters[i];
        if( parameter->getTypeId() == ShaderParameter::SHPTypeString )
        {
            ShaderParameterStringPtr p = ShaderParameterStringPtr::dcast(parameter);
            TextureChunkPtr texc = TextureChunkPtr::dcast(p->findAttachment(TextureChunk::getClassType()));
            if( texc )
            {
                updateTextureParameter( p );
            }
        }
    }
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

    CGeffect cgEffect = (CGeffect) _effect[id].effect;
//    CGcontext cgContext = (CGcontext) _effect[id].context;

    if(!cgEffect)
        return;

    CGFXMaterialPtr cgfxMat = CGFXMaterialPtr::dcast(_parentMat);
    const MFShaderParameterPtr parameters = *(cgfxMat->getMFParameters());

    for(UInt32 i = 0; i < parameters.size(); ++i)
    {
        ShaderParameterPtr parameter = parameters[i];

        std::string paramName = parameter->getName();
        std::string cgParamName = paramName;

        CGparameter param = cgGetNamedEffectParameter(cgEffect, paramName.c_str());

        if(param == NULL)
        {
            FWARNING(("CGFXChunk : Ignoring unknown parameter '%s' ('%s')!\n",
                      paramName.c_str(), cgParamName.c_str()
                      ));
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
                TextureChunkPtr texc = TextureChunkPtr::dcast(p->findAttachment(TextureChunk::getClassType()));
                if( texc )
                {
                    updateTextureParameter( p );

//                    if(_action != NULL)
//                    {
//                        texc->activate(_action, 0);
//                        texc->deactivate(_action, 0);
//                    }

//                    OSG_ASSERT(texc->getGLId());
//                    printf("gloid: %d, glid: %d\n",win->getGLObjectId(texc->getGLId()),texc->getGLId());
                    cgGLSetupSampler(param, win->getGLObjectId(texc->getGLId()));
                    cgGLSetTextureParameter(param, win->getGLObjectId(texc->getGLId()));
                }
                else // parameter is a string
                {
                    // structs are also added as string parameters,
                    // but we don't really want to set them.
                    if( cgGetParameterType( param ) != CG_STRUCT )
                        cgSetStringParameterValue(param, p->getValue().c_str());
                }
            }
            break;
            default:
                FWARNING(("CGFXChunk : Parameter '%s' has unknown type %d!\n",
                          parameter->getName().c_str(), parameter->getTypeId()));
            break;
        }
    }

    // THINKABOUTME: what to do with the image list?? (remove unused?)
    //               and what with the virtual include files?
}

void CGFXChunk::setEffectFile(const std::string &effectFile)
{
    //printf("CGFXChunk::setEffectFile\n");
    _effectFile = effectFile;
    
    if( _effectFile.empty() )
        return;

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
//    FWARNING(("CGFXChunk : effectFilePath is '%s'!\n", _effectFilePath.c_str()));
	

    // ok without setting the current path relative includes in the cgfx file
    // doesn't work!
    if(!Directory::setCurrent(path.c_str()))
        FWARNING(("CGFXChunk : Couldn't change dir to: '%s'!\n", path.c_str()));

    // ----------------------

    // create cgfx string.
    std::string effectString;
    if( !read(fullFilePath, effectString) )
    {
        FWARNING(("CGFXChunk : Couldn't read cgfx file '%s' in '%s'!\n", effectFile.c_str(), fullFilePath.c_str() ));
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

#if 0
    // parse the cgfx string for #include statements and inline the code.
    // NOTE: This processes commented #includes, too!
    //       Therefore I deffed it out. (ks)
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
#endif

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

    _technique = 0;
    Window::reinitializeGLObject(getGLId());
}

void CGFXChunk::setCompilerOptions(const std::vector<std::string> &compilerOptions)
{
    if(_compilerOptions == compilerOptions)
    {
        return;
    }

    _compilerOptions = compilerOptions;
    
    Window::reinitializeGLObject(getGLId());
}

void CGFXChunk::setTechnique(Int32 technique)
{
    if(_technique == technique)
        return;

    _technique = technique;

    Window::refreshGLObject(getGLId());
}

Int32 CGFXChunk::getTechniqueIndex(const std::string &name) const
{
    if(_effect.empty())
        return -1;

    CGeffect effect = (CGeffect) _effect[1].effect;

    if(effect == NULL)
        return -1;

    CGtechnique technique = cgGetNamedTechnique( effect, name.c_str() );
    CGtechnique t = cgGetFirstTechnique(effect);
    Int32 index = 0;
    while( technique != t && (t = cgGetNextTechnique(technique)) )
    {
        ++index;
    }

    if(technique == NULL)
        return -1;

    return index;
}

std::string CGFXChunk::getTechniqueString(Int32 index) const
{
    if(_effect.empty())
        return "";

    CGeffect effect = (CGeffect) _effect[1].effect;

    if(effect == NULL)
        return "";

    CGtechnique technique = cgGetFirstTechnique(effect);
    for(Int32 i=1;i<=index;++i)
        technique = cgGetNextTechnique(technique);

    if(technique == NULL)
        return "";

    return cgGetTechniqueName(technique);
}

bool CGFXChunk::updateTechnique(Window *win, OSGCGeffect effect)
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

    CGtechnique technique = cgGetFirstTechnique((CGeffect) effect);
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
    technique = cgGetFirstTechnique((CGeffect) effect);
    while(currentTechnique < _technique)
    {
        // THINKABOUTME: technique can become 0 here if _technique>numTech...
        technique = cgGetNextTechnique(technique);
        ++currentTechnique;
    }

    if(!cgIsTechniqueValidated(technique))
    {
        // ok techique is not valid try to find a valid one.
        currentTechnique = 0;
        technique = cgGetFirstTechnique((CGeffect) effect);
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
            _effect[i].technique = (OSGCGtechnique) technique;
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

void CGFXChunk::setStateParameter(UInt32 type, const std::string &parameterName)
{
    if(type >= CGFXChunk::OSG_CG_LAST)
    {
        FWARNING(("CGFXChunk::setStateParameter : parameter type (%u) out of range!\n", type));
        return;
    }

    _state_parameters[type] = parameterName;
}

void CGFXChunk::setParameterCallback(parametercbfp fp)
{
    _userParametersCallback = fp;
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

    if(_userParametersCallback != NULL)
        _userParametersCallback(action, _effect[id].effect);

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
        CGparameter param = cgGetNamedEffectParameter((CGeffect) _effect[id].effect,
                                _state_parameters[OSG_CG_PROJECTION].c_str());
        cgSetMatrixParameterfc(param, m.getValues());
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
        CGparameter param = cgGetNamedEffectParameter((CGeffect) _effect[id].effect,
                                _state_parameters[OSG_CG_WORLDVIEWPROJECTION].c_str());
        cgSetMatrixParameterfc(param, m.getValues());
    }

    if(!_state_parameters[OSG_CG_WORLD].empty())
    {
        m = world;
        CGparameter param = cgGetNamedEffectParameter((CGeffect) _effect[id].effect,
                                _state_parameters[OSG_CG_WORLD].c_str());
        cgSetMatrixParameterfc(param, m.getValues());
    }

    if(!_state_parameters[OSG_CG_WORLDI].empty())
    {
        m = world;
        m.invert();
        CGparameter param = cgGetNamedEffectParameter((CGeffect) _effect[id].effect,
                                _state_parameters[OSG_CG_WORLDI].c_str());
        cgSetMatrixParameterfc(param, m.getValues());
    }

    if(!_state_parameters[OSG_CG_WORLDIT].empty())
    {
        m = world;
        m.invert();
        m.transpose();
        CGparameter param = cgGetNamedEffectParameter((CGeffect) _effect[id].effect,
                                _state_parameters[OSG_CG_WORLDIT].c_str());
        cgSetMatrixParameterfc(param, m.getValues());
    }

    if(!_state_parameters[OSG_CG_WORLDVIEW].empty())
    {
        m = viewing;
        m.mult(world);
        CGparameter param = cgGetNamedEffectParameter((CGeffect) _effect[id].effect,
                                _state_parameters[OSG_CG_WORLDVIEW].c_str());
        cgSetMatrixParameterfc(param, m.getValues());
    }
    
    if(!_state_parameters[OSG_CG_WORLDVIEWI].empty())
    {
        m = viewing;
        m.mult(world);
        m.invert();
        CGparameter param = cgGetNamedEffectParameter((CGeffect) _effect[id].effect,
                                _state_parameters[OSG_CG_WORLDVIEWI].c_str());
        cgSetMatrixParameterfc(param, m.getValues());
    }

    if(!_state_parameters[OSG_CG_WORLDVIEWIT].empty())
    {
        m = viewing;
        m.mult(world);
        m.invert();
        m.transpose();
        CGparameter param = cgGetNamedEffectParameter((CGeffect) _effect[id].effect,
                                _state_parameters[OSG_CG_WORLDVIEWIT].c_str());
        cgSetMatrixParameterfc(param, m.getValues());
    }

    if(!_state_parameters[OSG_CG_VIEW].empty())
    {
        m = viewing;
        CGparameter param = cgGetNamedEffectParameter((CGeffect) _effect[id].effect,
                                _state_parameters[OSG_CG_VIEW].c_str());
        cgSetMatrixParameterfc(param, m.getValues());
    }

    if(!_state_parameters[OSG_CG_VIEWI].empty())
    {
        m = viewingI;
        CGparameter param = cgGetNamedEffectParameter((CGeffect) _effect[id].effect,
                                _state_parameters[OSG_CG_VIEWI].c_str());
        cgSetMatrixParameterfc(param, m.getValues());
    }

    if(!_state_parameters[OSG_CG_VIEWIT].empty())
    {
        m = viewingI;
        m.transpose();
        CGparameter param = cgGetNamedEffectParameter((CGeffect) _effect[id].effect,
                                _state_parameters[OSG_CG_VIEWIT].c_str());
        cgSetMatrixParameterfc(param, m.getValues());
    }

    if(!_state_parameters[OSG_CG_VIEWPROJECTION].empty())
    {
        m = projection;
        m.mult( viewing );
        CGparameter param = cgGetNamedEffectParameter((CGeffect) _effect[id].effect,
                                _state_parameters[OSG_CG_VIEWPROJECTION].c_str());
        cgSetMatrixParameterfc(param, m.getValues());
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
        CGparameter param = cgGetNamedEffectParameter((CGeffect) _effect[id].effect,
                                _state_parameters[OSG_CG_TIME].c_str());
        cgSetParameter1f(param, t);
    }
}

/*------------------------------ State ------------------------------------*/

void CGFXChunk::update(DrawActionBase *action)
{
    updateStateParameters(action);
}

// Another Hack to check whether GLids for texture parameters are
// still valid (and if not to update them).
void CGFXChunk::checkTextureIds(DrawActionBase *action, OSGCGeffect effect)
{
    CGeffect cgEffect = (CGeffect) effect;
    Window* win = action->getWindow();
    CGFXMaterialPtr cgfxMat = CGFXMaterialPtr::dcast(_parentMat);
    const MFShaderParameterPtr parameters = *(cgfxMat->getMFParameters());

    for(UInt32 i = 0; i < parameters.size(); ++i)
    {
        ShaderParameterPtr parameter = parameters[i];

        std::string paramName = parameter->getName();
        std::string cgParamName = paramName;

        CGparameter param = cgGetNamedEffectParameter(cgEffect, paramName.c_str());

        if(param != NULL && parameter->getTypeId() == ShaderParameter::SHPTypeString )
        {
                ShaderParameterStringPtr p = ShaderParameterStringPtr::dcast(parameter);
                TextureChunkPtr texc = TextureChunkPtr::dcast(p->findAttachment(TextureChunk::getClassType()));
                if( texc )
                {
    //                 updateTextureParameter( p );
//                    printf("1 gloid: %d, glid: %d\n",win->getGLObjectId(texc->getGLId()),texc->getGLId());
                    if(_action != NULL && win->getGLObjectId(texc->getGLId()) == 0 )
                    {
                        // THINKABOUTME: Hmm, this sucks, too.
                        texc->activate(_action, 0);
                        texc->deactivate(_action, 0);
                    }
                    //                    OSG_ASSERT(texc->getGLId());
//                    printf("2 gloid: %d, glid: %d\n",win->getGLObjectId(texc->getGLId()),texc->getGLId());
                    cgGLSetupSampler(param, win->getGLObjectId(texc->getGLId()));
                    cgGLSetTextureParameter(param, win->getGLObjectId(texc->getGLId()));
                }
        }
    }
}


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
        checkTextureIds(action,_effect[id].effect);

        // GL_ENABLE_BIT GL_LIGHTING_BIT
        // well that's not fast but safe.
        // ok man koennte die RenderAction so erweitern dass alle cgfx materialien
        // unter einer eigenen draw tree root gehaengt werden (wie trans root) dann
        // wird fuer alle cgfx materialien nur ein activate/deactivate aufgerufen der
        // rest waeren nur noch changeFrom.
//        glPushAttrib(GL_ALL_ATTRIB_BITS);
//        glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);

        //UInt32 numPasses;
        //_effect[id].effect->Begin(&numPasses, 0);
        _effect[id].pass = (OSGCGpass) cgGetFirstPass((CGtechnique) _effect[id].technique);
    
        //printf("activate %p %u: begin pass 0 from %u\n", this, id, numPasses);
    }

    // Setup the pass
    //printf("activate %p %u: rendering pass %u\n", this, id, _effect[id].pass);
    
    //_effect[id].effect->Pass(_effect[id].pass);
    //_effect[id].pass++;
    
    cgSetPassState((CGpass) _effect[id].pass);
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
               cgGetNextPass((CGpass) old->_effect[oldid].pass) == NULL)
            {
                //printf("changeFrom %p %u: rendering end pass.\n", old, oldid);
                //old->_effect[oldid].effect->End();
                cgResetPassState((CGpass) old->_effect[oldid].pass);
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

        _effect[id].pass = (OSGCGpass) cgGetFirstPass((CGtechnique) _effect[id].technique);
    }

    // Setup the pass
    //printf("changeFrom %p %u: rendering pass %u\n", this, id, _effect[id].pass);
    
    _effect[id].pass = (OSGCGpass) cgGetNextPass((CGpass) _effect[id].pass);
    cgSetPassState((CGpass) _effect[id].pass);
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

    cgResetPassState((CGpass) _effect[id].pass);
    _effect[id].pass = NULL;

    // restore opengl state.
    // This is needed, because OSG's default state differs somewhat from
    // OpenGL's (which is set by cgResetPassState()).
    // By calling this in deactivate we can deactivate the Chunk more cleanly
    // than with glPush/Pop.
    // Because Chunks are deactivated in the same order as they are activated,
    // CGFXChunk would push a state that was modified by other chunks and then
    // pop this state _after_ the other chunks had their deactivate, de facto
    // disabling the deactivate of the other chunks.
    {
        glDepthFunc( GL_LEQUAL );
        glEnable( GL_DEPTH_TEST );
        glEnable( GL_NORMALIZE );
        GLfloat nul[4]={0,0,0,0};
        glLightfv(GL_LIGHT0, GL_DIFFUSE, nul);
        glLightfv(GL_LIGHT0, GL_SPECULAR, nul);
    }

//    glPopClientAttrib();
//    glPopAttrib();
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGCGFXChunk.cpp,v 1.21 2011/10/26 07:57:54 macnihilist Exp $";
    static Char8 cvsid_hpp       [] = OSGCGFXCHUNKBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCGFXCHUNKBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCGFXCHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif
