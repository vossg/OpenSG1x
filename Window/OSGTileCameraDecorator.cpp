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

#include "OSGTileCameraDecorator.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::TileCameraDecorator

The decorator to select a rectangular part of the image.

Left/Right/Bottom/Top define the part to scale up. All ar etaken from (0..1).

Note: Pixel-based backgrounds will not work here, as they use the viewport
for definition, which doesn't change.

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char TileCameraDecorator::cvsid[] = "@(#)$Id: OSGTileCameraDecorator.cpp,v 1.10 2002/06/30 05:04:24 vossg Exp $";

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

void TileCameraDecorator::initMethod (void)
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

TileCameraDecorator::TileCameraDecorator(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

TileCameraDecorator::TileCameraDecorator(const TileCameraDecorator &source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

TileCameraDecorator::~TileCameraDecorator(void)
{
}


/** \brief react to field changes
 */

void TileCameraDecorator::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}


void TileCameraDecorator::setSize( Real32 left, Real32 bottom, Real32 right, 
                        Real32 top )
{
    _sfLeft.setValue( left );
    _sfRight.setValue( right );
    _sfBottom.setValue( bottom );
    _sfTop.setValue( top );
}


/** get the separate elements needed for rendering */

void TileCameraDecorator::getProjection( Matrix &result, 
                                         UInt32 width, UInt32 height)
{
    getDecoratee()->getProjection( result, 
                  ( getFullWidth()  == 0 )? width  : getFullWidth(), 
                  ( getFullHeight() == 0 )? height : getFullHeight() );
    
    // scale the wanted part from the projection matrix
    Real32  xs = 1.f / ( getRight() - getLeft() ),
            ys = 1.f / ( getTop() - getBottom() );
    Matrix sm(  xs, 0, 0, -(getLeft()*2-1)*xs-1,  
                0, ys, 0, -(getBottom()*2-1)*ys-1,  
                0, 0, 1, 0, 
                0, 0, 0, 1);
    
    result.multLeft( sm );
}                                       

/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */

void TileCameraDecorator::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                               const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump TileCameraDecorator NI" << endl;
}

    

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

