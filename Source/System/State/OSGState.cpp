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

#include <OSGGL.h>

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
    clearChunks();
}


/** \brief react to field changes
 */

void State::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */

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


/*-------------------------- your_category---------------------------------*/

void State::addChunk(StateChunkPtr chunk, Int32 index)
{
    if(index > 0 && index > chunk->getClass()->getNumSlots())
    {
        SWARNING << "addChunk: index " 
                 << index
                 << " > Numslots "
                 << chunk->getClass()->getNumSlots()
                 << ",  ignored!" 
                 << std::endl;
        return;
    }

    UInt32 cindex =  chunk->getClassID();
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
                return;
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

    if(_mfChunks[cindex] != chunk)
    {
        setRefdCP(_mfChunks[cindex], chunk);
    }
}


void State::subChunk(StateChunkPtr chunk, Int32 index)
{
    if(index > 0 && index > chunk->getClass()->getNumSlots())
    {
        SWARNING << "subChunk: index "
                 << index
                 << " > Numslots "
                 << chunk->getClass()->getNumSlots()
                 << ",  ignored!" 
                 << std::endl;
        return;
    }

    UInt32 cindex =  chunk->getClassID();
    UInt32 csize  = _mfChunks.size();

    // special case: find it in the slots
    if(index < 0)
    {
        UInt8 nslots = chunk->getClass()->getNumSlots();
        UInt8 ci;

        for(ci = cindex; ci < cindex + nslots && ci < csize; ci++)
        {
            if(_mfChunks[ci] == chunk)
            {
                break;
            }
        }

        if(ci >= cindex + nslots)    // no free slot found
        {
            SWARNING << "subChunk: chunk " 
                     << chunk
                     << " of class "
                     << chunk->getClass()->getName()
                     << " not found!" 
                     << std::endl;
            return;
        }

        cindex = ci;
    }

    // remove the chunk from the state

     subRefCP(_mfChunks[cindex]);

    _mfChunks[cindex] = NullFC;
}

void State::subChunk(UInt32 classid, Int32 index)
{
    if(index > 0 && index > StateChunkClass::getNumSlots(classid))
    {
        SWARNING << "subChunk: index " << index << " > Numslots "
                 << StateChunkClass::getNumSlots(classid)
                 << ",  ignored!" << std::endl;
        return;
    }

    // remove the chunk from the state

    subRefCP(_mfChunks[classid + index]);

    _mfChunks[classid + index] = NullFC;
}

struct ClearSlot : public std::unary_function<      StateChunkPtr         &, 
                                              const NullFieldContainerPtr &>
{
    const NullFieldContainerPtr &operator() (StateChunkPtr &slotPtr) 
    { 
        subRefCP(slotPtr);
        
        return NullFC;
    }
};


void State::clearChunks(void)
{
    std::transform(_mfChunks.begin(), 
                   _mfChunks.end  (), 
                   _mfChunks.begin(),
                    ClearSlot());
}


// call the OpenGL commands to set my part of the state.
void State::activate(DrawActionBase *action)
{
    MFStateChunkPtr::iterator it;
    Int32 ind = 0;
    UInt32 cind;

    for(it = _mfChunks.begin(), cind = 0; it != _mfChunks.end();
          ++it, ++cind)
    {
        if(*it != NullFC)
        {
            (*it)->activate(action, UInt32(ind));
        }
        if(++ind >= StateChunkClass::getNumSlots(cind))
            ind = 0;
    }
}

// call commands to get from old to my state.
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

        if(n != NullFC)
        {
            if(o != NullFC)
                n->changeFrom(action, o.getCPtr(), UInt32(ind));
            else
                n->activate(action, UInt32(ind));
        }
        else if(o != NullFC)
            o->deactivate(action, UInt32(ind));

        if(++ind >= StateChunkClass::getNumSlots(cind))
            ind = 0;
    }

    ind = 0;

    for(i = cind; i < old->getChunks().size(); ++i)
    {
        StateChunkPtr o = old->getChunk(i);

        if(o != NullFC)
        {
            o->deactivate(action, UInt32(ind));
        }

        if(++ind >= StateChunkClass::getNumSlots(cind))
        {
            ind = 0;
        }
    }
}


// reset my part of the state.
void State::deactivate(DrawActionBase *action)
{
    MFStateChunkPtr::iterator it;
    Int32 ind = 0;
    UInt32 cind;

    for(it = _mfChunks.begin(), cind = 0; it != _mfChunks.end();
          ++it, ++cind)
    {
        if(*it != NullFC)
            (*it)->deactivate(action, UInt32(ind));
        if(++ind >= StateChunkClass::getNumSlots(cind))
            ind = 0;
    }
}

/*-------------------------- comparison -----------------------------------*/

Real32 State::switchCost(State *OSG_CHECK_ARG(state))
{
    return 0;
}

/** \brief assignment
 */

bool State::operator < (const State &other) const
{
    return this < &other;
}

/** \brief equal
 */

bool State::operator == (const State &OSG_CHECK_ARG(other)) const
{
    return false;
}

/** \brief unequal
 */

bool State::operator != (const State &other) const
{
    return ! (*this == other);
}


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

