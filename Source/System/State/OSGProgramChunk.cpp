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

#include <OSGBaseFunctions.h>

#include "OSGDrawActionBase.h"
#include "OSGWindow.h"

#include "OSGProgramChunk.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ProgramChunk
    \ingroup GrpSystemState

See \ref PageSystemProgramChunk for a description. The ProgramChunk contains
the source code of the program to use (osg::ProgramChunk::_sfProgram) and
the local program parameters (osg::ProgramChunk::_mfParamValues). The
parameters can have an associated name (osg::ProgramChunk::_mfParamNames).

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass ProgramChunk::_class("Program");

UInt32 ProgramChunk::_funcProgramString;
UInt32 ProgramChunk::_funcBindProgram;
UInt32 ProgramChunk::_funcDeletePrograms;
UInt32 ProgramChunk::_funcProgramLocalParameter4fv;
UInt32 ProgramChunk::_funcGetProgramiv;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ProgramChunk::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ProgramChunk::ProgramChunk(void) :
    Inherited()
{
    _funcProgramString                  =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glProgramStringARB");
    _funcBindProgram                    =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glBindProgramARB");
    _funcDeletePrograms                 =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glDeleteProgramsARB");
    _funcProgramLocalParameter4fv       =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE
                                            "glProgramLocalParameter4fvARB");
    _funcGetProgramiv       =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glGetProgramivARB");
}

ProgramChunk::ProgramChunk(const ProgramChunk &source) :
    Inherited(source)
{
}

ProgramChunk::~ProgramChunk(void)
{
    if(getGLId() > 0)
        Window::destroyGLObject(getGLId(), 1);
}

/*----------------------------- onCreate --------------------------------*/

void ProgramChunk::onCreate(const ProgramChunk *)
{
    if(GlobalSystemState == Startup)
        return;

    // !!! this temporary is needed to work around compiler problems (sgi)
    // CHECK CHECK
    //  ProgramChunkPtr tmpPtr = FieldContainer::getPtr<ProgramChunkPtr>(*this);
    ProgramChunkPtr tmpPtr(*this);

    beginEditCP(tmpPtr, ProgramChunk::GLIdFieldMask);

    setGLId(
        Window::registerGLObject(
            osgTypedMethodVoidFunctor2ObjCPtrPtr<ProgramChunkPtr, 
                                                 Window , 
                                                 UInt32>(
                                                     tmpPtr, 
                                                     &ProgramChunk::handleGL),
            1));

    endEditCP(tmpPtr, ProgramChunk::GLIdFieldMask);
}


/*------------------------- Chunk Class Access ---------------------------*/

const StateChunkClass *ProgramChunk::getClass( void ) const
{
    return &_class;
}

/*----------------------------- class specific ----------------------------*/

void ProgramChunk::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
    
    if(whichField & ProgramFieldMask)
    {
        Window::reinitializeGLObject(getGLId());
    }  
     
    if(whichField & ParamValuesFieldMask)
    {
        Window::refreshGLObject(getGLId());
    }
}

/*------------------------------ Output ----------------------------------*/

void ProgramChunk::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ProgramChunk NI" << std::endl;
}

/*---------------------------- Access ------------------------------------*/

/*! Read the program string from the given file
*/
bool ProgramChunk::read(const char *file)
{
    std::ifstream s(file);
    
    if(s)
    {
        return read(s);
    }
    else
    {
        return true;
    }
}

/*! Read the program string from the given stream
*/
bool ProgramChunk::read(std::istream &stream)
{
#define BUFSIZE 200
    
    getProgram().erase();    
    char buf[BUFSIZE];
    
    do
    {
        stream.read(buf, BUFSIZE);
        getProgram().append(buf, stream.gcount());
    }
    while(!stream.eof());
    
    return false;
}
    
