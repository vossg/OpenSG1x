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

void GrabForeground::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
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

    // If image is smaller than 2x2, resize it to vp size
    // the 2x2 is because you can't create 0x0 images
    if(i->getWidth() <= 1 || i->getHeight() <= 1)
    {
        i->set(i->getPixelFormat(), port->getPixelWidth(), 
                                    port->getPixelHeight());
    }
    
    UInt32 w = osgMin(i->getWidth(),  port->getPixelWidth());
    UInt32 h = osgMin(i->getHeight(), port->getPixelHeight());
    
    bool storeChanged = false;    
    if(i->getWidth() != port->getPixelWidth() )
    {
        glPixelStorei(GL_PACK_ROW_LENGTH, i->getWidth());
        storeChanged = true;
    }
    
    glReadPixels(port->getPixelLeft(), port->getPixelBottom(), 
                 w, h, i->getPixelFormat(),
                 GL_UNSIGNED_BYTE, i->getData());

    if(storeChanged)
        glPixelStorei(GL_PACK_ROW_LENGTH, 0);
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
    static char cvsid_cpp[] = "@(#)$Id: OSGGrabForeground.cpp,v 1.6 2002/06/30 05:04:24 vossg Exp $";
    static char cvsid_hpp[] = OSGGRABFOREGROUND_HEADER_CVSID;
    static char cvsid_inl[] = OSGGRABFOREGROUND_INLINE_CVSID;
}

