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
Bool PrimitiveIterator::isAtEnd( void ) const
{
#if 1
	return _ended;
#else
// this trigger a bug in sgi compiler in collision between
// FCPtr::getSize() and GeoProperty::getSize(). Don't use right now.
	return _primIndex >= _types->getSize();
#endif
}

inline		 
Int32 PrimitiveIterator::getIndex( void ) const
{
	return _primIndex;
}

inline		 
Int32 PrimitiveIterator::getLength( void ) const
{
	return _actPrimLength;
}

inline		 
UInt8 PrimitiveIterator::getType( void ) const
{
	return _actPrimType;
}

inline		 
Int32 PrimitiveIterator::getPositionIndex( Int32 which ) const
{
	if ( _geo->getIndex() != NullFC )
		return _indices->getValue( _actPointIndex + which );
	else
		return _actPointIndex + which;
}

inline		 
Pnt3f PrimitiveIterator::getPosition( Int32 which ) const
{
	Int32 ind = getPositionIndex( which );
	
	return _geo->getPositions()->getValue( ind );
}

inline		 
Int32 PrimitiveIterator::getNormalIndex( Int32 which ) const
{
	if ( _geo->getNormals() == NullFC )
		return -1;

	if ( _geo->getNormalPerVertex() )
		return _indices->getValue( _actPointIndex + which );
	else
		return _primIndex;
}

inline 
Vec3f PrimitiveIterator::getNormal( Int32 which ) const
{	
	Int32 ind = getNormalIndex( which );
	
	if ( ind < 0 )
		return NullVec3f;
		
	return _geo->getNormals()->getValue( ind );
}

inline		 
Int32 PrimitiveIterator::getColorIndex( Int32 which ) const
{
	if ( _geo->getColors() == NullFC )
		return -1;

	if ( _geo->getColorPerVertex() )
		return _indices->getValue( _actPointIndex + which );
	else
		return _primIndex;
}

inline 
Color3f PrimitiveIterator::getColor( Int32 which ) const
{	
	Int32 ind = getColorIndex( which );
	
	if ( ind < 0 )
		return NullColor3f;
		
	return _geo->getColors()->getValue( ind );
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

