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

#include <OSGGL.h>
#include <OSGGLU.h>
#include <OSGGLEXT.h>
#include <OSGRemoteAspect.h>
#include <OSGCamera.h>
#include <OSGViewport.h>
#include <OSGStereoCameraDecorator.h>
#include <OSGRenderAction.h>

#include <OSGShaderParameter.h>
#include <OSGShaderParameterBool.h>
#include <OSGShaderParameterInt.h>
#include <OSGShaderParameterReal.h>
#include <OSGShaderParameterVec2f.h>
#include <OSGShaderParameterVec3f.h>
#include <OSGShaderParameterVec4f.h>
#include <OSGShaderParameterMatrix.h>

#include "OSGSHLChunk.h"

OSG_USING_NAMESPACE

/*! \class osg::SHLChunk

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass SHLChunk::_class("SHL");

UInt32 SHLChunk::_shl_extension;
UInt32 SHLChunk::_cg_extension;

UInt32 SHLChunk::_funcCreateProgramObject = Window::invalidFunctionID;
UInt32 SHLChunk::_funcCreateShaderObject = Window::invalidFunctionID;
UInt32 SHLChunk::_funcDeleteObject = Window::invalidFunctionID;
UInt32 SHLChunk::_funcDetachObject = Window::invalidFunctionID;
UInt32 SHLChunk::_funcAttachObject = Window::invalidFunctionID;

UInt32 SHLChunk::_funcShaderSource = Window::invalidFunctionID;
UInt32 SHLChunk::_funcCompileShader = Window::invalidFunctionID;
UInt32 SHLChunk::_funcLinkProgram = Window::invalidFunctionID;
UInt32 SHLChunk::_funcGetInfoLog = Window::invalidFunctionID;
UInt32 SHLChunk::_funcUseProgramObject = Window::invalidFunctionID;

UInt32 SHLChunk::_funcGetObjectParameteriv = Window::invalidFunctionID;
UInt32 SHLChunk::_funcGetObjectParameterfv = Window::invalidFunctionID;
UInt32 SHLChunk::_funcGetUniformLocation = Window::invalidFunctionID;

UInt32 SHLChunk::_funcBindAttribLocation = Window::invalidFunctionID;
UInt32 SHLChunk::_funcGetAttribLocation = Window::invalidFunctionID;

UInt32 SHLChunk::_funcUniform1i = Window::invalidFunctionID;
UInt32 SHLChunk::_funcUniform2iv = Window::invalidFunctionID;
UInt32 SHLChunk::_funcUniform3iv = Window::invalidFunctionID;
UInt32 SHLChunk::_funcUniform4iv = Window::invalidFunctionID;

UInt32 SHLChunk::_funcUniform1f = Window::invalidFunctionID;
UInt32 SHLChunk::_funcUniform2fv = Window::invalidFunctionID;
UInt32 SHLChunk::_funcUniform3fv = Window::invalidFunctionID;
UInt32 SHLChunk::_funcUniform4fv = Window::invalidFunctionID;

UInt32 SHLChunk::_funcUniformMatrix4fv = Window::invalidFunctionID;

UInt32 SHLChunk::_funcGetUniformiv = Window::invalidFunctionID;
UInt32 SHLChunk::_funcGetUniformfv = Window::invalidFunctionID;

Int32 SHLChunk::_clusterId = -1;

SHLChunk::parametercbfp SHLChunk::_userParametersCallback = NULL;

// prototypes

typedef GLuint  (OSG_APIENTRY * OSGGLCREATEPROGRAMOBJECTARBPROC) (void);
typedef void    (OSG_APIENTRY * OSGGLDELETEOBJECTARBPROC) (GLuint obj);
typedef GLuint  (OSG_APIENTRY * OSGGLCREATESHADEROBJECTARBPROC) (GLenum shaderType);
typedef void    (OSG_APIENTRY * OSGGLSHADERSOURCEARBPROC) (GLuint shaderObj, GLsizei count, const char **strings, const GLint *length);
typedef void    (OSG_APIENTRY * OSGGLCOMPILESHADERARBPROC) (GLuint shaderObj);
typedef void    (OSG_APIENTRY * OSGGLGETOBJECTPARAMETERIVARBPROC) (GLuint obj, GLenum pname, GLint *params);
typedef void    (OSG_APIENTRY * OSGGLGETINFOLOGARBPROC) (GLuint obj,GLsizei maxLength, GLsizei *length, char *infoLog);
typedef void    (OSG_APIENTRY * OSGGLATTACHOBJECTARBPROC) (GLuint containerObj, GLuint obj);
typedef void    (OSG_APIENTRY * OSGGLLINKPROGRAMARBPROC) (GLuint programObj);
typedef void    (OSG_APIENTRY * OSGGLUSEPROGRAMOBJECTARBPROC) (GLuint programObj);

typedef GLint   (OSG_APIENTRY * OSGGLGETUNIFORMLOCATIONARBPROC) (GLuint programObj, const char *name);

typedef void   (OSG_APIENTRY * OSGGLUNIFORM1IARBPROC) (GLint location, GLint value);
typedef void   (OSG_APIENTRY * OSGGLUNIFORMIVARBPROC) (GLint location, GLsizei count, GLint *value);

typedef void   (OSG_APIENTRY * OSGGLUNIFORM1FARBPROC) (GLint location, GLfloat value);
typedef void   (OSG_APIENTRY * OSGGLUNIFORMFVARBPROC) (GLint location, GLsizei count, GLfloat *value);

typedef void   (OSG_APIENTRY * OSGGLUNIFORMMATRIXFVARBPROC) (GLint location, GLsizei count, GLboolean transpose, GLfloat *value);

typedef void   (OSG_APIENTRY * OSGGLGETUNIFORMFIARBPROC) (GLuint programObj, GLint location, GLint *value);
typedef void   (OSG_APIENTRY * OSGGLGETUNIFORMFVARBPROC) (GLuint programObj, GLint location, GLfloat *value);


/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SHLChunk::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SHLChunk::SHLChunk(void) :
    Inherited(),
    _osgParametersCallbacks(),
    _oldParameterSize(0),
    _userParameterCallbacks()
{
    _shl_extension = Window::registerExtension("GL_ARB_shading_language_100");
    _cg_extension = Window::registerExtension("GL_EXT_Cg_shader");

    _funcCreateProgramObject =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glCreateProgramObjectARB", 
                                  _shl_extension);

    _funcCreateShaderObject =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glCreateShaderObjectARB", 
                                  _shl_extension);
    _funcDeleteObject =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glDeleteObjectARB", 
                                  _shl_extension);
    
    _funcDetachObject =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glDetachObjectARB", 
                                  _shl_extension);
    
    _funcAttachObject =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glAttachObjectARB", 
                                  _shl_extension);

    _funcShaderSource =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glShaderSourceARB", 
                                  _shl_extension);
                                  
    _funcCompileShader =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glCompileShaderARB", 
                                  _shl_extension);
                                  
    _funcLinkProgram =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glLinkProgramARB", 
                                  _shl_extension);
                                  
    _funcGetInfoLog =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glGetInfoLogARB", 
                                  _shl_extension);
                                  
    _funcUseProgramObject =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glUseProgramObjectARB", 
                                  _shl_extension);
    
    _funcGetObjectParameteriv =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glGetObjectParameterivARB", 
                                  _shl_extension);

    _funcGetObjectParameterfv =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glGetObjectParameterfvARB", 
                                  _shl_extension);

    _funcGetUniformLocation =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glGetUniformLocationARB", 
                                  _shl_extension);
    
    _funcBindAttribLocation =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glBindAttribLocationARB", 
                                  _shl_extension);

    _funcGetAttribLocation =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glGetAttribLocationARB", 
                                  _shl_extension);
    
    _funcUniform1i =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glUniform1iARB", 
                                  _shl_extension);

    _funcUniform2iv =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glUniform2ivARB", 
                                  _shl_extension);
                                  
    _funcUniform3iv =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glUniform3ivARB", 
                                  _shl_extension);
                                  
    _funcUniform4iv =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glUniform4ivARB", 
                                  _shl_extension);

    _funcUniform1f =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glUniform1fARB", 
                                  _shl_extension);

    _funcUniform2fv =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glUniform2fvARB", 
                                  _shl_extension);

    _funcUniform3fv =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glUniform3fvARB", 
                                  _shl_extension);

    _funcUniform4fv =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glUniform4fvARB", 
                                  _shl_extension);

    _funcUniformMatrix4fv =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glUniformMatrix4fvARB", 
                                  _shl_extension);

    _funcGetUniformiv =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glGetUniformivARB", 
                                  _shl_extension);
    
    _funcGetUniformfv =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glGetUniformfvARB", 
                                  _shl_extension);
}

SHLChunk::SHLChunk(const SHLChunk &source) :
    Inherited(source),
    _osgParametersCallbacks(source._osgParametersCallbacks),
    _oldParameterSize(source._oldParameterSize),
    _userParameterCallbacks(source._userParameterCallbacks)
{
}

SHLChunk::~SHLChunk(void)
{
}

void SHLChunk::onCreate(const SHLChunk *source)
{
    Inherited::onCreate(source);

    // ignore prototypes.
    if(GlobalSystemState == Startup)
        return;

    // we need this for clustering without it handleGL is never called.
    RemoteAspect::addFieldFilter(SHLChunk::getClassType().getId(), SHLChunk::GLIdFieldMask);

    SHLChunkPtr tmpPtr(*this);
    beginEditCP(tmpPtr, SHLChunk::GLIdFieldMask);
        setGLId(Window::registerGLObject(osgTypedMethodVoidFunctor2ObjCPtrPtr<SHLChunkPtr,
                                         Window , UInt32>(tmpPtr, &SHLChunk::handleGL), 1));
    endEditCP(tmpPtr, SHLChunk::GLIdFieldMask);

    //printf("SHLChunk::onCreate : glId %u\n", getGLId());
}

void SHLChunk::onDestroy(void)
{
    Inherited::onDestroy();

    if(getGLId() > 0)
        Window::destroyGLObject(getGLId(), 1);
}

const StateChunkClass *SHLChunk::getClass(void) const
{
    return &_class;
}

/*----------------------------- class specific ----------------------------*/

