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

#define OSG_COMPILESYSTEMLIB

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"
#include "OSGTriangleIterator.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::TriangleIterator

The TriangleIterator iterates through the geometry one triangle at a
time.  Larger primtitives like strips are automatically split into
triangles, non-polygonal primitives like lines and points are ignored.

\sa PrimitiveIterator FaceIterator

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char TriangleIterator::cvsid[] = "@(#)$Id: OSGTriangleIterator.cpp,v 1.9 2001/06/10 12:42:07 vossg Exp $";

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

TriangleIterator::TriangleIterator(void) : 
	_primIt(), _geo(),
	_triIndex(0), _actPrimIndex(0), _triPntIndex()
{
}

TriangleIterator::TriangleIterator( const GeometryPtr& geo ) :
	_primIt(), _geo( geo ),
	_triIndex(0), _actPrimIndex(0), _triPntIndex()
{
	_primIt.setGeo( geo );
}

TriangleIterator::TriangleIterator( const NodePtr& geo ) :
	_primIt(), _geo( dcast<GeometryPtr>(geo->getCore()) ),
	_triIndex(0), _actPrimIndex(0), _triPntIndex()
{
	_primIt.setGeo( geo );
}


TriangleIterator::TriangleIterator(const TriangleIterator &source) :
	_primIt( source._primIt ), _geo( source._geo ),
	_triIndex(source._triIndex), _actPrimIndex(source._actPrimIndex),
	_triPntIndex()
{
	_triPntIndex[0] = source._triPntIndex[0];
	_triPntIndex[1] = source._triPntIndex[1];
	_triPntIndex[2] = source._triPntIndex[2];
}

/** \brief Destructor
 */

TriangleIterator::~TriangleIterator(void)
{
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/** \brief increment
 */

void TriangleIterator::operator++ ()
{
	// already at end?
	if ( _primIt.isAtEnd() )
		return;
	
	++_triIndex;

	// at end of primitive?
	if ( _actPrimIndex >= _primIt.getLength() )
	{
		++_primIt;		
		startPrim();
		
		return;
	}

	switch ( _primIt.getType() )
	{
	case GL_TRIANGLES:  	_triPntIndex[0] = _actPrimIndex++;
							_triPntIndex[1] = _actPrimIndex++;
							_triPntIndex[2] = _actPrimIndex++;
							break;
	case GL_QUAD_STRIP:
	case GL_TRIANGLE_STRIP: if ( _actPrimIndex & 1 )
							{
								_triPntIndex[0] = _triPntIndex[2];
							}
							else
							{
								_triPntIndex[1] = _triPntIndex[2];
							}							
							_triPntIndex[2] = _actPrimIndex++;
							break;
	case GL_POLYGON:
	case GL_TRIANGLE_FAN:	_triPntIndex[1] = _triPntIndex[2];
							_triPntIndex[2] = _actPrimIndex++;
							break;
	case GL_QUADS:			if ( _actPrimIndex & 1 )
							{
								_triPntIndex[1] = _triPntIndex[2];
								_triPntIndex[2] = _actPrimIndex++;
							}
							else
							{
								_triPntIndex[0] = _actPrimIndex++;
								_triPntIndex[1] = _actPrimIndex++;
								_triPntIndex[2] = _actPrimIndex++;
							}							
							break;
	default:				SWARNING << "TriangleIterator::++: encountered " 
									  << "unknown primitive type " 
									  << _primIt.getType()
									  << ", ignoring!" << endl;
							startPrim();
							break;
	}			
}

void TriangleIterator::startPrim( void )
{
	// already at end?
	if ( _primIt.isAtEnd() )
		return;
		
	_triPntIndex[0] = 0;
	_triPntIndex[1] = 1;
	_triPntIndex[2] = 2;
	_actPrimIndex = 3;
	
	// loop until you find a useful primitive or run out
	while ( ! _primIt.isAtEnd() )
	{
		switch ( _primIt.getType() )
		{
		case GL_POINTS: 		// non-polygon types: ignored
		case GL_LINES:
		case GL_LINE_STRIP: 
		case GL_LINE_LOOP:	
								break;
		case GL_TRIANGLES:  	// polygon types
		case GL_TRIANGLE_STRIP:
		case GL_TRIANGLE_FAN:
		case GL_QUADS:
		case GL_QUAD_STRIP:
		case GL_POLYGON:		if ( _primIt.getLength() >= 3 )
									return;
								break;
		default:				SWARNING << "TriangleIterator::startPrim: "
										  << "encountered " 
										  << "unknown primitive type " 
										  << _primIt.getType()
										  << ", ignoring!" << endl;
								break;
		}
		
		++_primIt;
	}			
}

void TriangleIterator::seek( Int32 index )
{
	_primIt.setToBegin();
	_triIndex = 0;
	startPrim();
	
	while ( getIndex() != index )
		++(*this);
}

void TriangleIterator::setToBegin( void )
{
	_primIt.setToBegin();
	_triIndex = 0;
	startPrim();
}

void TriangleIterator::setToEnd( void )
{
	_primIt.setToEnd();
	_actPrimIndex = 0;
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

TriangleIterator& TriangleIterator::operator = (const TriangleIterator &source)
{
	if (this == &source)
		return *this;

	// free mem alloced by members of 'this'

	// alloc new mem for members

	// copy 
	
	this->_geo 				= source._geo;
	this->_primIt 			= source._primIt;
	this->_triIndex  		= source._triIndex;
	this->_actPrimIndex  	= source._actPrimIndex;
	this->_triPntIndex[0] 	= source._triPntIndex[0];
	this->_triPntIndex[1] 	= source._triPntIndex[1];
	this->_triPntIndex[2] 	= source._triPntIndex[2];

	return *this;
}

/*-------------------------- comparison -----------------------------------*/

/** \brief assignment
 */

Bool TriangleIterator::operator < (const TriangleIterator &other) const
{
    return _primIt < other._primIt ||
			( _primIt == other._primIt &&
		      _actPrimIndex < other._actPrimIndex );
}

/** \brief equal
 */

Bool TriangleIterator::operator == (const TriangleIterator &other) const
{
	if ( _primIt.isAtEnd() && other._primIt.isAtEnd() )
		return true;
	if ( _primIt.isAtEnd() || other._primIt.isAtEnd() )
		return false;
    return _primIt == other._primIt &&
			_actPrimIndex == other._actPrimIndex;
}

/** \brief unequal
 */

Bool TriangleIterator::operator != (const TriangleIterator &other) const
{
	return ! (*this == other);
}


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


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

