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

#ifndef _OSGSTATECHUNK_H_
#define _OSGSTATECHUNK_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#if defined(WIN32) && defined(OSG_BUILD_DLL)
#   ifdef OSG_COMPILESTATE
#       define OSG_STATE_DLLMAPPING __declspec(dllexport)
#   else
#       define OSG_STATE_DLLMAPPING __declspec(dllimport)
#   endif
#else
#define OSG_STATE_DLLMAPPING
#endif

#include <vector>

#include "OSGBaseTypes.h"
#include "OSGMField.h"
#include "OSGSFBaseTypes.h"
#include "OSGFieldDescription.h"
#include "OSGFieldContainer.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class StateChunk;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

typedef FCPtr<FieldContainerPtr, StateChunk> StateChunkPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

// little helper class to wrap and create chunk ids
// the id is a low int to index into the state's chunk vector
// A static instance of this is part of every new chunk class

class OSG_STATE_DLLMAPPING StateChunkClass
{
  public:

	StateChunkClass( String name, UInt32 numslots = 1 );
	
	// get name and id of this class
	UInt32 getID( void ) const;	
	const String getName( void ) const;
	UInt32 getNumSlots( void ) const;
	
	// get name and id of indicated class
	static const String getName( UInt32 index ) ;
	static UInt32 getNumSlots( UInt32 index ) ;
	
	// access to the class name list
	typedef vector<String>::const_iterator iterator;
	
    static iterator begin(); 
    static iterator end();
	
  private:
  	
	UInt32 _classId;	
	static vector<String>* _classNames;
	static vector<UInt32>* _numslots;
};

/*! \ingroup baselib
 *  \brief Brief
 *
 *  detailed
 */

class OSG_STATE_DLLMAPPING StateChunk : public FieldContainer
{
  public:

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------
	
    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

	typedef FieldContainer Inherited;
    typedef StateChunkPtr Ptr;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "StateChunk"; }
 
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_ABSTR_FIELD_CONTAINER_DECL(StateChunkPtr)

    /*----------------------------- dump ----------------------------------*/

    virtual void dump(void) const;

    /*------------------------- your_category -------------------------------*/

	// call the OpenGL commands to set my part of the state 
	virtual void activate ( UInt32 index = 0 );

	// call commands to get from old to my state. Only meaningful for
	// chunks of the same type
	virtual void changeFrom( StateChunk * old, UInt32 index = 0 );

	// reset my part of the state
	virtual void deactivate ( UInt32 index = 0 );

    /*----------------------------- access ----------------------------------*/

	inline UInt32 getClassID( void ) const;	
	virtual const StateChunkClass * getClass( void ) const;	

    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

	// estimate the cost to switch to the chunk 
	// the unit is unclear, maybe musecs. It's not important anyway,
	// it just has to be consistent over all types of chunks
	virtual Real32 switchCost( StateChunk * chunk );

	// defines an ordering for chunks. Only well defined for chunks of the
	// same type.
    virtual Bool operator < (const StateChunk &other) const;
    
	virtual Bool operator == (const StateChunk &other) const;
	virtual Bool operator != (const StateChunk &other) const;

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

	// chunks class
	// set in constructor, never changed after that
	UInt32 _ownClass;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    StateChunk(void);
	StateChunk( const StateChunk& source );
    virtual ~StateChunk(void); 

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

	// StateChunk & operator =(const StateChunk &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef StateChunk *StateChunkP;

// pointer field

template <>
struct FieldDataTraits<StateChunkPtr> : public Traits
{
    enum                           { StringConvertable = 0x00  };

    static Char8 *getSName(void)   { return "SFStateChunkPtr"; }
    static Char8 *getMName(void)   { return "MFStateChunkPtr"; }

//  static Bool   getDefault(void) { return false;             }
};

typedef SField<StateChunkPtr> SFStateChunkPtr;
typedef MField<StateChunkPtr> MFStateChunkPtr;

// null pointer

extern StateChunkPtr NullStateChunk;

OSG_END_NAMESPACE

#include "OSGStateChunk.inl"

#endif /* _OSGSTATECHUNK_H_ */
