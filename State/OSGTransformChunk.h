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


#ifndef _OSGTRANSFORMCHUNK_H_
#define _OSGTRANSFORMCHUNK_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <vector>

#include "OSGFieldContainerPtr.h"
#include "OSGSFMathTypes.h"
#include "OSGStateChunk.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class OSGTransformChunk;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

typedef OSGFCPtr<OSGStateChunkPtr, OSGTransformChunk> OSGTransformChunkPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup baselib
 *  \brief Brief
 *
 *  detailed
 */

class OSGTransformChunk : public OSGStateChunk
{
  public:

  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------
    
    OSG_FC_FIRST_FIELD_IDM_DECL(OSGMatrixField)

    OSG_FC_LAST_FIELD_IDM_DECL

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

	typedef OSGStateChunk Inherited;
    typedef OSGTransformChunkPtr OSGPtr;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "TransformChunk"; }
 
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_FIELD_CONTAINER_DECL(OSGTransformChunkPtr)

	virtual const OSGStateChunkClass *  getClass( void ) const;

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

    OSGSFMatrix *getSFMatrix(void);

          OSGMatrix   &getMatrix  (void);
    const OSGMatrix   &getMatrix  (void) const;

	void               setMatrix  ( const OSGMatrix & matrix );

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

    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------



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

	// class. Used for indexing in State
	static OSGStateChunkClass _class;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------
	
	OSGSFMatrix _matrix;
	
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// prohibit default functions (move to 'public' if you need one)

    OSGTransformChunk(void);
    OSGTransformChunk(const OSGTransformChunk &source);    
    virtual ~OSGTransformChunk(void); 

	OSGTransformChunk & operator =(const OSGTransformChunk &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef OSGTransformChunk *OSGTransformChunkP;

OSG_END_NAMESPACE

#include "OSGTransformChunk.inl"

#endif /* _OSGTRANSFORMCHUNK_H_ */
