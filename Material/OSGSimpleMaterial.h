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


#ifndef _OSGSIMPLEMATERIAL_H_
#define _OSGSIMPLEMATERIAL_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGSFVecTypes.h"
#include "OSGChunkMaterial.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class MaterialChunk;
typedef FCPtr<StateChunkPtr, MaterialChunk> MaterialChunkPtr;
typedef SField<MaterialChunkPtr           > SFMaterialChunkPtr;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

class SimpleMaterial;
typedef FCPtr <ChunkMaterialPtr, SimpleMaterial> SimpleMaterialPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup baselib
 *  \brief Brief
 *
 *  detailed
 */

class OSG_MATERIAL_DLLMAPPING SimpleMaterial : public ChunkMaterial
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_FC_FIRST_FIELD_IDM_DECL(AmbientField)

    OSG_FC_FIELD_IDM_DECL(DiffuseField)
    OSG_FC_FIELD_IDM_DECL(SpecularField)
    OSG_FC_FIELD_IDM_DECL(ShininessField)
    OSG_FC_FIELD_IDM_DECL(EmissionField)
    OSG_FC_FIELD_IDM_DECL(TransparencyField)

    OSG_FC_LAST_FIELD_IDM_DECL

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

	typedef ChunkMaterial Inherited;
    typedef SimpleMaterialPtr Ptr;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "SimpleMaterial"; }
 
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_FIELD_CONTAINER_DECL(SimpleMaterialPtr)

    /*----------------------------- dump ----------------------------------*/

    virtual void dump(void) const;
 
    /*------------------------- your_category -------------------------------*/


	/** sets up the OpenGL and calls the Geometry's draw method.
	    Not sure that's the best idea. Alternative: Functor */
	
	virtual void draw( Geometry* geo, Action * action );

    /*----------------------------- access ----------------------------------*/
	
	// Ambient Color
       
			SFVec3f 	*getSFAmbient( void );
			Vec3f		&getAmbient  ( void );
	const	Vec3f		&getAmbient  ( void ) const;
	void				 setAmbient  ( const Vec3f & color );
	
	// Diffuse Color
       
			SFVec3f 	*getSFDiffuse( void );
			Vec3f		&getDiffuse  ( void );
	const	Vec3f		&getDiffuse  ( void ) const;
	void				 setDiffuse  ( const Vec3f & color );
	
	// Specular Color
       
			SFVec3f 	*getSFSpecular( void );
			Vec3f		&getSpecular  ( void );
	const	Vec3f		&getSpecular  ( void ) const;
	void				 setSpecular  ( const Vec3f & color );
	
	// Shininess 
       
			SFReal32 	*getSFShininess( void );
			Real32		 getShininess  ( void );
			Real32		 getShininess  ( void ) const;
	void				 setShininess  ( const Real32 color );
	
	// Emission Color
       
			SFVec3f 	*getSFEmission( void );
			Vec3f		&getEmission  ( void );
	const	Vec3f		&getEmission  ( void ) const;
	void				 setEmission  ( const Vec3f & color );
	
	// Transparency 
       
			SFReal32 	*getSFTransparency( void );
			Real32		 getTransparency  ( void );
			Real32		 getTransparency  ( void ) const;
	void				 setTransparency  ( const Real32 color );

	
    /*------------------------- assignment ----------------------------------*/

    /*------------------------- comparison ----------------------------------*/

#if 0
	// defines an ordering for materials.
    virtual Bool operator < (const SimpleMaterial &other) const;
    
	virtual Bool operator == (const SimpleMaterial &other) const;
	virtual Bool operator != (const SimpleMaterial &other) const;
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
	 
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------


    SimpleMaterial(void);
    SimpleMaterial(const SimpleMaterial &source);    
    virtual ~SimpleMaterial(void); 

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
	
	SFVec3f 	_ambient;
	SFVec3f 	_diffuse;
	SFVec3f 	_specular;
	SFReal32 	_shininess;
	SFVec3f 	_emission;
	SFReal32 	_transparency;
	
	// this chunk is used for rendering the material
	
	MaterialChunkPtr	_materialChunk;
	
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// prohibit default functions (move to 'public' if you need one)

	SimpleMaterial & operator =(const SimpleMaterial &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef SimpleMaterial *SimpleMaterialP;

OSG_END_NAMESPACE

#include "OSGSimpleMaterial.inl"

#endif /* _SimpleMaterial_H_ */
