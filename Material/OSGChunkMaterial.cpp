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

#define OSG_COMPILEMATERIAL

#include <OSGState.h>
#include <OSGDrawAction.h>
#include <OSGGeometry.h>

#include "OSGChunkMaterial.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ChunkMaterial
    \ingroup MaterialLib

The chunk material class.

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char ChunkMaterial::cvsid[] = "@(#)$Id: OSGChunkMaterial.cpp,v 1.9 2001/04/23 18:33:14 dirk Exp $";

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

void ChunkMaterial::initMethod (void)
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

ChunkMaterial::ChunkMaterial(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

ChunkMaterial::ChunkMaterial(const ChunkMaterial &source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

ChunkMaterial::~ChunkMaterial(void)
{
}


/** \brief react to field changes
 */

void ChunkMaterial::changed(BitVector, ChangeMode)
{
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
	
	if (i == _chunks.end())
	{
		SWARNING << "ChunkMaterial::subChunk(" << this << ") has no chunk " 
				 << chunk << endl;
	}
	else
		_chunks.erase( i );
		
	return true;
}
	
	
	
void ChunkMaterial::draw( Geometry* geo, DrawAction * action )
{
	StatePtr state = State::create();

	addRefCP( state );
	
	for ( MFStateChunkPtr::iterator i = _chunks.begin(); 
			i != _chunks.end(); i++ )
		state->addChunk( *i );
	
	state->activate( action );
	
	geo->draw( action );

	state->deactivate( action );

	subRefCP( state ); // kill it
}
	
void ChunkMaterial::activate( void )
{
	for ( MFStateChunkPtr::iterator i = _chunks.begin(); 
			i != _chunks.end(); i++ )
		i->activate();
}
	
void ChunkMaterial::deactivate( void )
{
	for ( MFStateChunkPtr::iterator i = _chunks.begin(); 
			i != _chunks.end(); i++ )
		i->deactivate();
}

/*-------------------------- assignment -----------------------------------*/

/*------------------------------- dump ----------------------------------*/

void ChunkMaterial::dump(      UInt32     uiIndent, 
                         const BitVector &bvFlags) const
{
    SLOG << "ChunkMaterial at " << this << endl;
    SLOG << "Chunks: " << endl;
	
	for ( MFStateChunkPtr::const_iterator i = _chunks.begin(); 
			i != _chunks.end(); i++ )
		SLOG << *i << endl;	
}

/*-------------------------- comparison -----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

