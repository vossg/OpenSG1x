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
#include <OSGShaderParameterReal.h>
#include <OSGShaderParameterVec2f.h>
#include <OSGShaderParameterVec3f.h>
#include <OSGShaderParameterVec4f.h>
#include <OSGShaderParameterMatrix.h>

#include "OSGCGChunk.h"

#include <Cg/cgGL.h>

OSG_USING_NAMESPACE

CGChunk::OSGCGcontext CGChunk::_current_context = NULL;

/*! \class osg::CGChunk

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass CGChunk::_class("CG");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CGChunk::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void CGChunk::cgErrorCallback(void)
{
    CGerror LastError = cgGetError();

    if(LastError)
    {
        FWARNING(("Cg error occured!\n\n"));
        if(cgIsContext((CGcontext) _current_context))
        {
            const char *Listing = cgGetLastListing((CGcontext) _current_context);
            FWARNING(("\n---------------------------------------------------\n"));
            FWARNING(("%s\n\n", cgGetErrorString(LastError)));
            FWARNING(("%s\n", Listing));
            FWARNING(("---------------------------------------------------\n"));
        }
    }
}

/*----------------------- constructors & destructors ----------------------*/

CGChunk::CGChunk(void) :
    Inherited(),
    _context(NULL),
    _vProgram(NULL),
    _fProgram(NULL),
    _vp_isvalid(false),
    _fp_isvalid(false)
{
}

CGChunk::CGChunk(const CGChunk &source) :
    Inherited(source),
    _context(source._context),
    _vProgram(source._vProgram),
    _fProgram(source._fProgram),
    _vp_isvalid(source._vp_isvalid),
    _fp_isvalid(source._fp_isvalid)
{
}

CGChunk::~CGChunk(void)
{
}

void CGChunk::onCreate(const CGChunk *source)
{
    Inherited::onCreate(source);

    // ignore prototypes.
    if(GlobalSystemState == Startup)
        return;

    // we need this for clustering without it handleGL is never called.
    RemoteAspect::addFieldFilter(CGChunk::getClassType().getId(),
                                 CGChunk::GLIdFieldMask);
    
    cgSetErrorCallback(CGChunk::cgErrorCallback);

    CGChunkPtr tmpPtr(*this);
    beginEditCP(tmpPtr, CGChunk::GLIdFieldMask);
        setGLId(Window::registerGLObject(osgTypedMethodVoidFunctor2ObjCPtrPtr<CGChunkPtr,
                                         Window , UInt32>(tmpPtr, &CGChunk::handleGL), 1));
    endEditCP(tmpPtr, CGChunk::GLIdFieldMask);
}

void CGChunk::onDestroy(void)
{
    Inherited::onDestroy();

    if(cgIsProgram((CGprogram) _vProgram))
        cgDestroyProgram((CGprogram) _vProgram);
    if(cgIsProgram((CGprogram) _fProgram))
        cgDestroyProgram((CGprogram) _fProgram);
    if(cgIsContext((CGcontext) _context))
        cgDestroyContext((CGcontext) _context);
        
    if(getGLId() > 0)
        Window::destroyGLObject(getGLId(), 1);
}

const StateChunkClass *CGChunk::getClass(void) const
{
    return &_class;
}

/*----------------------------- class specific ----------------------------*/

void CGChunk::changed(BitVector whichField, UInt32 origin)
{
    if((whichField & VertexProgramFieldMask) ||
       (whichField & FragmentProgramFieldMask))
    {
        Window::reinitializeGLObject(getGLId());
    }  
     
    if(whichField & ParametersFieldMask)
    {
        Window::refreshGLObject(getGLId());
    }

    Inherited::changed(whichField, origin);
}

void CGChunk::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CGChunk NI" << std::endl;
}

/*! GL object handler
    create the program and destroy it
*/
void CGChunk::handleGL(Window *win, UInt32 idstatus)
{
    Window::GLObjectStatusE mode;
    UInt32 id;

    Window::unpackIdStatus(idstatus, id, mode);

    if(mode == Window::destroy)
    {
        ;
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
            updateCGContext();
        }

        updateParameters(win, getParameters());
    }
    else
    {
        SWARNING << "CGChunk(" << this << "::handleGL: Illegal mode: "
             << mode << " for id " << id << std::endl;
    }
}

