/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                 Copyright (C) 2000 by the OpenSG Forum                    *
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

#include <GL/gl.h>

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#define OSG_COMPILEWINDOW
#define OSG_COMPILEWINDOWINST

#include <OSGDrawAction.h>

#include "OSGViewport.h"
// #include "OSGPipe.h"

#include "OSGBackground.h"
#include "OSGCamera.h"
#include "OSGWindow.h"

OSG_USING_NAMESPACE


/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \defgroup WindowLib

The WindowLib include all objects concerned with opening, managing and
drawing into windows.

*/


/*! \defgroup Windows
    \ingroup WindowLib

The Windows group include all the general and window-system specific
Window objects.

*/

/*! \class osg::Window
    \ingroup Windows

The Window base class.

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

OSG_BEGIN_NAMESPACE

#if defined(__sgi)

#pragma instantiate SField<WindowPtr>::_fieldType
#pragma instantiate MField<WindowPtr>::_fieldType

#else

OSG_DLLEXPORT_DEF1(SField, WindowPtr, OSG_WINDOW_DLLTMPLMAPPING)
OSG_DLLEXPORT_DEF1(MField, WindowPtr, OSG_WINDOW_DLLTMPLMAPPING)

#endif

OSG_END_NAMESPACE


/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char Window::cvsid[] = "@(#)$Id: $";

OSG_FC_FIRST_FIELD_IDM_DEF(Window, WidthField)

OSG_FC_FIELD_IDM_DEF      (Window, HeightField, WidthField )
OSG_FC_FIELD_IDM_DEF      (Window, PortsField,  HeightField)

OSG_FC_LAST_FIELD_IDM_DEF (Window, PortsField)

// Static Class Varible implementations: 
FieldDescription Window::_desc[] = 
{
        FieldDescription(SFUInt16::getClassType(), 
                            "width", 
                            OSG_FC_FIELD_IDM_DESC(WidthField),
                            false,
                            (FieldAccessMethod) &Window::getSFWidth),

        FieldDescription(SFUInt16::getClassType(),
                            "height", 
                            OSG_FC_FIELD_IDM_DESC(HeightField),
                            false,
                            (FieldAccessMethod) &Window::getSFHeight),

        FieldDescription(MFViewportPtr::getClassType(), 
                            "ports", 
                            OSG_FC_FIELD_IDM_DESC(PortsField),
                            false,
                            (FieldAccessMethod) &Window::getMFPorts),

        FieldDescription(SFBool::getClassType(), 
                            "resizePending", 
                            OSG_FC_FIELD_IDM_DESC(ResizePendingField),
                            true,
                            (FieldAccessMethod) &Window::getSFResizePending),

        FieldDescription(MFGLObjectFlagE::getClassType(), 
                            "globjectflags", 
                            OSG_FC_FIELD_IDM_DESC(GLObjectFlagsField),
                            true,
                            (FieldAccessMethod) &Window::getMFGLObjectFlags)
};

FieldContainerType Window::_type(
    "Window", 
    "FieldContainer", 
    0,
    NULL,
    0,
    _desc, 
    sizeof(_desc));
	

// GLobject handling

Lock                      *Window::_GLObjectLock;
vector<Window::GLObject*>  Window::_glObjects;
vector<UInt32>             Window::_glObjectDestroyList;


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

OSG_ABSTR_FIELD_CONTAINER_DEF(Window, WindowPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

Window::Window(void) :
	Inherited(), 
	_ports(), _width(0), _height(0), _resizePending(), _glObjectFlags()
{
	// reserve index 0, illegal for most OpenGL functions
	if ( _glObjects.empty() )
		_glObjects.push_back( NULL );	
}


/** \brief Copy Constructor
 */

Window::Window( const Window& source ) :
	Inherited( source ), _ports( source._ports ), _width( source._width ), 
	_height( source._height ), _resizePending( source._resizePending ),
	_glObjectFlags( source._glObjectFlags )
{	
	// mark all flags as notused, i.e. have to initialize on use
	for ( vector<GLObjectFlagE>::iterator it = _glObjectFlags.begin();
			it != _glObjectFlags.end(); ++it )
		*it = notused;
}


/** \brief Destructor
 */

Window::~Window(void)
{
	// delete the ports and the context
}

/*------------------------------ access -----------------------------------*/


