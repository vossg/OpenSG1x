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

#include <OSGNode.h>
#include <OSGNodeCore.h>

OSG_BEGIN_NAMESPACE


inline NodePtr Action::getActNode( void )
{
    return _actNode;
}

    
inline void Action::setActNode(NodePtr node)
{
    _actNode = node;
}

inline
const NodePtr Action::getNode( int index )
{
    if ( ! _actList )
    {
        return _actNode->getChild( index );
    }
    else
    {
        return (*_actList)[ index ];
    }
}

inline
void Action::addNode( NodePtr node )
{
    _newList.push_back( node );
}

inline
void Action::useNodeList( void )
{
    _useNewList = true;
}

inline
UInt32 Action::getNNodes( void ) const
{
    if ( ! _actList )
    {
        return _actNode->getNChildren();
    }
    else
    {
        return (*_actList).size();
    }
}


inline
UInt32 Action::getTravMask(void) const
{
    return _travMask;
}

inline
void Action::setTravMask(UInt32 val)
{
    _travMask = val;
}

/*-------------------------- your_category---------------------------------*/

// callEnter/callLeave: call the right functor. If the type is unknown and new
// (i.e. its index is larger than the vector) try to find the function in the
// default list.

inline
Action::ResultE Action::callEnter( NodePtr node )
{
    ResultE result;

    UInt32 uiFunctorIndex = node->getCore()->getType().getId();
    CNodePtr cnode(node);

    if ( uiFunctorIndex < _enterFunctors.size() )
        result = _enterFunctors[uiFunctorIndex].call(cnode,this);
    else if (  getDefaultEnterFunctors() &&
                uiFunctorIndex < getDefaultEnterFunctors()->size() )
    {
        // field container registered method after this action was instantiated
        // copy the new functors from default vector
        std::vector<Functor> *defaultEnter = getDefaultEnterFunctors();

        while ( defaultEnter->size() > _enterFunctors.size() )
        {
            _enterFunctors.push_back( (*defaultEnter)[_enterFunctors.size()] );
        }
        result = _enterFunctors[uiFunctorIndex].call(cnode,this);
    }
    else // unknown field container
        result = _defaultEnterFunction(cnode,this);

    return result;
}

inline
Action::ResultE Action::callLeave( NodePtr node )
{
    ResultE result;

    UInt32 uiFunctorIndex = node->getCore()->getType().getId();
    CNodePtr cnode(node);

    if ( uiFunctorIndex < _leaveFunctors.size() )
        result = _leaveFunctors[uiFunctorIndex].call(cnode,this);
    else if (   getDefaultLeaveFunctors() &&
                uiFunctorIndex < getDefaultLeaveFunctors()->size() )
    {
        // field container registered method after this action was instantiated
        // copy the new functors from default vector
        std::vector<Functor> *defaultLeave = getDefaultLeaveFunctors();

        while ( defaultLeave->size() > _leaveFunctors.size() )
        {
            _leaveFunctors.push_back( (*defaultLeave)[_leaveFunctors.size()] );
        }
        result = _leaveFunctors[uiFunctorIndex].call(cnode,this);
    }
    else // unknown field container
        result = _defaultLeaveFunction(cnode,this);

    return result;
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */


/*-------------------------- comparison -----------------------------------*/

/** \brief assignment
 */


/** \brief equal
 */


/** \brief unequal
 */



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

