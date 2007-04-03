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
#include <OSGNodePtr.h>
#include <OSGCamera.h>
#include <OSGBackground.h>
#include <OSGForeground.h>
#include <OSGDrawAction.h>
#include <OSGRenderAction.h>
#include "OSGPassiveViewport.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::PassiveViewport
    \ingroup GrpSystemWindowViewports

A PassiveViewport is a basic Viewport for integration into other OpenGL
programs. See \ref PageSystemWindowViewports for a description.

*/

/*----------------------- constructors & destructors ----------------------*/

PassiveViewport::PassiveViewport(void) :
    Inherited()
{
}

PassiveViewport::PassiveViewport(const PassiveViewport &source) :
    Inherited(source)
{
}

PassiveViewport::~PassiveViewport(void)
{
}

/*----------------------------- class specific ----------------------------*/

void PassiveViewport::initMethod (void)
{
}

void PassiveViewport::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void PassiveViewport::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PassiveViewport NI" << std::endl;
}

void PassiveViewport::activateSize(void)
{
    GLint vp[4];
    glGetIntegerv(GL_VIEWPORT, vp);

    setLeft  (Real32(vp[0]));
    setBottom(Real32(vp[1]));
    setRight (Real32(vp[0] + vp[2]));
    setTop   (Real32(vp[1] + vp[3]));

    Inherited::activateSize();
}

void PassiveViewport::activate(void)
{
    Inherited::activate();
}

void PassiveViewport::deactivate(void)
{
    Inherited::deactivate();
}

void PassiveViewport::draw( DrawAction * action )
{
    Inherited::draw(action);
}


void PassiveViewport::render(RenderActionBase *action)
{
    Inherited::render(action);
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
    static char cvsid_cpp[] = "@(#)$Id: OSGPassiveViewport.cpp,v 1.6 2002/06/30 05:04:24 vossg Exp $";
    static char cvsid_hpp[] = OSGPASSIVEVIEWPORT_HEADER_CVSID;
    static char cvsid_inl[] = OSGPASSIVEVIEWPORT_INLINE_CVSID;
}
