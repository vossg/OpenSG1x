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

#include <OSGShaderParameter.h>
#include <OSGShaderParameterBool.h>
#include <OSGShaderParameterInt.h>
#include <OSGShaderParameterReal.h>
#include <OSGShaderParameterVec2f.h>
#include <OSGShaderParameterVec3f.h>
#include <OSGShaderParameterVec4f.h>
#include <OSGShaderParameterMatrix.h>

#include <OSGSHLChunk.h>

#include "OSGSHLParameterChunk.h"

OSG_USING_NAMESPACE

/*! \class osg::SHLParameterChunk

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass SHLParameterChunk::_class("SHLParameter");

UInt32 SHLParameterChunk::_shl_extension;

UInt32 SHLParameterChunk::_funcGetUniformLocation = Window::invalidFunctionID;

UInt32 SHLParameterChunk::_funcUniform1i = Window::invalidFunctionID;
UInt32 SHLParameterChunk::_funcUniform2iv = Window::invalidFunctionID;
UInt32 SHLParameterChunk::_funcUniform3iv = Window::invalidFunctionID;
UInt32 SHLParameterChunk::_funcUniform4iv = Window::invalidFunctionID;

UInt32 SHLParameterChunk::_funcUniform1f = Window::invalidFunctionID;
UInt32 SHLParameterChunk::_funcUniform2fv = Window::invalidFunctionID;
UInt32 SHLParameterChunk::_funcUniform3fv = Window::invalidFunctionID;
UInt32 SHLParameterChunk::_funcUniform4fv = Window::invalidFunctionID;

UInt32 SHLParameterChunk::_funcUniformMatrix4fv = Window::invalidFunctionID;

UInt32 SHLParameterChunk::_funcGetUniformiv = Window::invalidFunctionID;
UInt32 SHLParameterChunk::_funcGetUniformfv = Window::invalidFunctionID;
    
// prototypes

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

void SHLParameterChunk::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SHLParameterChunk::SHLParameterChunk(void) :
    Inherited(),
    _parameter_access(NULL)
{
}

SHLParameterChunk::SHLParameterChunk(const SHLParameterChunk &source) :
    Inherited(source),
    _parameter_access(source._parameter_access)
{
    _shl_extension = Window::registerExtension("GL_ARB_shading_language_100");

    _funcGetUniformLocation =
        Window::registerFunction (OSG_DLSYM_UNDERSCORE"glGetUniformLocationARB", 
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

SHLParameterChunk::~SHLParameterChunk(void)
{
}

void SHLParameterChunk::onCreate(const SHLParameterChunk *source)
{
    Inherited::onCreate(source);

    // ignore prototypes.
    if(GlobalSystemState == Startup)
        return;

    _parameter_access = new ShaderParameterAccess(getParameters());
}

void SHLParameterChunk::onDestroy(void)
{
    Inherited::onDestroy();

    if(_parameter_access != NULL)
        delete _parameter_access;
}

const StateChunkClass *SHLParameterChunk::getClass(void) const
{
    return &_class;
}

/*----------------------------- class specific ----------------------------*/

void SHLParameterChunk::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void SHLParameterChunk::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SHLParameterChunk NI" << std::endl;
}

void SHLParameterChunk::updateParameters(Window *win)
{
    SHLChunkPtr shl = getSHLChunk();

    if(shl == NullFC)
        return;

    GLuint program = (GLuint) win->getGLObjectId(shl->getGLId());

    if(program == 0)
        return;

    // get "glGetUniformLocationARB" function pointer
    PFNGLGETUNIFORMLOCATIONARBPROC getUniformLocation = (PFNGLGETUNIFORMLOCATIONARBPROC)
        win->getFunction(_funcGetUniformLocation);

    for(UInt32 i = 0; i < getParameters().size(); ++i)
    {
        ShaderParameterPtr parameter = getParameters()[i];

        // works also but is not possible with a switch and a switch is much faster.
        //UInt16 groupid = parameter->getType().getGroupId();
        //if(groupid == ShaderParameterInt::getClassType().getGroupId())
        
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
                
                // get "glGetUniformfvARB" function pointer
                PFNGLGETUNIFORMFVARBPROC getUniformfv = (PFNGLGETUNIFORMFVARBPROC)
                    win->getFunction(_funcGetUniformfv);

                // get "glUniform2fvARB" function pointer
                PFNGLUNIFORMFVARBPROC uniform2fv = (PFNGLUNIFORMFVARBPROC)
                    win->getFunction(_funcUniform2fv);
    
                // need to test if this is faster!!!
                GLint location = getUniformLocation(program, p->getName().c_str());
                if(location != -1)
                {
                    GLfloat values[2];
                    getUniformfv(program, location, values);
                    if(values[0] != p->getValue()[0] ||
                       values[1] != p->getValue()[1])
                    {
                        printf("changed parameter vec2f!\n");
                        uniform2fv(location, 1, p->getValue().getValues());
                    }
                }
                else
                {
                    FWARNING(("Unknown parameter '%s'!\n", p->getName().c_str()));
                }
            }
            break;
            case ShaderParameter::SHPTypeVec3f:
            {
                ShaderParameterVec3fPtr p = ShaderParameterVec3fPtr::dcast(parameter);
                
                // get "glGetUniformfvARB" function pointer
                PFNGLGETUNIFORMFVARBPROC getUniformfv = (PFNGLGETUNIFORMFVARBPROC)
                    win->getFunction(_funcGetUniformfv);

                // get "glUniform3fvARB" function pointer
                PFNGLUNIFORMFVARBPROC uniform3fv = (PFNGLUNIFORMFVARBPROC)
                    win->getFunction(_funcUniform3fv);
    
                GLint location = getUniformLocation(program, p->getName().c_str());
                if(location != -1)
                {
                    GLfloat values[3];
                    getUniformfv(program, location, values);
                    if(values[0] != p->getValue()[0] ||
                       values[1] != p->getValue()[1] ||
                       values[2] != p->getValue()[2])
                    {
                        //printf("changed parameter vec3f!\n");
                        uniform3fv(location, 1, p->getValue().getValues());
                    }
                }
                else
                {
                    FWARNING(("Unknown parameter '%s'!\n", p->getName().c_str()));
                }
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
        }
    }
}

