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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#define OSG_COMPILEGEOMETRY

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include "OSGPrimitiveIterator.h"

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

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char PrimitiveIterator::cvsid[] = "@(#)$Id: OSGPrimitiveIterator.cpp,v 1.2 2001/01/18 11:06:17 vossg Exp $";

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

PrimitiveIterator::PrimitiveIterator(void) :
	_geo(), _primIndex(), _actPrimType(), _actPrimLength(),
	_actPointIndex(), _types(), _lengths(), _indices(), _ended()
{
}

PrimitiveIterator::PrimitiveIterator( const GeometryPtr& geo ) :
	_geo(), _primIndex(), _actPrimType(), _actPrimLength(),
	_actPointIndex(), _types(), _lengths(), _indices(), _ended()
{
	setGeo( geo );
}

PrimitiveIterator::PrimitiveIterator( const NodePtr& geo ) :
	_geo(), _primIndex(), _actPrimType(), _actPrimLength(),
	_actPointIndex(), _types(), _lengths(), _indices(), _ended()
{
	setGeo( geo );
}


PrimitiveIterator::PrimitiveIterator(const PrimitiveIterator &source) :
	_geo(source._geo),
	_primIndex(source._primIndex), _actPrimType(source._actPrimType), 
	_actPointIndex(source._actPointIndex),
	_actPrimLength(source._actPrimLength),  
	_types(source._types), 
	_lengths(source._lengths), _indices(source._indices), 
	_ended(source._ended)
{
}

/** \brief Destructor
 */

PrimitiveIterator::~PrimitiveIterator(void)
{
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

void PrimitiveIterator::setGeo( const GeometryPtr& geo )
{
	_geo = geo;
	_types = geo->getTypes();
	_lengths = geo->getLengths();
	_indices = geo->getIndex();
	
	setToBegin();
}

void PrimitiveIterator::setGeo( const NodePtr& geo )
{
	setGeo( geo->getCore().dcast<GeometryPtr>() );
}

/** \brief increment
 */

void PrimitiveIterator::operator++ ()
{
	if ( isAtEnd() )
	{
		return;
	}

	_actPointIndex += _actPrimLength;
	
	++_primIndex;

	if ( _primIndex >= _types->getSize() )
	{
		_ended = true;
	}
	else
	{
		_actPrimType = _types->getValue( _primIndex );
		_actPrimLength = _lengths->getValue( _primIndex );
	}
}

void PrimitiveIterator::setToBegin( void )
{
	_primIndex = 0;
	_actPointIndex = 0;
	_ended = false;
	_actPrimType = _types->getValue( _primIndex );
	_actPrimLength = _lengths->getValue( _primIndex );
}

void PrimitiveIterator::setToEnd( void )
{
	_primIndex = _types->getSize();
	_actPointIndex = 0;
	_ended = true;
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

PrimitiveIterator& PrimitiveIterator::operator = (const PrimitiveIterator &source)
{
	if (this == &source)
		return *this;

	// free mem alloced by members of 'this'

	// alloc new mem for members

	// copy 
	
	this->_geo 				= source._geo;
	this->_primIndex 		= source._primIndex;
	this->_actPrimType 		= source._actPrimType;
	this->_actPrimLength 	= source._actPrimLength;
	this->_actPointIndex 	= source._actPointIndex;
	this->_types 			= source._types;
	this->_lengths 			= source._lengths;
	this->_indices 			= source._indices;

	return *this;
}

/*-------------------------- comparison -----------------------------------*/

/** \brief assignment
 */

Bool PrimitiveIterator::operator < (const PrimitiveIterator &other) const
{
    return _geo == other._geo &&
		   _primIndex <= other._primIndex;
}

/** \brief equal
 */

Bool PrimitiveIterator::operator == (const PrimitiveIterator &other) const
{
    return _ended == other._ended &&
			_geo == other._geo &&
			_primIndex == other._primIndex;
}

/** \brief unequal
 */

Bool PrimitiveIterator::operator != (const PrimitiveIterator &other) const
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

