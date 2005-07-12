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

#include <OSGLog.h>
#include <OSGFieldContainer.h>
#include <OSGFieldContainerPtr.h>
#include <OSGNode.h>
#include <OSGNodeCore.h>
#include "OSGAction.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Action
    \ingroup GrpSystemAction

The action base class.

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char Action::cvsid[] = "@(#)$Id: $";

Action * Action::_prototype = NULL;

std::vector<Action::Functor> *Action::_defaultEnterFunctors;
std::vector<Action::Functor> *Action::_defaultLeaveFunctors;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/



/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

void Action::registerEnterDefault(  const FieldContainerType &type, 
                                        const Action::Functor &func )
{
    if ( ! _defaultEnterFunctors )
        _defaultEnterFunctors = new std::vector<Action::Functor>;

    while(type.getId() >= _defaultEnterFunctors->size())
    {
        _defaultEnterFunctors->push_back( 
            osgTypedFunctionFunctor2CPtrRef<
                ResultE, 
                CNodePtr,
                Action *                   >(&Action::_defaultEnterFunction));
    }
    
    (*_defaultEnterFunctors)[ type.getId() ] = func;
}

void Action::registerLeaveDefault(  const FieldContainerType &type, 
                                        const Action::Functor &func )
{
    if ( ! _defaultLeaveFunctors )
        _defaultLeaveFunctors = new std::vector<Action::Functor>;

    while(type.getId() >= _defaultLeaveFunctors->size())
    {
        _defaultLeaveFunctors->push_back( 
            osgTypedFunctionFunctor2CPtrRef<
                ResultE, 
                CNodePtr,
                Action *                   >(&Action::_defaultLeaveFunction));
    }
    
    (*_defaultLeaveFunctors)[ type.getId() ] = func;
}

void Action::setPrototype( Action * proto )
{
    _prototype = proto;
}

