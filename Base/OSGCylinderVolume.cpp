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

#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif


#include <assert.h>

#define OSG_COMPILEBASE

// Application declarations

#include <OSGPlane.h>
#include <OSGVolume.h>

// Class declarations
#include "OSGCylinderVolume.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                               Types                                     *
\***************************************************************************/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/

/**  */
void CylinderVolume::getCenter(Pnt3f &center) const 
{ 
	center = _axisPos + _axisDir * .5;
}

/**  */
float CylinderVolume::getVolume(void) const
{ 
    return _radius * _radius * Pi * _axisDir.length();
}

/** gives the boundaries of the volume */
void CylinderVolume::getBounds( Pnt3f &min, Pnt3f &max ) const
{
	// this is rather simpleminded, but good enough for now
	
	if ( _axisDir[0] < 0 )
	{
		min[0] = _axisPos[0] + _axisDir[0] - _radius;
		max[0] = _axisPos[0] - _axisDir[0] + _radius;
	}
	else
	{
		min[0] = _axisPos[0] - _axisDir[0] - _radius;
		max[0] = _axisPos[0] + _axisDir[0] + _radius;
	}
	
	if ( _axisDir[1] < 0 )
	{
		min[1] = _axisPos[1] + _axisDir[1] - _radius;
		max[1] = _axisPos[1] - _axisDir[1] + _radius;
	}
	else
	{
		min[1] = _axisPos[1] - _axisDir[1] - _radius;
		max[1] = _axisPos[1] + _axisDir[1] + _radius;
	}
	
	if ( _axisDir[2] < 0 )
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

void CylinderVolume::initEnclose (const Volume &volume)
{
	assert(false);
}

void CylinderVolume::initInside (const Volume &volume)
{
	assert(false);
}

/*-------------------------- extending ------------------------------------*/

/** extends (if necessary) to contain the given 3D point */
void CylinderVolume::extendBy (const Pnt3f &pt)
{
	assert(false);
}

void CylinderVolume::extendBy (const Volume &volume)
{
	assert(false);
}

/*-------------------------- intersection ---------------------------------*/
	
/** Returns true if intersection of given point and CylinderVolume is not empty */
Bool CylinderVolume::intersect (const Pnt3f &point) const
{
	Real32 dist = Line(_axisPos, _axisDir).distance( point );

	if ( dist > _radius )
		return false;
		
	Plane bottom( _axisDir, _axisPos), top( -_axisDir, _axisPos + _axisDir );
	
	Bool inspace = bottom.isInHalfSpace( point ) && top.isInHalfSpace( point );
	
	return inspace;
}


/** intersect the CylinderVolume with the given Line */
Bool CylinderVolume::intersect ( const Line &line ) const
{
	return line.intersect(*this);
}

/** intersect the volume with the given Line */
Bool CylinderVolume::intersect ( const Line &line,
		 Real32 &enter, Real32 &exit ) const
{
		return line.intersect(*this, enter, exit);
}

 /** intersect the CylinderVolume with another Volume */
Bool CylinderVolume::intersect (const Volume &volume) const
{
	// TODO; not impl.
	assert(false);
	return false;
}

 /** intersect the CylinderVolume with another CylinderVolume */
Bool CylinderVolume::intersect (const CylinderVolume &volume) const
{
	// TODO; not impl.
	assert(false);
	return false;
}

Bool CylinderVolume::isOnSurface (const Pnt3f &point) const
{
	Real32 dist = Line(_axisPos, _axisDir).distance( point );

	if ( dist > _radius )
		return false;
		
	Plane bottom( -_axisDir, _axisPos), top( _axisDir, _axisPos + _axisDir );
	
	Bool onplane = bottom.isOnPlane( point ) || top.isOnPlane( point );
	
	return	( onplane && dist <= _radius ) || 
			( !onplane && osgabs( dist - _radius ) < Eps );
}

/*-------------------------- transformation -------------------------------*/

/** transform volume by the given matrix */
void CylinderVolume::transform (const Matrix &mat)
{
	assert(false);
}

/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/
