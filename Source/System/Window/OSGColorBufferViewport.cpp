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
#include <OSGGL.h>

#include "OSGColorBufferViewport.h"

OSG_USING_NAMESPACE

/*! \class osg::ColorBufferViewport
    \ingroup GrpSystemWindowViewports

Viewport to only render to specific color channels, see \ref
PageSystemWindowViewports for a description.

The color channels used are defined by the _sfRed, _sfGreen, _sfBlue and
_sfAlpha Fields. 

*/

/*----------------------- constructors & destructors ----------------------*/

ColorBufferViewport::ColorBufferViewport(void) :
    Inherited()
{
}

ColorBufferViewport::ColorBufferViewport(const ColorBufferViewport &source) :
    Inherited(source)
{
}

ColorBufferViewport::~ColorBufferViewport(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ColorBufferViewport::initMethod (void)
{
}

void ColorBufferViewport::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void ColorBufferViewport::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump ColorBufferViewport NI" << std::endl;
}

void ColorBufferViewport::activateSize(void)
{
    Inherited::activateSize();
}

void ColorBufferViewport::activate(void)
{
    glColorMask(getRed(), getGreen(), getBlue(), getAlpha());
    Inherited::activate();
}

void ColorBufferViewport::deactivate(void)
{
    Inherited::deactivate();
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
}

void ColorBufferViewport::draw( DrawAction * action )
{
    Inherited::draw(action);
}

void ColorBufferViewport::render(RenderActionBase *action)
{
    Inherited::render(action);
}

/*------------------------------------------------------------------------*/
/*                              cvs id's                                  */

#ifdef OSG_SGI_CC
#pragma set woff 1174
#endif

#ifdef OSG_LINUX_ICC
#pragma warning( disable : 177 )
#endif

namespace
{
    static Char8 cvsid_cpp       [] = "@(#)$Id: $";
    static Char8 cvsid_hpp       [] = OSGCOLORBUFFERVIEWPORTBASE_HEADER_CVSID;
    static Char8 cvsid_inl       [] = OSGCOLORBUFFERVIEWPORTBASE_INLINE_CVSID;

    static Char8 cvsid_fields_hpp[] = OSGCOLORBUFFERVIEWPORTFIELDS_HEADER_CVSID;
}

#ifdef __sgi
#pragma reset woff 1174
#endif

