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

// System declarations

#include "OSGConfig.h"

#ifdef OSG_STREAM_IN_STD_NAMESPACE
#include <iostream>
#else
#include <iostream.h>
#endif

#include <assert.h>

#define OSG_COMPILEBASE

#include "OSGLine.h"
#include "OSGBoxVolume.h"

// Class declarations
#include "OSGSphereVolume.h"

OSG_USING_NAMESPACE

// Static Class Variable implementations: 


/*
//----------------------------------------------------------------------
// Method: circumscribe
// Author: steschne
// Date:   Mon Dec 22 17:38:03 1997
// Description:
//         Return a sphere containing a given box
//----------------------------------------------------------------------
void SphereVolume::circumscribe(const BoxVolume &box)
{
	float radius = 0.5 * (box.getMax() - box.getMin()).length();
	Vec3f center;

	box.getCenter(center);

	setValue(center, radius);
}
*/


//----------------------------------------------------------------------
// Method: initEnclose
// Author: pdaehne
// Date:   Mon Dec 5 14:20:20 1999
// Description:
//----------------------------------------------------------------------
void SphereVolume::initEnclose (const Volume &volume)
{
	assert(false);
}

//----------------------------------------------------------------------
// Method: initInside
// Author: pdaehne
// Date:   Mon Dec 5 14:20:20 1999
// Description:
//----------------------------------------------------------------------
void SphereVolume::initInside (const Volume &volume)
{
	assert(false);
}

//----------------------------------------------------------------------
// Method: getVolume
// Author: steschne
// Date:   Mon Dec 22 17:38:03 1997
// Description:
//----------------------------------------------------------------------
float SphereVolume::getVolume (void) const
{
	return 0;
}

//----------------------------------------------------------------------
// Method: extendBy
// Author: steschne
// Date:   Mon Dec 22 17:38:03 1997
// Description:
//----------------------------------------------------------------------
void SphereVolume::extendBy (const Pnt3f &pt)
{
	return;
}

//----------------------------------------------------------------------
// Method: extendBy
// Author: steschne
// Date:   Mon Dec 22 17:38:03 1997
// Description:
//----------------------------------------------------------------------
void SphereVolume::extendBy (const Volume &volume)
{
	return;
}

//----------------------------------------------------------------------
// Method: extendBy
// Author: steschne
// Date:   Mon Dec 22 17:38:03 1997
// Description:
//----------------------------------------------------------------------
void SphereVolume::extendBy (const SphereVolume &volume)
{
	return;
}

//----------------------------------------------------------------------
// Method: intersect
// Author: steschne
// Date:   Mon Dec 22 17:38:03 1997
// Description:
//----------------------------------------------------------------------
Bool SphereVolume::intersect (const Vec3f &point) const
{
	// TODO; not impl.
	assert(false);
	return false;
}

//----------------------------------------------------------------------
// Method: intersect
// Author: steschne
// Date:   Mon Dec 22 17:38:03 1997
// Description:
//          Intersect line and sphere, 
//          returning true if there is an intersection
//----------------------------------------------------------------------
Bool SphereVolume::intersect( const Line &line ) const
{
	// TODO; not impl.
	assert(false);
	return false;
}

//----------------------------------------------------------------------
// Method: intersect
// Author: steschne
// Date:   Mon Dec 22 17:38:03 1997
// Description:
//          Intersect line and sphere, 
//          returning true if there is an intersection
//----------------------------------------------------------------------
Bool SphereVolume::intersect( const Line &line, 
																	  Vec3f &min, 
																	  Vec3f &max ) const
{
	// TODO; not impl.
	assert(false);
	return false;
}

//----------------------------------------------------------------------
// Method: intersect
// Author: steschne
// Date:   Mon Dec 22 17:38:03 1997
// Description:
//----------------------------------------------------------------------
Bool SphereVolume::intersect (const Volume &volume) const
{
	// TODO; not impl.
	assert(false);
	return false;
}

//----------------------------------------------------------------------
// Method: intersect
// Author: steschne
// Date:   Mon Dec 22 17:38:03 1997
// Description:
//----------------------------------------------------------------------
Bool SphereVolume::intersect(const SphereVolume &sphere) const
{
	float distance = getRadius() + sphere.getRadius();
	float currentDistance = 0; // (sphere.getCenter() - getCenter()).length();

	if (currentDistance < distance)
		return true;
	else
		return false;
}

//----------------------------------------------------------------------
// Method: transform
// Author: steschne
// Date:   Mon Dec 22 17:38:03 1997
// Description:
//----------------------------------------------------------------------
void SphereVolume::transform (const Matrix &mat)
{
	// TODO; not impl.
	assert(false);
}
