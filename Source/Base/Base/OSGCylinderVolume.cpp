/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
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

#include "OSGConfig.h"

#include <assert.h>

#include <OSGPlane.h>
#include <OSGVolume.h>

#include "OSGCylinderVolume.h"

OSG_USING_NAMESPACE


void CylinderVolume::getCenter(Pnt3f &center) const
{
    center = _axisPos + _axisDir * .5;
}


Real32 CylinderVolume::getScalarVolume(void) const
{
    return isEmpty() ? 0.0f : (_radius * _radius * Pi * _axisDir.length());
}

/*! gives the boundaries of the volume */

void CylinderVolume::getBounds(Pnt3f &min, Pnt3f &max) const
{
    // this is rather simpleminded, but good enough for now

    if(_axisDir[0] < 0)
    {
        min[0] = _axisPos[0] + _axisDir[0] - _radius;
        max[0] = _axisPos[0] - _axisDir[0] + _radius;
    }
    else
    {
        min[0] = _axisPos[0] - _axisDir[0] - _radius;
        max[0] = _axisPos[0] + _axisDir[0] + _radius;
    }

    if(_axisDir[1] < 0)
    {
        min[1] = _axisPos[1] + _axisDir[1] - _radius;
        max[1] = _axisPos[1] - _axisDir[1] + _radius;
    }
    else
    {
        min[1] = _axisPos[1] - _axisDir[1] - _radius;
        max[1] = _axisPos[1] + _axisDir[1] + _radius;
    }

    if(_axisDir[2] < 0)
    {
        min[2] = _axisPos[2] + _axisDir[2] - _radius;
        max[2] = _axisPos[2] - _axisDir[2] + _radius;
    }
    else
    {
        min[2] = _axisPos[2] - _axisDir[2] - _radius;
        max[2] = _axisPos[2] + _axisDir[2] + _radius;
    }
}

/*-------------------------- extending ------------------------------------*/

#ifdef __sgi
#pragma set woff 1209
#endif

/*! extends (if necessary) to contain the given 3D point */

void CylinderVolume::extendBy(const Pnt3f &OSG_CHECK_ARG(pt))
{
    assert(false);
}


void CylinderVolume::extendBy(const Volume &volume)
{
  OSG::extend(*this, volume);
}

#ifdef __sgi
#pragma reset woff 1209
#endif


/*-------------------------- intersection ---------------------------------*/

/*! Returns true if intersection of given point and CylinderVolume 
    is not empty
*/

bool CylinderVolume::intersect(const Pnt3f &point) const
{
    Real32 dist = Line(_axisPos, _axisDir).distance(point);

    if(dist > _radius)
        return false;

    Plane bottom( _axisDir, _axisPos           );
    Plane top   (-_axisDir, _axisPos + _axisDir);

    bool inspace = bottom.isInHalfSpace(point) && top.isInHalfSpace(point);

    return inspace;
}


/*! intersect the CylinderVolume with the given Line */

bool CylinderVolume::intersect(const Line &line) const
{
    return line.intersect(*this);
}

/*! intersect the volume with the given Line */

bool CylinderVolume::intersect(const Line   &line,
                                     Real32 &enter, 
                                     Real32 &exit ) const
{
    return line.intersect(*this, enter, exit);
}

bool CylinderVolume::intersect(const Volume &volume) const
{
    return OSG::intersect(*this,volume);
}


bool CylinderVolume::isOnSurface(const Pnt3f &point) const
{
    Real32 dist = Line(_axisPos, _axisDir).distance(point);

    if(dist > _radius)
        return false;
    
    Plane bottom(-_axisDir, _axisPos           );
    Plane top   ( _axisDir, _axisPos + _axisDir);

    bool onplane = bottom.isOnPlane(point) || top.isOnPlane(point);

    return  ( onplane &&  dist <= _radius            ) ||
            (!onplane && osgabs(dist - _radius) < Eps);
}

/*-------------------------- transformation -------------------------------*/

#ifdef __sgi
#pragma set woff 1209
#endif

/*! transform volume by the given matrix */

void CylinderVolume::transform(const Matrix &OSG_CHECK_ARG(mat))
{
    assert(false);
}

#ifdef __sgi
#pragma reset woff 1209
#endif

//! print the volume 

void CylinderVolume::dump(      UInt32    OSG_CHECK_ARG(uiIndent), 
                          const BitVector OSG_CHECK_ARG(bvFlags )) const
{
    PLOG << "Cylinder(" 
         << _axisPos 
         << "|" 
         << _axisDir
         << "|" 
         << _radius
         << ")";
}

