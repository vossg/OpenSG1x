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


/*! Calc the distance from the point to the Plane.
*/
inline
Real32 Plane::distance(const Pnt3f &pnt) const 
{ 
    return _normalVec.dot(pnt) - _distance; 
}

/*! Check if the point is on the plane.
*/
inline
bool Plane::isOnPlane(const Pnt3f &point) const
{
    Real32 scalar = _normalVec.dot(point) - _distance;

    return osgabs(scalar) < Eps ? true : false;
}


/*! Check if the point is in the Plane's halfspace.
*/
inline
bool Plane::isInHalfSpace(const Pnt3f &point) const
{
    Real32 scalar = _normalVec.dot(point) - _distance;

    return scalar >= 0 ? true : false;
}

/*! Check if the box formed by min/max is fully in the Plane's halfspace.
*/
inline 
bool Plane::isInHalfSpace(const Pnt3f  &min, const Pnt3f  &max) const
{
    Pnt3f p;
    
    setDirectionIndexPoint(min, max, _directionIndex, p);
    
    return isInHalfSpace(p);
}

/*! Check if the box formed by min/max is fully outside the Plane's halfspace.
*/
inline 
bool Plane::isOutHalfSpace(const Pnt3f  &min, const Pnt3f  &max) const
{
    Pnt3f p;
    
    setDirectionIndexPoint(min, max, _directionIndex ^ 7, p);
    
    return !isInHalfSpace(p);   
}


/*! Set the plane given the normal and distance. 
    The normal needs to be normalized!
 */
inline
void Plane::set(const Vec3f &normal, Real32 distance)
{
    _normalVec = normal;
    _distance = distance;   

    updateDirectionIndex();
}


/*! Set the plane given the (x,y,z) normal and distance
    The normal needs to be normalized!
 */

inline
void Plane::set(Real32 x, Real32 y, Real32 z, Real32 distance)
{
    _normalVec.setValues(x, y, z);

    _distance = distance;    

    updateDirectionIndex();
}


/*! Set the plane given the (x,y,z) normal and distance in a Vec4f
    The normal needs to be normalized!
 */

inline
void Plane::set(const Vec4f &plane)
{
    _normalVec.setValues(plane[0], plane[1], plane[2]);

    _distance = plane[3];    

    updateDirectionIndex();
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

inline
void Plane::setDirectionIndexPoint(const Pnt3f &min, const Pnt3f & max,
                                   const UInt8 index,      Pnt3f &pnt) const
{
    if(index & 0x1)
    {
        pnt[0] = min[0];
    }
    else
    {
        pnt[0] = max[0];
    }

    if(index & 0x2)
    {
        pnt[1] = min[1];
    }
    else
    {
        pnt[1] = max[1];
    }

    if(index & 0x4)
    {
        pnt[2] = min[2];
    }
    else
    {
        pnt[2] = max[2];
    }
}


OSG_END_NAMESPACE

#endif // _OSGPLANE_INL_
