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

class LightChunk;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

typedef FCPtr<StateChunkPtr, LightChunk> LightChunkPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup baselib
 *  \brief Brief
 *
 *  detailed
 */

class OSG_DLLEXPORT LightChunk : public StateChunk
{
  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_FC_FIRST_FIELD_IDM_DECL(DiffuseField             )

    OSG_FC_FIELD_IDM_DECL      (AmbientField             )  
    OSG_FC_FIELD_IDM_DECL      (SpecularField            )  
    OSG_FC_FIELD_IDM_DECL      (PositionField            )  
    OSG_FC_FIELD_IDM_DECL      (DirectionField           )   
    OSG_FC_FIELD_IDM_DECL      (ExponentField            )
    OSG_FC_FIELD_IDM_DECL      (CutoffField              )  
    OSG_FC_FIELD_IDM_DECL      (ConstantAttenuationField )  
    OSG_FC_FIELD_IDM_DECL      (LinearAttenuationField   )  
    OSG_FC_FIELD_IDM_DECL      (QuadraticAttenuationField)  

    OSG_FC_LAST_FIELD_IDM_DECL

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

	typedef StateChunk Inherited;
    typedef LightChunkPtr Ptr;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "LightChunk"; }
 
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_FIELD_CONTAINER_DECL(LightChunkPtr)

	virtual const StateChunkClass *  getClass( void ) const;

    /*----------------------------- dump ----------------------------------*/

    virtual void dump(void) const;
 
    /*------------------------- your_category -------------------------------*/

	// call the OpenGL commands to set my part of the state 
	virtual void activate ( UInt32 index );

	// call commands to get from old to my state. Only meaningful for
	// chunks of the same type
	virtual void changeFrom( StateChunk * old, UInt32 index );

	// reset my part of the state
	virtual void deactivate ( UInt32 index );

    /*----------------------------- access ----------------------------------*/

	// Diffuse Color
	
        SFVec4f  *getSFDiffuse( void );
          Vec4f   &getDiffuse  ( void );
    const Vec4f   &getDiffuse  ( void ) const;
	void           setDiffuse  ( const Vec4f & color );

	// Ambient Color
	
        SFVec4f   *getSFAmbient( void );
          Vec4f   &getAmbient  ( void );
    const Vec4f   &getAmbient  ( void ) const;
	void           setAmbient  ( const Vec4f & color );

	// Specular Color
	
        SFVec4f   *getSFSpecular( void );
          Vec4f   &getSpecular  ( void );
    const Vec4f   &getSpecular  ( void ) const;
	void           setSpecular  ( const Vec4f & color );

	// Position
	
        SFVec4f   *getSFPosition( void );
          Vec4f   &getPosition  ( void );
    const Vec4f   &getPosition  ( void ) const;
	void           setPosition  ( const Vec4f & pos );

	// Direction
	
        SFVec3f   *getSFDirection( void );
          Vec3f   &getDirection  ( void );
    const Vec3f   &getDirection  ( void ) const;
	void           setDirection  ( const Vec3f & dir );

	// Exponent
	
        SFReal32   *getSFExponent( void );
          Real32    getExponent  ( void );
          Real32    getExponent  ( void ) const;
	void            setExponent  ( const Real32 exponent );

	// Cutoff
	
        SFReal32   *getSFCutoff( void );
          Real32    getCutoff  ( void );
          Real32    getCutoff  ( void ) const;
	void            setCutoff  ( const Real32 cutoff );

	// Constant Attenuation
	
        SFReal32   *getSFConstantAttenuation( void );
          Real32    getConstantAttenuation  ( void );
          Real32    getConstantAttenuation  ( void ) const;
	void            setConstantAttenuation  ( const Real32 constAtt );

	// Linear Attenuation
	
        SFReal32   *getSFLinearAttenuation( void );
          Real32    getLinearAttenuation  ( void );
          Real32    getLinearAttenuation  ( void ) const;
	void            setLinearAttenuation  ( const Real32 linAtt );

	// Quadratic Attenuation
	
        SFReal32   *getSFQuadraticAttenuation( void );
          Real32    getQuadraticAttenuation  ( void );
          Real32    getQuadraticAttenuation  ( void ) const;
	void            setQuadraticAttenuation  ( const Real32 quadAtt );

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

	// class. Used for indexing in State
	static StateChunkClass _class;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   instance variables                                                  
    //-----------------------------------------------------------------------
	
	SFVec4f _diffuse;
	SFVec4f _ambient;
	SFVec4f _specular;
	SFVec4f _position;
	SFVec3f _direction;
	SFReal32 _exponent;
	SFReal32 _cutoff;
	SFReal32 _constantAttenuation;
	SFReal32 _linearAttenuation;
	SFReal32 _quadraticAttenuation;
	
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    LightChunk(void);
    LightChunk(const LightChunk &source);    
    virtual ~LightChunk(void); 

	LightChunk &operator =(const LightChunk &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef LightChunk *LightChunkP;

OSG_END_NAMESPACE

#include "OSGLightChunk.inl"

#endif /* _OSGLIGHTCHUNK_H_ */
