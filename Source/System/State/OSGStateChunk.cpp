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

#include "OSGStateChunk.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::StateChunk
    \ingroup GrpSystemState
    
See \ref PageSystemState for the conceptual background. 

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/*! \class osg::StateChunkClass
    \ingroup GrpSystemState

See \ref StateChunkClass for the
conceptual background.

*/

/*! \var osg::StateChunkClass::_classId
    The numerical ID associated with each StateChunkClass. It is used to
    uniquely identify and quickly compare the class.
    
    \dev The classId is consecutive in the number of slots allocated to the
    chunk class, i.e. if a class has id 4 and 4 chunks, the next registered
    class will get id 8. The classId is used as an index into the osg::State's
    chunk vector, which necessitates this behaviour. \enddev
*/   

/*! The global vector of known StateChunkClasses' names. Use
    StateChunkClass::getName with the Classes ID to access it.
    
    \dev See the osg::StateChunkClass::_classId for details. \enddev
*/   

std::vector<std::string> *StateChunkClass::_classNames = NULL;

/*! The global vector of known StateChunkClasses' number of concurrently
    active slots. Use StateChunkClass::getNumSlots with the Class's ID to access
    it.
    
    \dev See the osg::StateChunkClass::_classId for details. \enddev
*/   

std::vector<UInt32> *StateChunkClass::_numslots   = NULL;

/*! Constructor. The name is mandatory, the number of concurrently active slots
    is optional, default is 1. 
*/

StateChunkClass::StateChunkClass(Char8 *name, UInt32 numslots)
{
    if(!_classNames)
    {
        _classNames = new std::vector<std::string>(0);
        _numslots   = new std::vector<     UInt32>(0);
    }

    _classId = _classNames->size();

    for(unsigned i = 0; i < numslots; i++)
    {
        _classNames->push_back(std::string(name));
        _numslots->push_back (numslots);
    }
}

UInt32 StateChunkClass::getId(void) const
{
    return _classId;
}

const Char8 *StateChunkClass::getName(void) const
{
    return(*_classNames)[_classId].c_str();
}

Int32 StateChunkClass::getNumSlots(void) const
{
    return(*_numslots)[_classId];
}

/*! Access the name for the class whose id is index. 
*/

const Char8 *StateChunkClass::getName(UInt32 index)
{
    if(index >=(*_classNames).size())
            return "<Unknown StatChunkClass!>";

    return(*_classNames)[index].c_str();
}

/*! Access the number of slots for the class whose id is index. 
*/

Int32 StateChunkClass::getNumSlots(UInt32 index)
{
    if(index >= (*_numslots).size())
        return -1;

    return (*_numslots)[index];
}

/*! \var osg::StateChunkClass::iterator

    Iterator type to access the chunk class list.
*/

/*! Iterator to allow access to all known StateChunkClasses. 
*/

StateChunkClass::iterator StateChunkClass::begin(void)
{
    return _classNames->begin();
}

/*! Iterator to allow access to all known StateChunkClasses. 
*/

StateChunkClass::iterator StateChunkClass::end(void)
{
    return _classNames->end();
}

