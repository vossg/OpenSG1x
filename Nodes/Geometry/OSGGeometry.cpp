/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------


#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"
#include "OSGLog.h"

#include <GL/gl.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#define OSG_COMPILEGEOMETRY

#include <OSGGeometryBase.h>
#include <OSGFieldContainer.h>
#include <OSGFieldContainerPtr.h>
#include <OSGAction.h>
#include <OSGDrawAction.h>

#include <OSGNode.h>

#include "OSGGeometry.h"
#include "OSGGeoPumpFactory.h"

#include "OSGPrimitiveIterator.h"
#include "OSGTriangleIterator.h"
#include "OSGFaceIterator.h"

#include "OSGGeoPropPtrs.h"

OSG_USING_NAMESPACE

/** \enum VecBase::VectorSizeE
 *  \brief 
 */

/** \var VecBase::VectorSizeE VecBase::_iSize
 * 
 */

/** \fn const char *VecBase::getClassname(void)
 *  \brief Classname
 */

/** \var ValueTypeT VecBase::_values[iSize];
 *  \brief Value store
 */

OSG_GEOMETRY_DLLMAPPING GeometryPtr OSG::NullGeo;

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

OSG_FC_FIRST_FIELD_IDM_DEF(Geometry, TypesField)

OSG_FC_FIELD_IDM_DEF      (Geometry, 
                           LengthsField, 
                           TypesField)

OSG_FC_FIELD_IDM_DEF      (Geometry, 
                           PositionsField, 
                           LengthsField)

OSG_FC_FIELD_IDM_DEF      (Geometry, 
                           NormalsField, 
                           PositionsField)

OSG_FC_FIELD_IDM_DEF      (Geometry, 
                           NormalPerVertexField, 
                           NormalsField)

OSG_FC_FIELD_IDM_DEF      (Geometry, 
                           ColorsField, 
                           NormalPerVertexField)

OSG_FC_FIELD_IDM_DEF      (Geometry, 
                           ColorPerVertexField, 
                           ColorsField)

OSG_FC_FIELD_IDM_DEF      (Geometry, 
                           GeoIndexField, 
                           ColorPerVertexField)

OSG_FC_FIELD_IDM_DEF      (Geometry, 
						   MaterialField,
                           GeoIndexField)

OSG_FC_LAST_FIELD_IDM_DEF (Geometry, 
                           MaterialField)

char Geometry::cvsid[] = "@(#)$Id: $";
FieldDescription Geometry::_desc[] = 
{
	FieldDescription(
        SFGeoPTypePtr::getClassType(),
        "types", 
        OSG_FC_FIELD_IDM_DESC(TypesField),
        false,
        (FieldAccessMethod) &Geometry::getSFTypes), 

	FieldDescription(
        SFGeoPLengthPtr::getClassType(),
        "lengths", 
        OSG_FC_FIELD_IDM_DESC(LengthsField),
        false,
        (FieldAccessMethod) &Geometry::getSFLengths), 
    
	FieldDescription(
        SFGeoPositionPtr::getClassType(),
        "positions", 
        OSG_FC_FIELD_IDM_DESC(PositionsField),
        false,
        (FieldAccessMethod) &Geometry::getSFPositions), 
    

	FieldDescription(
        SFGeoNormalPtr::getClassType(),
        "normals", 
        OSG_FC_FIELD_IDM_DESC(NormalsField),
        false,
        (FieldAccessMethod) &Geometry::getSFNormals), 

	FieldDescription(
        SFBool::getClassType(),
        "normalPerVertex", 
        OSG_FC_FIELD_IDM_DESC(NormalPerVertexField),
        false,
        (FieldAccessMethod) &Geometry::getSFNormalPerVertex), 
    

	FieldDescription(
        SFGeoColorPtr::getClassType(),
        "colors", 
        OSG_FC_FIELD_IDM_DESC(ColorsField),
        false,
        (FieldAccessMethod) &Geometry::getSFColors), 

	FieldDescription(
        SFBool::getClassType(),
        "colorPerVertex", 
        OSG_FC_FIELD_IDM_DESC(ColorPerVertexField),
        false,
        (FieldAccessMethod) &Geometry::getSFColorPerVertex), 


	FieldDescription(
        SFGeoIndexPtr::getClassType(),
        "index", 
        OSG_FC_FIELD_IDM_DESC(GeoIndexField),
        false,
        (FieldAccessMethod) &Geometry::getSFIndex), 


	FieldDescription(
        SFMaterialPtr::getClassType(),
        "material", 
        OSG_FC_FIELD_IDM_DESC(MaterialField),
        false,
        (FieldAccessMethod) &Geometry::getSFMaterial), 
};

