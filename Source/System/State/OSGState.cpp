/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#include "OSGStateChunk.h"

#include "OSGState.h"


#if !defined(OSG_DO_DOC) || defined(OSG_DOC_DEV)

OSG_BEGIN_NAMESPACE

/*! \ingroup STLHelpers
    \hideinhierarchy
    Helper struct to remove chunks from a state.
*/

struct ClearSlot : public std::unary_function<      StateChunkPtr         &, 
                                              const NullFieldContainerPtr &>
{
    const NullFieldContainerPtr &operator() (StateChunkPtr &slotPtr) 
    { 
        subRefCP(slotPtr);
        
        return NullFC;
    }
};

OSG_END_NAMESPACE

#endif

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/


/*! \class osg::State
    \ingroup GrpSystemState
    
The state base class. See \ref PageSystemState for the conceptual background. 

*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char State::cvsid[] = "@(#)$Id: $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

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

State::State(void) :
    Inherited()
{
}

State::State(const State &source) :
    Inherited(source)
{
}

State::~State(void)
{
    clearChunks();
}

#if defined(OSG_FIXED_MFIELDSYNC)
void State::onDestroyAspect(UInt32 uiId, UInt32 uiAspect)
{
    Inherited::onDestroyAspect(uiId, uiAspect);

    clearChunks();
}
#endif

void State::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

/*------------------------------- dump ----------------------------------*/

void State::dump(     UInt32    OSG_CHECK_ARG(uiIndent),
                 const BitVector OSG_CHECK_ARG(bvFlags)) const
{
    std::cerr << "State at " << this << std::endl;

    MFStateChunkPtr::const_iterator it;
    UInt32 cind;

    for(it = _mfChunks.begin(), cind = 0; it != _mfChunks.end(); it++, cind++)
    {
        std::cerr << StateChunkClass::getName(cind) << "\t";
        if(*it == NullFC)
            std::cerr << "NullChunk" << std::endl;
        else
            std::cerr << *it << std::endl;
    }
}

/*-------------------- OpenGL State Management --------------------------*/

/*! Activate (i.e. call all their OpenGL commands) the current set of
    StateChunks. Activate will simply overwrite whatever was set before. 
*/

void State::activate(DrawActionBase *action)
{
    MFStateChunkPtr::iterator it;
    Int32 ind = 0;
    UInt32 cind;

    for(it = _mfChunks.begin(), cind = 0; it != _mfChunks.end();
          ++it, ++cind)
    {
        if(*it != NullFC && !(*it)->getIgnore())
        {
            (*it)->activate(action, UInt32(ind));
        }
        if(++ind >= StateChunkClass::getNumSlots(cind))
            ind = 0;
    }
}


/*! Switch to this state from the given old State. The chunks will try to 
    optimize the transition.
*/

void State::changeFrom(DrawActionBase *action, State *old)
{
    MFStateChunkPtr::iterator it;
    Int32 ind = 0;
    UInt32 i;
    UInt32 cind;

    for(it = _mfChunks.begin(), cind = 0; it != _mfChunks.end();
          ++it, ++cind)
    {
        StateChunkPtr o = old->getChunk(cind);
        StateChunkPtr n = *it;

        if(n != NullFC && !n->getIgnore())
        {
            if(o != NullFC && !o->getIgnore())
                n->changeFrom(action, o.getCPtr(), UInt32(ind));
            else
                n->activate(action, UInt32(ind));
        }
        else if(o != NullFC && !o->getIgnore())
        {
            o->deactivate(action, UInt32(ind));
        }

        if(++ind >= StateChunkClass::getNumSlots(cind))
            ind = 0;
    }

    if(ind >= StateChunkClass::getNumSlots(cind))
        ind = 0;

    for(i = cind; i < old->getChunks().size(); ++i)
    {
        StateChunkPtr o = old->getChunk(i);

        if(o != NullFC && !o->getIgnore())
        {
            o->deactivate(action, UInt32(ind));
        }

        if(++ind >= StateChunkClass::getNumSlots(i))
        {
            ind = 0;
        }
    }
}


/*! Deactivate the current set of StateChunks, i.e. switch everything back to
    the default state for the OpenGL state covered by the given chunks.
*/

void State::deactivate(DrawActionBase *action)
{
    MFStateChunkPtr::iterator it;
    Int32 ind = 0;
    UInt32 cind;

    for(it = _mfChunks.begin(), cind = 0; it != _mfChunks.end();
          ++it, ++cind)
    {
        if(*it != NullFC && !(*it)->getIgnore())
            (*it)->deactivate(action, UInt32(ind));
        if(++ind >= StateChunkClass::getNumSlots(cind))
            ind = 0;
    }
}


/*---------------------------- Access -----------------------------------*/

