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
#include <math.h>

#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#define OSG_COMPILEWINDOW
#define OSG_COMPILEPERSPEKTIVECAMERAINST

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

OSG_BEGIN_NAMESPACE

#if defined(__sgi)

#pragma instantiate SField<PerspectiveCameraPtr>::_fieldType
#pragma instantiate MField<PerspectiveCameraPtr>::_fieldType

#else

OSG_DLLEXPORT_DEF1(SField, PerspectiveCameraPtr, OSG_WINDOW_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, PerspectiveCameraPtr, OSG_WINDOW_DLLTMPLMAPPING)

#endif

OSG_END_NAMESPACE

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char PerspectiveCamera::cvsid[] = "@(#)$Id: $";

OSG_FC_FIRST_FIELD_IDM_DEF(PerspectiveCamera, DegreeField)
OSG_FC_LAST_FIELD_IDM_DEF (PerspectiveCamera, DegreeField)

// Static Class Varible implementations: 
FieldDescription PerspectiveCamera::_desc[] = 
{
       FieldDescription(
           SFReal32::getClassType(),
           "degrees", 
           OSG_FC_FIELD_IDM_DESC(DegreeField),
           false,
           (FieldAccessMethod) &PerspectiveCamera::getSFDegrees),
};

FieldContainerType PerspectiveCamera::_type(
    "PerspectiveCamera", 
    "Camera", 
    0,
    (PrototypeCreateF) &PerspectiveCamera::createEmpty,
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

OSG_FIELD_CONTAINER_DEF(PerspectiveCamera, PerspectiveCameraPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

PerspectiveCamera::PerspectiveCamera(void) :
	Inherited(), _degrees( 60 )
{
}

PerspectiveCamera::PerspectiveCamera( const PerspectiveCamera& source) :
	Inherited(), _degrees( source.getDegrees() )
{
}

/** \brief Destructor
 */

PerspectiveCamera::~PerspectiveCamera(void)
{
}

/*------------------------------ access -----------------------------------*/

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

void PerspectiveCamera::draw( DrawAction * action, const Viewport& port )
{
}

void PerspectiveCamera::getProjection( Matrix& result, 
	const Viewport& port )
{
	MatrixPerspective( result, getDegrees() / 2, 
			port.getPixelWidth() / (float) port.getPixelHeight(), 
			getNear(), getFar() );
}
	

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

/*-------------------------- comparison -----------------------------------*/

/*------------------------------- dump ----------------------------------*/

void PerspectiveCamera::dump(      UInt32     uiIndent, 
                             const BitVector &bvFlags) const
{
    SDEBUG << "Dump PerspectiveCamera NI" << endl;
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

