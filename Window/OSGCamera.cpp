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

using namespace osg;

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char OSGCamera::cvsid[] = "@(#)$Id: $";

OSG_FC_FIRST_FIELD_IDM_DEF(OSGCamera, OSGBeaconField)

OSG_FC_FIELD_IDM_DEF      (OSGCamera, OSGNearField, OSGBeaconField)
OSG_FC_FIELD_IDM_DEF      (OSGCamera, OSGFarField,  OSGNearField)

OSG_FC_LAST_FIELD_IDM_DEF (OSGCamera, OSGFarField)

// Static Class Varible implementations: 
OSGFieldDescription OSGCamera::_desc[] = 
{
        OSGFieldDescription(OSGSFNodePtr::getClassType(), 
                            "beacon", 
                            OSG_FC_FIELD_IDM_DESC(OSGBeaconField),
                            false,
                            (OSGFieldAccessMethod) &OSGCamera::getSFBeacon),
        
        OSGFieldDescription(OSGSFReal32::getClassType(),
                            "near", 
                            OSG_FC_FIELD_IDM_DESC(OSGNearField),
                            false,
                            (OSGFieldAccessMethod) &OSGCamera::getSFNear),
        
        OSGFieldDescription(OSGSFReal32::getClassType(),
                            "far", 
                            OSG_FC_FIELD_IDM_DESC(OSGFarField),
                            false,
                            (OSGFieldAccessMethod) &OSGCamera::getSFFar),
};

OSGFieldContainerType OSGCamera::_type(
    "Camera", 
    "FieldContainer", 
    0,
    (OSGPrototypeCreateF) &OSGCamera::createEmpty,
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

OSG_FIELD_CONTAINER_DEF(OSGCamera, OSGCameraPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

OSGCamera::OSGCamera(void) :
	Inherited(), _beacon(), _near(0), _far(0)
{
}

OSGCamera::OSGCamera(const OSGCamera &source) :
	Inherited(), _beacon(source.getBeacon()), _near(source.getNear()), 
	_far(source.getFar())
{
}

/** \brief Destructor
 */

OSGCamera::~OSGCamera(void)
{
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/
	

/*-------------------------- your_category---------------------------------*/

/** setup the GL for rendering and tell the Action what it needs to know */

void OSGCamera::setup( OSGDrawAction * action, OSGViewport * port )
{
	OSGMatrix m;

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
void OSGCamera::draw( OSGDrawAction * action, OSGViewport * port )
{
}

/** get the separate elements needed for rendering */

void OSGCamera::getProjection( OSGMatrix& result, OSGViewport * port )
{
	SFATAL << "OSGCamera::getProjection: NIY" << endl;
	abort();
}

void OSGCamera::getProjectionTranslation( OSGMatrix& result, OSGViewport * port )
{
	result.setIdentity();
}

void OSGCamera::getViewing( OSGMatrix& result, OSGViewport * port )
{
	if ( getBeacon() == OSGNullNode )
	{
		SWARNING << "OSGCamera::setup: no beacon!" << endl;
		return;
	}	

	getBeacon()->getToWorld( result );	
	result.invert();
}

void OSGCamera::getFrustum( OSGFrustumVolume& result, OSGViewport * port )
{
	SFATAL << "OSGCamera::getFrustum: NIY" << endl;
	abort();
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

OSGCamera& OSGCamera::operator = (const OSGCamera &source)
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

void OSGCamera::dump(void) const
{
    SDEBUG << "Dump OSGCamera NI" << endl;
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

