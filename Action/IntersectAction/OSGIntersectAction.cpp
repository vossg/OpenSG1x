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


#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#define OSG_COMPILEINTERSECTACTION

#include <OSGLog.h>
#include <OSGFieldContainer.h>
#include <OSGFieldContainerPtr.h>
#include <OSGNode.h>
#include <OSGNodeCore.h>
#include <OSGAction.h>
#include "OSGIntersectAction.h"

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

using namespace OSG;

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char IntersectAction::cvsid[] = "@(#)$Id: OSGIntersectAction.cpp,v 1.1 2001/01/26 10:37:12 dirk Exp $";

vector<Action::Functor> *IntersectAction::_defaultEnterFunctors;

vector<Action::Functor> *IntersectAction::_defaultLeaveFunctors;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/



/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

void IntersectAction::registerEnterDefault(	const FieldContainerType &type, 
										const Action::Functor &func )
{
	if ( ! _defaultEnterFunctors )
		_defaultEnterFunctors = new vector<Action::Functor>;

	while(type.getId() >= _defaultEnterFunctors->size())
	{
		_defaultEnterFunctors->push_back( 
				osgFunctionFunctor2(&IntersectAction::_defaultFunction));
	}
	
	(*_defaultEnterFunctors)[ type.getId() ] = func;
}

void IntersectAction::registerLeaveDefault(	const FieldContainerType &type, 
										const Action::Functor &func )
{
	if ( ! _defaultLeaveFunctors )
		_defaultLeaveFunctors = new vector<Action::Functor>;

	while(type.getId() >= _defaultLeaveFunctors->size())
	{
		_defaultLeaveFunctors->push_back( 
				osgFunctionFunctor2(&IntersectAction::_defaultFunction));
	}
	
	(*_defaultLeaveFunctors)[ type.getId() ] = func;
}


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

IntersectAction::IntersectAction(void) :
	_line(), _maxdist(), 
	_hit(false), _enter(-1), _leave(-1), _hitT(-1), _hitObject(),
	_hitTriangle(-1)
{
	if ( _defaultEnterFunctors )
		_enterFunctors = *_defaultEnterFunctors;

	if ( _defaultLeaveFunctors )
		_leaveFunctors = *_defaultLeaveFunctors;
}


IntersectAction::IntersectAction( const Line &line, const Real32 maxdist ) :
	_line( line ), _maxdist( maxdist ), 
	_hit(false), _enter(-1), _leave(-1), _hitT(-1), _hitObject(),
	_hitTriangle(-1)
{
	if ( _defaultEnterFunctors )
		_enterFunctors = *_defaultEnterFunctors;

	if ( _defaultLeaveFunctors )
		_leaveFunctors = *_defaultLeaveFunctors;
}

/** \brief Destructor
 */

IntersectAction::~IntersectAction(void)
{
}

/*------------------------------ application -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

void IntersectAction::setLine( const Line &line, const Real32 maxdist )
{
	_line = line;
	_maxdist = maxdist;
}
	
Action::ResultE  IntersectAction::setEnterLeave( Real32 enter, Real32 leave )
{
	if ( leave < 0 || enter > _maxdist ||
		( _hit && enter > _hitT ) )
		return Action::Skip;

	return Action::Continue;
}

void IntersectAction::setHit( Real32 t, NodePtr obj, Int32 triIndex )
{
	if ( t < 0 || t > _hitT )
		return;
		
	_hitT = t;
	_hitObject = obj;
	_hitTriangle = triIndex;
	_hit = true;
}

/*-------------------------- your_category---------------------------------*/


Action::ResultE IntersectAction::start( void )
{
	_hitT = Inf;
	_hitObject = NullNode;
	_hitTriangle = -1;
	_hit = false;
    return Continue;
}


/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

/*

IntersectAction& IntersectAction::operator = (const IntersectAction &source)
{
	if (this == &source)
		return *this;

	// copy parts inherited from parent
	*(static_cast<Inherited *>(this)) = source;

	// free mem alloced by members of 'this'

	// alloc new mem for members

	// copy 
}

*/

/*-------------------------- comparison -----------------------------------*/

/** \brief assignment
 */

Bool IntersectAction::operator < (const IntersectAction &other) const
{
    return this < &other;
}

/** \brief equal
 */

Bool IntersectAction::operator == (const IntersectAction &other) const
{
    return false;
}

/** \brief unequal
 */

Bool IntersectAction::operator != (const IntersectAction &other) const
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

