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


#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include "OSGGeometry.h"


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

OSG_FIELD_CONTAINER_INL_DEF(Geometry, GeometryPtr)

/*------------- constructors & destructors --------------------------------*/

/*--------------------------- type information-----------------------------*/

/*------------------------------ access -----------------------------------*/

inline
GeoPTypePtr		Geometry::getTypes( void ) const
{
    return _types.getValue();
}

inline
void				Geometry::setTypes( GeoPTypePtr types )
{
    _types.setValue( types );
}

inline
GeoPLengthPtr	Geometry::getLengths( void ) const
{
    return _lengths.getValue();
}

inline
void				Geometry::setLengths( GeoPLengthPtr lengths )
{
    _lengths.setValue( lengths );
}
	
inline
GeoPositionPtr	Geometry::getPositions( void ) const
{
    return _positions.getValue();
}

inline
void				Geometry::setPositions( GeoPositionPtr pos )
{
    _positions.setValue( pos );
}
		
inline
GeoNormalPtr		Geometry::getNormals( void ) const
{
    return _normals.getValue();
}

inline
void				Geometry::setNormals( GeoNormalPtr normals )
{
    _normals.setValue( normals );
}

inline
Bool				Geometry::getNormalPerVertex( void ) const
{
    return _normalsPerVertex.getValue();
}

inline
void				Geometry::setNormalPerVertex( Bool npv )
{
    _normalsPerVertex.setValue( npv );
}
		
inline
GeoColorPtr			Geometry::getColors( void ) const
{
    return _colors.getValue();
}

inline
void				Geometry::setColors( GeoColorPtr colors )
{
    _colors.setValue( colors );
}

inline
Bool				Geometry::getColorPerVertex( void ) const
{
    return _colorsPerVertex.getValue();
}

inline
void				Geometry::setColorPerVertex( Bool npv )
{
    _colorsPerVertex.setValue( npv );
}
		
inline
GeoTexCoordsPtr		Geometry::getTexCoords( void ) const
{
    return _texcoords.getValue();
}

inline
void				Geometry::setTexCoords( GeoTexCoordsPtr texcoords )
{
    _texcoords.setValue( texcoords );
}
		
inline
GeoIndexPtr			Geometry::getIndex( void ) const
{
    return _index.getValue();
}

inline
void				Geometry::setIndex( GeoIndexPtr index )
{
    _index.setValue( index );
}
		
inline
MaterialPtr		Geometry::getMaterial( void ) const
{
    return _material.getValue();
}

inline
void				Geometry::setMaterial( MaterialPtr material )
{
    _material.setValue( material );
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

