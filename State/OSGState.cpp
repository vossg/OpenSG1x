/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include "OSGFieldDescription.h"
#include "OSGState.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

OSG_FC_FIRST_FIELD_IDM_DEF(State, ChunksField)
OSG_FC_LAST_FIELD_IDM_DEF (State, ChunksField)

char State::cvsid[] = "@(#)$Id: $";


FieldDescription State::_desc[] = 
{
        FieldDescription(
        MFStateChunkPtr::getClassType(), 
        "chunks", 
        OSG_FC_FIELD_IDM_DESC(ChunksField),
        false,
        (FieldAccessMethod) &State::getMFChunks,
        "")
};

FieldContainerType State::_type(
	"State", 
	"FieldContainer", 
	NULL,
	(PrototypeCreateF) &State::createEmpty,
	NULL,
	_desc, 
	sizeof(_desc));

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

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

OSG_FIELD_CONTAINER_DEF(State, StatePtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

State::State(void) :
	Inherited()
{
}

State::State( const State& source ) :
	Inherited(source)
{
}

/** \brief Destructor
 */

State::~State(void)
{
}

/*------------------------------ access -----------------------------------*/

MFStateChunkPtr *State::getMFChunks( void )
{
	return &_chunks;
}

/*---------------------------- properties ---------------------------------*/


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
	UInt32 csize = _chunks.size();
	
	// special case: find empty slot automatically
	if ( index < 0 )
	{
		UInt8 nslots = chunk->getClass()->getNumSlots();
		UInt8 ci;

		for ( ci = cindex; ci < cindex + nslots && ci < csize; ci++ ) 
			if ( _chunks.getValue( ci ) == NullStateChunk )
				break;
		
		if ( ci >= cindex + nslots )	// no free slot found
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

		_chunks.resize( newsize );
	
		for ( UInt32 i = oldsize; i < newsize; i++ )
			_chunks.setValue( NullStateChunk, i );
	}

	_chunks.setValue( chunk, cindex );
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
	UInt32 csize = _chunks.size();
	
	// special case: find it in the slots
	if ( index < 0 )
	{
		UInt8 nslots = chunk->getClass()->getNumSlots();
		UInt8 ci;

		for ( ci = cindex; ci < cindex + nslots && ci < csize; ci++ ) 
			if ( _chunks.getValue( ci ) == chunk )
				break;
		
		if ( ci >= cindex + nslots )	// no free slot found
		{
			SWARNING << "subChunk: chunk " << chunk << " of class " 
					 << chunk->getClass()->getName() << " not found!" << endl;
			return;
		}
		cindex = ci;
	}

	// remove the chunk from the state 

	_chunks.setValue( NullStateChunk, cindex );
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

	_chunks.setValue( NullStateChunk, classid + index );	
}

// call the OpenGL commands to set my part of the state.
void State::activate ( void )
{
	MFStateChunkPtr::iterator it;
	UInt32 ind = 0;
	UInt32 cind;

	for ( it = _chunks.begin(), cind = 0; it != _chunks.end(); 
		  it++, cind++,  ind++ )
	{
		if ( *it != NullStateChunk )
			(*it)->activate( ind );
		if ( ind >= StateChunkClass::getNumSlots( cind ) )
			ind = -1;
	}
}

// call commands to get from old to my state. 
void State::changeFrom( State * old )
{
	MFStateChunkPtr::iterator it;
	UInt32 ind = 0;
	UInt32 cind;

	for ( it = _chunks.begin(), cind = 0; it != _chunks.end(); 
		  it++, cind++, ind++ )
	{
		StateChunkPtr o = old->getChunk( cind );
		StateChunkPtr n = *it;

		if ( n != NullStateChunk )
		{			
			if ( o != NullStateChunk )
				n->changeFrom( o.getCPtr(), ind );
			else
				n->activate( ind );
		}
		else if ( o != NullStateChunk )
			o->deactivate( ind );
			
		if ( ind >= StateChunkClass::getNumSlots( cind ) )
			ind = -1;
	}
}


// reset my part of the state.
void State::deactivate ( void )
{
	MFStateChunkPtr::iterator it;
	UInt32 ind = 0;
	UInt32 cind;

	for ( it = _chunks.begin(), cind = 0; it != _chunks.end(); 
		  it++, cind++,  ind++ )
	{
		if ( *it != NullStateChunk )
			(*it)->deactivate( ind );
		if ( ind >= StateChunkClass::getNumSlots( cind ) )
			ind = -1;
	}
}

/*-------------------------- assignment -----------------------------------*/

/*------------------------------- dump ----------------------------------*/

void State::dump(void) const
{
    SDEBUG << "Dump State NI" << endl;
}

/*-------------------------- comparison -----------------------------------*/

Real32 State::switchCost( State * state )
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

Bool State::operator == (const State &other) const
{
	return false;
}

/** \brief unequal
 */

Bool State::operator != (const State &other) const
{
	return ! (*this == other);
}

/*------------------------- debug ----------------------------------*/

void State::print( void )
{
	cerr << "State at " << this << endl;

	MFStateChunkPtr::iterator it;
	UInt32 cind;
	
	for ( it = _chunks.begin(), cind = 0; it != _chunks.end(); it++, cind++ )
	{
		cerr << StateChunkClass::getName(cind) << "\t";
		if ( *it == NullStateChunk )
			cerr << "NullChunk" << endl;
		else
			cerr << *it << endl;
	}

}


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/



///---------------------------------------------------------------------------
///  FUNCTION: 
///---------------------------------------------------------------------------
//:  Example for the head comment of a function
///---------------------------------------------------------------------------
///
//p: Paramaters: 
//p: 
///
//g: GlobalVars:
//g: 
///
//r: Return:
//r: 
///
//c: Caution:
//c: 
///
//a: Assumptions:
//a: 
///
//d: Description:
//d: 
///
//s: SeeAlso:
//s: 
///---------------------------------------------------------------------------

