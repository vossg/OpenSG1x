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

#define OSG_COMPILEACTION

#include <OSGLog.h>
#include <OSGFieldContainer.h>
#include <OSGFieldContainerPtr.h>
#include <OSGNode.h>
#include <OSGNodeCore.h>
#include "OSGAction.h"

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

char Action::cvsid[] = "@(#)$Id: $";

vector<Action::Functor> *Action::_defaultEnterFunctors;

vector<Action::Functor> *Action::_defaultLeaveFunctors;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/



/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

void Action::registerEnterDefault(	const FieldContainerType &type, 
										const Action::Functor &func )
{
	if ( ! _defaultEnterFunctors )
		_defaultEnterFunctors = new vector<Action::Functor>;

	while(type.getId() >= _defaultEnterFunctors->size())
	{
		_defaultEnterFunctors->push_back( 
				osgFunctionFunctor2(&Action::_defaultFunction));
	}
	
	(*_defaultEnterFunctors)[ type.getId() ] = func;
}

void Action::registerLeaveDefault(	const FieldContainerType &type, 
										const Action::Functor &func )
{
	if ( ! _defaultLeaveFunctors )
		_defaultLeaveFunctors = new vector<Action::Functor>;

	while(type.getId() >= _defaultLeaveFunctors->size())
	{
		_defaultLeaveFunctors->push_back( 
				osgFunctionFunctor2(&Action::_defaultFunction));
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

Action::Action(void)
{
	if ( _defaultEnterFunctors )
		_enterFunctors = *_defaultEnterFunctors;

	if ( _defaultLeaveFunctors )
		_leaveFunctors = *_defaultLeaveFunctors;
}


/** \brief Destructor
 */

Action::~Action(void)
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

void Action::registerEnterFunction( const FieldContainerType &type, 
		const Action::Functor& func )
{
	while ( type.getId() >= _enterFunctors.size() )
	{
		_enterFunctors.push_back(
            osgFunctionFunctor2(&Action::_defaultFunction));
	}
	
	_enterFunctors[ type.getId() ] = func;
}

void Action::registerLeaveFunction( const FieldContainerType &type, 
		const Action::Functor& func )
{
	while ( type.getId() >= _leaveFunctors.size() )
	{
		_leaveFunctors.push_back(
            osgFunctionFunctor2(&Action::_defaultFunction));
	}
	
	_leaveFunctors[ type.getId() ] = func;
}



// application entry points

Action::ResultE Action::apply(vector<NodePtr>::iterator begin,
                              vector<NodePtr>::iterator end)
{
	Action::ResultE res = Continue;
	
/*  Does not work everywhere. (GV)

	if ( ! begin || ! end )
	{
		SWARNING << "apply: begin or end is NULL!" << endl;
		return Quit;
	}
*/
	
	// call the start function and its' returns
	if ( ( res = callStart() ) != Continue )
		return res;	
	
	// call the given nodes
	
	for ( ; begin != end; begin ++ )
	{
		if ( *begin == NullNode )
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

Action::ResultE Action::apply( NodePtr node  )
{
	if ( node == NullNode )
	{
		SWARNING << "apply: node is Null!" << endl;
		return Quit;			
	}

	vector<NodePtr> list;
	list.push_back( node );

    return apply( list.begin(), list.end() );
}




// recursion calling

Action::ResultE Action::recurse( NodePtr node  )
{
    if ( node == NullNode )
        return Continue;

	NodeCorePtr core = node->getCore();
	
	if ( core == NullNodeCore )
	{
		SWARNING << "recurse: core is Null,  don't know what to do!" << endl;
		return Quit;					
	}
	
//	const FieldContainerType &t = core->getType();	
	Action::ResultE result;
	
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
		vector<NodePtr>::iterator it;

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
Action::ResultE Action::callNewList( void )
{
	Action::ResultE result = Continue;

	if ( ! _newList.empty() )
	{
		// need to make a copy, because the one in the action is cleared
		
		vector<NodePtr> list = _newList;
		vector<NodePtr>::iterator it;
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

Action::ResultE Action::callStart( void )
{
	Action::ResultE res = Continue;
	
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

Action::ResultE Action::callStop( ResultE res )
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


Action::ResultE Action::start( void )
{
    return Continue;
}

Action::ResultE Action::stop( ResultE res )
{
    return res;
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

Action& Action::operator = (const Action &source)
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

Bool Action::operator < (const Action &other)
{
    return this < &other;
}

/** \brief equal
 */

Bool Action::operator == (const Action &other)
{
	return false;
}

/** \brief unequal
 */

Bool Action::operator != (const Action &other)
{
	return ! (*this == other);
}


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/


Action::ResultE Action::_defaultFunction(CNodePtr& node, Action * action)
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

