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

#include <OSGVolume.h>
#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>

#include "OSGVector.h"
#include "OSGMatrix.h"
#include "OSGLine.h"

OSG_BEGIN_NAMESPACE


/*-------------------------- state -----------------------------------------*/

/** set the volume to contain nothing */
OSG_BASE_DLLMAPPING
void Volume::setValid (const bool value)
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
OSG_BASE_DLLMAPPING
bool Volume::isValid (void) const
{
    return ( _state & OSGVALID ) ? true : false;
}

/** set the volume to contain nothing */
OSG_BASE_DLLMAPPING
void Volume::setEmpty (const bool value)
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
OSG_BASE_DLLMAPPING
bool Volume::isEmpty (void) const
{
    return ( _state & OSGEMPTY ) ? true : false;
}

/** set the volume to contain nothing */
OSG_BASE_DLLMAPPING
void Volume::setStatic (const bool value)
{
    if (value)
        _state |= OSGSTATIC;
    else
        _state &= ~OSGSTATIC;
}

/**  Checks if the volume is static */
OSG_BASE_DLLMAPPING
bool Volume::isStatic (void) const
{
    return ( _state & OSGSTATIC ) ? true : false;
}

/** set the volume to contain nothing */
OSG_BASE_DLLMAPPING
void Volume::setInfinite (const bool value)
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
OSG_BASE_DLLMAPPING
bool Volume::isInfinite (void) const
{
    return ( _state & OSGINFINITE ) ? true : false;
}


/**  Checks if the volume is intouchable, i.e. it's values should not be 
     changed. Mainly used internally to speed up early outs in extendBy(). */
OSG_BASE_DLLMAPPING
bool Volume::isUntouchable (void) const
{
    // return ! isValid() || isInfinite() || isStatic();
    return (_state & (OSGINFINITE | OSGVALID | OSGSTATIC)) != OSGVALID;
}


/**  Return the lowest point of the volume. Just a convience wrapper for
     getBounds() */
OSG_BASE_DLLMAPPING
Pnt3f Volume::getMin(void) const
{
    Pnt3f pmin,pmax;
    getBounds(pmin, pmax);
    return pmin;
}

/**  Return the highest point of the volume. Just a convience wrapper for
     getBounds() */
OSG_BASE_DLLMAPPING
Pnt3f Volume::getMax(void) const
{
    Pnt3f pmin,pmax;
    getBounds(pmin, pmax);
    return pmax;
}

OSG_END_NAMESPACE

#endif // VOLUME_CLASS_DECLARATION
