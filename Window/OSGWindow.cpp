/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *                         Copyright 2000 by OpenSG Forum                    *
 *                                                                           *
 *          contact: {reiners|vossg}@igd.fhg.de, jbehr@zgdv.de               *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
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

char OSGWindow::cvsid[] = "@(#)$Id: $";

OSG_FC_FIRST_FIELD_IDM_DEF(OSGWindow, OSGWidthField)

OSG_FC_FIELD_IDM_DEF      (OSGWindow, OSGHeightField, OSGWidthField )
OSG_FC_FIELD_IDM_DEF      (OSGWindow, OSGPortsField,  OSGHeightField)

OSG_FC_LAST_FIELD_IDM_DEF (OSGWindow, OSGPortsField)

// Static Class Varible implementations: 
OSGFieldDescription OSGWindow::_desc[] = 
{
        OSGFieldDescription(OSGSFUInt16::getClassType(), 
                            "width", 
                            OSG_FC_FIELD_IDM_DESC(OSGWidthField),
                            false,
                            (OSGFieldAccessMethod) &OSGWindow::getSFWidth),

        OSGFieldDescription(OSGSFUInt16::getClassType(),
                            "height", 
                            OSG_FC_FIELD_IDM_DESC(OSGHeightField),
                            false,
                            (OSGFieldAccessMethod) &OSGWindow::getSFHeight),

        OSGFieldDescription(OSGMFViewportPtr::getClassType(), 
                            "ports", 
                            OSG_FC_FIELD_IDM_DESC(OSGPortsField),
                            false,
                            (OSGFieldAccessMethod) &OSGWindow::getMFPorts),
};

OSGFieldContainerType OSGWindow::_type(
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

OSG_ABSTR_FIELD_CONTAINER_DEF(OSGWindow, OSGWindowPtr)

/*------------- constructors & destructors --------------------------------*/

/** \brief Constructor
 */

OSGWindow::OSGWindow(void) :
	Inherited(), _ports(), _width(0), _height(0)
{
}


/** \brief Destructor
 */

OSGWindow::~OSGWindow(void)
{
	// delete the ports and the context
}

/*------------------------------ access -----------------------------------*/


void OSGWindow::addPort(const OSGViewportPtr &portP)
{
    if(portP != OSGNullFC)
    {
        _ports.addValue(portP);
        _ports.back()->setParent(getPtr<OSGWindowPtr>(*this));
    }
}

void OSGWindow::insertPort(OSGUInt32 portIndex, const OSGViewportPtr &portP)
{    
    OSGMFViewportPtr::iterator portIt = _ports.begin();

    if(portP != OSGNullFC)
    {
        portIt += portIndex;
        
        (*(_ports.insert(portIt, portP)))->setParent(getPtr<OSGWindowPtr>(*this));
    }
}

void OSGWindow::replacePort(OSGUInt32 portIndex, const OSGViewportPtr &portP)
{
    if(portP != OSGNullFC)
    {
        _ports.getValue(portIndex)->setParent(OSGWindowPtr::NullPtr);
        _ports.getValue(portIndex) = portP;
        _ports.getValue(portIndex)->setParent(getPtr<OSGWindowPtr>(*this));
    }
}

void OSGWindow::replacePortBy(const OSGViewportPtr &portP, 
                             const OSGViewportPtr &newportP)
{
    OSGMFViewportPtr::iterator portIt = _ports.find(portP);

    if(newportP != OSGNullFC)
    {
        if(portIt != _ports.end())
        {
            (*portIt)->setParent(OSGWindowPtr::NullPtr);
            (*portIt) = newportP;
            (*portIt)->setParent(getPtr<OSGWindowPtr>(*this));
        }
    }
}

void OSGWindow::subPort(const OSGViewportPtr &portP)
{
    OSGMFViewportPtr::iterator portIt = _ports.find(portP);

    if(portIt != _ports.end())
    {
        (*portIt)->setParent(OSGWindowPtr::NullPtr);

        _ports.erase(portIt);
    }

}

void OSGWindow::subPort(OSGUInt32  portIndex)
{
    OSGMFViewportPtr::iterator portIt = _ports.begin();

    portIt += portIndex;

    if(portIt != _ports.end())
    {
        (*portIt)->setParent(OSGWindowPtr::NullPtr);

        _ports.erase(portIt);
    }
}

OSGViewportPtr OSGWindow::getPort(OSGUInt32  portIndex)
{
    return _ports.getValue(portIndex);
}

OSGMFViewportPtr *OSGWindow::getMFPorts(void)
{
    return &_ports;
}

/*---------------------------- properties ---------------------------------*/

/*-------------------------- your_category---------------------------------*/

	
void OSGWindow::draw( OSGDrawAction * action )
{
	OSGMFViewportPtr::iterator portIt = _ports.begin();

	activate();

	while ( portIt != _ports.end() )
	{
		(*portIt)->draw( action );
		portIt++;
	}

	swap();
}
	
void OSGWindow::resize( int width, int height )
{
	setWidth( width );
	setHeight( height );
}

/*-------------------------- assignment -----------------------------------*/

/** \brief assignment
 */

OSGWindow& OSGWindow::operator = (const OSGWindow &source)
{
	if (this == &source)
		return *this;

	// copy parts inherited from parent
	*(static_cast<Inherited *>(this)) = source;

	// free mem alloced by members of 'this'

	// alloc new mem for members

	// copy 

	return *this;
}

/*-------------------------- comparison -----------------------------------*/

/*------------------------------- dump ----------------------------------*/

void OSGWindow::dump(void) const
{
    SDEBUG << "Dump OSGWindow NI" << endl;
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

