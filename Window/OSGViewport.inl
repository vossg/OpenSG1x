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

#include "OSGViewport.h"

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

OSG_FIELD_CONTAINER_INL_DEF(Viewport, ViewportPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */



/** \brief Destructor
 */


/*------------------------------ access -----------------------------------*/

inline BackgroundPtr Viewport::getBackground( void ) const
{
	return _background.getValue();
}

inline SFBackgroundPtr *Viewport::getSFBackground( void )
{
	return &_background;
}

inline NodePtr Viewport::getRoot( void ) const
{
	return _root.getValue();
}

inline SFNodePtr *Viewport::getSFRoot( void )
{
	return &_root;
}

inline CameraPtr Viewport::getCamera( void ) const
{
	return _camera.getValue();
}

inline SFCameraPtr *Viewport::getSFCamera( void )
{
	return &_camera;
}

inline WindowPtr Viewport::getParent( void ) const
{
	return _parent.getValue();
}

inline SFWindowPtr *Viewport::getSFParent( void )
{
	return &_parent;
}
	
inline void Viewport::setParent( const WindowPtr parent )
{
	_parent.setValue( parent );
}
	
inline void Viewport::setBackground( const BackgroundPtr bkgnd )
{
	_background.setValue( bkgnd );
}
	
inline void Viewport::setRoot( const NodePtr root )
{
	_root.setValue( root );
}
	
inline void Viewport::setCamera( const CameraPtr cam )
{
	_camera.setValue( cam );
}



inline Real32 Viewport::getLeft( void ) const
{
	return _left.getValue();
}

inline SFReal32 *Viewport::getSFLeft( void )
{
	return &_left;
}

inline void Viewport::setLeft( Real32 left )
{
	_left.setValue( left );
}

inline Real32 Viewport::getRight( void ) const
{
	return _right.getValue();
}

inline SFReal32 *Viewport::getSFRight( void )
{
	return &_right;
}

inline void Viewport::setRight( Real32 right )
{
	_right.setValue( right );
}

inline Real32 Viewport::getBottom( void ) const
{
	return _bottom.getValue();
}

inline SFReal32 *Viewport::getSFBottom( void )
{
	return &_bottom;
}

inline void Viewport::setBottom( Real32 bottom )
{
	_bottom.setValue( bottom );
}

inline Real32 Viewport::getTop( void ) const
{
	return _top.getValue();
}

inline SFReal32 *Viewport::getSFTop( void )
{
	return &_top;
}

inline void Viewport::setTop( Real32 top )
{
	_top.setValue( top );
}



inline Int32 Viewport::getPixelWidth( void ) const
{
	return getPixelRight() - getPixelLeft() + 1;
}

inline Int32 Viewport::getPixelHeight( void ) const
{
	return getPixelTop() - getPixelBottom() + 1;
}

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/


inline void Viewport::setSize( Real32 left, Real32 bottom, Real32 right, 
						Real32 top )
{
	_left.setValue( left );
	_right.setValue( right );
	_bottom.setValue( bottom );
	_top.setValue( top );
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

