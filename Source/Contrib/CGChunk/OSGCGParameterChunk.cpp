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

#include <OSGCGChunk.h>

#include "OSGCGParameterChunk.h"

OSG_USING_NAMESPACE


/*! \class osg::CGParameterChunk

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass CGParameterChunk::_class("CGParameter");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CGParameterChunk::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CGParameterChunk::CGParameterChunk(void) :
    Inherited()
{
}

CGParameterChunk::CGParameterChunk(const CGParameterChunk &source) :
    Inherited(source)
{
}

CGParameterChunk::~CGParameterChunk(void)
{
}

const StateChunkClass *CGParameterChunk::getClass(void) const
{
    return &_class;
}

/*----------------------------- class specific ----------------------------*/

void CGParameterChunk::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void CGParameterChunk::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump CGParameterChunk NI" << std::endl;
}

/*------------------------------ State ------------------------------------*/

void CGParameterChunk::activate(DrawActionBase *action, UInt32 /*idx*/)
{
    updateParameters(action->getWindow());
}

void CGParameterChunk::changeFrom(DrawActionBase *action, StateChunk * old_chunk,
                                UInt32 /*idx*/)
{
    CGParameterChunk *old = dynamic_cast<CGParameterChunk *>(old_chunk);

    if(old == NULL)
    {
        FWARNING(( "CGParameterChunk::changeFrom: caught non-CGParameterChunk!\n"));
        return;
    }

    // CGParameterChunk didn't change so do nothing.
    if(old == this)
        return;

    updateParameters(action->getWindow());
}


void CGParameterChunk::deactivate(DrawActionBase */*action*/, UInt32 /*idx*/)
{
}

/*-------------------------- Comparison -----------------------------------*/

Real32 CGParameterChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

bool CGParameterChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

bool CGParameterChunk::operator == (const StateChunk &other) const
{
    CGParameterChunk const *tother = dynamic_cast<CGParameterChunk const*>(&other);

    if(!tother)
        return false;

    if(getParameters().size() != tother->getParameters().size())
        return false;

    return true;
}

bool CGParameterChunk::operator != (const StateChunk &other) const
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGCGParameterChunk.cpp,v 1.1 2004/08/27 12:49:19 a-m-z Exp $";
    static Char8 cvsid_hpp       [] = OSGCGPARAMETERCHUNKBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCGPARAMETERCHUNKBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCGPARAMETERCHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif
