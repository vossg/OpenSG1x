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

#include "OSGConfig.h"

#include <OSGGL.h>

#include <OSGField.h>
#include <OSGFieldContainer.h>
#include <OSGAction.h>
#include <OSGDrawAction.h>
#include <OSGRenderAction.h>
#include "OSGBackground.h"
#include "OSGViewport.h"
#include "OSGWindow.h"
#include "OSGCamera.h"
#include "OSGForeground.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::Viewport
    \ingroup GrpSystemWindowsViewports

A Viewport is a part of the Window it is attached to used for rendering. Every 
Window can hold an arbitrary number of viewports.   

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char Viewport::cvsid[] = "@(#)$Id: $";

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

void Viewport::initMethod (void)
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

Viewport::Viewport(void) :
    Inherited()
{
}

/** \brief Copy Constructor
 */

Viewport::Viewport(const Viewport &source) :
    Inherited(source)
{
}

/** \brief Destructor
 */

Viewport::~Viewport(void)
{
}


/** \brief react to field changes
 */

void Viewport::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

/*---------------------------- properties ---------------------------------*/


Int32 Viewport::getPixelLeft( void ) const
{
    if ( getLeft() > 1 )
        return Int32(getLeft());

    return Int32(getParent()->getWidth() * getLeft());
}

Int32 Viewport::getPixelRight( void ) const
{
    // >1: pixel
    if ( getRight() > 1 )
        return Int32(getRight());

    // <=1: partial screen, use 1 less to not overlap other windows
    return Int32(getParent()->getWidth() * getRight() - 1);
}

Int32 Viewport::getPixelBottom( void ) const
{
    if ( getBottom() > 1 )
        return Int32(getBottom());

    return Int32(getParent()->getHeight() * getBottom());
}

Int32 Viewport::getPixelTop( void ) const
{
    // >1: pixel
    if ( getTop() > 1 )
        return Int32(getTop());

    // <=1: partial screen, use 1 less to not overlap other windows
    return Int32(getParent()->getHeight() * getTop() - 1);
}

bool Viewport::isFullWindow( void ) const
{
    return  getPixelBottom() == 0 &&
            getPixelLeft()   == 0 &&
            getPixelTop()    == getParent()->getHeight() - 1 &&
            getPixelRight()  == getParent()->getWidth() - 1;
}

/*-------------------------- your_category---------------------------------*/

void Viewport::draw( DrawAction * action )
{
    if ( getCamera() == NullFC )
    {
        SWARNING << "Viewport::draw: no camera!" << std::endl;
        return;
    }
    if ( getBackground() == NullFC )
    {
        SWARNING << "Viewport::draw: no background!" << std::endl;
        return;
    }
    if ( getRoot() == NullFC )
    {
        SWARNING << "Viewport::draw: no root!" << std::endl;
        return;
    }

    GLint pl=getPixelLeft(), pr=getPixelRight(), pb=getPixelBottom(), 
          pt=getPixelTop();
    GLint pw=pr-pl+1,ph=pt-pb+1;
    bool full = isFullWindow();

    glViewport( pl, pb, pw, ph );
    glScissor( pl, pb, pw, ph );
    
    if ( ! full )
        glEnable( GL_SCISSOR_TEST );

    action->setViewport( this );
    action->setCamera( getCamera().getCPtr() );
    action->setBackground( getBackground().getCPtr() );
    
    getCamera()->setup( action, *this );
    getBackground()->clear( action, this );

    action->apply( getRoot() );

    for ( UInt16 i=0; i < getForegrounds().size(); i++ )
        getForegrounds( i )->draw( action, this );

    if ( ! full )
        glDisable( GL_SCISSOR_TEST );
}


void Viewport::render( RenderAction * action )
{
    if ( getCamera() == NullFC )
    {
        SWARNING << "Viewport::render: no camera!" << std::endl;
        return;
    }
    if ( getBackground() == NullFC )
    {
        SWARNING << "Viewport::render: no background!" << std::endl;
        return;
    }
    if ( getRoot() == NullFC )
    {
        SWARNING << "Viewport::render: no root!" << std::endl;
        return;
    }

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

/*
fprintf(stderr,"%p: node 0x%p startrender\n", Thread::getCurrent(), 
                getRoot().getCPtr());
*/
    action->apply( getRoot() );

    for(UInt16 i=0; i < getForegrounds().size(); i++)
        getForegrounds(i)->draw(action, this);

/*
    if ( ! full )
        glDisable( GL_SCISSOR_TEST );
        */
}

/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */

void Viewport::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                    const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    SLOG << "Dump Viewport NI" << std::endl;
}

    

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/


