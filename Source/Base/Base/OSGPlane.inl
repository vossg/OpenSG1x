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

#ifndef _OSGPLANE_INL_
#define _OSGPLANE_INL_

#include "OSGConfig.h"

OSG_BEGIN_NAMESPACE


inline
Real32 Plane::distance(const Pnt3f &pnt) const 
{ 
    return _normalVec.dot(pnt) - _distance; 
}


/*! Set the plane given the normal and distance. 
    The normal needs to be normalized!
 */

inline
void Plane::set(const Vec3f &normal, Real32 distance)
{
    _normalVec = normal;
    _distance = distance;   
}


/*! Set the plane given the (x,y,z) normal and distance
    The normal needs to be normalized!
 */

inline
void Plane::set(Real32 x, Real32 y, Real32 z, Real32 distance)
{
    _normalVec.setValues(x, y, z);

    _distance = distance;    
}


/*! Set the plane given the (x,y,z) normal and distance in a Vec4f
    The normal needs to be normalized!
 */

inline
void Plane::set(const Vec4f &plane)
{
    _normalVec.setValues(plane[0], plane[1], plane[2]);

    _distance = plane[3];    
}


inline
const Vec3f &Plane::getNormal(void) const 
{ 
    return _normalVec; 
}


inline
Real32 Plane::getDistanceFromOrigin(void) const 
{ 
    return _distance; 
}


inline
bool operator!=(const Plane &p1, const Plane &p2)
{ 
    return !(p1 == p2); 
}

OSG_END_NAMESPACE

#endif // _OSGPLANE_INL_
