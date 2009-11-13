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

#include "OSGFogChunk.h"

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::FogChunk
The fog chunk contains the parameters that are specific for rendering fog. 	
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

StateChunkClass FogChunk::_class("Fog");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void FogChunk::initMethod (void)
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

FogChunk::FogChunk(void) :
    Inherited()
{
}

FogChunk::FogChunk(const FogChunk &source) :
    Inherited(source)
{
}

FogChunk::~FogChunk(void)
{
}

/*------------------------- Chunk Class Access ---------------------------*/

const StateChunkClass *FogChunk::getClass(void) const
{
    return &_class;
}

/*----------------------------- class specific ----------------------------*/

void FogChunk::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void FogChunk::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump FogChunk NI" << std::endl;
}

/*------------------------------ State ------------------------------------*/

void FogChunk::activate(DrawActionBase *, UInt32)
{	
    glFogi  (GL_FOG_MODE,    getMode   ()                );
    glFogf  (GL_FOG_DENSITY, getDensity()                );
    glFogf  (GL_FOG_START,   getStart  ()                );
    glFogf  (GL_FOG_END,     getEnd    ()                );
    glFogfv (GL_FOG_COLOR,   getColor  ().getValuesRGBA());

    glEnable(GL_FOG);
}

void FogChunk::changeFrom( DrawActionBase *act, StateChunk * oldChunk, UInt32 index )
{
    oldChunk->deactivate(act, index);
    this    ->activate  (act, index);
}

void FogChunk::deactivate ( DrawActionBase *, UInt32 )
{
    glDisable(GL_FOG);
}

/*-------------------------- Comparison -----------------------------------*/

Real32 FogChunk::switchCost(StateChunk *)
{
    return 0;
}

/** \brief assignment
 */

bool FogChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

/** \brief equal
 */

bool FogChunk::operator == (const StateChunk &other) const
{
    FogChunk const *tother = dynamic_cast<FogChunk const*>(&other);

    if(!tother)
        return false;

    if(tother == this)
        return true;

    if(getMode()    != tother->getMode()   ||
       getColor()   != tother->getColor()  ||
       getStart()   != tother->getStart()  ||   
       getEnd()     != tother->getEnd()    ||
       getDensity() != tother->getDensity())
        return false;
	
    return true;
}

/** \brief unequal
 */

bool FogChunk::operator != (const StateChunk &other) const
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
    static Char8 cvsid_cpp       [] = "@(#)$Id: OSGFogChunk.cpp,v 1.2 2009/11/13 18:07:01 neumannc Exp $";
    static Char8 cvsid_hpp       [] = OSGFOGCHUNKBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGFOGCHUNKBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGFOGCHUNKFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

OSG_END_NAMESPACE

