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

char CameraDecorator::cvsid[] = "@(#)$Id: OSGCameraDecorator.cpp,v 1.6 2002/01/18 03:09:20 dirk Exp $";

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

void CameraDecorator::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                           const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump CameraDecorator NI" << endl;
}


/*--------------------------- decoration --------------------------------*/



SFNodePtr *CameraDecorator::getSFBeacon(void)
{
    return getCamera()->getSFBeacon();
}

SFReal32 *CameraDecorator::getSFNear(void)
{
    return getCamera()->getSFNear();
}

SFReal32 *CameraDecorator::getSFFar(void)
{
    return getCamera()->getSFFar();
}


NodePtr &CameraDecorator::getBeacon(void)
{
    return getCamera()->getBeacon();
}

const NodePtr &CameraDecorator::getBeacon(void) const
{
    return getCamera()->getBeacon();
}

Real32 &CameraDecorator::getNear(void)
{
    return getCamera()->getNear();
}

const Real32 &CameraDecorator::getNear(void) const
{
    return getCamera()->getNear();
}

Real32 &CameraDecorator::getFar(void)
{
    return getCamera()->getFar();
}

const Real32 &CameraDecorator::getFar(void) const
{
    return getCamera()->getFar();
}


void CameraDecorator::setBeacon( const NodePtr &value )
{
    getCamera()->setBeacon(value);
}

void CameraDecorator::setNear( const Real32 &value )
{
    getCamera()->setNear(value);
}

void CameraDecorator::setFar( const Real32 &value )
{
    getCamera()->setFar(value);
}



/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