void StateChunkClass::swap(StateChunkClass &other)
{
    FINFO(("Swap %s(%d|%d) %s(%d|%d)\n",
           this->getName(),
           this->getId(),
           this->getNumSlots(),
           other.getName(),
           other.getId(),
           other.getNumSlots()));

    bool bNeighborSwap = false;

    if(this->getNumSlots() != other.getNumSlots())
    {
        if( ( (this->getId() < other.getId() &&
               this->getId() + this->getNumSlots() != other.getId()) ||
              (other.getId() < this->getId() &&
               other.getId() + other.getNumSlots() != this->getId())  ) )
        {
            FWARNING(("Can only swap if #slots is equal or if"
                      "the chunks are neighbors\n"));
            return;
        }
        else
        {
            bNeighborSwap = true;
        }
    }

    std::string thisName      = this->getName    ();
    UInt32      thisNumSlots  = this->getNumSlots();

    std::string otherName     = other.getName    ();
    UInt32      otherNumSlots = other.getNumSlots();

    if(bNeighborSwap == false)
    {
        UInt32 tmp;

        tmp            = this->_classId;
        this->_classId = other._classId;
        other._classId = tmp;
    }
    else
    {
        if(this->_classId < other._classId)
        {
            other._classId  = this->_classId;
            this->_classId += otherNumSlots;
        }
        else
        {
            this->_classId  = other._classId;
            other._classId += thisNumSlots;
       }
    }

    for(UInt32 i = this->getId(); 
               i < this->getId() + thisNumSlots;
             ++i)
    { 
        (*_classNames)[i] = thisName;
        (*_numslots  )[i] = thisNumSlots;
    }

    for(UInt32 i = other.getId(); 
               i < other.getId() + otherNumSlots;
             ++i)
    { 
        (*_classNames)[i] = otherName;
        (*_numslots  )[i] = otherNumSlots;
    }
}

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char StateChunk::cvsid[] = "@(#)$Id: $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void StateChunk::initMethod(void)
{
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

StateChunk::StateChunk(void) :
    Inherited()
{
}

StateChunk::StateChunk(const StateChunk &source) :
    Inherited(source)
{
}

StateChunk::~StateChunk(void)
{
}

/*------------------------------- Sync -----------------------------------*/

void StateChunk::changed(BitVector, UInt32)
{
}

/*------------------------------ Output ----------------------------------*/

void StateChunk::dump(      UInt32    OSG_CHECK_ARG(uiIndent),
                      const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump StateChunk NI" << std::endl;
}


/*------------------------------ State ------------------------------------*/

void StateChunk::update(DrawActionBase *OSG_CHECK_ARG(action))
{
}

/*! Activate the chunk, i.e. set the OpenGl state covered by the chunk which is
    different from the default state to the given state.
*/

void StateChunk::activate(DrawActionBase *OSG_CHECK_ARG(action), 
                          UInt32          OSG_CHECK_ARG(index ))
{
    FWARNING(("StateChunk::activate called!\n"));
}

/*! Change from an old chunk of the same type to this chunk. Note that in
    general no type checking is done, make sure to use this on a legal 
    combination of chunks!
*/

void StateChunk::changeFrom(DrawActionBase *action, 
                            StateChunk     *old, 
                            UInt32          index)
{
    old->deactivate(action, index);
    activate(action, index);
}

/*! Deactivate the chunk, i.e. set the OpenGl state covered by the chunk which is
    different from the default state to the default state.
*/

void StateChunk::deactivate(DrawActionBase *OSG_CHECK_ARG(action), 
                            UInt32          OSG_CHECK_ARG(index))
{
    FWARNING(("StateChunk::deactivate called!\n"));
}

/*! Check if the chunk is transparent, i.e. needs to be rendered after the
    opaque objects.
*/

bool StateChunk::isTransparent(void) const
{
    return false;
}

/*---------------------- Chunk Class Access -------------------------------*/

const StateChunkClass *StateChunk::getClass(void) const
{
    return NULL;
}

/*-------------------------- Comparison -----------------------------------*/

/*! Calculate how expensive it is to switch from one instance of the chunk
    class to another. In most cases not implemented yet, will return 0.
*/

Real32 StateChunk::switchCost(StateChunk *OSG_CHECK_ARG(chunk))
{
    return 0;
}

bool StateChunk::operator <(const StateChunk &other) const
{
    return this < &other;
}

/*! Compare two chunks. In most cases not implemented yet, will return false.
*/

bool StateChunk::operator ==(const StateChunk &OSG_CHECK_ARG(other)) const
{
    return false;
}

bool StateChunk::operator !=(const StateChunk &other) const
{
    return !(*this == other);
}
