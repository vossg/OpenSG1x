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
    _contexts()
{
}

CGChunk::CGChunk(const CGChunk &source) :
    Inherited(source),
    _contexts()
{
}

CGChunk::~CGChunk(void)
{
}

void CGChunk::onCreate(const CGChunk *source)
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
    for(std::map<Window *, cgS>::iterator i = _contexts.begin();i != _contexts.end();++i)
    {
    	cgS cg = (*i).second;
    	if(cgIsProgram(cg.vProgram))
            cgDestroyProgram(cg.vProgram);
        if(cgIsProgram(cg.fProgram))
            cgDestroyProgram(cg.fProgram);
        if(cgIsContext(cg.context))
            cgDestroyContext(cg.context);
    }

    if(getGLId() > 0)
        Window::destroyGLObject(getGLId(), 1);
}

/*------------------------- Chunk Class Access ---------------------------*/

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
        updateCGContexts();
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
void CGChunk::handleGL(Window *win, UInt32 idstatus)
{
    Window::GLObjectStatusE mode;
    UInt32 id;

    Window::unpackIdStatus(idstatus, id, mode);

    // ACHTUNG da ich nicht mitbekomme wenn ein gl fenster zerstoert wird
    // und das neue fenster auch den gleichen pointer wie das alte hat,
    // fange ich das beim neu erzeugen eines gl fensters ab!
    if(mode == Window::initialize)
    {
        cgMapIt i = _contexts.find(win);
        if(i == _contexts.end())
            i = createCGContext(win);
        else
            createCGContext(win); // update old pointer with new program.

        _current_context = (*i).second.context;
    }
}

void CGChunk::updateCGContexts(void)
{
	for(std::map<Window *, cgS>::iterator i = _contexts.begin();i != _contexts.end();++i)
	{
		updateCGContext((*i).first);
    }
}

CGChunk::cgMapIt CGChunk::createCGContext(Window *win)
{
    // create a new cg context.
    cgS cg;
    cg.context = cgCreateContext();
    cg.vProgram = NULL;
    cg.fProgram = NULL;
    cg.vp_isvalid = false;
    cg.fp_isvalid = false;

    _current_context = cg.context;

    if(hasVP() && !getVertexProgram().empty())
    {
        cg.vProgram = cgCreateProgram(cg.context, CG_SOURCE, getVertexProgram().c_str(),
                                      CG_PROFILE_ARBVP1, NULL, NULL);

        if(cgIsProgram(cg.vProgram))
        {
            cg.vp_isvalid = true;
            cgGLLoadProgram(cg.vProgram);
        }
        else
        {
            FWARNING(("Couldn't load vertex program!\n"));
        }
    }

    if(hasFP() && !getFragmentProgram().empty())
    {
        cg.fProgram = cgCreateProgram(cg.context, CG_SOURCE, getFragmentProgram().c_str(),
                                      CG_PROFILE_ARBFP1, NULL, NULL);
        if(cgIsProgram(cg.fProgram))
        {
            cg.fp_isvalid = true;
            cgGLLoadProgram(cg.fProgram);
        }
        else
        {
            FWARNING(("Couldn't load fragment program!\n"));
        }
    }
    _contexts.insert(std::pair<Window *, cgS>(win, cg));
    return _contexts.find(win);
}

void CGChunk::updateCGContext(Window *win)
{
    cgMapIt i = _contexts.find(win);
    if(i == _contexts.end())
    {
    	FWARNING(("Couldn't update context!\n"));
    	return;
    }

    _current_context = (*i).second.context;

    // reload programs
    if(hasVP() && !getVertexProgram().empty())
    {
        if(cgIsProgram((*i).second.vProgram))
            cgDestroyProgram((*i).second.vProgram);

        (*i).second.vProgram = cgCreateProgram((*i).second.context, CG_SOURCE, getVertexProgram().c_str(),
                                               CG_PROFILE_ARBVP1, NULL, NULL);
        if(cgIsProgram((*i).second.vProgram))
        {
            (*i).second.vp_isvalid = true;
            cgGLLoadProgram((*i).second.vProgram);
        }
        else
        {
            (*i).second.vp_isvalid = false;
            FWARNING(("Couldn't load vertex program!\n"));
        }
    }

    if(hasFP() && !getFragmentProgram().empty())
    {
        if(cgIsProgram((*i).second.fProgram))
            cgDestroyProgram((*i).second.fProgram);

        (*i).second.fProgram = cgCreateProgram((*i).second.context, CG_SOURCE, getFragmentProgram().c_str(),
                                               CG_PROFILE_ARBFP1, NULL, NULL);
        if(cgIsProgram((*i).second.fProgram))
        {
            (*i).second.fp_isvalid = true;
            cgGLLoadProgram((*i).second.fProgram);
        }
        else
        {
            (*i).second.fp_isvalid = false;
            FWARNING(("Couldn't load fragment program!\n"));
        }
    }
}

/*------------------------------ State ------------------------------------*/

void CGChunk::activate(DrawActionBase *action, UInt32 idx)
{
    cgMapIt i = _contexts.find(action->getWindow());

    // Ok das wird normalerweise in handleGL gemacht allerdings im cluster
    // (auf der serverseite) wird handleGL nicht aufgerufen!
    if(i == _contexts.end())
    	i = createCGContext(action->getWindow());

    _current_context = (*i).second.context;

    action->getWindow()->validateGLObject(getGLId());

    if((*i).second.vp_isvalid)
    {
        cgGLEnableProfile(CG_PROFILE_ARBVP1);
        cgGLBindProgram((*i).second.vProgram);
    }

    if((*i).second.fp_isvalid)
    {
        cgGLEnableProfile(CG_PROFILE_ARBFP1);
        cgGLBindProgram((*i).second.fProgram);
    }
}




void CGChunk::changeFrom(DrawActionBase *action, StateChunk * old_chunk,
                                UInt32 idx)
{
	CGChunk *old = dynamic_cast<CGChunk *>(old_chunk);

    if(old == NULL)
    {
        FWARNING(( "CGChunk::changeFrom: caught non-CGChunk!\n"));
        return;
    }

    cgMapIt i = _contexts.find(action->getWindow());
    if(i == _contexts.end())
    	i = createCGContext(action->getWindow());

    _current_context = (*i).second.context;

    action->getWindow()->validateGLObject(getGLId());

    if((*i).second.vp_isvalid)
    {
        cgGLEnableProfile(CG_PROFILE_ARBVP1);
        cgGLBindProgram((*i).second.vProgram);
    }

    if((*i).second.fp_isvalid)
    {
        cgGLEnableProfile(CG_PROFILE_ARBFP1);
        cgGLBindProgram((*i).second.fProgram);
    }
}


void CGChunk::deactivate(DrawActionBase *action, UInt32 idx)
{
	cgMapIt i = _contexts.find(action->getWindow());
    if(i == _contexts.end())
    {
    	FWARNING(("CGChunk::deactivate : Couldn't find contex!\n"));
    	return;
    }

    if((*i).second.fp_isvalid)
        cgGLDisableProfile(CG_PROFILE_ARBFP1);

    if((*i).second.vp_isvalid)
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGCGChunk.cpp,v 1.5 2003/05/12 15:15:01 amz Exp $";
    static Char8 cvsid_hpp       [] = OSGCGCHUNKBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCGCHUNKBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCGCHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

