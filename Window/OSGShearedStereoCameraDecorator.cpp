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

#include <OSGMatrixUtility.h>

#include "OSGNodePtr.h"
#include "OSGPerspectiveCamera.h"
#include "OSGShearedStereoCameraDecorator.h"

OSG_USING_NAMESPACE

/*! \class osg::ShearedStereoCameraDecorator
The base class for stereo decorators. 	
*/

/*----------------------- constructors & destructors ----------------------*/

//! Constructor

ShearedStereoCameraDecorator::ShearedStereoCameraDecorator(void) :
    Inherited()
{
}

//! Copy Constructor

ShearedStereoCameraDecorator::ShearedStereoCameraDecorator(const ShearedStereoCameraDecorator &source) :
    Inherited(source)
{
}

//! Destructor

ShearedStereoCameraDecorator::~ShearedStereoCameraDecorator(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void ShearedStereoCameraDecorator::initMethod (void)
{
}

//! react to field changes

void ShearedStereoCameraDecorator::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

//! output the instance for debug purposes

void ShearedStereoCameraDecorator::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ShearedStereoCameraDecorator NI" << endl;
}


//! get the projection matrix

void ShearedStereoCameraDecorator::getProjection( Matrix &result, 
                                                  UInt32 width, UInt32 height)
{
    PerspectiveCameraPtr cam = PerspectiveCameraPtr::dcast(getDecoratee());
    
    if(cam == NullFC)
    {
        FFATAL(("ShearedStereoCameraDecorator::getProjection: can only"
                " decorate PerspectiveCameras!\n"));
        result.setIdentity();
        return;
    }
    
    Matrix trans;
    MatrixStereoPerspective(result, trans, cam->getFov(), 
                            width / (Real32) height, 
                            cam->getNear(), cam->getFar(),
                            getZeroParallaxDistance(),
                            getEyeSeparation(),
                            getLeftEye() ? 0.f : 1.f,
                            getOverlap());
    
    result.mult(trans);
}                                       


/*-------------------------------------------------------------------------*/
/*                              cvs id's                                   */

#ifdef __sgi
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id: OSGShearedStereoCameraDecorator.cpp,v 1.6 2002/08/07 04:04:14 vossg Exp $";
    static char cvsid_hpp[] = OSGSHEAREDSTEREOCAMERADECORATOR_HEADER_CVSID;
    static char cvsid_inl[] = OSGSHEAREDSTEREOCAMERADECORATOR_INLINE_CVSID;
}
