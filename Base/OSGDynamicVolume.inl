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

#ifndef _OSGDYNAMICVOLUME_INL_
#define _OSGDYNAMICVOLUME_INL_

#include <OSGBaseTypes.h>
#include <OSGBaseFunctions.h>

#include "OSGVector.h"
#include "OSGMatrix.h"
#include "OSGLine.h"

OSG_BEGIN_NAMESPACE

/** gives the center of the volume */
inline
void DynamicVolume::getCenter (Pnt3f &center) const
{
    getInstance().getCenter(center);
}

/** gives the scalar volume of the volume */
inline
float DynamicVolume::getScalarVolume (void) const
{
    return getInstance().getScalarVolume();
}

/** gives the boundaries of the volume */
inline
void DynamicVolume::getBounds( Pnt3f &min, Pnt3f &max ) const
{
    getInstance().getBounds(min,max);
}

/** extends (if necessary) to contain the given 3D point */
inline
void DynamicVolume::extendBy (const Pnt3f &pt)
{
    getInstance().extendBy(pt);
}

/** extend the volume by the given volume */
inline
void DynamicVolume::extendBy (const Volume &volume)
{
    getInstance().extendBy(volume);
}

/** Returns true if intersection of given point and Volume is not empty */
inline
Bool DynamicVolume::intersect (const Pnt3f &point) const
{
    return getInstance().intersect(point);
}

/** intersect the volume with the given Line */
inline
Bool DynamicVolume::intersect (const Line &line ) const
{
    return getInstance().intersect(line);
}

/** intersect the volume with the given Line */
inline
Bool DynamicVolume::intersect ( const Line &line,
                                                Real32 &enter, Real32 &exit  ) const
{
    return getInstance().intersect(line,enter,exit);
}

/** intersect the volume with another volume */
inline
Bool DynamicVolume::intersect (const Volume &volume) const
{
    return getInstance().intersect(volume);
}

/** check if the point is on the volume's surface */
inline
Bool DynamicVolume::isOnSurface (const Pnt3f &point) const
{
    return getInstance().isOnSurface(point);
}

/** transform the volume bye the given matrix*/
inline
void DynamicVolume::transform (const Matrix &matrix)
{
    getInstance().transform(matrix);
}

OSG_END_NAMESPACE

#endif // DYNAMICVOLUME_CLASS_DECLARATION