void SHLChunk::changed(BitVector whichField, UInt32 origin)
{
    if((whichField & VertexProgramFieldMask) ||
       (whichField & FragmentProgramFieldMask) ||
       (whichField & CgFrontEndFieldMask))
    {
        Window::reinitializeGLObject(getGLId());
    }

    if(whichField & ParametersFieldMask)
    {
        Window::refreshGLObject(getGLId());
    }

    Inherited::changed(whichField, origin);
}

void SHLChunk::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SHLChunk NI" << std::endl;
}

/*! GL object handler
    create the program and destroy it
*/
void SHLChunk::handleGL(Window *win, UInt32 idstatus)
{
    Window::GLObjectStatusE mode;
    UInt32 id;

    Window::unpackIdStatus(idstatus, id, mode);

    if(!win->hasExtension(_shl_extension))
    {
        FWARNING(("OpenGL Shading Language is not supported, couldn't find extension 'GL_ARB_shading_language_100'!\n"));
        win->setGLObjectId(getGLId(), 0);
        return;
    }

    // BUG this is not called for every window!
    if(mode == Window::destroy)
    {
        // This is called after the destructor so getGLId() doesn't work anymore!
        //printf("Window::destroy: %p %u %x\n", win, id, win->getGLObjectId(id));
        GLuint program = (GLuint) win->getGLObjectId(id);
        if(program != 0)
        {
            // get "glDeleteObjectARB" function pointer
            OSGGLDELETEOBJECTARBPROC deleteObject = (OSGGLDELETEOBJECTARBPROC)
                win->getFunction(_funcDeleteObject);
            deleteObject(program);
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
            updateProgram(win);
        }

        updateParameters(win, getParameters(), true, true/*mode != Window::needrefresh*/);
    }
    else
    {
        SWARNING << "SHLChunk(" << this << "::handleGL: Illegal mode: "
             << mode << " for id " << id << std::endl;
    }
}