Action *Action::getPrototype( void )
{
    return _prototype;
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

Action::Action(void) : _travMask(TypeTraits<UInt32>::getMax())
{
    if ( _defaultEnterFunctors )
        _enterFunctors = *_defaultEnterFunctors;

    if ( _defaultLeaveFunctors )
        _leaveFunctors = *_defaultLeaveFunctors;
}

/** \brief Copy-Constructor
 */

Action::Action( const Action & source ) :
    _enterFunctors( source._enterFunctors ),
    _leaveFunctors( source._leaveFunctors ),
    _travMask     ( source._travMask      )
{
}


/** \brief create a new action
 */

Action * Action::create( void )
{
    Action * act;
    
    if ( _prototype )
        act = new Action( *_prototype );
    else
        act = new Action();
    
    return act;
}

/** \brief Destructor
 */

Action::~Action(void)
{
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

void Action::registerEnterFunction( const FieldContainerType &type, 
        const Action::Functor& func )
{
    while ( type.getId() >= _enterFunctors.size() )
    {
        _enterFunctors.push_back(
            osgTypedFunctionFunctor2CPtrRef<
                ResultE, 
                CNodePtr,
                Action *                   >(&Action::_defaultEnterFunction));
    }
    
    _enterFunctors[ type.getId() ] = func;
}

void Action::registerLeaveFunction( const FieldContainerType &type, 
        const Action::Functor& func )
{
    while ( type.getId() >= _leaveFunctors.size() )
    {
        _leaveFunctors.push_back(
            osgTypedFunctionFunctor2CPtrRef<
                ResultE, 
                CNodePtr,
                Action *                   >(&Action::_defaultLeaveFunction));
    }
    
    _leaveFunctors[ type.getId() ] = func;
}



// application entry points

Action::ResultE Action::apply(std::vector<NodePtr>::iterator begin,
                              std::vector<NodePtr>::iterator end)
{
    Action::ResultE res = Continue;
    
    // call the start function and its' returns
    if ( ( res = callStart() ) != Continue )
        return res;     
    
    // call the given nodes
    
    for ( ; begin != end; begin ++ )
    {
        if ( *begin == NullFC )
        {
            SWARNING << "apply: encountered NullNode!" << std::endl;
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

Action::ResultE Action::apply(NodePtr node)
{
    if(node == NullFC)
    {
        SWARNING << "apply: node is Null!" << std::endl;
        return Quit;            
    }

    std::vector<NodePtr> nodeList;

    nodeList.push_back(node);

    return apply(nodeList.begin(), nodeList.end());
}




// recursion calling

Action::ResultE Action::recurse( NodePtr node  )
{
    if ( node == NullFC )
        return Continue;

    if((node->getTravMask() & getTravMask()) == 0)
        return Continue;

    NodeCorePtr core = node->getCore();
    
    if ( core == NullFC )
    {
        SWARNING << "recurse: core is Null,  don't know what to do!" 
                 << std::endl;
        return Quit;                    
    }
    
    Action::ResultE result;
    
    _actList = NULL;
    _actNode = node;
    _newList.clear();
    _useNewList = false;
    
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
    else if ( ! _useNewList ) // new list is empty, but not used?
    {
        std::vector<NodePtr>::iterator it;

        for ( it = node->getMFChildren()->begin(); it != node->getMFChildren()->end(); it ++ )
        {
            result = recurse( *it );
            
            if ( result != Continue )
                break;
        }
    }

    _actNode = node;
    if ( result == Continue )
        result = callLeave( node );
    else
        callLeave( node );

    if ( result == Skip )
        return Continue;
        
    return result;
}

// call the _newList objects
Action::ResultE Action::callNewList(void)
{
    Action::ResultE result = Continue;

    // need to make a copy, because the one in the action is cleared

    std::vector<NodePtr> nodeList;
    nodeList.swap(_newList);

    std::vector<NodePtr>::iterator it;

    _actList = &nodeList;

    for(it = nodeList.begin(); it != nodeList.end(); ++it)
    {
        result = recurse(*it);

        if(result != Continue)
            break;
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

bool Action::operator < (const Action &other)
{
    return this < &other;
}

/** \brief equal
 */

bool Action::operator == (const Action &OSG_CHECK_ARG(other))
{
    return false;
}

/** \brief unequal
 */

bool Action::operator != (const Action &other)
{
    return ! (*this == other);
}


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

std::vector<Action::Functor>* Action::getDefaultEnterFunctors( void )
{
    return _defaultEnterFunctors;
}

std::vector<Action::Functor>* Action::getDefaultLeaveFunctors( void )
{
    return _defaultLeaveFunctors;
}


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

// default Action function: just call all kids

Action::ResultE Action::_defaultEnterFunction(CNodePtr &OSG_CHECK_ARG(node  ), 
                                              Action   *OSG_CHECK_ARG(action))
{
    return Continue;
}

Action::ResultE Action::_defaultLeaveFunction(CNodePtr &OSG_CHECK_ARG(node  ), 
                                              Action   *OSG_CHECK_ARG(action))
{
    return Continue;
}

/*************** Functions ******************/

OSG_BEGIN_NAMESPACE

inline
Action::ResultE doCallEnter(NodePtr               node, 
                            TraverseEnterFunctor &func)
{
    return func.call(node);
}

inline
Action::ResultE doCallLeave(NodePtr               node, 
                            Action::ResultE       res,
                            TraverseLeaveFunctor &func)
{
    return func.call(node, res);
}

OSG_END_NAMESPACE

/*! Simple tree traversal function. Calls func for every node encountered
 */
OSG_SYSTEMLIB_DLLMAPPING
Action::ResultE OSG::traverse(std::vector<NodePtr> &nodeList, 
                              TraverseEnterFunctor  func    )
{
    Action::ResultE res = Action::Continue;

    std::vector<NodePtr>::iterator it = nodeList.begin();
    std::vector<NodePtr>::iterator en = nodeList.end  ();
    
    for ( ; it != en; ++it )
    {
        res = traverse((*it), func);
        
        if(res == Action::Quit)
            break;
    }
        
    return res;
}

/*! Simple tree traversal function. Calls func for every node encountered
 */
OSG_SYSTEMLIB_DLLMAPPING
Action::ResultE OSG::traverse( NodePtr              node, 
                               TraverseEnterFunctor func )
{
    Action::ResultE res = Action::Continue;
    
    res = doCallEnter(node, func);
    
    switch(res)
    {
    case Action::Skip:      return Action::Continue;
    case Action::Continue:  return traverse( node->getMFChildren()->getValues(), 
                                             func );
    default:                break;
    }
                 
    return res;
}
                            
/*! Simple tree traversal function. Calls enter before entering a node,
    leave after leaving.
 */
OSG_SYSTEMLIB_DLLMAPPING
Action::ResultE OSG::traverse(std::vector<NodePtr> &nodeList, 
                              TraverseEnterFunctor  enter, 
                              TraverseLeaveFunctor  leave )
{
    Action::ResultE res = Action::Continue;

    std::vector<NodePtr>::iterator it = nodeList.begin();
    std::vector<NodePtr>::iterator en = nodeList.end  ();
    
    for ( ; it != en; ++it )
    {
        res = traverse((*it), enter, leave);
        
        if(res == Action::Quit)
            break;
    }
        
    return res;
}

                            
/*! Simple tree traversal function. Calls enter before entering a node,
    leave after leaving.
 */
OSG_SYSTEMLIB_DLLMAPPING
Action::ResultE OSG::traverse(   NodePtr node, 
                                 TraverseEnterFunctor enter, 
                                 TraverseLeaveFunctor leave )
{
    Action::ResultE res = Action::Continue;
    
    res = doCallEnter(node, enter);
    
    switch(res)
    {
    case Action::Skip:      res = Action::Continue;
                            break;
    case Action::Continue:  res = traverse( node->getMFChildren()->getValues(), 
                                             enter, leave );
    default:                break;
    }
     
    res = doCallLeave(node, res, leave);
                
    return res;
}
