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


#ifndef _OSGVOLUME_INL_
#define _OSGVOLUME_INL_

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGVolume.h>
#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>

#include "OSGVector.h"
#include "OSGMatrix.h"
#include "OSGLine.h"

OSG_BEGIN_NAMESPACE


/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/


/*-------------------------- state -----------------------------------------*/

/** set the volume to contain nothing */
void Volume::setValid (const Bool value = true) 
{ 
	if ( ! isStatic() )
	{
		if (value)
		  _state |= OSGVALID;
		else 
		  _state &= ~OSGVALID; 
	}
}

/**  Checks if the volume is valid */
Bool Volume::isValid (void) const 
{ 
	return ( _state & OSGVALID ) ? true : false;
}

/** set the volume to contain nothing */
void Volume::setEmpty (const Bool value = true) 
{ 
	if (value) 
	{
		_state |= OSGEMPTY;
		_state |= OSGVALID;
		_state &= ~OSGINFINITE;
	}	
	else 
		_state &= ~OSGEMPTY;
}

/**  Checks if the volume is empty */
Bool Volume::isEmpty (void) const 
{ 
	return ( _state & OSGEMPTY ) ? true : false; 
}

/** set the volume to contain nothing */
void Volume::setStatic (const Bool value = true) 
{ 
	if (value)
		_state |= OSGSTATIC;
	else 
		_state &= ~OSGSTATIC; 
}

/**  Checks if the volume is static */
Bool Volume::isStatic (void) const
{ 
	return ( _state & OSGSTATIC ) ? true : false; 
}

/** set the volume to contain nothing */
void Volume::setInfinite (const Bool value = true) 
{ 
	if (value) 
	{
		_state |= OSGINFINITE;
		_state |= OSGVALID;
		_state &= ~OSGEMPTY;
	}
	else 
		_state &= ~OSGINFINITE; 
}

/**  Checks if the volume is infinite */
Bool Volume::isInfinite (void) const 
{ 
	return ( _state & OSGINFINITE ) ? true : false; 
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/


OSG_END_NAMESPACE

#endif // VOLUME_CLASS_DECLARATION
