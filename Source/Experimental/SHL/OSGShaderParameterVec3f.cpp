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

#include "OSGShaderParameterVec3f.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ShaderParameterVec3f

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ShaderParameterVec3f::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ShaderParameterVec3f::ShaderParameterVec3f(void) :
    Inherited()
{
}

ShaderParameterVec3f::ShaderParameterVec3f(const ShaderParameterVec3f &source) :
    Inherited(source)
{
}

ShaderParameterVec3f::~ShaderParameterVec3f(void)
{
}

void ShaderParameterVec3f::onCreate(const ShaderParameterVec3f */*source*/)
{
    // ignore prototypes.
    if(GlobalSystemState == Startup)
        return;

    ShaderParameterVec3fPtr tmpPtr(*this);
    beginEditCP(tmpPtr, ShaderParameterVec3f::TypeIdFieldMask);
        setTypeId(ShaderParameter::SHPTypeVec3f);
    endEditCP(tmpPtr, ShaderParameterVec3f::TypeIdFieldMask);
}

/*----------------------------- class specific ----------------------------*/

void ShaderParameterVec3f::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ShaderParameterVec3f::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ShaderParameterVec3f NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGShaderParameterVec3f.cpp,v 1.1 2004/06/05 18:16:44 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGSHADERPARAMETERVEC3FBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSHADERPARAMETERVEC3FBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSHADERPARAMETERVEC3FFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif
