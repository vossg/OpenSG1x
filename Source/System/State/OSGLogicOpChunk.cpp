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

#include "OSGLogicOpChunk.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::LogicOpChunk
This StateChunk wraps the state associated with the glLogicOp function.
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass LogicOpChunk::_class("LogicOp");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void LogicOpChunk::initMethod (void)
{
    Inherited::initMethod();
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

LogicOpChunk::LogicOpChunk(void) :
    Inherited()
{
}

LogicOpChunk::LogicOpChunk(const LogicOpChunk &source) :
    Inherited(source)
{
}

LogicOpChunk::~LogicOpChunk(void)
{
}

/*------------------------- Chunk Class Access ---------------------------*/

const StateChunkClass *LogicOpChunk::getClass(void) const
{
    return &_class;
}

/*------------------------------- Sync -----------------------------------*/

void LogicOpChunk::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

/*------------------------------ Output ----------------------------------*/

void LogicOpChunk::dump(       UInt32,
                         const BitVector) const
{
    SLOG << "Dump LogicOpChunk NI" << std::endl;
}

/*------------------------------ State ------------------------------------*/

void LogicOpChunk::activate(DrawActionBase *, UInt32)
{
    if(_sfLogicOp.getValue() != GL_COPY)
    {
        glEnable (GL_COLOR_LOGIC_OP    );
        glLogicOp(_sfLogicOp.getValue());
    }
}

void LogicOpChunk::changeFrom( DrawActionBase *act, StateChunk * old_chunk, UInt32 index )
{
    old_chunk->deactivate( act, index );
    activate( act, index );
}

void LogicOpChunk::deactivate ( DrawActionBase *, UInt32 )
{
    if(_sfLogicOp.getValue() != GL_COPY)
    {
        glDisable(GL_COLOR_LOGIC_OP);
        glLogicOp(GL_COPY          );
    }
}

/*-------------------------- Comparison -----------------------------------*/

Real32 LogicOpChunk::switchCost(StateChunk *)
{
    return 0;
}

/** \brief assignment
 */

bool LogicOpChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

/** \brief equal
 */

bool LogicOpChunk::operator == (const StateChunk &other) const
{
    LogicOpChunk const *tother = dynamic_cast<LogicOpChunk const*>(&other);

    if(!tother)
        return false;

    if(tother == this)
        return true;
    
    if(getLogicOp() != tother->getLogicOp())
        return false;

    return true;
}

/** \brief unequal
 */

bool LogicOpChunk::operator != (const StateChunk &other) const
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGLogicOpChunk.cpp,v 1.1 2007/06/25 14:32:45 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGLOGICOPCHUNKBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGLOGICOPCHUNKBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGLOGICOPCHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

