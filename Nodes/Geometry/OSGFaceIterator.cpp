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

#include "OSGFaceIterator.h"

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

char FaceIterator::cvsid[] = "@(#)$Id: OSGFaceIterator.cpp,v 1.2 2001/01/18 11:06:17 vossg Exp $";

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

FaceIterator::FaceIterator(void) : 
	_primIt(), _geo(),
	_faceIndex(0), _actPrimIndex(), _facePntIndex()
{
}

FaceIterator::FaceIterator( const GeometryPtr& geo ) :
	_primIt(), _geo( geo ),
	_faceIndex(0), _actPrimIndex(), _facePntIndex()
{
	_primIt.setGeo( geo );
}

FaceIterator::FaceIterator( const NodePtr& geo ) :
	_primIt(), _geo( geo->getCore().dcast<GeometryPtr>() ),
	_faceIndex(0), _actPrimIndex(), _facePntIndex()
{
	_primIt.setGeo( geo );
}


FaceIterator::FaceIterator(const FaceIterator &source) :
	_primIt( source._primIt ), _geo( source._geo ),
	_faceIndex(source._faceIndex), _facePntIndex()
{
	_facePntIndex[0] = source._facePntIndex[0];
	_facePntIndex[1] = source._facePntIndex[1];
	_facePntIndex[2] = source._facePntIndex[2];
	_facePntIndex[3] = source._facePntIndex[3];
}

/** \brief Destructor
 */

FaceIterator::~FaceIterator(void)
{
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/** \brief increment
 */

void FaceIterator::operator++ ()
{
	// already at end?
	if ( _primIt.isAtEnd() )
	{
		return;
	}
	
	++_faceIndex;

	// at end of primitive?
	if ( _actPrimIndex >= _primIt.getPrimLength() )
	{
		++_primIt;
		
		if ( ! _primIt.isAtEnd() )
			startPrim();
		
		return;
	}

	switch ( _primIt.getPrimType() )
	{
	case GL_TRIANGLES:  	_facePntIndex[0] = _actPrimIndex++;
							_facePntIndex[1] = _actPrimIndex++;
							_facePntIndex[2] = _actPrimIndex++;
							_facePntIndex[3] = -1;
							_actPrimIndex += 3;	
							break;
	case GL_QUAD_STRIP: 	_facePntIndex[0] = _facePntIndex[2];
							_facePntIndex[1] = _facePntIndex[3];
							_facePntIndex[3] = _actPrimIndex++;
							_facePntIndex[2] = _actPrimIndex++;
							break;
	case GL_TRIANGLE_STRIP: if ( _actPrimIndex & 1 )
							{
								_facePntIndex[0] = _facePntIndex[2];
							}
							else
							{
								_facePntIndex[1] = _facePntIndex[2];
							}							
							_facePntIndex[2] = _actPrimIndex++;
							break;
	case GL_POLYGON:
	case GL_TRIANGLE_FAN:	_facePntIndex[1] = _facePntIndex[2];
							_facePntIndex[2] = _actPrimIndex++;
							break;
	case GL_QUADS:			_facePntIndex[0] = _actPrimIndex++;
							_facePntIndex[1] = _actPrimIndex++;
							_facePntIndex[2] = _actPrimIndex++;
							_facePntIndex[3] = _actPrimIndex++;
							break;
	default:			SWARNING << "FaceIterator::++: encountered " 
								  << "unknown primitive type " 
								  << _primIt.getPrimType()
								  << ", ignoring!" << endl;
						if ( ! _primIt.isAtEnd() )
							startPrim();
						break;
	}			
}

void FaceIterator::startPrim( void )
{
	_facePntIndex[0] = 0;
	_facePntIndex[1] = 1;
	_facePntIndex[2] = 2;
	_facePntIndex[3] = -1;
	_actPrimIndex = 3;
	
	switch ( _primIt.getPrimType() )
	{
	case GL_POINTS: 	// non-polygon types: ignored
	case GL_LINES:
	case GL_LINE_STRIP: 
	case GL_LINE_LOOP:	++_primIt;
						if ( ! _primIt.isAtEnd() )
							startPrim();
						break;
	case GL_TRIANGLES: 
	case GL_TRIANGLE_STRIP:
	case GL_TRIANGLE_FAN:	if ( _primIt.getPrimLength() < 3 )
						{
							++_primIt;
							if ( ! _primIt.isAtEnd() )
								startPrim();
							break;
						}
						break;
	case GL_POLYGON:	switch ( _primIt.getPrimLength() )
						{
						case 0: case 1: case 2:
							++_primIt;
							if ( ! _primIt.isAtEnd() )
								startPrim();
							break;
						case 4:
							_facePntIndex[3] = _actPrimIndex++;	
							break;
						default:
							break;
						}
						break;
	case GL_QUADS:		if ( _primIt.getPrimLength() < 4 )
						{
							++_primIt;
							if ( ! _primIt.isAtEnd() )
								startPrim();
							break;
						}
						_facePntIndex[3] = _actPrimIndex++;						
						break;
	case GL_QUAD_STRIP:	if ( _primIt.getPrimLength() < 4 )
						{
							++_primIt;
							if ( ! _primIt.isAtEnd() )
								startPrim();
							break;
						}
						_facePntIndex[3] = _facePntIndex[3];						
						_facePntIndex[2] = _actPrimIndex++;						
						break;
	default:			SWARNING << "FaceIterator::startPrim: encountered " 
								  << "unknown primitive type " 
								  << _primIt.getPrimType()
								  << ", ignoring!" << endl;
						++_primIt;
						if ( ! _primIt.isAtEnd() )
							startPrim();
						break;
	}			
}

void FaceIterator::setToBegin( void )
{
	_primIt.setToBegin();
	_faceIndex = 0;
	startPrim();
}

void FaceIterator::setToEnd( void )
{
	_primIt.setToEnd();
	_actPrimIndex = 0;
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

FaceIterator& FaceIterator::operator = (const FaceIterator &source)
{
	if (this == &source)
		return *this;

	// free mem alloced by members of 'this'

	// alloc new mem for members

	// copy 
	
	this->_geo 				= source._geo;
	this->_primIt 			= source._primIt;
	this->_faceIndex  		= source._faceIndex;
	this->_actPrimIndex  	= source._actPrimIndex;
	this->_facePntIndex[0] 	= source._facePntIndex[0];
	this->_facePntIndex[1] 	= source._facePntIndex[1];
	this->_facePntIndex[2] 	= source._facePntIndex[2];
	this->_facePntIndex[3] 	= source._facePntIndex[3];

	return *this;
}

/*-------------------------- comparison -----------------------------------*/

/** \brief assignment
 */

Bool FaceIterator::operator < (const FaceIterator &other) const
{
    return _primIt < other._primIt ||
			( _primIt == other._primIt &&
		      _actPrimIndex < other._actPrimIndex );
}

/** \brief equal
 */

Bool FaceIterator::operator == (const FaceIterator &other) const
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

Bool FaceIterator::operator != (const FaceIterator &other) const
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

