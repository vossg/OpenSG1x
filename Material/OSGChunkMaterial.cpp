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

#include <OSGState.h>
#include <OSGDrawActionBase.h>
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

char ChunkMaterial::cvsid[] = "@(#)$Id: OSGChunkMaterial.cpp,v 1.19 2002/02/04 20:14:08 dirk Exp $";

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

bool ChunkMaterial::addChunk( StateChunkPtr chunk )
{
    _mfChunks.push_back( chunk );
    return true;
}

bool ChunkMaterial::subChunk( StateChunkPtr chunk )
{
    MFStateChunkPtr::iterator i;

    i = _mfChunks.find( chunk );

    if (i == _mfChunks.end())
    {
        SWARNING << "ChunkMaterial::subChunk(" << this << ") has no chunk "
                 << chunk << endl;
    }
    else
        _mfChunks.erase( i );

    return true;
}



void ChunkMaterial::draw( Geometry* geo, DrawActionBase * action )
{
    StatePtr state = makeState();

    addRefCP( state );

    state->activate( action );

    geo->draw( action );

    state->deactivate( action );

    subRefCP( state ); // kill it
}

void ChunkMaterial::draw( DrawFunctor& func, DrawActionBase * action )
{
    StatePtr state = makeState();

    addRefCP( state );

    state->activate( action );

    func.call( action );

    state->deactivate( action );

    subRefCP( state ); // kill it
}

StatePtr ChunkMaterial::makeState( void )
{
    StatePtr state = State::create();

    for ( MFStateChunkPtr::iterator i = _mfChunks.begin();
            i != _mfChunks.end(); i++ )
        state->addChunk( *i );

    return state;
}

void ChunkMaterial::rebuildState(void)
{
    if(_pState != NullFC)
    {
        _pState->clearChunks();
    }
    else
    {
        _pState = State::create();
    }

    MFStateChunkPtr::iterator it        = _mfChunks.begin();
    MFStateChunkPtr::iterator chunksEnd = _mfChunks.end();

    for (; it != chunksEnd; ++it)
    {
        _pState->addChunk(*it);
    }
}

bool ChunkMaterial::isTransparent(void) const
{
    bool             returnValue = false;

    MFStateChunkPtr::const_iterator it        = _mfChunks.begin();
    MFStateChunkPtr::const_iterator chunksEnd = _mfChunks.end();

    for (; it != chunksEnd && returnValue == false; ++it)
    {
        returnValue = (*it)->isTransparent();
    }

    return returnValue;
}

/*-------------------------- assignment -----------------------------------*/

/*------------------------------- dump ----------------------------------*/

void ChunkMaterial::dump(      UInt32    OSG_CHECK_ARG(uiIndent),
                         const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "ChunkMaterial at " << this << endl;
    SLOG << "Chunks: " << endl;

    for ( MFStateChunkPtr::const_iterator i = _mfChunks.begin();
            i != _mfChunks.end(); i++ )
        SLOG << *i << endl;
}

/*-------------------------- comparison -----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