/*------------------------------ State ------------------------------------*/

void SHLParameterChunk::activate(DrawActionBase *action, UInt32 /*idx*/)
{
    if(!action->getWindow()->hasExtension(_shl_extension))
    {
        FWARNING(("OpenGL Shading Language is not supported, couldn't find extension 'GL_ARB_shading_language_100'!\n"));
        return;
    }
    updateParameters(action->getWindow());
}

void SHLParameterChunk::changeFrom(DrawActionBase *action, StateChunk * old_chunk,
                                UInt32 /*idx*/)
{
    if(!action->getWindow()->hasExtension(_shl_extension))
    {
        FWARNING(("OpenGL Shading Language is not supported, couldn't find extension 'GL_ARB_shading_language_100'!\n"));
        return;
    }

    SHLParameterChunk *old = dynamic_cast<SHLParameterChunk *>(old_chunk);

    if(old == NULL)
    {
        FWARNING(( "SHLParameterChunk::changeFrom: caught non-SHLParameterChunk!\n"));
        return;
    }

    // SHLParameterChunk didn't change so do nothing.
    if(old == this)
        return;

    updateParameters(action->getWindow());
}


void SHLParameterChunk::deactivate(DrawActionBase *action, UInt32 /*idx*/)
{
}

/*-------------------------- Comparison -----------------------------------*/

Real32 SHLParameterChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

bool SHLParameterChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool SHLParameterChunk::operator == (const StateChunk &other) const
{
    SHLParameterChunk const *tother = dynamic_cast<SHLParameterChunk const*>(&other);

    if(!tother)
        return false;

    if(getParameters().size() != tother->getParameters().size())
        return false;

    return true;
}

bool SHLParameterChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}

/*------------------------------------ Set --------------------------------*/

bool SHLParameterChunk::setUniformParameter(const char *name, bool value)
{
    return _parameter_access->setParameter<ShaderParameterBool>(name, value);
}

bool SHLParameterChunk::setUniformParameter(const char *name, Int32 value)
{
    return _parameter_access->setParameter<ShaderParameterInt>(name, value);
}

bool SHLParameterChunk::setUniformParameter(const char *name, Real32 value)
{
    return _parameter_access->setParameter<ShaderParameterReal>(name, value);
}

bool SHLParameterChunk::setUniformParameter(const char *name, const Vec2f &value)
{
    return _parameter_access->setParameter<ShaderParameterVec2f>(name, value);
}

bool SHLParameterChunk::setUniformParameter(const char *name, const Vec3f &value)
{
    return _parameter_access->setParameter<ShaderParameterVec3f>(name, value);
}

bool SHLParameterChunk::setUniformParameter(const char *name, const Vec4f &value)
{
    return _parameter_access->setParameter<ShaderParameterVec4f>(name, value);
}

bool SHLParameterChunk::setUniformParameter(const char *name, const Matrix &value)
{
    return _parameter_access->setParameter<ShaderParameterMatrix>(name, value);
}

/*------------------------------------ Get --------------------------------*/

bool SHLParameterChunk::getUniformParameter(const char *name, bool &value)
{
    return _parameter_access->getParameter<ShaderParameterBool>(name, value);
}

bool SHLParameterChunk::getUniformParameter(const char *name, Int32 &value)
{
    return _parameter_access->getParameter<ShaderParameterInt>(name, value);
}

bool SHLParameterChunk::getUniformParameter(const char *name, Real32 &value)
{
    return _parameter_access->getParameter<ShaderParameterReal>(name, value);
}

bool SHLParameterChunk::getUniformParameter(const char *name, Vec2f &value)
{
    return _parameter_access->getParameter<ShaderParameterVec2f>(name, value);
}

bool SHLParameterChunk::getUniformParameter(const char *name, Vec3f &value)
{
    return _parameter_access->getParameter<ShaderParameterVec3f>(name, value);
}

bool SHLParameterChunk::getUniformParameter(const char *name, Vec4f &value)
{
    return _parameter_access->getParameter<ShaderParameterVec4f>(name, value);
}

bool SHLParameterChunk::getUniformParameter(const char *name, Matrix &value)
{
    return _parameter_access->getParameter<ShaderParameterMatrix>(name, value);
}

bool SHLParameterChunk::subUniformParameter(const char *name)
{
    return _parameter_access->subParameter(name);
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGSHLParameterChunk.cpp,v 1.1 2004/08/26 18:27:15 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGSHLPARAMETERCHUNKBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSHLPARAMETERCHUNKBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSHLPARAMETERCHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif
