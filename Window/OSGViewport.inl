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

OSG_FIELD_CONTAINER_INL_DEF(OSGViewport, OSGViewportPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */



/** \brief Destructor
 */


/*------------------------------ access -----------------------------------*/

inline OSGBackgroundPtr OSGViewport::getBackground( void ) const
{
	return _background.getValue();
}

inline OSGSFBackgroundPtr *OSGViewport::getSFBackground( void )
{
	return &_background;
}

inline OSGNodePtr OSGViewport::getRoot( void ) const
{
	return _root.getValue();
}

inline OSGSFNodePtr *OSGViewport::getSFRoot( void )
{
	return &_root;
}

inline OSGCameraPtr OSGViewport::getCamera( void ) const
{
	return _camera.getValue();
}

inline OSGSFCameraPtr *OSGViewport::getSFCamera( void )
{
	return &_camera;
}

inline OSGWindowPtr OSGViewport::getParent( void ) const
{
	return _parent.getValue();
}

inline OSGSFWindowPtr *OSGViewport::getSFParent( void )
{
	return &_parent;
}
	
inline void OSGViewport::setParent( const OSGWindowPtr parent )
{
	_parent.setValue( parent );
}
	
inline void OSGViewport::setBackground( const OSGBackgroundPtr bkgnd )
{
	_background.setValue( bkgnd );
}
	
inline void OSGViewport::setRoot( const OSGNodePtr root )
{
	_root.setValue( root );
}
	
inline void OSGViewport::setCamera( const OSGCameraPtr cam )
{
	_camera.setValue( cam );
}



inline OSGReal32 OSGViewport::getLeft( void ) const
{
	return _left.getValue();
}

inline OSGSFReal32 *OSGViewport::getSFLeft( void )
{
	return &_left;
}

inline void OSGViewport::setLeft( OSGReal32 left )
{
	_left.setValue( left );
}

inline OSGReal32 OSGViewport::getRight( void ) const
{
	return _right.getValue();
}

inline OSGSFReal32 *OSGViewport::getSFRight( void )
{
	return &_right;
}

inline void OSGViewport::setRight( OSGReal32 right )
{
	_right.setValue( right );
}

inline OSGReal32 OSGViewport::getBottom( void ) const
{
	return _bottom.getValue();
}

inline OSGSFReal32 *OSGViewport::getSFBottom( void )
{
	return &_bottom;
}

inline void OSGViewport::setBottom( OSGReal32 bottom )
{
	_bottom.setValue( bottom );
}

inline OSGReal32 OSGViewport::getTop( void ) const
{
	return _top.getValue();
}

inline OSGSFReal32 *OSGViewport::getSFTop( void )
{
	return &_top;
}

inline void OSGViewport::setTop( OSGReal32 top )
{
	_top.setValue( top );
}



inline OSGInt32 OSGViewport::getPixelWidth( void )
{
	return getPixelRight() - getPixelLeft() + 1;
}

inline OSGInt32 OSGViewport::getPixelHeight( void )
{
	return getPixelTop() - getPixelBottom() + 1;
}

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/


inline void OSGViewport::setSize( OSGReal32 left, OSGReal32 bottom, OSGReal32 right, 
						OSGReal32 top )
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

