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
	_state = value ? (_state | OSGVALID) : (_state & ~OSGVALID); 
}

/**  Checks if the volume is valid */
Bool Volume::isValid (void) const 
{ 
	return ( _state & OSGVALID ) ? true : false;
}

/** set the volume to contain nothing */
void Volume::setEmpty (const Bool value = true) 
{ 
	_state = value ? (_state | OSGEMPTY) : ( _state & ~OSGEMPTY); 
}

/**  Checks if the volume is empty */
Bool Volume::isEmpty (void) const 
{ 
	return ( _state & OSGEMPTY ) ? true : false; 
}

/** set the volume to contain nothing */
void Volume::setStatic (const Bool value = true) 
{ 
	_state = value ? (_state | OSGSTATIC) : ( _state & ~OSGSTATIC); 
}

/**  Checks if the volume is static */
Bool Volume::isStatic (void) const
{ 
	return ( _state & OSGSTATIC ) ? true : false; 
}

/** set the volume to contain nothing */
void Volume::setInfinite (const Bool value = true) 
{ 
	_state = value ? (_state | OSGINFINITE) : ( _state & ~OSGINFINITE); 
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
