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

// prototypes

typedef GLuint  (OSG_APIENTRY * PFNGLCREATEPROGRAMOBJECTARBPROC) (void);
typedef void    (OSG_APIENTRY * PFNGLDELETEOBJECTARBPROC) (GLuint obj);
typedef GLuint  (OSG_APIENTRY * PFNGLCREATESHADEROBJECTARBPROC) (GLenum shaderType);
typedef void    (OSG_APIENTRY * PFNGLSHADERSOURCEARBPROC) (GLuint shaderObj, GLsizei count, const char **strings, const GLint *length);
typedef void    (OSG_APIENTRY * PFNGLCOMPILESHADERARBPROC) (GLuint shaderObj);
typedef void    (OSG_APIENTRY * PFNGLGETOBJECTPARAMETERIVARBPROC) (GLuint obj, GLenum pname, GLint *params);
typedef void    (OSG_APIENTRY * PFNGLGETINFOLOGARBPROC) (GLuint obj,GLsizei maxLength, GLsizei *length, char *infoLog);
typedef void    (OSG_APIENTRY * PFNGLATTACHOBJECTARBPROC) (GLuint containerObj, GLuint obj);
typedef void    (OSG_APIENTRY * PFNGLLINKPROGRAMARBPROC) (GLuint programObj);
typedef void    (OSG_APIENTRY * PFNGLUSEPROGRAMOBJECTARBPROC) (GLuint programObj);

typedef GLint   (OSG_APIENTRY * PFNGLGETUNIFORMLOCATIONARBPROC) (GLuint programObj, const char *name);

typedef void   (OSG_APIENTRY * PFNGLUNIFORM1IARBPROC) (GLint location, GLint value);
typedef void   (OSG_APIENTRY * PFNGLUNIFORMIVARBPROC) (GLint location, GLsizei count, GLint *value);

typedef void   (OSG_APIENTRY * PFNGLUNIFORM1FARBPROC) (GLint location, GLfloat value);
typedef void   (OSG_APIENTRY * PFNGLUNIFORMFVARBPROC) (GLint location, GLsizei count, GLfloat *value);

typedef void   (OSG_APIENTRY * PFNGLUNIFORMMATRIXFVARBPROC) (GLint location, GLsizei count, GLboolean transpose, GLfloat *value);

typedef void   (OSG_APIENTRY * PFNGLGETUNIFORMFIARBPROC) (GLuint programObj, GLint location, GLint *value);
typedef void   (OSG_APIENTRY * PFNGLGETUNIFORMFVARBPROC) (GLuint programObj, GLint location, GLfloat *value);


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
    _osgParameters()
{
}

SHLChunk::SHLChunk(const SHLChunk &source) :
    Inherited(source),
    _osgParameters(source._osgParameters)
{
    _shl_extension = Window::registerExtension("GL_ARB_shading_language_100");
    
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
       (whichField & FragmentProgramFieldMask))
    {
        Window::reinitializeGLObject(getGLId());
    }

    if(whichField & ParametersFieldMask)
    {
        checkOSGParameters();
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
            PFNGLDELETEOBJECTARBPROC deleteObject = (PFNGLDELETEOBJECTARBPROC)
                win->getFunction(_funcDeleteObject);
            deleteObject(program);
            win->setGLObjectId(getGLId(), 0);
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
    PFNGLCREATEPROGRAMOBJECTARBPROC createProgramObject = (PFNGLCREATEPROGRAMOBJECTARBPROC)
        win->getFunction(_funcCreateProgramObject);

    // get "glDeleteObjectARB" function pointer
    PFNGLDELETEOBJECTARBPROC deleteObject = (PFNGLDELETEOBJECTARBPROC)
        win->getFunction(_funcDeleteObject);

    // get "glCreateShaderObjectARB" function pointer
    PFNGLCREATESHADEROBJECTARBPROC createShaderObject = (PFNGLCREATESHADEROBJECTARBPROC)
        win->getFunction(_funcCreateShaderObject);

    // get "glShaderSourceARB" function pointer
    PFNGLSHADERSOURCEARBPROC shaderSource = (PFNGLSHADERSOURCEARBPROC)
        win->getFunction(_funcShaderSource);

    // get "glCompileShaderARB" function pointer
    PFNGLCOMPILESHADERARBPROC compileShader = (PFNGLCOMPILESHADERARBPROC)
        win->getFunction(_funcCompileShader);

    // get "glGetObjectParameterivARB" function pointer
    PFNGLGETOBJECTPARAMETERIVARBPROC getObjectParameteriv = (PFNGLGETOBJECTPARAMETERIVARBPROC)
        win->getFunction(_funcGetObjectParameteriv);

    // get "glGetInfoLogARB" function pointer
    PFNGLGETINFOLOGARBPROC getInfoLog = (PFNGLGETINFOLOGARBPROC)
        win->getFunction(_funcGetInfoLog);

    // get "glAttachObjectARB" function pointer
    PFNGLATTACHOBJECTARBPROC attachObject = (PFNGLATTACHOBJECTARBPROC)
        win->getFunction(_funcAttachObject);

    // get "glLinkProgramARB" function pointer
    PFNGLLINKPROGRAMARBPROC linkProgram = (PFNGLLINKPROGRAMARBPROC)
        win->getFunction(_funcLinkProgram);

    // get "glUseProgramObjectARB" function pointer
    PFNGLUSEPROGRAMOBJECTARBPROC useProgramObject = (PFNGLUSEPROGRAMOBJECTARBPROC)
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
        vShader = createShaderObject(GL_VERTEX_SHADER_ARB);
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
        fShader = createShaderObject(GL_FRAGMENT_SHADER_ARB);
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
        if(!success)
        {
            char *debug;
            GLint debugLength;
            getObjectParameteriv(program, GL_OBJECT_INFO_LOG_LENGTH_ARB, &debugLength);
              
            debug = new char[debugLength];
            getInfoLog(program, debugLength, &debugLength, debug);
        
            FFATAL(("Couldn't link vertex and fragment program!\n%s\n", debug));
            delete [] debug;
            deleteObject(program);
            win->setGLObjectId(getGLId(), 0);
        }
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
                                bool useProgram, bool force)
{
    GLuint program = (GLuint) win->getGLObjectId(getGLId());

    if(program == 0)
        return;

    if(parameters.empty())
        return;


    // get "glUseProgramObjectARB" function pointer
    PFNGLUSEPROGRAMOBJECTARBPROC useProgramObject = (PFNGLUSEPROGRAMOBJECTARBPROC)
        win->getFunction(_funcUseProgramObject);

    if(useProgram)
        useProgramObject(program);

    // get "glGetUniformLocationARB" function pointer
    PFNGLGETUNIFORMLOCATIONARBPROC getUniformLocation = (PFNGLGETUNIFORMLOCATIONARBPROC)
        win->getFunction(_funcGetUniformLocation);

    // just a example showing how to get parameter values.
#if 0
    // get "glGetUniformfvARB" function pointer
    PFNGLGETUNIFORMFVARBPROC getUniformfv = (PFNGLGETUNIFORMFVARBPROC)
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
                PFNGLUNIFORM1IARBPROC uniform1i = (PFNGLUNIFORM1IARBPROC)
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
                PFNGLUNIFORM1IARBPROC uniform1i = (PFNGLUNIFORM1IARBPROC)
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
                PFNGLUNIFORM1FARBPROC uniform1f = (PFNGLUNIFORM1FARBPROC)
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
                PFNGLUNIFORMFVARBPROC uniform2fv = (PFNGLUNIFORMFVARBPROC)
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
                PFNGLUNIFORMFVARBPROC uniform3fv = (PFNGLUNIFORMFVARBPROC)
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
                PFNGLUNIFORMFVARBPROC uniform4fv = (PFNGLUNIFORMFVARBPROC)
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
                PFNGLUNIFORMMATRIXFVARBPROC uniformMatrix4fv = (PFNGLUNIFORMMATRIXFVARBPROC)
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

    if(useProgram)
        useProgramObject(0);
}

void SHLChunk::checkOSGParameters(void)
{
    _osgParameters.clear();
    const MFShaderParameterPtr &parameters = getParameters();
    for(UInt32 i = 0; i < parameters.size(); ++i)
    {
        ShaderParameterPtr parameter = parameters[i];
        if(parameter->getName().size() > 3 &&
           parameter->getName()[0] == 'O' &&
           parameter->getName()[1] == 'S' &&
           parameter->getName()[2] == 'G')
        {
            _osgParameters.insert(parameter->getName());
        }
    }
}

