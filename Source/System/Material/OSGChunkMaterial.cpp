/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright(C) 2000-2002 by the OpenSG Forum                   *
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

#include <OSGGL.h>

#include <OSGAttachmentContainerPtr.h>
#include <OSGState.h>
#include <OSGDrawActionBase.h>
#include <OSGGeometry.h>

#include "OSGChunkMaterial.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::ChunkMaterial
    \ingroup GrpSystemMaterial

The chunk material class. See \ref PageSystemMaterialChunkMaterial for a
description.

Chunks can be attached and detached from the material using
osg::ChunkMaterial::addChunk() and osg::ChunkMaterial::subChunk(). For more
complex manipulation of the chunk list use the osg::ChunkMaterial::_mfChunks
field's functions.

*/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

void ChunkMaterial::initMethod(void)
{
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*------------- constructors & destructors --------------------------------*/

ChunkMaterial::ChunkMaterial(void) :
    Inherited()
{
}

ChunkMaterial::ChunkMaterial(const ChunkMaterial &source) :
    Inherited(source)
{
}

ChunkMaterial::~ChunkMaterial(void)
{
    MFStateChunkPtr::iterator matIt  = _mfChunks.begin();
    MFStateChunkPtr::iterator matEnd = _mfChunks.end ();
    
    while(matIt != matEnd)
    {
        subRefCP(*matIt);

        ++matIt;
    }
}

void ChunkMaterial::changed(BitVector whichField, UInt32 origin)
{
    if(origin & ChangedOrigin::Abstract)
    {
        MFStateChunkPtr::iterator matIt  = _mfChunks.begin();
        MFStateChunkPtr::iterator matEnd = _mfChunks.end ();
        
        while(matIt != matEnd)
        {
            addRefCP(*matIt);
           
            ++matIt;
        }
    }

    Inherited::changed(whichField, origin);
}


/*-------------------------- your_category---------------------------------*/

bool ChunkMaterial::addChunk(StateChunkPtr chunk)
{
    _mfChunks.push_back(chunk);

    addRefCP(chunk);

    return true;
}

bool ChunkMaterial::subChunk(StateChunkPtr chunk)
{
    MFStateChunkPtr::iterator i;

    i = _mfChunks.find(chunk);

    if(i == _mfChunks.end())
    {
        SWARNING << "ChunkMaterial::subChunk(" << this << ") has no chunk "
                 << chunk << std::endl;
    }
    else
    {
         subRefCP      (chunk);
        _mfChunks.erase(i    );
    }

    return true;
}

StateChunkPtr ChunkMaterial::find(const FieldContainerType &type, UInt32 index)
{
    UInt32 count = 0;
    for(MFStateChunkPtr::iterator i = _mfChunks.begin();i != _mfChunks.end();++i)
    {
        if((*i)->getType() == type)
        {
            if(count == index)
                return (*i);
            ++count;
        }
    }
    return NullFC;
}

/*! Draw the geometry with this material.
*/

void ChunkMaterial::draw(Geometry* geo, DrawActionBase * action)
{
    StatePtr state = makeState();

    addRefCP(state);

    state->activate(action);

    geo->drawPrimitives(action);

    state->deactivate(action);

    subRefCP(state); // kill it
}

/*! Draw the function behind the functor with this material. The functored
    function should be very careful changing OpenGL state, better just use
    glBegin(), glEnd() and the standard stuff in between.
*/

void ChunkMaterial::draw(DrawFunctor& func, DrawActionBase * action)
{
    StatePtr state = makeState();

    addRefCP(state);

    state->activate(action);

    func.call(action);

    state->deactivate(action);

    subRefCP(state); // kill it
}

/*! Create a osg::State that represents this Material and return it.
*/

StatePtr ChunkMaterial::makeState(void)
{
    StatePtr state = State::create();

    for(MFStateChunkPtr::iterator i = _mfChunks.begin();
            i != _mfChunks.end(); i++)
        state->addChunk(*i);

    return state;
}

/*! Rebuild the internal State. Just collects the chunks in the State.
*/

void ChunkMaterial::rebuildState(void)
{
    if(_pState != NullFC)
    {
        _pState->clearChunks();
    }
    else
    {
        _pState = State::create();

        addRefCP(_pState);
    }

    MFStateChunkPtr::iterator it        = _mfChunks.begin();
    MFStateChunkPtr::iterator chunksEnd = _mfChunks.end();

    for(; it != chunksEnd; ++it)
    {
        _pState->addChunk(*it);
    }
}

/*! Check if the Material (i.e. any of its chunks) is transparent..
*/

bool ChunkMaterial::isTransparent(void) const
{
    bool             returnValue = false;

    MFStateChunkPtr::const_iterator it        = _mfChunks.begin();
    MFStateChunkPtr::const_iterator chunksEnd = _mfChunks.end();

    for(; it != chunksEnd && returnValue == false; ++it)
    {
        returnValue =(*it)->isTransparent();
    }

    return returnValue;
}

/*------------------------------- dump ----------------------------------*/

void ChunkMaterial::dump(      UInt32    OSG_CHECK_ARG(uiIndent),
                         const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "ChunkMaterial at " << this << std::endl;
    SLOG << "Chunks: " << std::endl;

    for(MFStateChunkPtr::const_iterator i = _mfChunks.begin();
            i != _mfChunks.end(); i++)
        SLOG << *i << std::endl;
}


/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning(disable : 177)
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: FCTemplate_cpp.h,v 1.13 2002/06/01 10:37:25 vossg Exp $";
    static Char8 cvsid_hpp       [] = OSGCHUNKMATERIAL_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCHUNKMATERIAL_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCHUNKMATERIALFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif


