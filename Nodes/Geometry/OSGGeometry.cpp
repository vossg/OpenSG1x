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

#include <OSGFieldContainer.h>
#include <OSGFieldContainerPtr.h>
#include <OSGAction.h>
#include <OSGDrawAction.h>

#include <OSGNode.h>

#include "OSGGeometry.h"
#include "OSGGeoPumpFactory.h"

OSG_USING_NAMESPACE

/** \enum OSGVecBase::VectorSizeE
 *  \brief 
 */

/** \var OSGVecBase::VectorSizeE OSGVecBase::_iSize
 * 
 */

/** \fn const char *OSGVecBase::getClassname(void)
 *  \brief Classname
 */

/** \var OSGValueTypeT OSGVecBase::_values[iSize];
 *  \brief Value store
 */

OSGGeometryPtr OSG::OSGNullGeo;

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

OSG_FC_FIRST_FIELD_IDM_DEF(OSGGeometry, OSGTypesField)

OSG_FC_FIELD_IDM_DEF      (OSGGeometry, 
                           OSGLengthsField, 
                           OSGTypesField)

OSG_FC_FIELD_IDM_DEF      (OSGGeometry, 
                           OSGPositionsField, 
                           OSGLengthsField)

OSG_FC_FIELD_IDM_DEF      (OSGGeometry, 
                           OSGNormalsField, 
                           OSGPositionsField)

OSG_FC_FIELD_IDM_DEF      (OSGGeometry, 
                           OSGNormalPerVertexField, 
                           OSGNormalsField)

OSG_FC_FIELD_IDM_DEF      (OSGGeometry, 
                           OSGColorsField, 
                           OSGNormalPerVertexField)

OSG_FC_FIELD_IDM_DEF      (OSGGeometry, 
                           OSGColorPerVertexField, 
                           OSGColorsField)

OSG_FC_FIELD_IDM_DEF      (OSGGeometry, 
                           OSGGeoIndexField, 
                           OSGColorPerVertexField)

OSG_FC_LAST_FIELD_IDM_DEF (OSGGeometry, 
                           OSGGeoIndexField)

char OSGGeometry::cvsid[] = "@(#)$Id: $";

OSGFieldDescription OSGGeometry::_desc[] = 
{
	OSGFieldDescription(
        OSGSFGeoPTypePtr::getClassType(),
        "types", 
        OSG_FC_FIELD_IDM_DESC(OSGTypesField),
        false,
        (OSGFieldAccessMethod) &OSGGeometry::getSFTypes), 

	OSGFieldDescription(
        OSGSFGeoPLengthPtr::getClassType(),
        "lengths", 
        OSG_FC_FIELD_IDM_DESC(OSGLengthsField),
        false,
        (OSGFieldAccessMethod) &OSGGeometry::getSFLengths), 
    
	OSGFieldDescription(
        OSGSFGeoPositionPtr::getClassType(),
        "positions", 
        OSG_FC_FIELD_IDM_DESC(OSGPositionsField),
        false,
        (OSGFieldAccessMethod) &OSGGeometry::getSFPositions), 
    

	OSGFieldDescription(
        OSGSFGeoNormalPtr::getClassType(),
        "normals", 
        OSG_FC_FIELD_IDM_DESC(OSGNormalsField),
        false,
        (OSGFieldAccessMethod) &OSGGeometry::getSFNormals), 

	OSGFieldDescription(
        OSGSFBool::getClassType(),
        "normalPerVertex", 
        OSG_FC_FIELD_IDM_DESC(OSGNormalPerVertexField),
        false,
        (OSGFieldAccessMethod) &OSGGeometry::getSFNormalPerVertex), 
    

	OSGFieldDescription(
        OSGSFGeoColorPtr::getClassType(),
        "colors", 
        OSG_FC_FIELD_IDM_DESC(OSGColorsField),
        false,
        (OSGFieldAccessMethod) &OSGGeometry::getSFColors), 

	OSGFieldDescription(
        OSGSFBool::getClassType(),
        "colorPerVertex", 
        OSG_FC_FIELD_IDM_DESC(OSGColorPerVertexField),
        false,
        (OSGFieldAccessMethod) &OSGGeometry::getSFColorPerVertex), 


	OSGFieldDescription(
        OSGSFGeoIndexPtr::getClassType(),
        "index", 
        OSG_FC_FIELD_IDM_DESC(OSGGeoIndexField),
        false,
        (OSGFieldAccessMethod) &OSGGeometry::getSFIndex), 
};

OSGFieldContainerType OSGGeometry::_type(
    "Geometry",
    "NodeCore",
    NULL,
    (OSGPrototypeCreateF) &OSGGeometry::createEmpty,
    initMethod,
    _desc,
    sizeof(_desc));


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

/** \brief initialize the static features of the class, e.g. action callbacks
 */

void OSGGeometry::initMethod (void)
{
	OSGDrawAction::registerEnterDefault( getStaticType(), 
		osgMethodFunctor2BaseCPtr<OSG::OSGAction::ResultE,
								OSGCNodePtr,  
								OSGGeometryPtr, 
								OSGAction *>(&OSGGeometry::draw));
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

OSG_FIELD_CONTAINER_DEF(OSGGeometry, OSGGeometryPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

OSGGeometry::OSGGeometry(void) :
	Inherited(),
    _types(), _lengths(), _positions(), _normals(), _colors(),
	_normalsPerVertex(), _colorsPerVertex(), _index()
{
}

OSGGeometry::OSGGeometry(const OSGGeometry &source) :
    Inherited(source),
    _types(source._types), _lengths(source._lengths), 
	_positions(source._positions), _normals(source._normals), 
	_colors(source._colors),
	_normalsPerVertex(source._normalsPerVertex), 
	_colorsPerVertex(source._colorsPerVertex), _index(source._index)
{
}

/** \brief Destructor
 */

OSGGeometry::~OSGGeometry(void)
{
}

/*------------------------------ access -----------------------------------*/

void OSGGeometry::adjustVolume( OSGVolume & volume )
{
	if ( getPositions()->getTypeId() != OSGGeoPosition3f::getStaticTypeId() )
	{
		SWARNING << "adjustVolume: only supporting 3f positions right now!" << endl;
		return;
	}	

    OSGGeoPosition3fPtr pos;

#ifdef 	OSG_HAS_MEMBER_TEMPLATE_RETURNVALUES
    pos = getPositions().dcast<OSGGeoPosition3fPtr>();
#else
    getPositions().dcast(pos);
#endif

	if ( pos == OSGNullFC )
		return;				// Node has no points, no volume
	
	OSGMFPnt3f *p = pos->getFieldPtr();
	
	volume.setValid();
	
	for ( OSGMFPnt3f::iterator it = p->begin(); it != p->end(); it++ )
	{
		volume.extendBy( *it );
	}
}

/*---------------------------- pointer ------------------------------------*/

OSGGeometryPtr OSGGeometry::getPtr(void)
{
    OSGGeometryPtr returnValue(*this);

    return returnValue;
}

/*---------------------------- properties ---------------------------------*/

OSGSFGeoPTypePtr		*OSGGeometry::getSFTypes( void )
{
	return &_types;
}

OSGSFGeoPLengthPtr		*OSGGeometry::getSFLengths( void )
{
	return &_lengths;
}

OSGSFGeoPositionPtr		*OSGGeometry::getSFPositions( void )
{
	return &_positions;
}

OSGSFGeoColorPtr		*OSGGeometry::getSFColors( void )
{
	return &_colors;
}

OSGSFBool				*OSGGeometry::getSFColorPerVertex( void )
{
	return &_colorsPerVertex;
}

OSGSFGeoNormalPtr		*OSGGeometry::getSFNormals( void )
{
	return &_normals;
}

OSGSFBool				*OSGGeometry::getSFNormalPerVertex( void )
{
	return &_normalsPerVertex;
}

OSGSFGeoIndexPtr		*OSGGeometry::getSFIndex( void )
{
	return &_index;
}

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */
#if 0
OSGGeometry& OSGGeometry::operator = (const OSGGeometry &source)
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
OSGBool CLASSNAME::operator < (const CLASSNAME &other) const
{
    return this < &other;
}

/** \brief equal
 */

OSGBool CLASSNAME::operator == (const CLASSNAME &other) const
{
}

/** \brief unequal
 */

OSGBool CLASSNAME::operator != (const CLASSNAME &other) const
{
	return ! (*this == other);
}
#endif

/*------------------------------- dump ----------------------------------*/

void OSGGeometry::dump(void) const
{
    SDEBUG << "Dump OSGGeometry NI" << endl;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/** \brief Actions
 */
	
OSGAction::ResultE OSGGeometry::draw(OSGAction * action )
{
	// find the pump
	OSGDrawAction *a = dynamic_cast<OSGDrawAction*>(action);

	OSGGeoPumpFactory::Index ind = OSGGeoPumpFactory::the().getIndex( this );
	OSGGeoPumpFactory::Pump p = OSGGeoPumpFactory::the().getPump( a, ind );

	// call the pump

	if ( p )
		p( a, this );
	else
	{
		SWARNING << "draw: no Pump found for geometry " << this << endl;
	}
	
	return OSGAction::Continue;
}

void OSGGeometry::changed(OSGBitVector whichField, OSGChangeMode from)
{
    OSGUInt32 i;

    if(whichField & OSGPositionsFieldMask)
    {
        for(i = 0; i < _parents.size(); i++)
        {
            _parents[i]->invalidateVolume();
        }            
    }
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