void Window::addPort(const ViewportPtr &portP)
{
    if(portP != NullFC)
    {
        _ports.addValue(portP);
        _ports.back()->setParent(FieldContainer::getPtr<WindowPtr>(*this));
    }
}

void Window::insertPort(UInt32 portIndex, const ViewportPtr &portP)
{    
    MFViewportPtr::iterator portIt = _ports.begin();

    if(portP != NullFC)
    {
        portIt += portIndex;
        
        (*(_ports.insert(portIt, portP)))->setParent(
            FieldContainer::getPtr<WindowPtr>(*this));
    }
}


void Window::replacePort(UInt32 portIndex, const ViewportPtr &portP)
{
    if(portP != NullFC)
    {
        _ports.getValue(portIndex)->setParent(WindowPtr::NullPtr);
        _ports.getValue(portIndex) = portP;
        _ports.getValue(portIndex)->setParent(
            FieldContainer::getPtr<WindowPtr>(*this));
    }
}

void Window::replacePortBy(const ViewportPtr &portP, 
                             const ViewportPtr &newportP)
{
    MFViewportPtr::iterator portIt = _ports.find(portP);

    if(newportP != NullFC)
    {
        if(portIt != _ports.end())
        {
            (*portIt)->setParent(WindowPtr::NullPtr);
            (*portIt) = newportP;
            (*portIt)->setParent(
                FieldContainer::getPtr<WindowPtr>(*this));
        }
    }
}

void Window::subPort(const ViewportPtr &portP)
{
    MFViewportPtr::iterator portIt = _ports.find(portP);

    if(portIt != _ports.end())
    {
        (*portIt)->setParent(WindowPtr::NullPtr);

        _ports.erase(portIt);
    }

}

void Window::subPort(UInt32  portIndex)
{
    MFViewportPtr::iterator portIt = _ports.begin();

    portIt += portIndex;

    if(portIt != _ports.end())
    {
        (*portIt)->setParent(WindowPtr::NullPtr);

        _ports.erase(portIt);
    }
}

ViewportPtr Window::getPort(UInt32  portIndex)
{
    return _ports.getValue(portIndex);
}

MFViewportPtr *Window::getMFPorts(void)
{
    return &_ports;
}




UInt32 Window::registerGLObject ( GLObjectFunctor functor, UInt32 num )
{
	int      id, i; 
	GLObject *pGLObject;

	id	      = _glObjects.size();
	i	      = 0;
	pGLObject = new GLObject( functor );
	
	// does the requested block fit into the capacity?
	
	if (  ( _glObjects.capacity() >= id+num ) || ( !id )  )
	{
		while ( i < num ) 
		{
			_glObjects.push_back( pGLObject );

			i = i + 1;
		}		
		return( id );
	}
	
	// doesn't fit, try to find a block in the middle
	
	int cnt = 0;		

	// start searching at 1, id 0 is reserved for GL
	for ( i = 1; i < _glObjects.size(); i++ )
	{		
		if ( !_glObjects[i] ) 
		{
			if ( cnt == 0 )
			{
				id = i;
				cnt = cnt + 1;
			}

			if ( cnt == num ) 
			{
				// block of unused entries found ...
						
				while ( i >= id ) 
				{
				    _glObjects[i] = pGLObject;
					i = i - 1;
				} 
							
				return ( id );
			}
		}
		else
		{
			cnt = 0;
		}
	}
	
	// no block found, add at the end
	
	// fill the empty slots at the end 
	i = id + cnt - 1;
	while ( i >= id )
	{
		_glObjects[i] = pGLObject;
		i = i - 1;
	}
	
	// expand the vector for the rest 
	for ( i = 1; i <= num - cnt; i++ ) 
	{		
		_glObjects.push_back( pGLObject );
	}
	
	return ( id );
}

void Window::validateGLObject ( UInt32 id )
{
	UInt32 s;

	s = _glObjectFlags.size();
	while ( s <= id ) 
	{
		_glObjectFlags.push_back( notused );
		s = s + 1;
	}
	
	if ( _glObjectFlags[id] == notused ) 
	{
		_glObjectFlags[id] = initialized;
		_glObjects[id]->incRefCounter();
		_glObjects[id]->getFunctor().call( initialize, id );
	}
}

