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

#include "OSGShaderChunk.h"

#include <OSGShaderParameter.h>
#include <OSGShaderParameterBool.h>
#include <OSGShaderParameterInt.h>
#include <OSGShaderParameterReal.h>
#include <OSGShaderParameterVec2f.h>
#include <OSGShaderParameterVec3f.h>
#include <OSGShaderParameterVec4f.h>
#include <OSGShaderParameterMatrix.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ShaderChunk

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ShaderChunk::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ShaderChunk::ShaderChunk(void) :
    Inherited(),
    _parameter_access(NULL)
{
}

ShaderChunk::ShaderChunk(const ShaderChunk &source) :
    Inherited(source),
    _parameter_access(source._parameter_access)
{
}

ShaderChunk::~ShaderChunk(void)
{
}

void ShaderChunk::onCreate(const ShaderChunk */*source*/)
{
    // ignore prototypes.
    if(GlobalSystemState == Startup)
        return;

    _parameter_access = new ShaderParameterAccess(getParameters());
}

void ShaderChunk::onDestroy(void)
{
    if(_parameter_access != NULL)
        delete _parameter_access;
}

/*----------------------------- class specific ----------------------------*/

void ShaderChunk::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ShaderChunk::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ShaderChunk NI" << std::endl;
}

/*---------------------------------- Access -------------------------------*/

/*! Read the program string from the given file
*/
bool ShaderChunk::readVertexProgram(const char *file)
{
    std::ifstream s(file);
    
    if(s.good())
    {
        return readVertexProgram(s);
    }
    else
    {
        FWARNING(("ShaderChunk::readVertexProgram: couldn't open '%s' for reading!\n",
                  file));
        return false;
    }
}

/*! Read the program string from the given stream
*/
bool ShaderChunk::readVertexProgram(std::istream &stream)
{
#define BUFSIZE 200
    
    getVertexProgram().erase();    
    char buf[BUFSIZE];

    if(!stream.good())
    {
        FWARNING(("SHLChunk::readVertexProgram: stream is not good!\n"));
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
bool ShaderChunk::readFragmentProgram(const char *file)
{
    std::ifstream s(file);
    
    if(s.good())
    {
        return readFragmentProgram(s);
    }
    else
    {
        FWARNING(("ShaderChunk::readFragmentProgram: couldn't open '%s' for reading!\n",
                  file));
        return false;
    }
}

/*! Read the program string from the given stream
*/
bool ShaderChunk::readFragmentProgram(std::istream &stream)
{
#define BUFSIZE 200
    
    getFragmentProgram().erase();    
    char buf[BUFSIZE];

    if(!stream.good())
    {
        FWARNING(("SHLChunk::readFragmentProgram: stream is not good!\n"));
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

/*------------------------------------ Set --------------------------------*/

bool ShaderChunk::setUniformParameter(const char *name, bool value)
{
    return _parameter_access->setParameter<ShaderParameterBool>(name, value);
}

bool ShaderChunk::setUniformParameter(const char *name, Int32 value)
{
    return _parameter_access->setParameter<ShaderParameterInt>(name, value);
}

bool ShaderChunk::setUniformParameter(const char *name, Real32 value)
{
    return _parameter_access->setParameter<ShaderParameterReal>(name, value);
}

bool ShaderChunk::setUniformParameter(const char *name, const Vec2f &value)
{
    return _parameter_access->setParameter<ShaderParameterVec2f>(name, value);
}

bool ShaderChunk::setUniformParameter(const char *name, const Vec3f &value)
{
    return _parameter_access->setParameter<ShaderParameterVec3f>(name, value);
}

bool ShaderChunk::setUniformParameter(const char *name, const Vec4f &value)
{
    return _parameter_access->setParameter<ShaderParameterVec4f>(name, value);
}

bool ShaderChunk::setUniformParameter(const char *name, const Matrix &value)
{
    return _parameter_access->setParameter<ShaderParameterMatrix>(name, value);
}

/*------------------------------------ Get --------------------------------*/

bool ShaderChunk::getUniformParameter(const char *name, bool &value)
{
    return _parameter_access->getParameter<ShaderParameterBool>(name, value);
}

bool ShaderChunk::getUniformParameter(const char *name, Int32 &value)
{
    return _parameter_access->getParameter<ShaderParameterInt>(name, value);
}

bool ShaderChunk::getUniformParameter(const char *name, Real32 &value)
{
    return _parameter_access->getParameter<ShaderParameterReal>(name, value);
}

bool ShaderChunk::getUniformParameter(const char *name, Vec2f &value)
{
    return _parameter_access->getParameter<ShaderParameterVec2f>(name, value);
}

bool ShaderChunk::getUniformParameter(const char *name, Vec3f &value)
{
    return _parameter_access->getParameter<ShaderParameterVec3f>(name, value);
}

bool ShaderChunk::getUniformParameter(const char *name, Vec4f &value)
{
    return _parameter_access->getParameter<ShaderParameterVec4f>(name, value);
}

bool ShaderChunk::getUniformParameter(const char *name, Matrix &value)
{
    return _parameter_access->getParameter<ShaderParameterMatrix>(name, value);
}

bool ShaderChunk::subUniformParameter(const char *name)
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGShaderChunk.cpp,v 1.2 2004/07/02 17:59:45 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGSHADERCHUNKBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSHADERCHUNKBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSHADERCHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