void CGChunk::updateCGContext(void)
{
    if(_context == NULL)
        _context = (OSGCGcontext) cgCreateContext();
    
    _current_context = _context;

    // can't do this in onCreate()
    if(getVertexProfile() == CG_PROFILE_UNKNOWN)
        setVertexProfile(cgGLGetLatestProfile(CG_GL_VERTEX));
    cgGLSetOptimalOptions((CGprofile) getVertexProfile());
    
    if(getFragmentProfile() == CG_PROFILE_UNKNOWN)
        setFragmentProfile(cgGLGetLatestProfile(CG_GL_FRAGMENT));
    cgGLSetOptimalOptions((CGprofile) getFragmentProfile());

    // reload programs
    if(hasVP() && !getVertexProgram().empty())
    {
        if(cgIsProgram((CGprogram) _vProgram))
            cgDestroyProgram((CGprogram) _vProgram);

        const char *entry = NULL;
        if(!getVertexEntryPoint().empty())
            entry = getVertexEntryPoint().c_str();
    
        const char **args = NULL;
        if(!getVertexArguments().empty())
        {
            UInt32 asize = getVertexArguments().size();
            args = new const char *[asize + 1];
            for(UInt32 i=0;i<asize;++i)
                args[i] = getVertexArguments()[i].c_str();
            args[asize] = NULL;
        }
        
        _vProgram = (OSGCGprogram) cgCreateProgram((CGcontext) _context,
                                    CG_SOURCE, getVertexProgram().c_str(),
                                    (CGprofile) getVertexProfile(), entry, args);
        if(_vProgram)
        {
            _vp_isvalid = true;
            cgGLLoadProgram((CGprogram) _vProgram);
        }
        else
        {
            _vp_isvalid = false;
            FWARNING(("Couldn't load vertex program!\n"));
        }
        
        if(!getVertexArguments().empty())
            delete [] args;
    }

    if(hasFP() && !getFragmentProgram().empty())
    {
        if(cgIsProgram((CGprogram) _fProgram))
            cgDestroyProgram((CGprogram) _fProgram);

        const char *entry = NULL;
        if(!getFragmentEntryPoint().empty())
            entry = getFragmentEntryPoint().c_str();
    
        const char **args = NULL;
        if(!getFragmentArguments().empty())
        {
            UInt32 asize = getFragmentArguments().size();
            args = new const char *[asize + 1];
            for(UInt32 i=0;i<asize;++i)
                args[i] = getFragmentArguments()[i].c_str();
            args[asize] = NULL;
        }
        
        _fProgram = (OSGCGprogram) cgCreateProgram((CGcontext) _context,
                                    CG_SOURCE, getFragmentProgram().c_str(),
                                    (CGprofile) getFragmentProfile(), entry, args);
        if(cgIsProgram((CGprogram) _fProgram))
        {
            _fp_isvalid = true;
            cgGLLoadProgram((CGprogram) _fProgram);
        }
        else
        {
            _fp_isvalid = false;
            FWARNING(("Couldn't load fragment program!\n"));
        }

        if(!getFragmentArguments().empty())
            delete [] args;
    }
}

