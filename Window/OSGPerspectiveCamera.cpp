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
#include <math.h>

#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <OSGBaseTypes.h>
#include <OSGLog.h>
#include <OSGVector.h>
#include <OSGMatrix.h>
#include <OSGMatrixUtility.h>

#include "OSGViewport.h"
#include "OSGCamera.h"
#include "OSGWindow.h"
#include "OSGBackground.h"
#include "OSGPerspectiveCamera.h"

using namespace osg;

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char OSGPerspectiveCamera::cvsid[] = "@(#)$Id: $";

OSG_FC_FIRST_FIELD_IDM_DEF(OSGPerspectiveCamera, OSGDegreeField)
OSG_FC_LAST_FIELD_IDM_DEF (OSGPerspectiveCamera, OSGDegreeField)

// Static Class Varible implementations: 
OSGFieldDescription OSGPerspectiveCamera::_desc[] = 
{
       OSGFieldDescription(
           OSGSFReal32::getClassType(),
           "degrees", 
           OSG_FC_FIELD_IDM_DESC(OSGDegreeField),
           false,
           (OSGFieldAccessMethod) &OSGPerspectiveCamera::getSFDegrees),
};

OSGFieldContainerType OSGPerspectiveCamera::_type(
    "PerspectiveCamera", 
    "Camera", 
    0,
    (OSGPrototypeCreateF) &OSGPerspectiveCamera::createEmpty,
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

OSG_FIELD_CONTAINER_DEF(OSGPerspectiveCamera, OSGPerspectiveCameraPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

OSGPerspectiveCamera::OSGPerspectiveCamera(void) :
	Inherited(), _degrees( 60 )
{
}

OSGPerspectiveCamera::OSGPerspectiveCamera( const OSGPerspectiveCamera& source) :
	Inherited(), _degrees( source.getDegrees() )
{
}

/** \brief Destructor
 */

OSGPerspectiveCamera::~OSGPerspectiveCamera(void)
{
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

void OSGPerspectiveCamera::draw( OSGDrawAction * action, OSGViewport * port )
{
}

void OSGPerspectiveCamera::getProjection( OSGMatrix& result, 
	OSGViewport * port )
{
	OSGMatrixPerspective( result, getDegrees() / 2, 
			port->getPixelWidth() / (float) port->getPixelHeight(), 
			getNear(), getFar() );
}
	

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

/*-------------------------- comparison -----------------------------------*/

/*------------------------------- dump ----------------------------------*/

void OSGPerspectiveCamera::dump(void) const
{
    SDEBUG << "Dump OSGPerspectiveCamera NI" << endl;
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