void SHLChunk::updateProgram(Window *win)
{
    //printf("SHLChunk::updateProgram glid %u\n", getGLId());

    // get "glCreateProgramObjectARB" function pointer
    OSGGLCREATEPROGRAMOBJECTARBPROC createProgramObject = (OSGGLCREATEPROGRAMOBJECTARBPROC)
        win->getFunction(_funcCreateProgramObject);

    // get "glDeleteObjectARB" function pointer
    OSGGLDELETEOBJECTARBPROC deleteObject = (OSGGLDELETEOBJECTARBPROC)
        win->getFunction(_funcDeleteObject);

    // get "glCreateShaderObjectARB" function pointer
    OSGGLCREATESHADEROBJECTARBPROC createShaderObject = (OSGGLCREATESHADEROBJECTARBPROC)
        win->getFunction(_funcCreateShaderObject);

    // get "glShaderSourceARB" function pointer
    OSGGLSHADERSOURCEARBPROC shaderSource = (OSGGLSHADERSOURCEARBPROC)
        win->getFunction(_funcShaderSource);

    // get "glCompileShaderARB" function pointer
    OSGGLCOMPILESHADERARBPROC compileShader = (OSGGLCOMPILESHADERARBPROC)
        win->getFunction(_funcCompileShader);

    // get "glGetObjectParameterivARB" function pointer
    OSGGLGETOBJECTPARAMETERIVARBPROC getObjectParameteriv = (OSGGLGETOBJECTPARAMETERIVARBPROC)
        win->getFunction(_funcGetObjectParameteriv);

    // get "glGetInfoLogARB" function pointer
    OSGGLGETINFOLOGARBPROC getInfoLog = (OSGGLGETINFOLOGARBPROC)
        win->getFunction(_funcGetInfoLog);

    // get "glAttachObjectARB" function pointer
    OSGGLATTACHOBJECTARBPROC attachObject = (OSGGLATTACHOBJECTARBPROC)
        win->getFunction(_funcAttachObject);

    // get "glLinkProgramARB" function pointer
    OSGGLLINKPROGRAMARBPROC linkProgram = (OSGGLLINKPROGRAMARBPROC)
        win->getFunction(_funcLinkProgram);

    // get "glUseProgramObjectARB" function pointer
    OSGGLUSEPROGRAMOBJECTARBPROC useProgramObject = (OSGGLUSEPROGRAMOBJECTARBPROC)
        win->getFunction(_funcUseProgramObject);

    GLuint program = (GLuint) win->getGLObjectId(getGLId());
    // delete old program.
    if(program != 0)
        deleteObject(program);
    program = createProgramObject();
    //printf("updateProgram create: %p %u %x\n", win, getGLId(), program);
    win->setGLObjectId(getGLId(), (UInt32) program);

    UInt32 vShader = 0;
    GLint has_vertex = 0;
    // reload programs
    if(!getVertexProgram().empty())
    {
        GLenum shader_type = GL_VERTEX_SHADER_ARB;
        if(getCgFrontEnd())
        {
            if(win->hasExtension(_cg_extension))
                shader_type = GL_CG_VERTEX_SHADER_EXT;
            else
                FWARNING(("EXT_Cg_shader extension not supported, using GLSL front end!\n"));
        }

        vShader = createShaderObject(shader_type);
        const char *source = getVertexProgram().c_str();
        shaderSource(vShader, 1, (const char **) &source, 0);

        int success = 0;
        compileShader(vShader);
        getObjectParameteriv(vShader, GL_OBJECT_COMPILE_STATUS_ARB, &has_vertex);
        
        if(has_vertex == 0)
        {
            char *debug;
            GLint debugLength;
            getObjectParameteriv(vShader, GL_OBJECT_INFO_LOG_LENGTH_ARB, &debugLength);
              
            debug = new char[debugLength];
            getInfoLog(vShader, debugLength, &debugLength, debug);
        
            FFATAL(("Couldn't compile vertex program!\n%s\n", debug));
            delete [] debug;
            deleteObject(vShader);
        }
    }

    UInt32 fShader = 0;
    GLint has_fragment = 0;
    if(!getFragmentProgram().empty())
    {
        GLenum shader_type = GL_FRAGMENT_SHADER_ARB;
        if(getCgFrontEnd())
        {
            if(win->hasExtension(_cg_extension))
                shader_type = GL_CG_FRAGMENT_SHADER_EXT;
            else
                FWARNING(("EXT_Cg_shader extension not supported, using GLSL front end!\n"));
        }

        fShader = createShaderObject(shader_type);
        const char *source = getFragmentProgram().c_str();
        shaderSource(fShader, 1, (const char **) &source, 0);

        compileShader(fShader);
        getObjectParameteriv(fShader, GL_OBJECT_COMPILE_STATUS_ARB, &has_fragment);
        
        if(has_fragment == 0)
        {
            char *debug;
            GLint debugLength;
            getObjectParameteriv(fShader, GL_OBJECT_INFO_LOG_LENGTH_ARB, &debugLength);
              
            debug = new char[debugLength];
            getInfoLog(fShader, debugLength, &debugLength, debug);
        
            FFATAL(("Couldn't compile fragment program!\n%s\n", debug));
            delete [] debug;
            deleteObject(fShader);
        }
    }

    if(has_vertex || has_fragment)
    {
        if(has_vertex)
        {
            attachObject(program, vShader);
            // just flagged for deletion
            deleteObject(vShader);
        }

        if(has_fragment)
        {
            attachObject(program, fShader);
            // just flagged for deletion
            deleteObject(fShader);
        }

        linkProgram(program);
        
        GLint success = 0;
        getObjectParameteriv(program, GL_OBJECT_LINK_STATUS_ARB, &success);
        char *debug = NULL;
        GLint debugLength;
        getObjectParameteriv(program, GL_OBJECT_INFO_LOG_LENGTH_ARB, &debugLength);
        if(debugLength > 0)
        {
            debug = new char[debugLength];
            debug[0] = 0;
            getInfoLog(program, debugLength, &debugLength, debug);
        }

        if(success)
        {
            if(debug != NULL && debug[0] != 0)
                FWARNING(("SHLChunk: link status: %s\n", debug));
        }
        else
        {
            if(debug != NULL && debug[0] != 0)
                FFATAL(("Couldn't link vertex and fragment program!\n%s\n", debug));
            deleteObject(program);
            win->setGLObjectId(getGLId(), 0);
        }
        if(debug != NULL)
            delete [] debug;
    }
    else
    {
        deleteObject(program);
        win->setGLObjectId(getGLId(), 0);
    }
    // update all parameters.
    updateParameters(win, getParameters());
}

