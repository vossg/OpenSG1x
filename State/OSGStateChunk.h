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


#ifndef _OSGSTATECHUNK_H_
#define _OSGSTATECHUNK_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

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

class OSGStateChunk;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

typedef OSGFCPtr<OSGFieldContainerPtr, OSGStateChunk> OSGStateChunkPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

// little helper class to wrap and create chunk ids
// the id is a low int to index into the state's chunk vector
// A static instance of this is part of every new chunk class

class OSGStateChunkClass
{
  public:

	OSGStateChunkClass( OSGString name, OSGUInt32 numslots = 1 );
	
	// get name and id of this class
	OSGUInt32 getID( void ) const;	
	const OSGString getName( void ) const;
	OSGUInt32 getNumSlots( void ) const;
	
	// get name and id of indicated class
	static const OSGString getName( OSGUInt32 index ) ;
	static OSGUInt32 getNumSlots( OSGUInt32 index ) ;
	
	// access to the class name list
	typedef vector<OSGString>::const_iterator iterator;
	
    static iterator begin(); 
    static iterator end();
	
  private:
  	
	OSGUInt32 _classId;	
	static vector<OSGString>* _classNames;
	static vector<OSGUInt32>* _numslots;
};

/*! \ingroup baselib
 *  \brief Brief
 *
 *  detailed
 */

class OSGStateChunk : public OSGFieldContainer
{
  public:

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

    static const char *getClassname(void) { return "StateChunk"; }
 
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_ABSTR_FIELD_CONTAINER_DECL(OSGStateChunkPtr)

    /*----------------------------- dump ----------------------------------*/

    virtual void dump(void) const;

    /*------------------------- your_category -------------------------------*/

	// call the OpenGL commands to set my part of the state 
	virtual void activate ( OSGUInt32 index = 0 );

	// call commands to get from old to my state. Only meaningful for
	// chunks of the same type
	virtual void changeFrom( OSGStateChunk * old, OSGUInt32 index = 0 );

	// reset my part of the state
	virtual void deactivate ( OSGUInt32 index = 0 );

    /*----------------------------- access ----------------------------------*/

	inline OSGUInt32 getClassID( void ) const;	
	virtual const OSGStateChunkClass * getClass( void ) const;	

    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

	// estimate the cost to switch to the chunk 
	// the unit is unclear, maybe musecs. It's not important anyway,
	// it just has to be consistent over all types of chunks
	virtual OSGReal32 switchCost( OSGStateChunk * chunk );

	// defines an ordering for chunks. Only well defined for chunks of the
	// same type.
    virtual OSGBool operator < (const OSGStateChunk &other) const;
    
	virtual OSGBool operator == (const OSGStateChunk &other) const;
	virtual OSGBool operator != (const OSGStateChunk &other) const;

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
	OSGUInt32 _ownClass;

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGStateChunk(void);
	OSGStateChunk( const OSGStateChunk& source );
    virtual ~OSGStateChunk(void); 

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

	// OSGStateChunk & operator =(const OSGStateChunk &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef OSGStateChunk *OSGStateChunkP;

// pointer field

template <>
struct OSGFieldDataTraits<OSGStateChunkPtr> : public OSGTraits
{
    static char *getSName(void) { return "SFStateChunkPtr"; }
    static char *getMName(void) { return "MFStateChunkPtr"; }

    static OSGBool          getDefault(void)    { return false; }

    static bool             getFromString(OSGStateChunkPtr &,
                                          const char *&)
    {
        // TO_BE_DONE
        return false;
    }

    static void             putToString(const OSGStateChunkPtr &,
                                              OSGString &)
    {
        // TO_BE_DONE
    }
};

typedef OSGSField<OSGStateChunkPtr> OSGSFStateChunkPtr;
typedef OSGMField<OSGStateChunkPtr> OSGMFStateChunkPtr;

// null pointer

extern OSGStateChunkPtr OSGNullStateChunk;

OSG_END_NAMESPACE

#include "OSGStateChunk.inl"

#endif /* _OSGSTATECHUNK_H_ */
