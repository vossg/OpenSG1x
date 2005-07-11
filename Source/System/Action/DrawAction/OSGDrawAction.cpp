/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#include <OSGLog.h>
#include <OSGFieldContainer.h>
#include <OSGFieldContainerPtr.h>
#include <OSGNode.h>
#include <OSGNodeCore.h>
#include "OSGAction.h"
#include "OSGDrawAction.h"

#include <OSGGL.h>
#include <OSGVolumeDraw.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::DrawAction
    \ingroup GrpSystemAction

The draw action class.

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char DrawAction::cvsid[] = "@(#)$Id: $";

DrawAction * DrawAction::_prototype = NULL;

std::vector<Action::Functor> *DrawAction::_defaultEnterFunctors = NULL;
std::vector<Action::Functor> *DrawAction::_defaultLeaveFunctors = NULL;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/



/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

void DrawAction::registerEnterDefault(  const FieldContainerType &type, 
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

void DrawAction::registerLeaveDefault(  const FieldContainerType &type, 
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


void DrawAction::setPrototype( DrawAction * proto )
{
    _prototype = proto;
}

DrawAction *DrawAction::getPrototype( void )
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

DrawAction::DrawAction(void) :
     Inherited (),
    _lightCount(0)
{
    if ( _defaultEnterFunctors )
        _enterFunctors = *_defaultEnterFunctors;

    if ( _defaultLeaveFunctors )
        _leaveFunctors = *_defaultLeaveFunctors;
}


/** \brief Copy-Constructor
 */

DrawAction::DrawAction( const DrawAction & source ) :
     Inherited (source),
    _lightCount(source._lightCount)
{
}

/** \brief create a new action
 */

DrawAction * DrawAction::create( void )
{
    DrawAction * act;
    
    if ( _prototype )
        act = new DrawAction( *_prototype );
    else
        act = new DrawAction();
    
    return act;
}


/** \brief Destructor
 */

DrawAction::~DrawAction(void)
{
}

/*------------------------------ access -----------------------------------*/

/*-------------------------- your_category---------------------------------*/


Action::ResultE DrawAction::start( void )
{
    Inherited::start();
    
    _lightCount = 0;
    
    return Continue;
}

bool DrawAction::isVisible( Node* node )
{
    if ( getFrustumCulling() == false )
        return true;
        
    getStatistics()->getElem(statCullTestedNodes)->inc();
    
    DynamicVolume vol;
    node->getWorldVolume( vol );

    if ( _frustum.intersect( vol ) )
    {
// fprintf(stderr,"%p: node 0x%p vis\n", Thread::getCurrent(), node);
        return true;
    }
    
    getStatistics()->getElem(statCulledNodes)->inc();

// fprintf(stderr,"%p: node 0x%p invis\n", Thread::getCurrent(), node);
// _frustum.dump();            
    return false;
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

/*

DrawAction& DrawAction::operator = (const DrawAction &source)
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

bool DrawAction::operator < (const DrawAction &other) const
{
    return this < &other;
}

/** \brief equal
 */

bool DrawAction::operator == (const DrawAction &OSG_CHECK_ARG(other)) const
{
    return false;
}

/** \brief unequal
 */

bool DrawAction::operator != (const DrawAction &other) const
{
    return ! (*this == other);
}


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


std::vector<DrawAction::Functor>* DrawAction::getDefaultEnterFunctors( void )
{
    return _defaultEnterFunctors;
}

std::vector<DrawAction::Functor>* DrawAction::getDefaultLeaveFunctors( void )
{
    return _defaultLeaveFunctors;
}

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

