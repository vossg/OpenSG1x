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
CylinderVolume::CylinderVolume(void) : Volume() 
{
	;
}


/// Construct a cylinder given its axis and radius
CylinderVolume::CylinderVolume(const Pnt3f &p, const Vec3f &d, 
		float r) : Volume(),	_axisPos(p), _axisDir(d), _radius(r) {;}


/// Copy constructor
CylinderVolume::CylinderVolume(const CylinderVolume &c): Volume()
, _axisPos(c._axisPos), _axisDir(c._axisDir), _radius(c._radius) {;}



/// Desctructor	
CylinderVolume::~CylinderVolume(void) 
{
	;
}


/*------------------------------ feature ----------------------------------*/


/// Change the axis and radius
void CylinderVolume::setValue(const Pnt3f &p, const Vec3f &d, float r)
{ 
	_axisPos = p; 
	_axisDir = d; 
	_radius = r; 
}


/// set just the axis 
void CylinderVolume::setAxis(const Pnt3f &p, const Vec3f &d) 
{ 
	_axisPos = p; 
	_axisDir = d; 
}

/// set just the radius
void CylinderVolume::setRadius(float r) 
{ 
	_radius = r; 
}

/// return the axis
void CylinderVolume::getAxis(Pnt3f &apos, Vec3f &adir) const
{
	adir = _axisDir;
	apos = _axisPos;
}
  
/// return the radius
float CylinderVolume::getRadius(void) const 
{ 
	return _radius; 
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
