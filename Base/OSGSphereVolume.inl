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


#ifndef _OSGSPHEREVOLUME_INL_
#define _OSGSPHEREVOLUME_INL_

#include <OSGVolume.h>

OSG_BEGIN_NAMESPACE


/*-------------------------- constructor ----------------------------------*/
inline
SphereVolume::SphereVolume(void) : Volume(), _radius(0) {;}

inline
SphereVolume::SphereVolume(const SphereVolume &obj)
 : Volume(),    _center(obj._center), _radius(obj._radius) { setEmpty(false);}

inline
SphereVolume::SphereVolume(const Pnt3f &c, float r)
: Volume(), _center(c), _radius(r) { setEmpty(false);}

inline
SphereVolume::~SphereVolume() {;}

/*------------------------------ feature ----------------------------------*/

/// Change the center and radius
inline
void SphereVolume::setValue(const Pnt3f &c, float r)
{
    setEmpty(false);
    _center = c;
    _radius = r;
}

/*------------------------- set values -------------------------------*/

/// set just the center
inline
void SphereVolume::setCenter(const Pnt3f &c)
{
    _center = c;
}

/// set just the radius
inline
void SphereVolume::setRadius(float r)
{
    _radius = r;
}

/*------------------------- get values -------------------------------*/

/// Returns the center
inline
void SphereVolume::getCenter(Pnt3f &center) const
{
    center = _center;
}

/// Returns the center
inline
const Pnt3f& SphereVolume::getCenter( void ) const
{
    return _center;
}

/// Returns the radius
inline
float SphereVolume::getRadius() const
{
    return _radius;
}

/*-------------------------- extending ------------------------------------*/

inline
void SphereVolume::extendBy (const Volume &volume)
{
    osg::extend(*this,volume);
}

inline
void SphereVolume::extendBy(const SphereVolume &volume)
{
  osg::extend(*this,volume);
}

/*-------------------------- intersection ---------------------------------*/

inline
Bool SphereVolume::intersect (const Volume &volume) const
{
  return osg::intersect(*this,volume);
}

inline
Bool SphereVolume::intersect(const SphereVolume &volume) const
{
  return osg::intersect(*this,volume);
}

OSG_END_NAMESPACE

#endif // SPHEREVOLUME_CLASS_DECLARATIONS
