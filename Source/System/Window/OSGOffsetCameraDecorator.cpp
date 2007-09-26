/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#include "OSGNodePtr.h"
#include "OSGOffsetCameraDecorator.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::OffsetCameraDecorator
    \ingroup GrpSystemWindowCameraDecorators

The osg::OffsetCameraDecorator for selecting only a part of a virtual large image, see \ref
PageSystemWindowCameraDecoratorsTile for a description.

The borders of the tile are defined by the _sfLeft, _sfRight, _sfBottom and
_sfTop Fields. The size of the full image is defined by the _sfFullWidth and
_sfFullHeight Fields.

*/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void OffsetCameraDecorator::initMethod (void)
{
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*------------- constructors & destructors --------------------------------*/

OffsetCameraDecorator::OffsetCameraDecorator(void) :
    Inherited()
{
}

OffsetCameraDecorator::OffsetCameraDecorator(const OffsetCameraDecorator &source) :
    Inherited(source)
{
}

OffsetCameraDecorator::~OffsetCameraDecorator(void)
{
}

void OffsetCameraDecorator::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void OffsetCameraDecorator::getProjection( Matrix &result, 
                                         UInt32 width, UInt32 height)
{
    if(width == 0 || height == 0)
    {
        result.setIdentity();
        return;
    }

    CameraPtr camera = getDecoratee();
    if(camera == NullFC)
    {
        FWARNING(("OffsetCameraDecorator::getProjection: no decoratee!\n"));
        result.setIdentity();
        return;
    }

    if(getFullWidth() != 0)
        width = getFullWidth();

    if(getFullHeight() != 0)
        height = getFullHeight();

    camera->getProjection(result, width, height);

    Real32 x = getOffsetX() / Real32(width);
    Real32 y = getOffsetY() / Real32(height);

    Matrix sm(  1, 0, 0, x,
                0, 1, 0, y,
                0, 0, 1, 0, 
                0, 0, 0, 1);

    result.multLeft(sm);
}

/*! Get/calculate the decoration matrix for this camera. The default is identity.
*/
void OffsetCameraDecorator::getDecoration(Matrix &result, 
										UInt32 width, UInt32 height)
{
    if(width == 0 || height == 0)
    {
        result.setIdentity();
        return;
    }

    CameraPtr camera = getDecoratee();
    if(camera == NullFC)
    {
        FWARNING(("OffsetCameraDecorator::getProjection: no decoratee!\n"));
        result.setIdentity();
        return;
    }

    if(getFullWidth() != 0)
        width = getFullWidth();
    
    if(getFullHeight() != 0)
        height = getFullHeight();
    
    // this is the only difference to getProjection()
    camera->getDecoration(result, width, height);

    Real32 x = getOffsetX() / Real32(width);
    Real32 y = getOffsetY() / Real32(height);

    Matrix sm(  1, 0, 0, x,
                0, 1, 0, y,
                0, 0, 1, 0, 
                0, 0, 0, 1);

    result.multLeft(sm);
}

/*------------------------------- dump ----------------------------------*/

void OffsetCameraDecorator::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                               const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump OffsetCameraDecorator NI" << std::endl;
}
