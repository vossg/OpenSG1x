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
CGprofile CGChunk::_vertexProfile = CG_PROFILE_UNKNOWN;
CGprofile CGChunk::_fragmentProfile = CG_PROFILE_UNKNOWN;
    
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
        Window::reinitializeGLObject(getGLId());
    }  
     
    if(whichField & ParamValuesFieldMask)
    {
        Window::refreshGLObject(getGLId());
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
            CGparameter fpparam = cgGetNamedParameter(_fProgram, getParamNames()[i].c_str());
            Vec4f &val = getParamValues()[i];
            if(vpparam != 0)
                cgGLSetParameter4fv(vpparam, val.getValues());
            
            if(fpparam != 0)
                cgGLSetParameter4fv(fpparam, val.getValues());
        }
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
        _context = cgCreateContext();
    
    _current_context = _context;

    // can't do this in onCreate()
    if(_vertexProfile == CG_PROFILE_UNKNOWN)
    {
        // CG_PROFILE_ARBVP1
        _vertexProfile = cgGLGetLatestProfile(CG_GL_VERTEX);
        cgGLSetOptimalOptions(_vertexProfile);
    }
    
    if(_fragmentProfile == CG_PROFILE_UNKNOWN)
    {
        // CG_PROFILE_ARBFP1
        _fragmentProfile = cgGLGetLatestProfile(CG_GL_FRAGMENT);
        cgGLSetOptimalOptions(_fragmentProfile);
    }
    
    // reload programs
    if(hasVP() && !getVertexProgram().empty())
    {
        if(cgIsProgram(_vProgram))
            cgDestroyProgram(_vProgram);

        _vProgram = cgCreateProgram(_context, CG_SOURCE, getVertexProgram().c_str(),
                                    _vertexProfile, NULL, NULL);
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
                                               _fragmentProfile, NULL, NULL);
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

/*---------------------------- Access ------------------------------------*/

/*! Read the program string from the given file
*/
bool CGChunk::readVertexProgram(const char *file)
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
        return true;
    }
}

/*! Read the program string from the given stream
*/
bool CGChunk::readVertexProgram(std::istream &stream)
{
#define BUFSIZE 200
    
    getVertexProgram().erase();    
    char buf[BUFSIZE];

    if(!stream.good())
    {
        FWARNING(("ProgramChunk::read: stream is not good!\n"));
        return true;
   
    }
    
    do
    {
        stream.read(buf, BUFSIZE);
        getVertexProgram().append(buf, stream.gcount());
    }
    while(!stream.eof());
    
    return false;
}

/*! Read the program string from the given file
*/
bool CGChunk::readFragmentProgram(const char *file)
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
        return true;
    }
}

/*! Read the program string from the given stream
*/
bool CGChunk::readFragmentProgram(std::istream &stream)
{
#define BUFSIZE 200
    
    getFragmentProgram().erase();    
    char buf[BUFSIZE];

    if(!stream.good())
    {
        FWARNING(("ProgramChunk::read: stream is not good!\n"));
        return true;
   
    }
    
    do
    {
        stream.read(buf, BUFSIZE);
        getFragmentProgram().append(buf, stream.gcount());
    }
    while(!stream.eof());
    
    return false;
}

/*! Add a named parameter 
*/
bool CGChunk::addParameter(const char   *name, 
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
    
const Vec4f& CGChunk::getParameter(Int16 index)
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
bool CGChunk::setParameter(Int16 index, const Vec4f& value)
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
Int16 CGChunk::findParameter(const std::string &name)
{
    MField<std::string>::iterator it;
    
    it = std::find(getParamNames().begin(), getParamNames().end(), name);

    if(it == getParamNames().end())
        return -1;

    return it - getParamNames().begin();
}

/*------------------------------ State ------------------------------------*/

void CGChunk::activate(DrawActionBase *action, UInt32 /*idx*/)
{
    _current_context = _context;

    action->getWindow()->validateGLObject(getGLId());

    if(_vp_isvalid)
    {
        cgGLEnableProfile(_vertexProfile);
        cgGLBindProgram(_vProgram);
    }

    if(_fp_isvalid)
    {
        cgGLEnableProfile(_fragmentProfile);
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
        cgGLEnableProfile(_vertexProfile);
        cgGLBindProgram(_vProgram);
    }

    if(_fp_isvalid)
    {
        cgGLEnableProfile(_fragmentProfile);
        cgGLBindProgram(_fProgram);
    }
}


void CGChunk::deactivate(DrawActionBase */*action*/, UInt32 /*idx*/)
{
    if(_fp_isvalid)
        cgGLDisableProfile(_fragmentProfile);

    if(_vp_isvalid)
        cgGLDisableProfile(_vertexProfile);
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
       getFragmentProgram() != tother->getFragmentProgram() ||
       getParamValues().size() != tother->getParamValues().size() ||
       getParamNames().size()  != tother->getParamNames().size())
        return false;
    
    

    return true;
}

bool CGChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}


bool CGChunk::hasVP(void)
{
    if(cgGLIsProfileSupported(_vertexProfile))
    {
        return true;
    }
    
    SWARNING << "Vertex programming extensions "
             << cgGetProfileString(_vertexProfile)
             << " not supported!" << std::endl;
    return false;
}

bool CGChunk::hasFP(void)
{
    if (cgGLIsProfileSupported(_fragmentProfile))
        return true;

    SWARNING << "Fragment programming extensions "
             << cgGetProfileString(_fragmentProfile)
             << " not supported!" << std::endl;
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