void SHLChunk::updateParameters(Window *win,
                                const MFShaderParameterPtr &parameters,
                                bool useProgram, bool force,
                                bool keepProgramActive)
{
    GLuint program = (GLuint) win->getGLObjectId(getGLId());

    if(program == 0)
    {
        FNOTICE(("SHLChunk::updateParameters: program == 0!\n"
                 "This frame will probably be rendered wrong!\n"));
        return;
    }
    
    checkOSGParameters();

    if(parameters.empty())
        return;

    // get "glUseProgramObjectARB" function pointer
    OSGGLUSEPROGRAMOBJECTARBPROC useProgramObject = (OSGGLUSEPROGRAMOBJECTARBPROC)
        win->getFunction(_funcUseProgramObject);

    if(useProgram)
        useProgramObject(program);

    // get "glGetUniformLocationARB" function pointer
    OSGGLGETUNIFORMLOCATIONARBPROC getUniformLocation = (OSGGLGETUNIFORMLOCATIONARBPROC)
        win->getFunction(_funcGetUniformLocation);

    // just a example showing how to get parameter values.
#if 0
    // get "glGetUniformfvARB" function pointer
    OSGGLGETUNIFORMFVARBPROC getUniformfv = (OSGGLGETUNIFORMFVARBPROC)
        win->getFunction(_funcGetUniformfv);
    GLfloat values[2];
    getUniformfv(program, location, values);
#endif

    for(UInt32 i = 0; i < parameters.size(); ++i)
    {
        ShaderParameterPtr parameter = parameters[i];

        // ignore special osg parameters
        if(parameter->getName().size() > 3 &&
           parameter->getName()[0] == 'O' &&
           parameter->getName()[1] == 'S' &&
           parameter->getName()[2] == 'G')
        {
            continue;
        }
        
        // works also but is not possible with a switch and a switch is much faster.
        //UInt16 groupid = parameter->getType().getGroupId();
        //if(groupid == ShaderParameterInt::getClassType().getGroupId())
        
        if(!force)
        {
            if(!parameter->hasChanged())
                continue;
            parameter->resetChanged();
        }

        //printf("seeting parameter: '%s'\n", parameter->getName().c_str());

        switch(parameter->getTypeId())
        {
            case ShaderParameter::SHPTypeBool:
            {
                ShaderParameterBoolPtr p = ShaderParameterBoolPtr::dcast(parameter);
                // get "glUniform1iARB" function pointer
                OSGGLUNIFORM1IARBPROC uniform1i = (OSGGLUNIFORM1IARBPROC)
                    win->getFunction(_funcUniform1i);
    
                //printf("setting: %s %d\n", p->getName().c_str(), p->getValue());
                GLint location = getUniformLocation(program, p->getName().c_str());
                if(location != -1)
                    uniform1i(location, (GLint) p->getValue());
                else
                    FWARNING(("Unknown parameter '%s'!\n", p->getName().c_str()));
            }
            break;
            case ShaderParameter::SHPTypeInt:
            {
                ShaderParameterIntPtr p = ShaderParameterIntPtr::dcast(parameter);
                // get "glUniform1iARB" function pointer
                OSGGLUNIFORM1IARBPROC uniform1i = (OSGGLUNIFORM1IARBPROC)
                    win->getFunction(_funcUniform1i);
    
                //printf("setting: %s %d\n", p->getName().c_str(), p->getValue());
                GLint location = getUniformLocation(program, p->getName().c_str());
                if(location != -1)
                    uniform1i(location, p->getValue());
                else
                    FWARNING(("Unknown parameter '%s'!\n", p->getName().c_str()));
            }
            break;
            case ShaderParameter::SHPTypeReal:
            {
                ShaderParameterRealPtr p = ShaderParameterRealPtr::dcast(parameter);
                // get "glUniform1fARB" function pointer
                OSGGLUNIFORM1FARBPROC uniform1f = (OSGGLUNIFORM1FARBPROC)
                    win->getFunction(_funcUniform1f);

                //printf("setting: %s %f\n", p->getName().c_str(), p->getValue());
                GLint location = getUniformLocation(program, p->getName().c_str());
                if(location != -1)
                    uniform1f(location, p->getValue());
                else
                    FWARNING(("Unknown parameter '%s'!\n", p->getName().c_str()));
            }
            break;
            case ShaderParameter::SHPTypeVec2f:
            {
                ShaderParameterVec2fPtr p = ShaderParameterVec2fPtr::dcast(parameter);
                // get "glUniform2fvARB" function pointer
                OSGGLUNIFORMFVARBPROC uniform2fv = (OSGGLUNIFORMFVARBPROC)
                    win->getFunction(_funcUniform2fv);
    
                GLint location = getUniformLocation(program, p->getName().c_str());
                if(location != -1)
                    uniform2fv(location, 1, p->getValue().getValues());
                else
                    FWARNING(("Unknown parameter '%s'!\n", p->getName().c_str()));
            }
            break;
            case ShaderParameter::SHPTypeVec3f:
            {
                ShaderParameterVec3fPtr p = ShaderParameterVec3fPtr::dcast(parameter);
                // get "glUniform3fvARB" function pointer
                OSGGLUNIFORMFVARBPROC uniform3fv = (OSGGLUNIFORMFVARBPROC)
                    win->getFunction(_funcUniform3fv);
    
                GLint location = getUniformLocation(program, p->getName().c_str());
                if(location != -1)
                    uniform3fv(location, 1, p->getValue().getValues());
                else
                    FWARNING(("Unknown parameter '%s'!\n", p->getName().c_str()));
            }
            break;
            case ShaderParameter::SHPTypeVec4f:
            {
                ShaderParameterVec4fPtr p = ShaderParameterVec4fPtr::dcast(parameter);
                // get "glUniform4fvARB" function pointer
                OSGGLUNIFORMFVARBPROC uniform4fv = (OSGGLUNIFORMFVARBPROC)
                    win->getFunction(_funcUniform4fv);
    
                GLint location = getUniformLocation(program, p->getName().c_str());
                if(location != -1)
                    uniform4fv(location, 1, p->getValue().getValues());
                else
                    FWARNING(("Unknown parameter '%s'!\n", p->getName().c_str()));
            }
            break;
            case ShaderParameter::SHPTypeMatrix:
            {
                ShaderParameterMatrixPtr p = ShaderParameterMatrixPtr::dcast(parameter);
                // get "glUniformMatrix4fvARB" function pointer
                OSGGLUNIFORMMATRIXFVARBPROC uniformMatrix4fv = (OSGGLUNIFORMMATRIXFVARBPROC)
                    win->getFunction(_funcUniformMatrix4fv);
    
                GLint location = getUniformLocation(program, p->getName().c_str());
                if(location != -1)
                    uniformMatrix4fv(location, 1, GL_FALSE, p->getValue().getValues());
                else
                    FWARNING(("Unknown parameter '%s'!\n", p->getName().c_str()));
            }
            break;
            default:
                FWARNING(("Parameter '%s' has unknown tpye %d!\n", parameter->getName().c_str(),
                                                                   parameter->getTypeId()));
            break;
        }
    }

    if(useProgram && !keepProgramActive)
        useProgramObject(0);
}

void SHLChunk::checkOSGParameters(void)
{
    // ok this can go wrong if you sub and add a parameter
    // between one begin/endEditCP ...
    if(getParameters().getSize() == _oldParameterSize)
        return;
    _oldParameterSize = getParameters().getSize();

    _osgParametersCallbacks.clear();
    const MFShaderParameterPtr &parameters = getParameters();
    for(UInt32 i = 0; i < parameters.size(); ++i)
    {
        ShaderParameterPtr parameter = parameters[i];
        if(parameter->getName().size() > 3 &&
           parameter->getName()[0] == 'O' &&
           parameter->getName()[1] == 'S' &&
           parameter->getName()[2] == 'G')
        {
            if(parameter->getName() == "OSGWorldMatrix")
            {
                // .net compiler needs this workaround in opt mode ...
                parametercbfp fp = updateWorldMatrix;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGInvWorldMatrix")
            {
                // .net compiler needs this workaround in opt mode ...
                parametercbfp fp = updateInvWorldMatrix;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGCameraOrientation")
            {
                parametercbfp fp = updateCameraOrientation;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGCameraPosition")
            {
                parametercbfp fp = updateCameraPosition;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGViewMatrix")
            {
                parametercbfp fp = updateViewMatrix;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGInvViewMatrix")
            {
                parametercbfp fp = updateInvViewMatrix;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGStereoLeftEye")
            {
                parametercbfp fp = updateStereoLeftEye;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGClusterId")
            {
                parametercbfp fp = updateClusterId;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGActiveLightsMask")
            {
                parametercbfp fp = updateActiveLightsMask;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGLight0Active")
            {
                parametercbfp fp = updateLight0Active;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGLight1Active")
            {
                parametercbfp fp = updateLight1Active;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGLight2Active")
            {
                parametercbfp fp = updateLight2Active;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGLight3Active")
            {
                parametercbfp fp = updateLight3Active;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGLight4Active")
            {
                parametercbfp fp = updateLight4Active;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGLight5Active")
            {
                parametercbfp fp = updateLight5Active;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGLight6Active")
            {
                parametercbfp fp = updateLight6Active;
                _osgParametersCallbacks.push_back(fp);
            }
            else if(parameter->getName() == "OSGLight7Active")
            {
                parametercbfp fp = updateLight7Active;
                _osgParametersCallbacks.push_back(fp);
            }
            else
            {
                // check user parameter callbacks.
                userParameterCallbacksMap::iterator it =
                    _userParameterCallbacks.find(parameter->getName());
                if(it != _userParameterCallbacks.end())
                {
                    parametercbfp fp = (*it).second;
                    _osgParametersCallbacks.push_back(fp);
                }
                else
                {
                    FWARNING(("SHLChunk::checkOSGParameters : unknown osg parameter '%s'\n",
                              parameter->getName().c_str()));
                }
            }
        }
    }
}

void SHLChunk::addParameterCallback(const char *name, parametercbfp fp)
{
    if(name == NULL)
        return;

//    std::string szName(name);

    setUniformParameter(name, 0);
    _userParameterCallbacks.insert(std::make_pair<std::string, parametercbfp>(name, fp));
}

void SHLChunk::setParameterCallback(parametercbfp fp)
{
    _userParametersCallback = fp;
}

void SHLChunk::updateOSGParameters(DrawActionBase *action, GLuint program)
{
    // get "glGetUniformLocationARB" function pointer
    OSGGLGETUNIFORMLOCATIONARBPROC getUniformLocation = (OSGGLGETUNIFORMLOCATIONARBPROC)
        action->getWindow()->getFunction(_funcGetUniformLocation);

    if(_userParametersCallback != NULL)
        _userParametersCallback(getUniformLocation, action, program);

    if(_osgParametersCallbacks.empty())
        return;

    for(UInt32 i=0;i<_osgParametersCallbacks.size();++i)
        _osgParametersCallbacks[i](getUniformLocation, action, program);
}

void SHLChunk::updateWorldMatrix(OSGGLGETUNIFORMLOCATIONARBPROC getUniformLocation,
                                DrawActionBase *action, GLuint program)
{
    if(action->getCamera() == NULL || action->getViewport() == NULL)
    {
        FWARNING(("SHLChunk::updateWorldMatrix : Can't update OSGWorldMatrix"
                  "parameter, camera or viewport is NULL!\n"));
        return;
    }

    Matrix m;
    RenderAction *ra = dynamic_cast<RenderAction *>(action);
    if(ra != NULL)
        m = ra->top_matrix();

    // get "glUniformMatrix4fvARB" function pointer
    OSGGLUNIFORMMATRIXFVARBPROC uniformMatrix4fv = (OSGGLUNIFORMMATRIXFVARBPROC)
        action->getWindow()->getFunction(_funcUniformMatrix4fv);
    GLint location = getUniformLocation(program, "OSGWorldMatrix");
    if(location != -1)
        uniformMatrix4fv(location, 1, GL_FALSE, m.getValues());
}

void SHLChunk::updateInvWorldMatrix(OSGGLGETUNIFORMLOCATIONARBPROC getUniformLocation,
                                   DrawActionBase *action, GLuint program)
{
    if(action->getCamera() == NULL || action->getViewport() == NULL)
    {
        FWARNING(("SHLChunk::updateInvWorldMatrix : Can't update OSGInvWorldMatrix"
                  "parameter, camera or viewport is NULL!\n"));
        return;
    }

    Matrix m;
    RenderAction *ra = dynamic_cast<RenderAction *>(action);
    if(ra != NULL)
        m = ra->top_matrix();
    m.invert();

    // get "glUniformMatrix4fvARB" function pointer
    OSGGLUNIFORMMATRIXFVARBPROC uniformMatrix4fv = (OSGGLUNIFORMMATRIXFVARBPROC)
        action->getWindow()->getFunction(_funcUniformMatrix4fv);
    GLint location = getUniformLocation(program, "OSGInvWorldMatrix");
    if(location != -1)
        uniformMatrix4fv(location, 1, GL_FALSE, m.getValues());
}

void SHLChunk::updateCameraOrientation(OSGGLGETUNIFORMLOCATIONARBPROC getUniformLocation,
                                       DrawActionBase *action, GLuint program)
{
    if(action->getCamera() == NULL || action->getViewport() == NULL)
    {
        FWARNING(("SHLChunk::updateCameraOrientation : Can't update OSGCameraOrientation"
                  "parameter, camera or viewport is NULL!\n"));
        return;
    }

    Matrix m;
    action->getCamera()->getViewing(m,
                                action->getViewport()->getPixelWidth(),
                                action->getViewport()->getPixelHeight());
    m.invert();
    m[3].setValues(0, 0, 0, 1);

    // get "glUniformMatrix4fvARB" function pointer
    OSGGLUNIFORMMATRIXFVARBPROC uniformMatrix4fv = (OSGGLUNIFORMMATRIXFVARBPROC)
        action->getWindow()->getFunction(_funcUniformMatrix4fv);
    GLint location = getUniformLocation(program, "OSGCameraOrientation");
    if(location != -1)
        uniformMatrix4fv(location, 1, GL_FALSE, m.getValues());
}

void SHLChunk::updateCameraPosition(OSGGLGETUNIFORMLOCATIONARBPROC getUniformLocation,
                                    DrawActionBase *action, GLuint program)
{
    if(action->getCamera() == NULL || action->getViewport() == NULL)
    {
        FWARNING(("SHLChunk::updateCameraPosition : Can't update OSGCameraPosition"
                  "parameter, camera or viewport is NULL!\n"));
        return;
    }

    Matrix m;
    action->getCamera()->getViewing(m,
                                action->getViewport()->getPixelWidth(),
                                action->getViewport()->getPixelHeight());
    m.invert();
    Vec3f cameraPos(m[3][0], m[3][1], m[3][2]);

    // get "glUniform3fvARB" function pointer
    OSGGLUNIFORMFVARBPROC uniform3fv = (OSGGLUNIFORMFVARBPROC)
        action->getWindow()->getFunction(_funcUniform3fv);
    GLint location = getUniformLocation(program, "OSGCameraPosition");
    if(location != -1)
        uniform3fv(location, 1, cameraPos.getValues());
}

void SHLChunk::updateViewMatrix(OSGGLGETUNIFORMLOCATIONARBPROC getUniformLocation,
                                DrawActionBase *action, GLuint program)
{
    if(action->getCamera() == NULL || action->getViewport() == NULL)
    {
        FWARNING(("SHLChunk::updateViewMatrix : Can't update OSGViewMatrix"
                  "parameter, camera or viewport is NULL!\n"));
        return;
    }

    Matrix m;
    action->getCamera()->getViewing(m,
                                action->getViewport()->getPixelWidth(),
                                action->getViewport()->getPixelHeight());

    // get "glUniformMatrix4fvARB" function pointer
    OSGGLUNIFORMMATRIXFVARBPROC uniformMatrix4fv = (OSGGLUNIFORMMATRIXFVARBPROC)
        action->getWindow()->getFunction(_funcUniformMatrix4fv);
    GLint location = getUniformLocation(program, "OSGViewMatrix");
    if(location != -1)
        uniformMatrix4fv(location, 1, GL_FALSE, m.getValues());
}

void SHLChunk::updateInvViewMatrix(OSGGLGETUNIFORMLOCATIONARBPROC getUniformLocation,
                                   DrawActionBase *action, GLuint program)
{
    if(action->getCamera() == NULL || action->getViewport() == NULL)
    {
        FWARNING(("SHLChunk::updateInvViewMatrix : Can't update OSGInvViewMatrix"
                  "parameter, camera or viewport is NULL!\n"));
        return;
    }

    Matrix m;
    action->getCamera()->getViewing(m,
                                action->getViewport()->getPixelWidth(),
                                action->getViewport()->getPixelHeight());
    m.invert();

    // get "glUniformMatrix4fvARB" function pointer
    OSGGLUNIFORMMATRIXFVARBPROC uniformMatrix4fv = (OSGGLUNIFORMMATRIXFVARBPROC)
        action->getWindow()->getFunction(_funcUniformMatrix4fv);
    GLint location = getUniformLocation(program, "OSGInvViewMatrix");
    if(location != -1)
        uniformMatrix4fv(location, 1, GL_FALSE, m.getValues());
}

void SHLChunk::updateStereoLeftEye(OSGGLGETUNIFORMLOCATIONARBPROC getUniformLocation,
                                   DrawActionBase *action, GLuint program)
{
    if(action->getCamera() == NULL || action->getViewport() == NULL)
    {
        FWARNING(("SHLChunk::updateStereoLeftEye : Can't update OSGStereoLeftEye"
                  "parameter, camera or viewport is NULL!\n"));
        return;
    }

    // ok -1 is mono
    Int32 leftEye = -1;
    // now search for a stereo camera decorator and get the eye.
    CameraPtr camera(*action->getCamera());
    CameraDecoratorPtr decorator = CameraDecoratorPtr::dcast(camera);
    while(decorator != NullFC)
    {
        StereoCameraDecoratorPtr stereoDecorator = StereoCameraDecoratorPtr::dcast(decorator);
        if(stereoDecorator != NullFC)
        {
            if(stereoDecorator->getLeftEye())
                leftEye = 1;
            else
                leftEye = 0;
            break;
        }
        decorator = CameraDecoratorPtr::dcast(decorator->getDecoratee());
    }

    // get "glUniform1iARB" function pointer
    OSGGLUNIFORM1IARBPROC uniform1i = (OSGGLUNIFORM1IARBPROC)
        action->getWindow()->getFunction(_funcUniform1i);

    GLint location = getUniformLocation(program, "OSGStereoLeftEye");
    if(location != -1)
        uniform1i(location, leftEye);
}

void SHLChunk::setClusterId(Int32 id)
{
    _clusterId = id;
}

void SHLChunk::updateClusterId(OSGGLGETUNIFORMLOCATIONARBPROC getUniformLocation,
                               DrawActionBase *action, GLuint program)
{
    // get "glUniform1iARB" function pointer
    OSGGLUNIFORM1IARBPROC uniform1i = (OSGGLUNIFORM1IARBPROC)
        action->getWindow()->getFunction(_funcUniform1i);

    GLint location = getUniformLocation(program, "OSGClusterId");
    if(location != -1)
        uniform1i(location, (GLint) _clusterId);
}

void SHLChunk::updateActiveLightsMask(OSGGLGETUNIFORMLOCATIONARBPROC getUniformLocation,
                                      DrawActionBase *action, GLuint program)
{
    RenderAction *ract = (RenderAction *) action;

    // get "glUniform1iARB" function pointer
    OSGGLUNIFORM1IARBPROC uniform1i = (OSGGLUNIFORM1IARBPROC)
        action->getWindow()->getFunction(_funcUniform1i);

    GLint location = getUniformLocation(program, "OSGActiveLightsMask");
    if(location != -1)
        uniform1i(location, (GLint) ract->getActiveLightsMask());
}

void SHLChunk::updateLight0Active(OSGGLGETUNIFORMLOCATIONARBPROC getUniformLocation,
                                      DrawActionBase *action, GLuint program)
{
    RenderAction *ract = (RenderAction *) action;

    // get "glUniform1iARB" function pointer
    OSGGLUNIFORM1IARBPROC uniform1i = (OSGGLUNIFORM1IARBPROC)
        action->getWindow()->getFunction(_funcUniform1i);

    GLint location = getUniformLocation(program, "OSGLight0Active");
    if(location != -1)
        uniform1i(location, (GLint) ract->getActiveLightsMask() & 1);
}

void SHLChunk::updateLight1Active(OSGGLGETUNIFORMLOCATIONARBPROC getUniformLocation,
                                      DrawActionBase *action, GLuint program)
{
    RenderAction *ract = (RenderAction *) action;

    // get "glUniform1iARB" function pointer
    OSGGLUNIFORM1IARBPROC uniform1i = (OSGGLUNIFORM1IARBPROC)
        action->getWindow()->getFunction(_funcUniform1i);

    GLint location = getUniformLocation(program, "OSGLight1Active");
    if(location != -1)
        uniform1i(location, (GLint) ract->getActiveLightsMask() & 2);
}

void SHLChunk::updateLight2Active(OSGGLGETUNIFORMLOCATIONARBPROC getUniformLocation,
                                      DrawActionBase *action, GLuint program)
{
    RenderAction *ract = (RenderAction *) action;

    // get "glUniform1iARB" function pointer
    OSGGLUNIFORM1IARBPROC uniform1i = (OSGGLUNIFORM1IARBPROC)
        action->getWindow()->getFunction(_funcUniform1i);

    GLint location = getUniformLocation(program, "OSGLight2Active");
    if(location != -1)
        uniform1i(location, (GLint) ract->getActiveLightsMask() & 4);
}

void SHLChunk::updateLight3Active(OSGGLGETUNIFORMLOCATIONARBPROC getUniformLocation,
                                      DrawActionBase *action, GLuint program)
{
    RenderAction *ract = (RenderAction *) action;

    // get "glUniform1iARB" function pointer
    OSGGLUNIFORM1IARBPROC uniform1i = (OSGGLUNIFORM1IARBPROC)
        action->getWindow()->getFunction(_funcUniform1i);

    GLint location = getUniformLocation(program, "OSGLight3Active");
    if(location != -1)
        uniform1i(location, (GLint) ract->getActiveLightsMask() & 8);
}

void SHLChunk::updateLight4Active(OSGGLGETUNIFORMLOCATIONARBPROC getUniformLocation,
                                      DrawActionBase *action, GLuint program)
{
    RenderAction *ract = (RenderAction *) action;

    // get "glUniform1iARB" function pointer
    OSGGLUNIFORM1IARBPROC uniform1i = (OSGGLUNIFORM1IARBPROC)
        action->getWindow()->getFunction(_funcUniform1i);

    GLint location = getUniformLocation(program, "OSGLight3Active");
    if(location != -1)
        uniform1i(location, (GLint) ract->getActiveLightsMask() & 16);
}

void SHLChunk::updateLight5Active(OSGGLGETUNIFORMLOCATIONARBPROC getUniformLocation,
                                      DrawActionBase *action, GLuint program)
{
    RenderAction *ract = (RenderAction *) action;

    // get "glUniform1iARB" function pointer
    OSGGLUNIFORM1IARBPROC uniform1i = (OSGGLUNIFORM1IARBPROC)
        action->getWindow()->getFunction(_funcUniform1i);

    GLint location = getUniformLocation(program, "OSGLight3Active");
    if(location != -1)
        uniform1i(location, (GLint) ract->getActiveLightsMask() & 32);
}

void SHLChunk::updateLight6Active(OSGGLGETUNIFORMLOCATIONARBPROC getUniformLocation,
                                      DrawActionBase *action, GLuint program)
{
    RenderAction *ract = (RenderAction *) action;

    // get "glUniform1iARB" function pointer
    OSGGLUNIFORM1IARBPROC uniform1i = (OSGGLUNIFORM1IARBPROC)
        action->getWindow()->getFunction(_funcUniform1i);

    GLint location = getUniformLocation(program, "OSGLight3Active");
    if(location != -1)
        uniform1i(location, (GLint) ract->getActiveLightsMask() & 64);
}

void SHLChunk::updateLight7Active(OSGGLGETUNIFORMLOCATIONARBPROC getUniformLocation,
                                      DrawActionBase *action, GLuint program)
{
    RenderAction *ract = (RenderAction *) action;

    // get "glUniform1iARB" function pointer
    OSGGLUNIFORM1IARBPROC uniform1i = (OSGGLUNIFORM1IARBPROC)
        action->getWindow()->getFunction(_funcUniform1i);

    GLint location = getUniformLocation(program, "OSGLight3Active");
    if(location != -1)
        uniform1i(location, (GLint) ract->getActiveLightsMask() & 128);
}

/*------------------------------ State ------------------------------------*/

void SHLChunk::update(DrawActionBase *action)
{
    action->getWindow()->validateGLObject(getGLId());

    GLuint program = (GLuint) action->getWindow()->getGLObjectId(getGLId());
    if(program == 0)
        return;

    updateOSGParameters(action, program);
}

void SHLChunk::activate(DrawActionBase *action, UInt32 /*idx*/)
{
    //printf("SHLChunk::activate : %p\n", action->getWindow());
    action->getWindow()->validateGLObject(getGLId());

    GLuint program = (GLuint) action->getWindow()->getGLObjectId(getGLId());
    if(program == 0)
        return;

    //printf("SHLChunk::activate : %p %x\n", action->getWindow(), action->getWindow()->getGLObjectId(getGLId()));

    // get "glUseProgramObjectARB" function pointer
    OSGGLUSEPROGRAMOBJECTARBPROC useProgramObject = (OSGGLUSEPROGRAMOBJECTARBPROC)
        action->getWindow()->getFunction(_funcUseProgramObject);
    
    useProgramObject(program);

    updateOSGParameters(action, program);
    
    if(getPointSize())
    {
        glEnable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);
    }
    else
    {
        glDisable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);
    }
}

void SHLChunk::changeFrom(DrawActionBase *action, StateChunk * old_chunk,
                                UInt32 /*idx*/)
{
    SHLChunk *old = dynamic_cast<SHLChunk *>(old_chunk);

    if(old == NULL)
    {
        FWARNING(( "SHLChunk::changeFrom: caught non-SHLChunk!\n"));
        return;
    }

    // SHLChunk didn't change so do nothing.
    if(old == this)
    {
        // just update the osg parameters the world matrix could have been changed.
        GLuint program = (GLuint) action->getWindow()->getGLObjectId(getGLId());
        if(program != 0)
            updateOSGParameters(action, program);
        return;
    }

    action->getWindow()->validateGLObject(getGLId());

    // get "glUseProgramObjectARB" function pointer
    OSGGLUSEPROGRAMOBJECTARBPROC useProgramObject = (OSGGLUSEPROGRAMOBJECTARBPROC)
        action->getWindow()->getFunction(_funcUseProgramObject);

    if(action->getWindow()->getGLObjectId(old->getGLId()) != 0)
        useProgramObject(0);

    //printf("SHLChunk::changeFrom : %p %x\n", action->getWindow(), action->getWindow()->getGLObjectId(getGLId()));

    GLuint program = (GLuint) action->getWindow()->getGLObjectId(getGLId());

    if(program != 0)
    {
        useProgramObject(program);
        updateOSGParameters(action, program);

        if(getPointSize())
        {
            glEnable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);
        }
        else
        {
            glDisable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);
        }
    }
}


void SHLChunk::deactivate(DrawActionBase *action, UInt32 /*idx*/)
{
    if(action->getWindow()->getGLObjectId(getGLId()) == 0)
        return;
    
    // get "glUseProgramObjectARB" function pointer
    OSGGLUSEPROGRAMOBJECTARBPROC useProgramObject = (OSGGLUSEPROGRAMOBJECTARBPROC)
        action->getWindow()->getFunction(_funcUseProgramObject);

    useProgramObject(0);
    
    if(getPointSize())
    {
        glDisable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);
    }
}

/*-------------------------- Comparison -----------------------------------*/

Real32 SHLChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

bool SHLChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool SHLChunk::operator == (const StateChunk &other) const
{
    SHLChunk const *tother = dynamic_cast<SHLChunk const*>(&other);

    if(!tother)
        return false;

    if(getVertexProgram() != tother->getVertexProgram() ||
       getFragmentProgram() != tother->getFragmentProgram() ||
       getParameters().size() != tother->getParameters().size())
        return false;

    return true;
}

bool SHLChunk::operator != (const StateChunk &other) const
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGSHLChunk.cpp,v 1.47 2006/04/12 13:08:25 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGSHLCHUNKBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSHLCHUNKBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSHLCHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif
