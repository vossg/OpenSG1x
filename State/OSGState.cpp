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

#include "OSGConfig.h"

#include <GL/gl.h>

#include "OSGStateChunk.h"

#include "OSGState.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/


/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char State::cvsid[] = "@(#)$Id: $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/** \brief initialize the static features of the class, e.g. action callbacks
 */

void State::initMethod (void)
{
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

State::State(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

State::State(const State &source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

State::~State(void)
{
}


/** \brief react to field changes
 */

void State::changed(BitVector, ChangeMode)
{
}

/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */

void State::dump(      UInt32    OSG_CHECK_ARG(uiIndent),
                 const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    cerr << "State at " << this << endl;

    MFStateChunkPtr::const_iterator it;
    UInt32 cind;

    for ( it = _mfChunks.begin(), cind = 0; it != _mfChunks.end(); it++, cind++ )
    {
        cerr << StateChunkClass::getName(cind) << "\t";
        if ( *it == NullStateChunk )
            cerr << "NullChunk" << endl;
        else
            cerr << *it << endl;
    }
}


/*-------------------------- your_category---------------------------------*/

void State::addChunk( StateChunkPtr chunk, Int32 index )
{
    if ( index > 0 && index > chunk->getClass()->getNumSlots() )
    {
        SWARNING << "addChunk: index " << index << " > Numslots "
                 << chunk->getClass()->getNumSlots() << ",  ignored!" << endl;
        return;
    }

    UInt32 cindex = chunk->getClassID();
    UInt32 csize = _mfChunks.size();

    // special case: find empty slot automatically
    if ( index < 0 )
    {
        UInt8 nslots = chunk->getClass()->getNumSlots();
        UInt8 ci;

        for ( ci = cindex; ci < cindex + nslots && ci < csize; ci++ )
            if ( _mfChunks.getValue( ci ) == NullStateChunk )
                break;

        if ( ci >= cindex + nslots )    // no free slot found
        {
            SWARNING << "addChunk: no free slot found for "
                     << chunk->getClass()->getName() << " class, ignored!" << endl;
            return;
        }
        cindex = ci;
    }
    else
        cindex += index;

    // add the chunk to the state at cindex
    if ( cindex >= csize )
    {
        UInt32 oldsize = csize,
                  newsize = cindex + 1;

        _mfChunks.resize( newsize );

        for ( UInt32 i = oldsize; i < newsize; i++ )
            _mfChunks.setValue( NullStateChunk, i );
    }

    _mfChunks.setValue( chunk, cindex );
}


void State::subChunk( StateChunkPtr chunk, Int32 index )
{
    if ( index > 0 && index > chunk->getClass()->getNumSlots() )
    {
        SWARNING << "subChunk: index " << index << " > Numslots "
                 << chunk->getClass()->getNumSlots() << ",  ignored!" << endl;
        return;
    }

    UInt32 cindex = chunk->getClassID();
    UInt32 csize = _mfChunks.size();

    // special case: find it in the slots
    if ( index < 0 )
    {
        UInt8 nslots = chunk->getClass()->getNumSlots();
        UInt8 ci;

        for ( ci = cindex; ci < cindex + nslots && ci < csize; ci++ )
            if ( _mfChunks.getValue( ci ) == chunk )
                break;

        if ( ci >= cindex + nslots )    // no free slot found
        {
            SWARNING << "subChunk: chunk " << chunk << " of class "
                     << chunk->getClass()->getName() << " not found!" << endl;
            return;
        }
        cindex = ci;
    }

    // remove the chunk from the state

    _mfChunks.setValue( NullStateChunk, cindex );
}

void State::subChunk( UInt32 classid, Int32 index )
{
    if ( index > 0 && index > StateChunkClass::getNumSlots(classid) )
    {
        SWARNING << "subChunk: index " << index << " > Numslots "
                 << StateChunkClass::getNumSlots(classid)
                 << ",  ignored!" << endl;
        return;
    }

    // remove the chunk from the state

    _mfChunks.setValue( NullStateChunk, classid + index );
}

void State::clearChunks(void)
{
    fill(_mfChunks.begin(), _mfChunks.end(), NullStateChunk);
}


// call the OpenGL commands to set my part of the state.
void State::activate(DrawActionBase *action)
{
    MFStateChunkPtr::iterator it;
    Int32 ind = 0;
    UInt32 cind;

    for ( it = _mfChunks.begin(), cind = 0; it != _mfChunks.end();
          ++it, ++cind,  ++ind )
    {
        if ( *it != NullStateChunk )
            (*it)->activate( action, UInt32(ind) );
        if ( ind >= StateChunkClass::getNumSlots( cind ) )
            ind = -1;
    }
}

// call commands to get from old to my state.
void State::changeFrom(DrawActionBase *action, State *old)
{
    MFStateChunkPtr::iterator it;
    Int32 ind = 0;
    UInt32 i;
    UInt32 cind;

    for ( it = _mfChunks.begin(), cind = 0; it != _mfChunks.end();
          ++it, ++cind, ++ind )
    {
        StateChunkPtr o = old->getChunk( cind );
        StateChunkPtr n = *it;

        if ( n != NullStateChunk )
        {
            if ( o != NullStateChunk )
                n->changeFrom( action, o.getCPtr(), UInt32(ind) );
            else
                n->activate( action, UInt32(ind) );
        }
        else if ( o != NullStateChunk )
            o->deactivate( action, UInt32(ind) );

        if ( ind >= StateChunkClass::getNumSlots( cind ) )
            ind = -1;
    }

    ind = 0;

    for(i = cind; i < old->getChunks().size(); ++i, ++ind)
    {
        StateChunkPtr o = old->getChunk(i);

        if(o != NullFC)
        {
            o->deactivate(action, UInt32(ind));
        }

        if(ind >= StateChunkClass::getNumSlots(cind))
        {
            ind = -1;
        }
    }
}


// reset my part of the state.
void State::deactivate ( DrawActionBase *action )
{
    MFStateChunkPtr::iterator it;
    Int32 ind = 0;
    UInt32 cind;

    for ( it = _mfChunks.begin(), cind = 0; it != _mfChunks.end();
          ++it, ++cind,  ++ind )
    {
        if ( *it != NullStateChunk )
            (*it)->deactivate( action, UInt32(ind) );
        if ( ind >= StateChunkClass::getNumSlots( cind ) )
            ind = -1;
    }
}

/*-------------------------- comparison -----------------------------------*/

Real32 State::switchCost(State *OSG_CHECK_ARG(state))
{
    return 0;
}

/** \brief assignment
 */

Bool State::operator < (const State &other) const
{
    return this < &other;
}

/** \brief equal
 */

Bool State::operator == (const State &OSG_CHECK_ARG(other)) const
{
    return false;
}

/** \brief unequal
 */

Bool State::operator != (const State &other) const
{
    return ! (*this == other);
}


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

