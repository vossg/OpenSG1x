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
#include "OSGSFBaseTypes.h"
#include "OSGStateChunk.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class OSG_STATE_DLLMAPPING MaterialChunk;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

typedef FCPtr<StateChunkPtr, MaterialChunk> MaterialChunkPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup baselib
 *  \brief Brief
 *
 *  detailed
 */

class MaterialChunk : public StateChunk
{
  private:

	typedef StateChunk Inherited;

  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------

    OSG_FC_FIRST_FIELD_IDM_DECL(DiffuseField                 )

    OSG_FC_FIELD_IDM_DECL      (AmbientField,   DiffuseField )  
    OSG_FC_FIELD_IDM_DECL      (SpecularField,  AmbientField )  
    OSG_FC_FIELD_IDM_DECL      (EmissionField,  SpecularField)  
    OSG_FC_FIELD_IDM_DECL      (ShininessField, EmissionField)   

    OSG_FC_LAST_FIELD_IDM_DECL(ShininessField                )

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef MaterialChunkPtr Ptr;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "MaterialChunk"; }
 
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_FIELD_CONTAINER_DECL(MaterialChunkPtr)

	virtual const StateChunkClass *  getClass( void ) const;

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

	// Diffuse Color
	
        SFColor4f   *getSFDiffuse( void );
          Color4f   &getDiffuse  ( void );
    const Color4f   &getDiffuse  ( void ) const;
	void             setDiffuse  ( const Color4f & color );

	// Ambient Color
	
        SFColor4f   *getSFAmbient( void );
          Color4f   &getAmbient  ( void );
    const Color4f   &getAmbient  ( void ) const;
	void             setAmbient  ( const Color4f & color );

	// Specular Color
	
        SFColor4f   *getSFSpecular( void );
          Color4f   &getSpecular  ( void );
    const Color4f   &getSpecular  ( void ) const;
	void             setSpecular  ( const Color4f & color );

	// Emission Color
	
        SFColor4f   *getSFEmission( void );
          Color4f   &getEmission  ( void );
    const Color4f   &getEmission  ( void ) const;
	void             setEmission  ( const Color4f & color );

	// Shininess
	
        SFReal32   *getSFShininess( void );
          Real32    getShininess  ( void );
          Real32    getShininess  ( void ) const;
	void            setShininess  ( const Real32 shininess );

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
	
	SFColor4f _diffuse;
	SFColor4f _ambient;
	SFColor4f _specular;
	SFColor4f _emission;
	SFReal32  _shininess;
	
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// prohibit default functions (move to 'public' if you need one)

    MaterialChunk(void);
    MaterialChunk(const MaterialChunk &source);    
    virtual ~MaterialChunk(void); 

	MaterialChunk & operator =(const MaterialChunk &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef MaterialChunk *MaterialChunkP;

OSG_END_NAMESPACE

#include "OSGMaterialChunk.inl"

#endif /* _OSGMATERIALCHUNK_H_ */
