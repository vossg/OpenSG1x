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

#include "OSGStateChunk.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \defgroup StateChunks
    \ingroup StateLib

The StateChunk encapsulates a logical part of the OpenGL state.

*/

/*! \class osg::StateChunk

The state chunk base class.

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/


// StateChunkClass code

vector<string>* StateChunkClass::_classNames = NULL;
vector<UInt32>* StateChunkClass::_numslots = NULL;

StateChunkClass::StateChunkClass( Char8 *name, UInt32 numslots )
{
    if ( ! _classNames )
    {
        _classNames = new vector<string>(0);
        _numslots   = new vector<UInt32>(0);
    }

    _classId = _classNames->size();

    for ( unsigned i = 0; i < numslots; i++ )
    {
        _classNames->push_back( name );
        _numslots->push_back( numslots );
    }
}

StateChunkClass::iterator StateChunkClass::begin( void )
{
    return _classNames->begin();
}

StateChunkClass::iterator StateChunkClass::end( void )
{
    return _classNames->end();
}

// instance access

UInt32 StateChunkClass::getID( void ) const
{
    return _classId;
}

Int32 StateChunkClass::getNumSlots( void ) const
{
    return (*_numslots)[_classId];
}

const Char8 *StateChunkClass::getName( void ) const
{
    return (*_classNames)[_classId].c_str();
}

// static access

Int32 StateChunkClass::getNumSlots( UInt32 index )
{
    if ( index >= (*_numslots).size() )
        return -1;

    return (*_numslots)[index];
}

const Char8 *StateChunkClass::getName( UInt32 index )
{
    if ( index >= (*_classNames).size() )
            return "<Unknown StatChunkClass!>";

    return (*_classNames)[index].c_str();
}


/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char StateChunk::cvsid[] = "@(#)$Id: $";

OSG_SYSTEMLIB_DLLMAPPING StateChunkPtr osg::NullStateChunk;

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

void StateChunk::initMethod (void)
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

StateChunk::StateChunk(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

StateChunk::StateChunk(const StateChunk &source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

StateChunk::~StateChunk(void)
{
}


/** \brief react to field changes
 */

void StateChunk::changed(BitVector, ChangeMode)
{
}

/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */

void StateChunk::dump(         UInt32     uiIndent,
                         const BitVector &bvFlags) const
{
    SLOG << "Dump StateChunk NI" << endl;
}


/*---------------------------- properties ---------------------------------*/

const StateChunkClass *  StateChunk::getClass( void ) const
{
    return NULL;
}

Bool StateChunk::isTransparent(void) const
{
    return false;
}

/*-------------------------- your_category---------------------------------*/

void StateChunk::activate ( DrawActionBase * action, UInt32 index )
{
}

void StateChunk::changeFrom( DrawActionBase * action, StateChunk * old, UInt32 index )
{
    old->deactivate( action, index );
    activate( action, index );
}

void StateChunk::deactivate ( DrawActionBase * action, UInt32 index )
{
}

/*-------------------------- comparison -----------------------------------*/

Real32 StateChunk::switchCost( StateChunk * chunk )
{
    return 0;
}

/** \brief assignment
 */

Bool StateChunk::operator < (const StateChunk &other) const
{
    return this < &other;
}

/** \brief equal
 */

Bool StateChunk::operator == (const StateChunk &other) const
{
    return false;
}

/** \brief unequal
 */

Bool StateChunk::operator != (const StateChunk &other) const
{
    return ! (*this == other);
}



/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

