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

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include "OSGViewport.h"
// #include "OSGPipe.h"

#include "OSGBackground.h"
#include "OSGCamera.h"
#include "OSGWindow.h"

using namespace osg;

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

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
};

FieldContainerType Window::_type(
    "Window", 
    "FieldContainer", 
    0,
    NULL,
    0,
    _desc, 
    sizeof(_desc));

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
	Inherited(), _ports(), _width(0), _height(0)
{
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
        _ports.back()->setParent(getPtr<WindowPtr>(*this));
    }
}

void Window::insertPort(UInt32 portIndex, const ViewportPtr &portP)
{    
    MFViewportPtr::iterator portIt = _ports.begin();

    if(portP != NullFC)
    {
        portIt += portIndex;
        
        (*(_ports.insert(portIt, portP)))->setParent(getPtr<WindowPtr>(*this));
    }
}

void Window::replacePort(UInt32 portIndex, const ViewportPtr &portP)
{
    if(portP != NullFC)
    {
        _ports.getValue(portIndex)->setParent(WindowPtr::NullPtr);
        _ports.getValue(portIndex) = portP;
        _ports.getValue(portIndex)->setParent(getPtr<WindowPtr>(*this));
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
            (*portIt)->setParent(getPtr<WindowPtr>(*this));
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

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

	
void Window::draw( DrawAction * action )
{
	MFViewportPtr::iterator portIt = _ports.begin();

	activate();

	while ( portIt != _ports.end() )
	{
		(*portIt)->draw( action );
		portIt++;
	}

	swap();
}
	
void Window::resize( int width, int height )
{
	setWidth( width );
	setHeight( height );
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

Window& Window::operator = (const Window &source)
{
	if (this == &source)
		return *this;

	// copy parts inherited from parent
	//*(static_cast<Inherited *>(this)) = source;

	// free mem alloced by members of 'this'

	// alloc new mem for members

	// copy 

	return *this;
}

/*-------------------------- comparison -----------------------------------*/

/*------------------------------- dump ----------------------------------*/

void Window::dump(void) const
{
    SDEBUG << "Dump Window NI" << endl;
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

