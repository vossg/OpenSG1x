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


#define OSG_COMPILESYSTEMLIB

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>

#include "OSGCameraDecorator.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::CameraDecorator

The base class for the camera.

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char CameraDecorator::cvsid[] = "@(#)$Id: OSGCameraDecorator.cpp,v 1.2 2001/08/07 17:22:17 dirk Exp $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

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

/** \brief initialize the static features of the class, e.g. action callbacks
 */

void CameraDecorator::initMethod (void)
{
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

CameraDecorator::CameraDecorator(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

CameraDecorator::CameraDecorator(const CameraDecorator &source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

CameraDecorator::~CameraDecorator(void)
{
}


/** \brief react to field changes
 */

void CameraDecorator::changed(BitVector, ChangeMode)
{
}


/** get the separate elements needed for rendering */
// this is simple, just copying data

void CameraDecorator::getProjection( Matrix& result, UInt32 width, 
    	    	    	    	    UInt32 height )
{
	getCamera()->getProjection( result, width, height );
}

void CameraDecorator::getProjectionTranslation( Matrix& result, UInt32 width, 
    	    	    	    	    UInt32 height )
{
	getCamera()->getProjectionTranslation( result, width, height );
}

void CameraDecorator::getViewing( Matrix& result, UInt32 width, UInt32 height )
{
	getCamera()->getViewing( result, width, height );
}


/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */

void CameraDecorator::dump(      UInt32     uiIndent, 
                         const BitVector &bvFlags) const
{
	SLOG << "Dump CameraDecorator NI" << endl;
}

    

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

