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

#include <OSGLog.h>
#include <OSGFieldContainer.h>
#include <OSGFieldContainerPtr.h>
#include <OSGNode.h>
#include <OSGNodeCore.h>
#include "OSGAction.h"
#include "OSGDrawAction.h"

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

using namespace OSG;

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char OSGDrawAction::cvsid[] = "@(#)$Id: $";

vector<OSGAction::Functor> *OSGDrawAction::_defaultEnterFunctors;

vector<OSGAction::Functor> *OSGDrawAction::_defaultLeaveFunctors;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/



/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

void OSGDrawAction::registerEnterDefault(	const OSGFieldContainerType &type, 
										const OSGAction::Functor &func )
{
	if ( ! _defaultEnterFunctors )
		_defaultEnterFunctors = new vector<OSGAction::Functor>;

	while(type.getId() >= _defaultEnterFunctors->size())
	{
		_defaultEnterFunctors->push_back( 
				osgFunctionFunctor2(&OSGAction::_defaultFunction));
	}
	
	(*_defaultEnterFunctors)[ type.getId() ] = func;
}

void OSGDrawAction::registerLeaveDefault(	const OSGFieldContainerType &type, 
										const OSGAction::Functor &func )
{
	if ( ! _defaultLeaveFunctors )
		_defaultLeaveFunctors = new vector<OSGAction::Functor>;

	while(type.getId() >= _defaultLeaveFunctors->size())
	{
		_defaultLeaveFunctors->push_back( 
				osgFunctionFunctor2(&OSGAction::_defaultFunction));
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

OSGDrawAction::OSGDrawAction(void)
{
	if ( _defaultEnterFunctors )
		_enterFunctors = *_defaultEnterFunctors;

	if ( _defaultLeaveFunctors )
		_leaveFunctors = *_defaultLeaveFunctors;
}


/** \brief Destructor
 */

OSGDrawAction::~OSGDrawAction(void)
{
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/
	
void OSGDrawAction::setCamera( OSGCamera * cam )
{
	_camera = cam;
}
		
void OSGDrawAction::setBackground( OSGBackground * background )
{
	_background = background;
}
		
void OSGDrawAction::setWindow( OSGWindow * window )
{
	_window = window;
}


/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

/*

OSGDrawAction& OSGDrawAction::operator = (const OSGDrawAction &source)
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

OSGBool OSGDrawAction::operator < (const OSGDrawAction &other) const
{
    return this < &other;
}

/** \brief equal
 */

OSGBool OSGDrawAction::operator == (const OSGDrawAction &other) const
{
    return false;
}

/** \brief unequal
 */

OSGBool OSGDrawAction::operator != (const OSGDrawAction &other) const
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

