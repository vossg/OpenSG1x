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

#include "OSGShaderParameterMVec2f.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ShaderParameterMVec2f

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ShaderParameterMVec2f::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ShaderParameterMVec2f::ShaderParameterMVec2f(void) :
    Inherited()
{
    setTypeId(ShaderParameter::SHPTypeMVec2f);
}

ShaderParameterMVec2f::ShaderParameterMVec2f(const ShaderParameterMVec2f &source) :
    Inherited(source)
{
}

ShaderParameterMVec2f::~ShaderParameterMVec2f(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ShaderParameterMVec2f::changed(BitVector whichField, UInt32 origin)
{
    if(whichField & ShaderParameterMVec2f::ValueFieldMask)
        setChanged();

    Inherited::changed(whichField, origin);
}

void ShaderParameterMVec2f::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ShaderParameterMVec2f NI" << std::endl;
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGShaderParameterMVec2f.cpp,v 1.1 2007/03/09 18:11:48 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGSHADERPARAMETERMVEC2FBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSHADERPARAMETERMVEC2FBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSHADERPARAMETERMVEC2FFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

