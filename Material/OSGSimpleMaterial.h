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

#include "OSGSFBaseTypes.h"
#include "OSGChunkMaterial.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class MaterialChunk;
typedef FCPtr<StateChunkPtr, MaterialChunk> MaterialChunkPtr;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

class SimpleMaterial;
typedef FCPtr <ChunkMaterialPtr, SimpleMaterial> SimpleMaterialPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \brief SimpleMaterial class
 */

class OSG_MATERIAL_DLLMAPPING SimpleMaterial : public ChunkMaterial
{
  private:

    typedef ChunkMaterial Inherited;

  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_FC_FIRST_FIELD_IDM_DECL(AmbientField                     )

    OSG_FC_FIELD_IDM_DECL      (DiffuseField,      AmbientField  )
    OSG_FC_FIELD_IDM_DECL      (SpecularField,     DiffuseField  )
    OSG_FC_FIELD_IDM_DECL      (ShininessField,    SpecularField )
    OSG_FC_FIELD_IDM_DECL      (EmissionField,     ShininessField)
    OSG_FC_FIELD_IDM_DECL      (TransparencyField, EmissionField )

    OSG_FC_LAST_FIELD_IDM_DECL (TransparencyField                )

    static const SimpleMaterialPtr NullPtr;

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

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

     virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector &bvFlags  = 0) const;

    /*------------------------- your_category -------------------------------*/


    /** sets up the OpenGL and calls the Geometry's draw method.
        Not sure that's the best idea. Alternative: Functor */
    
    virtual void draw( Geometry* geo, DrawAction * action );

    /*----------------------------- access ----------------------------------*/
    
    // Ambient Color
       
            SFColor3f   *getSFAmbient( void );
            Color3f     &getAmbient  ( void );
    const   Color3f     &getAmbient  ( void ) const;
    void                 setAmbient  ( const Color3f & color );
    
    // Diffuse Color
       
            SFColor3f   *getSFDiffuse( void );
            Color3f     &getDiffuse  ( void );
    const   Color3f     &getDiffuse  ( void ) const;
    void                 setDiffuse  ( const Color3f & color );
    
    // Specular Color
       
            SFColor3f   *getSFSpecular( void );
            Color3f     &getSpecular  ( void );
    const   Color3f     &getSpecular  ( void ) const;
    void                 setSpecular  ( const Color3f & color );
    
    // Shininess 
       
            SFReal32    *getSFShininess( void );
            Real32       getShininess  ( void );
            Real32       getShininess  ( void ) const;
    void                 setShininess  ( const Real32 color );
    
    // Emission Color
       
            SFColor3f   *getSFEmission( void );
            Color3f     &getEmission  ( void );
    const   Color3f     &getEmission  ( void ) const;
    void                 setEmission  ( const Color3f & color );
    
    // Transparency 
       
            SFReal32    *getSFTransparency( void );
            Real32       getTransparency  ( void );
            Real32       getTransparency  ( void ) const;
    void                 setTransparency  ( const Real32 color );

    
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
    
    SFColor3f   _ambient;
    SFColor3f   _diffuse;
    SFColor3f   _specular;
    SFReal32    _shininess;
    SFColor3f   _emission;
    SFReal32    _transparency;
    
    // this chunk is used for rendering the material
    
    MaterialChunkPtr    _materialChunk;
    
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
