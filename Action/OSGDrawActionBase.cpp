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

#define OSG_COMPILESYSTEMLIB

#include <stdlib.h>
#include <stdio.h>

#include <OSGConfig.h>
#include <OSGWindow.h>
#include <OSGCamera.h>
#include <OSGViewport.h>

#include <GL/gl.h>
#include <OSGVolumeDraw.h>

#include <OSGDrawActionBase.h>

OSG_USING_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char DrawActionBase::cvsid[] = "@(#)$Id: $";

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



/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

DrawActionBase::DrawActionBase(void) :
	Inherited  (),
    _camera         (NULL),
    _background     (NULL),
    _window         (NULL),
    _viewport       (NULL),
    _volumeDrawing  (false),
    _frustumCulling (true),
    _autoFrustum    (true),
    _frustum  	    ()
{
}


DrawActionBase::DrawActionBase(const DrawActionBase &source) :
	Inherited   (source            	    ),
    _camera         (source._camera         ),
    _background     (source._background     ),
    _window         (source._window         ),
    _viewport       (source._viewport       ),
    _volumeDrawing  (source._volumeDrawing ),
    _frustumCulling (source._frustumCulling ),
    _autoFrustum    (source._autoFrustum    ),
    _frustum  	    (source._frustum	    )
{
}

/** \brief Destructor
 */

DrawActionBase::~DrawActionBase(void)
{
}

/*------------------------------ start -----------------------------------*/


Action::ResultE DrawActionBase::start(void)
{
    if ( getFrustumCulling() && getAutoFrustum() )
    {
    	getCamera()->getFrustum( _frustum, *getViewport() );
    }	
   
    return Action::Continue;
}

/*------------------------------ access -----------------------------------*/

void DrawActionBase::setViewport(Viewport *viewport)
{
    _viewport = viewport;
}

void DrawActionBase::setCamera(Camera *cam)
{
    _camera = cam;
}
		
void DrawActionBase::setBackground(Background *background)
{
    _background = background;
}
		
void DrawActionBase::setWindow(Window *window)
{
    _window = window;
}
		

// do frustum culling at all?
// default true
		
void DrawActionBase::setFrustumCulling(Bool frustumCulling)
{
    _frustumCulling = frustumCulling;
}

// automatically calc the frustum at the beginning of the traversal
// default true

void DrawActionBase::setAutoFrustum(Bool autoFrustum)
{
    _autoFrustum = autoFrustum;
}

// draw the tested volumes
// default false

void DrawActionBase::setVolumeDrawing(Bool volumeDrawing)
{
    _volumeDrawing = volumeDrawing;
}

// explicitly set the frustum 
		
void DrawActionBase::setFrustum(FrustumVolume &frustum)
{
    _frustum = frustum;
}

/*---------------------------- properties ---------------------------------*/

/*---------------------------- culling ------------------------------------*/

Bool DrawActionBase::isVisible( Node* node )
{
    if ( getFrustumCulling() == false )
    	return true;

    DynamicVolume vol;
    node->getWorldVolume( vol );
    
    if ( _frustum.intersect( vol ) )
    	return true;
    
    return false;
}
    
// select all visible nodes
UInt32 DrawActionBase::selectVisibles( void )
{
    if ( getFrustumCulling() == false )
    	return getNNodes();

    useNodeList();
    
    UInt32 count = 0;
    for ( UInt32 i = 0; i < getNNodes(); i++ )
    {
    	Bool l;
	Bool d = getVolumeDrawing();
	if ( d )
	{
    	    l = glIsEnabled( GL_LIGHTING );
	    glDisable( GL_LIGHTING );
    	}
	
    	if ( isVisible( getNode(i).getCPtr() ) )
	{
	    if ( d ) glColor3f( 0,1,0 );
	    addNode( getNode(i) );
	    ++count;
	}
	else
	    if ( d ) glColor3f( 1,0,0 );
	
	if ( d )
	{ 
	    drawVolume( getNode(i)->getVolume() );
	    if ( l ) glEnable( GL_LIGHTING );
    	}
    }
    
    return count;
}


/*-------------------------- assignment -----------------------------------*/

/*-------------------------- comparison -----------------------------------*/

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/


