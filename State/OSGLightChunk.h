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


#ifndef _OSGLIGHTCHUNK_H_
#define _OSGLIGHTCHUNK_H_
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

class OSGLightChunk;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

typedef OSGFCPtr<OSGStateChunkPtr, OSGLightChunk> OSGLightChunkPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup baselib
 *  \brief Brief
 *
 *  detailed
 */

class OSGLightChunk : public OSGStateChunk
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_FC_FIRST_FIELD_IDM_DECL(OSGDiffuseField             )

    OSG_FC_FIELD_IDM_DECL      (OSGAmbientField             )  
    OSG_FC_FIELD_IDM_DECL      (OSGSpecularField            )  
    OSG_FC_FIELD_IDM_DECL      (OSGPositionField            )  
    OSG_FC_FIELD_IDM_DECL      (OSGDirectionField           )   
    OSG_FC_FIELD_IDM_DECL      (OSGExponentField            )
    OSG_FC_FIELD_IDM_DECL      (OSGCutoffField              )  
    OSG_FC_FIELD_IDM_DECL      (OSGConstantAttenuationField )  
    OSG_FC_FIELD_IDM_DECL      (OSGLinearAttenuationField   )  
    OSG_FC_FIELD_IDM_DECL      (OSGQuadraticAttenuationField)  

    OSG_FC_LAST_FIELD_IDM_DECL

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

	typedef OSGStateChunk Inherited;
    typedef OSGLightChunkPtr OSGPtr;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "LightChunk"; }
 
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_FIELD_CONTAINER_DECL(OSGLightChunkPtr)

	virtual const OSGStateChunkClass *  getClass( void ) const;

    /*----------------------------- dump ----------------------------------*/

    virtual void dump(void) const;
 
    /*------------------------- your_category -------------------------------*/

	// call the OpenGL commands to set my part of the state 
	virtual void activate ( OSGUInt32 index );

	// call commands to get from old to my state. Only meaningful for
	// chunks of the same type
	virtual void changeFrom( OSGStateChunk * old, OSGUInt32 index );

	// reset my part of the state
	virtual void deactivate ( OSGUInt32 index );

    /*----------------------------- access ----------------------------------*/

	// Diffuse Color
	
        OSGSFVec4f  *getSFDiffuse( void );
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

	// Position
	
        OSGSFVec4f   *getSFPosition( void );
          OSGVec4f   &getPosition  ( void );
    const OSGVec4f   &getPosition  ( void ) const;
	void              setPosition  ( const OSGVec4f & pos );

	// Direction
	
        OSGSFVec3f   *getSFDirection( void );
          OSGVec3f   &getDirection  ( void );
    const OSGVec3f   &getDirection  ( void ) const;
	void              setDirection  ( const OSGVec3f & dir );

	// Exponent
	
        OSGSFReal32   *getSFExponent( void );
          OSGReal32    getExponent  ( void );
          OSGReal32    getExponent  ( void ) const;
	void               setExponent  ( const OSGReal32 exponent );

	// Cutoff
	
        OSGSFReal32   *getSFCutoff( void );
          OSGReal32    getCutoff  ( void );
          OSGReal32    getCutoff  ( void ) const;
	void               setCutoff  ( const OSGReal32 cutoff );

	// Constant Attenuation
	
        OSGSFReal32   *getSFConstantAttenuation( void );
          OSGReal32    getConstantAttenuation  ( void );
          OSGReal32    getConstantAttenuation  ( void ) const;
	void               setConstantAttenuation  ( const OSGReal32 constAtt );

	// Linear Attenuation
	
        OSGSFReal32   *getSFLinearAttenuation( void );
          OSGReal32    getLinearAttenuation  ( void );
          OSGReal32    getLinearAttenuation  ( void ) const;
	void               setLinearAttenuation  ( const OSGReal32 linAtt );

	// Quadratic Attenuation
	
        OSGSFReal32   *getSFQuadraticAttenuation( void );
          OSGReal32    getQuadraticAttenuation  ( void );
          OSGReal32    getQuadraticAttenuation  ( void ) const;
	void               setQuadraticAttenuation  ( const OSGReal32 quadAtt );

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
	OSGSFVec4f _position;
	OSGSFVec3f _direction;
	OSGSFReal32 _exponent;
	OSGSFReal32 _cutoff;
	OSGSFReal32 _constantAttenuation;
	OSGSFReal32 _linearAttenuation;
	OSGSFReal32 _quadraticAttenuation;
	
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    OSGLightChunk(void);
    OSGLightChunk(const OSGLightChunk &source);    
    virtual ~OSGLightChunk(void); 

	OSGLightChunk &operator =(const OSGLightChunk &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef OSGLightChunk *OSGLightChunkP;

OSG_END_NAMESPACE

#include "OSGLightChunk.inl"

#endif /* _OSGLIGHTCHUNK_H_ */
