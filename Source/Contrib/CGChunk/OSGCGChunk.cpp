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

#include "OSGCGChunk.h"

OSG_USING_NAMESPACE

CGcontext CGChunk::_current_context = NULL;

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
    	if(cgIsContext(_current_context))
    	{
            const char *Listing = cgGetLastListing(_current_context);
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

void CGChunk::onCreate(const CGChunk */*source*/)
{
    // Doesn't work in external shared libraries!
    //if(GlobalSystemState == Startup)
    //    return;

    static bool prototype = true;

    if(prototype)
    {
        prototype = false;
        return;
    }

    // we need this for clustering without it handleGL is never called.
    RemoteAspect::addFieldFilter(CGChunk::getClassType().getId(), CGChunk::GLIdFieldMask);
    
    cgSetErrorCallback(CGChunk::cgErrorCallback);


    CGChunkPtr tmpPtr(*this);
    beginEditCP(tmpPtr, CGChunk::GLIdFieldMask);
        setGLId(Window::registerGLObject(osgTypedMethodVoidFunctor2ObjCPtrPtr<CGChunkPtr,
                                         Window , UInt32>(tmpPtr, &CGChunk::handleGL), 1));
    endEditCP(tmpPtr, CGChunk::GLIdFieldMask);


#if 0
    vLight = cgGetNamedParameter(_vProgram, "light_index");
#endif
}

void CGChunk::onDestroy(void)
{
    if(cgIsProgram(_vProgram))
        cgDestroyProgram(_vProgram);
    if(cgIsProgram(_fProgram))
        cgDestroyProgram(_fProgram);
    if(cgIsContext(_context))
        cgDestroyContext(_context);
        
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
    Inherited::changed(whichField, origin);

    if((whichField & VertexProgramFieldMask) ||
       (whichField & FragmentProgramFieldMask))
    {
        updateCGContext();
    }
}

void CGChunk::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CGChunk NI" << std::endl;
}

/*! GL object handler
    create the program and destroy it
*/
void CGChunk::handleGL(Window */*win*/, UInt32 idstatus)
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
        //SWARNING << "Last program user destroyed" << std::endl;
    }
    else if(mode == Window::initialize || mode == Window::reinitialize ||
            mode == Window::needrefresh)
    {
        if(mode != Window::needrefresh)
        {
            createCGContext();
        }
        
        // set params
    }
    else
    {
        SWARNING << "CGChunk(" << this << "::handleGL: Illegal mode: "
             << mode << " for id " << id << std::endl;
    }
}

void CGChunk::createCGContext(void)
{
    // create a new cg context.
    _context = cgCreateContext();
    _vProgram = NULL;
    _fProgram = NULL;
    _vp_isvalid = false;
    _fp_isvalid = false;

    _current_context = _context;

    if(hasVP() && !getVertexProgram().empty())
    {
        _vProgram = cgCreateProgram(_context, CG_SOURCE, getVertexProgram().c_str(),
                                      CG_PROFILE_ARBVP1, NULL, NULL);

        if(cgIsProgram(_vProgram))
        {
            _vp_isvalid = true;
            cgGLLoadProgram(_vProgram);
            //parseProgramParams(_vProgram);
        }
        else
        {
            FWARNING(("Couldn't load vertex program!\n"));
        }
    }

    if(hasFP() && !getFragmentProgram().empty())
    {
        _fProgram = cgCreateProgram(_context, CG_SOURCE, getFragmentProgram().c_str(),
                                      CG_PROFILE_ARBFP1, NULL, NULL);
        if(cgIsProgram(_fProgram))
        {
            _fp_isvalid = true;
            cgGLLoadProgram(_fProgram);
            //parseProgramParams(_fProgram);
        }
        else
        {
            FWARNING(("Couldn't load fragment program!\n"));
        }
    }
}

