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


// special cases, mostly conversions between dimensions

// Colors: Unsigned byte needs to be mapped to [0..1]

// Color3ub

template<>
inline Color3f
GeoProperty<GeoColor3ubPropertyDesc>::getValue( const UInt32 index ) 
{
	const Color3ub &val = _field.getValue( index );
	return Color3f( val.red()/255., val.green()/255., val.blue()/255. );
}

template<>
inline Color3f
GeoProperty<GeoColor3ubPropertyDesc>::getValue( const UInt32 index ) const
{
	const Color3ub &val = _field.getValue( index );
	return Color3f( val.red()/255., val.green()/255., val.blue()/255. );
}

template<>
inline void
GeoProperty<GeoColor3ubPropertyDesc>::getValue( 
	Color3f & res, 
	const UInt32 index ) 
{
	const Color3ub &val = _field.getValue( index );
	res.setValuesRGB( val.red()/255., val.green()/255., val.blue()/255. );
}

template<>
inline void
GeoProperty<GeoColor3ubPropertyDesc>::getValue( 
	Color3f & res, 
	const UInt32 index ) const
{
	const Color3ub &val = _field.getValue( index );
	res.setValuesRGB( val.red()/255., val.green()/255., val.blue()/255. );
}

template<>
inline void
GeoProperty<GeoColor3ubPropertyDesc>::setValue( const Color3f & val,
	const UInt32 index ) 
{
	_field.setValue( 
			Color3ub( val.red() * 255., val.green() * 255., val.blue() * 255.), 
			index );
}

template<>
inline void
GeoProperty<GeoColor3ubPropertyDesc>::addValue( const Color3f & val ) 
{
	_field.addValue( 
			Color3ub( val.red() * 255., val.green() * 255., val.blue() * 255.) 
			);
}


// Color4ub

template<>
inline Color3f
GeoProperty<GeoColor4ubPropertyDesc>::getValue( const UInt32 index ) 
{
	const Color4ub &val = _field.getValue( index );
	return Color3f( val.red()/255., val.green()/255., val.blue()/255. );
}

template<>
inline Color3f
GeoProperty<GeoColor4ubPropertyDesc>::getValue( const UInt32 index ) const
{
	const Color4ub &val = _field.getValue( index );
	return Color3f( val.red()/255., val.green()/255., val.blue()/255. );
}

template<>
inline void
GeoProperty<GeoColor4ubPropertyDesc>::getValue( 
	Color3f & res, 
	const UInt32 index ) 
{
	const Color4ub &val = _field.getValue( index );
	res.setValuesRGB( val.red()/255., val.green()/255., val.blue()/255. );
}

template<>
inline void
GeoProperty<GeoColor4ubPropertyDesc>::getValue( 
	Color3f & res, 
	const UInt32 index ) const
{
	const Color4ub &val = _field.getValue( index );
	res.setValuesRGB( val.red()/255., val.green()/255., val.blue()/255. );
}

template<>
inline void
GeoProperty<GeoColor4ubPropertyDesc>::setValue( const Color3f & val,
	const UInt32 index ) 
{
	_field.setValue( 
			Color4ub( val.red() * 255., val.green() * 255., val.blue() * 255., 255), 
			index );
}

template<>
inline void
GeoProperty<GeoColor4ubPropertyDesc>::addValue( const Color3f & val ) 
{
	_field.addValue( 
			Color4ub( val.red() * 255., val.green() * 255., val.blue() * 255., 255) 
			);
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

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/


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

