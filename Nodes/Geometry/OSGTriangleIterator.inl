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

/*------------- constructors & destructors --------------------------------*/

/*--------------------------- type information-----------------------------*/

/*------------------------------ access -----------------------------------*/


inline		 
Int32 TriangleIterator::getIndex( void) const
{
	return _triIndex;
}

inline		 
UInt8 TriangleIterator::getType( void ) const
{
	return _primIt.getType();
}

inline		 
Int32 TriangleIterator::getPositionIndex( Int32 which ) const
{
	return _primIt.getPositionIndex( _triPntIndex[which] );
}

inline		 
Pnt3f TriangleIterator::getPosition( Int32 which ) const
{
	Int32 ind = getPositionIndex( which );
	
	return _geo->getPositions()->getValue( ind );
}

inline		 
Int32 TriangleIterator::getNormalIndex( Int32 which ) const
{
	return _primIt.getNormalIndex( _triPntIndex[which] );
}

inline 
Vec3f TriangleIterator::getNormal( Int32 which ) const
{	
	Int32 ind = getNormalIndex( which );
	
	if ( ind < 0 )
		return NullVec3f;
		
	return _geo->getNormals()->getValue( ind );
}

inline		 
Int32 TriangleIterator::getColorIndex( Int32 which ) const
{
	return _primIt.getColorIndex( _triPntIndex[which] );
}

inline 
Color3f TriangleIterator::getColor( Int32 which ) const
{	
	Int32 ind = getColorIndex( which );
	
	if ( ind < 0 )
		return NullColor3f;
		
	return _geo->getColors()->getValue( ind );
}


/*! Return the texture coordinate index of a point in the current face. 
	\param which the point to access. Must be between 0 and getLength().
*/
inline		 
Int32 TriangleIterator::getTexCoordsIndex( Int32 which ) const
{
	return _primIt.getColorIndex( _triPntIndex[which] );
}

/*! Return the texture coordinate of a point in the current face. 
	\param which the point to access. Must be between 0 and getLength().
*/
inline 
Vec2f TriangleIterator::getTexCoords( Int32 which ) const
{	
	Int32 ind = getTexCoordsIndex( which );
	
	if ( ind < 0 )
		return NullVec2f;
		
	return _geo->getTexCoords()->getValue( ind );
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