void SHLChunk::updateOSGParameters(DrawActionBase *action, GLuint program)
{
    if(_osgParameters.empty())
        return;

    // get "glGetUniformLocationARB" function pointer
    PFNGLGETUNIFORMLOCATIONARBPROC getUniformLocation = (PFNGLGETUNIFORMLOCATIONARBPROC)
        action->getWindow()->getFunction(_funcGetUniformLocation);

    // update camera orientation
    if(_osgParameters.count("OSGCameraOrientation") > 0)
    {
        Matrix m;
        NodePtr beacon = action->getCamera()->getBeacon();
        beacon->getToWorld(m);
        m[3].setValues(0,0,0,0);
    
        // get "glUniformMatrix4fvARB" function pointer
        PFNGLUNIFORMMATRIXFVARBPROC uniformMatrix4fv = (PFNGLUNIFORMMATRIXFVARBPROC)
            action->getWindow()->getFunction(_funcUniformMatrix4fv);
        GLint location = getUniformLocation(program, "OSGCameraOrientation");
        if(location != -1)
            uniformMatrix4fv(location, 1, GL_FALSE, m.getValues());
    }

    // update camera position
    if(_osgParameters.count("OSGCameraPosition") > 0)
    {
        Matrix m;
        NodePtr beacon = action->getCamera()->getBeacon();
        beacon->getToWorld(m);
        Vec3f cameraPos(m[3][0], m[3][1], m[3][2]);
    
        // get "glUniform3fvARB" function pointer
        PFNGLUNIFORMFVARBPROC uniform3fv = (PFNGLUNIFORMFVARBPROC)
            action->getWindow()->getFunction(_funcUniform3fv);
        GLint location = getUniformLocation(program, "OSGCameraPosition");
        if(location != -1)
            uniform3fv(location, 1, cameraPos.getValues());
    }
}

/*------------------------------ State ------------------------------------*/

void SHLChunk::activate(DrawActionBase *action, UInt32 /*idx*/)
{
    //printf("SHLChunk::activate : %p\n", action->getWindow());
    action->getWindow()->validateGLObject(getGLId());

    GLuint program = (GLuint) action->getWindow()->getGLObjectId(getGLId());
    if(program == 0)
        return;

    //printf("SHLChunk::activate : %p %x\n", action->getWindow(), action->getWindow()->getGLObjectId(getGLId()));

    // get "glUseProgramObjectARB" function pointer
    PFNGLUSEPROGRAMOBJECTARBPROC useProgramObject = (PFNGLUSEPROGRAMOBJECTARBPROC)
        action->getWindow()->getFunction(_funcUseProgramObject);
    
    useProgramObject(program);

    updateOSGParameters(action, program);
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
        return;

    action->getWindow()->validateGLObject(getGLId());

    // get "glUseProgramObjectARB" function pointer
    PFNGLUSEPROGRAMOBJECTARBPROC useProgramObject = (PFNGLUSEPROGRAMOBJECTARBPROC)
        action->getWindow()->getFunction(_funcUseProgramObject);

    if(action->getWindow()->getGLObjectId(old->getGLId()) != 0)
        useProgramObject(0);

    //printf("SHLChunk::changeFrom : %p %x\n", action->getWindow(), action->getWindow()->getGLObjectId(getGLId()));

    GLuint program = (GLuint) action->getWindow()->getGLObjectId(getGLId());

    if(program != 0)
    {
        useProgramObject(program);
        updateOSGParameters(action, program);
    }
}


void SHLChunk::deactivate(DrawActionBase *action, UInt32 /*idx*/)
{
    if(action->getWindow()->getGLObjectId(getGLId()) == 0)
        return;
    
    // get "glUseProgramObjectARB" function pointer
    PFNGLUSEPROGRAMOBJECTARBPROC useProgramObject = (PFNGLUSEPROGRAMOBJECTARBPROC)
        action->getWindow()->getFunction(_funcUseProgramObject);

    useProgramObject(0);
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGSHLChunk.cpp,v 1.23 2004/09/08 13:00:30 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGSHLCHUNKBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSHLCHUNKBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSHLCHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif
