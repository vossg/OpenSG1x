/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 *                                                                           *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#define OSG_COMPILESYSTEMLIB

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include <GL/gl.h>

#include "OSGLog.h"

#include "OSGFieldContainerPtr.h"
#include "OSGGeometry.h"
#include "OSGDrawAction.h"

#include "OSGMaterial.h"

#include "OSGGeoPumpFactory.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \defgroup PumpFactory
	\ingroup GeometryLib

The PumpFactory is responsible for selecting the most appropriate pump
function to send the geometry's data to OpenGL.

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char GeoPumpFactory::cvsid[] = "@(#)$Id: $";

GeoPumpFactory GeoPumpFactory::_the;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/



/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/



/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

GeoPumpFactory::GeoPumpFactory(void)
{
}

/** \brief Destructor
 */

GeoPumpFactory::~GeoPumpFactory(void)
{
}

/*------------------------------ access -----------------------------------*/


/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/


GeoPumpFactory::Index GeoPumpFactory::getIndex( Geometry * )
{
	return 0;
}
	

GeoPumpFactory::GeoPump GeoPumpFactory::getGeoPump( 
				Window * , 
				GeoPumpFactory::Index  )
{
	return &masterGeoPump;
}

GeoPumpFactory::PartialGeoPump GeoPumpFactory::getPartialGeoPump( 
				Window * , 
				GeoPumpFactory::Index  )
{
    	FWARNING(("GeoPumpFactory::getPartialGeoPump: not implemented yet!\n"));
	return NULL;
}

GeoPumpFactory::InterfacePump GeoPumpFactory::getInterfacePump( 
				Window * , 
				GeoPumpFactory::Index  )
{
    	FWARNING(("GeoPumpFactory::getInterfacePump: not implemented yet!\n"));
	return NULL;
}

GeoPumpFactory::PartialInterfacePump GeoPumpFactory::getPartialInterfacePump( 
				Window * , 
				GeoPumpFactory::Index  )
{
    	FWARNING(("GeoPumpFactory::getPartialInterfacePump: not "
	    	    "implemented yet!\n"));
	return NULL;
}


/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

	
GeoPumpFactory::Index GeoPumpFactory::numIndices( void )
{
	return 1;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

// The real pumping functions

typedef void (OSG_APIENTRY *pumpFunc)( GLubyte * data );

// Some helper arrays for function selection
// indexed by data type and dimension

static const int formatBase = GL_BYTE;
static const int numFormats = GL_DOUBLE - GL_BYTE + 1;

static char *formatNames[] = 
{	"GL_BYTE", "GL_UNSIGNED_BYTE", "GL_SHORT", "GL_UNSIGNED_SHORT", 
	"GL_INT", "GL_UNSIGNED_INT", "GL_FLOAT", "GL_2_BYTES", 
	"GL_3_BYTES", "GL_4_BYTES", "GL_DOUBLE"
};

static pumpFunc PositionFuncs[numFormats][4] = {
	{ NULL, NULL, NULL, NULL },							// GL_BYTE
	{ NULL, NULL, NULL, NULL },							// GL_UNSIGNED_BYTE
	{ NULL, (pumpFunc)glVertex2sv, 
	  (pumpFunc)glVertex3sv, (pumpFunc)glVertex4sv },	// GL_SHORT
	{ NULL, NULL, NULL, NULL },							// GL_UNSIGNED_SHORT
	{ NULL, (pumpFunc)glVertex2iv, 
	  (pumpFunc)glVertex3iv, (pumpFunc)glVertex4iv },	// GL_INT
	{ NULL, NULL, NULL, NULL },							// GL_UNSIGNED_INT
	{ NULL, (pumpFunc)glVertex2fv,
	  (pumpFunc)glVertex3fv, (pumpFunc)glVertex4fv }, 	// GL_FLOAT
	{ NULL, NULL, NULL, NULL },							// GL_2_BYTES
	{ NULL, NULL, NULL, NULL },							// GL_3_BYTES
	{ NULL, NULL, NULL, NULL },							// GL_4_BYTES
	{ NULL, (pumpFunc)glVertex2dv, 
	  (pumpFunc)glVertex3dv, (pumpFunc)glVertex4dv },	// GL_DOUBLE
};

static pumpFunc NormalFuncs[numFormats][4] = {
	{ NULL, NULL, (pumpFunc)glNormal3sv, NULL },		// GL_BYTE
	{ NULL, NULL, NULL, NULL },							// GL_UNSIGNED_BYTE
	{ NULL, NULL, (pumpFunc)glNormal3sv, NULL },		// GL_SHORT
	{ NULL, NULL, NULL, NULL },							// GL_UNSIGNED_SHORT
	{ NULL, NULL, (pumpFunc)glNormal3iv, NULL },		// GL_INT
	{ NULL, NULL, NULL, NULL },							// GL_UNSIGNED_INT
	{ NULL, NULL, (pumpFunc)glNormal3fv, NULL },		// GL_FLOAT
	{ NULL, NULL, NULL, NULL },							// GL_2_BYTES
	{ NULL, NULL, NULL, NULL },							// GL_3_BYTES
	{ NULL, NULL, NULL, NULL },							// GL_4_BYTES
	{ NULL, NULL, (pumpFunc)glNormal3dv, NULL },		// GL_DOUBLE
};

static pumpFunc ColorFuncs[numFormats][4] = {
	{ NULL, NULL, 
	  (pumpFunc)glColor3bv, (pumpFunc)glColor4bv },		// GL_BYTE
	{ NULL, NULL, 
	  (pumpFunc)glColor3ubv, (pumpFunc)glColor4ubv },	// GL_UNSIGNED_BYTE
	{ NULL, NULL, 
	  (pumpFunc)glColor3sv, (pumpFunc)glColor4sv },		// GL_SHORT
	{ NULL, NULL,  
	  (pumpFunc)glColor3usv, (pumpFunc)glColor4usv },	// GL_UNSIGNED_SHORT
	{ NULL, NULL,  
	  (pumpFunc)glColor3iv, (pumpFunc)glColor4iv },		// GL_INT
	{ NULL, NULL,  
	  (pumpFunc)glColor3uiv, (pumpFunc)glColor4uiv },	// GL_UNSIGNED_INT
	{ NULL, NULL,  
	  (pumpFunc)glColor3fv, (pumpFunc)glColor4fv },		// GL_FLOAT
	{ NULL, NULL, NULL, NULL },							// GL_2_BYTES
	{ NULL, NULL, NULL, NULL },							// GL_3_BYTES
	{ NULL, NULL, NULL, NULL },							// GL_4_BYTES
	{ NULL, NULL,  
	  (pumpFunc)glColor3dv, (pumpFunc)glColor4dv },		// GL_DOUBLE
};


static pumpFunc TexCoordsFuncs[numFormats][4] = {
	{ NULL, NULL, NULL, NULL },							 // GL_BYTE
	{ NULL, NULL, NULL, NULL },							 // GL_UNSIGNED_BYTE
	{ (pumpFunc)glTexCoord1sv, (pumpFunc)glTexCoord2sv, 
	  (pumpFunc)glTexCoord3sv, (pumpFunc)glTexCoord4sv },// GL_SHORT
	{ NULL, NULL, NULL, NULL },							 // GL_UNSIGNED_SHORT
	{ (pumpFunc)glTexCoord1iv, (pumpFunc)glTexCoord2iv, 
	  (pumpFunc)glTexCoord3iv, (pumpFunc)glTexCoord4iv },// GL_INT
	{ NULL, NULL, NULL, NULL },							 // GL_UNSIGNED_INT
	{ (pumpFunc)glTexCoord1fv, (pumpFunc)glTexCoord2fv, 
	  (pumpFunc)glTexCoord3fv, (pumpFunc)glTexCoord4fv },// GL_FLOAT
	{ NULL, NULL, NULL, NULL },							 // GL_2_BYTES
	{ NULL, NULL, NULL, NULL },							 // GL_3_BYTES
	{ NULL, NULL, NULL, NULL },							 // GL_4_BYTES
	{ (pumpFunc)glTexCoord1dv, (pumpFunc)glTexCoord2dv, 
	  (pumpFunc)glTexCoord3dv, (pumpFunc)glTexCoord4dv },// GL_DOUBLE
};


// TODO: Multitexture


// The master pump. Can render everything, but takes ages to do so.
// A real fallback, when everything else fails.
// Its second function is the example of how things are supposed to work.
// If an optimized pump creates a different result, it's wrong.
// The formal specification is defined in the design document though.

// some little helper macros to make the code more readable

// define and initialize the variables needed to access the data

#define pumpInternalSetup( name, typename, getmethod, mandatory )			\
	GLubyte * name##Data;													\
	UInt32 name##Stride;													\
	UInt32 name##Ind = 0;												\
	typename name##Ptr;														\
																			\
	name##Ptr = geo->getmethod();											\
	if ( mandatory && name##Ptr == NullFC )								\
	{																		\
		SWARNING << "masterPump: Geometry " << geo << " has no " 			\
				 << #name << "s!" << endl;									\
		return;																\
	}																		\
	else if ( name##Ptr != NullFC )										\
	{																		\
		name##Data = name##Ptr->getData();									\
		if ( ! ( name##Stride = name##Ptr->getStride() ) )					\
			name##Stride =	name##Ptr->getFormatSize() *					\
							name##Ptr->getDimension();						\
	}																		\
	else																	\
	{																		\
		name##Data = NULL;													\
		name##Stride = 0;													\
	}

#define pumpGLSetup( name, typename, getmethod )							\
	GLubyte * name##Data;													\
	UInt32 name##Stride;													\
	UInt32 name##Ind = 0;												\
	typename name##Ptr;														\
	pumpFunc name##Func;													\
																			\
	name##Ptr = geo->getmethod();											\
	if ( name##Ptr != NullFC )											\
	{																		\
		name##Data = name##Ptr->getData();									\
		if ( ! ( name##Stride = name##Ptr->getStride() ) )					\
			name##Stride = name##Ptr->getFormatSize() *						\
			name##Ptr->getDimension();										\
		if ( ! ( name##Func = name##Funcs[ name##Ptr->getFormat() -			\
											formatBase ]					\
										 [ name##Ptr->getDimension() - 1 ]	\
		   )   )															\
		{																	\
			SWARNING << "masterPump: Geometry " << geo << "has illegal " 	\
					 << #name << "s: " << name##Ptr->getDimension() 		\
					 << "D " << formatNames[ name##Ptr->getFormat() -		\
											formatBase ]					\
					 << "!" << endl;										\
			return;															\
		}																	\
	}																		\
	else																	\
	{																		\
		name##Data = NULL;													\
		name##Func = NULL;													\
		name##Stride = 0;													\
	}

// the master pump function

#ifdef __sgi
#pragma set woff 1174
#endif

void GeoPumpFactory::masterGeoPump( Window *win, Geometry * geo )
{
	// Setup: get all the data
	
	pumpInternalSetup( Type, GeoPTypesPtr, getTypes, true );
	pumpInternalSetup( Length, GeoPLengthsPtr, getLengths, true );
	pumpInternalSetup( Index, GeoIndicesPtr, getIndices, false );

	pumpGLSetup( Position, GeoPositionsPtr, getPositions );
	pumpGLSetup( Color, GeoColorsPtr, getColors );
	pumpGLSetup( Normal, GeoNormalsPtr, getNormals );
	pumpGLSetup( TexCoords, GeoTexCoordsPtr, getTexCoords );
	
	if ( ! PositionData )
	{
		SWARNING << "masterPump: Geometry " << geo << " has no positions!?!"
				 << endl;
		return;
	}
	
	// find the mapping indices
	UInt16 nmappings = geo->getIndexMapping().size();
	Int16 PositionIndex = -1, 
	      NormalIndex = -1, 
	      ColorIndex = -1, 
	      TexCoordsIndex = -1;

    	if ( nmappings )
	{
	    PositionIndex  = geo->calcMappingIndex( Geometry::MapPosition );
	    NormalIndex    = geo->calcMappingIndex( Geometry::MapNormal );
	    ColorIndex     = geo->calcMappingIndex( Geometry::MapColor );
	    TexCoordsIndex = geo->calcMappingIndex( Geometry::MapTexcoords );
	    
	    if ( ! PositionData )
	    {
		    SWARNING << "masterPump: Geometry " << geo << "has no position index!?!"
				     << endl;
		    return;
	    }
	    
	}
	else if ( IndexData )
	{
	    nmappings = 1;
	    PositionIndex = 
	    NormalIndex =
	    ColorIndex =
	    TexCoordsIndex = 0;
	}
	
	// overall color?
	if ( ColorData && ColorPtr->getSize() == 1 )
		ColorFunc( ColorData );

	UInt32 LengthSize = LengthPtr->getSize();

	for ( LengthInd = 0; LengthInd < LengthSize; LengthInd++ )
	{
		glBegin( *(TypeData + TypeInd++ * TypeStride) );
		
		for ( UInt32 l = *(UInt32*)(LengthData + LengthInd * LengthStride); 
					   l > 0; l-- )
		{
			if ( IndexData )
			{
				UInt32 * vind;
			
				vind = (UInt32*)(IndexData + IndexStride * IndexInd);
				IndexInd += nmappings;
				
				if ( ColorData && ColorIndex >= 0 )
				{
					ColorFunc( ColorData + ColorStride * vind[ColorIndex] );
				}		
				
				if ( NormalData && NormalIndex >= 0 )
				{
					NormalFunc( NormalData + NormalStride * vind[NormalIndex] );
				}		
				
				if ( TexCoordsData && TexCoordsIndex >= 0  )
				{
					TexCoordsFunc( TexCoordsData + TexCoordsStride * vind[TexCoordsIndex] );
				}		
					
				PositionFunc( PositionData + PositionStride * vind[PositionIndex] );
			}
			else
			{	
				if ( ColorData )
				{
					ColorFunc( ColorData + ColorStride * PositionInd );
				}		
				
				if ( NormalData )
				{
					NormalFunc( NormalData + NormalStride * PositionInd );
				}		
				
				if ( TexCoordsData  )
				{
					TexCoordsFunc( TexCoordsData + TexCoordsStride * 
													PositionInd );
				}		
					
				PositionFunc( PositionData + PositionStride * PositionInd );
				
				PositionInd++;
			}
		}
		
		glEnd();
	}

}

		
void GeoPumpFactory::masterPartialGeoPump( Window *win, Geometry * geo,
	    UInt32 primtype, UInt32 firstvert, UInt32 nvert )	
{
    	FWARNING(("GeoPumpFactory::masterPartialGeoPump: not implemented yet!\n"));
}
	
void GeoPumpFactory::masterInterfacePump( Window *win, 
	    GeoPositionsInterface *pos, GeoNormalsInterface *norm,
	    GeoColorsInterface *col, GeoTexCoordsInterface *texcoords,
	    GeoTexCoordsInterface *texcoords2,
	    GeoTexCoordsInterface *texcoords3,
	    GeoTexCoordsInterface *texcoords4,
	    GeoPTypesInterface *type, GeoPLengthsInterface*len,
	    GeoIndicesInterface *ind, UInt16 *pMap, UInt16 nmap )
{
    	FWARNING(("GeoPumpFactory::masterInterfacePump: not implemented yet!\n"));
}
	
void GeoPumpFactory::masterPartialInterfacePump( Window *win, 
	    GeoPositionsInterface *pos, GeoNormalsInterface *norm,
	    GeoColorsInterface *col, GeoTexCoordsInterface *texcoords,
	    GeoTexCoordsInterface *texcoords2,
	    GeoTexCoordsInterface *texcoords3,
	    GeoTexCoordsInterface *texcoords4,
	    GeoPTypesInterface *type, GeoPLengthsInterface*len,
	    GeoIndicesInterface *ind, UInt16 *pMap, UInt16 nmap,
	    UInt32 primtype, UInt32 firstvert, UInt32 nvert )
{
    	FWARNING(("GeoPumpFactory::masterPartialInterfacePump: not implemented yet!\n"));
}

#ifdef __sgi
#pragma reset woff 1174
#endif

///---------------------------------------------------------------------------
///  FUNCTION: 
///---------------------------------------------------------------------------
//:  Example for the head comment of a function
///---------------------------------------------------------------------------
///
//p: Paramaters: 
//p: 
///
//g: GlobalVars:
//g: 
///
//r: Return:
//r: 
///
//c: Caution:
//c: 
///
//a: Assumptions:
//a: 
///
//d: Description:
//d: 
///
//s: SeeAlso:
//s: 
///---------------------------------------------------------------------------

