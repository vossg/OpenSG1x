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

#include "OSGCGFragmentProgramChunk.h"

OSG_USING_NAMESPACE

/*! \class osg::CGFragmentProgramChunk

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass CGFragmentProgramChunk::_class("CGFragmentProgram");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CGFragmentProgramChunk::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*----------------------- constructors & destructors ----------------------*/

CGFragmentProgramChunk::CGFragmentProgramChunk(void) :
    Inherited(),
    _fProgram(NULL),
    _fp_isvalid(false)
{
}

CGFragmentProgramChunk::CGFragmentProgramChunk(const CGFragmentProgramChunk &source) :
    Inherited(source),
    _fProgram(source._fProgram),
    _fp_isvalid(source._fp_isvalid)
{
}

CGFragmentProgramChunk::~CGFragmentProgramChunk(void)
{
}

void CGFragmentProgramChunk::onCreate(const CGFragmentProgramChunk *source)
{
    CGProgramChunk::onCreate(source);

    // ignore prototypes.
    if(GlobalSystemState == Startup)
        return;

    // we need this for clustering without it handleGL is never called.
    RemoteAspect::addFieldFilter(CGFragmentProgramChunk::getClassType().getId(), CGFragmentProgramChunk::GLIdFieldMask);

    CGFragmentProgramChunkPtr tmpPtr(*this);
    beginEditCP(tmpPtr, CGFragmentProgramChunk::GLIdFieldMask);
        setGLId(Window::registerGLObject(osgTypedMethodVoidFunctor2ObjCPtrPtr<CGFragmentProgramChunkPtr,
                                         Window , UInt32>(tmpPtr, &CGFragmentProgramChunk::handleGL), 1));
    endEditCP(tmpPtr, CGFragmentProgramChunk::GLIdFieldMask);
}

void CGFragmentProgramChunk::onDestroy(void)
{
    if(cgIsProgram(_fProgram))
        cgDestroyProgram(_fProgram);
    if(cgIsContext(_context))
        cgDestroyContext(_context);
        
    if(getGLId() > 0)
        Window::destroyGLObject(getGLId(), 1);
}

const StateChunkClass *CGFragmentProgramChunk::getClass(void) const
{
    return &_class;
}

/*----------------------------- class specific ----------------------------*/

void CGFragmentProgramChunk::changed(BitVector whichField, UInt32 origin)
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

void CGFragmentProgramChunk::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CGFragmentProgramChunk NI" << std::endl;
}

/*! GL object handler
    create the program and destroy it
*/
void CGFragmentProgramChunk::handleGL(Window */*win*/, UInt32 idstatus)
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
            CGparameter fpparam = cgGetNamedParameter(_fProgram, getParamNames()[i].c_str());
            Vec4f &val = getParamValues()[i];
            if(fpparam != 0)
                cgGLSetParameter4fv(fpparam, val.getValues());
        }
    }
    else
    {
        SWARNING << "CGFragmentProgramChunk(" << this << "::handleGL: Illegal mode: "
             << mode << " for id " << id << std::endl;
    }
}

void CGFragmentProgramChunk::updateCGContext(void)
{
    if(_context == NULL)
        _context = cgCreateContext();
    
    _current_context = _context;

    // can't do this in onCreate()
    
    if(getProfile() == CG_PROFILE_UNKNOWN)
        setProfile(cgGLGetLatestProfile(CG_GL_FRAGMENT));
    cgGLSetOptimalOptions((CGprofile) getProfile());
    
    // reload programs
    if(hasFP() && !getProgram().empty())
    {
        if(cgIsProgram(_fProgram))
            cgDestroyProgram(_fProgram);

        _fProgram = cgCreateProgram(_context, CG_SOURCE, getProgram().c_str(),
                                    (CGprofile) getProfile(), NULL, NULL);
        if(cgIsProgram(_fProgram))
        {
            _fp_isvalid = true;
            cgGLLoadProgram(_fProgram);
        }
        else
        {
            _fp_isvalid = false;
            FWARNING(("Couldn't load fragment program!\n"));
        }
    }
}

/*------------------------------ State ------------------------------------*/

void CGFragmentProgramChunk::activate(DrawActionBase *action, UInt32 /*idx*/)
{
    _current_context = _context;

    action->getWindow()->validateGLObject(getGLId());

    if(_fp_isvalid)
    {
        cgGLEnableProfile((CGprofile) getProfile());
        cgGLBindProgram(_fProgram);
    }
}




void CGFragmentProgramChunk::changeFrom(DrawActionBase *action, StateChunk * old_chunk,
                                UInt32 /*idx*/)
{
    CGFragmentProgramChunk *old = dynamic_cast<CGFragmentProgramChunk *>(old_chunk);

    if(old == NULL)
    {
        FWARNING(( "CGFragmentProgramChunk::changeFrom: caught non-CGFragmentProgramChunk!\n"));
        return;
    }

    _current_context = _context;

    action->getWindow()->validateGLObject(getGLId());

    if(_fp_isvalid)
    {
        cgGLEnableProfile((CGprofile) getProfile());
        cgGLBindProgram(_fProgram);
    }
}


void CGFragmentProgramChunk::deactivate(DrawActionBase */*action*/, UInt32 /*idx*/)
{
    if(_fp_isvalid)
        cgGLDisableProfile((CGprofile) getProfile());
}

/*-------------------------- Comparison -----------------------------------*/

Real32 CGFragmentProgramChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

bool CGFragmentProgramChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool CGFragmentProgramChunk::operator == (const StateChunk &other) const
{
    return CGProgramChunk::operator==(other);
    
/*
    CGProgramChunk const *tother = dynamic_cast<CGProgramChunk const*>(&other);

    if(!tother)
        return false;

    return (this == tother);
*/
}

bool CGFragmentProgramChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}

bool CGFragmentProgramChunk::hasFP(void)
{
    if (cgGLIsProfileSupported((CGprofile) getProfile()))
        return true;

    SWARNING << "Fragment programming extensions "
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGCGFragmentProgramChunk.cpp,v 1.2 2004/03/11 14:32:35 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGCGFRAGMENTPROGRAMCHUNKBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCGFRAGMENTPROGRAMCHUNKBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCGFRAGMENTPROGRAMCHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif
