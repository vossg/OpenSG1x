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

#include "OSGCGVertexProgramChunk.h"

OSG_USING_NAMESPACE

/*! \class osg::CGVertexProgramChunk

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass CGVertexProgramChunk::_class("CGVertexProgram");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CGVertexProgramChunk::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*----------------------- constructors & destructors ----------------------*/

CGVertexProgramChunk::CGVertexProgramChunk(void) :
    Inherited(),
    _vProgram(NULL),
    _vp_isvalid(false)
{
}

CGVertexProgramChunk::CGVertexProgramChunk(const CGVertexProgramChunk &source) :
    Inherited(source),
    _vProgram(source._vProgram),
    _vp_isvalid(source._vp_isvalid)
{
}

CGVertexProgramChunk::~CGVertexProgramChunk(void)
{
}

void CGVertexProgramChunk::onCreate(const CGVertexProgramChunk *source)
{
    CGProgramChunk::onCreate(source);
    
    // ignore prototypes.
    if(GlobalSystemState == Startup)
        return;

    // we need this for clustering without it handleGL is never called.
    RemoteAspect::addFieldFilter(CGVertexProgramChunk::getClassType().getId(), CGVertexProgramChunk::GLIdFieldMask);

    CGVertexProgramChunkPtr tmpPtr(*this);
    beginEditCP(tmpPtr, CGVertexProgramChunk::GLIdFieldMask);
        setGLId(Window::registerGLObject(osgTypedMethodVoidFunctor2ObjCPtrPtr<CGVertexProgramChunkPtr,
                                         Window , UInt32>(tmpPtr, &CGVertexProgramChunk::handleGL), 1));
    endEditCP(tmpPtr, CGVertexProgramChunk::GLIdFieldMask);
}

void CGVertexProgramChunk::onDestroy(void)
{
    if(cgIsProgram(_vProgram))
        cgDestroyProgram(_vProgram);

    if(cgIsContext(_context))
        cgDestroyContext(_context);

    if(getGLId() > 0)
        Window::destroyGLObject(getGLId(), 1);
}

const StateChunkClass *CGVertexProgramChunk::getClass(void) const
{
    return &_class;
}

/*----------------------------- class specific ----------------------------*/

void CGVertexProgramChunk::changed(BitVector whichField, UInt32 origin)
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

void CGVertexProgramChunk::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CGVertexProgramChunk NI" << std::endl;
}

/*! GL object handler
    create the program and destroy it
*/
void CGVertexProgramChunk::handleGL(Window */*win*/, UInt32 idstatus)
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
        
        // set params
        for(UInt16 i = 0; i < getParamValues().size(); ++i)
        {
            CGparameter vpparam = cgGetNamedParameter(_vProgram, getParamNames()[i].c_str());
            Vec4f &val = getParamValues()[i];
            if(vpparam != 0)
                cgGLSetParameter4fv(vpparam, val.getValues());
        }
    }
    else
    {
        SWARNING << "CGVertexProgramChunk(" << this << "::handleGL: Illegal mode: "
             << mode << " for id " << id << std::endl;
    }
}

void CGVertexProgramChunk::updateCGContext(void)
{
    if(_context == NULL)
        _context = cgCreateContext();
    
    _current_context = _context;

    // can't do this in onCreate()
    if(getProfile() == CG_PROFILE_UNKNOWN)
        setProfile(cgGLGetLatestProfile(CG_GL_VERTEX));
    cgGLSetOptimalOptions((CGprofile) getProfile());
    
    // reload programs
    if(hasVP() && !getProgram().empty())
    {
        if(cgIsProgram(_vProgram))
            cgDestroyProgram(_vProgram);

        _vProgram = cgCreateProgram(_context, CG_SOURCE, getProgram().c_str(),
                                    (CGprofile) getProfile(), NULL, NULL);
        if(_vProgram)
        {
            _vp_isvalid = true;
            cgGLLoadProgram(_vProgram);
        }
        else
        {
            _vp_isvalid = false;
            FWARNING(("Couldn't load vertex program!\n"));
        }
    }
}

/*------------------------------ State ------------------------------------*/

void CGVertexProgramChunk::activate(DrawActionBase *action, UInt32 /*idx*/)
{
    _current_context = _context;

    action->getWindow()->validateGLObject(getGLId());

    if(_vp_isvalid)
    {
        cgGLEnableProfile((CGprofile) getProfile());
        cgGLBindProgram(_vProgram);
    }
}




void CGVertexProgramChunk::changeFrom(DrawActionBase *action, StateChunk * old_chunk,
                                UInt32 /*idx*/)
{
    CGVertexProgramChunk *old = dynamic_cast<CGVertexProgramChunk *>(old_chunk);

    if(old == NULL)
    {
        FWARNING(( "CGVertexProgramChunk::changeFrom: caught non-CGVertexProgramChunk!\n"));
        return;
    }

    _current_context = _context;

    action->getWindow()->validateGLObject(getGLId());

    if(_vp_isvalid)
    {
        cgGLEnableProfile((CGprofile) getProfile());
        cgGLBindProgram(_vProgram);
    }
}


void CGVertexProgramChunk::deactivate(DrawActionBase */*action*/, UInt32 /*idx*/)
{
    if(_vp_isvalid)
        cgGLDisableProfile((CGprofile) getProfile());
}

/*-------------------------- Comparison -----------------------------------*/

Real32 CGVertexProgramChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

bool CGVertexProgramChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool CGVertexProgramChunk::operator == (const StateChunk &other) const
{
    return CGProgramChunk::operator==(other);
    
#if 0
    CGVertexProgramChunk const *tother = dynamic_cast<CGVertexProgramChunk const*>(&other);

    if(!tother)
        return false;

    if(getVertexProgram() != tother->getVertexProgram() ||
       getVertexProfile() != tother->getVertexProfile() ||
       getFragmentProgram() != tother->getFragmentProgram() ||
       getFragmentProfile() != tother->getFragmentProfile() ||
       getParamValues().size() != tother->getParamValues().size() ||
       getParamNames().size()  != tother->getParamNames().size())
        return false;
    
    

    return true;
#endif
}

bool CGVertexProgramChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}


bool CGVertexProgramChunk::hasVP(void)
{
    if(cgGLIsProfileSupported((CGprofile) getProfile()))
    {
        return true;
    }
    
    SWARNING << "Vertex programming extensions "
             << cgGetProfileString((CGprofile) getProfile())
             << " not supported!" << std::endl;
    return false;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGCGVertexProgramChunk.cpp,v 1.2 2004/03/11 14:32:35 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGCGVERTEXPROGRAMCHUNKBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCGVERTEXPROGRAMCHUNKBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCGVERTEXPROGRAMCHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif
