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

#include "OSGCGProgramChunk.h"

OSG_USING_NAMESPACE

CGcontext CGProgramChunk::_current_context = NULL;
    
/*! \class osg::CGProgramChunk

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass CGProgramChunk::_class("CGProgram");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CGProgramChunk::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void CGProgramChunk::cgErrorCallback(void)
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

CGProgramChunk::CGProgramChunk(void) :
    Inherited(),
    _context(NULL)
{
}

CGProgramChunk::CGProgramChunk(const CGProgramChunk &source) :
    Inherited(source),
    _context(source._context)
{
}

CGProgramChunk::~CGProgramChunk(void)
{
}

void CGProgramChunk::onCreate(const CGProgramChunk */*source*/)
{
    // ignore prototypes.
    if(GlobalSystemState == Startup)
        return;

    cgSetErrorCallback(CGProgramChunk::cgErrorCallback);
}

void CGProgramChunk::onDestroy(void)
{
}

const StateChunkClass *CGProgramChunk::getClass(void) const
{
    return &_class;
}

/*----------------------------- class specific ----------------------------*/

void CGProgramChunk::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void CGProgramChunk::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CGProgramChunk NI" << std::endl;
}

/*---------------------------- Access ------------------------------------*/

/*! Read the program string from the given file
*/
bool CGProgramChunk::readProgram(const char *file)
{
    std::ifstream s(file);
    
    if(s.good())
    {
        return readProgram(s);
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
bool CGProgramChunk::readProgram(std::istream &stream)
{
#define BUFSIZE 200
    
    getProgram().erase();    
    char buf[BUFSIZE];

    if(!stream.good())
    {
        FWARNING(("ProgramChunk::read: stream is not good!\n"));
        return true;
   
    }
    
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
bool CGProgramChunk::addParameter(const char   *name, 
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
    
const Vec4f& CGProgramChunk::getParameter(Int16 index)
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
bool CGProgramChunk::setParameter(Int16 index, const Vec4f& value)
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
Int16 CGProgramChunk::findParameter(const std::string &name)
{
    MField<std::string>::iterator it;
    
    it = std::find(getParamNames().begin(), getParamNames().end(), name);

    if(it == getParamNames().end())
        return -1;

    return it - getParamNames().begin();
}

/*-------------------------- Comparison -----------------------------------*/

Real32 CGProgramChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

bool CGProgramChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool CGProgramChunk::operator == (const StateChunk &other) const
{
    CGProgramChunk const *tother = dynamic_cast<CGProgramChunk const*>(&other);

    if(!tother)
        return false;

    if(getProgram() != tother->getProgram() ||
       getProfile() != tother->getProfile() ||
       getParamValues().size() != tother->getParamValues().size() ||
       getParamNames().size()  != tother->getParamNames().size())
        return false;

    return true;
}

bool CGProgramChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}

void CGProgramChunk::parseProgramParams(CGprogram prog)
{
    parseParams(cgGetFirstParameter(prog, CG_PROGRAM));
}

void CGProgramChunk::parseParams(CGparameter param)
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGCGProgramChunk.cpp,v 1.1 2004/02/29 18:40:35 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGCGPROGRAMCHUNKBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCGPROGRAMCHUNKBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCGPROGRAMCHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif
