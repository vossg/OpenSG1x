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

#include "OSGShaderParameterChunk.h"

#include <OSGShaderParameter.h>
#include <OSGShaderParameterBool.h>
#include <OSGShaderParameterInt.h>
#include <OSGShaderParameterReal.h>
#include <OSGShaderParameterVec2f.h>
#include <OSGShaderParameterVec3f.h>
#include <OSGShaderParameterVec4f.h>
#include <OSGShaderParameterMatrix.h>

#include <OSGShaderParameterMInt.h>
#include <OSGShaderParameterMReal.h>
#include <OSGShaderParameterMVec2f.h>
#include <OSGShaderParameterMVec3f.h>
#include <OSGShaderParameterMVec4f.h>
#include <OSGShaderParameterMMatrix.h>


OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ShaderParameterChunk

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ShaderParameterChunk::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ShaderParameterChunk::ShaderParameterChunk(void) :
    Inherited(),
    _parameter_access(NULL)
{
}

ShaderParameterChunk::ShaderParameterChunk(const ShaderParameterChunk &source) :
    Inherited(source),
    _parameter_access(source._parameter_access)
{
}

ShaderParameterChunk::~ShaderParameterChunk(void)
{
}

void ShaderParameterChunk::onCreate(const ShaderParameterChunk *source)
{
    Inherited::onCreate(source);

    // ignore prototypes.
    if(GlobalSystemState == Startup)
        return;

    _parameter_access = new ShaderParameterAccess(getParameters());
}

void ShaderParameterChunk::onDestroy(void)
{
    Inherited::onDestroy();

    if(_parameter_access != NULL)
        delete _parameter_access;
}

/*----------------------------- class specific ----------------------------*/

void ShaderParameterChunk::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ShaderParameterChunk::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ShaderParameterChunk NI" << std::endl;
}

/*---------------------------------- Access -------------------------------*/


/*------------------------------------ Set --------------------------------*/

bool ShaderParameterChunk::setUniformParameter(const char *name, bool value)
{
    return _parameter_access->setParameter<ShaderParameterBool>(name, value);
}

bool ShaderParameterChunk::setUniformParameter(const char *name, Int32 value)
{
    return _parameter_access->setParameter<ShaderParameterInt>(name, value);
}

bool ShaderParameterChunk::setUniformParameter(const char *name, Real32 value)
{
    return _parameter_access->setParameter<ShaderParameterReal>(name, value);
}

bool ShaderParameterChunk::setUniformParameter(const char *name, const Vec2f &value)
{
    return _parameter_access->setParameter<ShaderParameterVec2f>(name, value);
}

bool ShaderParameterChunk::setUniformParameter(const char *name, const Vec3f &value)
{
    return _parameter_access->setParameter<ShaderParameterVec3f>(name, value);
}

bool ShaderParameterChunk::setUniformParameter(const char *name, const Vec4f &value)
{
    return _parameter_access->setParameter<ShaderParameterVec4f>(name, value);
}

bool ShaderParameterChunk::setUniformParameter(const char *name, const Matrix &value)
{
    return _parameter_access->setParameter<ShaderParameterMatrix>(name, value);
}

// arrays

bool ShaderParameterChunk::setUniformParameter(const char *name, const MFInt32 &value)
{
    return _parameter_access->setMParameter<ShaderParameterMInt>(name, value);
}

bool ShaderParameterChunk::setUniformParameter(const char *name, const MFReal32 &value)
{
    return _parameter_access->setMParameter<ShaderParameterMReal>(name, value);
}

bool ShaderParameterChunk::setUniformParameter(const char *name, const MFVec2f &value)
{
    return _parameter_access->setMParameter<ShaderParameterMVec2f>(name, value);
}

bool ShaderParameterChunk::setUniformParameter(const char *name, const MFVec3f &value)
{
    return _parameter_access->setMParameter<ShaderParameterMVec3f>(name, value);
}

bool ShaderParameterChunk::setUniformParameter(const char *name, const MFVec4f &value)
{
    return _parameter_access->setMParameter<ShaderParameterMVec4f>(name, value);
}

bool ShaderParameterChunk::setUniformParameter(const char *name, const MFMatrix &value)
{
    return _parameter_access->setMParameter<ShaderParameterMMatrix>(name, value);
}

/*------------------------------------ Get --------------------------------*/

bool ShaderParameterChunk::getUniformParameter(const char *name, bool &value)
{
    return _parameter_access->getParameter<ShaderParameterBool>(name, value);
}

bool ShaderParameterChunk::getUniformParameter(const char *name, Int32 &value)
{
    return _parameter_access->getParameter<ShaderParameterInt>(name, value);
}

bool ShaderParameterChunk::getUniformParameter(const char *name, Real32 &value)
{
    return _parameter_access->getParameter<ShaderParameterReal>(name, value);
}

bool ShaderParameterChunk::getUniformParameter(const char *name, Vec2f &value)
{
    return _parameter_access->getParameter<ShaderParameterVec2f>(name, value);
}

bool ShaderParameterChunk::getUniformParameter(const char *name, Vec3f &value)
{
    return _parameter_access->getParameter<ShaderParameterVec3f>(name, value);
}

bool ShaderParameterChunk::getUniformParameter(const char *name, Vec4f &value)
{
    return _parameter_access->getParameter<ShaderParameterVec4f>(name, value);
}

bool ShaderParameterChunk::getUniformParameter(const char *name, Matrix &value)
{
    return _parameter_access->getParameter<ShaderParameterMatrix>(name, value);
}

bool ShaderParameterChunk::subUniformParameter(const char *name)
{
    return _parameter_access->subParameter(name);
}

// arrays

bool ShaderParameterChunk::getUniformParameter(const char *name, MFInt32 &value)
{
    return _parameter_access->getParameter<ShaderParameterMInt>(name, value);
}

bool ShaderParameterChunk::getUniformParameter(const char *name, MFReal32 &value)
{
    return _parameter_access->getParameter<ShaderParameterMReal>(name, value);
}

bool ShaderParameterChunk::getUniformParameter(const char *name, MFVec2f &value)
{
    return _parameter_access->getParameter<ShaderParameterMVec2f>(name, value);
}

bool ShaderParameterChunk::getUniformParameter(const char *name, MFVec3f &value)
{
    return _parameter_access->getParameter<ShaderParameterMVec3f>(name, value);
}

bool ShaderParameterChunk::getUniformParameter(const char *name, MFVec4f &value)
{
    return _parameter_access->getParameter<ShaderParameterMVec4f>(name, value);
}

bool ShaderParameterChunk::getUniformParameter(const char *name, MFMatrix &value)
{
    return _parameter_access->getParameter<ShaderParameterMMatrix>(name, value);
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGShaderParameterChunk.cpp,v 1.2 2007/03/09 18:11:48 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGSHADERPARAMETERCHUNKBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSHADERPARAMETERCHUNKBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSHADERPARAMETERCHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif
