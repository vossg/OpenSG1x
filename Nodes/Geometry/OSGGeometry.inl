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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------


#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include "OSGGeometry.h"

/** \fn const char *OSGSimpleAttachment::getClassname(void)
 *  \brief Classname
 */

/** \typedef OSGSimpleAttachment::Inherited
 *  \brief Parent type
 */

/** \typedef OSGSimpleAttachment::_field
 *  \brief Data store
 */

OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

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

OSG_FIELD_CONTAINER_INL_DEF(OSGGeometry, OSGGeometryPtr)

/*------------- constructors & destructors --------------------------------*/

/*--------------------------- type information-----------------------------*/

/*------------------------------ access -----------------------------------*/

inline
OSGGeoPTypePtr		OSGGeometry::getTypes( void )
{
    return _types.getValue();
}

inline
void				OSGGeometry::setTypes( OSGGeoPTypePtr types )
{
    _types.setValue( types );
}

inline
OSGGeoPLengthPtr	OSGGeometry::getLengths( void )
{
    return _lengths.getValue();
}

inline
void				OSGGeometry::setLengths( OSGGeoPLengthPtr lengths )
{
    _lengths.setValue( lengths );
}
	
inline
OSGGeoPositionPtr	OSGGeometry::getPositions( void )
{
    return _positions.getValue();
}

inline
void				OSGGeometry::setPositions( OSGGeoPositionPtr pos )
{
    _positions.setValue( pos );
}
		
inline
OSGGeoNormalPtr		OSGGeometry::getNormals( void )
{
    return _normals.getValue();
}

inline
void				OSGGeometry::setNormals( OSGGeoNormalPtr normals )
{
    _normals.setValue( normals );
}

inline
OSGBool				OSGGeometry::getNormalPerVertex( void )
{
    return _normalsPerVertex.getValue();
}

inline
void				OSGGeometry::setNormalPerVertex( OSGBool npv )
{
    _normalsPerVertex.setValue( npv );
}
		
inline
OSGGeoColorPtr		OSGGeometry::getColors( void )
{
    return _colors.getValue();
}

inline
void				OSGGeometry::setColors( OSGGeoColorPtr colors )
{
    _colors.setValue( colors );
}

inline
OSGBool				OSGGeometry::getColorPerVertex( void )
{
    return _colorsPerVertex.getValue();
}

inline
void				OSGGeometry::setColorPerVertex( OSGBool npv )
{
    _colorsPerVertex.setValue( npv );
}
		
inline
OSGGeoIndexPtr		OSGGeometry::getIndex( void )
{
    return _index.getValue();
}

inline
void				OSGGeometry::setIndex( OSGGeoIndexPtr index )
{
    _index.setValue( index );
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

OSG_END_NAMESPACE

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

