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

#include "OSGNodePtr.h"
#include "OSGStereoBufferViewport.h"

OSG_USING_NAMESPACE

/*! \class osg::StereoBufferViewport
A Viewport is a part of the Window it is attached to used for rendering. Every Window can hold an arbitrary number of viewports. 	 	
*/

/*----------------------- constructors & destructors ----------------------*/

//! Constructor

StereoBufferViewport::StereoBufferViewport(void) :
    Inherited()
{
}

//! Copy Constructor

StereoBufferViewport::StereoBufferViewport(const StereoBufferViewport &source) :
    Inherited(source)
{
}

//! Destructor

StereoBufferViewport::~StereoBufferViewport(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void StereoBufferViewport::initMethod (void)
{
}

//! react to field changes

void StereoBufferViewport::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

//! output the instance for debug purposes

void StereoBufferViewport::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump StereoBufferViewport NI" << std::endl;
}


void StereoBufferViewport::draw( DrawAction * action )
{
    if(getLeftBuffer())
    {
        if(getRightBuffer())
        {
            glDrawBuffer(GL_BACK);
        }
        else
        {
            glDrawBuffer(GL_BACK_LEFT);
        }
    }
    else
    {
        if(getRightBuffer())
        {
            glDrawBuffer(GL_BACK_RIGHT);
        }
        else
        {
            glDrawBuffer(GL_NONE);
        }
    }
    Inherited::draw(action);
    glDrawBuffer(GL_BACK);
}


void StereoBufferViewport::render( RenderAction * action )
{
    if(getLeftBuffer())
    {
        if(getRightBuffer())
        {
            glDrawBuffer(GL_BACK);
        }
        else
        {
            glDrawBuffer(GL_BACK_LEFT);
        }
    }
    else
    {
        if(getRightBuffer())
        {
            glDrawBuffer(GL_BACK_RIGHT);
        }
        else
        {
            glDrawBuffer(GL_NONE);
        }
    }
    Inherited::render(action);
    glDrawBuffer(GL_BACK);
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
    static char cvsid_cpp[] = "@(#)$Id: OSGStereoBufferViewport.cpp,v 1.7 2002/09/02 07:05:15 vossg Exp $";
    static char cvsid_hpp[] = OSGSTEREOBUFFERVIEWPORT_HEADER_CVSID;
    static char cvsid_inl[] = OSGSTEREOBUFFERVIEWPORT_INLINE_CVSID;
}
