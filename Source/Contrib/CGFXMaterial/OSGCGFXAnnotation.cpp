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

#include <OSGShaderParameter.h>
#include <OSGShaderParameterBool.h>
#include <OSGShaderParameterInt.h>
#include <OSGShaderParameterReal.h>
#include <OSGShaderParameterVec2f.h>
#include <OSGShaderParameterVec3f.h>
#include <OSGShaderParameterVec4f.h>
#include <OSGShaderParameterMatrix.h>
#include <OSGShaderParameterString.h>

#include "OSGCGFXAnnotation.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::CGFXAnnotation

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CGFXAnnotation::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CGFXAnnotation::CGFXAnnotation(void) :
    Inherited(),
    _parameter_access(NULL)
{
}

CGFXAnnotation::CGFXAnnotation(const CGFXAnnotation &source) :
    Inherited(source),
    _parameter_access(source._parameter_access)
{
}

CGFXAnnotation::~CGFXAnnotation(void)
{
}

void CGFXAnnotation::onCreate(const CGFXAnnotation *source)
{
    Inherited::onCreate(source);

    // ignore prototypes.
    if(GlobalSystemState == Startup)
        return;

    _parameter_access = new ShaderParameterAccess(getParameters());
}

void CGFXAnnotation::onDestroy(void)
{
    Inherited::onDestroy();

    if(_parameter_access != NULL)
        delete _parameter_access;
}


/*----------------------------- class specific ----------------------------*/

void CGFXAnnotation::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void CGFXAnnotation::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump CGFXAnnotation NI" << std::endl;
}

/*---------------------------------- Access -------------------------------*/


/*------------------------------------ Get --------------------------------*/

bool CGFXAnnotation::getParameter(const char *name, bool &value)
{
    return _parameter_access->getParameter<ShaderParameterBool>(name, value);
}

bool CGFXAnnotation::getParameter(const char *name, Int32 &value)
{
    return _parameter_access->getParameter<ShaderParameterInt>(name, value);
}

bool CGFXAnnotation::getParameter(const char *name, Real32 &value)
{
    return _parameter_access->getParameter<ShaderParameterReal>(name, value);
}

bool CGFXAnnotation::getParameter(const char *name, Vec2f &value)
{
    return _parameter_access->getParameter<ShaderParameterVec2f>(name, value);
}

bool CGFXAnnotation::getParameter(const char *name, Vec3f &value)
{
    return _parameter_access->getParameter<ShaderParameterVec3f>(name, value);
}

bool CGFXAnnotation::getParameter(const char *name, Vec4f &value)
{
    return _parameter_access->getParameter<ShaderParameterVec4f>(name, value);
}

bool CGFXAnnotation::getParameter(const char *name, Matrix &value)
{
    return _parameter_access->getParameter<ShaderParameterMatrix>(name, value);
}

bool CGFXAnnotation::getParameter(const char *name, std::string &value)
{
    return _parameter_access->getParameter<ShaderParameterString>(name, value);
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGCGFXAnnotation.cpp,v 1.1 2005/06/09 14:53:41 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGCGFXANNOTATIONBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCGFXANNOTATIONBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCGFXANNOTATIONFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