void Window::refreshGLObject ( UInt32 id )
{
	if ( id >= _glObjectFlags.size() )
	{
		SWARNING << "Window::refreshGLObject: nothing known about id " << id
				 << "!" << endl;
		return;
	}
	
	switch ( _glObjectFlags[id] ) 
	{
	case notused:	// not used yet, no need to refresh
	case destroy:
	case finaldestroy:	// object is being destroyed, ignore refresh
		break;
	case initialize:	// can't happen, internal temporal state
		SWARNING << "Window::refreshGLObject: id " << id
				 << " in state initialize ?!?!" << endl;
		return;
	case initialized:
		_glObjectFlags[id] = needrefresh;
		break;
	default:
		SWARNING << "Window::refreshGLObject: id " << id
				 << " in state " << _glObjectFlags[id] << "?!?!" << endl;
		return;
	}
}

void Window::destroyGLObject ( UInt32 id, UInt32 num )
{
	_glObjectDestroyList.push_back( id );
	_glObjectDestroyList.push_back( num );
}

void Window::frame( void )
{	
	if ( _glObjectDestroyList.size() > 0 )
	{
		UInt32 i;
		i = _glObjectDestroyList[ _glObjectDestroyList.size()-2 ] ;

		UInt32 rc = _glObjects[ i ]->getRefCounter();

		if ( _glObjectFlags[ i ] == initialized ) 
		{			
		
			_glObjectFlags[ i ] = destroy;
			_glObjects[ i ]->getFunctor().call( destroy, i );			

			if ( ! ( rc = _glObjects[ i ]->decRefCounter() )  )
			{			
				// call functor with the final-flag
				_glObjectFlags[ i ] = finaldestroy;
				_glObjects[ i ]->getFunctor().call( finaldestroy, i );
			}

			_glObjectFlags[ i ] = notused;			
		}

		// if the GLObject is removed from each GL-Context, free GLObject-IDs.

		if ( ! rc )
		{
			delete _glObjects[ i ];
			for ( UInt32 j = 0; j < (*(_glObjectDestroyList.end()-1)) ; j++)
			{
				_glObjects[i+j] = NULL;
			}	
			_glObjectDestroyList.pop_back(); 
			_glObjectDestroyList.pop_back();
		}
	}
}

void Window::setupGL ( void )
{	
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	glPixelStorei( GL_PACK_ALIGNMENT, 1 );
}

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

	
void Window::draw( DrawAction * action )
{
	activate();
	
	resizeGL();

	drawAllViewports( action );

	swap();
	frame();	// after frame cleanup: delete GL objects, if needed
}
	
void Window::drawAllViewports( DrawAction * action )
{
	DrawAction *a = dynamic_cast<DrawAction*>(action);
	MFViewportPtr::iterator portIt = _ports.begin();

	a->setWindow( this );
	
	while ( portIt != _ports.end() )
	{
		(*portIt)->draw( action );
		portIt++;
	}
}
	
void Window::resize( int width, int height )
{
	setWidth( width );
	setHeight( height );
	setResizePending( true );
}
	
void Window::resizeGL( void )
{
	if ( isResizePending () )
	{
		glViewport( 0, 0, getWidth(), getHeight() );
		setResizePending( false );
	}
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

Window& Window::operator = (const Window &source)
{
	if (this == &source)
		return *this;

	// copy 

	setWidth( source.getWidth() );
	setHeight( source.getHeight() );
	_ports.setValues( source._ports.getValues() );
	_glObjectFlags.setValues( source._glObjectFlags.getValues() );
	
	// mark all flags as notused, i.e. have to initialize on use
	for ( vector<GLObjectFlagE>::iterator it = _glObjectFlags.begin();
			it != _glObjectFlags.end(); ++it )
		*it = notused;
	
	return *this;
}

/*-------------------------- comparison -----------------------------------*/

/*------------------------------- dump ----------------------------------*/

void Window::dump(      UInt32     uiIndent, 
                  const BitVector &bvFlags) const
{
	SLOG << "Dump Window NI" << endl;
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/


/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

///---------------------------------------------------------------------------
///  FUNCTION: 
///---------------------------------------------------------------------------
//:  Example for the head comment of a function
///---------------------------------------------------------------------------
///
//p: Paramaters: 
//p: 
///
//g: GlobalVars:
//g: 
///
//r: Return:
//r: 
///
//c: Caution:
//c: 
///
//a: Assumptions:
//a: 
///
//d: Description:
//d: 
///
//s: SeeAlso:
//s: 
///---------------------------------------------------------------------------