void CGChunk::updateParameters(Window */*win*/,
                               const MFShaderParameterPtr &parameters,
                               bool force)
{
    for(UInt32 i = 0; i < parameters.size(); ++i)
    {
        ShaderParameterPtr parameter = parameters[i];

        // works also but is not possible with a switch and a switch is much faster.
        //UInt16 groupid = parameter->getType().getGroupId();
        //if(groupid == ShaderParameterInt::getClassType().getGroupId())

        if(!force)
        {
            if(!parameter->hasChanged())
                    continue;
            parameter->resetChanged();
        }

        switch(parameter->getTypeId())
        {
            //case ShaderParameter::SHPTypeBool:
            //break;
            //case ShaderParameter::SHPTypeInt:
            //break;
            case ShaderParameter::SHPTypeReal:
            {
                ShaderParameterRealPtr p = ShaderParameterRealPtr::dcast(parameter);

                if(_vp_isvalid)
                {
                    CGparameter vpparam = cgGetNamedParameter((CGprogram) _vProgram, p->getName().c_str());
                    if(vpparam != 0)
                        cgGLSetParameter1f(vpparam, p->getValue());
                    //FWARNING(("Unknown parameter '%s'!\n", p->getName().c_str()));
                }
                
                if(_fp_isvalid)
                {
                    CGparameter fpparam = cgGetNamedParameter((CGprogram) _fProgram, p->getName().c_str());
                    if(fpparam != 0)
                        cgGLSetParameter1f(fpparam, p->getValue());
                }
            }
            break;
            case ShaderParameter::SHPTypeVec2f:
            {
                ShaderParameterVec2fPtr p = ShaderParameterVec2fPtr::dcast(parameter);

                if(_vp_isvalid)
                {
                    CGparameter vpparam = cgGetNamedParameter((CGprogram) _vProgram,
                                                        p->getName().c_str());
                    if(vpparam != 0)
                        cgGLSetParameter2fv(vpparam, p->getValue().getValues());
                }
                
                if(_fp_isvalid)
                {
                    CGparameter fpparam = cgGetNamedParameter((CGprogram) _fProgram,
                                                        p->getName().c_str());
                    if(fpparam != 0)
                        cgGLSetParameter2fv(fpparam, p->getValue().getValues());
                }
            }
            break;
            case ShaderParameter::SHPTypeVec3f:
            {
                ShaderParameterVec3fPtr p = ShaderParameterVec3fPtr::dcast(parameter);

                if(_vp_isvalid)
                {
                    CGparameter vpparam = cgGetNamedParameter((CGprogram) _vProgram,
                                                        p->getName().c_str());
                    if(vpparam != 0)
                        cgGLSetParameter3fv(vpparam, p->getValue().getValues());
                }
                
                if(_fp_isvalid)
                {
                    CGparameter fpparam = cgGetNamedParameter((CGprogram) _fProgram,
                                                        p->getName().c_str());
                    if(fpparam != 0)
                        cgGLSetParameter3fv(fpparam, p->getValue().getValues());
                }
            }
            break;
            case ShaderParameter::SHPTypeVec4f:
            {
                ShaderParameterVec4fPtr p = ShaderParameterVec4fPtr::dcast(parameter);
                
                if(_vp_isvalid)
                {
                    CGparameter vpparam = cgGetNamedParameter((CGprogram) _vProgram,
                                                        p->getName().c_str());
                    if(vpparam != 0)
                        cgGLSetParameter4fv(vpparam, p->getValue().getValues());
                }
                
                if(_fp_isvalid)
                {
                    CGparameter fpparam = cgGetNamedParameter((CGprogram) _fProgram,
                                                        p->getName().c_str());
                    if(fpparam != 0)
                        cgGLSetParameter4fv(fpparam, p->getValue().getValues());
                }
            }
            break;
            case ShaderParameter::SHPTypeMatrix:
            {
                ShaderParameterMatrixPtr p = ShaderParameterMatrixPtr::dcast(parameter);
                
                if(_vp_isvalid)
                {
                    CGparameter vpparam = cgGetNamedParameter((CGprogram) _vProgram,
                                                        p->getName().c_str());
                    if(vpparam != 0)
                        cgGLSetMatrixParameterfr(vpparam, p->getValue().getValues());
                }
                
                if(_fp_isvalid)
                {
                    CGparameter fpparam = cgGetNamedParameter((CGprogram) _fProgram,
                                                        p->getName().c_str());
                    if(fpparam != 0)
                        cgGLSetMatrixParameterfr(fpparam, p->getValue().getValues());
                }
            }
            break;
            default:
                FWARNING(("Parameter '%s' has unknown tpye %d!\n", parameter->getName().c_str(),
                                                                   parameter->getTypeId()));
            break;
        }
    }
}

/*------------------------------ State ------------------------------------*/

void CGChunk::activate(DrawActionBase *action, UInt32 /*idx*/)
{
    _current_context = _context;

    action->getWindow()->validateGLObject(getGLId());

    if(_vp_isvalid)
    {
        cgGLEnableProfile((CGprofile) getVertexProfile());
        cgGLBindProgram((CGprogram) _vProgram);
    }

    if(_fp_isvalid)
    {
        cgGLEnableProfile((CGprofile) getFragmentProfile());
        cgGLBindProgram((CGprogram) _fProgram);
    }
}




