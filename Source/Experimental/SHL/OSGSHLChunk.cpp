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

UInt32 SHLChunk::_funcUniform4fv = Window::invalidFunctionID;

SHLChunk::destroyMap SHLChunk::_destroy;

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
    _programs()
{
}

SHLChunk::SHLChunk(const SHLChunk &source) :
    Inherited(source),
    _programs(source._programs)
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
    
    _funcUniform4fv =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glUniform4fvARB", 
                                  _shl_extension);
}

SHLChunk::~SHLChunk(void)
{
}

void SHLChunk::onCreate(const SHLChunk */*source*/)
{
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
}

void SHLChunk::onDestroy(void)
{
    // Can't delete the programs here will be deleted in handleGL.
    for(programsIt it = _programs.begin(); it != _programs.end(); ++it)
    {
        Window *win = (*it).first;
        GLuint id = (*it).second;

        destroyIt itd = _destroy.find(win);
        
        if(itd != _destroy.end())
        {
            (*itd).second.push_back(id);
        }
        else
        {
            std::vector<GLuint> v;
            v.push_back(id);
            _destroy.insert(std::pair<Window *, std::vector<GLuint> >(win, v));
        }
    }

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
    Inherited::changed(whichField, origin);

    if((whichField & VertexProgramFieldMask) ||
       (whichField & FragmentProgramFieldMask))
    {
        Window::reinitializeGLObject(getGLId());
    }

    if(whichField & ParamValuesFieldMask)
    {
        Window::refreshGLObject(getGLId());
    }
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
        //printf("Window::destroy: %p\n", win);
        destroyIt itd = _destroy.find(win);
        if(itd != _destroy.end())
        {
            // get "glDeleteObjectARB" function pointer
            void (OSG_APIENTRY* deleteObject)(GLuint obj) =
            (void (OSG_APIENTRY*)(GLuint obj))
            win->getFunction(_funcDeleteObject);

            for(UInt32 i=0;i<(*itd).second.size();++i)
            {
                //printf("destroy program id %u\n", (*itd).second[i]);
                deleteObject((*itd).second[i]);
            }
            (*itd).second.clear();
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

        programsIt it = _programs.find(win);
        if(it != _programs.end())
        {
            GLuint program = (*it).second;
            // get "glUseProgramObjectARB" function pointer
            void (OSG_APIENTRY* useProgramObject)(GLuint programObj) =
            (void (OSG_APIENTRY*)(GLuint programObj))
            win->getFunction(_funcUseProgramObject);
            
            useProgramObject(program);
            
            // get "glUniform4fvARB" function pointer
            void (OSG_APIENTRY* uniform4fv)(GLint location, GLsizei count, GLfloat *value) =
            (void (OSG_APIENTRY*)(GLint location, GLsizei count, GLfloat *value))
            win->getFunction(_funcUniform4fv);
    
            // get "glGetUniformLocationARB" function pointer
            GLint (OSG_APIENTRY* getUniformLocation)(GLuint programObj, const char *name) =
            (GLint (OSG_APIENTRY*)(GLuint programObj, const char *name))
            win->getFunction(_funcGetUniformLocation);
            
            
            // HACK need to add all parameter types.
            // set params
            for(UInt16 i = 0; i < getParamValues().size(); ++i)
            {
                GLint location = getUniformLocation(program, getParamNames()[i].c_str());
                Vec4f &val = getParamValues()[i];
                uniform4fv(location, 1, val.getValues());
            }
            useProgramObject(0);
        }
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
    GLuint (OSG_APIENTRY* createProgramObject)(void) =
    (GLuint (OSG_APIENTRY*)(void))
    win->getFunction(_funcCreateProgramObject);
    
    // get "glDeleteObjectARB" function pointer
    void (OSG_APIENTRY* deleteObject)(GLuint obj) =
    (void (OSG_APIENTRY*)(GLuint obj))
    win->getFunction(_funcDeleteObject);

    // get "glCreateShaderObjectARB" function pointer
    GLuint (OSG_APIENTRY* createShaderObject)(GLenum shaderType) =
    (GLuint (OSG_APIENTRY*)(GLenum shaderType))
    win->getFunction(_funcCreateShaderObject);
    
    // get "glShaderSourceARB" function pointer
    void (OSG_APIENTRY* shaderSource)(GLuint shaderObj, GLsizei count, const char **strings, const GLint *length) =
    (void (OSG_APIENTRY*)(GLuint shaderObj, GLsizei count, const char **strings, const GLint *length))
    win->getFunction(_funcShaderSource);
    
    // get "glCompileShaderARB" function pointer
    void (OSG_APIENTRY* compileShader)(GLuint shaderObj) =
    (void (OSG_APIENTRY*)(GLuint shaderObj))
    win->getFunction(_funcCompileShader);
    
    // get "glGetObjectParameterivARB" function pointer
    void (OSG_APIENTRY* getObjectParameteriv)(GLuint obj, GLenum pname, GLint *params) =
    (void (OSG_APIENTRY*)(GLuint obj, GLenum pname, GLint *params))
    win->getFunction(_funcGetObjectParameteriv);

    // get "glGetInfoLogARB" function pointer
    void (OSG_APIENTRY* getInfoLog)(GLuint obj,GLsizei maxLength, GLsizei *length, char *infoLog) =
    (void (OSG_APIENTRY*)(GLuint obj,GLsizei maxLength, GLsizei *length, char *infoLog))
    win->getFunction(_funcGetInfoLog);
    
    // get "glAttachObjectARB" function pointer
    void (OSG_APIENTRY* attachObject)(GLuint containerObj, GLuint obj) =
    (void (OSG_APIENTRY*)(GLuint containerObj, GLuint obj))
    win->getFunction(_funcAttachObject);

    // get "glLinkProgramARB" function pointer
    void (OSG_APIENTRY* linkProgram)(GLuint programObj) =
    (void (OSG_APIENTRY*)(GLuint programObj))
    win->getFunction(_funcLinkProgram);
    
    // get "glUseProgramObjectARB" function pointer
    void (OSG_APIENTRY* useProgramObject)(GLuint programObj) =
    (void (OSG_APIENTRY*)(GLuint programObj))
    win->getFunction(_funcUseProgramObject);
    
    UInt32 program = 0;
    programsIt it = _programs.find(win);
    if(it == _programs.end())
    {
        program = createProgramObject();
        _programs.insert(std::pair<Window *, UInt32>(win, program));
        it = _programs.find(win);
    }
    else
    {
        deleteObject((*it).second);
        program = createProgramObject();
        (*it).second = program;
    }

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
            _programs.erase(it);
            deleteObject(program);
        }
    }
    else
    {
        _programs.erase(it);
        deleteObject(program);
    }
}

/*---------------------------- Access ------------------------------------*/

/*! Read the program string from the given file
*/
bool SHLChunk::readVertexProgram(const char *file)
{
    std::ifstream s(file);
    
    if(s.good())
    {
        return readVertexProgram(s);
    }
    else
    {
        FWARNING(("ProgramChunk::read: couldn't open '%s' for reading!\n",
                    file));
        return false;
    }
}

/*! Read the program string from the given stream
*/
bool SHLChunk::readVertexProgram(std::istream &stream)
{
#define BUFSIZE 200
    
    getVertexProgram().erase();    
    char buf[BUFSIZE];

    if(!stream.good())
    {
        FWARNING(("ProgramChunk::read: stream is not good!\n"));
        return false;
   
    }
    
    do
    {
        stream.read(buf, BUFSIZE);
        getVertexProgram().append(buf, stream.gcount());
    }
    while(!stream.eof());
    
    return true;
}

/*! Read the program string from the given file
*/
bool SHLChunk::readFragmentProgram(const char *file)
{
    std::ifstream s(file);
    
    if(s.good())
    {
        return readFragmentProgram(s);
    }
    else
    {
        FWARNING(("ProgramChunk::read: couldn't open '%s' for reading!\n",
                    file));
        return false;
    }
}

/*! Read the program string from the given stream
*/
bool SHLChunk::readFragmentProgram(std::istream &stream)
{
#define BUFSIZE 200
    
    getFragmentProgram().erase();    
    char buf[BUFSIZE];

    if(!stream.good())
    {
        FWARNING(("ProgramChunk::read: stream is not good!\n"));
        return false;
   
    }
    
    do
    {
        stream.read(buf, BUFSIZE);
        getFragmentProgram().append(buf, stream.gcount());
    }
    while(!stream.eof());
    
    return true;
}

