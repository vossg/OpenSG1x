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

char OSGAction::cvsid[] = "@(#)$Id: $";

vector<OSGAction::Functor> *OSGAction::_defaultEnterFunctors;

vector<OSGAction::Functor> *OSGAction::_defaultLeaveFunctors;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/



/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

void OSGAction::registerEnterDefault(	const OSGFieldContainerType &type, 
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

void OSGAction::registerLeaveDefault(	const OSGFieldContainerType &type, 
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

OSGAction::OSGAction(void)
{
	if ( _defaultEnterFunctors )
		_enterFunctors = *_defaultEnterFunctors;

	if ( _defaultLeaveFunctors )
		_leaveFunctors = *_defaultLeaveFunctors;
}


/** \brief Destructor
 */

OSGAction::~OSGAction(void)
{
}

/*------------------------------ access -----------------------------------*/

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

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

void OSGAction::registerEnterFunction( const OSGFieldContainerType &type, 
		const OSGAction::Functor& func )
{
	while ( type.getId() >= _enterFunctors.size() )
	{
		_enterFunctors.push_back(
            osgFunctionFunctor2(&OSGAction::_defaultFunction));
	}
	
	_enterFunctors[ type.getId() ] = func;
}

void OSGAction::registerLeaveFunction( const OSGFieldContainerType &type, 
		const OSGAction::Functor& func )
{
	while ( type.getId() >= _leaveFunctors.size() )
	{
		_leaveFunctors.push_back(
            osgFunctionFunctor2(&OSGAction::_defaultFunction));
	}
	
	_leaveFunctors[ type.getId() ] = func;
}



// application entry points

OSGAction::ResultE OSGAction::apply( vector<OSGNodePtr>::iterator begin,
	vector<OSGNodePtr>::iterator end  )
{
	OSGAction::ResultE res = Continue;
	
	if ( ! begin || ! end )
	{
		SWARNING << "apply: begin or end is NULL!" << endl;
		return Quit;
	}
	
	// call the start function and its' returns
	if ( ( res = callStart() ) != Continue )
		return res;	
	
	// call the given nodes
	
	for ( ; begin != end; begin ++ )
	{
		if ( *begin == OSGNullNode )
		{
			SWARNING << "apply: encountered NullNode!" << endl;
			return Quit;			
		}
		else
		{
			res = recurse( *begin );
			
			if ( res != Continue )
				break;
		}
	}
		
	// call the stop function and its' returns
	res = callStop( res );	
	
	return res;
}

OSGAction::ResultE OSGAction::apply( OSGNodePtr node  )
{
	if ( node == OSGNullNode )
	{
		SWARNING << "apply: node is Null!" << endl;
		return Quit;			
	}

	vector<OSGNodePtr> list;
	list.push_back( node );

    return apply( list.begin(), list.end() );
}




// recursion calling

OSGAction::ResultE OSGAction::recurse( OSGNodePtr node  )
{
    if ( node == OSGNullNode )
        return Continue;

	OSGNodeCorePtr core = node->getCore();
	
	if ( core == OSGNullNodeCore )
	{
		SWARNING << "recurse: core is Null,  don't know what to do!" << endl;
		return Quit;					
	}
	
	const OSGFieldContainerType &t = core->getType();	
	OSGAction::ResultE result;
	
	_actList = NULL;
	_actNode = node;
	_newList.clear();
	
	result = callEnter( node );

	if ( result != Continue )
	{
		if ( result == Skip )
			return Continue;
	
		return result;
	}
	
	if ( ! _newList.empty() )
	{
		result = callNewList();
	}
	else
	{
		vector<OSGNodePtr>::iterator it;

		for ( it = node->getMFChildren()->begin(); it != node->getMFChildren()->end(); it ++ )
		{
			result = recurse( *it );
			
			if ( result != Continue )
				break;
		}
	}	
	
	if ( result == Continue )
		result = callLeave( node );
	else
		callLeave( node );

	if ( result == Skip )
		return Continue;
		
	return result;
}

// call the _newList objects
OSGAction::ResultE OSGAction::callNewList( void )
{
	OSGAction::ResultE result = Continue;

	if ( ! _newList.empty() )
	{
		// need to make a copy, because the one in the action is cleared
		
		vector<OSGNodePtr> list = _newList;
		vector<OSGNodePtr>::iterator it;
		_actList = &list;

		for ( it = list.begin(); it != list.end(); it ++ )
		{
			result = recurse( *it );
			
			if ( result != Continue )
				break;
		}
	}
	
	return result;
}


// call the start function and its results

OSGAction::ResultE OSGAction::callStart( void )
{
	OSGAction::ResultE res = Continue;
	
	// call the start and see if it returns some nodes
	
	_newList.clear();

	if ( ( res = start() ) != Continue )
		return res;	
	
	// got some nodes? call them
	
	if ( ! _newList.empty() )
		res = callNewList();
	
	// return the result

	return res;
}

// call the stop function and its results

OSGAction::ResultE OSGAction::callStop( ResultE res )
{
	// call the start and see if it returns some nodes
	
	_newList.clear();

	if ( ( res = stop( res ) ) != Continue )
		return res;	
			
	if ( ! _newList.empty() )
		res = callNewList();

	return res;
}

// default start/stop, does nothing


OSGAction::ResultE OSGAction::start( void )
{
    return Continue;
}

OSGAction::ResultE OSGAction::stop( ResultE res )
{
    return res;
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

OSGAction& OSGAction::operator = (const OSGAction &source)
{
	if (this == &source)
		return *this;

	// free mem alloced by members of 'this'

	
	// alloc new mem for members

	// copy 

	return *this;
}

/*-------------------------- comparison -----------------------------------*/

/** \brief assignment
 */

OSGBool OSGAction::operator < (const OSGAction &other)
{
    return this < &other;
}

/** \brief equal
 */

OSGBool OSGAction::operator == (const OSGAction &other)
{
	return false;
}

/** \brief unequal
 */

OSGBool OSGAction::operator != (const OSGAction &other)
{
	return ! (*this == other);
}


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/


OSGAction::ResultE OSGAction::_defaultFunction(OSGCNodePtr& node, OSGAction * action)
{
	return Continue;
}

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

