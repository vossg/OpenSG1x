/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000,2001 by the OpenSG Forum                   *
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

#define OSG_COMPILEXXXX

#include <stdlib.h>
#include <stdio.h>

#include "OSGConfig.h"

#include "CLASSNAME.h"

OSG_USING_NAMESPACE

namespace 
{
    char cvsid_cpp[] = "@(#)$Id: $";
    char cvsid_hpp[] = OSG_HEADER_CVSID;
    char cvsid_inl[] = OSG_INLINE_CVSID;
}

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

char CLASSNAME::cvsid[] = "@(#)$Id: $";

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

CLASSNAME::CLASSNAME(void) :
	Inherited(),
	  // TODO: initialize members
{
}


//CLASSNAME::CLASSNAME(const CLASSNAME &source) :
//	Inherited(source),
//	  // TODO: initialize members
//{
//}

/** \brief Destructor
 */

CLASSNAME::~CLASSNAME(void)
{
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

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

OSGBool CLASSNAME::operator < (const CLASSNAME &other) const
{
    return this < &other;
}

/** \brief equal
 */

OSGBool CLASSNAME::operator == (const CLASSNAME &other) const
{
}

/** \brief unequal
 */

OSGBool CLASSNAME::operator != (const CLASSNAME &other) const
{
	return ! (*this == other);
}


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/