void CGChunk::changeFrom(DrawActionBase *action, StateChunk * old_chunk,
                                UInt32 /*idx*/)
{
    CGChunk *old = dynamic_cast<CGChunk *>(old_chunk);

    if(old == NULL)
    {
        FWARNING(( "CGChunk::changeFrom: caught non-CGChunk!\n"));
        return;
    }

    // CGChunk didn't change so do nothing.
    if(old == this)
        return;

    _current_context = _context;

    action->getWindow()->validateGLObject(getGLId());

    // now deactivate the old.
    if(old->_fp_isvalid)
    {
        // unbinds program too
        cgGLDisableProfile((CGprofile) old->getFragmentProfile());
    }

    if(old->_vp_isvalid)
    {
        // unbinds program too
        cgGLDisableProfile((CGprofile) old->getVertexProfile());
    }

    if(_vp_isvalid)
    {
        cgGLEnableProfile((CGprofile) getVertexProfile());
        cgGLBindProgram((CGprogram) _vProgram);
    }

    if(_fp_isvalid)
    {
        cgGLEnableProfile((CGprofile) getFragmentProfile());
        cgGLBindProgram((CGprogram) _fProgram);
    }
}


void CGChunk::deactivate(DrawActionBase */*action*/, UInt32 /*idx*/)
{
    if(_fp_isvalid)
        cgGLDisableProfile((CGprofile) getFragmentProfile());

    if(_vp_isvalid)
        cgGLDisableProfile((CGprofile) getVertexProfile());
}

/*-------------------------- Comparison -----------------------------------*/

Real32 CGChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

bool CGChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool CGChunk::operator == (const StateChunk &other) const
{
    CGChunk const *tother = dynamic_cast<CGChunk const*>(&other);

    if(!tother)
        return false;

    if(getVertexProgram() != tother->getVertexProgram() ||
       getVertexProfile() != tother->getVertexProfile() ||
       getFragmentProgram() != tother->getFragmentProgram() ||
       getFragmentProfile() != tother->getFragmentProfile() ||
       getParameters().size() != tother->getParameters().size())
        return false;

    return true;
}

bool CGChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}


bool CGChunk::hasVP(void)
{
    if(cgGLIsProfileSupported((CGprofile) getVertexProfile()))
    {
        return true;
    }
    
    SWARNING << "Vertex programming extensions "
             << cgGetProfileString((CGprofile) getVertexProfile())
             << " not supported!" << std::endl;
    return false;
}

bool CGChunk::hasFP(void)
{
    if (cgGLIsProfileSupported((CGprofile) getFragmentProfile()))
        return true;

    SWARNING << "Fragment programming extensions "
             << cgGetProfileString((CGprofile) getFragmentProfile())
             << " not supported!" << std::endl;
    return false;
}

#if 0
void CGChunk::parseProgramParams(OSGCGprogram prog)
{
    parseParams(cgGetFirstParameter(prog, CG_PROGRAM));
}

void CGChunk::parseParams(OSGCGparameter param)
{
    if(!param)
        return;

    do
    {
        switch(cgGetParameterType((CGparameter) param))
        {
            case CG_STRUCT :
                parseParams(cgGetFirstStructParameter((CGparameter) param));
            break;
            case CG_ARRAY :
            {
                int ArraySize = cgGetArraySize((CGparameter) param, 0);
                int i;
                for(i=0; i < ArraySize; ++i)
                    parseParams(cgGetArrayParameter((CGparameter) param, i));
            }
            break;
            default: // Display parameter information
                const char *name = cgGetParameterName((CGparameter) param);
                CGtype paramType = cgGetParameterType((CGparameter) param);
                const char *type = cgGetTypeString(paramType);
                CGresource paramRes = cgGetParameterResource((CGparameter) param);
                const char *resource = cgGetResourceString(paramRes);
                printf("-- Name = '%s'\n", name);
                printf("-- Type = '%s'\n", type);
                printf("-- Resource = '%s'\n\n", resource);
        }
    }
    while((param = cgGetNextParameter((CGparameter) param)) != 0);
}
#endif

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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGCGChunk.cpp,v 1.2 2003/07/28 08:44:22 amz Exp $";
    static Char8 cvsid_hpp       [] = OSGCGCHUNKBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCGCHUNKBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCGCHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif
