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

/*-------------------------- constructor ----------------------------------*/
inline
SphereVolume::SphereVolume(void) : Volume(), _radius(0) {;}

inline
SphereVolume::SphereVolume(const SphereVolume &obj) 
 : Volume(),	_center(obj._center), _radius(obj._radius) { setEmpty(false);}

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

/*-------------------------- operation ------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

OSG_END_NAMESPACE

#endif // SPHEREVOLUME_CLASS_DECLARATIONS
