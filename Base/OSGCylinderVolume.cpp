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

// Class declarations
#include "OSGCylinderVolume.h"

OSG_USING_NAMESPACE

// Static Class Variable implementations: 

//----------------------------------------------------------------------
// Method: getCenter
// Author: pdaehne
// Date:   Mon Dec 5 14:20:20 1999
// Description:
//         Change the axis and radius
//----------------------------------------------------------------------
void CylinderVolume::getCenter(Vec3f &center) const 
{ 
	assert(false);
}

//----------------------------------------------------------------------
// Method: getVolume
// Author: pdaehne
// Date:   Mon Dec 5 14:20:20 1999
// Description:
//         Change the axis and radius
//----------------------------------------------------------------------
float CylinderVolume::getVolume(void) const
{ 
	assert(false);
    return 0.;
}

//----------------------------------------------------------------------
// Method: initEnclose
// Author: pdaehne
// Date:   Mon Dec 5 14:20:20 1999
// Description:
//----------------------------------------------------------------------
void CylinderVolume::initEnclose (const Volume &volume)
{
	assert(false);
}

//----------------------------------------------------------------------
// Method: initInside
// Author: pdaehne
// Date:   Mon Dec 5 14:20:20 1999
// Description:
//----------------------------------------------------------------------
void CylinderVolume::initInside (const Volume &volume)
{
	assert(false);
}

//----------------------------------------------------------------------
// Method: intersect
// Author: pdaehne
// Date:   Mon Dec 5 14:20:20 1999
// Description:
//         TODOC
//----------------------------------------------------------------------
Bool CylinderVolume::intersect (const Vec3f &point) const
{
	assert(false);
	return false;
}


//----------------------------------------------------------------------
// Method: intersect
// Author: pdaehne
// Date:   Mon Dec 5 14:20:20 1999
// Description:
//         TODOC
//----------------------------------------------------------------------
Bool CylinderVolume::intersect ( const Line &line ) const
{
  // TODO
  assert(false);
  return false;
}

//----------------------------------------------------------------------
// Method: intersect
// Author: pdaehne
// Date:   Mon Dec 5 14:20:20 1999
// Description:
//         TODOC
//----------------------------------------------------------------------
Bool CylinderVolume::intersect ( const Line &line,
																			 Vec3f &min, Vec3f &max ) const
{
  // TODO
  assert(false);
  return false;
}

//----------------------------------------------------------------------
// Method: intersect
// Author: pdaehne
// Date:   Mon Dec 5 14:20:20 1999
// Description:
//         TODOC
//----------------------------------------------------------------------
Bool CylinderVolume::intersect (const Volume &volume) const
{
	// TODO; not impl.
	assert(false);
	return false;
}

//----------------------------------------------------------------------
// Method: intersect
// Author: pdaehne
// Date:   Mon Dec 5 14:20:20 1999
// Description:
//         TODOC
//----------------------------------------------------------------------
Bool CylinderVolume::intersect (const CylinderVolume &volume) const
{
	// TODO; not impl.
	assert(false);
	return false;
}


//----------------------------------------------------------------------
// Method: extendBy
// Author: pdaehne
// Date:   Mon Dec 5 14:20:20 1999
// Description:
//         TODOC
//----------------------------------------------------------------------
void CylinderVolume::extendBy (const Pnt3f &pt)
{
}

//----------------------------------------------------------------------
// Method: extendBy
// Author: pdaehne
// Date:   Mon Dec 5 14:20:20 1999
// Description:
//         TODOC
//----------------------------------------------------------------------
void CylinderVolume::extendBy (const Volume &volume)
{
}


//----------------------------------------------------------------------
// Method: transform
// Author: pdaehne
// Date:   Mon Dec 5 14:20:20 1999
// Description:
//         TODOC
//----------------------------------------------------------------------
void CylinderVolume::transform (const Matrix &mat)
{
	;
}
