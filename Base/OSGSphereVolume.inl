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


#ifndef _OSGSPHEREVOLUME_INL_
#define _OSGSPHEREVOLUME_INL_

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGVolume.h>

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


/*------------------------------ feature ----------------------------------*/

/// Change the center and radius
inline
void SphereVolume::setValue(const Pnt3f &c, float r)
{ 
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

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

OSG_END_NAMESPACE

#endif // SPHEREVOLUME_CLASS_DECLARATIONS
