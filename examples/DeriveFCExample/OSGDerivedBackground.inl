/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
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

/** Example class of an derived FieldContainer.
	Defines a background FieldContainer which contains 3 Fields 
	a single Field of Real32 (_real), an other single Field (_single) 
	and a multi Field (_multi).
*/

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


OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

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

/** inline definition of the FieldContainerPointer
*/ 
OSG_FIELD_CONTAINER_INL_DEF(DerivedBackground, DerivedBackgroundPtr)

/*------------- constructors & destructors --------------------------------*/

/*--------------------------- type information-----------------------------*/

/*------------------------------ access -----------------------------------*/

/** imlementation of the defined set- & get- functions
*/

	/** set a value of one of the included Fields
	*/
	inline void DerivedBackground::setReal(SFReal32 real)
	{
		_real = real;
	}

	inline void DerivedBackground::setSingle(SFValzeTypeT single)
	{
		_single = single;
	}

	inline void DerivedBackground::setMulti(MFValueTypeT multi)
	{
		_multi = multi;
	}


	/** get a value of one of the included Fields
	*/
	inline SFReal32 DerivedBackground::getReal( void )
	{
		return _real.getValue();
	}

	inline SFValueTypeT DerivedBackground::getSingle( void )
	{
		return _single.getValue();
	}

	inline MFValueTypeT DerivedBackground::getMulti( void )
	{
		return _multi.getValue();
	}

	/** get function for the Fields
	*/

	inline SFReal32 *DerivedBackground::getSFReal( void )
	{
		return &_real;
	}

	inline SFValueTypeT *DerivedBackground::getSFSingle( void )
	{
		return &_single;
	}

	inline MFValueTypeT *DerivedBackground::getMFMulti( void )
	{
		return &_multi;
	}

/*------------------------------- size ----------------------------------*/

/*------------------------------- dump ----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/*------------------------------ access -----------------------------------*/


OSG_END_NAMESPACE

