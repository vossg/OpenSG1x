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


#ifndef _OSGMATERIALCHUNK_H_
#define _OSGMATERIALCHUNK_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <vector>

#include "OSGFieldContainerPtr.h"
#include "OSGSFMathTypes.h"
#include "OSGSFVecTypes.h"
#include "OSGSFSysTypes.h"
#include "OSGStateChunk.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class OSGMaterialChunk;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

typedef OSGFCPtr<OSGStateChunkPtr, OSGMaterialChunk> OSGMaterialChunkPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup baselib
 *  \brief Brief
 *
 *  detailed
 */

class OSGMaterialChunk : public OSGStateChunk
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_FC_FIRST_FIELD_IDM_DECL(OSGDiffuseField             )

    OSG_FC_FIELD_IDM_DECL      (OSGAmbientField             )  
    OSG_FC_FIELD_IDM_DECL      (OSGSpecularField            )  
    OSG_FC_FIELD_IDM_DECL      (OSGEmissionField            )  
    OSG_FC_FIELD_IDM_DECL      (OSGShininessField           )   

    OSG_FC_LAST_FIELD_IDM_DECL

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

	typedef OSGStateChunk Inherited;
    typedef OSGMaterialChunkPtr OSGPtr;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "MaterialChunk"; }
 
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_FIELD_CONTAINER_DECL(OSGMaterialChunkPtr)

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

	// Diffuse Color
	
        OSGSFVec4f   *getSFDiffuse( void );
          OSGVec4f   &getDiffuse  ( void );
    const OSGVec4f   &getDiffuse  ( void ) const;
	void              setDiffuse  ( const OSGVec4f & color );

	// Ambient Color
	
        OSGSFVec4f   *getSFAmbient( void );
          OSGVec4f   &getAmbient  ( void );
    const OSGVec4f   &getAmbient  ( void ) const;
	void              setAmbient  ( const OSGVec4f & color );

	// Specular Color
	
        OSGSFVec4f   *getSFSpecular( void );
          OSGVec4f   &getSpecular  ( void );
    const OSGVec4f   &getSpecular  ( void ) const;
	void              setSpecular  ( const OSGVec4f & color );

	// Emission Color
	
        OSGSFVec4f   *getSFEmission( void );
          OSGVec4f   &getEmission  ( void );
    const OSGVec4f   &getEmission  ( void ) const;
	void              setEmission  ( const OSGVec4f & color );

	// Shininess
	
        OSGSFReal32   *getSFShininess( void );
          OSGReal32    getShininess  ( void );
          OSGReal32    getShininess  ( void ) const;
	void               setShininess  ( const OSGReal32 shininess );

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
	
	OSGSFVec4f _diffuse;
	OSGSFVec4f _ambient;
	OSGSFVec4f _specular;
	OSGSFVec4f _emission;
	OSGSFReal32 _shininess;
	
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// prohibit default functions (move to 'public' if you need one)

    OSGMaterialChunk(void);
    OSGMaterialChunk(const OSGMaterialChunk &source);    
    virtual ~OSGMaterialChunk(void); 

	OSGMaterialChunk & operator =(const OSGMaterialChunk &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef OSGMaterialChunk *OSGMaterialChunkP;

OSG_END_NAMESPACE

#include "OSGMaterialChunk.inl"

#endif /* _OSGMATERIALCHUNK_H_ */
