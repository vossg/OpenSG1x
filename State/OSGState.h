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

class OSGState;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

typedef OSGFCPtr<OSGStateChunkPtr, OSGState> OSGStatePtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup baselib
 *  \brief Brief
 *
 *  detailed
 */

class OSGState : public OSGFieldContainer
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_FC_FIRST_FIELD_IDM_DECL(OSGChunksField)

    OSG_FC_LAST_FIELD_IDM_DECL

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

	typedef OSGFieldContainer Inherited;
    typedef OSGStateChunkPtr OSGPtr;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "OSGState"; }
 
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_FIELD_CONTAINER_DECL(OSGStatePtr)

    /*----------------------------- dump ----------------------------------*/

    virtual void dump(void) const;
 
    /*------------------------- your_category -------------------------------*/

	// call the OpenGL commands to set my part of the state.
	void activate ( void );

	// call commands to get from old to my state. 
	void changeFrom( OSGState * old );

	// reset my part of the state.
	void deactivate ( void );

    /*----------------------------- access ----------------------------------*/

	// get the chunk, returns OSGNullStateChunk if not present
	
	OSGStateChunkPtr getChunk( OSGUInt32 id );
	
	// check if there's already a chunk of that type present
	
	OSGBool chunkPresent( OSGUInt32 id );
	OSGBool chunkPresent( OSGStateChunkPtr chunk );
	
	// add the chunk to the state
	// index == -1: find an empty slot
	void addChunk( OSGStateChunkPtr chunk, OSGInt32 index = 0 );
	
	// remove the chunk from the state
	// index == -1: find it in the classes slots	
	void subChunk( OSGStateChunkPtr chunk, OSGInt32 index = -1 );
	
	// remove the chunk of the given class from the state
	void subChunk( OSGUInt32 classid, OSGInt32 index = -1 );
	
    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

	// estimate the cost to switch to the state 
	// the unit is unclear, maybe musecs. It's not important anyway,
	// it just has to be consistent over all types of chunks
	virtual OSGReal32 switchCost( OSGState * state );

	// defines an ordering for states.
    virtual OSGBool operator < (const OSGState &other) const;
    
	virtual OSGBool operator == (const OSGState &other) const;
	virtual OSGBool operator != (const OSGState &other) const;

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

	OSGMFStateChunkPtr _chunks;
	
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	OSGMFStateChunkPtr *getMFChunks( void );

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

	friend class OSGFieldContainer;
	
    //-----------------------------------------------------------------------
    //   friend functions                                                    
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   class variables                                                     
    //-----------------------------------------------------------------------

	static char cvsid[];

	static OSGFieldDescription   _desc[];
	static OSGFieldContainerType _type;

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

    OSGState(void);
    virtual ~OSGState(void); 

    OSGState(const OSGState &source);    
	OSGState & operator =(const OSGState &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef OSGState *OSGStateP;

OSG_END_NAMESPACE

#include "OSGState.inl"

#endif /* _OSGSTATE_H_ */