/*! Add a named parameter 
*/
bool SHLChunk::addParameter(const char   *name, 
                                      Int16  index)
{
    if(index < 0)
        return true;
        
    if(getParamNames().size() <= index)
    {
        getParamNames().resize(index + 1);
    }
    getParamNames()[index] = name;
    return false;
}
    
const Vec4f& SHLChunk::getParameter(Int16 index)
{
    static const Vec4f bad(-1e10,-1e10,-1e10);
    
    if(index < 0)
        return bad;
        
    if(getParamValues().size() <= index)
    {
        return getParamValues()[index];
    }
    
    return bad;
}
 
/*! Set parameter value, create it if not set yet.
*/
bool SHLChunk::setParameter(Int16 index, const Vec4f& value)
{
    if(index < 0)
        return true;
        
    if(getParamValues().size() <= index)
    {
        getParamValues().resize(index + 1);
    }
    getParamValues()[index] = value;
    return false;
}

/*! Find the index for a named parameter, return -1 if not found.
*/
Int16 SHLChunk::findParameter(const std::string &name)
{
    MField<std::string>::iterator it;
    
    it = std::find(getParamNames().begin(), getParamNames().end(), name);

    if(it == getParamNames().end())
        return -1;

    return it - getParamNames().begin();
}

/*------------------------------ State ------------------------------------*/

void SHLChunk::activate(DrawActionBase *action, UInt32 /*idx*/)
{
    //printf("SHLChunk::activate : %p\n", action->getWindow());
    action->getWindow()->validateGLObject(getGLId());

    programsIt it = _programs.find(action->getWindow());
    if(it == _programs.end())
        return;

    // get "glUseProgramObjectARB" function pointer
    void (OSG_APIENTRY* useProgramObject)(GLuint programObj) =
    (void (OSG_APIENTRY*)(GLuint programObj))
    action->getWindow()->getFunction(_funcUseProgramObject);
    
    useProgramObject((*it).second);
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

    action->getWindow()->validateGLObject(getGLId());

    // get "glUseProgramObjectARB" function pointer
    void (OSG_APIENTRY* useProgramObject)(GLuint programObj) =
    (void (OSG_APIENTRY*)(GLuint programObj))
    action->getWindow()->getFunction(_funcUseProgramObject);

    programsIt it = old->_programs.find(action->getWindow());
    // deactivate the old one
    if(it != old->_programs.end())
        useProgramObject(0);

    it = _programs.find(action->getWindow());

    if(it != _programs.end())
        useProgramObject((*it).second);
}


void SHLChunk::deactivate(DrawActionBase *action, UInt32 /*idx*/)
{
    programsIt it = _programs.find(action->getWindow());
    if(it == _programs.end())
        return;

    // get "glUseProgramObjectARB" function pointer
    void (OSG_APIENTRY* useProgramObject)(GLuint programObj) =
    (void (OSG_APIENTRY*)(GLuint programObj))
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
       getParamValues().size() != tother->getParamValues().size() ||
       getParamNames().size()  != tother->getParamNames().size())
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGSHLChunk.cpp,v 1.7 2004/05/27 18:20:29 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGSHLCHUNKBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSHLCHUNKBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSHLCHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif
