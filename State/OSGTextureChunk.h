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

#ifndef _OSGTEXTURECHUNK_H_
#define _OSGTEXTURECHUNK_H_
#ifdef __sgi
#pragma once
#endif

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <vector>

#include "OSGFieldContainerPtr.h"
#include "OSGSFMathTypes.h"
#include "OSGSFSysTypes.h"
#include "OSGSFImageTypes.h"
#include "OSGSFBaseTypes.h"
#include "OSGImage.h"
#include "OSGWindow.h"
#include "OSGStateChunk.h"

OSG_BEGIN_NAMESPACE

//---------------------------------------------------------------------------
//  Forward References
//---------------------------------------------------------------------------

class TextureChunk;

//---------------------------------------------------------------------------
//   Types
//---------------------------------------------------------------------------

typedef FCPtr<StateChunkPtr, TextureChunk> TextureChunkPtr;

//---------------------------------------------------------------------------
//  Class
//---------------------------------------------------------------------------

/*! \ingroup baselib
 *  \brief Brief
 *
 *  detailed
 */

class OSG_STATE_DLLMAPPING TextureChunk : public StateChunk
{
  private:

	typedef StateChunk Inherited;

  public:

    //-----------------------------------------------------------------------
    //   constants                                                           
    //-----------------------------------------------------------------------
    
    OSG_FC_FIRST_FIELD_IDM_DECL(ImageField)
    OSG_FC_FIELD_IDM_DECL      (MinFilterField, 	ImageField )  
    OSG_FC_FIELD_IDM_DECL      (MagFilterField, 	MinFilterField )  
    OSG_FC_FIELD_IDM_DECL      (WrapSField, 		MagFilterField )  
    OSG_FC_FIELD_IDM_DECL      (WrapTField, 		WrapSField )  
    OSG_FC_FIELD_IDM_DECL      (WrapRField, 		WrapTField )  
    OSG_FC_FIELD_IDM_DECL      (EnvModeField, 		WrapRField )  
    OSG_FC_FIELD_IDM_DECL      (GenFuncSField, 		EnvModeField )  
    OSG_FC_FIELD_IDM_DECL      (GenFuncTField,  	GenFuncSField )  
    OSG_FC_FIELD_IDM_DECL      (GenFuncRField, 		GenFuncTField )  
    OSG_FC_FIELD_IDM_DECL      (GenFuncQField, 		GenFuncRField )  
    OSG_FC_FIELD_IDM_DECL      (GenFuncSPlaneField, GenFuncQField )  
    OSG_FC_FIELD_IDM_DECL      (GenFuncTPlaneField, GenFuncSPlaneField )  
    OSG_FC_FIELD_IDM_DECL      (GenFuncRPlaneField, GenFuncTPlaneField )  
    OSG_FC_FIELD_IDM_DECL      (GenFuncQPlaneField, GenFuncRPlaneField )  
    OSG_FC_FIELD_IDM_DECL      (GLIdField, 			GenFuncQPlaneField )  
    OSG_FC_LAST_FIELD_IDM_DECL (GLIdField)

    //-----------------------------------------------------------------------
    //   enums                                                               
    //-----------------------------------------------------------------------

    //-----------------------------------------------------------------------
    //   types                                                               
    //-----------------------------------------------------------------------

    typedef TextureChunkPtr Ptr;

    //-----------------------------------------------------------------------
    //   class functions                                                     
    //-----------------------------------------------------------------------

    static const char *getClassname(void) { return "TextureChunk"; }
 
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

    /*-------------- general fieldcontainer declaration --------------------*/

    OSG_FIELD_CONTAINER_DECL(TextureChunkPtr)

	virtual const StateChunkClass *  getClass( void ) const;

    /*----------------------------- dump ----------------------------------*/

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector &bvFlags  = 0) const;

    /*------------------------- your_category -------------------------------*/

	// call the OpenGL commands to set my part of the state 
	virtual void activate ( DrawAction * action, UInt32 index = 0 );

	// call commands to get from old to my state. Only meaningful for
	// chunks of the same type
	virtual void changeFrom( DrawAction * action, StateChunk * old, UInt32 index = 0 );

	// reset my part of the state
	virtual void deactivate ( DrawAction * action, UInt32 index = 0 );

    /*----------------------------- access ----------------------------------*/

	OSG_SFIELD_ACCESS_FUNCTIONS_DECL( SFImageP, ImageP, Image )
	OSG_SFIELD_ACCESS_FUNCTIONS_DECL( SFUInt32, UInt32, MinFilter )
	OSG_SFIELD_ACCESS_FUNCTIONS_DECL( SFUInt32, UInt32, MagFilter )
	OSG_SFIELD_ACCESS_FUNCTIONS_DECL( SFUInt32, UInt32, WrapS )
	OSG_SFIELD_ACCESS_FUNCTIONS_DECL( SFUInt32, UInt32, WrapT )
	OSG_SFIELD_ACCESS_FUNCTIONS_DECL( SFUInt32, UInt32, WrapR )
	OSG_SFIELD_ACCESS_FUNCTIONS_DECL( SFUInt32, UInt32, EnvMode )
	OSG_SFIELD_ACCESS_FUNCTIONS_DECL( SFUInt32, UInt32, GenFuncS )
	OSG_SFIELD_ACCESS_FUNCTIONS_DECL( SFUInt32, UInt32, GenFuncT )
	OSG_SFIELD_ACCESS_FUNCTIONS_DECL( SFUInt32, UInt32, GenFuncR )
	OSG_SFIELD_ACCESS_FUNCTIONS_DECL( SFUInt32, UInt32, GenFuncQ )
	OSG_SFIELD_ACCESS_FUNCTIONS_DECL( SFPlane,  Plane,  GenFuncSPlane )
	OSG_SFIELD_ACCESS_FUNCTIONS_DECL( SFPlane,  Plane,  GenFuncTPlane )
	OSG_SFIELD_ACCESS_FUNCTIONS_DECL( SFPlane,  Plane,  GenFuncRPlane )
	OSG_SFIELD_ACCESS_FUNCTIONS_DECL( SFPlane,  Plane,  GenFuncQPlane )

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

	OSG_SFIELD_ACCESS_FUNCTIONS_DECL( SFUInt32, UInt32, GLId )

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

	SFImageP _Image;
	SFUInt32 _MinFilter;
	SFUInt32 _MagFilter;
	SFUInt32 _WrapS;
	SFUInt32 _WrapT;
	SFUInt32 _WrapR;
	SFUInt32 _EnvMode;
	SFUInt32 _GenFuncS;
	SFUInt32 _GenFuncT;
	SFUInt32 _GenFuncR;
	SFUInt32 _GenFuncQ;
	SFPlane  _GenFuncSPlane;
	SFPlane  _GenFuncTPlane;
	SFPlane  _GenFuncRPlane;
	SFPlane  _GenFuncQPlane;

	// the texture object id of the texture
	SFUInt32 _GLId;
	
    //-----------------------------------------------------------------------
    //   instance functions                                                  
    //-----------------------------------------------------------------------

	// handle the GL stuff: creation, activatiom, deletion
	void handleGL( Window::GLObjectFlagE mode, UInt32 id );

	// prohibit default functions (move to 'public' if you need one)

    TextureChunk(void);
    TextureChunk(const TextureChunk &source);    
    virtual ~TextureChunk(void); 

	TextureChunk & operator =(const TextureChunk &source);
};

//---------------------------------------------------------------------------
//   Exported Types
//---------------------------------------------------------------------------

// class pointer

typedef TextureChunk *TextureChunkP;

OSG_END_NAMESPACE

#include "OSGTextureChunk.inl"

#endif /* _OSGTEXTURECHUNK_H_ */
