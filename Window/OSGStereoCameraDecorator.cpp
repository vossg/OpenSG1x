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

#include "OSGNodePtr.h"
#include "OSGStereoCameraDecorator.h"

OSG_USING_NAMESPACE

/*! \class osg::StereoCameraDecorator
The base class for stereo decorators. 
*/

/*----------------------- constructors & destructors ----------------------*/

//! Constructor

StereoCameraDecorator::StereoCameraDecorator(void) :
    Inherited()
{
}

//! Copy Constructor

StereoCameraDecorator::StereoCameraDecorator(const StereoCameraDecorator &source) :
    Inherited(source)
{
}

//! Destructor

StereoCameraDecorator::~StereoCameraDecorator(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void StereoCameraDecorator::initMethod (void)
{
}

//! react to field changes

void StereoCameraDecorator::changed(BitVector, UInt32)
{
}

//! output the instance for debug purposes

void StereoCameraDecorator::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump StereoCameraDecorator NI" << std::endl;
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
    static char cvsid_cpp[] = "@(#)$Id: OSGStereoCameraDecorator.cpp,v 1.5 2002/09/02 07:05:15 vossg Exp $";
    static char cvsid_hpp[] = OSGSTEREOCAMERADECORATOR_HEADER_CVSID;
    static char cvsid_inl[] = OSGSTEREOCAMERADECORATOR_INLINE_CVSID;
}