/*! Add a named parameter 
*/
bool ProgramChunk::addParameter(const char   *name, 
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
    
const Vec4f& ProgramChunk::getParameter(Int16 index)
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
bool ProgramChunk::setParameter(Int16 index, const Vec4f& value)
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
Int16 ProgramChunk::findParameter(const std::string &name)
{
    MField<std::string>::iterator it;
    
    it = std::find(getParamNames().begin(), getParamNames().end(), name);

    if(it == getParamNames().end())
        return -1;

    return it - getParamNames().begin();
}


/*------------------------------ State ------------------------------------*/

/*! Print the error message if compilation fails
*/
void ProgramChunk::printCompileError(Window *win, UInt32 idstatus)
{
    Window::GLObjectStatusE mode;
    UInt32 id;
    
    Window::unpackIdStatus(idstatus, id, mode);
    
    GLint pos;   
    glGetIntegerv(GL_PROGRAM_ERROR_POSITION_ARB, &pos);
    
    FWARNING(("ProgramChunk(%p:%d,%d): error compiling program "
              "at position %d: %s\n",
              win, id, mode, pos, glGetString(GL_PROGRAM_ERROR_STRING_ARB)));
    
    UInt32 first, last;
    first = osgMax(static_cast<GLint>(                  0), pos-20);
    last  = osgMin(static_cast<GLint>(getProgram().size()), pos+20);
    
    std::string mesg("Location: ");
    
    for(UInt32 i = first; i < last; ++i)
    {
        if(i == pos)
        {
            mesg += '>';
            mesg += '>';
        }
        
        mesg += getProgram()[i];

        if(i == pos)
        {
            mesg += '<';
            mesg += '<';
        }
    }
    
    SWARNING << mesg << endLog;
}

/*! GL object handler
    create the program and destroy it
*/
void ProgramChunk::handleGL(Window *win, UInt32 idstatus)
{
    Window::GLObjectStatusE mode;
    UInt32 id;
    
    Window::unpackIdStatus(idstatus, id, mode);

    // get the program-specific specifics from the derived chunks
    GLenum target = getTarget();
    UInt32 extension = getExtension();

    if(!win->hasExtension(extension))
        return;

    if(mode == Window::destroy)
    {
        // get "glDeleteProgramsARB" function pointer
        void (OSG_APIENTRY* deletePrograms)(GLsizei num, const GLuint *progs) =
            (void (OSG_APIENTRY*)(GLsizei num, const GLuint *progs))
            win->getFunction(_funcDeletePrograms);

        GLuint prog = id;
        deletePrograms(1, &prog);
    }
    else if(mode == Window::finaldestroy)
    {
        //SWARNING << "Last program user destroyed" << std::endl;
    }
    else if(mode == Window::initialize || mode == Window::reinitialize ||
            mode == Window::needrefresh)
    {
        // get "glBindProgramARB" function pointer
        void (OSG_APIENTRY* bindProgram)(GLenum target, GLuint prog) =
            (void (OSG_APIENTRY*)(GLenum target, GLuint prog))
            win->getFunction(_funcBindProgram);
             
        glErr("ProgramChunk::handleGL: bindProgram precheck");
        
        bindProgram(target, id);
             
        glErr("ProgramChunk::handleGL: bindProgram postcheck");
        
        if(mode != Window::needrefresh)
        {
            // get "glProgramStringARB" function pointer
            void (OSG_APIENTRY* programString)(GLenum target, GLenum format, 
                        GLsizei lesn, const void *string) =
                (void (OSG_APIENTRY*)(GLenum target, GLenum format, 
                        GLsizei len, const void *string))
                win->getFunction(_funcProgramString);
            
            glErr("ProgramChunk::handleGL: programString precheck");
            
            glEnable(target);
            
            glErr("ProgramChunk::handleGL: enable postcheck");
            
            programString(target, GL_PROGRAM_FORMAT_ASCII_ARB,
                            getProgram().size(), getProgram().c_str());
            
            GLenum err = glGetError();
            
            if(err == GL_INVALID_OPERATION)
            {
                printCompileError(win, idstatus);
            }
            else if (err != GL_NO_ERROR)
            {
                SWARNING << "ProgramChunk::programString postcheck failed:"
                         << gluErrorString(err) << endLog;
            }
            
            glDisable(target);
            
            glErr("ProgramChunk::handleGL: disable postcheck");
        }
        
        void (OSG_APIENTRY* programLocalParameter4fv)(GLenum target, 
                        GLuint index, const GLfloat *params) =
            (void (OSG_APIENTRY*)(GLenum target, 
                        GLuint index, const GLfloat *params))
            win->getFunction(_funcProgramLocalParameter4fv);
             
        glErr("ProgramChunk::handleGL: programLocalParameter precheck");
       
        for(UInt16 i = 0; i < getParamValues().size(); ++i)
        {
            Vec4f &val=getParamValues()[i];
            
            programLocalParameter4fv(target, i, val.getValues());
            
            glErr("ProgramChunk::handleGL: programLocalParameter");
        }      
             
        glErr("ProgramChunk::handleGL: programLocalParameter postcheck");
    }
    else
    {
        SWARNING << "ProgramChunk(" << this << "::handleGL: Illegal mode: "
             << mode << " for id " << id << std::endl;
    }

}

void ProgramChunk::activate(DrawActionBase *action, UInt32)
{
    // get the program-type specifics from the derived chunks
    GLenum target = getTarget();
    UInt32 extension = getExtension();

    if(!action->getWindow()->hasExtension(extension))
    {
        return;
    }
    
    if(getProgram().empty())
        return;
        
    action->getWindow()->validateGLObject(getGLId());
           
    // get "glBindProgramARB" function pointer
    void (OSG_APIENTRY* bindProgram)(GLenum target, GLuint prog) =
        (void (OSG_APIENTRY*)(GLenum target, GLuint prog))
        action->getWindow()->getFunction(_funcBindProgram);
             
    glErr("ProgramChunk::activate: bindProgram precheck");

    glEnable(target);
             
    glErr("ProgramChunk::activate: enable postcheck");

    bindProgram(target, getGLId());
             
    glErr("ProgramChunk::activate: bindProgram postcheck");
}

void ProgramChunk::changeFrom(DrawActionBase *action, 
                              StateChunk * old_chunk, 
                              UInt32 )
{
    ProgramChunk * old = dynamic_cast<ProgramChunk*>(old_chunk);

    if(old == NULL)
    {
        FWARNING(( "ProgramChunk::changeFrom: caught non-ProgramChunk!\n"));
        return;
    }
       
    // get the program-type specifics from the derived chunks
    GLenum target = getTarget();
    UInt32 extension = getExtension();

    if(!action->getWindow()->hasExtension(extension))
        return;
     
    if(getProgram().empty())
    {
        if(old->getProgram().empty())
            return;
        
        glDisable(target);
    }

    action->getWindow()->validateGLObject(getGLId());
           
    // get "glBindProgramARB" function pointer
    void (OSG_APIENTRY* bindProgram)(GLenum target, GLuint prog) =
        (void (OSG_APIENTRY*)(GLenum target, GLuint prog))
        action->getWindow()->getFunction(_funcBindProgram);
             
    glErr("ProgramChunk::changeFrom: bindProgram precheck");

    if(old->getProgram().empty())
        glEnable(target);
             
    glErr("ProgramChunk::changeFrom: enable postcheck");

    bindProgram(target, getGLId());
             
    glErr("ProgramChunk::changeFrom: bindProgram postcheck");
}

void ProgramChunk::deactivate(DrawActionBase *action, UInt32)
{
    // get the program-type specifics from the derived chunks
    GLenum target = getTarget();
    UInt32 extension = getExtension();

    if(!action->getWindow()->hasExtension(extension))
    {
        return;
    }
    
    if(getProgram().empty())
    {
        return;
    }
           
    // get "glBindProgramARB" function pointer
    void (OSG_APIENTRY* bindProgram)(GLenum target, GLuint prog) =
        (void (OSG_APIENTRY*)(GLenum target, GLuint prog))
        action->getWindow()->getFunction(_funcBindProgram);

             
    glErr("ProgramChunk::deactivate: bindProgram precheck");

    bindProgram(target, getGLId());
             
    glErr("ProgramChunk::deactivate: bindProgram postcheck");

    glDisable(target);
             
    glErr("ProgramChunk::deactivate: disable postcheck");
}


/*! Virtual helper function to let the derived chunks return the extension that
    they implement. Only if this extension is supproted on the current Window
    is the porgram called.
*/
UInt32 ProgramChunk::getExtension(void) const
{
    FWARNING(( "ProgramChunk::getExtension called!\n" ));
    return 0;
}

/*! Virtual helper function to let the derived chunks return the target
    constant that they implement.
*/
GLenum ProgramChunk::getTarget(void) const
{
    FWARNING(( "ProgramChunk::getTarget called!\n" ));
    return 0;
}


/*! Virtual helper function to let the derived chunks return the name of the
    target constant that they implement, for debugging purposes.
*/
const char *ProgramChunk::getTargetName(void) const
{
    FWARNING(( "ProgramChunk::getTargetName called!\n" ));
    return "ERROR";
}

/*-------------------------- Comparison -----------------------------------*/

bool ProgramChunk::isTransparent(void) const
{
    return false;
}

Real32 ProgramChunk::switchCost(StateChunk *)
{
    return 0;
}

bool ProgramChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool ProgramChunk::operator == (const StateChunk &other) const
{
    ProgramChunk const *tother = dynamic_cast<ProgramChunk const*>(&other);

    if(!tother)
        return false;

    if(tother == this)
        return true;

    if(getProgram()            != tother->getProgram()            ||
       getParamValues().size() != tother->getParamValues().size() ||
       getParamNames().size()  != tother->getParamNames().size()
      )
        return false;

    // !!! FIXME: implement    
    
    return false;
}

bool ProgramChunk::operator != (const StateChunk &other) const
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: $";
    static Char8 cvsid_hpp       [] = OSGPROGRAMCHUNKBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGPROGRAMCHUNKBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGPROGRAMCHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