/*! Add the given chunk to the State. The index defines the behaviour,
    especially for multi-slot chunks. 

    If it is set to AutoSlotReplace (the default), addChunk will try to find an
    empty slot for the chunk class, if it doesn't find one the last one will be
    replaced with the new entry. This is also useful for chunk classes with
    only a single slot, as it will override an old instance of the chunk class,
    which is usually the desired behaviour.
    
    If it is set to AutoSlot, the new chunk will only be added to the State if
    there is a free slot. If there is no free slot true will be returned, in
    all other cases it will be false.
    
    If the index is explicitly given (i.e. it is >=0) the chunk will be set
    into the given slot, possibly overwriting an old entry. If the index is
    larger than the number of slots for the given chunck class true will be
    returned.
*/

bool State::addChunk(StateChunkPtr chunk, Int32 index)
{
    if(index > 0 && index > chunk->getClass()->getNumSlots())
    {
        SWARNING << "addChunk: index " 
                 << index
                 << " > Numslots "
                 << chunk->getClass()->getNumSlots()
                 << ",  ignored!" 
                 << std::endl;
        return true;
    }

    UInt32 cindex =  chunk->getClassId();
    UInt32 csize  = _mfChunks.size();

    // special case: find empty slot automatically
    if(index == AutoSlot || index == AutoSlotReplace)
    {
        UInt8 nslots = chunk->getClass()->getNumSlots();
        UInt8 ci;

        for(ci = cindex; ci < cindex + nslots && ci < csize; ++ci)
        {
            if(_mfChunks[ci] == NullFC)
            {
                break;
            }
        }

        if(ci >= cindex + nslots)    // no free slot found
        {
            if(index == AutoSlot)
            {
                SWARNING << "addChunk: no free slot found for "
                         << chunk->getClass()->getName() 
                         << " class, ignored!" << std::endl;
                return true;
            }
            // use last slot
            --ci;
        }

        cindex = ci;
    }
    else
    {
        cindex += index;
    }

    // add the chunk to the state at cindex
    if(cindex >= csize)
    {
        UInt32 oldsize = csize;
        UInt32 newsize = cindex + 1;

        _mfChunks.resize(newsize);

        for(UInt32 i = oldsize; i < newsize; i++)
        {
            _mfChunks[i] = NullFC;
        }
    }

    setRefdCP(_mfChunks[cindex], chunk);
    
    return false;
}

/*! Remove the given chunk from the State. Returns false if successful, true if
    the chunk wasn't found.
*/

bool State::subChunk(StateChunkPtr chunk)
{
    if(chunk == NullFC)
        return true;
        
    UInt32 cindex =  chunk->getClassId();
    UInt32 csize  = _mfChunks.size();

    // special case: find it in the slots
    UInt8 nslots = chunk->getClass()->getNumSlots();
    UInt8 ci;

    for(ci = cindex; ci < cindex + nslots && ci < csize; ci++)
    {
        if(_mfChunks[ci] == chunk)
        {
            break;
        }
    }

    if(ci >= cindex + nslots)    // chunk not found
    {
        SWARNING << "subChunk: chunk " 
                 << chunk
                 << " of class "
                 << chunk->getClass()->getName()
                 << " not found!" 
                 << std::endl;
        return true;
    }

    // remove the chunk from the state

    subRefCP(_mfChunks[ci]);

    _mfChunks[ci] = NullFC;
    
    return false;
}


/*! Remove the chunk defined by the class id and the slot index from the State. 
    Returns false if successful, true if the chunk wasn't found.
*/

bool State::subChunk(UInt32 classid, Int32 index)
{
    if(index < 0 || index > StateChunkClass::getNumSlots(classid))
    {
        SWARNING << "subChunk: index " << index << " > Numslots "
                 << StateChunkClass::getNumSlots(classid)
                 << ",  ignored!" << std::endl;
        return true;
    }

    if(_mfChunks[classid + index] == NullFC)
        return true;

    // remove the chunk from the state

    subRefCP(_mfChunks[classid + index]);

    _mfChunks[classid + index] = NullFC;
    
    return false;
}

/*! Remove all chunks from the state
*/

void State::clearChunks(void)
{
    std::transform(_mfChunks.begin(), 
                   _mfChunks.end  (), 
                   _mfChunks.begin(),
                    ClearSlot());
}

/*-------------------------- comparison -----------------------------------*/


/*! Calculate the switch cost for the whole state, which is the sum of the
switch cost of all its chunks. Right now it's always 0.
*/

Real32 State::switchCost(State *OSG_CHECK_ARG(state))
{
    return 0;
}

bool State::operator < (const State &other) const
{
    return this < &other;
}

/*! Compare the two states. Not implemented yet, always false.
*/

bool State::operator == (const State &OSG_CHECK_ARG(other)) const
{
    return false;
}

bool State::operator != (const State &other) const
{
    return ! (*this == other);
}
