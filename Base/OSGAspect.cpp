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

#define OSG_COMPILEBASE

#include "OSGAspect.h"
#include "OSGThreadManager.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char Aspect::cvsid[] = "@(#)$Id: $";

vector<Aspect *> Aspect::_aspectV(ThreadManager::getNumAspects());

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/



/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

bool Aspect::init(void)
{
    for(UInt32 i = 0; i < ThreadManager::getNumAspects(); i++)
    {
        _aspectV[i] = new Aspect(i);
    }

    return true;
}

bool Aspect::exit(void)
{
    for(UInt32 i = 0; i < ThreadManager::getNumAspects(); i++)
    {
        delete _aspectV[i];
    }

    return true;
}

void Aspect::moveList(ChangeList *listP, 
                      UInt32      fromAspect,
                      UInt32      toAspect)
{
    if(listP != NULL)
    {
        _aspectV[toAspect]  ->_changeListS.insert(listP);
        _aspectV[fromAspect]->_changeListS.erase (listP);
    }

}

void Aspect::addList(ChangeList *listP,
                     UInt32      aspectId)
{
    if(listP != NULL)
    {
        _aspectV[aspectId]->_changeListS.insert(listP);
    }
}

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/



/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

#if 0
CLASSNAME& CLASSNAME::operator = (const CLASSNAME &source)
{
	if (this == &source)
		return *this;

	// copy parts inherited from parent
	*(static_cast<Inherited *>(this)) = source;

	// free mem alloced by members of 'this'

	// alloc new mem for members

	// copy 
}

/*-------------------------- comparison -----------------------------------*/

/** \brief assignment
 */

Bool CLASSNAME::operator < (const CLASSNAME &other) const
{
    return this < &other;
}

/** \brief equal
 */

Bool CLASSNAME::operator == (const CLASSNAME &other) const
{
}

/** \brief unequal
 */

Bool CLASSNAME::operator != (const CLASSNAME &other) const
{
	return ! (*this == other);
}

#endif

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

Aspect::Aspect(UInt32 aspectId) :
    _aspectId(aspectId),
    _changeListS()
{
}

/** \brief Destructor
 */

Aspect::~Aspect(void)
{
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

