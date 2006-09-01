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

#include <OSGSHLChunk.h>

#include "OSGSHLParameterChunk.h"

OSG_USING_NAMESPACE


/*! \class osg::SHLParameterChunk

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass SHLParameterChunk::_class("SHLParameter");

UInt32 SHLParameterChunk::_shl_extension;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SHLParameterChunk::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

SHLParameterChunk::SHLParameterChunk(void) :
    Inherited()
{
}

SHLParameterChunk::SHLParameterChunk(const SHLParameterChunk &source) :
    Inherited(source)
{
    _shl_extension = Window::registerExtension("GL_ARB_shading_language_100");
}

SHLParameterChunk::~SHLParameterChunk(void)
{
}

const StateChunkClass *SHLParameterChunk::getClass(void) const
{
    return &_class;
}

/*----------------------------- class specific ----------------------------*/

void SHLParameterChunk::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void SHLParameterChunk::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SHLParameterChunk NI" << std::endl;
}

/*------------------------------ State ------------------------------------*/

void SHLParameterChunk::activate(DrawActionBase *action, UInt32 /*idx*/)
{
    if(!action->getWindow()->hasExtension(_shl_extension))
    {
        FWARNING(("OpenGL Shading Language is not supported, couldn't find extension 'GL_ARB_shading_language_100'!\n"));
        return;
    }
    updateParameters(action->getWindow());
}

void SHLParameterChunk::changeFrom(DrawActionBase *action, StateChunk * old_chunk,
                                UInt32 /*idx*/)
{
    SHLParameterChunk *old = dynamic_cast<SHLParameterChunk *>(old_chunk);
    
    // SHLParameterChunk didn't change so do nothing.
    if(old == this)
        return;

    if(!action->getWindow()->hasExtension(_shl_extension))
    {
        FWARNING(("OpenGL Shading Language is not supported, couldn't find extension 'GL_ARB_shading_language_100'!\n"));
        return;
    }

    if(old == NULL)
    {
        FWARNING(( "SHLParameterChunk::changeFrom: caught non-SHLParameterChunk!\n"));
        return;
    }

    updateParameters(action->getWindow());
}


void SHLParameterChunk::deactivate(DrawActionBase *OSG_CHECK_ARG(action), UInt32 OSG_CHECK_ARG(idx))
{
}

/*-------------------------- Comparison -----------------------------------*/

Real32 SHLParameterChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

bool SHLParameterChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool SHLParameterChunk::operator == (const StateChunk &other) const
{
    SHLParameterChunk const *tother = dynamic_cast<SHLParameterChunk const*>(&other);

    if(!tother)
        return false;

    if(getParameters().size() != tother->getParameters().size())
        return false;

    return true;
}

bool SHLParameterChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGSHLParameterChunk.cpp,v 1.4 2006/09/01 16:39:42 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGSHLPARAMETERCHUNKBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSHLPARAMETERCHUNKBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSHLPARAMETERCHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif
