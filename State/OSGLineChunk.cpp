/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

#include "OSGDrawActionBase.h"
#include "OSGWindow.h"

#include "OSGLineChunk.h"

OSG_USING_NAMESPACE

/*! \class osg::LineChunk
    \ingroup StateChunks

The line chunk contains the parameters that are specific set for lines.
*/


StateChunkClass LineChunk::_class("Line");

/*----------------------- constructors & destructors ----------------------*/

//! Constructor

LineChunk::LineChunk(void) :
    Inherited()
{
}

//! Copy Constructor

LineChunk::LineChunk(const LineChunk &source) :
    Inherited(source)
{
}

//! Destructor

LineChunk::~LineChunk(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void LineChunk::initMethod (void)
{
}

//! react to field changes

void LineChunk::changed(BitVector, UInt32)
{
}

//! output the instance for debug purposes

void LineChunk::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump LineChunk NI" << endl;
}


/*-------------------------- your_category---------------------------------*/

void LineChunk::activate(DrawActionBase *, UInt32)
{
    if(_sfWidth.getValue() != 1)
    {
        glLineWidth(_sfWidth.getValue());
    }
    
    if(_sfStipplePattern.getValue() != 0xffffu)
    {
        glLineStipple(_sfStippleRepeat.getValue(), 
                      _sfStipplePattern.getValue());
        glEnable(GL_LINE_STIPPLE);
    }
    
    if(_sfSmooth.getValue())
    {
        glEnable(GL_LINE_SMOOTH);
    }
}

void LineChunk::changeFrom( DrawActionBase *act, StateChunk * old_chunk, UInt32 index )
{
    old_chunk->deactivate( act, index );
    activate( act, index );
}

void LineChunk::deactivate ( DrawActionBase *, UInt32 )
{
    if(_sfWidth.getValue() != 1)
    {
        glLineWidth(1);
    }
    
    if(_sfStipplePattern.getValue() != 0xffffu)
    {
        glDisable(GL_LINE_STIPPLE);
    }
    
    if(_sfSmooth.getValue())
    {
        glDisable(GL_LINE_SMOOTH);
    }
}

/*-------------------------- comparison -----------------------------------*/

Real32 LineChunk::switchCost(StateChunk *)
{
    return 0;
}

/** \brief assignment
 */

bool LineChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

/** \brief equal
 */

bool LineChunk::operator == (const StateChunk &other) const
{
    LineChunk const *tother = dynamic_cast<LineChunk const*>(&other);

    if ( !tother )
        return false;

    return true;
}

/** \brief unequal
 */

bool LineChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id: OSGLineChunk.cpp,v 1.6 2002/06/01 10:37:25 vossg Exp $";
    static char cvsid_hpp[] = OSGLINECHUNK_HEADER_CVSID;
    static char cvsid_inl[] = OSGLINECHUNK_INLINE_CVSID;
}