FieldContainerType Geometry::_type(
    "Geometry",
    "NodeCore",
    NULL,
    (PrototypeCreateF) &Geometry::createEmpty,
    initMethod,
    _desc,
    sizeof(_desc));


/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

const char *Geometry::mapType( UInt8 type )
{
	switch ( type )
	{
	case GL_POINTS: 		return "Points";
	case GL_LINES: 			return "Lines";
	case GL_LINE_LOOP: 		return "LineLoop";
	case GL_LINE_STRIP: 	return "LineStrip";
	case GL_TRIANGLES: 		return "Triangles";
	case GL_TRIANGLE_STRIP: return "TriangleStrip";
	case GL_TRIANGLE_FAN: 	return "TriangleFan";
	case GL_QUADS: 			return "Quads";
	case GL_QUAD_STRIP:  	return "QuadStrip";
	case GL_POLYGON: 		return "Polygon";
	}
	
	return "Unknown Primitive";
}
	
/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/** \brief initialize the static features of the class, e.g. action callbacks
 */

void Geometry::initMethod (void)
{
	DrawAction::registerEnterDefault( getStaticType(), 
		osgMethodFunctor2BaseCPtr<OSG::Action::ResultE,
								CNodePtr,  
								GeometryPtr, 
								Action *>(&Geometry::doDraw));
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

OSG_FIELD_CONTAINER_DEF(Geometry, GeometryPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

Geometry::Geometry(void) :
	Inherited(),
    _types(), _lengths(), _positions(), _normals(), _colors(),
	_normalsPerVertex(), _colorsPerVertex(), _index(), _material()
{
}

Geometry::Geometry(const Geometry &source) :
    Inherited(source),
    _types(source._types), _lengths(source._lengths), 
	_positions(source._positions), _normals(source._normals), 
	_colors(source._colors),
	_normalsPerVertex(source._normalsPerVertex), 
	_colorsPerVertex(source._colorsPerVertex), _index(source._index),
	_material(source._material)
{
}

/** \brief Destructor
 */

Geometry::~Geometry(void)
{
}

/*------------------------------ access -----------------------------------*/

void Geometry::adjustVolume( Volume & volume )
{
	if ( getPositions()->getTypeId() != GeoPosition3f::getStaticTypeId() )
	{
		SWARNING << "adjustVolume: only supporting 3f positions right now!" << endl;
		return;
	}	

    GeoPosition3fPtr pos;

#ifdef 	OSG_HAS_MEMBER_TEMPLATE_RETURNVALUES
    pos = getPositions().dcast<GeoPosition3fPtr>();
#else
    getPositions().dcast(pos);
#endif

	if ( pos == NullFC )
		return;				// Node has no points, no volume
	
	MFPnt3f *p = pos->getFieldPtr();
	
	volume.setValid();
	
	for ( MFPnt3f::iterator it = p->begin(); it != p->end(); it++ )
	{
		volume.extendBy( *it );
	}
}

/*---------------------------- pointer ------------------------------------*/

GeometryPtr Geometry::getPtr(void) const
{
    GeometryPtr returnValue(*this);

    return returnValue;
}

/*---------------------------- properties ---------------------------------*/

SFGeoPTypePtr		*Geometry::getSFTypes( void )
{
	return &_types;
}

SFGeoPLengthPtr		*Geometry::getSFLengths( void )
{
	return &_lengths;
}

SFGeoPositionPtr		*Geometry::getSFPositions( void )
{
	return &_positions;
}

SFGeoColorPtr		*Geometry::getSFColors( void )
{
	return &_colors;
}

SFBool				*Geometry::getSFColorPerVertex( void )
{
	return &_colorsPerVertex;
}

SFGeoNormalPtr		*Geometry::getSFNormals( void )
{
	return &_normals;
}

SFBool				*Geometry::getSFNormalPerVertex( void )
{
	return &_normalsPerVertex;
}

SFGeoIndexPtr		*Geometry::getSFIndex( void )
{
	return &_index;
}

SFMaterialPtr		*Geometry::getSFMaterial( void )
{
	return &_material;
}

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */
#if 0
Geometry& Geometry::operator = (const Geometry &source)
{
	if (this == &source)
		return *this;

	// copy parts inherited from parent
	*(static_cast<Inherited *>(this)) = source;

	// free mem alloced by members of 'this'

	// alloc new mem for members

	// copy 
}
#endif


/*-------------------------- comparison -----------------------------------*/

/** \brief assignment
 */
#if 0
Bool CLASSNAME::operator < (const CLASSNAME &other) const
{
    return this < &other;
}

/** \brief equal
 */

Bool CLASSNAME::operator == (const CLASSNAME &other) const
{
}

/** \brief unequal
 */

Bool CLASSNAME::operator != (const CLASSNAME &other) const
{
	return ! (*this == other);
}
#endif

/*------------------------------- dump ----------------------------------*/

void Geometry::dump(void) const
{
    SDEBUG << "Dump Geometry NI" << endl;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/** \brief Actions
 */
	
Action::ResultE Geometry::doDraw(Action * action )
{
	if ( getMaterial() != NullFC )
		getMaterial()->draw( this, action );
	else
		draw( action );
	return Action::Continue;
}
	
Action::ResultE Geometry::draw(Action * action )
{
	// find the pump
	DrawAction *a = dynamic_cast<DrawAction*>(action);

	GeoPumpFactory::Index ind = GeoPumpFactory::the().getIndex( this );
	GeoPumpFactory::Pump p = GeoPumpFactory::the().getPump( a, ind );

	// call the pump

	if ( p )
		p( a, this );
	else
	{
		SWARNING << "draw: no Pump found for geometry " << this << endl;
	}
	
	return Action::Continue;
}

void Geometry::changed(BitVector whichField, ChangeMode from)
{
    UInt32 i;

    if(whichField & PositionsFieldMask)
    {
        for(i = 0; i < _parents.size(); i++)
        {
            _parents[i]->invalidateVolume();
        }            
    }
}

    
/** Triangle iterator functions */
    

TriangleIterator Geometry::beginTriangles( void ) const
{
	TriangleIterator it( this->getPtr() );

	it.setToBegin();
	
	return it;
}


TriangleIterator Geometry::endTriangles  ( void ) const
{
	TriangleIterator it( this->getPtr() );

	it.setToEnd();
	
	return it;
}
    
/** Primitive iterator functions */
    

PrimitiveIterator Geometry::beginPrimitives( void ) const
{
	PrimitiveIterator it( this->getPtr() );

	it.setToBegin();
	
	return it;
}


PrimitiveIterator Geometry::endPrimitives  ( void ) const
{
	PrimitiveIterator it( this->getPtr() );

	it.setToEnd();
	
	return it;
}
    
/** Face iterator functions */
    

FaceIterator Geometry::beginFaces( void ) const
{
	FaceIterator it( this->getPtr() );

	it.setToBegin();
	
	return it;
}


FaceIterator Geometry::endFaces  ( void ) const
{
	FaceIterator it( this->getPtr() );

	it.setToEnd();
	
	return it;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/



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

