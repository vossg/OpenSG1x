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

#include <OSGGL.h>

#include <OSGViewport.h>

#include "OSGGrabForeground.h"

OSG_USING_NAMESPACE

#ifdef __sgi
#pragma set woff 1174
#endif

namespace
{
    static char cvsid_cpp[] = "@(#)$Id: OSGGrabForeground.cpp,v 1.2 2002/02/26 06:10:15 vossg Exp $";
    static char cvsid_hpp[] = OSGGRABFOREGROUND_HEADER_CVSID;
    static char cvsid_inl[] = OSGGRABFOREGROUND_INLINE_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

/*! \class osg::GrabForeground
Background is the base class for all background clearing.  	 	
*/

/*----------------------- constructors & destructors ----------------------*/

//! Constructor

GrabForeground::GrabForeground(void) :
    Inherited()
{
}

//! Copy Constructor

GrabForeground::GrabForeground(const GrabForeground &source) :
    Inherited(source)
{
}

//! Destructor

GrabForeground::~GrabForeground(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void GrabForeground::initMethod (void)
{
}

//! react to field changes

void GrabForeground::changed(BitVector, ChangeMode)
{
}

//! output the instance for debug purposes

void GrabForeground::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump GrabForeground NI" << endl;
}


/** \brief grab the image 
 */
    
void GrabForeground::draw(DrawActionBase *, Viewport *port)
{
    ImageP i = getImage();
    
    if(i == NULL)       // No image, no grab.
        return;
    
    if(i->getWidth()  != port->getPixelWidth() ||
       i->getHeight() != port->getPixelHeight() )
    {
        i->set(i->getPixelFormat(), port->getPixelWidth(), 
                                    port->getPixelHeight());
    }
    
    glReadPixels(0, 0, i->getWidth(), i->getHeight(), i->getPixelFormat(),
                 GL_UNSIGNED_BYTE, i->getData());
}

