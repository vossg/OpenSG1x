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

#include "OSGShadeModelChunk.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ShadeModelChunk
ShadeModelChunk controls the shading model used for rendering lines and filled polygons.     
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass ShadeModelChunk::_class("ShadeModel");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ShadeModelChunk::initMethod (void)
{
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

ShadeModelChunk::ShadeModelChunk(void) :
    Inherited()
{
}

ShadeModelChunk::ShadeModelChunk(const ShadeModelChunk &source) :
    Inherited(source)
{
}

ShadeModelChunk::~ShadeModelChunk(void)
{
}

/*------------------------- Chunk Class Access ---------------------------*/

const StateChunkClass *ShadeModelChunk::getClass(void) const
{
    return &_class;
}

/*------------------------------- Sync -----------------------------------*/

void ShadeModelChunk::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

/*------------------------------ Output ----------------------------------*/

void ShadeModelChunk::dump(      UInt32,
                           const BitVector ) const
{
    SLOG << "Dump ShadeModelChunk NI" << std::endl;
}

/*------------------------------ State ------------------------------------*/

void ShadeModelChunk::activate(DrawActionBase * action, UInt32 idx)
{
    if(getShadeModel() != GL_SMOOTH)
        glShadeModel(getShadeModel());
}

void ShadeModelChunk::changeFrom(DrawActionBase *action, StateChunk *old_chunk, UInt32 idx)
{
    ShadeModelChunk *old = dynamic_cast<ShadeModelChunk *>(old_chunk);

    if(old == NULL)
    {
        FWARNING(("ShadeModelChunk::changeFrom: caught non-ShadeModelChunk!\n"));
        return;
    }

    // ShadeModelChunk didn't change so do nothing.
    if(old == this)
        return;
    
    if(old->getShadeModel() != getShadeModel())
        glShadeModel(getShadeModel());
}

void ShadeModelChunk::deactivate(DrawActionBase * action, UInt32 idx )
{
    if(getShadeModel() != GL_SMOOTH)
        glShadeModel(GL_SMOOTH);
}


/*-------------------------- Comparison -----------------------------------*/

Real32 ShadeModelChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

bool ShadeModelChunk::operator <(const StateChunk &other) const
{
    return this < &other;
}

bool ShadeModelChunk::operator ==(const StateChunk &other) const
{
    ShadeModelChunk const *tother = 
            dynamic_cast<ShadeModelChunk const*>(&other);

    if(!tother)
        return false;

    if(tother == this)
        return true;

    return true;
}

bool ShadeModelChunk::operator !=(const StateChunk &other) const
{
    return !(*this == other);
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGShadeModelChunk.cpp,v 1.1 2008/08/04 02:39:05 vossg Exp $";
    static Char8 cvsid_hpp       [] = OSGSHADEMODELCHUNKBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGSHADEMODELCHUNKBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGSHADEMODELCHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

