/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
 *                                                                           *
 *          contact: {reiners|vossg}@igd.fhg.de, jbehr@zgdv.de               *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

/** \enum OSGVecBase::VectorSizeE
 *  \brief 
 */

/** \var OSGVecBase::VectorSizeE OSGVecBase::_iSize
 * 
 */

/** \fn const char *OSGVecBase::getClassname(void)
 *  \brief Classname
 */

/** \var OSGValueTypeT OSGVecBase::_values[iSize];
 *  \brief Value store
 */

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

OSG_FC_FIRST_FIELD_IDM_DEF(OSGState, OSGChunksField)
OSG_FC_LAST_FIELD_IDM_DEF (OSGState, OSGChunksField)

char OSGState::cvsid[] = "@(#)$Id: $";


OSGFieldDescription OSGState::_desc[] = 
{
        OSGFieldDescription(
        OSGMFStateChunkPtr::getClassType(), 
        "chunks", 
        OSG_FC_FIELD_IDM_DESC(OSGChunksField),
        false,
        (OSGFieldAccessMethod) &OSGState::getMFChunks,
        "")
};

OSGFieldContainerType OSGState::_type(
	"State", 
	"FieldContainer", 
	NULL,
	(OSGPrototypeCreateF) &OSGState::createEmpty,
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

OSG_FIELD_CONTAINER_DEF(OSGState, OSGStatePtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

OSGState::OSGState(void) :
	Inherited()
{
}

OSGState::OSGState( const OSGState& source ) :
	Inherited(source)
{
}

/** \brief Destructor
 */

OSGState::~OSGState(void)
{
}

/*------------------------------ access -----------------------------------*/

OSGMFStateChunkPtr *OSGState::getMFChunks( void )
{
	return &_chunks;
}

/*---------------------------- properties ---------------------------------*/


/*-------------------------- your_category---------------------------------*/
	
void OSGState::addChunk( OSGStateChunkPtr chunk, OSGInt32 index )
{
	if ( index > 0 && index > chunk->getClass()->getNumSlots() )
	{
		SWARNING << "addChunk: index " << index << " > Numslots "
				 << chunk->getClass()->getNumSlots() << ",  ignored!" << endl;
		return;
	}
	
	OSGUInt32 cindex = chunk->getClassID();
	OSGUInt32 csize = _chunks.size();
	
	// special case: find empty slot automatically
	if ( index < 0 )
	{
		OSGUInt8 nslots = chunk->getClass()->getNumSlots();
		OSGUInt8 ci;

		for ( ci = cindex; ci < cindex + nslots && ci < csize; ci++ ) 
			if ( _chunks.getValue( ci ) == OSGNullStateChunk )
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
		OSGUInt32 oldsize = csize, 
				  newsize = cindex + 1;

		_chunks.resize( newsize );
	
		for ( OSGUInt32 i = oldsize; i < newsize; i++ )
			_chunks.setValue( OSGNullStateChunk, i );
	}

	_chunks.setValue( chunk, cindex );
}

	
void OSGState::subChunk( OSGStateChunkPtr chunk, OSGInt32 index )
{
	if ( index > 0 && index > chunk->getClass()->getNumSlots() )
	{
		SWARNING << "subChunk: index " << index << " > Numslots "
				 << chunk->getClass()->getNumSlots() << ",  ignored!" << endl;
		return;
	}
	
	OSGUInt32 cindex = chunk->getClassID();
	OSGUInt32 csize = _chunks.size();
	
	// special case: find it in the slots
	if ( index < 0 )
	{
		OSGUInt8 nslots = chunk->getClass()->getNumSlots();
		OSGUInt8 ci;

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

	_chunks.setValue( OSGNullStateChunk, cindex );
}
	
void OSGState::subChunk( OSGUInt32 classid, OSGInt32 index )
{
	if ( index > 0 && index > OSGStateChunkClass::getNumSlots(classid) )
	{
		SWARNING << "subChunk: index " << index << " > Numslots "
				 << OSGStateChunkClass::getNumSlots(classid) 
				 << ",  ignored!" << endl;
		return;
	}

	// remove the chunk from the state 

	_chunks.setValue( OSGNullStateChunk, classid + index );	
}

// call the OpenGL commands to set my part of the state.
void OSGState::activate ( void )
{
	OSGMFStateChunkPtr::iterator it;
	OSGUInt32 ind = 0;
	OSGUInt32 cind;

	for ( it = _chunks.begin(), cind = 0; it != _chunks.end(); 
		  it++, cind++,  ind++ )
	{
		if ( *it != OSGNullStateChunk )
			(*it)->activate( ind );
		if ( ind >= OSGStateChunkClass::getNumSlots( cind ) )
			ind = -1;
	}
}

// call commands to get from old to my state. 
void OSGState::changeFrom( OSGState * old )
{
	OSGMFStateChunkPtr::iterator it;
	OSGUInt32 ind = 0;
	OSGUInt32 cind;

	for ( it = _chunks.begin(), cind = 0; it != _chunks.end(); 
		  it++, cind++, ind++ )
	{
		OSGStateChunkPtr o = old->getChunk( cind );
		OSGStateChunkPtr n = *it;

		if ( n != OSGNullStateChunk )
		{			
			if ( o != OSGNullStateChunk )
				n->changeFrom( o, ind );
			else
				n->activate( ind );
		}
		else if ( o != OSGNullStateChunk )
			o->deactivate( ind );
			
		if ( ind >= OSGStateChunkClass::getNumSlots( cind ) )
			ind = -1;
	}
}


// reset my part of the state.
void OSGState::deactivate ( void )
{
	OSGMFStateChunkPtr::iterator it;
	OSGUInt32 ind = 0;
	OSGUInt32 cind;

	for ( it = _chunks.begin(), cind = 0; it != _chunks.end(); 
		  it++, cind++,  ind++ )
	{
		if ( *it != OSGNullStateChunk )
			(*it)->deactivate( ind );
		if ( ind >= OSGStateChunkClass::getNumSlots( cind ) )
			ind = -1;
	}
}

/*-------------------------- assignment -----------------------------------*/

/*------------------------------- dump ----------------------------------*/

void OSGState::dump(void) const
{
    SDEBUG << "Dump OSGState NI" << endl;
}

/*-------------------------- comparison -----------------------------------*/

OSGReal32 OSGState::switchCost( OSGState * state )
{
	return 0;
}

/** \brief assignment
 */

OSGBool OSGState::operator < (const OSGState &other) const
{
    return this < &other;
}

/** \brief equal
 */

OSGBool OSGState::operator == (const OSGState &other) const
{
	return false;
}

/** \brief unequal
 */

OSGBool OSGState::operator != (const OSGState &other) const
{
	return ! (*this == other);
}

/*------------------------- debug ----------------------------------*/

void OSGState::print( void )
{
	cerr << "State at " << this << endl;

	OSGMFStateChunkPtr::iterator it;
	OSGUInt32 cind;
	
	for ( it = _chunks.begin(), cind = 0; it != _chunks.end(); it++, cind++ )
	{
		cerr << OSGStateChunkClass::getName(cind) << "\t";
		if ( *it == OSGNullStateChunk )
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

