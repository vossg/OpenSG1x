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

#include "OSGConfig.h"

#include <GL/gl.h>

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

/*! \class Window
    \ingroup Windows

The Window base class.

*/

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

char Window::cvsid[] = "@(#)$Id: $";

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/
// GLobject handling

Lock                      *Window::_GLObjectLock;
vector<Window::GLObject*>  Window::_glObjects;
vector<UInt32>             Window::_glObjectDestroyList;

// GL extension handling

vector<String>			   Window::_registeredExtensions;
vector<String>			   Window::_registeredFunctions;

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

void Window::initMethod (void)
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

Window::Window(void) :
    Inherited()
{
	// reserve index 0, illegal for most OpenGL functions
	if ( _glObjects.empty() )
		_glObjects.push_back( NULL );	
}

/** \brief Copy Constructor
 */

Window::Window(const Window &source) :
    Inherited(source)
{
	// mark all flags as notused, i.e. have to initialize on use
	for ( vector<UInt32>::iterator it = _mfGlObjectFlags.begin();
			it != _mfGlObjectFlags.end(); ++it )
		*it = notused;
}

/** \brief Destructor
 */

Window::~Window(void)
{
	// delete the ports and the context
}


/** \brief react to field changes
 */

void Window::changed(BitVector, ChangeMode)
{
}

/*------------------------------ access -----------------------------------*/


void Window::addPort(const ViewportPtr &portP)
{
    if(portP != NullFC)
    {
        _mfPort.addValue(portP);
// CHECK CHECK
//        _mfPort.back()->setParent(FieldContainer::getPtr<WindowPtr>(*this));
        _mfPort.back()->setParent(WindowPtr(*this));
    }
}

void Window::insertPort(UInt32 portIndex, const ViewportPtr &portP)
{    
    MFViewportPtr::iterator portIt = _mfPort.begin();

    if(portP != NullFC)
    {
        portIt += portIndex;
  
// CHECK CHECK      
//        (*(_mfPort.insert(portIt, portP)))->setParent(
//            FieldContainer::getPtr<WindowPtr>(*this));
        (*(_mfPort.insert(portIt, portP)))->setParent(
            WindowPtr(*this));
    }
}


void Window::replacePort(UInt32 portIndex, const ViewportPtr &portP)
{
    if(portP != NullFC)
    {
        _mfPort.getValue(portIndex)->setParent(WindowPtr::NullPtr);
        _mfPort.getValue(portIndex) = portP;
// CHECK CHECK
//        _mfPort.getValue(portIndex)->setParent(
//            FieldContainer::getPtr<WindowPtr>(*this));
        _mfPort.getValue(portIndex)->setParent(
            WindowPtr(*this));
    }
}

void Window::replacePortBy(const ViewportPtr &portP, 
                             const ViewportPtr &newportP)
{
    MFViewportPtr::iterator portIt = _mfPort.find(portP);

    if(newportP != NullFC)
    {
        if(portIt != _mfPort.end())
        {
            (*portIt)->setParent(WindowPtr::NullPtr);
            (*portIt) = newportP;
// CHECK CHECK
//            (*portIt)->setParent(
//                FieldContainer::getPtr<WindowPtr>(*this));
            (*portIt)->setParent(
                WindowPtr(*this));
        }
    }
}

void Window::subPort(const ViewportPtr &portP)
{
    MFViewportPtr::iterator portIt = _mfPort.find(portP);

    if(portIt != _mfPort.end())
    {
        (*portIt)->setParent(WindowPtr::NullPtr);

        _mfPort.erase(portIt);
    }

}

void Window::subPort(UInt32  portIndex)
{
    MFViewportPtr::iterator portIt = _mfPort.begin();

    portIt += portIndex;

    if(portIt != _mfPort.end())
    {
        (*portIt)->setParent(WindowPtr::NullPtr);

        _mfPort.erase(portIt);
    }
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

	s = _mfGlObjectFlags.size();
	while ( s <= id ) 
	{
		_mfGlObjectFlags.push_back( notused );
		s = s + 1;
	}
	
	if ( _mfGlObjectFlags[id] == notused ) 
	{
		_mfGlObjectFlags[id] = initialized;
		_glObjects[id]->incRefCounter();
		_glObjects[id]->getFunctor().call( initialize, id );
	}
}

