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
#include <OSGCamera.h>
#include <OSGBackground.h>
#include <OSGForeground.h>
#include <OSGDrawAction.h>
#include <OSGRenderAction.h>
#include "OSGPassiveViewport.h"

OSG_USING_NAMESPACE

/*! \class osg::PassiveViewport
The PassiveViewport does nothing itself, but expects OpenGL to be properly configured when draw() or render() are called. 
*/

/*----------------------- constructors & destructors ----------------------*/

//! Constructor

PassiveViewport::PassiveViewport(void) :
    Inherited()
{
}

//! Copy Constructor

PassiveViewport::PassiveViewport(const PassiveViewport &source) :
    Inherited(source)
{
}

//! Destructor

PassiveViewport::~PassiveViewport(void)
{
}

/*----------------------------- class specific ----------------------------*/

//! initialize the static features of the class, e.g. action callbacks

void PassiveViewport::initMethod (void)
{
}

//! react to field changes

void PassiveViewport::changed(BitVector, UInt32)
{
}

//! output the instance for debug purposes

void PassiveViewport::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump PassiveViewport NI" << endl;
}


void PassiveViewport::draw( DrawAction * action )
{
    if ( getCamera() == NullFC )
    {
        SWARNING << "PassiveViewport::draw: no camera!" << endl;
        return;
    }
    if ( getBackground() == NullFC )
    {
        SWARNING << "PassiveViewport::draw: no background!" << endl;
        return;
    }
    if ( getRoot() == NullFC )
    {
        SWARNING << "PassiveViewport::draw: no root!" << endl;
        return;
    }

    GLint vp[4];
    glGetIntegerv(GL_VIEWPORT, vp);
    setLeft(vp[0]);
    setBottom(vp[1]);
    setRight(vp[0] + vp[2]);
    setTop(vp[1] + vp[3]); 
    
    GLint pl=getPixelLeft(), pr=getPixelRight(), pb=getPixelBottom(), 
          pt=getPixelTop();
    GLint pw=pr-pl+1,ph=pt-pb+1;

    glViewport( pl, pb, pw, ph );
    glScissor( pl, pb, pw, ph );
    
    glEnable( GL_SCISSOR_TEST );

    action->setViewport( this );
    action->setCamera( getCamera().getCPtr() );
    action->setBackground( getBackground().getCPtr() );
    
    getCamera()->setup( action, *this );
    getBackground()->clear( action, this );

    action->apply( getRoot() );

    for ( UInt16 i=0; i < getForegrounds().size(); i++ )
        getForegrounds( i )->draw( action, this );

    glDisable( GL_SCISSOR_TEST );
}


void PassiveViewport::render( RenderAction * action )
{
    if ( getCamera() == NullFC )
    {
        SWARNING << "Viewport::render: no camera!" << endl;
        return;
    }
    if ( getBackground() == NullFC )
    {
        SWARNING << "Viewport::render: no background!" << endl;
        return;
    }
    if ( getRoot() == NullFC )
    {
        SWARNING << "Viewport::render: no root!" << endl;
        return;
    }

    GLint vp[4];
    glGetIntegerv(GL_VIEWPORT, vp);
    setLeft(vp[0]);
    setBottom(vp[1]);
    setRight(vp[0] + vp[2]);
    setTop(vp[1] + vp[3]); 

/*
    GLint pl=getPixelLeft(), pr=getPixelRight(), pb=getPixelBottom(), 
          pt=getPixelTop();
    GLint pw=pr-pl+1,ph=pt-pb+1;
    bool full = isFullWindow();

    glViewport( pl, pb, pw, ph );
    glScissor( pl, pb, pw, ph );

    if ( ! full )
        glEnable( GL_SCISSOR_TEST );
    */

    action->setCamera    (getCamera    ().getCPtr());
    action->setBackground(getBackground().getCPtr());
    action->setViewport  (this                     );

//  getCamera()->setup( action, *this );
//  getBackground()->clear( action, this );

    

    action->apply( getRoot() );

    for(UInt16 i=0; i < getForegrounds().size(); i++)
        getForegrounds(i)->draw(action, this);

/*
    if ( ! full )
        glDisable( GL_SCISSOR_TEST );
        */
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
    static char cvsid_cpp[] = "@(#)$Id: OSGPassiveViewport.cpp,v 1.5 2002/06/01 10:37:26 vossg Exp $";
    static char cvsid_hpp[] = OSGPASSIVEVIEWPORT_HEADER_CVSID;
    static char cvsid_inl[] = OSGPASSIVEVIEWPORT_INLINE_CVSID;
}
