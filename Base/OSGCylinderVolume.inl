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

#ifndef _OSGCYLINDERVOLUME_INL_
#define _OSGCYLINDERVOLUME_INL_

#include <OSGCylinderVolume.h>
#include "OSGLine.h"
#include "OSGVolume.h"

OSG_BEGIN_NAMESPACE

/*! Default Constructor
*/
inline
CylinderVolume::CylinderVolume(void) : Volume()
{
    ;
}

inline
CylinderVolume::CylinderVolume(const Pnt3f &p, const Vec3f &d,
        float r) : Volume(),    _axisPos(p), _axisDir(d), _radius(r) { setEmpty(false);}

inline
CylinderVolume::CylinderVolume(const CylinderVolume &c): Volume(c)
, _axisPos(c._axisPos), _axisDir(c._axisDir), _radius(c._radius) {;}

inline
CylinderVolume::~CylinderVolume(void)
{
    ;
}

inline
void CylinderVolume::setValue(const Pnt3f &p, const Vec3f &d, float r)
{
    _axisPos = p;
    _axisDir = d;
    _radius = r;
}

inline
void CylinderVolume::setAxis(const Pnt3f &p, const Vec3f &d)
{
    _axisPos = p;
    _axisDir = d;
}

inline
void CylinderVolume::setRadius(float r)
{
    _radius = r;
}

inline
void CylinderVolume::getAxis(Pnt3f &apos, Vec3f &adir) const
{
    adir = _axisDir;
    apos = _axisPos;
}

inline
float CylinderVolume::getRadius(void) const
{
    return _radius;
}

inline
void CylinderVolume::extendBy(const Volume &volume)
{
  OSG::extend(*this,volume);
}

inline
void CylinderVolume::extendBy(const CylinderVolume &volume)
{
    OSG::extend(*this,volume);
}

inline
bool CylinderVolume::intersect (const Volume &volume) const
{
  return OSG::intersect(*this,volume);
}

inline
bool CylinderVolume::intersect(const CylinderVolume &volume) const
{
  return OSG::intersect(*this,volume);
}

OSG_END_NAMESPACE

#endif //CYLINDERVOLUME_CLASS_DECLARATION