void CGChunk::updateCGContext(void)
{
    if(_context == NULL)
        return;

    _current_context = _context;

    // reload programs
    if(hasVP() && !getVertexProgram().empty())
    {
        if(cgIsProgram(_vProgram))
            cgDestroyProgram(_vProgram);

        _vProgram = cgCreateProgram(_context, CG_SOURCE, getVertexProgram().c_str(),
                                    CG_PROFILE_ARBVP1, NULL, NULL);
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

    if(hasFP() && !getFragmentProgram().empty())
    {
        if(cgIsProgram(_fProgram))
            cgDestroyProgram(_fProgram);

        _fProgram = cgCreateProgram(_context, CG_SOURCE, getFragmentProgram().c_str(),
                                               CG_PROFILE_ARBFP1, NULL, NULL);
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

void CGChunk::activate(DrawActionBase *action, UInt32 /*idx*/)
{
    _current_context = _context;

    action->getWindow()->validateGLObject(getGLId());

    if(_vp_isvalid)
    {
        cgGLEnableProfile(CG_PROFILE_ARBVP1);
        cgGLBindProgram(_vProgram);
    }

    if(_fp_isvalid)
    {
        cgGLEnableProfile(CG_PROFILE_ARBFP1);
        cgGLBindProgram(_fProgram);
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

    _current_context = _context;

    action->getWindow()->validateGLObject(getGLId());

    if(_vp_isvalid)
    {
        cgGLEnableProfile(CG_PROFILE_ARBVP1);
        cgGLBindProgram(_vProgram);
    }

    if(_fp_isvalid)
    {
        cgGLEnableProfile(CG_PROFILE_ARBFP1);
        cgGLBindProgram(_fProgram);
    }
}


void CGChunk::deactivate(DrawActionBase */*action*/, UInt32 /*idx*/)
{
    if(_fp_isvalid)
        cgGLDisableProfile(CG_PROFILE_ARBFP1);

    if(_vp_isvalid)
        cgGLDisableProfile(CG_PROFILE_ARBVP1);
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

    if(_sfVertexProgram.getValue() != tother->_sfVertexProgram.getValue())
        return false;
    if(_sfFragmentProgram.getValue() != tother->_sfFragmentProgram.getValue())
        return false;
    if(_sfActiveLightIndex.getValue() != tother->_sfActiveLightIndex.getValue())
        return false;

    return true;
}

bool CGChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}


bool CGChunk::hasVP(void)
{
    if(cgGLIsProfileSupported(CG_PROFILE_ARBVP1))
    {
        return true;
    }

    FWARNING(("Vertex programming extensions GL_ARB_vertex_program not supported.\n"));
    return false;
}

bool CGChunk::hasFP(void)
{
    if (cgGLIsProfileSupported(CG_PROFILE_ARBFP1))
        return true;

    FWARNING(("Fragment programming extensions GL_ARB_fragment_program not supported.\n"));
    return false;
}

void CGChunk::parseProgramParams(CGprogram prog)
{
    parseParams(cgGetFirstParameter(prog, CG_PROGRAM));
}

void CGChunk::parseParams(CGparameter param)
{
    if(!param)
        return;

    do
    {
        switch(cgGetParameterType(param))
        {
            case CG_STRUCT :
                parseParams(cgGetFirstStructParameter(param));
            break;
            case CG_ARRAY :
            {
                int ArraySize = cgGetArraySize(param, 0);
                int i;
                for(i=0; i < ArraySize; ++i)
                    parseParams(cgGetArrayParameter(param, i));
            }
            break;
            default: // Display parameter information
                const char *name = cgGetParameterName(param);
                CGtype paramType = cgGetParameterType(param);
                const char *type = cgGetTypeString(paramType);
                CGresource paramRes = cgGetParameterResource(param);
                const char *resource = cgGetResourceString(paramRes);
                printf("-- Name = '%s'\n", name);
                printf("-- Type = '%s'\n", type);
                printf("-- Resource = '%s'\n\n", resource);
        }
    }
    while((param = cgGetNextParameter(param)) != 0);
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGCGChunk.cpp,v 1.2 2003/07/28 08:44:22 amz Exp $";
    static Char8 cvsid_hpp       [] = OSGCGCHUNKBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCGCHUNKBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCGCHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif
