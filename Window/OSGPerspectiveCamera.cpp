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
#include <math.h>

#include "OSGConfig.h"

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

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PerspectiveCamera
    \ingroup Cameras

A perspective camera with a symmetric frustum.      

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char PerspectiveCamera::cvsid[] = "@(#)$Id: $";

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

void PerspectiveCamera::initMethod (void)
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

PerspectiveCamera::PerspectiveCamera(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

PerspectiveCamera::PerspectiveCamera(const PerspectiveCamera &source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

PerspectiveCamera::~PerspectiveCamera(void)
{
}


/** \brief react to field changes
 */

void PerspectiveCamera::changed(BitVector, UInt32)
{
}

/*-------------------------- your_category---------------------------------*/

void PerspectiveCamera::draw(      DrawAction *OSG_CHECK_ARG(action), 
                             const Viewport&   OSG_CHECK_ARG(port  ))
{
}

void PerspectiveCamera::getProjection( Matrix& result, 
    UInt32 width, UInt32 height )
{
    Real32 fov = getFov();

    if(fov < 0)
    {
        result.setIdentity();
        return;
    }
    
    // try to be nice to people giving degrees...
    if ( fov > Pi )
        fov = osgdegree2rad( fov );

    MatrixPerspective( result, fov / 2, 
            width / (float) height, 
            getNear(), getFar() );
}
    

/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */

void PerspectiveCamera::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                             const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump PerspectiveCamera NI" << endl;
}

    

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

