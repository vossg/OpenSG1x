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


#ifndef _OSGCHUNKMATERIAL_H_
#define _OSGCHUNKMATERIAL_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGState.h"
#include "OSGMaterial.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class State;
typedef FCPtr <FieldContainerPtr, State> StatePtr;

class StateChunk;
typedef FCPtr <FieldContainerPtr, StateChunk> StateChunkPtr;
typedef MField<StateChunkPtr                   > MFStateChunkPtr;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

class ChunkMaterial;
typedef FCPtr <MaterialPtr, ChunkMaterial> ChunkMaterialPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup baselib
 *  \brief Brief
 *
 *  detailed
 */

class OSG_MATERIAL_DLLMAPPING ChunkMaterial : public Material
{
  private:

	typedef Material Inherited;

  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_FC_FIRST_FIELD_IDM_DECL(StateChunksField)

    OSG_FC_LAST_FIELD_IDM_DECL (StateChunksField)

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef ChunkMaterialPtr Ptr;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "ChunkMaterial"; }
 
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_FIELD_CONTAINER_DECL(ChunkMaterialPtr)

    /*----------------------------- dump ----------------------------------*/

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector &bvFlags  = 0) const;

    /*------------------------- your_category -------------------------------*/


	/** sets up the OpenGL and calls the Geometry's draw method.
	    Not sure that's the best idea. Alternative: Functor */
	
	virtual void draw( Geometry* geo, DrawAction * action );

    /*----------------------------- access ----------------------------------*/
	
	/** derived access */
	
	// add a chunk to the material. Light & Transform chunks are not allowed
	Bool 	addChunk( StateChunkPtr chunk );
	
	// remove the chunk from the material
	Bool 	subChunk( StateChunkPtr chunk );
	
    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

#if 0
	// defines an ordering for materials.
    virtual Bool operator < (const ChunkMaterial &other) const;
    
	virtual Bool operator == (const ChunkMaterial &other) const;
	virtual Bool operator != (const ChunkMaterial &other) const;
#endif

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

	/** property access. Returns FCNULL if not set or available. */

	MFStateChunkPtr		*getMFStateChunks( void );


    ChunkMaterial(void);
    ChunkMaterial(const ChunkMaterial &source);    
    virtual ~ChunkMaterial(void); 

  private:

    //-----------------------------------------------------------------------
    //   enums                                 pri                              
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

	ChunkMaterial & operator =(const ChunkMaterial &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef ChunkMaterial *ChunkMaterialP;

OSG_END_NAMESPACE

#include "OSGChunkMaterial.inl"

#endif /* _ChunkMaterial_H_ */
