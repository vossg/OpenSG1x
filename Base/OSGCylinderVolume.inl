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

#ifndef _OSGCYLINDERVOLUME_INL_
#define _OSGCYLINDERVOLUME_INL_

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <OSGCylinderVolume.h>
#include "OSGLine.h"
#include "OSGVolume.h"

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

/*-------------------------------------------------------------------------*\
 -  public                                                                 -
\*-------------------------------------------------------------------------*/


/*! Default Constructor
*/
inline
CylinderVolume::CylinderVolume(void) : Volume() 
{
	;
}


/// Construct a cylinder given its axis and radius
inline
CylinderVolume::CylinderVolume(const Pnt3f &p, const Vec3f &d, 
		float r) : Volume(),	_axisPos(p), _axisDir(d), _radius(r) { setEmpty(false);}


/// Copy constructor
inline
CylinderVolume::CylinderVolume(const CylinderVolume &c): Volume(c)
, _axisPos(c._axisPos), _axisDir(c._axisDir), _radius(c._radius) {;}



/// Desctructor	

inline
CylinderVolume::~CylinderVolume(void) 
{
	;
}


/*------------------------------ feature ----------------------------------*/


/// Change the axis and radius
inline
void CylinderVolume::setValue(const Pnt3f &p, const Vec3f &d, float r)
{ 
	_axisPos = p; 
	_axisDir = d; 
	_radius = r; 
}


/// set just the axis 
inline
void CylinderVolume::setAxis(const Pnt3f &p, const Vec3f &d) 
{ 
	_axisPos = p; 
	_axisDir = d; 
}

/// set just the radius
inline
void CylinderVolume::setRadius(float r) 
{ 
	_radius = r; 
}

/// return the axis
inline
void CylinderVolume::getAxis(Pnt3f &apos, Vec3f &adir) const
{
	adir = _axisDir;
	apos = _axisPos;
}
  
/// return the radius
inline
float CylinderVolume::getRadius(void) const 
{ 
	return _radius; 
}

/*-------------------------- extending ------------------------------------*/

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

/*-------------------------- intersection ---------------------------------*/

inline
Bool CylinderVolume::intersect (const Volume &volume) const
{
  return OSG::intersect(*this,volume);
}

inline
Bool CylinderVolume::intersect(const CylinderVolume &volume) const
{
  return OSG::intersect(*this,volume);
}


/*-------------------------------------------------------------------------*\
 -  protected                                                              -
\*-------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------*\
 -  private                                                                -
\*-------------------------------------------------------------------------*/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

OSG_END_NAMESPACE

#endif //CYLINDERVOLUME_CLASS_DECLARATION
