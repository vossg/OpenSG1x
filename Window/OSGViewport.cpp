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

#include <OSGConfig.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <GL/gl.h>

#include <OSGField.h>
#include <OSGFieldContainer.h>
#include <OSGAction.h>
#include <OSGDrawAction.h>
#include "OSGBackground.h"
#include "OSGViewport.h"
#include "OSGWindow.h"
#include "OSGCamera.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char OSGViewport::cvsid[] = "@(#)$Id: $";

OSG_FC_FIRST_FIELD_IDM_DEF(OSGViewport, OSGLeftField)

OSG_FC_FIELD_IDM_DEF      (OSGViewport, OSGRightField,      OSGLeftField  )
OSG_FC_FIELD_IDM_DEF      (OSGViewport, OSGBottomField,     OSGRightField )
OSG_FC_FIELD_IDM_DEF      (OSGViewport, OSGTopField,        OSGBottomField)
OSG_FC_FIELD_IDM_DEF      (OSGViewport, OSGParentField,     OSGTopField   )
OSG_FC_FIELD_IDM_DEF      (OSGViewport, OSGCameraField,     OSGParentField)
OSG_FC_FIELD_IDM_DEF      (OSGViewport, OSGRootField,       OSGCameraField)
OSG_FC_FIELD_IDM_DEF      (OSGViewport, OSGBackgroundField, OSGRootField  )

OSG_FC_LAST_FIELD_IDM_DEF (OSGViewport, OSGBackgroundField)

// Static Class Varible implementations: 
OSGFieldDescription OSGViewport::_desc[] = 
{
        OSGFieldDescription(
            OSGSFReal32::getClassType(), 
            "left", 
            OSG_FC_FIELD_IDM_DESC(OSGLeftField),
            false,
            (OSGFieldAccessMethod) &OSGViewport::getSFLeft),

        OSGFieldDescription(
            OSGSFReal32::getClassType(), 
            "right", 
            OSG_FC_FIELD_IDM_DESC(OSGRightField),
            false,           
            (OSGFieldAccessMethod) &OSGViewport::getSFRight),

        OSGFieldDescription(
            OSGSFReal32::getClassType(), 
            "bottom", 
            OSG_FC_FIELD_IDM_DESC(OSGBottomField),
            false,
            (OSGFieldAccessMethod) &OSGViewport::getSFBottom),

        OSGFieldDescription(
            OSGSFReal32::getClassType(), 
            "top", 
            OSG_FC_FIELD_IDM_DESC(OSGTopField),
            false,
            (OSGFieldAccessMethod) &OSGViewport::getSFTop),

        OSGFieldDescription(
            OSGSFWindowPtr::getClassType(), 
            "parent", 
            OSG_FC_FIELD_IDM_DESC(OSGParentField),
            false,
            (OSGFieldAccessMethod) &OSGViewport::getSFParent),

        OSGFieldDescription(
            OSGSFCameraPtr::getClassType(), 
            "camera", 
            OSG_FC_FIELD_IDM_DESC(OSGCameraField),
            false,
            (OSGFieldAccessMethod) &OSGViewport::getSFCamera),

        OSGFieldDescription(
            OSGSFNodePtr::getClassType(), 
            "root", 
            OSG_FC_FIELD_IDM_DESC(OSGRootField),
            false,
            (OSGFieldAccessMethod) &OSGViewport::getSFRoot),

        OSGFieldDescription(
            OSGSFBackgroundPtr::getClassType(), 
            "background", 
            OSG_FC_FIELD_IDM_DESC(OSGBackgroundField),
            false,
            (OSGFieldAccessMethod) &OSGViewport::getSFBackground),
};

OSGFieldContainerType OSGViewport::_type(
    "Viewport", 
    "FieldContainer", 
    0,
    (OSGPrototypeCreateF) &OSGViewport::createEmpty,
    0,
    _desc, 
    sizeof(_desc));

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

OSG_FIELD_CONTAINER_DEF(OSGViewport, OSGViewportPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

OSGViewport::OSGViewport(void) :
	Inherited(), _left(0), _right(1), _bottom(0), _top(1), 
	_camera(), _root(), _background(), _parent()
{
}

OSGViewport::OSGViewport( const OSGViewport& source) :
	Inherited(), _left(source.getLeft()), _right(source.getRight()), 
	_bottom(source.getBottom()), _top(source.getTop()), 
	_camera(source.getCamera()), _root(source.getRoot()), 
	_background(source.getBackground()), _parent(source.getParent())
{
}

/** \brief Destructor
 */

OSGViewport::~OSGViewport(void)
{
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/


OSGInt32 OSGViewport::getPixelLeft( void )
{
	if ( getLeft() > 1 )
		return getLeft();

	return getParent()->getWidth() * getLeft();
}

OSGInt32 OSGViewport::getPixelRight( void )
{
	if ( getRight() > 1 )
		return getRight();

	return getParent()->getWidth() * getRight() - 1;
}

OSGInt32 OSGViewport::getPixelBottom( void )
{
	if ( getBottom() > 1 )
		return getBottom();

	return getParent()->getHeight() * getBottom();
}

OSGInt32 OSGViewport::getPixelTop( void )
{
	if ( getTop() > 1 )
		return getTop();

	return getParent()->getHeight() * getTop() - 1;
}

OSGBool OSGViewport::isFullWindow( void )
{
	return	getPixelBottom() == 0 &&
			getPixelLeft()   == 0 &&
			getPixelTop()    == getParent()->getHeight() - 1 &&
			getPixelRight()  == getParent()->getWidth() - 1;
}

/*-------------------------- your_category---------------------------------*/

void OSGViewport::draw( OSGDrawAction * action )
{
	if ( getCamera() == OSGNullNode )
	{
		SWARNING << "OSGViewport::draw: no camera!" << endl;
		return;
	}
	if ( getBackground() == OSGNullNode )
	{
		SWARNING << "OSGViewport::draw: no background!" << endl;
		return;
	}
	if ( getRoot() == OSGNullNode )
	{
		SWARNING << "OSGViewport::draw: no root!" << endl;
		return;
	}

	GLint pl=getPixelLeft(), pr=getPixelRight(), pb=getPixelBottom(), 
		  pt=getPixelTop();
	GLint pw=pr-pl,ph=pt-pb;
	OSGBool full = isFullWindow();

	glViewport( pl, pb, pw, ph );
	glScissor( pl, pb, pw, ph );
	
	if ( ! full )
		glEnable( GL_SCISSOR_TEST );

	action->setCamera( getCamera().getCPtr() );
	action->setBackground( getBackground().getCPtr() );
	
	getCamera()->setup( action, this );
	getBackground()->clear( action, this );

	action->apply( getRoot() );

	if ( ! full )
		glDisable( GL_SCISSOR_TEST );
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

OSGViewport& OSGViewport::operator = (const OSGViewport &source)
{
	if (this == &source)
		return *this;

	// copy parts inherited from parent
	//*(static_cast<Inherited *>(this)) = source;

	// free mem alloced by members of 'this'

	// alloc new mem for members

	// copy 
}

/*-------------------------- comparison -----------------------------------*/

/*------------------------------- dump ----------------------------------*/

void OSGViewport::dump(void) const
{
    SDEBUG << "Dump OSGViewport NI" << endl;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


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

