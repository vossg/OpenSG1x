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

#include <OSGFieldDescription.h>

#include <OSGAction.h>
#include <OSGDrawAction.h>
#include <OSGGeometry.h>

#include <OSGStateChunk.h>
#include <OSGState.h>

#include "OSGMaterial.h"
#include "OSGChunkMaterial.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/


OSG_FC_FIRST_FIELD_IDM_DEF(ChunkMaterial, StateChunksField)

OSG_FC_LAST_FIELD_IDM_DEF(ChunkMaterial, StateChunksField)



char ChunkMaterial::cvsid[] = "@(#)$Id: OSGChunkMaterial.cpp,v 1.1 2000/12/17 23:46:51 dirk Exp $";


FieldDescription ChunkMaterial::_desc[] = 
{
	FieldDescription(
        MFStateChunkPtr::getClassType(),
        "chunks", 
        OSG_FC_FIELD_IDM_DESC(StateChunksField),
        false,
        (FieldAccessMethod) &ChunkMaterial::getMFStateChunks)
};

FieldContainerType ChunkMaterial::_type(
	"ChunkMaterial", 
	"Material", 
	NULL,
    (PrototypeCreateF) &ChunkMaterial::createEmpty,
    NULL,
	_desc, 
	sizeof(_desc)
	);

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

OSG_FIELD_CONTAINER_DEF(ChunkMaterial, ChunkMaterialPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

ChunkMaterial::ChunkMaterial(void) :
	Inherited(),
	_chunks()
{
}

ChunkMaterial::ChunkMaterial( const ChunkMaterial& source ) :
	Inherited(source),
	_chunks( source._chunks )
{
}

/** \brief Destructor
 */

ChunkMaterial::~ChunkMaterial(void)
{
}

/*------------------------------ access -----------------------------------*/


/*---------------------------- pointer ------------------------------------*/

/*---------------------------- properties ---------------------------------*/

MFStateChunkPtr		*ChunkMaterial::getMFStateChunks( void )
{
	return &_chunks;
}


/*-------------------------- your_category---------------------------------*/

Bool ChunkMaterial::addChunk( StateChunkPtr chunk )
{
	_chunks.push_back( chunk );
	return true;
}

Bool ChunkMaterial::subChunk( StateChunkPtr chunk )
{
	MFStateChunkPtr::iterator i;
	
	i = _chunks.find( chunk );
	
	if ( ! i )
	{
		SWARNING << "ChunkMaterial::subChunk(" << this << ") has no chunk " 
				 << chunk << endl;
	}
	else
		_chunks.erase( i );
		
	return true;
}
	
	
	
void ChunkMaterial::draw( Geometry* geo, Action * action )
{
	StatePtr state = State::create();
	
	for ( MFStateChunkPtr::iterator i = _chunks.begin(); 
			i != _chunks.end(); i++ )
		state->addChunk( *i );
	
	state->activate();
	
	geo->draw( action );

	state->deactivate();
}

/*-------------------------- assignment -----------------------------------*/

/*------------------------------- dump ----------------------------------*/

void ChunkMaterial::dump(void) const
{
    SDEBUG << "ChunkMaterial at " << this << endl;
    SDEBUG << "Chunks: " << endl;
	
	for ( MFStateChunkPtr::const_iterator i = _chunks.begin(); 
			i != _chunks.end(); i++ )
		SDEBUG << *i << endl;
	
}

/*-------------------------- comparison -----------------------------------*/

#if 0

/** \brief assignment
 */

Bool ChunkMaterial::operator < (const ChunkMaterial &other) const
{
    return this < &other;
}

/** \brief equal
 */

Bool ChunkMaterial::operator == (const ChunkMaterial &other) const
{
	return false;
}

/** \brief unequal
 */

Bool ChunkMaterial::operator != (const ChunkMaterial &other) const
{
	return ! (*this == other);
}

#endif

/*------------------------- debug ----------------------------------*/

void ChunkMaterial::print( void )
{
    cerr << "ChunkMaterial at " << this << endl;
    cerr << "Chunks: " << endl;
	
	for ( MFStateChunkPtr::const_iterator i = _chunks.begin(); 
			i != _chunks.end(); i++ )
		cerr << *i << endl;
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