void Window::refreshGLObject ( UInt32 id )
{
	if ( id >= _mfGlObjectFlags.size() )
	{
		SWARNING << "Window::refreshGLObject: nothing known about id " << id
				 << "!" << endl;
		return;
	}
	
	switch ( _mfGlObjectFlags[id] ) 
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
		_mfGlObjectFlags[id] = needrefresh;
		break;
	default:
		SWARNING << "Window::refreshGLObject: id " << id
				 << " in state " << _mfGlObjectFlags[id] << "?!?!" << endl;
		return;
	}
}

void Window::destroyGLObject ( UInt32 id, UInt32 num )
{
	_glObjectDestroyList.push_back( id );
	_glObjectDestroyList.push_back( num );
}

void Window::dumpExtensions ( void )
{	
	vector<String>::iterator it;
	cout << "GL Extensions: ";
	for ( it = _extensions.begin(); it != _extensions.end(); it++ )
	{
		cout << it->str() << ", ";
	}
	cout << endl;		
}

void Window::frameInit( void )
{
    // any new extension registered ? 
    while ( _registeredExtensions.size() > _availExtensions.size() )
    {			
	
        // GL extension string allready retrieved ? 
		if ( _extensions.empty() )
		{			
			// if not, retrieve and split it
			String s = String( (Char8 *)glGetString(GL_EXTENSIONS) );
			s.tokenize( _extensions );
			sort( _extensions.begin(), _extensions.end() );
		}
				
	    /* perform a binary search over the retrieved extension strings.
		   Push back the result as an availability flag for the extension
		   requested by the application */		   
		_availExtensions.push_back( binary_search( 
 					   _extensions.begin(),
					   _extensions.end(),
					   _registeredExtensions[_availExtensions.size()] )  );
	}
	
	while ( _registeredFunctions.size() > _extFunctions.size() )
{	
		_extFunctions.push_back( (void*)getFunctionByName( 
						_registeredFunctions[ _extFunctions.size() ] ));
	}

}

void Window::frameExit( void )
{	
	if ( _glObjectDestroyList.size() > 0 )
	{
		UInt32 i;
		i = _glObjectDestroyList[ _glObjectDestroyList.size()-2 ] ;

		UInt32 rc = _glObjects[ i ]->getRefCounter();

		if ( _mfGlObjectFlags[ i ] == initialized ) 
		{			
		
			_mfGlObjectFlags[ i ] = destroy;
			_glObjects[ i ]->getFunctor().call( destroy, i );			

			if ( ! ( rc = _glObjects[ i ]->decRefCounter() )  )
			{			
				// call functor with the final-flag
				_mfGlObjectFlags[ i ] = finaldestroy;
				_glObjects[ i ]->getFunctor().call( finaldestroy, i );
			}

			_mfGlObjectFlags[ i ] = notused;			
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
	frameInit();    // query recently registered GL extensions
	
	resizeGL();

	drawAllViewports( action );

	swap();
	frameExit();	// after frame cleanup: delete GL objects, if needed
}
	
void Window::drawAllViewports( DrawAction * action )
{
	DrawAction *a = dynamic_cast<DrawAction*>(action);
	MFViewportPtr::iterator portIt = _mfPort.begin();

	a->setWindow( this );
	
	while ( portIt != _mfPort.end() )
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
	_mfPort.setValues( source._mfPort.getValues() );
	_mfGlObjectFlags.setValues( source._mfGlObjectFlags.getValues() );
	
	// mark all flags as notused, i.e. have to initialize on use
	for ( vector<UInt32>::iterator it = _mfGlObjectFlags.begin();
			it != _mfGlObjectFlags.end(); ++it )
		*it = notused;
	
	return *this;
}


/*------------------------------- dump ----------------------------------*/

/** \brief output the instance for debug purposes
 */

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

