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

#ifndef _OSGSTATE_H_
#define _OSGSTATE_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <vector>

#include "OSGFieldDescription.h"
#include "OSGFieldContainer.h"
#include "OSGStateChunk.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class State;
class DrawAction;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

typedef FCPtr<FieldContainerPtr, State> StatePtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup baselib
 *  \brief Brief
 *
 *  detailed
 */

class OSG_STATE_DLLMAPPING State : public FieldContainer
{
  private:

	typedef FieldContainer Inherited;

  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_FC_FIRST_FIELD_IDM_DECL(ChunksField)

    OSG_FC_LAST_FIELD_IDM_DECL (ChunksField)

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef StateChunkPtr Ptr;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "State"; }
 
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_FIELD_CONTAINER_DECL(StatePtr)

    /*----------------------------- dump ----------------------------------*/

    virtual void dump(void) const;
 
    /*------------------------- your_category -------------------------------*/

	// call the OpenGL commands to set my part of the state.
	void activate ( DrawAction *action );

	// call commands to get from old to my state. 
	void changeFrom( DrawAction *action, State * old );

	// reset my part of the state.
	void deactivate ( DrawAction *action );

    /*----------------------------- access ----------------------------------*/

	// get the chunk, returns NullStateChunk if not present
	
	StateChunkPtr getChunk( UInt32 id );
	
	// check if there's already a chunk of that type present
	
	Bool chunkPresent( UInt32 id );
	Bool chunkPresent( StateChunkPtr chunk );
	
	// add the chunk to the state
	// index == -1: find an empty slot
	void addChunk( StateChunkPtr chunk, Int32 index = 0 );
	
	// remove the chunk from the state
	// index == -1: find it in the classes slots	
	void subChunk( StateChunkPtr chunk, Int32 index = -1 );
	
	// remove the chunk of the given class from the state
	void subChunk( UInt32 classid, Int32 index = -1 );
	
    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

	// estimate the cost to switch to the state 
	// the unit is unclear, maybe musecs. It's not important anyway,
	// it just has to be consistent over all types of chunks
	virtual Real32 switchCost( State * state );

	// defines an ordering for states.
    virtual Bool operator < (const State &other) const;
    
	virtual Bool operator == (const State &other) const;
	virtual Bool operator != (const State &other) const;

    /*------------------------- debug ----------------------------------*/

	void print( void );
	
  protected:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------

	MFStateChunkPtr _chunks;
	
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	MFStateChunkPtr *getMFChunks( void );

  private:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   friend classes                                                      
    //-----------------------------------------------------------------------

	friend class FieldContainer;
	
    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

	static FieldDescription   _desc[];
	static FieldContainerType _type;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------
	
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// prohibit default functions (move to 'public' if you need one)

    State(void);
    virtual ~State(void); 

    State(const State &source);    
	State & operator =(const State &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef State *StateP;

OSG_END_NAMESPACE

#include "OSGState.inl"

#endif /* _OSGSTATE_H_ */
