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
#include "OSGLog.h"

#include <GL/gl.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include "OSGNode.h"
#include "OSGFieldContainerPtr.h"
#include "OSGCamera.h"

/** \enum VecBase::VectorSizeE
 *  \brief 
 */

/** \var VecBase::VectorSizeE VecBase::_iSize
 * 
 */

/** \fn const char *VecBase::getClassname(void)
 *  \brief Classname
 */

/** \var ValueTypeT VecBase::_values[iSize];
 *  \brief Value store
 */

using namespace osg;

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char Camera::cvsid[] = "@(#)$Id: $";

OSG_FC_FIRST_FIELD_IDM_DEF(Camera, BeaconField)

OSG_FC_FIELD_IDM_DEF      (Camera, NearField, BeaconField)
OSG_FC_FIELD_IDM_DEF      (Camera, FarField,  NearField)

OSG_FC_LAST_FIELD_IDM_DEF (Camera, FarField)

// Static Class Varible implementations: 
FieldDescription Camera::_desc[] = 
{
        FieldDescription(SFNodePtr::getClassType(), 
                            "beacon", 
                            OSG_FC_FIELD_IDM_DESC(BeaconField),
                            false,
                            (FieldAccessMethod) &Camera::getSFBeacon),
        
        FieldDescription(SFReal32::getClassType(),
                            "near", 
                            OSG_FC_FIELD_IDM_DESC(NearField),
                            false,
                            (FieldAccessMethod) &Camera::getSFNear),
        
        FieldDescription(SFReal32::getClassType(),
                            "far", 
                            OSG_FC_FIELD_IDM_DESC(FarField),
                            false,
                            (FieldAccessMethod) &Camera::getSFFar),
};

FieldContainerType Camera::_type(
    "Camera", 
    "FieldContainer", 
    0,
    (PrototypeCreateF) &Camera::createEmpty,
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

OSG_FIELD_CONTAINER_DEF(Camera, CameraPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

Camera::Camera(void) :
	Inherited(), _beacon(), _near(0), _far(0)
{
}

Camera::Camera(const Camera &source) :
	Inherited(), _beacon(source.getBeacon()), _near(source.getNear()), 
	_far(source.getFar())
{
}

/** \brief Destructor
 */

Camera::~Camera(void)
{
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/
	

/*-------------------------- your_category---------------------------------*/

/** setup the GL for rendering and tell the Action what it needs to know */

void Camera::setup( DrawAction * action, Viewport * port )
{
	Matrix m;

	// set the projection

	getProjection( m, port );

	//SDEBUG << "Projection matrix: " << m << endl;

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glLoadMatrixf( m.getValues() );
	
	// set the viewing

	getViewing( m, port );

	//SDEBUG << "Viewing matrix: " << m << endl;
	
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glLoadMatrixf( m.getValues() );
}

/** draw the camera's geometry (if any). Usually there is none. */
void Camera::draw( DrawAction * action, Viewport * port )
{
}

/** get the separate elements needed for rendering */

void Camera::getProjection( Matrix& result, Viewport * port )
{
	SFATAL << "Camera::getProjection: NIY" << endl;
	abort();
}

void Camera::getProjectionTranslation( Matrix& result, Viewport * port )
{
	result.setIdentity();
}

void Camera::getViewing( Matrix& result, Viewport * port )
{
	if ( getBeacon() == NullNode )
	{
		SWARNING << "Camera::setup: no beacon!" << endl;
		return;
	}	

	getBeacon()->getToWorld( result );	
	result.invert();
}

void Camera::getFrustum( FrustumVolume& result, Viewport * port )
{
	SFATAL << "Camera::getFrustum: NIY" << endl;
	abort();
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

Camera& Camera::operator = (const Camera &source)
{
	if (this == &source)
		return *this;

	// copy parts inherited from parent
	// *(static_cast<Inherited *>(this)) = source;

	// free mem alloced by members of 'this'

	// alloc new mem for members

	// copy 

    return *this;
}

/*-------------------------- comparison -----------------------------------*/

/*------------------------------- dump ----------------------------------*/

void Camera::dump(void) const
{
    SDEBUG << "Dump Camera NI" << endl;
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

